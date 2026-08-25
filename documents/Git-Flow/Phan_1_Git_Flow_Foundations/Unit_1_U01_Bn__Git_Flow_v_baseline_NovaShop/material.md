# Unit U01: Bản đồ Git Flow và baseline NovaShop — Học liệu cốt lõi

> **Khóa học:** Git Flow thực chiến qua dự án NovaShop · **Phần:** Git Flow Foundations · **Thực hành:** Git trên artifact Markdown/CSV, không viết mã nguồn ứng dụng · **Mức xác thực:** simulated

## 🎯 Learning Outcomes

- **LO1.1 — Analyze:** Phân loại đúng vai trò, nguồn, đích và vòng đời của `main`, `develop`, `feature`, `release`, `hotfix` trong ít nhất 8/10 tình huống NovaShop. Bằng chứng: branch-routing decision table và graph có giải thích.
- **LO1.2 — Apply:** Khởi tạo baseline repo tài liệu NovaShop có `main`, `develop`, tag mốc và policy kiểm chứng được. Bằng chứng: Git refs, branch graph và baseline checklist.

## 🧭 Ngữ cảnh nghề nghiệp/dự án và phần tăng trưởng của Unit

NovaShop là MVP thương mại điện tử B2C mô phỏng. Trong Unit này, bạn đóng vai thành viên Scrum Team phụ trách quản lý thay đổi. Đầu vào là project brief và Product Backlog synthetic chưa được version hóa. Đầu ra tại **M-GF-01** là ba artifact nghề nghiệp:

1. baseline branch graph có `main`, `develop` và tag mốc;
2. branch-routing decision table phân loại được thay đổi NovaShop;
3. Git Flow working agreement nêu vai trò branch, review gate, quy tắc evidence và giới hạn áp dụng.

Increment đạt khi `main` đại diện mốc ổn định, `develop` đại diện dòng tích hợp kế tiếp, tag baseline truy vấn được, working tree sạch và policy không tạo branch môi trường chỉ vì tên môi trường. Artifact này được dùng lại ở U02 để định tuyến feature NS-101/NS-102, và về sau để audit release/hotfix.

## 📚 Nguồn đầu vào đã map

- **SRC-GIT-DOC:** Git Reference Manual 2.54.0, Git Project / Software Freedom Conservancy, truy cập 2026-08-25.
- **SRC-PROGIT:** Pro Git, 2nd Edition, living web edition, truy cập 2026-08-25.
- **SRC-NVIE:** Vincent Driessen, *A successful Git branching model*, bản gốc 2010, lưu ý phản tư 2020, truy cập 2026-08-25.
- **SRC-VIBLO:** KhanhVQ, *Cơ bản về Gitflow Workflow*, 2020-10-23, truy cập 2026-08-25.
- **SRC-NS-BRIEF:** NovaShop simulated e-commerce project brief, version 1.0, internal approved.

Nội dung dưới đây diễn giải độc lập. Không tái phân phối sơ đồ hay văn bản của nguồn bên thứ ba.

---

## 1. Kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết

- Không cần biết Git Flow trước đó; cần đọc được PBI/acceptance criteria và chỉnh sửa Markdown/CSV.
- Cần biết mở terminal tại đúng thư mục, sao chép output lệnh vào file evidence và phân biệt dữ liệu synthetic với dữ liệu thật.
- Tuyệt đối không dùng credential, remote production, thông tin thẻ hoặc PII trong repository học tập.

### Môi trường, công cụ và phiên bản

- **Profile:** `ENV-GIT-ARTIFACT`.
- **Git CLI:** 2.40 trở lên; course verification dùng 2.54.0.windows.1.
- **Editor:** hỗ trợ Markdown CommonMark và CSV UTF-8.
- **Phạm vi:** repo Git local cô lập chỉ chứa artifact; không có mã nguồn ứng dụng hoặc dịch vụ cloud.

Preflight:

```text
git --version
git config --get user.name
git config --get user.email
```

Trong repo Lab, danh tính được cấu hình ở scope `--local` với email giả thuộc miền `example.invalid`.

### Phương thức xác minh artifact

`artifact_review`: reviewer đối chiếu decision table, working agreement và output Git với oracle được nêu rõ; không coi ảnh chụp đơn lẻ là đủ nếu thiếu ref hoặc lệnh tạo ra kết luận.

### Hợp đồng ví dụ triển khai và thực hành

- **Mode:** `professional_artifact`.
- **Rationale:** năng lực cần đánh giá là quyết định workflow và bằng chứng Git trên Markdown/CSV; không có LO viết hoặc chạy mã nguồn ứng dụng.
- **Worked example:** `MEX-U01-01` phủ `OUT-U01-01`–`OUT-U01-03`, `LO1.1`–`LO1.2`, và được biến đổi trong `LAB-U01-01/CP-U01-01`–`CP-U01-03`.

## 2. Định vị trong lộ trình (Mental Map)

Git Flow là **policy sử dụng các ref Git**, không phải một loại object mới và không phải thành phần bắt buộc của Scrum. Mental model xuyên Unit:

```text
Nhu cầu thay đổi
      ↓ phân loại theo trạng thái sản phẩm cần thay đổi
feature ← develop → release → main → tag phát hành
                       ↘ develop
production incident: main → hotfix → main + develop (hoặc release đang mở)
      ↓
evidence = graph + ref containment + decision/review record
```

U01 dạy cách đọc bản đồ và thiết lập baseline. U02 dùng bản đồ để đưa một PBI qua feature flow; U04/U05 mới vận hành release và hotfix đầy đủ. Vì vậy ở U01, mục tiêu là **phân loại đúng và chứng minh topology**, chưa phải mô phỏng mọi release.

## 3. Nội dung lý thuyết cốt lõi

**📋 Checklist bắt buộc phủ — giữ nguyên văn và đúng thứ tự Content Outlines:**

- [x] Snapshot, commit, HEAD, branch, merge và tag như một đồ thị kiểm toán
- [x] Vai trò, nguồn, đích và vòng đời của main, develop, feature, release và hotfix
- [x] Điều kiện áp dụng Git Flow, phép đổi master thành main và policy baseline NovaShop

#### OUT-U01-01 — Snapshot, commit, HEAD, branch, merge và tag như một đồ thị kiểm toán

**Mapping:** Outline `OUT-U01-01` · LO `LO1.1`, `LO1.2` · Milestone `M-GF-01` · Artifact: baseline graph và ref evidence.

##### Định nghĩa rõ ràng

- **Snapshot** là trạng thái nội dung được Git ghi nhận ở một thời điểm. Git mô hình hóa lịch sử thành chuỗi snapshot, không chỉ là danh sách các dòng chênh lệch.
- **Commit** là object trỏ tới snapshot, metadata và commit cha. Commit thường có một cha; merge commit có từ hai cha; commit đầu tiên không có cha.
- **Branch** là ref có thể di chuyển, trỏ tới một commit. Tên `main` hay `develop` không mang đặc quyền kỹ thuật; ý nghĩa đến từ team policy.
- **HEAD** là ref tượng trưng cho vị trí đang checkout. Khi HEAD gắn với một branch, commit mới làm branch đó tiến lên.
- **Merge** kết hợp lịch sử. Khi hai dòng đã phân kỳ và policy yêu cầu giữ ranh giới, merge commit cung cấp two-parent evidence; khi không phân kỳ, Git có thể fast-forward ref.
- **Tag** là tên cho một object, thường là một commit. Tag dùng làm mốc ổn định; trong khóa này, mốc phát hành và baseline dùng annotated tag để có annotation kiểm toán.

Ranh giới quan trọng: branch là con trỏ **di chuyển** theo commit; tag phát hành là mốc được kỳ vọng **không di chuyển**; working tree chỉ là bản đang làm việc, chưa phải evidence lịch sử cho tới khi nội dung được commit.

##### Vấn đề/vai trò và quyết định cần đưa ra

Release Owner cần trả lời “trạng thái nào đã được ghi nhận, ref nào đang trỏ tới nó và một ref có chứa commit cần kiểm toán hay không?”. Người học phải quyết định loại evidence phù hợp:

- dùng `git status` để chứng minh working state;
- dùng `git log --graph` để đọc ancestry;
- dùng `git show-ref` để liệt kê ref;
- dùng `git merge-base --is-ancestor A B` để kiểm tra commit/ref A có nằm trong lịch sử B;
- dùng `git cat-file -t <tag-name>` hoặc `git show <tag-name>` để phân biệt/đọc tag.

Ảnh graph đẹp không thay thế containment oracle; ngược lại, exit code containment không giải thích vì sao branch được định tuyến như vậy. Audit pack cần cả state evidence và decision rationale.

##### Cơ chế và mental model

Hãy hình dung commit graph là các nút có mũi tên ngược về cha. Ref chỉ là nhãn đặt trên một nút:

```text
A---B  main, baseline-0.0.0
     \
      C  develop, HEAD
```

Tạo `develop` từ `main` ban đầu chỉ tạo thêm ref cùng trỏ B. Commit policy trên `develop` làm ref này tiến tới C; `main` và tag vẫn ở B. Khi merge một feature về `develop`, graph hoặc di chuyển ref, hoặc thêm merge commit tùy lịch sử và option. Xóa feature branch chỉ xóa nhãn; commit đã được merge vẫn reachable từ `develop`.

##### Khi dùng / khi không dùng

Dùng graph/ref/containment khi cần chứng minh nguồn branch, nội dung đã được hợp nhất, mốc release hoặc back-merge. Dùng diff khi cần biết nội dung thay đổi. Không dùng số lượng commit làm bằng chứng chất lượng; nhiều commit không đồng nghĩa nhiều giá trị. Không dùng tên branch để suy ra ancestry: branch tên `feature/...` vẫn có thể bị tạo nhầm từ `main`.

Trade-off: `--no-ff` làm lịch sử có thêm merge commit nhưng giữ ranh giới feature dễ quan sát; fast-forward gọn hơn nhưng có thể làm mất dấu nhóm commit nếu chỉ nhìn graph. Đây là policy cần nhất quán, không phải chân lý cho mọi team.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** Release Owner kiểm tra baseline NovaShop trước khi nhóm bắt đầu NS-101.
- **Input/baseline/constraint:** commit B chứa project brief/backlog; `main` và tag `baseline-0.0.0` phải ở B; `develop` có thêm commit C chứa working agreement; repo chỉ dùng dữ liệu synthetic.
- **Decision/action:** dùng graph để đọc cấu trúc và containment để chứng minh B là ancestor của C; không kết luận chỉ từ tên ref.
- **Artifact/output:** `evidence/M-GF-01/graph.txt`, `refs.txt`, `containment.txt`.
- **Expected result:** `main` và tag cùng trỏ baseline; `develop` chứa baseline và commit policy; working tree sạch.
- **Verification/oracle:** `git merge-base --is-ancestor main develop` trả exit code 0; `git show-ref --heads --tags` có đủ ba ref; `git status --short` không in dòng file thay đổi.

##### Ví dụ triển khai trong Material — professional artifact

Leaf này cung cấp lớp “evidence” của **MEX-U01-01** ở mục 4. Ba output bắt buộc là status, graph và refs. `LAB-U01-01/CP-U01-01` tái tạo baseline trên input khác; `CP-U01-02` diễn giải graph; `CP-U01-03` chẩn đoán một ref ngoài policy.

##### Best practices

- **Rule:** luôn ghi cả lệnh, thời điểm kiểm tra và output đã redact. **Rationale:** output không có context không thể tái lập kết luận. **Positive:** `containment.txt` ghi `git merge-base --is-ancestor main develop`, exit code 0 và ref được kiểm. **Negative:** ảnh terminal bị cắt tên branch khiến reviewer không biết A/B là gì; audit bị đánh `REVISE`.
- **Rule:** kiểm tra working tree sạch trước khi switch/merge/tag. **Rationale:** thay đổi chưa commit có thể làm switch bị chặn hoặc trộn input ngoài ý muốn. **Positive:** status rỗng rồi mới tạo `develop`. **Negative:** file backlog chưa stage bị bỏ quên; tag không đại diện baseline dự kiến.
- **Rule:** dùng annotated tag cho mốc audit theo policy NovaShop. **Rationale:** tag object lưu annotation/tagger và phân biệt rõ với ref nhẹ. **Positive:** `git cat-file -t baseline-0.0.0` trả `tag`. **Negative:** lightweight tag trả `commit`; gate tag audit không đạt.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** `git status` báo detached HEAD. **Nguyên nhân:** checkout trực tiếp tag/commit. **Chẩn đoán:** `git branch --show-current` không trả tên. **Sửa:** switch sang branch đúng trước khi commit. **Phòng tránh:** preflight luôn ghi current branch.
- **Dấu hiệu:** graph có tên đúng nhưng containment fail. **Nguyên nhân:** branch được tạo từ ref sai hoặc ref bị di chuyển. **Chẩn đoán:** so `git merge-base` với SHA baseline đã lưu. **Sửa:** nếu branch chưa chia sẻ, tạo branch mới từ ref đúng và chuyển artifact hợp lệ; không force-push shared history. **Phòng tránh:** lưu `git rev-parse develop` trước khi mở work.
- **Dấu hiệu:** tag tồn tại nhưng type là `commit`. **Nguyên nhân:** tạo lightweight tag. **Chẩn đoán:** `git cat-file -t <tag-name>`. **Sửa:** chỉ thay tag trong repo Lab khi chưa công bố và có reviewer đồng ý; nếu đã công bố, tạo mốc sửa theo policy thay vì âm thầm di chuyển tag. **Phòng tránh:** dùng `git tag -a` và audit type ngay khi tạo.

#### OUT-U01-02 — Vai trò, nguồn, đích và vòng đời của main, develop, feature, release và hotfix

**Mapping:** Outline `OUT-U01-02` · LO `LO1.1` · Milestone `M-GF-01` · Artifact: branch-routing decision table và working agreement.

##### Định nghĩa rõ ràng

Git Flow dùng hai branch dài hạn và ba loại branch hỗ trợ có vòng đời hữu hạn:

| Loại branch | Vai trò trạng thái | Nguồn hợp lệ | Đích kết thúc | Vòng đời |
| --- | --- | --- | --- | --- |
| `main` | Mốc production-ready/release đã công bố | nhận release hoặc hotfix đã duyệt | không “merge kết thúc” sang branch khác theo định kỳ; fix phải truyền lại dòng tương lai | dài hạn |
| `develop` | Tích hợp thay đổi cho release kế tiếp | khởi tạo từ `main`; nhận feature và release/hotfix propagation | tạo release; tiếp tục nhận feature | dài hạn |
| `feature/<issue-id>-<slug>` | Một capability/change có scope theo PBI | `develop` tại thời điểm bắt đầu | `develop` hoặc bị loại bỏ nếu thử nghiệm không được chọn | hữu hạn |
| `release/<semver>` | Ổn định scope đã chọn, UAT fix và metadata phát hành | `develop` | `main` và `develop` | hữu hạn |
| `hotfix/<semver>-<slug>` | Sửa khẩn trạng thái production đã phát hành | `main`/production tag tương ứng | `main` và dòng tương lai phù hợp (`develop` hoặc release đang mở) | hữu hạn |

“Nguồn” là ref làm base khi tạo branch; “đích” là nơi thay đổi phải được tích hợp khi kết thúc. Đây là policy topology. Git không tự biết một branch là feature hay hotfix.

##### Vấn đề/vai trò và quyết định cần đưa ra

Scrum Team cần phân loại thay đổi theo **trạng thái cần tác động**, không theo chức danh người yêu cầu hoặc môi trường deploy:

- capability cho tương lai → feature từ `develop`;
- ổn định scope gần phát hành → release từ `develop`;
- lỗi trên production hiện hành cần sửa khẩn → hotfix từ `main`;
- branch `main`/`develop` là dòng trạng thái, không phải nơi làm việc tùy tiện.

Quyết định gồm: branch type, source, merge target, điều kiện đóng và evidence. Một yêu cầu “hãy tạo branch QC” chưa đủ: phải chứng minh trạng thái QC có vòng đời/ownership khác biệt và lợi ích vượt merge cost.

##### Cơ chế và mental model

Topology tạo ra các đường truyền có chủ đích. Feature chỉ đi vào “tương lai” qua `develop`. Release khóa một tập scope để sửa lỗi chuẩn bị phát hành trong khi `develop` có thể tiến tiếp. Hotfix bắt đầu từ “hiện tại production” để không kéo theo thay đổi chưa phát hành, rồi phải truyền fix sang tương lai để tránh hồi quy.

Việc xóa supporting branch sau merge giảm ref rác nhưng không xóa commit reachable. Branch dài hạn mới tạo thêm dòng trạng thái phải đồng bộ vĩnh viễn; mỗi dòng như vậy làm tăng chi phí merge, ownership và nguy cơ drift.

##### Khi dùng / khi không dùng

Dùng đủ năm vai trò khi sản phẩm có release theo phiên bản, cần ổn định release độc lập, hoặc phải hỗ trợ production trong khi phát triển tiếp. Không biến mọi công việc thành release/hotfix: sửa acceptance artifact trước khi scope freeze vẫn là feature. Không tạo branch theo người (`feature/an`) hoặc môi trường (`qc`) nếu không có contract trạng thái độc lập.

Trade-off chính là khả năng kiểm toán và hỗ trợ nhiều dòng đổi lấy thời gian sống branch, merge cost và nguy cơ divergence. Team release liên tục từ một dòng chính thường có thể chọn flow đơn giản hơn.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** Product Owner và Release Owner định tuyến 10 yêu cầu NovaShop trước Sprint 1.
- **Input/baseline/constraint:** backlog có Search, Cart, Checkout, UAT wording fix và incident phí vận chuyển; không có payment thật; mỗi supporting branch phải có điểm đóng.
- **Decision/action:** lập routing table, ghi branch source/target và lý do dựa trên trạng thái bị tác động.
- **Artifact/output:** bảng ở `project-artifacts/M-GF-01/branch-routing.md`.
- **Expected result:** ít nhất 8/10 dòng đúng; cả năm vai trò được phân biệt; không có `feature` từ `main` hoặc `hotfix` từ `develop`.
- **Verification/oracle:** reviewer che cột “decision”, tự phân loại từ scenario rồi so; mỗi dòng phải thỏa source/target/lifecycle table bên trên.

##### Ví dụ triển khai trong Material — professional artifact

Leaf này cung cấp lớp “routing” của **MEX-U01-01** ở mục 4. `LAB-U01-01/CP-U01-01` thay input bằng đề nghị branch `qc`; checkpoint buộc người học dùng decision criteria thay vì sao chép tên branch từ bảng mẫu.

##### Best practices

- **Rule:** định tuyến theo trạng thái cần thay đổi. **Rationale:** source đúng cô lập production khỏi work tương lai. **Positive:** incident sai phí đang ở `main` đi hotfix từ `main`. **Negative:** tạo hotfix từ `develop` kéo cả Admin chưa phát hành vào patch.
- **Rule:** mọi supporting branch phải có owner, exit criteria và target. **Rationale:** branch không có điểm đóng sẽ drift. **Positive:** feature đóng khi DoD/review pass và merge `develop`. **Negative:** `feature/search` sống qua nhiều release, chứa thêm Cart; reviewer không xác định scope.
- **Rule:** không direct commit vào `main`/`develop` theo NovaShop policy. **Rationale:** review record là phần của audit trail. **Positive:** thay đổi baseline ngoại lệ được ghi rõ tại kickoff; sau đó mọi thay đổi qua branch/review. **Negative:** “sửa nhanh” trực tiếp trên `develop` không có PBI/evidence, làm đứt traceability.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** branch tên `hotfix` nhưng commit base nằm trên `develop`. **Nguyên nhân:** phân loại theo mức độ khẩn, không theo production baseline. **Chẩn đoán:** `git merge-base hotfix/... main` và graph. **Sửa:** dừng merge; tạo lại từ production ref đúng trong repo cô lập và chỉ mang scope fix đã review. **Phòng tránh:** routing record được duyệt trước khi tạo branch.
- **Dấu hiệu:** release nhận capability mới sau scope freeze. **Nguyên nhân:** nhầm release branch với integration branch. **Chẩn đoán:** đối chiếu commit/PBI với frozen scope list. **Sửa:** loại thay đổi khỏi release bằng phương pháp không rewrite shared history và đưa về `develop` cho release sau. **Phòng tránh:** release allow-list chỉ gồm release fix/metadata/UAT corrections.
- **Dấu hiệu:** `qc` liên tục thiếu commit từ `develop`. **Nguyên nhân:** thêm branch dài hạn nhưng không có owner/merge contract. **Chẩn đoán:** containment hai chiều và age của divergence. **Sửa:** ngừng dùng branch môi trường nếu không đại diện trạng thái sản phẩm; triển khai từ ref/version được phê duyệt. **Phòng tránh:** architecture decision trước khi thêm long-lived branch.

#### OUT-U01-03 — Điều kiện áp dụng Git Flow, phép đổi master thành main và policy baseline NovaShop

**Mapping:** Outline `OUT-U01-03` · LO `LO1.1`, `LO1.2` · Milestone `M-GF-01` · Artifact: Git Flow working agreement và baseline checklist.

##### Định nghĩa rõ ràng

**Điều kiện áp dụng Git Flow** là tập decision drivers chứng minh lợi ích của nhiều dòng branch lớn hơn chi phí phối hợp. Mô hình gốc dùng `master`; khóa này dùng `main`. Vì branch chỉ là ref thông thường, đổi tên không làm đổi topology: `main` vẫn giữ vai trò production-ready, còn `develop` giữ vai trò integration.

**Policy baseline NovaShop** là hợp đồng có thể kiểm tra, gồm tên branch, source/target, review rule, tag rule, evidence, data safety và exception handling. Git Flow/Conventional Commits là team policy; Scrum Guide không quy định branch, pull request, tag hoặc thời điểm release.

##### Vấn đề/vai trò và quyết định cần đưa ra

Team phải quyết định:

1. có cần Git Flow không, dựa trên cadence, số version hỗ trợ, nhu cầu release stabilization và audit;
2. tên default branch là gì và tài liệu nguồn được ánh xạ ra sao;
3. guardrail nào có oracle thay vì khẩu hiệu;
4. đề nghị thêm branch dài hạn có tạo ra trạng thái sản phẩm độc lập, owner và exit/merge contract hay không.

NovaShop chọn Git Flow cho bài toán mô phỏng release theo phiên bản và hotfix song song. Quyết định này sẽ được đánh giá lại ở U06; không tuyên bố Git Flow là lựa chọn mặc định cho mọi sản phẩm.

##### Cơ chế và mental model

Policy hoạt động như một hàm quyết định:

```text
change state + urgency + release phase + supported versions
→ branch type/source/target
→ required review/acceptance evidence
→ containment/tag oracle
```

Đổi `master` thành `main` chỉ thay token trong policy và lệnh. Mọi nguồn nói `master` được đọc với phép ánh xạ `master ≙ main`; không được đổi ý nghĩa production-ready hoặc cho phép feature bắt đầu từ `main`.

Một policy kiểm chứng được phải biến câu “không commit trực tiếp” thành evidence cụ thể: review record có source/target, finding disposition và merge decision; graph/containment chứng minh kết quả. Branch protection trên hosting có thể hỗ trợ, nhưng khóa local này dùng artifact review tương đương.

##### Khi dùng / khi không dùng

Git Flow phù hợp hơn khi có release định kỳ, release stabilization, nhiều version đang được hỗ trợ hoặc yêu cầu audit rõ. Cân nhắc flow đơn giản hơn khi một phiên bản web được deploy liên tục, thay đổi rất nhỏ và long-lived branch tạo merge queue lớn. Không dùng Sprint boundary để tự động cắt release: Sprint tạo nhịp inspection/adaptation; release cadence là quyết định sản phẩm/kỹ thuật riêng.

Trade-off: policy nghiêm giúp traceability nhưng tạo ceremony và thời gian chờ; policy quá nhẹ giảm overhead nhưng có thể không đủ khi phải duy trì release/hotfix song song. Chọn mức vừa đủ và đo lại bằng lead time/merge cost.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** Sponsor yêu cầu thêm `qc` dài hạn “để test cho chắc”.
- **Input/baseline/constraint:** NovaShop đã có `develop`; QC không có release ownership riêng, không hỗ trợ version riêng và không có exit criteria; môi trường deploy nằm ngoài scope repo artifact.
- **Decision/action:** từ chối tạo `qc`; ghi rằng QC/UAT sử dụng ref của feature hoặc release phù hợp, không tạo trạng thái code dài hạn mới.
- **Artifact/output:** working agreement có decision driver và mục “branch ngoài policy”; decision record nêu lợi ích, chi phí drift và trigger xem xét lại.
- **Expected result:** `git show-ref --heads` chỉ có branch được policy chấp nhận; reviewer tìm được statement `master ≙ main` và ranh giới Scrum/Git Flow.
- **Verification/oracle:** branch ngoài policy = 0; mọi branch role có source/target/lifecycle; policy nêu ít nhất hai dấu hiệu “không nên dùng Git Flow”.

##### Ví dụ triển khai trong Material — professional artifact

Leaf này cung cấp lớp “working agreement” của **MEX-U01-01** ở mục 4. `LAB-U01-01/CP-U01-03` đưa vào ref `qc` tạm thời để người học phát hiện, giải thích và đưa repo về policy-compliant state.

##### Best practices

- **Rule:** ghi rõ phép ánh xạ `master` trong nguồn thành `main` trong NovaShop. **Rationale:** tránh vừa đổi tên vừa vô tình đổi vai trò. **Positive:** bảng policy giữ source/target nguyên nghĩa. **Negative:** team coi `main` là integration và merge feature trực tiếp, làm production baseline không còn đáng tin.
- **Rule:** mỗi rule có oracle và owner. **Rationale:** “cẩn thận” không thể audit. **Positive:** Release Owner kiểm tag type/ref containment; reviewer kiểm finding severity. **Negative:** policy chỉ ghi “merge đúng quy trình”, không ai xác định PASS/FAIL.
- **Rule:** tách Scrum khỏi branching policy. **Rationale:** Scrum định nghĩa accountabilities/events/artifacts/commitments, không áp đặt Git workflow. **Positive:** DoD được dùng làm quality commitment, còn review/branch rule được ghi là team agreement. **Negative:** tuyên bố Sprint Review bắt buộc phải merge `main`, làm sai cả mục đích event lẫn release decision.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** team tạo release branch mỗi Sprint dù không có release scope. **Nguyên nhân:** đồng nhất Sprint cadence với release cadence. **Chẩn đoán:** không tìm thấy scope freeze/UAT/version decision. **Sửa:** chỉ cắt release khi có tập scope và release decision; Sprint vẫn kết thúc bằng inspection. **Phòng tránh:** working agreement tách hai cadence.
- **Dấu hiệu:** policy có cả `master` và `main` như hai production branches. **Nguyên nhân:** đổi tên không hoàn tất hoặc đọc nguồn máy móc. **Chẩn đoán:** `git show-ref --heads` và tài liệu policy. **Sửa:** chọn một canonical default branch trong repo Lab; cập nhật reference text. **Phòng tránh:** baseline checklist kiểm đúng một production-ready branch.
- **Dấu hiệu:** branch môi trường xuất hiện sau mỗi yêu cầu ad hoc. **Nguyên nhân:** không có admission criteria. **Chẩn đoán:** mỗi branch thiếu state/owner/exit/target. **Sửa:** ghi ADR rồi xóa ref không có unique unmerged work trong bản sao Lab; bảo toàn evidence trước/sau. **Phòng tránh:** yêu cầu bốn trường state–owner–exit–merge trước khi thêm branch dài hạn.

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### MEX-U01-01 — Branch-routing table và baseline graph cho NovaShop

**Stable ID:** `MEX-U01-01` · **Mode:** professional artifact · **LO:** `LO1.1`, `LO1.2` · **Outline:** `OUT-U01-01`, `OUT-U01-02`, `OUT-U01-03`.

### Input/trạng thái ban đầu

- Project brief và backlog synthetic chưa version hóa.
- Default branch policy: `main`; integration branch: `develop`.
- Mốc đầu tiên: `baseline-0.0.0`, annotated tag.
- Constraints: local-only, không credential/PII, không branch môi trường mặc định, không direct commit sau baseline.

### Cách thực hiện

**Artifact 1 — Routing table đã ra quyết định**

| # | Tình huống | Quyết định | Source → target | Exit/oracle |
| ---: | --- | --- | --- | --- |
| 1 | NS-101 Search cho release kế tiếp | `feature/NS-101-product-search` | `develop` → `develop` | DoD/review PASS; contained in `develop` |
| 2 | NS-102 Cart Promotion cho release kế tiếp | feature | `develop` → `develop` | acceptance evidence đầy đủ |
| 3 | Chuẩn bị scope 0.1.0 đã chọn | `release/0.1.0` | `develop` → `main` và `develop` | UAT PASS; tag sau merge `main` |
| 4 | Sửa wording trong UAT 0.1.0 | release fix | tiếp tục trên `release/0.1.0` | finding đóng; không thêm capability |
| 5 | Sai phí vận chuyển trên production 0.1.0 | `hotfix/0.1.1-shipping-fee` | `main` → `main` và dòng tương lai | regression PASS; patch tag |
| 6 | Admin capability cho 0.2.0 khi 0.1.0 đang ổn định | feature | `develop` → `develop` | không đi vào release 0.1.0 |
| 7 | Cập nhật Product Backlog chưa thành product change | artifact/governance branch theo issue | `develop` → `develop` | review record; scope rõ |
| 8 | Thử nghiệm không đạt tiêu chí | feature bị loại bỏ | `develop` → không merge | decision record; branch cleanup an toàn |
| 9 | Sponsor yêu cầu branch `qc` nhưng không có state/owner/exit riêng | không tạo long-lived branch | dùng ref feature/release thích hợp | `qc` không có trong refs |
| 10 | Commit trực tiếp vào `main` để “tiết kiệm thời gian” | REJECT | không áp dụng | review/branch policy chặn |

**Oracle LO1.1:** đúng ít nhất 8/10; các dòng 1, 3 và 5 bắt buộc đúng vì kiểm tra ba tuyến cốt lõi. Mỗi dòng có state rationale, source, target và exit.

**Artifact 2 — Baseline graph và lệnh tạo**

Trong một bản sao Lab cô lập, tạo commit baseline, annotated tag và integration branch:

```text
git init -b main
git config --local user.name "NovaShop Learner"
git config --local user.email "learner@example.invalid"
git add project-artifacts
git commit -m "chore(M-GF-01): establish NovaShop artifact baseline"
git tag -a baseline-0.0.0 -m "NovaShop training baseline 0.0.0"
git switch -c develop
git add governance
git commit -m "docs(M-GF-01): define Git Flow working agreement"
```

`project-artifacts` chứa bản sao project brief/backlog; `governance` chứa routing table và working agreement. Hai thư mục được tạo/chỉnh bằng editor, không chứa mã nguồn ứng dụng.

Expected topology:

```text
* C (HEAD -> develop) docs(M-GF-01): define Git Flow working agreement
* B (tag: baseline-0.0.0, main) chore(M-GF-01): establish NovaShop artifact baseline
```

**Artifact 3 — Working agreement tối thiểu**

| Policy field | NovaShop decision | Oracle |
| --- | --- | --- |
| Production-ready ref | `main` (`master` trong nguồn gốc được ánh xạ thành `main`) | đúng một canonical ref |
| Integration ref | `develop` | `main` là ancestor của `develop` |
| Supporting branch | feature/release/hotfix theo bảng vai trò | source/target/lifecycle đầy đủ |
| Review | không direct commit `main`/`develop` sau baseline; error finding = 0 trước merge | review record PASS |
| Tag | annotated tag cho baseline/release | object type `tag` |
| Evidence | status + graph + refs + decision rationale | reviewer tái lập kết luận |
| Safety | local-only, synthetic-only, không force push shared branch | scan/manual review PASS |
| Applicability | dùng cho release/version/hotfix song song; đánh giá lại khi cadence liên tục và merge cost cao | ADR ở U06 |

Backlog/change state được phân loại bằng routing table; policy chuyển phân loại thành source/target/lifecycle; Git refs hiện thực hóa quyết định; evidence chứng minh refs khớp policy. Nếu input đổi từ “capability tương lai” thành “incident production”, source đổi từ `develop` sang `main`. Nếu chỉ đổi người yêu cầu hoặc môi trường test mà state sản phẩm không đổi, branch type không tự đổi.

### Output mong đợi

```text
* C (HEAD -> develop) docs(M-GF-01): define Git Flow working agreement
* B (tag: baseline-0.0.0, main) chore(M-GF-01): establish NovaShop artifact baseline
```

**Happy path:** cả routing, policy và refs cùng PASS. **Edge case:** yêu cầu `qc` bị từ chối vì thiếu state/owner/exit; refs vẫn không có `qc`. **Failure behavior:** nếu tag type là `commit`, artifact review kết luận `REVISE`, không tự nhận baseline đạt.

### Cách xác minh

```text
git status --short --branch
git log --graph --decorate --oneline --all
git show-ref --heads --tags
git merge-base --is-ancestor main develop
git cat-file -t baseline-0.0.0
```

Oracle:

- status cho biết đang ở `develop` và không có file thay đổi;
- graph có hai commit theo topology trên;
- refs có `refs/heads/main`, `refs/heads/develop`, `refs/tags/baseline-0.0.0`;
- containment trả exit code 0;
- tag type là `tag`.

### Mapping Material worked example → Hands-on Lab tương ứng

- **MEX-U01-01** → **LAB-U01-01/CP-U01-01** (`LO1.1`, `LO1.2`): tái tạo routing/baseline trên CARD-U01 và lưu status evidence.
- **MEX-U01-01** → **LAB-U01-01/CP-U01-02** (`LO1.1`, `LO1.2`): dùng graph/ref containment để chứng minh topology.
- **MEX-U01-01** → **LAB-U01-01/CP-U01-03** (`LO1.1`, `LO1.2`): debug ref `qc` ngoài policy và ghi prevention rule.

Lab thay input/constraint và yêu cầu recreate/debug; không chỉ chép artifact mẫu.

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

| Dấu hiệu | Nguyên nhân khả dĩ | Chẩn đoán/bằng chứng | Cách khắc phục | Phòng tránh |
| --- | --- | --- | --- | --- |
| `main` không tồn tại sau `git init` | Git/config tạo default branch khác | `git branch --show-current` | Trong repo Lab chưa chia sẻ, đổi canonical branch và cập nhật policy | dùng `git init -b main`; preflight current branch |
| `develop` không chứa baseline | tạo từ commit/ref sai | `git merge-base --is-ancestor main develop` | tạo branch đúng từ baseline trong bản sao sạch | lưu SHA của `main` trước khi tạo |
| status không sạch khi tag | file chưa commit/stage | `git status --short` | quyết định commit hoặc loại input; không tag trạng thái mơ hồ | baseline checklist trước tag |
| tag không có annotation | lightweight tag | `git cat-file -t baseline-0.0.0` | sửa theo policy chỉ khi tag chưa công bố; lưu decision | luôn dùng `git tag -a` |
| routing table đúng tên nhưng sai nguồn | học thuộc prefix, không xét state | graph + base SHA | đánh giá lại state và tạo work từ ref đúng | source/target review trước branch creation |
| policy nói Git Flow là Scrum rule | trộn framework quản lý sản phẩm với VCS workflow | đối chiếu Scrum Guide và policy | sửa wording thành team engineering agreement | có boundary statement trong working agreement |

## 6. Từ điển thuật ngữ và mô hình tư duy

| Thuật ngữ | Nghĩa dùng trong Unit |
| --- | --- |
| Ref | Tên trỏ tới object Git; branch/tag là các loại ref thường gặp. |
| Reachable/contained | Có thể đi theo parent từ ref đích tới commit cần kiểm tra. |
| Ancestry | Quan hệ cha–con giữa commit, độc lập với tên branch. |
| Working tree | Nội dung đang checkout; có thể khác snapshot đã commit. |
| Index/staging area | Tập nội dung được chọn cho commit kế tiếp. |
| Supporting branch | Feature/release/hotfix có mục đích và vòng đời hữu hạn. |
| Production-ready | Trạng thái theo policy có thể phát hành; trong NovaShop được đại diện bởi `main`/tag sau gate. |
| Integration branch | Dòng tích hợp thay đổi cho release kế tiếp; NovaShop dùng `develop`. |
| Oracle | Điều kiện/lệnh cho kết luận PASS/REVISE có thể quan sát. |
| Working agreement | Policy do team thống nhất; không đồng nghĩa quy tắc bắt buộc của Scrum. |

Mô hình tư duy cần giữ: **đừng tin tên ref; hãy kiểm tra ancestry, state và evidence**.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

- [Git Reference Manual 2.54.0](https://git-scm.com/docs/git/2.54.0) — Git Project / Software Freedom Conservancy; GPL-2.0-only, reference use.
- [Pro Git — Branches in a Nutshell](https://git-scm.com/book/en/v2/Git-Branching-Branches-in-a-Nutshell) và [Basic Branching and Merging](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging) — 2nd Edition; CC BY-NC-SA 3.0; diễn giải độc lập.
- [A successful Git branching model](https://nvie.com/posts/a-successful-git-branching-model/) — Vincent Driessen; reference-only; không tái phân phối sơ đồ.
- [Cơ bản về Gitflow Workflow](https://viblo.asia/p/co-ban-ve-gitflow-workflow-4dbZNn6yZYM) — KhanhVQ/Viblo; All Rights Reserved; chỉ tham chiếu và diễn giải độc lập.
- `starter/NovaShop_Project_Brief.md` — artifact synthetic version 1.0, internal approved.

### Phần bổ sung/suy diễn

- **[BỔ SUNG — nguồn: Git Reference Manual/Pro Git]** Các oracle `show-ref`, `merge-base`, `cat-file`, status và cách đọc commit graph được tổ hợp thành audit checklist cho khóa học.
- **[BỔ SUNG — nguồn: NovaShop project brief và change card synthetic]** Routing table, tên ref, working agreement và dữ liệu MEX là tình huống đào tạo mô phỏng, không phải repository thật.
- Không có phần suy diễn không nguồn vượt ra ngoài phạm vi Unit.

# Unit U03: Tích hợp song song, conflict và lịch sử an toàn — Học liệu cốt lõi

> **Khóa học:** Git Flow thực chiến qua dự án NovaShop · **Thuộc:** Feature Delivery and Integration · **Mức xác thực:** simulated

## 🎯 Learning Outcomes

- **LO3.1 — Analyze:** Chẩn đoán và giải quyết conflict giữa các feature branch mà không làm mất acceptance criteria đã phê duyệt. Bằng chứng đích là conflict decision log và diff sau resolution.
- **LO3.2 — Evaluate:** Lựa chọn merge, no-fast-forward, rebase cục bộ hoặc revert phù hợp với ownership và rủi ro lịch sử. Bằng chứng đích là strategy decision record và branch graph sau tích hợp.

## 🧭 Ngữ cảnh nghề nghiệp/dự án và phần tăng trưởng của Unit

NovaShop đang ở milestone **M-GF-03**. `develop` đã nhận feature đầu tiên; Cart, Checkout và Payment sandbox tiếp tục được chuẩn bị song song. Học viên đóng vai thành viên nhóm delivery chịu trách nhiệm đưa thay đổi vào integration branch mà vẫn giữ được quyết định nghiệp vụ, lịch sử kiểm toán và khả năng khôi phục.

Increment của Unit gồm:

- một **Integration evidence pack** cho biết feature nào được tích hợp, theo thứ tự nào và trạng thái ref trước/sau;
- một **Conflict decision log** nối từng vùng xung đột với acceptance criteria, quyết định của stakeholder và oracle sau resolution;
- một graph chứng minh feature tip đã thuộc `develop`, working tree sạch, conflict marker bằng 0 và shared history không bị rewrite.

Mốc đạt: resolution giữ đủ acceptance criteria, có stakeholder decision khi Git không thể quyết định nghĩa nghiệp vụ, và không rebase/force-push branch đã được chia sẻ. Các artifact này là baseline của **ASM-GF-02**, sau đó được **ASM-GF-03** dùng để quyết định release scope.

## 📚 Nguồn đầu vào đã map

- **SRC-GIT-DOC:** Git Reference Manual 2.54.0, Git Project, truy cập 2026-08-25.
- **SRC-PROGIT:** Pro Git, 2nd Edition, living web edition, truy cập 2026-08-25.
- **SRC-NVIE:** *A successful Git branching model*, Vincent Driessen, bản gốc 2010 và ghi chú 2020, truy cập 2026-08-25.
- **SRC-SCRUM:** Scrum Guide, November 2020, truy cập 2026-08-25.
- **SRC-NS-CARDS:** NovaShop Git Flow change cards, artifact đào tạo nội bộ phiên bản 1.0.

Git Flow trong Unit là working agreement của nhóm, không phải quy tắc bắt buộc của Scrum. Scrum yêu cầu Increment hữu dụng và đáp ứng Definition of Done; cách tổ chức branch là lựa chọn kỹ thuật của nhóm.

---

## 1. Kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết

- Hoàn thành U02 và có thể đọc `git status`, `git log --graph`, `git diff`.
- Biết feature branch bắt đầu từ `develop` và merge trở lại `develop` sau review.
- Có thể sửa artifact Markdown/CSV, đọc PBI, acceptance criteria và review finding.

### Môi trường, công cụ và phiên bản

- Repo Git local cô lập, chỉ chứa artifact Markdown/CSV synthetic của NovaShop.
- Git CLI 2.40+; nội dung khóa được kiểm tra với Git 2.54.0.windows.1.
- Trình soạn Markdown CommonMark-compatible và trình soạn CSV UTF-8.
- Không remote production, credential, PII, dữ liệu thanh toán thật hoặc mã nguồn ứng dụng.

Preflight:

```text
git --version
git config --get user.name
git config --get user.email
git status --short --branch
git branch --list main develop
```

Chỉ tiếp tục khi đang ở bản sao Lab, `main` và `develop` tồn tại, danh tính Git là danh tính đào tạo và working tree sạch. `user.name`/`user.email` không được chứa thông tin cá nhân thật trong evidence nộp bài.

### Phương thức xác minh artifact

`artifact_review`: reviewer đối chiếu decision record, diff và graph với acceptance oracle; các lệnh Git cung cấp evidence cấu trúc, còn quyết định nghiệp vụ phải được kiểm bằng requirement/acceptance evidence.

### Hợp đồng ví dụ triển khai và thực hành

- **Mode:** `professional_artifact`.
- **Rationale:** Unit vận hành Git trên tài liệu nghề nghiệp và tạo decision/evidence record; không viết, build hoặc test mã nguồn ứng dụng.
- **Worked example:** `MEX-U03-01` phủ LO3.1, LO3.2 và cả ba outline leaf.
- **Lab pairing:** `MEX-U03-01` được biến đổi sang Checkout × Payment tại `LAB-U03-01`, các checkpoint `CP-U03-01`, `CP-U03-02`, `CP-U03-03`.

## 2. Định vị trong lộ trình (Mental Map)

```text
U02: feature đã review
        │
        ▼
U03: dự báo overlap → chọn integration order → tạo merge conflict
        │                                      │
        │                                      ▼
        └────────────── evidence ← resolve theo business oracle
                                               │
                                               ▼
                              chọn history strategy + kiểm containment
                                               │
                                               ▼
U04: cắt release từ một develop đã tích hợp và kiểm toán được
```

Mental model trung tâm: Git có thể phát hiện hai patch không ghép tự động, nhưng không biết câu nào đúng với FR-02/FR-03. Vì vậy một merge hợp lệ cần đồng thời đạt hai lớp oracle:

1. **Oracle cấu trúc Git:** graph, ref containment, working tree và conflict marker.
2. **Oracle nghiệp vụ:** acceptance criteria, ID/meaning contract và stakeholder decision.

## 3. Nội dung lý thuyết cốt lõi

**Checklist bắt buộc phủ — giữ nguyên văn và đúng thứ tự Content Outlines:**

- [x] Feature song song, integration order và phòng ngừa conflict
- [x] Chẩn đoán, giải quyết và kiểm chứng merge conflict bằng evidence
- [x] Merge, no-fast-forward, squash, rebase, revert và ranh giới shared history

#### OUT-U03-01 — Feature song song, integration order và phòng ngừa conflict

**Mapping:** OUT-U03-01 · LO3.1, LO3.2 · M-GF-03 / Integration evidence pack · MEX-U03-01

##### Định nghĩa rõ ràng

Feature song song là các dòng thay đổi được tạo từ một baseline chung nhưng tiến triển độc lập. **Integration order** là quyết định thứ tự đưa các dòng đó vào `develop`. Conflict không chỉ là marker `<<<<<<<`; semantic conflict còn xảy ra khi Git merge sạch nhưng hai thay đổi tạo quy tắc nghiệp vụ mâu thuẫn, trùng ID hoặc làm mất acceptance behavior.

Phòng ngừa conflict không có nghĩa là tránh mọi thay đổi chung. Ranh giới đúng là giảm overlap không cần thiết, làm rõ ownership và phát hiện dependency sớm, trong khi vẫn tích hợp đủ thường xuyên để chênh lệch không phình lớn.

##### Vấn đề/vai trò và quyết định cần đưa ra

Delivery team cần quyết định:

- feature nào phụ thuộc feature nào;
- artifact/row/field nào có khả năng chồng lấn;
- feature nào merge trước để baseline cho feature sau;
- ai có authority quyết định khi hai acceptance contract xung đột;
- điểm dừng nào buộc phải trả về review thay vì tự chọn một phía.

Product Owner làm rõ giá trị/scope; domain stakeholder xác nhận nghĩa nghiệp vụ; reviewer xác nhận evidence. Git không thay thế các vai trò đó.

##### Cơ chế và mental model

Lập một **conflict map** theo ba trục:

| Trục | Câu hỏi | Evidence |
| --- | --- | --- |
| Dependency | B có cần artifact/decision từ A không? | PBI refs, commit plan |
| Overlap | A và B chạm cùng file, row, ID hay nghĩa nghiệp vụ không? | `git diff --name-only`, artifact map |
| Risk | Nếu resolution sai, acceptance contract nào bị mất? | AC refs, owner, severity |

Nếu B phụ thuộc A, merge A trước rồi cập nhật B trên baseline mới. Nếu độc lập nhưng overlap cao, merge thay đổi có oracle rõ hơn trước để conflict thứ hai được cô lập. Nếu không overlap, thứ tự có thể ưu tiên readiness. Mỗi merge chỉ nên đưa một hypothesis thay đổi vào `develop`, giúp truy ngược nguyên nhân khi oracle fail.

##### Khi dùng / khi không dùng

- **Dùng:** nhiều feature cùng Sprint hoặc nhiều nhóm sửa chung artifact; dependency/ownership khác nhau; `develop` là integration branch đã chia sẻ.
- **Không dùng như lịch cố định:** đừng xếp thứ tự chỉ theo ai hoàn thành trước nếu dependency nói ngược lại.
- **Giới hạn:** conflict map dự báo overlap đã biết, không phát hiện mọi semantic conflict. Review acceptance contract vẫn bắt buộc.
- **Trade-off:** merge sớm giảm khoảng cách nhưng có thể làm `develop` biến động; merge muộn ổn định branch cá nhân nhưng làm conflict lớn và khó quy trách nhiệm.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** Cart owner và Checkout owner cùng thay đổi bảng handoff; Release Owner cần `develop` có trạng thái có thể giải thích.
- **Input/baseline/constraint:** `develop` chứa `cart-checkout-handoff.csv`; `feature/NS-102-cart-promo` thêm `PROMO_REJECTED`, `feature/NS-103-checkout` thêm `ADDRESS_INVALID`; cả hai yêu cầu giữ lựa chọn/input; Checkout branch đã được peer fetch.
- **Decision/action:** ghi overlap ở cùng vùng `input_behavior`, merge Cart trước vì Cart oracle đã được review; Checkout được merge sau và tuyệt đối không rebase branch đã chia sẻ.
- **Artifact/output:** conflict map và integration-order row trong `MEX-U03-01`.
- **Expected result:** graph có hai merge point giải thích được; cả hai status ID hiện diện với `PRESERVE`.
- **Verification/oracle/evidence:** `git log --graph --decorate --oneline --all`, `git merge-base --is-ancestor <feature-tip> develop`, và review table đối chiếu FR-02/FR-03.

##### Ví dụ triển khai trong Material — MEX-U03-01, phần conflict map

**Professional artifact: Conflict decision record cho Cart và Checkout**

| Feature | Baseline | Vùng overlap | Acceptance criteria có rủi ro | Readiness | Integration decision |
| --- | --- | --- | --- | --- | --- |
| `feature/NS-102-cart-promo` | `develop@D0` | `input_behavior` | FR-02: mã sai không làm mất sản phẩm | Review PASS | Merge thứ nhất bằng no-fast-forward |
| `feature/NS-103-checkout` | `develop@D0`, đã shared | `input_behavior` | FR-03: validation lỗi giữ checkout input | Review PASS | Merge thứ hai; resolve trên merge, không rebase shared branch |

**Oracle:** hai feature tip là ancestor của `develop`; decision record nêu dependency/overlap/owner; không có thay đổi ngoài scope. Lab thay Cart–Checkout bằng Checkout–Payment và buộc hai branch sửa cùng dòng dự phòng tại `CP-U03-01`.

##### Best practices

- **Rule:** lập integration order theo dependency và vùng artifact chồng lấn. **Rationale:** mỗi merge có phạm vi nguyên nhân nhỏ hơn. **Positive:** Cart PASS được merge trước, sau đó Checkout giải quyết đúng vùng overlap. **Negative:** merge ba branch cùng lúc khiến reviewer không biết thay đổi nào làm mất `PRESERVE`.
- **Rule:** lưu feature tip và graph trước merge. **Rationale:** object ID là baseline kiểm toán và giúp chứng minh không rewrite. **Positive:** evidence pack có `status-before` và `graph-before`. **Negative:** chỉ lưu ảnh sau merge nên không chứng minh branch shared giữ nguyên tip.
- **Rule:** giảm overlap bằng ownership và artifact boundary, không bằng né tích hợp. **Rationale:** branch tồn tại lâu làm tăng divergence. **Positive:** domain owner chốt ID namespace trước khi sửa. **Negative:** trì hoãn cả hai feature tới cuối Sprint khiến conflict lớn hơn.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** Git merge sạch nhưng một status ID xuất hiện hai nghĩa. **Nguyên nhân:** semantic conflict không trùng dòng. **Chẩn đoán:** so ID/meaning với acceptance oracle. **Sửa:** mở decision record, chọn canonical meaning có stakeholder approval và re-review. **Phòng tránh:** conflict map phải có ID/contract overlap, không chỉ file overlap.
- **Dấu hiệu:** mỗi lần merge lại phát sinh nhiều vùng không liên quan. **Nguyên nhân:** branch sống lâu hoặc chứa thay đổi ngoài scope. **Chẩn đoán:** `git diff --name-status develop...feature/<id>`. **Sửa:** tách change request mới; không rewrite branch shared. **Phòng tránh:** commit/branch scope nhỏ và integration cadence đã thống nhất.

#### OUT-U03-02 — Chẩn đoán, giải quyết và kiểm chứng merge conflict bằng evidence

**Mapping:** OUT-U03-02 · LO3.1 · M-GF-03 / Conflict decision log · MEX-U03-01

##### Định nghĩa rõ ràng

Merge conflict là trạng thái Git không thể tự tạo một kết quả duy nhất từ `ours`, `theirs` và merge base. **Resolution** là một thay đổi mới trong merge result; nó không đồng nghĩa với chọn nguyên một phía. Chẩn đoán gồm xác định merge base, file unmerged, stage của index và acceptance contract bị đe dọa.

`ours`/`theirs` phụ thuộc phía đang đứng khi chạy merge, không phải nhãn “đúng/sai”. Với `develop` merge một feature: `ours` thường là `develop`, `theirs` là feature. Cách gọi này thay đổi nếu hướng merge đổi.

##### Vấn đề/vai trò và quyết định cần đưa ra

Người giải quyết conflict phải trả lời: phần nào chỉ là format, phần nào mang nghĩa; có đủ authority để quyết định không; kết quả cần kết hợp cả hai hay chọn canonical contract; oracle nào chứng minh không mất acceptance criteria. Khi thiếu domain decision, hành động đúng là giữ merge ở trạng thái dở dang, lưu evidence, hỏi stakeholder hoặc abort — không đoán.

##### Cơ chế và mental model

Trong conflict ba phía:

- **merge base:** phiên bản chung trước khi hai nhánh tách;
- **ours:** phiên bản tại `HEAD` của branch nhận merge;
- **theirs:** phiên bản của branch được merge;
- **result:** artifact do người giải quyết tạo và stage bằng `git add`.

Chuỗi evidence tối thiểu là: `status conflict` → diff ba phía/AC at risk → decision và owner → resolved diff → marker scan → business oracle → merge commit/graph. `git diff --check` phát hiện một số lỗi whitespace và marker còn trong diff, nhưng không chứng minh nghĩa nghiệp vụ; vì vậy phải có oracle bổ sung.

##### Khi dùng / khi không dùng

- **Dùng resolution tại merge:** cả hai branch đã review, conflict nhỏ, owner và oracle sẵn có.
- **Abort:** branch nguồn/đích sai, working tree có thay đổi ngoài scope, chưa có authority hoặc conflict lan rộng bất ngờ.
- **Không dùng “accept ours/theirs” mặc định:** chỉ hợp lệ khi decision record chứng minh toàn bộ phía bị bỏ là dư thừa/sai.
- **Trade-off:** sửa nhanh ngay trong merge giảm thời gian chờ nhưng dễ tạo quyết định nghiệp vụ không review; dừng xin quyết định lâu hơn nhưng bảo toàn accountability.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** Cart và Checkout cùng thay một dòng dự phòng; Product Owner xác nhận cả hai failure behavior thuộc MVP.
- **Input/baseline/constraint:** conflict marker chứa `PROMO_REJECTED` ở một phía và `ADDRESS_INVALID` ở phía kia; ID phải duy nhất; `input_behavior=PRESERVE` cho cả hai.
- **Decision/action:** thay vùng conflict bằng hai row, giữ nguyên ID/meaning đã review; ghi owner của quyết định và không sửa row ngoài vùng conflict.
- **Artifact/output:** resolved CSV, conflict decision row, diff before/after.
- **Expected result:** marker bằng 0, mỗi ID đúng một lần, FR-02 và FR-03 đều PASS.
- **Verification/oracle/evidence:** `git diff --check`; `git grep -n` cho từng ID; reviewer so meaning/behavior với AC table và ký `PASS`.

##### Ví dụ triển khai trong Material — MEX-U03-01, phần resolution record

| Trường | Giá trị đã quyết định |
| --- | --- |
| Branches / merge base | `develop` nhận `feature/NS-103-checkout`; common baseline `D0` |
| Conflicted artifact | `project-artifacts/integration/cart-checkout-handoff.csv` |
| AC at risk | FR-02 giữ sản phẩm; FR-03 giữ checkout input |
| Options | chọn Cart; chọn Checkout; giữ hai ID với contract `PRESERVE` |
| Chosen resolution | giữ cả `PROMO_REJECTED` và `ADDRESS_INVALID`; mỗi ID một row |
| Rationale/owner | hai behavior độc lập và đều nằm trong scope Done; Product Owner xác nhận |
| Structural oracle | marker bằng 0; working tree sạch sau commit |
| Business oracle | hai ID duy nhất; cả hai có `input_behavior=PRESERVE` |
| Prevention | reserve ID riêng và review conflict map trước khi sửa shared table |

Lab dùng ID `ADDRESS_INVALID` và `DECLINED_RETRYABLE`, nên học viên phải tái tạo cơ chế dưới input mới thay vì sao chép artifact này (`CP-U03-01`, `CP-U03-02`).

##### Best practices

- **Rule:** resolution dựa trên acceptance criteria và stakeholder decision, không dựa riêng vào việc marker biến mất. **Rationale:** Git chỉ biết text graph. **Positive:** reviewer kiểm cả ID và input behavior. **Negative:** `git checkout --ours` làm merge sạch nhưng loại bỏ failure path đã duyệt.
- **Rule:** giới hạn resolved diff vào vùng được quyết định. **Rationale:** thay đổi tiện tay làm mất traceability. **Positive:** `git diff --cached` chỉ có hai row và decision record. **Negative:** người resolve đồng thời đổi glossary khác không có PBI.
- **Rule:** lưu evidence trước `git add`. **Rationale:** sau khi stage, trạng thái unmerged không còn hiện như ban đầu. **Positive:** `status-conflict.txt` và diff ba phía được ghi trong evidence pack. **Negative:** chỉ có merge commit nên reviewer không tái lập được chẩn đoán.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** `git status` vẫn báo `both modified` sau khi sửa file. **Nguyên nhân:** result chưa được stage. **Chẩn đoán:** xem `git status` và `git diff --name-only --diff-filter=U`. **Sửa:** rà oracle rồi `git add <artifact>`. **Phòng tránh:** checklist tách “edit result” và “stage result”.
- **Dấu hiệu:** marker bằng 0 nhưng oracle đếm thiếu một ID. **Nguyên nhân:** chọn một phía hoặc xóa nhầm row. **Chẩn đoán:** so resolved file với ours/theirs và AC list. **Sửa:** phục hồi row đúng nghĩa trước merge commit. **Phòng tránh:** decision table liệt kê từng AC at risk.
- **Dấu hiệu:** conflict xuất hiện ở file ngoài conflict map. **Nguyên nhân:** baseline đã tiến hoặc branch có scope creep. **Chẩn đoán:** `git diff --name-status <merge-base>..<feature-tip>`. **Sửa:** lưu evidence rồi `git merge --abort`; cập nhật plan/review. **Phòng tránh:** kiểm tip và file set ngay trước merge.

#### OUT-U03-03 — Merge, no-fast-forward, squash, rebase, revert và ranh giới shared history

**Mapping:** OUT-U03-03 · LO3.2 · M-GF-03 / Strategy decision record và graph · MEX-U03-01

##### Định nghĩa rõ ràng

- **Fast-forward merge:** chỉ di chuyển ref đích khi không có divergence; không tạo merge commit.
- **No-fast-forward merge:** tạo merge commit ngay cả khi fast-forward có thể xảy ra, giữ boundary của feature trong graph.
- **Squash:** đưa tổng diff thành một commit mới; commit gốc của feature không trở thành ancestor của target.
- **Rebase:** tái phát commit lên base mới, tạo commit object mới; phù hợp cho lịch sử cục bộ chưa chia sẻ, rủi ro với shared branch.
- **Revert:** tạo commit mới đảo effect của commit/merge đã công bố; không xóa lịch sử.

`merge` là khái niệm chung; `--no-ff` là một topology policy. Squash/rebase không “xấu” tuyệt đối: quyết định phụ thuộc ownership, traceability và việc commit đã được người khác dựa vào hay chưa.

##### Vấn đề/vai trò và quyết định cần đưa ra

Reviewer/maintainer cần chọn strategy trả lời được bốn câu hỏi: lịch sử đã shared chưa; cần giữ feature boundary/tip containment không; commit trung gian có giá trị kiểm toán không; rollback cần theo feature hay theo từng commit. Trong NovaShop, `main`/`develop` và feature branch đã peer fetch là shared; không được rewrite chúng.

##### Cơ chế và mental model

Commit ID phụ thuộc parent và content. Rebase/squash tạo commit mới nên object ID thay đổi; cộng tác viên đang giữ old tip sẽ nhìn thấy hai dòng lịch sử khác nhau. Merge/no-ff và revert chỉ bổ sung commit, nên các old commit vẫn reachable. Chính sách NovaShop ưu tiên append-only trên shared refs để evidence trước/sau còn đối chiếu được.

| Tình huống | Strategy mặc định | Oracle topology |
| --- | --- | --- |
| Feature local, chưa push/share, cần cập nhật base | rebase cục bộ được phép | old commits chưa là baseline của người khác |
| Feature đã review/fetch, cần boundary | merge `--no-ff` | feature tip là ancestor của `develop` |
| Nhiều commit nhiễu, policy chấp nhận mất tip containment | squash có cân nhắc | squash commit map tới PBI; feature tip không được tuyên bố contained |
| Merge đã công bố gây lỗi | revert | commit đảo mới; merge cũ vẫn trong graph |

##### Khi dùng / khi không dùng

- **No-ff:** dùng khi project cần feature boundary và merge record. Đổi lại graph nhiều merge commit hơn.
- **Squash:** dùng khi commit trung gian không cần audit và team policy cho phép; không dùng nếu oracle yêu cầu feature tip contained.
- **Rebase:** chỉ trên commits do mình sở hữu và chưa shared; không rebase `develop`, `main` hoặc branch peer đã fetch.
- **Revert:** dùng cho thay đổi đã merge/published; không dùng để “làm như chưa từng xảy ra” vì history vẫn ghi cả original và inverse.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** Checkout branch đã được peer dùng để review; Release Owner cần chứng minh exact reviewed tip đã vào `develop`.
- **Input/baseline/constraint:** tip `feature/NS-103-checkout` đã được ghi trong review record; target `develop` là shared.
- **Decision/action:** merge `--no-ff`; nếu merge result sau đó bị bác bỏ, dùng revert merge theo review mới thay vì reset/force-push.
- **Artifact/output:** strategy decision record và graph có merge node.
- **Expected result:** reviewed feature tip là ancestor của `develop`; old tip vẫn query được; không có force update.
- **Verification/oracle/evidence:** `git merge-base --is-ancestor feature/NS-103-checkout develop` trả exit code 0; graph thể hiện merge boundary.

##### Ví dụ triển khai trong Material — MEX-U03-01, phần strategy record

| Decision driver | Observed state | Choice | Consequence accepted |
| --- | --- | --- | --- |
| Ownership | Checkout tip đã peer fetch | Không rebase | Giữ commit IDs đã review |
| Traceability | Cần feature boundary | `merge --no-ff` | Graph có thêm merge commit |
| Rollback | Release Owner cần đảo effect có audit | Revert nếu cần | Lịch sử giữ original và inverse |
| Squash | Tip containment là acceptance oracle | Không squash | Giữ từng commit đã review |

MEX đạt khi conflict record, graph và containment cùng kể một câu chuyện: tip được review vẫn reachable, merge result giữ hai AC và `develop` sạch. Lab yêu cầu áp dụng strategy này lên Checkout × Payment rồi xử lý một negative validation ở `CP-U03-03`.

##### Best practices

- **Rule:** chỉ rebase commit cục bộ chưa chia sẻ. **Rationale:** rebase đổi commit ID và phá baseline của cộng tác viên. **Positive:** developer rebase branch chưa push trước review. **Negative:** rebase branch đã peer fetch rồi force-push, khiến review record trỏ old tip.
- **Rule:** chọn squash chỉ khi acceptance oracle không yêu cầu tip containment. **Rationale:** squash giữ diff nhưng không giữ ancestry của feature tip. **Positive:** policy map squash commit tới PBI và chấm bằng content oracle. **Negative:** vừa squash vừa tuyên bố `merge-base --is-ancestor feature-tip develop` phải PASS.
- **Rule:** dùng revert cho published history bị lỗi. **Rationale:** append-only giữ audit trail và an toàn cho người đã fetch. **Positive:** revert merge bằng commit có incident/ref. **Negative:** reset `develop` rồi force-push làm mất common baseline.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** feature tip không phải ancestor dù diff có mặt. **Nguyên nhân:** squash merge. **Chẩn đoán:** `git merge-base --is-ancestor <tip> develop` và xem graph. **Sửa:** không bịa containment; cập nhật oracle theo policy hoặc làm lại trên bản sao nếu no-ff là yêu cầu. **Phòng tránh:** chốt strategy trước merge.
- **Dấu hiệu:** reviewer thấy duplicate commits sau pull. **Nguyên nhân:** shared branch bị rebase. **Chẩn đoán:** so old/new tip và patch IDs trong evidence. **Sửa:** dừng force update, thống nhất recovery branch từ ref được phê duyệt. **Phòng tránh:** đánh dấu shared ownership trong review record.
- **Dấu hiệu:** revert merge báo cần mainline. **Nguyên nhân:** merge commit có nhiều parent. **Chẩn đoán:** `git show --no-patch --pretty=raw <merge-commit>`. **Sửa:** maintainer xác định đúng parent theo topology rồi review lệnh revert; không thử trên production/shared ref. **Phòng tránh:** lưu source/target và parent order trong merge evidence.

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### MEX-U03-01 — Conflict decision record cho Cart và Checkout

**Mapping:** LO3.1, LO3.2 · OUT-U03-01/02/03 · professional artifact · `LAB-U03-01`/`CP-U03-01..03`

#### Input/trạng thái ban đầu

- `develop@D0` là baseline sạch.
- Cart và Checkout bắt đầu từ D0, cùng thay `cart-checkout-handoff.csv`.
- Cart yêu cầu `PROMO_REJECTED` giữ sản phẩm; Checkout yêu cầu `ADDRESS_INVALID` giữ input.
- Checkout tip đã peer fetch nên history là shared.

#### Decision và artifact hoàn chỉnh

1. Conflict map ghi overlap, AC at risk, owner và integration order: Cart trước, Checkout sau.
2. Merge Cart bằng no-fast-forward; khi merge Checkout, giữ cả hai ID và `PRESERVE`.
3. Strategy record bác bỏ rebase/squash vì reviewed tip containment là oracle.
4. Evidence pack lưu status/graph trước, diff conflict, resolved diff, graph/containment sau và review PASS.

#### Output mong đợi

| Oracle | PASS condition |
| --- | --- |
| Marker | Không còn dòng bắt đầu bằng `<<<<<<<`, `=======`, `>>>>>>>` trong artifact tracked |
| Business | `PROMO_REJECTED` và `ADDRESS_INVALID` mỗi ID đúng một lần; đều `PRESERVE` |
| Topology | cả hai feature tip là ancestor của `develop`; có merge boundary |
| Safety | Checkout old tip còn reachable; không có force-update evidence |
| Quality | working tree sạch; decision record có owner/rationale |

#### Cách xác minh

```text
git diff --check
git grep -n -E '^(<<<<<<<|=======|>>>>>>>)' -- '*.md' '*.csv'
git merge-base --is-ancestor feature/NS-102-cart-promo develop
git merge-base --is-ancestor feature/NS-103-checkout develop
git log --graph --decorate --oneline --all
git status --short --branch
```

`git grep` trả exit code 1 khi không tìm thấy marker; trong oracle này đó là kết quả mong đợi, không phải lỗi artifact. Hai lệnh `merge-base --is-ancestor` phải trả 0. Reviewer còn phải kiểm bảng ID/behavior; các lệnh Git không tự chứng minh FR-02/FR-03.

### Mapping Material worked example → Hands-on Lab tương ứng

- `MEX-U03-01` → `LAB-U03-01/CP-U03-01`: tái tạo conflict map và resolution trên Checkout × Payment, input khác Material.
- `MEX-U03-01` → `LAB-U03-01/CP-U03-02`: chứng minh graph, merge point và traceability sau resolution.
- `MEX-U03-01` → `LAB-U03-01/CP-U03-03`: chạy negative validation với duplicate ID, khôi phục và chứng minh shared-history safety.

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

| Dấu hiệu | Nguyên nhân có khả năng | Chẩn đoán/bằng chứng | Khắc phục an toàn | Phòng tránh |
| --- | --- | --- | --- | --- |
| Merge chạy trên branch sai | Không kiểm `HEAD` | `git status --short --branch` | Lưu evidence; nếu merge chưa commit thì `git merge --abort`; quay về ref đúng | preflight trước mọi merge |
| `merge --abort` không chạy | Không có merge đang dở hoặc working tree đã bị đổi thêm | `git status`, kiểm `MERGE_HEAD` qua `git rev-parse -q --verify MERGE_HEAD` | Không reset mù; lưu patch ngoài phạm vi rồi khôi phục bản sao Lab | working tree sạch trước merge |
| Marker hết nhưng review REVISE | Chỉ giải conflict cú pháp | diff và AC table không khớp | sửa result theo stakeholder decision, chạy lại oracle | map AC at risk trước edit |
| Containment FAIL | squash hoặc merge chưa hoàn tất | `merge-base --is-ancestor`, graph | đối chiếu strategy record; làm lại trong bản sao nếu policy yêu cầu no-ff | chọn oracle trước strategy |
| Old feature tip biến mất khỏi evidence | branch bị rewrite/xóa quá sớm | so tip đã ghi với `git cat-file -e <tip>^{commit}` | dừng, dùng ref/evidence còn giữ; không force-push tiếp | lưu tip và trì hoãn xóa branch tới sau gate |

Quy tắc dừng: nếu conflict chạm artifact ngoài scope, thiếu acceptance oracle hoặc thiếu authority, không được tự hoàn tất merge. Lưu evidence và dùng `git merge --abort` trong bản sao Lab.

## 6. Từ điển thuật ngữ và mô hình tư duy

| Thuật ngữ | Nghĩa trong Unit |
| --- | --- |
| Merge base | Commit chung tốt nhất dùng làm gốc so sánh ba phía |
| Ours / theirs | Hai phiên bản theo hướng merge hiện tại, không phải đúng / sai |
| Semantic conflict | Mâu thuẫn nghĩa nghiệp vụ dù Git có thể merge text sạch |
| Integration order | Thứ tự đưa feature đã review vào integration branch |
| Shared history | Commit/ref đã được người khác fetch, review hoặc dùng làm baseline |
| Containment | Quan hệ ancestor chứng minh commit/ref thuộc lịch sử đích |
| No-fast-forward | Merge policy tạo merge commit để giữ feature boundary |
| Squash | Tổng hợp diff thành commit mới, không giữ ancestry feature tip |
| Rebase | Phát lại commit trên base mới, làm đổi commit object |
| Revert | Commit mới đảo effect, không xóa lịch sử đã công bố |

Mô hình nhớ: **Predict overlap → Preserve evidence → Resolve by oracle → Prove topology**.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

- Git Reference Manual 2.54.0: `git merge`, `git rebase`, `git revert`, `git merge-base`, `git diff`, `git status`.
- Pro Git, 2nd Edition: basic branching/merging và distributed workflows.
- Vincent Driessen, *A successful Git branching model*: vai trò `develop` và feature integration trong Git Flow.
- Scrum Guide 2020: Increment/Definition of Done và ranh giới giữa Scrum với lựa chọn kỹ thuật.
- NovaShop Change Cards và Backlog synthetic: ngữ cảnh Cart, Checkout, Payment và acceptance oracle.

### Phần bổ sung/suy diễn

- **[BỔ SUNG — nguồn: Git Reference Manual 2.54.0]** Cách dùng `merge-base --is-ancestor`, `diff --check`, `status` và graph làm structural oracle được diễn giải độc lập cho môi trường đào tạo.
- **[SUY DIỄN — từ kiến thức đã huấn luyện]** Conflict map ba trục dependency/overlap/risk và bảng evidence pack là cấu trúc sư phạm dành riêng cho NovaShop; đây là team artifact, không phải lệnh Git hay thành phần Scrum bắt buộc.
- **[SUY DIỄN — từ kiến thức đã huấn luyện]** Dữ liệu MEX-U03-01 là synthetic và không tuyên bố phản ánh repository doanh nghiệp thật.

---
<!-- QUALITY GATE: 3/3 outline leaf đã tick và giữ đúng thứ tự; từng leaf có mapping, definition, role/decision, mechanism, use/not-use, example/oracle, best-practice positive-negative và failure chain; MEX-U03-01 phủ LO/outline và map CP-U03-01..03; không chứa mã nguồn ứng dụng. -->

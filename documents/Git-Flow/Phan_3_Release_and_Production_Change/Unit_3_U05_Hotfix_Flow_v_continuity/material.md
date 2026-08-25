# Unit U05: Hotfix Flow và continuity — Học liệu cốt lõi

> **Khóa học:** Git Flow thực chiến qua dự án NovaShop · **Hình thức:** project-based, không lập trình ứng dụng · **Thuộc:** Release and Production Change

## 🎯 Learning Outcomes

- **LO5.1** [analyze] — Phân loại hotfix so với feature hoặc release fix và vận hành hotfix từ `main` với regression evidence.
- **LO5.2** [evaluate] — Chứng minh hotfix đã được gắn patch tag và truyền tới `main`, `develop` hoặc release branch đang mở mà không làm mất thay đổi.

## 🧭 Ngữ cảnh dự án và phần tăng trưởng của Unit

NovaShop đang chạy bản mô phỏng `v0.1.0`. Trong khi nhóm đã đưa đặc tả Admin cho phiên bản kế tiếp lên `develop`, vận hành phát hiện bảng phí giao hàng ở production áp sai ngưỡng miễn phí. Học viên đóng vai thành viên chịu trách nhiệm incident và release governance: sửa đúng production baseline, không kéo theo thay đổi Admin chưa phát hành, và để lại bằng chứng cho dòng phát triển tương lai.

Project increment **M-GF-05** gồm:

- `project-artifacts/M-GF-05/hotfix-dossier-v0.1.1.md`;
- `project-artifacts/M-GF-05/workflow-continuity-audit-v0.1.1.md`;
- tag `v0.1.1` trên lịch sử `main`;
- `HOTFIX_CHANGE_COMMIT` được ghi trong dossier và containment evidence chứng minh chính change commit này có trong các nhánh bắt buộc.

Increment đạt khi hotfix bắt đầu từ production baseline, regression checklist PASS, không có feature ngoài incident, tag được tạo sau release gate trên `main`, và continuity audit có kết luận PASS/REVISE dựa trên Git evidence. Tất cả dữ liệu là **simulated**; không dùng giao dịch, credential hoặc thông tin khách hàng thật.

## 📚 Nguồn đầu vào đã map

- **SRC-GIT-DOC** — Git Reference Manual 2.54.0, Git Project / Software Freedom Conservancy, truy cập 2026-08-25.
- **SRC-PROGIT** — Pro Git, 2nd Edition, living web edition, truy cập 2026-08-25.
- **SRC-NVIE** — Vincent Driessen, *A successful Git branching model* (2010; reflection 2020), truy cập 2026-08-25.
- **SRC-SEMVER** — Semantic Versioning 2.0.0, truy cập 2026-08-25.
- **SRC-SCRUM** — The Scrum Guide, November 2020, truy cập 2026-08-25.
- **SRC-NS-CARDS** — NovaShop Git Flow change cards 1.0, internal approved.

---

## 1. Kiến thức tiên quyết và môi trường

Học viên đã hoàn thành U04, có repository artifact với `main` chứa tag `v0.1.0`, `develop` đã tiến về phiên bản kế tiếp, và biết đọc graph, ref, merge record. Công cụ cần dùng là Git CLI 2.40+ (course plan đã kiểm trên 2.54.0.windows.1), trình soạn Markdown tương thích CommonMark và trình sửa CSV UTF-8.

Preflight trong **bản sao riêng của repository học viên**:

```text
git --version
git config --get user.name
git config --get user.email
git status --short --branch
git show-ref --verify refs/heads/main
git show-ref --verify refs/heads/develop
git show-ref --verify refs/tags/v0.1.0
```

Môi trường sẵn sàng khi ba ref cuối tồn tại, working tree sạch và danh tính Git là danh tính đào tạo, không phải credential production. Phương thức xác minh của Unit là `artifact_review`: reviewer đối chiếu dossier, checklist và output Git với oracle định trước.

## 2. Định vị trong lộ trình (Mental Map)

U04 kết thúc release có kế hoạch; U05 xử lý thay đổi **không có kế hoạch** trên phiên bản đang chạy; U06 dùng evidence của U05 để audit governance và quyết định workflow.

```text
production symptom
  → triage loại thay đổi
  → hotfix từ main/production tag
  → sửa hẹp + regression evidence
  → capture HOTFIX_CHANGE_COMMIT
  → merge main → gate PASS → patch tag
  → propagate change commit sang develop hoặc release đang mở
  → containment audit + postmortem
```

Git chỉ chứng minh quan hệ lịch sử; Git không tự chứng minh incident đã hết. Vì vậy mỗi quyết định topology phải đi cùng business oracle trong artifact Markdown/CSV.

## 3. Nội dung lý thuyết cốt lõi

**📋 Checklist bắt buộc phủ — giữ nguyên văn và đúng thứ tự Content Outlines:**

- [x] Incident triage và quyết định hotfix so với feature hoặc release fix
- [x] Hotfix từ main, regression evidence và patch tag
- [x] Propagation tới develop hoặc release đang mở, postmortem và continuity audit

#### OUT-U05-01 Incident triage và quyết định hotfix so với feature hoặc release fix

**Mapping:** OUT-U05-01 · LO5.1 · M-GF-05, incident record và branch-type decision.

##### Định nghĩa và ranh giới

Incident triage xác nhận triệu chứng, mức ảnh hưởng, production baseline, độ khẩn và loại thay đổi trước khi chọn tuyến Git. **Hotfix** là nhánh hỗ trợ ngắn hạn tách từ `main` để sửa vấn đề nghiêm trọng của phiên bản production. **Release fix** sửa finding trên một release branch chưa phát hành. **Feature** tạo hoặc thay đổi capability cho phiên bản tương lai từ `develop`.

Điểm phân biệt không phải ticket có chữ “bug”, mà là **nơi lỗi tồn tại và thời điểm cần đưa sửa đổi vào sử dụng**. Lỗi chỉ có trên release candidate là release fix; cải tiến quy tắc tương lai là feature; hành vi sai đang ảnh hưởng production và không thể chờ release kế tiếp là ứng viên hotfix.

##### Vấn đề, vai trò và quyết định

Incident owner phải quyết định: có cần can thiệp production ngay không, baseline nào đang chạy, scope tối thiểu nào đủ khôi phục hành vi, và tuyến branch nào không kéo theo thay đổi chưa phát hành. Product Owner làm rõ tác động/ưu tiên; người làm việc chọn cách thực hiện; reviewer xác nhận evidence. Đây là working practice, không bổ sung accountability mới vào Scrum.

##### Cơ chế và mental model

Dùng bốn câu hỏi theo thứ tự:

1. Triệu chứng có tái lập trên ref production (`main`/tag đang chạy) không?
2. Tác động có đủ khẩn để không chờ release đang hoạch định không?
3. Sửa đổi khôi phục hành vi đã cam kết hay thêm capability?
4. Có thể cô lập phạm vi và kiểm chứng regression không?

Nếu câu 1–2 là “có”, câu 3 là “khôi phục” và câu 4 là “có”, chọn hotfix. Nếu lỗi chỉ ở release branch, chọn release fix. Nếu là capability mới hoặc không khẩn, đưa vào Product Backlog và xử lý bằng feature flow.

##### Khi dùng, khi không dùng và trade-off

- Dùng hotfix khi production đang sai, tác động cần xử lý sớm và fix có thể cô lập.
- Không dùng hotfix để né refinement, đưa feature “gấp” vào production, hoặc sửa finding chỉ tồn tại trên release candidate.
- Hotfix rút ngắn thời gian phản hồi nhưng tạo thêm merge, regression và continuity cost; hotfix lặp lại là tín hiệu cần inspect hệ thống chất lượng/cadence.

##### Ví dụ thực tế riêng và oracle

- **Context/stakeholder:** vận hành báo đơn synthetic có subtotal `600000` vẫn bị tính phí `30000`, trong khi rule phát hành là miễn phí từ `500000`.
- **Baseline/constraint:** tag production `v0.1.0`; `develop` đã có Admin vNext; không được đưa Admin vào patch.
- **Decision/action:** ghi triage HOTFIX-301 và chọn `hotfix/0.1.1-shipping-fee` từ `main`.
- **Artifact:** phần “Why hotfix instead of feature/release fix” trong dossier.
- **Expected:** record có production evidence, urgency, scope included/excluded và owner.
- **Oracle/evidence:** `git merge-base --is-ancestor v0.1.0 hotfix/0.1.1-shipping-fee` trả exit code `0`; diff hotfix không chứa artifact Admin.

##### Liên kết ví dụ triển khai trong Material

Thành phần “Triage” của **MEX-U05-01** ở mục 4 hiện thực OUT-U05-01. Lab **LAB-U05-01/CP-U05-01** tái tạo quyết định với boundary input mới và một nhánh sai nguồn phải chẩn đoán.

##### Best practices

| Rule | Rationale/cơ chế | Positive example | Negative example/hậu quả |
| --- | --- | --- | --- |
| Chốt production baseline và impact trước khi mở hotfix | Baseline sai làm fix mang theo thay đổi chưa production | HOTFIX-301 ghi `v0.1.0`, triệu chứng, scope exclusion Admin | Tạo từ `develop`; patch vô tình chứa Admin vNext |
| Ghi tiêu chí đóng incident trước khi sửa | Oracle có trước ngăn “fix theo cảm giác” | Ba mức subtotal có expected fee rõ | Chỉ ghi “phí đã đúng”; reviewer không tái lập được |
| Chọn scope nhỏ nhất khôi phục hành vi | Giảm regression surface và thời gian review | Chỉ sửa rule phí và checklist liên quan | Gộp wording checkout; khó rollback/audit |

##### Anti-pattern, failure modes và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán/bằng chứng | Cách sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| Hotfix chứa file Admin | Bắt đầu từ `develop` | `git diff --name-only v0.1.0...hotfix/0.1.1-shipping-fee` | Giữ evidence, tạo lại branch từ `main`; không rewrite shared branch | Triage template bắt buộc ghi source ref |
| Ticket “khẩn” nhưng không có production symptom | Scope pressure bị gọi nhầm incident | Record thiếu observed impact/ref | Trả về Product Backlog/feature flow | Review branch-type decision trước khi tạo branch |
| Reviewer không biết khi nào PASS | Không có oracle định lượng | Checklist chỉ có mô tả chung | Bổ sung input–expected result | Definition of Ready cho incident evidence |

#### OUT-U05-02 Hotfix từ main, regression evidence và patch tag

**Mapping:** OUT-U05-02 · LO5.1, LO5.2 · M-GF-05, hotfix branch, regression gate và tag `v0.1.1`.

##### Định nghĩa và ranh giới

Hotfix flow dùng `main`—nhánh biểu diễn trạng thái production-ready trong mô hình Git Flow—làm nguồn. Hotfix gồm các commit cần thiết cho incident rồi được merge vào `main`. **Regression evidence** chứng minh sửa đổi đạt incident oracle và không phá hành vi liên quan. **Patch tag** định danh commit phát hành trên `main`; tag không phải bằng chứng kiểm thử tự thân.

Trong khóa, `v0.1.1` là quy ước patch của NovaShop cho bug fix tương thích trên artifact contract. SemVer 2.0.0 xem `0.y.z` là initial development, nên không diễn giải `0.1.1` như bảo đảm ổn định phổ quát; nhóm phải công bố version policy.

##### Vấn đề, vai trò và quyết định

Người thực hiện phải quyết định commit nào nằm trong scope, regression cases nào bắt buộc, khi nào merge vào `main`, và chỉ tạo tag sau khi gate trên trạng thái `main` đạt PASS. Ngay sau commit chứa incident correction và regression artifacts, họ capture SHA commit đó thành `HOTFIX_CHANGE_COMMIT`; một commit metadata ghi SHA có thể theo sau. Change SHA này là điểm chung dùng để audit propagation mà không tạo bài toán tự tham chiếu.

##### Cơ chế và mental model

Tạo hotfix từ `main` làm production commit thành ancestor của hotfix. Khi cùng một hotfix được merge `--no-ff` riêng vào `main` và `develop`, hai nhánh có **hai merge commit khác nhau**, nhưng cùng chứa hotfix change commit. Tag `v0.1.1` đặt trên merge commit của `main` vì thế **không bắt buộc** là ancestor của `develop`. Oracle đúng tách hai claim:

```text
Tag v0.1.1 thuộc lịch sử main.
HOTFIX_CHANGE_COMMIT thuộc lịch sử main và nhánh tương lai bắt buộc.
```

Các lệnh kiểm:

```text
git rev-parse HEAD
git merge-base --is-ancestor v0.1.0 hotfix/0.1.1-shipping-fee
git cat-file -t refs/tags/v0.1.1
git merge-base --is-ancestor v0.1.1 main
git branch --contains HOTFIX_CHANGE_COMMIT
```

Lệnh `rev-parse HEAD` được chạy ngay sau commit correction/regression và trước metadata commit. Ở lệnh cuối, `HOTFIX_CHANGE_COMMIT` biểu thị SHA đã lưu trong dossier, không phải chuỗi gõ nguyên văn. `--is-ancestor` đạt với exit `0`; `cat-file` in `tag` nếu policy yêu cầu annotated tag.

##### Khi dùng, khi không dùng và trade-off

- Dùng annotated tag khi policy cần message/audit object; lightweight tag hợp lệ về Git nhưng không đạt policy NovaShop.
- Chưa tag khi regression còn REVISE hoặc merge vào `main` chưa hoàn tất.
- Không sửa/move tag đã chia sẻ; nếu nội dung phát hành thay đổi, phát hành version mới.
- `--no-ff` giữ merge event dễ thấy nhưng tạo merge commit khác nhau trên mỗi target; audit change commit thay vì đòi tag commit nằm ở mọi target.

##### Ví dụ thực tế riêng và oracle

- **Context:** regression owner kiểm bảng phí sau HOTFIX-301.
- **Input:** subtotal `499999`, `500000`, `650000`; expected fee `30000`, `0`, `0`.
- **Decision/action:** chỉ merge khi ba case và Cart/Checkout consistency PASS; capture SHA của commit chứa fix; merge `main`, review rồi tạo annotated tag.
- **Artifact:** `shipping-regression.csv`, merge review record, release note patch.
- **Expected:** tag object là `tag`; tag reachable từ `main`; patch diff không có Admin; dossier lưu SHA change commit.
- **Oracle:** `git diff --name-only v0.1.0..v0.1.1` đúng scope; `git merge-base --is-ancestor v0.1.1 main` trả `0`.

##### Liên kết ví dụ triển khai trong Material

Thành phần “Regression, capture change commit và patch tag” của **MEX-U05-01** hiện thực OUT-U05-02. Lab **CP-U05-02** thêm boundary case ban đầu REVISE; học viên đóng finding trước khi tag.

##### Best practices

| Rule | Rationale/cơ chế | Positive example | Negative example/hậu quả |
| --- | --- | --- | --- |
| Regression kiểm incident và hành vi lân cận | Fix hẹp vẫn có thể phá Cart/Checkout contract | Kiểm dưới/đúng/trên ngưỡng cùng consistency | Chỉ kiểm 600000; lỗi biên lọt qua |
| Capture commit chứa incident correction trước các merge | Merge commits trên targets khác nhau; change SHA là bằng chứng chung | Dossier lưu `HOTFIX_CHANGE_COMMIT` ngay sau fix commit; metadata commit có thể theo sau | Dùng tag main để audit develop và kết luận sai REVISE |
| Tag sau merge và gate PASS trên `main` | Tag phải định danh đúng release đã duyệt | Merge, review main, `git tag -a v0.1.1` | Tag trên hotfix trước review |

##### Anti-pattern, failure modes và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán/bằng chứng | Cách sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| `git cat-file -t refs/tags/v0.1.1` in `commit` | Tạo lightweight tag | Kiểm object type | Nếu chưa chia sẻ, tạo lại annotated tag theo policy; nếu đã chia sẻ, dừng và xin release decision | Checklist ghi tag type |
| Tag không reachable từ `main` | Tag trên hotfix chưa merge | `git merge-base --is-ancestor v0.1.1 main` trả `1` | Không publish; hoàn tất đúng tuyến rồi version theo policy | Tag containment gate |
| Continuity audit kiểm `v0.1.1` trong `develop` và FAIL | Nhầm main merge commit với change commit chung | Đọc graph và SHA incident correction commit | Audit lại bằng `HOTFIX_CHANGE_COMMIT` | Template tách tag containment và change containment |

#### OUT-U05-03 Propagation tới develop hoặc release đang mở, postmortem và continuity audit

**Mapping:** OUT-U05-03 · LO5.2 · M-GF-05, workflow continuity audit và postmortem.

##### Định nghĩa và ranh giới

**Propagation** làm production fix xuất hiện trong dòng phát triển tương lai. Theo Git Flow gốc, hotfix thường merge vào `main` và `develop`. Ngoại lệ: nếu có release branch, hotfix được merge vào release branch đó thay cho `develop`; khi release hoàn tất và back-merge, change commit tới `develop`. Nếu `develop` cần fix ngay, nhóm có thể merge thêm có chủ đích nhưng phải audit conflict/duplicate.

**Containment audit** kiểm `HOTFIX_CHANGE_COMMIT` có là ancestor của ref bắt buộc hay không. **Postmortem** ghi timeline, impact, root cause, detection gap, action phòng ngừa và owner; không phải nơi quy trách cá nhân. Containment chứng minh topology, không thay thế regression.

##### Vấn đề, vai trò và quyết định

Release owner chọn target theo trạng thái thật: không có release mở thì `develop`; có `release/0.2.0` thì release là target bắt buộc, còn đường tới `develop` được kiểm khi release finish. Reviewer chỉ kết luận continuity PASS khi `HOTFIX_CHANGE_COMMIT` nằm trong mọi target theo scenario và remediation có owner.

##### Cơ chế và mental model

`git branch --contains` liệt kê local branch có change commit làm ancestor. Khi release mở, chuỗi kỳ vọng là:

```text
v0.1.1 tag → main merge commit
HOTFIX_CHANGE_COMMIT → main
HOTFIX_CHANGE_COMMIT → release/0.2.0
release/0.2.0 finish → develop, nên HOTFIX_CHANGE_COMMIT → develop
```

Không suy ra containment từ tên branch hoặc ticket. Đặc biệt, không yêu cầu tag `v0.1.1` trên main merge commit phải nằm trong release/develop.

##### Khi dùng, khi không dùng và trade-off

- Audit ngay sau hotfix finish và audit lại khi release đang mở được finish.
- Không merge mù vào cả release và `develop` nếu cùng thay đổi gây conflict/duplicate; ghi lý do nếu propagation sớm.
- Không đóng incident chỉ vì `main` đã có tag nếu dòng tương lai chưa có route.
- Postmortem đủ nhẹ để hoàn thành nhưng phải có action, owner và oracle.

##### Ví dụ thực tế riêng và oracle

- **Context:** HOTFIX-301 xảy ra khi không có release branch mở, nhưng `develop` có Admin vNext.
- **Input/constraint:** `v0.1.1` đã ở `main`; dossier lưu `HOTFIX_CHANGE_COMMIT`; Admin phải được giữ.
- **Decision/action:** merge hotfix riêng vào `develop`, rồi audit change commit.
- **Artifact:** bảng target–evidence–result và action “thêm boundary-value row cho mọi shipping rule”.
- **Expected:** change commit ở `main` và `develop`; Admin vẫn ở `develop`; patch `v0.1.0..v0.1.1` không có Admin.
- **Oracle:** `git branch --contains HOTFIX_CHANGE_COMMIT` liệt kê `main` và `develop`; reviewer đối chiếu Admin preservation.

##### Liên kết ví dụ triển khai trong Material

Thành phần “Continuity” của **MEX-U05-01** hiện thực OUT-U05-03. Lab **CP-U05-03** đưa failure “change commit chưa có trong develop”; Assignment dùng constraint khó hơn là `release/0.2.0` đang mở.

##### Best practices

| Rule | Rationale/cơ chế | Positive example | Negative example/hậu quả |
| --- | --- | --- | --- |
| Target propagation theo trạng thái release thực tế | Route sai có thể bỏ sót/nhân đôi fix | Không release: merge `develop`; có release: merge release và audit đường về develop | Luôn merge mọi nơi theo thói quen |
| Audit change commit, không audit tag-main merge commit trên nhánh tương lai | Separate `--no-ff` merges tạo merge commits khác nhau | `git branch --contains` SHA incident correction commit | Đòi `v0.1.1` contained trong develop và báo lỗi giả |
| Postmortem action có owner và oracle | Action mơ hồ không phòng tái diễn | QA owner thêm ba boundary cases | “Cần test kỹ hơn”; không owner |

##### Anti-pattern, failure modes và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán/bằng chứng | Cách sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| `main` có change commit nhưng target tương lai không có | Quên propagation | `git branch --contains HOTFIX_CHANGE_COMMIT` | Merge hotfix vào target đúng, review conflict, audit lại | Hotfix DoD có change-containment gate |
| Release mở nhưng fix chỉ vào `develop` | Bỏ qua ngoại lệ Git Flow | So release với change SHA | Propagate vào release và tái UAT | Triage hỏi “active release?” |
| Postmortem action không owner | Đóng tài liệu hình thức | Audit cột owner/review condition | Gán owner, due condition, oracle | Không cho PASS khi owner rỗng |

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### MEX-U05-01 — Hotfix dossier v0.1.1 cho lỗi phí vận chuyển

**Mode:** professional artifact · **LO:** LO5.1, LO5.2 · **Outline:** OUT-U05-01, OUT-U05-02, OUT-U05-03 · **Mức xác thực:** simulated.

#### Input/trạng thái ban đầu

- `main` và tag `v0.1.0` cùng chỉ production baseline.
- `develop` có một commit cập nhật Admin vNext.
- HOTFIX-301: subtotal từ `500000` trở lên phải có shipping fee `0`; production artifact đang ghi lớn hơn `500000`.
- Không có release branch đang mở.

#### Professional artifact đã hoàn thiện

**Incident và branch decision**

| Trường | Giá trị mẫu |
| --- | --- |
| Incident / severity | HOTFIX-301 / P1 simulated |
| Observable impact | Subtotal đúng `500000` bị tính `30000` thay vì `0` |
| Production baseline | `v0.1.0` trên `main` |
| Decision | Hotfix; production sai và không thể chờ release kế tiếp |
| Included / excluded | Shipping threshold, regression, incident record / Admin vNext, bulk export |
| Source → targets | `main` → `hotfix/0.1.1-shipping-fee` → `main`, `develop` |
| Change identity | `HOTFIX_CHANGE_COMMIT` = SHA commit chứa shipping correction/regression; capture ngay sau commit đó, trước merge |

**Regression gate**

| Case | Input subtotal | Expected fee | Observed artifact result | Gate |
| --- | ---: | ---: | ---: | --- |
| REG-SHIP-01 | 499999 | 30000 | 30000 | PASS |
| REG-SHIP-02 | 500000 | 0 | 0 | PASS |
| REG-SHIP-03 | 650000 | 0 | 0 | PASS |
| REG-SHIP-04 | Cart/Checkout references | Same rule ID | Same rule ID | PASS |

**Release và continuity evidence contract**

| Claim | Oracle | Expected |
| --- | --- | --- |
| Hotfix từ production | `git merge-base --is-ancestor v0.1.0 hotfix/0.1.1-shipping-fee` | exit `0` |
| Change identity captured | `git rev-parse HEAD` ngay sau correction/regression commit | SHA lưu trong dossier; metadata commit có thể theo sau |
| Patch đúng scope | `git diff --name-only v0.1.0..v0.1.1` + review | Không có Admin vNext |
| Annotated patch tag | `git cat-file -t refs/tags/v0.1.1` | `tag` |
| Tag thuộc main | `git merge-base --is-ancestor v0.1.1 main` | exit `0` |
| Change ở các dòng bắt buộc | `git branch --contains HOTFIX_CHANGE_COMMIT` | Có `main`, `develop` |
| Repository sạch | `git status --short --branch` | Chỉ branch header |

**Postmortem excerpt**

| Mục | Nội dung mẫu |
| --- | --- |
| Root cause | Boundary `>= 500000` bị ghi thành `> 500000` |
| Detection gap | Regression trước release thiếu đúng boundary `500000` |
| Prevention | Mọi shipping threshold phải có dưới/đúng/trên boundary |
| Owner/oracle | QA owner; gate kế tiếp có đủ ba row và reviewer ký PASS |

#### Luồng quyết định và hành động

1. Triage khóa baseline, impact, scope và chọn hotfix.
2. Hotfix branch từ `main`; chỉ incident artifacts thay đổi; regression PASS.
3. SHA của commit chứa incident correction/regression được capture thành `HOTFIX_CHANGE_COMMIT`; metadata record có thể được commit sau.
4. Hotfix merge riêng vào `main`; reviewer kiểm trạng thái `main`, rồi tạo annotated tag `v0.1.1`.
5. Hotfix merge riêng vào `develop`; audit change SHA, đóng postmortem.

#### Expected result và oracle

MEX PASS khi regression PASS, source/tag oracle đạt, tag object là `tag`, patch diff không có Admin và `git branch --contains HOTFIX_CHANGE_COMMIT` có `main` cùng `develop`. Việc `v0.1.1` không contained trong `develop` sau hai `--no-ff` merge riêng là hợp lệ; change commit mới là oracle propagation.

### Mapping Material worked example → Hands-on Lab tương ứng

- **MEX-U05-01 → LAB-U05-01/CP-U05-01:** tái tạo triage/source decision với wrong-source branch.
- **MEX-U05-01 → LAB-U05-01/CP-U05-02:** thêm boundary input REVISE, capture change commit và chỉ tag sau gate.
- **MEX-U05-01 → LAB-U05-01/CP-U05-03:** debug change-containment thiếu trên `develop`, ghi prevention/recovery.

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

1. **Ancestor command không có output nhưng bị hiểu là lỗi.** `git merge-base --is-ancestor` dùng exit status: `0` là đúng, `1` là không; kiểm exit status thay vì chờ text.
2. **Tag tồn tại nhưng sai loại.** `git cat-file -t refs/tags/v0.1.1` in `commit` với lightweight tag, `tag` với annotated tag.
3. **Dùng tag để audit develop.** Tag ở main merge commit có thể không nằm trong develop; lấy SHA incident correction commit đã capture và kiểm `git branch --contains`.
4. **Merge đang dang dở.** Lưu `git status`; trên bản sao lab có thể `git merge --abort`, rồi quyết định lại. Không rewrite shared history để làm graph “đẹp”.
5. **Business checklist PASS nhưng topology sai.** Hai gate độc lập; source/target phải được sửa và evidence tái tạo.

## 6. Từ điển thuật ngữ và mô hình tư duy

| Thuật ngữ | Nghĩa trong NovaShop |
| --- | --- |
| Production baseline | Commit/tag đại diện phiên bản mô phỏng đã phát hành |
| Hotfix | Nhánh ngắn hạn từ `main` cho lỗi production khẩn |
| Release fix | Sửa finding trên release branch chưa production |
| Regression evidence | Input, expected, observed và PASS/REVISE |
| HOTFIX_CHANGE_COMMIT | SHA commit chứa incident correction/regression, bằng chứng chung qua các merge target |
| Annotated tag | Tag object có metadata/message; NovaShop dùng cho release |
| Propagation | Đưa change commit sang dòng tương lai đúng tuyến |
| Containment | Quan hệ một commit là ancestor của ref mục tiêu |
| Continuity audit | Chứng minh release hiện tại và tương lai không mất fix |
| Postmortem | Root cause, detection gap, prevention, owner sau incident |

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

- https://nvie.com/posts/a-successful-git-branching-model/ — hotfix targets và ngoại lệ khi release branch mở.
- https://git-scm.com/docs/git-merge-base — semantics của `--is-ancestor`.
- https://git-scm.com/docs/git-tag — annotated/lightweight tag.
- https://semver.org/ — MAJOR.MINOR.PATCH, bất biến sau release và `0.y.z`.
- https://scrumguides.org/scrum-guide.html — ranh giới Scrum/practice.
- `starter/NovaShop_Change_Cards.md` — HOTFIX-301 và INC-501, internal approved.

### Phần bổ sung/suy diễn

- [BỔ SUNG — nguồn: NovaShop Project Brief và Change Cards] Subtotal, fee, severity, file artifact và regression rows là synthetic.
- [SUY DIỄN — từ Git graph semantics] Cấu trúc bảng continuity audit/postmortem và tên field `HOTFIX_CHANGE_COMMIT` được thiết kế cho M-GF-05.

---
<!-- QUALITY GATE: 3/3 outline leaf đã tick và đủ semantic contract; MEX-U05-01 phủ LO5.1/LO5.2, map CP-U05-01..03; tag-main containment tách khỏi change-commit propagation; không có mã nguồn ứng dụng. -->

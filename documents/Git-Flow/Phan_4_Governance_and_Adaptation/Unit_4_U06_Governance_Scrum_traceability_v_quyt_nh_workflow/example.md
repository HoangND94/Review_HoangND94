# Unit U06 — Example CASE-U06-01: Audit không phải cuộc thi đếm lỗi

> **Mức xác thực:** simulated · **Mode:** professional artifact · **Không có mã nguồn ứng dụng**

## 🎯 Learning Outcomes liên quan

- **LO6.1 / OUT-U06-01, OUT-U06-02:** audit six observations, tránh false positive, tách team/Git Flow/Scrum rules và tạo remediation có owner.
- **LO6.2 / OUT-U06-03:** viết ADR dựa trên drivers; trong changed context này quyết định **giữ Git Flow có thời hạn**, đối lập với MEX pilot simpler flow.
- **Project increment:** M-GF-06 — audit report và ADR-GF-002.

## 🧰 Điều kiện kiểm chứng

Case dùng Git CLI 2.40+ trong repository artifact local cô lập, Markdown/CommonMark và CSV UTF-8. Các lệnh chỉ đọc graph/ref/object; validation method là `artifact_review`. Không dùng hosting API, network, credential hoặc dữ liệu production. Khi case ghi tên biến commit in hoa, reviewer dùng SHA synthetic đã có trong evidence record, không gõ tên biến như một ref Git.

## 1. Ticket và tiêu chí thành công

**Ticket GOV-602:** Trước khi rollout `v0.2.0`, sponsor hỏi vì sao nhóm không bỏ `develop`/release branch ngay sau audit MEX. Reviewer nhận sáu observation mới; một số đáng ngờ nhưng hợp lệ. Họ phải chỉ tạo finding khi evidence chứng minh chênh lệch, sửa một Scrum statement sai và dùng metrics mới để quyết định workflow.

Tiêu chí thành công:

- 6/6 observations được xem xét, nhưng PASS không bị biến thành finding;
- mỗi finding có exact evidence, tầng rule, severity, owner, remediation và closure oracle;
- Git evidence không thay thế Scrum artifact/commitment/event;
- ADR có cadence, supported versions, lead time, merge cost, alternatives, consequences và trigger.

## 2. Input, baseline và constraints

### Audit observations

| ID | Observation supplied |
| --- | --- |
| O-01 | Một emergency commit vào `main` có incident ID nhưng after-the-fact review record bắt buộc còn thiếu |
| O-02 | Feature Order Tracking có merge base/source từ `develop` và review PASS |
| O-03 | `v0.1.1` là annotated tag trên lịch sử `main` |
| O-04 | Hotfix change commit có trong `main` và active `release/0.2.0`; release chưa finish |
| O-05 | Release-fix change commit đã có trong `develop` |
| O-06 | Working agreement ghi “PR merge chứng minh Increment đạt Definition of Done” |

`git fsck --no-reflogs --unreachable` còn báo một unreachable object sau khi trainer xóa branch thực hành đã phê duyệt. Không có evidence force-push/corruption khác.

### Delivery drivers — changed input

- planned release cadence: mỗi 4 tuần;
- supported version lines: `0.1.x` và `0.2.x` song song trong 8 tuần theo scenario;
- median ready-to-release lead time: 4 ngày, release stabilization waiting 0.5 ngày;
- merge/back-merge coordination: 2 person-hours/release;
- sample window: 3 release exercises; số liệu synthetic, uncertainty cao.

Constraints: không rewrite history, không move tag, không tự gọi hosting API, không dùng output unreachable làm finding nếu thiếu causal evidence.

## 3. Phân tích lựa chọn

### 3.1 Phân loại evidence thay vì đoán

Audit dùng rule: “suspicious” không đồng nghĩa “REVISE”. O-02..05 có positive oracle; O-01 và O-06 thiếu/vi phạm expected condition. Unreachable object được ghi là **context note**, không phải finding.

### 3.2 Workflow options

| Option | Fit với input | Trade-off |
| --- | --- | --- |
| A — Giữ classic Git Flow trong 8 tuần | Hai supported version lines và planned stabilization có giá trị; current merge cost thấp | Tiếp tục back-merge/branch governance; phải đóng review/Scrum findings |
| B — Chuyển ngay main + short-lived topics | Topology đơn giản hơn | Mất isolation đúng lúc đang patch hai version lines; migration giữa rollout tăng risk |
| C — Transition sau support window | Giữ controls hiện tại, chuẩn bị main-readiness pilot khi chỉ còn một line | Decision bị trì hoãn; cần trigger rõ để không thành trì hoãn vô hạn |

Chọn **C**, với operating state A trong 8 tuần. Đây không mâu thuẫn MEX: context/metrics khác dẫn tới decision khác.

## 4. Cách triển khai professional artifacts

### 4.1 Audit matrix

| ID | Rule layer + exact oracle | Observed result | Status | Remediation / owner / closure |
| --- | --- | --- | --- | --- |
| O-01 | Team emergency-main policy yêu cầu incident link **và** retrospective review | Incident có; review thiếu | REVISE / High | Release owner tổ chức review; close khi record có disposition và prevention |
| O-02 | Git Flow feature source `develop`; review policy PASS | Source/record đủ | PASS | Không remediation; giữ sample evidence |
| O-03 | Team release policy annotated tag; tag phải ở `main` | type `tag`, ancestor main exit `0` | PASS | Không “sửa” tag |
| O-04 | Active-release exception; audit **change commit**, không tag-main merge commit | change contained main/release; develop pending đúng lifecycle | PASS-with-follow-up | Release owner audit develop khi release finish; chưa gọi missing fix |
| O-05 | Release fix phải back-merge `develop` | ancestor exit `0` | PASS | Không remediation |
| O-06 | Scrum DoD/Increment không được thay bởi PR state | Statement đánh đồng | REVISE / Medium | Scrum Master coach boundary; release owner sửa team policy; peer-review statement |

Context note: unreachable object có thể xuất hiện sau branch deletion; thiếu evidence causal nên không chấm violation. Nếu sau này có ref-update log/reflog evidence, mở finding mới thay vì sửa ngược audit này.

### 4.2 Corrected Scrum boundary statement

> PR/merge evidence có thể hỗ trợ transparency về thay đổi và review. Một Increment chỉ được xem là đáp ứng Definition of Done khi toàn bộ DoD evidence áp dụng đạt; Git merge không thay thế Increment hoặc DoD. Sprint Review inspect outcome và adaptation, không phải PR/release gate bắt buộc của Scrum.

Statement ghi hai owners: Scrum Master hỗ trợ hiểu Scrum; release owner duy trì team merge/release policy. Nó không chuyển quyền kỹ thuật cho một Scrum accountability.

### 4.3 ADR-GF-002 — Workflow trong cửa sổ hỗ trợ hai versions

| Trường | Nội dung đã điền |
| --- | --- |
| Status | Accepted for 8-week support window |
| Context | Planned 4-week cadence, two supported lines, low measured merge cost, rollout đang diễn ra |
| Option A | Giữ Git Flow |
| Option B | Chuyển simpler flow ngay |
| Option C | Giữ có thời hạn, transition review sau support window |
| Decision | Option C; vận hành Git Flow 8 tuần, không migration giữa rollout |
| Consequences | Duy trì release/hotfix route; thêm after-the-fact review gate; chuẩn bị main-readiness checklist |
| Scrum boundary | Workflow là team practice; không thêm/bớt Scrum element |
| Trigger | Review khi chỉ còn 1 supported line **hoặc** merge cost >6 person-hours/release trong 2 releases **hoặc** lead-time waiting >40% trong 2 releases |
| Owner/review | Workflow owner; review cuối support window với peer evidence |

Các ngưỡng là trigger scenario do team chọn, không phải benchmark ngành.

## 5. Output mong đợi

- Audit có **2 findings, 4 PASS observations và 1 context note**; không inflate count để “đạt 5/6 violations”. LO6.1 yêu cầu phát hiện ≥5/6 trong fixture CARD-U06/MEX, không yêu cầu mọi sample đều có 5 lỗi.
- O-04 không bị false negative vì tag `v0.1.1` có thể không contained trong active release; change SHA mới là propagation oracle.
- Working agreement tách PR evidence khỏi Increment/DoD.
- ADR giữ Git Flow có thời hạn vì hai supported versions, đồng thời có trigger transition/review.

## 6. Cách xác minh

| Claim | Validation | Expected |
| --- | --- | --- |
| Tag đúng policy/main | `git cat-file -t refs/tags/v0.1.1`; `git merge-base --is-ancestor v0.1.1 main` | `tag`; exit `0` |
| Hotfix active-release continuity | `git branch --contains` với `HOTFIX_CHANGE_COMMIT` | `main`, `release/0.2.0` |
| Release-fix back-merge | `git merge-base --is-ancestor RELEASE_FIX_COMMIT develop` | exit `0` |
| Unreachable classification | `git fsck --no-reflogs --unreachable` + context review | note only; không auto-REVISE |
| Scrum boundary | Artifact/commitment/event checklist | không gọi PR/Git Flow/tag là Scrum element |
| ADR completeness | peer checklist | 4 drivers, 3 options, consequences, trigger, owner đều có |

Các tên `HOTFIX_CHANGE_COMMIT` và `RELEASE_FIX_COMMIT` trong bảng biểu thị SHA thật đã ghi trong fixture/evidence record; reviewer dán SHA khi chạy.

## 7. Failure modes, limits và trade-off

### False positive từ lifecycle chưa hoàn tất

**Dấu hiệu:** develop chưa chứa hotfix khi active release chưa finish. **Nguyên nhân:** reviewer kiểm trạng thái cuối quá sớm. **Chẩn đoán:** release vẫn open, change đã contained trong release. **Sửa:** PASS-with-follow-up và closure audit khi finish. **Phòng tránh:** finding có lifecycle/timepoint.

### False assurance từ PR merge

**Dấu hiệu:** O-06 gọi merged là Done. **Nguyên nhân:** dùng Git state làm proxy toàn bộ quality. **Chẩn đoán:** DoD checklist còn evidence ngoài Git. **Sửa:** corrected boundary statement; **phòng tránh:** separate DoD oracle.

### ADR không còn đúng sau support window

Decision hiện tại tối ưu isolation nhưng giữ topology cost. Khi chỉ còn một supported line, evidence có thể ủng hộ simpler flow; trigger buộc review. ADR là reversible decision record, không phải giáo điều.

### Giới hạn case

Sample chỉ có ba release exercises, số liệu synthetic và không đại diện benchmark. Case chứng minh phương pháp ra quyết định, không chứng minh Git Flow tốt hơn cho mọi sản phẩm.

## 8. Bài học chuyển giao

Audit tốt giảm cả false negative lẫn false positive. Workflow decision phải thay đổi khi context thay đổi; cùng một nhóm có thể chọn Git Flow trong cửa sổ multi-version rồi chuyển flow đơn giản khi chỉ còn một line. Lab sẽ dùng CARD-U06 với sáu lỗi cài sẵn và metrics khác; học viên phải tự viết audit/ADR, không sao chép decision của case.

## Provenance của các case

- SRC-NVIE — classic routes và context fit/reflection.
- SRC-GIT-DOC, SRC-PROGIT — tag, ancestor, reachability evidence.
- SRC-SCRUM — Increment, DoD, Sprint Review purpose và practices outside framework.
- [SUY DIỄN — từ project scenario] O-01..06, support window, metrics và ADR triggers là fixtures synthetic.

---
<!-- QUALITY GATE: case có ticket, input/constraint, analysis, implementation artifact, exact expected output, validation, failure modes/trade-off; map LO6.1/LO6.2 và 3 outline; khác MEX về objective/input/decision. -->

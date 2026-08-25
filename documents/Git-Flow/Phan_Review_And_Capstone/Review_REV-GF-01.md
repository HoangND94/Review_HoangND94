# Review tích hợp — Review chẩn đoán Git Flow NovaShop

> **Khóa học:** Git Flow thực chiến qua dự án NovaShop · **Loại khóa:** Git branching workflow, release governance và Agile/Scrum artifact delivery

| Thuộc tính | Giá trị |
| --- | --- |
| Mã review | REV-GF-01 |
| Thời lượng dự kiến | 60 phút |
| Mức xác thực | simulated |

## 🗺️ Phạm vi ôn tập
U01–U05: branch routing, feature evidence, conflict, release và hotfix continuity

## 🎯 Learning Outcomes được củng cố/đánh giá
- **LO1.1** [analyze] — Phân loại đúng vai trò, nguồn, đích và vòng đời của main, develop, feature, release và hotfix trong ít nhất 8/10 tình huống NovaShop. · Bằng chứng: Branch-routing decision table và graph có giải thích.
- **LO1.2** [apply] — Khởi tạo baseline repo tài liệu NovaShop có main, develop, tag mốc và policy kiểm chứng được. · Bằng chứng: Git refs, branch graph và baseline checklist.
- **LO2.1** [apply] — Vận hành feature branch từ develop tới develop cho một PBI NovaShop và duy trì truy vết PBI–commit–review–acceptance evidence. · Bằng chứng: Feature evidence pack và pull-request review record.
- **LO2.2** [evaluate] — Đánh giá một feature đã đủ điều kiện merge theo Definition of Done, review findings và trạng thái working tree. · Bằng chứng: Merge decision có kết luận PASS/REVISE và evidence.
- **LO3.1** [analyze] — Chẩn đoán và giải quyết conflict giữa các feature branch mà không làm mất acceptance criteria đã phê duyệt. · Bằng chứng: Conflict decision log và diff sau resolution.
- **LO3.2** [evaluate] — Lựa chọn merge, no-fast-forward, rebase cục bộ hoặc revert phù hợp với ownership và rủi ro lịch sử. · Bằng chứng: Strategy decision record và branch graph sau tích hợp.
- **LO4.1** [apply] — Vận hành release branch từ develop qua scope freeze, UAT fix, merge main/develop và đóng branch đúng topology. · Bằng chứng: Release dossier, graph và containment evidence.
- **LO4.2** [create] — Gắn annotated tag và lập release evidence có version rationale, compatibility contract và traceability tới scope Done. · Bằng chứng: Tag audit, changelog và release traceability matrix.
- **LO5.1** [analyze] — Phân loại hotfix so với feature hoặc release fix và vận hành hotfix từ main với regression evidence. · Bằng chứng: Incident triage record và hotfix branch evidence.
- **LO5.2** [evaluate] — Chứng minh hotfix đã được gắn patch tag và truyền tới main, develop hoặc release branch đang mở mà không làm mất thay đổi. · Bằng chứng: Containment audit và workflow continuity record.

| Learning Outcomes | Unit nguồn | Evidence được ôn lại |
| --- | --- | --- |
| LO1.1, LO1.2 | U01 | Routing table, baseline graph, `show-ref` |
| LO2.1, LO2.2 | U02 | Feature dossier, review disposition, merge-to-develop evidence |
| LO3.1, LO3.2 | U03 | Conflict decision log, merge/rebase boundary, recovery evidence |
| LO4.1, LO4.2 | U04 | Scope freeze, UAT decision, annotated tag và back-merge evidence |
| LO5.1, LO5.2 | U05 | Incident triage, hotfix origin, patch tag và containment audit |

Review chỉ kết hợp lại các quyết định và oracle đã luyện ở U01–U05; không giới thiệu branch type, lệnh Git hay quy tắc Scrum mới.

## 🧭 Ngữ cảnh tích hợp nghề nghiệp/dự án

**Bối cảnh nghề nghiệp/dự án:**
**NovaShop** — MVP thương mại điện tử B2C mô phỏng gồm tìm kiếm, giỏ hàng, checkout, thanh toán sandbox, theo dõi đơn và quản trị cơ bản.. Vai trò học viên: Thành viên nhóm sản phẩm chịu trách nhiệm quản lý thay đổi, review, release và hotfix trên repository artifact NovaShop.. Mục tiêu: Thiết lập và vận hành Git Flow có bằng chứng để đưa NovaShop từ backlog qua feature, release và hotfix mà không viết mã nguồn ứng dụng.

**Project increment hoặc vấn đề tích hợp cần xử lý:**
- **milestone_id:** M-GF-REV
- **artifacts_added:** - Reviewed workflow diagnosis
- **baseline:** Increments M-GF-01 through M-GF-05
- **change_scope:** - Cross-flow diagnosis and correction list

## 🧰 Điều kiện thực hiện

**Kiến thức/kỹ năng tiên quyết:**
- **completed_units:** - U01<br>- U02<br>- U03<br>- U04<br>- U05
- **assets:** - NovaShop branch graph snapshot<br>- Feature/Integration/Release/Hotfix evidence samples

**Môi trường, công cụ và phiên bản:**
- **profile_ref:** ENV-GIT-ARTIFACT
- **description:** Repo Git local cô lập chứa duy nhất artifact Markdown/CSV của NovaShop; không có mã nguồn ứng dụng, dịch vụ cloud hay credential.
- **operating_system:** Windows, macOS hoặc Linux
- **runtimes:** _(Không có / chưa áp dụng)_
- **tools:** - - **name:** Git CLI<br>- **version:** 2.40+; verified on 2.54.0.windows.1<br>- - **name:** Markdown editor<br>- **version:** CommonMark-compatible<br>- - **name:** CSV editor<br>- **version:** UTF-8 compatible
- **services:** _(Không có / chưa áp dụng)_
- **overrides:** _(Không có / chưa áp dụng)_

## 🧩 Nhiệm vụ review

### Nhiệm vụ 1 — Routing under pressure (20 phút)

- **Vai trò/scenario:** bạn là release facilitator nhận mười change cards đã xáo trộn: feature Search mới, Cart finding trước merge, UAT wording fix, production shipping incident, documentation correction, feature chưa Done, hotfix khi release đang mở, experiment bị hủy, tag correction và backlog clarification.
- **LO/Unit:** LO1.1–LO1.2/U01, LO2.1/U02, LO4.1/U04, LO5.1/U05.
- **Input/baseline:** routing sheet trống; main đang ở `v0.1.0`, develop đã tiến thêm, `release/0.2.0` đang mở. Không được giả định mọi thay đổi đều cần branch mới.
- **Yêu cầu:** với mỗi card, chọn `feature`, `release fix`, `hotfix`, thay đổi backlog không đi vào repo, hoặc từ chối xử lý; ghi nguồn, đích, vòng đời và một evidence oracle.
- **Deliverable:** corrected branch-routing map.
- **Acceptance/verification:** tối thiểu 8/10 quyết định đúng; tất cả hotfix bắt đầu từ main; không feature nào kết thúc ở main; đối chiếu bằng routing rules U01 và `git merge-base`/containment oracle đã học.
- **Phản tư:** một routing map nhiều branch có giảm hay làm tăng lead time trong bối cảnh release hằng ngày?

### Nhiệm vụ 2 — Forensic graph và release continuity (25 phút)

- **Vai trò/scenario:** bạn là reviewer tiếp quản một graph snapshot sau feature, release và hotfix. Snapshot đi kèm sáu symptom: direct commit vào main, feature sai nguồn, conflict resolution làm mất AC, lightweight tag, release fix thiếu ở develop và hotfix chỉ có ở main.
- **LO/Unit:** LO2.2/U02, LO3.1–LO3.2/U03, LO4.1–LO4.2/U04, LO5.2/U05.
- **Input/baseline:** graph, `show-ref`, `branch --contains` và hai artifact diff; một finding là false positive có chủ đích.
- **Constraint:** không sửa graph trong Review; chỉ chẩn đoán từ evidence. Không kết luận chỉ dựa trên tên branch.
- **Yêu cầu:** lập diagnosis sheet gồm symptom → exact evidence → cause → impact → correction → prevention; đánh dấu finding false positive và giải thích oracle bác bỏ.
- **Deliverable:** violation diagnosis sheet và corrected graph vẽ lại ở mức ref/merge cần thiết.
- **Acceptance/verification:** mỗi lỗi thật có evidence quan sát được; không dùng rebase để chữa shared history; release/hotfix correction giữ đủ containment; false positive được loại bằng lệnh hoặc artifact evidence.
- **Trade-off:** sửa graph bằng merge bổ sung hay revert có thể làm lịch sử kém tuyến tính nhưng bảo toàn audit trail như thế nào?

### Nhiệm vụ 3 — Peer review và correction decision (15 phút)

- **Vai trò/scenario:** đổi artifact với một nhóm khác; bạn là peer reviewer, không phải người làm thay.
- **LO/Unit:** LO2.2/U02, LO3.2/U03, LO4.2/U04, LO5.2/U05.
- **Input/constraint:** routing map và diagnosis sheet của nhóm bạn; chỉ dùng acceptance criteria ở Review, không thêm team policy mới.
- **Yêu cầu:** ghi tối đa ba findings theo `error|warning`, exact evidence, owner và disposition; người nhận sửa hoặc nêu quyết định không sửa có risk rõ.
- **Deliverable:** peer feedback record.
- **Acceptance/verification:** mọi `error` được đóng trước kết luận PASS; warning có owner/decision; reviewer có thể đi tới cùng kết luận từ evidence mà không hỏi người tạo.
- **Phản tư:** evidence nào chứng minh topology, evidence nào chỉ mô tả ý định?

## 📦 Deliverables
- Corrected branch-routing map
- Violation diagnosis sheet
- Peer feedback record

## ✅ Acceptance criteria
- Tối thiểu 8/10 routing decisions đúng
- Mỗi lỗi có evidence, cause, correction và prevention
- Không thêm quy tắc chưa được dạy

## 🧪 Cách xác minh
**Phương thức:** artifact_review

- `Đối chiếu branch graph và containment output theo Review oracle`

**Bằng chứng phải nộp:**
- Decision sheet
- Corrected graph
- Peer feedback

## 📊 Rubric hoặc cơ chế phản hồi
Không chấm điểm; dùng acceptance criteria/checklist phản hồi.

> **Quality gate:** Nếu `graded=true`, tổng trọng số rubric phải đúng **100%** và từng dòng map tới Learning Outcome/bằng chứng quan sát được. Nếu `graded=false`, nêu rõ cơ chế phản hồi theo acceptance criteria và không giả lập điểm số.

## 📚 Nguồn đầu vào và provenance

### Nguồn đã map
- SRC-GIT-DOC — Git Reference Manual: https://git-scm.com/docs/git/2.54.0 (publisher: Git Project / Software Freedom Conservancy; version: 2.54.0; accessed_at: 2026-08-25; license: GPL-2.0-only; reference use with independent explanation; allowed_use: reference)
- SRC-NVIE — A successful Git branching model: https://nvie.com/posts/a-successful-git-branching-model/ (publisher: Vincent Driessen / nvie; version: 2010-01-05; reflection 2020-03-05; accessed_at: 2026-08-25; license: Page text reference-only; separately licensed diagram is not redistributed; allowed_use: reference)
- SRC-SCRUM — The Scrum Guide: https://scrumguides.org/scrum-guide.html (publisher: Ken Schwaber, Jeff Sutherland / ScrumGuides.org; version: November 2020; accessed_at: 2026-08-25; license: CC BY-SA 4.0; allowed_use: adapt)
- SRC-NS-CARDS — NovaShop Git Flow change cards: starter/NovaShop_Change_Cards.md (publisher: Training artifact created for this course; version: 1.0; accessed_at: 2026-08-25; license: Internal approved for learner use; allowed_use: internal_approved)

### Phần bổ sung/suy diễn
- `[BỔ SUNG — nguồn: Git Reference Manual 2.54.0]` Dùng `merge-base`, `show-ref` và branch containment làm oracle cho ancestry/ref; Review không yêu cầu lệnh ngoài các Unit trước.
- `[BỔ SUNG — nguồn: The Scrum Guide, November 2020]` Review giữ ranh giới: Git evidence hỗ trợ minh bạch nhưng không thay thế Product Backlog, Increment hoặc Definition of Done.
- `[SUY DIỄN — từ project spine NovaShop]` Mười routing card và graph có false positive là dữ liệu mô phỏng để luyện chẩn đoán; không mô tả như incident thật.

---
<!-- QUALITY GATE: chỉ dùng phạm vi đã học; mỗi nhiệm vụ nối >=2 chủ đề; có expected output + validation; graded thì rubric = 100%, ungraded thì có cơ chế phản hồi; mọi trường đã hoàn thiện. -->

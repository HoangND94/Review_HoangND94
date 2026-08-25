# Review REV-01 — Từ Product Goal đến Sprint Planning

| Thuộc tính | Giá trị |
| --- | --- |
| Covers | U03–U06 |
| Thời lượng | 60 phút |
| Graded | false — phản hồi theo acceptance criteria |
| LO | LO3.1–LO6.2 |
| Validation | artifact_review |
| Xác thực | simulated |

## 🗺️ Phạm vi ôn tập

U03 Product Goal/stakeholder, U04 story mapping/PBI/acceptance criteria, U05 refinement/sizing/ordering và U06 Sprint Goal/Sprint Backlog. Review chỉ nối kiến thức đã học, không thêm framework hay kỹ thuật bắt buộc mới.

## 🎯 Learning Outcomes được củng cố/đánh giá

- LO3.1–LO3.2: Product Goal, stakeholder/customer evidence.
- LO4.1–LO4.2: journey → story map/backlog, vertical slice và observable acceptance.
- LO5.1–LO5.2: relative sizing, uncertainty và ordering evidence.
- LO6.1–LO6.2: Sprint Goal, capacity forecast và why/what/how plan.

## Mục tiêu tích hợp

Review không dạy kiến thức mới. Nhóm kiểm tra chuỗi đã học:

`stakeholder evidence → Product Goal → journey/story map → Product Backlog → refinement/ordering → Sprint Goal → Sprint Backlog`

Một link sai ở upstream phải xuất hiện trong impact downstream. Output của Review là `Integrated traceability review` và `Prioritized correction list`; chúng là evidence cho Capstone, không phải Assignment mới.

## Bối cảnh và input mới

Kho vận cho biết address validation cần thêm failure behavior cho vùng không hỗ trợ giao hàng. Sponsor vẫn muốn guest checkout và capacity Sprint giảm 20%. Nhóm nhận Product Goal, stakeholder map, Story Map, Backlog v2, sizing record, Sprint Goal và Sprint Backlog do một team khác tạo; trong bộ artifact có ít nhất ba inconsistency do giảng viên cài trước.

Constraints: không đổi Product Goal chỉ để giải một task; không giảm DoD; không dùng story point như giờ; mọi finding phải có evidence và downstream impact.

## Nhiệm vụ 1 — Goal-to-backlog integrity

- **Kết nối:** U03 + U04; LO3.1, LO3.2, LO4.1, LO4.2.
- **Vai trò:** Product Owner và peer reviewer.
- **Yêu cầu:** tìm PBI/acceptance example thiếu journey/goal link, scope nằm ngoài product boundary, hoặc stakeholder claim không có evidence.
- **Deliverable:** trace snapshot gồm `source → decision → artifact → oracle` và finding ID.
- **Acceptance:** 100% PBI thuộc MVP slice có actor/outcome, Product Goal link và observable acceptance evidence; item ngoài scope được remove/defer bằng rationale.
- **Trade-off phản tư:** guest checkout tạo value nào và có guardrail dữ liệu gì?

## Nhiệm vụ 2 — Backlog readiness và ordering

- **Kết nối:** U04 + U05; LO4.2, LO5.1, LO5.2.
- **Vai trò:** Developers trong refinement.
- **Input mới:** failure path “vùng không hỗ trợ giao hàng” và dependency shipping sandbox.
- **Yêu cầu:** review vertical slice, sizing assumptions và ordering rationale; không yêu cầu mọi PBI có cùng mức chi tiết.
- **Deliverable:** finding list với severity `error|warning`, affected PBI, evidence, owner và proposed decision (không phải solution implementation).
- **Acceptance:** estimate dispersion có reason; dependency/risk/learning value xuất hiện trong ordering; acceptance example quan sát được cho failure path.
- **Trade-off phản tư:** đưa risk item sớm có thể giảm feature output nhưng tăng learning như thế nào?

## Nhiệm vụ 3 — Sprint forecast consistency

- **Kết nối:** U05 + U06; LO5.1, LO5.2, LO6.1, LO6.2.
- **Vai trò:** toàn Scrum Team tại Sprint Planning review.
- **Input mới:** capacity giảm 20% sau khi backlog đã ordered.
- **Yêu cầu:** kiểm Sprint Goal có outcome và Product Goal link; kiểm selected scope/plan phản ánh capacity, history, DoD, dependency và risk.
- **Deliverable:** correction list được ưu tiên theo impact tới Sprint Goal/transparency.
- **Acceptance:** why/what/how nhất quán; forecast ghi assumptions; scope có thể đổi nhưng Sprint Goal/DoD không bị sửa tùy tiện.
- **Trade-off phản tư:** giảm scope nào ít làm mất learning/value nhất, và evidence nào hỗ trợ quyết định?

## Deliverables

1. `Integrated traceability review`: tối thiểu các cột Finding ID, source artifact/version, LO/outline, symptom, evidence, impact downstream, severity.
2. `Prioritized correction list`: finding, owner, decision deadline, acceptance oracle và artifact cần cập nhật.

Không nộp đáp án triển khai hay code. Reviewer chỉ yêu cầu chain hợp lệ và quyết định có evidence.

## ✅ Acceptance criteria

| Check | PASS khi | Feedback khi chưa đạt |
| --- | --- | --- |
| Goal → backlog → Sprint Goal | Mọi link resolve, boundary nhất quán | Chỉ rõ link mồ côi và artifact owner |
| Evidence | Mỗi finding trích exact field/ID, không chỉ nêu cảm giác | Yêu cầu bổ sung observation/oracle |
| Cross-impact | Upstream change liệt kê downstream affected artifacts | Gắn severity error nếu forecast/goal sai |
| Correction priority | Có impact, owner, due checkpoint và pass-fail oracle | Trả về nếu chỉ ghi “cần cải thiện” |
| Scope/data | Synthetic-only, không unsupported claim | Loại dữ liệu/claim và reset từ starter |

Peer pairs đổi bộ artifact, review 10 phút rồi trả `PASS|REVISE` cùng tối đa ba findings ưu tiên. Review hoàn tất khi ba nhiệm vụ và năm check có evidence; không quy đổi thành điểm.

## 📊 Rubric hoặc cơ chế phản hồi

Review `graded=false`: không có điểm hay trọng số. Peer reviewer phản hồi theo năm acceptance checks, mỗi finding phải có `file/ID`, evidence quote/value, severity, owner và action; chỉ trạng thái `PASS` mới cho phép dùng planning baseline ở Capstone.

## Reset và reuse

Không sửa artifact gốc của team khác. Tạo annotated copy; nếu mapping sai dây chuyền, quay về Product Goal version đã nhận và áp từng correction theo thứ tự upstream → downstream. Giữ trace snapshot/correction list cho CAP-01.

## Provenance

- [Scrum Guide 2020](https://scrumguides.org/scrum-guide.html).
- [Introduction to the Product Backlog](https://www.scrum.org/resources/introduction-product-backlog), accessed 2026-08-25.
- [Introduction to Sprint Planning](https://www.scrum.org/resources/introduction-sprint-planning), accessed 2026-08-25.
- `[SUY DIỄN — từ kiến thức đã huấn luyện]` Inconsistencies, capacity shock và shipping constraint là dữ liệu đào tạo simulated.

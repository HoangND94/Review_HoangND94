# Unit U08: Definition of Done, Increment và Sprint Review — Assignment 04

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASM-U08 (Assignment 04) |
| Thời lượng | 90 phút |
| Hình thức | Team submission, đánh giá độc lập |
| Bloom | evaluate, create |
| Mức xác thực | simulated |

## 🎯 Learning Outcomes được đánh giá

- **LO8.1:** Áp dụng acceptance criteria và Definition of Done để phân loại chính xác Done/Not Done kèm evidence.
- **LO8.2:** Tổng hợp stakeholder feedback thành Product Backlog changes có owner, rationale và traceability.

## Scenario độc lập

Sponsor muốn trình diễn checkout dù address picker chưa hoàn thành selected keyboard test. Đồng thời stakeholders đưa yêu cầu mới về cách hiển thị phí vận chuyển. Nhóm phải ra quyết định chất lượng, tổ chức Sprint Review trên outcome thật và tạo Product Backlog v3 để ASM-U10 dùng cho release forecast.

Đây là đề đánh giá, không phải walkthrough. Học viên tự chọn cấu trúc phân tích và thứ tự làm việc; không sao chép decision/artifact từ Material, Example hoặc Lab.

## 🔗 Liên kết project xuyên suốt

- **Milestone:** M-U08.
- **Dependency:** ASM-U06/Assignment 03.
- **Baseline tiêu thụ:** `Sprint Goal`, `Sprint Backlog` đã nộp ở ASM-U06.
- **Artifacts tạo ra:** `Increment evidence pack`, `Sprint Review record`, `Product Backlog v3`.
- **Downstream reuse:** ASM-U10/Assignment 05 dùng `Sprint Review record` và `Product Backlog v3`; Capstone dùng cả ba artifact.

Nếu baseline A03 thiếu ID/evidence link, nhóm phải ghi assumption/gap trong submission; không được thay bằng một Sprint Goal mới không truy vết.

## Input package

### A03 baseline excerpt

- Sprint Goal `SG-A03`: “người mua hoàn tất checkout sandbox và thấy tổng phí trước khi xác nhận, kể cả khi payment bị từ chối”.
- Sprint Backlog item IDs: `A04-411 address picker`, `A04-412 payment decline persistence`, `A04-413 order status audit`.
- DoD áp dụng: `DOD-NS-1.0` gồm AC PASS; peer review; integration evidence; selected responsive/accessibility/security checks theo scope; docs/audit evidence khi áp dụng; không Critical/High mở.

### Synthetic evidence fixture

| PBI | Acceptance evidence | DoD evidence |
| --- | --- | --- |
| A04-411 | AC1 chọn tỉnh/thành bằng pointer PASS; AC2 giữ địa chỉ khi quay lại PASS | peer/integration/docs PASS; selected keyboard test `E-A04-KB411` FAIL: không mở được province list bằng Enter/Space; selected authz not-applicable có rationale |
| A04-412 | AC1 decline hiển thị lỗi PASS; AC2 input được giữ PASS; AC3 retry tạo một order PASS | peer/integration/docs PASS; selected keyboard test PASS; selected authorization test PASS |
| A04-413 | AC1 customer chỉ thấy order của mình PASS; AC2 admin update status PASS | peer/integration/selected authz PASS; required audit event evidence `E-A04-AUD413` MISSING |

Mọi test chạy trên synthetic fixture. Accessibility scope chỉ bao phủ checkout flow trên Firefox/Windows và selected keyboard interaction; security scope chỉ bao phủ selected customer/admin authorization cases. Không có bằng chứng cho claim WCAG 2.2 AA, ASVS 5.0.0 level hay production conformance toàn diện.

### Stakeholder feedback cards

| ID | Source/need | Evidence/constraint |
| --- | --- | --- |
| FB-A04-01 | Customer Service muốn tách shipping fee khỏi product subtotal trước payment | 6/12 synthetic tickets hỏi vì sao tổng tiền tăng |
| FB-A04-02 | Sponsor muốn lưu thẻ thật để “one-click” | Trái constraint no-card-data/sandbox; không có security design |
| FB-A04-03 | Sales muốn thêm marketplace seller ngay Sprint tới | Ngoài MVP system boundary; chưa có Product Goal change |

## 🧠 Khái niệm và best practices được đánh giá

### TASK-U08-01 — Quality decision và feedback adaptation

| Contract | Mapping |
| --- | --- |
| OUT-U08-01 / LO8.1 | Scenario: evidence fixture + `DOD-NS-1.0`; rule: mỗi decision phải resolve criterion→evidence→scope→Done/Not Done; rationale: ngăn decision cảm tính; deliverable: Increment evidence pack; oracle: AT-U08-01; rubric: RB-U08-01 |
| OUT-U08-02 / LO8.2 | Scenario: ba feedback cards + Goal/boundary; rule: mọi feedback có disposition, trade-off, owner và downstream update; rationale: giữ closed-loop traceability; deliverables: Sprint Review record + Product Backlog v3; oracle: AT-U08-02; rubric: RB-U08-02 |

Best-practice constraints bắt buộc: không hạ DoD hồi tố; không gọi undone work là Increment; không suy rộng selected check thành full conformance; accepted feedback phải xuất hiện trong backlog diff; deferred/rejected feedback vẫn có rationale và audit link.

## 📋 Yêu cầu

### Functional requirements

- **FR-01 [LO8.1]:** phân loại toàn bộ ba PBI bằng AC và mọi DoD check áp dụng; ghi evidence/gap và Increment membership.
- **FR-02 [LO8.1]:** tạo scope/limitation statement cho selected accessibility/security evidence.
- **FR-03 [LO8.2]:** tạo Sprint Review record có Sprint Goal progress, Done outcome, Not Done gaps, thay đổi môi trường và disposition toàn bộ feedback.
- **FR-04 [LO8.2]:** tạo Product Backlog v3 diff có add/update/order, owner, rationale và traceability tới feedback/evidence.

### Non-functional requirements và loại trừ

- **NFR-01 [LO8.1]:** mọi evidence ID trong decision phải resolve; `MISSING/FAIL` không được viết thành PASS.
- **NFR-02 [LO8.1]:** claim chỉ giới hạn ở fixture/page/flow/role/browser/selected check được cung cấp; không tuyên bố whole-standard/production conformance.
- **NFR-03 [LO8.2]:** mọi artifact dùng ID ổn định; không PII, credential hoặc dữ liệu thẻ thật.
- Out of scope: sửa phần mềm, chạy audit WCAG/ASVS đầy đủ, thiết kế lưu thẻ thật, thay Product Goal hoặc mở rộng marketplace.

## 📦 Deliverables và cách nộp

Nộp một thư mục `ASM-U08/`:

1. `Increment_Evidence_Pack.md` — AC/DoD/evidence/scope/decision/Increment membership cho 3 PBI.
2. `Sprint_Review_Record.md` — outcome inspection và 3/3 feedback dispositions.
3. `Product_Backlog_v3.md` — baseline/diff/order/rationale/owner/evidence links; đủ để ASM-U10 dùng.
4. `Traceability_and_Oracle.md` — mapping LO→FR/NFR→deliverable→AT→rubric và self-check result.

Được nộp Markdown hoặc PDF tương đương, nhưng ID/link phải đọc và truy vết được. Không nộp dữ liệu ngoài fixture.

## ✅ Acceptance criteria và output mong đợi

### AT-U08-01 — Quality gate có thể tái kiểm [LO8.1]

**Given** A03 baseline, evidence fixture và `DOD-NS-1.0`; **when** reviewer chọn bất kỳ PBI; **then** reviewer lần theo được AC, từng DoD check áp dụng, evidence status, scope/limitation, decision và Increment/backlog disposition mà không cần hỏi nhóm. Không có item với criterion bắt buộc FAIL/MISSING được liệt kê như Increment Done.

Evidence chấm: Increment evidence pack + traceability table. Failure behavior: link không resolve, DoD bị sửa, hoặc claim vượt scope ⇒ AT-U08-01 FAIL.

### AT-U08-02 — Feedback tạo adaptation nhất quán [LO8.2]

**Given** Sprint Goal, kết quả quality gate và ba feedback cards; **when** reviewer chọn bất kỳ feedback; **then** reviewer thấy disposition, evidence/rationale/trade-off, owner, PBI/link hoặc trigger; Product Backlog v3 và Sprint Review record nhất quán. Downstream handoff nêu rõ artifact/field ASM-U10 sẽ dùng.

Evidence chấm: Review record + backlog v3 diff + impact/traceability. Failure behavior: “ghi nhận” không owner/trigger, accepted feedback không có backlog link, hoặc baseline A03 bị thay không giải thích ⇒ AT-U08-02 FAIL.

## 📊 Rubric chấm điểm — tổng 100%

| ID | Trọng số | LO | Excellent | Meets | Partial | Not met |
| --- | ---: | --- | --- | --- | --- | --- |
| RB-U08-01 — Đúng khái niệm, trace và evidence | 50% | LO8.1 | AT-U08-01 PASS; mọi link/scope độc lập kiểm được; giải thích trade-off/limitation chính xác | AT-U08-01 PASS; decision cốt lõi đúng, đủ AC/DoD/evidence/scope | Decision hợp lý nhưng thiếu một liên kết hoặc limitation quan trọng | AT FAIL; gọi work thiếu gate là Done, sửa DoD hồi tố hoặc claim conformance không có basis |
| RB-U08-02 — Change và downstream consistency | 50% | LO8.2 | AT-U08-02 PASS; cả edge case/trade-off/ordering/A05 handoff rõ | AT-U08-02 PASS; 3/3 feedback và backlog diff nhất quán | Có disposition nhưng thiếu owner/trigger, ordering rationale hoặc downstream link | AT FAIL; feedback mất dấu, baseline/Goal bị phá hoặc A05 không tiêu thụ được |

Điểm đạt: 70%, đồng thời không được có vi phạm critical: undone work được gọi Done, DoD bị hạ hồi tố, dữ liệu thật/secret, hoặc claim WCAG/ASVS toàn diện không có evidence.

## 🧪 Cách xác minh

Reviewer thực hiện artifact review, không cần công cụ trả phí:

- resolve 100% PBI/evidence/feedback/PBI-backlog IDs;
- tái chạy invariant AC+DoD trên cả ba PBI;
- so Sprint Review record với Increment membership;
- so 3 feedback cards với Product Backlog v3/decision log;
- xác nhận scope statement và A03→A04→A05 handoff.

## Nguồn và provenance

- **SRC-SG20** — [The Scrum Guide, November 2020](https://scrumguides.org/scrum-guide.html).
- **SRC-DOD** — [What is the Definition of Done?](https://www.scrum.org/resources/what-definition-done-0), snapshot 2026-08-25.
- **SRC-WCAG22** — [WCAG 2.2 Recommendation](https://www.w3.org/TR/2024/REC-WCAG22-20241212/).
- **SRC-ASVS500** — [OWASP ASVS 5.0.0](https://github.com/OWASP/ASVS/tree/v5.0.0_release).
- Assignment fixture: **[BỔ SUNG — nguồn: SRC-PROJECT, synthetic course data]**. Không có dữ liệu doanh nghiệp/khách hàng thật.

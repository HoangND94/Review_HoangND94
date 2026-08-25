# Unit U03: Product Goal, stakeholder và khách hàng — Ví dụ và nghiên cứu tình huống

> **Case ID:** CASE-U03-01 · **Mức xác thực:** simulated · **Milestone:** M-U03

## 🎯 Learning Outcomes liên quan

- **LO3.1 / OUT-U03-01:** viết Product Goal có outcome, metric, boundary và review trigger.
- **LO3.2 / OUT-U03-02:** phân tích buyer, Customer Service, warehouse và sponsor bằng evidence map/persona/journey.

## Điều kiện chạy case

Dùng ENV-PRO-ARTIFACT, Markdown editor và spreadsheet CSV UTF-8. Mở starter project brief/dataset/template và Team Charter baseline. Validation là artifact review.

## Nguồn đầu vào đã map

- SRC-SG20 — https://scrumguides.org/scrum-guide.html — Product Goal/product boundary, November 2020.
- SRC-EBM24 — https://www.scrum.org/resources/online-evidence-based-management-guide — outcome/evidence framing, May 2024.
- SRC-AP01 — https://agilemanifesto.org/principles.html — customer feedback/collaboration, version 2001.
- SRC-PROJECT — starter/NovaShop_Project_Brief.md — simulated context, version 1.0.

## Case Study 01: Product Goal cho self-service order status

### 1. Ticket và tiêu chí thành công

- **Vai trò:** Product Owner chuẩn bị discovery cho slice order tracking.
- **Vấn đề:** OBS-04 ghi 6/15 support requests hỏi trạng thái. Sponsor đề xuất “xây timeline 12 trạng thái” nhưng chưa có evidence rằng mức chi tiết này tạo value.
- **Input khác Material MEX:** case thu hẹp vào status self-service, dùng một synthetic comprehension test riêng; không tái dùng Goal giảm re-entry.
- **Tiêu chí:** Goal không khóa timeline 12 trạng thái; có primary outcome/guardrail/boundary/trigger; ít nhất ba stakeholder claims có evidence và conflict.

### 2. Input, trạng thái ban đầu và ràng buộc

| ID | Card |
| --- | --- |
| OBS-04 | 6/15 synthetic support requests hỏi trạng thái |
| EV-C03-01 | 9/12 người mua mô phỏng giải thích đúng “trạng thái hiện tại + mốc tiếp theo” |
| EV-C03-02 | 5/12 giải thích đúng timeline 12 trạng thái; case-specific synthetic test |
| WH-C03-01 | Warehouse cần tên trạng thái map được tới workflow; stakeholder constraint, chưa có usage count |
| SP-C03-01 | Sponsor muốn giảm 50% status-help requests; target assumption |
| FR-04 | Chỉ hiển thị order thuộc tài khoản/session mô phỏng |

Boundary: tracking/status/correlation trong web responsive; refunds, ERP đầy đủ, carrier production và notification automation ngoài case. Thời horizon: hai Sprint mô phỏng. Không có production telemetry.

### 3. Phân tích lựa chọn

Option “timeline 12 trạng thái” cụ thể nhưng khóa solution trước khi hiểu need; EV-C03-02 còn cho tín hiệu comprehension thấp. Option “cải thiện trải nghiệm” quá mơ hồ để order backlog. Lựa chọn là Goal ở mức outcome: người mua tự hiểu order state và next step, giảm nhu cầu hỏi trạng thái; cách biểu diễn emerge qua backlog/experiments.

Primary metric dùng status-help requests/15 sessions vì baseline có denominator. Comprehension là leading signal. FR-04 là privacy guardrail; đạt metric nhưng lộ order sai owner vẫn thất bại.

### 4. Cách triển khai professional artifact

#### Product Goal card PG-C03-TRACK

| Trường | Nội dung |
| --- | --- |
| Future state | Người mua mô phỏng tự hiểu order state và next step, Customer Service tập trung vào exception thay vì status lookup |
| Primary metric | status-help requests / 15 tracked-order sessions |
| Baseline/target/horizon | 6/15 → không quá 3/15 sau hai Sprint mô phỏng |
| Leading signal | ít nhất 10/12 người mô phỏng giải thích đúng state/next step |
| Boundary | current state, next step, synthetic correlation/history; web responsive |
| Out of scope | refund workflow, carrier production, ERP, 12-state solution commitment |
| Guardrails | 100% evidence cards chỉ hiển thị order đúng owner/session; no PII |
| Assumptions | comprehension improvement sẽ giảm help request; cần kiểm |
| Review triggers | guardrail fail; metric không tái tính; warehouse mapping conflict không giải được; Goal không còn valuable/feasible |

#### Stakeholder evidence map

| Stakeholder | Claim/need | Evidence | Confidence/limitation | Implication/conflict |
| --- | --- | --- | --- | --- |
| Buyer | hiểu nhanh trạng thái và hành động tiếp | OBS-04, EV-C03-01/02 | medium, synthetic sample 12–15 | explore comprehensible state model, không khóa 12 states |
| Customer Service | giảm status lookup, giữ exception context | OBS-04 | medium; request type proxy | track help reason/correlation |
| Warehouse | state names phải map workflow | WH-C03-01, stakeholder constraint | low-medium; chưa có count | validate mapping; conflict simplicity vs operational precision |
| Sponsor | giảm 50% help requests | SP-C03-01 target | low as evidence | measurement target, không claim achieved |

#### Persona và journey

**Persona behavior:** “Người mua muốn biết order đang ở đâu và cần làm gì tiếp theo.” Evidence-backed attributes: có status question (OBS-04) và comprehension differs by representation (EV-C03-01/02). Unknown: notification preference. Không thêm tuổi, giới, nghề hoặc quote.

| Journey step | Need/action | Evidence/pain | Handoff | Opportunity |
| --- | --- | --- | --- | --- |
| Order confirmation | biết order đã được ghi nhận | FR-03/04 contract | checkout → order | clear confirmation/correlation |
| Open tracking | xem đúng order | FR-04 guardrail | account/session → order | ownership evidence |
| Interpret status | hiểu current/next step | EV-C03-01/02 | order state → buyer | test representation |
| Exception/support | hỏi khi action needed | OBS-04 | buyer → CS/warehouse | context-rich help path |

### 5. Output mong đợi

Goal cho phép nhiều solutions cạnh tranh trong backlog nhưng mọi option phải hỗ trợ same outcome/guardrail. Giả sử sau hai Sprint có 3/15 help requests, comprehension 11/12 nhưng một owner-visibility check fail: kết luận là **review/adapt**, không công bố Goal achieved, vì guardrail hỏng.

### 6. Cách xác minh

| Test | PASS condition |
| --- | --- |
| Goal | outcome, formula, baseline/target/horizon, boundary, guardrail, ≥2 triggers |
| Stakeholders | ≥3 groups; claim→evidence→confidence→implication |
| Persona | mọi attribute có evidence/assumption; không stereotype |
| Journey | end-to-end, pain/evidence/handoff/opportunity; không chỉ screen list |
| Conflict | buyer comprehension vs warehouse precision có trade-off/research need |
| Safety | FR-04/no PII và simulated limitation rõ |

Một test fail làm artifact REVISE. Reviewer không chấm “đẹp” hoặc chọn solution ưa thích.

### 7. Giải thích sâu và failure modes

Primary metric là proxy trong scenario nhỏ; nó không chứng minh satisfaction hoặc business value ngoài lớp. Nếu team đổi denominator từ 15 sang 30 nhưng giữ nguyên count target 3 mà không version contract, so sánh mất nghĩa. Nếu persona ghi “người trẻ thích tracking”, không có source; phải loại.

Failure mode khác là biến WH-C03-01 thành quyền veto. Warehouse cung cấp constraint/evidence; PO accountable Goal/backlog và Scrum Team collaborate. Conflict cần test representation/mapping, không thắng bằng chức danh.

### 8. Bài học chuyển giao

Product Goal nên ổn định đủ để tạo focus nhưng có trigger để abandon/adapt khi evidence làm objective không còn hợp lệ. Stakeholder map cho biết **vì sao** một opportunity có trong journey; nó không tự động tạo feature. LAB-U03-01 dùng buyer/warehouse evidence cards khác và một output request mới.

## Provenance của các case

- Product Goal/Scrum facts từ SRC-SG20; outcome framing từ SRC-EBM24; feedback principle từ SRC-AP01.
- OBS-04, FR-04 và product boundary từ SRC-PROJECT/starter dataset.
- [SUY DIỄN — từ kiến thức đã huấn luyện] EV-C03-01/02, WH-C03-01, SP-C03-01, thresholds và persona/journey là synthetic instructional case.

> **Simulated disclosure:** không có customer research hoặc production result thật; mọi count chỉ dùng làm oracle trong lớp.

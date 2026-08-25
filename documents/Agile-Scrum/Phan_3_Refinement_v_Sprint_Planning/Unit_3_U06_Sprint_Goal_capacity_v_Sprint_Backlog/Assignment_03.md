# Unit U06 — Assignment 03: Sprint Planning khi capacity giảm 30%

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASM-U06 |
| Hình thức | team, thực hiện độc lập |
| Thời lượng | 90 phút |
| Độ khó/Bloom | medium / create |
| Xác thực | simulated |
| Validation | artifact_review |

> Đây là đánh giá độc lập. Đề chỉ cung cấp input, constraints và oracle; không cung cấp thứ tự thao tác, Sprint Goal mẫu, forecast tham chiếu hoặc Sprint Backlog đã điền.

## 🎯 Learning Outcomes được đánh giá

- **LO6.1:** viết Sprint Goal liên kết Product Goal và chọn forecast phù hợp với backlog order, capacity, lịch sử, uncertainty và DoD.
- **LO6.2:** tạo Sprint Backlog gồm why, what, how, dependency, acceptance evidence, risk response và adaptation boundary.

## 🧭 Scenario và input pack

Sau khi ASM-U04 tạo Story Map/Product Backlog v1 và U05 refine thành Product Backlog v2, NovaShop chuẩn bị Sprint 10 ngày. Hai thành viên có lịch vắng **bất đối xứng** làm capacity giảm đúng 30%; payment sandbox bảo trì toàn bộ ngày 2. Nhóm phải bảo vệ một Sprint Goal tạo value, đồng thời forecast minh bạch thay vì giữ scope bằng cách giảm chất lượng.

Input bắt buộc:

- **Story Map** và **Product Backlog v1** đã đạt ASM-U04;
- Product Backlog v2 cùng sizing/ordering record được tạo từ chính PBI ID của baseline đó ở U05;
- Product Goal và Definition of Done trong project brief;
- historical Done sizes của ba Sprint tương đồng: `13, 16, 15` relative units; sample nhỏ, không phải guarantee;
- capacity calendar: đội thường có 5 thành viên trong 10 ngày (50 person-days availability context); member A vắng D1–D10 và member B vắng D6–D10, còn 35 person-days, giảm 30%; support duty vẫn như baseline lịch sử;
- payment notice: sandbox unavailable D2, expected available D3; sandbox contact available D1/D3/D5; fixture chỉ được dùng để chuẩn bị/chẩn đoán, không thay integration evidence nếu DoD yêu cầu;
- change constraint: Product Owner không đổi Product Goal hoặc Product Backlog order trong bài, nhưng sẵn sàng thương lượng selected scope khi Developers nêu evidence.

Các con số chỉ là simulated scenario. Không đổi relative size thành giờ/person-day, không dùng velocity để so đội, không dùng tiền/thẻ/credential thật.

## 🔗 Liên kết project xuyên suốt

- **Milestone:** M-U06.
- **Depends on:** ASM-U04.
- **Baseline artifacts tiêu thụ:** Product Backlog v1; Story Map. Đây là output chính thức của direct dependency ASM-U04. Mỗi selected PBI phải dùng ID/Goal/journey link của chuỗi artifact này hoặc có impact note giải thích mapping sau refinement U05.
- **Derived practice inputs:** Product Backlog v2 và Sizing record được tạo trong U05 từ đúng chuỗi PBI của baseline A02. Chúng cung cấp readiness/size/order evidence cho scenario, nhưng không phải project-link baseline và không tạo thêm một Assignment dependency. Reviewer phải lần được v2/sizing về PBI ID của v1 và Story Map.
- **Produces:** Sprint Goal; Sprint Backlog.
- **Reused by:** ASM-U08 để quality-gate Increment và tổ chức Sprint Review.
- **Terminal delivery:** NOT_APPLICABLE — Assignment chưa cuối.

## 🧠 Khái niệm và best practices được đánh giá

### TASK-U06-01 — Ra quyết định Sprint Planning dưới constraint mới

| Contract | Nội dung |
| --- | --- |
| Concept refs | OUT-U06-01, OUT-U06-02 |
| LO | LO6.1, LO6.2 |
| Scenario/input | A02 artifacts, Product Backlog v2, history, asymmetric absence calendar (-30%), D2 maintenance, DoD |
| Deliverables | Sprint Goal; Sprint Backlog |
| Acceptance refs | AT-U06-01, AT-U06-02 |

**Best-practice constraint 1 — OUT-U06-01:** “Mọi quyết định thuộc OUT-U06-01 phải liên kết input, mục tiêu và evidence chấp nhận.” Rationale đã dạy: traceability ngăn quyết định cảm tính và cho phép stakeholder kiểm tra lại giả định; trong bài này, forecast còn phải công khai history, upcoming capacity, DoD, uncertainty và scope boundary. Áp dụng cho **AT-U06-01** và **RB-U06-01**.

**Best-practice constraint 2 — OUT-U06-02:** “Mọi thay đổi thuộc OUT-U06-02 phải nêu trade-off và cập nhật artifact downstream bị ảnh hưởng.” Rationale đã dạy: thay đổi cục bộ mà không cập nhật chuỗi artifact làm mất minh bạch; trong bài này, Sprint Backlog phải ghi dependency condition, owner/trigger, evidence và risk response mà không giảm DoD. Áp dụng cho **AT-U06-02** và **RB-U06-02**.

## 📋 Yêu cầu

### Functional requirements

- **FR-ASM-U06-01 [LO6.1]:** Sprint Goal là một objective theo outcome, có Product Goal link và boundary; không phải danh sách PBI hoặc target point.
- **FR-ASM-U06-02 [LO6.1]:** forecast selected PBI do Developers đưa ra, tôn trọng Product Backlog order và nêu history/capacity/DoD/skill/dependency evidence, assumptions, uncertainty, core/negotiable scope cùng trigger review.
- **FR-ASM-U06-03 [LO6.2]:** Sprint Backlog thể hiện why, what, how cho mọi selected PBI và nối về ID/Goal/journey/evidence của baseline A02/U05.
- **FR-ASM-U06-04 [LO6.2]:** plan xử lý hai lịch vắng bất đối xứng và payment maintenance bằng dependency condition, owner/inspection trigger, happy/late behavior, forecast impact và risk response; fixture limitation phải rõ.

### Non-functional requirements

- **NFR-ASM-U06-01 [LO6.1, LO6.2] — Không giảm Definition of Done:** work thiếu mandatory evidence không được gọi Done và không được tính như Increment usable.
- **NFR-ASM-U06-02 [LO6.1] — Forecast phải công khai assumptions:** artifact dùng ngôn ngữ forecast/uncertainty, không guarantee, point-to-time conversion, productivity comparison hoặc unsupported certainty.

### Constraints và out of scope

- Product Goal, Product Backlog order, relative sizes, calendar và maintenance notice là input cố định; nhóm có thể ghi inconsistency/risk nhưng không âm thầm sửa.
- Không yêu cầu task-hour schedule, cá nhân hóa performance, implementation/API/UI design hay kế hoạch production.
- Không sao chép Goal, forecast, số scope hoặc Sprint Backlog row từ Material/Lab; input Assignment khác và phải có decision riêng.
- Nếu một PBI baseline không đủ readiness/evidence để forecast, nêu rõ risk/decision; không tự bịa acceptance behavior.

## 📦 Deliverables và cách nộp

1. **Sprint Goal** — artifact có Goal, Product Goal link, forecast basis, selected/core/negotiable scope, assumptions/uncertainty, DoD statement và review trigger.
2. **Sprint Backlog** — artifact có why/what/how, traceability, dependency/owner/trigger, acceptance evidence/DoD, risk response, adaptation boundary và impact note cho absence/maintenance.

Tên logic: `ASM-U06_Sprint-Goal` và `ASM-U06_Sprint-Backlog`. Nộp Markdown/PDF/bảng export theo nền tảng lớp, cùng version, có reviewer/timestamp mô phỏng và evidence location cho AT-U06-01/02. Hai artifact được xem là nộp đủ khi mở được, ID resolve về A02/U05, không có PII/secret và đủ thông tin để ASM-U08 dùng mà không đoán scope/DoD.

## ✅ Acceptance criteria và output mong đợi

### AT-U06-01 — Sprint Goal và forecast có evidence [LO6.1 → RB-U06-01]

**Contract từ plan:** Artifact thể hiện đúng quyết định thuộc OUT-U06-01 và truy vết được tới dữ liệu đầu vào. Expected: người chấm xác định được input, quyết định, lý do và bằng chứng chấp nhận mà không cần suy đoán.

**Given** Product Goal, ordered Product Backlog v2, history `13/16/15`, capacity calendar giảm 30% và unchanged DoD; **when** reviewer đọc Sprint Goal/forecast và loại thử một selected PBI; **then** reviewer xác định được outcome cần bảo vệ, PBI core/negotiable, basis/assumptions/uncertainty và điều kiện review mà không suy đoán. Goal vẫn có coherence, forecast không được diễn đạt như guarantee và không dùng point-time conversion.

**Expected evidence:** `Product Goal → Sprint Goal → selected PBI` resolve; history/capacity/DoD/skill/dependency đều được cân nhắc; scope-removal/impact note cho thấy boundary; mọi claim có source field trong artifact.

### AT-U06-02 — Sprint Backlog thích nghi nhất quán [LO6.2 → RB-U06-02]

**Contract từ plan:** Artifact xử lý change request mới thuộc OUT-U06-02 mà không phá vỡ mục tiêu và baseline đã được phê duyệt. Expected: tác động, trade-off, tiêu chí chấp nhận và phần cập nhật downstream đều nhất quán.

**Given** member A/B vắng theo capacity calendar và payment sandbox unavailable D2; **when** reviewer inspect từng selected row và áp hai trạng thái `available D3`/`still unavailable D3`; **then** plan cho thấy why/what/how, dependency condition/owner/trigger, acceptance evidence, risk response, forecast impact và phần scope có thể thương lượng; fixture không thay mandatory integration evidence, DoD không giảm và baseline trace không bị đứt.

**Expected evidence:** mọi selected PBI có complete planning row; maintenance/absence impact đồng bộ với Goal/forecast; late behavior tạo một quyết định/trigger quan sát được; Sprint Backlog có đủ thông tin làm baseline cho ASM-U08.

## 🧪 Cách xác minh

Hai reviewer độc lập chạy AT-U06-01 và AT-U06-02, ghi `PASS`/`REVISE`, PBI/row/evidence location và lý do. Reviewer cũng kiểm rubric evidence, Story Map/Product Backlog ID và DoD version. Kết quả cuối chỉ PASS khi hai acceptance tests cùng PASS, hai artifact cùng version, 100% selected PBI resolve và không có quality downgrade/PII/secret. Bất đồng reviewer nghĩa là oracle/rationale chưa đủ rõ và cần REVISE.

## 📊 Rubric chấm điểm — tổng 100%

| ID | Trọng số | LO | Bằng chứng | Excellent | Meets | Partial | Not met |
| --- | ---: | --- | --- | --- | --- | --- | --- |
| RB-U06-01 — Đúng khái niệm, truy vết và evidence | 50% | LO6.1 | AT-U06-01; Sprint Goal; forecast basis/scope note | Goal outcome sắc nét; toàn bộ trace resolve; forecast cân evidence/uncertainty thuyết phục và phân tích trade-off/sensitivity | Goal/forecast đúng; đủ input, rationale, assumptions, core/negotiable và evidence | Goal hợp lý nhưng thiếu một link, basis, uncertainty hoặc boundary quan trọng | Goal là scope list/point target; forecast không truy vết, guarantee hoặc point-time conversion |
| RB-U06-02 — Xử lý thay đổi và tính nhất quán downstream | 50% | LO6.2 | AT-U06-02; Sprint Backlog; maintenance/absence impact | Mọi row actionable; happy/late path, dependency, evidence, response và trade-off nhất quán; artifact sẵn cho ASM-U08 | Plan đủ why/what/how/dependency/evidence/response; change request xử lý đúng, DoD giữ nguyên | Có plan nhưng thiếu trigger, evidence, forecast impact hoặc một downstream link | Plan chỉ có PBI/task assignment, hạ DoD, fixture giả Done hoặc mâu thuẫn Goal/baseline |

**Điểm đạt:** 70%. Tổng trọng số: **100%**.

## 📚 Nguồn và provenance

- **SRC-SG20:** Scrum Guide, November 2020, ScrumGuides.org, accessed 2026-08-25, CC BY-SA 4.0, adapt.
- **SRC-SPRINT-PLANNING:** Scrum.org Introduction to Sprint Planning, living snapshot/accessed 2026-08-25, website terms, reference.
- **SRC-FORECAST:** Scrum.org Forecasting and Release Planning, living snapshot/accessed 2026-08-25, website terms, reference.
- **SRC-PROJECT:** `starter/NovaShop_Project_Brief.md`, training artifact v1.0, accessed 2026-08-25, internal approved.
- Story Map/Product Backlog/Sizing record là artifact simulated trong chuỗi NovaShop; history, capacity và maintenance notice là assessment data synthetic.
- Không dùng nguồn bổ sung và không tuyên bố benchmark, deadline hay forecast thực tế.

---
<!-- QUALITY GATE: concept/LO → input → constraint → deliverable → AT/evidence → rubric resolve; A03 consumes A02 outputs and produces Sprint artifacts for A04; no walkthrough/reference solution. -->

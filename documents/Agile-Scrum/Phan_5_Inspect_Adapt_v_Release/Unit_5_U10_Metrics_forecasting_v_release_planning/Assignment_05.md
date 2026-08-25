# Assignment 05 — Release forecast và quyết định đầu tư tiếp theo

| Thuộc tính | Giá trị |
| --- | --- |
| Assessment ID | ASM-U10 |
| Milestone | M-U10 |
| Thời lượng | 90 phút |
| Mode | team, làm độc lập với hướng dẫn Lab |
| Bloom | analyze, create |
| Learning Outcomes | LO10.1, LO10.2 |
| Validation | artifact_review |
| Xác thực | simulated |

## 🎯 Learning Outcomes được đánh giá

- **LO10.1:** Metrics dashboard và raw-input trace chứng minh công thức, đơn vị, window và giới hạn diễn giải.
- **LO10.2:** Release forecast/roadmap chứng minh scenario, uncertainty, risk, guardrail và update trigger.

## 🧠 Khái niệm và best practices được đánh giá

| Concept/LO | Scenario/input | Constraint đã học | Deliverable | Oracle/evidence | Rubric |
| --- | --- | --- | --- | --- | --- |
| OUT-U10-01 / LO10.1 | Flow/value snapshot mới bên dưới | Metric có formula, unit, window, finish rule và limitation; không so velocity giữa team | Metrics dashboard | AT-U10-01, raw-input trace | RB-U10-01 |
| OUT-U10-02 / LO10.2 | Sponsor đòi ngày chắc chắn; payment risk open | Range/scenario, DoD guardrail, assumptions, risk và update trigger; forecast không phải guarantee | Release forecast, Improvement roadmap | AT-U10-02, impact analysis | RB-U10-02 |

Các constraint là contract đánh giá, không phải walkthrough. Học viên tự chọn cách tính/biểu diễn phù hợp và phải bảo vệ trade-off.

## Bối cảnh và change request

Sau Sprint Review, sponsor muốn cam kết ngày ra mắt để đặt chiến dịch quảng cáo. Product Backlog v3 còn **23 PBI** đã refined theo policy hiện tại. Historical throughput ba Sprint gần nhất là `5, 4, 6`; Sprint gần nhất có 1 item open age 6 ngày. Value snapshot synthetic: 1.200 visitors, 210 checkout starts, 147 successful orders và 11 đơn cần nhập lại. `RISK-PAY-02` có probability medium, impact mất 1–2 item capacity ở Sprint kế tiếp.

Team phải đưa ra một release decision có điều kiện. Không được giảm Definition of Done, xóa observation bất lợi hoặc chuyển forecast thành commitment.

## 🔗 Liên kết project xuyên suốt

- **Depends on:** ASM-U08.
- **Baseline artifacts tiêu thụ:** `Sprint Review record`, `Product Backlog v3`.
- **Produces:** `Metrics dashboard`, `Release forecast`, `Improvement roadmap`.
- **Terminal delivery:** cả ba artifact được CAP-01 tiêu thụ; acceptance refs AT-U10-01 và AT-U10-02.

Nếu baseline không có version/owner hoặc không truy vết được tới ASM-U08, ghi input defect và dừng publish; không tự tạo số thay thế.

## Input và starter assets

- Sprint Review record và Product Backlog v3 từ ASM-U08.
- Dataset/change snapshot trong đề bài; [project brief](../../starter/NovaShop_Project_Brief.md) chỉ cung cấp boundary/DoD.
- Measurement convention: elapsed cycle time; throughput chỉ đếm item đạt Done.
- Không có production endpoint, account, secret, dữ liệu khách hàng hoặc benchmark ngoài.

## 📋 Yêu cầu

### Functional requirements

- **FR-A05-01 / LO10.1:** Tạo dashboard tính ít nhất throughput history, work-item-age signal, checkout completion và re-entry share; mỗi metric có formula, unit, window, source và limitation.
- **FR-A05-02 / LO10.2:** Tạo optimistic/base/conservative forecast cho 23 PBI; mỗi scenario nêu assumption, risk, DoD/value guardrail và điều kiện vô hiệu.
- **FR-A05-03 / LO10.2:** Viết release decision cho sponsor và roadmap gồm owner, action, leading signal, guardrail, review trigger.

### Non-functional requirements

- **NFR-A05-01:** Không có PII, secret, payment data thật hoặc claim benchmark/conformance không có nguồn.
- **NFR-A05-02:** Reviewer có thể tái lập mọi con số từ input; rounding rule được nêu.
- **NFR-A05-03:** Không dùng `guaranteed`, `committed date` hoặc ngôn ngữ tương đương cho forecast; DoD không bị hạ.
- **NFR-A05-04:** Tất cả link baseline → decision → downstream deliverable resolve bằng ID/version.

### Ràng buộc và ngoài phạm vi

- Không được giả định thêm người/capacity hay invent history.
- Không bắt buộc Monte Carlo, code, tool trả phí hoặc một loại chart cụ thể.
- Không xây MVP, không thiết kế campaign và không giải quyết chi tiết payment integration.
- Học viên có thể chọn rule scenario nhưng phải giải thích và cho reviewer tái lập.

## Nhiệm vụ độc lập — TASK-U10-01

Tạo ba deliverable và một impact note xử lý yêu cầu “ngày chắc chắn”. Artifact phải chứng minh:

- **Best-practice rule 1:** quyết định thuộc OUT-U10-01 liên kết input, mục tiêu và evidence chấp nhận. **Rationale:** traceability ngăn metric/diễn giải cảm tính. Map AT-U10-01 → RB-U10-01.
- **Best-practice rule 2:** thay đổi thuộc OUT-U10-02 nêu trade-off và cập nhật artifact downstream. **Rationale:** forecast cục bộ thiếu roadmap/trigger làm project flow stale. Map AT-U10-02 → RB-U10-02.

Không có chuỗi bước giải, scenario throughput, phép tính mẫu hoặc reference answer trong Assignment này.

## 📦 Deliverables và cách nộp

1. **Metrics dashboard** — Markdown/PDF/spreadsheet export, có raw-input trace và measurement contract.
2. **Release forecast** — ba scenario, range/confidence/assumptions/risk/trigger và decision memo tối đa 250 từ.
3. **Improvement roadmap** — action, owner, leading signal, guardrail, review date và downstream link CAP-01.
4. **Evidence index** — map FR/NFR/LO → section → AT → rubric.

Tên file chứa `ASM-U10`, team ID giả lập và version. Nộp đủ khi bốn file mở được, cross-links resolve và không kèm reference solution/instructor note.

## ✅ Acceptance criteria và output mong đợi

### AT-U10-01 — Metrics và traceability (LO10.1)

**Given** snapshot được cung cấp, **when** reviewer tính lại dashboard theo measurement contract, **then** mọi result/rounding khớp input; source row/window/unit/limitation hiện rõ và interpretation không vượt evidence.

**Expected:** reviewer xác định được input, quyết định, lý do và evidence mà không suy đoán. Sai một công thức hoặc dùng metric để xếp hạng team là FAIL.

### AT-U10-02 — Forecast/change impact (LO10.2)

**Given** scope 23 PBI, history và open payment risk, **when** reviewer thay đổi một assumption trong scenario, **then** forecast/decision/roadmap phản ánh tác động nhất quán; DoD giữ nguyên, range không bị gọi là guarantee và có trigger cập nhật.

**Expected:** change request được xử lý mà không phá baseline; trade-off, acceptance evidence và downstream CAP-01 link nhất quán. Thiếu risk/trigger hoặc hạ DoD là FAIL.

## 🧪 Cách xác minh

Reviewer không chấm thẩm mỹ. Họ:

- recalculate metric và ít nhất một scenario từ raw input;
- đối chiếu evidence index với FR/NFR/LO;
- search ngôn ngữ certainty/unsupported claim;
- kiểm baseline artifact names đúng output ASM-U08 và terminal artifacts đúng CAP-01;
- ghi `PASS|REVISE|FAIL`, exact evidence và finding owner.

## 📊 Rubric chấm điểm — tổng 100%

| ID | Tiêu chí | Trọng số | LO | Evidence | Excellent | Meets | Partial | Not met |
| --- | --- | ---: | --- | --- | --- | --- | --- | --- |
| RB-U10-01 | Đúng khái niệm, truy vết và evidence | 50% | LO10.1 | AT-U10-01, measurement contract, raw-input trace | Tất cả metric đúng; interpretation/trade-off/limitation sắc nét và tái lập độc lập | Metric cốt lõi đúng, đủ input–rationale–evidence | Quyết định hợp lý nhưng thiếu một link/limitation | Sai metric hoặc không truy vết được |
| RB-U10-02 | Xử lý thay đổi và nhất quán downstream | 50% | LO10.2 | AT-U10-02, scenario sensitivity, roadmap/CAP link | Happy/edge/risk đều nhất quán; range, guardrail và trigger rõ | Forecast/change xử lý đúng; artifacts downstream nhất quán | Có forecast nhưng thiếu trade-off, risk hoặc trigger | Guarantee, hạ DoD hoặc phá baseline |

**Điểm đạt:** 70%. Một violation PII/secret, formula trọng yếu sai, hoặc gọi work chưa đạt DoD là release evidence sẽ khiến artifact FAIL bất kể tổng điểm.

## Provenance

- [The Scrum Guide, November 2020](https://scrumguides.org/scrum-guide.html), CC BY-SA 4.0.
- [Evidence-Based Management Guide, May 2024](https://www.scrum.org/resources/online-evidence-based-management-guide), CC BY-SA 4.0.
- [Introduction to Forecasting and Release Planning](https://www.scrum.org/resources/introduction-forecasting-and-release-planning), reference-only, accessed 2026-08-25.
- [Kanban Guide for Scrum Teams](https://www.scrum.org/resources/kanban-guide-scrum-teams), complementary practice.
- `[SUY DIỄN — từ kiến thức đã huấn luyện]` Scope, history, risk và value snapshot của Assignment là dữ liệu synthetic dành cho đánh giá.

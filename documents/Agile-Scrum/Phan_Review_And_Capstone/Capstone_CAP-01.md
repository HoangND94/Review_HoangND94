# Capstone CAP-01 — NovaShop Agile Delivery Pack và change challenge

| Thuộc tính | Giá trị |
| --- | --- |
| Thời lượng | 120 phút |
| Hình thức | Team delivery + 10 phút demo/phản biện |
| Learning Outcomes | LO1.1–LO10.2 |
| Điểm đạt | 70/100 |
| Xác thực | simulated |
| Validation | demo + artifact_review |

## 🎯 Learning Outcomes được đánh giá

- **LO1.1–LO2.2:** chọn cách làm/giả thuyết, Scrum framework và operating model.
- **LO3.1–LO4.2:** Product Goal/stakeholder evidence, journey/story map, backlog và vertical slices.
- **LO5.1–LO6.2:** sizing/ordering, Sprint Goal, capacity forecast và Sprint Backlog.
- **LO7.1–LO9.2:** Daily/flow adaptation, DoD/Review feedback và Retrospective experiment.
- **LO10.1–LO10.2:** metrics dashboard, scenario forecast và release decision.

Mapping chi tiết LO → requirement → deliverable → oracle → rubric nằm trong các bảng bên dưới; mọi LO phải có named evidence trong pack.

## Nhiệm vụ tổng hợp

Bạn là Scrum Team chịu trách nhiệm bàn giao evidence cho sponsor NovaShop. Hãy tích hợp các artifact đã tạo từ ASM-U02 đến ASM-U10 và Lab milestones thành **NovaShop Agile Delivery Pack**, sau đó xử lý change card cuối:

> Marketing muốn giữ release window sớm. Đồng thời shipping sandbox thay đổi cách tính phí, payment risk vẫn mở và evidence keyboard navigation của checkout chưa đạt. Sponsor hỏi có thể gọi checkout là Done, thêm fee change vào Sprint hiện tại và cam kết ngày release hay không.

Nhóm phải inspect evidence, đưa ra adaptation và bảo vệ quyết định. Đề không có một đáp án duy nhất; phương án chỉ đạt khi đúng Scrum contract, giữ quality guardrails, truy vết value và làm uncertainty minh bạch.

**Provenance:** toàn bộ bối cảnh, số liệu và integrations là simulated/sandbox; không phải dự án khách hàng thật.

## Baseline được phép tái sử dụng

- `Team Charter`, `Working Agreement` từ ASM-U02.
- `Story Map`, `Product Backlog v1` từ ASM-U04.
- `Sprint Goal`, `Sprint Backlog` từ ASM-U06.
- `Increment evidence pack`, `Sprint Review record`, `Product Backlog v3` từ ASM-U08.
- `Metrics dashboard`, `Release forecast`, `Improvement roadmap` từ ASM-U10.
- Problem/value hypotheses, Product Goal/stakeholder evidence, refinement record, Daily/flow evidence, retrospective experiment từ Labs/Units.
- [Project brief](../starter/NovaShop_Project_Brief.md), [synthetic dataset](../starter/NovaShop_Synthetic_Data.csv) và [artifact field contracts](../starter/Artifact_Templates.md).

Không được dùng solution/instructor asset, production endpoint, tiền thật, PII hoặc credential. Nếu một baseline thiếu version/evidence, ghi defect và xử lý nó trong pack thay vì bịa dữ liệu.

## 📋 Phạm vi và yêu cầu

System boundary vẫn là storefront, account/address, cart/promotion, checkout, payment/shipping sandbox, order tracking, admin cơ bản và analytics events. Không yêu cầu code, mobile native, marketplace, ERP, AI recommendation, production deployment hay full WCAG/ASVS certification. Nhóm tự chọn format/visualization và decision technique, nhưng phải giải trình trade-off và giữ exact artifact IDs.

## Functional requirements

| ID | Requirement quan sát được | LO trọng tâm | Evidence/Deliverable |
| --- | --- | --- | --- |
| CAP-FR-01 | Phân loại cách làm/giả thuyết và cho thấy evidence đã thay đổi quyết định | LO1.1, LO1.2 | Decision/hypothesis register |
| CAP-FR-02 | Operating model map đúng accountabilities/events/artifacts/commitments và working rules kiểm được | LO2.1, LO2.2 | Team operating evidence |
| CAP-FR-03 | Product Goal/stakeholder evidence truy vết qua journey, story map và backlog | LO3.1–LO4.2 | Goal-to-backlog trace |
| CAP-FR-04 | Sizing/ordering và Sprint forecast nêu assumption, capacity, DoD, dependency/risk | LO5.1–LO6.2 | Refinement + Sprint Planning evidence |
| CAP-FR-05 | Có ít nhất hai inspect-and-adapt loops: Daily/flow và Review/Retrospective | LO7.1–LO9.2 | Event records, impediment/feedback/experiment |
| CAP-FR-06 | Checkout được phân loại Done/Not Done từ acceptance/DoD evidence, không từ áp lực demo | LO8.1 | Quality-gate decision |
| CAP-FR-07 | Final change card cập nhật đúng artifact downstream mà không phá Product/Sprint Goal | LO5.2, LO6.1, LO7.2, LO8.2 | Change impact note + diffs |
| CAP-FR-08 | Metric/forecast/release decision đúng formula và nêu uncertainty/risk/update trigger | LO10.1, LO10.2 | Dashboard, forecast, roadmap |

## Non-functional requirements

- **CAP-NFR-01 — Traceability:** mỗi claim nối source/input → decision → LO/requirement → artifact → oracle → downstream consumer; orphan link = FAIL.
- **CAP-NFR-02 — Evidence integrity:** reviewer tái lập được metric và ít nhất ba quyết định; tự khai “đã kiểm” không phải evidence.
- **CAP-NFR-03 — Quality language:** không gọi work chưa đạt DoD là Increment; không tuyên bố full WCAG/ASVS conformance hay forecast guarantee.
- **CAP-NFR-04 — Data safety:** không PII, secret, payment data thật hoặc endpoint production.
- **CAP-NFR-05 — Reproducibility:** pack mở được từ workspace sạch, internal links resolve, version/source/owner rõ.
- **CAP-NFR-06 — Scope/time:** deliverable dùng professional artifacts; không thêm coding requirement hay công nghệ chưa học.

## 🗓️ Milestones và project increments

| Milestone | Artifact bắt buộc | Dependency | Checkpoint oracle |
| --- | --- | --- | --- |
| M-U01 | Decision canvas, value hypotheses | Project brief | Assumption/evidence/threshold/adaptation đủ |
| M-U02 | Team Charter, Working Agreement | M-U01 | Scrum map đúng, rule quan sát được |
| M-U03 | Product Goal, stakeholder/journey | M-U01–02 | Outcome/metric/boundary/evidence rõ |
| M-U04 | Story Map, Backlog v1 | M-U03, ASM-U02 | Vertical slice và acceptance evidence |
| M-U05 | Sizing record, Backlog v2 | M-U04 | Uncertainty + value/risk/dependency ordering |
| M-U06 | Sprint Goal, Sprint Backlog | M-U05, ASM-U04 | Why/what/how, capacity, DoD/risk nhất quán |
| M-U07 | Daily/flow/impediment record | M-U06 | Adaptation hướng Sprint Goal, không giảm quality |
| M-U08 | Evidence pack, Review, Backlog v3 | M-U07, ASM-U06 | Done/Not Done + feedback disposition |
| M-U09 | Causal map, experiment, agreement v2 | M-U08 | Cause khác symptom; signal/guardrail/review date |
| M-U10 | Dashboard, forecast, roadmap | M-U09, ASM-U08 | Formula/range/risk/trigger tái lập được |

Nhóm nêu checkpoint status `PASS|REVISE|FAIL`, exact evidence và owner. Mọi `REVISE/FAIL` ảnh hưởng final decision phải được xử lý hoặc công khai như release blocker.

## Final change impact challenge

Tạo một change impact note trả lời mà không cung cấp implementation:

1. Những facts, assumptions và pressures nào đang bị trộn?
2. Checkout có đạt DoD không? Evidence/requirement nào quyết định?
3. Fee change tác động Product Backlog, Sprint Goal/Sprint Backlog, dependency/risk và forecast thế nào?
4. Scope/time/quality trade-off nào được chọn; ai accountable/quyết định?
5. Artifact versions nào thay đổi; downstream link nào phải cập nhật?
6. Khi nào inspect lại; signal/guardrail nào dẫn tới continue/adjust/stop?

Không có điểm cho việc chọn “release” hay “không release” tự thân; điểm nằm ở contract, evidence, trade-off và traceability.

## Deliverables

1. **NovaShop Agile Delivery Pack** — mục lục versioned, các artifact milestone và decision index.
2. **Traceability matrix** — ít nhất các cột LO/requirement, input/source, decision, artifact/version, acceptance oracle, rubric, downstream consumer.
3. **Final change impact note** — tối đa 3 trang, có artifact diff index và release blocker/decision.
4. **Demo and defense record** — agenda 10 phút, evidence pointers, reviewer questions/answers và score sheet.

Pack không được chứa reference solution của Assignment, dữ liệu thật hay unsupported claim.

## ✅ Acceptance criteria và Definition of Done

- Tất cả outputs ASM-U02→ASM-U10 được tiêu thụ; không có Assignment trung gian chỉ được đính kèm mà không ảnh hưởng decision downstream.
- CAP-FR-01…08 và CAP-NFR-01…06 mỗi mục có exact evidence, owner và status.
- Final change phản ánh nhất quán trong backlog, Sprint plan/evidence, risk, forecast và roadmap; diff có before/after/reason.
- Mỗi LO1.1→LO10.2 có ít nhất một named evidence và một rubric criterion.
- Definition of Done, phần chưa Done, release limitations và open risks hiển thị rõ.
- Reviewer từ môi trường sạch mở pack, theo link và tái lập được ba quyết định cùng metrics/forecast sample.
- Không còn PII/secret, broken link, unsupported conformance/benchmark hoặc guarantee.

## Validation và demo oracle

### Artifact review

- Recalculate một flow metric, một value metric và một scenario forecast.
- Trace ba mẫu: Product Goal→PBI→Sprint Goal; PBI→acceptance→DoD; Review feedback→Backlog v3→forecast.
- Inspect change diff và xác nhận mọi affected downstream artifact được version/update.
- Search unsafe data và certainty/conformance language.

### Demo 10 phút

1. 2 phút: Product Goal/value và project spine.
2. 3 phút: hai inspect-and-adapt loops với before/after evidence.
3. 3 phút: final change, DoD/release/forecast decision.
4. 2 phút: limitations, risks, next experiment và handoff.

Reviewer hỏi “evidence nào?”, “assumption nào?”, “điều gì làm bạn đổi quyết định?”. Trả lời phải trỏ artifact/ID; diễn giải không có evidence được ghi finding.

## 📊 Rubric — tổng 100%

| ID | Tiêu chí | Trọng số | LO | Evidence | Excellent | Meets | Partial | Not met |
| --- | --- | ---: | --- | --- | --- | --- | --- | --- |
| CAP-RB-01 | Giá trị sản phẩm và traceability | 25% | LO1.2, LO3.1, LO3.2, LO4.1, LO4.2 | Goal-to-backlog-to-metric trace | Không orphan; trade-off/evidence độc lập rõ | Chuỗi cốt lõi đầy đủ | Thiếu một số link/evidence | Không truy vết được value |
| CAP-RB-02 | Vận dụng Scrum đúng framework | 25% | LO2.1, LO2.2, LO6.1, LO7.1, LO8.2, LO9.2 | Operating model và inspect/adapt records | Đúng framework, giải thích trade-off/anti-pattern | Accountabilities/events/artifacts đúng | Lệch nhỏ làm giảm transparency | Bỏ/biến dạng thành phần cốt lõi |
| CAP-RB-03 | Chất lượng Increment và evidence | 25% | LO5.1, LO5.2, LO6.2, LO7.2, LO8.1 | DoD, quality gate, flow/risk evidence | Happy/edge evidence và reproduction đầy đủ | DoD/evidence đủ để quyết định | Decision hợp lý nhưng evidence thiếu | Gọi work chưa Done là Increment |
| CAP-RB-04 | Metrics, adaptation và forecast | 15% | LO1.1, LO9.1, LO10.1, LO10.2 | Dashboard, causal analysis, experiment, scenarios | Formula/interpretation đúng; uncertainty/triggers rõ | Metric/forecast đúng contract | Tính đúng nhưng diễn giải quá mức | Sai formula hoặc guarantee |
| CAP-RB-05 | Demo và phản biện | 10% | LO1.1, LO2.2, LO3.1, LO4.2, LO5.2, LO6.1, LO7.2, LO8.2, LO9.2, LO10.2 | Demo record và evidence pointers | Trả lời bằng evidence, thừa nhận giới hạn | Bảo vệ quyết định chính | Một số trả lời thiếu evidence | Không chứng minh được quyết định |

**Điểm đạt:** 70%. CAP-NFR-04 violation, falsified evidence hoặc unsupported “Done/conformant/guaranteed” claim là blocker và phải sửa trước bàn giao.

## Provenance

- [The Scrum Guide, November 2020](https://scrumguides.org/scrum-guide.html), CC BY-SA 4.0.
- [Evidence-Based Management Guide, May 2024](https://www.scrum.org/resources/online-evidence-based-management-guide), CC BY-SA 4.0.
- [Introduction to Forecasting and Release Planning](https://www.scrum.org/resources/introduction-forecasting-and-release-planning), accessed 2026-08-25.
- [NovaShop project brief](../starter/NovaShop_Project_Brief.md), internal approved.
- `[SUY DIỄN — từ kiến thức đã huấn luyện]` Final change card, timebox, số liệu và integrations là thiết kế sư phạm synthetic.

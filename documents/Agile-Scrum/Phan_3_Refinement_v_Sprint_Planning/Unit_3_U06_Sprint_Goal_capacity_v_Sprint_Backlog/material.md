# Unit U06: Sprint Goal, capacity và Sprint Backlog — Học liệu cốt lõi

> **Khóa học:** Agile–Scrum thực hành qua dự án thương mại điện tử NovaShop · **Thuộc:** Refinement và Sprint Planning · **Xác thực:** simulated

## 🎯 Learning Outcomes

- **LO6.1** [create] — Viết Sprint Goal liên kết Product Goal và chọn scope phù hợp với capacity, lịch sử cùng Definition of Done. Bằng chứng: Sprint Goal và forecast có assumptions.
- **LO6.2** [create] — Tạo Sprint Backlog gồm why, what, how, dependency, acceptance evidence và risk response. Bằng chứng: Sprint Backlog có kế hoạch thích nghi được.

## 🧭 Ngữ cảnh và increment M-U06

Baseline là Story Map/Product Backlog v1 từ ASM-U04 và Product Backlog v2/Sizing record từ U05. Scrum Team tạo Sprint Goal, Developers forecast những PBI có thể hoàn thành, rồi tạo Sprint Backlog có plan đủ để bắt đầu và thích nghi. Output **Sprint Goal** và **Sprint Backlog** được ASM-U08 dùng để kiểm Increment/Review; REV-01 kiểm chuỗi Product Goal → backlog → Sprint Goal.

Capacity và lịch sử là evidence hỗ trợ forecast, không phải artifact/commitment chính thức của Scrum và không tạo guarantee. Definition of Done không được giảm để làm số forecast đẹp.

## 📚 Nguồn đầu vào đã map

- **SRC-SG20** — [The Scrum Guide 2020](https://scrumguides.org/scrum-guide.html), Ken Schwaber và Jeff Sutherland, CC BY-SA 4.0, adapt.
- **SRC-SPRINT-PLANNING** — [Introduction to Sprint Planning](https://www.scrum.org/resources/introduction-sprint-planning), Scrum.org, snapshot 2026-08-25, reference-only.
- **SRC-FORECAST** — [Introduction to Forecasting and Release Planning](https://www.scrum.org/resources/introduction-forecasting-and-release-planning), Scrum.org, snapshot 2026-08-25, reference-only.
- **SRC-PROJECT** — `starter/NovaShop_Project_Brief.md`, training artifact v1.0, internal approved.

## 1. Prerequisite, environment và preflight

Hoàn thành U05; có Product Goal, ordered Product Backlog v2, Sizing record với uncertainty, capacity calendar và DoD baseline. ENV-PRO-ARTIFACT dùng Markdown/CSV/whiteboard, không có runtime/service/credential.

**Preflight PASS:** Product Backlog v2 có order/rationale; PBI candidate có acceptance evidence/size uncertainty; capacity calendar phân biệt available/unavailable; DoD mở được; template có “Sprint Planning record”. **Validation:** artifact review. **Mode:** professional_artifact vì LO yêu cầu planning decision/artifact, không yêu cầu code.

## 2. Mental map

```text
Product Goal (direction)
      ↓ WHY của Sprint
Sprint Goal (một objective, tạo coherence/flexibility)
      ↓ WHAT có thể forecast từ ordered backlog + lịch sử + upcoming capacity + DoD
Selected PBIs
      ↓ HOW do Developers tạo và thích nghi
Actionable plan + dependency + evidence + risk response
      = Sprint Backlog (why + what + how)
```

Ba chủ đề why/what/how liên kết chứ không phải ba pha handoff. Sprint Planning là hoạt động cộng tác của cả Scrum Team; Developers sở hữu forecast và plan, Product Owner làm rõ value/order, Scrum Master giúp hiểu đúng Scrum khi cần.

## 3. Nội dung lý thuyết cốt lõi

**📋 Checklist bắt buộc phủ — giữ nguyên văn và đúng thứ tự Content Outlines:**

- [x] Sprint Goal và forecast dựa trên Product Goal, capacity, lịch sử, DoD
- [x] Sprint Backlog: why, what, how, dependency và risk response

#### OUT-U06-01 — Sprint Goal và forecast dựa trên Product Goal, capacity, lịch sử, DoD

**Mapping:** OUT-U06-01 · LO6.1 · M-U06, tạo Sprint Goal và forecast có assumptions.

##### Định nghĩa và ranh giới

Sprint Goal là objective duy nhất của Sprint và commitment của Sprint Backlog. Nó giải thích vì sao Sprint có giá trị, tạo coherence và cho Developers flexibility về exact work cần làm để đạt Goal. Sprint Goal hỗ trợ Product Goal nhưng không chỉ lặp Product Goal hoặc liệt kê PBI.

Forecast là dự báo của Developers về những gì có thể Done trong Sprint, được tạo qua thảo luận với Product Owner và dựa trên ordered backlog, past performance, upcoming capacity cùng Definition of Done. **Capacity** là availability/constraint thực tế (ngày nghỉ, support duty, kỹ năng cần thiết); nó không phải phép chia point cho person-day. Forecast không phải guarantee hoặc cam kết scope cố định.

##### Vấn đề, vai trò và quyết định

Nếu chỉ kéo một số PBI, Sprint trở thành collection of tasks; nếu Goal quá rộng, đội không biết trade scope thế nào khi có sự cố. Scrum Team quyết định objective đáng đạt; Developers quyết định amount/work forecast và plan; Product Owner làm rõ trade-off value. Các quyết định phải nêu Goal link, outcome, capacity/history evidence, assumptions, uncertainty, DoD impact và boundary cho scope adaptation.

##### Cơ chế và mental model

1. Bắt đầu từ Product Goal và ordered PBI, tìm một outcome chung.
2. Viết Sprint Goal theo **actor/business outcome + condition/boundary**, không dùng “hoàn thành X/Y”.
3. Kiểm capacity calendar và skill bottleneck; xem lịch sử của chính đội trong context tương tự.
4. Chọn candidate PBI theo order, Goal contribution, dependency/risk và khả năng đạt DoD.
5. Ghi forecast basis, assumptions, range/uncertainty và scope boundary: item nào core cho Goal, item nào negotiable.
6. Nếu evidence thay đổi trong Sprint, Developers và Product Owner thương lượng scope mà không làm nguy hiểm Sprint Goal; chất lượng không giảm.

##### Khi dùng, khi không dùng và trade-off

Mỗi Sprint cần Sprint Goal. Dữ liệu lịch sử có ích khi Definition of Done, đội và work context đủ tương đồng; không dùng mechanical average khi context đổi mạnh hoặc sample nhỏ mà không ghi giới hạn. Capacity calendar hữu ích để thấy absence/skill constraint, nhưng chi tiết task-hour quá sớm tạo false precision. Goal tập trung cao làm trade-off dễ hơn nhưng có thể loại một số urgent work; nếu nhiều objective không liên quan, Scrum Team cần xem lại Product Goal/order hoặc phạm vi Sprint.

##### Ví dụ thực tế riêng và oracle

- **Context:** Product Goal nhấn mạnh đơn hợp lệ đi đến đóng gói không nhập lại.
- **Input:** candidate address validation, payment outcome, email confirmation; lịch sử 16/18/17 size units; upcoming capacity giảm; DoD không đổi.
- **Decision:** Sprint Goal “Kiểm chứng rằng người mua có thể gửi một đơn sandbox với dữ liệu giao hàng hợp lệ và nhận kết quả không mất input khi payment từ chối.” Core scope gồm address/payment; email negotiable.
- **Artifact:** Sprint Goal card + forecast assumptions.
- **Expected:** Goal vẫn có nghĩa nếu email bị bỏ; selected core đủ tạo outcome; không hứa ngày hoặc guarantee.
- **Oracle:** thay email availability thành unavailable; nếu Goal vẫn đạt với on-screen outcome và DoD, boundary hợp lý. Nếu bỏ address hoặc payment làm Goal không thể đạt, đó là core.

##### Best practices

- **Rule:** Goal mô tả outcome, không liệt kê output. **Rationale:** outcome cho phép đổi exact work. **Positive:** “người mua hoàn tất một đơn hợp lệ…”. **Negative:** “xong PB-1,2,3”; khi một PBI đổi, đội không biết điều gì cần bảo vệ.
- **Rule:** forecast ghi assumptions/history/capacity/DoD và giới hạn. **Rationale:** transparency giúp inspect forecast. **Positive:** “lịch sử 16–18, capacity giảm, core 13, DoD unchanged”. **Negative:** “cam kết 18 points”; false certainty.
- **Rule:** không giảm DoD để vừa scope. **Rationale:** work chưa đạt DoD không phải Increment usable. **Positive:** bỏ negotiable item. **Negative:** bỏ accessibility/security evidence để “hoàn thành”; quality debt bị che.

##### Anti-pattern, failure và troubleshooting

- **Dấu hiệu:** Goal là danh sách PBI. **Nguyên nhân:** nhầm objective với scope. **Chẩn đoán:** bỏ một PBI làm câu Goal vô nghĩa về cú pháp. **Sửa:** viết actor/outcome/boundary. **Phòng tránh:** test Goal bằng một change scenario.
- **Dấu hiệu:** capacity được quy thành point/ngày cố định. **Nguyên nhân:** trộn sizing với duration. **Chẩn đoán:** conversion table không xét work/uncertainty. **Sửa:** dùng lịch sử như range và capacity như context. **Phòng tránh:** ghi assumptions thay vì hệ số.
- **Dấu hiệu:** forecast lớn hơn dù capacity/DoD xấu hơn mà không rationale. **Nguyên nhân:** pressure/optimism. **Chẩn đoán:** không có evidence delta. **Sửa:** review core/negotiable và risk. **Phòng tránh:** peer challenge forecast basis.

#### OUT-U06-02 — Sprint Backlog: why, what, how, dependency và risk response

**Mapping:** OUT-U06-02 · LO6.2 · M-U06, tạo Sprint Backlog có plan thích nghi và acceptance evidence.

##### Định nghĩa và ranh giới

Sprint Backlog gồm Sprint Goal (**why**), các Product Backlog items được chọn (**what**) và actionable plan để tạo Increment (**how**). Nó là plan bởi và dành cho Developers, là bức tranh real-time, đủ chi tiết để inspect progress tại Daily Scrum và được cập nhật trong Sprint. Nó không phải task contract bất biến, bảng giao việc từ manager hoặc chỉ bản sao PBI list.

Dependency/risk fields là thực hành làm plan minh bạch, không phải trường bắt buộc do Scrum Guide quy định. Acceptance evidence nối what/how với DoD để đội biết trạng thái nào đáng gọi Done.

##### Vấn đề, vai trò và quyết định

Selected PBI chưa đủ để bắt đầu: đội cần biết plan, điểm phối hợp, evidence và phản ứng khi assumption sai. Developers quyết định how, task decomposition và adaptation; Product Owner có thể làm rõ scope/value nhưng không phân công task. Quyết định cần ghi: work nào phục vụ Goal, dependency nào external/internal, evidence nào chứng minh Done, risk response nào bảo vệ Goal, boundary nào cho phép đổi scope.

##### Cơ chế và mental model

Mỗi row Sprint Backlog nên nối: `Sprint Goal contribution → PBI outcome/criteria → plan increment → dependency condition/owner → evidence/DoD → risk signal → response/adaptation`. Daily inspection cập nhật remaining plan và risk, không thay lịch sử. Nếu một dependency fail, đội chọn workaround, reorder how hoặc thương lượng selected scope; Sprint Goal chỉ bị thay/huỷ khi các điều kiện Scrum tương ứng xảy ra, không tùy tiện đổi để báo xanh.

##### Khi dùng, khi không dùng và trade-off

Sprint Backlog luôn cần nhưng format tùy đội. Dùng dependency/risk detail khi nó ảnh hưởng sequencing/Goal; không biến plan thành Gantt cấp giờ hoặc checklist hàng trăm task không ai inspect. Plan quá thô gây surprise, quá chi tiết sớm gây maintenance waste. “Đủ actionable” nghĩa Developers biết bước tiếp theo, evidence và điểm cần inspect, không có nghĩa biết mọi task từ ngày đầu.

##### Ví dụ thực tế riêng và oracle

- **Context:** payment sandbox chỉ mở từ ngày 3.
- **Input:** PBI payment approved/declined; Goal cần order outcome; address work không phụ thuộc sandbox.
- **Decision:** plan ngày đầu làm rõ contract/fixture và address evidence; external dependency owner kiểm availability; trigger cuối ngày 2; response dùng approved/declined fixture để tiếp tục evidence, nhưng integration evidence vẫn bắt buộc trước Done.
- **Artifact:** Sprint Backlog row có why/what/how/dependency/evidence/risk.
- **Expected:** đội không idle, không gọi fixture-only work Done nếu integration evidence thuộc DoD, Goal boundary vẫn rõ.
- **Oracle:** sandbox không mở ngày 3; row chuyển risk status, response/owner được kích hoạt và forecast impact minh bạch.

##### Best practices

- **Rule:** mọi selected PBI nối trực tiếp Sprint Goal và evidence. **Rationale:** chống “miscellaneous scope”. **Positive:** contribution/evidence rõ. **Negative:** urgent item không Goal link; Daily Scrum không biết trade-off.
- **Rule:** dependency ghi condition, owner, due/trigger và fallback giới hạn. **Rationale:** tên dependency không tạo hành động. **Positive:** “sandbox available by D3; owner; check; fixture not enough for Done”. **Negative:** “blocked by payment”; không có next decision.
- **Rule:** adaptation boundary nêu core/negotiable và quality guardrail. **Rationale:** đổi scope nhanh mà không phá Goal/DoD. **Positive:** email negotiable, payment evidence core. **Negative:** bỏ test để giữ hết PBI.

##### Anti-pattern, failure và troubleshooting

- **Dấu hiệu:** Sprint Backlog chỉ có PBI title. **Nguyên nhân:** what không có how/evidence. **Chẩn đoán:** Developers không nêu được next action/dependency. **Sửa:** thêm actionable plan và oracle. **Phòng tránh:** planning review why/what/how.
- **Dấu hiệu:** mỗi task gắn cứng một người từ đầu. **Nguyên nhân:** manager dispatch. **Chẩn đoán:** không thể swarm/adapt. **Sửa:** Developers tự tổ chức theo Goal và skills. **Phòng tránh:** task ownership có thể đổi, outcome ownership là của đội.
- **Dấu hiệu:** risk response biến thành hạ DoD. **Nguyên nhân:** forecast pressure. **Chẩn đoán:** evidence bắt buộc bị xóa. **Sửa:** giảm/đổi scope, giữ guardrail. **Phòng tránh:** DoD field trên mỗi row.

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### Sprint Planning canvas khi capacity giảm

**Stable ID:** MEX-U06-01 · **Artifact:** Sprint Planning canvas và Sprint Backlog · **Mapping:** LO6.1, LO6.2; OUT-U06-01, OUT-U06-02.

**Verification method từ plan:** đối chiếu từng trường của artifact với checklist, input source và oracle được nêu trong Material.

### Mapping Material worked example → Hands-on Lab tương ứng

- **MEX-U06-01 → LAB-U06-01/CP-U06-01:** recreate Goal/forecast/plan bằng backlog và capacity mới; LO6.1, LO6.2.
- **MEX-U06-01 → LAB-U06-01/CP-U06-02:** modify plan dưới payment-maintenance constraint; LO6.1, LO6.2.

**Input/baseline:** Product Goal `PG-NS-01`; ordered backlog: `PB-601 Address quality=5`, `PB-602 Payment + on-screen order outcome=8`, `PB-603 Email confirmation=3`, `PB-604 Promotion=5`. Ba Sprint tương đồng Done 16/18/17 relative units. Upcoming calendar giảm khoảng 20% availability do support duty; payment specialist vẫn có mặt. DoD giữ nguyên; email sandbox risk mở.

#### Artifact A — Why/What forecast canvas

- **Sprint Goal:** “Kiểm chứng rằng người mua có thể gửi một đơn sandbox với địa chỉ hợp lệ và nhận kết quả chấp nhận/từ chối mà không mất dữ liệu cần sửa.”
- **Product Goal link:** giảm nhập lại, tăng đơn online hợp lệ; đây là target simulated.
- **Forecast core:** PB-601 (5) + PB-602 (8) = 13 relative units.
- **Negotiable:** PB-603 (3) chỉ kéo khi core evidence đi đúng hướng; PB-604 không thuộc Goal Sprint này.
- **Basis:** lịch sử 16–18 chỉ là range; capacity giảm nên chọn core 13; same team/reference/DoD; payment skill available.
- **Assumptions/uncertainty:** address catalog stable; sandbox approved/declined available; email optional; no retry/refund.
- **Adaptation boundary:** có thể bỏ PB-603 hoặc re-plan how; không bỏ address/payment evidence và không giảm DoD.

#### Artifact B — Sprint Backlog

| Why/Goal contribution | What | How — actionable plan | Dependency/owner/trigger | Acceptance evidence + DoD | Risk response/boundary |
| --- | --- | --- | --- | --- | --- |
| Dữ liệu giao hàng hợp lệ, giảm nhập lại | PB-601 | Reconfirm criteria; prepare valid/invalid synthetic address fixtures; create validation/evidence tasks | Address list owner; inspect end D1 | Happy + invalid-address result; retained input; review evidence; no PII | Nếu catalog inconsistent, freeze allowed fixture scope và log limitation; PB-601 vẫn core |
| Nhận payment outcome không mất input | PB-602 | Confirm approved/declined contract; sequence fixture check then sandbox evidence; capture order/no-order state | Payment owner; sandbox check D2; PB-601 for valid address | Approved creates one sandbox order; declined creates none and retains input; DoD evidence complete | Fixture supports work but cannot replace integration evidence required by DoD; escalate/reforecast if sandbox absent D3 |
| Tăng clarity sau order, không bắt buộc Goal | PB-603 | Prepare on-screen message; email task only after core checks | Email sandbox; inspect D4 | On-screen result required; email evidence only if selected | Drop PB-603 first when core at risk; Goal/DoD unchanged |

**Giải thích:** 13 không được tính bằng 20% nhân story point; đó là forecast judgment kết hợp historical range, availability, skill, order, risk và DoD. Sprint Goal không liệt kê PBI nên vẫn hướng dẫn adaptation. Sprint Backlog cho thấy why/what/how, dependency, evidence và risk response.

**Happy behavior:** core evidence đạt, đội có thể kéo negotiable PB-603 nếu vẫn bảo vệ Goal/DoD. **Edge/failure:** sandbox trễ qua trigger; plan kích hoạt escalation/reforecast và không gọi fixture-only work Done.

**Verification — PASS khi:**

1. Sprint Goal là một outcome, link Product Goal và không phải PBI list.
2. Forecast có history, capacity, DoD, assumptions/uncertainty; không guarantee/conversion.
3. Core/negotiable boundary rõ; selected work có Goal contribution.
4. Mỗi row Sprint Backlog có why, what, how, dependency/owner/trigger, evidence/DoD và response.
5. Edge sandbox failure không làm giảm DoD; forecast impact minh bạch.

Expected result: **Goal hướng outcome; forecast có assumptions; plan cho thấy why/what/how và adaptation boundaries.** Reviewer ghi PASS/REVISE cùng check/row bị ảnh hưởng.

**Material ↔ Lab:** [CP-U06-01](HandsOnLab_06.md#checkpoint-1--cp-u06-01-tạo-goalforecast-với-capacity-giảm-30) dùng backlog/order-status và capacity -30%; [CP-U06-02](HandsOnLab_06.md#checkpoint-2--cp-u06-02-thích-nghi-khi-payment-sandbox-bảo-trì) thêm maintenance day 2. Cả hai tham chiếu MEX-U06-01.

## 5. Lỗi thường gặp

| Dấu hiệu | Nguyên nhân | Chẩn đoán | Sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| Goal = PBI list | Scope thay objective | Không có actor/outcome | Viết lại why/boundary | Change-test Sprint Goal |
| Forecast = guarantee | Áp lực deadline | Không assumption/range | Ghi basis/uncertainty | Dùng ngôn ngữ forecast |
| Capacity = point/day | Trộn size/time | Conversion table | Dùng history + context | Tách capacity worksheet |
| Backlog chỉ có what | Planning dừng sớm | Không next action/evidence | Thêm how/dependency/oracle | Review why/what/how |
| Risk response hạ DoD | Cứu scope | Evidence bị bỏ | Giảm negotiable scope | Guardrail trên plan |

## 6. Thuật ngữ và mental model

- **Sprint Goal:** objective duy nhất và commitment của Sprint Backlog.
- **Forecast:** dự báo Developers về work có thể Done, không phải guarantee.
- **Capacity:** availability/skill constraint sắp tới, không phải point conversion.
- **Past performance:** evidence lịch sử của chính đội/context, có giới hạn.
- **Sprint Backlog:** Sprint Goal + selected PBI + actionable plan.
- **Core/negotiable:** boundary thực hành để thích nghi scope mà bảo vệ Goal/DoD.
- **Risk trigger:** điều kiện quan sát kích hoạt response/reforecast.

Mental model: **Goal bảo vệ why; forecast minh bạch what; plan làm actionable how; inspection thay plan, không che uncertainty**.

## 7. Nguồn tham khảo và provenance phần bổ sung

Nội dung dùng đúng SRC-SG20, SRC-SPRINT-PLANNING, SRC-FORECAST và SRC-PROJECT. PBI, lịch sử, capacity và scenario MEX là simulated course data, không phải benchmark/guarantee. Không dùng nguồn bổ sung.

---
<!-- QUALITY GATE: hai leaf đủ semantic contract; MEX-U06-01 phủ LO/outline, map CP-U06-01/02; checklist hoàn tất; không còn chỉ dẫn khung. -->

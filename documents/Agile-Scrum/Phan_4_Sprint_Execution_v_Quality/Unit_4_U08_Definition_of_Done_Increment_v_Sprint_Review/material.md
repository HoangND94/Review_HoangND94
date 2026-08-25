# Unit U08: Definition of Done, Increment và Sprint Review — Học liệu cốt lõi

> **Khóa học:** Agile–Scrum thực hành qua dự án thương mại điện tử NovaShop · **Thuộc:** Sprint Execution và Quality · **Mức xác thực:** simulated

## 🎯 Learning Outcomes

- **LO8.1** — Áp dụng acceptance criteria và Definition of Done để phân loại chính xác Done/Not Done kèm evidence. Bằng chứng: Increment evidence pack và quality-gate decision.
- **LO8.2** — Tổng hợp stakeholder feedback thành Product Backlog changes có owner, rationale và traceability. Bằng chứng: Sprint Review record và backlog v3.

## Ngữ cảnh và phần tăng trưởng M-U08

NovaShop kết thúc Sprint với một số PBI hoàn thành một phần. Scrum Team phải xác định phần nào thật sự thuộc Increment, inspect outcome với stakeholders và cập nhật Product Backlog. Ba artifact mới—**Increment evidence pack**, **Sprint Review record**, **Product Backlog v3**—tiêu thụ Sprint Goal/Sprint Backlog từ ASM-U06 và trở thành baseline trực tiếp cho ASM-U10.

Toàn bộ evidence là mô phỏng. Các kiểm tra accessibility/security chỉ áp dụng cho tập tiêu chí đã ghi rõ; kết quả không phải tuyên bố conformance WCAG 2.2 AA, không phải chứng nhận ASVS 5.0.0 và không đại diện kiểm toán production.

## Nguồn đầu vào đã map

- **SRC-SG20** — [The Scrum Guide](https://scrumguides.org/scrum-guide.html), Ken Schwaber & Jeff Sutherland/ScrumGuides.org, November 2020, accessed 2026-08-25, CC BY-SA 4.0, allowed use: adapt.
- **SRC-DOD** — [What is the Definition of Done?](https://www.scrum.org/resources/what-definition-done-0), Scrum.org, snapshot/accessed 2026-08-25, website terms, allowed use: reference.
- **SRC-WCAG22** — [WCAG 2.2](https://www.w3.org/TR/2024/REC-WCAG22-20241212/), W3C Recommendation 12 December 2024, accessed 2026-08-25, W3C document use rules, allowed use: reference.
- **SRC-ASVS500** — [OWASP ASVS 5.0.0](https://github.com/OWASP/ASVS/tree/v5.0.0_release), OWASP Foundation, May 2025, accessed 2026-08-25, CC BY-SA 4.0, allowed use: adapt.

## 1. Kiến thức tiên quyết và môi trường

Học viên cần hoàn thành U07; có Sprint Goal, Sprint Backlog, board/evidence và DoD versioned. Môi trường `ENV-PRO-ARTIFACT` dùng Markdown/CSV và checklist review. Smoke check: ID của PBI/evidence mở được; DoD có version/effective scope; bản làm việc tách khỏi starter asset; mọi dữ liệu là synthetic.

## 2. Mental map

`Sprint execution evidence (U07) → acceptance + DoD gate (U08) → inspect Increment/outcome với stakeholder → Product Backlog v3 → metrics/forecast (U10)`

Acceptance criteria trả lời một PBI có hành vi được yêu cầu hay chưa. DoD mô tả trạng thái chất lượng chung để work trở thành một phần của Increment. Sprint Review dùng Increment và thay đổi môi trường để quyết định bước tiếp theo; đây là working session, không phải lễ nghiệm thu hay release gate.

## 3. Nội dung lý thuyết cốt lõi

**Checklist Content Outlines:**

- [x] Increment, acceptance criteria và Definition of Done evidence
- [x] Sprint Review và chuyển stakeholder feedback thành adaptation

### OUT-U08-01 — Increment, acceptance criteria và Definition of Done evidence

**Mapping:** OUT-U08-01 · LO8.1 · M-U08/Increment evidence pack và quality-gate decision.

#### Định nghĩa và ranh giới

- **Acceptance criteria (AC)** là điều kiện quan sát được cho một PBI/slice cụ thể.
- **DoD** là mô tả chính thức về trạng thái Increment khi đạt các quality measures bắt buộc cho sản phẩm.
- **Increment** là bước tiến cụ thể, usable hướng Product Goal, cộng dồn với các Increment trước và đã được verify để hoạt động cùng nhau.

PBI chỉ được gọi Done và trở thành một phần của Increment khi AC phù hợp **và toàn bộ DoD áp dụng** đều đạt. “Dev complete”, “demo được bằng chuột” hoặc “chỉ thiếu một check” không tạo trạng thái Done một phần. Work không đạt DoD trở lại Product Backlog để xem xét sau; Sprint Review không phải gate phát hành và không biến work chưa Done thành Increment.

#### Vấn đề, vai trò và quyết định

Developers chịu trách nhiệm instill quality bằng việc tuân thủ DoD và cung cấp evidence. Product Owner không thể override quality gate để làm đẹp báo cáo. Stakeholders cần biết chính xác phần usable có thể inspect. Quyết định trọng tâm là: PBI nào Done/Not Done; evidence nào chứng minh; gap nào phải quay về Product Backlog; phạm vi claim chất lượng tới đâu.

#### Cơ chế và mental model

Quality gate chạy theo `PBI → AC evidence → DoD applicability → DoD evidence → decision → Increment membership/backlog disposition`. Mỗi evidence cần ID, scope, thời điểm, result và link tới criterion. “PASS” không có scope/tệp chứng cứ không đủ.

Evidence pack tối thiểu:

| Trường | Oracle |
| --- | --- |
| PBI/AC | ID resolve, từng AC có PASS/FAIL và evidence link |
| DoD version | version cố định, mỗi dòng áp dụng có result/evidence |
| Scope statement | page/flow/role/browser/check được test; limitation rõ |
| Decision | Done chỉ khi không còn FAIL/MISSING bắt buộc |
| Increment membership | Done item được liệt kê; Not Done có backlog action |

Với accessibility, một keyboard test trên checkout chỉ chứng minh selected check trong scope đó. WCAG 2.2 conformance yêu cầu nhiều điều kiện ở cấp page/process; không suy rộng từ một check. Với security, mapping một test authorization tới một selected ASVS requirement cũng không chứng minh toàn bộ level/standard.

#### Khi dùng, khi không dùng và trade-off

Dùng gate ngay khi PBI có khả năng đạt DoD và trước khi gọi Done/release. Không trì hoãn mọi kiểm tra tới Sprint Review. AC và DoD không thay thế nhau: AC có thể PASS nhưng security/accessibility evidence bắt buộc còn thiếu; DoD có thể PASS nhưng một hành vi nghiệp vụ vẫn FAIL. DoD mạnh làm minh bạch chi phí chất lượng; mở rộng DoD cần capacity và tự động hóa phù hợp, nhưng không được hạ hồi tố trong Sprint để cứu forecast.

#### Ví dụ thực tế có oracle

PBI `CHK-201` cho payment decline có 3/3 AC PASS, integration PASS, peer review PASS, selected keyboard test trên checkout states PASS và selected customer/admin authorization test PASS; documentation PASS. Nó có thể được gọi Done nếu đây là toàn bộ `DOD-NS-1.0` áp dụng. `CHK-202` hiển thị phí vận chuyển có AC PASS nhưng selected keyboard test FAIL vì không chọn được delivery option bằng phím; quyết định phải là Not Done.

Scope statement đúng: “Kiểm SC 2.1.1 Keyboard cho checkout delivery selector trên fixture, Chrome/Windows; 8/9 bước PASS, một FAIL; không tuyên bố WCAG 2.2 AA conformance.” Claim sai: “Checkout đạt chuẩn WCAG AA” từ một test.

#### Best practices

- **Rule:** evidence phải gắn criterion và scope. **Rationale:** reviewer cần tái tạo decision. **Positive:** `E-A11Y-22` → selected SC 2.1.1 → delivery selector → FAIL. **Negative:** “accessibility checked” không cho biết đã kiểm gì; Done decision không audit được.
- **Rule:** tất cả điều kiện bắt buộc là gate, không lấy trung bình. **Rationale:** một gap có thể làm Increment unusable/không đạt quality measure. **Positive:** 9 PASS + 1 FAIL = Not Done. **Negative:** “90% hoàn thành nên Done”; consequence là transparency giả.
- **Rule:** version DoD trước decision. **Rationale:** ngăn thay chuẩn hồi tố. **Positive:** dùng `DOD-NS-1.0` cho mọi PBI Sprint. **Negative:** xóa keyboard check sau khi test FAIL.

#### Failure diagnosis

| Dấu hiệu | Nguyên nhân | Chẩn đoán/evidence | Sửa và phòng tránh |
| --- | --- | --- | --- |
| PBI Done nhưng evidence link 404/MISSING | Gate dựa vào lời xác nhận | Resolve từng link/ID | Chuyển Not Done tới khi evidence hợp lệ; dùng checklist link-check |
| AC PASS nhưng Increment không usable | DoD bị bỏ qua | So matrix AC và DoD | Chạy đủ DoD áp dụng, không lấy AC thay quality gate |
| Claim “WCAG/ASVS compliant” từ vài check | Scope bị suy rộng | So claim với test scope và yêu cầu conformance | Viết selected-check statement + limitation; bỏ claim toàn diện |

### OUT-U08-02 — Sprint Review và chuyển stakeholder feedback thành adaptation

**Mapping:** OUT-U08-02 · LO8.2 · M-U08/Sprint Review record và Product Backlog v3.

#### Định nghĩa và ranh giới

Sprint Review là cơ hội inspect outcome của Sprint và xác định future adaptations. Scrum Team cùng key stakeholders xem phần đã hoàn thành, điều đã đổi trong môi trường, tiến độ tới Product Goal và cộng tác về bước tiếp theo. Đây là working session, không chỉ slide/demo, không phải sign-off gate và không phải Sprint Retrospective.

Feedback là input, không tự động thành commitment. Product Owner vẫn accountable cho Product Backlog management. Mỗi feedback phải có disposition có lý do: **accept** (tạo/sửa PBI), **defer** (cần evidence/điều kiện sau), **reject** (trái Goal/constraint/out-of-scope), hoặc **merge** với PBI hiện có.

#### Vấn đề, vai trò và quyết định

Stakeholder cần thấy usable outcome và ảnh hưởng tới mục tiêu; Product Owner cần quyết định feedback nào làm thay đổi ordered backlog; Developers cung cấp feasibility/evidence. Quyết định cần tạo traceability: feedback → rationale/value/risk → PBI owner → Product Goal/Sprint evidence → downstream impact.

#### Cơ chế và mental model

`Increment evidence + outcome signal + environment change + feedback → clarification → disposition → backlog diff → owner/next evidence`. Một feedback card tối thiểu có ID, source/need, evidence, disposition, rationale, owner, PBI link và impact. Product Backlog v3 là diff có order/rationale, không chỉ danh sách ghi chú.

#### Khi dùng, khi không dùng và trade-off

Dùng Sprint Review cho collaboration chiến lược/tactical quanh sản phẩm và Product Goal. Không dùng để chấm cá nhân, ép accept work chưa Done hoặc giải quyết team-process issue chi tiết (đưa sang Retrospective). Accept nhiều feedback tăng responsiveness nhưng làm loãng Goal; reject/defer cần evidence để không trở thành độc đoán.

#### Ví dụ thực tế có oracle

Stakeholder đưa ba feedback: `FB-31` muốn thấy phí vận chuyển trước payment; `FB-32` muốn AI recommendation; `FB-33` muốn same-day shipping. NovaShop accept `FB-31` thành `PB-320` vì giảm surprise ở checkout và nằm trong boundary; reject `FB-32` vì AI out-of-scope của MVP; defer `FB-33` tới khi có carrier evidence. Mỗi disposition có owner/Product Owner, rationale, Goal impact và review trigger. PASS khi 3/3 feedback có disposition; accepted item xuất hiện trong backlog v3 với order rationale; rejected/deferred card giữ audit trail.

#### Best practices

- **Rule:** chỉ inspect work Done như Increment. **Rationale:** feedback trên trạng thái giả tạo tạo quyết định sai. **Positive:** demo CHK-201; nêu CHK-202 Not Done/gap riêng. **Negative:** trình bày CHK-202 như hoàn tất và giấu keyboard failure.
- **Rule:** disposition mọi feedback, không “ghi nhận” chung chung. **Rationale:** tạo closed-loop traceability. **Positive:** `FB-31 → ACCEPT → PB-320 → owner/review`. **Negative:** “sẽ xem xét” không có owner/trigger, feedback mất dấu.
- **Rule:** cập nhật backlog theo Goal/value/risk evidence. **Rationale:** feedback lớn tiếng không đồng nghĩa giá trị cao. **Positive:** defer same-day shipping chờ carrier evidence. **Negative:** đưa mọi ý kiến lên đầu backlog, phá ordering rationale.

#### Failure diagnosis

| Dấu hiệu | Nguyên nhân | Chẩn đoán/evidence | Sửa và phòng tránh |
| --- | --- | --- | --- |
| Review chỉ có demo/slides | Không có collaboration/adaptation | Agenda/record không có feedback disposition/backlog diff | Thêm working segment và decision owner |
| Feedback accepted nhưng backlog không đổi | Chuỗi artifact đứt | Resolve feedback→PBI links | Tạo/update PBI, order/rationale và impact note |
| Stakeholder “approve” item Not Done | Review bị biến thành quality gate | So evidence pack với demo list | Gỡ khỏi Increment, giữ gap minh bạch, trả work về backlog |

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### MEX-U08-01 — Quality gate và feedback disposition matrix

**Mode:** professional_artifact · **LO:** LO8.1, LO8.2 · **Outline:** OUT-U08-01, OUT-U08-02 · **Lab:** `LAB-U08-01/CP-U08-01`, `CP-U08-02`.

### Increment evidence pack

| PBI | AC | DoD evidence | Scope/limitation | Decision |
| --- | --- | --- | --- | --- |
| CHK-201 payment decline | 3/3 PASS (`E-AC-201`) | integration/review/docs PASS; selected keyboard PASS; selected authz PASS | Checkout fixture; Chrome/Windows; selected checks only | Done; include Increment |
| CHK-202 shipping selector | 2/2 PASS (`E-AC-202`) | keyboard FAIL (`E-A11Y-202`); remaining checks PASS | Selected SC 2.1.1 test only; no WCAG conformance claim | Not Done; return backlog |
| ORD-203 admin status | 2/2 PASS (`E-AC-203`) | selected customer/admin authorization + audit evidence PASS | Selected ASVS-mapped check only; no ASVS level claim | Done; include Increment |

### Sprint Review record và backlog diff

| Feedback | Evidence/need | Disposition | Rationale | Owner/link/next check |
| --- | --- | --- | --- | --- |
| FB-31 phí trước payment | 3/5 synthetic interviews mention surprise | Accept | Trong boundary, hỗ trợ checkout completion hypothesis | PO → PB-320; refine 27-Aug |
| FB-32 AI recommendation | Sponsor idea, chưa evidence | Reject | Out-of-scope MVP | PO; revisit only if Product Goal changes |
| FB-33 same-day shipping | 1 sales request; carrier unknown | Defer | Dependency/evidence chưa đủ | PO + Ops; trigger carrier sandbox contract |

Backlog v3 diff: add `PB-320`, keep `CHK-202` với evidence gap, không add AI; `FB-33` nằm decision log chờ trigger. Scope statement đi kèm: selected checks demonstrate only recorded cases, not whole-site WCAG/ASVS conformance.

### Oracle

- `QG-01`: mỗi PBI có AC + DoD version + evidence + decision; bất kỳ FAIL/MISSING bắt buộc nào ⇒ Not Done.
- `SCOPE-01`: claim không vượt page/flow/role/browser/selected check đã test.
- `SR-01`: chỉ Done items nằm trong Increment/demo-as-complete.
- `FB-01`: mọi feedback có disposition/rationale/owner/link hoặc trigger.
- `PB-01`: Product Backlog v3 diff resolve tới feedback/evidence và có ordering rationale.

Kết quả mẫu: 5/5 PASS. Lab dùng fixture mới; Assignment dùng A03 baseline và change request khác, không được suy ra đáp án bằng đổi ID.

### Mapping Material worked example → Hands-on Lab tương ứng

- **MEX-U08-01** → **LAB-U08-01/CP-U08-01** và **LAB-U08-01/CP-U08-02**; cùng phủ LO8.1, LO8.2 và yêu cầu evidence riêng theo từng checkpoint.

## 5. Thuật ngữ

- **Done/Not Done:** quyết định nhị phân theo AC + DoD áp dụng; không phải phần trăm hoàn thành.
- **Evidence pack:** tập criterion→evidence→decision có scope/version.
- **Disposition:** quyết định xử lý feedback có rationale và đường đi tiếp theo.
- **Conformance claim:** tuyên bố đáp ứng toàn bộ yêu cầu conformance; không đồng nghĩa selected-check result.
- **Backlog diff:** thay đổi add/update/order/remove có lý do so với baseline.

## 7. Nguồn tham khảo và provenance phần bổ sung

Scrum/DoD/Review rules bám SRC-SG20 và SRC-DOD. Claim-scope guardrails bám SRC-WCAG22 và SRC-ASVS500. Fixture, IDs, test results và matrices: **[BỔ SUNG — nguồn: SRC-PROJECT, dữ liệu mô phỏng cho khóa học]**. Không có chứng nhận hay audit thực tế.

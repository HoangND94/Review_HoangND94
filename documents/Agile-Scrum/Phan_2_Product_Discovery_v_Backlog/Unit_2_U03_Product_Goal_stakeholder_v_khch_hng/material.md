# Unit U03: Product Goal, stakeholder và khách hàng — Học liệu cốt lõi

> **Khóa học:** Agile–Scrum thực hành qua dự án thương mại điện tử NovaShop · **Thuộc:** Product Discovery và Backlog

## 🎯 Learning Outcomes

- **LO3.1** [create] — Viết Product Goal cho NovaShop có outcome, chỉ số, ranh giới sản phẩm và điều kiện đánh giá lại.
- **LO3.2** [analyze] — Phân tích tối thiểu ba nhóm stakeholder/customer để xác định pain point, nhu cầu thông tin và xung đột ưu tiên.

## Ngữ cảnh dự án và phần tăng trưởng của Unit

NovaShop là tình huống **simulated**, dùng payment/shipping/email sandbox và dữ liệu synthetic; không có customer, giao dịch, PII hay credential thật. U03 kế thừa Team Charter/Working Agreement từ U02 và tạo milestone **M-U03**:

- Product Goal card có future outcome, metric contract, product boundary và review trigger;
- stakeholder evidence map phân biệt claim, evidence, confidence và implication;
- evidence-based persona không dùng demographic stereotype;
- customer journey nối bước, pain point, evidence và opportunity.

MEX-U03-01 hiện thực hóa cả hai outline leaf. LAB-U03-01 dùng evidence cards mới và một conflict/change card. Artifact M-U03 là baseline cho story map/backlog U04, Review REV-01 và CAP-01.

## Nguồn đầu vào đã map

- SRC-SG20 — The Scrum Guide: https://scrumguides.org/scrum-guide.html (publisher: Ken Schwaber, Jeff Sutherland / ScrumGuides.org; version: November 2020; accessed_at: 2026-08-25; license: CC BY-SA 4.0; allowed_use: adapt)
- SRC-EBM24 — Evidence-Based Management Guide: https://www.scrum.org/resources/online-evidence-based-management-guide (publisher: Scrum.org; version: May 2024; accessed_at: 2026-08-25; license: CC BY-SA 4.0; allowed_use: adapt)
- SRC-AP01 — Principles behind the Agile Manifesto: https://agilemanifesto.org/principles.html (publisher: Agile Manifesto authors; version: 2001; accessed_at: 2026-08-25; license: reference-only; allowed_use: reference)
- SRC-PROJECT — NovaShop simulated e-commerce project brief: starter/NovaShop_Project_Brief.md (publisher: Training artifact created for this course; version: 1.0; accessed_at: 2026-08-25; license: internal approved; allowed_use: internal_approved)

## 1. Kiến thức tiên quyết và môi trường

Hoàn thành U02 hoặc có Scrum operating-model baseline đã review. Học viên cần đọc tỷ lệ có mẫu số, phân biệt target/observation/assumption và ghi conflict bằng evidence.

Môi trường **ENV-PRO-ARTIFACT**: Markdown editor CommonMark-compatible, spreadsheet CSV UTF-8 và whiteboard/paper. Không cần code, cloud hay tài khoản trả phí.

Smoke check:

1. Mở project brief, synthetic CSV và artifact templates.
2. Xác nhận OBS-01 = 7/10, OBS-02 = 4/12, OBS-03 = target 20%, OBS-04 = 6/15.
3. Mở Team Charter/Working Agreement baseline hoặc ghi limitation nếu dùng bản giảng viên.
4. Tạo working copy cho Product Goal/stakeholder evidence; starter asset không bị sửa.

Phương thức xác minh: **artifact_review**. Practice mode: **professional_artifact**, vì LO yêu cầu product/discovery artifacts có oracle, không yêu cầu code.

## 2. Định vị trong lộ trình

U01 làm rõ uncertainty/hypothesis; U02 tạo accountability và feedback cadence; U03 chọn một future state đủ rõ để Product Backlog hướng tới và làm rõ evidence từ người chịu tác động. U04 sẽ chuyển journey/opportunities thành story map và vertical slices.

Mental model: **business intent → stakeholder evidence → product future state → measure/boundary → Product Backlog discovery**. Không được đảo chuỗi thành “feature list → tìm metric để hợp thức hóa”.

## 3. Nội dung lý thuyết cốt lõi

**Checklist bắt buộc phủ — giữ nguyên văn và đúng thứ tự Content Outlines:**

- [x] Product Goal: outcome, chỉ số và ranh giới sản phẩm
- [x] Stakeholder evidence, persona và customer journey

#### OUT-U03-01 Product Goal: outcome, chỉ số và ranh giới sản phẩm

**Mapping:** OUT-U03-01 · LO3.1 · M-U03 Product Goal card

##### Định nghĩa và ranh giới

Product Goal mô tả future state của product, là target để Scrum Team lập kế hoạch và là commitment của Product Backlog. Product có boundary rõ, stakeholder và user/customer đã biết. Scrum Team tập trung một Product Goal tại một thời điểm và hoàn thành hoặc abandon mục tiêu đó trước khi nhận mục tiêu dài hạn tiếp theo.

Một Product Goal không phải:

- danh sách features hoặc project scope cố định;
- Sprint Goal;
- deadline/release plan;
- metric target đứng một mình;
- tuyên bố vision quá xa không hỗ trợ ordering.

Trong khóa này, Product Goal card bổ sung outcome metric, baseline/target, boundary, assumptions và review trigger để kiểm chứng quyết định. Các trường bổ sung là practice nghề nghiệp, không phải field bắt buộc trong Scrum Guide.

##### Vấn đề, vai trò và quyết định cần đưa ra

Product Owner accountable phát triển và truyền đạt Product Goal; Scrum Team cùng stakeholder cung cấp evidence và kiểm feasibility/value. Goal phải giúp quyết định:

- future state nào đáng đầu tư trước;
- evidence nào cho thấy progress hoặc invalidation;
- phần nào nằm trong product boundary và phần nào không;
- khi nào giữ, điều chỉnh hoặc abandon Goal;
- backlog opportunity nào phục vụ Goal và item nào chỉ là output hấp dẫn.

Sponsor targets là input chứ chưa là evidence. Product Owner không được đổi Goal sau mọi feedback; chỉ review khi trigger hoặc evidence cho thấy objective không còn phù hợp.

##### Cơ chế và mental model

Một Goal card kiểm chứng được có sáu lớp:

1. **Actor/future state:** ai đạt kết quả nào.
2. **Outcome metric:** hành vi/kết quả sẽ thay đổi; có công thức/đơn vị.
3. **Baseline/target/time horizon:** điểm bắt đầu, ngưỡng hướng tới và cửa sổ đo.
4. **Product boundary:** components trong phạm vi và out-of-scope.
5. **Assumptions/guardrails:** điều chưa biết và kết quả không được làm xấu.
6. **Review trigger:** evidence hoặc thay đổi context buộc đánh giá lại.

Output metrics như số màn hình chỉ chứng minh đã làm việc; outcome metrics như tỷ lệ đơn hợp lệ không cần nhập lại cho biết thay đổi mong muốn. Một proxy sớm có thể dùng nhưng phải ghi limitation.

##### Khi dùng, khi không dùng và trade-off

Dùng Product Goal để thống nhất hướng dài hạn cho complex product work và làm basis cho Product Backlog. Không viết Goal mới cho mỗi Sprint hoặc mỗi stakeholder request. Nếu work hoàn toàn operational theo contract ngắn, một service objective/plan có thể phù hợp hơn; không tạo Product Goal hình thức.

Goal càng cụ thể càng dễ đo/order nhưng có nguy cơ khóa giải pháp. Goal quá rộng tạo freedom nhưng không hỗ trợ decision. Metric tạo focus nhưng dễ bị game; guardrail và evidence review giảm rủi ro. Một Goal có nhiều metrics có bức tranh tốt hơn nhưng tăng complexity; nên có primary outcome và vài guardrails rõ.

##### Ví dụ NovaShop riêng và oracle

- **Context/stakeholder:** PO cần thống nhất future state cho hành trình order trước U04.
- **Input:** OBS-02 = 4/12 đơn synthetic cần nhập lại địa chỉ, nên baseline đơn không cần nhập lại là 8/12; sponsor target là ít nhất 95% đơn hợp lệ đi tới packing không cần nhập lại.
- **Decision/action:** Goal: “Trong ba tháng sau release mô phỏng, người mua và kho vận có luồng order số hóa giúp ít nhất 95% đơn hợp lệ đi tới packing không cần nhập lại, từ baseline synthetic 8/12; phạm vi từ catalog đến tracking, không gồm ERP/payment thật.”
- **Artifact:** PG-U03-01 card với primary metric, boundary và review trigger.
- **Expected:** Goal nói future outcome, không bắt buộc guest checkout hoặc một solution cụ thể.
- **Oracle:** PASS khi card có outcome, formula/denominator, baseline 8/12, target/time horizon, in/out boundary và ít nhất hai review triggers. FAIL khi viết “xây website có checkout trước ngày X”.

##### Liên kết MEX và Lab

Product Goal card được triển khai đầy đủ trong **MEX-U03-01 — Product Goal card và stakeholder evidence map** ở mục 4. CP-U03-01 tái tạo Goal bằng evidence conflict mới; CP-U03-02 đánh giá Goal khi sponsor đưa output target mới. Cả hai tham chiếu MEX-U03-01.

##### Best practices

**Rule:** Viết Goal bằng future outcome và để solution emerge trong Product Backlog. **Rationale:** Goal khóa giải pháp làm giảm khả năng học. **Positive:** “95% đơn hợp lệ không cần nhập lại”. **Negative/hậu quả:** “triển khai form 12 trường” có thể hoàn thành output mà re-entry không giảm.

**Rule:** Mỗi metric phải có baseline, numerator/denominator, window và limitation. **Rationale:** tỷ lệ thiếu contract không thể tái tính hoặc so sánh. **Positive:** “8/12 baseline synthetic, target ≥95% valid orders trong ba tháng mô phỏng”. **Negative/hậu quả:** “tăng conversion 20%” không biết tăng điểm phần trăm hay tương đối, từ baseline nào.

##### Failure diagnosis và cách sửa

- **Dấu hiệu:** Goal là roadmap features. **Nguyên nhân:** nhầm output với future state. **Chẩn đoán:** bỏ feature name thì không còn outcome. **Sửa:** viết actor/result/measure trước rồi đưa features về backlog. **Phòng tránh:** dùng outcome test.
- **Dấu hiệu:** Goal thay mỗi tuần. **Nguyên nhân:** không có review trigger hoặc nhầm backlog adaptation với Goal change. **Chẩn đoán:** mỗi request tạo Goal mới dù objective còn hợp lệ. **Sửa:** giữ Goal, adapt backlog; chỉ review khi trigger. **Phòng tránh:** ghi triggers và decision owner.

#### OUT-U03-02 Stakeholder evidence, persona và customer journey

**Mapping:** OUT-U03-02 · LO3.2 · M-U03 stakeholder map/persona/customer journey

##### Định nghĩa và ranh giới

**Stakeholder evidence map** nối một stakeholder claim với evidence source, confidence, implication và conflict. **Persona** là mô hình hành vi/nhu cầu dựa trên evidence, không phải hồ sơ hư cấu dựa tuổi, giới hay thu nhập không liên quan. **Customer journey** biểu diễn các bước actor thực hiện để đạt outcome, gồm action, need, pain point, evidence, handoff và opportunity.

Stakeholder không chỉ là customer: sponsor, kho vận, Customer Service và quality reviewer đều chịu tác động hoặc ảnh hưởng quyết định. Stakeholder opinion không tự động là customer evidence. Journey không phải process map nội bộ thuần túy và không phải solution screen flow.

##### Vấn đề, vai trò và quyết định cần đưa ra

Product Owner cần hiểu ai tạo/nhận value, ai chịu risk và conflicts nào ảnh hưởng Goal. Đội phải quyết định:

- claim nào là observation, assumption hay target;
- confidence dựa vào sample/provenance nào;
- persona nào đủ evidence để dùng, persona nào phải bỏ;
- pain point nào cần discovery trước;
- conflict giữa friction, data completeness và investment được xử lý bằng guardrail/trade-off nào.

##### Cơ chế và mental model

Chuỗi evidence:

**stakeholder → need/decision → claim → source → confidence/limitation → implication → opportunity/experiment**.

Persona gom các pattern hành vi có evidence; không “đại diện tất cả”. Journey đặt pattern vào thời gian: discover → evaluate → cart → checkout → confirmation → tracking/support. Handoff giúp thấy một cải tiến cho buyer có thể tạo cost cho warehouse. Conflict matrix buộc nêu hai outcomes và evidence thiếu, thay vì chọn stakeholder quyền lực nhất.

Nếu evidence mới trái persona, cập nhật confidence/persona/journey; không loại evidence để bảo vệ artifact.

##### Khi dùng, khi không dùng và trade-off

Dùng evidence map khi có nhiều nhóm và claim cạnh tranh; dùng persona khi cần một model hành vi ổn định hơn từng quote; dùng journey khi outcome kéo qua nhiều bước/handoff. Không dựng persona khi chỉ có stereotype hoặc một câu nói; khi đó giữ hypothesis/segment candidate. Không dùng journey cho architecture/component map.

Nhiều evidence tăng confidence nhưng tốn thời gian; sample synthetic nhỏ cho học nhanh nhưng không chứng minh thị trường. Persona làm discussion cụ thể nhưng có thể che diversity; giữ confidence/exception. Journey giúp thấy end-to-end value nhưng dễ phình; giới hạn bằng Product Goal/boundary.

##### Ví dụ NovaShop riêng và oracle

- **Context:** buyer, warehouse và Customer Service có needs giao nhau.
- **Input:** OBS-01 7/10 bỏ khi buộc account; OBS-02 4/12 re-entry; OBS-04 6/15 hỏi trạng thái; OBS-03 target 20% là assumption.
- **Decision/action:** map ba observed needs và một sponsor target; tạo persona hành vi “người mua ưu tiên hoàn tất nhanh và cần biết trạng thái” không thêm demographic; journey đánh dấu friction account, address handoff và tracking gap.
- **Artifact:** SEM-U03-01, PER-U03-01, JRN-U03-01.
- **Expected:** mỗi pain point có source/confidence; conflict “ít friction ↔ đủ dữ liệu giao hàng” có guardrail; sponsor target không được gắn nhãn observation.
- **Oracle:** PASS khi có ít nhất ba stakeholder groups, mỗi claim nối evidence/confidence/implication, persona chỉ chứa evidence-backed attributes, journey có end-to-end steps và không có pain point mồ côi. FAIL nếu persona ghi tuổi/nghề tùy ý.

##### Liên kết MEX và Lab

MEX-U03-01 tích hợp evidence map với Goal. CP-U03-01 dùng evidence cards mới cho buyer/warehouse/sponsor; CP-U03-02 thêm output request để kiểm Goal/journey implication mà không sao chép MEX.

##### Best practices

**Rule:** Mỗi persona attribute và journey pain point phải có evidence ID hoặc nhãn assumption. **Rationale:** traceability ngăn stereotype trở thành requirement. **Positive:** “cần checkout ít ma sát — OBS-01, confidence medium”. **Negative/hậu quả:** “nữ 25–34 thích mỹ phẩm” không có evidence và dễ dẫn tới exclusion.

**Rule:** Ghi conflict như hai outcome cùng trade-off/guardrail, không chọn theo quyền lực. **Rationale:** local optimization có thể chuyển cost sang stakeholder khác. **Positive:** giảm fields nhưng giữ address validity threshold. **Negative/hậu quả:** bỏ validation để giảm friction làm re-entry tăng.

##### Failure diagnosis và cách sửa

- **Dấu hiệu:** mọi claim “high confidence”. **Nguyên nhân:** bỏ qua sample/provenance. **Chẩn đoán:** OBS nhỏ nhưng confidence không có rationale. **Sửa:** hạ confidence, ghi limitation/evidence cần thêm. **Phòng tránh:** confidence rubric.
- **Dấu hiệu:** journey chỉ liệt kê màn hình. **Nguyên nhân:** solution-first. **Chẩn đoán:** không có actor need/pain/evidence/handoff. **Sửa:** dựng actor outcome/steps trước UI. **Phòng tránh:** journey oracle.

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### MEX-U03-01 — Product Goal card và stakeholder evidence map

**Practice contract:** professional_artifact · **LO:** LO3.1, LO3.2 · **Outline:** OUT-U03-01, OUT-U03-02 · **Milestone:** M-U03

### Input/trạng thái ban đầu

- OBS-01: 7/10 guest buyers bỏ checkout khi buộc account.
- OBS-02: 4/12 orders cần nhập lại địa chỉ.
- OBS-03: sponsor target tăng đơn 20%, status assumption.
- OBS-04: 6/15 support requests hỏi trạng thái.
- Product boundary: catalog đến order tracking/admin cơ bản; payment thật, ERP và mobile native ngoài scope.

### Product Goal card PG-U03-01

| Trường | Giá trị |
| --- | --- |
| Future state/outcome | Người mua hoàn tất order và kho vận nhận order hợp lệ qua luồng số hóa, giảm handoff nhập lại |
| Primary metric | valid orders reaching packing without re-entry / all valid orders |
| Baseline | 8/12 trong dataset synthetic vì 4/12 cần re-entry |
| Target/horizon | ít nhất 95% trong ba tháng sau release mô phỏng |
| Supporting signal | status-help requests và checkout progression, chỉ là proxy |
| In boundary | catalog/search, cart, checkout sandbox, confirmation/tracking, order admin |
| Out of scope | payment thật/card storage, ERP đầy đủ, mobile native, refund phức tạp |
| Guardrails | không PII/card; checkout failure giữ input; không tuyên bố market result |
| Review triggers | evidence cho thấy target/measure không hợp lệ; product boundary thay đổi; guardrail vi phạm; Goal không còn valuable/feasible |
| Assumptions | account friction ảnh hưởng progression; better tracking giảm support; đều cần kiểm |

### Stakeholder evidence map SEM-U03-01

| Stakeholder | Claim/need | Evidence/status | Confidence/limitation | Implication/conflict |
| --- | --- | --- | --- | --- |
| Guest buyer | hoàn tất checkout với ít friction | OBS-01 7/10 bỏ khi buộc account | medium; synthetic, sample 10, không causal | explore account friction; giữ address/payment guardrails |
| Warehouse | order hợp lệ, không re-entry | OBS-02 4/12 cần nhập lại | medium; synthetic, sample 12 | address completeness là guardrail; conflict với fewer fields |
| Customer Service | thấy status/correlation để xử lý exception | OBS-04 6/15 hỏi status | medium; synthetic, sample 15 | include tracking/status opportunity, không kết luận exact UI |
| Sponsor | tăng online orders 20% | OBS-03 target assumption | low as evidence; target only | dùng làm investment hypothesis, không claim achieved |

### Evidence-based persona PER-U03-01

**Tên hành vi:** Người mua cần hoàn tất và theo dõi đơn với ít ma sát.

- Goal: đi từ tìm sản phẩm tới xác nhận/tracking.
- Behaviors/evidence: account gate friction (OBS-01); status information need (OBS-04).
- Needs: ít bước không cần thiết, input không mất khi failure, trạng thái dễ hiểu.
- Constraints: vẫn cung cấp địa chỉ hợp lệ; chỉ xem order của account/session synthetic.
- Unknowns: guest checkout có thực sự cải thiện outcome; status detail nào đủ.
- Không đưa tuổi, giới, thu nhập hoặc quote giả.

### Customer journey JRN-U03-01

| Step | Actor need/action | Pain/evidence | Handoff/risk | Opportunity, chưa phải solution |
| --- | --- | --- | --- | --- |
| Discover/evaluate | tìm và chọn sản phẩm | chưa có evidence pain | catalog/search | giữ trong boundary, cần evidence |
| Cart | kiểm total/promotion | FR-02 oracle | pricing/promo | observable validation |
| Checkout | cung cấp thông tin tối thiểu | OBS-01 account friction | buyer → order | test friction hypothesis |
| Validate order | gửi địa chỉ/order hợp lệ | OBS-02 re-entry | order → warehouse | improve validity without extra friction |
| Confirm/track | biết order state/next step | OBS-04 status questions | order → buyer/CS | explore self-service status |

### Expected result và verification oracle

PASS khi:

1. Goal có outcome, metric formula, baseline/target/horizon, boundary và review triggers.
2. Ít nhất ba stakeholder groups có claim → evidence → confidence → implication.
3. Persona không có stereotype/unsupported attribute.
4. Journey mỗi pain point có evidence hoặc assumption label, và conflict buyer/warehouse hiện rõ.
5. OBS-03 vẫn là target/assumption; sample synthetic limitations được ghi.

Edge oracle: nếu evidence mới cho thấy re-entry chỉ 1/20 nhưng checkout completion giảm, Goal chưa tự động đổi; PO inspect metric validity, guardrails và review trigger, rồi ghi decision.

### Mapping Material worked example → Hands-on Lab tương ứng

- **MEX-U03-01 → LAB-U03-01/CP-U03-01:** tạo Goal/evidence/journey bằng evidence cards mới và trace table.
- **MEX-U03-01 → LAB-U03-01/CP-U03-02:** xử lý sponsor output request, cập nhật impact note và downstream consistency.
- Lab checkpoints ghi material_example_refs = MEX-U03-01.

## 5. Lỗi thường gặp và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán/evidence | Cách sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| Goal là feature/deadline | output-first | không có future state/measure | viết outcome trước, chuyển feature về backlog | Goal oracle |
| Metric không tái tính được | thiếu denominator/window | hai reviewer cho kết quả khác | thêm formula/baseline/window | measurement contract |
| Persona stereotype | attribute không có source | không resolve evidence ID | bỏ hoặc gắn assumption/research need | evidence-per-attribute |
| Stakeholder mạnh nhất luôn thắng | không có conflict analysis | decision thiếu trade-off/guardrail | ghi cả outcomes/evidence và decision criterion | conflict matrix |
| Journey là screen list | solution-first | thiếu need/pain/handoff | dựng actor steps/evidence trước | journey checklist |

## 6. Từ điển thuật ngữ

- **Product Goal:** future state của product, commitment của Product Backlog.
- **Outcome:** thay đổi hành vi/kết quả; khác output đã tạo.
- **Metric contract:** formula, unit, baseline, target, window và limitation.
- **Product boundary:** phần product/system nằm trong và ngoài quyết định.
- **Review trigger:** evidence/context buộc đánh giá lại Goal/artifact.
- **Stakeholder evidence map:** claim → evidence → confidence → implication/conflict.
- **Persona:** mô hình hành vi/nhu cầu có evidence; không phải demographic fiction.
- **Customer journey:** chuỗi bước actor đạt outcome, gồm pain/evidence/handoff.
- **Opportunity:** vùng vấn đề đáng khám phá; chưa phải solution/PBI.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

- SRC-SG20 — Product Goal/product boundary/Product Backlog commitment, November 2020.
- SRC-EBM24 — outcome/evidence-based goal and measurement framing, May 2024.
- SRC-AP01 — customer collaboration, frequent value/feedback principles, 2001.
- SRC-PROJECT — scenario, boundary, requirements và synthetic records.

### Phần bổ sung/suy diễn

- [SUY DIỄN — từ kiến thức đã huấn luyện] Goal-card fields, confidence labels, persona/journey format và IDs là thiết kế sư phạm/professional artifact, không phải field bắt buộc của Scrum.
- [SUY DIỄN — từ kiến thức đã huấn luyện] Baseline 8/12 được suy ra trực tiếp từ OBS-02 4/12 re-entry; sample quá nhỏ để dùng như benchmark.

> **Simulated disclosure:** mọi số liệu, persona và mục tiêu là giả lập; không tuyên bố kết quả nghiên cứu thị trường hoặc hiệu quả production.

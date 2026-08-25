# Hands-on Lab LAB-U03-01 — Discovery workshop cho hành trình mua hàng

| Thuộc tính | Giá trị |
| --- | --- |
| Hình thức | guided_with_fading |
| Thời lượng | 90 phút |
| Độ khó | medium |
| Mức xác thực | simulated |
| Validation | artifact_review |

## 🎯 Learning Outcomes được thực hành

- **LO3.1:** tạo Product Goal có outcome, metric, boundary và review trigger.
- **LO3.2:** phân tích ít nhất ba stakeholder/customer groups bằng evidence map, persona và journey.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

- **MEX-U03-01 → CP-U03-01, CP-U03-02:** mỗi checkpoint ghi material_example_refs = MEX-U03-01.

## Bối cảnh và increment

Học viên đóng vai Product Owner cùng Scrum Team thực hiện discovery workshop. Buyer muốn ít friction, warehouse cần order đủ dữ liệu, sponsor muốn scope nhìn thấy được. Nhóm phải tạo Product Goal dựa trên evidence, không biến stakeholder mạnh nhất hoặc một feature target thành Goal.

Lab tạo **M-U03-LAB Discovery Pack** gồm Product Goal card, stakeholder evidence map, evidence-based persona, customer journey, traceability và change-impact note. Artifact là input cho U04/REV-01/CAP-01.

NovaShop và mọi evidence card là **simulated**; không có PII, payment thật hay production claim.

## Điều kiện bắt đầu

### Starter assets

- starter/NovaShop_Project_Brief.md
- starter/NovaShop_Synthetic_Data.csv
- starter/Artifact_Templates.md
- Team Charter/Working Agreement baseline U02 hoặc bản giảng viên phát

Dùng Markdown editor CommonMark-compatible, spreadsheet CSV UTF-8 và whiteboard/paper. Tạo project-artifacts/M-U03/lab/U03_discovery_pack_working.md; không sửa starter.

### Evidence cards mới, khác MEX Material

| ID | Card | Status/limitation |
| --- | --- | --- |
| LAB-EV-U03-01 | 8/12 buyer sessions synthetic dừng ở account-creation step | observation; sample 12, không causal |
| LAB-EV-U03-02 | 5/12 guest-order cards thiếu ít nhất một address field kho vận cần | observation; sample 12 |
| LAB-EV-U03-03 | 7/10 warehouse users chọn đúng next action khi có validation summary | observation; sample 10 |
| LAB-TGT-U03-01 | Sponsor muốn “200 SKU online trước launch” | output target/assumption, không phải outcome evidence |

**Changed input cho CP-U03-02 — LAB-CR-U03:** sau workshop, sponsor yêu cầu đổi Product Goal thành “đưa 200 SKU online cuối Sprint tới”; đồng thời evidence card LAB-EV-U03-04 cho biết 11/12 buyer sessions tìm được một sản phẩm phù hợp trong catalog 50 SKU. Card này không tự chứng minh assortment tối ưu hoặc revenue.

### Constraints

- Goal chỉ đổi khi evidence/review trigger làm objective hiện tại không còn phù hợp; backlog/journey có thể adapt thường xuyên hơn.
- Chỉ dùng evidence synthetic, ghi denominator/confidence/limitation.
- Persona không có demographic stereotype hoặc quote giả.
- Product boundary giữ storefront-to-tracking; ERP, payment thật và mobile native ngoài scope.

## 📋 Lab outline và Definition of Done

1. CP-U03-01 và CP-U03-02 có evidence, MEX ref và kết luận PASS/REVISE.
2. Product Goal có future outcome, metric contract, boundary, assumptions/guardrails và ≥2 review triggers.
3. Ít nhất ba stakeholder groups có claim → evidence → confidence → implication/conflict.
4. Persona và journey không có attribute/pain point mồ côi.
5. Changed input có impact analysis/version diff; artifact mở được, traceability resolve và no-PII/secret.

## Checkpoint 0 — Baseline và safety check (10 phút)

### Numbered microsteps

1. **Why:** xác nhận evidence/provenance trước synthesis. **Action:** mở starter CSV và bốn Lab evidence cards; kiểm record IDs, numerator/denominator và nhãn observation/target. **Explanation:** count không có denominator hoặc status không rõ không thể dùng làm metric contract.
2. **Why:** giữ governance baseline. **Action:** mở U02 Charter/Agreement và ghi Product Owner accountability cùng consultation path vào metadata, không sao chép rules không liên quan. **Explanation:** stakeholder input không thay accountability.
3. **Why:** bảo vệ starter và dữ liệu. **Action:** tạo working file với LAB-U03-01, M-U03, simulated, material_example_refs = MEX-U03-01, data_policy = synthetic_only. **Explanation:** metadata là audit anchor.

### Verify

PASS khi ba starter files mở được, bốn Lab cards có denominator/status, U02 baseline hoặc limitation được ghi, working file tồn tại và starter không đổi.

### Expected result

PRECHECK-U03 = PASS; file working có section trống cho Goal, evidence map, persona, journey và traceability.

### Evidence

Lưu evidence/precheck_u03.md với source/card inventory và safety scan result.

### Troubleshooting

- Không thấy denominator → không tự suy ra; kiểm card hoặc đánh dấu unusable.
- U02 artifact thiếu → dùng baseline giảng viên và ghi dependency limitation.
- Có PII/secret → dừng, loại input và tạo lại từ synthetic starter.

### Reset/rollback

Tạo working copy mới từ template; giữ precheck evidence và xác nhận starter assets chưa đổi.

## Checkpoint 1 — Tạo Product Goal và discovery evidence chain (55 phút)

**Checkpoint ID:** CP-U03-01 · **material_example_refs:** MEX-U03-01 · **LO:** LO3.1, LO3.2

### Numbered microsteps

1. **Why:** tách evidence khỏi power/opinion. **Action:** tạo stakeholder evidence map cho buyer, warehouse và sponsor; được thêm Customer Service nếu có source. Mỗi dòng gồm need/decision, claim, evidence/status, confidence/limitation, implication và conflict. **Explanation:** LAB-TGT-U03-01 phải giữ nhãn output target.
2. **Why:** conflict cần quyết định minh bạch. **Action:** viết conflict card “fewer checkout fields ↔ valid address data” với evidence hai phía, guardrail và missing evidence. **Explanation:** không chọn một bên chỉ vì quyền lực.
3. **Why:** persona phải phản ánh behavior. **Action:** tạo một persona candidate chỉ từ evidence-backed goal, behavior, need, constraint và unknown; gắn source ID cho từng attribute. **Explanation:** nếu không có source, ghi assumption/research need hoặc loại.
4. **Why:** journey cần end-to-end context. **Action:** dựng các bước discover/evaluate → cart → account/checkout → address validation → confirmation/tracking; với mỗi bước ghi actor need/action, pain/evidence, handoff/risk và opportunity. **Explanation:** opportunity chưa phải solution/PBI.
5. **Why:** Goal phải định hướng nhưng không khóa feature. **Action:** viết Product Goal card gồm future state, primary metric/formula, baseline, target/time horizon, supporting signals, boundary, out-of-scope, assumptions, guardrails và ≥2 review triggers. **Explanation:** nếu evidence không cho baseline đáng tin, ghi measurement gap và condition to establish baseline thay vì bịa.
6. **Why:** kiểm alignment. **Action:** nối stakeholder implication/journey opportunity tới Goal hoặc ghi “không phục vụ Goal”; tạo trace table input → claim → Goal/journey field → oracle → downstream U04. **Explanation:** không có pain/opportunity mồ côi.

### Verify

| Check | PASS condition |
| --- | --- |
| Goal | outcome, formula/unit, baseline or explicit measurement gap, target/horizon, boundary, guardrail, ≥2 triggers |
| Stakeholders | ≥3 groups; mỗi claim có source/status/confidence/implication |
| Conflict | buyer/warehouse outcomes, evidence, guardrail và missing evidence rõ |
| Persona | mọi attribute resolve source/assumption; không stereotype |
| Journey | ≥5 steps, mỗi pain/opportunity resolve evidence/assumption và handoff |
| Traceability/safety | mọi link resolve; no PII/secret; simulated limitation |

### Expected result

CP-U03-01 = PASS khi Discovery Pack dùng input mới, không sao chép MEX, và reviewer có thể tái lập Goal cùng conflicts từ evidence. Goal chỉ có output “200 SKU” hoặc persona có demographic không nguồn làm REVISE.

### Evidence

- project-artifacts/M-U03/lab/U03_discovery_pack_working.md
- evidence/cp_u03_01_review.md
- input → claim → artifact → oracle trace table

### Troubleshooting

1. **Input hint:** claim không có source thì hạ thành assumption/research need.
2. **Metric hint:** tỷ lệ thiếu numerator/denominator/window phải REVISE.
3. **Persona hint:** xóa attribute nếu không thay decision hoặc không có evidence.
4. **Journey hint:** nếu chỉ có screens, quay lại actor need/pain/handoff.
5. **Goal hint:** nếu Goal chứa solution name, hỏi outcome còn lại khi bỏ solution đó.

### Reset/rollback

Giữ CP0 snapshot, tạo working copy mới và làm lại CP1. Không sửa Lab evidence cards hoặc starter.

## Checkpoint 2 — Đánh giá output request “200 SKU” (20 phút)

**Checkpoint ID:** CP-U03-02 · **material_example_refs:** MEX-U03-01 · **LO:** LO3.1, LO3.2 · **Changed input:** LAB-CR-U03 và LAB-EV-U03-04

### Numbered microsteps

1. **Why:** tránh đổi Goal chỉ vì request mới. **Action:** ghi change card, source/status và liệt kê Goal/metric/boundary/stakeholder/journey fields có thể bị ảnh hưởng. **Explanation:** output request và outcome evidence là hai loại input khác nhau.
2. **Why:** kiểm review trigger. **Action:** so LAB-CR-U03/LAB-EV-U03-04 với từng trigger đã đặt; ghi fired/not fired/insufficient evidence kèm rationale. **Explanation:** decision có thể giữ, adapt hoặc abandon Goal, nhưng phải theo oracle, không theo đáp án định sẵn.
3. **Why:** cân nhắc options/trade-off. **Action:** nêu ít nhất hai dispositions cho “200 SKU” như backlog option, experiment/input target hoặc Goal change; đánh giá value evidence, cost, risk và boundary. **Explanation:** số SKU có thể là output proxy nhưng không tự chứng minh future state.
4. **Why:** giữ downstream consistency. **Action:** version các field thực sự đổi, cập nhật evidence map/journey/traceability và ghi unchanged fields. **Explanation:** change local không được làm mất source/oracle downstream.

### Verify

- Change card và EV-04 được gắn status/limitation.
- Từng review trigger có conclusion/evidence.
- Có ≥2 options và trade-off; không tuyên bố 50/200 SKU là market proof.
- Product Goal decision có owner/rationale; downstream sections/diff nhất quán.
- No-PII/secret và simulated disclosure vẫn hiện rõ.

### Expected result

CP-U03-02 = PASS khi reviewer thấy rõ evidence mới có hoặc không kích hoạt Goal review và mọi adaptation nhất quán. “Sponsor yêu cầu nên Goal đổi” hoặc “11/12 nên 50 SKU chắc chắn đủ” đều là REVISE.

### Evidence

- evidence/cp_u03_02_impact.md
- before/after diff của Discovery Pack
- self-check PASS/REVISE với finding owner

### Troubleshooting

- Không biết trigger có fire → đọc exact trigger và hỏi input mới có thay future objective/measure/boundary không.
- Output bị coi là outcome → viết lại actor/result độc lập với số feature.
- Journey/trace mất link → lần từ change ID tới affected fields; rollback phần không resolve.

### Reset/rollback

Khôi phục CP1, áp change trên working copy mới và xác nhận CP1 evidence/starter không đổi.

## 🧪 Final validation

**Thời lượng:** 5 phút.

Reviewer độc lập:

1. kiểm CP0/CP1/CP2, Goal oracle, ≥3 stakeholder chains, persona/journey và traceability;
2. kiểm changed input/diff và data safety;
3. ghi LAB-U03-PASS chỉ khi toàn bộ DoD đạt; ngược lại ghi REVISE, exact evidence gap và owner.

Exit condition: Goal cùng discovery artifacts tái lập được từ evidence, changed input xử lý nhất quán và không có unsupported claim.

## Deliverables và tái sử dụng

- U03_discovery_pack_working.md;
- cp_u03_01_review.md;
- cp_u03_02_impact.md;
- final evidence checklist và trace table.

Giữ Product Goal card, stakeholder map và journey cho U04 story mapping, REV-01 và CAP-01. Không biến opportunity thành PBI trước khi U04.

## ♻️ Reset, cleanup và khả năng chạy lại

Không có service/credential. Giữ bản PASS; archive working draft theo quy ước lớp. Chạy lại bằng working copy mới từ starter, không ghi đè bản PASS hoặc sửa starter. Xác nhận no-PII/secret scan và internal links sau reset.

## Nguồn và provenance

### Nguồn đã map

- SRC-SG20 — The Scrum Guide: https://scrumguides.org/scrum-guide.html (publisher: Ken Schwaber, Jeff Sutherland / ScrumGuides.org; version: November 2020; accessed_at: 2026-08-25; license: CC BY-SA 4.0; allowed_use: adapt)
- SRC-EBM24 — Evidence-Based Management Guide: https://www.scrum.org/resources/online-evidence-based-management-guide (publisher: Scrum.org; version: May 2024; accessed_at: 2026-08-25; license: CC BY-SA 4.0; allowed_use: adapt)
- SRC-AP01 — Principles behind the Agile Manifesto: https://agilemanifesto.org/principles.html (publisher: Agile Manifesto authors; version: 2001; accessed_at: 2026-08-25; license: reference-only; allowed_use: reference)
- SRC-PROJECT — NovaShop simulated e-commerce project brief: starter/NovaShop_Project_Brief.md (publisher: Training artifact created for this course; version: 1.0; accessed_at: 2026-08-25; license: internal approved; allowed_use: internal_approved)

### Phần bổ sung/suy diễn

- [SUY DIỄN — từ kiến thức đã huấn luyện] LAB evidence cards, change card, thresholds và professional-artifact format là synthetic instructional design.

> **Chính sách lời giải:** Lab có hướng dẫn giảm dần và pass-fail oracle, không chứa reference solution của Assignment khác.

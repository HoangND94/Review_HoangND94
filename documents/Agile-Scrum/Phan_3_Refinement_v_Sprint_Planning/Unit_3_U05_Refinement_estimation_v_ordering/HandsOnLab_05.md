# Hands-on Lab LAB-U05-01 — Refinement và Planning Poker với change request

| Thuộc tính | Giá trị |
| --- | --- |
| Hình thức | guided_with_fading |
| Thời lượng | 90 phút |
| Độ khó | medium |
| Xác thực | simulated |
| Validation | artifact_review |

## 🎯 Learning Outcomes được thực hành

- **LO5.1:** tạo relative sizing record có reference, assumptions, dispersion, uncertainty.
- **LO5.2:** tạo Product Backlog v2 có order dựa trên value/risk/dependency/learning và review trigger.
- **material_example_refs:** **MEX-U05-01** tại CP-U05-01 và CP-U05-02. Lab đổi sang inventory scenario, vote set và dependency constraint mới; học viên không copy payment artifact trong Material.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

- **MEX-U05-01 → LAB-U05-01/CP-U05-01:** LO5.1, LO5.2; evidence là sizing record, vote rounds và trace assumptions.
- **MEX-U05-01 → LAB-U05-01/CP-U05-02:** LO5.1, LO5.2; evidence là dependency map, ordered backlog và impact note.

## 🧭 Scenario và project slice

Product Backlog v1 của Lab có ba outcome:

- `LAB-INV-01`: người mua thấy stock status cùng catalog result;
- `LAB-INV-02`: người mua không thêm được số lượng vượt stock snapshot;
- `LAB-INV-03`: admin cập nhật stock synthetic và có audit evidence.

Reference `LAB-REF-SEARCH=3` là PBI tìm một SKU theo từ khóa, đã đạt cùng DoD. Vote vòng đầu do facilitator cung cấp:

| PBI | Votes |
| --- | --- |
| LAB-INV-01 | 3, 5, 5, 8 |
| LAB-INV-02 | 5, 8, 13, 8 |
| LAB-INV-03 | 3, 8, 13, 13 |

Change card cho CP2: inventory sandbox đồng bộ mỗi 30 phút, **không giữ chỗ stock**, và chỉ admin update mới phát audit event. Constraints: không đổi point sang giờ; không dùng vote để đánh giá cá nhân; Product Goal/DoD giữ nguyên; mọi dependency phải ghi hard/soft/assumed cùng evidence/owner.

## 🧰 Điều kiện bắt đầu

Hoàn thành U04 và đọc MEX-U05-01. Mở ba starter assets; tạo bản làm việc:

- `project-artifacts/M-U05/lab/U05_lab_sizing-record.md`
- `project-artifacts/M-U05/lab/U05_lab_product-backlog-v2.md`
- `project-artifacts/M-U05/lab/U05_lab_evidence.md`

ENV-PRO-ARTIFACT dùng Markdown, CSV UTF-8 và whiteboard/paper; không có service/credential. Starter assets luôn chỉ đọc.

## 📋 Lab outline và Definition of Done

CP-U05-01/02 đều PASS; 3/3 PBI có readiness gap, vote history, extreme rationale, final size hoặc trạng thái “chưa size”, uncertainty/trigger; Product Backlog v2 có một order rõ và bốn chiều evidence; change card cập nhật cả size assumption lẫn order impact; không có conversion point–time/productivity claim; evidence và reset có thể review.

## Checkpoint 0 — Baseline và safety

### Numbered microsteps

1. **Why:** bảo vệ baseline. **Action:** tạo ba file làm việc, ghi `authenticity: simulated`, source PBI/votes và hash logic `baseline-v1`; không sửa starter hoặc output U04 chính thức. **Giải thích:** sizing cần giữ được trạng thái trước/sau để audit learning.
2. **Why:** xác nhận thước so. **Action:** ghi reference `LAB-REF-SEARCH=3`, Definition of Done dùng chung và câu “size là relative/team-local, không phải giờ”. **Giải thích:** reference khác DoD làm so sánh vô nghĩa.
3. **Why:** tách dữ kiện với assumption. **Action:** lập hai cột “known” và “unknown” cho ba PBI trước khi nhìn votes. **Giải thích:** điều này ngăn số vote biến assumption thành fact.

### Verify

Ba file mở được; reference/DoD/statement có mặt; vote data chưa bị sửa; starter assets không đổi; known/unknown không để trống cho PBI nào.

### Expected result

Baseline có thể chạy lại và reviewer phân biệt input cung cấp với quyết định của nhóm.

### Evidence

Ghi mục `CP0` trong evidence file với version, source IDs, reference check và kết luận PASS/REVISE.

### Troubleshooting

Nếu PBI thiếu criteria từ U04, ghi readiness gap thay vì tự bịa; nếu reference không cùng DoD, chọn lại reference đã cung cấp; nếu votes đã bị discussion sửa, lấy lại vote table gốc.

### Reset/rollback

Giữ file CP0 chỉ đọc; tạo bản sao `working-cp1`. Reset thành công khi vote table khớp input và không có final estimate/order.

## Checkpoint 1 — CP-U05-01: Refine và size backlog biến thể

**material_example_refs:** MEX-U05-01 · **LO:** LO5.1, LO5.2

### Numbered microsteps

1. **Why:** xác nhận PBI đủ để thảo luận. **Action:** với từng PBI, ghi actor/outcome, acceptance boundary, readiness gap và open question. **Giải thích:** không size một nhãn work chưa có outcome/boundary.
2. **Why:** dùng dispersion làm tín hiệu. **Action:** chép votes đúng thứ tự; tính `min/max` nhưng không tính trung bình; chọn người ở hai extreme để ghi mỗi bên một assumption/evidence. **Giải thích:** extremes lộ khác biệt mental model.
3. **Why:** cập nhật hiểu biết trước re-vote. **Action:** quyết định clarification nào thuộc PBI, điều nào để later, điều nào blocking. Ghi trade-off và owner cho open question. **Giải thích:** refinement thay artifact dựa trên conversation.
4. **Why:** tạo estimate trung thực. **Action:** thực hiện vòng vote thứ hai độc lập trong nhóm; ghi nguyên votes. Chọn final relative size khi assumptions đã hội tụ, hoặc ghi `?` cùng learning action nếu còn blocking. **Giải thích:** consensus bị ép không phải evidence.
5. **Why:** chuẩn bị ordering. **Action:** thêm cho từng PBI bốn trường value, risk, dependency, learning value nhưng chưa quyết định order cuối. **Giải thích:** size không thay thế các yếu tố này.

### Verify

Artifact review CP-U05-01:

1. 3/3 PBI có outcome/boundary/readiness gap;
2. vote vòng 1 và 2, extreme rationale, clarification được lưu;
3. final size hoặc `?` có reference, uncertainty và trigger;
4. không có average-as-answer, conversion point–hour hoặc tên cá nhân gắn performance;
5. bốn trường ordering có evidence cụ thể, không chỉ “high/medium” không lý do.

### Expected result

Sizing record đủ để người ngoài giải thích vì sao estimate đổi hoặc chưa thể chốt. Product Backlog working copy đã có dữ kiện ordering nhưng chưa nhận change card CP2.

### Evidence

Lưu `sizing-record-cp1`, ảnh/bảng reveal hai vòng, trace `PBI → assumption → clarification → final/trigger`, và checklist PASS/REVISE.

### Troubleshooting

- Nếu mọi vote giống nhau ngay vòng 1, mỗi người viết assumption trước khi reveal lại; không yêu cầu đổi số giả tạo.
- Nếu disagreement là scope, quay lại acceptance boundary; nếu là contract chưa biết, ghi learning action.
- Nếu nhóm muốn đổi point thành ngày, quay lại reference/DoD và xóa conversion khỏi artifact.

### Reset/rollback

Tạo bản mới từ CP0 và chạy lại reveal; giữ evidence CP1 cũ để so learning, không ghi đè. Xác nhận reset khi final size/order không còn nhưng input votes vẫn nguyên.

## Checkpoint 2 — CP-U05-02: Reorder khi inventory dependency đổi

**material_example_refs:** MEX-U05-01 · **LO:** LO5.1, LO5.2 · **changed constraint:** sync 30 phút, no reservation, audit event chỉ từ admin update.

### Numbered microsteps

1. **Why:** phân tích impact trước quyết định. **Action:** ghi change card và lập bảng `assumption/size/order field affected` cho từng PBI. **Giải thích:** dependency mới có thể đổi uncertainty mà không nhất thiết đổi mọi size.
2. **Why:** tránh dependency giả. **Action:** phân loại mỗi quan hệ là hard, soft hoặc assumed; gắn evidence từ change card và một owner/review trigger. **Giải thích:** “có liên quan” không đồng nghĩa “phải làm trước”.
3. **Why:** làm visible trade-off. **Action:** so ít nhất hai order candidate. Với mỗi candidate, nêu value được mở, risk exposure, dependency feasibility và learning thu được; không dùng tổng điểm duy nhất. **Giải thích:** alternative cho thấy rationale thực sự quyết định.
4. **Why:** tạo Product Backlog v2. **Action:** Product Owner role chọn một order, ghi rationale cho từng vị trí và trigger có thể đảo order. Nếu size assumption bị phá, đánh dấu item cần re-refine thay vì tự thay số. **Giải thích:** order là quyết định accountable và emergent.
5. **Why:** kiểm downstream. **Action:** ghi impact note cho U06: dependency/risk nào phải xuất hiện khi Sprint Planning, và item nào chưa đủ evidence để forecast. **Giải thích:** M-U05 phải tạo input dùng được, không chỉ bảng chấm điểm.

### Verify

CP-U05-02 PASS khi: impact table phủ 3/3 PBI; dependency có type/evidence/owner; có ít nhất hai order option và trade-off; Product Backlog v2 có một order duy nhất, rationale/trigger từng item; size không bị sửa vô căn cứ; impact note nói rõ input cho U06; không dùng velocity/team comparison.

### Expected result

Change request được xử lý nhất quán. Reviewer biết inventory sync/no-reservation ảnh hưởng PBI nào, tại sao order được chọn, điều gì làm order đổi và uncertainty nào chuyển sang Sprint Planning.

### Evidence

Lưu diff `cp1 → cp2`, dependency map, hai candidate order, Product Backlog v2, impact note và review record.

### Troubleshooting

- Nếu mọi dependency được gọi hard, thử bỏ item trước và hỏi outcome sau có còn kiểm được không; nếu có, quan hệ có thể soft/assumed.
- Nếu rationale chỉ lặp “value cao”, yêu cầu evidence/Goal link và risk/learning counterweight.
- Nếu change card làm criteria không còn đúng, đưa PBI về refinement; không sửa size/order mà giữ artifact cũ.

### Reset/rollback

Khôi phục working copy từ CP1, bỏ change card/impact/order CP2, giữ sizing record đã PASS. Reset đúng khi order chưa được chọn và bốn trường pre-change còn nguyên.

## 🧪 Final validation

Reviewer chạy toàn bộ oracle từ bản sao CP0 theo thứ tự CP1 → CP2. Exit condition: hai checkpoint PASS; artifact mở được; traceability resolve; không có dữ liệu thật; starter assets không đổi. Nếu dependency hoặc assumption thay đổi, chạy lại cả sizing impact và ordering review thay vì chỉ sửa một cell.

## 📦 Bằng chứng và deliverables

- **Artifact Lab:** Sizing record và Product Backlog v2 sau CP-U05-02.
- **Traceability table:** `PBI → assumption → clarification → size/order → evidence`.
- **Evidence checklist:** CP-U05-01/02 review, before/after và reset result.
- `U05_lab_sizing-record.md`: votes, rationale, size/uncertainty.
- `U05_lab_product-backlog-v2.md`: evidence bốn chiều, order, trigger, impact note.
- `U05_lab_evidence.md`: before/after, dependency map, reviews.

Giữ Sizing record và Product Backlog v2 để **REV-01**, **CAP-01** và làm practice baseline cho U06. Không có Assignment U05; output đánh giá chuỗi tiếp theo là ASM-U06, vốn dùng Product Backlog artifacts theo project link.

Không có service/credential. Cleanup chỉ chuyển bản thử lỗi vào `discarded/` trong `project-artifacts/M-U05/lab/`, giữ bản final/evidence và xác nhận starter assets không đổi. Không xóa rộng hoặc ghi đè output U04.

## ♻️ Reset, cleanup và khả năng chạy lại

Reset từng checkpoint theo phần tương ứng. Cleanup chỉ tác động các bản làm việc trong `project-artifacts/M-U05/lab/`; giữ final/evidence, chuyển bản thử lỗi vào `discarded/`, rồi xác nhận starter assets và output U04 không đổi. Không có service hoặc credential cần thu hồi.

## 🔐 Chính sách lời giải

Learner Lab chỉ có hướng dẫn giảm dần và oracle; không chứa reference solution của Assignment. U05 không có assessment độc lập; artifact được giữ làm practice evidence cho U06/REV-01/CAP-01.

## 📚 Provenance

- **SRC-SG20:** Scrum Guide, November 2020, ScrumGuides.org, accessed 2026-08-25, CC BY-SA 4.0, adapt.
- **SRC-BACKLOG:** Scrum.org Product Backlog, living snapshot/accessed 2026-08-25, website terms, reference.
- **SRC-PLANNING-POKER:** Agile Alliance Planning Poker, living snapshot/accessed 2026-08-25, website terms, reference.
- **SRC-FORECAST:** Scrum.org Forecasting and Release Planning, living snapshot/accessed 2026-08-25, website terms, reference.

Votes, PBI và constraint inventory là simulated course data; không phải benchmark/team data. Không dùng nguồn bổ sung.

---
<!-- QUALITY GATE: MEX-U05-01 resolve ở hai CP; đủ microsteps/Verify/Expected/Evidence/Troubleshooting/Reset; changed input; no Assignment solution. -->

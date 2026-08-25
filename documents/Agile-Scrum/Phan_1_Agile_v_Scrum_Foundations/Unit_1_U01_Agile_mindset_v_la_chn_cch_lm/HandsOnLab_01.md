# Hands-on Lab LAB-U01-01 — Chẩn đoán cách làm cho NovaShop

| Thuộc tính | Giá trị |
| --- | --- |
| Hình thức | guided_with_fading |
| Thời lượng | 60 phút |
| Độ khó | medium |
| Mức xác thực | simulated |
| Validation | artifact_review |

## 🎯 Learning Outcomes được thực hành

- **LO1.1:** phân loại ít nhất 4/5 work item bằng uncertainty, feedback và cost-of-change.
- **LO1.2:** viết hai value hypothesis có oracle và adaptation rule.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

- **MEX-U01-01 → CP-U01-01, CP-U01-02:** cả hai checkpoint ghi material_example_refs = MEX-U01-01 và tạo evidence riêng.

## Bối cảnh và project increment

Học viên đóng vai Scrum Team tư vấn cho sponsor trước khi lập backlog NovaShop. Baseline chỉ có project brief và synthetic observations. Lab tạo **M-U01-LAB Decision Pack** gồm decision canvas, hai value hypotheses, traceability table và impact note. Artifact dùng lại tư duy của MEX-U01-01 nhưng dùng input khác; không sao chép checkout artifact trong Material.

NovaShop và mọi record dưới đây là **simulated**. Không dùng PII, tiền thật, endpoint hay credential production.

## Điều kiện bắt đầu

### Starter assets

- starter/NovaShop_Project_Brief.md
- starter/NovaShop_Synthetic_Data.csv
- starter/Artifact_Templates.md

Tạo bản làm việc dưới project-artifacts/M-U01/lab/. Giữ nguyên starter asset. Công cụ: Markdown editor CommonMark-compatible và spreadsheet đọc CSV UTF-8.

### Input mới của Lab

Năm work item cần chẩn đoán:

| ID | Work item | Input/constraint mới so với Material |
| --- | --- | --- |
| WI-L01 | Bộ lọc catalog theo loại da | Không có observation; có thể test bằng prototype synthetic |
| WI-L02 | Export đơn theo schema shipping sandbox v1 | Contract trường và oracle đã ổn định |
| WI-L03 | Tự phục vụ trạng thái đơn | OBS-04 = 6/15 yêu cầu hỗ trợ hỏi trạng thái |
| WI-L04 | Lưu payment card | Bị cấm bởi product boundary/data policy |
| WI-L05 | Validation địa chỉ | OBS-02 = 4/12 đơn cần nhập lại; oracle FR-03 đã có |

**Changed input cho CP-U01-02 — LAB-CR-U01:** từ ngày review, shipping sandbox thông báo schema v1 sẽ thay bằng hai candidate schema chưa chốt trong vòng kế tiếp; sponsor vẫn yêu cầu export hoàn tất ngay. Đây là change card synthetic dành riêng cho Lab.

### Ràng buộc

- Chỉ dùng data synthetic và sandbox.
- Mọi quyết định có source ID, rationale, counter-example và evidence cần thu.
- Không biến “cấm lưu thẻ” thành một experiment.
- Không thay Product Goal; Unit này chỉ tạo quyết định/hypothesis đầu vào.

## 📋 Lab outline và Definition of Done

1. CP-U01-01 và CP-U01-02 đều có artifact, evidence và kết luận PASS/REVISE.
2. Ít nhất 4/5 classification khớp oracle của Lab và mọi dòng đều có rationale, không chỉ nhãn.
3. Hai hypothesis đủ outcome, signal, baseline, threshold, timebox, guardrail và adaptation.
4. Impact note chỉ ra chính xác các trường bị đổi sau LAB-CR-U01.
5. File mở được, ID/link nội bộ resolve, không PII/secret; reset được mà starter asset không đổi.

## Checkpoint 0 — Baseline và safety check (8 phút)

### Numbered microsteps

1. **Why:** tránh tạo artifact từ file thiếu hoặc dữ liệu ngoài phạm vi. **Action:** mở ba starter asset, kiểm CSV có OBS-01 đến OBS-04 và các cột record_type đến notes. **Explanation:** record ID là anchor để reviewer truy vết, không phải nội dung cần chép toàn bộ.
2. **Why:** bảo vệ baseline. **Action:** tạo project-artifacts/M-U01/lab/U01_decision_pack_working.md từ các trường Decision record và Value hypothesis; không sửa file template. **Explanation:** bản làm việc tách evidence của học viên khỏi nguồn phát hành.
3. **Why:** thiết lập oracle trước khi quyết định. **Action:** thêm metadata Lab ID, learner/team ID giả, timestamp review, material_example_refs = MEX-U01-01 và data_policy = synthetic_only. **Explanation:** metadata làm evidence có thể audit mà không cần PII.

### Verify

Kiểm bằng checklist:

- ba starter asset mở được;
- OBS-02 và OBS-04 đọc được với denominator;
- file làm việc tồn tại và starter asset không có diff;
- metadata có Lab ID, MEX ref và data policy.

### Expected result

PRECHECK-U01 = PASS và một file làm việc trống có đủ trường, chưa có quyết định mẫu.

### Evidence

Lưu evidence/precheck_u01.md gồm tên file, record IDs đã thấy và bốn kết quả PASS/FAIL. Không chụp dữ liệu ngoài workspace.

### Troubleshooting

- **Không thấy OBS-04 →** có thể mở sai encoding/file; kiểm header và chọn UTF-8. Nếu vẫn thiếu, dùng lại starter file, không tự bịa record.
- **Template bị sửa →** so với bản starter và chuyển nội dung sang file working mới.
- **CSV có PII →** dừng Lab, đánh dấu SAFETY-FAIL và báo giảng viên.

### Reset/rollback

Đóng bản working lỗi và tạo bản mới từ template. Xác nhận ba starter asset giữ nguyên timestamp/content; không xóa thư mục rộng.

## Checkpoint 1 — Phân loại năm work item và tạo hai hypothesis (32 phút)

**Checkpoint ID:** CP-U01-01 · **material_example_refs:** MEX-U01-01 · **LO:** LO1.1, LO1.2

### Numbered microsteps

1. **Why:** một nhãn không chứng minh lựa chọn. **Action:** tạo bảng cho WI-L01…WI-L05 với các cột evidence, uncertainty nhu cầu, uncertainty giải pháp, feedback availability, reversibility/cost, approach, rationale và counter-example. **Explanation:** bảy cột đầu là cơ chế ra quyết định; approach chỉ là kết luận.
2. **Why:** ngăn assumption biến thành fact. **Action:** với mỗi dòng, gắn input là observation, contract, constraint hoặc unknown; dùng đúng OBS/FR/CON ID khi có. **Explanation:** độ mạnh của evidence quyết định mức confidence.
3. **Why:** xử lý ranh giới an toàn. **Action:** đánh dấu WI-L04 là prohibited/out-of-scope và ghi phương án an toàn “payment sandbox status card”; không chấm nó như một experiment. **Explanation:** Agile không cho phép bỏ qua data policy.
4. **Why:** kiểm transfer từ MEX. **Action:** tự chọn approach cho bốn work item còn lại, nêu feedback window và một counter-example. **Explanation:** một hạng mục có thể tách phần ổn định và phần adaptive.
5. **Why:** biến hai uncertainty thành quyết định kiểm chứng được. **Action:** chọn hai work item có uncertainty thực sự; điền hai value hypothesis theo mẫu actor/outcome, change, signal/đơn vị, baseline, threshold/timebox, guardrail, continue/adjust/stop. **Explanation:** không dùng output “xây tính năng” làm outcome.
6. **Why:** tạo traceability. **Action:** thêm bảng input ID → decision ID → hypothesis ID → oracle → downstream consumer U03/CAP-01. **Explanation:** reviewer phải tái lập được đường đi mà không hỏi tác giả.

### Verify

Artifact review theo oracle CP-U01-01:

| Check | PASS condition |
| --- | --- |
| Classification | Ít nhất 4/5 dòng phù hợp: WI-L02 có contract-driven element; WI-L04 prohibited; WI-L01/WI-L03 chứa adaptive discovery; WI-L05 tách contract validation với uncertainty cải tiến |
| Rationale | 5/5 dòng có uncertainty, feedback/cost và counter-example hoặc lý do prohibited |
| Hypotheses | 2/2 đủ tám trường bắt buộc và dùng input khác MEX checkout |
| Traceability | Mọi decision/hypothesis có input ID và oracle |
| Safety | Không PII/secret/claim production |

### Expected result

CP-U01-01 = PASS khi artifact đủ trường, dùng dataset/order-tracking/catalog/shipping inputs mới và reviewer phân loại đúng ít nhất 4/5 theo cơ chế. Nếu đúng nhãn nhưng thiếu rationale, kết quả vẫn là REVISE.

### Evidence

- project-artifacts/M-U01/lab/U01_decision_pack_working.md
- evidence/cp_u01_01_review.md
- bảng trace input → decision → hypothesis → oracle

### Troubleshooting

1. **Input hint:** nếu không chọn được approach, kiểm lại loại input: observation, contract, constraint hay unknown.
2. **State hint:** nếu mọi dòng giống nhau, kiểm feedback availability và reversibility từng work item.
3. **Contract hint:** nếu hypothesis thiếu quyết định, tìm threshold, guardrail và nhánh adjust.
4. Không dùng bảng đáp án trong phần Verify làm rationale; mỗi dòng phải viện dẫn input riêng.

### Reset/rollback

Lưu bản CP0, sao chép nó thành một working file mới rồi thực hiện lại CP1. Không xóa evidence CP0 hoặc sửa starter assets.

## Checkpoint 2 — Thích nghi khi shipping contract trở nên bất định (15 phút)

**Checkpoint ID:** CP-U01-02 · **material_example_refs:** MEX-U01-01 · **LO:** LO1.1, LO1.2 · **Changed input:** LAB-CR-U01

### Numbered microsteps

1. **Why:** adaptation chỉ hợp lệ khi input/constraint thay đổi. **Action:** ghi LAB-CR-U01 vào impact note và liệt kê decision/hypothesis/oracle nào phụ thuộc shipping schema v1. **Explanation:** impact analysis trước sửa ngăn thay đổi lan truyền vô hình.
2. **Why:** giữ phần ổn định không bị phá. **Action:** đánh dấu các field vẫn cố định, gồm synthetic-only, không PII và mục tiêu export; chỉ mở lại các giả định liên quan schema. **Explanation:** inspect-and-adapt không có nghĩa làm lại toàn bộ artifact.
3. **Why:** phản ánh uncertainty mới. **Action:** cập nhật dòng WI-L02 với candidate options, feedback cần thu, reversibility/cost và review trigger; nếu cần, tạo một hypothesis mới hoặc sửa hypothesis liên quan, nhưng phải ghi version/diff. **Explanation:** choice phải dựa trên trạng thái mới, không bảo vệ kết luận cũ.
4. **Why:** kiểm tính nhất quán. **Action:** cập nhật traceability và viết trade-off giữa chờ contract chốt, tạo adapter/prototype sandbox hoặc khóa schema v1 tạm thời. **Explanation:** Lab không quy định một option duy nhất; oracle đánh giá rationale và evidence.

### Verify

Review theo checklist:

- change card có source ID và timestamp;
- impact note nêu phần changed/unchanged;
- decision mới có ít nhất hai option, trade-off và trigger;
- hypothesis/oracle liên quan được version hóa;
- no-PII/secret vẫn PASS.

### Expected result

CP-U01-02 = PASS khi change request được xử lý nhất quán, không còn claim “schema ổn định”, và reviewer thấy rõ vì sao approach/feedback plan thay đổi hoặc được giữ. Một lựa chọn khác oracle mẫu vẫn PASS nếu evidence và trade-off thỏa contract.

### Evidence

- evidence/cp_u01_02_impact.md
- diff trước/sau của decision pack
- self-check có kết luận PASS hoặc REVISE và owner sửa finding

### Troubleshooting

- **Không biết phần nào đổi →** lần theo trace table từ WI-L02.
- **Đổi cả Product Goal →** vượt scope; rollback phần Goal và chỉ cập nhật decision/hypothesis.
- **Có hai option nhưng không chọn được →** ghi missing evidence và trigger; trạng thái INCONCLUSIVE trung thực tốt hơn kết luận giả.

### Reset/rollback

Khôi phục bản CP1, áp dụng lại LAB-CR-U01 theo một working copy mới và xác nhận CP1 evidence không đổi. Không xóa starter hoặc artifact đã review.

## 🧪 Final validation

**Thời lượng:** 5 phút.

Từ bản working sạch:

1. Reviewer độc lập chạy checklist DoD và ghi từng evidence path.
2. Nếu CP0, CP1, CP2 và safety đều PASS, đổi trạng thái artifact thành LAB-U01-PASS.
3. Nếu có một check FAIL, trạng thái là REVISE; ghi finding, owner và check cần chạy lại. Không tự khai PASS.

Exit condition: hai checkpoint có evidence, changed input được xử lý, traceability resolve và không có PII/secret. Expected output là một decision pack cùng checklist PASS/REVISE rõ ràng.

## Deliverables và tái sử dụng

- U01_decision_pack_working.md: decision canvas và hai hypotheses.
- cp_u01_01_review.md: classification/hypothesis evidence.
- cp_u01_02_impact.md: change diff và trade-off.
- traceability table và final checklist.

Giữ problem/decision canvas cùng hypothesis register cho U03 discovery và CAP-01. Review REV-01 có thể dùng rationale làm context, nhưng không coi target synthetic là kết quả thực tế.

## ♻️ Reset, cleanup và khả năng chạy lại

Không có dịch vụ hoặc credential cần thu hồi. Đóng editor, giữ deliverables đã PASS, chuyển bản nháp lỗi sang thư mục working/archive nếu quy ước lớp cho phép. Để chạy lại, tạo file working mới từ starter; không ghi đè bản PASS. Xác nhận starter asset vẫn mở được và không thay đổi.

## Nguồn và provenance

### Nguồn đã map

- SRC-AM01 — Manifesto for Agile Software Development: https://agilemanifesto.org/ (publisher: Agile Manifesto authors; version: 2001; accessed_at: 2026-08-25; license: may be copied only in its entirety with notice; allowed_use: reference)
- SRC-AP01 — Principles behind the Agile Manifesto: https://agilemanifesto.org/principles.html (publisher: Agile Manifesto authors; version: 2001; accessed_at: 2026-08-25; license: reference-only; allowed_use: reference)
- SRC-SG20 — The Scrum Guide: https://scrumguides.org/scrum-guide.html (publisher: Ken Schwaber, Jeff Sutherland / ScrumGuides.org; version: November 2020; accessed_at: 2026-08-25; license: CC BY-SA 4.0; allowed_use: adapt)
- SRC-PROJECT — NovaShop simulated e-commerce project brief: starter/NovaShop_Project_Brief.md (publisher: Training artifact created for this course; version: 1.0; accessed_at: 2026-08-25; license: internal approved; allowed_use: internal_approved)

### Phần bổ sung/suy diễn

- [SUY DIỄN — từ kiến thức đã huấn luyện] WI-L01…WI-L05, LAB-CR-U01 và oracle phân loại là thiết kế sư phạm synthetic.

> **Chính sách lời giải:** Lab cung cấp trường, oracle và hint giảm dần; không cung cấp reference solution cho Assignment. Toàn bộ dữ liệu là simulated.

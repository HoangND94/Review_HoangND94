# Hands-on Lab LAB-U02-01 — Thiết lập Scrum Team và mô phỏng chu kỳ sự kiện

| Thuộc tính | Giá trị |
| --- | --- |
| Hình thức | guided_with_fading |
| Thời lượng | 75 phút |
| Độ khó | medium |
| Mức xác thực | simulated |
| Validation | artifact_review |

## 🎯 Learning Outcomes được thực hành

- **LO2.1:** map accountabilities, values, events, artifacts và commitments với độ chính xác ít nhất 80%.
- **LO2.2:** tạo Team Charter/Working Agreement có quyền quyết định và rule kiểm chứng được.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

- **MEX-U02-01 → CP-U02-01, CP-U02-02:** mỗi checkpoint ghi material_example_refs = MEX-U02-01.

## Bối cảnh và increment

NovaShop đang có một operating model giả lập bị lỗi: “Product Council” gồm ba người cùng giữ quyền Product Owner; Delivery Manager giao task và thu ba câu báo cáo tại Daily Scrum; Sprint Review được gọi là buổi ký nghiệm thu. Học viên đóng vai Scrum Team, chẩn đoán và sửa mô hình mà vẫn cung cấp transparency cho sponsor.

Lab tạo milestone **M-U02-LAB**: operating model map, Team Charter, Working Agreement, event/artifact map và impact note. Đây là thực hành có hướng dẫn; không phải lời giải của ASM-U02. Mọi nhân vật/evidence đều synthetic, không dùng PII hoặc credential.

## Điều kiện bắt đầu

### Starter assets và smoke check

- starter/NovaShop_Project_Brief.md
- starter/NovaShop_Synthetic_Data.csv
- starter/Artifact_Templates.md
- U01 decision/hypothesis artifact hoặc baseline do giảng viên phát

Tạo project-artifacts/M-U02/lab/U02_operating_model_working.md. Mở template Team Charter/Working Agreement; không sửa starter.

### Baseline cards khác MEX Material

| ID | Flawed statement |
| --- | --- |
| FL-U02-01 | Sales Lead, Operations Lead và Product Lead đều là Product Owner và mỗi người có veto |
| FL-U02-02 | Scrum Master chia task đầu ngày và duyệt hoàn thành |
| FL-U02-03 | Daily Scrum: từng cá nhân báo hôm qua/hôm nay/blocker cho Delivery Manager trong 30 phút |
| FL-U02-04 | Sprint Review chỉ là demo và ký Done |
| FL-U02-05 | Product Backlog gắn Sprint Goal; Sprint Backlog gắn Product Goal |
| NEED-U02-01 | Sponsor cần weekly risk visibility và biết ai xử lý impediment |

**Changed input cho CP-U02-02 — LAB-CR-U02:** Security/Accessibility reviewer yêu cầu quyền veto mọi technical decision, tham dự Daily để phê duyệt task, và đòi giữ bằng chứng quality trong phạm vi requirement được chọn. Requirement về quality evidence là hợp lệ; cách phân quyền đề xuất chưa được chấp nhận sẵn.

### Constraints

- Không bỏ hoặc đổi bản chất accountabilities, events, artifacts và commitments của Scrum.
- Không tạo hierarchy trong Scrum Team.
- Có thể dùng Team Charter, Working Agreement, risk digest và decision record như practices bổ trợ.
- Không hạ Definition of Done hoặc gọi work chưa Done là Increment.

## 📋 Lab outline và Definition of Done

1. CP-U02-01 và CP-U02-02 có evidence riêng, material_example_refs đúng và reviewer conclusion.
2. Operating model đạt ít nhất 80% mapping cards, không có critical Scrum error.
3. Team Charter có decision rights; Working Agreement có trigger, behavior, owner, evidence và inspection date.
4. Changed input được triage thành nhu cầu hợp lệ, proposal không hợp lệ và adaptation phù hợp; downstream map nhất quán.
5. File mở được, ID/link resolve, no-PII/secret và starter asset không đổi.

## Checkpoint 0 — Baseline và safety check (10 phút)

### Numbered microsteps

1. **Why:** bảo đảm source và môi trường đúng. **Action:** mở ba starter files và U01 artifact; ghi source IDs/version vào file working. **Explanation:** artifact review cần provenance, không cần copy nội dung nguồn.
2. **Why:** giữ baseline tái lập được. **Action:** tạo working file và thêm metadata LAB-U02-01, M-U02, simulated, material_example_refs = MEX-U02-01. **Explanation:** metadata phân biệt Lab với MEX/Assignment.
3. **Why:** quan sát lỗi trước khi sửa. **Action:** chép nguyên năm flawed statement cùng NEED-U02-01 vào mục Baseline; chưa viết giải pháp. **Explanation:** before-state là evidence cho impact/diff.

### Verify

PASS khi starter mở được, baseline có đủ FL-U02-01…05/NEED-U02-01, working file có metadata và không chứa PII/secret.

### Expected result

PRECHECK-U02 = PASS và một baseline snapshot chưa bị sửa.

### Evidence

Lưu evidence/precheck_u02.md cùng checksum thủ công “6 cards present / starter unchanged”.

### Troubleshooting

- Thiếu card → dùng lại danh sách Lab, không lấy lời giải từ Material.
- U01 artifact chưa có → dùng baseline do giảng viên phát và ghi limitation.
- Starter bị thay đổi → chuyển nội dung sang working copy mới.

### Reset/rollback

Tạo working file mới từ template và giữ baseline snapshot. Không xóa hoặc sửa starter.

## Checkpoint 1 — Sửa operating model và event map (40 phút)

**Checkpoint ID:** CP-U02-01 · **material_example_refs:** MEX-U02-01 · **LO:** LO2.1, LO2.2

### Numbered microsteps

1. **Why:** tránh sửa bằng trực giác. **Action:** với mỗi FL card, thêm cột violates/weakens, affected accountability/event/artifact/commitment, symptom và evidence source. **Explanation:** diagnosis phải tách critical framework error khỏi practice chưa hiệu quả.
2. **Why:** tạo một mô hình coherent. **Action:** dựng operating map gồm PO, Developers, SM, sponsor/other stakeholders; ghi accountability, decision right, consultation path và visible evidence. **Explanation:** chức danh tổ chức không thay accountability Scrum.
3. **Why:** values phải quan sát được. **Action:** chọn ít nhất ba Scrum values và map mỗi value tới một hành vi/evidence trong NovaShop. **Explanation:** chỉ liệt kê năm từ không chứng minh cách vận hành.
4. **Why:** events phải phục vụ empiricism. **Action:** tạo bảng năm events với purpose, inspected artifact/progress, adaptation/output, participants và timebox. **Explanation:** agenda tùy chọn; purpose và opportunity inspect/adapt không tùy chọn.
5. **Why:** commitment phải khớp artifact. **Action:** map Product Backlog, Sprint Backlog, Increment với commitment tương ứng và ghi một oracle cho mỗi cặp. **Explanation:** commitment tạo focus để inspection có nghĩa.
6. **Why:** transparency cần rule cụ thể. **Action:** viết Team Charter và tối thiểu ba Working Agreement rules theo trigger → behavior → owner → evidence → inspection date, trong đó có NEED-U02-01. **Explanation:** sponsor visibility có thể đáp ứng mà không chuyển “how” thành approval.
7. **Why:** reviewer cần traceability. **Action:** map từng baseline card tới change ID, artifact section và verification check. **Explanation:** không có card nào được “sửa ngầm”.

### Verify

| Check | PASS condition |
| --- | --- |
| Accountabilities | một PO, một SM, Developers; no internal hierarchy; decision rights rõ |
| Values | ít nhất 3 value có positive behavior/evidence |
| Events | 5/5 đúng purpose; Daily 15 phút và hướng Sprint Goal; Review không là approval gate |
| Artifacts | 3/3 map đúng commitments |
| Working rules | tối thiểu 3 rule đủ trigger/behavior/owner/evidence/inspection |
| Accuracy | ít nhất 80% cards đúng; không critical error |

### Expected result

CP-U02-01 = PASS khi artifact là một operating model mới, không sao chép MEX, và reviewer có thể xác định ai quyết định gì, inspect gì ở event nào và evidence nằm ở đâu.

### Evidence

- U02_operating_model_working.md
- evidence/cp_u02_01_mapping_review.md
- baseline-to-change trace table

### Troubleshooting

1. **Input:** nếu không biết card sai ở đâu, phân loại nó theo accountability, event hoặc artifact/commitment.
2. **State:** nếu “Product Council” vẫn có three vetoes, mô hình vẫn là committee dù đổi tên.
3. **Contract:** nếu Daily có manager report nhưng không Sprint Goal/plan adaptation, kiểm lại purpose.
4. **Evidence:** nếu Working Agreement dùng “nên”, tìm trigger, owner và observable output còn thiếu.

### Reset/rollback

Giữ CP0 snapshot, tạo branch copy của working file và làm lại CP1. Không ghi đè baseline evidence.

## Checkpoint 2 — Triage yêu cầu veto của quality reviewer (20 phút)

**Checkpoint ID:** CP-U02-02 · **material_example_refs:** MEX-U02-01 · **LO:** LO2.1, LO2.2 · **Changed input:** LAB-CR-U02

### Numbered microsteps

1. **Why:** một change request có thể trộn nhu cầu đúng với giải pháp sai. **Action:** tách LAB-CR-U02 thành need, proposed mechanism, affected decision rights, affected event và evidence requirement. **Explanation:** không bác toàn bộ yêu cầu chỉ vì một phần trái framework.
2. **Why:** giữ accountability nhất quán. **Action:** ghi ít nhất hai options đáp ứng quality visibility mà không mặc định chuyển quyền how; nêu trade-off và owner quyết định. **Explanation:** oracle không bắt buộc một option duy nhất nhưng cấm veto hierarchy trong Scrum Team.
3. **Why:** cập nhật downstream. **Action:** sửa Team Charter, Working Agreement và event/artifact map ở các section bị ảnh hưởng; gắn change ID vào diff. **Explanation:** quality evidence có thể đi qua Definition of Done/evidence/review path mà không biến Daily thành approval.
4. **Why:** kiểm values và transparency. **Action:** ghi cách Openness/Courage/Respect được bảo vệ và khi nào rule mới được inspect. **Explanation:** governance tốt phải cho phép reviewer thấy limitation thật.

### Verify

- Impact note tách đúng need và proposed mechanism.
- Không có quality reviewer veto how hoặc duyệt task tại Daily.
- Quality requirement/evidence path không bị bỏ.
- Team Charter, Agreement và event map nhất quán.
- Trade-off, owner, review trigger và no-PII/secret đều có.

### Expected result

CP-U02-02 = PASS khi requirement chất lượng được giữ bằng evidence/DoD/consultation path, còn proposal làm sai accountability/event được thay bằng cơ chế có rationale. Nếu đội chỉ viết “từ chối reviewer”, kết quả là REVISE.

### Evidence

- evidence/cp_u02_02_impact.md
- before/after diff
- self-check PASS/REVISE với finding owner

### Troubleshooting

- Không phân biệt need/proposal → gạch chân câu nói về outcome/evidence và câu nói về quyền duyệt.
- Quality path biến mất → trace lại requirement đến DoD/evidence owner.
- Reviewer vẫn điều khiển Daily → kiểm participant/purpose và đưa consultation/deep dive sang channel phù hợp.

### Reset/rollback

Khôi phục CP1, áp dụng lại LAB-CR-U02 trong working copy mới. Xác nhận CP1 review và starter assets không đổi.

## 🧪 Final validation

**Thời lượng:** 5 phút.

Reviewer độc lập dùng artifact review:

1. Chấm mapping card và critical errors.
2. Kiểm hai checkpoint, change diff, evidence paths và no-PII/secret.
3. Ghi LAB-U02-PASS chỉ khi tất cả DoD đạt; ngược lại ghi REVISE, finding và owner.

Expected output: operating model, Team Charter, Working Agreement, event/artifact map, traceability và impact note có kết luận tái lập được.

## Deliverables và tái sử dụng

- project-artifacts/M-U02/lab/U02_operating_model_working.md
- evidence/cp_u02_01_mapping_review.md
- evidence/cp_u02_02_impact.md
- final evidence checklist

## ♻️ Reset, cleanup và khả năng chạy lại

Không có service/credential cần cleanup. Giữ artifact PASS làm reference cho CAP-01; không nộp nó như lời giải ASM-U02. Assignment dùng change request và deliverables riêng. Khi chạy lại, tạo working copy mới; không ghi đè starter hoặc bản PASS.

## Nguồn và provenance

### Nguồn đã map

- SRC-SG20 — The Scrum Guide: https://scrumguides.org/scrum-guide.html (publisher: Ken Schwaber, Jeff Sutherland / ScrumGuides.org; version: November 2020; accessed_at: 2026-08-25; license: CC BY-SA 4.0; allowed_use: adapt)
- SRC-TEAM — What is a Scrum Team?: https://www.scrum.org/resources/what-scrum-team (publisher: Scrum.org; version: living page snapshot 2026-08-25; accessed_at: 2026-08-25; license: reference-only; allowed_use: reference)
- SRC-EVENTS — Introduction to the Scrum Events: https://www.scrum.org/resources/introduction-scrum-events (publisher: Scrum.org; version: living page snapshot 2026-08-25; accessed_at: 2026-08-25; license: reference-only; allowed_use: reference)
- SRC-PROJECT — NovaShop simulated e-commerce project brief: starter/NovaShop_Project_Brief.md (publisher: Training artifact created for this course; version: 1.0; accessed_at: 2026-08-25; license: internal approved; allowed_use: internal_approved)

### Phần bổ sung/suy diễn

- [SUY DIỄN — từ kiến thức đã huấn luyện] FL cards, NEED-U02-01, LAB-CR-U02 và mapping score là synthetic instructional design.

> **Chính sách lời giải:** hướng dẫn giảm dần và oracle không cung cấp final/reference solution của Assignment.

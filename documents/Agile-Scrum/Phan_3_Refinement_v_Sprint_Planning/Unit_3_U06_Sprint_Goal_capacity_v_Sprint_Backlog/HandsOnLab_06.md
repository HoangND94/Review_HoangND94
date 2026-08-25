# Hands-on Lab LAB-U06-01 — Sprint Planning khi capacity giảm và có dependency

| Thuộc tính | Giá trị |
| --- | --- |
| Hình thức | guided_with_fading |
| Thời lượng | 90 phút |
| Độ khó | medium |
| Xác thực | simulated |
| Validation | artifact_review |

## 🎯 Learning Outcomes được thực hành

- **LO6.1:** tạo Sprint Goal và forecast có Product Goal link, history/capacity/DoD assumptions.
- **LO6.2:** tạo Sprint Backlog why/what/how có dependency, evidence, risk response và adaptation boundary.
- **material_example_refs:** **MEX-U06-01** tại CP-U06-01 và CP-U06-02. Lab đổi history, capacity calendar, PBI IDs và maintenance condition so với Material.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

- **MEX-U06-01 → LAB-U06-01/CP-U06-01:** LO6.1, LO6.2; evidence là Goal/forecast canvas, Goal-removal test và Sprint Backlog.
- **MEX-U06-01 → LAB-U06-01/CP-U06-02:** LO6.1, LO6.2; evidence là maintenance impact, plan diff và review result.

## 🧭 Scenario và input

Một Sprint training simulation có capacity khả dụng giảm **30%** so với baseline vì lịch đào tạo/leave đã biết. Ba Sprint tương đồng Done 15/16/14 relative units. Product Backlog v2 Lab:

| PBI | Size | Outcome/order note |
| --- | ---: | --- |
| LAB-SP-01 | 5 | Guest sửa địa chỉ invalid mà không mất giỏ; order 1 |
| LAB-SP-02 | 8 | Payment approved/declined tạo order/no-order rõ; order 2 |
| LAB-SP-03 | 3 | On-screen + email confirmation; order 3, email risk |
| LAB-SP-04 | 5 | Theo dõi trạng thái sau order; order 4 |

Product Goal/DoD theo project brief. Capacity baseline calendar là 50 availability units, upcoming là 35; đây chỉ là context, **không** tạo hệ số point/availability. CP1 lập plan trước Sprint mà chưa biết sự cố. Tại review cuối ngày 6, CP2 mới đưa notice: payment sandbox sẽ bảo trì ngày 7–8; đến cuối ngày 8, nhà cung cấp cập nhật rằng thời điểm mở lại trượt sang ngày 10. Fixture approved/declined được phép cho preparation nhưng không thay integration evidence thuộc DoD. Vì vậy Lab luyện **in-Sprint inspection và replanning sau khi work đã bắt đầu**, khác Assignment lập forecast trước Sprint với maintenance đã biết ở ngày 2.

Constraints: chỉ dữ liệu synthetic; không đổi Product Goal; không giảm DoD; không gọi forecast là commitment/guarantee; không copy con số hoặc Sprint Goal từ MEX; mọi decision có evidence.

## 🧰 Prerequisite, starter và file làm việc

Hoàn thành U05; đọc MEX-U06-01. Mở project brief, synthetic CSV, template và Product Backlog v2 Lab. Tạo:

- `project-artifacts/M-U06/lab/U06_lab_planning-canvas.md`
- `project-artifacts/M-U06/lab/U06_lab_sprint-backlog.md`
- `project-artifacts/M-U06/lab/U06_lab_evidence.md`

ENV-PRO-ARTIFACT chỉ dùng Markdown/CSV/whiteboard. Không dùng service thật, secret hay PII. Starter assets chỉ đọc.

## 📋 Lab outline và Definition of Done

CP-U06-01/02 đều PASS; Sprint Goal là một outcome liên kết Product Goal; forecast có history/capacity/DoD/assumptions và core/negotiable boundary; Sprint Backlog có why/what/how/dependency-owner-trigger/evidence/risk response cho mọi selected PBI; maintenance impact được xử lý mà không hạ DoD; evidence, before/after và reset review được.

## Checkpoint 0 — Baseline và safety check

### Numbered microsteps

1. **Why:** bảo vệ input. **Action:** tạo ba file, ghi `authenticity: simulated`, source/version và chép đúng PBI/history/capacity facts; không thêm forecast. **Giải thích:** reviewer phải phân biệt input với decision.
2. **Why:** giữ sizing/capacity đúng vai trò. **Action:** ghi “size là relative/team-local; capacity=35 là availability context; không có conversion”. **Giải thích:** hai đại lượng hỗ trợ judgment nhưng không chia trực tiếp.
3. **Why:** xác nhận quality boundary. **Action:** trích các DoD check liên quan acceptance evidence, Critical/High, docs, no secret/PII và usable Increment; ghi payment integration evidence là mandatory cho LAB-SP-02 Done. **Giải thích:** risk response không được xóa guardrail.

### Verify

Ba file mở được; inputs khớp; chưa có Goal/forecast; no-conversion statement và DoD guardrail có mặt; starter assets không đổi.

### Expected result

Baseline sạch và có thể chạy lại; mọi số liệu là simulated, không có credential/payment data thật.

### Evidence

Lưu `CP0-baseline` với input checksum logic, source ID, DoD subset và PASS/REVISE.

### Troubleshooting

Nếu history bị thiếu, không tự tạo thêm Sprint; nếu capacity calendar không tổng 35, đối chiếu source rows; nếu PBI không có criteria, ghi readiness risk và loại khỏi forecast đến khi đủ rõ.

### Reset/rollback

Giữ CP0 read-only; tạo working copy. Reset đúng khi working copy chưa có Goal/forecast/plan nhưng input khớp CP0.

## Checkpoint 1 — CP-U06-01: Tạo Goal/forecast với capacity giảm 30%

**material_example_refs:** MEX-U06-01 · **LO:** LO6.1, LO6.2

### Numbered microsteps

1. **Why:** tìm một outcome chung. **Action:** với bốn PBI theo order, ghi actor/outcome và contribution tới Product Goal; đánh dấu item không cùng objective gần nhất. **Giải thích:** ordered không đồng nghĩa tất cả item cùng Sprint Goal.
2. **Why:** tạo Sprint Goal linh hoạt. **Action:** viết một câu Goal có actor/outcome/boundary, không dùng PBI ID hoặc từ “hoàn thành”. Viết một phản ví dụ scope-list rồi nêu vì sao loại. **Giải thích:** contrast làm rõ quyết định mà không cung cấp câu mẫu từ Material.
3. **Why:** tạo forecast có evidence. **Action:** lập bảng history 15/16/14, capacity baseline/upcoming, skill/dependency, DoD, PBI size/uncertainty. Developers role chọn core và negotiable scope; ghi rationale, assumptions, uncertainty. Không tính point bằng 30% hay 35/50. **Giải thích:** forecast là judgment từ nhiều evidence.
4. **Why:** kiểm Goal–scope coherence. **Action:** bỏ thử từng selected PBI và ghi Goal còn đạt hay không; từ đó xác nhận core/negotiable boundary. **Giải thích:** test này cho biết item nào bảo vệ objective.
5. **Why:** biến what thành plan. **Action:** tạo Sprint Backlog row cho selected PBI với why contribution, what, how increment/next action, dependency/owner/trigger, acceptance evidence/DoD, risk response. **Giải thích:** plan đủ actionable nhưng vẫn thay đổi được.

### Verify

CP-U06-01 PASS khi:

1. Goal là một outcome và link Product Goal; không phải PBI list;
2. forecast basis có history, capacity change, DoD, order, assumptions/uncertainty;
3. core/negotiable phân biệt và Goal-removal test có evidence;
4. mọi selected row đủ why/what/how/dependency/evidence/response;
5. không có point-time conversion, guarantee hoặc hạ DoD.

### Expected result

Planning canvas và Sprint Backlog đủ để đội bắt đầu Sprint và giải thích vì sao forecast phù hợp với context giảm capacity. Artifact phải khác MEX về Goal wording, PBI, lịch sử và plan.

### Evidence

Lưu planning canvas `cp1`, Sprint Backlog `cp1`, Goal-removal matrix, reviewer result và trace `Product Goal → Sprint Goal → PBI → evidence`.

### Troubleshooting

- Goal chứa nhiều “và” cho objective không liên quan: thu hẹp actor/outcome hoặc để item ngoài Sprint.
- Forecast chỉ dựa trên average: thêm upcoming capacity, risk/skill/DoD và giới hạn sample.
- How là assignment theo người: đổi thành actionable work/coordination; Developers tự tổ chức owner khi Sprint diễn ra.

### Reset/rollback

Tạo bản mới từ CP0; giữ bản CP1/evidence để so. Reset thành công khi Goal-removal/forecast/Sprint Backlog rows không còn trong working copy.

## Checkpoint 2 — CP-U06-02: Thích nghi khi payment sandbox bảo trì

**material_example_refs:** MEX-U06-01 · **LO:** LO6.1, LO6.2 · **changed constraint / constraint mới:** notice xuất hiện cuối ngày 6, maintenance ngày 7–8 rồi bị gia hạn đến ngày 10.

### Numbered microsteps

1. **Why:** phân biệt planned risk với evidence mới trong Sprint. **Action:** chụp snapshot Sprint Backlog cuối ngày 6, ghi work/evidence đã Done, đang làm và chưa bắt đầu; sau đó thêm notice bảo trì ngày 7–8. **Giải thích:** replanning phải dựa trên trạng thái thực, không giả định đội đang ở ngày 1.
2. **Why:** xác định tác động thật. **Action:** lập impact table cho Goal, selected PBI, sequence, evidence, dependency trigger và forecast; tách phần payment preparation có thể kiểm bằng fixture khỏi integration evidence phải đợi sandbox. **Giải thích:** external dependency có thể đổi how/uncertainty nhưng fixture không làm work đạt DoD.
3. **Why:** luyện inspection khi giả định tiếp tục đổi. **Action:** lập response đầu tiên cho mốc mở lại ngày 9, rồi áp update cuối ngày 8 rằng sandbox chỉ dự kiến mở ngày 10; ghi phần nào của plan/forecast cần đổi lần hai và phần nào giữ nguyên. **Giải thích:** adaptation là vòng lặp evidence → decision, không phải một contingency viết sẵn rồi bỏ quên.
4. **Why:** tạo response có owner/trigger. **Action:** đặt inspection trigger đầu ngày 9 và ngày 10, owner, expected evidence cùng behavior nếu sandbox mở hoặc tiếp tục trễ; tự quyết định sequence mới dựa trên trạng thái ngày 6. **Giải thích:** “blocked” không phải risk response.
5. **Why:** bảo vệ Goal và giữ history minh bạch. **Action:** áp dụng core/negotiable boundary; nếu cần, reforecast item negotiable, ghi rationale/trade-off và lưu ba trạng thái `day6-before → day6-notice → day8-extension`. Chỉ đề xuất thay/huỷ Goal khi evidence cho thấy objective không còn phù hợp. **Giải thích:** scope có thể thương lượng, còn Goal/DoD định hướng adaptation và diff cho phép inspection.

### Verify

CP-U06-02 PASS khi: snapshot ngày 6 phản ánh trạng thái work thật; impact table phủ Goal/forecast/plan/evidence; dependency có condition/owner/trigger; fixture giới hạn rõ; cả notice ban đầu và extension có decision/diff; response có open/late behavior; core/negotiable trade-off không hạ DoD; ba trạng thái plan minh bạch.

### Expected result

Maintenance muộn và lần gia hạn được xử lý nhất quán; đội có next action từ ngày 7, biết evidence nào còn thiếu, biết điều kiện reforecast ở ngày 9/10 và vẫn bảo vệ Sprint Goal. Work không bị gọi Done chỉ vì fixture pass, và phần đã Done trước notice không bị viết lại để làm đẹp plan.

### Evidence

Lưu notice, extension update, impact table, ba Sprint Backlog snapshot/diff, risk decisions, Goal/forecast status và CP-U06-02 review.

### Troubleshooting

- Nếu response là “chờ”: tìm preparation/clarification khác nhưng không giả integration evidence.
- Nếu đội muốn bỏ test/DoD: giảm negotiable scope trước và ghi impact.
- Nếu Goal đổi chỉ để khớp item còn lại: quay lại Product Goal/outcome và thảo luận với Product Owner; ghi decision.

### Reset/rollback

Khôi phục bản CP1 cùng snapshot cuối ngày 6, bỏ notice/extension/impact/resequence nhưng giữ Goal/forecast đã PASS. Reset đúng khi dependency trở về pre-notice state và diff so với snapshot ngày 6 rỗng.

## 🧪 Final validation

Từ CP0 sạch, chạy review CP1 rồi áp notice và review CP2. Exit condition: hai checkpoint PASS, traceability resolve, no point conversion/guarantee, no quality downgrade, no PII/secret, starter assets không đổi. Khi một input/assumption đổi, rerun Goal coherence, forecast basis và affected Sprint Backlog rows.

## 📦 Bằng chứng và deliverables

- **Artifact Lab:** Planning canvas và Sprint Backlog sau CP-U06-02.
- **Traceability table:** `Product Goal → Sprint Goal → PBI → acceptance/DoD evidence`.
- **Evidence checklist:** CP-U06-01/02 review, day6-before/day6-notice/day8-extension diff và reset result.
- `U06_lab_planning-canvas.md`: Goal, forecast, assumptions, core/negotiable.
- `U06_lab_sprint-backlog.md`: day6-before/day6-notice/day8-extension snapshots.
- `U06_lab_evidence.md`: trace, Goal-removal test, impact/risk decision, review results.

Giữ artifact để **ASM-U06**, **CAP-01** và review tích hợp **REV-01**. Assignment dùng backlog, lịch vắng bất đối xứng và maintenance đã biết trước Sprint ở ngày 2; Lab dùng calendar đào tạo/leave tổng hợp cùng notice muộn rồi gia hạn trong Sprint. Không nộp Lab như Assignment. Output chính thức của ASM-U06 sẽ được ASM-U08 tiêu thụ.

Không có service/credential cần cleanup. Chuyển bản thử lỗi vào `discarded/` trong thư mục Lab, giữ final/evidence, xác nhận starter và artifact U04/U05 chính thức không đổi. Không xóa rộng.

## ♻️ Reset, cleanup và khả năng chạy lại

Reset từng checkpoint theo hướng dẫn tại checkpoint. Cleanup chỉ tác động bản làm việc trong `project-artifacts/M-U06/lab/`: giữ final/evidence, chuyển bản thử lỗi vào `discarded/`, rồi xác nhận starter và artifact U04/U05 chính thức không đổi. Không có service hoặc credential cần thu hồi.

## 🔐 Chính sách lời giải

Learner Lab chỉ có hướng dẫn giảm dần và oracle; không chứa reference solution của Assignment. Output Lab không được nộp thay ASM-U06.

## 📚 Provenance

- **SRC-SG20:** Scrum Guide, November 2020, ScrumGuides.org, accessed 2026-08-25, CC BY-SA 4.0, adapt.
- **SRC-SPRINT-PLANNING:** Scrum.org Introduction to Sprint Planning, living snapshot/accessed 2026-08-25, website terms, reference.
- **SRC-FORECAST:** Scrum.org Forecasting and Release Planning, living snapshot/accessed 2026-08-25, website terms, reference.
- **SRC-PROJECT:** `starter/NovaShop_Project_Brief.md`, training artifact v1.0, accessed 2026-08-25, internal approved.

History, capacity, PBI và maintenance notice là simulated course data. Không dùng nguồn bổ sung.

---
<!-- QUALITY GATE: MEX-U06-01 resolve ở CP-U06-01/02; đủ microsteps/Verify/Expected/Evidence/Troubleshooting/Reset; changed constraint; no Assignment solution. -->

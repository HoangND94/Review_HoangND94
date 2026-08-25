# Unit U07: Daily Scrum, flow và impediment — Ví dụ và nghiên cứu tình huống

## 🎯 Learning Outcomes liên quan

> **Case:** CASE-U07-01 · **LO:** LO7.1, LO7.2 · **Outline:** OUT-U07-01, OUT-U07-02 · **Mức xác thực:** simulated

## Case Study 01 — Inventory reservation làm Goal có nguy cơ

### 1. Ticket và tiêu chí thành công

Developers của NovaShop cần điều phối Daily Scrum ngày 3. Sprint Goal là `SG-INV: đơn hợp lệ giữ tồn kho sandbox và hiển thị trạng thái xác nhận`. Một lỗi timeout của inventory sandbox khiến hai item chờ. Thành công khi nhóm tạo được plan ngày tới hướng Goal, log đúng impediment, thay đổi board có evidence và không hạ `DOD-NS-1.0`.

### 2. Input, baseline và ràng buộc

| ID | State lúc 09:00 | Age | Evidence | Liên hệ Goal |
| --- | --- | ---: | --- | --- |
| INV-31 | Verify | 2.5 ngày | 7/8 acceptance examples PASS; timeout case chưa chạy | Trực tiếp |
| INV-32 | In Progress | 1 ngày | UI confirmation đã peer review | Trực tiếp |
| INV-33 | In Progress | 0.5 ngày | Analytics event draft | Hỗ trợ |
| INV-34 | Ready | 0 | Email template | Không thiết yếu cho Goal |

Policy WIP gồm In Progress + Verify, limit 3. Event card `EV-INV-03` xác nhận sandbox chỉ ổn định lại lúc 13:00. Constraint: không bỏ timeout test, review, selected accessibility/security checks; không dùng endpoint/credential thật.

### 3. Phân tích lựa chọn

- **Option A — kéo INV-34 để tránh người rảnh:** tăng WIP lên 4, không giảm rủi ro Goal.
- **Option B — swarm vào INV-31, một người theo dõi sandbox, tạm dừng INV-33:** giảm context switching và tập trung lát cắt Goal; trade-off là telemetry chậm một ngày.
- **Option C — đánh dấu INV-31 Done và kiểm timeout sau:** làm giảm chất lượng, trái DoD.

Nhóm chọn B. Evidence chỉ cho phép gọi sandbox là impediment đã xác nhận, chưa cho phép quy kết ai làm chậm.

### 4. Artifact triển khai

#### Daily Scrum record `DS-INV-D3`

| Trường | Giá trị |
| --- | --- |
| Timebox | 09:00–09:13 |
| Progress to Goal | Happy path giữ tồn kho đã chạy; timeout-path thiếu evidence nên Goal đang có rủi ro cao |
| Flow signal | WIP 3/3; INV-31 age 2.5 ngày; 2 item phụ thuộc cùng sandbox |
| Adaptation | Đưa INV-33 về Ready có note trạng thái; Lan + Huy chuẩn bị timeout fixture cho INV-31; Quân kiểm sandbox 13:00 |
| Parking lot | 09:15–09:30: Lan/Huy rà fixture, không giữ cả nhóm |
| Review | 13:15 inspect sandbox/evidence; 16:00 inspect Goal risk |
| Guardrail | Giữ nguyên DOD-NS-1.0; INV-31 không Done khi timeout case chưa PASS |

#### Impediment log `IMP-INV-03`

| Evidence | Impact | Owner/action | Next review | Status |
| --- | --- | --- | --- | --- |
| EV-INV-03, INV-31/INV-32 dependency links | Chặn timeout verification của lát cắt Goal | Quân kiểm health card và cập nhật board; Scrum Master hỗ trợ escalation nếu quá 13:15 | 13:15 | Open |

#### Board diff

- `INV-33: In Progress → Ready` kèm handoff note và evidence link.
- `INV-31` giữ Verify, gắn `IMP-INV-03`.
- `INV-34` vẫn Ready; WIP sau adaptation = 2/3.

### 5. Output mong đợi

Record tạo plan có owner và review time; WIP giảm từ 3 xuống 2; item chưa đạt timeout evidence vẫn Not Done; thay đổi telemetry được ghi là trade-off, không bị che giấu.

### 6. Cách xác minh

| Oracle | PASS khi |
| --- | --- |
| C-U07-01 | `SG-INV` xuất hiện trong progress statement và từng action thiết yếu có liên hệ Goal |
| C-U07-02 | 09:00–09:13 không vượt 15 phút; discussion sâu có parking lot |
| C-U07-03 | WIP tái tính từ board trước = 3, sau = 2 |
| C-U07-04 | `IMP-INV-03` có evidence, impact, owner, action, review time |
| C-U07-05 | DoD ID không đổi; INV-31 không bị gọi Done |

Kết quả case: 5/5 PASS.

### 7. Failure modes và giới hạn

- Nếu WIP sau record vẫn ghi 3 nhưng INV-33 đã về Ready, nguyên nhân là policy/count sai; chẩn đoán bằng state list, sửa phép đếm và lưu snapshot mới.
- Nếu “sandbox lỗi” không trỏ tới `EV-INV-03`, kết luận thiếu evidence; thêm event card hoặc hạ mức chắc chắn thành giả thuyết cần kiểm.
- Nếu nhóm chọn Option A, dấu hiệu là WIP=4 và Goal risk không đổi; rollback INV-34 về Ready và ưu tiên finish-before-start.
- Một ngày chưa đủ chứng minh nguyên nhân dài hạn. Record này hỗ trợ adaptation ngày; causal analysis nhiều Sprint thuộc U09.

### 8. Bài học chuyển giao

Một Daily Scrum tốt không tối đa hóa số người “có việc”; nó tối đa hóa khả năng tiến tới Sprint Goal bằng evidence và một plan có thể kiểm. Trong `HandsOnLab_07.md`, học viên xử lý board checkout khác và một change card khiến adaptation ban đầu không còn phù hợp.

## Provenance của các case

- **SRC-SG20** — [The Scrum Guide, November 2020](https://scrumguides.org/scrum-guide.html).
- **SRC-EVENTS** — [Introduction to the Scrum Events](https://www.scrum.org/resources/introduction-scrum-events), snapshot 2026-08-25.
- **SRC-KANBAN-SCRUM** — [Kanban Guide for Scrum Teams, 2021](https://www.scrum.org/resources/kanban-guide-scrum-teams).
- **SRC-PROJECT** — Fixture CASE-U07-01: **[BỔ SUNG — nguồn: NovaShop simulated project brief, dữ liệu mô phỏng cho khóa học]**.

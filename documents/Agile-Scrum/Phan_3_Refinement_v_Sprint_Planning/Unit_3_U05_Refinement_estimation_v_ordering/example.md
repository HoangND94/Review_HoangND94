# Unit U05: Refinement, estimation và ordering — Ví dụ và nghiên cứu tình huống

> **Case ID:** CASE-U05-01 · **LO:** LO5.1, LO5.2 · **Outline:** OUT-U05-01, OUT-U05-02 · **Xác thực:** simulated

## 🎯 Learning Outcomes liên quan

- **LO5.1 / OUT-U05-01:** refinement và relative sizing có assumptions/uncertainty.
- **LO5.2 / OUT-U05-02:** ordering tách value/risk/dependency/learning và có trigger.

**Project increment:** M-U05, tạo Sizing record và Product Backlog v2 dùng được ở Sprint Planning.

## 🧰 Điều kiện chạy lại

Dùng ENV-PRO-ARTIFACT (Markdown CommonMark/bảng tính CSV UTF-8/whiteboard), project brief, synthetic CSV và template Refinement/Ordering. Không cần code/service/credential. Verification là artifact review theo năm oracle ở mục 4.

## Case Study 01 — Refinement backlog tự tra cứu trạng thái đơn

### 1. Ticket và tiêu chí thành công

Customer Service muốn giảm các yêu cầu hỏi trạng thái (`OBS-04`: 6/15 yêu cầu synthetic). Product Owner có bốn PBI thô cho order tracking. Scrum Team cần size tương đối và order đủ minh bạch để chuẩn bị Sprint Planning, nhưng email sandbox đang không ổn định.

Case đạt khi: vote dispersion được giải thích bằng assumptions; final size có reference/uncertainty; order tách value, risk, dependency và learning; thay đổi email dependency dẫn tới impact có thể dự đoán.

### 2. Input, baseline và constraints

- Reference `TRK-REF`: hiển thị một trạng thái đơn synthetic, size 3, đạt cùng DoD.
- `TRK-01`: liệt kê đơn thuộc tài khoản.
- `TRK-02`: xem trạng thái/thời điểm cập nhật.
- `TRK-03`: gửi email khi trạng thái đổi.
- `TRK-04`: từ chối truy cập đơn của tài khoản khác.
- Email sandbox có availability chưa biết; authorization rule đã có oracle; không có SMS, refund hoặc live carrier tracking.
- Estimate là team-local, không đổi sang giờ; order không được tính bằng tổng điểm mơ hồ.

### 3. Phân tích và quyết định

#### Sizing record

| PBI | Vote 1 | Điều lộ ra | Quyết định refinement | Final | Uncertainty |
| --- | --- | --- | --- | ---: | --- |
| TRK-01 | 3/3/5/3 | Vote 5 giả định pagination | Lát đầu tối đa 10 đơn synthetic | 3 | Review khi pagination bắt buộc |
| TRK-02 | 3/5/5/8 | Vote 8 giả định carrier timeline | Scope chỉ trạng thái nội bộ + timestamp | 5 | Mapping status chưa có owner |
| TRK-03 | 3/8/13/13 | Email retry/duplicate chưa rõ | Chưa ép consensus; tách learning action về delivery contract | ? | Email contract blocking |
| TRK-04 | 5/5/8/5 | Vote 8 giả định audit trail | Từ chối + evidence, audit nâng cao later | 5 | Review nếu NFR audit đổi |

TRK-03 được ghi “chưa size” thay vì trung bình 9.25 hay ép 8. Đây là outcome hợp lệ của refinement: uncertainty blocking đã được nhìn thấy.

#### Ordered backlog

| Order | PBI | Value | Risk | Dependency | Learning | Rationale/trigger |
| ---: | --- | --- | --- | --- | --- | --- | --- |
| 1 | TRK-04 | Bảo vệ quyền riêng tư/đúng actor | Access risk cao | Không | Xác nhận authorization boundary | Làm sớm vì guardrail; review nếu auth contract đổi |
| 2 | TRK-01 | Mở self-service | Thấp | TRK-04 guardrail | Thấp | Tạo entry point sau khi boundary rõ |
| 3 | TRK-02 | Outcome chính: hiểu trạng thái | Mapping risk trung bình | TRK-01 | Trung bình | Hoàn tất lát self-service; mapping owner phải chốt |
| 4 | TRK-03 | Notification tiện lợi | Email risk cao | TRK-02 | Cao | Hoãn feature nhưng làm learning action sớm; review khi contract có evidence |

Quyết định không đặt TRK-03 lên đầu chỉ vì risk cao: outcome chính vẫn có thể kiểm chứng không cần email, còn một learning action nhỏ xử lý uncertainty. Trade-off là notification đến sau nhưng lát tracking không bị chặn bởi integration chưa rõ.

### 4. Output mong đợi và validation

Reviewer chạy artifact review:

1. **LO5.1:** 4/4 PBI có vote, extreme rationale và uncertainty; 3 item có final size hợp lý, TRK-03 được đánh dấu blocking thay vì false precision.
2. **LO5.1:** mọi size so với TRK-REF/cùng DoD; không có point-to-hour hay productivity claim.
3. **LO5.2:** 4/4 row order có evidence value/risk/dependency/learning và trigger.
4. **LO5.2:** hard/soft dependency phân biệt được; learning action của email không bị gọi là delivery feature Done.
5. **Edge test:** giả sử email contract trở nên ổn định và duplicate handling có oracle. Expected: TRK-03 quay lại refinement/sizing và order được review; không tự động nhảy lên đầu nếu Product Goal/value chưa đổi.

Case PASS khi năm check đạt. Nếu người đọc chỉ thấy một priority score hoặc final point không có assumption, kết quả REVISE.

### 5. Failure modes và bài học chuyển giao

- **Lấy trung bình vote:** che dấu việc TRK-03 chưa hiểu; sửa bằng extreme discussion và trạng thái `?`.
- **Risk cao luôn làm trước:** nhầm exposure với order; sửa bằng tách delivery outcome và learning action.
- **Email là hard dependency của tracking:** kiểm tra lại outcome; self-service status không cần email. Ghi dependency soft/later.
- **Size được dùng làm priority:** hai khái niệm trả lời câu hỏi khác nhau; tách cột và rationale.

Bài học: refinement tốt có thể kết thúc bằng một câu hỏi rõ thay vì một con số giả. Ordering tốt cho thấy yếu tố chi phối và điều kiện đổi quyết định. Lab sẽ dùng inventory dependency cùng vote data khác; không sao chép artifact case này.

## Provenance của các case

- **SRC-SG20** — [Scrum Guide](https://scrumguides.org/scrum-guide.html) (ScrumGuides.org; November 2020; accessed 2026-08-25; CC BY-SA 4.0; adapt).
- **SRC-BACKLOG** — [Product Backlog](https://www.scrum.org/resources/introduction-product-backlog) (Scrum.org; living snapshot/accessed 2026-08-25; website terms; reference).
- **SRC-PLANNING-POKER** — [Planning Poker](https://agilealliance.org/glossary/planning-poker/) (Agile Alliance; living snapshot/accessed 2026-08-25; website terms; reference).
- **SRC-FORECAST** — [Forecasting and Release Planning](https://www.scrum.org/resources/introduction-forecasting-and-release-planning) (Scrum.org; living snapshot/accessed 2026-08-25; website terms; reference).

Các ID, votes và quyết định là simulated, dựa trên phạm vi NovaShop và `OBS-04`; không phải số liệu đội thật. Không dùng nguồn bổ sung.

---
<!-- QUALITY GATE: CASE-U05-01 độc lập, đủ input/constraint/artifact/expected/validation/trade-off/failure; map đủ LO/outline. -->

# Unit U10 — Worked case: quyết định release cho chiến dịch quà tặng

> **Case ID:** CASE-U10-01 · **LO:** LO10.1, LO10.2 · **Outline:** OUT-U10-01, OUT-U10-02 · **Xác thực:** simulated

## 🎯 Learning Outcomes liên quan

- **LO10.1:** phân tích flow/value metric bằng measurement contract tái lập được.
- **LO10.2:** tạo scenario forecast có assumption, risk, limitation và update trigger.

## Scenario

Hai Sprint sau baseline, NovaShop muốn chạy chiến dịch quà tặng. Sponsor đề nghị công bố một ngày cố định. Product Backlog còn 20 PBI đã split tương đối đồng nhất. Bốn Sprint gần nhất có throughput `5, 6, 4, 5`; một open risk là nhà cung cấp shipping sandbox có thể làm mất một item capacity mỗi Sprint. Value snapshot cho thấy order success tăng nhưng re-entry share vẫn sát guardrail 5%.

Đây là case riêng: input, scope và risk khác `MEX-U10-01`; không dùng lại bảng 18 PBI hay kết luận 3–5 Sprint.

## Input và constraints

| Input | Giá trị |
| --- | --- |
| Remaining scope | 20 PBI đã refined/split |
| Historical throughput | 5, 6, 4, 5 items/Sprint |
| DoD | Giữ nguyên quality/security/accessibility evidence đã chọn |
| Risk | Shipping capacity loss: 0 hoặc 1 item/Sprint |
| Review cadence | Cuối mỗi Sprint và ngay khi scope đổi trên 10% |

Constraints: không thêm capacity giả định; không loại Sprint throughput 4 chỉ vì làm range xấu; không gọi scenario là commitment.

## Problem → decision → artifact

### 1. Kiểm measurement contract

Bốn số đều đếm item đạt cùng finish rule `Done`; backlog items đã được split theo cùng policy. Vì sample chỉ có bốn Sprint, team ghi confidence `medium-low`, không suy diễn distribution dài hạn.

### 2. Tách evidence và assumptions

- **Fact trong scenario:** history `5,6,4,5`, scope snapshot 20, DoD hiện tại.
- **Assumption optimistic:** đạt 6 item/Sprint và risk không kích hoạt.
- **Assumption base:** đạt 5 item/Sprint.
- **Assumption conservative:** chỉ đạt 4 item/Sprint do shipping/rework.

### 3. Tạo scenario

| Scenario | Công thức | Forecast | Risk/condition |
| --- | --- | ---: | --- |
| Optimistic | `ceil(20/6)` | 4 Sprint | Không mất capacity; item mix ổn định |
| Base | `ceil(20/5)` | 4 Sprint | Throughput trung tâm; scope không đổi |
| Conservative | `ceil(20/4)` | 5 Sprint | Shipping risk hoặc rework kích hoạt |

Optimistic và base cùng ra bốn Sprint nhưng không đồng nghĩa certainty cao: chúng phụ thuộc assumptions khác nhau. Range hữu ích là 4–5 Sprint; quyết định truyền thông phải giữ điều kiện và review trigger.

### 4. Release decision memo

**Decision:** chuẩn bị release window sau Sprint 4–5; chưa công bố một ngày guarantee. Ưu tiên đóng shipping risk và kiểm re-entry guardrail trước quyết định release cuối. Review forecast sau mỗi Sprint, khi scope đổi >10%, throughput dưới 4 hoặc DoD thay đổi.

**Trade-off:** cố định Sprint 4 chỉ hợp lệ nếu Product Owner giảm scope theo value mà không hạ DoD. Giữ toàn bộ scope mở khả năng Sprint 5. Thêm người không tự động biến throughput thành 6 vì onboarding/coordination chưa có evidence.

## Verification oracle

Reviewer thực hiện bốn check:

1. Tính lại `ceil(20/6)`, `ceil(20/5)`, `ceil(20/4)` và nhận cùng kết quả.
2. Xác nhận history không bị cherry-pick, unit/window/finish rule được nêu.
3. Tìm được DoD, risk, limitation và update trigger ngay trong memo.
4. Không có claim “chắc chắn”, “cam kết” hay causation từ value snapshot.

**Expected result:** bốn check PASS; thiếu một check là `REVISE`, sai formula hoặc hạ DoD là `FAIL`.

## Edge/failure behavior

- Nếu Product Owner thêm 6 PBI (>10%), trigger chạy lại: dùng scope 26, không giữ memo cũ.
- Nếu item mix chuyển thành epic chưa split, dừng item-count forecast và refine trước.
- Nếu throughput Sprint kế tiếp là 2 do outage, không xóa observation; cập nhật scenario/confidence và risk response.

## Mapping và reuse

Case chứng minh LO10.1 qua measurement contract/formula và LO10.2 qua range, risk, limitation, trigger. Cấu trúc memo được luyện lại với input Sprint 2 trong `HandsOnLab_10.md`; Assignment 05 dùng dataset/change request khác và không được giải sẵn ở đây.

## Provenance của các case

- [The Scrum Guide 2020](https://scrumguides.org/scrum-guide.html).
- [Evidence-Based Management Guide 2024](https://www.scrum.org/resources/online-evidence-based-management-guide).
- [Introduction to Forecasting and Release Planning](https://www.scrum.org/resources/introduction-forecasting-and-release-planning), accessed 2026-08-25.
- `[SUY DIỄN — từ kiến thức đã huấn luyện]` Toàn bộ campaign, backlog, throughput và risk trong case là synthetic.

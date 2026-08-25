# Unit U01: Agile mindset và lựa chọn cách làm — Ví dụ và nghiên cứu tình huống

> **Case ID:** CASE-U01-01 · **Mức xác thực:** simulated · **Milestone:** M-U01

## 🎯 Learning Outcomes liên quan

- **LO1.1 / OUT-U01-01:** chọn cách làm bằng uncertainty, feedback và cost-of-change.
- **LO1.2 / OUT-U01-02:** tạo value hypothesis có signal, threshold, guardrail và adaptation rule.
- **Professional artifact:** decision canvas và value hypothesis register.

## Điều kiện chạy case

Dùng ENV-PRO-ARTIFACT với Markdown editor và spreadsheet đọc CSV UTF-8. Mở được starter/NovaShop_Project_Brief.md, starter/NovaShop_Synthetic_Data.csv và starter/Artifact_Templates.md. Không cần code hoặc dịch vụ bên ngoài.

## Nguồn đầu vào đã map

- SRC-AM01 — https://agilemanifesto.org/ — Agile values, version 2001, accessed 2026-08-25, reference-only.
- SRC-AP01 — https://agilemanifesto.org/principles.html — Agile principles, version 2001, accessed 2026-08-25, reference-only.
- SRC-SG20 — https://scrumguides.org/scrum-guide.html — empiricism, November 2020, CC BY-SA 4.0.
- SRC-PROJECT — starter/NovaShop_Project_Brief.md — NovaShop scenario, version 1.0, internal approved.

## Case Study 01: Có nên xây theo dõi đơn theo một kế hoạch cố định?

### 1. Ticket và tiêu chí thành công

- **Vai trò/stakeholder:** Product Owner tư vấn cho Business Sponsor và Customer Service.
- **Vấn đề:** Sponsor muốn khóa ngay toàn bộ màn hình và workflow theo dõi đơn trong ba tháng. Đội mới chỉ biết 6/15 yêu cầu hỗ trợ synthetic hỏi trạng thái; chưa biết người mua cần loại thông tin nào hoặc self-service có giảm yêu cầu hỗ trợ không.
- **Project increment:** quyết định DEC-U01-TRACK-01 và hypothesis VH-U01-TRACK-01.
- **Tiêu chí thành công:** artifact phân biệt fact/assumption/target, giải thích lựa chọn cách làm, có counter-example, và cho phép reviewer đi tới quyết định continue/adjust/stop từ dữ liệu mô phỏng.

### 2. Input, trạng thái ban đầu và ràng buộc

| Input | Giá trị và mức tin cậy |
| --- | --- |
| OBS-04 | 6/15 yêu cầu hỗ trợ synthetic hỏi trạng thái đơn; observation, sample nhỏ |
| FR-04 | Người mua chỉ xem được đơn thuộc tài khoản mô phỏng; contract ổn định |
| Sponsor statement | “Nếu có timeline đầy đủ thì ticket sẽ giảm”; assumption |
| Product boundary | Order tracking trong scope; ERP và hoàn tiền phức tạp ngoài scope |
| Safety | Không PII, không endpoint hay credential thật |

Constraint thời gian: đội có thể thực hiện hai vòng prototype bằng evidence card. Không có production telemetry nên không được tuyên bố tác động kinh doanh thật.

### 3. Phân tích lựa chọn

Ba phương án được cân nhắc:

1. **Plan-driven toàn bộ:** khóa timeline đầy đủ ngay. Ưu điểm là dễ forecast output; nhược điểm là có thể đầu tư vào trạng thái người mua không cần.
2. **Adaptive toàn bộ:** thay cả contract quyền truy cập và luồng hiển thị qua thử nghiệm. Phương án này vi phạm ranh giới ổn định của FR-04.
3. **Kết hợp theo uncertainty:** giữ contract ownership/audit ổn định, nhưng thử lát nhỏ “xem trạng thái hiện tại + mốc tiếp theo” để học nhu cầu thông tin. Đây là lựa chọn được dùng.

Counter-example: nếu quy định hoặc carrier contract đã xác định chính xác các trạng thái bắt buộc và không cho phép biến thể UI, phần biểu diễn đó nên được plan/check theo contract; vẫn có thể inspect outcome sau release mô phỏng.

### 4. Cách triển khai professional artifact

#### Decision canvas

| Trường | Nội dung |
| --- | --- |
| Decision ID | DEC-U01-TRACK-01 |
| Stakeholder decision | Chọn lát adaptive cho thông tin tracking; giữ access-control contract plan-driven |
| Evidence | OBS-04 = 6/15 ticket hỏi trạng thái |
| Assumption | Thiếu self-service là nguyên nhân chính của các ticket |
| Uncertainty nhu cầu | Chưa biết người mua cần timeline đầy đủ hay chỉ trạng thái và mốc tiếp theo |
| Uncertainty giải pháp | Chưa biết mapping trạng thái sandbox có đủ dễ hiểu |
| Feedback/cost | Hai vòng synthetic; artifact có thể bỏ, chi phí đảo ngược thấp |
| Counter-example | Carrier contract bất biến hoặc không thể nhận feedback an toàn |

#### Value hypothesis register

| Trường | Nội dung |
| --- | --- |
| ID | VH-U01-TRACK-01 |
| Hypothesis | Nếu 15 người mua mô phỏng thấy trạng thái hiện tại và mốc tiếp theo, số người vẫn cần hỏi Customer Service về trạng thái sẽ không quá 3/15 |
| Baseline | 6/15 yêu cầu hỗ trợ liên quan trạng thái |
| Signal/timebox | số yêu cầu status-help trên 15 phiên synthetic trong vòng 2 |
| Guardrail | 15/15 phiên chỉ hiển thị đúng order-owner card; không lộ identifier thật |
| Continue | signal ≤ 3/15 và guardrail đạt |
| Adjust | signal đạt nhưng guardrail hỏng, hoặc người dùng không hiểu tên trạng thái |
| Stop/research | signal > 3/15 hoặc dữ liệu thiếu denominator |

Luồng triển khai: evidence được gắn mức tin cậy → uncertainty tách theo nhu cầu/giải pháp → phần ổn định và phần thử nghiệm được tách → hypothesis đặt oracle trước khi xem kết quả.

### 5. Output mong đợi

Giả sử vòng mô phỏng trả về 2/15 yêu cầu status-help nhưng một evidence card hiển thị đơn không thuộc owner. Kết quả đúng là **ADJUST**, không phải CONTINUE: signal đạt, guardrail FR-04 thất bại. Artifact phải giữ decision log và tạo risk/fix item; không xóa evidence bất lợi.

### 6. Cách xác minh

| Check | PASS | FAIL |
| --- | --- | --- |
| Traceability | OBS-04 và FR-04 nối tới decision/hypothesis | Claim không có input ID |
| LO1.1 | Có uncertainty, feedback, cost/reversibility và counter-example | Chỉ ghi “dùng Agile” |
| LO1.2 | Có outcome, baseline, threshold, timebox, guardrail, adaptation | Chỉ mô tả tính năng |
| Oracle | Với 2/15 và access violation, reviewer chọn ADJUST | Có thể chọn CONTINUE tùy ý |
| Safety | Chỉ anonymous synthetic cards | Có PII/credential thật |

Kết luận case là PASS nếu năm dòng đều đạt. Một dòng FAIL làm artifact mang trạng thái REVISE.

### 7. Giải thích sâu và failure modes

Mô hình kết hợp không phải “nửa Agile, nửa Waterfall” theo tỷ lệ. Nó đặt cách kiểm soát phù hợp quanh từng uncertainty. Access control có oracle đã biết nên cần contract rõ; nội dung tracking chưa biết nên cần feedback. Nếu đội dùng ticket count như bằng chứng nhân quả, dấu hiệu là rationale nhảy từ “6/15 hỏi trạng thái” sang “timeline chắc chắn giảm ticket”. Sửa bằng cách hạ claim thành hypothesis và giữ alternative causes như email lỗi hoặc tên trạng thái khó hiểu.

Giới hạn: sample nhỏ, synthetic và chỉ đo proxy “status-help”; nó không chứng minh satisfaction hay revenue. Khi denominator thay đổi, phải tạo baseline mới thay vì so hai tỷ lệ không tương thích.

### 8. Bài học chuyển giao

Nguyên tắc chuyển giao là tách phần **đã biết đủ để kiểm theo contract** khỏi phần **cần học bằng feedback**. Trong LAB-U01-01, học viên áp dụng nguyên tắc này cho năm work item khác và xử lý một change card mới; không sao chép tracking canvas ở case này.

## Provenance của các case

- Các định nghĩa Agile/empiricism được diễn giải từ SRC-AM01, SRC-AP01 và SRC-SG20.
- Scenario, FR-04 và OBS-04 đến từ SRC-PROJECT cùng dataset synthetic.
- [SUY DIỄN — từ kiến thức đã huấn luyện] Ngưỡng 3/15, hai vòng và artifact IDs là thiết kế sư phạm, không phải benchmark hay dữ liệu thị trường.

> **Simulated disclosure:** Case này không mô tả khách hàng, hệ thống hay hiệu quả kinh doanh có thật.

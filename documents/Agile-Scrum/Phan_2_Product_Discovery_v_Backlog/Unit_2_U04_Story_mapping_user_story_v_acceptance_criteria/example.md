# Unit U04: Story mapping, user story và acceptance criteria — Ví dụ và nghiên cứu tình huống

> **Case ID:** CASE-U04-01 · **Mức xác thực:** simulated · **Validation:** artifact_review

## 🎯 Learning Outcomes liên quan

- **LO4.1 / OUT-U04-01:** chuyển journey sau mua hàng thành Story Map và Product Backlog.
- **LO4.2 / OUT-U04-02:** chọn lát dọc và viết acceptance examples có happy cùng failure behavior.
- **Project increment:** M-U04; case minh họa cùng năng lực nhưng dùng luồng **theo dõi đơn**, độc lập với browse-to-checkout của Material, guest checkout của Lab và Assignment.

## 🧰 Điều kiện chạy lại

Mở `starter/NovaShop_Project_Brief.md`, `starter/NovaShop_Synthetic_Data.csv` và một bản làm việc của template Story Map. Dùng Markdown/whiteboard bất kỳ trong ENV-PRO-ARTIFACT. Không cần code, tài khoản hay dịch vụ thật.

## Case Study 01 — Giảm yêu cầu hỏi trạng thái đơn

### 1. Ticket và tiêu chí thành công

- **Stakeholder:** người mua cần biết đơn đang ở đâu; Customer Service muốn giảm yêu cầu tra cứu thủ công.
- **Vấn đề:** `OBS-04` ghi 6/15 yêu cầu mô phỏng liên quan trạng thái đơn. NovaShop cần kiểm chứng một hành trình tự tra cứu nhỏ mà không mở rộng sang hoàn tiền hoặc thay đổi đơn.
- **Input:** `FR-04`; actor đã đăng nhập; ba trạng thái sandbox `confirmed`, `packing`, `shipped`; constraint chỉ hiển thị đơn thuộc tài khoản mô phỏng.
- **Thành công:** backbone phủ từ mở lịch sử đến hiểu trạng thái; mỗi PBI có Goal/journey link; lát đầu tạo được outcome end-to-end; criteria có success và unauthorized/failure behavior.

### 2. Trạng thái ban đầu và lựa chọn

Customer journey sau mua gồm: **mở tài khoản → tìm đơn → xem trạng thái → quyết định có cần hỗ trợ**. Có ba lựa chọn:

1. xây toàn bộ cổng Customer Service — phạm vi vượt xa mục tiêu;
2. chỉ tạo bảng trạng thái ở backend — không tạo outcome cho người mua;
3. tạo lát dọc để người mua đã đăng nhập thấy danh sách đơn của mình, mở một đơn và thấy trạng thái/thời điểm cập nhật.

Nhóm chọn phương án 3. Trade-off là chưa có timeline chi tiết, push notification hay yêu cầu hỗ trợ trong lát đầu; đổi lại đội có thể kiểm chứng self-service và quyền truy cập sớm.

### 3. Artifact triển khai

#### Story Map

| Backbone | Truy cập lịch sử | Chọn đơn | Hiểu trạng thái | Quyết định tiếp theo |
| --- | --- | --- | --- | --- |
| User task | Mở “Đơn của tôi” | Chọn mã đơn | Xem trạng thái và thời điểm cập nhật | Biết đơn đang xử lý hay đã giao |
| **Slice TRACK-1** | Danh sách đơn thuộc actor | Mở một đơn hợp lệ | Hiển thị `confirmed/packing/shipped` | Hiển thị mô tả ngắn, không mở ticket |
| Later | Tìm theo ngày | Lọc theo trạng thái | Timeline vận chuyển | Liên hệ hỗ trợ |

#### Product Backlog excerpt

| PBI | Actor/outcome + trace | Acceptance examples | Evidence |
| --- | --- | --- | --- |
| PBI-TRK-01 | Người mua thấy các đơn của chính mình; `PG-NS-01 → J-HISTORY` | **Happy:** Given tài khoản A có hai đơn, When mở lịch sử, Then chỉ hai mã đơn A xuất hiện. **Edge:** Given A chưa có đơn, Then trạng thái rỗng có thông báo quan sát được. | Snapshot danh sách cùng actor synthetic |
| PBI-TRK-02 | Người mua hiểu trạng thái một đơn; `PG-NS-01 → J-STATUS` | **Happy:** Given đơn A-01 ở `packing`, When mở chi tiết, Then trạng thái và thời điểm cập nhật xuất hiện. **Failure:** Given actor A yêu cầu mã của B, Then chi tiết đơn B không xuất hiện và có kết quả từ chối. | Ma trận actor/order/result và snapshot kết quả |

### 4. Cách xác minh và expected output

Reviewer lập ma trận sau:

| Check | Oracle | Expected |
| --- | --- | --- |
| Journey coverage | Mỗi backbone có ít nhất một task trong TRACK-1 | 4/4 backbone được phủ |
| Traceability | Mỗi PBI có Product Goal và journey ID | 2/2 PBI resolve |
| Verticality | Một actor có thể đi từ lịch sử đến trạng thái | Không phụ thuộc “phase UI/API sau” |
| Happy criteria | Mỗi PBI có state, event, result | 2/2 đạt |
| Edge/failure | Empty history và cross-account được mô tả | 2 behavior quan sát được |
| Boundary | Không có refund, edit order, notification | 0 mục ngoài phạm vi |

Artifact **PASS** khi sáu hàng đều đạt. Nếu trace resolve nhưng TRACK-1 thiếu “Hiểu trạng thái”, kết quả là **REVISE** vì slice dừng ở danh sách và chưa tạo outcome đầy đủ.

### 5. Giải thích sâu, failure modes và trade-off

Story map giữ thứ tự hành vi sau mua; Product Backlog giữ nguồn work có thứ tự. Việc gộp PBI-TRK-01 và PBI-TRK-02 thành một lát phát hành không có nghĩa cả hai là một PBI khổng lồ: mỗi PBI vẫn có outcome và oracle riêng, còn slice trả lời câu hỏi “tập nhỏ nào đủ để người mua tự hiểu trạng thái?”.

- **Failure:** thẻ “xây order-status API” xuất hiện như PBI. Dấu hiệu là không có actor/result. Cách sửa là đưa nó vào plan “how” của PBI outcome tương ứng.
- **Failure:** criteria ghi “bảo mật tốt”. Dấu hiệu là không phân biệt được tài khoản A/B. Cách sửa là dùng actor/order matrix và outcome từ chối quan sát được.
- **Failure:** thêm hoàn tiền để “đủ journey”. Dấu hiệu là không truy vết tới ticket và boundary. Cách sửa là đưa vào later slice hoặc loại khỏi Product Goal hiện tại.

Trade-off chính là phạm vi nhỏ hơn nhưng feedback sớm hơn. Lát đầu không chứng minh rằng yêu cầu Customer Service thực sự giảm; nó chỉ tạo capability và event/evidence để kiểm chứng ở vòng sau.

### 6. Bài học chuyển giao

Không bắt đầu slicing từ component. Hãy bắt đầu bằng actor, outcome, journey và evidence; sau đó viết oracle độc lập với implementation. Trong Lab, học viên đổi actor sang guest và xử lý địa chỉ không hợp lệ. Trong Assignment, học viên nhận change request cùng ràng buộc dữ liệu riêng và phải tự tạo artifact; case này không cung cấp đáp án cho hai tình huống đó.

## Provenance của các case

- **SRC-SG20** — [The Scrum Guide](https://scrumguides.org/scrum-guide.html) (Ken Schwaber, Jeff Sutherland / ScrumGuides.org; November 2020; accessed 2026-08-25; CC BY-SA 4.0; adapt).
- **SRC-USER-STORIES** — [User Stories](https://agilealliance.org/glossary/user-stories/) (Agile Alliance; living snapshot 2026-08-25; accessed 2026-08-25; website terms; reference).
- **SRC-STORY-MAP** — [User Story Mapping](https://www.oreilly.com/library/view/user-story-mapping/9781491904893/) (Jeff Patton / O'Reilly Media; September 2014; accessed 2026-08-25; copyright, bibliographic reference/paraphrase only; reference).
- **SRC-GHERKIN** — [Gherkin Reference](https://cucumber.io/docs/gherkin/reference/) (Cucumber; living snapshot 2026-08-25; accessed 2026-08-25; documentation terms; reference).

Case, ID và số liệu là simulated. `OBS-04` cùng yêu cầu NovaShop chỉ là project input/fixture do `plan.project` quản lý, không phải source ref hay nguồn provenance bổ sung. Không có tuyên bố dự án thật; phần kiến thức chỉ dùng bốn nguồn đã liệt kê.

---
<!-- QUALITY GATE: CASE-U04-01 map đủ LO/outline; input, constraint, artifact, expected output, validation, trade-off và failure modes riêng; không còn chỉ dẫn khung. -->

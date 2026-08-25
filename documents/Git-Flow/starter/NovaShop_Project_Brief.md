# NovaShop — Project Brief mô phỏng

## Tuyên bố sử dụng

NovaShop là tình huống đào tạo **simulated** được tạo riêng cho khóa học. Tên doanh nghiệp, người dùng, số liệu, giao dịch và sự kiện đều là giả lập; không đại diện cho khách hàng có thật. Chỉ dùng payment, shipping và email sandbox; không dùng tiền thật, dữ liệu thẻ, PII hay credential production.

## Bối cảnh

NovaShop bán mỹ phẩm và sản phẩm chăm sóc cá nhân. Đơn từ mạng xã hội đang được nhân viên nhập lại bằng tay, gây chậm xử lý và khó theo dõi funnel. Sponsor muốn một MVP web responsive để chuẩn hóa hành trình từ tìm sản phẩm đến xác nhận đơn.

Các target đào tạo trong ba tháng sau release mô phỏng:

- tăng 20% số đơn trực tuyến so với baseline giả lập;
- giảm thời gian xử lý một đơn từ 15 xuống dưới 5 phút;
- ít nhất 95% đơn hợp lệ đi tới đóng gói mà không cần nhập lại;
- quan sát được conversion, cart abandonment và order success.

Các target trên là điều kiện của scenario, không phải benchmark ngành hay kết quả kinh doanh đã đạt.

## Stakeholders và nhu cầu

| Stakeholder | Nhu cầu/decision | Evidence mong đợi |
| --- | --- | --- |
| Business Sponsor | Quyết định tiếp tục đầu tư và thời điểm release | Outcome trend, risk và forecast có bất định |
| Product Owner | Một Product Goal và một Product Backlog minh bạch | Goal-to-PBI traceability và ordering rationale |
| Người mua | Tìm, mua và theo dõi đơn với ít ma sát | Journey evidence và acceptance examples |
| Kho vận | Nhận đơn hợp lệ, không nhập lại | Order validation và audit evidence |
| Customer Service | Tra cứu trạng thái và xử lý ngoại lệ | Status history và correlation evidence |
| Security/Accessibility reviewer | Biết chính xác phạm vi chất lượng đã kiểm | Evidence theo requirement được chọn, không có tuyên bố quá mức |

## Ranh giới sản phẩm

Trong phạm vi: catalog/search/filter, account/address, cart/promotion, checkout, payment và shipping sandbox, xác nhận/theo dõi đơn, admin sản phẩm–tồn kho–đơn, analytics events.

Ngoài phạm vi: marketplace đa nhà bán, mobile native, ERP/kế toán đầy đủ, tiền/thẻ thật, AI recommendation, loyalty program và hoàn tiền phức tạp.

## Yêu cầu cốt lõi

| ID | Yêu cầu | Oracle tối thiểu |
| --- | --- | --- |
| FR-01 | Xem, tìm kiếm và lọc sản phẩm | Kết quả phản ánh từ khóa và bộ lọc |
| FR-02 | Quản lý giỏ hàng và mã giảm giá | Tổng tiền cập nhật; mã sai có thông báo |
| FR-03 | Checkout với địa chỉ, vận chuyển và payment sandbox | Đơn hợp lệ sinh mã; lỗi validation không làm mất input |
| FR-04 | Xem lịch sử và trạng thái đơn | Chỉ trả đơn thuộc tài khoản mô phỏng |
| FR-05 | Admin cập nhật sản phẩm, tồn kho và trạng thái đơn | Thay đổi trạng thái có audit evidence |
| FR-06 | Ghi nhận funnel events | Event có tên, thời điểm, anonymous session và outcome |

| ID | Loại | Yêu cầu/giới hạn |
| --- | --- | --- |
| NFR-01 | Performance | Catalog dưới 2 giây trong tải mô phỏng đã ghi rõ |
| NFR-02 | Accessibility | Chỉ đánh giá tập success criteria WCAG 2.2 AA được chọn; không tuyên bố conformance toàn diện |
| NFR-03 | Security | Không lưu dữ liệu thẻ; phân quyền customer/admin; chỉ kiểm subset ASVS 5.0.0 được chỉ định |
| NFR-04 | Reliability | Checkout failure giữ input và có correlation evidence |
| NFR-05 | Compatibility | Responsive mobile/desktop trên test matrix mô phỏng |

## Constraints xuyên khóa

- Bốn Sprint mô phỏng; capacity và sự kiện thay đổi theo scenario card.
- Backlog có thể thích nghi sau inspection; Product Goal chỉ đổi khi evidence làm mục tiêu không còn phù hợp.
- Không giảm Definition of Done để cứu forecast.
- User story, story point, Planning Poker, story map và Kanban flow metrics là thực hành bổ trợ, không phải thành phần bắt buộc của Scrum.
- Forecast là dự báo dựa trên dữ liệu và assumptions, không phải guarantee.

## Definition of Done dùng trong scenario

Một PBI chỉ được gọi là Done khi acceptance criteria đạt, evidence review/test theo phạm vi có sẵn, không còn lỗi Critical/High, tài liệu liên quan được cập nhật, không có secret/PII và kết quả usable để inspection. Công việc không đạt toàn bộ DoD trở lại Product Backlog; Sprint Review không biến nó thành Done.

## Change cards dùng cho thực hành

- CR-01: Sponsor muốn Product Owner phê duyệt mọi quyết định kỹ thuật và Daily Scrum thành status report.
- CR-02: Thêm guest checkout nhưng vẫn phải có địa chỉ giao hàng hợp lệ.
- CR-03: Capacity Sprint giảm 30%; payment sandbox bảo trì ngày 2.
- CR-04: Checkout chưa đạt keyboard navigation nhưng sponsor muốn demo như Done.
- CR-05: Phí vận chuyển mới xuất hiện sau Sprint Review.
- CR-06: Flow data có một outlier và rủi ro payment chưa đóng trước quyết định release.

## Provenance

Artifact này do khóa học tạo và được phép dùng nội bộ cho người học. Kiến thức Scrum phải được đối chiếu với Scrum Guide 2020; quality examples chỉ dùng phạm vi đã chọn của WCAG 2.2 và OWASP ASVS 5.0.0.

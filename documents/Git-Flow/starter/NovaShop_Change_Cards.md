# NovaShop — Change Cards cho Git Flow Labs và Assignments

> Toàn bộ tình huống, mã đơn, trạng thái thanh toán và dữ liệu nghiệp vụ trong file này là synthetic. Không dùng credential, endpoint hay dữ liệu khách hàng thật.

## CARD-U01 — Repo chưa có workflow

- Baseline: Project brief và backlog nằm trong một thư mục chưa version hóa.
- Change: Tạo repository artifact có `main`, `develop`, tag baseline và working agreement.
- Constraint mới: Sponsor muốn thêm branch `qc` dài hạn; nhóm phải đánh giá yêu cầu này theo branch-role oracle thay vì chấp nhận mặc định.
- Evidence bắt buộc: graph, refs và routing table.

## CARD-U02-LAB — NS-102 Cart Promotion

- Baseline: `develop` chứa Search specification đã review.
- Change: Bổ sung Cart Promotion specification và acceptance evidence.
- Review finding: Quy tắc mã giảm giá hết hạn chưa có failure example.
- Constraint: Finding severity `error` phải đóng trước merge.
- Không cung cấp lời giải: học viên tự quyết định commit boundaries và review disposition.

## CARD-U02-ASM — NS-202 Payment Failure

- Baseline: starter artifacts và Git Flow working agreement.
- Change: Đặc tả trạng thái failure của payment sandbox.
- Edge case: sandbox trả cùng một mã lỗi hai lần nhưng checkout input vẫn phải được giữ.
- Evidence: feature dossier và pull-request review record.

## CARD-U03-LAB — Checkout × Payment Conflict

- Hai feature cùng sửa ma trận trạng thái trong `project-artifacts/checkout/payment-status.csv`.
- Checkout thêm trạng thái `ADDRESS_INVALID`; Payment thêm `DECLINED_RETRYABLE`.
- Business oracle: cả hai trạng thái phải tồn tại, dùng ID duy nhất và không đổi nghĩa trạng thái đã phê duyệt.
- Học viên phải lưu evidence trước conflict, quyết định resolution và graph sau merge.

## CARD-U03-ASM — NS-303 Shared Audit Field

- Checkout và Admin định nghĩa khác nhau cho `changed_by`.
- Constraint: schema sau tích hợp có một định nghĩa canonical nhưng vẫn giữ acceptance criteria của cả FR-03 và FR-05.
- Shared-history condition: một branch đã được peer khác fetch; không rewrite branch đó.
- Deliverable downstream: integration evidence pack và conflict decision log.

## CARD-U04-LAB — Order Tracking + Admin Release

- Release candidate dự kiến: Search, Cart, Checkout, Payment, Order Tracking và Admin cơ bản.
- UAT finding: wording `Delivered` bị dùng cho trạng thái chưa bàn giao.
- Scope pressure: sponsor đề nghị thêm bulk export sau khi scope freeze.
- Oracle: release fix được phép; bulk export quay lại Product Backlog cho release sau.

## CARD-U04-ASM — RC-401

- Baseline: integration dossier đã phê duyệt.
- Finding: glossary của Order Tracking không nhất quán.
- Compatibility contract: CSV column ID và status ID đã công bố cho sandbox consumers; wording mô tả có thể sửa mà không đổi ID.
- Release decision chỉ PASS khi UAT finding đóng và tag chưa được tạo sớm.

## CARD-U05-LAB — HOTFIX-301 Shipping Fee

- Production baseline: tag `v0.1.0`.
- Develop đã có thay đổi Admin cho phiên bản kế tiếp.
- Incident: bảng phí synthetic áp sai ngưỡng miễn phí.
- Oracle: fix chỉ sửa rule phí, có regression evidence và xuất hiện trong `main` lẫn `develop`.

## CARD-U05-ASM — INC-501 với release đang mở

- Production baseline: `v0.1.0`.
- Dòng tương lai: `release/0.2.0` đang UAT và `develop` đã tiến thêm.
- Incident: duplicate payment request trên sandbox có thể tạo hai order artifacts.
- Oracle: hotfix từ `main`; patch tag sau regression; fix vào `main` và release đang mở, sau đó tới `develop` khi release hoàn tất.

## CARD-U06 — Audit scenario

Lịch sử audit fixture có sáu dấu hiệu cần phân loại:

1. Direct commit vào `main` không có review record.
2. Feature bắt đầu từ `main` thay vì `develop`.
3. Release tag là lightweight trong khi policy yêu cầu annotated.
4. Release fix chưa xuất hiện trong `develop`.
5. Shared feature branch bị rebase và force-push trong evidence log.
6. Working agreement ghi “Sprint Review là release gate bắt buộc của Scrum”.

Học viên phải phân biệt vi phạm Git, vi phạm team policy và phát biểu sai về Scrum; mỗi finding có evidence, severity, owner và remediation.

## CARD-CAP — NovaShop v0.2.0 và v0.2.1

- Release scope: `CAP-601` Bulk Update và phần Order Tracking đã Done.
- Change pressure: một PBI chưa đủ review evidence không được đưa vào release.
- Incident sau release: `CAP-602` khiến timeline trạng thái đi lùi.
- Final decision: nhóm viết ADR tiếp tục Git Flow hoặc chuyển flow đơn giản hơn dựa trên release cadence, số version hỗ trợ, lead time và merge cost.

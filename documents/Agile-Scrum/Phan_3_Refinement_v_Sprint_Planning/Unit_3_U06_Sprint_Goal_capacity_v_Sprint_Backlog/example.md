# Unit U06: Sprint Goal, capacity và Sprint Backlog — Ví dụ và nghiên cứu tình huống

> **Case ID:** CASE-U06-01 · **LO:** LO6.1, LO6.2 · **Outline:** OUT-U06-01, OUT-U06-02 · **Xác thực:** simulated

## 🎯 Learning Outcomes liên quan

- **LO6.1 / OUT-U06-01:** Sprint Goal và evidence-based forecast.
- **LO6.2 / OUT-U06-02:** Sprint Backlog why/what/how có dependency/evidence/response.

**Project increment:** M-U06, tạo Sprint Goal và Sprint Backlog làm baseline cho execution/quality inspection.

## 🧰 Điều kiện chạy lại

Dùng ENV-PRO-ARTIFACT (Markdown CommonMark/bảng tính CSV UTF-8/whiteboard), project brief, synthetic CSV và template Sprint Planning. Không cần code/service/credential. Verification là artifact review theo năm oracle ở mục 5.

## Case Study 01 — Sprint inventory visibility khi có support duty

### 1. Ticket và tiêu chí thành công

Kho vận cần một thay đổi stock synthetic được người mua nhìn thấy mà không mất audit evidence (`FR-01`, `FR-05`). Đây là case admin–catalog, độc lập với checkout/capacity example trong Material và payment-maintenance Lab/Assignment.

Thành công khi Sprint Goal mô tả một outcome thống nhất; forecast dựa trên backlog order, lịch sử, upcoming capacity và DoD; Sprint Backlog có why/what/how, dependency/evidence/risk; một support incident không dẫn tới hạ DoD.

### 2. Input, baseline và constraints

- Product Goal: tăng tỷ lệ đơn hợp lệ, giảm xử lý lại; stock accuracy là guardrail cho journey.
- Product Backlog v2: `INV-701 Admin stock update + audit=8`, `INV-702 Buyer sees refreshed stock=5`, `INV-703 Inventory analytics event=3`, `INV-704 Bulk import=13`.
- Lịch sử ba Sprint tương đồng: 13, 15, 14 relative units Done.
- Upcoming capacity: đội tương tự lịch sử nhưng một Developer trực support tối đa 2 ngày; không biết incident có xảy ra.
- Dependency: catalog refresh sandbox sau admin event; bulk import không cần cho outcome đầu.
- DoD: acceptance evidence, audit evidence, no Critical/High, docs updated, no PII/secret.

### 3. Phân tích lựa chọn

Ba Sprint Goal candidate:

1. “Hoàn thành INV-701, INV-702 và INV-703” — là scope list, không phải objective.
2. “Cải thiện tồn kho” — quá mơ hồ, không có actor/outcome/oracle.
3. “Cho phép một stock change synthetic có audit được phản ánh thành trạng thái còn/hết hàng quan sát được cho người mua.”

Chọn candidate 3. Core scope `INV-701+INV-702=13`, đúng lower edge lịch sử; `INV-703=3` là negotiable nếu support duty không xảy ra và core evidence an toàn. `INV-704` ở ngoài Sprint. Đây là judgment có assumptions, không phải point/day formula.

### 4. Artifact triển khai

#### Why/What canvas

- **Sprint Goal:** candidate 3 ở trên.
- **Forecast core:** INV-701, INV-702; **negotiable:** INV-703.
- **Evidence basis:** lịch sử 13–15, cùng team/reference/DoD; support duty có thể giảm availability; dependencies của core đã biết.
- **Assumptions:** một SKU synthetic; admin role available; refresh sandbox nhận event; no bulk import.
- **Boundary:** drop INV-703 trước; không bỏ audit hoặc catalog evidence; không đưa INV-704 vào khi core chưa đạt.

#### Sprint Backlog

| Why | What | How | Dependency/trigger | Evidence/DoD | Risk response |
| --- | --- | --- | --- | --- | --- |
| Tạo stock change có audit | INV-701 | Làm rõ valid/invalid update; tạo synthetic fixture; chuẩn bị audit review; thực hiện increment theo skill của đội | Admin reviewer; inspect cuối D1 | Before/after stock, actor role, audit evidence, docs | Nếu support incident mở, swarm vào core; không bỏ audit |
| Buyer thấy trạng thái mới | INV-702 | Xác nhận refresh contract; sequence after one valid event; capture storefront status | INV-701 valid event; refresh owner; trigger D3 | SKU/state khớp, catalog evidence, DoD checks | Nếu refresh trễ, dùng fixture để chẩn đoán nhưng fixture-only không đủ Done |
| Có funnel signal bổ sung | INV-703 negotiable | Làm rõ event fields sau core | Core evidence; decision D5 | Event name/time/session/outcome nếu được chọn | Bỏ item nếu support/core risk tăng; Goal không đổi |

### 5. Expected output và validation

Artifact review PASS khi:

1. Goal là một outcome, link Product Goal và vẫn có nghĩa nếu INV-703 bị bỏ.
2. Forecast nêu history/capacity/DoD/assumptions; không guarantee hoặc conversion.
3. Core 13 và negotiable 3 được phân biệt; INV-704 nằm ngoài scope.
4. 3/3 row có why/what/how, dependency/trigger, evidence/DoD và response.
5. Edge test “support incident dùng trọn 2 ngày”: expected response là drop INV-703/re-plan how, giữ Goal, audit và quality evidence; nếu core không còn forecast được thì impact minh bạch.

Nếu Goal đổi thành “xong core PBI” hoặc team bỏ audit để giữ INV-703, case REVISE.

### 6. Trade-off, failure modes và chuyển giao

Scope 13 có thể trông bảo thủ so với lịch sử 13–15, nhưng capacity risk chưa biết và Goal cần hai PBI liên kết. Kéo INV-703 sớm làm tăng WIP mà không hoàn tất outcome core. Ngược lại, giữ nó negotiable tránh biến uncertainty thành idle buffer: team có lựa chọn khi evidence tốt.

- **Failure:** manager gán toàn bộ task ở Planning; dấu hiệu plan không thể swarm khi support incident. Sửa bằng plan bởi Developers và owner/trigger thay cho assignment cứng.
- **Failure:** fixture được dùng để tuyên bố Done; dấu hiệu thiếu refresh integration evidence thuộc DoD. Sửa bằng ghi rõ fixture chỉ chẩn đoán.
- **Failure:** Goal quá rộng gồm bulk import; dấu hiệu core + INV-704 vượt evidence range và không có single outcome nhỏ. Sửa bằng boundary.

Nguyên tắc chuyển giao: dùng Goal để bảo vệ outcome, forecast để minh bạch uncertainty, Sprint Backlog để cho thấy next decision. Lab sẽ dùng backlog/order-status cùng payment maintenance; không copy artifact case này.

## Provenance của các case

- **SRC-SG20** — [Scrum Guide](https://scrumguides.org/scrum-guide.html) (ScrumGuides.org; November 2020; accessed 2026-08-25; CC BY-SA 4.0; adapt).
- **SRC-SPRINT-PLANNING** — [Introduction to Sprint Planning](https://www.scrum.org/resources/introduction-sprint-planning) (Scrum.org; living snapshot/accessed 2026-08-25; website terms; reference).
- **SRC-FORECAST** — [Forecasting and Release Planning](https://www.scrum.org/resources/introduction-forecasting-and-release-planning) (Scrum.org; living snapshot/accessed 2026-08-25; website terms; reference).
- **SRC-PROJECT** — NovaShop project brief (`starter/NovaShop_Project_Brief.md`; training artifact v1.0; accessed 2026-08-25; internal approved).

PBI, history, capacity và incident là simulated; không phải performance/team benchmark. Không dùng nguồn bổ sung.

---
<!-- QUALITY GATE: CASE-U06-01 độc lập, đủ input/constraint/artifact/expected/validation/trade-off/failure, map đủ LO/outline. -->

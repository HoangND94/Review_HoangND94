# Hands-on Lab LAB-U07-01 — Mô phỏng Sprint nén và xử lý sự cố

| Thuộc tính | Giá trị |
| --- | --- |
| Unit | U07 — Daily Scrum, flow và impediment |
| Thời lượng | 90 phút |
| Hình thức | guided_with_fading |
| Mức xác thực | simulated |

## 🎯 Learning Outcomes được thực hành

- **LO7.1:** `CP-U07-01`, evidence `Daily_Scrum_D2.md` + board trước/sau.
- **LO7.2:** `CP-U07-01`, `CP-U07-02`, evidence `Impediment_Log.md` + `Change_Impact.md`.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

- **MEX-U07-01 → CP-U07-01, CP-U07-02.** Lab tái tạo cấu trúc quyết định với fixture khác; không sao chép artifact mẫu.

## Project slice, môi trường và safety

Từ Sprint Backlog của M-U06, nhóm vận hành ba ngày nén cho checkout. Chỉ dùng Markdown/CSV và fixture nhúng; không gọi sandbox thật, không dùng PII/credential. Giữ `Product Goal` và `DOD-NS-1.0`; được đổi Sprint Backlog/board nhưng không hạ quality.

Starter assets: bản sao read-only của `NovaShop_Project_Brief.md`, `NovaShop_Synthetic_Data.csv`, `Artifact_Templates.md`. Nếu chưa được cung cấp, dùng bảng dưới đây làm baseline đầy đủ.

### Baseline ngày 2, 09:00

Sprint Goal `SG-L7`: “người mua hoàn thành checkout sandbox; payment decline không làm mất địa chỉ đã nhập”. WIP policy: `In Progress + Verify`, limit 3.

| ID | State | Age | Evidence/constraint |
| --- | --- | ---: | --- |
| L7-21 address persistence | Verify | 2 ngày | happy-path 6/6 PASS; decline-path chưa chạy |
| L7-22 payment adapter | In Progress | 1 ngày | sandbox latency 3s, dưới ngưỡng scenario 5s |
| L7-23 order confirmation | In Progress | 1 ngày | peer review PASS |
| L7-24 promo banner | Ready | 0 | không thiết yếu cho SG-L7 |

## 📋 Lab outline và Definition of Done

PASS khi CP-U07-01 và CP-U07-02 đều có đủ chuỗi input→evidence→decision→board diff; mọi action có owner/review time; WIP count tái tính được; DoD ID không đổi; không có item thiếu evidence bị gọi Done. Mỗi checkpoint phải lưu bản trước/sau, checklist PASS/REVISE và reset note.

## Checkpoint 0 — Baseline và safety check

1. **Why:** bảo vệ starter asset và tránh ra quyết định từ dữ liệu thiếu.
2. **Action:** tạo thư mục làm việc `lab-u07/`; tạo bản sao nội dung baseline vào `Board_D2_0900.md`; ghi `fixture=embedded-simulated-v1`, `DOD=DOD-NS-1.0` và Sprint Goal ở đầu file.
3. **Explanation:** ID/version giúp reviewer phân biệt lỗi input với lỗi quyết định; starter asset không bị sửa.
4. **Verify:** mở file và đối chiếu đủ bốn item, state, age, evidence; tái tính WIP theo policy.
5. **Expected result:** WIP = 3/3; mọi ID duy nhất; không có dữ liệu thật.
6. **Evidence:** `E0_Baseline_Check.md` ghi 4/4 dòng khớp, WIP=3, safety=PASS.
7. **Troubleshooting:** nếu WIP khác 3, đánh dấu những state thuộc policy rồi đếm lại; nếu thiếu asset, không tìm dữ liệu ngoài mà dùng fixture nhúng.
8. **Reset/rollback:** xóa nội dung bản làm việc sai và tạo lại từ bảng nhúng; xác nhận checksum logic bằng WIP=3 và 4 ID.

## CP-U07-01 — Tạo Daily plan từ board mới

**material_example_refs:** `MEX-U07-01` · **LO:** LO7.1, LO7.2.

1. **Why:** biến inspection thành kế hoạch ngày cụ thể, hướng `SG-L7`.
2. **Action:** trong tối đa 15 phút, nhóm chọn facilitator/timekeeper; đọc Goal; nêu tối đa ba signal từ baseline; ghi `Daily_Scrum_D2.md` với progress/risk, adaptation, owner, review time và parking lot.
3. **Explanation:** signal phải là state/age/evidence; không dùng phán xét cá nhân. Ít nhất hai option phải được cân nhắc trước khi chọn.
4. **Action:** tạo `Impediment_Log.md`; nếu xem decline-path chưa chạy là trở ngại, ghi evidence đang thiếu, impact tới Goal, owner/action và thời điểm kiểm lại. Cập nhật bản sao board theo adaptation.
5. **Explanation:** “thiếu test” có thể là work còn lại chứ chưa chắc impediment; log phải nêu điều kiện khiến công việc không thể tiến.
6. **Verify:** reviewer chạy checklist: Goal hiện diện; timebox ≤15; WIP trước/sau tái tính được; action có owner/review; parking lot tách thảo luận sâu; DoD vẫn `DOD-NS-1.0`.
7. **Expected result:** artifact đủ trường, khác MEX về IDs/input/decision; board diff nhất quán; không kéo `L7-24` nếu chưa chỉ ra impact có lợi tới Goal.
8. **Evidence:** `E1_CP-U07-01.md`, `Board_D2_After.md`, `Daily_Scrum_D2.md`, `Impediment_Log.md`; kết luận PASS hoặc REVISE kèm finding.
9. **Troubleshooting:** nếu nhóm bất đồng, ghi Option A/B và dùng `Goal impact + WIP + quality guardrail` làm oracle; nếu action chung chung, thêm owner và giờ; nếu count sai, đối chiếu state policy.
10. **Reset/rollback:** giữ `E0`; khôi phục board từ `Board_D2_0900.md`, đổi tên artifact lỗi thành `.revise`, rồi chạy lại checkpoint.

## CP-U07-02 — Failure/change path: outage kéo dài và yêu cầu bắt đầu việc mới

**material_example_refs:** `MEX-U07-01` · **LO:** LO7.1, LO7.2 · **Biến thể mới:** input xuất hiện sau quyết định CP-01.

Change card lúc 11:30: `EV-L7-OUTAGE` — payment sandbox sẽ unavailable đến hết ngày; Sponsor đề nghị kéo `L7-24 promo banner` để “giữ utilization”. Một Developer phát hiện decline fixture có thể chuẩn bị offline nhưng execution phải chờ sandbox.

1. **Why:** kiểm tra khả năng thay đổi plan khi giả định CP-01 sai mà không tối ưu utilization hay phá DoD.
2. **Action:** ghi `Change_Impact.md` gồm assumption bị vô hiệu, Goal impact, các item bị ảnh hưởng, ít nhất hai option và quality guardrail.
3. **Explanation:** outage kéo dài là evidence mới; nó không tự động làm Sprint Goal obsolete và không cho phép gọi item chưa verified là Done.
4. **Action:** cập nhật `Impediment_Log.md` với event-card link, escalation owner, next review; cập nhật board/plan. Nếu kéo `L7-24`, phải chứng minh không tăng WIP vượt policy và lợi ích tới Goal; nếu không kéo, ghi trade-off về utilization.
5. **Explanation:** decision phải tối ưu progress-to-goal/learning, không phải số người bận. Có thể chuẩn bị fixture offline, swarm item không phụ thuộc, hoặc cộng tác Product Owner về scope trong khi giữ Goal/DoD.
6. **Verify:** so diff CP-01→CP-02; mọi thay đổi có rationale; WIP ≤3; `DOD-NS-1.0` không đổi; `L7-21/L7-22` không Done nếu thiếu decline execution; next review có giờ.
7. **Expected result:** change request được xử lý nhất quán; plan mới thừa nhận phần chưa thể verify, có action/review và trade-off; không có “Done giả”.
8. **Evidence:** `E2_CP-U07-02.md`, `Change_Impact.md`, board snapshot mới, impediment log diff.
9. **Troubleshooting:** nếu chỉ ghi “chờ”, kiểm xem có preparation/clarification độc lập nào tạo learning; nếu hạ DoD, rollback ngay; nếu Goal thực sự không còn hợp lệ, ghi evidence và chuyển quyết định hủy Sprint cho Product Owner—không tự hủy trong Lab.
10. **Reset/rollback:** khôi phục bản CP-01, áp lại change card từng liên kết; không sửa/xóa `EV-L7-OUTAGE` để làm kết quả đẹp hơn.

## ♻️ Reset, cleanup và khả năng chạy lại

Áp dụng mục **Reset/rollback** của từng checkpoint; chỉ khôi phục bản làm việc, giữ starter assets read-only và giữ nguyên evidence/change card gốc.

## 🧪 Final validation

Peer reviewer chấm các oracle sau:

- `L7-O1` — CP-01 và CP-02 đều trỏ `MEX-U07-01`, LO và đúng evidence file.
- `L7-O2` — Daily record có Goal, ≤15 phút, actionable plan và parking lot.
- `L7-O3` — WIP count khớp board ở cả ba snapshot.
- `L7-O4` — impediment có evidence/impact/owner/action/review.
- `L7-O5` — outage change có impact note và plan diff; DoD không đổi; không item thiếu evidence được gọi Done.
- `L7-O6` — fixture synthetic, không PII/secret; starter asset không bị sửa.

Exit condition: 6/6 PASS. Nếu có REVISE, lưu finding, reset checkpoint liên quan và review lại; không tự khai PASS.

## Deliverables và tái sử dụng

Nộp thư mục `lab-u07/` gồm baseline, hai board diff, Daily record, impediment log, change impact và ba evidence checklist. Giữ lại `Daily_Scrum_D2.md`, `Impediment_Log.md` và adaptation decision cho Capstone `CAP-01`; U08 dùng cách ghi evidence, không dùng các file này như lời giải Assignment.

## Provenance

Scrum event/quality rules: SRC-SG20 và SRC-EVENTS; flow practices: SRC-KANBAN-SCRUM. Fixture và change card: **[BỔ SUNG — nguồn: SRC-PROJECT, dữ liệu mô phỏng cho khóa học]**.

# Hands-on Lab LAB-U09-01 — Retrospective từ dữ liệu flow và sự kiện đội

| Thuộc tính | Giá trị |
| --- | --- |
| Unit | U09 — Retrospective và cải tiến đội |
| Thời lượng | 90 phút |
| Hình thức | guided_with_fading |
| Mức xác thực | simulated |

## 🎯 Learning Outcomes được thực hành

- **LO9.1:** `CP-U09-01`, `CP-U09-02`; evidence `Evidence_Map_L9.md`, `Causal_Map_L9.md`.
- **LO9.2:** `CP-U09-01`, `CP-U09-02`; evidence `Experiment_L9.md`, `Working_Agreement_v2_Lab.md`.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

- **MEX-U09-01 → CP-U09-01, CP-U09-02.** Lab dùng handoff/review fixture mới; CP-02 cung cấp evidence phản bác, không copy MEX.

## Project slice, môi trường và safety

Scrum Team điều tra cycle time tăng ở order tracking. Dùng Markdown/CSV và fixture synthetic; không thu thập dữ liệu hiệu suất cá nhân, PII hay secret. Causal conclusions phải ghi confidence/limitation. Improvement không được hạ `DOD-NS-1.0`.

Starter assets là bản sao read-only của project brief, flow dataset, Review record và Working Agreement v1. Nếu thiếu, fixture nhúng dưới đây là baseline đầy đủ.

### Fixture Sprint 4

| ID | Start | Ready for review | Review complete | Done | Rework | Event |
| --- | ---: | ---: | ---: | ---: | ---: | --- |
| OT-81 | D1 09:00 | D1 16:00 | D2 15:00 | D2 17:00 | 0h | reviewer queue 7h |
| OT-82 | D1 10:00 | D2 10:00 | D3 16:00 | D4 10:00 | 2h | reviewer queue 14h |
| OT-83 | D1 13:00 | D2 09:00 | D2 17:00 | D3 11:00 | 1h | reviewer queue 7h |
| OT-84 | D2 09:00 | D2 14:00 | D4 10:00 | D4 15:00 | 0h | reviewer unavailable D3 |
| OT-85 | D2 11:00 | D3 09:00 | D4 14:00 | D5 10:00 | 3h | reviewer queue 9h |

Event log `EV-REV-1`: một specialist thường là reviewer; Working Agreement v1 không có review rotation/response expectation. Review feedback U08 cho thấy audit evidence phải giữ nguyên, không được bỏ để giảm elapsed.

## 📋 Lab outline và Definition of Done

PASS khi symptom có cohort/window/unit; ít nhất hai cause hypotheses có support/against/unknown; không biến correlation thành proof hay quy lỗi cá nhân; experiment có owner/window/baseline/leading threshold/guardrail/review; Working Agreement v2 là trial version có expiry; CP-02 cập nhật tất cả artifact khi evidence mới xuất hiện.

## Checkpoint 0 — Baseline và safety check

1. **Why:** causal analysis sai nếu timestamps/unit hoặc provenance sai.
2. **Action:** tạo `lab-u09/`; chép fixture vào `Flow_Baseline_L9.md`; ghi `synthetic-v1`, timezone “scenario day”, data dictionary cho Start/Ready/Review/Done/Rework.
3. **Explanation:** đây là ngày/giờ mô phỏng; không suy ra benchmark thực tế hay năng suất cá nhân.
4. **Verify:** đủ OT-81…85, timestamp theo thứ tự hợp lệ, event log và `DOD-NS-1.0` hiện diện.
5. **Expected result:** 5 rows hợp lệ; PII/secret=0; starter asset không đổi.
6. **Evidence:** `E0_L9_Baseline.md` có row-count, schema check và PASS.
7. **Troubleshooting:** nếu timestamp thiếu, ghi UNKNOWN và loại phép tính phụ thuộc; không nội suy. Nếu timezone tranh cãi, dùng scenario-day nhất quán.
8. **Reset/rollback:** tạo lại bản làm việc từ fixture; giữ original read-only.

## CP-U09-01 — Evidence map, causal hypotheses và experiment

**material_example_refs:** `MEX-U09-01` · **LO:** LO9.1, LO9.2.

1. **Why:** tách symptom khỏi giải thích và tìm leverage point team kiểm soát.
2. **Action:** viết `Evidence_Map_L9.md`: chọn một symptom về elapsed/review wait với cohort/window; trích row/event IDs; ghi observation riêng khỏi interpretation.
3. **Explanation:** không bắt buộc công thức U10; chỉ cần timestamp/queue evidence tái kiểm được. Tránh “reviewer chậm” vì đó là nhãn người, không phải mechanism.
4. **Action:** viết `Causal_Map_L9.md` với tối thiểu H1 review queue/single-specialist và H2 rework/clarity hoặc hypothesis khác; mỗi H có evidence support, against/unknown, discrimination check và confidence.
5. **Explanation:** event `reviewer unavailable D3` có thể tạo outlier; một causal map tốt giữ alternative mở.
6. **Action:** chọn một leverage point và tạo `Experiment_L9.md` gồm hypothesis, cohort/window, baseline, intervention, owner, leading signal+threshold, quality/flow guardrails, review date và keep/change/revert rule. Cập nhật `Working_Agreement_v2_Lab.md` bằng trial rule link experiment.
7. **Explanation:** experiment phải kiểm hypothesis, không chỉ “giao tiếp tốt hơn”; guardrail phải giữ audit evidence/DoD.
8. **Verify:** peer reviewer lần evidence→hypothesis→leverage→experiment; kiểm ≥2 hypotheses; mọi field experiment/WA resolve; không có tên cá nhân ở cause node.
9. **Expected result:** causal claim có limitation; experiment đủ owner/signal/guardrail/review; WA v2 trial/reversible.
10. **Evidence:** `E1_CP-U09-01.md` cùng bốn artifact; PASS/REVISE và findings.
11. **Troubleshooting:** nếu chỉ có một hypothesis, tìm counter-example OT-84 hoặc rework rows; nếu signal không đo được, chọn count/share từ fixture; nếu owner làm tất cả, sửa thành decision owner + team behavior.
12. **Reset/rollback:** giữ baseline, đổi artifact lỗi thành `.revise`, quay lại symptom statement trước khi viết hypothesis lại.

## CP-U09-02 — Failure/change path: outage làm yếu hypothesis ban đầu

**material_example_refs:** `MEX-U09-01` · **LO:** LO9.1, LO9.2 · **Biến thể mới:** evidence phản bác xuất hiện sau CP-01.

Change card `EV-L9-OUTAGE`: log hệ thống cho thấy D3 09:00–15:00 review environment unavailable cho **mọi** reviewer; OT-82, OT-84 và OT-85 nằm trong window. Một second reviewer đã sẵn sàng nhưng cũng không truy cập được. Card được phát sau khi team đã nghi “single reviewer” là cause chính.

1. **Why:** học cách sửa causal claim/experiment khi evidence mới chống lại narrative ban đầu.
2. **Action:** tạo `Change_Impact_L9.md`: artifact/claim nào bị ảnh hưởng; support/confidence của từng hypothesis đổi thế nào; điều gì vẫn unknown.
3. **Explanation:** outage là mechanism chung, làm hypothesis single-reviewer yếu đi cho ba rows; nó không chứng minh queue/rotation không bao giờ quan trọng.
4. **Action:** cập nhật evidence map/causal map bằng `EV-L9-OUTAGE`; giữ audit trail phiên bản cũ. Quyết định giữ, sửa hoặc thay experiment; cập nhật signal/guardrail/WA trial tương ứng.
5. **Explanation:** nếu experiment rotation không còn test leverage chính, có thể sửa sang readiness/fallback environment/escalation trong sphere of control; không yêu cầu vendor “never fail”.
6. **Verify:** mọi causal claim bị ảnh hưởng có version/confidence mới; experiment mới trace tới hypothesis còn được support; WA link/expiry/review nhất quán; DoD/audit guardrail không đổi.
7. **Expected result:** team hạ hoặc sửa claim, không che evidence phản bác; experiment/WA downstream đồng bộ; limitation outage sample rõ.
8. **Evidence:** `E2_CP-U09-02.md`, impact note, before/after causal map, experiment diff, WA diff.
9. **Troubleshooting:** nếu team bảo vệ answer cũ, dùng discrimination question “second reviewer có làm giảm wait trong outage không?”; nếu sửa cause nhưng không experiment, lần impact table; nếu đề xuất bypass audit/test, rollback vì guardrail fail.
10. **Reset/rollback:** khôi phục CP-01; áp event card vào evidence map trước, rồi cập nhật hypothesis→experiment→WA theo thứ tự; không xóa version cũ.

## ♻️ Reset, cleanup và khả năng chạy lại

Áp dụng mục **Reset/rollback** của từng checkpoint; chỉ khôi phục bản làm việc, giữ starter assets read-only và giữ nguyên evidence/change card gốc.

## 🧪 Final validation

- `L9-O1`: MEX refs, LO và evidence files resolve ở cả hai checkpoint.
- `L9-O2`: symptom có cohort/window/unit và tái kiểm từ fixture.
- `L9-O3`: ≥2 hypotheses với support + against/unknown; people-as-cause = 0.
- `L9-O4`: experiment có baseline/intervention/owner/window/signal/threshold/guardrails/review/adaptation.
- `L9-O5`: WA v2 có version, trial link, effective window và expiry/review.
- `L9-O6`: outage được phản ánh trong causal confidence và mọi downstream artifact.
- `L9-O7`: DoD không giảm; synthetic/no PII/no unsupported causal claim.

Exit condition: 7/7 PASS từ peer review. REVISE phải giữ finding/version history rồi chạy lại checkpoint liên quan.

## Deliverables và tái sử dụng

Nộp baseline, evidence map, causal map before/after, experiment card, Working Agreement v2, impact note và ba evidence checklists. Giữ **Retrospective evidence map, improvement experiment, Working Agreement v2** cho `CAP-01`; U10 có thể tham chiếu experiment như context nhưng Assignment 05 vẫn tiêu thụ chính thức Sprint Review record/Product Backlog v3 từ ASM-U08.

## Provenance

Retrospective: SRC-SG20/SRC-EVENTS; evidence/experiment: SRC-EBM24; flow signals: SRC-KANBAN-SCRUM. Fixture/change card: **[BỔ SUNG — nguồn: SRC-PROJECT, synthetic course data]**.

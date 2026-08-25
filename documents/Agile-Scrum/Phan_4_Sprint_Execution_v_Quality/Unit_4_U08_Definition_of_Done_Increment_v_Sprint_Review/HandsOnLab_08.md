# Hands-on Lab LAB-U08-01 — Quality gate và Sprint Review với phản hồi mới

| Thuộc tính | Giá trị |
| --- | --- |
| Unit | U08 — Definition of Done, Increment và Sprint Review |
| Thời lượng | 90 phút |
| Hình thức | guided_with_fading |
| Mức xác thực | simulated |

## 🎯 Learning Outcomes được thực hành

- **LO8.1:** `CP-U08-01`, evidence `Increment_Evidence_L8.md` và quality-gate checklist.
- **LO8.2:** `CP-U08-01`, `CP-U08-02`, evidence `Sprint_Review_L8.md`, backlog diff và impact note.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

- **MEX-U08-01 → CP-U08-01, CP-U08-02.** Fixture Lab khác PBI/feedback trong Material và Assignment.

## Project slice, môi trường và phạm vi

Nhóm inspect lát cắt “chọn phương thức giao hàng” của checkout. Chỉ dùng Markdown/CSV và evidence giả lập. DoD `DOD-NS-1.0` không được hạ hồi tố. Accessibility scope ban đầu chỉ là selected keyboard interactions cho shipping selector; security scope chỉ là selected customer/admin authorization check. Không được tuyên bố WCAG 2.2 AA/ASVS 5.0.0 conformance toàn diện.

Starter assets là bản sao read-only của project brief, synthetic dataset và templates. Nếu thiếu, fixture nhúng bên dưới là nguồn đầy đủ; không tìm/copy dữ liệu người dùng thật.

### Fixture baseline

Sprint Goal `SG-L8`: “người mua thấy lựa chọn/phí giao hàng trước payment và không mất dữ liệu checkout khi đổi lựa chọn”.

| PBI | Acceptance evidence | DoD evidence |
| --- | --- | --- |
| L8-51 shipping selector | 3/3 AC PASS | integration/review/docs PASS; keyboard test `E-KB-51` FAIL: focus mắc ở custom dropdown |
| L8-52 persist checkout input | 3/3 AC PASS | integration/review/docs PASS; selected keyboard + authz checks PASS |
| L8-53 carrier audit event | 2/2 AC PASS | integration PASS; audit evidence `E-AUD-53` MISSING |

Feedback `FB-L8-01`: Customer Service muốn hiện “dự kiến giao” cạnh từng lựa chọn; có 4/10 synthetic tickets hỏi thời gian giao. Feedback `FB-L8-02`: Sponsor muốn gọi L8-51 Done vì demo bằng chuột thành công.

## 📋 Lab outline và Definition of Done

PASS khi mọi PBI được phân loại bằng AC+DoD evidence; Increment list không chứa FAIL/MISSING bắt buộc; scope statement có limitation; mọi feedback có disposition/rationale/owner/link hoặc trigger; backlog diff resolve; CP-02 xử lý evidence thay đổi mà không sửa DoD.

## Checkpoint 0 — Baseline và safety check

1. **Why:** bảo đảm decision dùng đúng DoD/evidence version.
2. **Action:** tạo `lab-u08/`, chép fixture vào `Baseline_L8.md`; ghi `DOD=DOD-NS-1.0`, timestamp và scope selected checks.
3. **Explanation:** version/scope ngăn reviewer suy rộng claim hoặc đổi gate sau khi biết kết quả.
4. **Verify:** kiểm đủ 3 PBI, 2 feedback, Sprint Goal và từng evidence status.
5. **Expected result:** không ID trùng; tất cả link logic resolve trong fixture; PII/secret = 0.
6. **Evidence:** `E0_L8_Baseline.md` có checklist và kết luận PASS.
7. **Troubleshooting:** nếu thiếu starter asset, dùng fixture nhúng; nếu evidence status không rõ, giữ `MISSING/UNKNOWN`, không tự suy thành PASS.
8. **Reset/rollback:** tạo lại thư mục làm việc từ fixture; starter asset vẫn read-only.

## CP-U08-01 — Tạo evidence pack và review record

**material_example_refs:** `MEX-U08-01` · **LO:** LO8.1, LO8.2.

1. **Why:** tạo một quality decision tái kiểm được trước khi inspect outcome.
2. **Action:** lập `Increment_Evidence_L8.md` với các cột PBI, AC result/link, từng DoD check áp dụng, scope/limitation, decision và backlog action. Không nhìn lại decision của MEX; tự áp invariant đã học.
3. **Explanation:** một FAIL/MISSING bắt buộc không thể được bù bằng nhiều PASS; decision phải là hệ quả của matrix.
4. **Action:** tạo `Sprint_Review_L8.md`: Sprint Goal progress, Increment items, Not Done gaps, environment change, feedback disposition. Tạo `Backlog_v3_Lab.diff.md` cho mọi add/update/order.
5. **Explanation:** Review là working session. Feedback được xử lý nhưng không override quality gate; Not Done gap phải quay lại backlog.
6. **Verify:** peer reviewer chọn ngẫu nhiên một decision và lần theo PBI→AC/DoD evidence→Increment/backlog; chọn từng feedback và lần theo disposition→rationale→owner→PBI/trigger.
7. **Expected result:** 3/3 PBI có decision; Increment không chứa item có FAIL/MISSING; 2/2 feedback có disposition; scope statement không có claim toàn diện.
8. **Evidence:** `E1_CP-U08-01.md`, evidence pack, Review record, backlog diff; checklist PASS/REVISE.
9. **Troubleshooting:** nếu team tranh luận “gần Done”, tìm dòng gate chưa PASS; nếu feedback chỉ ghi “noted”, thêm disposition và next action; nếu claim quá rộng, liệt kê page/flow/role/browser/check đã test và limitation.
10. **Reset/rollback:** giữ baseline; đổi artifact lỗi thành `.revise`, tạo lại matrix từ criterion IDs—không xóa FAIL/MISSING khỏi input.

## CP-U08-02 — Failure/change path: test cũ bị invalid và feedback xung đột

**material_example_refs:** `MEX-U08-01` · **LO:** LO8.1, LO8.2 · **Biến thể mới:** evidence và constraint xuất hiện sau CP-01.

Change card `EV-L8-02`:

- Test `E-KB-51` đã chạy nhầm build cũ; kết quả đó chuyển thành **INVALID**, không phải PASS.
- Retest đúng build `E-KB-51R` PASS cho keyboard selector trong scope Firefox/Windows fixture.
- Sponsor đề nghị thêm “free shipping cho mọi đơn” ngay vào backlog đầu tiên; finance chưa cung cấp margin guardrail.

1. **Why:** kiểm tra khả năng sửa decision khi provenance evidence thay đổi và tránh biến feedback chưa đủ dữ liệu thành commitment.
2. **Action:** lập `Change_Impact_L8.md` ghi evidence superseded, PBI/decision bị ảnh hưởng, artifact downstream cần update và limitation còn lại.
3. **Explanation:** INVALID evidence bị loại khỏi basis; retest PASS chỉ bao phủ scope ghi rõ, không mở rộng conformance.
4. **Action:** cập nhật evidence pack, Sprint Review record và backlog diff. Disposition yêu cầu free-shipping bằng evidence/Goal/risk; nếu defer, phải có owner, thông tin cần thu thập và trigger review; nếu accept, phải có measurable guardrail—không bịa margin.
5. **Explanation:** disposition không có trigger là trì hoãn vô hạn; accept thiếu constraint làm backlog item không kiểm chứng được.
6. **Verify:** mọi link tới `E-KB-51` ghi superseded/INVALID; basis mới trỏ `E-KB-51R`; decision và Increment membership nhất quán; feedback mới có closed-loop trace; DoD version không đổi.
7. **Expected result:** change request được xử lý đồng bộ ở evidence pack→Review→backlog; selected-check claim vẫn hẹp; không có margin giả lập bị trình bày như dữ liệu thật.
8. **Evidence:** `E2_CP-U08-02.md`, impact note, diff của ba artifact và evidence lineage.
9. **Troubleshooting:** nếu decision đổi nhưng Increment list không đổi, dùng impact table để tìm downstream; nếu team gọi INVALID là FAIL, tách “test không đáng tin” khỏi “product behavior fail”; nếu thiếu finance data, ghi UNKNOWN + trigger.
10. **Reset/rollback:** khôi phục bản CP-01, áp change card từ evidence lineage trước rồi mới cập nhật decision; không sửa file evidence gốc.

## ♻️ Reset, cleanup và khả năng chạy lại

Áp dụng mục **Reset/rollback** của từng checkpoint; chỉ khôi phục bản làm việc, giữ starter assets read-only và giữ nguyên evidence/change card gốc.

## 🧪 Final validation

- `L8-O1`: MEX mapping resolve và mỗi checkpoint có artifact/evidence riêng.
- `L8-O2`: tất cả PBI có AC+DoD version+evidence+decision.
- `L8-O3`: Increment membership không chứa FAIL/MISSING/INVALID basis bắt buộc.
- `L8-O4`: Review có Goal/outcome/environment/feedback/backlog diff.
- `L8-O5`: 100% feedback có disposition/rationale/owner/link hoặc trigger.
- `L8-O6`: evidence supersession cập nhật mọi downstream artifact; DoD không đổi.
- `L8-O7`: scope claim chỉ nói selected checks; không PII/secret.

Exit condition: 7/7 PASS từ peer review. REVISE phải có finding, owner và re-review; không tự khai chứng nhận WCAG/ASVS.

## Deliverables và tái sử dụng

Nộp baseline, evidence pack, Sprint Review record, backlog diff, impact note, evidence lineage và ba checklist. Artifact Lab hỗ trợ luyện kỹ năng; không được dùng như lời giải ASM-U08. Assignment 04 sẽ tiêu thụ Sprint Goal/Sprint Backlog từ ASM-U06 và tạo **Increment evidence pack, Sprint Review record, Product Backlog v3** cho ASM-U10/Capstone.

## Provenance

Scrum/DoD: SRC-SG20, SRC-DOD; scope guardrails: SRC-WCAG22, SRC-ASVS500. Fixture/change cards: **[BỔ SUNG — nguồn: SRC-PROJECT, synthetic course data]**.

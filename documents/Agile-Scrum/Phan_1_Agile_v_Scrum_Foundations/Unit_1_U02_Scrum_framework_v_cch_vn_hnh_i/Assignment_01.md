# Unit U02: Scrum framework và cách vận hành đội — Assignment 01

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASM-U02 |
| Hình thức | Team assessment, làm độc lập |
| Thời lượng | 90 phút |
| Độ khó | medium |
| Bloom | apply, create |
| Mức xác thực | simulated |
| Phương thức chấm | artifact_review |

## 🎯 Learning Outcomes được đánh giá

- **LO2.1:** lập bản đồ đúng Scrum accountabilities, values, events, artifacts và commitments với độ chính xác ít nhất 80%.
- **LO2.2:** tạo Team Charter và Working Agreement có quyền quyết định, quy tắc cộng tác và evidence kiểm tra được.

## 🧠 Khái niệm và best practices được đánh giá

| Contract | Concept/LO | Scenario và input | Best-practice constraint đã học | Deliverable | Oracle/evidence | Rubric |
| --- | --- | --- | --- | --- | --- | --- |
| TASK-U02-01A | OUT-U02-01 / LO2.1 | ASM-CR-U02-A, project brief, blank artifact templates | Mọi quyết định phải liên kết input, mục tiêu, accountability và evidence; không dùng chức danh thay accountability hoặc tạo hierarchy trong Scrum Team | Team Charter, kèm Scrum operating-model appendix | AT-U02-01; mapping review và trace table | RB-U02-01 |
| TASK-U02-01B | OUT-U02-02 / LO2.2 | ASM-CR-U02-A cùng cadence constraint | Mọi thay đổi phải nêu trade-off và cập nhật event/artifact/commitment/working rule downstream bị ảnh hưởng | Working Agreement, kèm change-impact note | AT-U02-02; impact diff và rule-review evidence | RB-U02-02 |

Các dòng trên là contract đánh giá, không phải hướng dẫn giải. Học viên phải tự chọn mô hình và bảo vệ quyết định.

## Bối cảnh và change request độc lập

NovaShop là tình huống đào tạo **simulated**; không có doanh nghiệp, nhân viên hay dữ liệu khách hàng thật. Sponsor cần visibility trước khi đầu tư tiếp nhưng lo đội tự quản làm mất kiểm soát.

### ASM-CR-U02-A — Sponsor governance request

Sponsor gửi một memo mới:

1. “Product Owner phải phê duyệt mọi technical decision trong 24 giờ.”
2. “Daily Scrum phải có Delivery Manager, mỗi người báo tiến độ cá nhân và manager chấp thuận task tiếp theo.”
3. “Board cần một bản risk/evidence snapshot mỗi tuần, gồm goal progress, impediment owner và quality limitation.”
4. “Một người đã được chỉ định làm Product Owner; Security/Accessibility reviewer là stakeholder tư vấn.”

Nhóm đóng vai Scrum Team và phải thiết kế operating model đúng Scrum, đồng thời đáp ứng nhu cầu transparency hợp lệ. Không được tái sử dụng, đổi tên hoặc nộp artifact đã hoàn thành trong Example/Lab; starting state của Assignment chỉ gồm input dưới đây và template trống.

**Giá trị nghiệp vụ:** giảm khoảng trống accountability và meeting hình thức mà không làm mất visibility của sponsor.

## 🔗 Liên kết project xuyên suốt

- **Milestone:** M-U02.
- **Assignment dependency:** không có Assignment trước; đây là đầu chuỗi assessment.
- **Baseline artifacts:** Project brief NovaShop; Artifact templates.
- **Artifacts tạo ra:** Team Charter; Working Agreement.
- **Consumer downstream:** ASM-U04 sử dụng hai artifact này làm governance baseline.
- **Terminal delivery:** NOT_APPLICABLE — đây không phải Assignment cuối.

## Điều kiện thực hiện và input

### Starter state

- starter/NovaShop_Project_Brief.md, version 1.0;
- starter/Artifact_Templates.md, bản trống;
- ASM-CR-U02-A ở trên;
- Scrum Guide 2020 và các nguồn đã map;
- một Markdown editor CommonMark-compatible.

Không cung cấp operating model, Team Charter hoặc Working Agreement mẫu. Nếu nhóm đã làm Lab, chỉ được dùng kiến thức/oracle đã học, không copy artifact Lab.

### Data/safety

Chỉ dùng actor label hoặc tên giả; không email, địa chỉ, customer record, token hay endpoint thật. Mọi claim về NovaShop phải mang phạm vi simulated.

## 📋 Yêu cầu

### Functional requirements

- **FR-ASM-U02-01 [LO2.1]:** Scrum operating-model appendix phải map ba accountabilities, năm values và mô hình Scrum Team tới decision rights/observable behavior của scenario.
- **FR-ASM-U02-02 [LO2.1]:** Appendix phải map năm Scrum events cùng ba artifacts/commitments; với mỗi event nêu purpose, inspection basis, possible adaptation, participants và timebox phù hợp.
- **FR-ASM-U02-03 [LO2.2]:** Team Charter phải xác định Product Goal focus, accountability boundaries, stakeholder consultation/visibility và cơ chế xử lý bất đồng.
- **FR-ASM-U02-04 [LO2.2]:** Working Agreement phải có ít nhất bốn rule; mỗi rule gồm trigger, behavior, owner, evidence và inspection/review condition.
- **FR-ASM-U02-05 [LO2.1, LO2.2]:** Change-impact note phải disposition cả bốn statement của ASM-CR-U02-A bằng accept, adapt hoặc reject-with-rationale, rồi chỉ ra artifact section bị ảnh hưởng.

### Non-functional requirements

- **NFR-ASM-U02-01 [LO2.1]:** Không bỏ/đổi bản chất accountabilities, events, artifacts hoặc commitments cốt lõi; không tạo hierarchy/sub-team trong Scrum Team.
- **NFR-ASM-U02-02 [LO2.2]:** Mọi rule/decision phải quan sát và kiểm tra được; câu chỉ có “giao tiếp tốt”, “linh hoạt” hoặc “theo best practice” không được tính.
- **NFR-ASM-U02-03 [LO2.1, LO2.2]:** Traceability phải đi từ memo statement → decision/rationale/trade-off → artifact section → acceptance evidence.
- **NFR-ASM-U02-04 [LO2.2]:** File mở được, ID duy nhất, không PII/secret và không tuyên bố NovaShop là dự án thật.

### Ràng buộc và ngoài phạm vi

- Không được bỏ Scrum event hoặc thay accountability bằng chức danh tổ chức.
- Không được hạ Definition of Done để đáp ứng memo.
- Không thiết kế code, deployment, HR org chart, compensation hoặc production security policy.
- Có thể bổ sung practice như risk snapshot/decision record nếu gắn nhãn complementary và không làm sai Scrum.

## Nhiệm vụ đánh giá

**TASK-U02-01 — Ra quyết định độc lập cho ASM-CR-U02-A**

Từ starter state, nộp Team Charter và Working Agreement cùng hai appendix bắt buộc. Artifact phải cho thấy nhóm đã phân tích request, chọn decision rights/cadence/evidence model, nêu trade-off và giữ consistency với project boundary. Đề bài không quy định trình tự thực hiện, cấu trúc tổ chức cụ thể hay câu chữ của solution.

## 📦 Deliverables và cách nộp

1. **Team Charter**
   - định dạng Markdown hoặc PDF có thể đọc độc lập;
   - tên logic: ASM-U02_Team_Charter;
   - kèm Scrum operating-model appendix;
   - có version, milestone M-U02 và simulated disclosure.
2. **Working Agreement**
   - định dạng Markdown hoặc PDF;
   - tên logic: ASM-U02_Working_Agreement;
   - kèm change-impact note và bảng traceability;
   - có rule evidence và review condition.
3. **Evidence checklist**
   - ghi AT-U02-01/02, evidence location và PASS/REVISE;
   - có peer reviewer và finding disposition bằng team/member ID giả.

Submission được xem là đủ khi cả ba artifact mở được, cross-reference resolve và mỗi acceptance test có evidence path. Không nộp Example/Lab artifact hay reference solution.

## ✅ Acceptance criteria và output mong đợi

### AT-U02-01 — OUT-U02-01 / LO2.1

**Given** project brief, blank templates và ASM-CR-U02-A, **when** reviewer kiểm Team Charter/operating-model appendix, **then**:

- ít nhất 80% mapping cards accountabilities/values/team đúng;
- reviewer xác định được input, decision, rationale, trade-off và evidence mà không hỏi tác giả;
- không có critical error: PO committee, internal hierarchy, PO/manager sở hữu how, Scrum Master giao task, hoặc accountability mới thay core Scrum.

**Evidence:** mapping review sheet, trace table và exact artifact section. Một critical error làm AT-U02-01 FAIL bất kể tổng tỷ lệ.

### AT-U02-02 — OUT-U02-02 / LO2.2

**Given** cadence request và weekly visibility need, **when** reviewer kiểm Working Agreement/change-impact note, **then**:

- năm events cùng ba artifact/commitment mappings đạt ít nhất 80%;
- mọi memo statement có disposition, rationale, trade-off và downstream section update;
- rule quan sát được, không biến Daily thành manager status gate hoặc Sprint Review thành approval gate;
- sponsor có một evidence path cụ thể và quality/DoD không bị hạ.

**Evidence:** event/artifact map, before/after impact table và rule checklist. Nếu artifact chỉ bác request mà không đáp ứng transparency need, AT-U02-02 FAIL.

### Failure behavior

- Thiếu một deliverable hoặc không mở được → INCOMPLETE.
- Traceability/evidence thiếu nhưng mô hình có vẻ hợp lý → REVISE, không tự suy đoán.
- Có PII/secret hoặc claim production → SAFETY FAIL và loại dữ liệu trước khi chấm lại.

## 🧪 Cách xác minh

Reviewer dùng artifact-review checklist:

| Check | Evidence bắt buộc |
| --- | --- |
| AT-U02-01 | mapping score, critical-error scan, memo-to-decision trace |
| AT-U02-02 | event/artifact score, four memo dispositions, rule evidence |
| Project link | M-U02 metadata; Team Charter/Agreement marked for ASM-U04 |
| Integrity | file opens, IDs unique, internal references resolve |
| Safety/provenance | simulated disclosure; no PII/secret |

Reviewer ghi PASS/REVISE cho từng test và nêu exact finding. Không chấm dựa vào độ đẹp của template.

## 📊 Rubric chấm điểm — tổng 100%

| ID | Trọng số | LO | Excellent | Meets | Partial | Not met |
| --- | ---: | --- | --- | --- | --- | --- |
| **RB-U02-01 — Đúng khái niệm, truy vết và evidence** | 50% | LO2.1 | Mapping đạt 100%, không critical error; mọi decision truy vết, trade-off/counter-example rõ và reviewer tái lập được AT-U02-01 | Mapping ≥80%, không critical error; decision cốt lõi có input/rationale/evidence và AT-U02-01 PASS | Mapping 60–79% hoặc thiếu một liên kết/evidence quan trọng nhưng không có critical error | Mapping <60%, AT-U02-01 FAIL hoặc có critical Scrum error |
| **RB-U02-02 — Xử lý thay đổi và consistency downstream** | 50% | LO2.2 | Cả bốn memo statement được disposition; rules hoàn toàn observable; events/artifacts nhất quán, edge/trade-off và downstream reuse rõ | AT-U02-02 PASS; change request được xử lý, visibility need đáp ứng, Charter/Agreement nhất quán | Có cập nhật nhưng thiếu một disposition, trade-off, rule field hoặc downstream link | AT-U02-02 FAIL; biến event thành gate/status report, hạ quality hoặc không có evidence |

**Điểm đạt:** 70% và không có critical Scrum/safety error.

## Nguồn và provenance

### Nguồn đã map

- SRC-SG20 — https://scrumguides.org/scrum-guide.html — November 2020, publisher Ken Schwaber/Jeff Sutherland, CC BY-SA 4.0.
- SRC-TEAM — https://www.scrum.org/resources/what-scrum-team — Scrum.org, snapshot 2026-08-25, reference-only.
- SRC-EVENTS — https://www.scrum.org/resources/introduction-scrum-events — Scrum.org, snapshot 2026-08-25, reference-only.
- SRC-PROJECT — starter/NovaShop_Project_Brief.md — version 1.0, internal approved.

### Phần bổ sung/suy diễn

- [SUY DIỄN — từ kiến thức đã huấn luyện] ASM-CR-U02-A, actor labels, file naming và evidence checklist là thiết kế đánh giá synthetic.

> **Độc lập và không lời giải:** Assignment chỉ nêu scenario, constraints, deliverables và pass-fail oracle; không có walkthrough, pseudo-solution, completed map, Team Charter mẫu hay Working Agreement mẫu.

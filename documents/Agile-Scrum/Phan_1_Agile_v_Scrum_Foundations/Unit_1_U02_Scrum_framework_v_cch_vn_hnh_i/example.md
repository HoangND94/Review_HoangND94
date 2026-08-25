# Unit U02: Scrum framework và cách vận hành đội — Ví dụ và nghiên cứu tình huống

> **Case ID:** CASE-U02-01 · **Mức xác thực:** simulated · **Milestone:** M-U02

## 🎯 Learning Outcomes liên quan

- **LO2.1 / OUT-U02-01, OUT-U02-02:** map accountabilities, values, events, artifacts và commitments.
- **LO2.2 / OUT-U02-01, OUT-U02-02:** tạo Team Charter/Working Agreement có decision rights và oracle.

## Điều kiện chạy case

Dùng ENV-PRO-ARTIFACT, Markdown editor và starter assets. U01 decision/hypothesis register đã có. Validation là artifact review; không chạy code hay service.

## Nguồn đầu vào đã map

- SRC-SG20 — https://scrumguides.org/scrum-guide.html — Scrum framework, November 2020, CC BY-SA 4.0.
- SRC-TEAM — https://www.scrum.org/resources/what-scrum-team — Scrum Team, snapshot 2026-08-25, reference-only.
- SRC-EVENTS — https://www.scrum.org/resources/introduction-scrum-events — event purposes, snapshot 2026-08-25, reference-only.
- SRC-PROJECT — starter/NovaShop_Project_Brief.md — simulated scenario, version 1.0, internal approved.

## Case Study 01: Hai proxy cùng order backlog và Sprint Review thành cổng ký

### 1. Ticket và tiêu chí thành công

- **Stakeholders:** Head of Sales, Head of Operations, Product Owner và Scrum Team.
- **Vấn đề:** Sales proxy order các hạng mục catalog, Operations proxy order hạng mục tồn kho; cả hai có quyền veto. Sprint Review chỉ được tổ chức khi Head of Sales “ký Done”.
- **Input khác Assignment:** case tập trung vào xung đột ordering và Review-as-gate; không dùng yêu cầu PO phê duyệt kỹ thuật/Daily status của ASM-U02.
- **Tiêu chí:** một operating model map đúng Scrum, giữ được consultation từ Sales/Operations, và một Working Agreement có trigger quan sát được.

### 2. Input, baseline và constraints

| ID | Baseline card |
| --- | --- |
| GOV-C01 | Sales proxy được ưu tiên mọi catalog item |
| GOV-C02 | Operations proxy được ưu tiên mọi inventory item |
| EVT-C01 | Review bị hủy nếu Head of Sales không tham dự |
| EVT-C02 | Work đã đạt DoD bị giữ ở trạng thái “chờ ký” |
| VIS-C01 | Sponsor cần thấy ordering rationale và risk mỗi tuần |

Constraints: một product, một Product Backlog, một Product Goal; Sprint hai tuần; no hierarchy inside Scrum Team; no PII/secret; release policy tổ chức có thể tồn tại nhưng không được đổi nghĩa Done/Review.

### 3. Phân tích lựa chọn

**Option A — giữ hai proxy có veto:** đại diện lợi ích nhanh nhưng không có một accountability cho value/order; backlog dễ tách thành hai queue.

**Option B — một PO quyết định trong im lặng:** đúng số lượng nhưng làm mất stakeholder collaboration và evidence.

**Option C — một PO accountable, dùng consultation/evidence map:** Sales và Operations cung cấp evidence/constraint; PO quyết định order minh bạch; Scrum Team cùng stakeholder inspect Increment/outcome ở Review. Chọn C vì giữ coherence và vẫn đáp ứng visibility.

Release approval bên ngoài, nếu bắt buộc, phải tách khỏi Definition of Done và không làm Sprint Review thành gate. Trade-off là PO cần capacity để tổng hợp nhiều nguồn và phải công khai rationale.

### 4. Cách triển khai professional artifact

#### Operating model map

| Actor/event | Accountability hoặc purpose | Quyền/interaction | Evidence |
| --- | --- | --- | --- |
| Product Owner | maximize value; effective backlog management | quyết định Product Goal/order; một người accountable | ordered Product Backlog + rationale |
| Developers | usable Increment | tự quyết how/Sprint plan, tuân DoD | Sprint Backlog + Increment evidence |
| Scrum Master | establish Scrum/team effectiveness | coach conflict/empiricism | impediment/improvement record |
| Sales/Operations | stakeholders | cung cấp evidence, constraint và feedback; không có ordering veto | source card → PO disposition |
| Sprint Review | inspect outcome/Product Goal progress | collaboration, future adaptation | Increment + feedback + backlog diff |
| Release governance | organization policy ngoài Scrum | chỉ áp dụng nếu có, không đổi Done | separate release decision record |

#### Team Charter extract

- Focus: một Product Goal và một Product Backlog.
- Decision right: PO giữ final ordering accountability; stakeholder influence được ghi bằng source/evidence và disposition.
- Developers giữ how; Scrum Master không phân việc.
- Work đạt DoD là Increment; release decision tách biệt.
- Values evidence: Openness qua rationale, Respect qua consultation, Courage qua việc ghi rejected request, Focus qua Product Goal.

#### Working Agreement extract

| Trigger | Behavior | Owner | Evidence/review |
| --- | --- | --- | --- |
| Hai stakeholder yêu cầu thứ tự xung đột | PO ghi options, evidence, impact và quyết định; không tạo hai backlog | PO | ordering decision; inspect khi input đổi |
| Key stakeholder vắng Sprint Review | dùng evidence/feedback channel phù hợp; Review vẫn theo purpose với người cần thiết có mặt | Scrum Team/PO | attendance rationale + feedback log |
| Item đạt DoD nhưng chưa release approval | ghi Done Increment và release status riêng | Developers/PO | DoD evidence + release record |
| Rule gây chậm hai lần | đưa evidence vào Retrospective | Scrum Team | improvement action |

### 5. Output mong đợi

- Một Product Backlog có PO accountable và traceable stakeholder input.
- Sprint Review không phụ thuộc chữ ký của một Head; purpose vẫn là inspect outcome và adapt.
- Done status dựa Definition of Done, không dựa release approval.
- Sales/Operations vẫn có đường influence minh bạch.

Edge result: nếu Head of Sales vắng nhưng Operations, người mua đại diện và sponsor có đủ evidence/feedback, Review không tự động bị hủy. Team ghi limitation về feedback Sales và lên follow-up; không giả vờ đã nhận ý kiến đó.

### 6. Cách xác minh

| Oracle | PASS condition |
| --- | --- |
| Accountabilities | một PO, một SM, Developers; không proxy-veto/hierarchy |
| Values | ít nhất ba value được nối tới hành vi/evidence, không chỉ liệt kê |
| Events | Sprint Review đúng purpose, participant/limitation rõ |
| Artifacts/commitments | Product Backlog↔Product Goal, Sprint Backlog↔Sprint Goal, Increment↔DoD |
| Rules | mỗi rule có trigger, behavior, owner, evidence/review |
| Safety | simulated/no PII/secret |

Tổng mapping cards đúng phải đạt ít nhất 80%; mọi critical error làm REVISE dù tổng điểm cao.

### 7. Giải thích sâu và failure modes

Một PO không có nghĩa “PO tự làm tất cả”. Accountability duy nhất giải quyết quyết định cuối; delegation và consultation giúp tránh bottleneck. Nếu artifact vẫn có cụm “Sales PO” và “Operations PO” với quyền order, dấu hiệu là committee chưa được loại.

Tách Done khỏi release không loại governance; nó làm hai trạng thái minh bạch. Nếu đội gọi work “Not Done” chỉ vì chưa ký release, flow/evidence bị méo. Ngược lại, nếu work chưa DoD nhưng được ký release, đó là critical failure.

Giới hạn: case không thiết kế chính sách release pháp lý hay organizational structure; nó chỉ giữ các ranh giới Scrum và evidence path.

### 8. Bài học chuyển giao

Khi stakeholder cần kiểm soát, hãy hỏi họ cần **decision authority** hay **visibility/evidence**. LAB-U02-01 cho một flawed map khác để học viên sửa; ASM-U02 đưa governance request mới và chỉ cung cấp contract/rubric, không cung cấp artifact mẫu của case này.

## Provenance của các case

- Framework facts được paraphrase từ SRC-SG20, SRC-TEAM và SRC-EVENTS.
- NovaShop boundary/data policy đến từ SRC-PROJECT.
- [SUY DIỄN — từ kiến thức đã huấn luyện] Proxy cards, attendance edge case và release record là tình huống sư phạm synthetic.

> **Simulated disclosure:** tên actor, policy và mọi evidence trong case là giả lập.

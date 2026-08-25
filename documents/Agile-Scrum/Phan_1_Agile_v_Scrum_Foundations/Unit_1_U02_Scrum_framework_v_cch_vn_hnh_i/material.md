# Unit U02: Scrum framework và cách vận hành đội — Học liệu cốt lõi

> **Khóa học:** Agile–Scrum thực hành qua dự án thương mại điện tử NovaShop · **Thuộc:** Agile và Scrum Foundations

## 🎯 Learning Outcomes

- **LO2.1** [apply] — Lập bản đồ đúng Scrum accountabilities, values, events, artifacts và commitments với độ chính xác ít nhất 80%.
- **LO2.2** [create] — Tạo Team Charter và Working Agreement có quyền quyết định, quy tắc cộng tác và bằng chứng kiểm tra được.

## Ngữ cảnh dự án và phần tăng trưởng của Unit

NovaShop là dự án **simulated**, dùng dữ liệu synthetic và sandbox; không đại diện cho doanh nghiệp hoặc người dùng có thật. U02 kế thừa decision canvas/value hypotheses từ U01 và tạo milestone **M-U02**:

- Scrum operating model map;
- Team Charter nêu mục tiêu chung, accountabilities và quyền quyết định;
- Working Agreement có trigger quan sát được, owner và thời điểm inspection.

Các artifact này giảm khoảng trống accountability và ngăn event biến thành nghi thức. MEX-U02-01 minh họa đầy đủ; LAB-U02-01 sửa một operating model sai; ASM-U02 đánh giá transfer bằng một governance request độc lập. Team Charter và Working Agreement đạt chuẩn sẽ được ASM-U04 và CAP-01 tái sử dụng.

## Nguồn đầu vào đã map

- SRC-SG20 — The Scrum Guide: https://scrumguides.org/scrum-guide.html (publisher: Ken Schwaber, Jeff Sutherland / ScrumGuides.org; version: November 2020; accessed_at: 2026-08-25; license: CC BY-SA 4.0; allowed_use: adapt)
- SRC-TEAM — What is a Scrum Team?: https://www.scrum.org/resources/what-scrum-team (publisher: Scrum.org; version: living page snapshot 2026-08-25; accessed_at: 2026-08-25; license: reference-only; allowed_use: reference)
- SRC-EVENTS — Introduction to the Scrum Events: https://www.scrum.org/resources/introduction-scrum-events (publisher: Scrum.org; version: living page snapshot 2026-08-25; accessed_at: 2026-08-25; license: reference-only; allowed_use: reference)
- SRC-PROJECT — NovaShop simulated e-commerce project brief: starter/NovaShop_Project_Brief.md (publisher: Training artifact created for this course; version: 1.0; accessed_at: 2026-08-25; license: internal approved; allowed_use: internal_approved)

## 1. Kiến thức tiên quyết và môi trường

Hoàn thành U01; biết phân biệt observation, assumption và decision. Dùng ENV-PRO-ARTIFACT: Markdown editor CommonMark-compatible, spreadsheet CSV UTF-8 và whiteboard vendor-neutral; không cần code, cloud hoặc dịch vụ trả phí.

Smoke check:

1. Mở được project brief, synthetic dataset và artifact templates.
2. Mở được U01 decision/hypothesis artifact đã review hoặc dùng baseline được giảng viên phát.
3. Tạo file working cho operating model mà không sửa starter.
4. Xác nhận không có PII, secret hay production endpoint.

Phương thức xác minh là **artifact_review**. Practice mode là **professional_artifact**, phù hợp với LO về mô hình vận hành và quy tắc cộng tác.

## 2. Định vị trong lộ trình

U01 trả lời “ta học và thích nghi thế nào”; U02 trả lời “ai accountable, inspect điều gì, ở event nào và adapt artifact nào”. U03 dùng mô hình đội này để tạo Product Goal; U06–U09 dùng lại event, commitment và quyền quyết định trong Sprint.

Mental model: **accountability tạo quyền và nghĩa vụ → values định hướng hành vi → events tạo nhịp inspect/adapt → artifacts tạo transparency → commitments tạo điểm tập trung**. Bỏ một mắt xích làm feedback loop yếu đi.

## 3. Nội dung lý thuyết cốt lõi

**Checklist bắt buộc phủ — giữ nguyên văn và đúng thứ tự Content Outlines:**

- [x] Scrum accountabilities, values và mô hình Scrum Team
- [x] Scrum events, artifacts và commitments trong một Sprint

#### OUT-U02-01 Scrum accountabilities, values và mô hình Scrum Team

**Mapping:** OUT-U02-01 · LO2.1, LO2.2 · M-U02 Team Charter/Working Agreement/operating model

##### Định nghĩa và ranh giới

Scrum Team là đơn vị nền tảng gồm **một Product Owner, một Scrum Master và Developers**. Team không có sub-team hay hierarchy nội bộ, tập trung vào một Product Goal, có đủ kỹ năng để tạo value và tự quản cách thực hiện công việc. “Developers” là accountability cho những người tạo bất kỳ phần nào của usable Increment; không đồng nghĩa riêng với chức danh lập trình viên.

Ba accountability:

- **Product Owner:** accountable tối đa hóa value và quản lý Product Backlog hiệu quả, gồm phát triển/truyền đạt Product Goal, làm rõ/order items và bảo đảm backlog minh bạch. Product Owner là một người, không phải committee; có thể ủy quyền công việc nhưng không chuyển accountability.
- **Developers:** accountable tạo Sprint Backlog, tuân thủ Definition of Done, thích nghi plan hằng ngày hướng Sprint Goal và giữ nhau accountable như professional.
- **Scrum Master:** accountable thiết lập Scrum và effectiveness của Scrum Team; giúp mọi người hiểu framework, coaching self-management/cross-functionality và hỗ trợ gỡ impediment.

Năm Scrum values là Commitment, Focus, Openness, Respect và Courage. Values không phải khẩu hiệu trang trí; chúng là tiêu chuẩn để xem một rule/decision có tăng hay làm suy yếu empiricism và trust.

Team Charter và Working Agreement là practice bổ trợ, không phải Scrum artifacts bắt buộc. Chúng đạt giá trị khi làm rõ cách team thực thi accountabilities/values mà không tạo hierarchy mới.

##### Vấn đề, vai trò và quyết định cần đưa ra

NovaShop có sponsor, specialist và reviewer, nhưng chỉ Scrum Team sở hữu các accountability Scrum. Đội phải quyết định:

- ai là một Product Owner cuối cùng cho ordering/value;
- Developers tự quyết định who/what/when/how trong phạm vi Sprint thế nào;
- Scrum Master can thiệp bằng coaching/facilitation chứ không phân việc;
- stakeholder nhận transparency ở đâu mà không trở thành người phê duyệt mọi kỹ thuật;
- hành vi nào chứng minh values, và trigger nào cho thấy rule cần inspect.

Output phải phân biệt **accountable** với **responsible/contributor/consulted**. Một specialist có thể làm việc trong Developers hoặc tư vấn; chức danh tổ chức không tự tạo accountability Scrum mới.

##### Cơ chế và mental model

Product Owner tạo một hướng value minh bạch; Developers biến lựa chọn thành Increment và tự quản plan; Scrum Master cải thiện môi trường để empiricism hoạt động. Values làm cho thông tin khó chịu được đưa ra đủ sớm: openness/courage lộ risk, respect hỗ trợ self-management, focus/commitment giữ mục tiêu chung.

Khi một approval layer đứng giữa Developers và technical decision, feedback chậm và accountability mờ: Product Owner dễ thành project manager, Developers mất self-management. Khi stakeholder không thấy evidence, họ lại tạo status gate. Cách đúng là cung cấp visibility bằng Product Backlog, Sprint Backlog, Increment, decision/risk record và đúng Scrum event, không chuyển quyền “how” cho sponsor.

##### Khi dùng, khi không dùng và trade-off

Dùng Scrum Team model cho complex product work cần một mục tiêu, đa kỹ năng và feedback thường xuyên. Không dùng từ “Scrum Team” để che một nhóm chức năng vẫn nhận task từ nhiều manager; hoặc để loại stakeholder khỏi collaboration. Với vận hành sự cố có command structure tạm thời, có thể dùng protocol phù hợp rồi quay lại inspect; không đổi nó thành accountability Scrum.

Self-management tăng tốc quyết định và ownership nhưng đòi hỏi transparency, kỹ năng và ranh giới tổ chức rõ. Một Product Owner duy nhất tạo coherence nhưng có bottleneck risk; giảm risk bằng delegation, stakeholder collaboration và backlog transparency, không tạo PO committee.

##### Ví dụ NovaShop riêng và oracle

- **Context:** Team gồm PO An (tên giả), Scrum Master Bình (tên giả) và sáu Developers đa kỹ năng.
- **Input/baseline:** sponsor cần weekly risk visibility; đội đang có hai người cùng order backlog và delivery manager giao task hằng ngày.
- **Decision/action:** chỉ định một PO accountable ordering/value; Developers tự chọn cách thực hiện; Scrum Master hỗ trợ framework/effectiveness; sponsor xem risk/goal evidence ở review cadence, không phê duyệt technical task.
- **Artifact:** phần Accountability/decision rights trong Team Charter.
- **Expected:** không có PO committee hay manager nội bộ; mỗi quyền quyết định có một accountability và consultation path.
- **Oracle:** PASS nếu 8/10 mapping cards đúng, PO là một người, “how” thuộc Developers, Scrum Master không là task assigner, và stakeholder visibility có evidence path. FAIL nếu chức danh được dùng thay accountability.

##### Liên kết MEX và Lab

Leaf này được hiện thực hóa trong **MEX-U02-01 — Scrum operating model map cho NovaShop** ở mục 4. CP-U02-01 sửa accountabilities/decision rights bằng input sai khác; CP-U02-02 xử lý một governance edge case. Cả hai checkpoint tham chiếu MEX-U02-01.

##### Best practices

**Rule:** Mỗi quyền quyết định phải map tới accountability Scrum và một evidence path. **Rationale:** quyền không rõ tạo committee hoặc escalation ngầm. **Positive:** PO orders Product Backlog; Developers quyết định how; sponsor xem goal/risk evidence. **Negative/hậu quả:** “PO duyệt mọi technical decision” làm mất self-management và tạo bottleneck.

**Rule:** Viết working rule dưới dạng trigger → behavior → owner → inspection date. **Rationale:** câu “giao tiếp tốt” không quan sát được. **Positive:** “Khi PBI bị blocked quá một ngày, owner ghi impediment và Developers phối hợp trong ngày; inspect ở Retrospective.” **Negative/hậu quả:** “mọi người hỗ trợ nhau” không tạo hành động hay evidence.

##### Failure diagnosis và cách sửa

- **Dấu hiệu:** nhiều người được gọi là PO. **Nguyên nhân:** nhầm đại diện stakeholder với accountability. **Chẩn đoán:** backlog có nhiều ordering authority. **Sửa:** một PO accountable, ghi delegation/consultation rõ. **Phòng tránh:** review decision-rights table.
- **Dấu hiệu:** Scrum Master giao task và chấm hiệu suất. **Nguyên nhân:** kéo mô hình line manager vào Scrum. **Chẩn đoán:** Developers không tự tạo/adapt Sprint Backlog. **Sửa:** chuyển task decision về Developers; Scrum Master coach/facilitate. **Phòng tránh:** dùng scenario review trong Charter.

#### OUT-U02-02 Scrum events, artifacts và commitments trong một Sprint

**Mapping:** OUT-U02-02 · LO2.1, LO2.2 · M-U02 cadence/artifact visibility/working rules

##### Định nghĩa và ranh giới

Sprint là event chứa bốn event còn lại. Mỗi event là cơ hội chính thức để inspect và adapt artifact/progress; timebox là thời lượng tối đa, không phải mục tiêu phải dùng hết.

| Event | Purpose/inspection | Adaptation/output | Participants cốt lõi | Timebox tối đa với Sprint một tháng |
| --- | --- | --- | --- | --- |
| Sprint | biến ý tưởng thành value, chứa toàn bộ work/events | Increment và learning; Sprint mới nối tiếp | Scrum Team | một tháng hoặc ngắn hơn |
| Sprint Planning | xác định why, what, how | Sprint Goal và Sprint Backlog | toàn Scrum Team; có thể mời advisor | 8 giờ |
| Daily Scrum | inspect progress toward Sprint Goal | actionable plan/Sprint Backlog update | Developers | 15 phút |
| Sprint Review | inspect outcome và progress toward Product Goal | future adaptations/Product Backlog update | Scrum Team và key stakeholders | 4 giờ |
| Sprint Retrospective | inspect quality/effectiveness/cách làm | improvements; có thể cập nhật DoD/plan | Scrum Team | 3 giờ |

Ba artifacts và commitments:

- Product Backlog — commitment **Product Goal**;
- Sprint Backlog — commitment **Sprint Goal**;
- Increment — commitment **Definition of Done**.

Commitment tạo focus và basis để đo progress. Sprint Review không phải approval gate và Daily Scrum không phải status report. Refinement là ongoing activity, không phải Scrum event bắt buộc. User story, story point hay burndown cũng là practice bổ trợ.

##### Vấn đề, vai trò và quyết định cần đưa ra

Đội cần thiết kế cadence để đúng purpose, artifact inspected, adaptation owner và evidence. Quyết định gồm:

- event nào xử lý loại feedback nào;
- artifact/commitment nào là basis;
- ai cần tham gia để purpose đạt;
- rule nào đưa thảo luận chi tiết ra khỏi timebox;
- transparency nào thỏa sponsor mà không biến event thành gate.

##### Cơ chế và mental model

Events tạo nhịp đều cho transparency → inspection → adaptation:

- Planning nối Product Goal với Sprint Goal/Sprint Backlog.
- Daily Scrum so progress với Sprint Goal và adapt plan.
- Review dùng Increment cùng context thị trường để adapt Product Backlog.
- Retrospective dùng evidence về cách làm/quality để tăng effectiveness.

Artifact thiếu commitment giống dashboard không có mục tiêu: có dữ liệu nhưng không biết sai lệch nào đáng phản ứng. Event không tạo adaptation là inspection hình thức; adaptation không dựa transparency là phản ứng cảm tính.

##### Khi dùng, khi không dùng và trade-off

Giữ đủ events và purpose khi tuyên bố dùng Scrum. Đừng thêm meeting chỉ vì quen thuộc; dùng ad-hoc collaboration khi cần chi tiết ngoài event, nhưng không thay thế cơ hội inspect/adapt chính thức. Shorter Sprint tăng feedback và giới hạn risk nhưng tăng cadence overhead; longer Sprint có thể giảm ceremony overhead nhưng tăng horizon/risk, tối đa một tháng.

Không dùng Sprint Review để “ký nghiệm thu” work chưa Done; không dùng Daily để manager thu báo cáo cá nhân; không hoãn adaptation đến Retrospective nếu risk cần xử lý ngay.

##### Ví dụ NovaShop riêng và oracle

- **Context:** Sprint hai tuần cho browse-to-checkout slice.
- **Input:** Sprint Goal draft, ordered backlog, Definition of Done và sponsor cần biết payment risk.
- **Decision:** Planning tạo Sprint Goal/Sprint Backlog; Daily inspect progress-to-goal; Review inspect usable Increment và payment evidence; Retrospective inspect workflow; weekly risk digest lấy từ visible risk/decision log, không thay event.
- **Artifact:** cadence-to-artifact map và Working Agreement.
- **Expected:** mỗi event có purpose, inspection object, adaptation, participants và timebox; ba artifact map đúng commitment.
- **Oracle:** trên 13 cards (5 events, 3 artifacts, 3 commitments, 2 key anti-patterns), ít nhất 11 đúng và không có critical error: Daily status-to-manager, Review approval gate, PO committee hoặc work chưa DoD gọi là Increment.

##### Liên kết MEX và Lab

MEX-U02-01 kết hợp event map với Team Charter/Working Agreement. CP-U02-01 yêu cầu sửa operating model có status Daily; CP-U02-02 thêm yêu cầu governance mới và kiểm downstream cadence.

##### Best practices

**Rule:** Mọi event rule phải bắt đầu bằng purpose và nêu artifact inspected/adapted. **Rationale:** agenda cố định có thể vẫn thất bại nếu không phục vụ empiricism. **Positive:** Daily dùng Sprint Goal và board để tạo plan 24 giờ. **Negative/hậu quả:** ba câu báo cáo cho manager nhưng Sprint Backlog không đổi.

**Rule:** Tách transparency khỏi approval authority. **Rationale:** stakeholder cần evidence nhưng approval gate có thể làm méo accountability và feedback. **Positive:** sponsor xem goal/risk/Increment ở cadence phù hợp và gửi feedback cho PO. **Negative/hậu quả:** Review biến thành cổng ký; work bị giữ dù đã Done hoặc được gọi Done dù chưa đạt DoD.

##### Failure diagnosis và cách sửa

- **Dấu hiệu:** event diễn ra đủ nhưng không có artifact diff/decision. **Nguyên nhân:** ceremony không có purpose/oracle. **Chẩn đoán:** sau event không chỉ ra được inspected evidence và adaptation. **Sửa:** ghi event contract purpose → input → decision → owner. **Phòng tránh:** inspect event effectiveness ở Retrospective.
- **Dấu hiệu:** status report kéo dài hơn 15 phút. **Nguyên nhân:** manager là trung tâm và problem-solving lẫn vào Daily. **Chẩn đoán:** câu hỏi hướng cá nhân, không hướng Sprint Goal. **Sửa:** Developers dùng progress-to-goal và tách deep dive sau Daily. **Phòng tránh:** Working Agreement có timebox/parking-lot trigger.

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### MEX-U02-01 — Scrum operating model map cho NovaShop

**Practice contract:** professional_artifact · **LO:** LO2.1, LO2.2 · **Outline:** OUT-U02-01, OUT-U02-02 · **Milestone:** M-U02

### Input

- U01 decision canvas/value hypotheses;
- một Product Goal focus tạm: giảm re-entry trong hành trình order;
- Sprint hai tuần; sponsor muốn weekly risk visibility;
- constraints synthetic-only, no PII/secret, không hạ DoD.

### Scrum operating model map

| Thành phần | Accountability/purpose | Decision/evidence |
| --- | --- | --- |
| Product Owner | maximize value; Product Goal/backlog management | orders backlog; một người accountable; decision hiện trong backlog |
| Developers | usable Increment và Sprint plan | chọn how, tạo/adapt Sprint Backlog, tuân DoD |
| Scrum Master | Scrum/effectiveness | coach, facilitate, support impediment removal; không phân task |
| Sponsor | stakeholder, không phải accountability Scrum | cung cấp constraint/feedback; xem risk/goal/Increment evidence |
| Sprint Planning | why/what/how | Sprint Goal + Sprint Backlog |
| Daily Scrum | progress toward Sprint Goal | plan 24 giờ/Sprint Backlog adaptation |
| Sprint Review | Sprint outcome/Product Goal progress | stakeholder feedback + Product Backlog adaptation |
| Retrospective | quality/effectiveness | improvement action/DoD consideration |
| Product Backlog | work/value transparency | commitment Product Goal |
| Sprint Backlog | why/what/how transparency | commitment Sprint Goal |
| Increment | usable verified result | commitment Definition of Done |

### Team Charter

- **Focus:** một Product Goal tại một thời điểm.
- **Decision rights:** PO owns ordering/value; Developers own how/Sprint plan; Scrum Master owns Scrum establishment/effectiveness support; sponsor is consulted on value/risk.
- **Values evidence:** openness = risks visible within one working day; focus = work linked Sprint Goal; courage = DoD failure reported; respect = disagreement attacks evidence, not people; commitment = team supports shared goal.
- **Boundary:** no sub-team/hierarchy inside Scrum Team; technical specialists collaborate as Developers when doing Increment work.

### Working Agreement

| Trigger | Behavior | Owner | Evidence/inspection |
| --- | --- | --- | --- |
| PBI blocked more than one working day | mark impediment, swarm or escalate appropriate dependency; do not lower DoD | Developers | board/impediment log; Daily |
| Deep dive would exceed Daily purpose | park named topic and meet immediately after with needed people | Developers | actionable Daily plan + parking item |
| Sponsor requests visibility | publish weekly goal/risk/evidence digest and discuss material changes with PO | PO coordinates; team supplies evidence | digest + backlog/decision link |
| Working rule fails twice | inspect evidence and adapt rule | Scrum Team | Retrospective decision |

### Expected result và verification oracle

PASS khi:

1. ba accountabilities và năm events map đúng;
2. Product Owner là một người, Scrum Team không có internal hierarchy;
3. artifacts map chính xác Product Goal/Sprint Goal/Definition of Done;
4. each working rule có trigger, behavior, owner, evidence và inspection;
5. sponsor có transparency nhưng không sở hữu how/DoD;
6. no-PII/secret và simulated disclosure hiện rõ.

Critical FAIL: PO committee, Daily status-to-manager, Review approval gate, Scrum Master giao task hoặc work chưa DoD gọi là Increment.

### Mapping Material worked example → Hands-on Lab tương ứng

- **MEX-U02-01 → LAB-U02-01/CP-U02-01:** sửa flawed map bằng team/cadence input khác và nộp traceability.
- **MEX-U02-01 → LAB-U02-01/CP-U02-02:** xử lý governance edge card và cập nhật impact note.
- Lab checkpoints phải ghi material_example_refs = MEX-U02-01; Assignment không được dùng artifact này làm đáp án.

## 5. Lỗi thường gặp và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán | Cách sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| PO committee | muốn đại diện mọi phòng ban bằng quyền đồng hạng | nhiều người có ordering veto | một PO accountable, stakeholder consultation rõ | decision-rights review |
| Daily là status report | manager-centered governance | không có progress-to-goal/plan diff | trả event cho Developers, tách risk digest | purpose card |
| Charter là danh sách giá trị | rule không quan sát được | không có trigger/evidence | chuyển thành trigger-behavior-owner-review | rubric rule |
| Sprint Review là approval | nhầm inspection với gate | work status phụ thuộc chữ ký sau DoD | inspect outcome/adapt backlog; release policy tách riêng | event map review |
| Scrum Master là project manager | accountability bị kéo về hierarchy | SM giao task và duyệt plan | Developers tự quản; SM coach framework | scenario rehearsal |

## 6. Từ điển thuật ngữ

- **Accountability:** nghĩa vụ cuối cùng đối với một outcome/decision; không nhất thiết là chức danh HR.
- **Scrum Team:** một PO, một SM và Developers, self-managing/cross-functional, không sub-team/hierarchy.
- **Scrum values:** Commitment, Focus, Openness, Respect, Courage.
- **Event:** cơ hội timeboxed để inspection/adaptation; Sprint là container.
- **Artifact:** biểu diễn work/value tạo transparency.
- **Commitment:** mục tiêu/quality state gắn với artifact: Product Goal, Sprint Goal, DoD.
- **Team Charter:** practice bổ trợ mô tả focus, boundaries và decision rights.
- **Working Agreement:** practice bổ trợ mô tả hành vi cộng tác có trigger/evidence.
- **Timebox:** thời lượng tối đa, không phải thời lượng phải dùng hết.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

- SRC-SG20, SRC-TEAM, SRC-EVENTS và SRC-PROJECT như khai trong course plan; nội dung được paraphrase và không sao chép dài.

### Phần bổ sung/suy diễn

- [SUY DIỄN — từ kiến thức đã huấn luyện] Cấu trúc Team Charter, working-rule oracle, tên người giả và weekly digest là thiết kế sư phạm; không phải thành phần bắt buộc của Scrum.
- [SUY DIỄN — từ kiến thức đã huấn luyện] Thang 13 cards/11 đúng là oracle đào tạo, không phải chứng nhận Scrum.

> **Simulated disclosure:** NovaShop, nhân sự và mọi evidence card đều giả lập; không có production claim.

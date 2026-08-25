# Unit U07: Daily Scrum, flow và impediment — Học liệu cốt lõi

> **Khóa học:** Agile–Scrum thực hành qua dự án thương mại điện tử NovaShop · **Thuộc:** Sprint Execution và Quality · **Mức xác thực:** simulated

## 🎯 Learning Outcomes

- **LO7.1** — Điều phối Daily Scrum đúng timebox, tập trung vào tiến độ tới Sprint Goal và tạo kế hoạch hành động cho ngày tiếp theo. Bằng chứng: Daily Scrum record và board snapshot.
- **LO7.2** — Dùng flow evidence để nhận diện impediment và chọn ít nhất một adaptation không làm suy giảm chất lượng. Bằng chứng: impediment log, impact analysis và adaptation decision.

## Ngữ cảnh và phần tăng trưởng M-U07

NovaShop đang thực hiện Sprint tạo lát cắt checkout dùng payment sandbox. Học viên vào vai Developers; Product Owner và Scrum Master hỗ trợ nhưng không biến Daily Scrum thành buổi báo cáo quản lý. Từ Sprint Goal, Sprint Backlog và board ngày 1 của M-U06, nhóm tạo ba artifact mới: **Daily Scrum record**, **impediment log** và **adaptation decision**. Chúng được dùng để chứng minh rằng kế hoạch thay đổi theo evidence nhưng Definition of Done (DoD) vẫn giữ nguyên.

Mục tiêu nghiệp vụ và số liệu của NovaShop đều là giả lập. Không dùng dữ liệu khách hàng, thẻ thanh toán hay credential thật.

## Nguồn đầu vào đã map

- **SRC-SG20** — [The Scrum Guide](https://scrumguides.org/scrum-guide.html), Ken Schwaber & Jeff Sutherland/ScrumGuides.org, November 2020, accessed 2026-08-25, CC BY-SA 4.0, allowed use: adapt.
- **SRC-EVENTS** — [Introduction to the Scrum Events](https://www.scrum.org/resources/introduction-scrum-events), Scrum.org, snapshot/accessed 2026-08-25, website terms, allowed use: reference.
- **SRC-KANBAN-SCRUM** — [Kanban Guide for Scrum Teams](https://www.scrum.org/resources/kanban-guide-scrum-teams), 2021 edition, accessed 2026-08-25, CC BY-SA 4.0, allowed use: adapt.
- **SRC-PROJECT** — `starter/NovaShop_Project_Brief.md`, training artifact version 1.0, accessed 2026-08-25, internal approved for learner use.

## 1. Kiến thức tiên quyết và môi trường

Học viên cần hoàn thành U06, có Sprint Goal, Sprint Backlog và hiểu DoD của NovaShop. Môi trường `ENV-PRO-ARTIFACT` chỉ cần trình soạn Markdown, bảng tính CSV UTF-8 và bảng cộng tác/paper tương đương; không cần runtime hay dịch vụ trả phí.

Smoke check: mở được ba starter asset hoặc bản sao do giảng viên cung cấp; xác nhận mọi ID Sprint Goal/PBI nhất quán; tạo một file làm việc mới, không sửa starter asset. Nếu asset chưa có trong workspace, dùng nguyên bảng dữ liệu nhúng trong ví dụ/lab làm fallback và ghi nguồn là “embedded simulated fixture”.

## 2. Mental map

`Sprint Goal + Sprint Backlog (U06) → Daily inspection (U07) → plan/board adaptation → Increment evidence (U08) → causal learning (U09)`

Daily Scrum là vòng inspect-and-adapt ngắn ở cấp kế hoạch ngày. Nó không quyết định một PBI đã Done; quality gate đó thuộc U08. Flow evidence làm vấn đề chờ đợi hiện ra sớm, còn U09 sẽ dùng chuỗi evidence nhiều ngày để kiểm tra nguyên nhân và thử nghiệm cải tiến.

## 3. Nội dung lý thuyết cốt lõi

**Checklist Content Outlines:**

- [x] Daily Scrum hướng Sprint Goal và kế hoạch hành động
- [x] Flow evidence, impediment và adaptation không giảm chất lượng

### OUT-U07-01 — Daily Scrum hướng Sprint Goal và kế hoạch hành động

**Mapping:** OUT-U07-01 · LO7.1 · M-U07/Daily Scrum record và board snapshot.

#### Định nghĩa và ranh giới

Daily Scrum là sự kiện 15 phút cho Developers để inspect tiến độ tới Sprint Goal và adapt Sprint Backlog khi cần. Developers tự chọn cấu trúc miễn là kết quả là một kế hoạch có thể hành động cho ngày làm việc tiếp theo. Product Owner hoặc Scrum Master chỉ tham gia với tư cách Developers khi họ đang làm Sprint Backlog item.

Daily Scrum không phải status report cho quản lý, không phải vòng đọc “hôm qua/hôm nay/blocker” bắt buộc, và không phải nơi giải quyết chi tiết mọi vấn đề. Thảo luận sâu được tách ra sau timebox với đúng người liên quan.

#### Vấn đề, vai trò và quyết định

Board có thể trông bận rộn nhưng Sprint Goal vẫn có nguy cơ. Developers cần trả lời ba quyết định: evidence mới nói gì về tiến độ tới Goal; kế hoạch ngày tới cần đổi gì; cuộc trao đổi chi tiết nào phải diễn ra sau sự kiện. Người dùng record là chính Developers; stakeholder chỉ cần thấy trạng thái và quyết định minh bạch, không điều khiển cách làm.

#### Cơ chế và mental model

Luồng ra quyết định là `Sprint Goal → board/evidence hiện tại → rủi ro khoảng cách tới Goal → adaptation → owner + thời điểm kiểm tra lại`. Nếu bắt đầu từ từng cá nhân, nhóm dễ tối ưu mức bận rộn. Nếu bắt đầu từ Goal, nhóm có thể dừng một việc ít liên quan để cùng hoàn thành lát cắt quan trọng.

Một Daily Scrum record tối thiểu có:

| Trường | Oracle quan sát được |
| --- | --- |
| Sprint Goal | ID và câu outcome, không chỉ danh sách việc |
| Evidence lúc bắt đầu | timestamp và board item cụ thể |
| Progress/risk to Goal | kết luận nối trực tiếp evidence với Goal |
| Adaptation | board/plan thay đổi gì, không thay DoD |
| Owner và review time | một người/nhóm chịu hành động, thời điểm kiểm tra lại |
| Parking lot | chủ đề cần thảo luận sâu sau 15 phút |

#### Khi dùng, khi không dùng và trade-off

Dùng mỗi ngày làm việc của Sprint, cùng giờ/nơi nếu phù hợp để giảm chi phí phối hợp. Không chờ Daily Scrum mới cập nhật plan khi evidence khẩn cấp xuất hiện; Developers có thể re-plan bất cứ lúc nào trong ngày. Timebox buộc nhóm tập trung vào quyết định, nhưng quá cứng nhắc với một kịch bản nói cố định có thể che mất Goal; tự do cấu trúc vẫn phải tạo actionable plan.

#### Ví dụ thực tế có oracle

- **Context:** Sprint Goal `SG-07: người mua hoàn tất checkout sandbox và giữ nguyên dữ liệu đã nhập khi payment bị từ chối`.
- **Baseline 09:00 ngày 2:** `CHK-71` address validation đang làm 2 ngày; `CHK-72` payment callback bị sandbox chặn tới 14:00; `CHK-73` telemetry đang Ready. WIP đang làm = 2, đúng policy limit 2.
- **Decision:** không kéo `CHK-73`; Mai và Nam cùng hoàn tất evidence cho `CHK-71`; An xác nhận sandbox lúc 14:00; 09:20 Mai/Nam trao đổi riêng về validation fixture.
- **Artifact:** record `DS-D2` và board diff Ready→In Progress không đổi, owner/review time được thêm.
- **Expected:** đến 14:15 có evidence mới cho `CHK-71` và status sandbox; không có việc thứ ba được bắt đầu; DoD không đổi.
- **Oracle:** PASS khi record nêu Goal, timestamp, board IDs, action/owner/review time; board trước/sau khớp record; thời lượng ≤15 phút. REVISE nếu chỉ ghi hoạt động cá nhân hoặc không tạo plan.

#### Best practices

- **Rule:** mở đầu bằng Sprint Goal và chênh lệch tới Goal. **Rationale:** tạo focus ở outcome chung. **Positive:** “Failure-path của `CHK-72` chưa có evidence, Goal có nguy cơ.” **Negative:** “Nam hôm qua sửa ba bug” không cho biết Goal tiến hay lùi; nhóm có thể tiếp tục bận rộn sai việc.
- **Rule:** mỗi adaptation phải có owner và review time. **Rationale:** quyết định không có điểm kiểm tra không tạo feedback loop. **Positive:** “An kiểm sandbox 14:00, cập nhật `IMP-07` trước 14:15.” **Negative:** “Theo dõi thêm” khiến impediment tồn tại mà không ai chịu trách nhiệm.
- **Rule:** tách problem-solving sâu khỏi timebox. **Rationale:** giữ sự kiện ngắn nhưng không bỏ vấn đề. **Positive:** parking lot có người cần tham gia và giờ bắt đầu. **Negative:** cả nhóm debug 40 phút, mất cơ hội inspect phần còn lại.

#### Failure diagnosis

| Dấu hiệu | Nguyên nhân khả dĩ | Chẩn đoán/evidence | Sửa và phòng tránh |
| --- | --- | --- | --- |
| Mọi câu đều hướng về Scrum Master | Sự kiện bị biến thành status report | Record không có Goal/board diff; quản lý giao việc | Developers luân phiên điều phối, dùng goal-first prompt; Scrum Master coaching ngoài sự kiện |
| Record có nhiều update nhưng không có action | Chỉ inspection, thiếu adaptation | So record với board sau 30 phút | Bắt buộc owner + review time trước khi đóng record |
| Timebox liên tục quá 15 phút | Problem-solving bị trộn vào | Đếm số chủ đề chi tiết và thời lượng | Parking lot; chỉ giữ quyết định cần cho plan ngày |

### OUT-U07-02 — Flow evidence, impediment và adaptation không giảm chất lượng

**Mapping:** OUT-U07-02 · LO7.2 · M-U07/flow board, impediment log và adaptation decision.

#### Định nghĩa và ranh giới

Flow evidence là dữ liệu quan sát được về trạng thái công việc: số item đang làm (WIP), tuổi item, thời gian bị blocked, hàng đợi và lần chuyển trạng thái. Đây là tín hiệu để hỏi và inspect, không tự chứng minh nguyên nhân. Impediment là điều cản trở tiến độ của Scrum Team; một item “blocked” trên board có thể là biểu hiện, còn trở ngại cần xử lý có thể là lịch sandbox, thiếu quyền hoặc quyết định chưa rõ.

Adaptation hợp lệ thay đổi kế hoạch, thứ tự phối hợp hoặc cách gỡ trở ngại nhưng không giảm chất lượng. Trong Sprint, quality không được giảm; DoD không phải nút điều chỉnh để cứu forecast.

#### Vấn đề, vai trò và quyết định

Developers dùng evidence để quyết định dừng bắt đầu việc mới, swarm/pair, đổi thứ tự, làm rõ scope với Product Owner hoặc escalate impediment. Scrum Master hỗ trợ loại bỏ impediment nhưng không sở hữu mọi action. Product Owner cộng tác khi scope cần renegotiate mà vẫn bảo vệ Sprint Goal.

#### Cơ chế và mental model

Chuỗi đúng là `signal → giả thuyết → kiểm tra evidence → impact tới Goal → option → quality guardrail → decision → review`. Ví dụ WIP tăng là signal; nguyên nhân có thể là sandbox, PBI quá lớn hoặc nhiều handoff. Chỉ sau khi đối chiếu timestamps, blocked reason và dependency mới chọn adaptation.

Impediment log tối thiểu gồm `ID, phát hiện lúc, evidence link, Goal impact, owner, action/escalation, next review, status`. Adaptation decision thêm `options considered, trade-off, board diff, DoD guardrail`.

#### Khi dùng, khi không dùng và trade-off

Dùng flow evidence khi nhiều item dở dang, completion chậm hoặc dependency tạo hàng chờ. Không dùng một metric đơn lẻ để đánh giá cá nhân hay làm bằng chứng chắc chắn về cause. WIP limit làm tắc nghẽn lộ rõ và khuyến khích finish-before-start, nhưng limit quá thấp trong công việc thật sự độc lập có thể tạo nhàn rỗi; nhóm điều chỉnh policy dựa trên evidence, không phá DoD.

#### Ví dụ thực tế có oracle

Từ baseline ngày 2, `CHK-71` có tuổi 2 ngày và `CHK-72` blocked 4 giờ theo notice sandbox. Nhóm kiểm event card, xác nhận không phải thiếu năng lực cá nhân. Hai option được ghi: (A) bắt đầu telemetry; (B) swarm hoàn tất `CHK-71`, chờ sandbox theo timebox. Nhóm chọn B vì trực tiếp giảm khoảng cách tới Goal và giữ WIP=2. Guardrail: tất cả evidence acceptance, selected accessibility/security checks và review vẫn giữ nguyên.

PASS khi số WIP tính từ board khớp 2; impediment có evidence notice, owner và review 14:15; adaptation diff không xóa bất kỳ dòng DoD. REVISE nếu gọi sandbox là “root cause” nhưng không có notice/timestamp, hoặc nếu chuyển `CHK-72` sang Done để làm đẹp board.

#### Best practices

- **Rule:** phân biệt signal với cause. **Rationale:** cùng một WIP tăng có nhiều cơ chế. **Positive:** ghi “WIP=3, 2 item blocked cùng dependency; kiểm dependency log”. **Negative:** kết luận “team chậm” từ WIP; hậu quả là action đổ lỗi và không gỡ hàng chờ.
- **Rule:** ưu tiên finish-before-start khi Goal bị đe dọa. **Rationale:** giảm context switch và tạo evidence Done sớm. **Positive:** swarm `CHK-71`, giữ `CHK-73` Ready. **Negative:** kéo thêm việc để mọi người bận, WIP tăng và feedback tới muộn.
- **Rule:** ghi quality guardrail cho mọi adaptation. **Rationale:** forecast không đáng tin nếu đổi định nghĩa chất lượng giữa Sprint. **Positive:** giảm scope nhưng giữ DoD. **Negative:** bỏ keyboard test để kịp demo, tạo trạng thái Done giả.

#### Failure diagnosis

| Dấu hiệu | Nguyên nhân khả dĩ | Chẩn đoán/evidence | Sửa và phòng tránh |
| --- | --- | --- | --- |
| Board có nhãn Blocked nhưng không ai hành động | Log thiếu owner/review | So blocked card với impediment log | Tạo `IMP-*`, owner, escalation path và review time |
| WIP count tranh cãi | Chính sách trạng thái không rõ | Đếm card ở các cột thuộc WIP policy | Ghi policy ngay trên board và lưu snapshot có timestamp |
| Adaptation “đạt forecast” nhưng quality gate mất | Nhóm coi DoD là tùy chọn | Diff DoD/checklist trước–sau | Khôi phục DoD; thương lượng scope, không thương lượng chất lượng |

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### MEX-U07-01 — Daily flow decision record cho checkout

**Mode:** professional_artifact · **LO:** LO7.1, LO7.2 · **Outline:** OUT-U07-01, OUT-U07-02 · **Lab:** `LAB-U07-01/CP-U07-01` và `CP-U07-02`.

### Input và board snapshot 09:00 ngày 2

| ID | Liên hệ Goal | State | Age | Blocked evidence |
| --- | --- | --- | ---: | --- |
| CHK-71 | Address validation | In Progress | 2 ngày | Không |
| CHK-72 | Payment decline/retain input | In Progress | 1 ngày | `SBX-NOTICE-14`, 4 giờ |
| CHK-73 | Telemetry | Ready | 0 | Không |

Sprint Goal: `SG-07`. WIP policy: In Progress + Verify, limit 2. DoD version: `DOD-NS-1.0`.

### Artifact hoàn chỉnh

| Trường | Record `DS-D2` |
| --- | --- |
| Progress to Goal | Happy path đã tích hợp; failure-path chưa thể kiểm tra vì sandbox; Goal có rủi ro trung bình |
| Flow evidence | WIP 2/2; `CHK-71` age 2 ngày; `CHK-72` blocked theo `SBX-NOTICE-14` |
| Decision | Không kéo `CHK-73`; swarm hoàn tất evidence `CHK-71`; kiểm sandbox theo lịch |
| Owner/review | Mai + Nam/11:30; An/14:15 |
| Parking lot | 09:20, Mai + Nam kiểm validation fixture |
| Quality guardrail | Giữ `DOD-NS-1.0`; không đánh dấu Done nếu thiếu failure-path evidence |

Board diff: không có item mới vào WIP; gắn `IMP-07` vào `CHK-72`; thêm action/review time vào Sprint Backlog.

### Oracle

- `DS-01`: record bắt đầu từ `SG-07`, có progress/risk và kế hoạch ngày tới.
- `DS-02`: timebox ≤15 phút; discussion sâu được parking.
- `FLOW-01`: WIP trên record = số card thuộc policy = 2.
- `IMP-01`: impediment nối evidence → impact → owner/action → review.
- `QG-01`: DoD ID trước/sau vẫn là `DOD-NS-1.0`; không có undone item được gọi Done.

Kết quả mong đợi là 5/5 oracle PASS. Đây là artifact mẫu để hiểu cấu trúc, không phải fixture cần sao chép. Lab dùng board và change card khác.

### Mapping Material worked example → Hands-on Lab tương ứng

- **MEX-U07-01** → **LAB-U07-01/CP-U07-01** và **LAB-U07-01/CP-U07-02**; cùng phủ LO7.1, LO7.2 và yêu cầu evidence riêng theo từng checkpoint.

## 5. Quy tắc troubleshooting tổng hợp

Khi record không pass, kiểm theo thứ tự: (1) input có timestamp/ID; (2) Sprint Goal có hiện diện; (3) số liệu board có tái tính được; (4) decision có owner/review; (5) DoD có bị thay đổi. Lỗi input được sửa bằng fixture fallback; lỗi khái niệm được sửa bằng viết lại chuỗi evidence→impact→decision; không “sửa” bằng cách xóa evidence bất lợi.

## 6. Thuật ngữ

- **Actionable plan:** kế hoạch đủ action, owner và thời điểm kiểm tra lại.
- **Board snapshot/diff:** trạng thái công việc tại một thời điểm/thay đổi giữa hai thời điểm.
- **Blocked:** trạng thái item không thể tiến vì một điều kiện cụ thể; cần evidence.
- **Impediment:** trở ngại làm giảm tiến độ/effectiveness của Scrum Team.
- **WIP:** các item nằm trong những state được policy xác định là đang làm.
- **Quality guardrail:** điều kiện không được phá khi adapt, ở đây gồm DoD.

## 7. Nguồn tham khảo và provenance phần bổ sung

Các quy tắc Scrum cốt lõi bám SRC-SG20; flow practices bám SRC-KANBAN-SCRUM; fixture, ID, WIP policy, oracle và artifact NovaShop là **[BỔ SUNG — nguồn: SRC-PROJECT, dữ liệu mô phỏng được tạo cho khóa học]**. Không có tuyên bố benchmark ngành hoặc dữ liệu dự án thật.

# Unit U04 — Assignment 02: Change request: guest checkout và MVP slice

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASM-U04 |
| Hình thức | team, thực hiện độc lập |
| Thời lượng | 90 phút |
| Độ khó/Bloom | medium / create |
| Xác thực | simulated |
| Validation | artifact_review |

> Đây là đánh giá độc lập. Đề nêu contract và oracle, không cung cấp trình tự giải, story map mẫu, backlog mẫu hoặc quyết định tham chiếu.

## 🎯 Learning Outcomes được đánh giá

- **LO4.1:** chuyển customer journey thành Story Map và Product Backlog có traceability.
- **LO4.2:** chia MVP thành lát dọc và viết acceptance criteria quan sát được, gồm happy cùng edge/failure behavior.

## 🧭 Change request và trạng thái ban đầu

NovaShop nhận **CR-ASM-U04**. Business muốn guest checkout để giảm ma sát được phản ánh bởi `OBS-01` (7/10 người mô phỏng bỏ checkout khi bị buộc tạo tài khoản). Kho vận đồng thời nêu `OBS-02` (4/12 đơn mô phỏng cần nhập lại địa chỉ). Security reviewer yêu cầu không thu thập dữ liệu ngoài nhu cầu tạo và giao đơn.

Input pack gồm:

- **Team Charter** và **Working Agreement** từ ASM-U02;
- Product Goal card và Customer journey đã được phê duyệt ở U03;
- project brief, `OBS-01`, `OBS-02`, `FR-03`, `NFR-04` và Definition of Done;
- change card: guest có giỏ một SKU synthetic; địa chỉ có đủ `tỉnh/thành`, `quận/huyện`, `phường/xã`, `đường`, `mã vùng giao hàng`; payment chỉ nhận trạng thái sandbox;
- edge card mới cho Assignment: địa chỉ vượt qua kiểm tra trường bắt buộc và định dạng, nhưng shipping-service sandbox trả `UNSERVICEABLE_ZONE` cho mã vùng `REMOTE-99` ở bước kiểm tra khả năng giao hàng. Đây là lỗi dependency/serviceability sau validation, khác failure “thiếu phường/xã” trước lookup của Lab.

Không có tài khoản, địa chỉ lưu hoặc PBI guest-checkout sẵn. Product Goal giữ nguyên. Marketplace, loyalty, tiền/thẻ thật, hoàn tiền và implementation design nằm ngoài phạm vi.

## 🔗 Liên kết project xuyên suốt

- **Milestone:** M-U04.
- **Depends on:** ASM-U02.
- **Baseline artifacts tiêu thụ:** Team Charter; Working Agreement. Đây là output của direct dependency ASM-U02; bài nộp phải chỉ ra ít nhất một working rule hoặc quyền quyết định đã ảnh hưởng cách review/ownership của artifact.
- **Prerequisite project inputs:** Product Goal card và Customer journey được tạo trong U03 rồi cấp như input cho scenario M-U04. Chúng không phải project-link baseline, không tạo thêm một Assignment dependency ngầm và không phải output cần chấm lại trong ASM-U04.
- **Produces:** Story Map; Product Backlog v1.
- **Reused by:** ASM-U06; vì vậy PBI ID, Goal link và evidence field phải ổn định để Assignment sau dùng làm baseline.
- **Terminal delivery:** NOT_APPLICABLE — đây chưa phải Assignment cuối.

## 🧠 Khái niệm và best practices được đánh giá

### TASK-U04-01 — Ra quyết định độc lập cho CR-ASM-U04

| Contract | Nội dung |
| --- | --- |
| Concept refs | OUT-U04-01, OUT-U04-02 |
| LO | LO4.1, LO4.2 |
| Scenario/input | Guest checkout; OBS-01/02; complete-address card với shipping result `UNSERVICEABLE_ZONE`; Team Charter; Working Agreement; Product Goal; journey |
| Deliverables | Story Map; Product Backlog v1 |
| Acceptance refs | AT-U04-01, AT-U04-02 |

**Best-practice constraint 1 — OUT-U04-01:** “Mọi quyết định thuộc OUT-U04-01 phải liên kết input, mục tiêu và evidence chấp nhận.” Rationale đã dạy: traceability ngăn quyết định cảm tính và cho phép stakeholder kiểm tra lại giả định; trong bài này, Product Goal/journey link còn cho ASM-U06 tiêu thụ PBI mà không đoán ý định. Áp dụng cho **AT-U04-01** và **RB-U04-01**.

**Best-practice constraint 2 — OUT-U04-02:** “Mọi thay đổi thuộc OUT-U04-02 phải nêu trade-off và cập nhật artifact downstream bị ảnh hưởng.” Rationale đã dạy: thay đổi cục bộ mà không cập nhật chuỗi artifact làm mất minh bạch; trong bài này, lát còn phải tạo outcome end-to-end và giữ DoD. Áp dụng cho **AT-U04-02** và **RB-U04-02**.

## 📋 Yêu cầu

### Functional requirements

- **FR-ASM-U04-01 [LO4.1]:** Story Map biểu diễn hành trình guest từ nhu cầu tìm/mua đến kết quả checkout; mỗi backbone trong lát được chọn có ít nhất một user task và evidence/Goal link.
- **FR-ASM-U04-02 [LO4.1]:** Product Backlog v1 chứa các PBI outcome của lát, dùng ID duy nhất và ghi actor, outcome, Goal/journey link, dependency/risk, open question cùng evidence dự kiến.
- **FR-ASM-U04-03 [LO4.2]:** lát MVP đi qua đủ capability để guest nhận kết quả checkout quan sát được; không dùng UI/API/database task làm PBI giá trị.
- **FR-ASM-U04-04 [LO4.2]:** mọi PBI được chọn có acceptance examples; tập criteria bao phủ happy checkout và edge địa chỉ đầy đủ/đúng định dạng nhưng shipping sandbox trả `UNSERVICEABLE_ZONE`.

### Non-functional requirements

- **NFR-ASM-U04-01 [LO4.2] — Không thu thập dữ liệu ngoài nhu cầu checkout:** artifact không yêu cầu ngày sinh, giới tính, password, dữ liệu thẻ hay thông tin ngoài outcome; reviewer xác minh bằng data-field inventory trong Product Backlog v1.
- **NFR-ASM-U04-02 [LO4.2] — Giữ lát dọc có thể kiểm chứng:** happy/edge outcome phải có oracle end-to-end; failure không được hạ DoD hoặc mô tả work chưa Done là Increment, và impact/boundary phải hiện trong Product Backlog v1.

### Constraints và out of scope

- Chỉ dùng dữ liệu synthetic và payment/shipping sandbox.
- Không đổi Product Goal; nếu nhận thấy xung đột, ghi assumption/risk thay vì tự sửa Goal.
- Không đưa quyết định implementation, endpoint, schema hay thiết kế UI thành điều kiện chấm.
- Không sao chép PBI, ID hoặc acceptance examples của Material/Lab; similarity về field template là hợp lệ, similarity về quyết định/output không được tính là evidence transfer.
- Ước lượng, ordering và Sprint forecast chưa thuộc phạm vi bài này.

## 📦 Deliverables và cách nộp

1. **Story Map** — một artifact Markdown/PDF/whiteboard export có: actor/outcome, Goal ID, backbone, user tasks, lát MVP và later boundary; ID khớp Product Backlog v1.
2. **Product Backlog v1** — một artifact Markdown/PDF/bảng tính export có: PBI fields, acceptance examples, dependency/risk/evidence, data-field inventory, impact/trade-off note và traceability table.

Tên logic khi nộp: `ASM-U04_Story-Map` và `ASM-U04_Product-Backlog-v1`; định dạng cụ thể theo nền tảng lớp. Bài nộp đủ khi hai artifact mở được, cùng version, có tên nhóm/reviewer, timestamp mô phỏng, và chứa evidence cho AT-U04-01/02. Không nộp link yêu cầu quyền truy cập ngoài quy định lớp.

## ✅ Acceptance criteria và output mong đợi

### AT-U04-01 — Traceable story map/backlog [LO4.1 → RB-U04-01]

**Contract từ plan:** Artifact thể hiện đúng quyết định thuộc OUT-U04-01 và truy vết được tới dữ liệu đầu vào. Expected: người chấm xác định được input, quyết định, lý do và bằng chứng chấp nhận mà không cần suy đoán.

**Given** Team Charter, Working Agreement, Product Goal, customer journey và input CR-ASM-U04; **when** reviewer chọn ngẫu nhiên một backbone và một PBI; **then** reviewer lần được `input/evidence → journey/backbone → PBI → Product Goal → acceptance evidence` mà không suy đoán. Mọi backbone của lát có task, mọi PBI có trace, và không có item mồ côi.

**Expected result/evidence:** traceability table resolve 100%; Story Map và Product Backlog dùng cùng ID; bài nộp chỉ ra working rule/decision right từ ASM-U02 đã dùng khi review hoặc phân quyền.

### AT-U04-02 — Vertical slice và change consistency [LO4.2 → RB-U04-02]

**Contract từ plan:** Artifact xử lý change request mới thuộc OUT-U04-02 mà không phá vỡ mục tiêu và baseline đã được phê duyệt. Expected: tác động, trade-off, tiêu chí chấp nhận và phần cập nhật downstream đều nhất quán.

**Given** guest checkout cùng edge card có địa chỉ đầy đủ/đúng định dạng nhưng shipping sandbox trả `UNSERVICEABLE_ZONE`; **when** reviewer áp dụng happy và edge input vào criteria; **then** mỗi scenario có outcome quan sát được, trạng thái order/no-order và dữ liệu cần giữ được xác định, dependency result được phân biệt với lỗi thiếu trường, DoD không giảm, data minimization không bị vi phạm, và impact/trade-off nhất quán trên hai artifact.

**Expected result/evidence:** reviewer có thể kết luận PASS/FAIL từ criteria; lát không phải tập task theo tầng; phần cập nhật downstream và boundary không mâu thuẫn; data-field inventory không chứa field ngoài phạm vi.

## 🧪 Cách xác minh

Hai reviewer độc lập dùng AT-U04-01 và AT-U04-02. Mỗi người ghi `PASS` hoặc `REVISE`, PBI/backbone được chọn, evidence location và lý do. Nếu kết luận khác nhau, artifact chưa có oracle đủ rõ và phải REVISE. Kết quả cuối chỉ PASS khi cả hai acceptance tests PASS, hai artifact cùng version và không có dữ liệu thật.

## 📊 Rubric chấm điểm — tổng 100%

| ID | Trọng số | LO | Bằng chứng | Excellent | Meets | Partial | Not met |
| --- | ---: | --- | --- | --- | --- | --- | --- |
| RB-U04-01 — Đúng khái niệm, truy vết và evidence | 50% | LO4.1 | AT-U04-01; Story Map; traceability trong Product Backlog v1 | Toàn bộ link hai chiều resolve; rationale/evidence độc lập; dùng rõ governance baseline và giải thích trade-off | Backbone/PBI đúng outcome; đủ input, Goal/journey link và evidence; không item mồ côi | Quyết định hợp lý nhưng thiếu một link/evidence hoặc một backbone chưa được phủ | Không truy vết được, map theo component hoặc artifact mâu thuẫn |
| RB-U04-02 — Xử lý thay đổi và tính nhất quán downstream | 50% | LO4.2 | AT-U04-02; acceptance examples; impact/data-field note | Happy/edge/failure rõ, lát thật sự end-to-end, boundary/data minimization/DoD nhất quán và trade-off thuyết phục | Lát tạo outcome; criteria quan sát được; edge card và downstream impact được xử lý đúng | Có lát và criteria nhưng thiếu một edge outcome, boundary hoặc consistency link quan trọng | Lát theo tầng, criteria không kiểm được, vi phạm data constraint hoặc hạ DoD |

**Điểm đạt:** 70%. Tổng trọng số: **100%**.

## 📚 Nguồn và provenance

- **SRC-SG20** — Scrum Guide, November 2020, ScrumGuides.org, accessed 2026-08-25, CC BY-SA 4.0, adapt.
- **SRC-USER-STORIES** — Agile Alliance User Stories, living snapshot/accessed 2026-08-25, website terms, reference.
- **SRC-STORY-MAP** — Jeff Patton/O'Reilly, September 2014, accessed 2026-08-25, copyright; bibliographic reference/paraphrase only.
- **SRC-GHERKIN** — Cucumber Gherkin Reference, living snapshot/accessed 2026-08-25, documentation terms, reference.
- NovaShop project brief và synthetic CSV chỉ là project input/fixture do `plan.project` quản lý, không phải source ref hoặc nguồn provenance bổ sung của U04. Scenario, actor, địa chỉ, order và status đều simulated; phần kiến thức chỉ dùng bốn source refs đã liệt kê.
- Không dùng nguồn bổ sung. Edge card của Assignment là dữ liệu synthetic mới để đánh giá transfer, không phải yêu cầu khách hàng thật.

---
<!-- QUALITY GATE: concept/LO → input → constraint → deliverable → AT/evidence → rubric resolve; A02 consumes ASM-U02 and produces artifacts for ASM-U06; no walkthrough or solution. -->

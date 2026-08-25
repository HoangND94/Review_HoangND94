# Unit U10: Metrics, forecasting và release planning — Học liệu cốt lõi

> **Khóa học:** Agile–Scrum thực hành qua dự án thương mại điện tử NovaShop · **Milestone:** M-U10 · **Xác thực:** simulated

## 🎯 Learning Outcomes

- **LO10.1 — Analyze:** Tính và diễn giải đúng WIP, cycle time, throughput cùng value metrics trên dataset mô phỏng.
- **LO10.2 — Create:** Lập release forecast theo ba kịch bản, nêu assumptions, uncertainty, risk và trigger cập nhật.

## Project increment

Unit này biến Product Backlog v3, flow history và value signals thành ba artifact được Capstone sử dụng: **Metrics dashboard**, **Release forecast** và **Improvement roadmap**. Học viên đóng vai Scrum Team tư vấn sponsor; nhiệm vụ là làm bất định minh bạch, không hứa một ngày chắc chắn mà dữ liệu không chứng minh được.

## Nguồn và ranh giới

- Scrum Guide 2020: empiricism, forecast dựa trên điều đã xảy ra và quyền release không phụ thuộc Sprint Review.
- Evidence-Based Management Guide, May 2024: dùng evidence và experiment để hướng tới outcome.
- Scrum.org, *Introduction to Forecasting and Release Planning*, snapshot 2026-08-25: forecast không phải commitment/guarantee.
- *Kanban Guide for Scrum Teams*, 2021: flow metrics bổ trợ Scrum; chúng không thay thế Product Goal, Sprint Goal hay các Scrum events.
- Dữ liệu NovaShop là synthetic; các tỷ lệ chỉ mô tả scenario, không phải benchmark thương mại điện tử.

## Tiên quyết và môi trường

Hoàn thành U09; có Product Backlog v3, Sprint Review record và [dataset synthetic](../../starter/NovaShop_Synthetic_Data.csv). Dùng spreadsheet đọc CSV UTF-8 hoặc tính tay. Không cần runtime, cloud service, credential hay dữ liệu thật. Preflight đạt khi mở được dataset, nhìn thấy các `record_type` `flow`, `metric`, `risk`, và xác nhận công thức dùng quy ước **elapsed days = finish_day − start_day**.

## Mental map

`Goal → evidence window → metric → interpretation → scenario forecast → release decision → inspect/update`

Metric không tự đưa ra quyết định. Nó nén một tập quan sát theo một measurement contract. Forecast dùng các quan sát đó cộng với assumptions để tạo một range có điều kiện. Khi evidence hoặc assumption đổi, Scrum Team inspect và cập nhật forecast; không “bảo vệ con số cũ”.

## 3. Nội dung lý thuyết cốt lõi

**Checklist bắt buộc phủ — giữ nguyên văn và đúng thứ tự Content Outlines:**

- [x] Flow metrics, value metrics và giới hạn diễn giải
- [x] Release forecasting theo kịch bản, uncertainty và risk

#### OUT-U10-01 — Flow metrics, value metrics và giới hạn diễn giải

**Mapping:** OUT-U10-01 · LO10.1 · M-U10 · artifact `Metrics dashboard`

##### Định nghĩa và ranh giới

**Work in Progress (WIP)** là số work item đã đi qua điểm bắt đầu nhưng chưa qua điểm kết thúc của workflow tại một thời điểm. **Cycle time** là thời gian từ lúc một item bắt đầu đến lúc hoàn tất theo hai điểm đã định nghĩa. **Throughput** là số item hoàn tất trong một time window. **Work item age** là thời gian một item đang mở đã ở trong workflow. Các metric chỉ so sánh được khi definition of workflow, đơn vị và cửa sổ dữ liệu nhất quán.

**Value metric** quan sát outcome hoặc hành vi stakeholder, chẳng hạn order success rate; nó khác output metric như số PBI Done. Một team có throughput cao nhưng conversion giảm vẫn có thể đang tạo nhiều output mà không tạo outcome mong đợi.

Velocity/story point không phải flow metric chuẩn hóa giữa các team. Story points là thang tương đối do từng team thiết lập; dùng chúng để xếp hạng team làm mất ý nghĩa và khuyến khích gaming. Flow metrics cũng không tự chứng minh năng suất cá nhân hay quan hệ nhân quả.

##### Vấn đề, vai trò và quyết định

Scrum Team cần trả lời ba câu khác nhau:

1. Công việc đang chảy thế nào và đâu là rủi ro flow?
2. Increment có làm thay đổi outcome người dùng/kinh doanh không?
3. Evidence đủ mạnh cho quyết định release, continue, adjust hay stop chưa?

Product Owner dùng value evidence để ordering; Developers dùng WIP/age/cycle time để inspect flow; sponsor dùng forecast range và risk để chọn mức đầu tư. Không dùng một metric duy nhất để thay cả ba quyết định.

##### Cơ chế và measurement contract

Mỗi metric phải có `name + purpose + formula + unit + start/finish rule + data window + exclusions + owner`.

Với Sprint 1 trong dataset:

- Items Done: PBI-101…PBI-106, nên throughput của window là **6 items/Sprint**.
- Cycle times theo quy ước `finish − start`: `2, 3, 3, 3, 4, 4` ngày; median là **3 ngày**. Median mô tả vị trí giữa của sample, không hứa item sau sẽ xong trong ba ngày.
- Tại cuối ngày 9, PBI-107 và PBI-108 chưa finish: WIP là **2**; age tương ứng là **2** và **1** ngày.
- Conversion mô phỏng là `135 order_success / 1000 visitors = 13,5%`.
- Checkout completion là `135 / 180 checkout_start = 75%`.
- Re-entry share là `9 / 135 = 6,67%`; nó chưa đạt target “tối đa 5% đơn hợp lệ cần nhập lại”.

Input sai làm metric sai: nếu `start_day` nghĩa là ngày tạo backlog còn một team khác dùng ngày bắt đầu active work, cycle time không còn cùng contract. Luôn kiểm data semantics trước công thức.

##### Khi dùng, khi không dùng và trade-off

Dùng WIP/age để inspect item đang tắc; cycle time/throughput để nhìn history và xây forecast cho item tương đối đồng nhất; value metric để đánh giá hướng đi tới Product Goal. Không dùng cycle-time average của sample nhỏ như SLA; không dùng conversion để quy toàn bộ thay đổi cho một feature khi không có experiment/control; không dùng throughput để bỏ qua kích thước hoặc loại công việc đã đổi.

Trade-off: metric đơn giản dễ dùng nhưng có thể che distribution; metric chi tiết tăng transparency nhưng tốn chi phí thu thập. Chọn tập metric tối thiểu đủ cho quyết định và ghi rõ blind spot.

##### Ví dụ NovaShop có thể kiểm chứng

- **Context:** Daily inspection trước cuộc họp release với sponsor.
- **Input:** các record Sprint 1; measurement date là cuối ngày 9.
- **Decision:** PBI-107 chưa đáng báo động theo history 3–4 ngày, còn PBI-108 mới một ngày; tuy nhiên re-entry share 6,67% vượt guardrail 5%, nên chưa được dùng order volume làm bằng chứng đủ cho goal “không nhập lại”.
- **Artifact:** dashboard ghi công thức, window, result, interpretation và limitation.
- **Expected:** reviewer tính lại được từng số; phần interpretation không tuyên bố causation hoặc guarantee.
- **Oracle:** PASS khi 6/6 công thức/đơn vị đúng, mọi kết luận liên kết data row, và có ít nhất một limitation; FAIL khi trộn start rules hoặc gọi 13,5% là benchmark ngành.

##### Best practices

- **Rule:** định nghĩa measurement contract trước khi tính. **Rationale:** cùng tên metric có thể dùng điểm bắt đầu/kết thúc khác nhau. **Positive:** “cycle time từ Active đến Done, elapsed days, Sprint 1”. **Negative:** chỉ ghi “cycle time = 3” khiến người đọc không biết đơn vị/window.
- **Rule:** ghép flow với value/quality signal. **Rationale:** tối ưu tốc độ đơn lẻ có thể tăng rework hoặc giảm outcome. **Positive:** đặt throughput cạnh re-entry share và DoD evidence. **Negative:** ăn mừng throughput tăng dù PBI chưa đạt quality gate.
- **Rule:** ghi limitation ngay cạnh kết luận. **Rationale:** người quyết định thường chỉ đọc dashboard. **Positive:** “sample 6 items; item mix Sprint 2 khác”. **Negative:** chôn limitation trong phụ lục rồi trình headline như certainty.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** team cố tăng số point Done. **Nguyên nhân:** dùng velocity làm target. **Chẩn đoán:** point scale đổi nhưng outcome/throughput không đổi. **Sửa:** quay lại Product Goal, flow/value evidence; dùng estimate cho conversation. **Phòng tránh:** cấm so velocity giữa team.
- **Dấu hiệu:** cycle time âm/trống. **Nguyên nhân:** finish trước start hoặc item chưa Done bị đưa vào cycle-time set. **Chẩn đoán:** lọc `state=done` và kiểm timestamp. **Sửa:** tách work item age cho item mở. **Phòng tránh:** data-quality check trước dashboard.
- **Dấu hiệu:** metric cải thiện nhưng stakeholder không thấy value. **Nguyên nhân:** đo output thay outcome. **Chẩn đoán:** không có link metric → Product Goal. **Sửa:** bổ sung outcome signal/experiment. **Phòng tránh:** mỗi dashboard card phải nêu decision supported.

#### OUT-U10-02 — Release forecasting theo kịch bản, uncertainty và risk

**Mapping:** OUT-U10-02 · LO10.2 · M-U10 · artifact `Release forecast` và `Improvement roadmap`

##### Định nghĩa và ranh giới

Forecast là phát biểu có điều kiện về kết quả tương lai dựa trên evidence hiện có và assumptions. Release plan là tập quyết định về scope, sequencing, risk, feedback và thời điểm xem xét lại. Forecast **không phải** commitment hoặc guarantee; release decision cũng không bị khóa vào cuối Sprint hay Sprint Review.

Scenario forecasting trình ít nhất ba điều kiện hợp lý—optimistic, base, conservative—để người đọc thấy sensitivity. Nó không phải ba lời đoán tùy ý: mỗi scenario phải nêu throughput/capacity assumption, backlog scope, risk và trigger làm scenario không còn hợp lệ.

##### Vấn đề, vai trò và quyết định

Sponsor cần quyết định tài trợ và truyền thông kỳ vọng; Product Owner cần chọn scope/value; Developers cần làm rõ dependency/DoD. Câu hỏi đúng là: “Với evidence và assumptions này, khoảng nào hợp lý, rủi ro nào chi phối, và khi nào cập nhật?” Câu hỏi sai là ép team đưa một ngày chắc chắn để tạo cảm giác kiểm soát.

##### Cơ chế lập forecast

1. Khóa scope snapshot và tiêu chí “Done”.
2. Chọn history có definition of workflow tương thích.
3. Ghi assumptions về item mix, capacity, dependency và quality.
4. Tính scenario bằng quy tắc minh bạch, ví dụ `ceil(remaining items / assumed throughput)`.
5. Thêm risk/guardrail, confidence statement và update trigger.
6. So sánh với Product Goal/value signal; chọn release/experiment/scope adaptation.

Với 18 PBI còn lại có kích thước tương đối đồng nhất:

| Scenario | Assumed throughput | Sprints theo `ceil(18/t)` | Điều kiện |
| --- | ---: | ---: | --- |
| Optimistic | 6 | 3 | Item mix giống Sprint 1; không có outage |
| Base | 5 | 4 | Có một phần capacity cho defect/feedback |
| Conservative | 4 | 5 | Payment risk hoặc accessibility rework tiêu thụ capacity |

Kết luận hợp lệ là **3–5 Sprint, base 4, confidence thấp–trung bình vì sample nhỏ**. Không chuyển nó thành “release chắc chắn sau bốn Sprint”.

##### Khi dùng, khi không dùng và trade-off

Dùng scenario forecast khi cần alignment/decision dưới bất định và có ít nhất một evidence window cùng definition. Không dùng history cũ khi product/team/workflow đổi mạnh; không forecast item chưa có boundary; không thêm precision bằng ngày/giờ nếu data không hỗ trợ. Khi sample quá nhỏ, dùng forecast như hypothesis, thu thêm data và đặt review sớm.

Trade-off scope–time–risk phải công khai. Giữ fixed date có thể cần giảm scope nhưng không giảm DoD; giữ scope có thể mở range; mua thêm capacity không bảo đảm throughput tăng ngay vì dependency/coordination.

##### Ví dụ triển khai trong Material — MEX-U10-01

**Stable ID:** `MEX-U10-01` · **Tên:** Metrics-to-forecast decision sheet · **Medium:** professional artifact · **LO:** LO10.1, LO10.2 · **Outline:** OUT-U10-01, OUT-U10-02

**Input/dependency:** dataset Sprint 1, Product Backlog snapshot còn 18 PBI, risk RISK-01, measurement contract `Active→Done`, Sprint là time window. Không cần code.

**Artifact đã hoàn thiện:**

| Khối | Nội dung quyết định |
| --- | --- |
| Evidence window | Sprint 1; 6 Done items; cycle-time median 3 ngày; WIP cuối ngày 9 = 2 |
| Value/quality | conversion 13,5%; checkout completion 75%; re-entry 6,67% vượt guardrail 5% |
| Scope snapshot | 18 PBI tương đối đồng nhất; DoD giữ nguyên |
| Forecast | optimistic 3, base 4, conservative 5 Sprint |
| Risk | RISK-01 payment sandbox open; accessibility evidence có thể tạo rework |
| Decision | Dùng range 3–5 Sprint để planning; ưu tiên giảm re-entry và đóng payment risk trước release claim |
| Update trigger | Sau mỗi Sprint; hoặc khi scope đổi >10%, throughput <4, DoD đổi, hay risk impact tăng |
| Limitation | Một Sprint history; không benchmark; không guarantee |

**Luồng quyết định:** rows `flow/metric/risk` → kiểm contract và tính metric → tạo scenario từ scope/throughput → thêm risk/value guardrail → phát biểu range và trigger. Khối “Decision” không được viết trước “Evidence window”.

**Happy path:** item mix và workflow tương thích; reviewer tính lại 3/4/5 Sprint và dùng range. **Edge path:** PBI-203 Sprint 2 có cycle time 8 ngày; sheet giữ outlier, giải thích impact và hạ confidence thay vì xóa. **Failure path:** backlog trộn epic chưa split; dừng forecast item-count, refine/slice trước hoặc dùng một measurement contract khác.

**Verification/oracle:**

- công thức flow/value khớp dataset và có unit/window;
- ba scenario tái lập được từ scope cùng assumptions;
- risk, DoD, limitation và update trigger hiện ngay trong sheet;
- không có từ ngữ guarantee/commitment cho range;
- reviewer độc lập đi tới cùng số scenario và hiểu điều kiện làm forecast vô hiệu.

**Expected result:** artifact review `PASS` khi đủ năm oracle; thiếu limitation/risk là `REVISE`; sai formula hoặc gọi forecast là cam kết là `FAIL`.

### Mapping Material worked example → Hands-on Lab tương ứng

`MEX-U10-01` được tái tạo với dataset Sprint 2 tại `LAB-U10-01/CP-U10-01`, rồi bị stress-test bằng outlier/risk tại `CP-U10-02`. Hai checkpoint cùng map LO10.1/LO10.2 và dùng input khác; Lab không copy nguyên các số 18/6/5/4 của ví dụ.

##### Best practices

- **Rule:** forecast bằng range/scenario và update trigger. **Rationale:** uncertainty thay đổi theo evidence. **Positive:** “3–5 Sprint; review sau Sprint hoặc scope +10%”. **Negative:** “ngày X chắc chắn” dựa trên một Sprint.
- **Rule:** giữ DoD là guardrail. **Rationale:** hạ quality biến throughput thành output chưa usable. **Positive:** giảm scope nhưng giữ security/accessibility evidence đã chọn. **Negative:** bỏ test để đạt date rồi gọi work là Done.
- **Rule:** tách decision, assumption và fact. **Rationale:** stakeholder cần biết cái gì đo được và cái gì là bet. **Positive:** mỗi scenario có assumption owner. **Negative:** ghi capacity dự kiến như dữ liệu đã xảy ra.

##### Anti-pattern, failure modes và troubleshooting

- **False precision:** ngày cụ thể nhưng không có probability/range. Chẩn đoán bằng cách hỏi “assumption nào tạo chữ số cuối?”; sửa bằng scenario window và confidence.
- **Stale forecast:** scope/history đổi mà sheet không đổi. So sánh snapshot IDs; cập nhật sau trigger; version forecast cùng backlog.
- **Risk-free base case:** risk register không xuất hiện trong scenario. Map mỗi open high-impact risk tới throughput/scope/guardrail; nếu không thể lượng hóa, hạ confidence và đặt decision checkpoint.
- **Average hides outlier:** chỉ dùng mean 3,6 ngày cho Sprint 2. Xem distribution/outlier, không xóa observation; ghi cause và sensitivity.

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

Một sponsor hỏi: “Conversion 13,5% rồi, có thể release trong bốn Sprint không?” Scrum Team không trả lời trực tiếp từ conversion. Họ kiểm quality guardrail (re-entry 6,67% chưa đạt), flow window (một Sprint), scope (18 PBI), risk (payment open), rồi đưa range 3–5 Sprint và điều kiện review. Output là `MEX-U10-01`; oracle là reviewer tái lập được công thức, scenario và lý do chưa thể guarantee.

## 5. Lỗi thường gặp và quy tắc áp dụng

| Dấu hiệu | Nguyên nhân | Evidence chẩn đoán | Sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| Dashboard nhiều số nhưng không có decision | Metric vanity | Card thiếu Product Goal/decision link | Bỏ metric không hỗ trợ quyết định | Measurement contract bắt buộc purpose |
| Forecast thay đổi tùy người trình bày | Assumption ngầm | Không có scope/version/window | Version hóa scope và assumption | Peer reproduce trước khi publish |
| Throughput tăng, chất lượng giảm | DoD bị nới | Undone/rework tăng | Khôi phục DoD; forecast lại | Quality guardrail cạnh flow metric |
| Outlier bị xóa | Muốn làm range đẹp | Raw data và dashboard lệch | Giữ outlier, giải thích sensitivity | Data-quality log và review |
| Sponsor đọc base là cam kết | Ngôn ngữ certainty | Memo không có range/trigger | Đổi headline và thêm conditions | Luôn nêu “forecast, not guarantee” |

## 6. Từ điển thuật ngữ

- **WIP:** item đã bắt đầu nhưng chưa kết thúc theo workflow.
- **Cycle time:** elapsed time giữa điểm start/finish đã định nghĩa.
- **Throughput:** số item hoàn tất trong time window.
- **Work item age:** elapsed time của item đang mở.
- **Value metric:** evidence về outcome/stakeholder value, không đồng nghĩa output.
- **Forecast:** dự báo có điều kiện, không phải cam kết.
- **Scenario:** tập assumptions nhất quán tạo một kết quả forecast.
- **Guardrail:** ngưỡng không được hy sinh khi tối ưu mục tiêu khác.
- **Update trigger:** sự kiện buộc inspect và tính/ra quyết định lại.

## 7. Nguồn tham khảo và provenance phần bổ sung

- [The Scrum Guide, November 2020](https://scrumguides.org/scrum-guide.html) — CC BY-SA 4.0.
- [Evidence-Based Management Guide, May 2024](https://www.scrum.org/resources/online-evidence-based-management-guide) — CC BY-SA 4.0.
- [Introduction to Forecasting and Release Planning](https://www.scrum.org/resources/introduction-forecasting-and-release-planning) — reference-only, accessed 2026-08-25.
- [Kanban Guide for Scrum Teams](https://www.scrum.org/resources/kanban-guide-scrum-teams) — complementary practice.
- `[SUY DIỄN — từ kiến thức đã huấn luyện]` Các con số, target, scenario và decision sheet NovaShop được tạo cho đào tạo bằng dữ liệu synthetic; không phải kết quả hay benchmark thật.

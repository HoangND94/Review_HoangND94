# Hands-on Lab 10 — Forecast release NovaShop dưới ba kịch bản

| Thuộc tính | Giá trị |
| --- | --- |
| Lab ID | LAB-U10-01 |
| Thời lượng | 75 phút (pilot variance ±20%) |
| Mode | guided_with_fading |
| Learning Outcomes | LO10.1, LO10.2 |
| Material example | MEX-U10-01 |
| Validation | artifact_review |
| Xác thực | simulated |

## 🎯 Learning Outcomes được thực hành

- **LO10.1:** tính/diễn giải WIP, work item age, cycle time, throughput và value/quality signal với unit/window/limitation.
- **LO10.2:** tạo forecast ba kịch bản, stress-test risk/scope change và đặt update trigger.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

- `MEX-U10-01 → LAB-U10-01/CP-U10-01`: tái tạo decision sheet bằng Sprint 2 và scope 14.
- `MEX-U10-01 → LAB-U10-01/CP-U10-02`: mở rộng bằng outlier, payment risk và scope 17.

## Why và project slice

Sponsor chuẩn bị quyết định release nhưng Sprint 2 có outlier shipping và open payment risk. Bạn phải tái tạo cấu trúc `MEX-U10-01` bằng input mới, sau đó stress-test forecast. Lab tạo **Metrics dashboard + Forecast v0.2 + Risk-trigger note** cho M-U10; Assignment 05 dùng change request khác nên Lab không cung cấp lời giải Assignment.

## Prerequisites, environment và starter assets

- Hoàn thành U09 và đọc Material/CASE-U10-01.
- Mở [project brief](../../starter/NovaShop_Project_Brief.md), [synthetic dataset](../../starter/NovaShop_Synthetic_Data.csv) và [artifact templates](../../starter/Artifact_Templates.md).
- Dùng spreadsheet CSV UTF-8 hoặc tính tay; không cần code, service hay credential.
- Chỉ dùng rows Sprint 2 cho flow và `RISK-01`; remaining scope của Lab là **14 PBI đã refined**, khác Material.

## 📋 Lab outline và Definition of Done

- Quy ước cycle time: `finish_day − start_day`; chỉ `state=done` vào cycle-time/throughput set.
- PBI đang mở dùng WIP/work item age, không giả finish date.
- Giữ DoD; không xóa outlier PBI-203.
- Ba scenario phải có assumption, risk, limitation và update trigger.
- Done khi CP-U10-01 và CP-U10-02 có evidence, reviewer tái lập được kết quả và không có claim guarantee.

## CP-U10-01 — Tái tạo MEX với dữ liệu Sprint 2

**Mapping:** LO10.1, LO10.2 · `material_example_refs: MEX-U10-01` · guidance đầy đủ

### Microsteps

1. **Why:** Khóa measurement contract trước khi tính để tránh trộn item Done và item đang mở. **Action:** tạo header gồm window `Sprint 2`, start/finish rule, unit `elapsed day`, inclusion `state=done`, measurement day `10`. **Explanation:** cùng tên cycle time nhưng rule khác sẽ không so sánh được.
2. **Why:** Flow evidence phải tái lập được. **Action:** lọc PBI-201…PBI-205; tính throughput, từng cycle time, median, WIP và age của item mở tại ngày 10. **Explanation:** PBI-205 không có `finish_day`, nên nằm trong WIP/age chứ không nằm trong cycle-time set.
3. **Why:** Forecast cần scope và scenario assumptions. **Action:** dùng remaining scope 14; tạo optimistic/base/conservative từ throughput `5/4/3` items mỗi Sprint và công thức `ceil(scope/throughput)`. **Explanation:** ba mức không phải probability; chúng là điều kiện để kiểm sensitivity.
4. **Why:** Artifact phải hỗ trợ decision. **Action:** thêm limitation `sample nhỏ + item mix khác`, DoD guardrail và trigger `sau Sprint/scope ±10%/throughput <3/risk impact đổi`. **Explanation:** thiếu trigger biến forecast thành snapshot stale.

### Verify

Reviewer tính lại từ raw rows và kiểm không có PBI mở trong cycle-time set; tính lại ba phép chia trần.

### Expected result

- Throughput Sprint 2 là 4 Done items.
- Cycle-time values là `1, 2, 8, 2` ngày; median là `2` ngày, outlier 8 vẫn hiện.
- WIP cuối ngày 10 là 1; PBI-205 age là 5 ngày.
- Với scope 14, scenario 5/4/3 cho lần lượt `3/4/5` Sprint.

### Evidence

Nộp dashboard có raw-row IDs, formula/unit/window, scenario table và reviewer initials; lưu phiên bản `u10-cp01`.

### Troubleshooting

- Median ra 3 hoặc 4: kiểm đã sắp `1,2,2,8` và lấy trung bình hai giá trị giữa.
- WIP bằng 0: kiểm PBI-205 chưa finish.
- Cycle-time set có 5 item: loại item `in_progress`.

### Reset

Không sửa CSV starter. Tạo một worksheet/file làm việc mới, nhập lại chỉ rows Sprint 2 và lưu bản cũ để so sánh.

## CP-U10-02 — Stress-test outlier và payment risk

**Mapping:** LO10.1, LO10.2 · `material_example_refs: MEX-U10-01` · guidance giảm dần

### Microsteps

1. **Why:** Median 2 ngày có thể che outlier 8 ngày. **Action:** ghi hai interpretations cạnh nhau: flow điển hình và tail-risk; chỉ ra decision mỗi interpretation hỗ trợ/không hỗ trợ. **Explanation:** statistic không được tách khỏi distribution và risk cause.
2. **Why:** RISK-01 cần xuất hiện trong forecast. **Action:** giả sử risk kích hoạt làm mất 1 item throughput/Sprint; cập nhật conservative scenario hoặc confidence, nhưng không đổi raw data. **Explanation:** risk là assumption sensitivity, không phải lịch sử đã xảy ra.
3. **Why:** Sponsor muốn một con số duy nhất. **Action:** viết decision note tối đa 150 từ gồm range, base, condition, quality/value guardrail và update trigger. **Explanation:** brevity không cho phép xóa uncertainty.
4. **Why:** Kiểm failure behavior. **Action:** áp change card “scope tăng từ 14 lên 17 PBI” và ghi chính xác trigger nào buộc tính lại; tạo forecast v0.3. **Explanation:** 3/14 = 21,4% >10%, nên forecast v0.2 stale.

### Verify

Peer reviewer che scenario table, đọc raw input/assumptions rồi tái lập range. Reviewer tìm được outlier, open risk, scope change, DoD/value guardrail và version trigger.

### Expected result

Artifact không xóa PBI-203, không gọi median là SLA, không coi risk assumption là fact và đánh dấu v0.2 stale sau scope change. Forecast v0.3 có phép tính mới nhưng vẫn giữ ngôn ngữ có điều kiện.

### Evidence

Impact note `outlier → interpretation`, `risk → scenario/confidence`, `scope change → new version`; decision note và peer-review result `PASS|REVISE`.

### Troubleshooting

- Hai reviewer ra range khác: so definition of scope và throughput assumption trước khi tranh luận con số.
- Decision note có chữ “chắc chắn/cam kết”: đổi thành forecast window + conditions.
- Muốn bỏ outlier: giữ row, ghi special-cause hypothesis và chỉ loại trong một sensitivity view có nhãn.

### Reset

Quay về bản `u10-cp01`, áp từng change card vào bản copy. Không overwrite raw data hoặc evidence của checkpoint 1.

## 🧪 Final validation

| Check | PASS khi | Failure action |
| --- | --- | --- |
| Data contract | Có window/rule/unit/exclusion | Sửa header và tính lại |
| Formula | Reviewer tái lập metric/scenario | Trả về raw-row trace |
| Uncertainty | Có range, limitation, risk, trigger | Đổi memo trước khi publish |
| Quality/value | DoD và re-entry/value guardrail hiện rõ | Không chấp nhận release decision |
| Integrity | Starter không đổi; không PII/secret | Reset từ starter |

Exit condition: cả hai checkpoint và năm check PASS. Lab chưa pilot thật nên thời lượng chỉ là estimate; người dạy ghi actual duration vào verification record, không sửa bằng chứng học viên.

## Deliverables và reuse

- Metrics dashboard Sprint 2.
- Forecast v0.2 và v0.3.
- Outlier/risk/scope impact note.
- Peer-review checklist.

Giữ các artifact để so sánh với Assignment 05 và tích hợp vào Capstone; chỉ reuse cấu trúc/oracle, không copy scenario hoặc quyết định.

## ♻️ Reset, cleanup và khả năng chạy lại

Starter assets là read-only. Mỗi checkpoint dùng bản copy có version; reset bằng cách mở lại CSV/template gốc và tạo worksheet mới, không xóa rộng hay sửa dữ liệu ngoài unit workspace. Lab không tạo cloud resource, service, credential hoặc chi phí; cleanup đạt khi chỉ còn deliverables/evidence đã liệt kê và starter không đổi.

## Provenance và chính sách lời giải

- [Scrum Guide 2020](https://scrumguides.org/scrum-guide.html).
- [Evidence-Based Management Guide 2024](https://www.scrum.org/resources/online-evidence-based-management-guide).
- [Forecasting and Release Planning](https://www.scrum.org/resources/introduction-forecasting-and-release-planning), accessed 2026-08-25.
- `[SUY DIỄN — từ kiến thức đã huấn luyện]` Scope 14/17 và change cards là synthetic.

Learner file chứa hướng dẫn giảm dần và oracle của Lab; không chứa reference solution hoặc expected implementation cho Assignment 05.

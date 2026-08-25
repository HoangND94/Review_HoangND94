# Hands-on Lab LAB-U04-01 — Story mapping và slicing luồng browse-to-checkout

| Thuộc tính | Giá trị |
| --- | --- |
| Hình thức | guided_with_fading |
| Thời lượng | 120 phút |
| Độ khó | medium |
| Xác thực | simulated |
| Validation | artifact_review |

## 🎯 Learning Outcomes được thực hành

- **LO4.1:** tạo Story Map và Product Backlog có traceability.
- **LO4.2:** tạo lát dọc và acceptance examples gồm happy/failure behavior.
- **MEX-U04-01 → CP-U04-01, CP-U04-02:** Lab dùng lại cấu trúc oracle của ví dụ Material nhưng đổi actor, baseline và constraint; không sao chép artifact đã hoàn chỉnh.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

- **MEX-U04-01 → LAB-U04-01/CP-U04-01:** LO4.1, LO4.2; evidence là artifact Lab và bảng `input → decision → PBI → evidence`.
- **MEX-U04-01 → LAB-U04-01/CP-U04-02:** LO4.1, LO4.2; evidence là impact note, artifact trước/sau và self/peer review.

## 🧭 Scenario và project slice

Ở M-U04, Scrum Team nhận **CR-02-LAB**: người mua chưa có tài khoản phải checkout một SKU bằng email synthetic; địa chỉ giao hàng cần `tỉnh/thành`, `quận/huyện`, `phường/xã`, `đường`, nhưng input Lab cố ý thiếu `phường/xã`. Product Goal giữ nguyên. Học viên tạo một Story Map và Product Backlog v1 bản Lab, sau đó sửa lát dọc để failure không sinh đơn và không làm mất giỏ.

Input mới so với Material:

- actor là guest, không có session đăng nhập hay địa chỉ lưu;
- `OBS-01`: 7/10 người mô phỏng bỏ checkout khi bị buộc tạo tài khoản;
- `OBS-02`: 4/12 đơn mô phỏng cần nhập lại địa chỉ;
- email an toàn `guest-04@example.test`, SKU `SK-L04`, payment sandbox `approved`;
- địa chỉ edge case: có tỉnh/quận/đường nhưng thiếu phường/xã.

**Constraints:** không tạo account trong lát Lab; không thu thập ngày sinh, giới tính hay mật khẩu; chỉ dùng dữ liệu synthetic; không sửa Product Goal hoặc starter assets; không giảm DoD.

## 🧰 Prerequisite, environment và starter assets

Hoàn thành U03 và đọc phần MEX-U04-01 trong `material.md`. Dùng ENV-PRO-ARTIFACT: Markdown CommonMark, bảng tính CSV UTF-8 và whiteboard/paper tương đương. Starter assets:

- `starter/NovaShop_Project_Brief.md`
- `starter/NovaShop_Synthetic_Data.csv`
- `starter/Artifact_Templates.md`

Tạo bản làm việc trong `project-artifacts/M-U04/lab/` với ba file: `U04_lab_story-map.md`, `U04_lab_backlog-v1.md`, `U04_lab_evidence.md`. Nếu công cụ không dùng file, dùng ba trang/canvas có cùng tên logic. Không ghi secret, PII hay payment data thật.

## 📋 Lab outline và Definition of Done

Lab đạt khi: CP-U04-01 và CP-U04-02 đều có kết luận PASS cùng evidence; Story Map và Product Backlog dùng ID nhất quán; mọi backbone của lát Lab có user task; mọi PBI trong lát có Goal/journey link, happy và edge/failure oracle; impact note phản ánh change; ba artifact mở được; starter assets không đổi; reset được mô tả và thử bằng một bản sao làm việc.

## Checkpoint 0 — Baseline và safety check

### Numbered microsteps

1. **Why:** bảo vệ nguồn gốc và khả năng chạy lại. **Action:** mở ba starter asset ở chế độ chỉ đọc, tạo ba file làm việc nêu trên và ghi đầu file `authenticity: simulated`, `source: CR-02-LAB`. **Giải thích:** starter asset là baseline; evidence phải tách khỏi quyết định của học viên.
2. **Why:** xác nhận input đúng case. **Action:** trong CSV tìm `OBS-01`, `OBS-02`; trong project brief tìm `FR-03`, CR-02 và Definition of Done. Ghi các ID, không chép thêm dữ liệu ngoài các hàng đó. **Giải thích:** ID cho phép reviewer lần lại claim mà không dùng PII.
3. **Why:** tránh vô tình dùng artifact Material như đáp án. **Action:** ghi bảng “Khác MEX-U04-01” gồm actor=guest, address=new, change=missing ward, account creation=out of scope. **Giải thích:** đây là bằng chứng practice variation schema 2.1.

### Verify

Reviewer kiểm ba file tồn tại/mở được; evidence file có bốn khác biệt; starter assets vẫn giữ nguyên; chỉ có email miền `.test` và status sandbox.

### Expected result

Baseline có đủ `OBS-01`, `OBS-02`, `FR-03`, CR-02, DoD; không có artifact quyết định sẵn và không có dữ liệu thật.

### Evidence

Lưu mục `CP0-baseline` trong `U04_lab_evidence.md`: danh sách source ID, bảng khác biệt và kết luận `PASS` hoặc `REVISE`.

### Troubleshooting

Nếu không thấy hàng CSV, kiểm encoding UTF-8 và header `record_type`; nếu template bị sửa, đóng không lưu rồi tạo bản làm việc mới; nếu thấy email/tên thật, thay bằng `guest-04@example.test` và ghi sự cố data hygiene.

### Reset/rollback

Đổi tên ba file làm việc thành hậu tố `.discarded`, tạo lại bản mới từ template và chạy lại Verify. Reset thành công khi source ID còn nguyên và ba file mới không chứa quyết định cũ.

## Checkpoint 1 — CP-U04-01: Tái tạo Story Map cho guest checkout

**material_example_refs:** MEX-U04-01 · **LO:** LO4.1, LO4.2

### Numbered microsteps

1. **Why:** bắt đầu từ hành trình thay vì component. **Action:** trong `U04_lab_story-map.md`, ghi actor, outcome “đặt được đơn không cần tạo account”, Product Goal ID và journey từ tìm sản phẩm đến nhận kết quả. Tự đặt 4–7 backbone bằng động từ của guest. **Giải thích:** giới hạn số backbone buộc nhóm giữ mức ý định, không sa vào từng click.
2. **Why:** bảo toàn coverage. **Action:** đặt ít nhất một user task dưới mỗi backbone; gắn `OBS-01` cho bước account friction và `OBS-02` cho bước địa chỉ. **Giải thích:** evidence link chứng minh vì sao task tồn tại.
3. **Why:** tạo lát dọc mới. **Action:** vẽ một hàng `LAB-SLICE-1` xuyên toàn backbone, chỉ dùng một SKU, một shipping option và payment `approved`; account creation nằm ngoài lát. **Giải thích:** lát nhỏ theo data/rule boundary nhưng vẫn đi đến order outcome.
4. **Why:** chuyển view discovery thành nguồn work. **Action:** trong `U04_lab_backlog-v1.md`, tạo PBI cho các outcome của lát; mỗi PBI ghi ID, actor, outcome, Goal/journey link, dependency/risk, open question và evidence dự kiến. Không dùng các ID `PBI-U04-401..403` của Material. **Giải thích:** ID mới chứng minh recreate, không copy.
5. **Why:** tạo oracle. **Action:** với từng PBI trong lát, viết ít nhất một acceptance example có Given/When/Then và result quan sát được. Ở checkpoint này dùng happy input đầy đủ, chưa giải missing-ward failure.

### Verify

Thực hiện artifact review `CP-U04-01`:

1. backbone theo actor/outcome, không theo UI/API/database;
2. mọi backbone có task trong `LAB-SLICE-1`;
3. mọi PBI có Goal link, journey link, dependency/risk và evidence;
4. happy example của từng PBI có state, event, result;
5. lát kết thúc bằng kết quả order sandbox có thể quan sát và không yêu cầu account.

### Expected result

Artifact đủ trường, khác MEX-U04-01, không có bước hành trình mồ côi và reviewer lần được `input → decision → PBI → evidence`. Nếu thiếu một link hoặc lát dừng trước outcome, kết luận là REVISE.

### Evidence

Lưu Story Map và Backlog ở trạng thái `v1-cp1`; trong `U04_lab_evidence.md` ghi bảng `PBI | input ID | decision | oracle`, kết quả năm check và tên peer reviewer.

### Troubleshooting

- Nếu backbone là component, đọc từng tên theo mẫu “Guest có thể …”; tên không hoàn chỉnh thì viết lại.
- Nếu có task không vào lát, quyết định rõ “later” hoặc đưa vào slice; không để trạng thái mơ hồ.
- Nếu criteria mô tả control/API, thay phần `Then` bằng kết quả người dùng hoặc trạng thái business quan sát được.

### Reset/rollback

Lưu bản `v1-cp1` đã PASS. Khi cần làm lại checkpoint, sao chép bản CP0 thành file mới; không ghi đè evidence PASS. Xác nhận rollback bằng cách đối chiếu file mới chưa có PBI của CP1.

## Checkpoint 2 — CP-U04-02: Debug lát dọc khi địa chỉ không hợp lệ

**material_example_refs:** MEX-U04-01 · **LO:** LO4.1, LO4.2 · **practice variation:** input thiếu `phường/xã`, khác failure payment trong Material.

### Numbered microsteps

1. **Why:** inspect tác động trước khi sửa. **Action:** thêm change card `ADDR-L04`: tỉnh=`Đà Nẵng`, quận=`Hải Châu`, phường/xã=`missing`, đường=`12 Test`; lập impact table gồm backbone, PBI, criteria và evidence bị ảnh hưởng. **Giải thích:** change có thể tác động nhiều artifact; bảng ngăn cập nhật cục bộ.
2. **Why:** bảo vệ verticality. **Action:** quyết định PBI nào sở hữu outcome “biết địa chỉ chưa hợp lệ mà không mất giỏ”; không tạo PBI ngang “thêm validator”. Ghi rationale và một option không chọn. **Giải thích:** technical work thuộc how, không thay actor/outcome.
3. **Why:** tạo failure oracle. **Action:** bổ sung acceptance example với state thiếu phường/xã, event xác nhận checkout và result phải quan sát được. Criteria phải phân biệt rõ order/no-order, dữ liệu nào được giữ và feedback nào xuất hiện; tự chọn câu chữ dựa trên contract.
4. **Why:** giữ traceability. **Action:** cập nhật Story Map, Backlog và impact table bằng cùng PBI ID; đánh dấu version `v2-cp2`. **Giải thích:** map và backlog là hai view của cùng quyết định.
5. **Why:** kiểm scope/data. **Action:** quét artifact để chắc chắn không thêm DOB, giới tính, password, card data; ghi trade-off của việc chưa hỗ trợ address autocomplete.

### Verify

Artifact review `CP-U04-02` PASS khi: change card có input cụ thể; impact table nêu mọi phần bị ảnh hưởng; failure criterion có Given/When/Then quan sát được; không sinh order khi address invalid; cart và input cần sửa không bị mô tả là mất; cùng PBI ID xuất hiện trên map/backlog/evidence; data-minimization constraint không bị vi phạm.

### Expected result

Change request được xử lý nhất quán; trade-off và boundary rõ. Happy path ở CP1 vẫn hợp lệ, còn failure path mới tạo oracle riêng. Không có task kỹ thuật được nâng thành PBI value.

### Evidence

Lưu diff tóm tắt `v1-cp1 → v2-cp2`, impact table, criteria trước/sau, checklist CP-U04-02 có kết luận và peer-review note.

### Troubleshooting

- Nếu criteria không nói có sinh order hay không, thêm outcome business rõ; không thêm chi tiết implementation.
- Nếu update chỉ có trong backlog, tìm PBI ID trên story map và đồng bộ view.
- Nếu nhóm bất đồng về dữ liệu cần giữ, đối chiếu `FR-03` và constraint tối thiểu hóa dữ liệu; ghi hai option rồi chọn bằng oracle.

### Reset/rollback

Để thử lại edge case, sao chép `v1-cp1` sang một nhánh làm việc mới và chỉ áp dụng `ADDR-L04`. Xác nhận reset khi happy artifact CP1 còn nguyên, file mới chưa chứa change card, và starter assets chưa đổi.

## 🧪 Final validation

Từ một bản sao sạch của CP0, reviewer kiểm theo thứ tự CP-U04-01 rồi CP-U04-02. Exit condition là cả hai checkpoint PASS, đủ evidence, không có PBI/journey link mồ côi, không có dữ liệu thật và starter assets không đổi. Nếu một check REVISE, sửa đúng artifact/ID bị chỉ ra rồi chạy lại toàn bộ check liên quan; không tự nâng kết luận lên PASS nếu chưa review.

## 📦 Deliverables và evidence

- **Artifact Lab:** `U04_lab_story-map.md` và `U04_lab_backlog-v1.md` ở trạng thái sau CP-U04-02.
- **Traceability table:** bảng `input → decision → PBI → evidence` trong `U04_lab_evidence.md`.
- **Evidence checklist:** kết luận CP-U04-01/02, peer-review note và reset check.
- `U04_lab_story-map.md`: bản CP1 và bản sau CP2.
- `U04_lab_backlog-v1.md`: PBI, trace, happy/failure oracle.
- `U04_lab_evidence.md`: baseline, variation table, traceability table, impact note, review result.
- Evidence bắt buộc: artifact trước/sau, CP-U04-01 review, CP-U04-02 review và peer-review note.

Giữ các artifact để tham khảo khi làm **ASM-U04** và để Capstone kiểm tra tiến trình học tập; không nộp chúng như lời giải Assignment. Output đánh giá chính thức của ASM-U04 phải được tạo độc lập theo change request của đề.

## ♻️ Reset, cleanup và khả năng chạy lại

Không có service, thiết bị hay credential cần thu hồi. Chỉ làm việc trong `project-artifacts/M-U04/lab/`. Để cleanup, giữ bản evidence cuối, chuyển bản thử lỗi sang thư mục `discarded/` trong cùng workspace, rồi mở lại ba starter asset để xác nhận không đổi. Không xóa đệ quy hoặc sửa file starter.

## 🔐 Chính sách lời giải

Learner Lab chỉ có hướng dẫn giảm dần và oracle; không chứa reference solution của Assignment. Output Lab không được nộp thay ASM-U04.

## 📚 Provenance

- **SRC-SG20** — Scrum Guide, November 2020, ScrumGuides.org, accessed 2026-08-25, CC BY-SA 4.0, adapt.
- **SRC-USER-STORIES** — Agile Alliance User Stories, living snapshot/accessed 2026-08-25, website terms, reference.
- **SRC-STORY-MAP** — Jeff Patton/O'Reilly, September 2014, accessed 2026-08-25, copyright; bibliographic reference/paraphrase only.
- **SRC-GHERKIN** — Cucumber Gherkin Reference, living snapshot/accessed 2026-08-25, documentation terms, reference.
- Project brief và synthetic CSV chỉ là project input/fixture do `plan.project` quản lý, không phải source ref hoặc nguồn provenance bổ sung của U04. Toàn bộ actor, email, địa chỉ, order và payment status trong Lab là simulated; phần kiến thức chỉ dùng bốn source refs đã liệt kê.
- Không dùng nguồn bổ sung. CR-02-LAB là biến thể đào tạo của CR-02, không đại diện cho yêu cầu khách hàng thật.

---
<!-- QUALITY GATE: MEX-U04-01 resolve ở CP-U04-01/02; mỗi checkpoint có microsteps, Verify, Expected, Evidence, Troubleshooting, Reset; có changed input; không lộ bài giải Assignment. -->

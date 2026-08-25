# Unit U04: Story mapping, user story và acceptance criteria — Học liệu cốt lõi

> **Khóa học:** Agile–Scrum thực hành qua dự án thương mại điện tử NovaShop · **Thuộc:** Product Discovery và Backlog · **Mức xác thực:** simulated

## 🎯 Learning Outcomes

- **LO4.1** [create] — Chuyển customer journey thành story map và Product Backlog có truy vết tới Product Goal. Bằng chứng: Story Map và Product Backlog v1 không có bước hành trình mồ côi.
- **LO4.2** [create] — Chia MVP thành lát dọc và viết acceptance criteria quan sát được cho toàn bộ PBI được chọn. Bằng chứng: MVP slice và acceptance criteria gồm happy path lẫn edge case.

## 🧭 Ngữ cảnh dự án và increment

NovaShop là MVP thương mại điện tử B2C mô phỏng. Học viên làm việc như một Scrum Team và luân chuyển góc nhìn Product Owner, Developers cùng người hỗ trợ workshop. Baseline của **M-U04** là Product Goal, stakeholder evidence và customer journey từ U03. Unit này biến evidence discovery thành **Story Map** và **Product Backlog v1**; hai artifact sẽ đi qua refinement ở U05, trở thành baseline cho Assignment ASM-U06 và được kiểm tra tích hợp ở REV-01.

Giá trị cần tạo là một lát browse-to-checkout có thể kiểm chứng sớm, thay vì một danh sách task theo tầng kỹ thuật. Increment đạt khi backbone phủ hành trình, PBI truy vết được tới Product Goal, lát MVP đi từ nhu cầu đến kết quả người dùng, và toàn bộ PBI được chọn có oracle quan sát được.

## 📚 Nguồn đầu vào đã map

- **SRC-SG20** — [The Scrum Guide: The Definitive Guide to Scrum](https://scrumguides.org/scrum-guide.html) (publisher: Ken Schwaber, Jeff Sutherland / ScrumGuides.org; version: November 2020; accessed: 2026-08-25; license: CC BY-SA 4.0; allowed use: adapt).
- **SRC-USER-STORIES** — [User Stories](https://agilealliance.org/glossary/user-stories/) (publisher: Agile Alliance; version: living glossary snapshot 2026-08-25; accessed: 2026-08-25; license: Agile Alliance website terms; allowed use: reference).
- **SRC-STORY-MAP** — [User Story Mapping](https://www.oreilly.com/library/view/user-story-mapping/9781491904893/) (publisher: Jeff Patton / O'Reilly Media; version: September 2014; accessed: 2026-08-25; license: copyright, bibliographic reference and paraphrase only; allowed use: reference).
- **SRC-GHERKIN** — [Gherkin Reference](https://cucumber.io/docs/gherkin/reference/) (publisher: Cucumber; version: living documentation snapshot 2026-08-25; accessed: 2026-08-25; license: Cucumber documentation terms; allowed use: reference).

## 1. Kiến thức tiên quyết và môi trường

Học viên cần hoàn thành U03, mở được `starter/NovaShop_Project_Brief.md`, `starter/NovaShop_Synthetic_Data.csv` và `starter/Artifact_Templates.md`, đồng thời biết ghi một quyết định kèm evidence. Môi trường **ENV-PRO-ARTIFACT** chỉ cần trình soạn Markdown tương thích CommonMark, bảng tính đọc CSV UTF-8 và whiteboard hoặc giấy tương đương; không có runtime, dịch vụ trả phí hay credential.

**Preflight PASS:** ba starter asset mở được; CSV có các hàng `OBS-01` đến `OBS-04`; template có mục “Story map và Product Backlog item”; file làm việc lưu được mà không sửa starter asset. Nếu một điều kiện sai, dừng và lấy lại bản starter trước khi tạo artifact.

**Phương thức xác minh:** artifact review. Mode là `professional_artifact` vì LO yêu cầu quyết định sản phẩm và artifact planning, không yêu cầu viết hoặc chạy code.

## 2. Định vị trong lộ trình

```text
Product Goal + customer journey (U03)
        ↓ chuyển evidence thành lựa chọn phạm vi
Story Map + Product Backlog v1 (U04)
        ↓ thêm detail, estimate, ordering
Sizing record + Product Backlog v2 (U05)
        ↓ chọn forecast theo Sprint Goal
Sprint Goal + Sprint Backlog (U06)
```

Story map giữ góc nhìn hành trình để đội không tối ưu một component riêng lẻ. Product Backlog biến các lựa chọn đó thành các hạng mục có thể tiếp tục nổi lên và được sắp xếp. U04 chưa ước lượng hoặc chốt Sprint scope; đó là quyết định của U05 và U06.

## 3. Nội dung lý thuyết cốt lõi

**📋 Checklist bắt buộc phủ — giữ nguyên văn và đúng thứ tự Content Outlines:**

- [x] Story map và Product Backlog theo hành trình giá trị
- [x] Vertical slicing và acceptance criteria quan sát được

#### OUT-U04-01 — Story map và Product Backlog theo hành trình giá trị

**Mapping:** OUT-U04-01 · LO4.1 · M-U04, tạo Story Map và Product Backlog v1 từ artifact U03.

##### Định nghĩa và ranh giới

Story map là một cách sắp xếp work theo hành trình người dùng: trục ngang mô tả các hoạt động/backbone theo trình tự đạt mục tiêu, các user task nằm dưới từng hoạt động, và các lát phát hành cắt qua nhiều hoạt động. Nó là kỹ thuật bổ trợ, không phải artifact bắt buộc của Scrum. **Product Backlog** mới là danh sách nổi lên, có thứ tự, là nguồn work duy nhất do Scrum Team thực hiện để cải thiện Product; Product Goal là commitment của nó.

Story map không đồng nghĩa với sơ đồ màn hình, process map nội bộ hay danh sách component. User story là cách diễn đạt nhu cầu để khơi gợi conversation; nó không thay thế Product Backlog item (PBI) và không bắt buộc mọi PBI phải có đúng một cú pháp.

##### Vấn đề, vai trò và quyết định

Customer journey thường rộng, còn backlog phẳng dễ làm mất thứ tự trải nghiệm. Product Owner dùng story map để làm rõ “ai nhận giá trị nào trước”; Developers nêu dependency, risk và cách tạo evidence; stakeholder kiểm tra rằng phạm vi phản ánh nhu cầu. Quyết định phải đưa ra là: backbone nào thật sự thuộc Product Goal, task nào có evidence, PBI nào tạo outcome, và mối liên kết nào phải giữ khi backlog thay đổi.

##### Cơ chế và mental model

Luồng chuyển đổi có thể kiểm tra là:

1. **Evidence → journey step:** mỗi bước có actor, mục tiêu và evidence ID.
2. **Journey step → backbone/user task:** nhóm theo ý định người dùng, không theo kiến trúc.
3. **User task → PBI:** PBI ghi actor, outcome, Goal link, open question, dependency/risk và oracle.
4. **PBI → Product Backlog:** Product Owner sắp xếp; refinement tiếp tục bổ sung detail, size và order.
5. **Traceability audit:** mỗi backbone có ít nhất một PBI; mỗi PBI có Goal link và journey link; không có PBI “mồ côi”.

Khi evidence đổi, chỉ các link downstream bị ảnh hưởng được cập nhật; không cần vẽ lại mọi thứ. Đây là lý do dùng ID ổn định cho Goal, journey step và PBI.

##### Khi dùng, khi không dùng và trade-off

Dùng story map khi nhiều vai trò cần một bức tranh chung về end-to-end value, khi backlog phẳng che mất bước hành trình, hoặc khi cần thảo luận lát MVP. Không cần dùng cho thay đổi rất nhỏ đã có flow và oracle rõ; một ordered backlog cùng traceability có thể đủ. Story map tạo chi phí duy trì: nếu đội không cập nhật cùng Product Backlog, hai nguồn sẽ mâu thuẫn. Vì vậy Product Backlog là nguồn quản trị work; story map là view hỗ trợ discovery và slicing.

##### Ví dụ thực tế riêng và oracle

- **Context:** người mua đã đăng nhập muốn tìm một sản phẩm còn hàng rồi thêm vào giỏ.
- **Input:** Product Goal NovaShop; `FR-01`, `FR-02`; journey `J-SEARCH → J-DECIDE → J-CART`; constraint chỉ dùng catalog và tồn kho sandbox.
- **Decision:** backbone là “Tìm → Đánh giá → Giữ lựa chọn”, không phải “frontend → API → database”. PBI `PBI-U04-A` có outcome “thấy đúng sản phẩm còn hàng theo từ khóa”, `PBI-U04-B` có outcome “giữ được lựa chọn và số lượng trong giỏ”.
- **Artifact:** hai dòng story map và hai PBI có Goal/journey link.
- **Expected:** cả ba journey step có user task; hai PBI đều có actor, outcome và oracle; không có task kỹ thuật độc lập giả làm value.
- **Oracle:** reviewer lần ngược được `PBI → journey step → Product Goal`; nếu bỏ một backbone, reviewer chỉ ra đúng khoảng trống hành trình.

##### Best practices

- **Rule:** đặt tên backbone bằng hành động/mục đích của người dùng. **Rationale:** ngôn ngữ value giữ thảo luận ở outcome. **Positive:** “Xác nhận đơn”. **Negative:** “Xây bảng Orders”; hậu quả là một tầng kỹ thuật có thể hoàn thành nhưng người mua chưa nhận kết quả.
- **Rule:** mọi PBI có Goal link, journey link và acceptance evidence dự kiến. **Rationale:** traceability cho phép kiểm tra lý do tồn tại và impact của thay đổi. **Positive:** `PBI-U04-A → J-SEARCH → PG-NS-01`. **Negative:** “Làm search API” không có actor/outcome; đội không biết nên giữ hay bỏ khi scope giảm.
- **Rule:** xem story map là view hỗ trợ, không phải backlog thứ hai. **Rationale:** hai nguồn order cạnh tranh làm mất minh bạch. **Positive:** thay đổi PBI được phản ánh bằng cùng ID. **Negative:** thẻ trên map và backlog dùng ID khác; audit phát hiện nội dung lệch nhau.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** backbone là tên component. **Nguyên nhân:** tách việc theo chuyên môn. **Chẩn đoán:** không hoàn thành được câu “người dùng có thể…”. **Sửa:** dựng lại từ actor/outcome rồi gắn technical work vào PBI. **Phòng tránh:** review backbone với stakeholder nghiệp vụ.
- **Dấu hiệu:** có bước journey không có PBI hoặc PBI không có journey link. **Nguyên nhân:** copy wish list vào backlog. **Chẩn đoán:** chạy bảng đối chiếu hai chiều. **Sửa:** thêm link hợp lệ hoặc loại PBI ngoài Goal. **Phòng tránh:** dùng ID ổn định và traceability audit ở mỗi refinement.

#### OUT-U04-02 — Vertical slicing và acceptance criteria quan sát được

**Mapping:** OUT-U04-02 · LO4.2 · M-U04, chọn lát MVP và tạo quality oracle cho từng PBI được chọn.

##### Định nghĩa và ranh giới

**Vertical slice** là một phần nhỏ đi qua các khả năng cần thiết để tạo kết quả có thể quan sát cho actor, thay vì hoàn tất riêng UI, service hoặc data layer. Một lát MVP là tập nhỏ nhất đủ để kiểm tra một giả thuyết giá trị end-to-end; “MVP” không có nghĩa là hạ Definition of Done.

**Acceptance criteria** là các điều kiện cụ thể để xác nhận PBI đáp ứng nhu cầu. Given/When/Then là một cách diễn đạt acceptance example: `Given` nêu trạng thái liên quan, `When` nêu sự kiện/hành động đơn nhất, `Then` nêu outcome quan sát được. Cú pháp không tự bảo đảm chất lượng; oracle phải kiểm được và không mô tả implementation.

##### Vấn đề, vai trò và quyết định

Horizontal slicing tạo cảm giác tiến độ nhưng trì hoãn feedback. Product Owner và Developers cần quyết định outcome tối thiểu nào đáng kiểm chứng, dependency nào bắt buộc, edge/failure nào ảnh hưởng giá trị, và evidence nào chứng minh PBI đạt. QA/BA hỗ trợ làm rõ oracle, nhưng toàn Scrum Team chịu trách nhiệm tạo Increment usable theo DoD.

##### Cơ chế và mental model

Kiểm tra một slice qua năm câu hỏi: có **actor** rõ không; actor đạt **outcome** gì; lát đi qua đủ capability để quan sát outcome chưa; phạm vi nhỏ đến mức có thể hoàn thành theo **DoD** chưa; happy và failure behavior có **oracle** chưa. Nếu câu trả lời phụ thuộc vào một “phase sau” để người dùng nhận giá trị, đó thường là horizontal slice.

Acceptance criteria chuyển conversation thành testable boundary. Happy path chứng minh intended outcome; edge/failure path chứng minh hệ thống từ chối hoặc phục hồi theo cách quan sát được. Criteria không nên khóa đội vào tên bảng, endpoint hay UI control trừ khi đó là constraint đã được phê duyệt.

##### Khi dùng, khi không dùng và trade-off

Dùng vertical slicing khi PBI quá lớn, khi work đang chia theo tầng, hoặc khi cần feedback sớm. Không ép mỗi task nội bộ thành một user story; task kỹ thuật có thể nằm trong plan “how” của Sprint Backlog. Có những enabler/risk-reduction item không tạo giá trị người dùng trực tiếp; chúng vẫn cần outcome học tập hoặc risk oracle và phải được Product Owner sắp xếp minh bạch.

##### Ví dụ thực tế riêng và oracle

- **Context:** người mua nhập mã giảm giá không hợp lệ trong giỏ.
- **Input:** giỏ có một sản phẩm 300.000đ; mã `EXPIRED-TEST`; constraint không gọi payment sandbox.
- **Decision:** một lát dọc hiển thị tổng hiện tại, nhận mã, từ chối mã hết hạn và giữ nguyên giỏ. Không chia thành “tạo ô nhập mã”, “tạo API promotion”, “tạo bảng mã”.
- **Artifact:** PBI có acceptance examples: happy path với mã sandbox hợp lệ và failure path với mã hết hạn.
- **Expected:** mã hết hạn không làm thay đổi tổng; thông báo có thể quan sát; sản phẩm/số lượng vẫn còn.
- **Oracle:** so sánh tổng và nội dung giỏ trước/sau; kiểm tra có thông báo từ chối. Không cần biết implementation nội bộ.

##### Best practices

- **Rule:** slice theo outcome và giữ DoD nguyên vẹn. **Rationale:** feedback chỉ đáng tin khi kết quả usable. **Positive:** đặt một đơn sandbox với một phương thức thanh toán. **Negative:** “xong UI checkout” nhưng chưa validation/evidence; hậu quả là không thể inspect như Increment.
- **Rule:** mỗi PBI được chọn có ít nhất một happy và một relevant edge/failure criterion. **Rationale:** biên lỗi thường quyết định khả năng sử dụng trong thương mại điện tử. **Positive:** payment bị từ chối giữ input và không sinh mã đơn. **Negative:** chỉ ghi “checkout hoạt động”; reviewer không có oracle.
- **Rule:** criteria mô tả hành vi, không mô tả thiết kế. **Rationale:** giữ không gian cho Developers tự quản. **Positive:** “Then tổng tiền không đổi”. **Negative:** “Then controller gọi method X”; criteria giòn và không chứng minh outcome.
- **Rule:** data fields trong slice chỉ phục vụ actor/outcome và data policy của project. **Rationale:** boundary dữ liệu rõ ngăn scope creep và vi phạm constraint no-PII/no-real-payment-data. **Positive:** guest slice chỉ nêu email synthetic cùng trường địa chỉ cần cho giao hàng. **Negative:** thu thêm ngày sinh, giới tính, password hoặc card data dù outcome không cần; hậu quả là artifact vi phạm project constraint và phải REVISE.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** mọi slice mang tên UI/API/DB. **Nguyên nhân:** tối ưu handoff chuyên môn. **Chẩn đoán:** không slice nào tự tạo outcome. **Sửa:** chọn một scenario nhỏ và bao trọn các capability cần thiết. **Phòng tránh:** review bằng năm câu hỏi actor–outcome–capability–DoD–oracle.
- **Dấu hiệu:** criteria như “nhanh”, “đúng”, “thân thiện”. **Nguyên nhân:** nhầm mong muốn với oracle. **Chẩn đoán:** hai reviewer có thể kết luận khác nhau. **Sửa:** thêm state, event và result quan sát được. **Phòng tránh:** chạy thử criteria trên một happy và một failure example trước refinement.

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### Story map browse-to-checkout với lát MVP dọc

**Stable ID:** MEX-U04-01 · **Artifact type:** Story Map, Product Backlog và acceptance examples · **Mapping:** LO4.1, LO4.2; OUT-U04-01, OUT-U04-02. Ví dụ này dùng người mua **đã đăng nhập** và địa chỉ đã lưu; guest checkout được dành cho Lab/Assignment dưới input khác.

**Verification method từ plan:** đối chiếu từng trường của artifact với checklist, input source và oracle được nêu trong Material.

### Mapping Material worked example → Hands-on Lab tương ứng

- **MEX-U04-01 → LAB-U04-01/CP-U04-01:** tái tạo map/backlog bằng actor guest và input mới; LO4.1, LO4.2.
- **MEX-U04-01 → LAB-U04-01/CP-U04-02:** mở rộng bằng failure path địa chỉ không hợp lệ; LO4.1, LO4.2.

**Input/baseline:** Product Goal `PG-NS-01`: tăng tỷ lệ đơn online hợp lệ và giảm nhập lại; `FR-01`–`FR-03`; journey đã xác thực bằng dữ liệu synthetic; payment/shipping chỉ là sandbox. Constraint: một lát đầu không có promotion, tài khoản mới hay theo dõi đơn.

#### Artifact A — Story Map

| Backbone activity | Tìm sản phẩm | Đánh giá lựa chọn | Tạo giỏ | Cung cấp giao hàng | Thanh toán sandbox | Nhận xác nhận |
| --- | --- | --- | --- | --- | --- | --- |
| User task | Tìm theo từ khóa | Xem giá và trạng thái còn hàng | Thêm một SKU, sửa số lượng | Chọn địa chỉ đã lưu | Chấp nhận hoặc từ chối payment test | Nhận mã đơn hoặc thông báo thất bại |
| **MVP slice S1** | Tìm đúng một SKU còn hàng | Chọn SKU | Giữ đúng SKU/số lượng | Dùng địa chỉ hợp lệ đã lưu | Xử lý trạng thái `approved`/`declined` | Chỉ sinh mã khi approved; giữ input khi declined |
| Later slice | Bộ lọc nâng cao | So sánh sản phẩm | Promotion | Địa chỉ mới | Thêm phương thức | Theo dõi trạng thái |

#### Artifact B — Product Backlog v1, excerpt của S1

| PBI | Actor/outcome và trace | Acceptance examples quan sát được | Dependency/risk/evidence |
| --- | --- | --- | --- |
| PBI-U04-401 | Người mua tìm được SKU còn hàng phù hợp; `PG-NS-01 → J-FIND` | **Happy:** Given catalog có `SK-01` còn hàng, When tìm “sữa rửa mặt”, Then `SK-01` xuất hiện kèm giá/trạng thái. **Edge:** Given không có kết quả, Then danh sách rỗng và thông báo đổi từ khóa xuất hiện. | Catalog sandbox; evidence là ảnh/result list với query và trạng thái |
| PBI-U04-402 | Người mua giữ được lựa chọn trong giỏ; `PG-NS-01 → J-CART` | **Happy:** Given `SK-01` còn hàng, When thêm số lượng 1, Then giỏ có đúng SKU, số lượng và tổng. **Edge:** Given tồn kho 0, When thêm, Then giỏ không đổi và có thông báo hết hàng. | Phụ thuộc PBI-401 về SKU; evidence là before/after cart state |
| PBI-U04-403 | Người mua đã đăng nhập đặt đơn bằng địa chỉ lưu; `PG-NS-01 → J-CHECKOUT` | **Happy:** Given giỏ hợp lệ, địa chỉ lưu hợp lệ và payment `approved`, When xác nhận, Then sinh một mã đơn sandbox và trạng thái tiếp nhận. **Failure:** Given payment `declined`, When xác nhận, Then không sinh mã đơn, giỏ/địa chỉ còn nguyên và có correlation evidence giả lập. | Phụ thuộc PBI-402; risk payment sandbox; evidence là order/no-order state và retained input |

**Giải thích quyết định:** backbone theo ý định người mua nên trace về journey được. S1 cắt qua catalog, cart, address, payment và confirmation để tạo một outcome end-to-end nhỏ. Promotion và địa chỉ mới được hoãn vì không cần để kiểm chứng đặt đơn với người dùng đã đăng nhập. Acceptance examples mô tả outcome; không áp đặt màn hình, API hoặc cấu trúc dữ liệu.

**Happy behavior:** ba PBI nối thành một hành trình tìm–giữ–đặt đơn; payment approved sinh đúng một mã đơn. **Edge/failure behavior:** không có kết quả, hết hàng hoặc payment declined tạo trạng thái quan sát được; failure không làm mất input và không sinh mã đơn.

**Verification/oracle — PASS khi tất cả đúng:**

1. Sáu backbone đều có task trong S1; không có khoảng trống từ tìm đến xác nhận.
2. Mỗi PBI có actor/outcome, `PG-NS-01`, journey ID, dependency/risk và evidence.
3. S1 không chứa promotion, account creation hoặc order tracking ngoài boundary.
4. Cả ba PBI có happy cùng edge/failure criterion; mỗi `Then` quan sát được độc lập với implementation.
5. Không PBI nào chỉ là UI/API/database task; DoD không bị giảm.

Kết quả mong đợi là **Backbone phủ hành trình; lát MVP tạo outcome đầu-cuối; acceptance criteria có observable result**. Reviewer ghi `PASS` hoặc `REVISE` kèm số mục sai và PBI liên quan.

**Material ↔ Lab:** MEX-U04-01 được tái tạo bằng actor/input mới tại [LAB-U04-01/CP-U04-01](HandsOnLab_04.md#checkpoint-1--cp-u04-01-tái-tạo-story-map-cho-guest-checkout) và được mở rộng bằng failure path địa chỉ tại [LAB-U04-01/CP-U04-02](HandsOnLab_04.md#checkpoint-2--cp-u04-02-debug-lát-dọc-khi-địa-chỉ-không-hợp-lệ). Lab không sao chép S1: actor đổi thành guest, không có địa chỉ lưu và có constraint dữ liệu tối thiểu.

## 5. Lỗi thường gặp và quy tắc chẩn đoán

| Dấu hiệu | Nguyên nhân có thể | Bằng chứng chẩn đoán | Cách sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| Map đầy thẻ nhưng không có Goal link | Bắt đầu từ solution wish list | Cột trace trống | Loại hoặc gắn lại PBI từ evidence/journey | Bắt buộc Goal/journey ID khi tạo PBI |
| “MVP” chỉ có UI hoặc API | Slice theo tầng | Không có actor hoàn thành outcome | Dựng scenario nhỏ xuyên capability | Review actor–outcome–DoD–oracle |
| Criteria chỉ có happy path | Conversation bỏ qua failure | Không có expected state khi từ chối | Thêm edge/failure relevant | Example mapping trước refinement |
| Story map và backlog lệch nhau | Hai bộ ID/owner | Cùng intent nhưng ID khác | Chọn Product Backlog làm nguồn, đồng bộ view | Audit hai chiều sau thay đổi |
| PBI quá lớn | Nhiều actor/outcome/event trong một item | Không thể viết một `When` rõ | Tách theo scenario/rule/data boundary | Giới hạn một outcome chính cho một PBI |

## 6. Từ điển thuật ngữ và mô hình tư duy

- **Backbone:** chuỗi hoạt động cấp cao theo mục tiêu người dùng.
- **User task:** hành động cụ thể dưới một backbone activity.
- **Product Backlog:** danh sách nổi lên, có thứ tự về những gì cần để cải thiện Product.
- **PBI:** một hạng mục trong Product Backlog; user story là một cách mô tả, không phải loại bắt buộc.
- **Vertical slice:** lát nhỏ tạo outcome quan sát được xuyên các capability cần thiết.
- **MVP slice:** lát nhỏ đủ để kiểm tra giả thuyết giá trị, vẫn phải đáp ứng DoD.
- **Acceptance criterion/example:** oracle hành vi để quyết định PBI có đáp ứng nhu cầu hay không.
- **Traceability:** khả năng lần từ Product Goal qua journey/PBI đến evidence và ngược lại.

Mental model ngắn: **evidence chọn journey → journey tạo map → map gợi ý slice → slice tạo PBI → criteria tạo oracle → backlog giữ nguồn work minh bạch**.

## 7. Nguồn tham khảo và provenance phần bổ sung

Nội dung lý thuyết của Unit chỉ dựa trên bốn source refs đã map ở đầu Unit: **SRC-SG20, SRC-USER-STORIES, SRC-STORY-MAP, SRC-GHERKIN**. `starter/NovaShop_Project_Brief.md` và synthetic dataset chỉ là **project input** do `plan.project` quản lý để đặt bối cảnh thực hành; chúng không phải source ref hoặc nguồn provenance bổ sung của U04. Các ID, con số, scenario và artifact MEX-U04-01 là dữ liệu **simulated** được tạo cho khóa, không phải case khách hàng thật.

**Phần bổ sung/suy diễn:** Không dùng nguồn bổ sung ngoài bốn source refs nêu trên. Các ví dụ cụ thể dùng project brief và synthetic dataset như fixture đầu vào của scenario, không dùng chúng để hậu thuẫn tuyên bố lý thuyết, benchmark hoặc tuyên bố thực tế.

---
<!-- QUALITY GATE: 100% outline leaf có đủ semantic contract; MEX-U04-01 phủ LO/outline và map CP-U04-01/02; checklist hoàn tất; không còn chỉ dẫn khung. -->

# Unit U01: Agile mindset và lựa chọn cách làm — Học liệu cốt lõi

> **Khóa học:** Agile–Scrum thực hành qua dự án thương mại điện tử NovaShop · **Thuộc:** Agile và Scrum Foundations

## 🎯 Learning Outcomes

- **LO1.1** [analyze] — Phân loại đúng cách tiếp cận Agile hoặc plan-driven cho ít nhất 4/5 tình huống và giải thích bằng mức bất định, vòng phản hồi và chi phí thay đổi.
- **LO1.2** [create] — Viết hai giả thuyết giá trị NovaShop có outcome, tín hiệu kiểm chứng, ngưỡng quyết định và hành động thích nghi.

## Ngữ cảnh dự án và phần tăng trưởng của Unit

NovaShop là MVP thương mại điện tử B2C responsive bán mỹ phẩm và sản phẩm chăm sóc cá nhân. Đây là tình huống **simulated**; toàn bộ tên, số liệu, giao dịch và tích hợp đều là dữ liệu đào tạo, không đại diện cho doanh nghiệp hoặc khách hàng có thật. Chỉ dùng sandbox và dữ liệu synthetic; không dùng PII, tiền thật hay credential production.

Tại milestone **M-U01**, học viên biến project brief còn nhiều giả định thành:

- một decision canvas phân biệt công việc cần khám phá thích nghi với công việc đủ ổn định để lập kế hoạch chi tiết;
- một problem canvas ghi stakeholder, outcome, assumption và evidence;
- một value hypothesis register có outcome, signal, baseline, threshold, guardrail và adaptation rule.

Increment này trực tiếp tạo bằng chứng cho LO1.1 và LO1.2, được luyện lại trong CASE-U01-01 và LAB-U01-01, rồi được dùng làm đầu vào discovery ở U03 và gói bàn giao CAP-01.

## Nguồn đầu vào đã map

- SRC-AM01 — Manifesto for Agile Software Development: https://agilemanifesto.org/ (publisher: Agile Manifesto authors; version: 2001; accessed_at: 2026-08-25; license: reference-only; allowed_use: reference)
- SRC-AP01 — Principles behind the Agile Manifesto: https://agilemanifesto.org/principles.html (publisher: Agile Manifesto authors; version: 2001; accessed_at: 2026-08-25; license: reference-only; allowed_use: reference)
- SRC-SG20 — The Scrum Guide: https://scrumguides.org/scrum-guide.html (publisher: Ken Schwaber, Jeff Sutherland / ScrumGuides.org; version: November 2020; accessed_at: 2026-08-25; license: CC BY-SA 4.0; allowed_use: adapt)
- SRC-PROJECT — NovaShop simulated e-commerce project brief: starter/NovaShop_Project_Brief.md (publisher: Training artifact created for this course; version: 1.0; accessed_at: 2026-08-25; license: Internal approved for learner use; allowed_use: internal_approved)

## 1. Kiến thức tiên quyết và môi trường

Không yêu cầu kinh nghiệm Agile/Scrum. Học viên cần đọc được bảng CSV đơn giản, phân biệt một quan sát với một giả định và ghi lại lý do của quyết định.

Môi trường là **ENV-PRO-ARTIFACT**: Windows, macOS hoặc Linux; Markdown editor tương thích CommonMark; spreadsheet đọc CSV UTF-8; whiteboard bất kỳ hoặc giấy. Không cần runtime, dịch vụ cloud hay tài khoản trả phí.

Kiểm tra sẵn sàng:

1. Mở được ba file trong thư mục starter: NovaShop_Project_Brief.md, NovaShop_Synthetic_Data.csv và Artifact_Templates.md.
2. Xác nhận CSV có các record OBS-01 đến OBS-04 và không có tên, email, địa chỉ hay token thật.
3. Tạo được một bản sao trống của mẫu Decision record; không sửa starter asset.
4. Nếu cả ba điều kiện đạt, ghi PRECHECK-U01 = PASS. Nếu thiếu file hoặc dữ liệu không phải synthetic, dừng và dùng lại bộ starter đã phát hành.

Phương thức xác minh: **artifact_review**. Mode thực hành: **professional_artifact**, vì LO yêu cầu ra quyết định và tạo artifact nghề nghiệp, không yêu cầu viết hay chạy code.

## 2. Định vị trong lộ trình

U01 đặt nền cho toàn khóa: thay vì mặc định mọi việc đều “làm Agile”, học viên trước hết chẩn đoán mức bất định và thiết kế vòng học. U02 dùng tư duy này để vận hành Scrum; U03 biến giả thuyết thành Product Goal và stakeholder evidence; các Unit sau tiếp tục inspect và adapt backlog, Sprint và release forecast.

Mental model ngắn: **mục tiêu → điều chưa biết → cách làm → evidence → quyết định tiếp theo**. Agile không phải đích đến; nó là lựa chọn phù hợp khi học nhanh từ phản hồi có giá trị hơn việc khóa chi tiết sớm.

## 3. Nội dung lý thuyết cốt lõi

**Checklist bắt buộc phủ — giữ nguyên văn và đúng thứ tự Content Outlines:**

- [x] Agile mindset: giá trị, nguyên tắc và ranh giới áp dụng
- [x] Empiricism, uncertainty và giả thuyết giá trị

#### OUT-U01-01 Agile mindset: giá trị, nguyên tắc và ranh giới áp dụng

**Mapping:** OUT-U01-01 · LO1.1 · M-U01 decision canvas/problem canvas

##### Định nghĩa và ranh giới

Agile mindset là cách ưu tiên con người cùng tương tác, sản phẩm hoạt động, cộng tác với khách hàng và khả năng phản hồi thay đổi, trong khi vẫn thừa nhận quy trình, tài liệu, hợp đồng và kế hoạch có giá trị. Nó hướng tới giao giá trị sớm, phản hồi thường xuyên, chất lượng bền vững, đơn giản và cải tiến liên tục.

Agile không đồng nghĩa với “không kế hoạch”, “không tài liệu”, “đổi bất cứ lúc nào” hay một framework cụ thể. Scrum là một framework có thể hiện thực hóa empiricism; Agile là hệ giá trị và nguyên tắc rộng hơn. Plan-driven là cách khóa phần lớn phạm vi và chuỗi thực hiện sớm khi yêu cầu, công nghệ và tiêu chí chấp nhận đủ ổn định. Nhiều sáng kiến dùng một phổ lựa chọn thay vì hai nhãn tuyệt đối.

##### Vấn đề, vai trò và quyết định cần đưa ra

Sponsor cần biết nên mua sự chắc chắn bằng phân tích và kế hoạch trước, hay mua sự học bằng increment nhỏ và phản hồi sớm. Product Owner và Scrum Team phải quyết định cho từng work item:

- mức bất định về **nhu cầu**: ta có biết người dùng thực sự cần gì không;
- mức bất định về **giải pháp**: ta có biết cách tạo kết quả và rủi ro tích hợp không;
- tốc độ và chi phí nhận phản hồi;
- chi phí thay đổi nếu quyết định sai hoặc quyết định muộn.

Output là decision canvas, không phải nhãn theo sở thích. Quyết định phải chỉ ra evidence, trade-off và một counter-example: tình huống nào sẽ khiến cách làm đã chọn không còn phù hợp.

##### Cơ chế và mental model

Xem mỗi work item qua ba vùng:

1. **Ổn định:** yêu cầu và phương pháp đều rõ; lỗi thay đổi muộn đắt. Lập kế hoạch chi tiết, kiểm soát thay đổi và xác minh theo contract có thể hiệu quả.
2. **Bất định có thể giảm bằng feedback:** outcome hoặc giải pháp chưa rõ nhưng có thể thử lát nhỏ. Dùng vòng ngắn: giả thuyết → increment/experiment → evidence → thích nghi.
3. **Bất định nhưng feedback không khả dụng hoặc rủi ro không thể đảo ngược:** cần discovery, prototype, phân tích an toàn hoặc approval trước; không gọi việc “làm nhanh” là Agile.

Khi input thay đổi, lựa chọn cũng có thể đổi. Ví dụ, một contract vận chuyển từng ổn định chuyển sang thử nghiệm API mới sẽ làm tăng bất định giải pháp và cần vòng kiểm chứng ngắn hơn.

##### Khi dùng, khi không dùng và trade-off

Dùng cách thích nghi khi nhu cầu thay đổi nhanh, stakeholder có thể phản hồi, increment nhỏ có thể quan sát được và chi phí thử nghiệm được giới hạn. Không dùng thử-ngay trên tiền thật, PII hay quyết định an toàn không thể đảo ngược; trước hết phải tạo sandbox, guardrail và review phù hợp.

Dùng plan-driven cho hạng mục có contract ổn định, tiêu chí pass-fail rõ, phụ thuộc tuần tự bắt buộc và thay đổi muộn rất đắt. Không dùng kế hoạch chi tiết như bằng chứng giả về nhu cầu khách hàng chưa được kiểm chứng. Trade-off của vòng ngắn là overhead đo lường và nguy cơ tối ưu tín hiệu cục bộ; trade-off của khóa kế hoạch sớm là phản hồi đến muộn và sunk cost.

##### Ví dụ NovaShop riêng và oracle

- **Context/stakeholder:** Sponsor phải chọn cách làm cho “giảm bỏ checkout”.
- **Input/baseline/constraint:** OBS-01 ghi 7/10 người mô phỏng bỏ checkout khi bắt buộc tạo tài khoản; chỉ có sandbox và mười phiên synthetic, chưa có causal evidence.
- **Decision/action:** Chọn adaptive discovery cho luồng checkout: thử một lát guest checkout giới hạn, giữ kiểm tra địa chỉ và không dùng payment thật. Ghi counter-example: nếu quy định bắt buộc định danh trước thanh toán được xác nhận và không thể thử khác, phần đó chuyển sang constraint plan-driven.
- **Artifact/output:** DC-U01-CHK-01 trong decision canvas.
- **Expected result:** Assumption “bắt buộc tạo tài khoản gây bỏ checkout” không bị ghi thành fact; quyết định nêu vòng feedback và guardrail.
- **Oracle/evidence:** PASS khi canvas có source OBS-01, uncertainty nhu cầu/giải pháp, lựa chọn, feedback window, cost-of-change, guardrail và counter-example. FAIL khi chỉ ghi “Agile vì yêu cầu hay đổi”.

##### Liên kết MEX và Lab

OUT-U01-01 được triển khai trong **MEX-U01-01 — Decision canvas cho bất định checkout NovaShop** ở mục 4. LAB-U01-01/CP-U01-01 yêu cầu tái tạo logic với năm work item khác; CP-U01-02 buộc sửa quyết định khi xuất hiện change card mới.

##### Best practices

**Rule:** Phân loại theo uncertainty, feedback và reversibility, không theo nhãn dự án. **Rationale:** cùng một sản phẩm có phần discovery bất định và phần compliance ổn định. **Positive:** checkout UX dùng experiment, còn format export đã ký contract dùng checklist tuần tự. **Negative/hậu quả:** tuyên bố “toàn bộ NovaShop phải Agile” khiến đội thử nghiệm cả hạng mục không được phép thay đổi hoặc bỏ qua evidence.

**Rule:** Ghi counter-example cho mỗi lựa chọn. **Rationale:** counter-example làm lộ điều kiện biên và ngăn biến phương pháp thành giáo điều. **Positive:** “adaptive, trừ khi không thể nhận feedback an toàn trong Sprint”. **Negative/hậu quả:** “luôn dùng Scrum” không thể được falsify và che khuất rủi ro.

##### Failure diagnosis và cách sửa

- **Dấu hiệu:** canvas chỉ có cột Agile/Waterfall. **Nguyên nhân:** phân loại bằng nhãn thay vì cơ chế. **Chẩn đoán:** reviewer không tìm thấy uncertainty, feedback hoặc cost-of-change. **Sửa:** bổ sung ba trục và evidence cho từng trục. **Phòng tránh:** dùng checklist oracle trước khi chốt.
- **Dấu hiệu:** kế hoạch thay đổi liên tục nhưng không học được gì. **Nguyên nhân:** phản ứng với ý kiến, không với evidence. **Chẩn đoán:** không có signal hoặc review window. **Sửa:** ghép mỗi adaptation với hypothesis và threshold. **Phòng tránh:** không đổi baseline khi chưa ghi decision ID.

#### OUT-U01-02 Empiricism, uncertainty và giả thuyết giá trị

**Mapping:** OUT-U01-02 · LO1.2 · M-U01 value hypothesis register

##### Định nghĩa và ranh giới

Empiricism là việc hình thành kiến thức từ trải nghiệm và ra quyết định dựa trên điều quan sát được. Trong Scrum, nó vận hành qua transparency, inspection và adaptation. Transparency làm trạng thái, giả định và evidence đủ rõ; inspection so sánh chúng với mục tiêu; adaptation thay đổi kế hoạch hoặc artifact khi sai lệch vượt giới hạn chấp nhận.

Uncertainty là phần chưa biết về value, usability, feasibility hoặc risk. Một giả thuyết giá trị là phát biểu có thể bị bác bỏ về nhóm người dùng, thay đổi dự kiến, outcome, signal, threshold, thời hạn và hành động tiếp theo. Nó không phải lời hứa kinh doanh, user story hay danh sách tính năng.

##### Vấn đề, vai trò và quyết định cần đưa ra

Sponsor có target, nhưng target không chứng minh giải pháp. Product Owner quyết định giả thuyết nào đáng kiểm trước; Developers giúp xác định increment và evidence khả thi; stakeholder giải thích tác động. Quyết định bắt buộc là: tiếp tục, điều chỉnh hay dừng hướng đầu tư sau khi so signal với threshold và guardrail.

##### Cơ chế và mental model

Chuỗi thực nghiệm:

1. Tách **fact quan sát được**, **assumption** và **target**.
2. Chọn outcome thay đổi hành vi hoặc kết quả, không chọn output “đã làm chức năng”.
3. Đặt signal có đơn vị, baseline, threshold và timebox.
4. Đặt guardrail để tránh cải thiện một metric bằng cách làm xấu hệ thống.
5. Thu evidence theo contract; so với threshold.
6. Áp dụng rule continue/adjust/stop và ghi limitation.

Nếu signal tăng nhưng guardrail vi phạm, hypothesis không được coi là đạt. Nếu sample quá nhỏ, kết luận là “chưa đủ evidence”, không phải “thất bại” hay “thành công”.

##### Khi dùng, khi không dùng và trade-off

Dùng hypothesis khi quan hệ giữa thay đổi và outcome chưa chắc, có thể quan sát signal trong phạm vi an toàn và có một quyết định thật sẽ phụ thuộc vào kết quả. Không dùng một experiment nhỏ để hợp thức hóa yêu cầu pháp lý, hoặc khi không có quyền thu dữ liệu cần thiết. Khi đó dùng review contract, research hoặc evidence khác.

Threshold buộc quyết định rõ nhưng có thể tạo game metric; guardrail giảm rủi ro này nhưng làm experiment phức tạp hơn. Proxy signal cho phản hồi sớm nhưng có thể không đại diện cho value dài hạn, vì vậy phải ghi giới hạn.

##### Ví dụ NovaShop riêng và oracle

- **Context/stakeholder:** Product Owner kiểm giả thuyết guest checkout cho người mua mô phỏng.
- **Input/baseline/constraint:** OBS-01 = 7/10 bỏ khi buộc tạo tài khoản; OBS-02 = 4/12 đơn cần nhập lại địa chỉ. Hai record là synthetic, sample nhỏ.
- **Decision/action:** Giả thuyết: “Nếu cho guest checkout có validation địa chỉ, tỷ lệ phiên mô phỏng đi từ checkout start đến xác nhận đơn sẽ tăng từ 3/10 lên ít nhất 5/10 trong 20 phiên tiếp theo; guardrail là không quá 4/12 đơn cần nhập lại. Nếu đạt cả threshold và guardrail, tiếp tục refinement; nếu signal đạt nhưng guardrail hỏng, điều chỉnh validation; nếu không đạt, dừng ưu tiên và phỏng vấn lại.”
- **Artifact/output:** VH-U01-CHK-01 trong value hypothesis register.
- **Expected result:** Có outcome, signal/đơn vị, baseline, threshold, timebox, guardrail và ba nhánh adaptation.
- **Oracle/evidence:** Reviewer có thể đi từ OBS-01/OBS-02 tới từng trường và xác định duy nhất một trong ba quyết định. Nếu chỉ ghi “guest checkout tăng conversion”, kết quả là REVISE.

##### Liên kết MEX và Lab

OUT-U01-02 nằm trong cùng **MEX-U01-01** vì decision approach chỉ có ý nghĩa khi nối tới hypothesis có oracle. CP-U01-01 dùng dataset/order-tracking mới; CP-U01-02 thêm constraint mới để học viên cập nhật threshold hoặc cách làm, không sao chép artifact Material.

##### Best practices

**Rule:** Mỗi hypothesis phải có decision rule trước khi xem kết quả. **Rationale:** đặt rule sau khi thấy dữ liệu tạo thiên lệch xác nhận. **Positive:** “đạt signal và guardrail → tiếp tục; vi phạm guardrail → điều chỉnh”. **Negative/hậu quả:** sau experiment mới chọn metric thuận lợi và tuyên bố thành công.

**Rule:** Gắn baseline, threshold, đơn vị và timebox vào signal. **Rationale:** một con số không có mẫu số hoặc cửa sổ đo không thể so sánh. **Positive:** “ít nhất 10/20 phiên synthetic hoàn tất checkout”. **Negative/hậu quả:** “conversion tốt hơn” khiến hai reviewer có thể kết luận trái nhau.

##### Failure diagnosis và cách sửa

- **Dấu hiệu:** hypothesis mô tả output, ví dụ “xây guest checkout”. **Nguyên nhân:** nhầm deliverable với outcome. **Chẩn đoán:** câu không có thay đổi hành vi/kết quả. **Sửa:** thêm actor, outcome và signal. **Phòng tránh:** hỏi “nếu tính năng hoàn thành nhưng hành vi không đổi thì sao?”.
- **Dấu hiệu:** metric đạt nhưng lỗi nhập lại tăng. **Nguyên nhân:** thiếu guardrail. **Chẩn đoán:** so OBS-02 với threshold chất lượng. **Sửa:** đánh dấu ADJUST, không PASS; bổ sung validation địa chỉ. **Phòng tránh:** chọn ít nhất một guardrail liên kết risk.

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### MEX-U01-01 — Decision canvas cho bất định checkout NovaShop

**Practice contract:** professional_artifact · **LO:** LO1.1, LO1.2 · **Outline:** OUT-U01-01, OUT-U01-02 · **Milestone:** M-U01

### Input/trạng thái ban đầu

- OBS-01: 7/10 người mô phỏng bỏ checkout khi buộc tạo tài khoản.
- OBS-02: 4/12 đơn mô phỏng cần nhập lại địa chỉ.
- Target sponsor: tăng đơn trực tuyến 20% trong scenario; đây là assumption/target, không phải kết quả đã đạt.
- Constraint: sandbox, synthetic-only, không PII/payment thật.

### Professional artifact hoàn chỉnh

| Trường decision canvas | Giá trị |
| --- | --- |
| Decision ID | DEC-U01-01 |
| Quyết định | Dùng adaptive discovery cho guest-checkout slice; dùng contract/checklist ổn định cho address validation và data policy |
| Nhu cầu chưa chắc | OBS-01 có tương quan, chưa chứng minh tạo tài khoản là nguyên nhân |
| Giải pháp chưa chắc | Chưa biết guest checkout có giữ đủ dữ liệu giao hàng |
| Feedback | 20 phiên checkout synthetic; review sau một vòng |
| Reversibility/cost | Feature flag sandbox có thể bỏ; payment/PII thật bị cấm |
| Counter-example | Nếu policy bắt buộc account được xác nhận hoặc không có feedback an toàn, không chạy experiment này |
| Evidence cần thu | completion count và re-entry count, kèm denominator |

| ID | Value hypothesis register |
| --- | --- |
| VH-U01-01 | Với guest buyer, guest checkout có validation địa chỉ được kỳ vọng tăng số phiên đi tới xác nhận đơn từ baseline 3/10 lên ít nhất 10/20 phiên synthetic |
| Signal/timebox | order-confirmation count / 20 checkout starts, đo trong một vòng mô phỏng |
| Guardrail | tỷ lệ đơn phải nhập lại không vượt baseline synthetic 4/12 |
| Nếu đạt | Giữ hướng đầu tư và đưa slice vào discovery/backlog |
| Nếu signal đạt nhưng guardrail hỏng | Điều chỉnh validation; không tuyên bố hypothesis đạt |
| Nếu không đạt hoặc evidence thiếu | Dừng/thiết kế lại research; giữ rõ trạng thái inconclusive |

Luồng quyết định là input observations → phân loại uncertainty/reversibility → chọn vòng feedback → đo signal và guardrail → tiếp tục/điều chỉnh/dừng. Artifact không chứng minh guest checkout chắc chắn tạo value; nó chỉ làm cho giả định và quyết định kiểm chứng được.

### Expected result và oracle

Artifact PASS khi:

1. assumption, observation và target được gắn nhãn khác nhau;
2. decision canvas có uncertainty, feedback, reversibility và counter-example;
3. hypothesis có actor/outcome, signal, baseline, threshold, timebox, guardrail và adaptation;
4. không có claim benchmark/conformance hoặc dữ liệu thật;
5. reviewer độc lập chọn được đúng một nhánh continue/adjust/stop từ một bộ kết quả.

Ví dụ kiểm oracle: nếu kết quả là 11/20 xác nhận đơn và 6/12 đơn cần nhập lại, decision phải là **ADJUST**, không phải PASS, vì guardrail hỏng.

### Mapping Material worked example → Hands-on Lab tương ứng

- **MEX-U01-01 → LAB-U01-01/CP-U01-01:** tái tạo canvas bằng năm work item và observation khác; evidence là artifact Lab cùng trace input → decision → evidence.
- **MEX-U01-01 → LAB-U01-01/CP-U01-02:** áp dụng change card làm thay đổi một constraint; evidence là impact note, diff và self-check.
- Trong Lab, cả hai checkpoint phải ghi material_example_refs = MEX-U01-01.

## 5. Lỗi thường gặp và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán/evidence | Cách sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| Mọi work item đều bị gắn Agile | Nhầm giá trị với một quy trình bắt buộc | Không có counter-example hoặc cost-of-change | Chấm lại theo uncertainty/feedback/reversibility | Bắt buộc ba trục trong canvas |
| Observation bị viết thành kết luận nhân quả | Sample synthetic nhỏ và thiên lệch xác nhận | Claim dùng “vì” nhưng chỉ có count | Hạ confidence, viết hypothesis có thể bác bỏ | Tách cột fact/assumption/target |
| Threshold không có denominator | Measurement contract thiếu | Reviewer không tái tính được | Thêm đơn vị, mẫu số, timebox | Dùng checklist hypothesis |
| Team đổi scope sau mọi ý kiến | Không có decision rule | Không tìm thấy signal/guardrail | Chỉ adapt khi oracle hoặc constraint thay đổi | Ghi trigger trước review |
| File có email/token thật | Dùng dữ liệu ngoài starter | No-PII/secret review FAIL | Loại artifact, tạo lại từ starter | Synthetic-only precheck |

## 6. Từ điển thuật ngữ và mô hình tư duy

- **Agile mindset:** hệ giá trị/nguyên tắc ưu tiên phản hồi, cộng tác, giá trị và khả năng thích nghi; không phải tên một quy trình duy nhất.
- **Plan-driven:** cách đầu tư nhiều hơn vào dự đoán và kế hoạch sớm khi input/contract đủ ổn định.
- **Empiricism:** học từ trải nghiệm quan sát được rồi thích nghi.
- **Transparency / inspection / adaptation:** làm rõ trạng thái / so với mục tiêu / điều chỉnh khi cần.
- **Uncertainty:** phần chưa biết có thể thay đổi quyết định.
- **Value hypothesis:** giả định outcome có signal và rule ra quyết định.
- **Signal:** phép đo dùng để giảm bất định; không tự động là value.
- **Threshold:** ngưỡng pass-fail định trước.
- **Guardrail:** giới hạn bảo vệ chất lượng hoặc rủi ro khi tối ưu signal.
- **Counter-example:** điều kiện làm lựa chọn hiện tại không còn hợp lệ.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

- SRC-AM01 — https://agilemanifesto.org/ — values, publisher Agile Manifesto authors, version 2001, accessed 2026-08-25, reference-only.
- SRC-AP01 — https://agilemanifesto.org/principles.html — principles, publisher Agile Manifesto authors, version 2001, accessed 2026-08-25, reference-only.
- SRC-SG20 — https://scrumguides.org/scrum-guide.html — empiricism, pillars và Scrum boundary, November 2020, CC BY-SA 4.0.
- SRC-PROJECT — starter/NovaShop_Project_Brief.md — scenario và synthetic data policy, version 1.0, internal approved.

### Phần bổ sung/suy diễn

- [SUY DIỄN — từ kiến thức đã huấn luyện] Decision canvas ba trục, ID artifact và các threshold 20 phiên là thiết kế sư phạm mô phỏng; không phải benchmark ngành.
- [SUY DIỄN — từ kiến thức đã huấn luyện] Phân vùng ổn định/adaptive/safety-first là heuristic phục vụ bài học, không phải thành phần bắt buộc của Scrum.

> **Simulated disclosure:** Mọi số liệu NovaShop chỉ là dữ liệu đào tạo. Không suy rộng thành kết quả thị trường hay lời khuyên cho production.

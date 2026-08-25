# Unit U05: Refinement, estimation và ordering — Học liệu cốt lõi

> **Khóa học:** Agile–Scrum thực hành qua dự án thương mại điện tử NovaShop · **Thuộc:** Refinement và Sprint Planning · **Xác thực:** simulated

## 🎯 Learning Outcomes

- **LO5.1** [evaluate] — Ước lượng tương đối PBI, ghi rõ giả định, bất định và lý do cho các chênh lệch lớn. Bằng chứng: Sizing record và planning-poker evidence.
- **LO5.2** [evaluate] — Sắp xếp Product Backlog theo value, risk, dependency và learning value với evidence cho từng quyết định. Bằng chứng: Product Backlog v2 có ordering rationale và impact note.

## 🧭 Ngữ cảnh và increment M-U05

Baseline là Story Map và Product Backlog v1 từ U04. Scrum Team làm rõ các PBI gần đầu backlog, dùng relative sizing để phơi lộ khác biệt về hiểu biết, rồi Product Owner chịu trách nhiệm về thứ tự dựa trên value, risk, dependency và learning. Output là **Sizing record** cùng **Product Backlog v2**; U06 dùng hai artifact này để forecast trong Sprint Planning.

Refinement, user story, story point và Planning Poker là các thực hành bổ trợ, không phải event/artifact bắt buộc của Scrum. Không dùng velocity hoặc story point để so sánh đội, chấm hiệu suất cá nhân hay đổi trực tiếp thành giờ.

## 📚 Nguồn đầu vào đã map

- **SRC-SG20** — [The Scrum Guide 2020](https://scrumguides.org/scrum-guide.html), Ken Schwaber và Jeff Sutherland, CC BY-SA 4.0, adapt.
- **SRC-BACKLOG** — [Introduction to the Product Backlog](https://www.scrum.org/resources/introduction-product-backlog), Scrum.org, snapshot 2026-08-25, reference-only.
- **SRC-PLANNING-POKER** — [Planning Poker](https://agilealliance.org/glossary/planning-poker/), Agile Alliance, snapshot 2026-08-25, reference-only.
- **SRC-FORECAST** — [Introduction to Forecasting and Release Planning](https://www.scrum.org/resources/introduction-forecasting-and-release-planning), Scrum.org, snapshot 2026-08-25, reference-only.

## 1. Prerequisite, environment và preflight

Hoàn thành U04; có Product Backlog v1 với PBI ID, outcome, acceptance examples, dependency/risk và evidence. ENV-PRO-ARTIFACT cần Markdown CommonMark, bảng tính CSV UTF-8 và whiteboard/paper; không có service hay credential.

**Preflight PASS:** mở được ba starter asset; Product Backlog v1 có ít nhất ba PBI truy vết được; template có “Refinement và ordering record”; tạo được bản làm việc mà không sửa baseline. **Validation:** artifact review. **Practice mode:** professional_artifact vì LO là quyết định planning, không phải coding.

## 2. Mental map

```text
Product Backlog v1 + Story Map (U04)
  → refinement: hiểu đúng, làm nhỏ, nêu uncertainty
  → relative sizing: so sánh và làm lộ bất đồng
  → ordering: value + risk + dependency + learning
Product Backlog v2 + Sizing record (U05)
  → Sprint Planning: Goal, forecast, plan (U06)
```

Refinement không biến Product Backlog thành kế hoạch cố định. Nó làm đủ rõ nhóm item gần đầu để Product Owner và Developers có thể tiếp tục ra quyết định; detail, size và order vẫn nổi lên khi học được điều mới.

## 3. Nội dung lý thuyết cốt lõi

**📋 Checklist bắt buộc phủ — giữ nguyên văn và đúng thứ tự Content Outlines:**

- [x] Product Backlog refinement và relative sizing
- [x] Backlog ordering theo value, risk, dependency và learning

#### OUT-U05-01 — Product Backlog refinement và relative sizing

**Mapping:** OUT-U05-01 · LO5.1 · M-U05, tạo Sizing record có assumptions/uncertainty và evidence bất đồng.

##### Định nghĩa và ranh giới

Product Backlog refinement là hoạt động liên tục chia nhỏ và làm rõ PBI bằng cách bổ sung description, order, size cùng các thuộc tính hữu ích. Scrum Guide không định nghĩa refinement là event có timebox cố định. **Relative sizing** so một PBI với reference item theo tổng hợp effort, complexity, uncertainty và risk mà đội đã thống nhất; nó không phải thời lượng, deadline hay giá trị kinh doanh.

Planning Poker là kỹ thuật thảo luận: thành viên chọn estimate độc lập, lộ đồng thời, người ở hai đầu giải thích assumptions, rồi đội thảo luận và có thể bỏ phiếu lại. Con số cuối ít quan trọng hơn evidence về khác biệt hiểu biết.

##### Vấn đề, vai trò và quyết định

PBI mơ hồ khiến Sprint Planning biến thành buổi khám phá quá muộn. Developers chịu trách nhiệm sizing vì họ tạo plan và thực hiện work; Product Owner cung cấp outcome, order và context; chuyên gia khác có thể tư vấn. Đội phải quyết định: PBI đủ rõ để so sánh chưa, reference nào ổn định, dispersion nào cần thảo luận, uncertainty nào phải ghi hoặc cần spike/experiment.

##### Cơ chế và mental model

Một refinement record đi theo chuỗi: **PBI outcome/criteria → readiness gap → assumptions/open questions → reference comparison → simultaneous estimates → explain extremes → update understanding → final size hoặc “chưa size” → review trigger**. Nếu bất đồng đến từ missing contract, việc ghi `?` và tạo learning action trung thực hơn ép consensus.

Size chỉ có nghĩa trong bối cảnh một đội, một reference set và một Definition of Done. Khi DoD, composition hoặc work type đổi đáng kể, lịch sử so sánh cần được xem lại.

##### Khi dùng, khi không dùng và trade-off

Dùng relative sizing khi đội cần so sánh work mới với work quen thuộc và chính xác tuyệt đối là giả tạo. Không cần size toàn backlog xa; detail sẽ lỗi thời. Không dùng estimate để xếp hạng nhân sự hoặc bắt đội cam kết ngày. Trade-off: sizing tạo ngôn ngữ chung nhưng có thể tốn thời gian; giới hạn discussion vào dispersion/risk quan trọng và chỉ refine đủ item có khả năng được làm sớm.

##### Ví dụ thực tế riêng và oracle

- **Context:** PBI “xác nhận mã giảm giá sandbox”.
- **Input:** reference `PBI-CART-REF=3`; votes `3, 3, 5, 8`; open question về stackable promotion; DoD giữ nguyên.
- **Decision:** người vote 8 nêu assumption “hai mã có thể cộng dồn”; Product Owner xác nhận phạm vi chỉ một mã. Criteria được cập nhật, re-vote `3, 3, 5, 5`, final size 5, uncertainty còn lại là expiry timezone.
- **Artifact:** sizing record lưu cả vòng đầu, assumption, clarification, vòng sau và trigger review.
- **Expected:** chênh lệch không bị xóa; size cuối có reference/rationale; timezone uncertainty vẫn hiển thị.
- **Oracle:** reviewer trả lời được “vì sao 5, khác reference 3 ở đâu, điều gì làm estimate phải xem lại?”.

##### Best practices

- **Rule:** dùng estimate độc lập trước discussion. **Rationale:** tránh anchoring theo người nói đầu. **Positive:** reveal đồng thời `3/3/5/8`. **Negative:** lead nói “chắc 3” rồi mọi người đồng ý; hidden risk không xuất hiện.
- **Rule:** ghi assumptions và uncertainty cạnh size. **Rationale:** một số không mang theo điều kiện làm nó đúng. **Positive:** `5; one-code-only; timezone open`. **Negative:** chỉ `5`; U06 không biết trigger nào làm forecast sai.
- **Rule:** giữ reference/DoD ổn định trong comparison. **Rationale:** thay thước đo làm lịch sử không còn so được. **Positive:** so với cart item đã đạt cùng DoD. **Negative:** so item research chưa test với Increment Done và gọi chênh lệch là productivity.

##### Anti-pattern, failure và troubleshooting

- **Dấu hiệu:** story point bị đổi thành ngày bằng công thức cố định. **Nguyên nhân:** muốn certainty giả. **Chẩn đoán:** cùng 5 point bị buộc cùng số giờ dù uncertainty khác. **Sửa:** tách size khỏi capacity/forecast và ghi assumptions. **Phòng tránh:** cấm conversion table.
- **Dấu hiệu:** consensus quá nhanh, không có dispersion record. **Nguyên nhân:** anchoring hoặc psychological safety thấp. **Chẩn đoán:** mọi vote giống người có thâm niên. **Sửa:** reveal đồng thời, mời extremes giải thích theo evidence. **Phòng tránh:** facilitator bảo vệ dissent.
- **Dấu hiệu:** size rất lớn nhưng PBI không đổi. **Nguyên nhân:** item có nhiều outcome/rule. **Chẩn đoán:** nhiều actor/When hoặc open question blocking. **Sửa:** split theo scenario/rule/data boundary hoặc tạo learning item. **Phòng tránh:** review readiness trước vote.

#### OUT-U05-02 — Backlog ordering theo value, risk, dependency và learning

**Mapping:** OUT-U05-02 · LO5.2 · M-U05, tạo Product Backlog v2 có ordering rationale và impact note.

##### Định nghĩa và ranh giới

Ordering là quyết định đặt quan hệ trước–sau trong một Product Backlog để tối đa hóa value và quản lý rủi ro/học tập; Product Owner chịu trách nhiệm về hiệu quả của Product Backlog management. **Value** là outcome mong đợi; **risk** là bất định/tác động có thể làm mất value; **dependency** là điều kiện cần có trước hoặc phối hợp; **learning value** là thông tin giúp đổi quyết định. Ordering không đồng nghĩa với sort theo một cột priority hay lấy “điểm cao nhất” của một công thức.

##### Vấn đề, vai trò và quyết định

PBI nhiều value có thể phụ thuộc contract chưa biết; item ít value trực tiếp có thể cần làm sớm để giảm rủi ro. Product Owner đưa ra order sau khi lắng nghe Developers và stakeholder. Quyết định cần nêu: item nào trước, yếu tố nào chi phối, dependency nào hard/soft, risk nào cần retire sớm, và signal nào làm order thay đổi.

##### Cơ chế và mental model

Mỗi ordering record có bốn cột evidence riêng: value, risk, dependency, learning. Nhóm so sánh trade-off rồi ghi **decision + rationale + review trigger**, không cộng cơ học các ordinal label. Hard dependency đặt giới hạn khả thi; soft dependency có thể đảo để học sớm. Risk có hai hướng: làm sớm để khám phá/giảm risk, hoặc hoãn khi exposure nhỏ và chi phí cơ hội lớn.

##### Khi dùng, khi không dùng và trade-off

Ordering diễn ra liên tục khi evidence hoặc context đổi. Không đóng băng toàn backlog; items xa có thể để thô. Một scoring model có thể hỗ trợ conversation nếu giả định minh bạch, nhưng không thay accountability của Product Owner. Trade-off là làm risk/learning item sớm có thể trì hoãn visible feature; đổi lại forecast sau đó có evidence tốt hơn.

##### Ví dụ thực tế riêng và oracle

- **Context:** hai PBI: `A` thêm bộ lọc thương hiệu; `B` kiểm chứng shipping quote sandbox.
- **Input:** A có visible value cao và dependency thấp; B có value trực tiếp trung bình nhưng risk/learning cao, là dependency của checkout.
- **Decision:** B đứng trước A để retire contract risk và mở đường cho đặt đơn; trigger: nếu sandbox contract đã được chứng minh từ source khác, Product Owner xem lại thứ tự.
- **Artifact:** ordering note tách bốn yếu tố và ghi option A-first không chọn.
- **Expected:** reviewer biết điều gì chi phối order; không hiểu nhầm B “có value cao hơn mọi mặt”.
- **Oracle:** đảo giả định dependency của B thành soft/no-risk; nếu rationale không dẫn đến xem lại order thì decision record thiếu trigger.

##### Best practices

- **Rule:** tách evidence của value, risk, dependency và learning. **Rationale:** một điểm tổng che khuất lý do và sensitivity. **Positive:** “B trước vì hard dependency + learning high”. **Negative:** “B=87 điểm”; người sau không biết 87 đổi khi contract rõ.
- **Rule:** ghi review trigger cho order. **Rationale:** Product Backlog là emergent. **Positive:** “review khi sandbox contract pass hoặc risk owner đóng RISK-01”. **Negative:** priority cố định bất chấp evidence mới.
- **Rule:** không dùng size làm value và không chia value/size như oracle duy nhất. **Rationale:** size là effort/uncertainty, value là outcome. **Positive:** cân trade-off riêng. **Negative:** item nhỏ luôn lên đầu, gây local optimization.

##### Anti-pattern, failure và troubleshooting

- **Dấu hiệu:** mọi item “P0”. **Nguyên nhân:** tránh trade-off. **Chẩn đoán:** không có order duy nhất hoặc rationale. **Sửa:** buộc so cặp item theo Goal và evidence. **Phòng tránh:** một ordered list, không nhiều danh sách cạnh tranh.
- **Dấu hiệu:** dependency được viện dẫn nhưng không có source/owner. **Nguyên nhân:** assumption biến thành fact. **Chẩn đoán:** không ai chỉ được condition/evidence. **Sửa:** phân loại hard/soft/assumed và tạo trigger. **Phòng tránh:** dependency map có owner.
- **Dấu hiệu:** risk item luôn bị hoãn vì “không có feature”. **Nguyên nhân:** bỏ learning value. **Chẩn đoán:** risk vẫn mở khi Sprint Planning. **Sửa:** tạo outcome học tập và oracle. **Phòng tránh:** review exposure cùng value.

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### Refinement record cho payment và inventory risk

**Stable ID:** MEX-U05-01 · **Artifact:** Sizing record và ordered backlog · **Mapping:** LO5.1, LO5.2; OUT-U05-01, OUT-U05-02.

**Verification method từ plan:** đối chiếu từng trường của artifact với checklist, input source và oracle được nêu trong Material.

### Mapping Material worked example → Hands-on Lab tương ứng

- **MEX-U05-01 → LAB-U05-01/CP-U05-01:** recreate sizing với backlog/votes mới; LO5.1, LO5.2.
- **MEX-U05-01 → LAB-U05-01/CP-U05-02:** modify ordering dưới inventory dependency mới; LO5.1, LO5.2.

**Baseline/input:** Product Backlog v1 có năm PBI dưới đây; reference `PBI-REF-CART=3`, đã đạt cùng DoD. Risk cards: inventory contract chỉ xác nhận stock theo SKU; payment sandbox có `approved/declined` nhưng retry/correlation chưa rõ. Constraint: không convert point sang giờ và không hạ DoD.

#### Artifact A — Sizing record

| PBI | Round 1 | Extreme assumption/evidence | Clarification/action | Round 2/final | Uncertainty/trigger |
| --- | --- | --- | --- | --- | --- |
| PB-501 Search + stock result | 3/3/5/3 | Vote 5: stock có thể stale | Scope chỉ hiển thị snapshot sandbox | 3/3/3/3 → **3** | Review nếu reservation được thêm |
| PB-502 Add one SKU to cart | 3/5/3/3 | Vote 5: price may change | Criteria giữ price snapshot tại add | 3/3/3/3 → **3** | Promotion out of scope |
| PB-503 Validate new address | 5/8/8/13 | Vote 13: nhiều format địa chỉ | Tách address autocomplete; giữ required fields + retain input | 8/8/8/8 → **8** | Danh mục ward sandbox chưa ổn định |
| PB-504 Payment approved/declined | 5/13/8/13 | Votes 13: retry và correlation chưa rõ | Giữ một attempt; tạo learning action cho correlation contract | 8/8/13/8 → **8**, confidence low | Review khi RISK-01 contract evidence có |
| PB-505 Order confirmation | 3/5/3/5 | Vote 5: email sandbox dependency | Outcome chính là on-screen order ID; email later | 3/3/3/3 → **3** | Review nếu email vào DoD |

#### Artifact B — Product Backlog v2 ordering excerpt

| Order | PBI | Value evidence | Risk | Dependency | Learning value | Decision/rationale/trigger |
| ---: | --- | --- | --- | --- | --- | --- | --- |
| 1 | PB-501 | Mở đầu journey mua | Stock snapshot có thể stale | Không | Xác nhận inventory contract tối thiểu | Làm trước để mở data path; review nếu stock source đổi |
| 2 | PB-502 | Giữ lựa chọn để checkout | Price consistency | PB-501 về SKU | Thấp | Đi sau stock, tạo cart baseline |
| 3 | PB-504 | Cho phép order outcome | **RISK-01 open** | PB-502; address có thể stub bằng fixture | **Cao:** payment/correlation | Đưa lên trước PB-503 để retire integration risk; review khi contract pass/fail có evidence |
| 4 | PB-503 | Giảm re-entry địa chỉ | Format/danh mục ward | PB-502; cần trước release checkout | Trung bình | Làm sau payment learning nhưng trước end-to-end release |
| 5 | PB-505 | Người mua biết kết quả | Email dependency | PB-503 + PB-504 | Thấp | On-screen confirmation đủ S1; email later |

**Giải thích:** dispersion ở PB-503/504 không bị trung bình hóa; assumptions làm rõ vì sao size khác. PB-504 đứng trước PB-503 không có nghĩa payment có value tuyệt đối cao hơn address: order ưu tiên learning/risk sớm, trong khi release vẫn cần cả hai. Đây là trade-off có trigger, không phải formula bất biến.

**Happy behavior:** contract payment được làm rõ, PB-504 giữ size 8 và order tiếp tục hợp lý. **Edge/failure:** nếu correlation/retry trở thành mandatory, PB-504 không được ép giữ 8; record chuyển về refine/split và Product Owner xem lại order/forecast.

**Verification — PASS khi:**

1. mọi final size có reference, vote history, rationale và uncertainty/trigger;
2. dispersion lớn ở PB-503/504 có evidence xử lý, không chỉ lấy trung bình;
3. ordering tách đủ value/risk/dependency/learning cho 5/5 PBI;
4. mỗi quan hệ trước–sau có rationale; RISK-01 và trigger resolve;
5. không có point-to-hour conversion, team comparison hoặc guarantee.

Expected result: **Estimate giữ uncertainty; ordering rationale tách value, risk, dependency và learning value.** Reviewer ghi `PASS`/`REVISE` với PBI và check number.

**Material ↔ Lab:** [CP-U05-01](HandsOnLab_05.md#checkpoint-1--cp-u05-01-refine-và-size-backlog-biến-thể) tái tạo sizing trên backlog/order-tracking khác; [CP-U05-02](HandsOnLab_05.md#checkpoint-2--cp-u05-02-reorder-khi-inventory-dependency-đổi) áp dụng dependency inventory mới. Cả hai khai `material_example_refs: MEX-U05-01`.

## 5. Lỗi thường gặp

| Dấu hiệu | Nguyên nhân | Chẩn đoán/evidence | Sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| Point thành giờ/ngày | Áp lực certainty | Có conversion table | Tách size record khỏi capacity forecast | Ghi “relative, team-local” trên artifact |
| Vote đồng thuận tức thì | Anchoring | Không có round/extreme rationale | Reveal đồng thời và hỏi extremes | Facilitator rotation |
| Order chỉ theo một score | Formula che trade-off | Không có evidence bốn chiều | Tách cột và ghi trigger | Pairwise review với Goal |
| Dependency giả | Assumption không owner | Không có contract/condition | Gắn owner, hard/soft, evidence | Dependency map review |
| Refine toàn backlog | Tìm completeness | Item xa chi tiết nhưng stale | Chỉ refine vùng có khả năng làm sớm | Đặt refinement horizon |

## 6. Thuật ngữ và mental model

- **Refinement:** hoạt động liên tục bổ sung detail, order, size; không phải Scrum event bắt buộc.
- **Relative size:** so sánh work trong bối cảnh một đội/reference/DoD.
- **Planning Poker:** kỹ thuật reveal estimate và assumptions, không phải yêu cầu Scrum.
- **Dispersion:** độ phân tán vote, tín hiệu khác biệt hiểu biết.
- **Ordering:** quan hệ trước–sau của một Product Backlog.
- **Learning value:** thông tin có thể đổi quyết định hoặc giảm uncertainty.
- **Hard/soft dependency:** điều kiện bắt buộc so với quan hệ thuận tiện/assumed.

Mental model: **refine để hiểu → size để lộ assumptions → order để tối đa hóa value và học → ghi trigger để thích nghi**.

## 7. Nguồn tham khảo và provenance phần bổ sung

Nội dung dùng đúng SRC-SG20, SRC-BACKLOG, SRC-PLANNING-POKER và SRC-FORECAST đã map. PBI, vote, size và order trong MEX-U05-01 là simulated course data; không phải benchmark hay dữ liệu đội thật. Không dùng nguồn bổ sung ngoài registry.

---
<!-- QUALITY GATE: hai leaf đủ semantic contract; MEX-U05-01 phủ LO/outline và map CP-U05-01/02; checklist hoàn tất; không còn chỉ dẫn khung. -->

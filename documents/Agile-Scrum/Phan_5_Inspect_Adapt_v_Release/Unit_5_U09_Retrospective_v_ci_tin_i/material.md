# Unit U09: Retrospective và cải tiến đội — Học liệu cốt lõi

> **Khóa học:** Agile–Scrum thực hành qua dự án thương mại điện tử NovaShop · **Thuộc:** Inspect, Adapt và Release · **Mức xác thực:** simulated

## 🎯 Learning Outcomes

- **LO9.1** — Phân tích dữ liệu Sprint để xác định nguyên nhân gốc và phân biệt symptom với cause. Bằng chứng: Retrospective evidence map và causal analysis.
- **LO9.2** — Thiết kế improvement experiment có owner, thời hạn, leading signal, guardrail và review date. Bằng chứng: Experiment card và Working Agreement v2.

## Ngữ cảnh và phần tăng trưởng M-U09

Sau Sprint Review U08, NovaShop có board history, flow data, event log, feedback và Working Agreement v1. Scrum Team dùng Retrospective để plan cách tăng quality/effectiveness; không chấm điểm cá nhân. Unit tạo **Retrospective evidence map**, **causal map**, **improvement experiment** và **Working Agreement v2**. Các artifact ghi rõ giả thuyết/giới hạn; số liệu đều synthetic, không phải benchmark hay kết quả doanh nghiệp thật.

## Nguồn đầu vào đã map

- **SRC-SG20** — [The Scrum Guide](https://scrumguides.org/scrum-guide.html), Ken Schwaber & Jeff Sutherland/ScrumGuides.org, November 2020, accessed 2026-08-25, CC BY-SA 4.0, allowed use: adapt.
- **SRC-EVENTS** — [Introduction to the Scrum Events](https://www.scrum.org/resources/introduction-scrum-events), Scrum.org, snapshot/accessed 2026-08-25, website terms, allowed use: reference.
- **SRC-EBM24** — [Evidence-Based Management Guide](https://www.scrum.org/resources/online-evidence-based-management-guide), Scrum.org, May 2024, accessed 2026-08-25, CC BY-SA 4.0, allowed use: adapt.
- **SRC-KANBAN-SCRUM** — [Kanban Guide for Scrum Teams](https://www.scrum.org/resources/kanban-guide-scrum-teams), 2021 edition, accessed 2026-08-25, CC BY-SA 4.0, allowed use: adapt.

## 1. Kiến thức tiên quyết và môi trường

Học viên hoàn thành U08, biết đọc board/evidence và có Working Agreement v1. `ENV-PRO-ARTIFACT` cần Markdown/CSV và whiteboard/paper. Smoke check: flow rows có stable ID/timestamp/state; event log phân biệt observation với opinion; Review record/DoD version mở được; bản làm việc không sửa starter asset.

## 2. Mental map

`Daily/Review evidence (U07–U08) → symptom → causal hypotheses → evidence test → improvement experiment → Working Agreement v2 → metrics/forecast U10`

Daily Scrum adapt plan trong Sprint; Retrospective inspect cách team làm việc và plan improvements. Một causal map không phải “sự thật cuối”; nó làm giả thuyết/quan hệ/evidence minh bạch để experiment tạo feedback mới.

## 3. Nội dung lý thuyết cốt lõi

**Checklist Content Outlines:**

- [x] Retrospective dựa trên evidence và causal analysis
- [x] Improvement experiment và cập nhật Working Agreement

### OUT-U09-01 — Retrospective dựa trên evidence và causal analysis

**Mapping:** OUT-U09-01 · LO9.1 · M-U09/Retrospective evidence map và causal map.

#### Định nghĩa và ranh giới

Sprint Retrospective là sự kiện kết thúc Sprint để Scrum Team plan cách tăng quality và effectiveness. Team inspect individuals, interactions, processes, tools và DoD; tìm điều hữu ích nhất cần đổi và xử lý sớm. Retrospective không phải Sprint Review (inspect product/outcome với stakeholders), không phải blame session và không cần đợi “root cause duy nhất” mới hành động.

**Symptom** là điều quan sát được cần giải thích, như 4/5 item checkout vượt 3 ngày. **Cause hypothesis** là cơ chế có thể tạo symptom, như hàng chờ sandbox. **Root cause** chỉ nên dùng khi evidence đủ chứng minh chuỗi; trong hệ thống phức tạp thường có nhiều yếu tố tương tác, nên ghi mức tin cậy và disconfirming evidence.

#### Vấn đề, vai trò và quyết định

Scrum Team cần chọn vấn đề đáng học, phân biệt data với diễn giải, so nhiều giả thuyết và quyết định một improvement có leverage. Scrum Master có thể facilitation/safety; không sở hữu outcome thay team. Artifact phải giúp reviewer trả lời: observation nào có timestamp; hypothesis nào được/không được evidence hỗ trợ; alternative nào còn mở; experiment sẽ học điều gì.

#### Cơ chế và mental model

Chuỗi causal analysis:

1. Viết symptom trung tính với cohort/time window/unit.
2. Lập evidence map: board timestamps, blocked reasons, review rework, event log, DoD gaps.
3. Đề xuất ≥2 hypotheses; không gắn nhãn người.
4. Với mỗi hypothesis, ghi evidence ủng hộ, evidence phản bác/thiếu và cách phân biệt.
5. Vẽ causal chain bằng động từ có cơ chế, đánh dấu assumption/confidence.
6. Chọn leverage point team kiểm soát và tạo experiment, không nhảy thẳng tới solution vĩnh viễn.

Có thể dùng 5 Whys/fishbone như prompts, nhưng số “why” không chứng minh nhân quả. Correlation (sandbox wait xuất hiện cùng cycle time dài) tạo giả thuyết; timestamp sequence và comparison group làm giả thuyết mạnh hơn nhưng vẫn có giới hạn sample.

#### Khi dùng, khi không dùng và trade-off

Dùng khi có outcome bất ngờ, recurring wait/rework, DoD friction hoặc phối hợp kém. Không thu thập dữ liệu giám sát cá nhân nhạy cảm, không so velocity để đổ lỗi, không kéo Retrospective thành audit toàn tổ chức. Evidence tăng chất lượng quyết định nhưng sample nhỏ có noise; qualitative observations bổ sung context, miễn ghi rõ loại evidence.

#### Ví dụ thực tế có oracle

Synthetic cohort checkout Sprint 3:

| Item | Total elapsed | Wait sandbox | Rework after review |
| --- | ---: | ---: | ---: |
| C-61 | 3.0d | 1.8d | 0 |
| C-62 | 4.0d | 2.6d | 1 |
| C-63 | 3.5d | 2.0d | 0 |
| C-64 | 2.0d | 0.8d | 0 |
| C-65 | 4.5d | 3.0d | 1 |

Symptom: 4/5 item có elapsed ≥3 ngày. H1 “sandbox queue làm tăng wait” được hỗ trợ bởi wait 10.2/17.0 item-days (60%) và event log cùng dependency; H2 “AC mơ hồ tạo rework” chỉ có 2/5 items, nên là contributing hypothesis, không giải thích toàn bộ. Leverage point là cách reserve/prepare test slot, không phải “lập trình viên chậm”. Oracle PASS khi symptom có cohort/window; ≥2 hypotheses; evidence support/against; cause khác symptom; limitation sample n=5 được ghi.

#### Best practices

- **Rule:** mô tả symptom bằng dữ liệu trung tính. **Rationale:** giảm confirmation bias/blame. **Positive:** “4/5 item ≥3 ngày trong Sprint 3.” **Negative:** “QA luôn chậm”; không có cohort/timestamp và tấn công vai trò.
- **Rule:** ghi cả evidence phản bác/thiếu. **Rationale:** causal map phải có khả năng sai. **Positive:** H2 chỉ giải thích 2 item. **Negative:** chỉ thu thập ví dụ ủng hộ sandbox, rồi gọi root cause chắc chắn.
- **Rule:** chọn leverage point trong sphere of control. **Rationale:** experiment phải thực thi/đo được. **Positive:** readiness + slot policy. **Negative:** “vendor phải ổn định 100%” không có owner/quyền kiểm soát.

#### Failure diagnosis

| Dấu hiệu | Nguyên nhân | Chẩn đoán/evidence | Sửa và phòng tránh |
| --- | --- | --- | --- |
| Causal map bắt đầu bằng tên người | Blame thay mechanism | Node không có event/state/timestamp | Viết lại observation; hỏi điều kiện hệ thống/process |
| “5 Whys” kết thúc ở đáp án facilitator thích | Confirmation bias | Không có alternative/disconfirming evidence | Bổ sung ≥2 hypotheses và discrimination test |
| Team tranh luận số liệu | Data definition không thống nhất | Check state policy/window/unit | Ghi data dictionary, UNKNOWN thay vì bịa |

### OUT-U09-02 — Improvement experiment và cập nhật Working Agreement

**Mapping:** OUT-U09-02 · LO9.2 · M-U09/experiment card và Working Agreement v2.

#### Định nghĩa và ranh giới

Improvement experiment là thay đổi nhỏ, timeboxed nhằm kiểm một causal/value hypothesis bằng tín hiệu và guardrail. Nó không phải danh sách “action item” mơ hồ hay policy vĩnh viễn. Working Agreement là quy tắc cộng tác do team dùng để điều phối; phiên bản v2 ghi trial rule, effective window và review/keep/change/revert condition.

#### Vấn đề, vai trò và quyết định

Team cần chọn một thay đổi có owner nhưng ownership không đồng nghĩa người đó làm tất cả. Quyết định bao gồm target cohort, intervention, baseline, leading signal, threshold, guardrail, start/end, review date và adaptation rule. Nếu signal cải thiện nhưng guardrail fail, experiment không được gọi thành công.

#### Cơ chế và mental model

Experiment card:

| Field | Câu hỏi |
| --- | --- |
| Hypothesis | Nếu thay X cho cohort Y thì signal Z đổi vì cơ chế gì? |
| Baseline | Trước thay đổi là bao nhiêu, window/unit nào? |
| Intervention | Hành vi cụ thể, ai sở hữu, kéo dài bao lâu? |
| Leading signal + threshold | Dấu hiệu sớm nào quyết định keep/change? |
| Guardrail | Điều gì không được xấu đi, đặc biệt quality/DoD? |
| Review date | Ai review evidence và quyết định keep/change/revert? |

Working Agreement v2 phải trace tới experiment ID. Sau review, rule được giữ, sửa hoặc gỡ; không để “temporary” thành policy vĩnh viễn do quên review.

#### Khi dùng, khi không dùng và trade-off

Dùng khi team có hypothesis đủ cụ thể và thay đổi nằm trong quyền kiểm soát. Không dùng experiment để biện minh bỏ DoD, thao túng cá nhân hoặc hứa causal proof từ sample nhỏ. Threshold giúp ra quyết định nhưng có thể tạo gaming; guardrail/evidence audit giảm rủi ro. Chạy quá nhiều experiment cùng lúc làm attribution yếu; ưu tiên 1–2 thay đổi có leverage.

#### Ví dụ thực tế có oracle

Experiment `EXP-09-01`:

- Hypothesis: nếu checkout item chỉ vào Verify khi readiness checklist đủ và đã reserve một sandbox slot, blocked share sẽ giảm vì hàng đợi/chuẩn bị được làm lộ sớm.
- Cohort/window: checkout items trong 5 ngày đầu Sprint 4.
- Baseline: wait sandbox 10.2/17.0 item-days = 60% ở cohort Sprint 3 (n=5; sample nhỏ).
- Intervention: trước move Verify, attach fixture readiness + reserve slot 09:00/14:00; owner Linh; team cùng thực hiện.
- Leading signal: đến ngày 5, blocked sandbox share ≤35% cho cohort.
- Guardrails: 0 item Done thiếu `DOD-NS-1.0` evidence; không tăng WIP Verify trên policy limit 1; không lưu credential.
- Review: 16:00 ngày 5; keep/change/revert dựa trên signal + guardrails + limitation.
- Working Agreement v2: rule được đánh dấu `TRIAL linked EXP-09-01`, effective ngày 1–5.

PASS khi owner/time/signal/threshold/guardrail/review/adaptation đủ; FAIL nếu chỉ ghi “cải thiện giao tiếp” hoặc nếu giảm wait bằng bỏ test.

#### Best practices

- **Rule:** một experiment kiểm một hypothesis chính. **Rationale:** giảm confounding. **Positive:** readiness+slot là một bundled mechanism được nêu rõ. **Negative:** cùng lúc đổi WIP, tool, team composition và DoD rồi không biết tác nhân.
- **Rule:** threshold + guardrail cùng quyết định. **Rationale:** speed không đổi lấy quality. **Positive:** blocked share đạt nhưng DoD gap=1 ⇒ không keep như thành công. **Negative:** tuyên bố thắng chỉ vì elapsed giảm.
- **Rule:** version Working Agreement và đặt expiry/review. **Rationale:** rule phải inspectable/reversible. **Positive:** `WA-2.0/TRIAL/EXP-09-01/day1–5`. **Negative:** thêm “always reserve” không ngày review; ceremony tích tụ.

#### Failure diagnosis

| Dấu hiệu | Nguyên nhân | Chẩn đoán/evidence | Sửa và phòng tránh |
| --- | --- | --- | --- |
| Review date đến nhưng không có decision | Owner/review forum thiếu | Experiment card không có calendar/decision owner | Gắn review vào Sprint event và expiry |
| Metric đạt, quality giảm | Guardrail thiếu/không enforced | So DoD gaps trước/sau | Đánh experiment fail/revise; khôi phục rule an toàn |
| Team không làm intervention nhất quán | Rule không quan sát được | Không có checklist/slot trace | Thu hẹp action; thêm evidence nhẹ, không giám sát cá nhân |

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### MEX-U09-01 — Evidence-to-experiment retrospective canvas

**Mode:** professional_artifact · **LO:** LO9.1, LO9.2 · **Outline:** OUT-U09-01, OUT-U09-02 · **Lab:** `LAB-U09-01/CP-U09-01`, `CP-U09-02`.

### Canvas hoàn chỉnh

| Stage | Artifact content |
| --- | --- |
| Symptom | 4/5 checkout items elapsed ≥3d in Sprint 3; source rows C-61…C-65 |
| H1 | Sandbox queue → wait; support 60% aggregate wait + event log; confidence medium; missing comparison Sprint |
| H2 | Late AC clarification → rework; support 2/5 reopened; cannot explain 3 non-reopened items |
| Leverage | Verify readiness + reserved slot, team-controlled |
| Experiment | EXP-09-01, owner Linh, days 1–5, blocked share ≤35% |
| Guardrails | 0 DoD gap; Verify WIP ≤1; no credential |
| WA update | WA-2.0 trial rule linked EXP-09-01; review 16:00 day 5 |

### Oracle

- `CAUSAL-01`: symptom có cohort/window/unit; cause nodes là mechanism, không phải người.
- `CAUSAL-02`: ≥2 hypotheses, mỗi cái có support và contradiction/unknown.
- `EXP-01`: intervention trace tới chosen hypothesis và team kiểm soát được.
- `EXP-02`: baseline/signal/threshold/owner/window/review đủ.
- `GUARD-01`: quality guardrail giữ DoD; Working Agreement có version/trial/expiry.

Kết quả mẫu: 5/5 PASS. Đây là evidence-backed hypothesis, không phải causal proof. Lab dùng dataset handoff/review mới và một outage card có thể làm hypothesis ban đầu sai.

### Mapping Material worked example → Hands-on Lab tương ứng

- **MEX-U09-01** → **LAB-U09-01/CP-U09-01** và **LAB-U09-01/CP-U09-02**; cùng phủ LO9.1, LO9.2 và yêu cầu evidence riêng theo từng checkpoint.

## 5. Thuật ngữ

- **Causal hypothesis:** giải thích có thể kiểm, chưa phải sự thật chắc chắn.
- **Disconfirming evidence:** evidence làm hypothesis yếu đi hoặc sai.
- **Leading signal:** tín hiệu sớm về direction của thay đổi.
- **Guardrail:** giới hạn bảo vệ quality/value/risk khi tối ưu signal.
- **Trial rule:** Working Agreement rule tạm thời có review/expiry.
- **Blameless:** tập trung mechanism/evidence và khả năng kiểm soát, không miễn trách nhiệm nghề nghiệp.

## 7. Nguồn tham khảo và provenance phần bổ sung

Retrospective purpose/scope bám SRC-SG20/SRC-EVENTS; evidence/experimental stance bám SRC-EBM24; flow signals bám SRC-KANBAN-SCRUM. Fixture, phép tính và artifact: **[BỔ SUNG — nguồn: SRC-PROJECT, synthetic course data]**; không tuyên bố quan hệ nhân quả production.

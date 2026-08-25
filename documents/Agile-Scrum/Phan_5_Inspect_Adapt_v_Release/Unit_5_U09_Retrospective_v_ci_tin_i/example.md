# Unit U09: Retrospective và cải tiến đội — Ví dụ và nghiên cứu tình huống

## 🎯 Learning Outcomes liên quan

> **Case:** CASE-U09-01 · **LO:** LO9.1, LO9.2 · **Outline:** OUT-U09-01, OUT-U09-02 · **Mức xác thực:** simulated

## Case Study 01 — Reopen tăng vì acceptance examples đến muộn

### 1. Ticket và tiêu chí thành công

NovaShop có 3/6 PBI giỏ hàng bị reopen sau review. Team cần phân biệt symptom/cause, không đổ lỗi BA/QA, và tạo một experiment có thể review trong Sprint kế. Thành công khi causal map có competing hypotheses/evidence và Working Agreement trial không hạ DoD.

### 2. Input, baseline và constraints

| PBI | AC examples ready | Dev start | First review | Reopen reason |
| --- | --- | --- | --- | --- |
| CART-71 | D0 | D1 | D2 | none |
| CART-72 | D2 | D1 | D3 | invalid promo boundary |
| CART-73 | D0 | D1 | D3 | none |
| CART-74 | D3 | D1 | D4 | stacked discount rule |
| CART-75 | D0 | D2 | D4 | browser-specific state |
| CART-76 | D2 | D1 | D4 | zero-total cart rule |

Event log: CART-72/74/76 bắt đầu trước khi boundary examples available và đều reopen vì business boundary; CART-75 reopen vì browser state dù examples đã sẵn. Constraint: sample n=6; timestamps ngày, không có hour-level data; không thu thập metric cá nhân.

### 3. Phân tích lựa chọn

Symptom là 3/6 reopen vì business boundaries, không phải “50% Developer làm sai”. H1 “boundary examples đến sau start tạo assumption/rework” được 3 rows hỗ trợ. H2 “peer review quá muộn” có thể đóng góp nhưng dữ liệu review day gần nhau; chưa đủ tách riêng. CART-75 là counter-example cho claim “mọi reopen do AC”. Kết luận đúng là H1 có confidence medium trong cohort, không phải root cause toàn hệ thống.

### 4. Artifact triển khai

#### Evidence/causal map

`Examples unavailable before start → Developers tự điền boundary assumptions → review phát hiện mismatch → reopen`.

Support: CART-72/74/76. Counter/alternative: CART-75 khác mechanism; CART-71/73 không reopen khi examples ready. Missing: item complexity, hour-level waiting.

#### Experiment `EXP-CART-01`

| Field | Value |
| --- | --- |
| Hypothesis | Nếu PBI có high-risk boundary example trước khi vào In Progress thì business-boundary reopen giảm vì assumptions được inspect sớm |
| Cohort/window | Cart/promotion PBIs, first 5 working days Sprint 5 |
| Baseline | 3/6 PBIs reopen vì business boundary in Sprint 4 |
| Intervention | PO + Developer + tester làm 15-minute example review cho high-risk PBI trước start; owner Hạnh; evidence = example-ready tag |
| Leading threshold | ≤1 business-boundary reopen trong cohort by day 5 |
| Guardrails | 0 DoD bypass; preparation ≤20 minutes/PBI; WIP policy unchanged |
| Review | Day 5, 16:00; keep/change/revert with sample limitation |

Working Agreement `WA-2.0`: trial rule linked `EXP-CART-01`, effective days 1–5, expires after review unless explicitly kept.

### 5. Output mong đợi và verification

- `C9-01`: symptom has cohort/window; 3/6 value reproduces from rows.
- `C9-02`: H1 support and CART-75 counter-example are explicit; no person is labeled cause.
- `C9-03`: experiment trace to H1 and has owner/window/baseline/threshold.
- `C9-04`: guardrails prevent DoD bypass and excessive ceremony.
- `C9-05`: WA rule is versioned, trial, linked, reviewable/reversible.

Kết quả case: 5/5 PASS.

### 6. Failure modes, trade-off và giới hạn

- Nếu team gọi “AC muộn” là proven root cause, sample/counter-example bị bỏ qua; hạ claim thành medium-confidence hypothesis.
- Nếu review examples cho mọi PBI, ceremony cost có thể tăng; target high-risk boundaries và guardrail ≤20 phút.
- Nếu reopen giảm nhưng items không start vì readiness gate quá nặng, signal chưa đủ; inspect throughput/Goal impact trong review.
- Data theo ngày không cho biết exact waiting time; không bịa giờ để làm causal chain đẹp hơn.

### 7. Bài học chuyển giao

Retrospective tốt biến disagreement thành hypotheses có khả năng sai, rồi dùng experiment nhỏ để học. Lab dùng review-handoff dataset khác và change card outage để buộc học viên sửa causal claim/experiment.

## Provenance của các case

- **SRC-SG20** — [The Scrum Guide, November 2020](https://scrumguides.org/scrum-guide.html).
- **SRC-EVENTS** — [Introduction to the Scrum Events](https://www.scrum.org/resources/introduction-scrum-events), snapshot 2026-08-25.
- **SRC-EBM24** — [Evidence-Based Management Guide, May 2024](https://www.scrum.org/resources/online-evidence-based-management-guide).
- **SRC-KANBAN-SCRUM** — [Kanban Guide for Scrum Teams, 2021](https://www.scrum.org/resources/kanban-guide-scrum-teams).
- Fixture CASE-U09-01: **[BỔ SUNG — nguồn: SRC-PROJECT/synthetic NovaShop course data]**.

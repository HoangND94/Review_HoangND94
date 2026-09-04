# Assignment B02 — Shift Quality Analyzer

**90 phút · độc lập.** Viết C17 CLI nhận tối đa 24 integer synthetic readings. Phân vào `LOW`, `NORMAL`, `HIGH` bằng biểu thức rõ ràng; in count mỗi nhóm, first index của HIGH và thông báo `NO-HIGH` nếu không có. Dừng parse khi gặp `--end`; token sau marker không được đọc.

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASG-B02-01 |
| Độ khó / Bloom | Intermediate / Apply |
| Mức xác thực | simulated |
| Liên kết project | NOT_APPLICABLE — assessment độc lập theo Unit |

## 🎯 Learning Outcomes được đánh giá

`ADVC-H1SD`: kiểm soát collection bounded và luồng quyết định/lặp với output kiểm chứng được.

## 🧠 Khái niệm và best practices được đánh giá

| Concept / LO | Scenario, rule/rationale, deliverable | tiêu chí kiểm chứng |
| --- | --- | --- |
| Array/memory · H1SD | readings[24] chỉ truy cập với `index < count`; capacity khác count. | AT-01 |
| Expression/if/switch · H1SD | Mỗi reading đúng một quality class; `switch` không fall-through ngoài ý muốn. | AT-02 |
| Loop/break · H1SD | `--end` là termination contract, không phải data; output có first-high/no-high. | AT-01, AT-03 |

## 🧭 Bối cảnh, điều kiện và requirements

Shift lead cần summary synthetic mới, không phải batch sample của Lab. **Tiên quyết:** Lab B02. **Môi trường:** ISO C17 strict build. **Starter:** không có code; chỉ command-line data synthetic.

### Functional requirements

- FR-01: parse tối đa 24 readings đến `--end`.
- FR-02: report ba bucket và first HIGH/`NO-HIGH` xác định.
- FR-03: malformed/capacity overflow fail không partial stdout.

### Non-functional requirements / constraints

NFR-01 strict no-warning; NFR-02 loop invariant được nêu trong README. Không dùng dynamic allocation/file I/O và không nộp walkthrough.

## Deliverables / acceptance

Nộp source, README, evidence cho no-high, mixed values, capacity boundary và invalid token. `AT-01`: loop không vượt count; `AT-02`: `switch` không fall-through ngoài ý muốn; `AT-03`: invalid input stdout rỗng, exit khác 0; strict build pass.

## Rubric

| Array/bounds 30 | Decision logic 25 | Loop/invariant 25 | Tests/evidence 20 |
|---:|---:|---:|---:|
| **Tổng 100** |  |  |  |

## 🧪 Submission, validation và provenance

Nộp `ASG-B02-01/` gồm source, README, evidence (command/exit/stdout/stderr) cho no-high, mixed, capacity, malformed. Sources: `material.md`, `example.md`, `assets/b02_array_flow_demo.c`. `[SUY DIỄN — từ kiến thức đã huấn luyện]` shift scenario synthetic.

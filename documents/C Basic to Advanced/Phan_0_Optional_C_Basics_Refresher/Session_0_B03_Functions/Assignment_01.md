# Assignment B03 — Calibration Function API

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASG-B03-01 · Intermediate · Apply/Analyze · simulated |
| Liên kết project | NOT_APPLICABLE — assessment độc lập theo Unit |

## 🎯 Learning Outcomes được đánh giá

`ADVC-H1SD`: thiết kế, hiện thực và kiểm chứng API C17 có contract input/output/lifetime rõ ràng.

## 🧠 Khái niệm và best practices được đánh giá

| Concept / LO | Contract đánh giá | tiêu chí kiểm chứng |
| --- | --- | --- |
| prototype/scope · H1SD | Header công bố parser/calculation API trước implementation. | strict build |
| value/reference/array · H1SD | `const` input, output pointer có failure policy, count bounded. | valid/null/empty |
| recursion/stack · H1SD | checksum có base case và max-size guard. | boundary/over-limit |

## 🧭 Bối cảnh, điều kiện và yêu cầu

Calibration tool synthetic cần module thay cho pipeline Lab. **Tiên quyết:** Lab B03. **Môi trường:** ISO C17, strict flags; không starter code/secret/PII.

### Functional requirements

- FR-01: parse/validate tối đa 20 samples, min/max/average và checksum bounded.
- FR-02: một API xuất nhiều result qua output pointers, null/empty/over-limit có status xác định.
- FR-03: header, implementation và main tách translation unit.

### Non-functional requirements và phạm vi

NFR-01 no-warning strict build; NFR-02 error path không partial result. Ngoài phạm vi: nested function, macro-function cho logic chính, dynamic plugin.

**90 phút · độc lập.** Thiết kế module C17 xử lý tối đa 20 calibration samples: API parse/validate, average, min/max và checksum recursive bounded. Một API phải trả hai result qua output pointer; mọi input pointer/output pointer có precondition và failure policy trong header.

**Acceptance:** valid fixture đúng; null/empty/over-limit có status xác định và không partial result; source tách `.h/.c/main.c`, strict build. Không dùng macro function cho logic chính hoặc nested function.

| API/prototype & const 30 | Correctness 30 | Error/lifetime contract 25 | Evidence/README 15 |
|---:|---:|---:|---:|
| **Tổng 100** |  |  |  |

## 📦 Submission · 🧪 Validation · 📚 Provenance

Nộp `ASG-B03-01/` (source, header, README, transcript valid/null/empty/over-limit). Sources: `material.md`, `example.md`, `assets/b03_functions_demo.c`; `[SUY DIỄN — từ kiến thức đã huấn luyện]` calibration scenario synthetic.

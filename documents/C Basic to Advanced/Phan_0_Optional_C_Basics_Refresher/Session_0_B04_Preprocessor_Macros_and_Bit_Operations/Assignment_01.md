# Assignment B04 — Config Word Editor

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASG-B04-01 · Intermediate · Apply · simulated |
| Liên kết project | NOT_APPLICABLE — assessment độc lập theo Unit |

## 🎯 Learning Outcomes được đánh giá

`ADVC-H1SD`: triển khai API flag/field portable và kiểm chứng contract bit-level.

## 🧠 Khái niệm và best practices được đánh giá

| Concept / LO | Contract đánh giá | tiêu chí kiểm chứng |
| --- | --- | --- |
| preprocessor/macro · H1SD | header guard, macro parenthesized hoặc function evaluate một lần. | preprocess + strict build |
| bit mask/shift · H1SD | validate index/width/value trước shift; giữ bit lân cận. | golden sequence |
| directives vs runtime · H1SD | README phân biệt `#if` và `if`. | review evidence |

## 🧭 Bối cảnh, điều kiện và yêu cầu

Config image là `uint32_t` trong memory, không phải peripheral thật. **Tiên quyết:** Lab B04. **Môi trường:** ISO C17 strict flags; input synthetic.

### Functional requirements

- FR-01: set/clear/read bit và read/write hai field công bố.
- FR-02: invalid bit/field/value fail trước operation.
- FR-03: in output deterministic cho golden sequence.

### Non-functional requirements và phạm vi

NFR-01 strict no-warning; NFR-02 không hardware address/MMIO/extension target. Đề không cung cấp code hay walkthrough.

**75 phút · độc lập.** Viết CLI chỉnh sửa một config word `uint32_t`: bật/tắt/read bit và gán hai field có width/shift công bố. Input bit/field/value ngoài range phải fail trước mọi shift. Dùng header guard, named constants/macro an toàn hoặc static function hợp lý; giải thích khác biệt compile-time directive và runtime decision.

**Acceptance:** golden sequence giữ bit không liên quan; invalid bit/field stdout rỗng; preprocessor/include không lỗi; strict build pass. Không truy cập hardware address.

| Macro/preprocessor 25 | Bit correctness 35 | Validation 25 | Evidence 15 |
|---:|---:|---:|---:|
| **Tổng 100** |  |  |  |

## 📦 Submission · 🧪 Validation · 📚 Provenance

Nộp `ASG-B04-01/`: source, README, golden/invalid transcripts. Sources: `material.md`, `example.md`, `assets/b04_macro_bits_demo.c`; `[SUY DIỄN — từ kiến thức đã huấn luyện]` config editor synthetic.

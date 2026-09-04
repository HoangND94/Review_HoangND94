# Assignment B09 — Harden a Record Decoder

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASG-B09-01 · Intermediate · Analyze/Apply · simulated |
| Liên kết project | NOT_APPLICABLE — assessment độc lập theo Unit |

## 🎯 Learning Outcomes được đánh giá
`ADVC-H3SD`: phát hiện/loại defect C bằng representation, bounds, ownership và tiêu chí kiểm chứng tái lập.

## 🧠 Khái niệm và best practices được đánh giá
| Concept / LO | Contract, deliverable | tiêu chí kiểm chứng |
| --- | --- | --- |
| alignment/packing · H3SD | byte-wise little-endian decode, không raw struct cast | golden bytes |
| overflow/string/const · H3SD | validate length/range/capacity trước operation | malformed/boundary |
| allocation/cleanup · H3SD | cleanup matrix và failure outcome | error-path evidence |

## 🧭 Điều kiện, yêu cầu và phạm vi
Tiên quyết Lab B09; ISO C17 strict build; record synthetic. FR: decoder length/label/u16, reject malformed/failure, document cleanup. NFR: no partial success, no warning; sanitizer only supplementary if available. Ngoài phạm vi: network/file format extension. Không walkthrough.

**105 phút · độc lập.** Viết decoder cho record synthetic gồm length, label bounded và 16-bit little-endian value. Từ chối length quá giới hạn, thiếu NUL/byte, arithmetic overflow và allocation failure. Không cast byte buffer thành struct; có cleanup matrix và test defect matrix.

**Acceptance:** golden + 4 negative classes; const API; macro/expression không side-effect bất ngờ; no leak trên paths đã chạy nếu tool hỗ trợ; strict build.

| Boundary/representation 30 | Error/ownership 30 | Defect tests 25 | Evidence 15 |
|---:|---:|---:|---:|
| **Tổng 100** |  |  |  |

## 📦 Submission · 🧪 Validation · 📚 Provenance
Nộp `ASG-B09-01/`: source, cleanup/defect matrix, README, golden + 4 negative transcripts. Sources: `material.md`, `example.md`, `assets/b09_defects_demo.c`; `[SUY DIỄN — từ kiến thức đã huấn luyện]` decoder synthetic.

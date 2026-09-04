# Assignment B08 — Optimize Only After Proof

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASG-B08-01 · Intermediate · Analyze/Evaluate · simulated |
| Liên kết project | NOT_APPLICABLE — assessment độc lập theo Unit |

## 🎯 Learning Outcomes được đánh giá
`ADVC-H3SD`: dùng correctness tiêu chí kiểm chứng, measurement và trade-off để quyết định tối ưu.

## 🧠 Khái niệm và best practices được đánh giá
| Concept / LO | Contract, deliverable | tiêu chí kiểm chứng |
| --- | --- | --- |
| baseline/correctness · H3SD | golden output trước/sau candidate | `-O0`/`-O2` compare |
| transformation · H3SD | một optimization có rationale/limitation | source review |
| profile/size/measurement · H3SD | ≥3 measurements cùng condition, size report | report evidence |

## 🧭 Điều kiện, yêu cầu và phạm vi
Tiên quyết Lab B08; ISO C17 + tool sẵn có. FR: tạo baseline, tối đa một transformation, quyết định keep/drop. NFR: output invariant, environment/flags recorded; không claim universal speedup. Ngoài phạm vi: hardware tuning. Không walkthrough.

**90 phút · độc lập.** Với program synthetic có workload cho sẵn, đề xuất và hiện thực tối đa một tối ưu (loop invariant, strength reduction, hoặc compiler option rationale). Nộp baseline/changed source, exact correctness tiêu chí kiểm chứng, ít nhất ba lần đo cùng điều kiện, size comparison và quyết định giữ/bỏ. Không chấm theo “nhanh nhất”.

**Acceptance:** output mọi build giống golden output; flags/compiler/environment được ghi; trade-off size/speed/readability nêu rõ; không suy rộng kết quả ngoài workload.

| Correctness tiêu chí kiểm chứng 35 | Measurement discipline 25 | Transformation/rationale 25 | Evidence/report 15 |
|---:|---:|---:|---:|
| **Tổng 100** |  |  |  |

## 📦 Submission · 🧪 Validation · 📚 Provenance
Nộp `ASG-B08-01/` baseline/changed source, report, evidence. Sources: `material.md`, `example.md`, `assets/b08_optimization_demo.c`; `[SUY DIỄN — từ kiến thức đã huấn luyện]` workload synthetic.

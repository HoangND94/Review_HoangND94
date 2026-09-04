# Assignment B06 — Incident Index

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASG-B06-01 · Intermediate · Analyze/Apply · simulated |
| Liên kết project | NOT_APPLICABLE — assessment độc lập theo Unit |

## 🎯 Learning Outcomes được đánh giá
`ADVC-H1SD`: chọn và kiểm chứng structure/algorithm theo workload, invariant và ownership.

## 🧠 Khái niệm và best practices được đánh giá
| Concept / LO | Contract, deliverable | tiêu chí kiểm chứng |
| --- | --- | --- |
| array/list/hash · H1SD | design note so sánh 2 lựa chọn cho lookup-heavy workload | review rationale |
| collection/invariant · H1SD | unique-ID, ownership và operation contract | empty/duplicate/full |
| search/sort/complexity · H1SD | correctness trước claim cost, comparator an toàn nếu dùng | missing/find tests |

## 🧭 Điều kiện, yêu cầu và phạm vi
**Tiên quyết:** Lab B06; **môi trường:** ISO C17 strict build; **starter:** không có code, data synthetic. FR-01 chọn representation tối đa 64 IDs; FR-02 add/find/remove theo contract; FR-03 preserve invariant/cleanup. NFR: strict no-warning, evidence có command/exit/stdout/stderr. Ngoài phạm vi: benchmark timing và structure không được chọn. Đề không chứa walkthrough.

**105 phút · độc lập.** Chọn array sorted, linked list, hoặc hash table cho index tối đa 64 incident IDs theo workload được cho (lookup nhiều hơn insert). Hiện thực add/find/remove hoặc giải thích rõ operation không hỗ trợ; bảo toàn unique-ID invariant và ownership. Gửi design note so sánh ít nhất hai lựa chọn.

**Acceptance:** duplicate, empty, missing, full/boundary và cleanup; correctness trước claim performance; strict build.

| Workload/design rationale 25 | Invariant/ownership 30 | Operations/tiêu chí kiểm chứngs 30 | Evidence 15 |
|---:|---:|---:|---:|
| **Tổng 100** |  |  |  |

## 📦 Submission · 🧪 Validation · 📚 Provenance
Nộp `ASG-B06-01/`: source, design note, README, evidence duplicate/empty/missing/full. Sources: `material.md`, `example.md`, `assets/b06_dsa_demo.c`; `[SUY DIỄN — từ kiến thức đã huấn luyện]` incident index synthetic.

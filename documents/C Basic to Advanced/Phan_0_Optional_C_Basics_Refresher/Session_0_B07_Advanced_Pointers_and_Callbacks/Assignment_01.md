# Assignment B07 — Alert Subscription Filter

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASG-B07-01 · Intermediate · Apply/Analyze · simulated |
| Liên kết project | NOT_APPLICABLE — assessment độc lập theo Unit |

## 🎯 Learning Outcomes được đánh giá
`ADVC-H1SD`: kiểm chứng function pointer/callback/context với lifetime và ownership rõ.

## 🧠 Khái niệm và best practices được đánh giá
| Concept / LO | Contract, deliverable | tiêu chí kiểm chứng |
| --- | --- | --- |
| pointer/lifetime · H1SD | ownership output + context lifetime note | empty/null paths |
| function pointer · H1SD | exact typedef, không cast signature | strict build/review |
| callback/context · H1SD | 2 predicates không global mutable state | many/no-match |

## 🧭 Điều kiện, yêu cầu và phạm vi
**Tiên quyết:** Lab B07; ISO C17 strict build; input alert synthetic. FR-01 lọc mảng bằng callback/context; FR-02 contract null callback/output; FR-03 caller cleanup output. NFR: no warning, deterministic evidence. Ngoài phạm vi: thread, plugin, global-state solution; không có walkthrough.

**75 phút · độc lập.** Xây API lọc mảng alert synthetic qua callback có context. Cung cấp hai callback (severity threshold, required flags) nhưng không dùng global state. Contract phải chỉ ra ownership của output, lifetime context và hành vi khi callback/output pointer null.

**Acceptance:** empty/many/no match/null invalid; signature type-correct không cast function pointer; caller giải phóng đúng output; strict build + evidence.

| Pointer/lifetime 30 | Callback/context 30 | Correctness/error paths 25 | Evidence 15 |
|---:|---:|---:|---:|
| **Tổng 100** |  |  |  |

## 📦 Submission · 🧪 Validation · 📚 Provenance
Nộp `ASG-B07-01/` source, API/ownership note, README, transcripts. Sources: `material.md`, `example.md`, `assets/b07_callbacks_demo.c`; `[SUY DIỄN — từ kiến thức đã huấn luyện]` alert scenario synthetic.

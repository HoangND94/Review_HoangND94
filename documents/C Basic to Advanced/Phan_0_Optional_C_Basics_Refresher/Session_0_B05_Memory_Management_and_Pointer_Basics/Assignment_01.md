# Assignment B05 — Resizable Reading Buffer

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASG-B05-01 · Intermediate · Apply/Analyze · simulated |
| Liên kết project | NOT_APPLICABLE — assessment độc lập theo Unit |

## 🎯 Learning Outcomes được đánh giá

`ADVC-H1SD`: thiết kế vector owned không làm lộ lifetime hoặc lỗi memory trong fixture.

## 🧠 Khái niệm và best practices được đánh giá

| Concept / LO | Contract đánh giá | tiêu chí kiểm chứng |
| --- | --- | --- |
| object/lifetime · H1SD | ownership table cho data/struct/return paths. | review + cleanup tests |
| allocation/realloc · H1SD | temporary pointer; failure giữ state cũ. | injected/represented failure |
| pointer arithmetic · H1SD | index trong `size`, không dereference one-past. | boundary tests |

## 🧭 Bối cảnh, điều kiện và requirements

Reading buffer synthetic có capacity 64, API khác Lab. **Tiên quyết:** Lab B05. **Môi trường:** ISO C17 strict flags; sanitizer nếu có, không bắt buộc tool unavailable.

### Functional requirements

- FR-01: init/append/get/clear-free với status.
- FR-02: append fail preserve size/data/capacity cũ.
- FR-03: empty/full/invalid index có behavior xác định.

### Non-functional requirements và phạm vi

NFR-01 cleanup không leak/double-free trên paths đã chạy; NFR-02 strict build. Ngoài phạm vi: file/network/thread.

**90 phút · độc lập.** Tạo module vector chứa `int` với init, append, get, clear/free. Capacity tối đa 64; append sau allocation failure phải báo lỗi và preserve size/data đang có. Nộp ownership table, C17 source và evidence empty/normal/capacity/failure.

**Acceptance:** không dereference null/one-past; `realloc` dùng temporary; cleanup một lần cho mỗi allocation; strict build (sanitizer evidence nếu môi trường hỗ trợ).

| Ownership/lifetime 30 | Resize & failure atomicity 35 | Bounds/API 20 | Evidence 15 |
|---:|---:|---:|---:|
| **Tổng 100** |  |  |  |

## 📦 Submission · 🧪 Validation · 📚 Provenance

Nộp `ASG-B05-01/` source, ownership table, README, evidence empty/normal/boundary/failure. Sources: `material.md`, `example.md`, `assets/b05_memory_demo.c`; `[SUY DIỄN — từ kiến thức đã huấn luyện]` buffer synthetic.

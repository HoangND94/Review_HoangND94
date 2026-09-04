# Assignment B01 — Configurable Device Status Record

**Thời lượng:** 75 phút · **Mức:** Apply/Analyze.

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASG-B01-01 |
| Độ khó / Bloom | Intermediate / Apply, Analyze |
| Mức xác thực | simulated |
| Liên kết project | NOT_APPLICABLE — assessment độc lập theo Unit |

## 🎯 Learning Outcomes được đánh giá

`ADVC-H1SD`: mô hình hóa và kiểm chứng typed record C17 an toàn. Bằng chứng: model, validation transcript và strict build.

## 🧠 Khái niệm và best practices được đánh giá

| Concept / LO | Scenario, rule/rationale, deliverable | tiêu chí kiểm chứng |
| --- | --- | --- |
| Basic/fixed-width types, casting · H1SD | Input config đi qua range check trước cast để tránh narrowing loss. | AT-01, AT-02 |
| enum/struct/union · H1SD | Chỉ đọc union member khớp discriminator; model record có nhãn. | AT-01, AT-03 |
| storage/pointer variable · H1SD | Không dùng pointer để né ownership/lifetime; giải thích duration của fields. | AT-03 |

## 🧭 Bối cảnh và change request

Tạo device-status record synthetic có state, flags và payload thay đổi; khác ticket Lab ở input/state table. Không có walkthrough hay source tham khảo được phép sao chép.

## 🧰 Điều kiện, yêu cầu và ràng buộc

**Tiên quyết:** Lab B01. **Môi trường:** ISO C17, strict flags. **Starter:** không có code; input tự tạo và không chứa PII.

### Functional requirements

- FR-01: validate ID/state/flags/payload tag rồi in bản tóm tắt có nhãn.
- FR-02: hỗ trợ đúng hai payload types công bố trong README.
- FR-03: từ chối mọi value/tag không hợp lệ mà không in success.

### Non-functional requirements

- NFR-01: no warning với strict build; NFR-02: type/format output nhất quán.

**Ngoài phạm vi:** persistence, network, hardware access và union type-punning.

## Nhiệm vụ

Thiết kế CLI nhận `id`, state, flags và payload cho một status record synthetic. State chỉ nhận ba giá trị đã công bố; flags là byte không dấu; payload có hai loại được phân biệt bằng enum. In bản tóm tắt có nhãn và từ chối mọi value/tag ngoài contract. Giải thích trong README lựa chọn type, cast và lifetime của mỗi field.

## Deliverables và acceptance

- C17 source + README + transcript; strict flags bắt buộc.
- `AT-01`: hai payload hợp lệ cho output xác định.
- `AT-02`: state, flag và tag ngoài range không tạo output success.
- `AT-03`: không đọc union không được tag và format fixed-width nhất quán.

## Rubric

| Model type/enum/struct/union | Validation + cast | Output/evidence | Documentation | Tổng |
|---:|---:|---:|---:|---:|
| 35 | 30 | 20 | 15 | 100 |

## 🧪 Cách xác minh và provenance

Nộp `ASG-B01-01/` gồm source, README, command + transcript cho 2 valid/3 invalid cases. Sources: `material.md`, `example.md`, `assets/b01_variables_demo.c`. `[SUY DIỄN — từ kiến thức đã huấn luyện]` status record là scenario synthetic.

# Assignment B10 — Audit-file Validator

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASG-B10-01 · Intermediate · Apply/Analyze · simulated |
| Liên kết project | NOT_APPLICABLE — assessment độc lập theo Unit |

## 🎯 Learning Outcomes được đánh giá
`ADVC-H1SD`, `ADVC-H3SD`: xây bounded stream pipeline, exact diagnostics và checksum/file tiêu chí kiểm chứng.

## 🧠 Khái niệm và best practices được đánh giá
| Concept / LO | Contract, deliverable | tiêu chí kiểm chứng |
| --- | --- | --- |
| FILE/stream/position · H1SD | `fopen`/read/close one time, distinguish EOF/I/O | missing/valid CSV |
| text/binary/fflush · H1SD | write→flush→close→reopen byte contract | round-trip |
| parser/S-record · H3SD | bounded profile, no partial success | malformed/checksum |

## 🧭 Điều kiện, yêu cầu và phạm vi
Tiên quyết Lab B10; ISO C17 strict build; fixtures local/synthetic. FR: validate CSV ≤32, optional report write, validate S1/S9 checksum. NFR: exact stderr/exit, no starter changes. Ngoài phạm vi: flashing, hardware/network; không walkthrough.

**120 phút · độc lập.** Xây C17 CLI đọc audit CSV local (header `id,value,flags`, tối đa 32 rows) và option ghi report text/binary vào folder output do người chạy tạo. Reject header/field/duplicate/overlong line; không partial success. Thêm validator S-record giới hạn S1/S9, checksum lỗi có diagnostic ổn định. Không sửa fixture/source assets và không dùng external hardware.

**Acceptance:** valid CSV, malformed field, duplicate, overlong, valid S-record, bad checksum và write→flush→close→reopen; mọi stream đóng đúng một lần, stdout/stderr/exit code ghi trong evidence; strict build.

| Stream/file contract 25 | Parser/diagnostics 30 | Write-reopen/tiêu chí kiểm chứngs 25 | Safety/evidence 20 |
|---:|---:|---:|---:|
| **Tổng 100** |  |  |  |

## 📦 Submission · 🧪 Validation · 📚 Provenance
Nộp `ASG-B10-01/`: source, README, logs valid/negative/roundtrip. Sources: `material.md`, `example.md`, `assets/b10_file_demo.c`, fixtures; `[SUY DIỄN — từ kiến thức đã huấn luyện]` audit context synthetic.

# Hands-on Lab B01 — Typed Diagnostic Record

**Thời lượng:** 90 phút · **Hình thức:** guided with fading · **Tham chiếu:** `assets/b01_variables_demo.c`, `CASE-B01-01`.

## Mục tiêu / DoD

Tạo record chẩn đoán với integer fixed-width, `enum`, `struct`, bit flags, cast có kiểm tra và một `union` chỉ dùng khi tag hợp lệ. DoD: strict build pass; valid record in đúng; tag/cast ngoài range bị từ chối.

## Checkpoint 1 — Model dữ liệu

1. **Why:** type là một phần của contract, không chỉ là số byte.
2. **Action:** tạo `diagnostic_t` gồm ID `uint32_t`, severity `enum`, flags `uint8_t` và payload tagged; ghi rõ giá trị enum hợp lệ.
3. **Giải thích:** chỉ đọc member union tương ứng tag; không dùng union để “ép kiểu” tùy tiện.

**Verify:** build strict, lưu `build.log`. **Expected:** exit 0/no warnings.

## Checkpoint 2 — Convert và format

1. **Why:** cast hẹp có thể làm mất dữ liệu.
2. **Action:** viết hàm chuyển `long` sang severity/flag sau range check; dùng format macro từ `<inttypes.h>` khi in fixed-width values.
3. **Giải thích:** storage class chỉ dùng khi lifetime/linkage cần thiết, không thêm `static` để “tối ưu”.

**Verify:** valid `id=42,severity=2,flags=3` in record rõ field; severity `9` bị từ chối với stderr ổn định. **Evidence:** hai transcript.

## Checkpoint 3 — Variation, troubleshooting, reset

1. **Why:** record mới có payload text hoặc numeric cần tag thật.
2. **Action:** thêm loại payload thứ hai và test sai tag.
3. **Giải thích:** tag sai là lỗi input/contract, không phải lý do đọc member khác.

**Expected:** sai tag không dereference/format payload. **Troubleshooting:** output số rất lớn thường do signed/unsigned format mismatch. **Reset:** chỉ xóa `lab01_scratch`.

## Nộp

Code, data model note, build command và evidence valid/invalid; chuẩn bị cho Assignment B01.

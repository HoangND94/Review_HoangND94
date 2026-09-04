# Hands-on Lab B03 — Portable Function Pipeline

**105 phút · guided with fading · Tham chiếu:** `assets/b03_functions_demo.c`, `CASE-B03-01`.

## DoD

Tách pipeline parse → transform → report thành prototype/header và implementation; dùng pass-by-value và output pointer đúng mục đích; xử lý mảng qua pointer + count; recursion có base case đo được.

## Checkpoint 1 — Interface trước body

1. **Why:** function contract giảm coupling.
2. **Action:** viết header với input `const`, output pointers và status `enum`; compile từng translation unit.
3. **Giải thích:** C không có nested function portable; “local function” là scope/linkage trong translation unit.

**Verify:** linker tạo binary, không implicit declaration. **Evidence:** build log.

## Checkpoint 2 — Value/reference/array

1. **Why:** caller phải biết object nào bị thay đổi.
2. **Action:** một hàm nhận value, một hàm update output qua pointer sau null-check, một hàm aggregate array với length.
3. **Giải thích:** return một status và đưa nhiều result qua output parameters có contract failure rõ.

**Verify:** test valid + null output path; valid output đúng và error path không sửa output đã khởi tạo.

## Checkpoint 3 — Recursion có guard

1. **Why:** recursion tiêu thụ stack.
2. **Action:** viết recursive checksum cho mảng tối đa 16 item, base case `count==0`; từ chối count vượt limit.
3. **Giải thích:** inline là hint/semantics linkage, không phải cam kết speed; macro-like function không thay thế type checking.

**Troubleshooting:** stack overflow thường do thiếu base/progress. **Reset:** xóa scratch.

**Học tiếp:** `Assignment_01.md` đánh giá API mới mà không cung cấp bước giải.

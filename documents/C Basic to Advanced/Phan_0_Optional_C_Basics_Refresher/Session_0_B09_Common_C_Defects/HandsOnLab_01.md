# Hands-on Lab B09 — Defect Triage with tiêu chí kiểm chứngs

**105 phút · guided with fading · Tham chiếu:** `assets/b09_defects_demo.c`, `CASE-B09-01`.

## DoD

Sửa hoặc cô lập defect trên byte parsing, signedness, macro/precedence, string, const và cleanup; mỗi claim có test/tiêu chí kiểm chứng. Strict build; sanitizer/Valgrind chỉ là evidence bổ sung khi sẵn có.

## Checkpoint 1 — Decode và arithmetic

1. **Why:** raw struct cast có thể sai alignment/endian/aliasing.
2. **Action:** decode byte-by-byte; kiểm overflow/underflow trước arithmetic và range trước cast.
3. **Giải thích:** signed/unsigned conversion có thể đổi comparison.

**Verify:** golden bytes `{0x34,0x12}` → 4660; malformed/boundary reject.

## Checkpoint 2 — Expression/string/const

1. **Why:** macro precedence và string terminator gây lỗi lặng.
2. **Action:** parenthesize macro, dùng `sizeof` đúng array scope, giữ destination capacity và NUL; phân biệt pointer-to-const với const pointer.
3. **Giải thích:** warning sạch không thay contract review.

**Verify:** boundary string và side-effect macro negative test.

## Checkpoint 3 — Ownership/reset

1. **Why:** memory leak thường nằm ở error path.
2. **Action:** vẽ cleanup matrix cho mọi return; test allocation failure.
3. **Giải thích:** free chỉ object owned, đúng một lần.

**Troubleshooting:** sanitizer report → map stack trace tới owner/length invariant; không suppress lỗi. **Reset:** xóa scratch.

**Học tiếp:** `Assignment_01.md` dùng format record khác và defect matrix riêng.

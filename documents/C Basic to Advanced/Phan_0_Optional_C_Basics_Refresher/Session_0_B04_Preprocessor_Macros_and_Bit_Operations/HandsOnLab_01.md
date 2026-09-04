# Hands-on Lab B04 — Portable Flag Register Image

**90 phút · guided with fading · Tham chiếu:** `assets/b04_macro_bits_demo.c`, `CASE-B04-01`.

## DoD

Tạo API thao tác `uint32_t register_image` trong memory: set/clear/read một bit và write/read field có mask/shift. Không dùng địa chỉ thiết bị/MMIO; strict build và tiêu chí kiểm chứng chính xác pass.

## Checkpoint 1 — Macro hygiene

1. **Why:** preprocessor thay token, không kiểm kiểu.
2. **Action:** định nghĩa object-like constants và macro mask với mọi operand/result có ngoặc; không truyền `i++` vào macro function-like.
3. **Giải thích:** `#if` là conditional compilation, tách khỏi `if` runtime.

**Verify:** preprocess (`gcc -E`) và build strict; evidence lưu output.

## Checkpoint 2 — Bit contract

1. **Why:** shift/mask sai dễ phá bit lân cận.
2. **Action:** validate bit index `< 32`, field width/shift không vượt 32; thao tác trên unsigned `uint32_t`.
3. **Giải thích:** SET/CLEAR là read-modify-write trên image local, không phải peripheral access.

**Verify:** set rồi clear bit 3; write field 3-bit tại shift 8, kiểm neighboring bits không đổi.

## Checkpoint 3 — Variation / reset

1. **Why:** invalid range phải bị chặn trước shift.
2. **Action:** thêm parser command cho `--set`, `--clear`, `--field`.
3. **Giải thích:** macro `MIN` không an toàn với side effect; dùng function khi cần evaluate một lần.

**Troubleshooting:** field ngoài range làm mất bit → kiểm value <= mask trước shift. **Reset:** xóa scratch.

**Học tiếp:** `Assignment_01.md` dùng config word và field khác.

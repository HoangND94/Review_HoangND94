# Hands-on Lab B07 — Context-aware Callback Filter

**90 phút · guided with fading · Tham chiếu:** `assets/b07_callbacks_demo.c`, `CASE-B07-01`.

## DoD

Tạo `filter(items,count,predicate,context,out)` với function-pointer signature đúng, immutable context và ownership output minh bạch. Null callback/context contract xác định; strict build pass.

## Checkpoint 1 — Pointer contract

1. **Why:** địa chỉ hợp lệ không kéo dài lifetime.
2. **Action:** xác định owner cho input/context/output; null-check trước dereference.
3. **Giải thích:** không return pointer tới automatic local object.

**Verify:** build strict, run empty and normal input.

## Checkpoint 2 — Callback signature

1. **Why:** cast function pointer để “khớp” signature là undefined behavior.
2. **Action:** dùng typedef exact signature, callback nhận `const void *context`; không dùng global mutable state.
3. **Giải thích:** caller bảo đảm context còn sống trong call; callback không giữ pointer sau return.

**Verify:** hai predicate khác nhau tạo selections đúng; invalid callback rejected.

## Checkpoint 3 — Variation/reset

1. **Why:** output ownership phải sống qua callback.
2. **Action:** thêm predicate range + flag; document ai free output.
3. **Giải thích:** pointer-to-pointer chỉ dùng khi callee cần thay pointer của caller.

**Troubleshooting:** crash sau return → kiểm lifetime context. **Reset:** xóa scratch.

**Học tiếp:** `Assignment_01.md` dùng alert model và callback khác.

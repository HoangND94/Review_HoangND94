# Hands-on Lab B05 — Owned Dynamic Vector

**105 phút · guided with fading · Tham chiếu:** `assets/b05_memory_demo.c`, `CASE-B05-01`.

## DoD

Hiện thực vector `data/size/capacity` sở hữu heap memory, `reserve/push/free` có status rõ; allocation failure không đổi vector cũ; strict build và sanitizer path (nếu tool sẵn có) sạch.

## Checkpoint 1 — Lifetime và ownership

1. **Why:** pointer không mang ownership/lifetime.
2. **Action:** lập bảng ai tạo/sở hữu/giải phóng; dùng `const` khi chỉ đọc.
3. **Giải thích:** layout code/data/heap/stack chỉ là quan sát host; contract C là storage duration/lifetime.

**Verify:** build strict, log không warning.

## Checkpoint 2 — Allocation failure atomic

1. **Why:** gán thẳng `realloc` có thể mất pointer cũ.
2. **Action:** reserve qua temporary pointer; chỉ commit `data/capacity` sau success; push kiểm capacity trước write.
3. **Giải thích:** pointer arithmetic chỉ trong cùng array object và một-past-end, không dereference one-past.

**Verify:** push 0, 1, capacity boundary; inject/handle allocation failure và hash state trước/sau. **Expected:** state giữ nguyên khi fail.

## Checkpoint 3 — Cleanup / reset

1. **Why:** mỗi đường thoát phải có ownership outcome.
2. **Action:** gọi free idempotent, set state về empty; test double cleanup.
3. **Giải thích:** không free non-owned/stack pointer.

**Evidence:** happy + failure transcript; ASan/Valgrind nếu có. **Troubleshooting:** leak → xem branch trả về trước cleanup. **Reset:** xóa scratch.

**Học tiếp:** `Assignment_01.md` thay workload và API vector.

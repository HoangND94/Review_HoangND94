# Hands-on Lab B02 — Bounded Batch Classifier

**90 phút · guided with fading · Tham chiếu:** `assets/b02_array_flow_demo.c`, `CASE-B02-01`.

## DoD

Xây CLI nhận tối đa 16 số nguyên, lưu vào array, phân loại bằng `if`/`switch`, duyệt bằng loop có invariant và in count theo class. Strict C17 build không warning; invalid input không tạo summary.

## Checkpoint 1 — Array contract

1. **Why:** capacity và count không đồng nghĩa.
2. **Action:** khai báo `values[16]`, chỉ ghi khi `count < 16`; ghi invariant `0 <= i < count` cạnh mọi loop.
3. **Giải thích:** C không bounds-check array; multidimensional array phải truyền đúng dimension còn lại.

**Verify:** đưa 1, 16, rồi 17 values. **Expected:** 1/16 pass, 17 reject; lưu transcript.

## Checkpoint 2 — Decision và looping

1. **Why:** mỗi input phải có đúng một class.
2. **Action:** dùng `if/else` cho range và `switch` cho class code; dùng `for` để aggregate, `break` chỉ khi điều kiện dừng đã ghi rõ.
3. **Giải thích:** không dùng `?:` lồng nhau làm che logic; tránh fall-through không chú thích.

**Verify:** fixture `-1 0 7 25` tạo đúng bốn bucket. **Evidence:** expected/actual + exit code.

## Checkpoint 3 — Variation, lỗi, reset

1. **Why:** loop cần chịu early-stop có kiểm soát.
2. **Action:** thêm `--until-negative`; số âm kết thúc input nhưng không được tính.
3. **Giải thích:** kiểm boundary trước index; không đọc `values[count]`.

**Troubleshooting:** count sai thường do `i <= count`; chuyển thành `i < count`. **Reset:** xóa `lab01_scratch` duy nhất.

**Học tiếp:** chuyển sang `Assignment_01.md` với dataset và change request mới.

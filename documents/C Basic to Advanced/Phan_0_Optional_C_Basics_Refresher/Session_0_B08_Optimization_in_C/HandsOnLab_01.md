# Hands-on Lab B08 — Evidence-led Optimization

**90 phút · guided with fading · Tham chiếu:** `assets/b08_optimization_demo.c`, `CASE-B08-01`.

## DoD

Giữ observable output/checksum bất biến trước và sau một transformation nhỏ; so sánh `-O0`/`-O2`, ghi size/timing/profile evidence và quyết định giữ/bỏ có giới hạn. Không tuyên bố speedup phổ quát.

## Checkpoint 1 — Baseline trước tối ưu

1. **Why:** nhanh hơn mà sai là regression.
2. **Action:** build strict `-O0`, khóa input synthetic, lưu stdout/checksum và command/environment.
3. **Giải thích:** output khác giữa builds có thể chỉ UB/uninitialized state, phải sửa trước benchmark.

**Verify:** baseline exit 0, expected output exact trong evidence.

## Checkpoint 2 — Một transformation có lý do

1. **Why:** tối ưu local có trade-off size/readability.
2. **Action:** chọn loop-invariant code motion hoặc strength reduction ở một hot path; không thay semantics.
3. **Giải thích:** compiler có thể tự CSE/constant propagation; source change cần profile hoặc rationale.

**Verify:** build `-O0`/`-O2`, `cmp` output/checksum; ghi `size` hai binary.

## Checkpoint 3 — Profile, variation, reset

1. **Why:** timing đơn lẻ dễ nhiễu.
2. **Action:** chạy lặp workload cố định; dùng `gprof` nếu sẵn có, nếu không ghi rõ tool unavailable và không claim hotspot.
3. **Giải thích:** inline/unroll có thể đổi size/cache behavior.

**Expected:** report nêu baseline, measurement, decision và limitation. **Reset:** xóa scratch/build artifacts.

**Học tiếp:** `Assignment_01.md` thay candidate/workload và yêu cầu báo cáo độc lập.

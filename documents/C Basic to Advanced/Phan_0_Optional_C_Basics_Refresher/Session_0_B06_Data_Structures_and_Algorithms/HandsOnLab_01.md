# Hands-on Lab B06 — Workload-driven Collection Choice

**120 phút · guided with fading · Tham chiếu:** `assets/b06_dsa_demo.c`, `CASE-B06-01`.

## DoD

So sánh array sorted với linked list cho workload insert/search; hiện thực một representation đã chọn, invariant và tiêu chí kiểm chứng. Không tuyên bố complexity của `qsort` ngoài contract của thư viện.

## Checkpoint 1 — Workload và invariant

1. **Why:** cấu trúc dữ liệu được chọn theo operation, không theo tên quen thuộc.
2. **Action:** ghi workload: 80% lookup, 20% insert; ghi invariant sorted/unique và ownership node.
3. **Giải thích:** primitive data là phần tử, non-primitive là representation/relations.

**Verify:** review bảng operation → expected cost/invariant; evidence trong README.

## Checkpoint 2 — Implementation + algorithm

1. **Why:** `bsearch` chỉ đúng với comparator/sort contract tương thích.
2. **Action:** hiện thực insert/lookup/browse cho array hoặc list; nếu dùng `qsort`, comparator không trừ trực tiếp hai int.
3. **Giải thích:** tree/hash/heap/queue/stack được đánh giá theo use case, không phải bắt buộc nhét vào solution.

**Verify:** empty/one/many/duplicate/missing lookup. **Expected:** invariant còn đúng sau mọi case.

## Checkpoint 3 — Variation/reset

1. **Why:** requirement thay đổi có thể đổi representation.
2. **Action:** đổi workload thành FIFO, nêu cấu trúc phù hợp và lý do thay vì sửa code bừa.
3. **Giải thích:** complexity là mô hình, không phải timing đo được.

**Troubleshooting:** search sai → xác minh sorted order/comparator. **Reset:** xóa scratch.

**Học tiếp:** `Assignment_01.md` yêu cầu tự chọn representation theo workload mới.

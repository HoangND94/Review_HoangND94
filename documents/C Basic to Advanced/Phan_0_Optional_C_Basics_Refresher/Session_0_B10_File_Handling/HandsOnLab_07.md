# Hands-on Lab B10 — Bounded Read/Write Stream

**105 phút · guided with fading · Tham chiếu:** `assets/b10_file_demo.c`, `CASE-B10-01`, fixtures `assets/lab06_*`.

## DoD

Đọc local text file bounded, validate CSV profile nhỏ, ghi text + binary evidence qua `fflush` → `fclose` → reopen, và kiểm exit/stdout/stderr xác định. Không sửa fixture, không flashing/S-record device operation.

## Checkpoint 1 — Open/read state

1. **Why:** `FILE *` là stream state, open success không chứng minh data hợp lệ.
2. **Action:** dùng `fopen`, `fgets` buffer bounded, phát hiện truncated line; chỉ hỏi `feof/ferror` sau read không như mong đợi.
3. **Giải thích:** active file position đổi theo read/write/seek; text và binary stream khác contract.

**Verify:** valid `lab06_records.csv` output count; missing path exit error, stdout rỗng.

## Checkpoint 2 — Write and reopen tiêu chí kiểm chứng

1. **Why:** write success trước close chưa chứng minh buffered data xuống stream.
2. **Action:** ghi hai file mới dưới `lab07_scratch/output`, kiểm `fprintf`/`fwrite`, `fflush`, `fclose`, reopen `r`/`rb` và byte-compare.
3. **Giải thích:** không `fflush` input stream; kiểm close error vì failure có thể muộn.

**Verify:** exact text `status=ready\n`, binary `43 31 37 00`; logs + exit 0.

## Checkpoint 3 — S-record variation/reset

1. **Why:** checksum validates accidental corruption, không phải chữ ký.
2. **Action:** validate S1/S9 profile của fixture; bad checksum phải return error deterministic.
3. **Giải thích:** parser không in summary partial và đóng stream một lần mọi path.

**Troubleshooting:** loop đọc sai EOF → kiểm return của `fgets`, không loop `while(!feof)`. **Reset:** xóa `lab07_scratch` duy nhất.

**Học tiếp:** `Assignment_01.md` mở rộng profile CSV/S-record mà không cho walkthrough.

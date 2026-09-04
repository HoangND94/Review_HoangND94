# Hands-on Lab B00 — Safe Sample Statistics CLI

**Thời lượng:** 75 phút · **Hình thức:** guided with fading · **Tham chiếu material/example:** `basic_refresher_demo.c`, `CASE-B00-01`.

## Mục tiêu và Definition of Done

Thực hành cấu trúc chương trình C17, kiểu dữ liệu, hàm/prototype, mảng chuỗi có giới hạn và con trỏ `const`. Hoàn thành khi chương trình nhận tối đa 8 số nguyên, in `count/min/max/mean` đúng cho input hợp lệ, từ chối token lỗi bằng exit code khác 0, và strict build không warning.

## Chuẩn bị

Tạo thư mục `lab01_scratch`; copy **không sửa** `assets/basic_refresher_demo.c` vào đó để đọc contract. Dùng GCC với `-std=c17 -Wall -Wextra -Wpedantic -Werror`.

## Checkpoint 1 — Khóa contract và prototype

1. **Why:** prototype tách interface khỏi implementation, tránh implicit declaration.
2. **Action:** tạo `stats.h`, `stats.c`, `main.c`; khai báo hàm nhận `const int values[]`, `size_t count` và output pointers cho min/max/mean.
3. **Giải thích:** `const` nói rõ hàm không được sửa input; `count` là ranh giới hợp lệ của mảng.

**Verify:** build strict. **Expected:** exit 0, không có warning. **Evidence:** lưu command và output vào `lab01_scratch/build.log`.

## Checkpoint 2 — Parse có giới hạn và tính thống kê

1. **Why:** dữ liệu text không tự trở thành `int` an toàn.
2. **Action:** parse từng `argv` bằng `strtol`, kiểm `endptr`, `errno` và range trước cast; chỉ gọi hàm thống kê khi `1 <= count <= 8`.
3. **Giải thích:** không dùng `atoi`; mọi token có ký tự dư hoặc overflow phải bị từ chối.

**Verify:** chạy `./stats 3 -5 150`. **Expected:** `OK count=3 min=-5 max=150 mean=49.33` (hoặc format đã ghi rõ trong README) và exit 0. Chạy `./stats 3 bad`; **Expected:** stderr có mã lỗi ổn định, stdout rỗng, exit khác 0. **Evidence:** lưu hai transcript.

## Checkpoint 3 — Variation và reset

1. **Why:** transfer khác với copy ví dụ.
2. **Action:** thêm mode `--limit N` chỉ nhận giá trị trong `[-N,N]`, vẫn dùng parser chung.
3. **Giải thích:** validation thuộc boundary, không rải điều kiện không nhất quán khắp `main`.

**Verify:** kiểm input biên `-10`, `10`, `11` với `--limit 10`. **Expected:** hai giá trị đầu được chấp nhận, `11` bị từ chối. **Troubleshooting:** kết quả mean sai thường do integer division; cast trước phép chia. **Reset:** xóa duy nhất `lab01_scratch`; không sửa asset gốc.

## Nộp bài

Nộp `stats.h`, `stats.c`, `main.c`, `README.md` (contract/command) và transcript happy + invalid. Lab chuẩn bị cho `Assignment_01.md`.

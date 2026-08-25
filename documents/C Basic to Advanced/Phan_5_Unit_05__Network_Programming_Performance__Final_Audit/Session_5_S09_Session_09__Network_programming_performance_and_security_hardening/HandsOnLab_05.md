# Hands-on Lab LAB-P05-01 — Hoàn thiện epoll framing và hardening bằng profiling evidence

> **Khóa học:** Advanced C Programming · **Unit:** S09 — Network programming, performance and security hardening · **Thuộc:** Part 5

| Thuộc tính | Giá trị |
| --- | --- |
| Mã lab | LAB-P05-01 |
| Hình thức | guided_with_fading |
| Thời lượng dự kiến | 105 phút |
| Độ khó | hard |
| Mức xác thực | inherit |

## 🎯 Learning Outcomes được thực hành

| Learning Outcome | Checkpoint | Bằng chứng bắt buộc |
| --- | --- | --- |
| ADVC-H2SD | CP-P05-01 | `epoll_guided.log`, diff của scratch source và ghi chú framing/lifecycle trong `lab05_evidence.md` |
| ADVC-H3SD | CP-P05-02 | `profile.log`, `profile_row.gprof`, `security.log`, sanitizer log và quyết định hardening trong `lab05_evidence.md` |

> Mỗi Learning Outcome được map tới ít nhất một trạng thái chạy được và một artifact kiểm chứng được.

## 🧭 Bối cảnh nghề nghiệp/dự án và project increment

**Bối cảnh nghề nghiệp/dự án:** integration maintainer nhận hai starter synthetic đã chạy được nhưng phải tạo evidence mạnh hơn trước handoff: framing không phụ thuộc ranh giới `send`, lifecycle không rò FD, kết quả tối ưu giữ nguyên và input/format được phòng vệ.

**Project increment của lab:** một scratch patch cùng evidence bundle tái lập được trên Ubuntu Jammy. Lab chỉ mở rộng fixture cục bộ; không triển khai gateway, backend, protocol hay acceptance path của Assignment.

## 🧰 Điều kiện bắt đầu

### Kiến thức/kỹ năng tiên quyết

- Đã học S07–S09 và đọc contract của `recv`, non-blocking readiness, delimiter framing, compiler optimization và defensive C.
- Biết build C17 bằng GCC, đọc exit code, dùng `diff`, `gprof` và sanitizer output.

### Môi trường, công cụ và phiên bản

- Image bắt buộc: `codex/adv-c-jammy:20260821` (`ENV-ADV-C-JAMMY`).
- Chạy container với `--network none`; fixture network chỉ dùng loopback nội bộ do chính executable sở hữu.
- Công cụ: GCC 11.4, GNU binutils/gprof, coreutils và shell POSIX trong image.

### Starter assets

- `assets/epoll_line_demo.c` — SHA-256 `3d3bbbbe86acc0f9056905ac94aa2613e4b686ea30314c647bca8dc0de566245`.
- `assets/profile_hardening_demo.c` — SHA-256 `11db93aa15ccded1e9c56f5ff3705fc088cb01c1d4c4cc5dc5434f068577c24d`.

Chỉ sửa bản sao trong `lab05_scratch/`; hai starter là baseline bất biến để tạo diff và reset.

### Input/trạng thái ban đầu

- Network fixture mặc định gửi split frame `PING` và `ECHO xin-chao` qua listener loopback port `0`.
- Profile fixture dùng matrix synthetic `256 × 256`, `200` repetitions và payload đối kháng `%n%s%x`.
- Không có endpoint, secret, PII, service hoặc traffic bên ngoài.

### Ràng buộc và phạm vi được phép thay đổi

- Không sửa file trong `assets/`, Assignment, plan, aggregate, Harness hoặc verification.
- Không bật network của container, không dùng port cố định, không thay sysctl/perf policy và không signal process ngoài child do fixture tạo.
- Warning profile `-std=c17 -Wall -Wextra -Wpedantic -Werror` là blocking gate.
- Timing là observation; pass/fail performance dựa trên cùng workload, checksum và profiler evidence, không dùng ngưỡng nanosecond phổ quát.
- Payload không được dùng làm format string; kiểm bounds trước copy/arithmetic.

## 📚 Nguồn đầu vào đã map

- Material và hai starter synthetic của S09.
- Môi trường khóa `ENV-ADV-C-JAMMY`.
- Yêu cầu lab bổ sung của người dùng được disclosure ở cuối tài liệu.

## 📋 Lab outline và Definition of Done

### Checklist phạm vi

1. Khóa baseline và oracle của cả hai starter.
2. Mở rộng split/coalesced framing và xác minh lifecycle bằng exact output.
3. Giảm dần hướng dẫn: tự hoàn thiện profile equivalence, bounded payload policy và sanitizer evidence.
4. Tạo diff, evidence note, profile/security logs; dọn binary nhưng giữ deliverables.

### Checkpoint đã hoạch định từ course plan

| Checkpoint | Mức hướng dẫn | LO | Trạng thái quan sát được |
| --- | --- | --- | --- |
| CP-P05-00 | Baseline đầy đủ | hỗ trợ ADVC-H2SD, ADVC-H3SD | Hai starter strict-build và đạt oracle gốc |
| CP-P05-01 | Guided | ADVC-H2SD | Ba frame qua nhiều write tạo ba response; child sạch; `fd_delta=0` |
| CP-P05-02 | Fading | ADVC-H3SD | Row/column checksum tương đương; profile có symbol; invalid payload bị chặn; sanitizer sạch |

### Definition of Done

- CP-P05-00, CP-P05-01 và CP-P05-02 đều pass từ scratch workspace mới.
- `lab05_scratch/` chứa hai source đã làm, hai unified diff, `epoll_guided.log`, `profile.log`, `profile_row.gprof`, `security.log` và `sanitizer.log`.
- `lab05_evidence.md` ghi image tag, command, exit code, exact/dynamic oracle, quyết định và residual risk của từng checkpoint.
- Starter trong `assets/` giữ đúng checksum; không có process con, listener hoặc binary lab còn chạy sau cleanup.

---

## 🪜 Các bước dự kiến và mức hướng dẫn

1. **0–25 phút — hướng dẫn đầy đủ:** khóa checksum, strict build và baseline outputs.
2. **25–70 phút — guided:** thay fixture/state contract theo các invariant được nêu, nhưng học viên tự chỉnh source và cleanup paths.
3. **70–100 phút — fading:** chỉ nhận acceptance contract cho equivalence và defensive input; học viên chọn cấu trúc helper/test flow.
4. **100–105 phút — handoff:** chạy final validation, hoàn thiện evidence và cleanup.

## Checkpoint CP-P05-00 — Baseline và safety check

### Action

Từ thư mục S09, xác nhận starter checksum, tạo scratch workspace và build hai bản sao. Không sửa starter hoặc bỏ `-Werror` để làm baseline pass.

### Verify

```sh
sha256sum assets/epoll_line_demo.c assets/profile_hardening_demo.c
mkdir -p lab05_scratch
cp assets/epoll_line_demo.c lab05_scratch/epoll_line_demo.c
cp assets/profile_hardening_demo.c lab05_scratch/profile_hardening_demo.c

cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 \
  lab05_scratch/epoll_line_demo.c -o lab05_scratch/epoll_baseline
timeout 10s lab05_scratch/epoll_baseline \
  >lab05_scratch/epoll_baseline.out 2>lab05_scratch/epoll_baseline.err
test "$?" -eq 0
test "$(cat lab05_scratch/epoll_baseline.out)" = \
  "frames=2 responses=2 child_exit=0 fd_delta=0"
test ! -s lab05_scratch/epoll_baseline.err

cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 \
  lab05_scratch/profile_hardening_demo.c -o lab05_scratch/profile_baseline
lab05_scratch/profile_baseline row 200 '%n%s%x' \
  >lab05_scratch/profile_row_base.out 2>lab05_scratch/profile_row_base.err
lab05_scratch/profile_baseline column 200 '%n%s%x' \
  >lab05_scratch/profile_column_base.out 2>lab05_scratch/profile_column_base.err
grep -Eq '^mode=row repetitions=200 checksum=1671168000 elapsed_ns=[0-9]+$' \
  lab05_scratch/profile_row_base.out
grep -Eq '^mode=column repetitions=200 checksum=1671168000 elapsed_ns=[0-9]+$' \
  lab05_scratch/profile_column_base.out
test "$(tail -n 1 lab05_scratch/profile_row_base.out)" = 'payload=%n%s%x'
test "$(tail -n 1 lab05_scratch/profile_column_base.out)" = 'payload=%n%s%x'
test ! -s lab05_scratch/profile_row_base.err
test ! -s lab05_scratch/profile_column_base.err
```

### Expected result

- Hai SHA-256 đúng giá trị ở mục Starter assets.
- Network stdout chính xác `frames=2 responses=2 child_exit=0 fd_delta=0`; stderr rỗng; exit code `0`.
- Mỗi profile run có checksum `1671168000`, payload literal `%n%s%x`, `elapsed_ns` là số nguyên không âm; stderr rỗng; exit code `0`.

### Evidence

Giữ bốn file `*_base.out`/`*_base.err`; ghi checksum, image tag và trạng thái từng lệnh vào mục `CP-P05-00` của `lab05_evidence.md`.

### Troubleshooting

- `sha256sum` lệch → đang đứng sai session hoặc starter đã đổi → dừng lab, không tự “sửa” baseline; đối chiếu đường dẫn và báo instructor.
- Compiler warning → xác nhận đúng image/tag và source copy → không bỏ flag; lưu compiler stderr.
- Network timeout → kiểm tra không chạy qua sandbox chặn cả loopback và không có binary cũ → dừng đúng PID lab, chạy lại trong image đã khóa.

### Reset/rollback

Chỉ xóa các output baseline được liệt kê, rồi copy lại hai starter:

```sh
rm -f -- lab05_scratch/epoll_baseline lab05_scratch/profile_baseline \
  lab05_scratch/epoll_baseline.out lab05_scratch/epoll_baseline.err \
  lab05_scratch/profile_row_base.out lab05_scratch/profile_row_base.err \
  lab05_scratch/profile_column_base.out lab05_scratch/profile_column_base.err
cp assets/epoll_line_demo.c lab05_scratch/epoll_line_demo.c
cp assets/profile_hardening_demo.c lab05_scratch/profile_hardening_demo.c
cmp -s assets/epoll_line_demo.c lab05_scratch/epoll_line_demo.c
cmp -s assets/profile_hardening_demo.c lab05_scratch/profile_hardening_demo.c
```

## Checkpoint CP-P05-01 — Guided framing và lifecycle epoll

### Action

Chỉ trong `lab05_scratch/epoll_line_demo.c`, mở rộng client fixture thành ba logical frame với một frame bị chia giữa hai lần gửi và hai frame hoàn chỉnh nằm trong lần gửi kế tiếp:

- write thứ nhất mang `E`;
- write thứ hai mang `CHO mot\nPING\nECHO hai\n`;
- response contract theo thứ tự là `mot\nPONG\nhai\n`.

Cập nhật expected response và target số dòng phía child, đồng thời cập nhật điều kiện hoàn thành phía parent để đếm đúng ba frame/ba response. Giữ parser state xuyên qua các lần `recv`, sent offset cho partial write, drain đến `EAGAIN`, half-close trước flush cuối, một owner cleanup và kiểm FD trở về baseline. Không đổi sang blocking-per-connection hoặc thêm traffic ngoài loopback.

### Verify

```sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 \
  lab05_scratch/epoll_line_demo.c -o lab05_scratch/epoll_guided
timeout 10s lab05_scratch/epoll_guided \
  >lab05_scratch/epoll_guided.log 2>lab05_scratch/epoll_guided.err
run_status=$?
test "$run_status" -eq 0
test "$(cat lab05_scratch/epoll_guided.log)" = \
  "frames=3 responses=3 child_exit=0 fd_delta=0"
test ! -s lab05_scratch/epoll_guided.err
set +e
diff -u assets/epoll_line_demo.c lab05_scratch/epoll_line_demo.c \
  >lab05_scratch/epoll_line_demo.diff
diff_status=$?
set -e
test "$diff_status" -eq 1
```

### Expected result

Compile warnings bằng `0`; stdout chính xác `frames=3 responses=3 child_exit=0 fd_delta=0`; stderr rỗng; exit code `0`. Unified diff không rỗng và chỉ đổi scratch source. `fd_delta=0` là lifecycle oracle; ba counter và child exit là framing/response oracle.

### Evidence

Nộp `epoll_line_demo.c`, `epoll_line_demo.diff`, `epoll_guided.log`, stderr rỗng và mục `CP-P05-01` trong `lab05_evidence.md`. Ghi rõ state nào giữ partial `E`, transition nào xử lý EOF/pending output và owner nào đóng FD.

### Troubleshooting

- `frames=2` → còn hard-coded completion count hoặc fixture length sai → đối chiếu byte count và mọi completion invariant, không thêm delay để che lỗi.
- Child exit khác `0` → server response/order không khớp → inspect response buffer và sent offset trước khi sửa parser.
- `fd_delta` dương → một accept/error/half-close path thiếu cleanup → trace ownership theo FD; không đóng một FD từ hai branch.
- Timeout → event interest không còn phản ánh pending input/output → kiểm `EPOLLIN`, `EPOLLOUT`, `EPOLLRDHUP` và điểm quay lại `epoll_wait`.

### Reset/rollback

```sh
rm -f -- lab05_scratch/epoll_guided lab05_scratch/epoll_guided.log \
  lab05_scratch/epoll_guided.err lab05_scratch/epoll_line_demo.diff
cp assets/epoll_line_demo.c lab05_scratch/epoll_line_demo.c
cmp -s assets/epoll_line_demo.c lab05_scratch/epoll_line_demo.c
```

Sau reset, CP-P05-00 network oracle phải pass lại trước lần thử tiếp theo.

## Checkpoint CP-P05-02 — Fading profile equivalence và security hardening

### Action

Tự thiết kế thay đổi trong `lab05_scratch/profile_hardening_demo.c` theo contract sau:

- giữ hai mode `row|column`, repetitions `1..10000`, checksum và literal-format output hiện có;
- thêm validation cho payload: dài `1..32` byte và chỉ chứa printable ASCII `0x20..0x7e`;
- invalid payload phải không có stdout, in đúng `invalid payload: printable ASCII, length 1..32 required` lên stderr và exit `1`;
- so sánh row/column trên cùng repetitions bằng checksum, không dùng `elapsed_ns` làm pass/fail;
- tạo build `-pg` riêng để lưu profile, rồi tạo ASan+UBSan build riêng cho cùng valid/adversarial fixtures.

Từ checkpoint này, tài liệu chỉ khóa contract/oracle; học viên tự chọn helper, vị trí validation và cách tổ chức cleanup mà không dùng input làm format string.

### Verify

```sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 \
  lab05_scratch/profile_hardening_demo.c -o lab05_scratch/profile_hardened
lab05_scratch/profile_hardened row 200 '%n%s%x' \
  >lab05_scratch/profile_row.out 2>lab05_scratch/profile_row.err
lab05_scratch/profile_hardened column 200 '%n%s%x' \
  >lab05_scratch/profile_column.out 2>lab05_scratch/profile_column.err
grep -Eq '^mode=row repetitions=200 checksum=1671168000 elapsed_ns=[0-9]+$' \
  lab05_scratch/profile_row.out
grep -Eq '^mode=column repetitions=200 checksum=1671168000 elapsed_ns=[0-9]+$' \
  lab05_scratch/profile_column.out
test "$(tail -n 1 lab05_scratch/profile_row.out)" = 'payload=%n%s%x'
test "$(tail -n 1 lab05_scratch/profile_column.out)" = 'payload=%n%s%x'
test ! -s lab05_scratch/profile_row.err
test ! -s lab05_scratch/profile_column.err
cat lab05_scratch/profile_row.out lab05_scratch/profile_column.out \
  >lab05_scratch/profile.log

cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O0 -g -pg \
  lab05_scratch/profile_hardening_demo.c -o lab05_scratch/profile_pg
(cd lab05_scratch && ./profile_pg row 200 '%n%s%x' >/dev/null && \
  gprof ./profile_pg gmon.out >profile_row.gprof)
grep -Eq 'scan_rows|main' lab05_scratch/profile_row.gprof

set +e
lab05_scratch/profile_hardened row 1 \
  'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA' \
  >lab05_scratch/security_invalid.out 2>lab05_scratch/security_invalid.err
invalid_status=$?
set -e
test "$invalid_status" -eq 1
test ! -s lab05_scratch/security_invalid.out
test "$(cat lab05_scratch/security_invalid.err)" = \
  'invalid payload: printable ASCII, length 1..32 required'

cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O1 -g \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  lab05_scratch/profile_hardening_demo.c -o lab05_scratch/profile_san
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
UBSAN_OPTIONS=halt_on_error=1 \
  lab05_scratch/profile_san row 200 '%n%s%x' \
  >lab05_scratch/sanitizer.out 2>lab05_scratch/sanitizer.log
san_status=$?
test "$san_status" -eq 0
test ! -s lab05_scratch/sanitizer.log
printf 'invalid-payload rc=%s stderr=%s\n' "$invalid_status" \
  "$(cat lab05_scratch/security_invalid.err)" >lab05_scratch/security.log
printf 'sanitizer rc=%s stderr_bytes=%s\n' "$san_status" \
  "$(wc -c <lab05_scratch/sanitizer.log)" >>lab05_scratch/security.log

set +e
diff -u assets/profile_hardening_demo.c \
  lab05_scratch/profile_hardening_demo.c \
  >lab05_scratch/profile_hardening_demo.diff
diff_status=$?
set -e
test "$diff_status" -eq 1
```

### Expected result

- Hai valid runs exit `0`, stderr rỗng, checksum cùng bằng `1671168000`; mỗi dòng payload chính xác `payload=%n%s%x`.
- `profile_row.gprof` được tạo từ normal exit và chứa symbol `scan_rows` hoặc `main`; timing/counter chỉ là evidence mô tả.
- Payload 33 ký tự exit `1`, stdout rỗng, stderr chính xác theo contract.
- Sanitizer run exit `0`, `sanitizer.log` rỗng.
- `security.log` chính xác hai dòng:

```text
invalid-payload rc=1 stderr=invalid payload: printable ASCII, length 1..32 required
sanitizer rc=0 stderr_bytes=0
```

### Evidence

Nộp scratch source/diff, `profile.log`, `profile_row.gprof`, `security.log`, `sanitizer.log` và mục `CP-P05-02` trong `lab05_evidence.md`. Giải thích vì sao checksum là equivalence oracle, timing không phải pass threshold, và literal format ngăn payload `%n%s%x` điều khiển `printf`.

### Troubleshooting

- Checksum khác giữa modes → workload hoặc vòng lặp đã đổi cùng lúc với hardening → khôi phục scan contract trước khi đọc timing.
- Không có `gmon.out` → thiếu `-pg` ở build/link hoặc process không normal-exit → chạy đúng binary trong `lab05_scratch` rồi mới gọi `gprof`.
- Invalid payload vẫn in mode line → validation diễn ra sau observable work → đưa validation trước initialize/profile/output.
- Sanitizer có finding → lưu nguyên log, thu nhỏ fixture và sửa root cause; không tắt sanitizer hoặc suppress finding.
- Payload `%n%s%x` không in nguyên văn → input đang được dùng làm format → kiểm mọi formatted-output call và giữ format literal.

### Reset/rollback

```sh
rm -f -- lab05_scratch/profile_hardened lab05_scratch/profile_pg \
  lab05_scratch/profile_san lab05_scratch/gmon.out \
  lab05_scratch/profile_row.out lab05_scratch/profile_row.err \
  lab05_scratch/profile_column.out lab05_scratch/profile_column.err \
  lab05_scratch/security_invalid.out lab05_scratch/security_invalid.err \
  lab05_scratch/sanitizer.out
cp assets/profile_hardening_demo.c lab05_scratch/profile_hardening_demo.c
cmp -s assets/profile_hardening_demo.c lab05_scratch/profile_hardening_demo.c
```

Giữ evidence đã chấp nhận ở nơi nộp trước khi rollback; sau reset, CP-P05-00 profile oracle phải pass lại.

## 🧪 Final validation

**Phương thức:** executable

Chạy trong image `codex/adv-c-jammy:20260821` với `--network none`, từ S09 và từ một scratch workspace đã tái tạo. Final gate gồm:

```sh
set -eu

test "$(sha256sum assets/epoll_line_demo.c | cut -d' ' -f1)" = \
  '3d3bbbbe86acc0f9056905ac94aa2613e4b686ea30314c647bca8dc0de566245'
test "$(sha256sum assets/profile_hardening_demo.c | cut -d' ' -f1)" = \
  '11db93aa15ccded1e9c56f5ff3705fc088cb01c1d4c4cc5dc5434f068577c24d'
sha256sum lab05_scratch/epoll_line_demo.c \
  lab05_scratch/profile_hardening_demo.c \
  >lab05_scratch/current_sources.sha256
sha256sum -c lab05_scratch/current_sources.sha256 \
  >lab05_scratch/current_hash_check.log
test "$(wc -l <lab05_scratch/current_hash_check.log)" -eq 2

set +e
diff -u assets/epoll_line_demo.c lab05_scratch/epoll_line_demo.c \
  >lab05_scratch/epoll_line_demo.diff
epoll_diff_status=$?
diff -u assets/profile_hardening_demo.c \
  lab05_scratch/profile_hardening_demo.c \
  >lab05_scratch/profile_hardening_demo.diff
profile_diff_status=$?
set -e
test "$epoll_diff_status" -eq 1
test "$profile_diff_status" -eq 1
test -s lab05_scratch/epoll_line_demo.diff
test -s lab05_scratch/profile_hardening_demo.diff

cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 \
  lab05_scratch/epoll_line_demo.c -o lab05_scratch/epoll_final
set +e
timeout 10s lab05_scratch/epoll_final >lab05_scratch/epoll_final.out 2>lab05_scratch/epoll_final.err
epoll_status=$?
set -e
test "$epoll_status" -eq 0
test "$(cat lab05_scratch/epoll_final.out)" = \
  'frames=3 responses=3 child_exit=0 fd_delta=0'
test ! -s lab05_scratch/epoll_final.err

cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 \
  lab05_scratch/profile_hardening_demo.c -o lab05_scratch/profile_final
set +e
lab05_scratch/profile_final row 200 '%n%s%x' >lab05_scratch/final_row.out 2>lab05_scratch/final_row.err
row_status=$?
lab05_scratch/profile_final column 200 '%n%s%x' >lab05_scratch/final_column.out 2>lab05_scratch/final_column.err
column_status=$?
set -e
test "$row_status" -eq 0
test "$column_status" -eq 0
test "$(wc -l <lab05_scratch/final_row.out)" -eq 2
test "$(wc -l <lab05_scratch/final_column.out)" -eq 2
grep -Eq '^mode=row repetitions=200 checksum=1671168000 elapsed_ns=[0-9]+$' lab05_scratch/final_row.out
grep -Eq '^mode=column repetitions=200 checksum=1671168000 elapsed_ns=[0-9]+$' lab05_scratch/final_column.out
test "$(tail -n 1 lab05_scratch/final_row.out)" = 'payload=%n%s%x'
test "$(tail -n 1 lab05_scratch/final_column.out)" = 'payload=%n%s%x'
test ! -s lab05_scratch/final_row.err
test ! -s lab05_scratch/final_column.err
cat lab05_scratch/final_row.out lab05_scratch/final_column.out \
  >lab05_scratch/final_profile.log

set +e
lab05_scratch/profile_final row 1 \
  'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA' \
  >lab05_scratch/final_long_33.out 2>lab05_scratch/final_long_33.err
long_status=$?
set -e
test "$long_status" -eq 1
test ! -s lab05_scratch/final_long_33.out
test "$(cat lab05_scratch/final_long_33.err)" = \
  'invalid payload: printable ASCII, length 1..32 required'

nonprint_payload=$(printf 'ok\nbad')
set +e
lab05_scratch/profile_final row 1 "$nonprint_payload" \
  >lab05_scratch/final_nonprint.out 2>lab05_scratch/final_nonprint.err
nonprint_status=$?
set -e
test "$nonprint_status" -eq 1
test ! -s lab05_scratch/final_nonprint.out
test "$(cat lab05_scratch/final_nonprint.err)" = \
  'invalid payload: printable ASCII, length 1..32 required'
printf 'long-33 rc=%s stdout_bytes=%s stderr=%s\n' \
  "$long_status" "$(wc -c <lab05_scratch/final_long_33.out)" \
  "$(cat lab05_scratch/final_long_33.err)" \
  >lab05_scratch/final_security.log
printf 'non-printable rc=%s stdout_bytes=%s stderr=%s\n' \
  "$nonprint_status" "$(wc -c <lab05_scratch/final_nonprint.out)" \
  "$(cat lab05_scratch/final_nonprint.err)" \
  >>lab05_scratch/final_security.log
test "$(cat lab05_scratch/final_security.log)" = "$(printf '%s\n%s' \
  'long-33 rc=1 stdout_bytes=0 stderr=invalid payload: printable ASCII, length 1..32 required' \
  'non-printable rc=1 stdout_bytes=0 stderr=invalid payload: printable ASCII, length 1..32 required')"

cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O0 -g -pg \
  lab05_scratch/profile_hardening_demo.c -o lab05_scratch/profile_final_pg
(cd lab05_scratch && \
  ./profile_final_pg row 200 '%n%s%x' \
    >profile_final_pg.out 2>profile_final_pg.err && \
  gprof ./profile_final_pg gmon.out >profile_final.gprof)
test ! -s lab05_scratch/profile_final_pg.err
test "$(wc -l <lab05_scratch/profile_final_pg.out)" -eq 2
grep -Eq '^mode=row repetitions=200 checksum=1671168000 elapsed_ns=[0-9]+$' \
  lab05_scratch/profile_final_pg.out
test "$(tail -n 1 lab05_scratch/profile_final_pg.out)" = 'payload=%n%s%x'
grep -q 'scan_rows' lab05_scratch/profile_final.gprof

cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O1 -g \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  lab05_scratch/profile_hardening_demo.c -o lab05_scratch/profile_final_san
set +e
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
UBSAN_OPTIONS=halt_on_error=1 \
  lab05_scratch/profile_final_san row 200 '%n%s%x' \
  >lab05_scratch/sanitizer_final.out 2>lab05_scratch/sanitizer_final.log
san_valid_status=$?
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
UBSAN_OPTIONS=halt_on_error=1 \
  lab05_scratch/profile_final_san row 1 \
  'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA' \
  >lab05_scratch/sanitizer_long.out 2>lab05_scratch/sanitizer_long.err
san_long_status=$?
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
UBSAN_OPTIONS=halt_on_error=1 \
  lab05_scratch/profile_final_san row 1 "$nonprint_payload" \
  >lab05_scratch/sanitizer_nonprint.out 2>lab05_scratch/sanitizer_nonprint.err
san_nonprint_status=$?
set -e
test "$san_valid_status" -eq 0
test "$san_long_status" -eq 1
test "$san_nonprint_status" -eq 1
test ! -s lab05_scratch/sanitizer_final.log
test ! -s lab05_scratch/sanitizer_long.out
test ! -s lab05_scratch/sanitizer_nonprint.out
test "$(cat lab05_scratch/sanitizer_long.err)" = \
  'invalid payload: printable ASCII, length 1..32 required'
test "$(cat lab05_scratch/sanitizer_nonprint.err)" = \
  'invalid payload: printable ASCII, length 1..32 required'
test "$(wc -l <lab05_scratch/sanitizer_final.out)" -eq 2
grep -Eq '^mode=row repetitions=200 checksum=1671168000 elapsed_ns=[0-9]+$' \
  lab05_scratch/sanitizer_final.out
test "$(tail -n 1 lab05_scratch/sanitizer_final.out)" = 'payload=%n%s%x'

test -s lab05_scratch/current_sources.sha256
test -s lab05_scratch/current_hash_check.log
test -s lab05_scratch/final_profile.log
test -s lab05_scratch/final_security.log
test -s lab05_scratch/profile_final.gprof
test -f lab05_scratch/sanitizer_final.log
test -s lab05_evidence.md
```

Gate dùng `set -eu` và chỉ tạm tắt fail-fast quanh các process được kỳ vọng trả non-zero để bắt exit code. `elapsed_ns` là slot đo động nhưng toàn bộ format còn lại, số dòng, checksum và payload được assert chính xác. Bất kỳ warning, timeout, hash/diff stale, sai exit/stdout/stderr, thiếu symbol `scan_rows`, sanitizer finding hoặc thiếu evidence nào đều làm gate fail.

## 📦 Bằng chứng và deliverables

- `lab05_scratch/epoll_line_demo.c`, `lab05_scratch/profile_hardening_demo.c`.
- `lab05_scratch/epoll_line_demo.diff`, `lab05_scratch/profile_hardening_demo.diff`.
- `lab05_scratch/current_sources.sha256`, `lab05_scratch/current_hash_check.log`.
- `lab05_evidence.md` với mapping CP → LO → command → oracle → decision/residual risk.
- `lab05_scratch/epoll_guided.log`, `profile.log`, `profile_row.gprof`, `security.log`, `sanitizer.log`.
- Final evidence được tái tạo từ learner source hiện tại: `final_profile.log`, `final_security.log`, `profile_final.gprof`, `sanitizer_final.log`.
- Không nộp binary, `gmon.out`, secret, PII hoặc dữ liệu ngoài fixture synthetic.

## ♻️ Reset, cleanup và khả năng chạy lại

**Troubleshooting từ plan:** khóa đúng image/checksum trước khi sửa; tách framing state, lifecycle state và output state; so checksum trước timing; lưu sanitizer finding thay vì suppress.

**Reset strategy từ plan:** chỉ thay đổi `lab05_scratch/`, nên có thể phục hồi từng source bằng `cp` từ asset và xác nhận bằng `cmp`. Sau final run, xóa chính xác các binary/process artifact nhưng giữ source, diff và evidence:

```sh
rm -f -- lab05_scratch/epoll_baseline lab05_scratch/profile_baseline \
  lab05_scratch/epoll_guided lab05_scratch/profile_hardened \
  lab05_scratch/profile_pg lab05_scratch/profile_san \
  lab05_scratch/epoll_final lab05_scratch/profile_final \
  lab05_scratch/profile_final_pg lab05_scratch/profile_final_san \
  lab05_scratch/gmon.out
test -z "$(pgrep -x epoll_baseline || true)"
test -z "$(pgrep -x epoll_guided || true)"
test -z "$(pgrep -x epoll_final || true)"
sha256sum assets/epoll_line_demo.c assets/profile_hardening_demo.c
```

Không dùng recursive delete; rerun bắt đầu bằng CP-P05-00 trên scratch source được copy mới.

## 🔁 Artifact được tái sử dụng ở đâu

S10 tái sử dụng `lab05_evidence.md`, hai diff và profile/security logs như evidence rehearsal cho final audit. Không tái sử dụng source lab làm lời giải Assignment.

## 🔐 Chính sách lời giải

Learner lab chỉ cung cấp contract, checkpoints, hints tăng dần và oracle. Không chứa source hoàn chỉnh sau thay đổi hoặc lời giải Assignment; instructor solution nếu có phải nằm ngoài output học viên và được kiểm soát truy cập.

## 📚 Provenance phần bổ sung

### Nguồn đã map

- S09 material và các starter source synthetic trong session.
- GCC/binutils và runtime contract của image `codex/adv-c-jammy:20260821`.

### Phần bổ sung/suy diễn

- `[BỔ SUNG — nguồn: SRC-USER-LABS]` — cấu trúc guided-with-fading, fixture ba frame, bounded payload contract, evidence bundle, thời lượng và quan hệ tái sử dụng bởi S10 được bổ sung theo yêu cầu trực tiếp; không thay đổi outline, LO hoặc Assignment.

---
<!-- QUALITY GATE: pilot từ môi trường sạch; mọi checkpoint có Action/Verify/Expected/Evidence/Troubleshooting/Reset; validation chạy được; không lộ đáp án Assignment; không secret/PII. -->

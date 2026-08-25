# Session S09: Session 09 — Network programming, performance and security hardening — Ví dụ và nghiên cứu tình huống

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 05 — Network Programming, Performance & Final Audit

## 🎯 Learning Outcomes liên quan

- **ADVC-H2SD:** tạo và kiểm chứng non-blocking/epoll network lifecycle.
- **ADVC-H3SD:** đánh giá hardening và profiling bằng evidence tái lập.

## 🧭 Liên kết với ngữ cảnh nghề nghiệp/dự án

**Bối cảnh nghề nghiệp/dự án:** MDB Edge Diagnostics Gateway — Simulated. Frontend M09 phải nhận line frames trên loopback, không làm hỏng process/thread backends, rồi tạo security/performance evidence cho quality reviewer.

**Project increment được minh họa:** M09. Case 01 minh họa state machine mạng; Case 02 minh họa measurement-first optimization và defensive C. Hai case dùng code hoàn chỉnh khác nhau và không phải lời giải Assignment 09.

## 🧰 Điều kiện chạy ví dụ

**Kiến thức/kỹ năng tiên quyết:** robust read/write, errno/EINTR, process/pthread lifecycle, C17 bounds/ownership, compiler warnings và cách đọc dynamic-analysis evidence.

**Môi trường, công cụ và phiên bản:** Ubuntu 22.04, Linux 5.15 baseline, GCC 11.4 hoặc Clang 14. Case mạng dùng Linux epoll; listener chỉ bind 127.0.0.1 với port 0. Không cần root hoặc thay sysctl.

**Phương thức xác minh artifact:** executable.

## 📚 Nguồn đầu vào đã map

POSIX.1-2017, RFC 9293/RFC 768, Linux man-pages, Linux kernel perf documentation, GCC 11.4, GNU gprof 2.38, C17/CERT C, CWE, Clang 14 và Valgrind. Link đầy đủ nằm trong material.md.

---

### Mapping case đã chốt trong course plan

- **CASE-S09-01:** ADVC-H2SD · OUT-S09-01 · authenticity inherited.
- **CASE-S09-02:** ADVC-H3SD · OUT-S09-02 · authenticity inherited.

**Mức xác thực mặc định:** simulated, synthetic-only.

## Case Study 01: Chứng minh split/coalesced frames trên epoll loopback

### 1. Ticket và tiêu chí thành công

- **Vai trò/stakeholder:** integration maintainer và reviewer của network frontend.
- **Vấn đề cần giải quyết:** một client chia “PING” thành hai lần send rồi gộp frame ECHO ngay sau delimiter; server không được giả định một recv tương ứng một frame.
- **Learning Outcome và outline item:** ADVC-H2SD · OUT-S09-01.
- **Project increment/professional artifact liên quan:** state-machine slice của M09.
- **Tiêu chí thành công:** đúng hai frame, đúng hai response, child client exit 0, FD count của parent trở về baseline, process hoàn tất trong timeout.

### 2. Input, trạng thái ban đầu và ràng buộc

Asset: [assets/epoll_line_demo.c](assets/epoll_line_demo.c).

Client do fixture fork gửi hai byte “PI”, chờ ngắn, rồi gửi “NG\nECHO xin-chao\n” và half-close hướng ghi. Server bind INADDR_LOOPBACK với port 0, dùng level-triggered epoll, accepted sockets O_NONBLOCK/CLOEXEC và buffer bounded. Chỉ PID child do fixture tạo mới có thể bị signal khi timeout; không có endpoint hay dữ liệu thật.

Protocol của case:

| Request | Response |
|---|---|
| PING + LF | PONG + LF |
| ECHO space text + LF | text + LF |
| Khác | ERR + LF |

### 3. Phân tích lựa chọn

Ba phương án được cân nhắc:

1. Xử lý mỗi recv như một request: ngắn nhưng sai TCP semantics.
2. Thread blocking cho từng client: hợp lệ với scale nhỏ nhưng không minh họa mục tiêu epoll.
3. Persistent per-connection buffers + epoll LT: được chọn vì tách readiness khỏi framing và dễ kiểm chứng trước khi cân nhắc ET.

Fixture lưu input qua các recv, parse mọi LF hoàn chỉnh, memmove phần dư, giữ output_sent cho partial send và chỉ close sau khi pending output đã flush. LT tránh failure “không drain hết edge”. Giới hạn của fixture là tối đa tám connection và hai command; Assignment 09 phải mở rộng sang 100 client, timeout và hai backend.

### 4. Cách triển khai

Chương trình hoàn chỉnh nằm trong asset. Các quyết định then chốt:

- socket listener dùng non-blocking/CLOEXEC ngay khi tạo;
- accept4 đặt flags cho từng accepted FD;
- EPOLLIN, EPOLLOUT, RDHUP/HUP/ERR được xem là các tín hiệu có thể đồng thời;
- recv loop dừng ở EAGAIN; send loop giữ offset;
- peer EOF chỉ đóng connection khi output queue rỗng;
- cleanup gỡ interest rồi close đúng một lần;
- count /proc/self/fd trước/sau tạo oracle leak FD.

### 5. Output mong đợi

~~~text
frames=2 responses=2 child_exit=0 fd_delta=0
~~~

Bất kỳ số khác, exit code khác 0 hoặc timeout đều là fail. Port cụ thể không được đưa vào golden output vì kernel tự cấp.

### 6. Cách xác minh

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2   assets/epoll_line_demo.c -o epoll_line_demo
timeout 10s ./epoll_line_demo
test "$?" -eq 0
~~~

Có thể chạy thêm:

~~~sh
strace -f -e trace=network,epoll_wait,close ./epoll_line_demo
~~~

strace là diagnostic tùy chọn; pass/fail vẫn dựa trên process exit và summary oracle.

### 7. Giải thích sâu và failure modes

- Nếu parser chạy trước khi giữ incomplete bytes, “PI” bị coi là invalid. Evidence là ERR hoặc frame count sai.
- Nếu chỉ parse một delimiter mỗi readiness, frame ECHO có thể nằm lại đến event khác. Fixture parse tới khi không còn LF.
- Nếu close ngay tại RDHUP, response queued có thể mất. Fixture flush rồi mới close.
- Nếu EPOLLOUT luôn bật, loop có thể wake liên tục. Fixture chỉ bật khi còn byte.
- Nếu child treo, parent chỉ signal child_pid của chính nó. Không dùng killall/pkill.
- Fixture không mô phỏng backpressure dài hoặc 100 clients; đó là phạm vi đánh giá độc lập.

### 8. Bài học chuyển giao

Readiness, framing và lifecycle là ba contract riêng. Assignment 09 thay command fixture bằng routing vào M07/M08, thêm 100-client load, oversize/error policies, idle timeout, graceful SIGTERM và evidence security/performance; không được sao chép fixture như một server hoàn chỉnh.

---

## Case Study 02: Profile locality mà không hy sinh correctness/security

### 1. Ticket và tiêu chí thành công

- **Vai trò/stakeholder:** security and quality reviewer.
- **Vấn đề cần giải quyết:** so sánh row-major và column-major scan trên cùng matrix, đồng thời chứng minh payload chứa format directives chỉ được in như data.
- **Learning Outcome và outline item:** ADVC-H3SD · OUT-S09-02.
- **Project increment/professional artifact liên quan:** M09 security/performance evidence.
- **Tiêu chí thành công:** hai mode có cùng checksum; invalid repetition bị reject; payload “%n%s%x” được in nguyên văn; timing không bị biến thành ngưỡng pass/fail.

### 2. Input, trạng thái ban đầu và ràng buộc

Asset: [assets/profile_hardening_demo.c](assets/profile_hardening_demo.c).

Matrix 256×256 được khởi tạo deterministically. repetitions mặc định 200, range hợp lệ 1..10000 và được parse bằng strtoul với errno/end/range checks. Payload mặc định là “%n%s%x”; printf luôn dùng literal format. Workload và checksum là synthetic.

### 3. Phân tích lựa chọn

Row-major khớp layout của C, thường có spatial locality tốt hơn; column-major tạo stride. Tuy nhiên case không khẳng định một tỷ lệ cải thiện: CPU, cache, compiler, scheduling và counter policy đều ảnh hưởng. Correctness oracle là checksum; elapsed_ns chỉ là observation.

perf stat phù hợp khi host cho phép counters. gprof dùng build -pg riêng để xác định call hotspot nhưng instrumentation thay đổi execution. Nếu perf bị từ chối, evidence phải nói BLOCKED-PMU; không chạy sudo hoặc sửa perf_event_paranoid.

### 4. Cách triển khai

Chương trình cung cấp hai scan functions trên cùng global matrix. Input parser reject zero, text thừa, overflow và giá trị lớn hơn bound trước khi cast. clock_gettime dùng CLOCK_MONOTONIC. Tổng nằm trong uint64_t cho toàn range công bố. Payload được truyền như argument của “%s”, không làm format string.

### 5. Output mong đợi

Mỗi run có dạng:

~~~text
mode=row repetitions=200 checksum=<same-value> elapsed_ns=<host-dependent>
payload=%n%s%x
~~~

Mode column phải có cùng checksum. elapsed_ns được phép khác bất kỳ chiều nào. Lệnh với repetitions=0 hoặc “200x” phải exit khác 0 và in invalid repetitions.

### 6. Cách xác minh

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2   assets/profile_hardening_demo.c -o profile_demo

row_out=$(./profile_demo row 200 '%n%s%x')
column_out=$(./profile_demo column 200 '%n%s%x')
printf '%s
' "$row_out"
printf '%s
' "$column_out"

row_sum=$(printf '%s
' "$row_out" | sed -n 's/.*checksum=\([0-9][0-9]*\).*/\1/p')
column_sum=$(printf '%s
' "$column_out" | sed -n 's/.*checksum=\([0-9][0-9]*\).*/\1/p')
test -n "$row_sum" && test "$row_sum" = "$column_sum"
! ./profile_demo row 0
! ./profile_demo row 200x
~~~

Optional perf evidence:

~~~sh
perf stat -r 5 -e task-clock,cycles,instructions,cache-references,cache-misses   -- ./profile_demo row 200
perf stat -r 5 -e task-clock,cycles,instructions,cache-references,cache-misses   -- ./profile_demo column 200
~~~

Optional gprof evidence:

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O0 -g -pg   assets/profile_hardening_demo.c -o profile_gprof
./profile_gprof row 1000 >/dev/null
gprof ./profile_gprof gmon.out | sed -n '1,35p'
~~~

### 7. Giải thích sâu và failure modes

- perf permission denied là environment block, không phải code fail hoặc pass.
- Checksum khác nhau chỉ ra bug/UB/input mismatch; dừng performance claim.
- Một lần row nhanh hơn không đủ kết luận. Giữ raw repetitions và fingerprint.
- gmon.out vắng thường do thiếu -pg ở compile/link hoặc abnormal exit.
- printf(payload) sẽ biến “%n” thành externally controlled format; asset dùng printf với literal.
- Sanitizer-clean trên workload này không chứng minh mọi input/lifetime đều an toàn.

### 8. Bài học chuyển giao

Assignment 09 phải profile chính gateway workload có routing/framing, không dùng matrix fixture làm evidence thay thế. Nguyên tắc chuyển giao là giữ invariant output, fingerprint host/toolchain, disclose counter availability và map mỗi security finding tới input trigger, corrective contract và after evidence.

---

## Provenance của các case

### Nguồn được dùng

- Case 01: POSIX.1-2017, RFC 9293, Linux man-pages epoll/socket.
- Case 02: C17/CERT C, GCC 11.4, Linux perf docs, GNU gprof 2.38, CWE, Clang/Valgrind evidence limits.
- Source text được paraphrase; hai C assets được viết mới cho khóa.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — course fixture]:** PING/ECHO protocol, tám connection và matrix workload là synthetic examples.
- **[SUY DIỄN — user-approved integration]:** M09 liên kết process/thread backend và terminal handoff.
- **[BỔ SUNG — nguồn: RFC 9293/POSIX/Linux man-pages]:** split/coalesced framing và non-blocking readiness behavior.
- **[BỔ SUNG — nguồn: GCC/perf/gprof/CERT C/CWE]:** measurement/hardening decisions và evidence boundaries.


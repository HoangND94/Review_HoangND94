# Session S09: Session 09 — Network programming, performance and security hardening — Học liệu cốt lõi

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 05 — Network Programming, Performance & Final Audit

## 🎯 Learning Outcomes

- **ADVC-H2SD — Create:** Xây dựng và kiểm chứng chương trình C trên Linux sử dụng socket non-blocking và epoll với framing, lifecycle và xử lý lỗi đúng contract.
- **ADVC-H3SD — Evaluate:** Đánh giá hardening và tối ưu bằng bằng chứng compiler, sanitizer, Valgrind, perf/gprof và quy tắc secure C phù hợp.

## 🧭 Ngữ cảnh nghề nghiệp/dự án và phần tăng trưởng của Unit

**Bối cảnh nghề nghiệp/dự án:** Trong dự án mô phỏng MDB Edge Diagnostics Gateway, process backend M07 và thread/IPC backend M08 đã có contract riêng. Integration maintainer cần thêm frontend TCP chỉ lắng nghe loopback, chuyển từng frame LF tới đúng backend và cung cấp evidence đủ để quality reviewer quyết định bàn giao.

**Project increment sau Unit này:** M09 tạo Networked diagnostics gateway release v9, protocol/concurrency tests, security/performance evidence và handoff note. Network case minh họa ADVC-H2SD; performance/security case minh họa ADVC-H3SD. Assignment 09 dùng cả hai để tạo terminal handoff.

**Mức xác thực của bối cảnh:** simulated. Mọi endpoint, payload và workload đều synthetic; đây không phải hệ thống hay dữ liệu khách hàng thật.

## 📚 Nguồn đầu vào đã map

- POSIX.1-2017: https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/
- Linux man-pages, socket/epoll APIs: https://www.kernel.org/doc/man-pages/
- TCP RFC 9293: https://www.rfc-editor.org/rfc/rfc9293.html
- UDP RFC 768: https://www.rfc-editor.org/rfc/rfc768.html
- Linux kernel 5.15 documentation: https://docs.kernel.org/5.15/
- GCC 11.4 manuals: https://gcc.gnu.org/onlinedocs/gcc-11.4.0/
- GNU gprof 2.38: https://sourceware.org/binutils/docs-2.38/gprof/
- SEI CERT C: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/
- CWE 4.20: https://cwe.mitre.org/
- Clang 14 sanitizer documentation: https://releases.llvm.org/14.0.0/tools/clang/docs/
- Valgrind Memcheck: https://valgrind.org/docs/manual/mc-manual.html

---

## 1. Kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết

- Robust POSIX I/O: partial transfer, EINTR, EOF và ownership của file descriptor.
- Process/signal lifecycle của S07; mutex/condition/thread lifecycle của S08.
- C17 bounds, ownership, build CMake/CTest và cách đọc sanitizer/Valgrind evidence.
- Baseline artifacts: Process job-runner backend và Thread-pool shared-memory backend cùng verification reports.

### Môi trường, công cụ và phiên bản

- Ubuntu 22.04, kernel 5.15 baseline; GCC 11.4 hoặc Clang 14; C17.
- glibc 2.35, CMake 3.22, Valgrind 3.18.1, GNU Binutils/gprof 2.38.
- Network chỉ bind 127.0.0.1 với port 0. Không cần root, capability hay thay đổi sysctl.
- Kiểm tra nhanh:

~~~sh
uname -r
gcc --version
perf --version
valgrind --version
~~~

Nếu perf bị policy của host từ chối, giữ nguyên policy và ghi đúng diagnostic là BLOCKED-PMU. Không biến việc thiếu counter thành kết quả đạt.

### Phương thức xác minh artifact

Material được artifact review theo mapping outline/LO và các oracle được nêu. Hai chương trình hoàn chỉnh của Example có executable verification riêng trong thư mục assets.

## 2. Định vị trong lộ trình (Mental Map)

S07 cung cấp process backend và robust descriptor lifecycle; S08 cung cấp thread/IPC backend cùng happens-before. S09 đặt epoll frontend trước hai backend, rồi dùng profiling và defensive C để quyết định release. Dòng dữ liệu là:

TCP bytes → per-connection input state → LF frame → dispatcher → process hoặc thread backend → queued response → partial send.

Quyết định then chốt không phải “chọn epoll vì nhanh”, mà là: framing contract nào; state nào thuộc connection; readiness mode nào; giới hạn input nào; lifecycle nào đóng FD; evidence nào đủ để chấp nhận một thay đổi tối ưu.

## 3. Nội dung lý thuyết cốt lõi

**Phạm vi nội dung:**

- [x] TCP/UDP socket programming, client-server model, blocking vs non-blocking I/O, select/poll/epoll event loop, protocol framing & serialization, timeout and connection lifecycle handling
- [x] Performance & security hardening: profiling with perf/gprof, cache locality, compiler optimization levels and undefined-behaviour pitfalls; defensive C and common CWE (buffer overflow, use-after-free, integer overflow, format string)

#### OUT-S09-01 — TCP/UDP socket programming, client-server model, blocking vs non-blocking I/O, select/poll/epoll event loop, protocol framing & serialization, timeout and connection lifecycle handling

**Mapping:** OUT-S09-01 · ADVC-H2SD · M09 epoll TCP frontend.

##### Định nghĩa rõ ràng

Socket là endpoint I/O. TCP cung cấp byte stream tin cậy, có thứ tự; nó không bảo toàn ranh giới giữa các lần send và recv. UDP chuyển datagram: mỗi receive lấy một datagram hoặc một phần bị cắt nếu buffer quá nhỏ; UDP không tự tạo reliability hay connection lifecycle như TCP.

Client-server mô tả vai trò khởi tạo và chấp nhận kết nối, không quyết định blocking mode. Với blocking I/O, lời gọi có thể ngủ cho tới khi tiến triển; với O_NONBLOCK, thao tác không thể tiến triển ngay trả lỗi EAGAIN hoặc EWOULDBLOCK. select, poll và epoll báo readiness; chúng không cam kết toàn bộ request hay response đã sẵn sàng.

Framing là contract tầng ứng dụng biến byte stream thành message. Serialization quy định biểu diễn field; không được gửi raw struct vì padding, alignment và endianness không phải wire contract. DC-LINE của khóa dùng LF làm delimiter và giới hạn payload 4096 byte như một training constraint.

##### Vấn đề/vai trò và quyết định cần đưa ra

Integration maintainer phải quyết định:

- TCP hay UDP dựa trên semantics, không dựa trên thói quen;
- blocking thread-per-connection hay một non-blocking event loop;
- select/poll/epoll theo portability, số FD và platform boundary;
- framing, size limit, malformed-input policy và response ordering;
- level-triggered hay edge-triggered epoll;
- timeout, half-close, reset, error/hangup và graceful-shutdown transitions;
- owner duy nhất chịu trách nhiệm epoll DEL và close.

Artifact chịu tác động là frontend M09 và protocol tests. Sai framing có thể tạo response thiếu, gộp sai hoặc treo dù TCP không mất byte.

##### Cơ chế và mental model

Một connection cần ít nhất: FD; input buffer và số byte hợp lệ; output buffer, length và sent offset; lifecycle state; last-activity timestamp; backend request correlation. recv có thể trả 1 byte, nhiều frame, 0 khi peer orderly shutdown, hoặc -1. Với non-blocking FD, EAGAIN nghĩa là dừng vòng drain và chờ readiness mới, không phải disconnect.

Level-triggered epoll tiếp tục báo khi trạng thái còn ready, dễ làm baseline đúng. Edge-triggered chỉ báo khi trạng thái thay đổi; mỗi accept/recv/send phải drain tới EAGAIN, nếu không dữ liệu có thể nằm lại mà không có edge mới. EPOLLIN có thể đi cùng EPOLLRDHUP, EPOLLHUP hoặc EPOLLERR; state machine phải xử lý tổ hợp, không dùng chuỗi nhánh loại trừ giả định chỉ có một cờ.

select sửa fd_set và có giới hạn triển khai; poll dùng mảng pollfd và quét tuyến tính; epoll duy trì interest/ready sets trong kernel, Linux-specific. Cả ba chỉ là multiplexing, không thay framing và không loại bỏ short I/O.

##### Khi dùng / khi không dùng

- Dùng TCP khi cần ordered reliable stream và chấp nhận tự định nghĩa framing. Dùng UDP khi message nhỏ, datagram boundary có giá trị và ứng dụng có policy riêng cho loss/reorder.
- Dùng epoll cho Linux service nhiều FD. Dùng poll khi cần code đơn giản/portable hơn với số FD vừa phải. Không ép epoll vào chương trình một connection chỉ để “tối ưu”.
- Dùng level-triggered trước khi correctness ổn định. Chỉ dùng edge-triggered khi có drain loops và test EAGAIN đầy đủ.
- Không giữ unbounded buffer chờ LF. Không coi timeout là độ chính xác tuyệt đối; clock phải monotonic và policy phải nói rõ idle hay absolute deadline.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** integration maintainer cần chứng minh split/coalesced TCP writes không phá DC-LINE.
- **Input/baseline/constraint:** client loopback gửi “PI”, sau đó “NG\nECHO xin-chao\n”; listener bind port 0; tối đa tám connection trong fixture.
- **Decision/action:** level-triggered epoll; accepted FD non-blocking/CLOEXEC; input giữ qua nhiều recv; output giữ sent offset.
- **Artifact/output:** assets/epoll_line_demo.c.
- **Expected result:** hai frame tạo hai response; child exit 0; số FD của parent trở về baseline.
- **Verification/oracle/evidence:**

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2   assets/epoll_line_demo.c -o epoll_line_demo
timeout 10s ./epoll_line_demo
~~~

Expected: frames=2 responses=2 child_exit=0 fd_delta=0.

##### Ví dụ code cụ thể

Micro-example dưới đây cô lập đúng hai contract khó quan sát của byte stream: một frame có thể bị chia qua nhiều lần gửi, và một lần `recv` có thể chứa phần cuối của frame trước cùng frame kế tiếp. `socketpair(AF_UNIX, SOCK_STREAM)` giữ toàn bộ traffic trong process/host; `poll` chỉ cung cấp readiness, còn `line_state` mới sở hữu framing state qua nhiều lần `recv`. Ví dụ không triển khai TCP listener, `epoll`, backend hay tải nhiều client nên không tiết lộ lời giải Assignment.

```c
#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct {
    char bytes[32];
    size_t used;
    unsigned frames;
} line_state;

static int send_all(int fd, const char *data, size_t length) {
    size_t sent = 0;
    while (sent < length) {
        const ssize_t rc = send(fd, data + sent, length - sent, 0);
        if (rc > 0) {
            sent += (size_t)rc;
        } else if (rc < 0 && errno == EINTR) {
            continue;
        } else {
            return -1;
        }
    }
    return 0;
}

static int append_and_emit(line_state *state, const char *chunk, size_t length) {
    if (length > sizeof(state->bytes) - state->used) {
        return -1;
    }
    memcpy(state->bytes + state->used, chunk, length);
    state->used += length;

    for (;;) {
        char *newline = memchr(state->bytes, '\n', state->used);
        if (newline == NULL) {
            return 0;
        }
        const size_t frame_length = (size_t)(newline - state->bytes);
        ++state->frames;
        printf("frame[%u]=%.*s\n", state->frames, (int)frame_length, state->bytes);
        const size_t consumed = frame_length + 1U;
        memmove(state->bytes, state->bytes + consumed, state->used - consumed);
        state->used -= consumed;
    }
}

int main(void) {
    int peers[2];
    if (socketpair(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0, peers) != 0) {
        perror("socketpair");
        return 1;
    }
    const int flags = fcntl(peers[1], F_GETFL);
    if (flags < 0 || fcntl(peers[1], F_SETFL, flags | O_NONBLOCK) != 0) {
        perror("fcntl");
        return 1;
    }
    if (send_all(peers[0], "AL", 2U) != 0 ||
        send_all(peers[0], "PHA\nBETA\n", 9U) != 0 ||
        shutdown(peers[0], SHUT_WR) != 0) {
        fputs("fixture write failed\n", stderr);
        return 1;
    }

    line_state state = {0};
    int saw_eof = 0;
    while (!saw_eof) {
        struct pollfd readable = {.fd = peers[1], .events = POLLIN};
        if (poll(&readable, 1, 1000) <= 0) {
            fputs("poll timeout/error\n", stderr);
            return 1;
        }
        for (;;) {
            char chunk[3];
            const ssize_t rc = recv(peers[1], chunk, sizeof(chunk), 0);
            if (rc > 0) {
                if (append_and_emit(&state, chunk, (size_t)rc) != 0) {
                    fputs("frame too large\n", stderr);
                    return 1;
                }
            } else if (rc == 0) {
                saw_eof = 1;
                break;
            } else if (errno == EINTR) {
                continue;
            } else if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
            } else {
                perror("recv");
                return 1;
            }
        }
    }

    (void)close(peers[0]);
    (void)close(peers[1]);
    printf("frames=%u buffered=%zu eof=%d\n", state.frames, state.used, saw_eof);
    return (state.frames == 2U && state.used == 0U) ? 0 : 1;
}
```

Lưu snippet thành `/tmp/s09_framing.c`, rồi build/run trong Ubuntu Jammy với network bị tắt:

```sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 \
  /tmp/s09_framing.c -o /tmp/s09_framing
timeout 5s /tmp/s09_framing >/tmp/s09_framing.out 2>/tmp/s09_framing.err
status=$?
cat /tmp/s09_framing.out
test "$status" -eq 0
test ! -s /tmp/s09_framing.err
```

Stdout chính xác là:

```text
frame[1]=ALPHA
frame[2]=BETA
frames=2 buffered=0 eof=1
```

Stderr rỗng và exit code là `0`. Oracle không dựa vào số lần `recv`: nó buộc đủ hai frame theo đúng thứ tự, không còn byte dở dang và chỉ kết thúc sau EOF. Vì vậy việc kernel coalesce hay split các write không làm thay đổi pass/fail.

##### Best practices

- **Rule:** parser hoạt động trên persistent input state. **Rationale:** TCP không giữ write boundary. **Positive:** “PI” được giữ tới khi “NG\n” đến. **Negative:** xử lý mỗi recv như một request sẽ trả ERR cho “PI” hoặc bỏ frame thứ hai.
- **Rule:** mọi pending output có sent offset và EPOLLOUT chỉ bật khi còn byte. **Rationale:** send có thể short/EAGAIN. **Positive:** resume từ output_sent. **Negative:** gửi lại từ đầu gây duplicate bytes.
- **Rule:** listener và accepted sockets đều non-blocking/CLOEXEC. **Rationale:** accept có thể hết queue giữa readiness và call; FD không được rò qua exec. **Positive:** accept4 với flags và drain tới EAGAIN. **Negative:** một blocking accepted FD làm cả event loop treo.
- **Rule:** close có một owner và idempotent state. **Rationale:** event flags có thể cùng báo lỗi/EOF. **Positive:** epoll DEL rồi close đúng một lần. **Negative:** hai path cleanup tạo double-close và có thể đóng nhầm FD đã được tái sử dụng.
- **Rule:** bounds được kiểm trước phép cộng/copy. **Rationale:** overflow biến kiểm tra capacity thành vô nghĩa. **Positive:** reject khi incoming > capacity - used. **Negative:** kiểm used + incoming > capacity sau khi phép cộng đã wrap.

##### Anti-pattern, failure modes và troubleshooting

| Dấu hiệu | Nguyên nhân thường gặp | Chẩn đoán/evidence | Sửa và phòng tránh |
|---|---|---|---|
| Response chỉ xuất hiện khi client đóng | Parser chờ EOF thay vì delimiter | Trace recv cho thấy LF đã có trong buffer | Parse mọi complete frame sau mỗi append |
| CPU 100% khi không có traffic | Retry EAGAIN trong vòng kín | strace lặp recv/send EAGAIN | Trả quyền về epoll và chỉ bật interest cần thiết |
| Edge-triggered server treo ngẫu nhiên | Không drain tới EAGAIN | Socket còn data nhưng không có edge mới | Dùng LT baseline hoặc hoàn chỉnh drain loop |
| Mất cuối response | Đóng ngay khi recv trả 0 | Output queue còn pending tại close | Half-close input, flush output rồi close |
| FD tăng sau mỗi test | Thiếu close ở accept/error path | So sánh /proc/self/fd theo run | Gán owner và một cleanup transition |

#### OUT-S09-02 — Performance & security hardening: profiling with perf/gprof, cache locality, compiler optimization levels and undefined-behaviour pitfalls; defensive C and common CWE (buffer overflow, use-after-free, integer overflow, format string)

**Mapping:** OUT-S09-02 · ADVC-H3SD · M09 security/performance evidence.

##### Định nghĩa rõ ràng

Profiling là đo nơi tài nguyên được tiêu thụ trên workload xác định. perf đọc software/hardware events qua kernel; event availability phụ thuộc host và policy. gprof cần compile và link với -pg, tạo gmon.out khi process kết thúc bình thường và làm thay đổi đặc tính chạy.

Cache locality gồm spatial locality (truy cập địa chỉ gần nhau) và temporal locality (tái dùng sớm). C lưu mảng nhiều chiều theo row-major; duyệt khác layout thường tạo nhiều cache miss hơn nhưng mức chênh là đặc tính host/workload, không phải hằng số của ngôn ngữ.

Optimization level là tập phép biến đổi của compiler. -O0 hữu ích cho debug; -O2 thường là release baseline; -O3 thêm biến đổi mạnh hơn; -Ofast có thể bỏ strict standards compliance nên không phải mặc định cho code cần semantics C17 nghiêm ngặt. Undefined behavior cho phép compiler giả định hành vi bị cấm không xảy ra; “chạy đúng ở -O0” không chứng minh code hợp lệ.

Defensive C biến input/lifetime/arithmetic/format assumptions thành checks và ownership contracts. CWE-120, CWE-416, CWE-190 và CWE-134 lần lượt phân loại buffer copy without bounds, use-after-free, integer overflow/wrap và externally controlled format string; CWE là taxonomy, không thay thế quy tắc C17/CERT C.

##### Vấn đề/vai trò và quyết định cần đưa ra

Quality reviewer cần quyết định thay đổi tối ưu có được giữ hay không và release có blocking weakness không. Quyết định phải dựa trên cùng input/checksum, fingerprint compiler/kernel/CPU, nhiều lần chạy và evidence path. Security decision phải nối weakness class với source path, trigger, corrective contract và after evidence; không được suy luận “sanitizer clean = không có UB”.

##### Cơ chế và mental model

Luồng đo hợp lệ là: khóa workload và correctness oracle → profile baseline → xác định hotspot → thay đúng một quyết định → chạy lại correctness → đo lại cùng điều kiện → ghi giới hạn. perf stat tổng hợp counters; perf record/report lấy samples; gprof cho call-graph/call-count theo instrumentation.

UB thường làm thay đổi observable behavior khi optimization thay đổi: signed overflow, out-of-bounds pointer, lifetime kết thúc hoặc format/type mismatch. Sanitizer chỉ quan sát path đã chạy. Compiler warnings, UBSan/ASan, Valgrind, static analysis, boundary tests và code review là các lớp evidence bổ sung, không lớp nào đơn độc là chứng minh tổng quát.

##### Khi dùng / khi không dùng

- Dùng perf khi host cho phép và cần counter/sample Linux. Không xin root hay hạ perf_event_paranoid cho bài học.
- Dùng gprof cho call instrumentation đơn giản trên build riêng. Không so timing của binary -pg với release binary như cùng điều kiện.
- Tối ưu layout/algorithm khi profile chỉ ra hotspot và checksum giữ nguyên. Không tối ưu theo một lần chạy hoặc theo cảm giác.
- Dùng ASan+UBSan ở debug build và Valgrind trên binary không ASan. TSan là build riêng.
- Không dùng -Ofast nếu chưa chứng minh semantics số học được phép thay đổi.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** reviewer đánh giá scan workload và format handling trước handoff.
- **Input/baseline/constraint:** ma trận 256×256 synthetic, cùng repetitions, payload “%n%s%x”.
- **Decision/action:** so row/column access; giữ checksum làm correctness oracle; in payload qua literal format; parse repetitions với range/errno.
- **Artifact/output:** assets/profile_hardening_demo.c.
- **Expected result:** row và column có checksum bằng nhau; payload được in nguyên văn; elapsed time chỉ là observation.
- **Verification/oracle/evidence:**

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2   assets/profile_hardening_demo.c -o profile_demo
./profile_demo row 200 '%n%s%x'
./profile_demo column 200 '%n%s%x'
~~~

Hai dòng mode phải có cùng checksum và payload=%n%s%x. Không đặt pass/fail theo elapsed_ns.

##### Ví dụ code cụ thể

Micro-example này tách correctness khỏi timing: cùng phép tính phải cho một checksum xác định ở `-O0`, `-O2` và sanitizer build. Kiểm tra overflow diễn ra trước phép nhân; chuỗi đối kháng được truyền như dữ liệu cho literal format `%s`, không bao giờ trở thành format string. Ví dụ chỉ xử lý một mảng nhỏ, không dùng matrix, profiler hay gateway code của Assignment.

```c
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static bool checked_scaled_sum(const uint32_t *values, size_t count,
                               uint32_t factor, uint64_t *sum_out) {
    uint64_t sum = 0;
    for (size_t index = 0; index < count; ++index) {
        if (factor != 0U && values[index] > UINT32_MAX / factor) {
            return false;
        }
        const uint64_t scaled = (uint64_t)values[index] * factor;
        if (sum > UINT64_MAX - scaled) {
            return false;
        }
        sum += scaled;
    }
    *sum_out = sum;
    return true;
}

int main(void) {
    static const uint32_t normal[] = {10U, 20U, 30U};
    static const uint32_t hostile[] = {UINT32_MAX};
    static const char payload[] = "%n%s%x";
    uint64_t checksum = 0;
    uint64_t ignored = 0;

    const bool normal_ok = checked_scaled_sum(normal, 3U, 3U, &checksum);
    const bool hostile_ok = checked_scaled_sum(hostile, 1U, 2U, &ignored);
    printf("checksum=%" PRIu64 " overflow_rejected=%d payload=%s\n",
           checksum, hostile_ok ? 0 : 1, payload);
    return (normal_ok && !hostile_ok && checksum == 180U) ? 0 : 1;
}
```

Lưu snippet thành `/tmp/s09_hardening.c`, rồi chạy các build độc lập trong Ubuntu Jammy:

```sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O0 \
  /tmp/s09_hardening.c -o /tmp/s09_hardening_O0
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 \
  /tmp/s09_hardening.c -o /tmp/s09_hardening_O2
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O1 -g \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  /tmp/s09_hardening.c -o /tmp/s09_hardening_san

/tmp/s09_hardening_O0 >/tmp/s09_O0.out 2>/tmp/s09_O0.err; s0=$?
/tmp/s09_hardening_O2 >/tmp/s09_O2.out 2>/tmp/s09_O2.err; s2=$?
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 \
UBSAN_OPTIONS=halt_on_error=1 \
  /tmp/s09_hardening_san >/tmp/s09_san.out 2>/tmp/s09_san.err; ss=$?
diff -u /tmp/s09_O0.out /tmp/s09_O2.out
diff -u /tmp/s09_O0.out /tmp/s09_san.out
test "$s0" -eq 0 -a "$s2" -eq 0 -a "$ss" -eq 0
test ! -s /tmp/s09_O0.err
test ! -s /tmp/s09_O2.err
test ! -s /tmp/s09_san.err
cat /tmp/s09_O2.out
```

Stdout chính xác của cả ba executable là:

```text
checksum=180 overflow_rejected=1 payload=%n%s%x
```

Mọi stderr rỗng, hai lệnh `diff` không in gì và exit code của từng executable là `0`. Checksum bằng nhau là oracle về equivalence qua optimization; `overflow_rejected=1` và payload được in nguyên văn là hai oracle security riêng. Thời gian chạy cố ý không thuộc oracle vì nó thay đổi theo host và scheduler.

##### Best practices

- **Rule:** profile trước, tối ưu sau. **Rationale:** nếu không biết hotspot, thay đổi có thể không tác động hoặc làm code khó kiểm chứng. **Positive:** gprof/perf evidence trỏ scan function và checksum giữ nguyên. **Negative:** đổi -O3 rồi tuyên bố nhanh hơn từ một lần chạy.
- **Rule:** cùng workload, warm-up/repetitions và fingerprint khi so sánh. **Rationale:** scheduling, CPU và counter multiplexing gây nhiễu. **Positive:** lưu raw runs và median/distribution. **Negative:** so hai input khác nhau hoặc hai host nhưng gọi là improvement.
- **Rule:** kiểm overflow trước phép cộng/cấp phát. **Rationale:** phép tính size đã wrap không thể cứu bằng kiểm tra sau. **Positive:** add <= MAX - used. **Negative:** used + add <= MAX với toán học có thể wrap.
- **Rule:** dữ liệu không tin cậy chỉ là argument của literal format. **Rationale:** format string điều khiển cách đọc argument và ghi bộ nhớ. **Positive:** printf("%s", payload). **Negative:** printf(payload) với “%n”.
- **Rule:** lifetime được biểu diễn bằng owner/state. **Rationale:** callback hoặc epoll event có thể tham chiếu state đã free. **Positive:** remove interest trước free và invalid hóa handle. **Negative:** free connection trong một branch rồi branch khác tiếp tục flush.
- **Rule:** sanitizer finding là blocking evidence, sanitizer-clean là bounded evidence. **Rationale:** dynamic tools chỉ thấy executed paths. **Positive:** ghi fixture coverage và residual risk. **Negative:** tuyên bố “không có UB” từ một test.

##### Anti-pattern, failure modes và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán/evidence | Sửa và phòng tránh |
|---|---|---|---|
| perf báo permission denied | Host policy chặn event | Lưu command, stderr và policy value | Ghi BLOCKED-PMU; dùng gprof cho objective còn lại; không đổi sysctl |
| gmon.out không có | Thiếu -pg ở compile/link hoặc abnormal exit | Kiểm build command và exit status | Build riêng với -pg ở cả hai giai đoạn, normal exit |
| -O0 pass, -O2 sai | UB/data race/uninitialized assumption | Warnings, UBSan/ASan, minimized fixture | Sửa root cause; không “fix” bằng tắt optimization |
| Benchmark dao động mạnh | Workload quá ngắn hoặc host nhiễu | Raw repetitions/distribution | Tăng bounded work, lưu fingerprint, không đặt ngưỡng phổ quát |
| Payload %n làm crash/ghi memory | Dùng input làm format | Compiler -Wformat-security và negative fixture | Dùng literal format, thêm test payload đối kháng |

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### Input/trạng thái ban đầu

Hai assets độc lập dùng dữ liệu synthetic. epoll_line_demo tạo listener loopback port 0 và một child client do parent sở hữu. profile_hardening_demo dùng matrix cố định, repetition bounded và payload có format specifiers.

### Cách thực hiện

Build bằng warning profile nghiêm ngặt. Chạy network fixture với timeout. Chạy hai access modes bằng cùng repetitions và so checksum. perf/gprof là evidence bổ sung; absence do permission phải được ghi trung thực.

### Output mong đợi

- Network: frames=2 responses=2 child_exit=0 fd_delta=0.
- Performance/security: checksum row bằng checksum column; payload được in literal; elapsed_ns có thể khác giữa lần chạy.
- Không có listener ngoài loopback, không dùng port cố định và không có process ngoài PID do fixture tạo bị signal.

### Cách xác minh

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 assets/epoll_line_demo.c -o epoll_line_demo
timeout 10s ./epoll_line_demo
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 assets/profile_hardening_demo.c -o profile_demo
./profile_demo row 200 '%n%s%x'
./profile_demo column 200 '%n%s%x'
~~~

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

1. **Test treo:** xác nhận timeout, loopback bind, client PID và pending output; không kill theo tên process. Chỉ signal PID child được fork bởi fixture.
2. **Address already in use:** fixture đúng phải dùng port 0; nếu code hardcode port, sửa bind contract thay vì retry vô hạn.
3. **EAGAIN bị log như lỗi:** kiểm O_NONBLOCK và readiness state; EAGAIN là điểm dừng drain, không phải fatal error.
4. **FD delta khác 0:** chụp /proc/self/fd trước/sau, truy owner của listener, epoll FD, accepted FD và error path.
5. **Perf không chạy:** lưu diagnostic, đánh dấu BLOCKED-PMU, vẫn chạy correctness/gprof; không dùng quyền cao hơn.
6. **Checksum khác giữa optimization levels:** dừng performance claim, điều tra UB trước.

## 6. Từ điển thuật ngữ và mô hình tư duy

- **Byte stream:** chuỗi byte có thứ tự, không có application message boundary.
- **Datagram:** message boundary do transport giữ, có thể mất/reorder.
- **Readiness:** trạng thái cho biết thao tác có khả năng tiến triển mà không block.
- **Level-triggered:** tiếp tục báo khi trạng thái ready còn tồn tại.
- **Edge-triggered:** báo khi trạng thái chuyển đổi; yêu cầu drain.
- **Framing:** quy tắc tách byte stream thành message.
- **Half-close:** một hướng TCP kết thúc trong khi hướng còn lại có thể tiếp tục.
- **Hotspot:** vùng tiêu thụ phần đáng kể resource trên workload đo.
- **Cache locality:** mức độ truy cập gần nhau hoặc tái sử dụng sớm.
- **Undefined behavior:** hành vi mà C standard không đặt requirement.
- **CWE:** danh mục weakness; không phải coding-rule implementation.
- **Oracle:** kết quả/quan hệ quan sát được quyết định pass, fail hoặc blocked.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

Các nguồn ở mục “Nguồn đầu vào đã map” được dùng ở chế độ reference và paraphrase. Ví dụ code được viết mới cho khóa, không sao chép implementation từ standard, kernel hay manual.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — user-approved project integration]:** M09 dùng chung process/thread backends và mở rộng Assignment 09 sang ADVC-H3SD.
- **[SUY DIỄN — course constraint]:** LF protocol, payload tối đa 4096 byte, command PING/ECHO và handoff artifact names là contract mô phỏng của khóa.
- **[BỔ SUNG — nguồn: RFC 9293, POSIX.1-2017, Linux man-pages]:** TCP byte-stream semantics, non-blocking error handling và epoll readiness model.
- **[BỔ SUNG — nguồn: GCC 11.4, Linux perf docs, GNU gprof 2.38]:** optimization/profile evidence contract.
- **[BỔ SUNG — nguồn: C17/CERT C/CWE/Clang/Valgrind]:** UB, defensive C, weakness mapping và giới hạn dynamic evidence.

---

# Session S07: Session 07 — System calls, processes and signals — Học liệu cốt lõi

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 04 — Linux System Programming: Process, Signal, IPC & Threads

## 🎯 Learning Outcomes

- **ADVC-H2SD — Create:** Xây dựng và kiểm chứng chương trình C trên Linux sử dụng process, signal và robust descriptor I/O với lifecycle, ownership và xử lý lỗi đúng contract.

## 🧭 Ngữ cảnh nghề nghiệp/dự án và phần tăng trưởng của Unit

**Bối cảnh nghề nghiệp/dự án:** MDB Edge Diagnostics Gateway — Simulated đã có quality-gated core v6. System maintainer cần chạy bounded synthetic commands trong child process để một job fail không làm hỏng process điều phối.

**Project increment sau Unit này:** M07 tạo Process job-runner backend, Process lifecycle verification report và A07 lifecycle decision note. Backend này được Assignment 09 tái sử dụng qua network routing.

**Mức xác thực của bối cảnh:** simulated, synthetic-only. Chỉ process/FD/PID do fixture hoặc bài làm tạo được quản lý; không signal process theo tên hoặc ngoài run-id.

## 📚 Nguồn đầu vào đã map

- POSIX.1-2017: https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/
- Linux man-pages: https://www.kernel.org/doc/man-pages/
- glibc 2.35 manual: https://sourceware.org/glibc/manual/2.35/
- SEI CERT C: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/
- Internal syllabus row S07.

---

## 1. Kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết

- C17 module, ownership và error-status contracts.
- Quality-gated gateway core v6; CMake/CTest và sanitizer evidence.
- Pointer lifetime, bounded buffer và public/private API boundary.

### Môi trường, công cụ và phiên bản

Ubuntu 22.04, Linux 5.15 baseline, glibc 2.35, GCC 11.4 hoặc Clang 14. Kiểm tra:

~~~sh
uname -a
getconf GNU_LIBC_VERSION
getconf OPEN_MAX
~~~

Process fixture chỉ exec /bin/sh hoặc /bin/sleep với synthetic arguments. Signal chỉ gửi tới self hoặc exact child PID. Không sudo, killall, pkill hay wildcard.

### Phương thức xác minh artifact

Material được artifact review theo OUT-S07-01/ADVC-H2SD. Worked example được build bằng C17 warning profile và chạy với timeout trong môi trường Linux cô lập.

## 2. Định vị trong lộ trình (Mental Map)

S06 cung cấp core v6 và quality gates. S07 thêm isolation bằng process:

command → pipe/FD ownership → fork → child async-safe pre-exec path → exec synthetic job → parent robust-read → wait/reap → typed terminal status.

S08 sẽ thêm shared-memory/thread backend; S09 sẽ chọn giữa process và thread paths. Vì vậy M07 phải bàn giao không chỉ code chạy được mà còn descriptor map, per-child terminal status và no-zombie evidence.

## 3. Nội dung lý thuyết cốt lõi

**Phạm vi nội dung:**

- [x] System call interface & file descriptors, robust I/O (partial read/write, EINTR), errno & error strategy; process lifecycle fork/exec/wait, exit status, zombie/orphan; signals with sigaction and async-signal-safety

#### OUT-S07-01 — System call interface & file descriptors, robust I/O (partial read/write, EINTR), errno & error strategy; process lifecycle fork/exec/wait, exit status, zombie/orphan; signals with sigaction and async-signal-safety

**Mapping:** OUT-S07-01 · ADVC-H2SD · M07 process job-runner backend.

##### Định nghĩa rõ ràng

System call là ranh giới yêu cầu kernel thực hiện thao tác. C library có thể bọc syscall và đặt errno khi operation báo lỗi. File descriptor là số nguyên process-local tham chiếu một open file description hoặc kernel object; dup/fork có thể tạo nhiều FD cùng tham chiếu, nên “close một số” và “resource đã hết owner” không đồng nghĩa.

Robust I/O chấp nhận read/write có thể chuyển ít byte hơn yêu cầu, bị EINTR, trả EOF hoặc fail. errno chỉ có nghĩa sau API trả error theo contract; một call thành công không bắt buộc xóa errno.

fork tạo child với bản sao virtual address space và descriptor table; parent/child cùng thừa hưởng open descriptions. exec thay process image nhưng giữ PID và các FD không có close-on-exec. wait/waitpid thu terminal status và giải phóng zombie metadata. Zombie là child đã kết thúc nhưng parent chưa wait; orphan là process còn chạy khi parent kết thúc và được hệ thống nhận nuôi — hai khái niệm không giống nhau.

Signal là asynchronous notification. sigaction đặt disposition/mask/flags. Handler chỉ được gọi async-signal-safe operations; thiết kế thông thường chỉ ghi volatile sig_atomic_t hoặc byte vào self-pipe, rồi main flow làm cleanup.

##### Vấn đề/vai trò và quyết định cần đưa ra

System maintainer phải quyết định:

- mỗi pipe end/FD thuộc parent hay child và close ở thời điểm nào;
- retry, return-progress hay fail khi short transfer/EINTR;
- exec failure được báo bằng status/channel nào;
- synchronous wait hay event-driven SIGCHLD/self-pipe;
- shutdown dừng nhận work, signal child nào, grace period và escalation nào;
- terminal status được encode thành domain status ra sao;
- evidence nào chứng minh each child exactly-one reap và không zombie.

Sai một unused pipe end có thể giữ reference khiến reader không bao giờ thấy EOF. Gọi malloc/printf trong handler có thể deadlock vì signal chen giữa library internal lock.

##### Cơ chế và mental model

Robust write giữ offset: khi write trả n > 0, tăng offset; EINTR khi return -1 thì retry theo policy; error khác được trả về cùng bytes-progress contract. Robust read xử lý bytes, EOF=0, EINTR retry và capacity trước append. Không đọc errno sau n >= 0.

Sau fork trong multi-threaded process, child chỉ có thread gọi fork nhưng library locks có thể đang ở trạng thái của thread khác; trước exec chỉ dùng async-signal-safe operations. exec success không return. exec fail phải dùng _exit, tránh exit vì atexit handlers và stdio buffers được copy từ parent.

wait status phải được giải mã bằng WIFEXITED/WEXITSTATUS, WIFSIGNALED/WTERMSIG, không so raw integer. waitpid có thể EINTR. Exactly-one terminal record gắn với exact PID; waitpid(-1) có thể phù hợp event loop nhưng ledger vẫn phải đối chiếu PID do service tạo.

SIGCHLD có thể coalesce; một notification không tương ứng đúng một child. Main flow phải reap trong loop đến khi không còn child ready. SA_RESTART có thể restart một số calls, không thay robust-I/O contract và không áp dụng đồng nhất cho mọi API.

##### Khi dùng / khi không dùng

- Dùng process backend khi cần isolation, exec program hoặc độc lập failure state. Không dùng khi shared in-memory state và low-overhead tasks là yêu cầu chính; thread pool có thể phù hợp hơn.
- Dùng pipe cho unidirectional byte stream parent-child. Không dùng raw struct làm external protocol; framing và serialization vẫn cần.
- Dùng blocking wait trong tool đơn giản có bounded child set. Dùng SIGCHLD/self-pipe khi main loop phải tiếp tục phục vụ nhiều nguồn event.
- Dùng SIGTERM cho graceful request khi child contract hỗ trợ; escalation chỉ sau deadline và chỉ exact owned PID.
- Không gọi fork-from-signal-handler, printf/malloc/pthread mutex trong handler hoặc system/popen khi mục tiêu là học fork/exec/wait contract.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** maintainer cần chứng minh output/status và controlled interrupt.
- **Input/baseline/constraint:** child exit fixture in “fixture-output” rồi exit 7; interrupt fixture exec sleep và chỉ nhận SIGTERM từ exact parent-owned PID.
- **Decision/action:** pipe có CLOEXEC ownership; child dup2/execv/_exit; parent bounded-read và waitpid retry; SIGINT handler chỉ đặt sig_atomic_t.
- **Artifact/output:** [assets/process_lifecycle_demo.c](assets/process_lifecycle_demo.c).
- **Expected result:** exit code 7 được decode, child reaped, FD delta 0; interrupt mode báo child terminated by SIGTERM và reaped.
- **Verification/oracle/evidence:**

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2   assets/process_lifecycle_demo.c -o process_demo
timeout 10s ./process_demo
timeout 10s ./process_demo interrupt
~~~

##### Ví dụ code cụ thể

Micro-example sau chỉ kiểm chứng một contract nhỏ: child gửi một frame cố định qua pipe rồi kết thúc với exit code `23`; parent phải đóng đúng pipe end, đọc đến EOF, giải mã wait status và reap đúng PID. Nó không dùng `exec`, signal handler hay tập job của Assignment 07, nên không cung cấp kiến trúc hoặc lời giải cho process backend M07.

Lưu snippet thành `/tmp/s07_pipe_wait.c`:

~~~c
#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int write_all(int fd, const char *data, size_t length) {
    size_t sent = 0;
    while (sent < length) {
        const ssize_t rc = write(fd, data + sent, length - sent);
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

int main(void) {
    int channel[2];
    if (pipe(channel) != 0) {
        perror("pipe");
        return 1;
    }

    const pid_t child = fork();
    if (child < 0) {
        perror("fork");
        (void)close(channel[0]);
        (void)close(channel[1]);
        return 1;
    }
    if (child == 0) {
        static const char message[] = "READY\n";
        (void)close(channel[0]);
        const int ok = write_all(channel[1], message, sizeof(message) - 1U);
        (void)close(channel[1]);
        _exit(ok == 0 ? 23 : 111);
    }

    (void)close(channel[1]);
    char buffer[16] = {0};
    size_t used = 0;
    int read_failed = 0;
    for (;;) {
        if (used == sizeof(buffer)) {
            fputs("frame too large\n", stderr);
            read_failed = 1;
            break;
        }
        const ssize_t rc = read(channel[0], buffer + used, sizeof(buffer) - used);
        if (rc > 0) {
            used += (size_t)rc;
        } else if (rc == 0) {
            break;
        } else if (errno != EINTR) {
            perror("read");
            read_failed = 1;
            break;
        }
    }
    (void)close(channel[0]);

    int status = 0;
    while (waitpid(child, &status, 0) < 0) {
        if (errno != EINTR) {
            perror("waitpid");
            return 1;
        }
    }
    if (read_failed != 0 || used != 6U || memcmp(buffer, "READY\n", 6U) != 0 ||
        !WIFEXITED(status) || WEXITSTATUS(status) != 23) {
        fputs("oracle failure\n", stderr);
        return 1;
    }

    printf("bytes=%zu payload=%.*s child_exit=%d reaped=1\n",
           used, (int)(used - 1U), buffer, WEXITSTATUS(status));
    return 0;
}
~~~

Biên dịch và chạy trên Ubuntu 22.04/Jammy:

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 \
  /tmp/s07_pipe_wait.c -o /tmp/s07_pipe_wait
timeout 5s /tmp/s07_pipe_wait
~~~

**Oracle bắt buộc:** compiler không phát warning; `stdout` chính xác là:

~~~text
bytes=6 payload=READY child_exit=23 reaped=1
~~~

`stderr` rỗng và exit code là `0`. Timeout, payload khác, raw status bị hiểu sai hoặc `reaped=1` không xuất hiện đều là FAIL.

**Quyết định và giải thích:** parent đóng write end ngay sau `fork`, nên EOF chỉ xuất hiện sau khi child đóng owner cuối cùng; cả `write` và `waitpid` đều có policy retry `EINTR`; status chỉ được đọc sau `WIFEXITED`. Vì vậy oracle đồng thời kiểm byte-progress, FD ownership và exactly-one reap thay vì chỉ kiểm “process đã chạy”.

##### Best practices

- **Rule:** vẽ descriptor ownership map trước fork. **Rationale:** mọi inherited pipe end giữ kernel reference. **Positive:** parent đóng write end, child đóng read end ngay. **Negative:** parent giữ write end nên read chờ EOF vô hạn.
- **Rule:** giữ bytes-completed offset cho I/O. **Rationale:** success không đồng nghĩa full count. **Positive:** advance trên n > 0, retry EINTR. **Negative:** gọi lại từ buffer start tạo duplicate bytes.
- **Rule:** đọc errno chỉ sau documented error return. **Rationale:** errno có thể giữ giá trị cũ. **Positive:** branch amount < 0 trước switch errno. **Negative:** amount > 0 nhưng errno cũ làm code báo fail.
- **Rule:** child pre-exec path chỉ async-signal-safe và dùng _exit khi exec fail. **Rationale:** fork có thể copy inconsistent library state/buffer. **Positive:** close/dup2/execv/_exit. **Negative:** perror/exit/malloc trong child của multi-threaded parent.
- **Rule:** terminal status luôn qua WIF*/W* macros và one ledger entry/PID. **Rationale:** raw wait status được encode. **Positive:** distinguish exit 7 và SIGTERM. **Negative:** status == 7 hoặc double wait.
- **Rule:** handler chỉ chuyển event sang main context. **Rationale:** most library calls không async-safe. **Positive:** set sig_atomic_t/self-pipe write. **Negative:** printf, free hoặc pthread_mutex_lock trong handler.
- **Rule:** signal exact PID/PGID do run tạo và xác minh ownership. **Rationale:** wildcard có thể tác động process khác. **Positive:** kill(child_pid,SIGTERM). **Negative:** pkill job_runner.

##### Anti-pattern, failure modes và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán/evidence | Sửa và phòng tránh |
|---|---|---|---|
| Reader treo sau khi child exit | Một write end vẫn mở | lsof hoặc /proc/PID/fd map | Đóng unused ends ngay sau fork |
| Duplicate/missing output | Không giữ partial-I/O offset | Inject short writes, compare checksum | Loop theo bytes completed |
| “Success” nhưng errno khác 0 | Dùng stale errno | Log return value trước errno | Chỉ inspect errno trên error |
| Child exit 127 không giải thích | exec path fail | Dedicated status/ledger, executable path | Phân biệt exec failure; _exit contract |
| Zombie xuất hiện | Thiếu wait/reap loop | ps state Z, child ledger thiếu terminal row | waitpid đúng PID; drain SIGCHLD events |
| Deadlock trong signal path | Handler gọi unsafe function/lock | Backtrace dừng trong stdio/malloc lock | Handler chỉ flag/self-pipe; cleanup ở main |
| Shutdown signal nhầm process | PID lookup/wildcard không có ownership | Audit exact PID/run-id | Chỉ signal PID đã spawn và chưa reaped |

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### Input/trạng thái ban đầu

Asset có hai independent modes. Exit mode kết nối parent-child bằng pipe và exec synthetic shell command. Interrupt mode tạo exact child sleep PID; parent tự nhận SIGINT, handler đặt flag, main flow gửi SIGTERM đúng PID và wait.

### Cách thực hiện

Build C17 strict warning profile trong Linux sandbox. Chạy mỗi mode với timeout. Quan sát decoded status, reaped flag và FD delta; không dựa vào process-name scan.

### Output mong đợi

~~~text
child_output=fixture-output
mode=exit exited=1 code=7 reaped=1 fd_delta=0
mode=interrupt requested=1 signal=15 reaped=1
~~~

SIGTERM thường có số 15 trên Linux target đã khóa. Pass/fail của code dùng SIGTERM macro và WTERMSIG, không hardcode raw wait status.

### Cách xác minh

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 assets/process_lifecycle_demo.c -o process_demo
timeout 10s ./process_demo
timeout 10s ./process_demo interrupt
~~~

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

1. **Build không thấy POSIX declarations:** compile trên Ubuntu target với feature-test macro nằm trong asset; không “sửa” bằng implicit declaration.
2. **Exit mode timeout:** kiểm FD ownership trước; một inherited write end thường chặn EOF.
3. **Code/status sai:** in WIFEXITED/WIFSIGNALED branches riêng; không in raw status như exit code.
4. **Interrupt mode không kết thúc:** xác nhận handler chỉ đặt flag và main flow dùng exact child_pid; không signal bằng tên.
5. **FD delta khác 0:** so /proc/self/fd và trace mọi setup/error path; thêm one-owner cleanup.
6. **EINTR bị coi fatal:** xác nhận syscall return -1 rồi mới inspect errno; retry theo operation policy.
7. **Core fixture chạy nhưng project fail:** so baseline artifact version/commit, environment và public status contract; Example không thay integration tests.

## 6. Từ điển thuật ngữ và mô hình tư duy

- **FD:** process-local handle tới kernel open description/object.
- **Open file description:** kernel state có offset/status flags có thể được nhiều FD chia sẻ.
- **Partial I/O:** operation tiến triển ít hơn count yêu cầu nhưng vẫn thành công.
- **EINTR:** syscall bị signal interrupt và trả lỗi theo API/flags.
- **fork:** tạo child process image từ caller.
- **exec:** thay process image, giữ PID và non-CLOEXEC FDs.
- **Zombie:** terminated child chưa được parent wait.
- **Orphan:** running process mất parent ban đầu.
- **Async-signal-safe:** operation được POSIX cho phép gọi trong signal handler.
- **Reap ledger:** evidence mỗi owned PID có đúng một terminal wait status.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

POSIX.1-2017, Linux man-pages, glibc 2.35, CERT C và syllabus. Nội dung được paraphrase; C asset được viết mới.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — user-approved project spine]:** gateway M07, artifact names và downstream A09 reuse.
- **[SUY DIỄN — course fixture]:** shell exit 7, sleep child và FD-delta oracle.
- **[BỔ SUNG — nguồn: POSIX.1-2017/Linux man-pages]:** partial I/O, fork/exec/wait, signal and async-safety semantics.
- **[BỔ SUNG — nguồn: CERT C]:** ownership/error/handler discipline.

---

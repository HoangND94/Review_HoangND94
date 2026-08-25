# Session S07: Session 07 — System calls, processes and signals — Ví dụ và nghiên cứu tình huống

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 04 — Linux System Programming: Process, Signal, IPC & Threads

## 🎯 Learning Outcomes liên quan

- **ADVC-H2SD:** tạo và kiểm chứng robust descriptor I/O, fork/exec/wait status và signal-safe shutdown contract.

## 🧭 Liên kết với ngữ cảnh nghề nghiệp/dự án

**Bối cảnh nghề nghiệp/dự án:** MDB Edge Diagnostics Gateway — Simulated cần process backend M07 trước khi network frontend M09 có thể route command vào isolated child jobs.

**Project increment được minh họa:** M07 process lifecycle slice: pipe ownership, bounded output, exit/signal status, exact-child signaling, exactly-one reap và FD cleanup.

## 🧰 Điều kiện chạy ví dụ

**Kiến thức/kỹ năng tiên quyết:** C17, file descriptors, ownership, compiler warning profile và process-local evidence.

**Môi trường, công cụ và phiên bản:** Ubuntu 22.04/Linux 5.15, glibc 2.35, GCC 11.4 hoặc Clang 14. Fixture chỉ exec /bin/sh và /bin/sleep với synthetic arguments. Không root; không signal ngoài child PID.

**Phương thức xác minh artifact:** executable.

## 📚 Nguồn đầu vào đã map

POSIX.1-2017, Linux man-pages, glibc 2.35, CERT C và internal syllabus; nội dung được paraphrase.

---

### Mapping case đã chốt trong course plan

- **CASE-S07-01:** ADVC-H2SD · OUT-S07-01 · authenticity inherited.

**Mức xác thực mặc định:** simulated, synthetic-only.

## Case Study 01: Thu output, decode terminal status và dừng exact child an toàn

### 1. Ticket và tiêu chí thành công

- **Vai trò/stakeholder:** system maintainer và integration reviewer.
- **Vấn đề cần giải quyết:** chứng minh parent không mất output, không nhầm raw wait status, không để zombie/FD và không dùng unsafe handler/wildcard signal.
- **Learning Outcome và outline item:** ADVC-H2SD · OUT-S07-01.
- **Project increment/professional artifact liên quan:** M07 Process job-runner backend.
- **Tiêu chí thành công:** exit mode thu chính xác “fixture-output”, decode exit 7, reap child và FD delta 0; interrupt mode handler chỉ đặt flag, main flow SIGTERM đúng child và reap signal status; cả hai hoàn tất trong timeout.

### 2. Input, trạng thái ban đầu và ràng buộc

Asset: [assets/process_lifecycle_demo.c](assets/process_lifecycle_demo.c).

Exit mode tạo một pipe, đặt FD_CLOEXEC, fork child, chuyển write end thành STDOUT rồi exec /bin/sh với command synthetic. Parent đóng write end, bounded-read tới EOF và waitpid exact PID.

Interrupt mode fork/exec /bin/sleep 10. Parent raise SIGINT cho chính nó; handler chỉ đặt volatile sig_atomic_t. Main flow sau handler gửi SIGTERM tới child_pid và wait. Nếu setup thất bại, cleanup chỉ dùng exact PID.

Không có input bên ngoài, process-name discovery, production command, sudo, killall hoặc pkill.

### 3. Phân tích lựa chọn

- **popen/system:** ngắn nhưng che fork/exec/wait contract nên không phù hợp mục tiêu.
- **printf trong handler:** dễ quan sát nhưng không async-signal-safe và có thể deadlock.
- **flag + main-flow cleanup:** được chọn; handler tối thiểu, lifecycle và errors được xử lý ở normal context.
- **raw status comparison:** sai vì wait status encoded. Fixture dùng WIFEXITED/WEXITSTATUS và WIFSIGNALED/WTERMSIG.
- **FD_CLOEXEC:** đặt trên cả pipe ends; write end được dup2 vào STDOUT nên target descriptor tồn tại qua exec theo chủ ý, original pipe FD được đóng.

Trade-off: fixture dùng blocking read/wait vì chỉ có một bounded child. M07 service có thể cần self-pipe/SIGCHLD event integration, nhưng cùng ownership/status invariants.

### 4. Cách triển khai

Chương trình hoàn chỉnh nằm trong asset và gồm:

- read_bounded giữ bytes-progress, retry EINTR và reject buffer exhaustion;
- wait_owned_child retry waitpid khi EINTR;
- child pre-exec path chỉ close, dup2, execv, _exit;
- status decode qua POSIX macros;
- signal handler chỉ gán sig_atomic_t;
- cleanup signal dùng exact fork return PID;
- /proc/self/fd before/after oracle cho exit mode.

Đây là lời giải của case nhỏ, không phải reference implementation cho Assignment 07: nó không quản lý job set, SIGCHLD drain loop, streaming output nhiều child hay graceful queue shutdown.

### 5. Output mong đợi

Exit mode:

~~~text
child_output=fixture-output
mode=exit exited=1 code=7 reaped=1 fd_delta=0
~~~

Interrupt mode:

~~~text
mode=interrupt requested=1 signal=15 reaped=1
~~~

Mỗi command phải exit 0. Timeout, signal khác, reaped=0, code khác hoặc fd_delta khác 0 là fail.

### 6. Cách xác minh

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2   assets/process_lifecycle_demo.c -o process_demo
timeout 10s ./process_demo
timeout 10s ./process_demo interrupt
~~~

Optional diagnostics:

~~~sh
strace -f -e trace=process,signal,read,write,close ./process_demo
strace -f -e trace=process,signal ./process_demo interrupt
~~~

strace không thay pass/fail oracle. Không chạy diagnostic lên PID ngoài fixture.

### 7. Giải thích sâu và failure modes

- **Read treo:** parent hoặc child còn giữ write end. Evidence: /proc/PID/fd cho thấy pipe writer chưa close.
- **Output duplicate:** retry write/read không giữ offset. Evidence: golden bytes/checksum sai.
- **Exit code in sai:** raw wait status bị dùng trực tiếp. Evidence: status không qua WIFEXITED branch.
- **Exit 127:** execv fail; cần phân biệt với application exit contract.
- **Interrupt deadlock:** handler gọi stdio/malloc/lock. Asset không gọi library ngoài sig_atomic_t assignment.
- **Child không reaped:** wait thiếu hoặc target PID sai; ps state Z/ledger thiếu terminal row.
- **Signal nhầm:** code lookup theo name hoặc wildcard. Policy bắt buộc exact PID trả về từ fork.
- **FD delta không 0:** missing close ở setup/error/normal branch. Descriptor ownership map là evidence sửa.

Giới hạn: /proc/self/fd là Linux-specific oracle; core process APIs được giảng theo POSIX target. Fixture không inject EINTR deterministically, vì vậy Assignment phải có wrapper/harness cho partial/EINTR paths.

### 8. Bài học chuyển giao

Assignment 07 mở rộng từ một child thành bounded job set, exec failure status, short-transfer injection, SIGINT/SIGCHLD shutdown và exactly-one terminal ledger. Học viên phải tự chọn decomposition; không sao chép case để thay process backend.

---

## Provenance của các case

### Nguồn được dùng

- POSIX.1-2017: pipe/read/write/fork/exec/wait/sigaction semantics.
- Linux man-pages: /proc FD diagnostic và target behavior.
- CERT C: error/ownership/signal-safety discipline.
- Asset được viết mới, không sao chép source của standard/manual.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — course fixture]:** /bin/sh exit 7, /bin/sleep và FD delta output.
- **[SUY DIỄN — user-approved project spine]:** M07 và downstream A09 reuse.
- **[BỔ SUNG — nguồn: POSIX/Linux man-pages]:** status decoding, EINTR và async-signal-safe pre-exec/handler model.


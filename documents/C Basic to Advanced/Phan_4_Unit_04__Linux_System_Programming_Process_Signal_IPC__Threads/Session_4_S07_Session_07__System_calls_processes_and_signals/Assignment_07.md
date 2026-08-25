# Session S07: Session 07 — System calls, processes and signals — Assignment 07

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 04 — Linux System Programming: Process, Signal, IPC & Threads

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASM-A07 (Assignment 07) |
| Thời lượng dự kiến | 150 phút |
| Độ khó | Hard |
| Bloom levels | Create |
| Mức xác thực | Simulated; synthetic-only |

## 🎯 Learning Outcomes được đánh giá

- **ADVC-H2SD:** tạo và kiểm chứng mini job runner dùng robust FD I/O, fork/exec/wait, typed terminal status, sigaction và bounded graceful shutdown.

| LO | Deliverables | Acceptance tests | Rubric |
|---|---|---|---|
| ADVC-H2SD | Process job-runner backend; lifecycle report; decision note | AT-A07-01..03 | RB-A07-01..04 |

## 🧠 Khái niệm và best practices được đánh giá

### CA-A07-PROCESS — Robust I/O và process/signal lifecycle

- **Concept/outline:** OUT-S07-01.
- **LO:** ADVC-H2SD.
- **Scenario/input:** quality-gated gateway core v6, synthetic job fixtures, public contract pack và CR-A07.
- **Rule 1:** read/write logic theo bytes-completed, retry EINTR khi API trả error và đóng unused pipe ends ngay sau fork. **Rationale:** POSIX cho phép partial transfer; leaked writer ngăn EOF và làm shutdown treo.
- **Rule 2:** child pre-exec path chỉ async-signal-safe; main context reap bằng waitpid và decode WIF*/W* macros; handler chỉ ghi flag/self-pipe state. **Rationale:** unsafe handler/pre-exec calls có thể deadlock; missing wait tạo zombie và mất failure semantics.
- **Deliverables:** Process job-runner backend; Process lifecycle verification report; A07 lifecycle decision note.
- **Oracles/evidence:** AT-A07-01 robust-I/O fixture; AT-A07-02 per-PID terminal ledger; AT-A07-03 controlled shutdown/no-zombie report.
- **Rubric:** RB-A07-01..04.

Đây là evaluation contract, không quy định data structure, event architecture, pipe topology, status encoding implementation hay thứ tự thao tác.

## 🧭 Bối cảnh nghề nghiệp/dự án và change request

**Bối cảnh nghề nghiệp/dự án:** Bạn là system maintainer của MDB Edge Diagnostics Gateway mô phỏng. Gateway core v6 đã có quality evidence nhưng chưa cô lập synthetic job failures.

**Project increment/change request cần hoàn thành:** M07 bổ sung process backend để spawn bounded commands, stream bounded output, thu exit/signal status và dừng an toàn khi nhận SIGINT/SIGCHLD.

**Scenario đã chốt trong plan:** CR-A07 yêu cầu mini job runner không dùng system/popen, không mất output/status, không để zombie và không signal process ngoài run. [material.md](material.md) và [example.md](example.md) là kiến thức/case tham khảo; Example asset không phải starter backend.

## 🔗 Liên kết project xuyên suốt

**Project milestone:** M07.

**Phụ thuộc vào Assignment trước:** ASM-A06.

**Baseline artifacts được sử dụng:** Quality-gated gateway core v6, đúng version đã accepted bởi A06.

**Artifacts Assignment này tạo ra:**

- Process job-runner backend.
- Process lifecycle verification report.

**Assignment sau sẽ tái sử dụng:** ASM-A09 dùng cả hai artifacts làm direct baseline cho process routing.

**Terminal delivery:** không áp dụng; A07 là increment trung gian.

## 🧰 Điều kiện thực hiện

### Kiến thức/kỹ năng tiên quyết

- Hoàn thành S06/ASM-A06; dùng được core v6 và quality evidence.
- C17 ownership/error contracts; bounded buffers.
- Linux FD, fork/exec/wait, sigaction và async-signal-safety từ S07.
- Chạy CMake/CTest, timeout và đọc /proc/PID evidence.

### Môi trường, công cụ và phiên bản

Ubuntu 22.04, Linux 5.15 baseline, glibc 2.35, GCC 11.4 hoặc Clang 14, CMake 3.22. Process tests chỉ spawn synthetic fixtures trong workspace. Signal tests chỉ gửi tới PID do harness tạo.

### Input và starter assets

- Quality-gated gateway core v6.
- Synthetic job fixtures gồm success, nonzero exit, signal termination, exec failure và bounded output.
- Public contract pack; CR-A07.
- Environment/run-id manifest.
- Không có production executable, customer payload, credential hay process-name target.

## 📋 Yêu cầu

### Functional requirements

- **FR-A07-01 · ADVC-H2SD:** spawn child bằng fork/exec; descriptor ownership đúng; exec failure có deterministic status contract.
- **FR-A07-02 · ADVC-H2SD:** collect/decode normal exit, nonzero exit, signal termination và exec failure; mỗi exact child PID có đúng một terminal ledger record.
- **FR-A07-03 · ADVC-H2SD:** SIGINT/SIGCHLD path dừng nhận work, xử lý bounded in-flight children, reap mọi direct child và exit không zombie.

### Non-functional requirements

- **NFR-A07-01 · ADVC-H2SD:** robust I/O xử lý short transfer, EINTR, EOF; errno chỉ được dùng sau documented error return; không busy-loop.
- **NFR-A07-02 · ADVC-H2SD:** handler chỉ dùng async-signal-safe operation; không malloc, printf, non-safe logging hoặc pthread lock.
- **NFR-A07-03 · ADVC-H2SD:** mọi test có deadline; chỉ signal exact PID/PGID do run tạo; cleanup không dùng wildcard và không tác động ngoài workspace/run-id.

### Ràng buộc và phạm vi loại trừ

- Không dùng system hoặc popen thay fork/exec/wait contract.
- Child path sau fork chỉ dùng async-signal-safe operations tới exec; exec failure kết thúc bằng _exit.
- Parent/child đóng mọi unused pipe end; intended inherited descriptors có CLOEXEC policy rõ.
- Không coi SA_RESTART là thay robust EINTR loops.
- Không killall, pkill, PID search theo tên hoặc signal PID chưa chứng minh thuộc current run.
- Không daemonize, chạy production command, dùng shell input không trusted hoặc thêm network scope.
- Bài làm độc lập; không cung cấp source/pseudo-code/walkthrough cho backend trong submission brief.

> [!IMPORTANT]
> Mọi design decision phải được chứng minh bằng behavior/status/resource evidence. Một process “đã kết thúc” nhưng chưa được reap vẫn là lifecycle failure.

## 📦 Deliverables và cách nộp

1. **Process job-runner backend:** source/public contract/build integration trong repository, clean-build được.
2. **Process lifecycle verification report:** per-job PID, input fixture, output checksum/length, terminal status class/value, exactly-one reap, descriptor/no-zombie and shutdown evidence.
3. **A07 lifecycle decision note:** FD ownership map, exec-failure/error policy, signal handler boundary, shutdown/escalation policy và residual risks.

**Submission contract:** nộp snapshot M07 cùng synthetic fixtures và PID/status evidence đã redact. Không nộp host-wide process listing, real command data, core dumps, build cache hoặc logs chứa absolute sensitive paths. Deliverable thiếu exact command, expected/actual result hoặc artifact version được xem là chưa đầy đủ.

## ✅ Acceptance criteria và output mong đợi

### AT-A07-01 — Robust pipe/FD I/O

**Given** harness ép short read/write, EINTR và EOF với bounded bytes; **when** backend stream data; **then** output bytes/checksum đúng, không lost/duplicate/busy-loop và mọi pipe end đóng theo owner map. Evidence: injected outcomes, progress ledger, checksum và FD before/after.

### AT-A07-02 — Terminal status ledger

**Given** jobs success, nonzero exit, signal termination và exec failure; **when** runner completes; **then** mỗi child PID có đúng expected decoded terminal class/value và exactly-one reap record. Evidence: spawn/exec/wait ledger; không dùng raw status như exit code.

### AT-A07-03 — Controlled shutdown/no zombie

**Given** nhiều owned synthetic children đang chạy; **when** harness gửi SIGINT chỉ tới runner PID; **then** runner dừng nhận job, thực hiện documented grace/escalation trong timeout, reap mọi direct child và final waitpid/no-zombie oracle đạt. Evidence: signal timeline, exact PID set, status ledger và scoped process check.

## 🧪 Cách xác minh

**Phương thức:** artifact_review với executable evidence.

~~~sh
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build/debug --target job_runner process_backend_tests
ctest --test-dir build/debug -R '^process_backend_' --output-on-failure
timeout --signal=INT --kill-after=2s 20s   ctest --test-dir build/debug -R '^process_shutdown_' --output-on-failure
~~~

Equivalent project commands được chấp nhận nếu resolve cùng AT IDs. Harness phải signal PID nó vừa spawn, không dùng process-name wildcard.

**Bằng chứng phải nộp:**

- exact environment/build commands và exit results;
- robust-I/O injection/progress report;
- per-child spawn/terminal/reap ledger;
- SIGINT/SIGCHLD shutdown timeline;
- descriptor ownership và no-zombie report;
- A07 lifecycle decision note.

## 📊 Rubric chấm điểm — tổng 100%

| ID | Tiêu chí | Trọng số | LO | Bằng chứng đạt | Chưa đạt |
|---|---|---:|---|---|---|
| RB-A07-01 | Spawn/exec/wait behavior và status contract | 35% | H2 | AT-A07-02 mọi job class đúng terminal status và exactly-one reap | Sai/mất status, forbidden launch shortcut hoặc missing/double reap |
| RB-A07-02 | Signal safety, graceful shutdown và no-zombie invariant | 30% | H2 | AT-A07-03 handler async-safe, shutdown bounded, không direct child/zombie | Unsafe handler, hang hoặc zombie/orphaned ownership |
| RB-A07-03 | Robust I/O, errno và FD lifecycle | 20% | H2 | AT-A07-01 short/EINTR/EOF đúng; owner/close evidence đầy đủ | Lost/duplicate bytes, stale errno, busy-loop hoặc FD leak |
| RB-A07-04 | Lifecycle evidence và decision note | 15% | H2 | Commands, PID/status/signal/cleanup decisions truy vết đủ | Evidence thiếu/stale hoặc policy không giải thích |

**Điểm đạt:** 70%. Signal ngoài owned PID/run-id hoặc unbounded cleanup là blocking safety failure.

## 📚 Nguồn đầu vào và provenance

### Nguồn đã map

POSIX.1-2017, Linux man-pages, glibc 2.35, CERT C và internal syllabus; reference/paraphrase only.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — user-approved project spine]:** M07 process backend, A06 baseline và A09 downstream reuse.
- **[SUY DIỄN — course fixtures]:** job classes, report/ledger shape và deadline harness.
- **[BỔ SUNG — nguồn: POSIX/Linux man-pages/CERT C]:** robust transfer, wait decoding, async-signal-safe and ownership/error contracts.

---

# Session S09: Session 09 — Network programming, performance and security hardening — Assignment 09

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 05 — Network Programming, Performance & Final Audit

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASM-A09 (Assignment 09) |
| Thời lượng dự kiến | 90 phút |
| Độ khó | Hard |
| Bloom levels | Create, Evaluate |
| Mức xác thực | Simulated; synthetic-only |

## 🎯 Learning Outcomes được đánh giá

- **ADVC-H2SD:** tạo và kiểm chứng TCP service non-blocking/epoll với framing, per-connection state, routing, timeout và graceful lifecycle.
- **ADVC-H3SD:** đánh giá defensive C và thay đổi tối ưu bằng sanitizer/Valgrind/profile evidence tái lập, có giới hạn claim rõ ràng.

Traceability tối thiểu:

| LO | Deliverable | Acceptance tests | Rubric |
|---|---|---|---|
| ADVC-H2SD | Gateway release, protocol/concurrency tests | AT-A09-01..03 | RB-A09-01..03 |
| ADVC-H3SD | Security/performance evidence, decision/handoff note | AT-A09-03..04 | RB-A09-03..04 |

## 🧠 Khái niệm và best practices được đánh giá

### CA-A09-NET — TCP byte stream và epoll readiness contract

- **Concept/outline:** OUT-S09-01.
- **LO:** ADVC-H2SD.
- **Scenario/input:** Hai accepted backend artifacts từ A07/A08; DC-LINE; change request CR-A09; fixtures có fragmented/coalesced frames, partial I/O, EOF/error và 100 simultaneous loopback clients.
- **Rule 1:** parse LF frames từ persistent per-connection input state và giữ pending output cùng sent offset. **Rationale:** TCP không giữ application write boundary; non-blocking recv/send có thể partial hoặc EAGAIN.
- **Rule 2:** coi readiness là quyền thử I/O, xử lý EINTR/EAGAIN/EOF/error/hangup/timeout bằng lifecycle state có một close owner. **Rationale:** nhiều event có thể đồng thời và readiness có thể thay đổi trước syscall.
- **Rule 3:** route qua cả process và thread/IPC public contracts, đồng thời giữ regression oracles của A07/A08. **Rationale:** terminal frontend chỉ tích hợp thật khi tiêu thụ output của cả hai direct dependencies.
- **Deliverables:** Networked diagnostics gateway release v9; A09 protocol and concurrency tests; A09 handoff and decision note.
- **Oracles/evidence:** AT-A09-01, AT-A09-02, AT-A09-03; protocol traces, load summary, FD baseline, backend regression summary.
- **Rubric:** RB-A09-01, RB-A09-02.

### CA-A09-PERFSEC — Measurement-first optimization và defensive C

- **Concept/outline:** OUT-S09-02.
- **LO:** ADVC-H3SD.
- **Scenario/input:** Gateway v9; fixed synthetic profile workload/checksum; boundary/format/lifetime fixtures; host/toolchain fingerprint.
- **Rule 1:** kiểm bounds/overflow trước pointer-size arithmetic, dùng literal format và ghi owner/lifetime ở mọi close/shutdown path. **Rationale:** trực tiếp chặn các trigger thuộc CWE-120/190/134/416 trong scope.
- **Rule 2:** profile cùng workload trước thay đổi, giữ checksum/output invariant và chỉ claim trên host đã fingerprint. **Rationale:** counter/timing phụ thuộc hardware, policy, compiler và workload.
- **Rule 3:** sanitizer, Valgrind, compiler và CWE/CERT mappings là bounded evidence; check không chạy được phải disclose. **Rationale:** dynamic tools chỉ quan sát path đã execute và CWE chỉ là taxonomy.
- **Deliverables:** A09 security and performance evidence; A09 handoff and decision note.
- **Oracles/evidence:** AT-A09-03, AT-A09-04; sanitizer/Valgrind reports, gprof report, perf report hoặc BLOCKED-PMU diagnostic, before/after checksum.
- **Rubric:** RB-A09-03, RB-A09-04.

Các contracts trên mô tả điều cần chứng minh, không chỉ định data structure, decomposition, event-dispatch layout hay thuật toán triển khai.

## 🧭 Bối cảnh nghề nghiệp/dự án và change request

**Bối cảnh nghề nghiệp/dự án:** Bạn là integration maintainer của MDB Edge Diagnostics Gateway mô phỏng. Process backend M07 cô lập synthetic jobs; thread/IPC backend M08 xử lý producer-consumer work. Quality reviewer cần một terminal network increment có correctness, lifecycle, hardening và profile evidence trước handoff.

**Project increment/change request cần hoàn thành:** M09 bổ sung epoll TCP frontend và evidence pack. Giá trị bàn giao là một gateway chạy local có contract kiểm chứng được, không phải benchmark hoặc network service production.

**Scenario đã chốt trong plan:** **[SUY DIỄN — user-approved project integration]** Hoàn thiện frontend TCP loopback non-blocking/epoll có line framing và per-connection state, định tuyến request synthetic vào hai backend đã accepted, harden input/lifetime và profile cùng một workload/checksum.

Tham khảo khái niệm và examples đã học tại [material.md](material.md) và [example.md](example.md). Bài này dùng change request, load và edge cases rộng hơn; Example assets không phải starter implementation của gateway.

## 🔗 Liên kết project xuyên suốt

**Project milestone:** M09.

**Phụ thuộc vào Assignment trước:**

- ASM-A07 — Process job-runner backend và Process lifecycle verification report.
- ASM-A08 — Thread-pool shared-memory backend và TSan and stress verification report.

**Baseline artifacts được sử dụng:** đủ bốn artifacts nêu trên; mỗi artifact phải xuất hiện trong input manifest với version/commit hoặc content hash phù hợp.

**Artifacts Assignment này tạo ra:**

- Networked diagnostics gateway release v9.
- A09 protocol and concurrency tests.
- A09 security and performance evidence.
- A09 handoff and decision note.

**Assignment sau sẽ tái sử dụng:** không có; đây là Assignment terminal.

**Terminal delivery:**

- **consumer_type:** handoff.
- **consumer_ref:** MDB-GATEWAY-SIMULATED-HANDOFF.
- **artifacts:** gateway release v9, security/performance evidence, handoff/decision note.
- **acceptance refs:** AT-A09-01..04.

## 🧰 Điều kiện thực hiện

### Kiến thức/kỹ năng tiên quyết

- Hoàn thành S07, S08, ASM-A07 và ASM-A08.
- Robust I/O, signal/process lifecycle, pthread synchronization, C17 ownership/bounds.
- Build CMake/CTest; đọc ASan/UBSan, Valgrind, TSan, perf/gprof outputs.
- Hiểu rõ sanitizer-clean không phải chứng minh mọi UB vắng mặt.

### Môi trường, công cụ và phiên bản

Ubuntu 22.04, Linux 5.15 baseline; GCC 11.4 hoặc Clang 14; CMake 3.22; Valgrind 3.18.1; perf kernel toolset; gprof Binutils 2.38. Network fixtures chỉ bind 127.0.0.1 hoặc ::1 bằng port 0. Không root, capability escalation hoặc system-wide tuning.

### Input và starter assets

- A07/A08 source artifacts và đúng bốn verification artifacts trong baseline.
- DC-LINE: LF-delimited request/response; synthetic maximum payload 4096 byte.
- Synthetic command/telemetry fixtures; CR-A09.
- Public contract pack và repository conventions.
- Không có credential, PII, customer payload, production address hoặc reference implementation.

## 📋 Yêu cầu

### Functional requirements

- **FR-A09-01 · ADVC-H2SD:** listener và mọi accepted socket non-blocking/CLOEXEC; event loop giữ state riêng và xử lý fragmented, coalesced, empty, malformed, oversized, EOF, reset và partial send/recv theo DC-LINE.
- **FR-A09-02 · ADVC-H2SD:** mỗi valid request chọn process hoặc thread/IPC backend qua public contract và tạo đúng một LF-delimited response; A07/A08 regression behavior không đổi.
- **FR-A09-03 · ADVC-H2SD:** ít nhất 100 simultaneous loopback clients hoàn tất; idle timeout, repeated reconnect và SIGTERM shutdown có bounded outcome; process/FD resources trở về baseline.
- **FR-A09-04 · ADVC-H3SD:** một fixed representative workload/checksum được profile bằng gprof và bằng perf khi host cho phép; hotspot, candidate change và retain/reject decision được truy vết.

### Non-functional requirements

- **NFR-A09-01 · ADVC-H3SD:** warning profile đạt; ASan+UBSan build không có in-scope finding; standalone Valgrind binary có zero invalid access và zero definite/indirect leak.
- **NFR-A09-02 · ADVC-H2SD/H3SD:** mọi length/capacity arithmetic overflow-safe; input bounded; format literal; connection/output lifetime có một owner và close exactly once.
- **NFR-A09-03 · ADVC-H3SD:** before/after output/checksum giống nhau; performance claim chỉ áp dụng cho workload/host/toolchain đã fingerprint và kèm raw evidence.
- **NFR-A09-04 · ADVC-H2SD:** synthetic-only, loopback/port 0, bounded timeout và run-id cleanup; không sudo/sysctl, external endpoint hoặc wildcard process signal.

### Ràng buộc và phạm vi loại trừ

- H3 extension là **[SUY DIỄN — user-approved]** trong boundary performance/security ngay trước source Assignment row.
- Training max 4096 là course contract, không phải thuộc tính TCP.
- Không giả định one recv = one frame; incomplete bytes phải tồn tại tới event sau và mọi complete coalesced frame phải được xử lý.
- Level-triggered epoll là baseline bắt buộc. Edge-triggered là optional; nếu chọn, accept/read/write phải drain tới EAGAIN và có tests riêng.
- Không dùng thread-per-client thay cho epoll requirement.
- Không chạy Valgrind trên ASan binary; TSan, ASan/UBSan, memcheck, gprof và release/perf là build/run profiles tách biệt khi áp dụng.
- Không được đổi /proc/sys/kernel/perf_event_paranoid. perf denied phải ghi BLOCKED-PMU, không ghi PASS và không làm mất gprof/correctness evidence.
- Không đặt universal latency/throughput threshold; 100 clients là functional concurrency oracle, không phải tuyên bố production capacity.
- Bài làm độc lập: không nộp lại Example assets như gateway implementation và không dùng source ngoài không khai provenance/license.

> [!IMPORTANT]
> Đề bài không cung cấp decomposition, state representation, routing implementation hoặc thứ tự thao tác. Mọi quyết định phải được giải thích bằng contract và evidence.

## 📦 Deliverables và cách nộp

1. **Networked diagnostics gateway release v9:** source/public headers/build definitions trong repository, clean-build được từ snapshot.
2. **A09 protocol and concurrency tests:** fixtures/harness cho AT-A09-01..03, có bounded timeout và synthetic-only manifest.
3. **A09 security and performance evidence:** environment fingerprint, exact commands, sanitizer/Valgrind summaries, gprof, perf hoặc BLOCKED-PMU diagnostic, raw checksums.
4. **A09 handoff and decision note:** protocol/lifecycle/ownership contracts, optimization retain/reject, residual risks, terminal artifact manifest.

**Submission contract:** nộp repository snapshot M09 và evidence manifest đã redact; không nộp build cache, standalone gmon.out ngoài evidence pack, secret/customer data hoặc log từ endpoint ngoài loopback. Một deliverable thiếu exact command, expected/actual result hoặc version link được xem là chưa nộp đủ.

## ✅ Acceptance criteria và output mong đợi

### AT-A09-01 — Protocol/framing/partial-I/O oracle

**Given** listener loopback port 0 và fixtures inject fragmented/coalesced frames, empty/malformed/oversized input, peer close mid-frame, EINTR/EAGAIN và short I/O; **when** protocol suite chạy; **then** mỗi complete valid frame tạo đúng một response, incomplete bytes được giữ, invalid input theo documented policy, không duplicate/stall/crash. Evidence: per-case request chunks, response bytes, state/result và test summary.

### AT-A09-02 — 100-client/lifecycle oracle

**Given** FD baseline, 100 simultaneous clients, repeated connect/disconnect, idle connections và owned server PID; **when** load/shutdown harness chạy với deadline; **then** ít nhất 100 clients hoàn tất với zero mismatch, server graceful-exit sau SIGTERM, mọi owned process/FD trở về baseline. Evidence: client ledger, timeout, before/after /proc PID/FD count và exit status.

### AT-A09-03 — Backend/security/memory oracle

**Given** both dependency backends, boundary lengths, overflow candidates và payload “%n%s%x”; **when** regression, ASan+UBSan và standalone Valgrind suites chạy; **then** cả hai routing paths đúng, A07/A08 regressions pass, input đối kháng là data, oversize/overflow reject deterministically, zero in-scope sanitizer finding, zero invalid access và definite/indirect leak. Evidence: route ledger, reports và disposition table.

### AT-A09-04 — Profile/optimization oracle

**Given** exact fixed workload/checksum và environment fingerprint; **when** gprof build chạy normal-exit, perf stat chạy nếu được phép và candidate change được so với baseline; **then** gprof report không rỗng và chỉ ra hotspot; perf có report hoặc exact BLOCKED-PMU diagnostic; output/checksum trước/sau identical; decision note chỉ claim trong measured context. Evidence: raw commands/reports/checksums và retain/reject rationale.

## 🧪 Cách xác minh

**Phương thức:** executable.

~~~sh
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON
cmake --build build/debug
ctest --test-dir build/debug --output-on-failure -R a09_

cmake -S . -B build/memcheck -DCMAKE_BUILD_TYPE=Debug -DENABLE_MEMCHECK_TESTS=ON
cmake --build build/memcheck
ctest --test-dir build/memcheck --output-on-failure -R a09_memcheck

cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release
cmake --build build/release
perf stat -r 5 -e task-clock,cycles,instructions,cache-references,cache-misses   -- ./build/release/apps/mdb_gateway_bench --fixture fixtures/a09_profile.txt

cmake -S . -B build/gprof -DCMAKE_BUILD_TYPE=RelWithDebInfo -DENABLE_GPROF=ON
cmake --build build/gprof
./build/gprof/apps/mdb_gateway_bench --fixture fixtures/a09_profile.txt
gprof ./build/gprof/apps/mdb_gateway_bench gmon.out
~~~

Nếu repository dùng target/path khác, submission phải cung cấp equivalent commands giải quyết đúng AT IDs; không được bỏ oracle.

**Bằng chứng phải nộp:**

- environment/kernel/compiler/perf-policy fingerprint;
- protocol case ledger và 100-client summary;
- FD/process baseline before/after và graceful-shutdown timeline;
- M07/M08 regression summary;
- ASan+UBSan và standalone Valgrind summaries;
- gprof report; perf report hoặc BLOCKED-PMU diagnostic;
- before/after checksum/output; defensive-C/optimization decision note;
- terminal handoff manifest.

## 📊 Rubric chấm điểm — tổng 100%

| ID | Tiêu chí | Trọng số | LO | Bằng chứng đạt | Chưa đạt |
|---|---|---:|---|---|---|
| RB-A09-01 | TCP framing, non-blocking I/O và epoll state correctness | 30% | H2 | AT-A09-01 pass toàn bộ split/coalesced/error/partial fixtures; không stall/duplicate | Thiếu required case, giả định recv boundary hoặc event loop stall/crash |
| RB-A09-02 | Concurrent lifecycle và tích hợp cả hai backend | 25% | H2 | AT-A09-02 đạt 100 clients/FD baseline/graceful shutdown; AT-A09-03 route cả A07/A08 | Mismatch/timeout/lifecycle leak hoặc bỏ một direct dependency |
| RB-A09-03 | Defensive C và memory-safety evidence | 25% | H2,H3 | Bounds/overflow/format/ownership contracts đạt; AT-A09-03 dynamic oracles clean | Unsafe arithmetic/format/lifetime hoặc blocking finding còn lại |
| RB-A09-04 | Profile decision và terminal handoff tái lập | 20% | H3 | AT-A09-04 có gprof, perf/disclosed block, invariant output và bounded claim; artifacts resolve | Thiếu baseline/hotspot, đổi output, che unavailable check hoặc handoff thiếu |

**Điểm đạt:** 70%. Một blocking safety violation, external endpoint, unauthorized privilege change hoặc signal ngoài owned PID làm RB liên quan chưa đạt bất kể tổng số học.

## 📚 Nguồn đầu vào và provenance

### Nguồn đã map

POSIX.1-2017; RFC 9293/768; Linux man-pages và kernel 5.15 docs; GCC 11.4; GNU gprof 2.38; C17/CERT C; CWE 4.20; Clang 14; Valgrind 3.18.1; internal syllabus. Chỉ dùng reference/paraphrase.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — user-approved]:** H3 extension, cumulative routing và terminal handoff.
- **[SUY DIỄN — course contract]:** LF framing, max 4096, synthetic commands, evidence folder conventions.
- **[BỔ SUNG — nguồn chính thống đã map]:** network readiness/framing, profile and compiler behavior, defensive-C/CWE mappings và dynamic-tool evidence limits.

---

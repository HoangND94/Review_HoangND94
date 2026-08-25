# Session S08: Session 08 — IPC, POSIX threads and C11 atomics — Assignment 08

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 04 — Linux System Programming: Process, Signal, IPC & Threads

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASM-A08 (Assignment 08) |
| Thời lượng dự kiến | 120 phút |
| Độ khó | Hard |
| Bloom levels | Create |
| Mức xác thực | Simulated; synthetic-only |

## 🎯 Learning Outcomes được đánh giá

- **ADVC-H2SD:** tạo và kiểm chứng bounded producer-consumer thread pool ghi result records vào POSIX shared-memory channel với đúng synchronization, exactly-once accounting và cleanup.

| LO | Deliverables | Acceptance tests | Rubric |
|---|---|---|---|
| ADVC-H2SD | Thread-pool shared-memory backend; TSan/stress report; decision note | AT-A08-01..04 | RB-A08-01..04 |

## 🧠 Khái niệm và best practices được đánh giá

### CA-A08-CONCURRENCY — IPC, condition predicates và atomics trong bounded backend

- **Concept/outline:** OUT-S08-01.
- **LO:** ADVC-H2SD.
- **Scenario/input:** quality-gated core v6, synthetic work/shared-memory fixtures, public contract pack và CR-A08.
- **Rule 1:** queue predicate được bảo vệ bằng cùng mutex; wait trong while; stopping state được mutate dưới lock; broadcast/join theo fixed lifecycle. **Rationale:** wake không bảo đảm predicate và inconsistent lock order tạo race/deadlock.
- **Rule 2:** shared layout/version/capacity/bounds và synchronization phải explicit; _Atomic dùng cho state thật sự atomic, không dùng volatile thay synchronization. **Rationale:** mmap chỉ chia sẻ bytes, không tạo happens-before.
- **Rule 3:** mọi pthread API được kiểm bằng return code trực tiếp; named IPC object có unique run-id, mode 0600 và exact-owner cleanup. **Rationale:** errno không phải error channel chung của pthread; stale/colliding object phá isolation.
- **Deliverables:** Thread-pool shared-memory backend; TSan and stress verification report; A08 synchronization decision note.
- **Oracles/evidence:** AT-A08-01..04; counts/checksums, TSan stacks/summary, shared-layout/cleanup record, bounded progress timeline.
- **Rubric:** RB-A08-01..04.

Contract không quy định queue representation, number of internal modules, exact lock decomposition, selected memory orders hoặc shared-record implementation.

## 🧭 Bối cảnh nghề nghiệp/dự án và change request

**Bối cảnh nghề nghiệp/dự án:** Bạn là system maintainer của MDB Edge Diagnostics Gateway mô phỏng. Core v6 đã qua quality gate; M07 cung cấp process backend. M08 phải cung cấp concurrent in-process path để epoll frontend M09 có thể chọn backend.

**Project increment/change request cần hoàn thành:** CR-A08 thêm bounded producer-consumer pipeline: worker pool xử lý synthetic work, publish result records qua POSIX shared-memory channel và shutdown không mất/nhân đôi work.

**Scenario đã chốt trong plan:** Queue, worker lifecycle, IPC layout và cleanup phải kiểm chứng bằng deterministic counts/checksums, TSan build riêng và repeated stress. [material.md](material.md) và [example.md](example.md) cung cấp khái niệm/case; Example asset không phải starter backend.

## 🔗 Liên kết project xuyên suốt

**Project milestone:** M08.

**Phụ thuộc vào Assignment trước:** ASM-A06.

**Baseline artifacts được sử dụng:** Quality-gated gateway core v6.

**Artifacts Assignment này tạo ra:**

- Thread-pool shared-memory backend.
- TSan and stress verification report.

**Assignment sau sẽ tái sử dụng:** ASM-A09 dùng cả hai artifacts làm direct baseline cho thread/IPC routing.

**Terminal delivery:** không áp dụng; A08 là increment trung gian.

## 🧰 Điều kiện thực hiện

### Kiến thức/kỹ năng tiên quyết

- Hoàn thành S07 và quality-gated core v6 từ A06.
- POSIX IPC choices; pthread create/join/detach, mutex/condition predicates, race/deadlock.
- C11 atomics và giới hạn của volatile.
- Chạy bounded timeout/stress và đọc TSan evidence.

### Môi trường, công cụ và phiên bản

Ubuntu 22.04, Linux 5.15, glibc 2.35, Clang 14 TSan, GCC 11.4, pthreads. TSan dùng build riêng. Named IPC resources chứa UID/run-id, mode 0600 và owner cleanup. Không root hoặc thay /proc/sys/fs/mqueue, /dev/shm mount hay host limits.

### Input và starter assets

- Quality-gated gateway core v6.
- Synthetic work records và shared-memory fixtures có version/capacity expectations.
- Public contract pack; CR-A08.
- Fixed seeds/counts cho repeated stress.
- Không có customer data, global shared name, credential hoặc production process.

## 📋 Yêu cầu

### Functional requirements

- **FR-A08-01 · ADVC-H2SD:** bounded queue giữ FIFO và exactly-once contract qua empty, full, wakeup, stop và shutdown transitions.
- **FR-A08-02 · ADVC-H2SD:** workers được create/join đúng lifecycle; owner không destroy/unmap state khi worker còn có thể truy cập.
- **FR-A08-03 · ADVC-H2SD:** POSIX shared-memory result channel có magic/version/capacity/bounds, synchronization/visibility và exact-owner cleanup contract.

### Non-functional requirements

- **NFR-A08-01 · ADVC-H2SD:** Clang 14 TSan build riêng không có project data-race finding trong required fixtures.
- **NFR-A08-02 · ADVC-H2SD:** repeated bounded stress hoàn tất trước deadline, không deadlock/livelock và không lost/duplicate work.
- **NFR-A08-03 · ADVC-H2SD:** volatile không được dùng làm thread synchronization; shared control state dùng mutex/condition hoặc C11 atomics với documented invariant/memory-order rationale.

### Ràng buộc và phạm vi loại trừ

- pthread functions được kiểm bằng return code trực tiếp, không dựa vào errno.
- Condition wait nằm trong while predicate với mutex tương ứng.
- Mọi multi-lock path tuân fixed lock order đã công bố.
- Không giữ queue lock qua unbounded callback/external I/O.
- Stop/broadcast/unlock/join/destroy/unmap ordering phải ngăn use-after-destroy.
- ASan/UBSan và TSan là binary/build riêng; không chạy TSan trên production binary.
- IPC names dùng UID/run-id, O_EXCL khi tạo, mode 0600 và owner unlink chính xác resource của run; không wildcard cleanup.
- Không dùng volatile flag để pass TSan hoặc thay atomic/mutex.
- Không unbounded queue, unbounded thread creation, busy polling/sleep làm primary synchronization.
- Bài làm độc lập; không sao chép Example asset làm backend.

> [!IMPORTANT]
> TSan clean là evidence trên executed schedules, không chứng minh mọi interleaving. Exactly-once ledger, timeout và repeated stress vẫn bắt buộc.

## 📦 Deliverables và cách nộp

1. **Thread-pool shared-memory backend:** source/public API/build integration, clean-build được từ snapshot.
2. **TSan and stress verification report:** exact compiler/options, required test ledger, TSan summary, repetitions/deadline, submitted/processed/published IDs/checksums và IPC cleanup result.
3. **A08 synchronization decision note:** queue predicates, lock order, happens-before, atomic/volatile decisions, shared layout/version và shutdown/resource ownership.

**Submission contract:** nộp snapshot M08 cùng synthetic fixtures và version-matched TSan/stress evidence. Mọi named IPC resource phải cleanup trước khi đóng run. Không nộp build cache, stale /dev/shm object, host-wide listings, secret hoặc customer data.

## ✅ Acceptance criteria và output mong đợi

### AT-A08-01 — Queue/exactly-once oracle

**Given** empty/full/wakeup/shutdown fixtures và known work IDs; **when** producer/consumers chạy; **then** submitted, processed và published ID sets/counts/checksums khớp, FIFO contract đạt nơi đã công bố và không lost/duplicate work. Evidence: per-ID ledger và final invariant report.

### AT-A08-02 — TSan/worker lifecycle oracle

**Given** Clang 14 TSan build riêng; **when** queue, worker lifecycle và concurrent shutdown suites chạy; **then** processes exit 0, không project data-race finding và every created joinable worker có exactly-one join record. Evidence: compiler/options, TSan output và worker ledger.

### AT-A08-03 — Shared-memory/atomic/cleanup oracle

**Given** valid và invalid version/capacity/layout fixtures; **when** writer/reader contract và owner cleanup chạy; **then** reader chỉ consume complete bounded records, status deterministic, atomic state đúng documented protocol và không còn named IPC resource của run. Evidence: layout manifest, visibility/status tests và scoped cleanup check.

### AT-A08-04 — Bounded stress/progress oracle

**Given** fixed seeds/counts, repeated runs và timeout; **when** full/empty contention và shutdown interleavings chạy; **then** mỗi run hoàn tất với expected counts/checksum, không deadlock/livelock symptom và lock-order evidence không vi phạm. Evidence: run table, durations, timeout status và failure capture nếu có.

## 🧪 Cách xác minh

**Phương thức:** artifact_review với executable TSan/stress evidence.

~~~sh
cmake -S . -B build/tsan   -DCMAKE_C_COMPILER=clang-14   -DCMAKE_BUILD_TYPE=Debug   -DCMAKE_C_FLAGS='-O1 -g -fno-omit-frame-pointer -fsanitize=thread -pthread'   -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=thread -pthread'
cmake --build build/tsan --target thread_backend_tests
TSAN_OPTIONS=halt_on_error=1:exitcode=66   ctest --test-dir build/tsan -R '^thread_backend_' --output-on-failure
timeout --signal=TERM --kill-after=2s 60s   ctest --test-dir build/tsan -R '^thread_pool_stress$' --output-on-failure
~~~

Equivalent commands được chấp nhận nếu giải quyết đúng AT IDs, compiler/runtime fingerprint và build separation.

**Bằng chứng phải nộp:**

- submitted/processed/published ID and checksum report;
- Clang/version/options and TSan summary;
- repeated stress/deadline table;
- shared-memory layout/version/visibility and cleanup evidence;
- worker create/join ledger;
- synchronization/atomic/lock-order decision note.

## 📊 Rubric chấm điểm — tổng 100%

| ID | Tiêu chí | Trọng số | LO | Bằng chứng đạt | Chưa đạt |
|---|---|---:|---|---|---|
| RB-A08-01 | Bounded queue, worker behavior và exactly-once accounting | 30% | H2 | AT-A08-01 transitions đúng; ID sets/count/checksum khớp | Lost/duplicate work, capacity/FIFO hoặc lifecycle failure |
| RB-A08-02 | Synchronization, TSan và progress under stress | 30% | H2 | AT-A08-02 TSan clean; AT-A08-04 mọi bounded run hoàn tất | Data race, hang/timeout, missed predicate hoặc lock-order defect |
| RB-A08-03 | Shared-memory, atomic state và IPC cleanup | 25% | H2 | AT-A08-03 bounds/version/visibility đúng; no volatile sync; exact resource cleanup | Torn/stale state, bounds defect, volatile sync hoặc stale resource |
| RB-A08-04 | Concurrency evidence và decision note | 15% | H2 | Commands, predicates, happens-before, lock order, atomic/IPC lifecycle truy vết đủ | Evidence thiếu/stale hoặc decisions không giải thích |

**Điểm đạt:** 70%. Wildcard cleanup, unauthorized host change hoặc deliberate suppression of project TSan finding là blocking safety failure.

## 📚 Nguồn đầu vào và provenance

### Nguồn đã map

POSIX.1-2017, C17/WG14, Linux man-pages, Clang 14 TSan, CERT C và internal syllabus; reference/paraphrase only.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — user-approved project spine]:** M08, A06 baseline và A09 downstream reuse.
- **[SUY DIỄN — course fixtures]:** shared layout, ID/checksum/stress report shape và run-id naming.
- **[BỔ SUNG — nguồn: POSIX/C17/Clang/CERT C]:** pthread error/condition semantics, data-race/atomic model và evidence boundaries.

---

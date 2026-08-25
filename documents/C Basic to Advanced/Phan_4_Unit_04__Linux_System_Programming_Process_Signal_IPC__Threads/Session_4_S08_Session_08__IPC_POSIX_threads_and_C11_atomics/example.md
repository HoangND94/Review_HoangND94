# Session S08: Session 08 — IPC, POSIX threads and C11 atomics — Ví dụ và nghiên cứu tình huống

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 04 — Linux System Programming: Process, Signal, IPC & Threads

## 🎯 Learning Outcomes liên quan

- **ADVC-H2SD:** tạo và kiểm chứng bounded producer-consumer thread pool với POSIX shared-memory layout, synchronization, atomic evidence và owner cleanup.

## 🧭 Liên kết với ngữ cảnh nghề nghiệp/dự án

**Bối cảnh nghề nghiệp/dự án:** MDB Edge Diagnostics Gateway — Simulated cần M08 thread/IPC backend làm direct dependency cho epoll frontend M09.

**Project increment được minh họa:** một slice nhỏ của M08: bounded queue, two-worker lifecycle, shared result channel, exactly-once checksum và no-stale-name cleanup.

## 🧰 Điều kiện chạy ví dụ

**Kiến thức/kỹ năng tiên quyết:** pthread lifecycle, C17 object lifetime, robust error handling, CMake/compiler basics và run-scoped resource ownership.

**Môi trường, công cụ và phiên bản:** Ubuntu 22.04/Linux 5.15, glibc 2.35, GCC 11.4 hoặc Clang 14. /dev/shm phải writable trong sandbox. TSan dùng Clang 14 binary riêng.

**Phương thức xác minh artifact:** executable.

## 📚 Nguồn đầu vào đã map

POSIX.1-2017, C17/WG14, Linux man-pages, Clang 14 ThreadSanitizer, CERT C và internal syllabus.

---

### Mapping case đã chốt trong course plan

- **CASE-S08-01:** ADVC-H2SD · OUT-S08-01 · authenticity inherited.

**Mức xác thực mặc định:** simulated, synthetic-only.

## Case Study 01: Bounded thread pool ghi result channel không race và không stale IPC name

### 1. Ticket và tiêu chí thành công

- **Vai trò/stakeholder:** system maintainer và concurrency reviewer.
- **Vấn đề cần giải quyết:** xử lý exactly once tám tasks bằng hai workers, không lost/duplicate/race/deadlock và không để POSIX shm name sau run.
- **Learning Outcome và outline item:** ADVC-H2SD · OUT-S08-01.
- **Project increment/professional artifact liên quan:** M08 Thread-pool shared-memory backend.
- **Tiêu chí thành công:** submitted=processed=8, checksum bình phương 1..8 bằng 204, cleanup=ok, exit 0 trong timeout; strict compile pass; TSan build riêng không báo project data race khi runtime hỗ trợ.

### 2. Input, trạng thái ban đầu và ràng buộc

Asset: [assets/thread_pool_shm_demo.c](assets/thread_pool_shm_demo.c).

- Tasks có IDs 0..7 và values 1..8.
- Queue capacity 3 tạo backpressure; two joinable workers.
- Shared object name /advc_s08_PID, O_EXCL, mode 0600, size đúng result_channel.
- Layout có magic, version, capacity, eight result slots và atomic processed.
- Name được shm_unlink ngay sau mmap; mapping/FD còn sống tới owner teardown.
- Không process/thread ngoài fixture, không customer data, root, global fixed name hoặc wildcard cleanup.

### 3. Phân tích lựa chọn

**IPC choice:** shared memory được chọn để minh họa mapped layout; pipe/mqueue sẽ copy bytes/messages qua kernel và không minh họa trực tiếp memory visibility. Case chỉ dùng threads trong một process, nhưng layout/version/cleanup contract chuẩn bị cho process reader; nó không tuyên bố ordinary mutex trong asset là process-shared mutex.

**Synchronization choice:** queue fields tạo multi-field invariant nên dùng mutex. not_empty/not_full chỉ thông báo state change; while loops mới bảo đảm predicate. Worker lấy task rồi unlock trước compute/write, tránh giữ queue lock qua work.

**Atomic choice:** processed là independent count nên dùng relaxed atomic. Result visibility với main được bảo đảm bởi successful pthread_join; atomic counter không publish payload. Dùng volatile sẽ không tạo atomicity/happens-before.

**Lifecycle choice:** joinable workers cho owner biết lúc nào có thể destroy mutex/conditions và unmap channel. Detach sẽ cần contract khác để chứng minh không use-after-destroy.

Trade-off: unlink ngay sau mmap bảo đảm no stale name nhưng process unrelated không thể open theo name sau đó; production process-sharing có thể unlink ở owner-defined handshake sau khi peers open.

### 4. Cách triển khai

Chương trình hoàn chỉnh trong asset gồm:

- queue_initialise/destroy kiểm mọi pthread return code trực tiếp;
- queue_submit chờ not_full trong while dưới mutex;
- worker chờ not_empty trong while, nhận stopping under same mutex;
- stop transition set flag và broadcast trước unlock/join;
- workers ghi unique slots, atomic-fetch processed;
- main join tất cả trước read results/destroy/unmap;
- shm object có unique PID name, mode 0600, ftruncate, mmap và exact unlink;
- final shm_open cùng name phải fail ENOENT.

Asset không phải solution Assignment 08: nó không tích hợp core v6, cross-process reader, stress harness, configurable work records hay full shutdown/error policies.

### 5. Output mong đợi

~~~text
submitted=8 processed=8 checksum=204 cleanup=ok
~~~

Exit code khác 0, timeout, checksum/count khác, cleanup=stale hoặc TSan finding là fail trong phạm vi check tương ứng.

### 6. Cách xác minh

Normal build:

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 -pthread   assets/thread_pool_shm_demo.c -o thread_pool_demo
timeout 10s ./thread_pool_demo
~~~

TSan build riêng:

~~~sh
clang-14 -std=c17 -Wall -Wextra -Wpedantic -Werror -O1 -g   -fno-omit-frame-pointer -fsanitize=thread -pthread   assets/thread_pool_shm_demo.c -o thread_pool_tsan
TSAN_OPTIONS=halt_on_error=1:exitcode=66 timeout 20s ./thread_pool_tsan
~~~

Nếu TSan runtime không hoạt động trong sandbox, lưu exact stderr/status là BLOCKED-RUNTIME; normal correctness test không được gắn nhãn race-free thay cho TSan.

### 7. Giải thích sâu và failure modes

- **if thay while:** spurious wake hoặc worker khác consume item làm pop empty. Evidence: count underflow/lost task/TSan.
- **Signal trước state mutation:** waiter có thể wake, thấy predicate false rồi ngủ; nếu protocol không có signal sau mutation, hang.
- **Join dưới queue lock:** worker cần lock để observe stopping/exit, tạo deadlock. Asset unlock trước join.
- **Destroy trước join:** worker dùng destroyed mutex/channel, có thể ASan/TSan/crash.
- **processed volatile:** read/write race và count lost. Asset dùng atomic.
- **Atomic counter như publish flag:** relaxed count không bảo đảm unrelated payload visibility; asset dựa vào unique slots + join.
- **pthread error qua errno:** diagnostic sai. Asset dùng strerror(return_code).
- **Fixed shm name:** collision/stale cross-run. Asset O_EXCL, PID name, mode 0600, immediate unlink.
- **TSan + ASan cùng binary:** unsupported/noisy profile; build riêng.

Giới hạn: timing/interleaving không deterministic; oracle dựa counts, IDs/checksum, timeout, TSan và cleanup. Một pass không chứng minh mọi schedule; Assignment yêu cầu repeated bounded stress.

### 8. Bài học chuyển giao

Assignment 08 phải tích hợp core v6, định nghĩa shared-memory channel contract, exactly-once ledger, full/empty/wakeup/shutdown fixtures và repeated stress. Học viên tự thiết kế module/API/locking; Example chỉ cung cấp mental model và một executable oracle nhỏ.

---

## Provenance của các case

### Nguồn được dùng

- POSIX.1-2017: pthread, condition variable và shm API contracts.
- C17/WG14: atomic/data-race model.
- Clang 14: TSan usage/evidence boundary.
- Linux man-pages/CERT C: target lifecycle, permissions và safe resource handling.
- Asset được viết mới, không sao chép implementation từ nguồn.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — course fixture]:** queue capacity 3, tasks 1..8, PID name và checksum 204.
- **[SUY DIỄN — user-approved project spine]:** M08 và downstream A09.
- **[BỔ SUNG — nguồn: POSIX/C17/Clang]:** predicate loops, join visibility, atomics và TSan evidence policy.


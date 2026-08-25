# Session S08: Session 08 — IPC, POSIX threads and C11 atomics — Học liệu cốt lõi

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 04 — Linux System Programming: Process, Signal, IPC & Threads

## 🎯 Learning Outcomes

- **ADVC-H2SD — Create:** Xây dựng và kiểm chứng chương trình C trên Linux sử dụng IPC, pthread và C11 atomics với lifecycle, synchronization, bounded progress và cleanup đúng contract.

## 🧭 Ngữ cảnh nghề nghiệp/dự án và phần tăng trưởng của Unit

**Bối cảnh nghề nghiệp/dự án:** MDB Edge Diagnostics Gateway — Simulated đã có process backend M07. Maintainer cần một backend in-process có bounded thread pool và POSIX shared-memory result channel để network frontend M09 có thể chọn execution path.

**Project increment sau Unit này:** M08 tạo Thread-pool shared-memory backend, TSan and stress verification report và synchronization decision note. M09 tái sử dụng hai artifact đầu.

**Mức xác thực của bối cảnh:** simulated, synthetic-only. POSIX IPC names chứa run-id/PID, quyền 0600 và được owner unlink; không dùng shared object/customer data thật.

## 📚 Nguồn đầu vào đã map

- POSIX.1-2017: https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/
- ISO C17 metadata/WG14 public draft: https://www.iso.org/standard/74528.html
- Linux man-pages: https://www.kernel.org/doc/man-pages/
- Clang 14 ThreadSanitizer: https://releases.llvm.org/14.0.0/tools/clang/docs/ThreadSanitizer.html
- SEI CERT C: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/
- Internal syllabus row S08.

---

## 1. Kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết

- Robust FD I/O, process/signal lifecycle và run-scoped cleanup từ S07.
- C17 object lifetime, opaque ADT và quality-gated gateway core v6.
- CMake/CTest; đọc sanitizer evidence và dùng timeout an toàn.

### Môi trường, công cụ và phiên bản

Ubuntu 22.04, Linux 5.15 baseline, glibc 2.35, GCC 11.4, Clang 14, pthreads. TSan dùng build riêng; không ghép TSan với ASan/UBSan. POSIX IPC object có unique name, permission 0600 và exact-owner cleanup.

~~~sh
clang-14 --version
getconf _POSIX_THREADS
test -d /dev/shm
test -d /proc/sys/fs/mqueue
~~~

Mqueue availability có thể phụ thuộc host/container; không dùng root để mount hoặc đổi limit cho bài học.

### Phương thức xác minh artifact

Material được artifact review theo OUT-S08-01/ADVC-H2SD. Worked example compile/run bình thường và, khi runtime hỗ trợ, chạy TSan trên binary riêng.

## 2. Định vị trong lộ trình (Mental Map)

M07 dùng process isolation và byte-stream IPC. M08 dùng shared address space để giảm copy nhưng phải tự tạo happens-before:

producer → bounded queue predicate → mutex/condition → worker → shared result layout → atomic processed counter → join → reader verification → owner cleanup.

S09 sẽ gọi process hoặc thread backend từ epoll frontend. Vì vậy M08 phải định nghĩa exactly-once accounting, capacity, stop/join ordering, shared-memory version/layout và evidence race/deadlock-free trong bounded fixtures.

## 3. Nội dung lý thuyết cốt lõi

**Phạm vi nội dung:**

- [x] IPC: pipe, FIFO, POSIX shared memory and message queue; POSIX threads: create/join/detach, mutex, condition variable, race condition, deadlock avoidance, thread pool; volatile vs C11 atomics

#### OUT-S08-01 — IPC: pipe, FIFO, POSIX shared memory and message queue; POSIX threads: create/join/detach, mutex, condition variable, race condition, deadlock avoidance, thread pool; volatile vs C11 atomics

**Mapping:** OUT-S08-01 · ADVC-H2SD · M08 thread/IPC backend.

##### Định nghĩa rõ ràng

**IPC:** unnamed pipe là unidirectional byte stream thường giữa related processes; FIFO là named filesystem-like endpoint cho unrelated processes nhưng vẫn có byte-stream/open semantics; POSIX shared memory tạo named kernel object được ftruncate/mmap, cung cấp shared bytes nhưng không tự đồng bộ; POSIX message queue giữ message boundaries, priority và kernel-managed queue limits.

**Threads:** pthread_create tạo execution context chia sẻ process address space; pthread_join đồng bộ termination và thu resource; detached thread tự giải phóng join state nhưng không thể join, nên ownership/evidence khác. Mutex bảo vệ invariant/critical section. Condition variable cho thread ngủ tới khi state có thể đã thay đổi; nó không giữ predicate và wake không phải permission bỏ kiểm tra.

Data race xảy ra khi hai threads truy cập cùng memory, ít nhất một write, không có synchronization phù hợp; theo C memory model hành vi là undefined. Deadlock là progress failure do wait cycle/order hoặc lifecycle; chương trình race-free vẫn có thể deadlock. Thread pool là fixed/bounded workers lấy work từ queue thay vì tạo thread cho từng task.

volatile mô tả observable accesses phù hợp hardware/signal use cases nhất định; nó không tạo atomicity hay inter-thread happens-before. _Atomic/C11 atomic operations cung cấp atomic access và memory-order semantics cho đúng object; atomic không tự bảo vệ multi-field invariant nếu thiếu protocol.

##### Vấn đề/vai trò và quyết định cần đưa ra

Maintainer phải quyết định:

- chọn pipe/FIFO/shared memory/mqueue theo message boundary, copy cost, relationship và cleanup;
- shared layout có magic/version/capacity/bounds nào;
- synchronization primitive bảo vệ field/predicate nào;
- queue full/empty/stopping transitions và backpressure policy;
- worker join hay detach, owner chịu destroy/unmap/unlink;
- lock order, critical-section scope và shutdown sequence;
- state nào cần mutex, state nào thật sự là single atomic;
- evidence nào chứng minh no lost/duplicate work, no race/deadlock và no stale IPC object.

Shared memory nhanh không đồng nghĩa correct: writer có thể publish flag trước khi record hoàn chỉnh nếu protocol không tạo happens-before. volatile không sửa lỗi đó.

##### Cơ chế và mental model

Pipe/FIFO/mqueue thực hiện communication qua kernel calls; shared memory cho processes/threads load/store trực tiếp sau mmap. Với process-shared synchronization, primitive cũng phải nằm trong shared mapping và có attributes phù hợp; chỉ đặt ordinary pthread mutex ở process-local memory không đồng bộ hai process.

Condition variable pattern:

- lock mutex;
- while predicate false và chưa stopping: pthread_cond_wait;
- wait atomically release mutex và reacquire trước return;
- re-check predicate vì spurious wake, broadcast hoặc thread khác đã consume state;
- mutate queue under same mutex; signal/broadcast theo transition; unlock.

pthread API trả error number trực tiếp; không dựa vào errno trừ API contract nói vậy. Join tạo synchronization: successful pthread_join đảm bảo main có thể đọc worker results theo contract. Detached threads cần lifecycle mechanism khác trước khi destroy shared state.

C11 atomics:
- relaxed phù hợp counter độc lập khi ordering của payload đến từ mutex/join;
- acquire/release dùng khi atomic flag publish/consume data theo documented protocol;
- sequential consistency dễ reasoning hơn nhưng không thay invariant design.
Chọn memory order yếu hơn chỉ sau khi chứng minh happens-before; không dùng volatile cast hoặc fence ngẫu nhiên.

Deadlock avoidance bắt đầu bằng fixed lock order và không giữ lock qua blocking external operations/callback không kiểm soát. Shutdown thường: stop accepting → set stopping dưới mutex → broadcast → workers drain hoặc cancel theo policy → join → destroy synchronization → unmap/close/unlink. Đảo thứ tự có thể tạo use-after-destroy.

##### Khi dùng / khi không dùng

- Dùng pipe cho simple byte stream/parent-child. Dùng FIFO khi cần named endpoint và chấp nhận open/cleanup semantics. Dùng mqueue khi message boundary/priority/kernel queue phù hợp. Dùng shared memory khi volume/copy cost đáng kể và có explicit layout/synchronization.
- Dùng joinable threads khi owner cần terminal evidence và safe teardown. Chỉ detach khi result/join không cần và lifetime của dependencies được bảo đảm bằng contract khác.
- Dùng condition variable cho state predicate, không dùng sleep polling.
- Dùng atomics cho independent flag/counter hoặc lock-free protocol đã chứng minh. Dùng mutex khi invariant gồm nhiều fields hoặc cần condition wait.
- Không tạo unbounded thread-per-task, unbounded queue hoặc global IPC name. Không dùng volatile thay atomic/mutex.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** maintainer cần exactly-once result channel và no stale shm name.
- **Input/baseline/constraint:** tám tasks 1..8, queue capacity 3, hai workers, shared object /advc_s08_PID, mode 0600.
- **Decision/action:** queue mutex + two condition variables với while predicates; joinable workers; distinct result slots; atomic processed counter relaxed vì payload visibility được join bảo đảm; shm_unlink ngay sau mmap.
- **Artifact/output:** [assets/thread_pool_shm_demo.c](assets/thread_pool_shm_demo.c).
- **Expected result:** submitted=8 processed=8 checksum=204 cleanup=ok.
- **Verification/oracle/evidence:**

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 -pthread   assets/thread_pool_shm_demo.c -o thread_pool_demo
timeout 10s ./thread_pool_demo
~~~

TSan build riêng:

~~~sh
clang-14 -std=c17 -Wall -Wextra -Wpedantic -Werror -O1 -g   -fno-omit-frame-pointer -fsanitize=thread -pthread   assets/thread_pool_shm_demo.c -o thread_pool_tsan
TSAN_OPTIONS=halt_on_error=1:exitcode=66 timeout 20s ./thread_pool_tsan
~~~

##### Ví dụ code cụ thể

Micro-example sau dùng đúng một slot tổng hợp để tách rõ ba quyết định: predicate `ready` thuộc mutex, condition variable chỉ đánh thức để kiểm tra lại predicate, còn atomic `processed` chỉ là counter độc lập. Ví dụ không có bounded queue, worker pool hay POSIX shared-memory layout của Assignment 08, nên không làm thay phần thiết kế học viên phải tự thực hiện.

Lưu snippet thành `/tmp/s08_handoff.c`:

~~~c
#define _POSIX_C_SOURCE 200809L
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t changed;
    int sample;
    int doubled;
    bool ready;
    _Atomic unsigned processed;
} sample_slot;

static void require_pthread(int rc, const char *operation) {
    if (rc != 0) {
        fprintf(stderr, "%s: %s\n", operation, strerror(rc));
        exit(2);
    }
}

static void *produce(void *context) {
    sample_slot *slot = context;
    require_pthread(pthread_mutex_lock(&slot->mutex), "producer lock");
    slot->sample = 21;
    slot->ready = true;
    require_pthread(pthread_cond_signal(&slot->changed), "signal");
    require_pthread(pthread_mutex_unlock(&slot->mutex), "producer unlock");
    return NULL;
}

static void *consume(void *context) {
    sample_slot *slot = context;
    require_pthread(pthread_mutex_lock(&slot->mutex), "consumer lock");
    while (!slot->ready) {
        require_pthread(pthread_cond_wait(&slot->changed, &slot->mutex), "wait");
    }
    const int value = slot->sample;
    slot->ready = false;
    require_pthread(pthread_mutex_unlock(&slot->mutex), "consumer unlock");

    slot->doubled = value * 2;
    (void)atomic_fetch_add_explicit(&slot->processed, 1U, memory_order_relaxed);
    return NULL;
}

int main(void) {
    sample_slot slot = {0};
    require_pthread(pthread_mutex_init(&slot.mutex, NULL), "mutex init");
    require_pthread(pthread_cond_init(&slot.changed, NULL), "condition init");
    atomic_init(&slot.processed, 0U);

    pthread_t consumer;
    pthread_t producer;
    require_pthread(pthread_create(&consumer, NULL, consume, &slot),
                    "create consumer");
    require_pthread(pthread_create(&producer, NULL, produce, &slot),
                    "create producer");
    require_pthread(pthread_join(producer, NULL), "join producer");
    require_pthread(pthread_join(consumer, NULL), "join consumer");

    const unsigned processed =
        atomic_load_explicit(&slot.processed, memory_order_relaxed);
    printf("sample=%d doubled=%d processed=%u\n",
           slot.sample, slot.doubled, processed);

    require_pthread(pthread_cond_destroy(&slot.changed), "condition destroy");
    require_pthread(pthread_mutex_destroy(&slot.mutex), "mutex destroy");
    return (slot.doubled == 42 && processed == 1U) ? 0 : 1;
}
~~~

Biên dịch và chạy trên Ubuntu 22.04/Jammy:

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 -pthread \
  /tmp/s08_handoff.c -o /tmp/s08_handoff
timeout 5s /tmp/s08_handoff
~~~

**Oracle bắt buộc:** compiler không phát warning; `stdout` chính xác là:

~~~text
sample=21 doubled=42 processed=1
~~~

`stderr` rỗng và exit code là `0`. Timeout, `processed` khác `1` hoặc `doubled` khác `42` đều là FAIL.

**Quyết định và giải thích:** consumer dùng `while (!ready)` dưới cùng mutex vì một lần wake không phải quyền tiêu thụ dữ liệu. `processed` dùng `memory_order_relaxed` vì nó chỉ đếm; visibility của `sample` đến consumer do mutex bảo đảm, còn main chỉ đọc `doubled` sau `pthread_join`. Oracle vì thế kiểm predicate, lifecycle và ranh giới đúng của atomic; thay `ready` bằng `volatile` sẽ không tạo happens-before.

##### Best practices

- **Rule:** pthread return code được kiểm trực tiếp. **Rationale:** pthread functions thường trả error number, không -1/errno. **Positive:** rc=pthread_create; strerror(rc). **Negative:** if rc==-1 rồi perror.
- **Rule:** condition wait luôn trong while trên predicate dưới cùng mutex. **Rationale:** wake có thể spurious hoặc state đã bị thread khác consume. **Positive:** while count==0 && !stopping wait. **Negative:** if rồi assume item tồn tại.
- **Rule:** state transition và signal có documented invariant. **Rationale:** signal không lưu event nếu không có waiter; predicate mới là truth. **Positive:** mutate queue under lock rồi signal. **Negative:** signal ngoài protocol như message.
- **Rule:** fixed lock order và không hold lock qua unbounded callback/I/O. **Rationale:** circular wait hoặc starvation. **Positive:** queue lock chỉ bảo vệ queue mutation. **Negative:** worker giữ queue lock khi xử lý task.
- **Rule:** join trước destroy/unmap. **Rationale:** worker có thể còn tham chiếu state. **Positive:** stopping→broadcast→join→destroy→unmap. **Negative:** destroy mutex/channel ngay sau setting stop.
- **Rule:** shared layout có version/capacity/bounds và owner cleanup. **Rationale:** mapping chỉ là bytes; stale/incompatible object gây corruption. **Positive:** O_EXCL, 0600, ftruncate, magic/version, exact unlink. **Negative:** fixed global name, no size validation.
- **Rule:** volatile không dùng cho synchronization. **Rationale:** không atomic/happens-before. **Positive:** _Atomic processed hoặc mutex-protected state. **Negative:** volatile bool ready giữa threads.
- **Rule:** TSan chạy build riêng và bounded stress lặp. **Rationale:** one clean run không chứng minh progress; mixed sanitizers unsupported/noisy. **Positive:** exact compiler/options/evidence. **Negative:** chạy TSan trên release/ASan binary rồi bỏ warning.

##### Anti-pattern, failure modes và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán/evidence | Sửa và phòng tránh |
|---|---|---|---|
| Missed work sau wake | cond wait dùng if hoặc predicate ngoài mutex | count ledger và interleaving trace | while predicate dưới same mutex |
| Deadlock khi shutdown | lock order hoặc join khi vẫn giữ lock worker cần | thread backtrace/timeline | set stop+broadcast, unlock rồi join |
| TSan data race | payload/state thiếu happens-before | TSan stack pairs | mutex/atomic protocol đúng, không suppress blanket |
| processed đúng nhưng record rỗng | counter publish không order payload | result checksum/visibility test | dùng mutex/join hoặc release/acquire publish |
| Stale /dev/shm object | owner không unlink/error path thiếu cleanup | scoped name listing | unique run name, O_EXCL, owner unlink |
| pthread error bị báo sai | đọc errno thay return code | log rc và strerror(rc) | kiểm rc trực tiếp |
| Queue CPU 100% | sleep/poll hoặc cond predicate sai | profiler/wakeup count | cond wait, bounded signal protocol |
| Crash sau stop | destroy/unmap trước workers kết thúc | ASan/TSan/backtrace | join trước destroy/unmap |

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### Input/trạng thái ban đầu

Tám synthetic tasks có IDs riêng; hai joinable workers; bounded queue capacity 3; POSIX shm object unique theo PID, mode 0600, mapped shared result channel.

### Cách thực hiện

Owner tạo/mmap/unlink name, khởi tạo layout, mutex/conditions và workers. Producer submit bounded tasks. Shutdown state được đặt dưới mutex và broadcast. Workers drain, ghi unique result slots, increment atomic counter. Owner join rồi kiểm checksum, destroy primitives, unmap/close và xác nhận name không mở lại được.

### Output mong đợi

~~~text
submitted=8 processed=8 checksum=204 cleanup=ok
~~~

Output khác, timeout, TSan finding hoặc shm name còn tồn tại là fail trong scope fixture.

### Cách xác minh

~~~sh
cc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 -pthread assets/thread_pool_shm_demo.c -o thread_pool_demo
timeout 10s ./thread_pool_demo
~~~

TSan command dùng binary riêng như mục 3; nếu runtime/container không hỗ trợ TSan, ghi BLOCKED-RUNTIME cùng diagnostic, không báo PASS.

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

1. **pthread call “fail” nhưng errno=0:** log return code trực tiếp bằng strerror(rc).
2. **Test treo:** lấy thread backtraces và lock-order/shutdown timeline; không tăng timeout để che deadlock.
3. **TSan finding:** giữ exact stacks/interleaving, sửa happens-before root cause; không blanket suppress project source.
4. **mqueue/shm unavailable:** ghi environment diagnostic; không mount/change system limits bằng root. Shared fixture cần /dev/shm writable trong sandbox.
5. **Stale name:** cleanup exact run name; không wildcard xóa /dev/shm.
6. **Checksum/lost-duplicate mismatch:** so submitted/processed/published IDs, không chỉ atomic count.
7. **Stress pass một lần:** lặp bounded runs với fixed seeds/counts và deadline; lưu distribution/failure run.

## 6. Từ điển thuật ngữ và mô hình tư duy

- **IPC:** communication giữa execution contexts/processes.
- **FIFO:** named byte-stream pipe endpoint.
- **POSIX shm:** named object mapped thành shared bytes; không tự synchronize.
- **POSIX mqueue:** kernel queue giữ message boundaries/priority.
- **Predicate:** state condition protected by mutex, không phải cond signal.
- **Happens-before:** ordering relation làm memory effects được quan sát hợp lệ.
- **Data race:** conflicting unsynchronized accesses; UB trong C.
- **Deadlock:** cycle/protocol khiến threads không tiến triển.
- **Joinable/detached:** lifecycle ownership modes của pthread.
- **Atomic:** object/operation có C memory-order semantics.
- **Backpressure:** producer bị chặn/reject khi bounded capacity đầy.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

POSIX.1-2017, C17/WG14, Linux man-pages, Clang 14 TSan, CERT C và syllabus; source được paraphrase, asset được viết mới.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — user-approved project spine]:** M08 backend và A09 downstream reuse.
- **[SUY DIỄN — course fixture]:** tasks 1..8, queue capacity 3, shm name/result layout và checksum.
- **[BỔ SUNG — nguồn: POSIX.1-2017]:** pthread/condition/IPC semantics và direct error codes.
- **[BỔ SUNG — nguồn: C17/Clang TSan/CERT C]:** data-race UB, atomics, diagnostic evidence limits.

---

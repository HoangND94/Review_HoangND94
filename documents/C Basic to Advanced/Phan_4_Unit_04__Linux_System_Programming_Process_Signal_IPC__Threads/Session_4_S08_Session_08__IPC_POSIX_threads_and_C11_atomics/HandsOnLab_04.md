# Hands-on Lab LAB-P04-01 — Đồng bộ thread pool và POSIX shared memory không race

> **Khóa học:** [NFP] Advanced C Programming · **Unit:** Session 08 — IPC, POSIX threads and C11 atomics · **Thuộc:** Part 4 — Linux System Programming: Process, Signal, IPC & Threads

| Thuộc tính | Giá trị |
| --- | --- |
| Mã lab | LAB-P04-01 |
| Hình thức | guided_with_fading |
| Thời lượng dự kiến | 90 phút |
| Độ khó | medium |
| Mức xác thực | inherit — project simulated, dữ liệu synthetic |
| Pilot | fresher with C basics, biên thời lượng ±20% |

## 🎯 Learning Outcomes được thực hành

- **ADVC-H2SD:** xây dựng và kiểm chứng chương trình C/Linux dùng pthread, condition variable, C11 atomic và POSIX shared memory với lifecycle, đồng bộ và cleanup đúng contract. Cả ba checkpoint đều map LO này tới executable output, predicate evidence và bounded stress log.

## 🧭 Bối cảnh nghề nghiệp/dự án và project increment

Học viên đóng vai concurrency maintainer của **MDB Edge Diagnostics Gateway — Simulated**. Lab dùng một slice synthetic của M08: hai joinable workers nhận tám task qua bounded queue capacity 3, ghi kết quả vào POSIX shared-memory mapping và bàn giao count/checksum sau `pthread_join`.

Increment của lab là scratch source đã thêm invariant checks, evidence về mutex/condition predicates, stress 50 run và owner cleanup. Lab không tích hợp core v6, cross-process protocol hay change request của Assignment 08.

## 🧰 Điều kiện bắt đầu

### Kiến thức/kỹ năng tiên quyết

- Biết pthread create/join, mutex, condition variable và khác biệt giữa `errno` với pthread return code.
- Hiểu predicate loop, bounded queue invariant và C11 atomic counter.
- Biết POSIX `shm_open`/`ftruncate`/`mmap`/`shm_unlink`; chỉ dùng resource có run-specific name.

### Môi trường, công cụ và phiên bản

- Ubuntu 22.04/Linux 5.15, glibc 2.35, C17; local sandbox/container `codex/adv-c-jammy:20260821` hoặc tương đương.
- GCC 11.4 cho normal/stress; Clang 14 cho binary TSan riêng chạy qua `setarch x86_64 -R`.
- `/dev/shm` writable trong sandbox. Không network, endpoint, sudo, sysctl, service hoặc credential.

Preflight cơ bản:

```bash
gcc --version | head -1
clang-14 --version | head -1
getconf _POSIX_THREADS
test -d /dev/shm && test -w /dev/shm
```

TSan là gate bắt buộc nên Final validation phải chạy trong profile cô lập dưới đây. `seccomp=unconfined` tắt seccomp filter của container để `personality(ADDR_NO_RANDOMIZE)` dùng bởi `setarch` hoạt động; đây là ngoại lệ rộng ở syscall layer nên phạm vi được bù bằng network-none, root filesystem read-only, UID `65534`, drop toàn bộ capability và `no-new-privileges`. Không dùng profile này cho service, production data hoặc workload có network.

Từ thư mục Session trên host, bind riêng deliverables vào `/evidence` có quyền ghi cho UID `65534`, rồi mở shell validation:

```bash
docker run --rm -it \
  --network none \
  --read-only \
  --tmpfs /tmp:rw,exec,nosuid,nodev,size=256m \
  --user 65534:65534 \
  --cap-drop ALL \
  --security-opt no-new-privileges \
  --security-opt seccomp=unconfined \
  -v "$PWD:/session:ro" \
  -v "$PWD/lab04-deliverables:/evidence:rw" \
  -w /session \
  -e LAB04_EVIDENCE=/evidence \
  codex/adv-c-jammy:20260821 bash
```

Nếu profile trên không khởi tạo được TSan thì Lab ở trạng thái **BLOCKED** và không được phát hành `LAB04_FINAL_PASS`; không hạ gate xuống normal stress.

### Starter asset

- [assets/thread_pool_shm_demo.c](assets/thread_pool_shm_demo.c): bounded queue, two-worker lifecycle, shared result channel và exact cleanup oracle.
- Plan path: `Phan_4_Unit_04__Linux_System_Programming_Process_Signal_IPC__Threads/Session_4_S08_Session_08__IPC_POSIX_threads_and_C11_atomics/assets/thread_pool_shm_demo.c`.

Tạo deliverable source và build root cô lập:

```bash
export LAB04_BUILD_ROOT="$(mktemp -d /tmp/advc-lab04.XXXXXX)"
export LAB04_EVIDENCE="$PWD/lab04-deliverables"
mkdir -p "$LAB04_EVIDENCE"
cp assets/thread_pool_shm_demo.c \
  "$LAB04_EVIDENCE/lab04_thread_pool.c"
printf 'build_root=%s\n' "$LAB04_BUILD_ROOT" | \
  tee "$LAB04_EVIDENCE/lab04_environment.log"
```

### Input/trạng thái ban đầu

- Task IDs `0..7`, values `1..8`; expected square checksum `204`.
- Queue capacity `3`, worker count `2`, shared result capacity `8`.
- Shared object name `/advc_s08_<pid>`, `O_EXCL`, mode `0600`; owner unlinks name ngay sau successful mapping.
- `processed` là relaxed atomic count; result visibility ở owner dựa trên unique slots và successful joins.

### Ràng buộc

- Chỉ sửa scratch `lab04_thread_pool.c`; không sửa starter phát hành hoặc Assignment.
- Không thay checksum/task count để che lost/duplicate work; không thêm sleep làm synchronization protocol.
- Mọi queue state read/write và condition predicate thuộc cùng mutex; unlock trước compute/join.
- TSan là build riêng và phải chạy `PASS` trong profile cô lập đã pin; normal stress không thay thế được TSan gate.
- Không xóa `/dev/shm/advc_s08_*` bằng wildcard. Nếu thấy stale object không xác định ownership, dừng và báo instructor.

## 📚 Nguồn và provenance

- Nguồn kỹ thuật đã map: SRC-C17-ISO, SRC-C17-WG14, SRC-POSIX17, SRC-LINUX-MAN, SRC-LLVM14 và SRC-CERTC.
- **[BỔ SUNG — nguồn: SRC-USER-LABS]** Guided workflow, invariant instrumentation, bounded stress, deliverable và fading policy do người dùng yêu cầu.

## 📋 Lab outline và Definition of Done

### Phạm vi

1. Chứng minh starter strict-build/run và cleanup baseline.
2. Thêm invariant checks, giải thích hai condition predicates và verify output không đổi.
3. Tự dựng bounded stress + cleanup gate và chứng minh TSan `PASS` trên profile đã pin.

### Definition of Done

- Normal binary strict-build exit `0` và in đúng `submitted=8 processed=8 checksum=204 cleanup=ok`.
- Scratch source giữ `while` predicate, mutex ownership, stop/broadcast, join-before-destroy và unique shared-memory cleanup; invariant checks không thay algorithm.
- Stress log có đúng 50 dòng oracle, không timeout, không stale shared-memory name trong sandbox cô lập.
- `lab04_evidence.md` ghi lock/predicate/happens-before/cleanup decision và exact TSan profile; Final validation chỉ chấp nhận `TSan=PASS`.
- Có đủ `lab04_thread_pool.c`, `lab04_evidence.md`, `lab04_stress.log`; build root được cleanup an toàn.

## 🪜 Mức hướng dẫn

- **Checkpoint CP-LAB-P04-01 — guided:** exact compile/run/cleanup oracle.
- **Checkpoint CP-LAB-P04-02 — guided_with_fading:** chỉ rõ invariant và vị trí lock, học viên tự đặt assertion/comment hợp lý.
- **Checkpoint CP-LAB-P04-03 — fading:** học viên tự tổ chức stress/TSan evidence và ra quyết định theo stderr/status.

---

## Checkpoint CP-LAB-P04-01 — Baseline strict build, run và cleanup

### Action

Biên dịch scratch source bằng GCC strict C17/pthread. Chạy một lần trong timeout và kiểm exact stdout. Chỉ quan sát `/dev/shm`; không xóa resource bằng pattern.

### Verify

```bash
set -o pipefail
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 -pthread \
  "$LAB04_EVIDENCE/lab04_thread_pool.c" \
  -o "$LAB04_BUILD_ROOT/thread_pool_demo"
timeout 10s "$LAB04_BUILD_ROOT/thread_pool_demo" 2>&1 | \
  tee "$LAB04_EVIDENCE/lab04_baseline.log"
grep -Fx 'submitted=8 processed=8 checksum=204 cleanup=ok' \
  "$LAB04_EVIDENCE/lab04_baseline.log"
if find /dev/shm -maxdepth 1 -name 'advc_s08_*' -print -quit | grep -q .; then
  printf 'stale shared-memory name detected\n' >&2
  exit 1
fi
```

### Expected result

- Compile và run exit `0`; không warning.
- Stdout có đúng một dòng `submitted=8 processed=8 checksum=204 cleanup=ok`.
- Không timeout, stderr hoặc matching stale name sau owner teardown.

### Evidence

Giữ `lab04_environment.log`, `lab04_baseline.log`. Bắt đầu `lab04_evidence.md` với compiler fingerprint, exact command, output, exit code và kết quả read-only cleanup check.

### Troubleshooting

- Link thiếu pthread symbol → xác nhận `-pthread` có ở compile/link command.
- `shm_open: File exists` → starter copy/name policy đã bị đổi hoặc sandbox có stale resource; không xóa wildcard, dùng sandbox sạch và ghi evidence.
- Timeout → không thêm sleep; dùng GDB/backtrace hoặc tạm log `count/stopping` dưới mutex để xác định predicate không tiến triển.

### Reset/rollback

Xóa riêng binary baseline, copy lại scratch source từ starter nếu chưa có thay đổi hợp lệ:

```bash
case "$LAB04_BUILD_ROOT" in
  /tmp/advc-lab04.*) rm -f -- "$LAB04_BUILD_ROOT/thread_pool_demo" ;;
  *) printf 'Refuse unsafe reset: %s\n' "$LAB04_BUILD_ROOT" >&2; exit 64 ;;
esac
```

Program đúng đã unlink name ngay sau map và unmap/close khi kết thúc; không có IPC resource để reset thủ công.

---

## Checkpoint CP-LAB-P04-02 — Mutex ownership và condition predicate

### Action

Trong scratch source:

1. Thêm `<assert.h>` và một file-local invariant check cho `count <= QUEUE_CAPACITY`, `head < QUEUE_CAPACITY`, `tail < QUEUE_CAPACITY`.
2. Chỉ gọi invariant check khi thread đang giữ `queue->mutex`: sau lock, sau push/pop mutation và trước unlock.
3. Ghi comment ngắn tại hai wait loops: producer chờ `count < capacity || stopping`; worker chờ `count > 0 || stopping`.
4. Không đổi `while` thành `if`, không signal trước state mutation và không giữ mutex khi compute hoặc join.

Hoàn thiện bảng trong `lab04_evidence.md`: `shared state | mutex owner | wait predicate | state mutation | signal/broadcast | visibility/teardown oracle`.

### Verify

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -O0 -g -pthread \
  "$LAB04_EVIDENCE/lab04_thread_pool.c" \
  -o "$LAB04_BUILD_ROOT/thread_pool_checked"
for run in $(seq 1 10); do
  timeout 10s "$LAB04_BUILD_ROOT/thread_pool_checked"
done | tee "$LAB04_EVIDENCE/lab04_predicate.log"
test "$(grep -Fxc 'submitted=8 processed=8 checksum=204 cleanup=ok' \
  "$LAB04_EVIDENCE/lab04_predicate.log")" -eq 10
```

### Expected result

- Strict Debug compile exit `0`.
- Mười run đều exit `0`, log có đúng 10 oracle lines; không assertion, hang hoặc stale cleanup.
- Evidence table chỉ rõ condition variable không lưu state: state nằm ở queue fields dưới mutex, nên predicate luôn được kiểm lại bằng `while`.

### Evidence

`lab04_thread_pool.c`, `lab04_predicate.log` và predicate table trong `lab04_evidence.md`. Ghi line/function nơi invariant được gọi; không cần chụp toàn bộ source vào report.

### Troubleshooting

- Assertion fail → xác định assertion chạy khi có mutex hay không, rồi kiểm mutation order; không bỏ assertion để pass.
- Count dưới/qua capacity → kiểm head/tail modulo và push/pop cùng mutex.
- Hang sau stop → kiểm `stopping` được set dưới mutex, broadcast trước unlock, owner unlock trước join.

### Reset/rollback

Giữ evidence, copy lại starter thành `lab04_thread_pool.c` rồi áp dụng lại từng invariant change nếu scratch bị hỏng. Xóa riêng `thread_pool_checked`; không xóa toàn evidence directory.

---

## Checkpoint CP-LAB-P04-03 — Fading bounded stress, TSan và owner cleanup

### Action

Tự dựng stress gate 50 run có timeout, exact output count và cleanup check. Sau normal stress, build một binary TSan riêng bằng Clang 14 và chạy qua `setarch x86_64 -R` trong exact Docker profile đã pin. Gate chỉ có hai kết quả hoàn tất:

- `PASS`: mọi TSan run exit `0`, exact stdout, stderr rỗng.
- `FAIL-RACE`: có data-race report hoặc project finding; sửa synchronization rồi chạy lại normal stress và TSan.

Nếu runtime/profile không chạy được thì dừng với trạng thái **BLOCKED**; đó không phải kết quả hoàn tất Lab.

### Verify

```bash
: > "$LAB04_EVIDENCE/lab04_stress.log"
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 -pthread \
  "$LAB04_EVIDENCE/lab04_thread_pool.c" \
  -o "$LAB04_BUILD_ROOT/thread_pool_stress"
for run in $(seq 1 50); do
  timeout 10s "$LAB04_BUILD_ROOT/thread_pool_stress" >> \
    "$LAB04_EVIDENCE/lab04_stress.log"
done
test "$(grep -Fxc 'submitted=8 processed=8 checksum=204 cleanup=ok' \
  "$LAB04_EVIDENCE/lab04_stress.log")" -eq 50

if find /dev/shm -maxdepth 1 -name 'advc_s08_*' -print -quit | grep -q .; then
  printf 'stale shared-memory name detected\n' >&2
  exit 1
fi

clang-14 -std=c17 -Wall -Wextra -Wpedantic -Werror -O1 -g \
  -fno-omit-frame-pointer -fsanitize=thread -pthread \
  "$LAB04_EVIDENCE/lab04_thread_pool.c" \
  -o "$LAB04_BUILD_ROOT/thread_pool_tsan"
set +e
TSAN_OPTIONS=halt_on_error=1:exitcode=66 \
  setarch x86_64 -R timeout 20s \
  "$LAB04_BUILD_ROOT/thread_pool_tsan" \
  >"$LAB04_BUILD_ROOT/tsan.stdout" 2>"$LAB04_BUILD_ROOT/tsan.stderr"
tsan_exit=$?
set -e
printf 'tsan_exit=%d\n' "$tsan_exit"
sed -n '1,20p' "$LAB04_BUILD_ROOT/tsan.stderr"
```

### Expected result

- Normal stress bắt buộc pass: 50/50 exact lines, mọi run trước timeout, no stale name.
- TSan exit `0`, stdout là exact oracle và stderr rỗng trong profile đã pin.
- Profile đã được kiểm bằng các fresh container invocations; không dùng một run runtime-fatal làm bằng chứng pass.

### Evidence

- `lab04_stress.log` đúng 50 lines.
- Trong `lab04_evidence.md`: stress count, cleanup result, exact Docker flags, TSan command/version/exit và dòng `TSan=PASS`.
- `lab04_thread_pool.c` là exact source đã dùng cho cả normal và TSan build.

### Troubleshooting

- Có 49/50 oracle lines hoặc timeout → tìm run fail, giữ log/stderr, kiểm predicate/lifecycle; không tăng timeout vô hạn.
- TSan data-race report → đọc hai access stacks và locksets; sửa ownership/happens-before, không suppress rộng.
- `unexpected memory mapping` → xác nhận đang dùng exact `setarch x86_64 -R` profile. Nếu vẫn lỗi, lưu stderr và báo Lab **BLOCKED**; không phát hành pass.
- Stale shared memory → dừng; xác định exact owner/run trước cleanup. Không dùng `rm /dev/shm/advc_s08_*`.

### Reset/rollback

Binary/stress resources chỉ nằm dưới exact build root. Program đúng immediate-unlink shared name; join/unmap/close trước exit. Nếu cleanup check fail, không tiếp tục run mới trong cùng sandbox cho tới khi ownership được xác minh.

## 🧪 Final validation

**Phương thức xác minh:** `executable`, fail-fast. Chạy trong exact Docker profile đã nêu. `lab04_evidence.md` phải có dòng máy đọc được `TSan=PASS`; `FAIL-RACE` hay runtime không khởi tạo được đều không được phát hành `LAB04_FINAL_PASS`.

```bash
set -Eeuo pipefail
: "${LAB04_EVIDENCE:?Run phần Starter asset trước}"
test -d "$LAB04_EVIDENCE"
test -s "$LAB04_EVIDENCE/lab04_thread_pool.c"
test -s "$LAB04_EVIDENCE/lab04_evidence.md"
test "$(id -u)" -eq 65534
grep -Eq '^CapEff:[[:space:]]+0+$' /proc/self/status
grep -Eq '^NoNewPrivs:[[:space:]]+1$' /proc/self/status
test "$(find /sys/class/net -mindepth 1 -maxdepth 1 -printf '%f\n' | \
  LC_ALL=C sort)" = lo
findmnt -no OPTIONS / | grep -Eq '(^|,)ro(,|$)'
setarch x86_64 -R true

LAB04_FINAL_ROOT="$(mktemp -d /tmp/advc-lab04-final.XXXXXX)"
lab04_final_cleanup() {
  case "${LAB04_FINAL_ROOT:-}" in
    /tmp/advc-lab04-final.*) rm -rf -- "$LAB04_FINAL_ROOT" ;;
    *) printf 'Refuse unsafe final cleanup: %s\n' \
         "${LAB04_FINAL_ROOT:-unset}" >&2; return 64 ;;
  esac
}
trap lab04_final_cleanup EXIT INT TERM
test -z "$(find "$LAB04_FINAL_ROOT" -mindepth 1 -maxdepth 1 -print -quit)"
cp "$LAB04_EVIDENCE/lab04_thread_pool.c" \
  "$LAB04_FINAL_ROOT/lab04_thread_pool.c"
source_sha256="$(sha256sum "$LAB04_FINAL_ROOT/lab04_thread_pool.c" | \
  awk '{print $1}')"
{
  printf 'source_sha256=%s\n' "$source_sha256"
  gcc --version | head -1
  clang-14 --version | head -1
  getconf _POSIX_THREADS
  uname -sr
} > "$LAB04_EVIDENCE/lab04_final_environment.log"

# Clean-sandbox precondition và strict learner build.
if find /dev/shm -maxdepth 1 -name 'advc_s08_*' -print -quit | grep -q .; then
  printf 'Pre-existing advc_s08 shared-memory name\n' >&2
  exit 1
fi
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -O2 -pthread \
  "$LAB04_FINAL_ROOT/lab04_thread_pool.c" \
  -o "$LAB04_FINAL_ROOT/thread_pool"
timeout 10s "$LAB04_FINAL_ROOT/thread_pool" \
  > "$LAB04_EVIDENCE/lab04_baseline.log" \
  2> "$LAB04_FINAL_ROOT/baseline.stderr"
test ! -s "$LAB04_FINAL_ROOT/baseline.stderr"
test "$(cat "$LAB04_EVIDENCE/lab04_baseline.log")" = \
  'submitted=8 processed=8 checksum=204 cleanup=ok'

# Exact bounded stress oracle: đúng 50 dòng, không extra output/stderr.
: > "$LAB04_EVIDENCE/lab04_stress.log"
: > "$LAB04_FINAL_ROOT/stress.stderr"
for run in $(seq 1 50); do
  timeout 10s "$LAB04_FINAL_ROOT/thread_pool" \
    >> "$LAB04_EVIDENCE/lab04_stress.log" \
    2>> "$LAB04_FINAL_ROOT/stress.stderr"
done
test ! -s "$LAB04_FINAL_ROOT/stress.stderr"
test "$(wc -l < "$LAB04_EVIDENCE/lab04_stress.log")" -eq 50
test "$(grep -Fxc \
  'submitted=8 processed=8 checksum=204 cleanup=ok' \
  "$LAB04_EVIDENCE/lab04_stress.log")" -eq 50
if find /dev/shm -maxdepth 1 -name 'advc_s08_*' -print -quit | grep -q .; then
  printf 'Stale advc_s08 shared-memory name after stress\n' >&2
  exit 1
fi

# TSan bắt buộc: 10 fresh processes qua profile setarch đã pin.
clang-14 -std=c17 -Wall -Wextra -Wpedantic -Werror -O1 -g \
  -fno-omit-frame-pointer -fsanitize=thread -pthread \
  "$LAB04_FINAL_ROOT/lab04_thread_pool.c" \
  -o "$LAB04_FINAL_ROOT/thread_pool_tsan"
: > "$LAB04_FINAL_ROOT/tsan.stdout"
: > "$LAB04_FINAL_ROOT/tsan.stderr"
for run in $(seq 1 10); do
  set +e
  TSAN_OPTIONS=halt_on_error=1:exitcode=66 \
    setarch x86_64 -R timeout 20s \
    "$LAB04_FINAL_ROOT/thread_pool_tsan" \
    >> "$LAB04_FINAL_ROOT/tsan.stdout" \
    2>> "$LAB04_FINAL_ROOT/tsan.stderr"
  tsan_exit=$?
  set -e
  if test "$tsan_exit" -ne 0; then
    if grep -Eq \
      'WARNING: ThreadSanitizer: data race|SUMMARY: ThreadSanitizer: data race' \
      "$LAB04_FINAL_ROOT/tsan.stderr"; then
      printf 'TSan project race detected; final validation fails\n' >&2
      exit 1
    fi
    printf 'TSan profile unavailable; LAB04 is BLOCKED (exit=%s)\n' \
      "$tsan_exit" >&2
    sed -n '1,20p' "$LAB04_FINAL_ROOT/tsan.stderr" >&2
    exit 75
  fi
done
test ! -s "$LAB04_FINAL_ROOT/tsan.stderr"
test "$(wc -l < "$LAB04_FINAL_ROOT/tsan.stdout")" -eq 10
test "$(grep -Fxc \
  'submitted=8 processed=8 checksum=204 cleanup=ok' \
  "$LAB04_FINAL_ROOT/tsan.stdout")" -eq 10
{
  printf 'tsan_runs=10\n'
  printf 'tsan_exit=0\n'
  printf 'TSan=PASS\n'
  cat "$LAB04_FINAL_ROOT/tsan.stdout"
} > "$LAB04_EVIDENCE/lab04_tsan.log"
grep -Fx 'TSan=PASS' "$LAB04_EVIDENCE/lab04_evidence.md"
grep -Ei 'predicate|mutex' "$LAB04_EVIDENCE/lab04_evidence.md" >/dev/null
grep -Ei 'pthread_join|join' "$LAB04_EVIDENCE/lab04_evidence.md" >/dev/null
grep -Ei 'cleanup|shm_unlink' "$LAB04_EVIDENCE/lab04_evidence.md" >/dev/null

# Khóa learner source, exact stress log, TSan evidence và reasoning hiện tại.
(
  cd "$LAB04_EVIDENCE"
  sha256sum \
    lab04_thread_pool.c \
    lab04_baseline.log \
    lab04_stress.log \
    lab04_tsan.log \
    lab04_evidence.md \
    lab04_final_environment.log > lab04_current.sha256
  sha256sum -c lab04_current.sha256
)

lab04_final_cleanup
trap - EXIT INT TERM
test ! -e "$LAB04_FINAL_ROOT"
printf 'LAB04_FINAL_PASS source_sha256=%s TSan=%s stress=50/50 cleanup=ok\n' \
  "$source_sha256" PASS
```

Final validation chỉ pass khi in `LAB04_FINAL_PASS`, strict learner build và normal stress/cleanup đều pass, hash record hiện tại kiểm được, và TSan pass 10/10 fresh processes với exit `0`, exact stdout, stderr rỗng. Mọi race finding là hard fail; profile/runtime không chạy được làm Lab **BLOCKED**, không tạo pass.

## 📦 Deliverables

- `lab04_thread_pool.c` — scratch source đã thêm invariant checks.
- `lab04_evidence.md` — predicate/ownership/happens-before/cleanup và TSan decision.
- `lab04_stress.log` — đúng 50 exact oracle lines.

## ♻️ Reset, cleanup và khả năng chạy lại

```bash
case "$LAB04_BUILD_ROOT" in
  /tmp/advc-lab04.*) rm -rf -- "$LAB04_BUILD_ROOT" ;;
  *) printf 'Refuse unsafe cleanup: %s\n' "$LAB04_BUILD_ROOT" >&2; exit 64 ;;
esac
test ! -e "$LAB04_BUILD_ROOT"
```

Không xóa `$LAB04_EVIDENCE`. Không có network/service/credential. Nếu run đúng, không còn named shared-memory object sau process exit.

## 🔁 Tái sử dụng ở S09

S09 dùng `lab04_evidence.md`, stress log và lock/lifecycle reasoning để review backend trước khi epoll frontend route request. Không dùng source lab như implementation Assignment 08 hoặc network backend hoàn chỉnh.

## 🔐 Chính sách lời giải

Lab cung cấp starter micro-case, invariant contract, command và oracle; checkpoint sau giảm hướng dẫn. Không có reference implementation hoặc walkthrough của Assignment 08.

## 📚 Provenance phần bổ sung

- **[BỔ SUNG — nguồn: SRC-USER-LABS]** Lab guided_with_fading, duration, invariant exercise, stress count, deliverables và reuse-by-S09 được thêm theo yêu cầu người dùng.
- API/synchronization semantics dựa trên POSIX.1-2017, C17 atomics, Linux man-pages và Clang 14 đã map; security exception của profile TSan được giới hạn theo yêu cầu người dùng và project context kế thừa simulated provenance.

---
<!-- QUALITY GATE: 3/3 checkpoint có Action/Verify/Expected/Evidence/Troubleshooting/Reset; local-only/network-none; TSan phải PASS, runtime unavailable làm Lab BLOCKED; không lộ Assignment. -->

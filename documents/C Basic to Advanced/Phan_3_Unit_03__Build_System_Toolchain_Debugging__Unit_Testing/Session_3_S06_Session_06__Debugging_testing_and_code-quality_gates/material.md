# Session S06: Session 06 — Debugging, testing and code-quality gates — Học liệu cốt lõi

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 03 — Build System, Toolchain, Debugging & Unit Testing

## 🎯 Learning Outcomes

- **ADVC-H3SD** [evaluate] — Đánh giá và cải thiện build, debug, test, phân tích tĩnh, coverage, profiling và secure-coding của mã C bằng bằng chứng tái lập từ GNU/LLVM toolchain và quy tắc CERT C phù hợp.

## 🧭 Ngữ cảnh nghề nghiệp/dự án và phần tăng trưởng của Unit

**Bối cảnh nghề nghiệp/dự án:** MDB Edge Diagnostics Gateway — Simulated. Học viên đóng vai quality reviewer, nhận **Packaged gateway core v5** cùng một fixture crash cố định và phải biến việc “đã sửa lỗi” thành một quality baseline có thể kiểm toán.

**Project increment sau Unit này:** milestone **M06** tạo **Quality-gated gateway core v6**, **A06 quality evidence** và defect/test decision note. Hai Assignment A07 và A08 chỉ được dùng baseline này sau khi diagnosis, regression, sanitizer, static-analysis và coverage gates cùng trỏ tới một snapshot.

**Mức xác thực của bối cảnh:** simulated; fixture, command và dữ liệu đều tổng hợp, không chứa memory dump hoặc dữ liệu khách hàng.

Năng lực mới gắn với ADVC-H3SD là chọn đúng công cụ cho từng câu hỏi, giữ bằng chứng pre-fix, sửa root cause tối thiểu và thiết kế gate có oracle rõ. “Không thấy lỗi” ở một tool không thay thế các tool còn lại.

## 📚 Nguồn đầu vào đã map

- [Debugging with GDB](https://sourceware.org/gdb/current/onlinedocs/gdb.html) — GDB 12.1 execution baseline; breakpoint, watchpoint, backtrace và core-file workflow.
- [Clang 14 documentation](https://releases.llvm.org/14.0.0/tools/clang/docs/index.html) — AddressSanitizer, UndefinedBehaviorSanitizer, ThreadSanitizer và clang-tidy.
- [GCC 11.4 manuals](https://gcc.gnu.org/onlinedocs/gcc-11.4.0/) — C17, debug/coverage instrumentation và gcov 11.4.
- [Cppcheck 2.7 manual](https://github.com/cppcheck-opensource/cppcheck/blob/2.7/man/manual.md) — project/compile-database analysis.
- [CMocka API](https://api.cmocka.org/) — API baseline 1.1.5.
- [LCOV 1.15 release](https://github.com/linux-test-project/lcov/releases/tag/v1.15) — trace capture/filter/summary.
- [SEI CERT C Coding Standard](https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/) — defect remediation và diagnostic review rules.
- Syllabus nội bộ v1.0 — phạm vi, LO, artifact và acceptance của Session 06.

---

## 1. Kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết

- Hoàn thành S05; clean-build được **Packaged gateway core v5** và hiểu translation unit/compile database.
- Đọc stack frame, source location, process exit status và CTest output.
- Phân biệt public API contract với implementation detail; không thay fixture để che lỗi.

### Môi trường, công cụ và phiên bản

- Ubuntu 22.04 native/VM/WSL2; C17; glibc 2.35.
- CMake 3.22.1; GCC/gcov 11.4; Clang/clang-tidy 14; GDB 12.1; cppcheck 2.7; CMocka 1.1.5.
- Ubuntu Jammy package `lcov 1.15-1` là package baseline. Trên Jammy, `lcov --version` có thể in `LCOV version 1.14`; evidence phải lưu **cả** package fingerprint và CLI fingerprint, không tự kết luận mismatch.
- ASan+UBSan dùng chung một Clang 14 binary; TSan dùng binary riêng. Không publish core file, absolute host path hoặc raw memory dump.

### Phương thức xác minh artifact

Phương thức là `artifact_review` kết hợp executable oracles. Kiểm tra môi trường trước khi diễn giải báo cáo:

```bash
cmake --version | head -1
gcc --version | head -1
gcov --version | head -1
clang-14 --version | head -1
gdb --version | head -1
cppcheck --version
pkg-config --modversion cmocka
apt-cache policy lcov
lcov --version
```

Baseline mong đợi: CMake 3.22.x, GCC/gcov 11.x, Clang 14.x, GDB 12.1, cppcheck 2.7, CMocka 1.1.5 và Jammy package `lcov 1.15-1`. Nếu fingerprint khác, lưu chênh lệch và không trộn report giữa các build.

## 2. Định vị trong lộ trình (Mental Map)

```text
M05: Packaged gateway core v5 + compile/build boundary
                    │
                    ▼
        fixed crash → GDB diagnosis → minimal fix
                    │
        ┌───────────┼───────────────┐
        ▼           ▼               ▼
  ASan/UBSan   CMocka + gcov    cppcheck/tidy
        └───────────┼───────────────┘
                    ▼
M06: Quality-gated gateway core v6 + version-matched evidence
                    │
              ┌─────┴─────┐
              ▼           ▼
        A07 process   A08 thread/IPC
```

S05 tạo package và compile database. S06 không thêm process/thread feature; nó chứng minh core hiện tại đủ ổn định để hai nhánh sau cùng tái sử dụng. TSan được giới thiệu ở đây nhưng gate thực thi có workload concurrent sẽ thuộc A08.

## 3. Nội dung lý thuyết cốt lõi

**Phạm vi nội dung:**

- [x] Debugging & code quality: gdb (breakpoint, watchpoint, backtrace, core dump), sanitizers (ASan/UBSan/TSan), static analysis (cppcheck, clang-tidy), unit test with CMocka/Unity, coverage with gcov/lcov

#### OUT-S06-01 Debugging & code quality: gdb (breakpoint, watchpoint, backtrace, core dump), sanitizers (ASan/UBSan/TSan), static analysis (cppcheck, clang-tidy), unit test with CMocka/Unity, coverage with gcov/lcov

**Mapping:** OUT-S06-01 · ADVC-H3SD · M06 / Quality-gated gateway core v6.

##### Định nghĩa rõ ràng và ranh giới

- **Debugger** điều khiển một process cụ thể. Breakpoint dừng tại vị trí/lệnh; watchpoint dừng khi giá trị/ô nhớ thay đổi; backtrace cho chuỗi frame; core file là snapshot process sau crash để phân tích offline. GDB giúp quan sát nguyên nhân ứng viên, không tự chứng minh fix đúng.
- **Sanitizer** là instrumentation do compiler chèn vào binary. ASan phát hiện nhiều lỗi truy cập/lifetime bộ nhớ, UBSan kiểm tra nhóm undefined behavior đã bật, TSan phát hiện data race khi schedule thực thi làm race quan sát được. Không tool nào chứng minh absence tuyệt đối.
- **Static analysis** suy luận trên source/AST/control-flow mà không cần chạy mọi path. cppcheck bổ sung heuristic riêng; clang-tidy dùng compile commands và có các nhóm check, trong đó `clang-analyzer-*` thực hiện path-sensitive analysis.
- **Unit test** gọi một production unit với input/fixture được kiểm soát và assertion có oracle. CMocka 1.1.5 là baseline của course; Unity là lựa chọn syllabus nêu nhưng không phải dependency bắt buộc của case này.
- **Coverage** đo code đã được instrumented test thực thi. gcov đọc `.gcno/.gcda` của GCC; LCOV gom, lọc và tóm tắt trace. Coverage là dấu hiệu về độ rộng test, không chứng minh assertion đúng hoặc defect-free.

Ranh giới quan trọng: breakpoint/watchpoint/backtrace là evidence quan sát; sanitizer/static analysis là detector theo mô hình riêng; test là behavioral oracle; coverage chỉ mô tả execution. Một report không thay thế report khác.

##### Vấn đề/vai trò và quyết định cần đưa ra

Quality reviewer phải quyết định:

1. Fixture nào tái hiện defect ổn định và evidence nào phải lưu **trước** khi sửa.
2. Frame/state nào là root cause thay vì điểm crash thứ cấp.
3. Fix nhỏ nhất nào giữ public API và A05 behavior.
4. Normal, boundary và error paths nào cần CMocka assertions.
5. Sanitizer nào ghép được, sanitizer nào phải tách build.
6. Compile database và check-set nào tạo static-analysis gate có thể tái lập.
7. File nào thuộc production coverage denominator và exclusion nào có lý do.
8. Finding nào phải sửa; finding ngoại lệ nào cần disposition truy vết.

Stakeholder A07/A08 cần một exact baseline. Evidence tạo từ commit khác hoặc option khác không đủ để release v6.

##### Cơ chế và mental model

**GDB:** Build với `-g` và tối ưu thấp để frame/biến dễ đọc. `break function` dừng trước khi chạy body; `watch expression` dùng hardware/software watchpoint để dừng khi value thay đổi; `bt full` nối call chain và locals. Với core file, GDB cần executable và debug symbols khớp exact binary. Core có thể chứa dữ liệu nhạy cảm nên chỉ giữ local rồi redact report.

**Sanitizers:** Compiler instrument load/store/arithmetic/synchronization và runtime thu metadata. ASan thường cần `-fno-omit-frame-pointer` để stack rõ. ASan+UBSan có thể kết hợp; TSan có runtime và memory model khác nên dùng build riêng. Detector chỉ thấy path đã chạy, vì vậy fixed fixtures và regression breadth vẫn bắt buộc.

**Static analysis:** `compile_commands.json` cung cấp include path, define và language options giống build. Nếu analyzer thiếu context, finding/no-finding đều có thể sai. Plan cố ý yêu cầu cppcheck 2.7 dùng `--std=c11` do parser limitation trong khi compiler vẫn build strict C17. Đây là parser setting, không hạ chuẩn production.

**CMocka:** Mỗi test có setup/action/assert/teardown rõ; `cmocka_unit_test` đăng ký function và `cmocka_run_group_tests` tổng hợp result. Assertion phải kiểm cả status lẫn output contract. Wrapper/mocking chỉ dùng ở boundary hợp lý; test không được copy lại production algorithm làm oracle.

**gcov/LCOV:** `--coverage` tạo compile metadata và counters. Chạy test sinh runtime data; `lcov --capture` tạo trace; `lcov --remove` lọc system/test/vendor/generated paths theo policy công bố; `lcov --summary` cho tỷ lệ. Thay exclusion để vượt 80% là làm sai denominator.

##### Khi dùng / khi không dùng, giới hạn và trade-off

- Dùng **breakpoint** khi cần quan sát entry/state theo control flow; dùng **watchpoint** khi biết state nào bị hỏng nhưng chưa biết writer. Không đặt hàng nghìn watchpoint hoặc coi optimized-away variable là bằng chứng thiếu defect.
- Dùng **core dump** khi crash khó tái hiện tương tác; không thu/publish core nếu fixture có secret hoặc policy cấm memory snapshot.
- Dùng **ASan+UBSan** cho memory/UB regression trong module tuần tự. Dùng **TSan** cho workload concurrent riêng; không ghép TSan với ASan trong cùng binary.
- Dùng **cppcheck + clang-tidy** để có hai perspective; không blanket-disable check hoặc phân tích source mà thiếu compile database.
- Dùng **CMocka** khi unit có C boundary dễ điều khiển. Dùng integration test khi behavior phụ thuộc nhiều process/module; mocking quá sâu chỉ chứng minh mock.
- Dùng **coverage threshold** như gate độ rộng đã định nghĩa. Không dùng coverage làm KPI duy nhất; một line executed không có nghĩa output đã được assert.
- Debug/coverage build ưu tiên quan sát (`-O0 -g`), sanitizer build ưu tiên instrumentation (`-O1 -g`), release performance build có mục tiêu khác. Không trộn report.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** quality reviewer triage một crash tính trung bình và bàn giao module ổn định cho process/thread teams.
- **Input/baseline/constraint:** [fixture crash](assets/s06_case/fixtures/legacy_crash.c) cố ý dereference null khi count bằng 0; [production module đã sửa](assets/s06_case/src/gateway_stats.c); CMocka 1.1.5; strict C17.
- **Decision/action:** build riêng fixture để lấy GDB backtrace; default build loại fixture lỗi, test production API; chạy ASan+UBSan, cppcheck/clang-tidy và coverage trên các build tách biệt.
- **Artifact/output:** [CMake project](assets/s06_case/CMakeLists.txt), CMocka test, diagnosis record và quality summaries.
- **Expected result:** pre-fix diagnostic dừng `SIGSEGV` ở `legacy_first`; default CTest có 4 tests pass; fixed API trả error cho null/zero input; production line coverage đạt ngưỡng case; static/sanitizer gates không còn finding mức chặn.
- **Verification/oracle/evidence:** exit status, `bt full`, CTest summary, sanitizer stderr, analysis output và LCOV summary. Diagnostic crash được kỳ vọng non-zero; nó là evidence, không phải gate pass.

##### Ví dụ code cụ thể

Micro-example độc lập với Assignment 06 mô phỏng lỗi off-by-one khi copy một C string vào buffer cố định. Build `INJECT_BUG` dùng điều kiện sai `len > capacity`, nên chấp nhận `len == capacity` rồi ghi thêm byte kết thúc null ra ngoài buffer. Build mặc định dùng `len >= capacity` và phải từ chối mà không đổi destination.

Lưu thành `/tmp/s06_micro.c`:

```c
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static int copy_tag(char *dst, size_t capacity, const char *src)
{
    if (dst == NULL || src == NULL || capacity == 0) {
        return -1;
    }
    const size_t len = strlen(src);
#ifdef INJECT_BUG
    if (len > capacity) {
#else
    if (len >= capacity) {
#endif
        return -1;
    }
    memcpy(dst, src, len + 1);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("usage: s06_micro TAG\n", stderr);
        return 64;
    }
    char buffer[4] = {'?', '?', '?', '?'};
    const int rc = copy_tag(buffer, sizeof buffer, argv[1]);
    if (rc != -1) {
        fprintf(stderr, "expected rejection, rc=%d\n", rc);
        return 2;
    }
    if (buffer[0] != '?') {
        fputs("buffer changed on rejection\n", stderr);
        return 3;
    }
    puts("S06_MICRO_PASS");
    return 0;
}
```

Tái hiện defect bằng ASan+UBSan. Exit khác `0` ở bước này là **evidence pre-fix mong đợi**, không phải quality-gate pass:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror \
  -DINJECT_BUG -O1 -g -fno-omit-frame-pointer \
  -fsanitize=address,undefined \
  /tmp/s06_micro.c -o /tmp/s06_bug_asan
ASAN_OPTIONS=halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1 \
  /tmp/s06_bug_asan ABCD
echo $?
```

Oracle pre-fix: stderr chứa `ERROR: AddressSanitizer: stack-buffer-overflow`; trong environment đã pin, process exit `1`.

Quan sát boundary bằng GDB trên binary Debug riêng:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror \
  -DINJECT_BUG -O0 -g /tmp/s06_micro.c -o /tmp/s06_bug_debug
gdb -q -batch \
  -ex 'break copy_tag' -ex run -ex next -ex next \
  -ex 'print len' -ex 'print capacity' -ex 'bt 2' \
  --args /tmp/s06_bug_debug ABCD
```

GDB phải hiển thị `len = 4`, `capacity = 4`, frame `copy_tag` và caller `main`. Container có thể cảnh báo không tắt được ASLR; cảnh báo đó không thay đổi oracle về hai giá trị và backtrace.

Build fixed và chạy các gate nhỏ, độc lập:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -O0 -g \
  /tmp/s06_micro.c -o /tmp/s06_fixed
/tmp/s06_fixed ABCD
echo $?

cppcheck --std=c11 --enable=warning,style --error-exitcode=1 \
  /tmp/s06_micro.c
clang-tidy-14 /tmp/s06_micro.c \
  --checks='-*,clang-analyzer-core.*,clang-analyzer-unix.*' \
  --warnings-as-errors='*' -- -std=c17

cd /tmp
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror --coverage \
  s06_micro.c -o s06_cov
./s06_cov ABCD >/dev/null
gcov s06_cov-s06_micro.gcno
```

Kết quả fixed mong đợi:

```text
S06_MICRO_PASS
0
cppcheck: exit 0, không có finding warning/style
clang-tidy-14: exit 0, không có analyzer finding trong check-set đã khai báo
gcov: tạo s06_micro.c.gcov và báo Lines executed lớn hơn 0%
```

- **Quyết định/root cause:** C string dài `len` cần `len + 1` bytes; vì vậy `len == capacity` đã là lỗi capacity. Sửa đúng boundary predicate thay vì đổi input hoặc tắt sanitizer.
- **Oracle/evidence:** ASan report + exit `1` và GDB `len/capacity` là evidence trước sửa; strict fixed run, analyzer commands và process exit `0` là gate sau sửa. Coverage chỉ chứng minh path đã chạy, không thay assertion hoặc tự trở thành threshold của micro-example.
- **Troubleshooting:** nếu ASan không symbol hóa, kiểm `-g`, frame pointer và matching symbolizer; nếu GDB hiện optimized-out, dùng đúng binary `-O0 -g`; nếu analyzer báo khác, lưu exact check/version và triage thay vì blanket suppression.
- **Giới hạn:** self-test dùng exit code để giữ ví dụ ngắn; CMocka/LCOV đầy đủ vẫn nằm ở integrated case của Unit. Micro-example không chứa API, fixture hay expected implementation của Assignment 06.

##### Best practices

| Rule | Rationale/cơ chế | Ví dụ đúng | Phản ví dụ/hậu quả |
|---|---|---|---|
| Cố định reproducer và lưu pre-fix evidence trước sửa. | Không có baseline thì không phân biệt root-cause fix với việc làm fixture ngừng đi qua path lỗi. | Lưu command, binary hash/commit, signal và failing frame. | Sửa fixture count từ 0 thành 1: crash biến mất nhưng error contract chưa được xử lý. |
| GDB evidence phải khớp executable/debug symbols; core ở local và được redact. | Symbol mismatch làm frame/source sai; core có thể chứa toàn bộ memory. | Ghi build ID/commit và chỉ nộp backtrace đã loại host path. | Mở core bằng binary mới rồi kết luận từ line number lệch. |
| ASan+UBSan và TSan là build riêng; mọi runtime gate chạy fixed fixtures. | Runtime/instrumentation khác nhau và chỉ thấy path đã chạy. | `build/asan` cho address+undefined, `build/tsan` cho concurrency. | Ghép TSan+ASan hoặc chỉ chạy happy path rồi tuyên bố sạch. |
| Analysis chạy từ compile database; suppression phải narrow và có disposition. | Include/define sai tạo false result; blanket suppression che lỗi mới. | `clang-tidy-14 -p build/debug ...` và record finding→fix/exception. | `--suppress=*` hoặc bỏ source lỗi khỏi target. |
| Unit test assert status và output ở normal/boundary/error paths. | Chỉ gọi function không kiểm contract; copy algorithm vào test có common-mode failure. | Assert mean, null rejection, zero-count rejection và overflow-safe case. | Test chỉ “không crash” hoặc tính expected bằng cùng algorithm. |
| Coverage denominator cố định trước khi đo. | Filter sau khi thấy kết quả cho phép gaming threshold. | Chỉ production source; exclude `/usr/*`, tests, vendor/generated theo policy. | Loại file coverage thấp không có lý do để vượt 80%. |

##### Anti-pattern, failure modes và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán/bằng chứng | Cách sửa | Phòng tránh |
|---|---|---|---|---|
| GDB hiện `??` hoặc locals “optimized out” | Thiếu `-g`, strip hoặc tối ưu cao/symbol mismatch. | `file`/`info files` và build fingerprint. | Rebuild Debug `-O0 -g` đúng snapshot. | Versioned debug build và manifest. |
| ASan report không có symbol | Thiếu frame pointer/symbolizer. | Kiểm compile flags và `llvm-symbolizer-14`. | Bật `-g -fno-omit-frame-pointer`, cài matching LLVM tool. | Preflight tool version. |
| Cppcheck/tidy báo header không tìm thấy | Compile database stale hoặc chạy sai build dir. | Mở command của TU trong `compile_commands.json`. | Clean configure với export database rồi chạy `-p`/`--project` đúng path. | Sinh database trong gate. |
| CMocka link fail | Thiếu `libcmocka-dev` hoặc pkg-config metadata. | `pkg-config --modversion cmocka`. | Dùng package baseline 1.1.5 trong environment được cấp. | Preflight trước buổi học. |
| Coverage bằng 0 hoặc stale | Chưa chạy instrumented test hoặc dùng `.gcda` từ build khác. | Timestamp/paths và gcov diagnostics. | Clean coverage build, chạy CTest rồi capture. | Mỗi metric một build directory. |
| `lcov --version` in 1.14 dù apt package là 1.15-1 | Jammy package/CLI fingerprint khác nhau. | Lưu `apt-cache policy lcov` và `lcov --version`. | Không “sửa” tool; ghi cả hai fingerprint trong manifest. | Dùng package version làm environment pin, CLI output làm runtime evidence. |

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### Input/trạng thái ban đầu

[assets/s06_case](assets/s06_case/CMakeLists.txt) chứa một fixture crash được bật bằng `BUILD_CRASH_FIXTURE=ON`, module production đã sửa và bốn CMocka tests. Default build không compile fixture lỗi vào quality gate.

### Cách thực hiện

Tạo build triage riêng để quan sát crash; tạo default/ASan/coverage directories độc lập cho code đã sửa. Static analysis dùng compile database của default build. Mỗi command lưu exit status và version fingerprint.

### Output mong đợi

- Triage: process nhận `SIGSEGV`; backtrace chứa `legacy_first`. Non-zero là kết quả được dự kiến.
- Default: bốn CMocka tests pass.
- Sanitizer: test exit 0, không có ASan/UBSan report thuộc project.
- Coverage: production lines ít nhất 80%; denominator chỉ gồm `src/gateway_stats.c` trong case.
- Analysis: cppcheck exit 0; clang-tidy không còn finding blocking chưa có disposition.

### Cách xác minh

```bash
cmake -S assets/s06_case -B /tmp/s06-triage \
  -DCMAKE_BUILD_TYPE=Debug -DBUILD_CRASH_FIXTURE=ON
cmake --build /tmp/s06-triage --target gateway_crash_fixture
gdb -q -batch -ex 'set pagination off' -ex run -ex 'bt full' \
  --args /tmp/s06-triage/apps/gateway_crash_fixture

cmake -S assets/s06_case -B /tmp/s06-debug \
  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build /tmp/s06-debug
ctest --test-dir /tmp/s06-debug --output-on-failure
cppcheck --project=/tmp/s06-debug/compile_commands.json \
  --std=c11 --error-exitcode=1
clang-tidy-14 -p /tmp/s06-debug \
  assets/s06_case/src/gateway_stats.c \
  --checks='clang-analyzer-*,cert-*'
```

Xem [example.md](example.md) để chạy ASan+UBSan và LCOV đầy đủ. Các đường dẫn `/tmp/s06-*` tránh ghi build artifact vào học liệu; có thể thay bằng build directories cô lập trong repository bài làm.

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

- Triage command cố ý crash; đừng đưa nó vào pass suite. Gate đúng là: crash evidence trước sửa **và** regression pass sau sửa.
- Nếu “fix” đổi public signature/status contract, AT-A06-01 vẫn fail dù crash biến mất.
- Nếu ASan sạch nhưng Valgrind/static analysis báo defect, điều tra mỗi finding theo detector; không dùng report này phủ định report kia.
- Nếu coverage dưới 80%, bổ sung test cho behavior thiếu; không thay exclusion sau khi xem số.
- Nếu clang-tidy check không có trên Clang 14, ghi exact diagnostic và dùng check-set đã pin; không âm thầm chuyển sang rolling version.
- Quy tắc CERT review phù hợp gồm ERR33-C (kiểm return value), EXP33-C (không đọc giá trị chưa khởi tạo) và MEM safety rules áp dụng cho defect quan sát được.

## 6. Từ điển thuật ngữ và mô hình tư duy

- **Breakpoint:** điểm dừng theo location/control flow.
- **Watchpoint:** điểm dừng khi giá trị hoặc memory location thay đổi.
- **Backtrace:** chuỗi call frames tại thời điểm dừng.
- **Core dump:** snapshot process phục vụ post-mortem; có thể nhạy cảm.
- **Instrumentation:** code kiểm tra/counter được compiler chèn vào binary.
- **Finding:** chẩn đoán cần triage, không mặc nhiên là defect hoặc false positive.
- **Disposition:** quyết định truy vết finding tới fix hoặc exception có lý do.
- **Fixture:** input/state cố định dùng để tái hiện/test.
- **Denominator policy:** tập production lines được tính vào coverage.
- **Quality gate:** điều kiện pass/fail có command, oracle và evidence xác định trước.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

Các nguồn ở mục “Nguồn đầu vào đã map” được dùng ở chế độ reference/paraphrase. Execution scope pin CMake 3.22.1, GCC/gcov 11.4, Clang/clang-tidy 14, GDB 12.1, cppcheck 2.7, CMocka 1.1.5 và Ubuntu Jammy package lcov 1.15-1.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — được user phê duyệt trong project plan]** Gateway, stakeholder và chuỗi M05→M06→A07/A08 là project spine mô phỏng.
- **[BỔ SUNG — nguồn: Ubuntu Jammy package metadata và runtime fingerprint]** Package `lcov 1.15-1` có thể tự báo CLI `LCOV version 1.14`; lưu hai fingerprint là quy tắc evidence của course environment.
- **[SUY DIỄN — từ quality-gate mechanics đã map]** Severity “blocking” và disposition manifest là policy của case; tool không tự quyết định business severity.
- Asset là implementation đào tạo nguyên bản, không phải reference implementation của Assignment 06.

---

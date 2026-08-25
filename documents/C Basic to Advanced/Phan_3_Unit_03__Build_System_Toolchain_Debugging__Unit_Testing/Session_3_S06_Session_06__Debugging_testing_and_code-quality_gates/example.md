# Session S06: Session 06 — Debugging, testing and code-quality gates — Ví dụ và nghiên cứu tình huống

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 03 — Build System, Toolchain, Debugging & Unit Testing

## 🎯 Learning Outcomes liên quan

- **ADVC-H3SD** [evaluate] — Đánh giá và cải thiện build, debug, test, phân tích tĩnh, coverage và secure-coding bằng evidence tái lập.
- Case chứng minh chuỗi evidence: reproducer → GDB diagnosis → minimal fix → CMocka regression → sanitizer/static-analysis/coverage gates.

## 🧭 Liên kết với ngữ cảnh nghề nghiệp/dự án

- **Baseline:** Packaged gateway core v5 và synthetic crash fixture.
- **Increment minh họa:** một module tính trung bình được quality-gate trước khi process/thread teams tái sử dụng.
- **Artifact:** diagnostic evidence và [asset chạy được](assets/s06_case/CMakeLists.txt).
- **Phạm vi:** đây là case QG-06 nhỏ, hoàn chỉnh. Assignment 06 dùng change request và baseline lớn hơn; asset này không phải đáp án tham chiếu để nộp lại.

## 🧰 Điều kiện chạy ví dụ

- Ubuntu 22.04 native/VM/WSL2.
- CMake 3.22.1; GCC/gcov 11.4; Clang/clang-tidy 14; GDB 12.1; cppcheck 2.7; CMocka 1.1.5; Jammy package lcov 1.15-1.
- `pkg-config --modversion cmocka` phải in `1.1.5`.
- Jammy có thể cài package `lcov 1.15-1` nhưng `lcov --version` in `LCOV version 1.14`; lưu cả hai fingerprint.
- Các build của case dùng directory tách biệt. Diagnostic crash cố ý trả non-zero.

## 📚 Nguồn đầu vào đã map

- GDB manual; Clang 14 sanitizer/clang-tidy documentation; GCC 11.4/gcov manuals.
- Cppcheck 2.7 manual; CMocka 1.1.5 API; LCOV 1.15 release; CERT C.
- Syllabus nội bộ v1.0 và OUT-S06-01.

### Mapping case đã chốt trong course plan

| Case | Outline | LO | Input cụ thể | Output/oracle |
|---|---|---|---|---|
| CASE-S06-01 / QG-06 | OUT-S06-01 | ADVC-H3SD | Null-dereference fixture, production mean API, four path tests | `SIGSEGV`/`legacy_first` pre-fix; four CMocka cases pass post-fix; sanitizer/analysis clean; production line coverage ≥80% |

## Case Study 01: Ticket QG-06 — Từ null dereference tới quality baseline kiểm toán được

### 1. Ticket và tiêu chí thành công

Một legacy probe gọi `legacy_first(NULL)` khi không có command-line argument. Stakeholder không chấp nhận patch chỉ làm crash biến mất: họ cần evidence xác định failing frame, API production có error contract, test phủ normal/boundary/error paths và các gate tái lập.

Tiêu chí thành công:

1. GDB tái hiện đúng `SIGSEGV` và frame `legacy_first`.
2. Fix production không đọc null, không chia zero và giữ output không đổi khi error.
3. Bốn CMocka cases kiểm normal, wide-sum boundary, null và empty input.
4. ASan+UBSan, cppcheck và clang-tidy không còn finding mức chặn.
5. LCOV production line coverage ít nhất 80% với denominator công bố.
6. Mỗi report ghi tool fingerprint và build directory tương ứng.

### 2. Input, trạng thái ban đầu và ràng buộc

Asset:

```text
assets/s06_case/
├── CMakeLists.txt
├── include/gateway_stats.h
├── src/gateway_stats.c
├── fixtures/legacy_crash.c
└── tests/test_stats.c
```

- [`legacy_crash.c`](assets/s06_case/fixtures/legacy_crash.c) là artifact chẩn đoán cố ý lỗi và chỉ build khi bật `BUILD_CRASH_FIXTURE=ON`.
- [`gateway_stats.c`](assets/s06_case/src/gateway_stats.c) là production path đã sửa.
- [`test_stats.c`](assets/s06_case/tests/test_stats.c) dùng API CMocka 1.1.5.
- Không sửa fixture để đổi null thành dữ liệu hợp lệ.
- Không compile fixture lỗi vào default quality gate.
- ASan+UBSan và coverage có build directory riêng; TSan không áp dụng vì case không có shared-memory concurrency.

### 3. Phân tích lựa chọn

| Lựa chọn | Giá trị | Giới hạn/trade-off | Quyết định |
|---|---|---|---|
| Chỉ đọc line crash | Nhanh | Line dereference chưa giải thích caller/state | Không đủ |
| GDB breakpoint/backtrace | Quan sát call chain và locals | Phụ thuộc debug symbols, execution path | Dùng cho pre-fix evidence |
| ASan+UBSan | Bắt memory/UB trên paths chạy | Không phát hiện mọi defect, runtime overhead | Dùng cho regression |
| TSan | Phát hiện race | Không có workload concurrent trong case | Không dùng ở case; dành cho A08 |
| CMocka | Oracle API rõ, failure isolation | Cần dependency 1.1.5 | Dùng |
| gcov/LCOV | Đo path đã thực thi ở line level | Không đo chất lượng assertion | Dùng cùng tests |
| cppcheck + clang-tidy | Phân tích mà không cần input chạy | Có false positive/context sensitivity | Dùng compile database + disposition |

Root cause được phân biệt với symptom: `legacy_first` dereference pointer không có precondition enforcement; “thêm argument khi chạy” chỉ tránh path lỗi. Production contract vì vậy phải reject null/empty và không sửa `out_mean` khi thất bại.

### 4. Cách triển khai

#### 4.1 Triage build và GDB evidence

```bash
cmake -S assets/s06_case -B /tmp/s06-triage \
  -DCMAKE_BUILD_TYPE=Debug \
  -DBUILD_CRASH_FIXTURE=ON
cmake --build /tmp/s06-triage --target gateway_crash_fixture

gdb -q -batch \
  -ex 'set pagination off' \
  -ex 'break legacy_first' \
  -ex run \
  -ex 'print values' \
  -ex continue \
  -ex 'bt full' \
  --args /tmp/s06-triage/apps/gateway_crash_fixture
```

`continue` kết thúc bằng signal nên command GDB có thể non-zero. Evidence đúng phải thể hiện `values = 0x0` và frame `legacy_first`; không đưa lệnh này vào pass suite.

#### 4.2 Error contract và wide accumulator

Public API của case:

```c
enum gateway_stats_status gateway_mean_i32(
    const int32_t *values,
    size_t count,
    int32_t *out_mean);
```

Core của fix kiểm output/input pointer trước, reject `count == 0` và cộng trong `int64_t`. Chỉ khi thành công mới ghi `*out_mean`. Xem [implementation đầy đủ](assets/s06_case/src/gateway_stats.c) và [header contract](assets/s06_case/include/gateway_stats.h).

Ràng buộc quan sát:

- `{2,4,6,8}` → status OK, mean `5`.
- `{INT32_MAX,INT32_MAX}` → status OK, mean `INT32_MAX`; cộng trong 32 bit sẽ overflow.
- null input/output → `GATEWAY_STATS_INVALID_ARGUMENT`.
- count bằng 0 → `GATEWAY_STATS_EMPTY`.
- Error path giữ giá trị output ban đầu.

#### 4.3 CMocka test và default build

```bash
cmake -S assets/s06_case -B /tmp/s06-debug \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build /tmp/s06-debug
ctest --test-dir /tmp/s06-debug --output-on-failure
```

CMake [đăng ký một CTest executable](assets/s06_case/CMakeLists.txt); bên trong executable có bốn `CMUnitTest`. Do đó CTest báo một test target pass, còn CMocka output liệt kê bốn test cases.

#### 4.4 ASan+UBSan build riêng

```bash
cmake -S assets/s06_case -B /tmp/s06-asan \
  -DCMAKE_C_COMPILER=clang-14 \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_C_FLAGS='-O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined -fno-sanitize-recover=all' \
  -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined'
cmake --build /tmp/s06-asan
ASAN_OPTIONS=halt_on_error=1:detect_leaks=1 \
UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
ctest --test-dir /tmp/s06-asan --output-on-failure
```

Pass oracle là exit 0 và stderr không có report thuộc project. Không bật `BUILD_CRASH_FIXTURE` trong gate này.

#### 4.5 Static-analysis gates

```bash
cppcheck \
  --project=/tmp/s06-debug/compile_commands.json \
  --std=c11 \
  --enable=warning,style,performance,portability \
  --error-exitcode=1

clang-tidy-14 \
  -p /tmp/s06-debug \
  assets/s06_case/src/gateway_stats.c \
  --checks='clang-analyzer-*,cert-*'
```

Compiler vẫn dùng C17. `--std=c11` chỉ là setting tương thích parser cppcheck 2.7 theo plan. Với clang-tidy, reviewer phân loại output: finding thuộc check-set blocking phải được sửa hoặc có disposition cụ thể; không dùng blanket suppression.

#### 4.6 Coverage build và denominator

```bash
cmake -S assets/s06_case -B /tmp/s06-coverage \
  -DCMAKE_C_COMPILER=gcc \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_C_FLAGS='-O0 -g --coverage' \
  -DCMAKE_EXE_LINKER_FLAGS='--coverage'
cmake --build /tmp/s06-coverage
ctest --test-dir /tmp/s06-coverage --output-on-failure

lcov --capture \
  --directory /tmp/s06-coverage \
  --output-file /tmp/s06-coverage/raw.info
lcov --remove /tmp/s06-coverage/raw.info \
  '/usr/*' '*/tests/*' '*/_deps/*' '*/generated/*' \
  --output-file /tmp/s06-coverage/production.info
lcov --summary /tmp/s06-coverage/production.info
```

Denominator của case chỉ gồm production source `src/gateway_stats.c`. Header không có executable line; tests/system/generated paths bị loại trước khi so ngưỡng.

### 5. Output mong đợi

GDB output được rút gọn:

```text
Breakpoint 1, legacy_first (values=0x0)
Program received signal SIGSEGV, Segmentation fault.
#0 legacy_first (values=0x0)
#1 main (...)
```

CTest/CMocka output có ý nghĩa tương đương:

```text
[==========] Running 4 test(s).
[  PASSED  ] 4 test(s).
100% tests passed, 0 tests failed out of 1
```

LCOV:

```text
Summary coverage rate:
  lines......: >=80.0%
```

Output static analysis/sanitizer có thể im lặng khi pass; vì vậy evidence phải có command và exit `0`, không chỉ file log rỗng. Package/CLI LCOV fingerprint đều được lưu.

### 6. Cách xác minh

| Gate | Command chính | Pass oracle |
|---|---|---|
| Pre-fix diagnosis | `gdb ... gateway_crash_fixture` | Expected `SIGSEGV`, null state và `legacy_first` frame; non-zero được ghi là diagnostic |
| Functional regression | `ctest --test-dir /tmp/s06-debug --output-on-failure` | 4 CMocka cases pass, 1 CTest target pass |
| Runtime safety | `ctest --test-dir /tmp/s06-asan` | exit 0, không ASan/UBSan finding |
| Cppcheck | `cppcheck --project=... --std=c11 --error-exitcode=1` | exit 0 |
| Clang-tidy | `clang-tidy-14 -p ...` | không blocking finding thiếu disposition |
| Coverage | `lcov --summary .../production.info` | production lines ≥80.0% |
| Tool identity | version commands + `apt-cache policy lcov` | fingerprints khớp/được giải thích |

Nếu cần core dump để luyện post-mortem, chỉ tạo trong workspace cô lập, mở bằng exact binary và xóa/giữ local theo policy; case chuẩn dùng live GDB nên không yêu cầu nộp core.

### 7. Giải thích sâu và failure modes

- **Fixture chạy không crash:** kiểm có vô tình truyền argument hoặc build sai target không; default build cố ý không chứa fixture.
- **GDB line lệch:** executable/debug symbols không cùng build; rebuild triage và ghi fingerprint.
- **Sanitizer fail chỉ trong CMocka runtime:** phân biệt finding thuộc project với dependency, nhưng không suppress rộng; giữ stack và disposition.
- **Output mean đổi trên error:** implementation ghi output trước validation; chuyển commit point sang success path.
- **Coverage 0%:** tests chưa chạy sau instrumented build hoặc LCOV capture sai directory.
- **Coverage cao nhưng thiếu error assertions:** metric không thay oracle; review test vẫn fail.
- **cppcheck parse khác compiler:** giữ `--std=c11` cho cppcheck 2.7, nhưng xác nhận production compile command vẫn `-std=c17`.
- **LCOV báo 1.14:** đối chiếu Jammy package `1.15-1`; đây là fingerprint được biết trước, không đổi package chỉ để chuỗi CLI giống tên package.

Trade-off: mỗi build directory làm gate chậm hơn và tốn storage, đổi lại tránh nhiễm instrumentation/counter và làm evidence tái lập. Debugger cho chiều sâu một execution; tests/analyzers cho breadth khác nhau. Release decision chỉ dựa trên giao của các oracle đã công bố.

### 8. Bài học chuyển giao

1. Luôn tách “điểm crash” khỏi “root cause” và giữ pre-fix evidence.
2. Một fix chỉ hoàn tất khi có regression oracle, không phải khi GDB không còn dừng.
3. Mỗi instrumentation profile cần clean build riêng; ASan+UBSan không ghép TSan.
4. Coverage threshold chỉ có nghĩa khi denominator và exclusions được khóa trước.
5. Report phải version-matched với source snapshot và tool fingerprint.
6. A06 yêu cầu học viên tự triage một change request khác; không nộp lại case QG-06.

## Provenance của các case

### Nguồn được dùng

- GDB manual; GCC 11.4/gcov manuals; Clang 14 sanitizer và clang-tidy documentation.
- Cppcheck 2.7 manual; CMocka 1.1.5 API; LCOV 1.15 release; CERT C.
- Syllabus nội bộ v1.0 cho OUT-S06-01, LO và quality thresholds.

### Phần bổ sung/suy diễn

- **[BỔ SUNG — Ubuntu Jammy environment fingerprint]** Package lcov 1.15-1 có thể in CLI version 1.14; case lưu cả hai trường.
- **[SUY DIỄN — từ tool mechanisms]** Severity blocking, finding disposition và manifest layout là policy đào tạo.
- **[SUY DIỄN — project plan đã được phê duyệt]** Ticket QG-06 và gateway module là bối cảnh mô phỏng.
- Source trong `assets/s06_case` là ví dụ nguyên bản, không sao chép từ CMocka/GDB/LCOV manuals.

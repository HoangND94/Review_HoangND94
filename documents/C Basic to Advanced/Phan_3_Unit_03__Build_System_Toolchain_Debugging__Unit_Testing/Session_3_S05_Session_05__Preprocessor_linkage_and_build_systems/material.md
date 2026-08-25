# Session S05: Session 05 — Preprocessor, linkage and build systems — Học liệu cốt lõi

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 03 — Build System, Toolchain, Debugging & Unit Testing

## 🎯 Learning Outcomes

- **ADVC-H3SD** [evaluate] — Đánh giá và cải thiện build, debug, test, phân tích tĩnh, coverage, profiling và secure-coding của mã C bằng bằng chứng tái lập từ GNU/LLVM toolchain và quy tắc CERT C phù hợp.

## 🧭 Ngữ cảnh nghề nghiệp/dự án và phần tăng trưởng của Unit

**Bối cảnh nghề nghiệp/dự án:** MDB Edge Diagnostics Gateway — Simulated. Học viên đóng vai integration engineer, nhận **Generic gateway core v4** từ Assignment 04 và phải biến mã monolithic thành package có public API ổn định.

**Project increment sau Unit này:** milestone **M05** tạo **Packaged gateway core v5** gồm static library, shared library, demo và báo cáo symbol/build. Artifact này là baseline trực tiếp của ASM-A06.

**Mức xác thực của bối cảnh:** simulated — dữ liệu và gateway đều là tình huống đào tạo, không đại diện cho hệ thống khách hàng thật.

Năng lực mới truy vết tới ADVC-H3SD là khả năng quyết định boundary giữa header/translation unit, chọn static hoặc shared delivery, mô tả build bằng Make/CMake và chứng minh quyết định bằng artifact thực tế thay vì suy đoán từ tên file.

## 📚 Nguồn đầu vào đã map

- [ISO/IEC 9899:2018 metadata](https://www.iso.org/standard/74528.html) và [WG14 N2176](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2176.pdf) — C17, translation unit, linkage, storage duration, inline và preprocessing.
- [GCC 11.4 manuals](https://gcc.gnu.org/onlinedocs/11.4.0/) — strict C17, visibility và compiler/linker options.
- [GNU Make manual](https://www.gnu.org/software/make/manual/make.html) — phạm vi tương thích Make 4.3.
- [CMake 3.22 documentation](https://cmake.org/cmake/help/v3.22/) — target model, `add_library` và visibility properties.
- [GNU Binutils documentation](https://sourceware.org/binutils/docs-2.38/) — `ar`, `nm`, `readelf` 2.38.
- [SEI CERT C Coding Standard](https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/) — macro, linkage và error-handling review rules.
- Syllabus nội bộ v1.0 — phạm vi, thời lượng, LO và acceptance của Session 05.

---

## 1. Kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết

- Hoàn thành S03–S04: opaque ADT, ownership, generic container và flag contract.
- Chạy được regression suite của **Generic gateway core v4**.
- Phân biệt declaration với definition và đọc được warning/link error cơ bản.

### Môi trường, công cụ và phiên bản

- Ubuntu 22.04 native/VM/WSL2; C17; glibc 2.35.
- GCC 11.4, Clang 14.0, GNU Make 4.3, CMake 3.22.1 và GNU Binutils 2.38.
- Mọi lệnh ghi vào build directory dưới workspace; không dùng `sudo`, `make install` hoặc `ldconfig`.

### Phương thức xác minh artifact

Material được review theo source/LO/outline; case tích hợp được build và test bằng asset đi kèm. Kiểm tra môi trường:

```bash
gcc --version | head -1
make --version | head -1
cmake --version | head -1
ar --version | head -1
readelf --version | head -1
```

Kết quả hợp lệ trên baseline là GCC 11.x, Make 4.3, CMake 3.22.x và Binutils 2.38.x. Nếu khác phiên bản, ghi exact fingerprint vào evidence trước khi diễn giải chênh lệch.

## 2. Định vị trong lộ trình (Mental Map)

```text
M04: Generic gateway core v4
        │  quyết định header/TU/linkage và build graph
        ▼
M05: static + shared package + demo + symbol evidence
        │  cung cấp compile database và package baseline
        ▼
M06: GDB/sanitizer/CMocka/static-analysis/coverage quality gate
```

S04 giải quyết representation và generic data structures. S05 không thiết kế lại các cấu trúc đó; S05 quyết định chúng được chia thành module nào, API nào được công khai, artifact nào được link và cách tái lập build. S06 sử dụng chính package/compile database này để tạo quality evidence.

## 3. Nội dung lý thuyết cốt lõi

**Phạm vi nội dung:**

- [x] Advanced preprocessor (variadic macros, X-macros, conditional compilation), translation units, internal/external linkage, storage duration, inline; Make & CMake, static vs shared library, symbol visibility

#### OUT-S05-01 Advanced preprocessor (variadic macros, X-macros, conditional compilation), translation units, internal/external linkage, storage duration, inline; Make & CMake, static vs shared library, symbol visibility

**Mapping:** OUT-S05-01 · ADVC-H3SD · M05 / Packaged gateway core v5.

##### Định nghĩa rõ ràng và ranh giới

- **Preprocessor** biến đổi token trước compilation. C17 cung cấp macro object-like/function-like, `#if`, `#include`, `#`, `##` và variadic parameter `__VA_ARGS__`. Nó không có type checking và macro argument có thể xuất hiện nhiều lần trong replacement list.
- **X-macro** là tên của một idiom: một danh sách `X(name, value)` được include/expand nhiều lần với định nghĩa `X` khác nhau. Đây không phải một feature được chuẩn C đặt tên.
- **Translation unit (TU)** là source file sau preprocessing. Compiler tạo object file theo từng TU; linker mới resolve symbol giữa các object.
- **Linkage** trả lời “hai identifier có chỉ cùng entity không?” File-scope `static` cho internal linkage; declaration `extern` có thể tham chiếu external definition ở TU khác. **Storage duration** trả lời “object tồn tại bao lâu?”; nó không đồng nghĩa với linkage.
- **`inline`** điều chỉnh inline-definition semantics và cho phép compiler cân nhắc thay lời gọi, nhưng không bắt buộc inlining. Với helper trong header, `static inline` tạo một internal definition per TU; public function vẫn nên có một external definition rõ trong `.c`.
- **Make** mô tả dependency graph ở mức file/recipe. **CMake** sinh native build graph theo target và usage requirements; nó không thay compiler/linker.
- **Static library** là archive object được linker lấy vào executable; **shared library** được dynamic loader map khi chạy. **Visibility** giới hạn dynamic symbol table, khác với C `static`: một symbol có external linkage vẫn có thể bị ẩn khỏi dynamic export.

Điểm dễ nhầm: include guard chỉ ngăn cùng header bị include lặp trong một TU; nó không ngăn header định nghĩa external object ở nhiều TU. Tương tự, tạo được file `.so` không chứng minh API export đúng.

##### Vấn đề/vai trò và quyết định cần đưa ra

Integration engineer phải đưa ra sáu quyết định quan sát được:

1. Cấu hình nào là compile-time (`#if`) và cấu hình nào phải là runtime data.
2. Logic nào đủ nhỏ/type-safe để là `static inline`, logic nào cần một external function.
3. Identifier nào chỉ dùng trong một TU và phải là `static`.
4. Public header chứa contract nào, private header/source giữ implementation nào.
5. Consumer cần static, shared hay cả hai; shared ABI có cần version/SOVERSION nào.
6. Build evidence nào chứng minh target, dependency và export surface đúng.

Stakeholder là integration engineer của M06: họ cần package tái lập và compile database; nếu S05 để duplicate definition, accidental export hoặc loader dependency mơ hồ thì quality gate sau không có baseline đáng tin cậy.

##### Cơ chế và mental model

```text
source.c + headers
       │ preprocessing: macro/#if/#include
       ▼
translation unit
       │ compile
       ▼
object.o ── ar ──> libgateway_core.a
       │
       └── shared link (-fPIC, SONAME, visibility) ──> libgateway_core.so
                                  │
application.o ────────────────────┴── link/load ──> process
```

- Preprocessor quyết định token nào tới compiler; nhánh không active không được type-check như code active.
- Compiler chỉ biết declaration trong TU hiện tại. Một header có `int counter;` tạo tentative definition tại mỗi TU và sẽ fail với modern `-fno-common`; header đúng là `extern int counter;`, còn đúng một `.c` định nghĩa object.
- Linker resolve undefined symbols, chọn archive members khi cần và tạo dynamic symbol/dependency metadata cho shared output.
- CMake `PUBLIC/PRIVATE/INTERFACE` mô tả propagation. `target_include_directories(gateway_shared PUBLIC ...)` truyền include path cho consumer; warning flags thường là `PRIVATE` để không áp đặt policy nội bộ lên consumer.
- `C_VISIBILITY_PRESET hidden` làm external symbols bị ẩn mặc định; public declarations được đánh dấu default visibility. `readelf -Ws` hoặc `nm -D --defined-only` là oracle.

Trong asset của case, `gateway_events.def` cố ý không có include guard vì được expand hai lần: một lần tạo enum và một lần tạo switch. Sau mỗi pass, `X` được `#undef`.

##### Khi dùng / khi không dùng, giới hạn và trade-off

- Dùng variadic macro cho logging/assert wrapper thật sự cần số argument biến đổi và replacement đơn giản. Không dùng để thay một typed API có thể viết bằng function; C17 không có `__VA_OPT__`, còn comma-swallowing `##__VA_ARGS__` là extension, không phải portable C17.
- Dùng X-macro khi một danh sách nhỏ phải sinh nhiều view đồng bộ (enum/string/table). Không dùng khi dữ liệu cần thay đổi lúc chạy hoặc code generation rõ ràng hơn.
- Dùng `#if` cho platform/feature build đã được test ở mọi configuration quan trọng. Không dùng thay runtime policy.
- Dùng static library cho self-contained deployment và khi duplicate code/upgrade coupling chấp nhận được. Dùng shared library khi nhiều process chia sẻ implementation hoặc cần cập nhật độc lập, đổi lại phải quản lý ABI, loader path và version.
- Dùng `static inline` cho header helper nhỏ, không có mutable file-state và semantics rõ. Không dùng như cách che một public implementation lớn.
- Makefile trực tiếp phù hợp project nhỏ hoặc học dependency mechanics. CMake phù hợp nhiều target/toolchain/test; vẫn cần hiểu command compiler/linker mà nó sinh.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** integration engineer đóng gói một API tính gain và event-name cho gateway.
- **Input/baseline/constraint:** một public header, một implementation, ba event; strict C17; CMake 3.22; shared library chỉ export ba hàm public.
- **Decision/action:** dùng X-list làm nguồn event duy nhất, file-local `static` cho clamp helper, hai CMake targets biên dịch cùng source với visibility policy khác nhau, demo link shared bằng build RPATH.
- **Artifact/output:** [CMake project của case](assets/s05_case/CMakeLists.txt), [public header](assets/s05_case/include/gateway.h), [implementation](assets/s05_case/src/gateway.c), [Makefile](assets/s05_case/Makefile).
- **Expected result:** demo in `gateway 5.0.0` và `event=GATEWAY_EVENT_WARN result=12`; hai CTest pass; dynamic table chỉ có ba `gateway_*` API thuộc project.
- **Verification/oracle/evidence:** clean build log, CTest summary, `ar t`, `nm`, `readelf` và demo output. Các lệnh đầy đủ nằm ở mục 4 và [example.md](example.md).

##### Ví dụ code cụ thể

Micro-example này tách khỏi Assignment 05 và dùng một status catalog synthetic. Một X-list sinh enum lẫn `switch`; `normalize_code` có internal linkage, còn shared library chỉ công bố `status_name`. CMake tạo cả static/shared library từ cùng source và đặt visibility theo target.

Tạo thư mục scratch `/tmp/s05_micro`. File `status.def` **cố ý không có include guard** vì được expand nhiều lần:

```c
X(STATUS_OK, 0, "OK")
X(STATUS_BUSY, 1, "BUSY")
X(STATUS_ERROR, 2, "ERROR")
```

`status.h`:

```c
#ifndef STATUS_H
#define STATUS_H

#if defined(__GNUC__)
#define STATUS_API __attribute__((visibility("default")))
#else
#define STATUS_API
#endif

#define X(symbol, value, text) symbol = value,
enum status_code {
#include "status.def"
};
#undef X

STATUS_API const char *status_name(enum status_code code);

static inline int status_is_error(enum status_code code)
{
    return code == STATUS_ERROR;
}

#endif
```

`status.c`:

```c
#include "status.h"
#include <stdio.h>

#ifndef STATUS_TRACE
#define STATUS_TRACE 0
#endif

#if STATUS_TRACE
#define TRACE(...) fprintf(stderr, __VA_ARGS__)
#else
#define TRACE(...) ((void)0)
#endif

static int normalize_code(int code)
{
    return (code >= STATUS_OK && code <= STATUS_ERROR) ? code : STATUS_ERROR;
}

const char *status_name(enum status_code code)
{
    const int normalized = normalize_code((int)code);
    TRACE("normalized=%d\n", normalized);
    switch ((enum status_code)normalized) {
#define X(symbol, value, text) case symbol: return text;
#include "status.def"
#undef X
    default:
        return "ERROR";
    }
}
```

`main.c`:

```c
#include "status.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    const enum status_code code = STATUS_BUSY;
    const char *name = status_name(code);
    const int is_error = status_is_error(code);
    printf("code=%d name=%s error=%d\n", (int)code, name, is_error);
    return (strcmp(name, "BUSY") == 0 && is_error == 0) ? 0 : 1;
}
```

`CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.22)
project(s05_micro C)

option(STATUS_TRACE "Enable local status trace" OFF)
set(STATUS_SOURCES status.c)

add_library(status_static STATIC ${STATUS_SOURCES})
add_library(status_shared SHARED ${STATUS_SOURCES})
set_target_properties(status_static status_shared PROPERTIES OUTPUT_NAME status)

foreach(target status_static status_shared)
  target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_compile_definitions(${target} PRIVATE
    STATUS_TRACE=$<BOOL:${STATUS_TRACE}>)
  set_target_properties(${target} PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO
    C_VISIBILITY_PRESET hidden)
  target_compile_options(${target} PRIVATE
    -Wall -Wextra -Wpedantic -Werror)
endforeach()

add_executable(status_demo main.c)
target_link_libraries(status_demo PRIVATE status_shared)
set_target_properties(status_demo PROPERTIES
  C_STANDARD 17
  C_STANDARD_REQUIRED YES
  C_EXTENSIONS NO)
target_compile_options(status_demo PRIVATE
  -Wall -Wextra -Wpedantic -Werror)

enable_testing()
add_test(NAME status_demo COMMAND status_demo)
```

Configure, build và kiểm artifact:

```bash
cmake -S /tmp/s05_micro -B /tmp/s05_micro/build -DSTATUS_TRACE=OFF
cmake --build /tmp/s05_micro/build
ctest --test-dir /tmp/s05_micro/build --output-on-failure
/tmp/s05_micro/build/status_demo
nm -D --defined-only /tmp/s05_micro/build/libstatus.so | awk '{print $3}'
ar t /tmp/s05_micro/build/libstatus.a
gcc -E -P -I/tmp/s05_micro /tmp/s05_micro/status.c | \
  grep -c 'case STATUS_'
```

Kết quả quan sát được; toàn bộ command phải exit `0`:

```text
1/1 Test #1: status_demo ... Passed
code=1 name=BUSY error=0
status_name
status.c.o
3
```

- **Quyết định:** X-list là nguồn duy nhất cho ba status; variadic `TRACE` chỉ tồn tại khi feature flag build bật; helper normalize là `static`; `static inline` nhỏ ở header không tạo external definition; CMake flags/visibility thuộc đúng target.
- **Oracle/evidence:** CTest và stdout chứng minh behavior; preprocessed output phải có đúng ba `case`; archive phải chứa object; dynamic symbol allow-list chỉ có `status_name`. Tên `.a/.so` một mình không đủ làm oracle.
- **Giới hạn/trade-off:** `STATUS_API` là GCC/Clang visibility scope của environment đã pin. Nếu bỏ `static`, `nm` có thể lộ helper; nếu thêm include guard vào `status.def`, pass expansion sau biến mất và compile/test fail.

##### Best practices

| Rule | Rationale/cơ chế | Ví dụ đúng | Phản ví dụ/hậu quả |
|---|---|---|---|
| Public header chỉ declaration/type/macro contract; đúng một external definition trong source. | Mỗi TU compile độc lập; definition trong header tạo multiple-definition hoặc state per TU ngoài ý muốn. | `extern int gateway_mode;` trong header, `int gateway_mode;` ở một `.c`. | `int gateway_mode;` trong header làm link fail hoặc phụ thuộc legacy common-symbol behavior. |
| File-private function/object dùng `static`; public export được allow-list. | Internal linkage và hidden visibility thu nhỏ collision/ABI surface. | `static int32_t clamp_i64_to_i32(...)`; public declaration có export attribute. | Helper external mặc định xuất hiện trong `.dynsym`, trở thành accidental ABI. |
| Macro parenthesize expression, không nhận argument có side effect nếu replacement có thể evaluate nhiều lần; ưu tiên `static inline`. | Preprocessing thay token, không giữ single-evaluation/type contract. | `static inline int min_i32(int a, int b)`. | `MIN(i++, limit)` có thể tăng `i` hai lần. |
| CMake policy đặt trên target, explicit `C_STANDARD 17`, `C_EXTENSIONS NO`. | Usage requirements và build graph có scope rõ. | `target_compile_options(gateway_shared PRIVATE ...)`. | `set(CMAKE_C_FLAGS ...)` âm thầm ảnh hưởng third-party/consumer targets. |
| Kiểm artifact bằng tool, không suy luận từ suffix. | Tên `.a/.so` không chứng minh member, dependency hay export. | Lưu `ar t`, `nm -g`, `readelf -Ws/-d`. | Chỉ chụp thư mục build nên accidental export/SONAME sai không bị phát hiện. |

##### Anti-pattern, failure modes và troubleshooting

| Dấu hiệu | Nguyên nhân thường gặp | Chẩn đoán/bằng chứng | Khắc phục | Phòng tránh |
|---|---|---|---|---|
| `multiple definition of ...` | External object/function body nằm trong header. | `nm` từng object và linker diagnostic. | Chuyển definition vào một `.c`; header giữ `extern`/prototype. | Header review + build ít nhất hai TU. |
| Shared demo báo “cannot open shared object file” | Không có RPATH hoặc scoped loader path. | `readelf -d demo`, `ldd demo`. | Dùng build RPATH hoặc scoped `LD_LIBRARY_PATH` cho đúng command. | Không cài global; test từ clean build tree. |
| Public function không xuất hiện trong `.dynsym` | Hidden mặc định nhưng thiếu default-visibility annotation. | `nm -D --defined-only lib...so`. | Đánh dấu public declaration và compile shared target với export definition. | Export macro + symbol contract test. |
| X-list sinh duplicate case/enum | Entry trùng hoặc quên `#undef X`. | Xem preprocessed output bằng `gcc -E`. | Sửa authoritative list, `#undef` sau mỗi pass. | List nhỏ, review uniqueness, compile with warnings-as-errors. |
| Thay header nhưng object không rebuild trong Make | Dependency header không được theo dõi. | `make --debug` hoặc timestamp/object diff. | Dùng `-MMD -MP` và include `.d`. | Generated dependencies như Makefile asset. |

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### Input/trạng thái ban đầu

Thư mục [assets/s05_case](assets/s05_case/CMakeLists.txt) chứa một API C17, X-list ba event, demo và test. Không cần dependency ngoài GCC/Make/CMake/Binutils baseline.

### Cách thực hiện

CMake tạo hai libraries cùng output basename nhưng khác loại; shared target bật hidden visibility và export annotation. Demo link shared target. Makefile độc lập tạo static archive để đối chiếu file dependency mechanics.

### Output mong đợi

```text
gateway 5.0.0
event=GATEWAY_EVENT_WARN result=12
100% tests passed, 0 tests failed out of 2
```

`ar t` liệt kê object của implementation. `nm -D --defined-only` trên shared object có `gateway_apply_gain`, `gateway_event_name`, `gateway_version`; không có `clamp_i64_to_i32`.

### Cách xác minh

```bash
cmake -S assets/s05_case -B assets/s05_case/build/debug \
  -DCMAKE_BUILD_TYPE=Debug
cmake --build assets/s05_case/build/debug --parallel
ctest --test-dir assets/s05_case/build/debug --output-on-failure
assets/s05_case/build/debug/apps/gateway_demo
ar t assets/s05_case/build/debug/lib/libgateway_core.a
nm -D --defined-only assets/s05_case/build/debug/lib/libgateway_core.so
readelf -d assets/s05_case/build/debug/apps/gateway_demo
make -C assets/s05_case clean all test
```

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

- Nếu CMake thấp hơn 3.22, dừng và dùng đúng Ubuntu 22.04 baseline; không hạ `cmake_minimum_required` để bỏ qua contract.
- Nếu `readelf` thấy internal helper, kiểm cả C linkage (`static`) và ELF visibility; đây là hai lớp khác nhau.
- Nếu static test pass nhưng shared test fail, so sánh target compile definitions, exported symbols và loader metadata; không sửa bằng cách export toàn bộ.
- Nếu strict C17 báo extension ở variadic macro, loại compiler extension hoặc công bố configuration riêng; portable path không dùng `__VA_OPT__`/comma-swallow extension.
- Quy tắc review áp dụng: PRE00-C/PRE31-C cho macro, DCL15-C cho file-scope identifier không cần external linkage, ERR33-C cho return code của tool/API.

## 6. Từ điển thuật ngữ và mô hình tư duy

- **Translation unit:** source sau preprocessing, đơn vị compiler xử lý.
- **Declaration/definition:** declaration giới thiệu contract; definition cấp body/storage.
- **Internal/external linkage:** phạm vi identity của entity qua TU.
- **Storage duration:** khoảng thời gian object tồn tại; độc lập với visibility.
- **Archive:** tập object trong static library, được linker lấy theo nhu cầu.
- **SONAME:** identity/version contract mà dynamic loader ghi nhận cho shared library.
- **Visibility:** việc symbol có xuất hiện cho dynamic linkage hay không.
- **Usage requirement:** property CMake truyền từ target sang consumer theo PUBLIC/PRIVATE/INTERFACE.
- **Oracle:** phép đo pass/fail trên artifact thật, ví dụ symbol table hoặc CTest result.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

Các nguồn ở mục “Nguồn đầu vào đã map” được dùng ở chế độ reference/paraphrase; không sao chép implementation hoặc đoạn chuẩn dài. Phiên bản thực thi: GCC 11.4, Make 4.3, CMake 3.22.1 và Binutils 2.38.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — từ cơ chế macro C17 đã map]** Tên và quy ước tổ chức “X-macro” là idiom cộng đồng; asset chỉ suy ra từ khả năng redefine/include macro, không tuyên bố đây là feature có tên trong ISO C.
- **[SUY DIỄN — được user phê duyệt trong project plan]** Gateway, stakeholder và chuỗi artifact M04→M05→M06 là project spine mô phỏng.
- **[BỔ SUNG — nguồn: CMake 3.22 và GNU Binutils 2.38]** Build RPATH và symbol-inspection commands chỉ phục vụ case local, không thay đổi loader toàn hệ thống.

---

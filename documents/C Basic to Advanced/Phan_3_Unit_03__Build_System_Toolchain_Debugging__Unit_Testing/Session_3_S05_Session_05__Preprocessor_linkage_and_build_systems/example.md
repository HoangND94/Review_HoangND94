# Session S05: Session 05 — Preprocessor, linkage and build systems — Ví dụ và nghiên cứu tình huống

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 03 — Build System, Toolchain, Debugging & Unit Testing

## 🎯 Learning Outcomes liên quan

- **ADVC-H3SD** — Đánh giá package/build decision bằng clean build, regression và symbol/dependency evidence.

## 🧭 Liên kết với ngữ cảnh nghề nghiệp/dự án

**Bối cảnh nghề nghiệp/dự án:** integration engineer cần một lát cắt nhỏ, chạy được của gateway để thử package contract trước khi áp dụng cho toàn bộ Generic gateway core v4.

**Project increment được minh họa:** M05 — một source API được cung cấp đồng thời dưới dạng static/shared library, một demo shared-link và hai contract tests.

## 🧰 Điều kiện chạy ví dụ

**Kiến thức/kỹ năng tiên quyết:** declaration/definition, header guard, file-scope `static`, command-line build cơ bản và S04 regression mindset.

**Môi trường, công cụ và phiên bản:** Ubuntu 22.04; GCC 11.4; GNU Make 4.3; CMake 3.22.1; Binutils 2.38. Clang 14 có thể thay GCC cho build đối chiếu.

**Phương thức xác minh artifact:** executable — clean configure/build, CTest, demo output và symbol/dependency inspection.

## 📚 Nguồn đầu vào đã map

- [C17/WG14 N2176](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2176.pdf)
- [GCC 11.4](https://gcc.gnu.org/onlinedocs/11.4.0/)
- [GNU Make](https://www.gnu.org/software/make/manual/make.html)
- [CMake 3.22](https://cmake.org/cmake/help/v3.22/)
- [GNU Binutils 2.38](https://sourceware.org/binutils/docs-2.38/)
- [SEI CERT C](https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/)

---

### Mapping case đã chốt trong course plan

- **CASE-S05-01** → **OUT-S05-01** → **ADVC-H3SD** → M05.
- **Mức xác thực:** inherit từ project, tức simulated.

## Case Study 01: Ticket PKG-05 — Đóng gói API event/gain với export surface tối thiểu

### 1. Ticket và tiêu chí thành công

- **Vai trò/stakeholder:** integration engineer bàn giao package cho đội quality.
- **Vấn đề cần giải quyết:** cùng một implementation phải tạo static/shared variants; demo không cần cài library vào hệ thống; shared object không được export helper nội bộ.
- **Learning Outcome và outline item:** ADVC-H3SD; OUT-S05-01.
- **Project increment/professional artifact liên quan:** một proof slice cho Packaged gateway core v5.
- **Tiêu chí thành công:**
  1. CMake 3.22 clean build tạo `libgateway_core.a`, `libgateway_core.so` và `gateway_demo`.
  2. Static/shared API tests cùng pass.
  3. Demo in đúng version/event/result và chạy bằng build RPATH.
  4. Dynamic symbol table chỉ chứa ba public `gateway_*` functions của project.
  5. GNU Make 4.3 path tạo static archive và demo độc lập.

### 2. Input, trạng thái ban đầu và ràng buộc

Cây source hoàn chỉnh:

```text
assets/s05_case/
├── CMakeLists.txt
├── Makefile
├── include/
│   ├── gateway.h
│   └── gateway_events.def
├── src/gateway.c
├── apps/demo.c
└── tests/test_api.c
```

- Authoritative event list có INFO=1, WARN=2, ERROR=3.
- Public API gồm `gateway_version`, `gateway_event_name`, `gateway_apply_gain`.
- Strict C17, `-Wall -Wextra -Wpedantic -Werror`.
- Không `sudo`, không install, không global loader mutation.
- X-list chỉ là compile-time source of truth; runtime không sửa danh sách.

### 3. Phân tích lựa chọn

**Phương án một static library duy nhất** đơn giản nhưng không kiểm được dynamic export/loader contract. **Phương án shared-only** không chứng minh archive delivery. Case chọn hai target biên dịch cùng source vì mục tiêu là so sánh delivery mode.

Mặc định hidden visibility giảm accidental ABI. Public header dùng một export macro chỉ active khi biên dịch shared target; static target không phụ thuộc ELF export attribute. Helper clamp vừa không thuộc public contract vừa chỉ dùng trong một TU, nên dùng C `static`.

Event enum và event-name switch dễ lệch nếu duy trì hai danh sách. X-list giảm duplication, đổi lại người bảo trì phải hiểu multiple inclusion và luôn `#undef X`. Với dữ liệu runtime hoặc list lớn, code generation/data table sẽ dễ đọc hơn.

CMake là path chính vì cần target graph, test và RPATH. Makefile được giữ như artifact đối chiếu dependency mechanics; nó không cố tái tạo shared/package policy đầy đủ.

### 4. Cách triển khai

Lời giải hoàn chỉnh nằm trong [assets/s05_case](assets/s05_case/CMakeLists.txt).

**Một danh sách, hai expansion:**

```c
enum gateway_event {
#define X(name, value) name = value,
#include "gateway_events.def"
#undef X
};

switch (event) {
#define X(name, value) case name: return #name;
#include "gateway_events.def"
#undef X
default:
    return "GATEWAY_EVENT_UNKNOWN";
}
```

File `gateway_events.def` không có include guard vì việc include lặp là chủ ý. Mỗi replacement dùng argument thuần, không side effect.

**Public/shared boundary:**

```c
#if defined(GATEWAY_BUILD_SHARED) && (defined(__GNUC__) || defined(__clang__))
#define GATEWAY_API __attribute__((visibility("default")))
#else
#define GATEWAY_API
#endif

GATEWAY_API const char *gateway_version(void);
```

Shared target nhận `GATEWAY_BUILD_SHARED` và `C_VISIBILITY_PRESET hidden`; helper trong implementation là `static`.

**Target-scoped CMake:**

```cmake
add_library(gateway_static STATIC src/gateway.c)
add_library(gateway_shared SHARED src/gateway.c)
target_compile_definitions(gateway_shared PRIVATE GATEWAY_BUILD_SHARED)
set_target_properties(gateway_shared PROPERTIES
  C_VISIBILITY_PRESET hidden
  VERSION 5.0.0
  SOVERSION 5)
```

Cả target đặt C17 và warnings trên chính target. Demo link `gateway_shared` và dùng `$ORIGIN/../lib` chỉ trong build tree.

### 5. Output mong đợi

Demo:

```text
gateway 5.0.0
event=GATEWAY_EVENT_WARN result=12
```

CTest:

```text
100% tests passed, 0 tests failed out of 2
```

`ar t` phải có object implementation. Địa chỉ trong `nm` thay đổi theo build, nhưng tên dynamic project symbols phải gồm:

```text
gateway_apply_gain
gateway_event_name
gateway_version
```

Không được có `clamp_i64_to_i32` trong dynamic exports.

### 6. Cách xác minh

Chạy từ thư mục Session S05:

```bash
cmake -S assets/s05_case -B assets/s05_case/build/debug \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build assets/s05_case/build/debug --parallel
ctest --test-dir assets/s05_case/build/debug --output-on-failure
assets/s05_case/build/debug/apps/gateway_demo

ar t assets/s05_case/build/debug/lib/libgateway_core.a
nm -D --defined-only assets/s05_case/build/debug/lib/libgateway_core.so
readelf -Ws assets/s05_case/build/debug/lib/libgateway_core.so
readelf -d assets/s05_case/build/debug/apps/gateway_demo

make -C assets/s05_case clean all test
```

Pass khi mọi command exit 0, hai tests pass, demo đúng hai dòng contract, shared project exports đúng allow-list và `readelf -d` cho thấy build-tree runtime/dependency hợp lệ. Không coi địa chỉ symbol hoặc thứ tự ngoài allow-list là golden output.

### 7. Giải thích sâu và failure modes

- Nếu demo build nhưng không chạy, đọc `readelf -d` trước. Thiếu RPATH là loader configuration issue, không phải API error; không “sửa” bằng `ldconfig`.
- Nếu `gateway_version` không export, kiểm `GATEWAY_BUILD_SHARED` có gắn đúng target và declaration mang default visibility.
- Nếu helper export, kiểm nó có external linkage hoặc bị đánh dấu default visibility. Cần sửa boundary, không dùng post-link symbol stripping để che lỗi source.
- Nếu enum/string lệch, xem preprocessed output `gcc -E` và xác nhận `X` được redefine/undef đúng.
- Nếu sửa header mà Make không rebuild, kiểm `-MMD -MP` và file `.d` đã được include.
- Shared library cho phép thay implementation độc lập nhưng tạo ABI/loader obligation; static library tránh runtime dependency nhưng code được copy vào consumer và update cần relink.

### 8. Bài học chuyển giao

- Build “thành công” chưa đủ; package contract cần behavior + symbol + dependency evidence.
- `static` của C và hidden visibility của ELF giải quyết hai tầng khác nhau.
- Target-scoped CMake giúp biết property nào thuộc library, property nào truyền sang consumer.
- Trong ASM-A05, học viên áp dụng nguyên tắc này cho **Generic gateway core v4** lớn hơn và change request khác; case không cung cấp module split hay export allow-list của bài Assignment.

---

## Provenance của các case

### Nguồn được dùng

Case dùng semantics C17/WG14, GCC 11.4, GNU Make 4.3, CMake 3.22 và Binutils 2.38 theo các nguồn đã map. Code asset là implementation đào tạo nguyên bản, không sao chép code của Linux kernel hoặc manual.

### Phần bổ sung/suy diễn

- **CASE-S05-01 — [SUY DIỄN từ preprocessing semantics C17]:** X-list là idiom tổ chức source, không phải feature chuẩn có tên “X-macro”.
- **CASE-S05-01 — [SUY DIỄN được phê duyệt trong plan]:** ticket PKG-05 và gateway package là scenario mô phỏng.
- **CASE-S05-01 — [BỔ SUNG từ CMake/Binutils docs]:** build RPATH và symbol allow-list là oracle local cho case, không tạo yêu cầu cài hệ thống.


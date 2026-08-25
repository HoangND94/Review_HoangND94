# Session S01: Session 01 — Kick-off and advanced pointers — Học liệu cốt lõi

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 01 — Advanced Pointers & Memory Management

## 🎯 Learning Outcomes
- **ADVC-H1SD** [create] — Thiết kế, hiện thực và kiểm chứng các mô-đun C17 dùng con trỏ nâng cao, quản lý bộ nhớ động, ADT đóng gói và cấu trúc dữ liệu generic mà không làm lộ ownership hoặc gây lỗi bộ nhớ trong các ca kiểm thử đã cho. · Bằng chứng: Public API/header và implementation C biên dịch với warning profile đã chốt; unit tests đạt; sanitizer hoặc Valgrind không báo lỗi thuộc phạm vi fixture.

## 🧭 Ngữ cảnh nghề nghiệp/dự án và phần tăng trưởng của Unit

**Bối cảnh nghề nghiệp/dự án:**
**MDB Edge Diagnostics Gateway — Simulated** — Cổng chẩn đoán và telemetry chạy local trên Linux cho thiết bị giả lập; tiếp nhận command, quản lý work records, thực thi backend process/thread và phục vụ protocol TCP loopback. Vai trò học viên: C systems developer chịu trách nhiệm phát triển và harden từng increment trong repository đào tạo. Mục tiêu: Bàn giao một gateway TCP loopback tích hợp core C17, process/thread backends và quality evidence; phục vụ ít nhất 100 client synthetic theo Assignment 09 mà không có finding mức chặn trong oracle áp dụng.

**Project increment sau Unit này:**
- **milestone_id:** M01
- **user_story:** Là system maintainer, tôi muốn command được định tuyến qua callback contract để có thể mở rộng gateway mà không dùng chuỗi if/else khó kiểm chứng.
- **business_value:** Tạo extension point đầu tiên và quality baseline tối thiểu cho repository.
- **baseline:** Project repository skeleton, synthetic fixtures và public contract pack.
- **change_scope:** - Environment evidence<br>- Function-pointer typedef<br>- Dispatcher registry<br>- Generic sort/search adapters<br>- Pointer-safety tests
- **inputs:** - DC-COMMAND<br>- Project repository skeleton<br>- Synthetic command and telemetry fixtures<br>- Public contract pack
- **integration_points:** - command dispatcher<br>- evidence manifest
- **artifacts_added:** - Dispatcher module v1<br>- A01 tests and evidence
- **acceptance_criteria:** - FR-01 đạt<br>- NFR-02 đạt<br>- Pointer misuse fixtures có oracle
- **definition_of_done:** - Project Definition of Done áp dụng cho M01

**Mức xác thực của bối cảnh:** simulated

Sau session, học viên có một baseline môi trường tái lập được và đủ năng lực thiết kế `Dispatcher module v1`: callback có kiểu chính xác, `context` có lifetime rõ, generic algorithm có hợp đồng `count/size`, cùng test cho nhánh thành công và nhánh lỗi. Increment M01 này là đầu vào bắt buộc của ASM-A02; toàn bộ dữ liệu command là synthetic, không phải dữ liệu thiết bị thật.

## 📚 Nguồn đầu vào đã map
- SRC-SYL — L2_MBD_ADVC_Syllabus_v1.0 1.xlsx: D:\Workspaces\FR_DN26_MBD_Simulink\L2_MBD_ADVC_Syllabus_v1.0 1.xlsx (publisher: Internal training syllabus; version: 1.0; accessed_at: 2026-08-21; license: internal_approved for this requested training-content generation; allowed_use: internal_approved)
- SRC-UBUNTU22 — Ubuntu 22.04 LTS package index: https://packages.ubuntu.com/jammy/ (publisher: Canonical / Ubuntu; version: Jammy 22.04 package baseline; accessed_at: 2026-08-21; license: Canonical site and package metadata terms; reference only; allowed_use: reference)
- SRC-C17-ISO — ISO/IEC 9899:2018 — Programming languages — C: https://www.iso.org/standard/74528.html (publisher: ISO/IEC JTC 1/SC 22; version: Edition 4, C17, 2018; accessed_at: 2026-08-21; license: ISO copyright; metadata and clause references only, no reproduction; allowed_use: reference)
- SRC-C17-WG14 — WG14 N2176 proposed C17 committee draft: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2176.pdf (publisher: ISO/IEC JTC 1/SC 22/WG14; version: N2176, 2017-10-09; non-final public committee document; accessed_at: 2026-08-21; license: Publicly accessible committee document; link and paraphrase only; allowed_use: reference)
- SRC-GCC11 — GCC 11.4 manuals: https://gcc.gnu.org/onlinedocs/gcc-11.4.0/ (publisher: GNU Project / Free Software Foundation; version: 11.4.0; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-GNUC — GNU C Language Manual: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/index.html (publisher: GNU Project / Free Software Foundation; version: rolling manual as accessed; C17 scope constrained by plan; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-CERTC — SEI CERT C Coding Standard: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/ (publisher: Carnegie Mellon University Software Engineering Institute; version: online work-in-progress snapshot as accessed; claims constrained to C17; accessed_at: 2026-08-21; license: CMU/SEI terms; reference and limited quotation only; allowed_use: reference)
- SRC-LLVM14 — LLVM/Clang 14.0.0 Documentation: https://releases.llvm.org/14.0.0/tools/clang/docs/index.html (publisher: LLVM Project; version: 14.0.0; accessed_at: 2026-08-21; license: Apache-2.0 WITH LLVM-exception; allowed_use: reference)
- SRC-VALGRIND318 — Valgrind Memcheck Manual: https://valgrind.org/docs/manual/mc-manual.html (publisher: Valgrind Developers; version: 3.18.1 Ubuntu baseline; options constrained to that release; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.2 or later; allowed_use: reference)

> Đây là khu vực provenance. Khi viết nội dung, tiêu hóa thông tin từ nguồn và trình bày độc lập; không chèn tên file nguồn vào câu văn kỹ thuật. Nguồn bổ sung hoặc phần suy diễn phải được ghi riêng tại mục 7.

---

## 1. Kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết
- **knowledge:** - C cơ bản: data types, control flow, functions, arrays, basic pointers và file I/O
- **skills:** - Biên dịch và chạy một chương trình C đơn giản
- **completed_units:** _(Không có / chưa áp dụng)_
- **assets:** - starter/assignment-01/README.md

### Môi trường, công cụ và phiên bản
- **profile_ref:** ENV-ADV-C-JAMMY
- **description:** Môi trường local cô lập cho C17/Linux system programming; Ubuntu 22.04 native, VM hoặc WSL2.
- **operating_system:** Ubuntu 22.04 LTS (Jammy), native/VM/WSL2; network tests bind loopback only
- **runtimes:** - - **name:** C language mode<br>- **version:** C17<br>- - **name:** glibc<br>- **version:** 2.35
- **tools:** - - **name:** GCC<br>- **version:** 11.4 baseline<br>- - **name:** Clang<br>- **version:** 14.0 baseline<br>- - **name:** GNU Make<br>- **version:** 4.3<br>- - **name:** CMake<br>- **version:** 3.22.1<br>- - **name:** GNU Binutils<br>- **version:** 2.38<br>- - **name:** GDB<br>- **version:** 12.1<br>- - **name:** Valgrind<br>- **version:** 3.18.1<br>- - **name:** cppcheck<br>- **version:** 2.7<br>- - **name:** clang-tidy<br>- **version:** 14.0<br>- - **name:** CMocka<br>- **version:** 1.1.5<br>- - **name:** gcov<br>- **version:** 11.4<br>- - **name:** LCOV package<br>- **version:** Ubuntu Jammy 1.15-1; bundled lcov --version reports 1.14<br>- - **name:** perf<br>- **version:** Linux 5.15 toolset<br>- - **name:** Git<br>- **version:** 2.34+
- **services:** _(Không có / chưa áp dụng)_
- **overrides:** _(Không có / chưa áp dụng)_

### Phương thức xác minh artifact
artifact_review

Chạy lần lượt `gcc --version`, `cmake --version`, `gdb --version` và `valgrind --version`; lưu dòng phiên bản đầu tiên vào evidence manifest. Sau đó biên dịch [environment_smoke.c](assets/environment_smoke.c) bằng `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror assets/environment_smoke.c -o /tmp/advc_env_smoke` và chạy `/tmp/advc_env_smoke`. Baseline đạt khi biên dịch exit `0`, không có warning và stdout đúng `ENV_SMOKE PASS`.

## 2. Định vị trong lộ trình (Mental Map)

S01 nâng con trỏ cơ bản thành **contract ở biên mô-đun**. Môi trường cố định làm cho warning và sanitizer trở thành bằng chứng lặp lại được; typed callback tách định tuyến command khỏi handler; `void *` cho phép adapter generic nhưng chỉ an toàn khi đi cùng kích thước, số phần tử và lifetime. M01 tạo dispatcher v1; S02 sẽ thay cách cấp phát record mà không đổi hành vi dispatcher, còn S03 sẽ giấu representation sau opaque handle.

## 3. Nội dung lý thuyết cốt lõi

**Phạm vi nội dung:**
- [x] Course Kick-off: objectives, MDB project context, learning method, environment & toolchain setup (Ubuntu/WSL2, GCC, CMake, GDB, Valgrind)
- [x] Pointer deep-dive: pointer-to-pointer, pointer arithmetic & const-correctness, function pointers, callback / dispatch table, void* generic API, common pointer pitfalls

Hai leaf dưới đây giữ nguyên văn, đúng thứ tự syllabus và cùng truy vết tới ADVC-H1SD/M01; mỗi leaf có contract và oracle riêng.


#### OUT-S01-01 Course Kick-off: objectives, MDB project context, learning method, environment & toolchain setup (Ubuntu/WSL2, GCC, CMake, GDB, Valgrind)

**Mapping:** OUT-S01-01 · ADVC-H1SD · M01 — baseline môi trường và evidence manifest cho Dispatcher module v1.

##### Định nghĩa rõ ràng
Kick-off là lúc khóa **mục tiêu, phạm vi và oracle**, không chỉ giới thiệu lịch học. Khóa dùng C17 trên Ubuntu 22.04 native/VM/WSL2; GCC biên dịch và cảnh báo, CMake tạo build tree, GDB quan sát trạng thái khi chương trình dừng, Valgrind Memcheck phát hiện truy cập/cấp phát sai trên binary debug không gắn ASan. Dự án MDB chỉ là mô phỏng local với fixture synthetic; không có endpoint, credential hay dữ liệu khách hàng.

##### Vấn đề/vai trò và quyết định cần đưa ra
Maintainer và reviewer cần tái lập cùng một lỗi từ cùng source. Học viên phải quyết định profile môi trường nào là baseline, lệnh clean build nào là chuẩn, bằng chứng nào chứng minh build/test đạt và công cụ nào trả lời câu hỏi nào. Quyết định được ghi thành version manifest và command log, không dựa vào câu “máy em chạy được”.

##### Cơ chế và mental model
Luồng xác minh là `source → compiler/warnings → linker → executable → test → debugger hoặc memory checker → evidence`. Warning là lỗi ở quality gate vì `-Werror`; GDB giúp kiểm tra control/data state nhưng không tự chứng minh chương trình không có UB; Memcheck theo dõi truy cập và heap trong lần chạy cụ thể. CMake chỉ điều phối lệnh build ở M01, chưa phải nội dung đánh giá về build system.

##### Khi dùng / khi không dùng
Dùng baseline này cho mọi artifact có thể thực thi trong khóa. Một Linux khác vẫn có thể dùng để học nếu fingerprint được ghi và sai khác được nêu, nhưng không dùng kết quả đó để khẳng định đã đạt baseline Jammy. Không chạy fixture không tin cậy trên production; không chạy Valgrind đồng thời trên binary ASan vì hai instrumentation tạo nhiễu và không phải oracle đã chốt.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng
- **Context/stakeholder:** reviewer của M01 cần xác nhận repository skeleton biên dịch đúng C17.
- **Input/baseline/constraint:** Ubuntu 22.04/WSL2, GCC 11.4 baseline, file [environment_smoke.c](assets/environment_smoke.c), không dùng dữ liệu thật.
- **Decision/action:** lưu output bốn lệnh version; biên dịch với `-std=c17 -Wall -Wextra -Wpedantic -Werror` rồi chạy smoke test.
- **Artifact/output:** version manifest, clean-build log và executable tạm ngoài repository.
- **Expected result:** compiler exit `0`, warning count `0`, stdout `ENV_SMOKE PASS`.
- **Verification/oracle/evidence:** exit code, stdout chính xác và bốn dòng version trong manifest; đây là oracle của AT-A01-01.

##### Ví dụ code cụ thể

Lưu snippet độc lập sau thành `/tmp/s01_env_micro.c`; ví dụ chỉ khóa language mode và warning profile, không dùng source hoặc logic của ASM-A01.

```c
#include <stdio.h>

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201710L
#error "C17 mode required"
#endif

int main(void)
{
    puts("S01_ENV_MICRO PASS");
    return 0;
}
```

Trong `ENV-ADV-C-JAMMY`, biên dịch và chạy:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror \
  /tmp/s01_env_micro.c -o /tmp/s01_env_micro
/tmp/s01_env_micro
```

- **Compile oracle:** stdout rỗng, stderr rỗng, exit code `0`.
- **Run oracle:** stdout `S01_ENV_MICRO PASS` và một ký tự xuống dòng; stderr rỗng; exit code `0`.

Guard `__STDC_VERSION__` làm build dừng nếu translation unit không ở C17 hoặc mới hơn, nên binary không thể tạo ra từ language mode cũ rồi vẫn báo PASS. Bộ cờ warning biến warning thành compile failure, còn `puts` tạo một oracle stdout cố định. Cặp exit code và stdout chứng minh đúng lệnh đã build/run; nó không thay thế fingerprint phiên bản GCC/GDB/Valgrind của evidence manifest.

##### Best practices
- **Rule:** ghi exact version và exact command. **Rationale:** warning set và sanitizer behavior phụ thuộc tool/version. **Positive:** manifest chứa dòng đầu của `gcc --version` và lệnh đầy đủ. **Negative/hậu quả:** chỉ ghi “GCC 11+”, reviewer không tái lập được.
- **Rule:** dùng build tree sạch cho evidence chính. **Rationale:** object cũ có thể che thay đổi cờ. **Positive:** xóa riêng build tree được xác định rồi configure lại. **Negative/hậu quả:** tái dùng cache không rõ nguồn, log không chứng minh source hiện tại đã được biên dịch.

##### Anti-pattern, failure modes và troubleshooting
Dấu hiệu `unrecognized command-line option` thường do sai compiler/version: xác nhận `which gcc` và `gcc --version`, chọn toolchain baseline rồi lưu lại. Dấu hiệu Valgrind báo loader/JIT thay vì code học viên: chạy binary debug thường, thu nhỏ fixture và kiểm stack trace. Dấu hiệu smoke test in đúng nhưng build có warning: quality gate vẫn fail; sửa warning tại nguyên nhân, không bỏ `-Werror` hay cast để che lỗi.

#### OUT-S01-02 Pointer deep-dive: pointer-to-pointer, pointer arithmetic & const-correctness, function pointers, callback / dispatch table, void* generic API, common pointer pitfalls

**Mapping:** OUT-S01-02 · ADVC-H1SD · M01 — typed dispatcher và generic sort/search/swap adapter.

##### Định nghĩa rõ ràng
Con trỏ lưu địa chỉ của một object hoặc function có kiểu. `T **` cho phép callee thay đổi một biến `T *` của caller; nó không đồng nghĩa với `const T **`. Phép cộng/trừ trên `T *` tính theo phần tử và chỉ được xác định trong cùng một array object hoặc vị trí one-past; one-past không được dereference. `const T *` cấm sửa `T` qua pointer đó, còn `T *const` cấm đổi chính pointer. Function pointer phải có prototype tương thích khi gọi. Dispatch table là bảng dữ liệu ánh xạ key tới typed callback và context. `void *` chuyển đổi được với object pointer nhưng không có kích thước phần tử, vì vậy generic API phải nhận `count` và `element_size`; phép offset portable dùng `unsigned char *`.

##### Vấn đề/vai trò và quyết định cần đưa ra
Dispatcher cần thêm command mà không tăng chuỗi `if/else`, đồng thời reviewer phải kiểm được prototype, lifetime, null policy và bounds. Học viên quyết định một callback typedef duy nhất, ai sở hữu context, policy cho unknown/null handler, comparator order, và điều kiện hợp lệ của generic buffer. Các quyết định đó là contract quan sát được, không phải chi tiết tùy ý.

##### Cơ chế và mental model
Caller truyền `&out` khi callee cần xuất một pointer: callee kiểm `out`, gán giá trị xác định, và không giữ địa chỉ biến local sau khi trả về. Trong table, mỗi entry chứa `name`, callback và `context`; dispatcher tìm entry rồi gọi đúng prototype. `qsort`/`bsearch` truyền địa chỉ phần tử dưới dạng `const void *`; comparator cast về đúng element type và trả âm/0/dương theo total order. Generic swap xem vùng nhớ như dãy byte và kiểm `index < count`; `void *` tự nó không chứng minh type, alignment hay lifetime.

##### Khi dùng / khi không dùng
Dùng callback table khi tập operation có chung contract và cần mở rộng bằng dữ liệu. Dùng `void *` khi một thuật toán thực sự độc lập với element type và có đủ size/alignment/lifetime contract. Không dùng cast function pointer để ép các handler khác prototype; hãy viết adapter typed. Không dùng pointer arithmetic để đi qua các object rời rạc, không dereference one-past, và không dùng `void * + n` nếu cần portable C17. Với vài kiểu cố định, wrapper typed thường dễ review hơn API generic.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng
- **Context/stakeholder:** gateway nhận `set 17`, command lạ và command bị disable; telemetry cần sort/search cả `INT_MIN`/`INT_MAX`.
- **Input/baseline/constraint:** registry local không mutable global; mảng `{INT_MAX,4,INT_MIN,4,0}`; comparator không phép trừ; generic swap nhận count/size.
- **Decision/action:** dùng `command_fn`, context có lifetime đến hết `main`, comparator `(a>b)-(a<b)`, `const int **out`-style output ở `find_int`, byte pointer cho swap.
- **Artifact/output:** [dispatcher_demo.c](assets/dispatcher_demo.c).
- **Expected result:** known command cập nhật context; unknown/null trả status; sort/search/swap qua mọi assertion; stdout `S01 DISPATCHER PASS`.
- **Verification/oracle/evidence:** biên dịch warning-free, chạy assertion fixture và chạy lại với `-fsanitize=address,undefined`; exit `0` và không sanitizer finding.

##### Ví dụ code cụ thể

Lưu snippet độc lập sau thành `/tmp/s01_pointer_micro.c`. Dữ liệu và logic “tìm số dương chẵn đầu tiên” khác command registry, sort/search/swap/apply của ASM-A01.

```c
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

typedef int (*predicate_fn)(int value);

static int is_positive_even(int value)
{
    return value > 0 && value % 2 == 0;
}

static int find_if(const int *values, size_t count,
                   predicate_fn predicate, const int **out_match)
{
    size_t index;

    if (out_match == NULL) {
        return 0;
    }
    *out_match = NULL;
    if ((values == NULL && count != 0U) || predicate == NULL) {
        return 0;
    }

    for (index = 0U; index < count; ++index) {
        if (predicate(values[index])) {
            *out_match = &values[index];
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    const int values[] = {-3, 7, 8, 10};
    const size_t count = sizeof values / sizeof values[0];
    const int *match = NULL;

    assert(find_if(values, count, is_positive_even, &match) == 1);
    assert(match != NULL && *match == 8);
    printf("S01_POINTER_MICRO value=%d index=%td\n", *match, match - values);
    assert(find_if(values, count, NULL, &match) == 0 && match == NULL);
    return 0;
}
```

Trong `ENV-ADV-C-JAMMY`, biên dịch và chạy:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror \
  /tmp/s01_pointer_micro.c -o /tmp/s01_pointer_micro
/tmp/s01_pointer_micro
```

- **Compile oracle:** stdout rỗng, stderr rỗng, exit code `0`.
- **Run oracle:** stdout `S01_POINTER_MICRO value=8 index=2` và một ký tự xuống dòng; stderr rỗng; exit code `0`.

`predicate_fn` khóa prototype của callback mà không cần cast, còn `const int *` ngăn helper sửa mảng qua pointer. `const int **out_match` cho phép callee xuất địa chỉ phần tử và luôn đặt output về `NULL` trước nhánh không thành công. Phép `match - values` được xác định vì hai pointer cùng nằm trong một array object; assertion callback-null là oracle cho nhánh lỗi, không phải lời giải dispatcher của Assignment.

##### Best practices
- **Rule:** mọi handler dùng cùng typedef, không cast để che mismatch. **Rationale:** gọi qua incompatible function type là undefined behavior. **Positive:** `typedef status (*command_fn)(const char *, void *)`. **Negative/hậu quả:** ép `(command_fn)legacy_handler` có thể sai ABI dù build qua.
- **Rule:** generic API công bố null/zero/count/size và kiểm trước khi tính offset. **Rationale:** `void *` không mang bounds. **Positive:** từ chối `index >= count` rồi mới dùng `unsigned char *`. **Negative/hậu quả:** nhân index trước khi kiểm có thể overflow/out-of-bounds.
- **Rule:** comparator so sánh quan hệ, không trả `a-b`. **Rationale:** signed overflow là UB và phá ordering. **Positive:** `(a > b) - (a < b)`. **Negative/hậu quả:** `INT_MIN - INT_MAX` có thể overflow.
- **Rule:** output pointer được gán trạng thái xác định trên mọi nhánh. **Rationale:** tránh caller đọc pointer cũ. **Positive:** đặt `*out = NULL` trước search. **Negative/hậu quả:** not-found để nguyên output gây stale/dangling use.

##### Anti-pattern, failure modes và troubleshooting
Segfault ngay khi callback chạy: kiểm prototype bằng bỏ mọi cast và bật `-Wcast-function-type`; sửa bằng adapter đúng kiểu. Sort sai ở cực trị: thêm fixture `INT_MIN/INT_MAX`, quan sát comparator và thay phép trừ bằng relational compare. Sanitizer báo heap/stack-use-after-scope ở context: truy ngược nơi đăng ký, bảo đảm context sống lâu hơn registry hoặc sao chép state có ownership rõ. Compiler chấp nhận `void *` arithmetic chỉ trong GNU mode: build lại `-std=c17 -Wpedantic`, cast sang byte pointer và ràng buộc count/size.


## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

Ví dụ tích hợp dùng cùng warning profile đã fingerprint để kiểm typed dispatcher và generic adapters. Đây là artifact học tập của M01, không phải starter hay đáp án của ASM-A01.

### Input/trạng thái ban đầu
Registry gồm `set`, `disabled`; mảng số gồm hai giá trị `4`, `INT_MIN`, `INT_MAX` và `0`. Context tồn tại suốt lần chạy; command lạ và callback null phải trả status, không crash.

### Cách thực hiện
Biên dịch [dispatcher_demo.c](assets/dispatcher_demo.c), chạy fixture assertion, sau đó biên dịch lại với ASan+UBSan. Quan sát rằng cùng một callback typedef được dùng xuyên registry, output pointer luôn được reset và generic swap tính offset qua `unsigned char *`.

### Output mong đợi
Cả hai binary exit `0`; stdout chính xác `S01 DISPATCHER PASS`; sanitizer không in finding. Unknown command và null callback được xử lý bằng status, không thay đổi context.

### Cách xác minh
- `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror assets/dispatcher_demo.c -o /tmp/s01_dispatcher && /tmp/s01_dispatcher`
- `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer assets/dispatcher_demo.c -o /tmp/s01_dispatcher_san && /tmp/s01_dispatcher_san`
- Oracle: hai lệnh exit `0`; mỗi lần in đúng `S01 DISPATCHER PASS`; stderr của lần sanitizer không có finding.

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

| Dấu hiệu | Nguyên nhân khả dĩ | Chẩn đoán/bằng chứng | Khắc phục | Phòng tránh |
|---|---|---|---|---|
| `-Werror=incompatible-pointer-types` ở registry | Callback sai prototype | So declaration với `command_fn`, bỏ cast tạm | Viết adapter đúng prototype | Một typedef public duy nhất và compile warning-as-error |
| Search đôi lúc không tìm thấy giá trị có thật | Mảng chưa sort cùng comparator | In/test mảng trước `bsearch` | `qsort` trước search hoặc dùng linear search | Test sorted precondition và duplicate fixture |
| ASan báo use-after-scope | Context trỏ tới object đã hết lifetime | Stack trace đến nơi đăng ký callback | Đổi lifetime/ownership hoặc unregister trước khi object chết | Ghi lifetime trong API contract |
| Kết quả khác giữa `gnu17` và `c17` | Dùng GNU `void *` arithmetic | Build `-std=c17 -Wpedantic` | Offset qua `unsigned char *` | Giữ C17 mode trong CI/evidence |

## 6. Từ điển thuật ngữ và mô hình tư duy

- **Object pointer:** con trỏ tới object; có thể chuyển đổi qua/lại `void *` theo contract C.
- **Function pointer:** con trỏ tới function có prototype; không được suy diễn từ quy tắc của object pointer.
- **One-past:** địa chỉ ngay sau phần tử cuối của cùng array, chỉ dùng cho so sánh/điều khiển vòng lặp, không dereference.
- **Const-correctness:** biểu diễn quyền sửa pointee/pointer trong type để compiler kiểm.
- **Callback/context:** operation được truyền như dữ liệu và state đi kèm; context không tự mang ownership.
- **Dispatch table:** bảng key → typed callback/context, extension point của M01.
- **Oracle:** kết quả pass/fail quan sát được như exit code, stdout, assertion hoặc sanitizer report.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng
- SRC-SYL — L2_MBD_ADVC_Syllabus_v1.0 1.xlsx: D:\Workspaces\FR_DN26_MBD_Simulink\L2_MBD_ADVC_Syllabus_v1.0 1.xlsx (publisher: Internal training syllabus; version: 1.0; accessed_at: 2026-08-21; license: internal_approved for this requested training-content generation; allowed_use: internal_approved)
- SRC-UBUNTU22 — Ubuntu 22.04 LTS package index: https://packages.ubuntu.com/jammy/ (publisher: Canonical / Ubuntu; version: Jammy 22.04 package baseline; accessed_at: 2026-08-21; license: Canonical site and package metadata terms; reference only; allowed_use: reference)
- SRC-C17-ISO — ISO/IEC 9899:2018 — Programming languages — C: https://www.iso.org/standard/74528.html (publisher: ISO/IEC JTC 1/SC 22; version: Edition 4, C17, 2018; accessed_at: 2026-08-21; license: ISO copyright; metadata and clause references only, no reproduction; allowed_use: reference)
- SRC-C17-WG14 — WG14 N2176 proposed C17 committee draft: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2176.pdf (publisher: ISO/IEC JTC 1/SC 22/WG14; version: N2176, 2017-10-09; non-final public committee document; accessed_at: 2026-08-21; license: Publicly accessible committee document; link and paraphrase only; allowed_use: reference)
- SRC-GCC11 — GCC 11.4 manuals: https://gcc.gnu.org/onlinedocs/gcc-11.4.0/ (publisher: GNU Project / Free Software Foundation; version: 11.4.0; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-GNUC — GNU C Language Manual: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/index.html (publisher: GNU Project / Free Software Foundation; version: rolling manual as accessed; C17 scope constrained by plan; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-CERTC — SEI CERT C Coding Standard: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/ (publisher: Carnegie Mellon University Software Engineering Institute; version: online work-in-progress snapshot as accessed; claims constrained to C17; accessed_at: 2026-08-21; license: CMU/SEI terms; reference and limited quotation only; allowed_use: reference)
- SRC-LLVM14 — LLVM/Clang 14.0.0 Documentation: https://releases.llvm.org/14.0.0/tools/clang/docs/index.html (publisher: LLVM Project; version: 14.0.0; accessed_at: 2026-08-21; license: Apache-2.0 WITH LLVM-exception; allowed_use: reference)
- SRC-VALGRIND318 — Valgrind Memcheck Manual: https://valgrind.org/docs/manual/mc-manual.html (publisher: Valgrind Developers; version: 3.18.1 Ubuntu baseline; options constrained to that release; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.2 or later; allowed_use: reference)

### Phần bổ sung/suy diễn
Không sử dụng nguồn bổ sung hay claim không có nguồn cụ thể. Hai asset C17 là code nguyên gốc phục vụ khóa học; không sao chép code từ ISO, GNU, CERT hoặc tài liệu bên ngoài. WG14 N2176 chỉ được dùng làm chỉ mục điều khoản công khai, không được trình bày là bản ISO cuối cùng.

---

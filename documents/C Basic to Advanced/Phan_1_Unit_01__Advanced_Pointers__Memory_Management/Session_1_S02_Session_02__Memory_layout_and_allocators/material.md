# Session S02: Session 02 — Memory layout and allocators — Học liệu cốt lõi

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 01 — Advanced Pointers & Memory Management

## 🎯 Learning Outcomes
- **ADVC-H1SD** [create] — Thiết kế, hiện thực và kiểm chứng các mô-đun C17 dùng con trỏ nâng cao, quản lý bộ nhớ động, ADT đóng gói và cấu trúc dữ liệu generic mà không làm lộ ownership hoặc gây lỗi bộ nhớ trong các ca kiểm thử đã cho. · Bằng chứng: Public API/header và implementation C biên dịch với warning profile đã chốt; unit tests đạt; sanitizer hoặc Valgrind không báo lỗi thuộc phạm vi fixture.

## 🧭 Ngữ cảnh nghề nghiệp/dự án và phần tăng trưởng của Unit

**Bối cảnh nghề nghiệp/dự án:**
**MDB Edge Diagnostics Gateway — Simulated** — Cổng chẩn đoán và telemetry chạy local trên Linux cho thiết bị giả lập; tiếp nhận command, quản lý work records, thực thi backend process/thread và phục vụ protocol TCP loopback. Vai trò học viên: C systems developer chịu trách nhiệm phát triển và harden từng increment trong repository đào tạo. Mục tiêu: Bàn giao một gateway TCP loopback tích hợp core C17, process/thread backends và quality evidence; phục vụ ít nhất 100 client synthetic theo Assignment 09 mà không có finding mức chặn trong oracle áp dụng.

**Project increment sau Unit này:**
- **milestone_id:** M02
- **user_story:** Là maintainer, tôi muốn core cấp phát bounded command records từ fixed-block pool để kiểm soát capacity và lifetime.
- **business_value:** Giảm heap churn trong workload bounded và tạo ownership/reset contract quan sát được.
- **baseline:** Dispatcher module v1 đã qua M01.
- **change_scope:** - Layout probe<br>- Fixed-block pool<br>- Overflow/alignment checks<br>- Dispatcher allocation integration<br>- Memory-safety evidence
- **inputs:** - Dispatcher module v1<br>- DC-COMMAND<br>- Synthetic command and telemetry fixtures
- **integration_points:** - command dispatcher<br>- memory pool
- **artifacts_added:** - Memory-safe command core v2<br>- A02 memory evidence
- **acceptance_criteria:** - FR-02 đạt<br>- NFR-01 đạt<br>- M01 behavior không regression
- **definition_of_done:** - Project Definition of Done áp dụng cho M02

**Mức xác thực của bối cảnh:** simulated

Sau S02, học viên có thể giải thích layout ở hai lớp (quy tắc C và quan sát ELF/Linux), thiết kế ownership cho allocation failure, và xây fixed-block pool có capacity, alignment, membership, double-free và reset oracle. Năng lực ADVC-H1SD được áp dụng để biến Dispatcher module v1 thành Memory-safe command core v2, là baseline của ASM-A03.

## 📚 Nguồn đầu vào đã map
- SRC-SYL — L2_MBD_ADVC_Syllabus_v1.0 1.xlsx: D:\Workspaces\FR_DN26_MBD_Simulink\L2_MBD_ADVC_Syllabus_v1.0 1.xlsx (publisher: Internal training syllabus; version: 1.0; accessed_at: 2026-08-21; license: internal_approved for this requested training-content generation; allowed_use: internal_approved)
- SRC-C17-ISO — ISO/IEC 9899:2018 — Programming languages — C: https://www.iso.org/standard/74528.html (publisher: ISO/IEC JTC 1/SC 22; version: Edition 4, C17, 2018; accessed_at: 2026-08-21; license: ISO copyright; metadata and clause references only, no reproduction; allowed_use: reference)
- SRC-C17-WG14 — WG14 N2176 proposed C17 committee draft: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2176.pdf (publisher: ISO/IEC JTC 1/SC 22/WG14; version: N2176, 2017-10-09; non-final public committee document; accessed_at: 2026-08-21; license: Publicly accessible committee document; link and paraphrase only; allowed_use: reference)
- SRC-GNUC — GNU C Language Manual: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/index.html (publisher: GNU Project / Free Software Foundation; version: rolling manual as accessed; C17 scope constrained by plan; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-GLIBC235 — GNU C Library Reference Manual: https://sourceware.org/glibc/manual/2.35/pdf/libc.pdf (publisher: GNU Project; version: glibc 2.35; accessed_at: 2026-08-21; license: GNU Free Documentation License; link and paraphrase; allowed_use: reference)
- SRC-LD238 — GNU ld 2.38 documentation: https://sourceware.org/binutils/docs-2.38/ld/ (publisher: GNU Project / Binutils; version: 2.38; accessed_at: 2026-08-21; license: GNU Free Documentation License; allowed_use: reference)
- SRC-CERTC — SEI CERT C Coding Standard: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/ (publisher: Carnegie Mellon University Software Engineering Institute; version: online work-in-progress snapshot as accessed; claims constrained to C17; accessed_at: 2026-08-21; license: CMU/SEI terms; reference and limited quotation only; allowed_use: reference)
- SRC-LLVM14 — LLVM/Clang 14.0.0 Documentation: https://releases.llvm.org/14.0.0/tools/clang/docs/index.html (publisher: LLVM Project; version: 14.0.0; accessed_at: 2026-08-21; license: Apache-2.0 WITH LLVM-exception; allowed_use: reference)
- SRC-VALGRIND318 — Valgrind Memcheck Manual: https://valgrind.org/docs/manual/mc-manual.html (publisher: Valgrind Developers; version: 3.18.1 Ubuntu baseline; options constrained to that release; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.2 or later; allowed_use: reference)

> Đây là khu vực provenance. Khi viết nội dung, tiêu hóa thông tin từ nguồn và trình bày độc lập; không chèn tên file nguồn vào câu văn kỹ thuật. Nguồn bổ sung hoặc phần suy diễn phải được ghi riêng tại mục 7.

---

## 1. Kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết
- **knowledge:** - Pointer/lifetime/callback contracts từ S01
- **skills:** - Chạy warning profile và sanitizer fixture
- **completed_units:** - s01
- **assets:** - starter/assignment-02/README.md

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

Chạy `gcc --version` và `valgrind --version`, rồi biên dịch [pool_demo.c](assets/pool_demo.c) với C17 warning profile. Baseline đạt khi `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror assets/pool_demo.c -o /tmp/s02_pool && /tmp/s02_pool` exit `0` và in `S02 POOL PASS`. Memory gate chạy riêng: `valgrind --tool=memcheck --leak-check=full --errors-for-leak-kinds=definite,indirect --error-exitcode=99 /tmp/s02_pool`.

## 2. Định vị trong lộ trình (Mental Map)

S01 đã khóa pointer/lifetime contract; S02 đặt các pointer đó lên một mô hình lưu trữ cụ thể. Học viên đi từ “địa chỉ hợp lệ” sang “địa chỉ còn lifetime, đúng alignment, thuộc allocator và nằm trong capacity”. M02 thay heap churn của record bằng bounded pool nhưng giữ hành vi M01. S03 sẽ che representation và ownership vừa thiết kế sau một opaque API.

## 3. Nội dung lý thuyết cốt lõi

**Phạm vi nội dung:**
- [x] Process memory layout (text/data/bss/heap/stack), struct alignment & padding, endianness; malloc/calloc/realloc/free behaviour, fragmentation, arena & fixed-block pool allocator

Leaf dưới đây giữ nguyên văn syllabus và truy vết tới ADVC-H1SD/M02; mọi nhóm khái niệm trong leaf được nối bằng một allocator case và oracle riêng.


#### OUT-S02-01 Process memory layout (text/data/bss/heap/stack), struct alignment & padding, endianness; malloc/calloc/realloc/free behaviour, fragmentation, arena & fixed-block pool allocator

**Mapping:** OUT-S02-01 · ADVC-H1SD · M02 — fixed-block pool và memory evidence cho Memory-safe command core v2.

##### Định nghĩa rõ ràng
C17 định nghĩa object, storage duration, alignment, representation và lifetime; các nhãn `.text/.data/.bss`, heap và stack là mô hình triển khai thường gặp trên ELF/Linux, không phải các vùng bắt buộc của ngôn ngữ C. Linker đặt code/data vào section; loader ánh xạ segment, còn allocator quản lý các block động trong address space. `struct` có thể chứa padding để mỗi member và phần tử array thỏa alignment; `sizeof`, `_Alignof` và `offsetof` là cách quan sát đúng trên target. Endianness là thứ tự byte của object nhiều byte trên một kiến trúc; C17 không chốt little/big endian.

`malloc` cấp vùng chưa khởi tạo; `calloc` cấp cho một số phần tử và zero toàn bộ byte; zero byte không nên bị suy diễn thành mọi giá trị semantic của mọi type. `realloc` có thể đổi địa chỉ; với kích thước khác zero, failure giữ block cũ nên phải dùng temporary pointer. `free(NULL)` hợp lệ, nhưng free pointer không phải block còn sống do allocator trả về là lỗi. Fragmentation là khả năng dung lượng trống không dùng được hiệu quả vì kích thước/vị trí/lifetime. Arena cấp tuần tự rồi thu hồi theo nhóm; fixed-block pool cấp các slot cùng kích thước và tái sử dụng theo policy.

##### Vấn đề/vai trò và quyết định cần đưa ra
Gateway có workload command record bị chặn capacity; maintainer cần tránh allocation tùy ý ở fast path và phải biết rõ exhaustion/reset. Học viên quyết định record layout, external byte encoding, overflow policy, block alignment/capacity, cách nhận diện foreign/double free và lifetime sau reset. Reviewer cần oracle trạng thái, không chấp nhận “không crash” là đủ.

##### Cơ chế và mental model
Mỗi object có `size`, `alignment`, `lifetime` và `owner`. Compiler có thể chèn padding giữa/cuối struct; sắp member khác nhau có thể đổi size nhưng không làm layout thành wire contract. Khi cấp `count * size`, kiểm `count > SIZE_MAX / size` trước phép nhân. Pool ánh xạ một tập slot hữu hạn sang state free/used: `alloc` chuyển free→used, `free` chỉ chuyển đúng slot used→free, exhaustion không mutate state, reset chuyển tất cả về free và làm invalid mọi pointer logic cũ. Arena rẻ khi lifetime đồng pha; pool dự đoán tốt khi block size/capacity cố định, đổi lại có internal waste và policy cứng.

##### Khi dùng / khi không dùng
Dùng heap chung khi kích thước/lifetime khó dự đoán và allocator overhead chấp nhận được. Dùng arena khi nhiều object chết cùng lúc; không dùng nếu cần free riêng lẻ lâu dài. Dùng fixed pool khi upper bound và maximum object size rõ; không dùng một pool duy nhất cho object rất chênh lệch kích thước hoặc khi capacity động là yêu cầu. Không serialize raw struct bằng `write(sizeof struct)`: padding, alignment, endian và phiên bản làm format không portable; encode từng field vào byte order công bố.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng
- **Context/stakeholder:** dispatcher M01 cần tối đa bốn command record sống đồng thời và byte output ổn định.
- **Input/baseline/constraint:** bốn slot 64 byte, alignment `max_align_t`, lần cấp thứ năm phải fail, free/reuse/double-free/foreign/reset có status; giá trị `0x01020304` phải encode big-endian.
- **Decision/action:** dùng union để giữ alignment, bitmap `used` làm oracle state, so equality với từng slot để kiểm membership, encode từng byte bằng shift.
- **Artifact/output:** [pool_demo.c](assets/pool_demo.c).
- **Expected result:** bốn pointer khác nhau và aligned; exhaustion trả `NULL`; slot được reuse; double/foreign free bị từ chối; wire bytes là `01 02 03 04`; stdout `S02 POOL PASS`.
- **Verification/oracle/evidence:** assertion fixture, warning-free build và Valgrind/ASan binary riêng; exit `0`, không invalid access hoặc definite/indirect leak.

##### Ví dụ code cụ thể

Lưu snippet độc lập sau thành `/tmp/s02_layout_heap_micro.c`. Ví dụ dùng một mảng record tăng từ hai lên ba phần tử; nó không cài fixed-block pool, command record, reset hay free-state logic của ASM-A02.

```c
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint8_t tag;
    uint32_t value;
} sample_record;

static void encode_u32_be(uint32_t value, unsigned char out[4])
{
    out[0] = (unsigned char)(value >> 24);
    out[1] = (unsigned char)(value >> 16);
    out[2] = (unsigned char)(value >> 8);
    out[3] = (unsigned char)value;
}

int main(void)
{
    const size_t count = 2U;
    const size_t grown_count = 3U;
    sample_record *records = calloc(count, sizeof *records);
    sample_record *grown;
    unsigned char wire[4];
    int layout_ok;

    if (records == NULL) {
        fputs("allocation failed\n", stderr);
        return 2;
    }
    assert(records[0].tag == 0U && records[0].value == 0U);
    records[0].tag = 7U;
    records[0].value = UINT32_C(0x01020304);

    if (grown_count > SIZE_MAX / sizeof *records) {
        free(records);
        return 3;
    }
    grown = realloc(records, grown_count * sizeof *records);
    if (grown == NULL) {
        free(records);
        fputs("growth failed\n", stderr);
        return 2;
    }
    records = grown;
    records[2].tag = 9U;
    records[2].value = 42U;

    layout_ok =
        offsetof(sample_record, value) >= sizeof(uint8_t) &&
        sizeof(sample_record) >=
            offsetof(sample_record, value) + sizeof(uint32_t) &&
        _Alignof(sample_record) >= _Alignof(uint32_t);
    encode_u32_be(records[0].value, wire);
    printf("S02_LAYOUT_HEAP_MICRO layout_ok=%d wire=%02X%02X%02X%02X\n",
           layout_ok,
           (unsigned)wire[0], (unsigned)wire[1],
           (unsigned)wire[2], (unsigned)wire[3]);

    free(records);
    return 0;
}
```

Trong `ENV-ADV-C-JAMMY`, biên dịch và chạy:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror \
  /tmp/s02_layout_heap_micro.c -o /tmp/s02_layout_heap_micro
/tmp/s02_layout_heap_micro
```

- **Compile oracle:** stdout rỗng, stderr rỗng, exit code `0`.
- **Run oracle:** stdout `S02_LAYOUT_HEAP_MICRO layout_ok=1 wire=01020304` và một ký tự xuống dòng; stderr rỗng; exit code `0`.

`sizeof`, `_Alignof` và `offsetof` kiểm các quan hệ layout cần đúng mà không khóa một số byte padding cụ thể cho mọi target. `calloc` cung cấp zeroed bytes cho block ban đầu; sau `realloc`, code chỉ thay owner pointer khi temporary pointer thành công và tự khởi tạo phần tử mới. Guard `SIZE_MAX` đứng trước phép nhân, còn encoder tạo big-endian bằng shift thay vì copy raw struct; stdout đồng thời là oracle layout và wire-format.

##### Best practices
- **Rule:** kiểm overflow trước `count * size`. **Rationale:** wrap tạo block nhỏ hơn contract rồi gây out-of-bounds. **Positive:** `count > SIZE_MAX / size` thì fail. **Negative/hậu quả:** nhân trước rồi kiểm kết quả có thể đã wrap.
- **Rule:** gán kết quả nonzero `realloc` vào temporary pointer. **Rationale:** failure giữ block cũ. **Positive:** chỉ thay owner pointer sau success. **Negative/hậu quả:** `p = realloc(p,n)` làm mất block khi trả `NULL`, gây leak.
- **Rule:** allocator kiểm alignment, exact membership và current state trước mutation. **Rationale:** foreign/interior/double free phá invariant. **Positive:** chỉ chấp nhận địa chỉ đầu của slot used. **Negative/hậu quả:** dùng range check lỏng chấp nhận `slot+1`.
- **Rule:** công bố reset invalidation. **Rationale:** slot được tái cấp có thể mang object khác dù địa chỉ giống. **Positive:** caller xóa mọi handle sau reset. **Negative/hậu quả:** dùng pointer pre-reset thành use-after-logical-lifetime.
- **Rule:** encode từng field, không copy raw struct. **Rationale:** padding/endian không phải external contract. **Positive:** explicit big-endian bytes. **Negative/hậu quả:** `memcpy` cả struct tạo output khác target hoặc làm lộ padding.

##### Anti-pattern, failure modes và troubleshooting
Valgrind báo invalid free: kiểm pointer có đúng địa chỉ block start, đúng owner và chưa free; sửa membership/state check trước mutation. UBSan/ASan báo overflow/out-of-bounds sau allocation: log `count/size`, thêm pre-multiplication guard và test `SIZE_MAX`. Wire fixture đảo byte: phân biệt host representation với protocol order, sửa explicit encoder và so byte array. Pool trả pointer misaligned: đo `(uintptr_t)p % required_alignment`, đổi storage/stride để đáp ứng alignment. Sau reset dữ liệu “tự đổi”: pointer cũ đã bị invalid theo contract; xóa reference hoặc dùng generation handle nếu bài toán cần phát hiện stale pointer.


## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

Ví dụ nối layout/alignment, bounded allocation, state invariant và explicit endian encoding trong một binary nhỏ. Nó minh họa quyết định; ASM-A02 yêu cầu một pool/integration khác và không được suy ra bằng cách chép asset này.

### Input/trạng thái ban đầu
Pool rỗng có capacity `4`, block `64` byte; năm lần alloc liên tiếp; một free/reuse/double-free; một foreign pointer; reset; giá trị `0x01020304` cần biểu diễn big-endian.

### Cách thực hiện
Biên dịch và chạy [pool_demo.c](assets/pool_demo.c). Đối chiếu `_Alignof(max_align_t)`, state bitmap và four-byte encoder. Chạy memory checker trên binary debug thường, hoặc ASan trên binary riêng.

### Output mong đợi
Mọi assertion pass, lần alloc thứ năm trả `NULL` không đổi state, freed slot được cấp lại, invalid/double free trả status, stdout chính xác `S02 POOL PASS`; checker không có finding mức chặn.

### Cách xác minh
- `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -g assets/pool_demo.c -o /tmp/s02_pool && /tmp/s02_pool`
- `valgrind --tool=memcheck --leak-check=full --errors-for-leak-kinds=definite,indirect --error-exitcode=99 /tmp/s02_pool`
- Oracle: cả hai exit `0`, stdout `S02 POOL PASS`; Valgrind báo `0 errors` và không definite/indirect leak.

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

| Dấu hiệu | Nguyên nhân | Chẩn đoán/bằng chứng | Khắc phục | Phòng tránh |
|---|---|---|---|---|
| `malloc` success nhưng ghi record overflow | `count*size` wrap hoặc size contract sai | ASan trace + log operands trước nhân | Guard bằng `SIZE_MAX/size` | Boundary fixtures cho 0, 1 và cực trị |
| `realloc` failure kéo theo leak | Ghi đè owner pointer | Fault-injection/review assignment | Dùng temporary pointer | Rule ownership trên mọi failure path |
| Pool free count tăng hai lần | Double free không kiểm state | Assert invariant sau từng operation | Từ chối slot đã free | Bitmap/state oracle và negative test |
| File/wire khác giữa máy | Raw struct/padding/endian | So từng byte và `offsetof` report | Encode từng field theo byte order | External schema độc lập object layout |

## 6. Từ điển thuật ngữ và mô hình tư duy

- **Storage duration/lifetime:** khoảng chương trình dành storage và khoảng object có thể được truy cập hợp lệ.
- **Alignment:** bội địa chỉ mà type yêu cầu; pool phải đáp ứng type khắt khe nhất được công bố.
- **Padding:** byte compiler chèn để thỏa layout; không phải dữ liệu nghiệp vụ.
- **Endianness:** thứ tự byte của giá trị nhiều byte trên target; wire order cần contract riêng.
- **External/internal fragmentation:** lãng phí do khoảng trống rời rạc hoặc block lớn hơn object.
- **Arena:** allocator thu hồi theo nhóm; reset kết thúc lifetime logic của mọi object trong arena.
- **Fixed-block pool:** tập slot cùng kích thước/capacity, nền tảng memory core v2.
- **Failure atomicity:** operation fail để observable state giữ nguyên như contract.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng
- SRC-SYL — L2_MBD_ADVC_Syllabus_v1.0 1.xlsx: D:\Workspaces\FR_DN26_MBD_Simulink\L2_MBD_ADVC_Syllabus_v1.0 1.xlsx (publisher: Internal training syllabus; version: 1.0; accessed_at: 2026-08-21; license: internal_approved for this requested training-content generation; allowed_use: internal_approved)
- SRC-C17-ISO — ISO/IEC 9899:2018 — Programming languages — C: https://www.iso.org/standard/74528.html (publisher: ISO/IEC JTC 1/SC 22; version: Edition 4, C17, 2018; accessed_at: 2026-08-21; license: ISO copyright; metadata and clause references only, no reproduction; allowed_use: reference)
- SRC-C17-WG14 — WG14 N2176 proposed C17 committee draft: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2176.pdf (publisher: ISO/IEC JTC 1/SC 22/WG14; version: N2176, 2017-10-09; non-final public committee document; accessed_at: 2026-08-21; license: Publicly accessible committee document; link and paraphrase only; allowed_use: reference)
- SRC-GNUC — GNU C Language Manual: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/index.html (publisher: GNU Project / Free Software Foundation; version: rolling manual as accessed; C17 scope constrained by plan; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-GLIBC235 — GNU C Library Reference Manual: https://sourceware.org/glibc/manual/2.35/pdf/libc.pdf (publisher: GNU Project; version: glibc 2.35; accessed_at: 2026-08-21; license: GNU Free Documentation License; link and paraphrase; allowed_use: reference)
- SRC-LD238 — GNU ld 2.38 documentation: https://sourceware.org/binutils/docs-2.38/ld/ (publisher: GNU Project / Binutils; version: 2.38; accessed_at: 2026-08-21; license: GNU Free Documentation License; allowed_use: reference)
- SRC-CERTC — SEI CERT C Coding Standard: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/ (publisher: Carnegie Mellon University Software Engineering Institute; version: online work-in-progress snapshot as accessed; claims constrained to C17; accessed_at: 2026-08-21; license: CMU/SEI terms; reference and limited quotation only; allowed_use: reference)
- SRC-LLVM14 — LLVM/Clang 14.0.0 Documentation: https://releases.llvm.org/14.0.0/tools/clang/docs/index.html (publisher: LLVM Project; version: 14.0.0; accessed_at: 2026-08-21; license: Apache-2.0 WITH LLVM-exception; allowed_use: reference)
- SRC-VALGRIND318 — Valgrind Memcheck Manual: https://valgrind.org/docs/manual/mc-manual.html (publisher: Valgrind Developers; version: 3.18.1 Ubuntu baseline; options constrained to that release; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.2 or later; allowed_use: reference)

### Phần bổ sung/suy diễn
Không dùng nguồn bổ sung hay claim không có nguồn cụ thể. Asset là code nguyên gốc của khóa. Mô hình `.text/.data/.bss/heap/stack` được ghi rõ là quan sát ELF/Linux, không bị trình bày thành yêu cầu của C17; mọi tài liệu bên ngoài chỉ được link/paraphrase theo quyền sử dụng trong registry.

---

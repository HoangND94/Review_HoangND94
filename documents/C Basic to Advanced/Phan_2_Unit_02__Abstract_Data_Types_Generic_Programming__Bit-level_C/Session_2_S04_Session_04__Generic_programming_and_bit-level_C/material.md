# Session S04: Session 04 — Generic programming and bit-level C — Học liệu cốt lõi

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 02 — Abstract Data Types, Generic Programming & Bit-level C

## 🎯 Learning Outcomes

- **ADVC-H1SD** [create] — Thiết kế, hiện thực và kiểm chứng các mô-đun C17 dùng con trỏ nâng cao, quản lý bộ nhớ động, ADT đóng gói và cấu trúc dữ liệu generic mà không làm lộ ownership hoặc gây lỗi bộ nhớ trong các ca kiểm thử đã cho.

## 🧭 Ngữ cảnh nghề nghiệp/dự án và phần tăng trưởng của Unit

**Bối cảnh nghề nghiệp/dự án:** MDB Edge Diagnostics Gateway — Simulated. Học viên đóng vai core developer, nhận **Opaque event ring core v3** và bổ sung reusable vector, intrusive list cùng flag/representation contracts cho metadata tổng hợp.

**Project increment sau Unit này:** milestone **M04** tạo **Generic gateway core v4**, test cho dynamic array/intrusive list, flag truth table và portability probes. M05 sẽ đóng gói chính artifact này; vì vậy bounds, ownership, membership và representation boundary phải là contract quan sát được, không phải giả định ẩn.

**Mức xác thực của bối cảnh:** simulated; event/command/telemetry fixtures là dữ liệu tổng hợp.

Năng lực mới gắn với ADVC-H1SD là tạo generic API mà caller không phải nhân bản container logic, đồng thời chỉ rõ phần nào portable C17 và phần nào phụ thuộc compiler/ABI.

## 📚 Nguồn đầu vào đã map

- [ISO/IEC 9899:2018 metadata](https://www.iso.org/standard/74528.html) và [WG14 N2176](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2176.pdf) — C17: object representation, `void *`, macro, `_Generic`, union, bit-field và flexible array member.
- [GNU C Language Manual](https://www.gnu.org/software/c-intro-and-ref/manual/html_node/index.html) — GNU/Clang userspace scope của container idiom.
- [glibc 2.35 manual](https://sourceware.org/glibc/manual/2.35/pdf/libc.pdf) — allocation/reallocation behavior.
- [Linux linked-list documentation](https://docs.kernel.org/core-api/list.html) — intrusive-list pattern; chỉ tham khảo khái niệm, không sao chép kernel macro/source.
- [GCC 11.4 manuals](https://gcc.gnu.org/onlinedocs/gcc-11.4.0/) và [Clang 14 documentation](https://releases.llvm.org/14.0.0/tools/clang/docs/index.html) — compiler baseline, warnings và sanitizers.
- [Valgrind Memcheck manual](https://valgrind.org/docs/manual/mc-manual.html) — memory-error evidence.
- [SEI CERT C Coding Standard](https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/) — integer, allocation, pointer và bitwise review rules.
- Syllabus nội bộ v1.0 — phạm vi, LO, artifact và acceptance của Session 04.

---

## 1. Kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết

- Hoàn thành S03: opaque handle, public/private boundary, ownership/lifetime và error-code contract.
- Biết `malloc/calloc/realloc/free`, `sizeof`, alignment và pointer arithmetic.
- Chạy được CTest, ASan+UBSan và Valgrind trên binary tách biệt.

### Môi trường, công cụ và phiên bản

- Ubuntu 22.04 native/VM/WSL2; C17; glibc 2.35.
- CMake 3.22.1; GCC 11.4; Clang 14.0; Valgrind 3.18.1.
- Strict flags: `-std=c17 -Wall -Wextra -Wpedantic -Werror`.
- Asset chỉ ghi build output vào directory được chỉ định; không cần dịch vụ, network hoặc dữ liệu ngoài fixture.

### Phương thức xác minh artifact

Phương thức `artifact_review` kết hợp executable oracle. Preflight:

```bash
cmake --version | head -1
gcc --version | head -1
clang-14 --version | head -1
valgrind --version
```

Expected baseline: CMake 3.22.x, GCC 11.x, Clang 14.x và Valgrind 3.18.x. Report phải ghi exact fingerprint nếu môi trường khác.

## 2. Định vị trong lộ trình (Mental Map)

```text
M03: opaque event ring core v3
        │ representation được đóng gói, ownership đã có contract
        ▼
M04: byte-vector + intrusive list + unsigned flags
        │ tagged union/FAM cho payload; layout probes chỉ là evidence
        ▼
M05: package gateway core v4 thành static/shared libraries
```

S03 dạy ẩn representation của một ADT. S04 mở rộng thành container layer dùng lại được nhưng vẫn phải bảo vệ ownership/representation. S05 không sửa các invariant này; nó chỉ đưa chúng qua translation-unit và package boundary.

## 3. Nội dung lý thuyết cốt lõi

**Phạm vi nội dung:**

- [x] Generic programming in C: void* + element-size APIs, macro generics, container_of, intrusive linked list; bit manipulation, bitfields, unions, flexible array member

#### OUT-S04-01 Generic programming in C: void* + element-size APIs, macro generics, container_of, intrusive linked list; bit manipulation, bitfields, unions, flexible array member

**Mapping:** OUT-S04-01 · ADVC-H1SD · M04 / Generic gateway core v4.

##### Định nghĩa rõ ràng và ranh giới

- **`void *` + element size:** object pointer có thể chuyển qua `void *`, nhưng ISO C không cho arithmetic trực tiếp trên `void *`. Generic container giữ `elem_size` và tính byte offset qua `unsigned char *`. API phải nói rõ copy nông/sâu, null, zero-size và destructor policy.
- **Macro generic:** function-like macro thay token, không có type checking và có thể evaluate argument nhiều lần. C17 `_Generic` chọn association theo type của controlling expression; nó hữu ích để dispatch tới typed `static inline` functions nhưng không tạo template.
- **`container_of`:** từ pointer tới một named embedded member, dùng `offsetof(type, member)` để suy ra address enclosing object. Contract chỉ hợp lệ với exact member của **live object**, đúng type/alignment/compiler target; null, fabricated, unrelated hoặc expired pointer ngoài phạm vi.
- **Intrusive list:** link node nằm trong payload object. List không allocation/copy payload; payload lifetime và membership state quyết định tính đúng. Muốn một object ở hai list đồng thời phải có hai link members.
- **Bit manipulation:** flags được encode bằng unsigned fixed-width masks. Set/clear/toggle/test lần lượt dùng OR, AND với complement, XOR và AND comparison. Shift count phải nhỏ hơn width sau promotion; unknown/reserved bits cần reject-or-preserve policy.
- **Bit-field:** chia storage unit thành named bit-width fields. Allocation order, padding, alignment, straddling và signedness của plain `int` bit-field có phần implementation-defined; raw layout không phải portable wire/storage ABI.
- **Union:** các members chia cùng storage. Tagged union đặt explicit discriminator cạnh union và chỉ đọc member khớp tag. Raw inactive-member bytes không phải serialization contract.
- **Flexible array member (FAM):** array không ghi size ở cuối struct có ít nhất một named member. `sizeof(struct)` không gồm trailing elements; allocation cần `sizeof(header) + n * sizeof(element)` với overflow check, object được truyền bằng pointer.

Điểm dễ nhầm: “generic” không xóa type/ownership contract; “bit-field vừa đúng số bit” không nghĩa layout portable; `realloc` trả null không nghĩa old block đã mất.

##### Vấn đề/vai trò và quyết định cần đưa ra

Core developer phải chốt:

1. Container copy bytes hay sở hữu object được trỏ tới; caller có destructor trách nhiệm nào.
2. Capacity tăng/giảm theo policy nào, xử lý overflow/allocation failure ra sao.
3. Khi nào `_Generic`/`static inline` tốt hơn macro expression.
4. Preconditions, qualifier contract và compiler scope của `container_of`.
5. Link node thể hiện unlinked/linked thế nào; iteration có cho phép remove không.
6. Reserved flag mask bị reject hay preserve.
7. Dữ liệu biến thể dùng tag nào và FAM extent được kiểm tra ở boundary nào.
8. Representation nào chỉ để probe nội bộ, representation nào là external format field-by-field.

Stakeholder M05 cần source có invariant/test rõ. Nếu vector mất state khi `realloc` fail hoặc list double-insert corrupt links, package boundary sau chỉ đóng gói defect.

##### Cơ chế và mental model

**Byte-vector**

```text
data ──> [elem 0 bytes][elem 1 bytes]...[capacity]
          ^ offset = index × elem_size
len <= cap
bytes = cap × elem_size  (chỉ sau overflow check)
```

Reserve tính new capacity và byte count an toàn. `realloc` gán vào temporary; chỉ commit `data/cap` khi thành công. Push kiểm `len + 1` không wrap, reserve trước, rồi `memcpy` đúng `elem_size`. Mỗi vector instance nên chứa một element type/size nhất quán.

**Intrusive list**

```text
record A [id | active_link] <──> record B [id | active_link]
               │                         │
               └─ container_of ──────────┘ → enclosing record
```

Head sentinel nối vòng giúp empty/single/multi dùng cùng phép nối. Insert chỉ nhận node unlinked; remove nối hai neighbor rồi reset node. Khi remove trong iteration, phải lưu next trước khi unlink. Payload không được free khi node còn linked.

**Flags and representation**

```text
set:    state |= mask
clear:  state &= ~mask
toggle: state ^= mask
test:   (state & mask) == mask
valid:  (mask & ~ALLOWED_MASK) == 0
```

Dùng `UINT32_C(1) << bit` và kiểm `bit < 32` trước shift. External format encode field bằng mask/shift trên integers có width/endian contract; không `memcpy` bit-field/union struct ra wire.

**Tagged union và FAM**

Tag quyết định active member. Với FAM, header giữ `len`; allocated extent là oracle. Copy by value chỉ copy fixed header, vì vậy object FAM được quản lý qua pointer và explicit length.

##### Khi dùng / khi không dùng, giới hạn và trade-off

- Dùng byte-vector khi nhiều element types cần cùng algorithm và copy-by-value rõ. Dùng typed container khi type safety/destructor semantics quan trọng hơn reuse.
- Dùng macro cho constant-expression/token generation hoặc `_Generic` dispatcher nhỏ. Dùng `static inline`/function khi cần single evaluation, type checking và debugger-friendly call.
- Dùng intrusive list khi payload lifetime ổn định và cần O(1) unlink không cấp phát node riêng. Không dùng nếu caller cần một object tham gia số list động hoặc payload không kiểm soát lifetime; non-intrusive nodes đơn giản hơn.
- Dùng flags cho independent boolean capabilities; dùng enum/status riêng khi states mutually exclusive.
- Dùng bit-field cho register/internal compact representation khi compiler/ABI được khóa và có probe. Không dùng làm protocol/persistent layout.
- Dùng tagged union cho tập variants hữu hạn; dùng opaque bytes/serialization schema khi format ngoài process cần tiến hóa.
- Dùng FAM cho một allocation chứa header + variable payload; không dùng nếu payload cần resize độc lập/thường xuyên.

Trade-off cốt lõi: generic byte APIs giảm duplication nhưng chuyển type/ownership checks sang contract; intrusive structures giảm allocation nhưng ghép lifetime; representation tricks tiết kiệm space nhưng giảm portability.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** gateway cần lưu mẫu `uint16_t`, duyệt active records, giữ flags và tạo packet payload biến độ dài.
- **Input/baseline/constraint:** values `10,20,30`; records id `1,2`; flags enabled/verbose; payload `abc`; strict C17.
- **Decision/action:** byte-vector copy elements; intrusive circular list dùng embedded link; const-preserving container recovery; reject bit 31; tagged temperature union; overflow-safe FAM allocation.
- **Artifact/output:** [CMake project](assets/s04_case/CMakeLists.txt) và [source đầy đủ](assets/s04_case/s04_case.c).
- **Expected result:** vector giữ 3 values; list sum `3`; flags `0x00000005`; temperature `42`; packet `abc`; bit-field size chỉ gắn nhãn implementation-specific; final line `S04_CASE_PASS`.
- **Verification/oracle/evidence:** assertions, stdout golden fields, CTest exit 0, ASan+UBSan/Valgrind clean. Xem mục 4 và [example.md](example.md).

##### Ví dụ code cụ thể

Micro-example sau độc lập với Assignment 04: hai record synthetic nằm trên stack, mỗi record nhúng một `link`; chương trình khôi phục enclosing object bằng `offsetof`, dispatch phép kiểm flag qua C17 `_Generic` và chỉ đọc qua pointer `const`. Phạm vi cố ý nhỏ để oracle không phụ thuộc allocator hay raw layout của bit-field/union/FAM.

Lưu block thành `/tmp/s04_micro.c` trong workspace lab cô lập:

```c
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

struct link {
    struct link *next;
};

struct metric {
    int id;
    uint32_t flags;
    struct link active_link;
};

#define METRIC_ENABLED (UINT32_C(1) << 0)
#define CONTAINER_OF_CONST(ptr, type, member) \
    ((const type *)((const unsigned char *)(ptr) - offsetof(type, member)))

static int flag_test_u32(uint32_t value, uint32_t mask)
{
    return (value & mask) == mask;
}

#define FLAG_TEST(value, mask) \
    _Generic((value), uint32_t: flag_test_u32)((value), (mask))

static void push_front(struct link *head, struct link *node)
{
    node->next = head->next;
    head->next = node;
}

int main(void)
{
    struct link head = {.next = NULL};
    struct metric first = {
        .id = 10, .flags = METRIC_ENABLED, .active_link = {.next = NULL}
    };
    struct metric second = {
        .id = 32, .flags = 0, .active_link = {.next = NULL}
    };

    push_front(&head, &second.active_link);
    push_front(&head, &first.active_link);

    int count = 0;
    int id_sum = 0;
    int enabled = 0;
    for (const struct link *it = head.next; it != NULL; it = it->next) {
        const struct metric *metric =
            CONTAINER_OF_CONST(it, struct metric, active_link);
        ++count;
        id_sum += metric->id;
        enabled += FLAG_TEST(metric->flags, METRIC_ENABLED);
    }

    printf("count=%d id_sum=%d enabled=%d\n", count, id_sum, enabled);
    if (count != 2 || id_sum != 42 || enabled != 1) {
        return 1;
    }
    puts("S04_MICRO_PASS");
    return 0;
}
```

Biên dịch và chạy bằng warning profile của Unit:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror \
  /tmp/s04_micro.c -o /tmp/s04_micro
/tmp/s04_micro
echo $?
```

Kết quả mong đợi chính xác:

```text
count=2 id_sum=42 enabled=1
S04_MICRO_PASS
0
```

- **Quyết định:** intrusive link tránh cấp phát node phụ; `CONTAINER_OF_CONST` giữ qualifier khi traversal chỉ đọc; mask dùng `UINT32_C` để phép dịch nằm trên kiểu unsigned; `_Generic` chỉ dispatch tới typed function nên mỗi argument được đánh giá một lần.
- **Oracle/evidence:** strict compile phải exit `0` và không warning; binary chỉ pass khi count, tổng ID và số record enabled cùng đúng, sau đó exit `0`. Sai membership hoặc mask làm ít nhất một giá trị lệch và binary exit `1`.
- **Giới hạn/trade-off:** macro chỉ hợp lệ với exact `active_link` của object `struct metric` còn sống. Ví dụ không dùng raw bit-field/union bytes làm oracle vì layout đó không portable; các representation này vẫn được kiểm bằng logical behavior và probe đã nêu trong leaf.

##### Best practices

| Rule | Rationale/cơ chế | Ví dụ đúng | Phản ví dụ/hậu quả |
|---|---|---|---|
| API generic mang element size/count và ownership/null/zero contract. | `void *` không cung cấp stride, type hay destructor semantics. | `vector_init(v, sizeof(uint16_t))` và copy đúng bytes. | Hardcode stride hoặc lưu borrowed pointer mà caller tưởng đã copy. |
| Kiểm overflow trước cộng/nhân; `realloc` qua temporary và commit cuối. | Wrap tạo allocation nhỏ; gán thẳng làm mất old pointer khi fail. | Kiểm `cap > SIZE_MAX / 2` và `cap > SIZE_MAX / elem_size`. | `v->data = realloc(v->data, bytes)` rồi state/data mất khi null. |
| Macro parenthesize và không nhận side-effect argument; ưu tiên typed inline. | Replacement có thể evaluate zero/nhiều lần và không type-check như function. | `_Generic` dispatch tới `flag_test_u32`. | `MAX(i++, limit)` tăng `i` nhiều lần. |
| `container_of` chỉ nhận exact member của live object; có const variant/contract. | Wrong provenance/type/lifetime dẫn tới invalid address hoặc cast-away qualifier. | `CONTAINER_OF_CONST(const_node, struct record, active_link)`. | Dùng null, member của object đã free hoặc cast bỏ const. |
| Một link node chỉ thuộc một list; unlink trước free; safe iteration khi remove. | Intrusive links là state nằm trong payload. | `linked` guard và reset links sau remove. | Double insertion làm neighbor pointers bị ghi chồng/corrupt. |
| Bit operations dùng unsigned fixed width và validate mask/shift. | Signed/out-of-range shift gây undefined/implementation-defined behavior. | `UINT32_C(1) << bit` sau `bit < 32`. | `1 << 31` trên signed `int`. |
| Bit-field/union raw bytes không là external ABI; union có explicit tag. | Layout/active representation không portable. | Encode protocol bằng masks và byte order explicit. | `write(fd, &bits, sizeof bits)` hoặc đọc union member sai tag. |
| FAM ở cuối, extent overflow-safe, access theo stored length. | `sizeof` không bao gồm trailing elements; unchecked math gây OOB. | `len <= SIZE_MAX - sizeof(header)` trước allocation. | Allocate chỉ `sizeof(header)` rồi ghi `bytes[0]`. |

##### Anti-pattern, failure modes và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán/bằng chứng | Cách sửa | Phòng tránh |
|---|---|---|---|---|
| Vector content mất khi OOM | Gán `realloc` trực tiếp hoặc commit cap sớm. | Allocation-failure injection và compare pointer/state. | Temporary pointer, commit sau success. | Failure-atomic invariant test. |
| ASan báo heap-buffer-overflow | Size multiplication/addition wrap hoặc index ≥ len. | Stack + values `len/cap/elem_size`. | Checked arithmetic và boundary guard. | n=0/1/max/overflow fixtures. |
| List loop vô hạn/corrupt | Double insert, foreign removal hoặc free khi linked. | Forward/backward invariant walk. | Membership guard, unlink/reset đúng. | Explicit linked state và lifecycle review. |
| `container_of` address sai | Sai member/type hoặc member pointer không thuộc live object. | So enclosing/member addresses ở valid fixture. | Chỉ gọi trong documented preconditions. | Typed wrappers/const variants, không support invalid input. |
| Reserved flag âm thầm xuất hiện | Không validate unknown mask. | Truth table với boundary/reserved bits. | Reject hoặc preserve theo documented policy. | Central allowed mask. |
| Layout probe khác compiler | Bit-field representation implementation-defined. | Ghi compiler/target/`sizeof`; không compare raw bytes portable. | Đổi oracle sang logical field behavior. | Không dùng raw layout ngoài implementation-locked boundary. |
| FAM payload hỏng | Allocate/copy thiếu trailing extent. | ASan + length/allocated-byte evidence. | Checked header+payload math, pointer-only lifecycle. | Central constructor và max-length contract. |

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### Input/trạng thái ban đầu

[assets/s04_case](assets/s04_case/CMakeLists.txt) là một executable C17 tự chứa. Input cố định: ba `uint16_t`, hai records, flag mask, tagged reading và ba payload bytes.

### Cách thực hiện

Case lần lượt kiểm byte-vector, intrusive list/container recovery, unsigned flags/`_Generic`, tagged union, FAM và bit-field probe. Assertions là behavioral oracle; stdout chỉ công bố logical values, còn bit-field output mang nhãn implementation-specific.

### Output mong đợi

```text
vector=10,20,30
list_id_sum=3 flags=0x00000005
reading_temperature=42 packet=abc
layout_probe_bytes=<implementation-specific>
S04_CASE_PASS
```

Giá trị `layout_probe_bytes` có thể khác implementation; chỉ yêu cầu là một số hợp lệ kèm nhãn, không dùng exact size làm cross-platform oracle.

### Cách xác minh

```bash
cmake -S assets/s04_case -B /tmp/s04-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build /tmp/s04-debug
ctest --test-dir /tmp/s04-debug --output-on-failure
/tmp/s04-debug/s04_generic_case

cmake -S assets/s04_case -B /tmp/s04-asan \
  -DCMAKE_C_COMPILER=clang-14 \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_C_FLAGS='-O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined' \
  -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined'
cmake --build /tmp/s04-asan
ASAN_OPTIONS=halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir /tmp/s04-asan --output-on-failure

valgrind --tool=memcheck --leak-check=full \
  --errors-for-leak-kinds=definite,indirect --error-exitcode=99 \
  /tmp/s04-debug/s04_generic_case
```

ASan+UBSan và Valgrind chạy trên binary riêng. Không chạy Valgrind trên sanitizer binary.

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

- Nếu compiler báo arithmetic trên `void *`, chuyển qua `unsigned char *`; không bật GNU extension để che portable-C defect.
- Nếu `_Generic` chọn sai association, kiểm exact type sau qualifiers/promotions; giữ dispatcher nhỏ và typed functions riêng.
- Nếu list test chỉ pass khi không remove, kiểm membership/lifetime và iteration rule trước khi nghi compiler.
- Nếu bit mask test sai ở high bit, kiểm literal unsigned và shift range.
- Nếu union output ngẫu nhiên, kiểm tag có khớp active member và member đã được khởi tạo.
- Nếu FAM `sizeof` nhỏ hơn kỳ vọng, đó là thiết kế: trailing payload không nằm trong `sizeof`; kiểm allocation extent.
- CERT rules phù hợp: ARR/INT cho size/index arithmetic, MEM cho allocation/lifetime, PRE31-C cho unsafe macro argument evaluation.

## 6. Từ điển thuật ngữ và mô hình tư duy

- **Element stride:** số bytes từ một element tới element kế tiếp.
- **Failure atomicity:** operation fail nhưng state trước operation vẫn hợp lệ/không mất dữ liệu.
- **Shallow copy:** copy bytes/pointer values, không nhân bản object được trỏ tới.
- **Intrusive node:** link metadata embedded trong payload.
- **Sentinel:** node đại diện head/end, giúp giảm special case.
- **Qualifier contract:** cam kết không cast-away `const`/`volatile` ngoài policy.
- **Reserved mask:** bits không được caller hiện tại tự đặt.
- **Active member:** union member tương ứng tag/được ghi hợp lệ.
- **Object representation:** bytes biểu diễn object, có thể chứa padding/implementation-specific layout.
- **Allocated extent:** số bytes thật được cấp cho header + FAM payload.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

Các nguồn ở mục “Nguồn đầu vào đã map” được dùng ở chế độ reference/paraphrase. Compiler/runtime scope: C17, glibc 2.35, GCC 11.4, Clang 14, CMake 3.22.1 và Valgrind 3.18.1.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — project plan đã được phê duyệt]** Gateway, stakeholder và chuỗi M03→M04→M05 là project spine mô phỏng.
- **[BỔ SUNG — nguồn: Linux linked-list documentation]** Intrusive-list pattern được tham khảo ở mức cơ chế; macro/source của kernel không được sao chép vào asset userspace.
- **[BỔ SUNG — nguồn: GNU C/GCC/Clang scope]** `container_of` là idiom có preconditions/compiler-target contract, không được trình bày như primitive ISO C độc lập.
- Asset `s04_case.c` là implementation đào tạo nguyên bản; bit-field probe chỉ thu evidence implementation-specific.

---

# Session S04: Session 04 — Generic programming and bit-level C — Ví dụ và nghiên cứu tình huống

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 02 — Abstract Data Types, Generic Programming & Bit-level C

## 🎯 Learning Outcomes liên quan

- **ADVC-H1SD** [create] — Thiết kế, hiện thực và kiểm chứng module C17 dùng generic containers, embedded links và representation contracts mà không gây lỗi memory trong fixtures.
- Case kết nối OUT-S04-01 với một executable oracle, sanitizer/Valgrind commands và portability note.

## 🧭 Liên kết với ngữ cảnh nghề nghiệp/dự án

- **Baseline:** Opaque event ring core v3 đã có ownership/error contract.
- **Increment minh họa:** adapter quản lý samples, active records, flags và variable-size packet.
- **Artifact:** [`assets/s04_case`](assets/s04_case/CMakeLists.txt).
- **Phạm vi:** case GRC-04 dùng dữ liệu nhỏ và API nội bộ khác CR-A04. Assignment 04 đòi đầy đủ reserve/push/access/remove/shrink/destroy, multi-size tests và integration regressions; không nộp lại asset mẫu.

## 🧰 Điều kiện chạy ví dụ

- Ubuntu 22.04 native/VM/WSL2.
- CMake 3.22.1; GCC 11.4 hoặc Clang 14; C17 strict; Valgrind 3.18.1.
- Không có external library, service hoặc network.
- Build/debug, ASan+UBSan và Valgrind dùng binary/directory riêng.

## 📚 Nguồn đầu vào đã map

- C17/WG14 N2176; GNU C manual; glibc 2.35 allocation documentation.
- Linux linked-list documentation ở mức pattern; GCC 11/Clang 14/Valgrind manuals.
- CERT C và syllabus nội bộ v1.0.

### Mapping case đã chốt trong course plan

| Case | Outline | LO | Input cụ thể | Output/oracle |
|---|---|---|---|---|
| CASE-S04-01 / GRC-04 | OUT-S04-01 | ADVC-H1SD | `uint16_t {10,20,30}`, records id 1/2, masks, tagged reading, FAM payload `abc` | Assertions pass; logical stdout đúng; layout chỉ implementation-specific; `S04_CASE_PASS` |

## Case Study 01: Ticket GRC-04 — Generic registry không đánh đổi ownership và portability

### 1. Ticket và tiêu chí thành công

Gateway prototype đang nhân bản logic cho từng type và lưu raw representation của flags/payload. Core maintainer yêu cầu một proof-of-contract:

1. Một byte-vector copy ba `uint16_t` và giữ `len <= cap`.
2. Reserve failure không làm mất pointer/data/`len/cap`.
3. Hai records tham gia intrusive list đúng order; double insertion bị reject; enclosing record được phục hồi mà không cast-away const.
4. Flag registry chỉ nhận allowed unsigned mask.
5. Tagged union chỉ đọc member khớp tag.
6. FAM hỗ trợ payload 0 và 3 bytes, reject overflow extent.
7. Bit-field chỉ được probe và ghi nhãn implementation-specific.
8. CTest, ASan+UBSan và Valgrind có oracle rõ.

### 2. Input, trạng thái ban đầu và ràng buộc

Asset:

```text
assets/s04_case/
├── CMakeLists.txt
└── s04_case.c
```

Input cố định:

- samples: `10U, 20U, 30U` kiểu `uint16_t`;
- records: id `1` và `2`, mỗi record có `active_link`;
- flags hợp lệ: ENABLED (bit 0), DIAGNOSTIC (bit 1), VERBOSE (bit 2);
- reading: tag TEMPERATURE, value `42`;
- packet: type `7`, payload bytes `a b c`.

Ràng buộc:

- ISO C17 strict, không arithmetic trên `void *`.
- Generic vector copy bytes; không sở hữu object được pointer element trỏ tới.
- `container_of` chỉ nhận exact embedded member của live record; case có const-preserving macro riêng.
- Bit 31 là unknown và phải bị reject.
- Không so raw bit-field bytes hoặc `sizeof` như portable golden value.
- FAM ở cuối; header + payload arithmetic phải reject overflow.

### 3. Phân tích lựa chọn

| Lựa chọn | Ưu điểm | Giới hạn | Quyết định |
|---|---|---|---|
| Một vector typed cho `uint16_t` | Type-safe | Nhân bản algorithm cho type khác | Không chọn cho proof generic |
| Byte-vector `void *` + `elem_size` | Reuse, C17 thuần | Contract/type/ownership do caller đảm bảo | Chọn |
| Macro expression cho mọi operation | Ngắn | Multiple evaluation, khó debug | Không; dùng function + `_Generic` dispatcher nhỏ |
| Intrusive list | Không cấp node riêng, O(1) unlink | Ghép payload lifetime/membership | Chọn cho active records |
| Bit-field làm flag storage/wire | Cú pháp gọn | Layout implementation-defined | Không; flags dùng `uint32_t` mask |
| Tagged union | Compact variant, explicit state | Caller phải duy trì tag | Chọn |
| FAM | Header+payload một allocation | Resize/copy phức tạp | Chọn cho immutable packet |

Failure-atomic reserve được kiểm bằng allocator hook chỉ dùng trong case: lần allocation kế tiếp trả null, sau đó assertions so state trước/sau. Production code có thể inject allocator theo cách khác; oracle không phụ thuộc implementation cụ thể.

### 4. Cách triển khai

#### 4.1 Byte-vector và checked arithmetic

Data model:

```c
struct byte_vector {
    unsigned char *data;
    size_t len;
    size_t cap;
    size_t elem_size;
};
```

`vector_reserve` tăng capacity theo bội hai, kiểm `SIZE_MAX / 2` và `SIZE_MAX / elem_size`, gọi realloc qua temporary rồi mới commit. `vector_push` kiểm `len == SIZE_MAX` trước `len + 1` và `memcpy` đúng element size. [Xem implementation đầy đủ](assets/s04_case/s04_case.c).

Failure oracle:

```c
void *data_before = vector.data;
size_t len_before = vector.len;
size_t cap_before = vector.cap;

fail_next_allocation = true;
assert(!vector_reserve(&vector, cap_before + 1U));
assert(vector.data == data_before);
assert(vector.len == len_before);
assert(vector.cap == cap_before);
```

#### 4.2 Intrusive list và qualifier-aware recovery

Payload sở hữu embedded link:

```c
struct record {
    int id;
    struct list_node active_link;
};
```

Const recovery:

```c
#define CONTAINER_OF_CONST(member_pointer, type, member) \
    ((const type *)((const unsigned char *)(member_pointer) - \
                    offsetof(type, member)))
```

Node có explicit `linked` state. Insert tail reject node đã linked; remove reconnect neighbors rồi reset node. Khi loop chỉ đọc, `const struct list_node *` đi vào const variant và trả `const struct record *`.

#### 4.3 Unsigned flags và `_Generic`

Allowed mask gồm ba low bits. `flags_set` reject `mask & ~ALLOWED_MASK` khác 0. Dispatcher:

```c
#define FLAG_TEST(state, mask) \
    _Generic((state), uint32_t: flag_test_u32)((state), (mask))
```

Typed function thực hiện comparison; case không truyền expression có side effect vào macro.

#### 4.4 Tagged union, FAM và layout boundary

Reading ghép `enum reading_kind` với union. Case ghi/đọc `temperature` chỉ khi tag TEMPERATURE. Packet:

```c
struct packet {
    uint16_t type;
    size_t len;
    unsigned char bytes[];
};
```

Constructor reject `len > SIZE_MAX - sizeof(*packet)`, allocate header + len, và chỉ copy khi len khác 0. Fixture kiểm n=0, n=3 và overflow. `struct layout_probe` có bit-fields nhưng chỉ in `sizeof` cùng nhãn “implementation-specific”; raw bytes không được serialize.

#### 4.5 Build description

[CMakeLists.txt](assets/s04_case/CMakeLists.txt) pin minimum 3.22, C17, no extensions, warnings-as-errors và đăng ký `s04_generic_contract` với CTest.

### 5. Output mong đợi

```text
vector=10,20,30
list_id_sum=3 flags=0x00000005
reading_temperature=42 packet=abc
layout_probe_bytes=<implementation-specific>
S04_CASE_PASS
```

Các assertions không in ra nhưng bắt buộc pass: allocation failure giữ state, double insert/unknown flag bị reject, empty/overflow FAM đúng contract, remove thành công. `<implementation-specific>` là một số tùy compiler/ABI; không hardcode.

### 6. Cách xác minh

Debug/CTest:

```bash
cmake -S assets/s04_case -B /tmp/s04-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build /tmp/s04-debug
ctest --test-dir /tmp/s04-debug --output-on-failure
/tmp/s04-debug/s04_generic_case
```

ASan+UBSan:

```bash
cmake -S assets/s04_case -B /tmp/s04-asan \
  -DCMAKE_C_COMPILER=clang-14 \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_C_FLAGS='-O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined -fno-sanitize-recover=all' \
  -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined'
cmake --build /tmp/s04-asan
ASAN_OPTIONS=halt_on_error=1:detect_leaks=1 \
UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
ctest --test-dir /tmp/s04-asan --output-on-failure
```

Valgrind chạy debug binary riêng:

```bash
valgrind --tool=memcheck --leak-check=full \
  --errors-for-leak-kinds=definite,indirect \
  --error-exitcode=99 \
  /tmp/s04-debug/s04_generic_case
```

Pass oracle:

| Gate | Kết quả |
|---|---|
| Configure/build | exit 0, warning count 0 |
| CTest | 1/1 test pass |
| Program | logical fields đúng và final marker `S04_CASE_PASS` |
| ASan+UBSan | exit 0, không finding thuộc asset |
| Valgrind | 0 invalid access, 0 definite/indirect leak |
| Portability review | layout line có nhãn implementation-specific; không có raw serialization |

### 7. Giải thích sâu và failure modes

- **`realloc` failure làm leak/mất data:** implementation đã gán trực tiếp vào field. Dùng temporary và chỉ commit khi non-null.
- **Byte offset sai:** arithmetic dùng element count trên `unsigned char *` mà quên nhân `elem_size`. So golden values và chạy ASan.
- **Double insertion không bị reject:** node thiếu membership state; list links có thể corrupt dù test order ngắn vẫn trông đúng.
- **`container_of` compile warning cast-away const:** caller dùng macro mutable với const member pointer. Dùng const variant/contract.
- **Unknown bit xuất hiện:** allowed-mask check thiếu hoặc complement có signed type. Cast/use `uint32_t` xuyên suốt.
- **Union đọc sai:** tag không khớp active member. Validate tag trước dispatch; không dùng raw bytes làm oracle.
- **FAM n=0 fail:** constructor cấm null bytes vô điều kiện. Null pointer được phép khi len 0 theo contract.
- **Layout size khác expected:** không phải defect nếu logical fields hoạt động; defect là dùng exact size/raw bytes như portable ABI.

Trade-off: byte-vector linh hoạt nhưng không kiểm static type; intrusive list tiết kiệm allocation nhưng buộc lifecycle discipline; tagged union/FAM giảm allocation nhưng cần constructor/bounds; explicit masks dài hơn bit-field nhưng portable hơn cho external format.

### 8. Bài học chuyển giao

1. Generic API luôn mang byte, type-use và ownership contract rõ.
2. Failure path là một phần state machine; `realloc` phải failure-atomic.
3. `container_of` là phép phục hồi có preconditions, không phải phép cast tùy ý.
4. Intrusive list ownership thuộc payload; membership phải quan sát được.
5. Bit-field/union representation không được lén trở thành wire ABI.
6. FAM allocation và length phải đi cùng nhau.
7. Assignment 04 đòi một increment M04 khác và regression A01–A03; asset case không phải starter solution.

## Provenance của các case

### Nguồn được dùng

- C17/WG14 N2176, GNU C/glibc manuals, Linux linked-list documentation, GCC/Clang/Valgrind manuals và CERT C.
- Syllabus nội bộ v1.0 cho OUT-S04-01, ADVC-H1SD và project inputs.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — project plan đã được phê duyệt]** Ticket GRC-04 và gateway registry là bối cảnh mô phỏng.
- **[BỔ SUNG — Linux list pattern]** Case hiện thực intrusive list userspace nguyên bản; không sao chép kernel macros.
- **[BỔ SUNG — compiler-target scope]** `container_of` được dạy cùng exact-member/live-object/qualifier preconditions.
- Asset dùng allocator hook file-private để có deterministic failure oracle; đây là technique của case, không áp đặt kiến trúc Assignment.

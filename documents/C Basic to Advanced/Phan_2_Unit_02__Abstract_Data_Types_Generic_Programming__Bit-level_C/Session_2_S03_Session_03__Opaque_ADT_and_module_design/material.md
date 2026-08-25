# Session S03: Session 03 — Opaque ADT and module design — Học liệu cốt lõi

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 02 — Abstract Data Types, Generic Programming & Bit-level C

## 🎯 Learning Outcomes
- **ADVC-H1SD** [create] — Thiết kế, hiện thực và kiểm chứng các mô-đun C17 dùng con trỏ nâng cao, quản lý bộ nhớ động, ADT đóng gói và cấu trúc dữ liệu generic mà không làm lộ ownership hoặc gây lỗi bộ nhớ trong các ca kiểm thử đã cho. · Bằng chứng: Public API/header và implementation C biên dịch với warning profile đã chốt; unit tests đạt; sanitizer hoặc Valgrind không báo lỗi thuộc phạm vi fixture.

## 🧭 Ngữ cảnh nghề nghiệp/dự án và phần tăng trưởng của Unit

**Bối cảnh nghề nghiệp/dự án:**
**MDB Edge Diagnostics Gateway — Simulated** — Cổng chẩn đoán và telemetry chạy local trên Linux cho thiết bị giả lập; tiếp nhận command, quản lý work records, thực thi backend process/thread và phục vụ protocol TCP loopback. Vai trò học viên: C systems developer chịu trách nhiệm phát triển và harden từng increment trong repository đào tạo. Mục tiêu: Bàn giao một gateway TCP loopback tích hợp core C17, process/thread backends và quality evidence; phục vụ ít nhất 100 client synthetic theo Assignment 09 mà không có finding mức chặn trong oracle áp dụng.

**Project increment sau Unit này:**
- **milestone_id:** M03
- **user_story:** Là maintainer, tôi muốn đệm event được cung cấp qua opaque handle và API contract ổn định để caller không phụ thuộc representation hoặc tự sửa ring state.
- **business_value:** Tách representation khỏi client, khóa ownership/error behavior và tạo FIFO event boundary có thể thay implementation mà không đổi public API.
- **baseline:** Memory-safe command core v2 đã qua M02.
- **change_scope:** - Opaque event-ring public API<br>- Private representation and file-local helpers<br>- FIFO empty/full/wrap-around behavior<br>- Defensive parameter and failure-state checks<br>- Ownership, lifetime and thread-safety contract<br>- A02 regression and memory-safety evidence
- **inputs:** - Memory-safe command core v2<br>- DC-EVENT<br>- Synthetic command and telemetry fixtures<br>- Public contract pack
- **integration_points:** - memory pool<br>- opaque event ring<br>- command dispatcher
- **artifacts_added:** - Opaque event ring core v3<br>- A03 API contract and test evidence
- **acceptance_criteria:** - FR-03 đạt<br>- NFR-01 và NFR-02 đạt<br>- M01–M02 behavior không regression<br>- Public header không lộ representation
- **definition_of_done:** - Project Definition of Done áp dụng cho M03

**Mức xác thực của bối cảnh:** simulated

Sau S03, học viên có thể thiết kế boundary mô-đun C17 thay vì chỉ viết một `struct`: public header self-contained với incomplete type, implementation private/internal linkage, status và failure-state nhất quán, ownership/invalidation/thread-safety được công bố và kiểm bằng lifecycle fixtures. Năng lực ADVC-H1SD tạo Opaque event ring core v3, được ASM-A04 tiêu thụ.

## 📚 Nguồn đầu vào đã map
- SRC-SYL — L2_MBD_ADVC_Syllabus_v1.0 1.xlsx: D:\Workspaces\FR_DN26_MBD_Simulink\L2_MBD_ADVC_Syllabus_v1.0 1.xlsx (publisher: Internal training syllabus; version: 1.0; accessed_at: 2026-08-21; license: internal_approved for this requested training-content generation; allowed_use: internal_approved)
- SRC-C17-ISO — ISO/IEC 9899:2018 — Programming languages — C: https://www.iso.org/standard/74528.html (publisher: ISO/IEC JTC 1/SC 22; version: Edition 4, C17, 2018; accessed_at: 2026-08-21; license: ISO copyright; metadata and clause references only, no reproduction; allowed_use: reference)
- SRC-C17-WG14 — WG14 N2176 proposed C17 committee draft: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2176.pdf (publisher: ISO/IEC JTC 1/SC 22/WG14; version: N2176, 2017-10-09; non-final public committee document; accessed_at: 2026-08-21; license: Publicly accessible committee document; link and paraphrase only; allowed_use: reference)
- SRC-GNUC — GNU C Language Manual: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/index.html (publisher: GNU Project / Free Software Foundation; version: rolling manual as accessed; C17 scope constrained by plan; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-CERTC — SEI CERT C Coding Standard: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/ (publisher: Carnegie Mellon University Software Engineering Institute; version: online work-in-progress snapshot as accessed; claims constrained to C17; accessed_at: 2026-08-21; license: CMU/SEI terms; reference and limited quotation only; allowed_use: reference)
- SRC-LINUX-CIRC — Circular Buffers: https://docs.kernel.org/core-api/circular-buffers.html (publisher: Linux Kernel documentation project; version: mainline documentation as accessed; fixed-ring pattern only; accessed_at: 2026-08-21; license: Linux kernel documentation terms; paraphrase only; allowed_use: reference)
- SRC-GCC11 — GCC 11.4 manuals: https://gcc.gnu.org/onlinedocs/gcc-11.4.0/ (publisher: GNU Project / Free Software Foundation; version: 11.4.0; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-LLVM14 — LLVM/Clang 14.0.0 Documentation: https://releases.llvm.org/14.0.0/tools/clang/docs/index.html (publisher: LLVM Project; version: 14.0.0; accessed_at: 2026-08-21; license: Apache-2.0 WITH LLVM-exception; allowed_use: reference)
- SRC-VALGRIND318 — Valgrind Memcheck Manual: https://valgrind.org/docs/manual/mc-manual.html (publisher: Valgrind Developers; version: 3.18.1 Ubuntu baseline; options constrained to that release; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.2 or later; allowed_use: reference)

> Đây là khu vực provenance. Khi viết nội dung, tiêu hóa thông tin từ nguồn và trình bày độc lập; không chèn tên file nguồn vào câu văn kỹ thuật. Nguồn bổ sung hoặc phần suy diễn phải được ghi riêng tại mục 7.

---

## 1. Kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết
- **knowledge:** - Pointer, allocation, alignment and ownership/reset contracts from S01–S02
- **skills:** - Build and run CTest plus a separate sanitizer or Valgrind oracle
- **completed_units:** - s02
- **assets:** - starter/assignment-03/README.md

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

Chạy `gcc --version`, `cmake --version`, `valgrind --version`; sau đó biên dịch cả translation units của ví dụ: `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -g assets/event_ring.c assets/event_ring_demo.c -o /tmp/s03_ring`. Baseline đạt khi `/tmp/s03_ring` exit `0` và in `S03 RING PASS`; Valgrind hoặc sanitizer chạy trên binary tách biệt.

## 2. Định vị trong lộ trình (Mental Map)

S01 cung cấp pointer/callback contract; S02 cung cấp allocation, lifetime và reset invariant. S03 đặt các quyết định đó sau một API ổn định: client thấy capability, không thấy representation. M03 tạo FIFO event boundary mà implementation có thể thay đổi không buộc consumer sửa source. S04 sẽ dùng core v3 trong generic containers/bit-level contract, nên ownership và status phải được khóa trước.

## 3. Nội dung lý thuyết cốt lõi

**Phạm vi nội dung:**
- [x] Modular design in C: opaque pointer / handle-based ADT, header vs implementation, internal linkage, API contract, error-code convention, ownership rules

Leaf dưới đây giữ nguyên văn syllabus và truy vết tới ADVC-H1SD/M03; opaque boundary, linkage, contract, status và ownership được kiểm cùng một lifecycle oracle.


#### OUT-S03-01 Modular design in C: opaque pointer / handle-based ADT, header vs implementation, internal linkage, API contract, error-code convention, ownership rules

**Mapping:** OUT-S03-01 · ADVC-H1SD · M03 — Opaque event ring core v3 và API/lifecycle evidence.

##### Định nghĩa rõ ràng
ADT mô tả tập giá trị và operation hợp lệ, không yêu cầu client biết representation. Trong C, public header có thể `typedef struct event_ring event_ring;`: đây là incomplete type, nên client có thể giữ `event_ring *` nhưng không thể `sizeof`, dereference hay đặt object theo value. Implementation file hoàn thiện `struct event_ring` và định nghĩa operation. `static` ở file scope cho function/object internal linkage, tránh export private helper; nó không đồng nghĩa với storage trên stack hay thread safety.

API contract gồm type/prototype, nullability, precondition, postcondition, success/error output, state-on-error, capacity semantics, ownership/lifetime/invalidation và concurrency guarantee. Error-code convention dùng một status type explicit, tách output qua parameter; `errno` chỉ có ý nghĩa nếu API công bố và return value báo lỗi. Ownership trả lời ai cấp/giải phóng, payload copy hay borrow, reference sống đến khi nào. Handle không tự động là an toàn; dùng sau destroy vẫn là dangling use.

##### Vấn đề/vai trò và quyết định cần đưa ra
Client của gateway không được sửa `head/tail/count` hoặc phụ thuộc backing storage; maintainer phải thay implementation mà giữ public API. Học viên quyết định boundary header/implementation, count-based hay sentinel capacity, status enum, null/error state, copy-versus-borrow payload, reset/destroy invalidation và thread-safety claim. Reviewer cần negative compile probe và executable lifecycle oracle, không chỉ đọc comment.

##### Cơ chế và mental model
Public header là capability surface; translation unit client chỉ biết tag/incomplete type. Factory nhận `event_ring **out`, validate và chỉ publish handle sau khi toàn bộ allocation thành công; destroy thu hồi owned storage. Trong count-based ring, invariant là `0 ≤ count ≤ capacity`; `head` chỉ phần tử đọc tiếp, `tail` chỉ slot ghi tiếp, index quay về `0` sau `capacity-1`. Push full và pop empty trả status trước mutation; copy payload tách lifetime event trong ring khỏi object input. Private helper `advance_index` dùng internal linkage.

##### Khi dùng / khi không dùng
Dùng opaque heap handle khi representation cần giấu, kích thước có thể đổi và lifecycle đi qua factory/destructor. Dùng caller-supplied storage hoặc public value type nếu allocation bị cấm và representation ổn định là phần contract; khi đó opaque pointer có thể không phù hợp. Dùng explicit status cho library/domain error có nhiều nhánh cần test. Không đọc `errno` sau success hoặc khi API không hứa dùng `errno`. Không tuyên bố thread-safe/lock-free chỉ vì field private; shared handle vẫn cần synchronization design.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng
- **Context/stakeholder:** command core v2 cần FIFO ba event, client không được chạm ring state.
- **Input/baseline/constraint:** event `{id,value}`, capacity public đúng ba; test zero capacity, empty/full, wrap, null, reset, destroy; payload được copy; external synchronization.
- **Decision/action:** forward declaration trong [event_ring.h](assets/event_ring.h), representation/helper private trong [event_ring.c](assets/event_ring.c), count-based state, enum status và publish-on-success factory.
- **Artifact/output:** public header, implementation và [event_ring_demo.c](assets/event_ring_demo.c).
- **Expected result:** client build bình thường; FIFO sequence `1,2,3,4` qua wrap; full/empty/null status đúng; stdout `S03 RING PASS`.
- **Verification/oracle/evidence:** warning-free multi-file build, assertion/lifecycle fixture, expected-failure opacity probe, ASan+UBSan hoặc Valgrind riêng.

##### Ví dụ code cụ thể

Lưu ba phần dưới đây lần lượt thành `/tmp/meter.h`, `/tmp/meter.c` và `/tmp/s03_opaque_micro.c`. Micro-ADT quản lý một giá trị bounded; nó không dùng event, FIFO, capacity, wrap-around hay adapter của ASM-A03.

`/tmp/meter.h`:

```c
#ifndef METER_H
#define METER_H

typedef struct meter meter;

typedef enum {
    METER_OK = 0,
    METER_BAD_ARGUMENT,
    METER_RANGE,
    METER_NO_MEMORY
} meter_status;

meter_status meter_create(int initial_value, meter **out_meter);
meter_status meter_add(meter *handle, int delta, int *out_value);
void meter_destroy(meter *handle);

#endif
```

`/tmp/meter.c`:

```c
#include "meter.h"

#include <stdlib.h>

struct meter {
    int value;
};

static int value_is_valid(int value)
{
    return value >= 0 && value <= 100;
}

meter_status meter_create(int initial_value, meter **out_meter)
{
    meter *created;

    if (out_meter == NULL) {
        return METER_BAD_ARGUMENT;
    }
    *out_meter = NULL;
    if (!value_is_valid(initial_value)) {
        return METER_RANGE;
    }

    created = malloc(sizeof *created);
    if (created == NULL) {
        return METER_NO_MEMORY;
    }
    created->value = initial_value;
    *out_meter = created;
    return METER_OK;
}

meter_status meter_add(meter *handle, int delta, int *out_value)
{
    int candidate;

    if (handle == NULL || out_value == NULL) {
        return METER_BAD_ARGUMENT;
    }
    if (delta < -10 || delta > 10) {
        return METER_RANGE;
    }

    candidate = handle->value + delta;
    if (!value_is_valid(candidate)) {
        return METER_RANGE;
    }
    handle->value = candidate;
    *out_value = candidate;
    return METER_OK;
}

void meter_destroy(meter *handle)
{
    free(handle);
}
```

`/tmp/s03_opaque_micro.c`:

```c
#include "meter.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    meter *handle = NULL;
    int value = -1;
    int rejected;

    assert(meter_create(4, &handle) == METER_OK && handle != NULL);
    assert(meter_add(handle, 5, &value) == METER_OK && value == 9);
    rejected = meter_add(handle, 20, &value) == METER_RANGE;
    assert(rejected && value == 9);
    assert(meter_add(handle, 0, &value) == METER_OK && value == 9);

    printf("S03_OPAQUE_MICRO value=%d rejected=%d\n", value, rejected);
    meter_destroy(handle);
    return 0;
}
```

Trong `ENV-ADV-C-JAMMY`, biên dịch và chạy:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -I/tmp \
  /tmp/meter.c /tmp/s03_opaque_micro.c -o /tmp/s03_opaque_micro
/tmp/s03_opaque_micro
```

- **Compile oracle:** stdout rỗng, stderr rỗng, exit code `0`.
- **Run oracle:** stdout `S03_OPAQUE_MICRO value=9 rejected=1` và một ký tự xuống dòng; stderr rỗng; exit code `0`.

Header chỉ forward-declare `meter`, nên client giữ handle nhưng không thấy representation; complete type và helper `static` chỉ tồn tại trong implementation. Factory đặt `*out_meter = NULL` trước validation và chỉ publish sau allocation thành công, làm ownership/error contract quan sát được. `meter_add` kiểm range trước mutation, vì vậy lần cộng `20` trả `METER_RANGE` và giá trị vẫn là `9`; assertion và stdout là oracle failure-atomic. `meter_destroy` kết thúc ownership của implementation, còn domain khác ring/FIFO giữ micro-example tách khỏi lời giải Assignment.

##### Best practices
- **Rule:** public header forward-declare type và self-contained. **Rationale:** client không thể phụ thuộc representation; include order không che dependency. **Positive:** header tự include `stddef.h/stdint.h`. **Negative/hậu quả:** complete struct/public private helper làm thay layout phá consumer.
- **Rule:** validate đầy đủ trước mutation/publish. **Rationale:** error path giữ state và owner rõ. **Positive:** factory đặt `*out=NULL`, allocate xong mới gán handle. **Negative/hậu quả:** publish một nửa object khiến caller destroy state lỗi.
- **Rule:** một status enum, output tách khỏi status. **Rationale:** exhaustive tests và không nhầm data hợp lệ với lỗi. **Positive:** `RING_EMPTY` và `out_event`. **Negative/hậu quả:** trả sentinel event hoặc đọc stale `errno`.
- **Rule:** ghi ownership/invalidation/copy-borrow. **Rationale:** signature không biểu diễn đầy đủ lifetime. **Positive:** ring sở hữu backing storage và copy event; destroy invalid handle. **Negative/hậu quả:** caller free borrowed pointer hoặc dùng handle sau destroy.
- **Rule:** claim concurrency chỉ bằng design/oracle. **Rationale:** private fields vẫn data race khi truy cập đồng thời. **Positive:** “not thread-safe; caller synchronizes”. **Negative/hậu quả:** ghi “thread-safe” không mutex/atomic/test.

##### Anti-pattern, failure modes và troubleshooting
Client compile được `sizeof(event_ring)`: representation đã lộ; grep public header, giữ chỉ forward declaration và thêm expected-failure probe. Ring mất event sau wrap: log `(head,tail,count)` trước/sau mỗi operation, so invariant và capacity model; sửa advance/mutation order. Allocation failure để `out` trỏ rác: inject failure, kiểm `*out==NULL`; validate/publish atomically. Status đúng nhưng state đổi ở push-full/pop-empty: snapshot size/peek trước/sau; đưa validation trước mutation. Race report ở shared handle: contract đang là external synchronization; thêm khóa ở caller hoặc thiết kế/test synchronization trước khi nâng guarantee.


## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

Ví dụ nối opaque type, header hygiene, internal linkage, factory ownership, explicit status và count-based FIFO. Nó là solution của case học tập, không phải reference implementation cho ASM-A03.

### Input/trạng thái ban đầu
Capacity `3`; bốn event `{1,10}`…`{4,40}`; zero-capacity create, pop-empty, push-full, null handle/element, one pop rồi wrap push, FIFO drain, reset và destroy.

### Cách thực hiện
Biên dịch [event_ring.c](assets/event_ring.c) cùng [event_ring_demo.c](assets/event_ring_demo.c) qua public [event_ring.h](assets/event_ring.h). Chạy assertion fixture; riêng opacity probe thử `sizeof(event_ring)` phải bị compiler từ chối.

### Output mong đợi
Positive build/run exit `0`, stdout `S03 RING PASS`; full push giữ size `3`; wrap trả sequence `1,2,3,4`; null/empty trả documented status. Negative opacity probe compile nonzero vì type incomplete; checker không có finding.

### Cách xác minh
- `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -g assets/event_ring.c assets/event_ring_demo.c -o /tmp/s03_ring && /tmp/s03_ring`
- `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer assets/event_ring.c assets/event_ring_demo.c -o /tmp/s03_ring_san && /tmp/s03_ring_san`
- Oracle: hai positive runs exit `0`, stdout khớp, sanitizer không finding; opacity probe được mô tả chi tiết trong Example và phải compile fail.

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

| Dấu hiệu | Nguyên nhân | Chẩn đoán/bằng chứng | Khắc phục | Phòng tránh |
|---|---|---|---|---|
| Consumer phụ thuộc `head/tail` | Complete struct lộ trong header | Opacity compile probe | Chuyển definition vào implementation | Forward declaration + public-header review |
| Push-full làm FIFO đổi | Validate sau mutation | Snapshot size/peek trước/sau | Check full trước ghi/tăng index | Failure-atomic fixtures |
| Create fail rồi leak/double free | Ownership publish từng phần | Fault injection + checker trace | Cleanup local, publish sau success | Single exit cleanup hoặc staged owner rõ |
| Caller đọc lỗi sai | Status lẫn output/stale `errno` | Test mọi enum branch | Explicit status + output parameter | Document exhaustive status table |
| Data race trong increment sau | Claim thread-safe không có sync | Thread sanitizer/design review | External lock hoặc design đồng bộ thật | Contract “not thread-safe” cho đến khi có oracle |

## 6. Từ điển thuật ngữ và mô hình tư duy

- **ADT:** kiểu được định nghĩa bởi operation/invariant, không bởi representation public.
- **Incomplete type:** type đã khai báo nhưng chưa đủ kích thước/member; nền tảng opaque handle.
- **Opaque handle:** pointer/capability client dùng qua API mà không dereference representation.
- **Translation unit:** source sau preprocessing; public header phải tự đủ dependency khi include vào một unit mới.
- **Internal linkage:** tên file-scope chỉ resolve trong translation unit, dùng cho helper private.
- **Failure atomicity:** operation lỗi giữ observable state theo contract.
- **Ownership/invalidation:** trách nhiệm giải phóng và thời điểm pointer/handle không còn hợp lệ.
- **Capacity model:** định nghĩa số phần tử public chứa được; M03 dùng count-based capacity đúng N slot.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng
- SRC-SYL — L2_MBD_ADVC_Syllabus_v1.0 1.xlsx: D:\Workspaces\FR_DN26_MBD_Simulink\L2_MBD_ADVC_Syllabus_v1.0 1.xlsx (publisher: Internal training syllabus; version: 1.0; accessed_at: 2026-08-21; license: internal_approved for this requested training-content generation; allowed_use: internal_approved)
- SRC-C17-ISO — ISO/IEC 9899:2018 — Programming languages — C: https://www.iso.org/standard/74528.html (publisher: ISO/IEC JTC 1/SC 22; version: Edition 4, C17, 2018; accessed_at: 2026-08-21; license: ISO copyright; metadata and clause references only, no reproduction; allowed_use: reference)
- SRC-C17-WG14 — WG14 N2176 proposed C17 committee draft: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2176.pdf (publisher: ISO/IEC JTC 1/SC 22/WG14; version: N2176, 2017-10-09; non-final public committee document; accessed_at: 2026-08-21; license: Publicly accessible committee document; link and paraphrase only; allowed_use: reference)
- SRC-GNUC — GNU C Language Manual: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/index.html (publisher: GNU Project / Free Software Foundation; version: rolling manual as accessed; C17 scope constrained by plan; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-CERTC — SEI CERT C Coding Standard: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/ (publisher: Carnegie Mellon University Software Engineering Institute; version: online work-in-progress snapshot as accessed; claims constrained to C17; accessed_at: 2026-08-21; license: CMU/SEI terms; reference and limited quotation only; allowed_use: reference)
- SRC-LINUX-CIRC — Circular Buffers: https://docs.kernel.org/core-api/circular-buffers.html (publisher: Linux Kernel documentation project; version: mainline documentation as accessed; fixed-ring pattern only; accessed_at: 2026-08-21; license: Linux kernel documentation terms; paraphrase only; allowed_use: reference)
- SRC-GCC11 — GCC 11.4 manuals: https://gcc.gnu.org/onlinedocs/gcc-11.4.0/ (publisher: GNU Project / Free Software Foundation; version: 11.4.0; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-LLVM14 — LLVM/Clang 14.0.0 Documentation: https://releases.llvm.org/14.0.0/tools/clang/docs/index.html (publisher: LLVM Project; version: 14.0.0; accessed_at: 2026-08-21; license: Apache-2.0 WITH LLVM-exception; allowed_use: reference)
- SRC-VALGRIND318 — Valgrind Memcheck Manual: https://valgrind.org/docs/manual/mc-manual.html (publisher: Valgrind Developers; version: 3.18.1 Ubuntu baseline; options constrained to that release; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.2 or later; allowed_use: reference)

### Phần bổ sung/suy diễn
Không dùng nguồn bổ sung hoặc claim không có nguồn cụ thể. Ba asset là code nguyên gốc của khóa; không sao chép macro, memory barrier hay implementation từ Linux kernel. Tài liệu circular buffer chỉ được paraphrase cho fixed-ring pattern, không dùng để tuyên bố thread-safety/lock-free.

---

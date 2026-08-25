# Session S03: Session 03 — Opaque ADT and module design — Ví dụ và nghiên cứu tình huống

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 02 — Abstract Data Types, Generic Programming & Bit-level C

## 🎯 Learning Outcomes liên quan
- **ADVC-H1SD** [create] — Thiết kế, hiện thực và kiểm chứng các mô-đun C17 dùng con trỏ nâng cao, quản lý bộ nhớ động, ADT đóng gói và cấu trúc dữ liệu generic mà không làm lộ ownership hoặc gây lỗi bộ nhớ trong các ca kiểm thử đã cho. · Bằng chứng: Public API/header và implementation C biên dịch với warning profile đã chốt; unit tests đạt; sanitizer hoặc Valgrind không báo lỗi thuộc phạm vi fixture.

## 🧭 Liên kết với ngữ cảnh nghề nghiệp/dự án

**Bối cảnh nghề nghiệp/dự án:**
**MDB Edge Diagnostics Gateway — Simulated** — Cổng chẩn đoán và telemetry chạy local trên Linux cho thiết bị giả lập; tiếp nhận command, quản lý work records, thực thi backend process/thread và phục vụ protocol TCP loopback. Vai trò học viên: C systems developer chịu trách nhiệm phát triển và harden từng increment trong repository đào tạo. Mục tiêu: Bàn giao một gateway TCP loopback tích hợp core C17, process/thread backends và quality evidence; phục vụ ít nhất 100 client synthetic theo Assignment 09 mà không có finding mức chặn trong oracle áp dụng.

**Project increment được minh họa:**
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

## 🧰 Điều kiện chạy ví dụ

**Kiến thức/kỹ năng tiên quyết:**
- **knowledge:** - Pointer, allocation, alignment and ownership/reset contracts from S01–S02
- **skills:** - Build and run CTest plus a separate sanitizer or Valgrind oracle
- **completed_units:** - s02
- **assets:** - starter/assignment-03/README.md

**Môi trường, công cụ và phiên bản:**
- **profile_ref:** ENV-ADV-C-JAMMY
- **description:** Môi trường local cô lập cho C17/Linux system programming; Ubuntu 22.04 native, VM hoặc WSL2.
- **operating_system:** Ubuntu 22.04 LTS (Jammy), native/VM/WSL2; network tests bind loopback only
- **runtimes:** - - **name:** C language mode<br>- **version:** C17<br>- - **name:** glibc<br>- **version:** 2.35
- **tools:** - - **name:** GCC<br>- **version:** 11.4 baseline<br>- - **name:** Clang<br>- **version:** 14.0 baseline<br>- - **name:** GNU Make<br>- **version:** 4.3<br>- - **name:** CMake<br>- **version:** 3.22.1<br>- - **name:** GNU Binutils<br>- **version:** 2.38<br>- - **name:** GDB<br>- **version:** 12.1<br>- - **name:** Valgrind<br>- **version:** 3.18.1<br>- - **name:** cppcheck<br>- **version:** 2.7<br>- - **name:** clang-tidy<br>- **version:** 14.0<br>- - **name:** CMocka<br>- **version:** 1.1.5<br>- - **name:** gcov<br>- **version:** 11.4<br>- - **name:** LCOV package<br>- **version:** Ubuntu Jammy 1.15-1; bundled lcov --version reports 1.14<br>- - **name:** perf<br>- **version:** Linux 5.15 toolset<br>- - **name:** Git<br>- **version:** 2.34+
- **services:** _(Không có / chưa áp dụng)_
- **overrides:** _(Không có / chưa áp dụng)_

**Phương thức xác minh artifact:**
executable

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

> Đây là khu vực provenance. Không chèn tên file nguồn vào câu văn của case study; mọi nguồn bổ sung/suy diễn được ghi riêng ở cuối tài liệu.

---

CASE-S03-01 giải một ticket end-to-end bằng ba translation units và một negative compile probe: API opaque, implementation private, FIFO count-based và lifecycle/error oracle. Asset là lời giải của case, không phải implementation tham chiếu cho ASM-A03.

### Mapping case đã chốt trong course plan
- - **id:** CASE-S03-01<br>- **learning_outcomes:** - ADVC-H1SD<br>- **outline_refs:** - OUT-S03-01<br>- **authenticity:** inherit

**Mức xác thực mặc định:** simulated

## Case Study 01: CASE-S03-01 — Opaque FIFO cho event synthetic

### 1. Ticket và tiêu chí thành công

- **Vai trò/stakeholder:** maintainer gateway; consumer của event API; reviewer M03.
- **Vấn đề cần giải quyết:** client cần enqueue/dequeue event nhưng không được biết hoặc sửa representation; full/empty/null/lifecycle phải cho kết quả xác định.
- **Learning Outcome và outline item:** ADVC-H1SD · OUT-S03-01.
- **Project increment/professional artifact liên quan:** M03 · mẫu Opaque event ring core v3.
- **Tiêu chí thành công:** public header tự chứa và opaque; capacity đúng ba; empty/full/wrap/FIFO/null/reset đúng status/state; positive build/run sạch; opacity probe phải compile fail.

### 2. Input, trạng thái ban đầu và ràng buộc

Event là value `{uint32_t id, int32_t value}`. Input gồm capacity `0` và `3`, bốn event id `1..4`, empty pop, ba push, full push, peek, pop/push để wrap, drain, null handle/element, reset và destroy. Ring copy event, sở hữu backing storage, public capacity bằng đúng số record chứa được và không thread-safe; caller phải đồng bộ nếu share handle.

### 3. Phân tích lựa chọn

Public complete struct đơn giản cho caller cấp trên stack nhưng khóa ABI/layout và cho phép phá invariant. Opaque heap handle che representation nhưng cần factory, failure cleanup và destroy. Sentinel-slot giảm một biến `count` nhưng public capacity dễ bị hiểu lệch; case chọn count-based để ba nghĩa là chứa ba event, đổi lại phải duy trì thêm invariant `count`.

### 4. Cách triển khai

Lời giải gồm [event_ring.h](assets/event_ring.h), [event_ring.c](assets/event_ring.c) và [event_ring_demo.c](assets/event_ring_demo.c). Header chỉ forward-declare handle và công bố status/contract. Implementation hoàn thiện struct, dùng `static advance_index`, kiểm overflow/allocation trước publish và validate full/empty trước mutation. Demo chỉ gọi public API.

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -g \
  assets/event_ring.c assets/event_ring_demo.c -o /tmp/s03_ring
/tmp/s03_ring
```

### 5. Output mong đợi

Positive fixture exit `0` và stdout:

```text
S03 RING PASS
```

Full push trả `RING_FULL` và size vẫn `3`; sau pop id `1` rồi push id `4`, drain trả `2,3,4`. [opacity_probe_fail.c](assets/opacity_probe_fail.c) phải bị compiler từ chối vì `event_ring` là incomplete type; compile success của probe là test failure.

### 6. Cách xác minh

- Positive: `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -g assets/event_ring.c assets/event_ring_demo.c -o /tmp/s03_ring && /tmp/s03_ring`.
- Sanitizer: `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer assets/event_ring.c assets/event_ring_demo.c -o /tmp/s03_ring_san && /tmp/s03_ring_san`.
- Opacity oracle: `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -Iassets -c assets/opacity_probe_fail.c -o /tmp/opacity_probe.o`; command **phải exit khác 0** với lỗi dùng incomplete type.
- Pass khi hai positive run exit `0`/stdout khớp/no finding và negative probe fail đúng lý do; mọi status/state assertion trong demo qua.

### 7. Giải thích sâu và failure modes

Incomplete type chặn dependency tại compile time; nó không tự ngăn use-after-destroy. Factory đặt output null và chỉ publish sau hai allocation thành công, nên failure không trao half-built owner. Copy payload tách lifetime input khỏi queue. Nếu wrap sai, log `(head,tail,count)` và tìm transition vi phạm trước/sau operation. Nếu negative probe compile được, header đã lộ definition. Lời giải không thread-safe/lock-free và không chứa memory barrier; shared access phải được đồng bộ ngoài API.

### 8. Bài học chuyển giao

Encapsulation chỉ có giá trị khi boundary, error state và lifetime cùng được kiểm. ASM-A03 dùng adapter vào Memory-safe command core v2, allocation-failure fixture, regression M01–M02 và decision note riêng; học viên phải tự chọn capacity model/representation trong constraints, không chép case.

---

## Provenance của các case

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
Không sử dụng nguồn bổ sung hoặc phần suy diễn không có nguồn. Bốn asset là code nguyên gốc của khóa. Không sao chép Linux circular-buffer macros/memory barriers; tài liệu kernel chỉ cung cấp bối cảnh pattern và không phải bằng chứng cho thread-safety của case.


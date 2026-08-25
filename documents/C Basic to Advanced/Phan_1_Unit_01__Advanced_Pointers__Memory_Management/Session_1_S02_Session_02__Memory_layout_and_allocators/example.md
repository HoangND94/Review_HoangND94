# Session S02: Session 02 — Memory layout and allocators — Ví dụ và nghiên cứu tình huống

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 01 — Advanced Pointers & Memory Management

## 🎯 Learning Outcomes liên quan
- **ADVC-H1SD** [create] — Thiết kế, hiện thực và kiểm chứng các mô-đun C17 dùng con trỏ nâng cao, quản lý bộ nhớ động, ADT đóng gói và cấu trúc dữ liệu generic mà không làm lộ ownership hoặc gây lỗi bộ nhớ trong các ca kiểm thử đã cho. · Bằng chứng: Public API/header và implementation C biên dịch với warning profile đã chốt; unit tests đạt; sanitizer hoặc Valgrind không báo lỗi thuộc phạm vi fixture.

## 🧭 Liên kết với ngữ cảnh nghề nghiệp/dự án

**Bối cảnh nghề nghiệp/dự án:**
**MDB Edge Diagnostics Gateway — Simulated** — Cổng chẩn đoán và telemetry chạy local trên Linux cho thiết bị giả lập; tiếp nhận command, quản lý work records, thực thi backend process/thread và phục vụ protocol TCP loopback. Vai trò học viên: C systems developer chịu trách nhiệm phát triển và harden từng increment trong repository đào tạo. Mục tiêu: Bàn giao một gateway TCP loopback tích hợp core C17, process/thread backends và quality evidence; phục vụ ít nhất 100 client synthetic theo Assignment 09 mà không có finding mức chặn trong oracle áp dụng.

**Project increment được minh họa:**
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

## 🧰 Điều kiện chạy ví dụ

**Kiến thức/kỹ năng tiên quyết:**
- **knowledge:** - Pointer/lifetime/callback contracts từ S01
- **skills:** - Chạy warning profile và sanitizer fixture
- **completed_units:** - s01
- **assets:** - starter/assignment-02/README.md

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
- SRC-GLIBC235 — GNU C Library Reference Manual: https://sourceware.org/glibc/manual/2.35/pdf/libc.pdf (publisher: GNU Project; version: glibc 2.35; accessed_at: 2026-08-21; license: GNU Free Documentation License; link and paraphrase; allowed_use: reference)
- SRC-LD238 — GNU ld 2.38 documentation: https://sourceware.org/binutils/docs-2.38/ld/ (publisher: GNU Project / Binutils; version: 2.38; accessed_at: 2026-08-21; license: GNU Free Documentation License; allowed_use: reference)
- SRC-CERTC — SEI CERT C Coding Standard: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/ (publisher: Carnegie Mellon University Software Engineering Institute; version: online work-in-progress snapshot as accessed; claims constrained to C17; accessed_at: 2026-08-21; license: CMU/SEI terms; reference and limited quotation only; allowed_use: reference)
- SRC-LLVM14 — LLVM/Clang 14.0.0 Documentation: https://releases.llvm.org/14.0.0/tools/clang/docs/index.html (publisher: LLVM Project; version: 14.0.0; accessed_at: 2026-08-21; license: Apache-2.0 WITH LLVM-exception; allowed_use: reference)
- SRC-VALGRIND318 — Valgrind Memcheck Manual: https://valgrind.org/docs/manual/mc-manual.html (publisher: Valgrind Developers; version: 3.18.1 Ubuntu baseline; options constrained to that release; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.2 or later; allowed_use: reference)

> Đây là khu vực provenance. Không chèn tên file nguồn vào câu văn của case study; mọi nguồn bổ sung/suy diễn được ghi riêng ở cuối tài liệu.

---

CASE-S02-01 dùng một workload bounded riêng để nối bốn quyết định: alignment của slot, exhaustion/reuse state, invalid-free policy và external endian encoding. Asset là lời giải hoàn chỉnh của case; ASM-A02 dùng baseline dispatcher và change request khác.

### Mapping case đã chốt trong course plan
- - **id:** CASE-S02-01<br>- **learning_outcomes:** - ADVC-H1SD<br>- **outline_refs:** - OUT-S02-01<br>- **authenticity:** inherit

**Mức xác thực mặc định:** simulated

## Case Study 01: CASE-S02-01 — Bounded pool cho command record synthetic

### 1. Ticket và tiêu chí thành công

- **Vai trò/stakeholder:** C systems developer; maintainer/reviewer của memory core.
- **Vấn đề cần giải quyết:** workload chỉ cho phép bốn record sống đồng thời; hệ thống phải báo exhaustion xác định, tái sử dụng an toàn và không phụ thuộc raw struct/endian của host.
- **Learning Outcome và outline item:** ADVC-H1SD · OUT-S02-01.
- **Project increment/professional artifact liên quan:** M02 · mẫu quyết định cho Memory-safe command core v2.
- **Tiêu chí thành công:** bốn slot aligned/unique; lần cấp thứ năm fail không mutate; free/reuse/double/foreign/reset đúng policy; encode `0x01020304` thành `01 02 03 04`; checker sạch.

### 2. Input, trạng thái ban đầu và ràng buộc

Input là pool capacity `4`, block size `64`, một `command_record` synthetic và giá trị wire `0x01020304`. Mỗi block phải thỏa `_Alignof(max_align_t)`. Không gọi `malloc/free` trong fast path, không chấp nhận interior/foreign pointer, reset làm invalid mọi pointer logic trước đó, và không serialize raw `command_record`.

### 3. Phân tích lựa chọn

Heap chung linh hoạt nhưng không cho capacity/exhaustion oracle cục bộ. Arena cấp nhanh nhưng không hỗ trợ free từng record. Fixed pool phù hợp vì block/capacity bounded; trade-off là 64 byte luôn được giữ cho cả record nhỏ và pool phải định nghĩa double/foreign free. Union slot được chọn để bảo đảm alignment; bitmap đơn giản, dễ kiểm nhưng lookup free tuyến tính.

### 4. Cách triển khai

Lời giải tự chứa ở [pool_demo.c](assets/pool_demo.c). `pool_alloc` chỉ chuyển slot free sang used; `pool_release` so exact địa chỉ từng slot trước khi đổi state; union gắn alignment `max_align_t`. Encoder dịch từng byte theo big-endian nên độc lập representation/padding của struct.

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -g \
  assets/pool_demo.c -o /tmp/s02_pool
/tmp/s02_pool
```

### 5. Output mong đợi

Mọi assertion pass và stdout chính xác:

```text
S02 POOL PASS
```

Exhaustion trả `NULL`; slot vừa free được reuse; lần free tiếp theo trả `POOL_DOUBLE_FREE`; pointer ngoài pool trả `POOL_FOREIGN_POINTER`. Kích thước/offset cụ thể của struct không được hardcode vì phụ thuộc target.

### 6. Cách xác minh

- Functional oracle: `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -g assets/pool_demo.c -o /tmp/s02_pool && /tmp/s02_pool`.
- Memory oracle: `valgrind --tool=memcheck --leak-check=full --errors-for-leak-kinds=definite,indirect --error-exitcode=99 /tmp/s02_pool`.
- Sanitizer thay thế: build binary riêng với `-fsanitize=address,undefined -fno-omit-frame-pointer`; không chạy Valgrind trên binary này.
- Pass khi exit `0`, stdout khớp, warning count `0`, Valgrind `0 errors` và không definite/indirect leak.

### 7. Giải thích sâu và failure modes

Mỗi transition free↔used là observable state; exhaustion không có transition. Exact-pointer equality tránh phép so thứ tự giữa object không cùng array và từ chối interior pointer. Nếu alignment assertion fail, storage/stride không đáp ứng advertised type; sửa representation thay vì cast. Nếu reset xong caller vẫn dùng pointer cũ, lỗi là vi phạm lifetime contract dù địa chỉ có thể được cấp lại. Pool mẫu chưa tối ưu O(1) free-list và không thread-safe; đó là trade-off, không phải claim hiệu năng.

### 8. Bài học chuyển giao

Allocator là state machine có owner, membership, capacity và failure policy; layout trong RAM không phải wire schema. ASM-A02 yêu cầu học viên tự tích hợp pool vào Dispatcher module v1, thiết kế layout/ownership note và chứng minh M01 không regression; asset case không cung cấp integration đó.

---

## Provenance của các case

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
Không sử dụng nguồn bổ sung hoặc phần suy diễn không có nguồn. Asset C17 là code nguyên gốc của khóa; quy tắc allocation/layout/endian chỉ được paraphrase từ nguồn đã map, không sao chép implementation bên ngoài.


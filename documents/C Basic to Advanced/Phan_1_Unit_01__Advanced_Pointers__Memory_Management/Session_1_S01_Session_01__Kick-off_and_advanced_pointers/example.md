# Session S01: Session 01 — Kick-off and advanced pointers — Ví dụ và nghiên cứu tình huống

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 01 — Advanced Pointers & Memory Management

## 🎯 Learning Outcomes liên quan
- **ADVC-H1SD** [create] — Thiết kế, hiện thực và kiểm chứng các mô-đun C17 dùng con trỏ nâng cao, quản lý bộ nhớ động, ADT đóng gói và cấu trúc dữ liệu generic mà không làm lộ ownership hoặc gây lỗi bộ nhớ trong các ca kiểm thử đã cho. · Bằng chứng: Public API/header và implementation C biên dịch với warning profile đã chốt; unit tests đạt; sanitizer hoặc Valgrind không báo lỗi thuộc phạm vi fixture.

## 🧭 Liên kết với ngữ cảnh nghề nghiệp/dự án

**Bối cảnh nghề nghiệp/dự án:**
**MDB Edge Diagnostics Gateway — Simulated** — Cổng chẩn đoán và telemetry chạy local trên Linux cho thiết bị giả lập; tiếp nhận command, quản lý work records, thực thi backend process/thread và phục vụ protocol TCP loopback. Vai trò học viên: C systems developer chịu trách nhiệm phát triển và harden từng increment trong repository đào tạo. Mục tiêu: Bàn giao một gateway TCP loopback tích hợp core C17, process/thread backends và quality evidence; phục vụ ít nhất 100 client synthetic theo Assignment 09 mà không có finding mức chặn trong oracle áp dụng.

**Project increment được minh họa:**
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

## 🧰 Điều kiện chạy ví dụ

**Kiến thức/kỹ năng tiên quyết:**
- **knowledge:** - C cơ bản: data types, control flow, functions, arrays, basic pointers và file I/O
- **skills:** - Biên dịch và chạy một chương trình C đơn giản
- **completed_units:** _(Không có / chưa áp dụng)_
- **assets:** - starter/assignment-01/README.md

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
- SRC-UBUNTU22 — Ubuntu 22.04 LTS package index: https://packages.ubuntu.com/jammy/ (publisher: Canonical / Ubuntu; version: Jammy 22.04 package baseline; accessed_at: 2026-08-21; license: Canonical site and package metadata terms; reference only; allowed_use: reference)
- SRC-C17-ISO — ISO/IEC 9899:2018 — Programming languages — C: https://www.iso.org/standard/74528.html (publisher: ISO/IEC JTC 1/SC 22; version: Edition 4, C17, 2018; accessed_at: 2026-08-21; license: ISO copyright; metadata and clause references only, no reproduction; allowed_use: reference)
- SRC-C17-WG14 — WG14 N2176 proposed C17 committee draft: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2176.pdf (publisher: ISO/IEC JTC 1/SC 22/WG14; version: N2176, 2017-10-09; non-final public committee document; accessed_at: 2026-08-21; license: Publicly accessible committee document; link and paraphrase only; allowed_use: reference)
- SRC-GCC11 — GCC 11.4 manuals: https://gcc.gnu.org/onlinedocs/gcc-11.4.0/ (publisher: GNU Project / Free Software Foundation; version: 11.4.0; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-GNUC — GNU C Language Manual: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/index.html (publisher: GNU Project / Free Software Foundation; version: rolling manual as accessed; C17 scope constrained by plan; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-CERTC — SEI CERT C Coding Standard: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/ (publisher: Carnegie Mellon University Software Engineering Institute; version: online work-in-progress snapshot as accessed; claims constrained to C17; accessed_at: 2026-08-21; license: CMU/SEI terms; reference and limited quotation only; allowed_use: reference)
- SRC-LLVM14 — LLVM/Clang 14.0.0 Documentation: https://releases.llvm.org/14.0.0/tools/clang/docs/index.html (publisher: LLVM Project; version: 14.0.0; accessed_at: 2026-08-21; license: Apache-2.0 WITH LLVM-exception; allowed_use: reference)
- SRC-VALGRIND318 — Valgrind Memcheck Manual: https://valgrind.org/docs/manual/mc-manual.html (publisher: Valgrind Developers; version: 3.18.1 Ubuntu baseline; options constrained to that release; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.2 or later; allowed_use: reference)

> Đây là khu vực provenance. Không chèn tên file nguồn vào câu văn của case study; mọi nguồn bổ sung/suy diễn được ghi riêng ở cuối tài liệu.

---

Hai case dùng dữ liệu synthetic và hai oracle khác nhau: CASE-S01-01 khóa môi trường có thể tái lập; CASE-S01-02 giải bài toán định tuyến và generic data contract. Code là lời giải mẫu cho ticket của case, không phải implementation của change request trong ASM-A01.

### Mapping case đã chốt trong course plan
- - **id:** CASE-S01-01<br>- **learning_outcomes:** - ADVC-H1SD<br>- **outline_refs:** - OUT-S01-01<br>- **authenticity:** inherit
- - **id:** CASE-S01-02<br>- **learning_outcomes:** - ADVC-H1SD<br>- **outline_refs:** - OUT-S01-02<br>- **authenticity:** inherit

**Mức xác thực mặc định:** simulated

## Case Study 01: CASE-S01-01 — Khóa baseline C17 trước khi nhận ticket

### 1. Ticket và tiêu chí thành công

- **Vai trò/stakeholder:** C systems developer bàn giao evidence cho reviewer M01.
- **Vấn đề cần giải quyết:** Hai máy cùng source nhưng warning profile và tool version chưa được chứng minh giống nhau; reviewer cần một smoke test tối thiểu trước khi đánh giá code.
- **Learning Outcome và outline item:** ADVC-H1SD · OUT-S01-01.
- **Project increment/professional artifact liên quan:** M01 · environment evidence cho Dispatcher module v1.
- **Tiêu chí thành công:** tool fingerprint được ghi; C17 smoke asset build với warning count `0`, exit `0` và in đúng `ENV_SMOKE PASS`.

### 2. Input, trạng thái ban đầu và ràng buộc

Input là [environment_smoke.c](assets/environment_smoke.c). Máy mục tiêu là Ubuntu 22.04 native/VM/WSL2, GCC 11.4 baseline; không cần network, credential hay service. Lệnh phải chỉ rõ `-std=c17 -Wall -Wextra -Wpedantic -Werror`; executable được đặt trong `/tmp`, không trộn vào source snapshot.

### 3. Phân tích lựa chọn

Chỉ lưu tên “GCC 11+” ngắn nhưng không tái lập chính xác. Chụp toàn bộ màn hình khó diff và có thể lộ thông tin máy. Case chọn text manifest gồm dòng version đầu tiên và exact command; trade-off là evidence không chứng minh mọi đường chạy, nhưng đủ làm preflight định danh toolchain và C17 mode.

### 4. Cách triển khai

Asset dùng kiểm tra tiền xử lý `__STDC_VERSION__ >= 201710L`; nếu vô tình build ở mode cũ, compiler dừng trước khi tạo binary. `main` chỉ in một oracle ổn định, không in `sizeof(void *)` vì giá trị đó phụ thuộc target. Chạy:

```bash
gcc --version | head -n 1
cmake --version | head -n 1
gdb --version | head -n 1
valgrind --version
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror \
  assets/environment_smoke.c -o /tmp/advc_env_smoke
/tmp/advc_env_smoke
```

### 5. Output mong đợi

Bốn lệnh đầu in fingerprint của công cụ. Hai lệnh cuối exit `0`, không warning và stdout:

```text
ENV_SMOKE PASS
```

Nếu bỏ `-std=c17` trên compiler mặc định mode cũ, lỗi compile `This example requires C17 mode` là failure mong đợi.

### 6. Cách xác minh

- `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror assets/environment_smoke.c -o /tmp/advc_env_smoke`
- `/tmp/advc_env_smoke`
- Pass khi compile/run đều exit `0`, warning count `0`, stdout khớp chính xác và manifest chứa đủ bốn fingerprint.

### 7. Giải thích sâu và failure modes

Preprocessor macro chứng minh language mode mà compiler công bố cho translation unit; nó không chứng minh library hay runtime không lỗi. Nếu compiler báo `#error`, kiểm exact command thay vì xóa guard. Nếu không tìm thấy Valgrind, xác nhận package baseline trước khi tiếp tục memory gate; không giả lập evidence. Case không thay thế unit test hay sanitizer của M01.

### 8. Bài học chuyển giao

Evidence tốt trả lời ba câu: chạy bằng công cụ nào, chạy lệnh gì, oracle nào quyết định pass. ASM-A01 yêu cầu học viên tự tích hợp nguyên tắc này vào repository/CMake scaffold và nộp clean-build log; case không cung cấp cấu trúc evidence manifest của bài làm.

---

## Case Study 02: CASE-S01-02 — Dispatcher typed và generic record operations

### 1. Ticket và tiêu chí thành công

- **Vai trò/stakeholder:** maintainer gateway và reviewer của M01.
- **Vấn đề cần giải quyết:** thêm handler mà không kéo dài chuỗi điều kiện, đồng thời sort/search/swap record qua generic API mà không mất type/bounds contract.
- **Learning Outcome và outline item:** ADVC-H1SD · OUT-S01-02.
- **Project increment/professional artifact liên quan:** M01 · prototype của Dispatcher module v1.
- **Tiêu chí thành công:** known/unknown/null callback trả đúng status; context cập nhật đúng một lần; dữ liệu gồm duplicate và hai cực trị sort/search đúng; out-of-range swap bị từ chối; sanitizer sạch.

### 2. Input, trạng thái ban đầu và ràng buộc

Registry có command `set`, command `disabled` với callback null và context `{calls=0,last_value=0}`. Dữ liệu số là `{INT_MAX,4,INT_MIN,4,0}`. Không dùng mutable global registry, không cast function pointer, comparator không được dùng phép trừ, và generic swap phải nhận base/count/element-size.

### 3. Phân tích lựa chọn

Chuỗi `if/else` có type safety nhưng extension point nằm trong control flow. Bảng callback chuyển extension point thành dữ liệu; đổi lại, contract về duplicate key, null handler và context lifetime phải rõ. Generic `void *` giảm duplication nhưng compiler không biết element type/bounds; case giới hạn nó ở byte-wise swap, còn comparator/wrapper chịu trách nhiệm khôi phục đúng type.

### 4. Cách triển khai

Lời giải hoàn chỉnh nằm ở [dispatcher_demo.c](assets/dispatcher_demo.c). `command_fn` khóa prototype; dispatcher duyệt bảng và không gọi callback null. Comparator dùng quan hệ để tránh signed overflow. `find_int` nhận output pointer, đặt `*out = NULL` trước search; `swap_elements` kiểm chỉ số rồi offset qua `unsigned char *`.

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror \
  assets/dispatcher_demo.c -o /tmp/s01_dispatcher
/tmp/s01_dispatcher
```

### 5. Output mong đợi

Mọi assertion qua và stdout chính xác:

```text
S01 DISPATCHER PASS
```

Unknown command trả `DISPATCH_UNKNOWN`; disabled callback và index ngoài bounds trả lỗi, không crash và không đổi context ngoài lần `set 17` thành công.

### 6. Cách xác minh

- Debug: `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror assets/dispatcher_demo.c -o /tmp/s01_dispatcher && /tmp/s01_dispatcher`
- Sanitizer: `gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -fsanitize=address,undefined -fno-omit-frame-pointer assets/dispatcher_demo.c -o /tmp/s01_dispatcher_san && /tmp/s01_dispatcher_san`
- Pass khi cả hai exit `0`, cùng stdout và sanitizer không có finding.

### 7. Giải thích sâu và failure modes

Typed callback cho compiler kiểm lời gọi; cast chỉ làm mất kiểm tra chứ không đổi function ABI. Comparator `a-b` hỏng ở `INT_MIN/INT_MAX`; relational compare luôn cho dấu đúng. `bsearch` chỉ có nghĩa trên mảng đã sort cùng ordering, và khi có duplicate nó có thể trả bất kỳ phần tử bằng key. Nếu ASan báo use-after-scope, nguyên nhân là context chết trước registry; sửa lifetime/ownership, không tắt sanitizer.

### 8. Bài học chuyển giao

Generic không có nghĩa là “không cần type”; type contract được chuyển sang callback, size, count và lifetime. ASM-A01 dùng command/fixture khác, yêu cầu thêm apply adapter và evidence repository, nên học viên phải tự thiết kế contract thay vì chép case.

---

## Provenance của các case

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
Không sử dụng nguồn bổ sung hoặc phần suy diễn không có nguồn. Hai asset là code nguyên gốc của khóa; case chỉ paraphrase quy tắc C17/GNU/CERT đã liệt kê, không sao chép nội dung hoặc code bên ngoài.


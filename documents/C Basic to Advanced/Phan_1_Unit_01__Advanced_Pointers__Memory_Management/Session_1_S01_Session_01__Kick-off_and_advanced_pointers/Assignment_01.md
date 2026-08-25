# Session S01: Session 01 — Kick-off and advanced pointers — Assignment 01

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 01 — Advanced Pointers & Memory Management

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASM-A01 (Assignment 01) |
| Thời lượng dự kiến | 120 phút |
| Độ khó | medium |
| Bloom levels | - create |
| Mức xác thực | simulated |

## 🎯 Learning Outcomes được đánh giá
- **ADVC-H1SD** [create] — Thiết kế, hiện thực và kiểm chứng các mô-đun C17 dùng con trỏ nâng cao, quản lý bộ nhớ động, ADT đóng gói và cấu trúc dữ liệu generic mà không làm lộ ownership hoặc gây lỗi bộ nhớ trong các ca kiểm thử đã cho. · Bằng chứng: Public API/header và implementation C biên dịch với warning profile đã chốt; unit tests đạt; sanitizer hoặc Valgrind không báo lỗi thuộc phạm vi fixture.

**Chuỗi truy vết ADVC-H1SD:** Dispatcher module v1 + A01 tests/evidence + decision note → AT-A01-01..03 → RB-A01-01..04. Mọi yêu cầu đều thuộc OUT-S01-01/02 đã học và đã được minh họa trong CASE-S01-01/02; bài dùng command và fixture mới để đánh giá khả năng chuyển giao.

## 🧠 Khái niệm và best practices được đánh giá
### CA-A01-ENV — Khóa environment và evidence contract
- **Khái niệm/outline:** OUT-S01-01
- **Learning Outcomes:** ADVC-H1SD
- **Scenario:** Reviewer phải tái lập build M01 trên Ubuntu 22.04 mà không đoán compiler hoặc command.
- **Inputs:** Project repository skeleton; Public contract pack; Change request CR-A01
- **Best-practice constraints:**
  - **Lưu exact tool fingerprint và clean-build command thay vì chỉ ghi GCC 11+.** — Lý do: Warning set và sanitizer behavior phụ thuộc version; evidence không có fingerprint không tái lập được.; Concepts: OUT-S01-01; Acceptance tests: AT-A01-01; Rubric: RB-A01-03, RB-A01-04
- **Deliverables:** A01 tests and evidence; A01 decision note
- **Acceptance tests và oracle quan sát được:**
  - **AT-A01-01** [ADVC-H1SD] — Clean configure/build ghi đúng compiler/tool versions và không warning; Expected: Build exit 0; version manifest hiện diện; warning count 0 trong enabled profile; Evidence/rubric: RB-A01-01: AT-A01-02 test report; RB-A01-02: Code review plus AT-A01-03; RB-A01-03: AT-A01-01..03 and version manifest; RB-A01-04: A01 decision note and submission manifest

### CA-A01-PTR — Typed callback and generic byte-contract transfer
- **Khái niệm/outline:** OUT-S01-02
- **Learning Outcomes:** ADVC-H1SD
- **Scenario:** Gateway cần thêm command handlers và sort/search record mà vẫn giữ prototype, lifetime và bounds contract.
- **Inputs:** Synthetic command and telemetry fixtures; Public contract pack; Change request CR-A01
- **Best-practice constraints:**
  - **Mọi handler dùng một typedef callback tương thích; không call qua incompatible function type.** — Lý do: Prototype mismatch dẫn tới undefined behavior và compiler không thể bảo vệ khi bị cast che giấu.; Concepts: OUT-S01-02; Acceptance tests: AT-A01-02, AT-A01-03; Rubric: RB-A01-01, RB-A01-02
  - **Generic API mang count, element size, null/zero policy và dùng byte pointer cho offset.** — Lý do: void* không có portable element arithmetic; thiếu size/lifetime contract gây out-of-bounds hoặc type-punning sai.; Concepts: OUT-S01-02; Acceptance tests: AT-A01-02, AT-A01-03; Rubric: RB-A01-01, RB-A01-02, RB-A01-03
- **Deliverables:** Dispatcher module v1; A01 tests and evidence
- **Acceptance tests và oracle quan sát được:**
  - **AT-A01-02** [ADVC-H1SD] — Dispatcher và generic algorithms qua known, unknown, null, duplicates, INT_MIN/INT_MAX và not-found fixtures; Expected: Mọi status/output khớp golden oracle; không incompatible callback call; Evidence/rubric: RB-A01-01: AT-A01-02 test report; RB-A01-02: Code review plus AT-A01-03; RB-A01-03: AT-A01-01..03 and version manifest; RB-A01-04: A01 decision note and submission manifest
  - **AT-A01-03** [ADVC-H1SD] — ASan+UBSan chạy positive và negative boundary fixtures; Expected: Process exit 0 và không sanitizer finding thuộc code học viên; Evidence/rubric: RB-A01-01: AT-A01-02 test report; RB-A01-02: Code review plus AT-A01-03; RB-A01-03: AT-A01-01..03 and version manifest; RB-A01-04: A01 decision note and submission manifest

**Ranh giới đánh giá:** CA-A01-ENV được quan sát qua version manifest, clean-build log và AT-A01-01; CA-A01-PTR được quan sát qua source review, golden fixtures AT-A01-02 và sanitizer AT-A01-03. Học viên tự chọn cấu trúc module và thuật toán; đề không quy định chuỗi bước hay cung cấp implementation tham chiếu.

## 🧭 Bối cảnh nghề nghiệp/dự án và change request

**Bối cảnh nghề nghiệp/dự án:**
**MDB Edge Diagnostics Gateway — Simulated** — Cổng chẩn đoán và telemetry chạy local trên Linux cho thiết bị giả lập; tiếp nhận command, quản lý work records, thực thi backend process/thread và phục vụ protocol TCP loopback. Vai trò học viên: C systems developer chịu trách nhiệm phát triển và harden từng increment trong repository đào tạo. Mục tiêu: Bàn giao một gateway TCP loopback tích hợp core C17, process/thread backends và quality evidence; phục vụ ít nhất 100 client synthetic theo Assignment 09 mà không có finding mức chặn trong oracle áp dụng.

**Project increment/change request cần hoàn thành:**
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

**Scenario đã chốt trong plan:**
Hoàn thiện increment M01 cho gateway mô phỏng: chốt environment evidence, xây typed dispatch table và dùng comparator/adapters cho qsort, bsearch, swap và apply trên dữ liệu synthetic.

Bạn là C systems developer nhận CR-A01 từ maintainer của gateway mô phỏng. Repository skeleton hiện chỉ có public contract pack và fixture synthetic; reviewer cần thêm command mà không sửa chuỗi `if/else` trung tâm, đồng thời cần sort/search/swap/apply telemetry record có nhiều kích thước. Giá trị bàn giao là extension point typed và evidence có thể chạy lại trên Ubuntu 22.04. Command/record của đề khác CASE-S01-02; không có dữ liệu hoặc endpoint thật.

## 🔗 Liên kết project xuyên suốt

**Project milestone:**
M01

**Phụ thuộc vào Assignment trước:**
- _(Không có / chưa áp dụng)_

**Baseline artifacts được sử dụng:**
- Project repository skeleton
- Synthetic command and telemetry fixtures
- Public contract pack

**Artifacts Assignment này tạo ra:**
- Dispatcher module v1

**Assignment sau sẽ tái sử dụng:**
- ASM-A02

**Terminal delivery (chỉ Assignment cuối):**
Không áp dụng — đây là increment trung gian; sản phẩm được Assignment kế tiếp sử dụng.


## 🧰 Điều kiện thực hiện

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

### Input và starter assets
- Project repository skeleton
- Synthetic command and telemetry fixtures
- Public contract pack
- Change request CR-A01

Starter pack cung cấp `starter/assignment-01/README.md`, CMake skeleton, public status contract, fixture command/telemetry synthetic và CR-A01. Fixture tối thiểu có known command, unknown command, registry entry có callback null, duplicate sort keys, `INT_MIN`, `INT_MAX`, not-found key và buffer với ít nhất hai `element_size`. Không có secret, network, PII hay production configuration. Học viên phải giữ nguyên fixture gốc và có thể thêm fixture riêng.

## 📋 Yêu cầu

### Functional requirements
- **FR-A01-01 [ADVC-H1SD]:** Registry ánh xạ mỗi command name hợp lệ tới callback đúng prototype và context còn sống trong suốt thời gian đăng ký; bằng chứng ở Dispatcher module v1 và AT-A01-02.
- **FR-A01-02 [ADVC-H1SD]:** Known command gọi đúng handler đúng một lần; unknown name và callback null trả status theo public contract, không crash và không mutate context; bằng chứng ở A01 tests và AT-A01-02/03.
- **FR-A01-03 [ADVC-H1SD]:** Generic sort/search/swap/apply xử lý đúng fixture với nhiều element size; zero/count/null policy được công bố; bằng chứng ở A01 tests và AT-A01-02/03.

### Non-functional requirements
- **NFR-A01-01 [ADVC-H1SD]:** Clean build C17 với `-Wall -Wextra -Wpedantic -Werror`; không cast function pointer để che type mismatch. Oracle: warning count `0`, build exit `0`, source review không có incompatible call.
- **NFR-A01-02 [ADVC-H1SD]:** ASan+UBSan chạy cả positive và negative boundary fixture, exit `0`, không finding thuộc code học viên; environment fingerprint và exact command được lưu trong evidence manifest.

### Ràng buộc và phạm vi loại trừ
- CMake scaffold được cấp sẵn và không được chấm như kiến thức CMake
- Không dùng mutable global registry
- Comparator tránh subtraction có thể signed-overflow
- void* arithmetic phải qua byte pointer và có size/count contract

CMake skeleton được cung cấp chỉ để chạy build/test và không được chấm như kiến thức CMake. Ngoài phạm vi: thread safety, dynamic plugin loading, networking, tối ưu hiệu năng và thay đổi public fixture. Không dùng mutable global registry; không giả định `void *` arithmetic là portable; không dùng comparator subtraction; không vô hiệu warning/sanitizer để làm test xanh.

> [!IMPORTANT]
> Đây là bài làm độc lập. Đề bài không cung cấp quy trình từng bước, code hoàn chỉnh hoặc đáp án. Có thể điều hướng tới khái niệm/Case Study đã học nhưng không được lộ lời giải cho change request này.

## 📦 Deliverables và cách nộp
- Dispatcher module v1
- A01 tests and evidence
- A01 decision note

**Submission contract:**
Nộp archive/repository snapshot của M01 cùng evidence manifest đã redact; không nộp build cache hoặc dữ liệu ngoài fixture.

- **Dispatcher module v1:** source/header và build metadata nằm trong snapshot M01, public surface tách khỏi test; nộp đủ khi clean build và AT-A01-02 resolve tới module này.
- **A01 tests and evidence:** test source, immutable fixture/golden oracle, version manifest, clean-build/CTest/sanitizer summaries; nộp đủ khi mỗi AT có command, exit code và kết quả thực.
- **A01 decision note:** tài liệu ngắn nêu callback typedef, context ownership/lifetime, unknown/null/zero policy, comparator và byte-offset decisions; mỗi quyết định trỏ tới test chứng minh.
- Snapshot không chứa build cache, executable, secret hoặc dữ liệu ngoài fixture synthetic; manifest liệt kê đủ file được nộp.

## ✅ Acceptance criteria và output mong đợi
- **AT-A01-01 [ADVC-H1SD]:** Given clean build tree và manifest trống, when chạy ba validation command trên environment đã fingerprint, then configure/build/test exit `0`, warning count `0`, manifest chứa exact compiler/tool versions. Bằng chứng: build log + version manifest; rubric RB-A01-03/04.
- **AT-A01-02 [ADVC-H1SD]:** Given fixture known/unknown/null, duplicate keys, `INT_MIN/INT_MAX`, not-found và hai element size, when chạy suite, then status/output khớp golden oracle, known handler gọi đúng một lần, nhánh lỗi không mutate state, không có incompatible callback call. Bằng chứng: per-fixture result; rubric RB-A01-01/02.
- **AT-A01-03 [ADVC-H1SD]:** Given sanitizer profile và cả positive/negative boundary fixtures, when chạy suite, then process exit `0` và stderr không có ASan/UBSan finding thuộc source học viên. Bằng chứng: exact command + sanitizer summary; rubric RB-A01-02/03.

## 🧪 Cách xác minh
**Phương thức:** artifact_review

- `cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build build/debug`
- `ctest --test-dir build/debug --output-on-failure`

**Bằng chứng phải nộp:**
- Version manifest
- Clean build log
- CTest summary
- Sanitizer summary
- Decision note

Mapping evidence: AT-A01-01 → version manifest + clean build log; AT-A01-02 → CTest report ghi tên từng fixture và golden result; AT-A01-03 → sanitizer command/log. Decision note và submission manifest cho phép reviewer truy ngược RB-A01-04. Evidence chỉ được ghi PASS khi command thực chạy với exit `0`; ảnh chụp không thay thế text log.

## 📊 Rubric chấm điểm — tổng 100%
| ID | Tiêu chí | Trọng số | Learning Outcomes | Bằng chứng | Mức hiệu suất |
|---|---|---:|---|---|---|
| RB-A01-01 | Dispatcher và generic behavior đúng contract | 40% | ADVC-H1SD | AT-A01-02 test report | **pass:** Tất cả required behavior/edge fixtures pass<br>**fail:** Có required fixture fail hoặc callback contract sai |
| RB-A01-02 | Pointer, type và bounds safety | 25% | ADVC-H1SD | Code review plus AT-A01-03 | **pass:** Không unsafe cast/bounds defect và sanitizer oracle đạt<br>**fail:** Có unsafe cast, UB hoặc finding mức chặn |
| RB-A01-03 | Build/test evidence tái lập | 25% | ADVC-H1SD | AT-A01-01..03 and version manifest | **pass:** Commands, expected results và evidence đầy đủ<br>**fail:** Thiếu command/result hoặc evidence không khớp |
| RB-A01-04 | Decision note và bàn giao | 10% | ADVC-H1SD | A01 decision note and submission manifest | **pass:** Giải thích typedef, null/zero và comparator decisions có evidence<br>**fail:** Thiếu quyết định hoặc artifact bàn giao |

**Điểm đạt:** 70%


## 📚 Nguồn đầu vào và provenance

### Nguồn đã map
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
Không sử dụng nguồn bổ sung hoặc giả định ngoài plan. Assignment dùng fixture synthetic nguyên gốc của khóa; học viên không được sao chép code từ tài liệu tham khảo. ISO/WG14/GNU/CERT/LLVM/Valgrind chỉ được dùng để đối chiếu và paraphrase quy tắc đã học.

---

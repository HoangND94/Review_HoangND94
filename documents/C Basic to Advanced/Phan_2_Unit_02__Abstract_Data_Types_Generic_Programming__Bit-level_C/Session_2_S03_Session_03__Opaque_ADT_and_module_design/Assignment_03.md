# Session S03: Session 03 — Opaque ADT and module design — Assignment 03

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 02 — Abstract Data Types, Generic Programming & Bit-level C

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASM-A03 (Assignment 03) |
| Thời lượng dự kiến | 120 phút |
| Độ khó | hard |
| Bloom levels | - create |
| Mức xác thực | simulated |

## 🎯 Learning Outcomes được đánh giá
- **ADVC-H1SD** [create] — Thiết kế, hiện thực và kiểm chứng các mô-đun C17 dùng con trỏ nâng cao, quản lý bộ nhớ động, ADT đóng gói và cấu trúc dữ liệu generic mà không làm lộ ownership hoặc gây lỗi bộ nhớ trong các ca kiểm thử đã cho. · Bằng chứng: Public API/header và implementation C biên dịch với warning profile đã chốt; unit tests đạt; sanitizer hoặc Valgrind không báo lỗi thuộc phạm vi fixture.

**Chuỗi truy vết ADVC-H1SD:** Opaque event ring core v3 + public API contract + tests/memory evidence + decision note → AT-A03-01..05 → RB-A03-01..05. OUT-S03-01 đã được dạy trong Material và thực hành nhận thức qua CASE-S03-01; bài đánh giá transfer bằng adapter/regression/failure fixtures mới.

## 🧠 Khái niệm và best practices được đánh giá
### CA-A03-MODULE — Opaque ring-buffer module contract transfer
- **Khái niệm/outline:** OUT-S03-01
- **Learning Outcomes:** ADVC-H1SD
- **Scenario:** Gateway core cần thêm FIFO event boundary có representation private, status nhất quán, defensive checks và ownership/thread-safety contract mà không làm regression command/memory core v2.
- **Inputs:** Memory-safe command core v2; DC-EVENT; Synthetic command and telemetry fixtures; Public contract pack; Change request CR-A03
- **Best-practice constraints:**
  - **Public header chỉ forward-declare opaque type và expose operations qua handle có prototype đầy đủ.** — Lý do: Incomplete type ngăn caller sizeof/dereference representation và cho phép implementation thay đổi mà giữ source-level API.; Concepts: OUT-S03-01; Acceptance tests: AT-A03-01, AT-A03-02; Rubric: RB-A03-01, RB-A03-02
  - **Public header self-contained và private file-scope helpers/objects dùng internal linkage.** — Lý do: Header boundary rõ làm giảm namespace pollution, conflicting definitions và accidental access tới implementation detail.; Concepts: OUT-S03-01; Acceptance tests: AT-A03-01; Rubric: RB-A03-02, RB-A03-05
  - **Mỗi operation ghi nullability, precondition, postcondition, output-on-error và state-on-error; validate trước mutation.** — Lý do: Contract failure-atomic và defensive checks biến invalid inputs thành observable status thay vì partial state corruption.; Concepts: OUT-S03-01; Acceptance tests: AT-A03-02, AT-A03-03; Rubric: RB-A03-01, RB-A03-02, RB-A03-03
  - **Dùng một status type nhất quán, tách status khỏi output và không yêu cầu caller đọc errno nếu API không công bố errno contract.** — Lý do: In-band indicators và stale errno làm lỗi dễ bị bỏ qua hoặc diễn giải sai; explicit status hỗ trợ exhaustive tests.; Concepts: OUT-S03-01; Acceptance tests: AT-A03-03, AT-A03-04; Rubric: RB-A03-02, RB-A03-05
  - **Công bố rõ create/destroy ownership, copy-versus-borrow payload, pointer invalidation và not-thread-safe/external-synchronization guarantee.** — Lý do: Ownership và thread-safety không được suy ra từ signature; thiếu declaration dẫn tới dangling references, double free hoặc data race ở increment sau.; Concepts: OUT-S03-01; Acceptance tests: AT-A03-04, AT-A03-05; Rubric: RB-A03-03, RB-A03-04, RB-A03-05
- **Deliverables:** Opaque event ring core v3; A03 public API contract; A03 unit/regression tests and memory evidence; A03 ownership, error and thread-safety decision note
- **Acceptance tests và oracle quan sát được:**
  - **AT-A03-01** [ADVC-H1SD] — Public header compile test và expected-failure opacity probe; Expected: Consumer TU chỉ include public header build thành công; probe cố sizeof/dereference opaque type bị compiler từ chối; public header không có complete ring struct; Evidence/rubric: RB-A03-01: AT-A03-02 plus A01–A02 regression result; RB-A03-02: AT-A03-01, AT-A03-03 and public API review; RB-A03-03: AT-A03-03..05 and memory reports; RB-A03-04: Commands and reports for AT-A03-01..05; RB-A03-05: A03 ownership, error and thread-safety decision note
  - **AT-A03-02** [ADVC-H1SD] — Ring behavior test empty, single, full, FIFO và wrap-around qua nhiều vòng; Expected: Size/capacity/status và output sequence khớp golden oracle; không overwrite unread event; Evidence/rubric: RB-A03-01: AT-A03-02 plus A01–A02 regression result; RB-A03-02: AT-A03-01, AT-A03-03 and public API review; RB-A03-03: AT-A03-03..05 and memory reports; RB-A03-04: Commands and reports for AT-A03-01..05; RB-A03-05: A03 ownership, error and thread-safety decision note
  - **AT-A03-03** [ADVC-H1SD] — Defensive parameter, allocation-failure và failure-atomic state tests; Expected: Mọi invalid/failure fixture trả documented status; observable ring state giữ nguyên khi contract yêu cầu; Evidence/rubric: RB-A03-01: AT-A03-02 plus A01–A02 regression result; RB-A03-02: AT-A03-01, AT-A03-03 and public API review; RB-A03-03: AT-A03-03..05 and memory reports; RB-A03-04: Commands and reports for AT-A03-01..05; RB-A03-05: A03 ownership, error and thread-safety decision note
  - **AT-A03-04** [ADVC-H1SD] — Ownership/lifetime/error/thread-safety contract review bằng executable lifecycle fixtures; Expected: Create/use/reset/destroy sequence đúng; borrowed/owned bytes và external-synchronization boundary khớp API contract; Evidence/rubric: RB-A03-01: AT-A03-02 plus A01–A02 regression result; RB-A03-02: AT-A03-01, AT-A03-03 and public API review; RB-A03-03: AT-A03-03..05 and memory reports; RB-A03-04: Commands and reports for AT-A03-01..05; RB-A03-05: A03 ownership, error and thread-safety decision note
  - **AT-A03-05** [ADVC-H1SD] — A01–A02 regression cùng ASan+UBSan và Valgrind ring stress runs; Expected: Regression exit 0; sanitizer không finding; Valgrind 0 invalid access và 0 definite/indirect leak theo policy; Evidence/rubric: RB-A03-01: AT-A03-02 plus A01–A02 regression result; RB-A03-02: AT-A03-01, AT-A03-03 and public API review; RB-A03-03: AT-A03-03..05 and memory reports; RB-A03-04: Commands and reports for AT-A03-01..05; RB-A03-05: A03 ownership, error and thread-safety decision note

**Ranh giới đánh giá:** opaque/header boundary → AT-A03-01/RB-A03-02; FIFO/capacity/integration → AT-A03-02/05/RB-A03-01; defensive failure → AT-A03-03/RB-A03-02/03; ownership/thread-safety → AT-A03-04/05/RB-A03-03/05; reproducibility → RB-A03-04. Đề chốt oracle, không chốt struct, index arithmetic hay cleanup flow.

## 🧭 Bối cảnh nghề nghiệp/dự án và change request

**Bối cảnh nghề nghiệp/dự án:**
**MDB Edge Diagnostics Gateway — Simulated** — Cổng chẩn đoán và telemetry chạy local trên Linux cho thiết bị giả lập; tiếp nhận command, quản lý work records, thực thi backend process/thread và phục vụ protocol TCP loopback. Vai trò học viên: C systems developer chịu trách nhiệm phát triển và harden từng increment trong repository đào tạo. Mục tiêu: Bàn giao một gateway TCP loopback tích hợp core C17, process/thread backends và quality evidence; phục vụ ít nhất 100 client synthetic theo Assignment 09 mà không có finding mức chặn trong oracle áp dụng.

**Project increment/change request cần hoàn thành:**
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

**Scenario đã chốt trong plan:**
Hoàn thiện increment M03 bằng một ring-buffer FIFO cho synthetic event records, chỉ truy cập qua opaque handle; API phải có defensive checks, status rõ, ownership/lifetime contract và tuyên bố thread-safety kiểm chứng được.

Bạn là maintainer nhận CR-A03 cho gateway mô phỏng. Memory-safe command core v2 đã pass M01–M02 nhưng chưa có boundary FIFO để giữ event synthetic trước khi container layer S04 xử lý. Consumer team yêu cầu một public API ổn định, không thấy representation, và cần biết chính xác ownership/error/invalidation/thread-safety. Bài phải tích hợp với core v2 và bảo toàn regression; event schema/fixture khác CASE-S03-01.

## 🔗 Liên kết project xuyên suốt

**Project milestone:**
M03

**Phụ thuộc vào Assignment trước:**
- ASM-A02

**Baseline artifacts được sử dụng:**
- Memory-safe command core v2

**Artifacts Assignment này tạo ra:**
- Opaque event ring core v3

**Assignment sau sẽ tái sử dụng:**
- ASM-A04

**Terminal delivery (chỉ Assignment cuối):**
Không áp dụng — đây là increment trung gian; sản phẩm được Assignment kế tiếp sử dụng.


## 🧰 Điều kiện thực hiện

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

### Input và starter assets
- Memory-safe command core v2
- DC-EVENT
- Synthetic command and telemetry fixtures
- Public contract pack
- Change request CR-A03

Starter pack gồm Memory-safe command core v2 đã qua acceptance, `starter/assignment-03/README.md`, DC-EVENT, public contract pack, command/telemetry fixtures synthetic và CR-A03. Fixtures bao phủ zero capacity, empty/single/full, nhiều vòng wrap, null handle/element/output, allocation failure, reset/destroy lifecycle, adapter input và A01–A02 regression. Không có secret, PII, network endpoint hay production data. Học viên không sửa golden fixtures/public upstream behavior.

## 📋 Yêu cầu

### Functional requirements
- **FR-A03-01 [ADVC-H1SD]:** Public API cung cấp create/destroy, capacity/size, push, peek hoặc pop và reset qua opaque handle; consumer không thể `sizeof`/dereference internals. Bằng chứng: public API + AT-A03-01/02.
- **FR-A03-02 [ADVC-H1SD]:** Empty, single, full, FIFO và wrap-around qua nhiều chu kỳ đúng một capacity model đã công bố; full không overwrite unread event. Bằng chứng: core v3 + AT-A03-02.
- **FR-A03-03 [ADVC-H1SD]:** Null handle/element/output, zero capacity, full/empty và injected allocation failure trả status deterministic; operation lỗi giữ observable state theo contract. Bằng chứng: AT-A03-03/04.
- **FR-A03-04 [ADVC-H1SD]:** Core v2 có adapter đưa DC-EVENT synthetic vào ring; toàn bộ A01–A02 regression vẫn pass. Bằng chứng: integration source + AT-A03-05.

### Non-functional requirements
- **NFR-A03-01 [ADVC-H1SD]:** Public header self-contained/include guard, chỉ public declarations; complete ring struct và private helper không xuất hiện. Oracle: standalone header compile + expected-failure opacity probe AT-A03-01.
- **NFR-A03-02 [ADVC-H1SD]:** API contract ghi owned/borrowed/copy payload, destroy/reset invalidation và mặc định `not thread-safe; external synchronization required`; claim mạnh hơn chỉ hợp lệ khi có design/oracle tương ứng. Bằng chứng: contract + AT-A03-04/05.
- **NFR-A03-03 [ADVC-H1SD]:** size arithmetic kiểm overflow trước allocation/indexing; ASan+UBSan và Valgrind chạy trên binary riêng, regression/stress exit `0` và không finding mức chặn. Bằng chứng: AT-A03-03/05 logs.

### Ràng buộc và phạm vi loại trừ
- CMake scaffold được cấp sẵn và không được chấm như kiến thức CMake trước Session 05
- Không expose complete ring struct, head, tail, count hoặc backing storage trong public header
- Chọn và document một capacity model: count-based hoặc sentinel-slot; public capacity phải có một nghĩa duy nhất
- Không tuyên bố lock-free hoặc thread-safe nếu không có synchronization design và oracle tương ứng
- Mọi operation lỗi phải giữ state theo failure-state contract
- Không copy Linux kernel circular-buffer macros hoặc memory-barrier implementation

CMake scaffold chỉ là phương tiện chạy và không được chấm trước S05. Không expose complete struct/state/storage; không dùng Linux kernel circular macros/barriers; không claim lock-free/thread-safe thiếu design/test; không đổi status để che error; không chạy Valgrind trên sanitizer binary. Ngoài phạm vi: concurrent ring, zero-copy borrowed payload bắt buộc, dynamic resizing, performance benchmark và S04 generic/bit-level features.

> [!IMPORTANT]
> Đây là bài làm độc lập. Đề bài không cung cấp quy trình từng bước, code hoàn chỉnh hoặc đáp án. Có thể điều hướng tới khái niệm/Case Study đã học nhưng không được lộ lời giải cho change request này.

## 📦 Deliverables và cách nộp
- Opaque event ring core v3
- A03 public API contract
- A03 unit/regression tests and memory evidence
- A03 ownership, error and thread-safety decision note

**Submission contract:**
Nộp snapshot M03 cùng public/private source, tests, API contract và evidence manifest đã redact; không nộp build cache hoặc dữ liệu ngoài synthetic fixtures.

- **Opaque event ring core v3:** public/private source và adapter core v2; đủ khi AT-A03-01/02/05 resolve và upstream regression pass.
- **A03 public API contract:** public declarations cùng nullability/pre/post/output-on-error/state-on-error/status/capacity/ownership/invalidation/thread-safety specification; đủ khi mỗi operation có test ref.
- **A03 unit/regression tests and memory evidence:** positive/negative/failure/lifecycle/stress fixtures, opacity/header compile reports, A01–A02 regression, sanitizer và Valgrind summaries từ binary riêng; đủ khi ghi command/version/exit code.
- **A03 decision note:** capacity model, representation boundary, error convention, copy/borrow, lifecycle/reset, overflow, synchronization guarantee và trade-off; mỗi claim trỏ acceptance evidence.
- Snapshot không chứa build cache, external data hoặc secret; submission manifest liệt kê đủ artifact.

## ✅ Acceptance criteria và output mong đợi
- **AT-A03-01 [ADVC-H1SD]:** Given clean consumer translation units, when một unit chỉ include public header và unit khác thử `sizeof`/dereference opaque type, then consumer bình thường build `0`, opacity probe build nonzero đúng lỗi incomplete type, header không lộ complete struct/helper. Bằng chứng: compile reports; RB-A03-02/04.
- **AT-A03-02 [ADVC-H1SD]:** Given capacity đã chốt và event sequence golden, when chạy empty/single/fill/full/pop/wrap/drain nhiều vòng, then size/capacity/status/FIFO khớp oracle và full không overwrite. Bằng chứng: named fixture report; RB-A03-01.
- **AT-A03-03 [ADVC-H1SD]:** Given null/zero/full/empty/arithmetic/allocation-failure fixtures và state snapshot, when gọi operation, then documented status trả về, output/error value đúng contract và state giữ nguyên trên nhánh fail. Bằng chứng: before/after assertions; RB-A03-02/03.
- **AT-A03-04 [ADVC-H1SD]:** Given lifecycle fixture, when create/use/reset/use/destroy và kiểm copy/borrow boundary, then owner/invalidation/status/thread-safety statements khớp observable behavior. Bằng chứng: contract review + executable result; RB-A03-03/05.
- **AT-A03-05 [ADVC-H1SD]:** Given integrated core v3 và binary tách biệt, when chạy A01–A02 regression, sanitizer suite và Valgrind stress, then regression exit `0`, sanitizer no finding, Valgrind `0` invalid access và `0` definite/indirect leak. Bằng chứng: three summaries; RB-A03-01/03/04.

## 🧪 Cách xác minh
**Phương thức:** artifact_review

- `cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build build/debug`
- `ctest --test-dir build/debug --output-on-failure`
- `cmake -S . -B build/sanitize -DCMAKE_BUILD_TYPE=Debug -DADVC_ENABLE_SANITIZERS=ON`
- `cmake --build build/sanitize`
- `ctest --test-dir build/sanitize --output-on-failure`
- `valgrind --tool=memcheck --leak-check=full --errors-for-leak-kinds=definite,indirect --error-exitcode=99 ./build/debug/tests/ring_tests`

**Bằng chứng phải nộp:**
- Public-header and opacity compile report
- Ring behavior and lifecycle CTest summary
- A01–A02 regression summary
- ASan+UBSan summary
- Valgrind summary
- Ownership, error and thread-safety decision note

Evidence mapping: AT-A03-01 → header/negative-probe compile report; AT-A03-02 → FIFO/capacity CTest; AT-A03-03 → invalid/fault-injection state snapshots; AT-A03-04 → lifecycle result + API decision table; AT-A03-05 → upstream regression, sanitizer và Valgrind logs. Mỗi report ghi exact command/version/exit code; expected compile failure chỉ PASS khi lỗi đúng opaque contract, không phải lỗi include/path.

## 📊 Rubric chấm điểm — tổng 100%
| ID | Tiêu chí | Trọng số | Learning Outcomes | Bằng chứng | Mức hiệu suất |
|---|---|---:|---|---|---|
| RB-A03-01 | FIFO behavior, capacity model and command-core integration | 35% | ADVC-H1SD | AT-A03-02 plus A01–A02 regression result | **pass:** Empty/full/wrap/FIFO behavior và integration fixtures đều pass<br>**fail:** Có FIFO, capacity, state hoặc regression failure |
| RB-A03-02 | Opaque boundary, header hygiene and API/error contract | 25% | ADVC-H1SD | AT-A03-01, AT-A03-03 and public API review | **pass:** Representation private, header self-contained và status/state contract nhất quán<br>**fail:** Public header lộ internals hoặc API/error behavior mơ hồ/sai |
| RB-A03-03 | Ownership, arithmetic and memory safety | 20% | ADVC-H1SD | AT-A03-03..05 and memory reports | **pass:** Lifetime/overflow/failure paths đúng và không có finding mức chặn<br>**fail:** Có dangling/double-free/overflow/invalid-access/leak finding hoặc state corruption |
| RB-A03-04 | Executable tests and reproducible evidence | 10% | ADVC-H1SD | Commands and reports for AT-A03-01..05 | **pass:** Required tests/oracles chạy lại được và evidence khớp expected results<br>**fail:** Thiếu command/result, test không deterministic hoặc evidence không resolve |
| RB-A03-05 | Ownership, error and thread-safety decision note | 10% | ADVC-H1SD | A03 ownership, error and thread-safety decision note | **pass:** Nêu rõ capacity, status, ownership, invalidation và synchronization boundary cùng trade-offs<br>**fail:** Thiếu decision hoặc tuyên bố thread-safety/ownership không được implementation và tests hỗ trợ |

**Điểm đạt:** 70%


## 📚 Nguồn đầu vào và provenance

### Nguồn đã map
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
Không sử dụng nguồn bổ sung hoặc giả định ngoài plan. Event/command fixtures là synthetic. Học viên không được sao chép Linux kernel circular-buffer macros/memory barriers hay implementation bên ngoài; C17/GNU/CERT/Linux/LLVM/Valgrind chỉ được dùng để đối chiếu và paraphrase contract/quy tắc đã học.

---

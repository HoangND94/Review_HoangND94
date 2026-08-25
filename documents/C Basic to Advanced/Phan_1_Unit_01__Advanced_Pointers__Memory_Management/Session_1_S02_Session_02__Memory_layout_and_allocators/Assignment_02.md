# Session S02: Session 02 — Memory layout and allocators — Assignment 02

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 01 — Advanced Pointers & Memory Management

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASM-A02 (Assignment 02) |
| Thời lượng dự kiến | 90 phút |
| Độ khó | hard |
| Bloom levels | - create |
| Mức xác thực | simulated |

## 🎯 Learning Outcomes được đánh giá
- **ADVC-H1SD** [create] — Thiết kế, hiện thực và kiểm chứng các mô-đun C17 dùng con trỏ nâng cao, quản lý bộ nhớ động, ADT đóng gói và cấu trúc dữ liệu generic mà không làm lộ ownership hoặc gây lỗi bộ nhớ trong các ca kiểm thử đã cho. · Bằng chứng: Public API/header và implementation C biên dịch với warning profile đã chốt; unit tests đạt; sanitizer hoặc Valgrind không báo lỗi thuộc phạm vi fixture.

**Chuỗi truy vết ADVC-H1SD:** Memory-safe command core v2 + memory evidence + layout/ownership note → AT-A02-01..03 → RB-A02-01..04. OUT-S02-01 đã được dạy trong Material và minh họa bằng CASE-S02-01; bài đánh giá transfer qua integration với Dispatcher module v1.

## 🧠 Khái niệm và best practices được đánh giá
### CA-A02-MEM — Pool allocator and layout decision
- **Khái niệm/outline:** OUT-S02-01
- **Learning Outcomes:** ADVC-H1SD
- **Scenario:** Dispatcher v1 phải dùng bounded pool mà vẫn xử lý allocation failure và reset an toàn.
- **Inputs:** Dispatcher module v1; Synthetic command and telemetry fixtures; Change request CR-A02
- **Best-practice constraints:**
  - **Kiểm tra overflow, alignment, membership và ownership trước khi thay đổi pool state.** — Lý do: Allocator pattern không được C chuẩn hóa; invariant cục bộ là oracle duy nhất ngăn out-of-bounds, foreign/double free.; Concepts: OUT-S02-01; Acceptance tests: AT-A02-01, AT-A02-02, AT-A02-03; Rubric: RB-A02-01, RB-A02-02, RB-A02-03
  - **Dùng temporary pointer cho nonzero-size realloc và không raw-copy padding làm external data.** — Lý do: realloc failure giữ block cũ; padding/endianness không phải portable wire representation.; Concepts: OUT-S02-01; Acceptance tests: AT-A02-01, AT-A02-03; Rubric: RB-A02-02, RB-A02-04
- **Deliverables:** Memory-safe command core v2; A02 memory evidence; A02 layout and ownership note
- **Acceptance tests và oracle quan sát được:**
  - **AT-A02-01** [ADVC-H1SD] — Layout probe và block alignment kiểm sizeof/_Alignof/offsetof trên target; Expected: Mọi block đúng alignment; report phân biệt portable C với ELF/Linux observation; Evidence/rubric: RB-A02-01: AT-A02-02 and M01 regression; RB-A02-02: AT-A02-01 and AT-A02-03; RB-A02-03: Commands and reports for AT-A02-01..03; RB-A02-04: A02 layout and ownership note
  - **AT-A02-02** [ADVC-H1SD] — Pool test exhaustion, uniqueness, reuse, reset, foreign pointer và double free; Expected: Mọi state/status khớp contract; M01 regression suite vẫn pass; Evidence/rubric: RB-A02-01: AT-A02-02 and M01 regression; RB-A02-02: AT-A02-01 and AT-A02-03; RB-A02-03: Commands and reports for AT-A02-01..03; RB-A02-04: A02 layout and ownership note
  - **AT-A02-03** [ADVC-H1SD] — Memory checker chạy stress allocation fixture; Expected: 0 invalid access và 0 definite/indirect leak theo policy công bố; Evidence/rubric: RB-A02-01: AT-A02-02 and M01 regression; RB-A02-02: AT-A02-01 and AT-A02-03; RB-A02-03: Commands and reports for AT-A02-01..03; RB-A02-04: A02 layout and ownership note

**Ranh giới đánh giá:** CA-A02-MEM được quan sát qua layout/alignment report AT-A02-01, state/regression fixture AT-A02-02 và memory checker AT-A02-03. Học viên tự chọn representation/free-list và capacity bookkeeping; đề chỉ chốt hành vi, invariants, evidence và các policy phải công bố.

## 🧭 Bối cảnh nghề nghiệp/dự án và change request

**Bối cảnh nghề nghiệp/dự án:**
**MDB Edge Diagnostics Gateway — Simulated** — Cổng chẩn đoán và telemetry chạy local trên Linux cho thiết bị giả lập; tiếp nhận command, quản lý work records, thực thi backend process/thread và phục vụ protocol TCP loopback. Vai trò học viên: C systems developer chịu trách nhiệm phát triển và harden từng increment trong repository đào tạo. Mục tiêu: Bàn giao một gateway TCP loopback tích hợp core C17, process/thread backends và quality evidence; phục vụ ít nhất 100 client synthetic theo Assignment 09 mà không có finding mức chặn trong oracle áp dụng.

**Project increment/change request cần hoàn thành:**
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

**Scenario đã chốt trong plan:**
Thêm pool alignment-safe cho command records của dispatcher v1 và tối ưu layout record synthetic mà không đổi observable command behavior.

Bạn là maintainer tiếp nhận CR-A02 cho gateway mô phỏng. Dispatcher module v1 đã pass M01 nhưng mỗi command record còn cấp phát qua heap chung. Stakeholder yêu cầu một pool bounded, alignment-safe để exhaustion và reset có thể dự đoán, đồng thời không thay đổi status/output command hiện có. Bài dùng record/fixture của starter pack, khác fixed pool độc lập trong CASE-S02-01; không có dữ liệu thật.

## 🔗 Liên kết project xuyên suốt

**Project milestone:**
M02

**Phụ thuộc vào Assignment trước:**
- ASM-A01

**Baseline artifacts được sử dụng:**
- Dispatcher module v1

**Artifacts Assignment này tạo ra:**
- Memory-safe command core v2

**Assignment sau sẽ tái sử dụng:**
- ASM-A03

**Terminal delivery (chỉ Assignment cuối):**
Không áp dụng — đây là increment trung gian; sản phẩm được Assignment kế tiếp sử dụng.


## 🧰 Điều kiện thực hiện

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

### Input và starter assets
- Dispatcher module v1
- Synthetic command and telemetry fixtures
- Change request CR-A02

Starter pack gồm Dispatcher module v1 đã qua acceptance, `starter/assignment-02/README.md`, command/telemetry fixtures synthetic và CR-A02. Hidden/public fixtures bao phủ capacity 0/1/maximum được công bố, exhaustion, uniqueness, reuse, reset, foreign pointer, interior pointer, double free, arithmetic cực trị và M01 regression. Không có account, endpoint, secret hoặc PII. Học viên giữ nguyên public contract M01 và ghi rõ mọi assumptions trong decision note.

## 📋 Yêu cầu

### Functional requirements
- **FR-A02-01 [ADVC-H1SD]:** `init/alloc/free/reset` giữ capacity/free-state invariants; mỗi allocation sống là unique và aligned; bằng chứng ở core v2 và AT-A02-01/02.
- **FR-A02-02 [ADVC-H1SD]:** Exhaustion không mutate state; reuse, foreign/interior pointer và double-free trả status đúng policy; reset làm invalid mọi derived pointer theo contract; bằng chứng ở AT-A02-02/03.
- **FR-A02-03 [ADVC-H1SD]:** Dispatcher cấp bounded command records qua pool sau init, không dùng heap ở fast path và giữ toàn bộ M01 observable behavior/tests pass; bằng chứng ở regression report AT-A02-02.

### Non-functional requirements
- **NFR-A02-01 [ADVC-H1SD]:** mọi `count*size`, stride và boundary arithmetic được kiểm overflow trước phép toán có thể wrap; mỗi block thỏa alignment đã công bố. Oracle: layout report + boundary fixture AT-A02-01/03.
- **NFR-A02-02 [ADVC-H1SD]:** debug binary chạy Valgrind **hoặc** sanitizer binary riêng chạy ASan+UBSan; fixture exit `0`, không invalid access và không definite/indirect leak theo policy. Exact command/version nằm trong evidence.

### Ràng buộc và phạm vi loại trừ
- Không malloc/free trong fast path sau pool init
- Reset invalidates mọi derived pointer và phải được document
- Không serialize raw struct layout
- Không chạy Valgrind trên ASan binary

Không `malloc/free` trong fast path sau pool init; init-time allocation chỉ được dùng nếu contract/starter cho phép. Không serialize raw struct, không dựa vào một giá trị `sizeof` cố định trên mọi target, không chạy Valgrind trên ASan binary và không bỏ negative test để có report sạch. Ngoài phạm vi: concurrent allocator, lock-free, custom virtual-memory mapping, benchmark throughput và CMake design.

> [!IMPORTANT]
> Đây là bài làm độc lập. Đề bài không cung cấp quy trình từng bước, code hoàn chỉnh hoặc đáp án. Có thể điều hướng tới khái niệm/Case Study đã học nhưng không được lộ lời giải cho change request này.

## 📦 Deliverables và cách nộp
- Memory-safe command core v2
- A02 memory evidence
- A02 layout and ownership note

**Submission contract:**
Nộp snapshot M02 cùng source, tests và evidence đã redact; build artifacts không tính là deliverable.

- **Memory-safe command core v2:** source/header và integration vào dispatcher; đủ khi pool behavior và M01 regression resolve qua AT-A02-02.
- **A02 memory evidence:** layout report (`sizeof/_Alignof/offsetof`, portable-vs-Linux boundary), per-fixture state results và một Valgrind hoặc ASan/UBSan summary; đủ khi ghi exact command/version/exit code.
- **A02 layout and ownership note:** capacity/block/alignment, overflow, ownership, exhaustion/free/reset/invalidation, endian/serialization decisions và trade-off; mỗi claim trỏ acceptance evidence.
- Snapshot M02 không chứa build artifacts, external dataset hay unredacted machine-specific secret; submission manifest liệt kê đủ artifact.

## ✅ Acceptance criteria và output mong đợi
- **AT-A02-01 [ADVC-H1SD]:** Given target đã fingerprint và pool mới init, when chạy layout probe/allocate mọi slot, then report ghi `sizeof/_Alignof/offsetof`, mọi địa chỉ thỏa advertised alignment và phân biệt C portable facts với ELF/Linux observations. Bằng chứng: report + assertions; rubric RB-A02-02/03/04.
- **AT-A02-02 [ADVC-H1SD]:** Given public state fixtures, when chạy exhaustion/uniqueness/reuse/reset/foreign/interior/double-free rồi M01 regression, then từng status/state khớp golden contract, nhánh lỗi không corrupt state và M01 vẫn pass. Bằng chứng: named test report; rubric RB-A02-01/03.
- **AT-A02-03 [ADVC-H1SD]:** Given stress/boundary fixture và memory-check profile tách biệt, when chạy, then exit `0`, `0` invalid access và `0` definite/indirect leak; overflow fixture fail an toàn trước mutation. Bằng chứng: checker log; rubric RB-A02-02/03.

## 🧪 Cách xác minh
**Phương thức:** artifact_review

- `cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build build/debug`
- `ctest --test-dir build/debug --output-on-failure`
- `valgrind --tool=memcheck --leak-check=full --errors-for-leak-kinds=definite,indirect --error-exitcode=99 ./build/debug/tests/pool_tests`

**Bằng chứng phải nộp:**
- Layout report
- CTest summary
- Valgrind or ASan summary
- Ownership/reset decision note

Evidence mapping: AT-A02-01 → layout/alignment report; AT-A02-02 → pool state table + M01 CTest regression; AT-A02-03 → exact checker command/log. Ownership/reset note là evidence RB-A02-04 và phải nêu pointer invalidation. Chỉ ghi PASS khi command thực chạy; nếu dùng ASan thay Valgrind, nộp build/run command của binary sanitizer riêng và lý do lựa chọn.

## 📊 Rubric chấm điểm — tổng 100%
| ID | Tiêu chí | Trọng số | Learning Outcomes | Bằng chứng | Mức hiệu suất |
|---|---|---:|---|---|---|
| RB-A02-01 | Pool behavior và integration đúng | 40% | ADVC-H1SD | AT-A02-02 and M01 regression | **pass:** Mọi required state/behavior pass<br>**fail:** Có invariant, status hoặc regression failure |
| RB-A02-02 | Alignment, overflow và memory safety | 30% | ADVC-H1SD | AT-A02-01 and AT-A02-03 | **pass:** Oracle alignment/overflow/memory đạt<br>**fail:** Có unsafe arithmetic, misalignment hoặc memory finding |
| RB-A02-03 | Tests/evidence tái lập | 20% | ADVC-H1SD | Commands and reports for AT-A02-01..03 | **pass:** Evidence đủ và khớp expected<br>**fail:** Thiếu command/result hoặc report không resolve |
| RB-A02-04 | Layout/ownership decision note | 10% | ADVC-H1SD | A02 layout and ownership note | **pass:** Nêu portable boundary, lifetime/reset và trade-off<br>**fail:** Thiếu quyết định hoặc nhầm raw layout là contract |

**Điểm đạt:** 70%


## 📚 Nguồn đầu vào và provenance

### Nguồn đã map
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
Không sử dụng nguồn bổ sung hoặc giả định ngoài plan. Fixture là synthetic và code phải do học viên tạo; tài liệu C17/GNU/glibc/binutils/CERT/LLVM/Valgrind chỉ phục vụ đối chiếu/paraphrase, không cấp implementation allocator để sao chép.

---

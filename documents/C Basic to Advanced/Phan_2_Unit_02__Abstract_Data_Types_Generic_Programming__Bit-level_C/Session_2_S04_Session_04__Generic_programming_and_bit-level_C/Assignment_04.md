# Session S04: Session 04 — Generic programming and bit-level C — Assignment 04

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 02 — Abstract Data Types, Generic Programming & Bit-level C

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASM-A04 (Assignment 04) |
| Thời lượng dự kiến | 120 phút |
| Độ khó | hard |
| Bloom levels | - create |
| Mức xác thực | simulated |

## 🎯 Learning Outcomes được đánh giá
- **ADVC-H1SD** [create] — Thiết kế, hiện thực và kiểm chứng các mô-đun C17 dùng con trỏ nâng cao, quản lý bộ nhớ động, ADT đóng gói và cấu trúc dữ liệu generic mà không làm lộ ownership hoặc gây lỗi bộ nhớ trong các ca kiểm thử đã cho. · Bằng chứng: Public API/header và implementation C biên dịch với warning profile đã chốt; unit tests đạt; sanitizer hoặc Valgrind không báo lỗi thuộc phạm vi fixture.


## 🧠 Khái niệm và best practices được đánh giá
### CA-A04-CONTAINERS — Generic container and representation contract transfer
- **Khái niệm/outline:** OUT-S04-01
- **Learning Outcomes:** ADVC-H1SD
- **Scenario:** Gateway core cần reusable vector, intrusive list và flag registry với overflow/lifetime/membership guarantees, đồng thời phải chứng minh macro, bit-field, union và FAM portability boundaries trên synthetic data.
- **Inputs:** Opaque event ring core v3; DC-EVENT; Synthetic command and telemetry fixtures; Public contract pack; Change request CR-A04
- **Best-practice constraints:**
  - **Generic API mang element size/count, null/zero policy và overflow-safe capacity arithmetic; realloc qua temporary pointer.** — Lý do: void* không cung cấp element arithmetic hoặc ownership; explicit byte contract và failure atomicity ngăn overflow, data loss và stale state.; Concepts: OUT-S04-01; Acceptance tests: AT-A04-01, AT-A04-06; Rubric: RB-A04-01, RB-A04-04, RB-A04-05
  - **Ưu tiên static inline và _Generic dispatcher; parenthesize macro parameters và cấm side-effect arguments ở unsafe macro.** — Lý do: Macro replacement có thể evaluate argument zero hoặc nhiều lần; side effects làm behavior phụ thuộc expansion thay vì API contract.; Concepts: OUT-S04-01; Acceptance tests: AT-A04-05; Rubric: RB-A04-04, RB-A04-06
  - **Chỉ phục hồi container khi pointer trỏ exact named member của live object; document compiler target và giữ const contract.** — Lý do: Fabricated, unrelated, null hoặc expired member pointer không có enclosing-object guarantee và có thể tạo invalid provenance/alignment access.; Concepts: OUT-S04-01; Acceptance tests: AT-A04-03, AT-A04-06; Rubric: RB-A04-02, RB-A04-04
  - **Payload object sở hữu embedded link; node có explicit unlinked/linked state và safe-iteration rule khi remove.** — Lý do: Intrusive list gắn link lifetime với payload; double insertion, free-while-linked hoặc remove khi iteration có thể corrupt cả list.; Concepts: OUT-S04-01; Acceptance tests: AT-A04-02, AT-A04-06; Rubric: RB-A04-02, RB-A04-05
  - **Dùng unsigned fixed-width masks, kiểm tra shift count và công bố reject-or-preserve policy cho unknown bits.** — Lý do: Signed bitwise/shift và out-of-range shift gây undefined hoặc implementation-defined behavior; reserved policy tránh silent configuration drift.; Concepts: OUT-S04-01; Acceptance tests: AT-A04-04; Rubric: RB-A04-03, RB-A04-04
  - **Không dùng bit-field order, padding hoặc raw bytes làm portable wire/storage contract; external format dùng explicit masks and shifts.** — Lý do: Bit-field allocation order, alignment, straddling và plain-int signedness phụ thuộc implementation.; Concepts: OUT-S04-01; Acceptance tests: AT-A04-05; Rubric: RB-A04-04, RB-A04-06
  - **Pair union với explicit tag, chỉ đọc active member và encode external bytes field-by-field.** — Lý do: Inactive-member representation có thể unspecified hoặc trap-prone và không thiết lập portable serialization contract.; Concepts: OUT-S04-01; Acceptance tests: AT-A04-05; Rubric: RB-A04-04, RB-A04-06
  - **FAM là last member sau ít nhất một named member; allocate/copy/pass by pointer với overflow-safe extent và không access ngoài allocated element count.** — Lý do: sizeof không cấp usable trailing elements; by-value assignment/copy không mang payload extent và unchecked size math tạo out-of-bounds allocation.; Concepts: OUT-S04-01; Acceptance tests: AT-A04-05, AT-A04-06; Rubric: RB-A04-04, RB-A04-05
- **Deliverables:** Generic gateway core v4; A04 dynamic-array and intrusive-list tests; A04 flag and representation probes; A04 container ownership and portability decision note; A04 regression and memory evidence
- **Acceptance tests và oracle quan sát được:**
  - **AT-A04-01** [ADVC-H1SD] — Dynamic array test multiple element sizes, growth, shrink, removal, overflow and allocation failure; Expected: len <= cap luôn đúng; contents khớp golden oracle; overflow bị reject; realloc failure giữ old data/pointer/state theo contract; Evidence/rubric: RB-A04-01: AT-A04-01 and allocation-failure report; RB-A04-02: AT-A04-02 and AT-A04-03; RB-A04-03: AT-A04-04 truth-table report; RB-A04-04: AT-A04-01, AT-A04-03 and AT-A04-05; RB-A04-05: Commands and reports for AT-A04-01..06; RB-A04-06: A04 container ownership and portability decision note
  - **AT-A04-02** [ADVC-H1SD] — Intrusive list test empty/single/multi, head/tail insertion, removal, safe iteration và membership misuse; Expected: Forward/backward order và link invariants đúng; double insertion/foreign removal được reject theo contract; Evidence/rubric: RB-A04-01: AT-A04-01 and allocation-failure report; RB-A04-02: AT-A04-02 and AT-A04-03; RB-A04-03: AT-A04-04 truth-table report; RB-A04-04: AT-A04-01, AT-A04-03 and AT-A04-05; RB-A04-05: Commands and reports for AT-A04-01..06; RB-A04-06: A04 container ownership and portability decision note
  - **AT-A04-03** [ADVC-H1SD] — container_of compile/runtime probe cho exact member, nonzero offset và const-qualified access; Expected: Exact member pointer phục hồi đúng enclosing address; const contract không bị cast-away; invalid fixtures không được gọi như supported input; Evidence/rubric: RB-A04-01: AT-A04-01 and allocation-failure report; RB-A04-02: AT-A04-02 and AT-A04-03; RB-A04-03: AT-A04-04 truth-table report; RB-A04-04: AT-A04-01, AT-A04-03 and AT-A04-05; RB-A04-05: Commands and reports for AT-A04-01..06; RB-A04-06: A04 container ownership and portability decision note
  - **AT-A04-04** [ADVC-H1SD] — Bit-flag truth-table test set, clear, toggle, test, boundary bit và unknown/reserved mask; Expected: Mọi mask operation khớp truth table; reserved/unknown bits được reject hoặc preserve đúng documented policy; Evidence/rubric: RB-A04-01: AT-A04-01 and allocation-failure report; RB-A04-02: AT-A04-02 and AT-A04-03; RB-A04-03: AT-A04-04 truth-table report; RB-A04-04: AT-A04-01, AT-A04-03 and AT-A04-05; RB-A04-05: Commands and reports for AT-A04-01..06; RB-A04-06: A04 container ownership and portability decision note
  - **AT-A04-05** [ADVC-H1SD] — Macro, bit-field, union and flexible-array portability probes; Expected: Macro tests không phụ thuộc side-effect evaluation; layout report được gắn implementation-specific; tagged-union active member và FAM n=0/1/max/overflow fixtures đúng contract; Evidence/rubric: RB-A04-01: AT-A04-01 and allocation-failure report; RB-A04-02: AT-A04-02 and AT-A04-03; RB-A04-03: AT-A04-04 truth-table report; RB-A04-04: AT-A04-01, AT-A04-03 and AT-A04-05; RB-A04-05: Commands and reports for AT-A04-01..06; RB-A04-06: A04 container ownership and portability decision note
  - **AT-A04-06** [ADVC-H1SD] — A01–A03 regression cùng ASan+UBSan và Valgrind container stress runs; Expected: Regression exit 0; sanitizer không finding; Valgrind 0 invalid access và 0 definite/indirect leak theo policy; Evidence/rubric: RB-A04-01: AT-A04-01 and allocation-failure report; RB-A04-02: AT-A04-02 and AT-A04-03; RB-A04-03: AT-A04-04 truth-table report; RB-A04-04: AT-A04-01, AT-A04-03 and AT-A04-05; RB-A04-05: Commands and reports for AT-A04-01..06; RB-A04-06: A04 container ownership and portability decision note


## 🧭 Bối cảnh nghề nghiệp/dự án và change request

**Bối cảnh nghề nghiệp/dự án:**
**MDB Edge Diagnostics Gateway — Simulated** — Cổng chẩn đoán và telemetry chạy local trên Linux cho thiết bị giả lập; tiếp nhận command, quản lý work records, thực thi backend process/thread và phục vụ protocol TCP loopback. Vai trò học viên: C systems developer chịu trách nhiệm phát triển và harden từng increment trong repository đào tạo. Mục tiêu: Bàn giao một gateway TCP loopback tích hợp core C17, process/thread backends và quality evidence; phục vụ ít nhất 100 client synthetic theo Assignment 09 mà không có finding mức chặn trong oracle áp dụng.

**Project increment/change request cần hoàn thành:**
- **milestone_id:** M04
- **user_story:** Là core developer, tôi muốn reusable vector, intrusive list và flag registry có contract rõ để gateway quản lý heterogeneous metadata mà không nhân bản container logic.
- **business_value:** Cung cấp container layer tái sử dụng cho các build, process, thread và network increments sau trong khi giữ bounds, lifetime và representation portable.
- **baseline:** Opaque event ring core v3 đã qua M03.
- **change_scope:** - Generic dynamic array with grow/shrink policy<br>- Overflow-safe capacity arithmetic and failure-atomic realloc<br>- Original userspace container_of helper with documented preconditions<br>- Intrusive doubly linked list and membership invariants<br>- Unsigned bit-flag configuration registry<br>- Macro, bit-field, union and FAM portability probes<br>- A01–A03 regression and memory-safety evidence
- **inputs:** - Opaque event ring core v3<br>- DC-EVENT<br>- Synthetic command and telemetry fixtures<br>- Public contract pack
- **integration_points:** - opaque event ring<br>- generic containers and flags<br>- command dispatcher
- **artifacts_added:** - Generic gateway core v4<br>- A04 container and portability evidence
- **acceptance_criteria:** - FR-04 đạt<br>- NFR-01, NFR-02 và NFR-04 đạt<br>- M01–M03 behavior không regression<br>- Container and representation decisions có executable oracle
- **definition_of_done:** - Project Definition of Done áp dụng cho M04

**Scenario đã chốt trong plan:**
Hoàn thiện increment M04 bằng generic dynamic array, intrusive doubly linked list qua container_of và unsigned bit-flag registry cho synthetic gateway records; chứng minh grow/shrink, membership, representation và failure paths bằng executable oracles.

Bạn tiếp nhận event ring v3 đã accepted, nhưng adapter metadata hiện có container logic lặp lại và flags không có reserved-mask policy. Nhóm build M05 chỉ nhận core v4 nếu vector/list/flag contracts có executable oracles và representation note rõ. CR-A04 dùng nhiều element sizes, fixtures và adapter integration khác case GRC-04 trong `example.md`; nộp lại asset mẫu không thỏa Assignment.

## 🔗 Liên kết project xuyên suốt

**Project milestone:**
M04

**Phụ thuộc vào Assignment trước:**
- ASM-A03

**Baseline artifacts được sử dụng:**
- Opaque event ring core v3

**Artifacts Assignment này tạo ra:**
- Generic gateway core v4

**Assignment sau sẽ tái sử dụng:**
- ASM-A05

**Terminal delivery (chỉ Assignment cuối):**
Không áp dụng — đây là increment trung gian; sản phẩm được Assignment kế tiếp sử dụng.


## 🧰 Điều kiện thực hiện

### Kiến thức/kỹ năng tiên quyết
- **knowledge:** - Opaque API, status, ownership and lifecycle contracts from S03
- **skills:** - Write boundary tests and run separate sanitizer/Valgrind builds
- **completed_units:** - s03
- **assets:** - starter/assignment-04/README.md

### Môi trường, công cụ và phiên bản
- **profile_ref:** ENV-ADV-C-JAMMY
- **description:** Môi trường local cô lập cho C17/Linux system programming; Ubuntu 22.04 native, VM hoặc WSL2.
- **operating_system:** Ubuntu 22.04 LTS (Jammy), native/VM/WSL2; network tests bind loopback only
- **runtimes:** - - **name:** C language mode<br>- **version:** C17<br>- - **name:** glibc<br>- **version:** 2.35
- **tools:** - - **name:** GCC<br>- **version:** 11.4 baseline<br>- - **name:** Clang<br>- **version:** 14.0 baseline<br>- - **name:** GNU Make<br>- **version:** 4.3<br>- - **name:** CMake<br>- **version:** 3.22.1<br>- - **name:** GNU Binutils<br>- **version:** 2.38<br>- - **name:** GDB<br>- **version:** 12.1<br>- - **name:** Valgrind<br>- **version:** 3.18.1<br>- - **name:** cppcheck<br>- **version:** 2.7<br>- - **name:** clang-tidy<br>- **version:** 14.0<br>- - **name:** CMocka<br>- **version:** 1.1.5<br>- - **name:** gcov<br>- **version:** 11.4<br>- - **name:** LCOV package<br>- **version:** Ubuntu Jammy 1.15-1; bundled lcov --version reports 1.14<br>- - **name:** perf<br>- **version:** Linux 5.15 toolset<br>- - **name:** Git<br>- **version:** 2.34+
- **services:** _(Không có / chưa áp dụng)_
- **overrides:** _(Không có / chưa áp dụng)_

### Input và starter assets
- Opaque event ring core v3
- DC-EVENT
- Synthetic command and telemetry fixtures
- Public contract pack
- Change request CR-A04

Starter snapshot phải chứa exact **Opaque event ring core v3**, DC-EVENT, synthetic command/telemetry fixtures, public contract pack, CMake scaffold và CR-A04. Ghi snapshot identifier vào evidence manifest. Không dùng customer data, credential, kernel source copy hoặc build artifacts từ baseline khác.

## 📋 Yêu cầu

### Functional requirements
- FR-A04-01: Dynamic array init/reserve/push/access/remove/shrink/destroy giữ len <= cap và hỗ trợ nhiều element sizes theo documented ownership policy.
- FR-A04-02: Intrusive doubly linked list init/insert/remove/iterate phục hồi đúng enclosing object và duy trì prev/next/membership invariants.
- FR-A04-03: Bit-flag registry set/clear/toggle/test flags trên unsigned fixed-width storage và xử lý unknown/reserved mask theo contract.
- FR-A04-04: Ring core v3 dùng container/flag layer ở một adapter quan sát được và giữ A01–A03 regression tests pass.
- FR-A04-05: Executable probes minh họa macro evaluation, bit-field layout, union active member và FAM allocation boundaries mà không biến raw representation thành external contract.

FR-A04-01..05 đều map tới **ADVC-H1SD**. Mỗi FR phải có test/probe quan sát được và được đóng gói trong ít nhất một deliverable; source review không thay allocation-failure, membership, truth-table, portability hoặc regression oracle.

### Non-functional requirements
- NFR-A04-01: Mọi count/capacity/byte-size calculation kiểm tra overflow trước allocation; realloc failure giữ old pointer và container state.
- NFR-A04-02: container_of/list implementation là userspace code nguyên bản, giữ qualifiers theo declared contract và không copy Linux kernel macros.
- NFR-A04-03: Không serialize raw struct, bit-field hoặc union representation; ASan+UBSan và Valgrind binary riêng không có finding mức chặn.

NFR-A04-01..03 map tới **ADVC-H1SD**. Overflow/failure atomicity phải có deterministic fixture; qualifier/ownership contract phải review được; ASan+UBSan và Valgrind reports phải đến từ binary riêng và cùng source snapshot.

### Ràng buộc và phạm vi loại trừ
- CMake scaffold được cấp sẵn và không được chấm như kiến thức CMake trước Session 05
- Generic API phải mang element size và document null/zero/copy/destructor policy
- Macro arguments dùng trong unsafe macro không được có side effects; ưu tiên static inline khi có thể
- container_of chỉ nhận pointer tới đúng named member của live enclosing object; không nhận null, fabricated hoặc unrelated pointer
- Một intrusive link node không được đồng thời ở hai list; muốn đa membership phải có link member riêng
- Bitwise và shifts dùng unsigned fixed-width operands; shift count phải nhỏ hơn promoted width
- Không dùng bit-field hoặc union inactive-member bytes làm wire/storage ABI
- FAM là last member; allocation/copy math phải overflow-safe và truy cập chỉ trong allocated extent

Ngoài phạm vi: custom allocator tổng quát, concurrent container, lock-free list, protocol redesign và benchmark hiệu năng. CMake scaffold chỉ là phương tiện chạy test; S04 không chấm kiến thức thiết kế CMake. Invalid `container_of` pointers là unsupported input cần được ngăn bởi contract/caller, không phải fixture được phép dereference.

> [!IMPORTANT]
> Đây là bài làm độc lập. Đề bài không cung cấp quy trình từng bước, code hoàn chỉnh hoặc đáp án. Có thể điều hướng tới khái niệm/Case Study đã học nhưng không được lộ lời giải cho change request này.

## 📦 Deliverables và cách nộp
- Generic gateway core v4
- A04 dynamic-array and intrusive-list tests
- A04 flag and representation probes
- A04 container ownership and portability decision note
- A04 regression and memory evidence

**Submission contract:**
Nộp snapshot M04 cùng source, tests, representation probes, decision note và evidence manifest đã redact; không nộp build cache hoặc dữ liệu ngoài synthetic fixtures.

- **Generic gateway core v4:** source/header/build snapshot tích hợp ring adapter; đủ khi FR-A04-01..05 đạt và A01–A03 không regression.
- **A04 dynamic-array and intrusive-list tests:** normal/boundary/failure/membership suites cùng golden oracle và exit status.
- **A04 flag and representation probes:** truth table, macro-evaluation, bit-field label, tagged-union và FAM boundary evidence.
- **A04 container ownership and portability decision note:** growth/shrink, copy/destructor, qualifier, membership, reserved mask và external-representation decisions.
- **A04 regression and memory evidence:** A01–A03, ASan+UBSan và Valgrind summaries, command/tool fingerprint và snapshot identifier.

## ✅ Acceptance criteria và output mong đợi
- AT-A04-01 [ADVC-H1SD] — Dynamic array test multiple element sizes, growth, shrink, removal, overflow and allocation failure; expected: len <= cap luôn đúng; contents khớp golden oracle; overflow bị reject; realloc failure giữ old data/pointer/state theo contract
- AT-A04-02 [ADVC-H1SD] — Intrusive list test empty/single/multi, head/tail insertion, removal, safe iteration và membership misuse; expected: Forward/backward order và link invariants đúng; double insertion/foreign removal được reject theo contract
- AT-A04-03 [ADVC-H1SD] — container_of compile/runtime probe cho exact member, nonzero offset và const-qualified access; expected: Exact member pointer phục hồi đúng enclosing address; const contract không bị cast-away; invalid fixtures không được gọi như supported input
- AT-A04-04 [ADVC-H1SD] — Bit-flag truth-table test set, clear, toggle, test, boundary bit và unknown/reserved mask; expected: Mọi mask operation khớp truth table; reserved/unknown bits được reject hoặc preserve đúng documented policy
- AT-A04-05 [ADVC-H1SD] — Macro, bit-field, union and flexible-array portability probes; expected: Macro tests không phụ thuộc side-effect evaluation; layout report được gắn implementation-specific; tagged-union active member và FAM n=0/1/max/overflow fixtures đúng contract
- AT-A04-06 [ADVC-H1SD] — A01–A03 regression cùng ASan+UBSan và Valgrind container stress runs; expected: Regression exit 0; sanitizer không finding; Valgrind 0 invalid access và 0 definite/indirect leak theo policy

Given allocation failure/overflow fixtures, state phải giữ invariant và old data theo contract. Given list misuse, operation phải reject mà không đổi valid links. Given reserved masks hoặc representation probes, output phải theo policy đã công bố; raw layout không được dùng như cross-platform golden oracle. Mọi test exit 0 sau khi tính cả A01–A03 regression.

## 🧪 Cách xác minh
**Phương thức:** artifact_review

- `cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug`
- `cmake --build build/debug`
- `ctest --test-dir build/debug --output-on-failure`
- `cmake -S . -B build/sanitize -DCMAKE_BUILD_TYPE=Debug -DADVC_ENABLE_SANITIZERS=ON`
- `cmake --build build/sanitize`
- `ctest --test-dir build/sanitize --output-on-failure`
- `valgrind --tool=memcheck --leak-check=full --errors-for-leak-kinds=definite,indirect --error-exitcode=99 ./build/debug/tests/container_tests`

**Bằng chứng phải nộp:**
- Dynamic-array test and allocation-failure report
- Intrusive-list and container_of report
- Bit-flag truth table
- Macro/bit-field/union/FAM portability report
- A01–A03 regression summary
- ASan+UBSan summary
- Valgrind summary
- Container ownership and portability decision note

Lưu command, tool fingerprint, exit status, snapshot identifier và relative evidence path. `ADVC_ENABLE_SANITIZERS=ON` phải tạo ASan+UBSan build theo scaffold; Valgrind chạy binary debug không instrument sanitizer. Một report bit-field chỉ pass khi gắn implementation/compiler scope, không khi khẳng định raw bytes portable.

## 📊 Rubric chấm điểm — tổng 100%
| ID | Tiêu chí | Trọng số | Learning Outcomes | Bằng chứng | Mức hiệu suất |
|---|---|---:|---|---|---|
| RB-A04-01 | Dynamic-array behavior and failure atomicity | 25% | ADVC-H1SD | AT-A04-01 and allocation-failure report | **pass:** Required vector behavior, overflow and failure paths pass<br>**fail:** Có content loss, len/cap violation, overflow hoặc failed-realloc state corruption |
| RB-A04-02 | Intrusive list and container_of correctness | 25% | ADVC-H1SD | AT-A04-02 and AT-A04-03 | **pass:** List order/membership/lifetime invariants và valid recovery fixtures pass<br>**fail:** Có link corruption, invalid recovery, double insertion hoặc unsafe qualifier cast |
| RB-A04-03 | Unsigned bit-flag registry behavior | 15% | ADVC-H1SD | AT-A04-04 truth-table report | **pass:** Set/clear/toggle/test và reserved-mask policy khớp contract<br>**fail:** Có signed/shift defect hoặc flag behavior sai/mơ hồ |
| RB-A04-04 | Generic, macro and representation safety | 15% | ADVC-H1SD | AT-A04-01, AT-A04-03 and AT-A04-05 | **pass:** Byte contracts, macro evaluation, bit-field/union/FAM boundaries được xử lý đúng<br>**fail:** Có unchecked size, unsafe macro evaluation hoặc raw representation được dùng như portable contract |
| RB-A04-05 | Regression, memory tests and reproducible evidence | 10% | ADVC-H1SD | Commands and reports for AT-A04-01..06 | **pass:** Regression và all required oracles pass; evidence resolve được<br>**fail:** Có regression/memory finding hoặc thiếu command/result/evidence |
| RB-A04-06 | Container ownership and portability decision note | 10% | ADVC-H1SD | A04 container ownership and portability decision note | **pass:** Nêu rõ growth/shrink, element ownership, membership, flags và representation trade-offs<br>**fail:** Thiếu decision hoặc quyết định mâu thuẫn implementation/tests |

**Điểm đạt:** 70%


## 📚 Nguồn đầu vào và provenance

### Nguồn đã map
- SRC-SYL — L2_MBD_ADVC_Syllabus_v1.0 1.xlsx: D:\Workspaces\FR_DN26_MBD_Simulink\L2_MBD_ADVC_Syllabus_v1.0 1.xlsx (publisher: Internal training syllabus; version: 1.0; accessed_at: 2026-08-21; license: internal_approved for this requested training-content generation; allowed_use: internal_approved)
- SRC-C17-ISO — ISO/IEC 9899:2018 — Programming languages — C: https://www.iso.org/standard/74528.html (publisher: ISO/IEC JTC 1/SC 22; version: Edition 4, C17, 2018; accessed_at: 2026-08-21; license: ISO copyright; metadata and clause references only, no reproduction; allowed_use: reference)
- SRC-C17-WG14 — WG14 N2176 proposed C17 committee draft: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2176.pdf (publisher: ISO/IEC JTC 1/SC 22/WG14; version: N2176, 2017-10-09; non-final public committee document; accessed_at: 2026-08-21; license: Publicly accessible committee document; link and paraphrase only; allowed_use: reference)
- SRC-GNUC — GNU C Language Manual: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/index.html (publisher: GNU Project / Free Software Foundation; version: rolling manual as accessed; C17 scope constrained by plan; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-GLIBC235 — GNU C Library Reference Manual: https://sourceware.org/glibc/manual/2.35/pdf/libc.pdf (publisher: GNU Project; version: glibc 2.35; accessed_at: 2026-08-21; license: GNU Free Documentation License; link and paraphrase; allowed_use: reference)
- SRC-POSIX17 — The Open Group Base Specifications Issue 7, 2018 Edition: https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/ (publisher: The Open Group and IEEE; version: POSIX.1-2017, 2018 Edition; accessed_at: 2026-08-21; license: IEEE/The Open Group copyright; reference only; allowed_use: reference)
- SRC-CERTC — SEI CERT C Coding Standard: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/ (publisher: Carnegie Mellon University Software Engineering Institute; version: online work-in-progress snapshot as accessed; claims constrained to C17; accessed_at: 2026-08-21; license: CMU/SEI terms; reference and limited quotation only; allowed_use: reference)
- SRC-LINUX-LIST — Linked Lists in Linux: https://docs.kernel.org/core-api/list.html (publisher: Linux Kernel documentation project; version: mainline documentation as accessed; pattern only; accessed_at: 2026-08-21; license: GPL-2.0-or-later source documentation; no kernel code copied; allowed_use: reference)
- SRC-GCC11 — GCC 11.4 manuals: https://gcc.gnu.org/onlinedocs/gcc-11.4.0/ (publisher: GNU Project / Free Software Foundation; version: 11.4.0; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-LLVM14 — LLVM/Clang 14.0.0 Documentation: https://releases.llvm.org/14.0.0/tools/clang/docs/index.html (publisher: LLVM Project; version: 14.0.0; accessed_at: 2026-08-21; license: Apache-2.0 WITH LLVM-exception; allowed_use: reference)
- SRC-VALGRIND318 — Valgrind Memcheck Manual: https://valgrind.org/docs/manual/mc-manual.html (publisher: Valgrind Developers; version: 3.18.1 Ubuntu baseline; options constrained to that release; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.2 or later; allowed_use: reference)

### Phần bổ sung/suy diễn
- **[SUY DIỄN — project plan đã được phê duyệt]** Gateway, stakeholder M05 và chuỗi M03→M04→M05 là bối cảnh mô phỏng.
- **[BỔ SUNG — Linux linked-list documentation]** Chỉ pattern intrusive list được tham khảo; implementation Assignment phải là userspace code nguyên bản, không sao chép kernel macros.
- **[BỔ SUNG — GNU C/GCC/Clang scope]** `container_of` được đánh giá theo exact-member/live-object/qualifier/compiler-target contract, không như một primitive ISO C cho pointer bất kỳ.

---

# Session S06: Session 06 — Debugging, testing and code-quality gates — Assignment 06

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 03 — Build System, Toolchain, Debugging & Unit Testing

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASM-A06 (Assignment 06) |
| Thời lượng dự kiến | 120 phút |
| Độ khó | hard |
| Bloom levels | - evaluate |
| Mức xác thực | simulated |

## 🎯 Learning Outcomes được đánh giá
- **ADVC-H3SD** [evaluate] — Đánh giá và cải thiện build, debug, test, phân tích tĩnh, coverage, profiling và secure-coding của mã C bằng bằng chứng tái lập từ GNU/LLVM toolchain và quy tắc CERT C phù hợp. · Bằng chứng: Build/test/analysis/profile report truy vết được tới quyết định sửa; không còn finding mức chặn trong oracle và mọi ngoại lệ đều có lý do.


## 🧠 Khái niệm và best practices được đánh giá
### CA-A06-QUALITY — Turn a crash diagnosis into an executable quality baseline
- **Khái niệm/outline:** OUT-S06-01
- **Learning Outcomes:** ADVC-H3SD
- **Scenario:** Process/thread teams chỉ được dùng gateway core khi crash fix, regression suite và quality evidence có cùng versioned baseline.
- **Inputs:** Packaged gateway core v5; Synthetic crash and boundary fixtures; Public contract pack; Change request CR-A06
- **Best-practice constraints:**
  - **Giữ fixed reproducer, lưu GDB evidence trước sửa và xác minh root-cause fix bằng sanitizer/regression thay vì sửa theo triệu chứng.** — Lý do: Backtrace/watchpoint chỉ là chẩn đoán; executable regression và instrumented runtime mới ngăn cùng defect quay lại.; Concepts: OUT-S06-01; Acceptance tests: AT-A06-01, AT-A06-02; Rubric: RB-A06-01, RB-A06-02, RB-A06-04
  - **Đo production line coverage trên clean -O0 --coverage build và xử lý static-analysis finding bằng sửa hoặc disposition truy vết, không bằng blanket suppression.** — Lý do: Coverage chỉ có ý nghĩa khi denominator ổn định; analysis report chỉ có giá trị khi finding và exception đều quan sát được.; Concepts: OUT-S06-01; Acceptance tests: AT-A06-03, AT-A06-04; Rubric: RB-A06-02, RB-A06-03, RB-A06-04
- **Deliverables:** Quality-gated gateway core v6; A06 quality evidence; A06 defect and test decision note
- **Acceptance tests và oracle quan sát được:**
  - **AT-A06-01** [ADVC-H3SD] — GDB tái hiện crash và evidence xác định đúng failing frame, invalid state và root cause; Expected: Pre-fix fixture dừng tại expected failure; backtrace/watch evidence truy vết tới root cause; post-fix regression pass; Evidence/rubric: RB-A06-01: AT-A06-01 and regression report; RB-A06-02: AT-A06-02 and AT-A06-04 reports; RB-A06-03: AT-A06-03 test and LCOV summaries; RB-A06-04: Version-matched evidence manifest and A06 decision note
  - **AT-A06-02** [ADVC-H3SD] — ASan+UBSan chạy toàn bộ required fixtures trên instrumented build; Expected: Test processes exit 0 và không sanitizer finding thuộc project code; Evidence/rubric: RB-A06-01: AT-A06-01 and regression report; RB-A06-02: AT-A06-02 and AT-A06-04 reports; RB-A06-03: AT-A06-03 test and LCOV summaries; RB-A06-04: Version-matched evidence manifest and A06 decision note
  - **AT-A06-03** [ADVC-H3SD] — CMocka regression suite đạt và LCOV production line coverage ít nhất 80 phần trăm; Expected: Mọi required CMocka test pass; lcov summary lines >=80.0% với exclusion policy được lưu; Evidence/rubric: RB-A06-01: AT-A06-01 and regression report; RB-A06-02: AT-A06-02 and AT-A06-04 reports; RB-A06-03: AT-A06-03 test and LCOV summaries; RB-A06-04: Version-matched evidence manifest and A06 decision note
  - **AT-A06-04** [ADVC-H3SD] — Cppcheck error gate và clang-tidy blocking-analysis gate chạy từ compile database; Expected: cppcheck error exit code 0; không còn clang-analyzer/CERT finding mức chặn chưa có disposition; Evidence/rubric: RB-A06-01: AT-A06-01 and regression report; RB-A06-02: AT-A06-02 and AT-A06-04 reports; RB-A06-03: AT-A06-03 test and LCOV summaries; RB-A06-04: Version-matched evidence manifest and A06 decision note


## 🧭 Bối cảnh nghề nghiệp/dự án và change request

**Bối cảnh nghề nghiệp/dự án:**
**MDB Edge Diagnostics Gateway — Simulated** — Cổng chẩn đoán và telemetry chạy local trên Linux cho thiết bị giả lập; tiếp nhận command, quản lý work records, thực thi backend process/thread và phục vụ protocol TCP loopback. Vai trò học viên: C systems developer chịu trách nhiệm phát triển và harden từng increment trong repository đào tạo. Mục tiêu: Bàn giao một gateway TCP loopback tích hợp core C17, process/thread backends và quality evidence; phục vụ ít nhất 100 client synthetic theo Assignment 09 mà không có finding mức chặn trong oracle áp dụng.

**Project increment/change request cần hoàn thành:**
- **milestone_id:** M06
- **user_story:** Là quality reviewer, tôi muốn tái hiện crash, sửa root cause và đặt regression/analysis/coverage gates cho packaged gateway core v5 trước khi thêm concurrent backends.
- **business_value:** Biến core đã đóng gói thành baseline có bằng chứng lỗi, test và quality metric tái lập cho hai nhánh process/thread.
- **baseline:** Packaged gateway core v5 và một synthetic crashing legacy fixture.
- **change_scope:** - GDB crash triage và local core evidence<br>- ASan/UBSan instrumented build<br>- CMocka regression tests<br>- gcov/LCOV production line coverage<br>- cppcheck và clang-tidy analysis<br>- CERT C remediation record
- **inputs:** - Packaged gateway core v5<br>- Synthetic crash and boundary fixtures<br>- Public contract pack
- **integration_points:** - quality gate<br>- build/package layer<br>- gateway core public API
- **artifacts_added:** - Quality-gated gateway core v6<br>- A06 quality evidence
- **acceptance_criteria:** - FR-06 đạt<br>- NFR-01 đạt<br>- NFR-02 đạt<br>- Production line coverage đạt ít nhất 80 phần trăm theo denominator đã công bố
- **definition_of_done:** - Project Definition of Done áp dụng cho M06

**Scenario đã chốt trong plan:**
Change request CR-A06 injects a reproducible crash and under-tested error paths into gateway core v5; học viên phải chứng minh root cause, sửa tối thiểu và thiết lập quality baseline dùng được bởi A07/A08.

Bạn là quality reviewer của baseline M05. Nhóm process và nhóm thread cùng chờ M06 nên không chấp nhận một patch thiếu provenance: bạn phải giữ fixed reproducer, xác định root cause từ state/backtrace, sửa tối thiểu và phát hành một evidence manifest mà reviewer có thể chạy lại. CR-A06 sử dụng module/error paths khác case QG-06 trong `example.md`; bài nộp lại asset mẫu không thỏa yêu cầu.

## 🔗 Liên kết project xuyên suốt

**Project milestone:**
M06

**Phụ thuộc vào Assignment trước:**
- ASM-A05

**Baseline artifacts được sử dụng:**
- Packaged gateway core v5

**Artifacts Assignment này tạo ra:**
- Quality-gated gateway core v6

**Assignment sau sẽ tái sử dụng:**
- ASM-A07
- ASM-A08

**Terminal delivery (chỉ Assignment cuối):**
Không áp dụng — đây là increment trung gian; sản phẩm được Assignment kế tiếp sử dụng.


## 🧰 Điều kiện thực hiện

### Kiến thức/kỹ năng tiên quyết
- **knowledge:** - Translation-unit, CMake target và static/shared boundary từ S05
- **skills:** - Clean-build và chạy regression tests của packaged gateway core v5
- **completed_units:** - s05
- **assets:** - starter/assignment-06/README.md

### Môi trường, công cụ và phiên bản
- **profile_ref:** ENV-ADV-C-JAMMY
- **description:** Môi trường local cô lập cho C17/Linux system programming; Ubuntu 22.04 native, VM hoặc WSL2.
- **operating_system:** Ubuntu 22.04 LTS (Jammy), native/VM/WSL2; network tests bind loopback only
- **runtimes:** - - **name:** C language mode<br>- **version:** C17<br>- - **name:** glibc<br>- **version:** 2.35
- **tools:** - - **name:** GCC<br>- **version:** 11.4 baseline<br>- - **name:** Clang<br>- **version:** 14.0 baseline<br>- - **name:** GNU Make<br>- **version:** 4.3<br>- - **name:** CMake<br>- **version:** 3.22.1<br>- - **name:** GNU Binutils<br>- **version:** 2.38<br>- - **name:** GDB<br>- **version:** 12.1<br>- - **name:** Valgrind<br>- **version:** 3.18.1<br>- - **name:** cppcheck<br>- **version:** 2.7<br>- - **name:** clang-tidy<br>- **version:** 14.0<br>- - **name:** CMocka<br>- **version:** 1.1.5<br>- - **name:** gcov<br>- **version:** 11.4<br>- - **name:** LCOV package<br>- **version:** Ubuntu Jammy 1.15-1; CLI có thể tự báo LCOV version 1.14, phải lưu cả hai fingerprint<br>- - **name:** perf<br>- **version:** Linux 5.15 toolset<br>- - **name:** Git<br>- **version:** 2.34+
- **services:** _(Không có / chưa áp dụng)_
- **overrides:** _(Không có / chưa áp dụng)_

### Input và starter assets
- Packaged gateway core v5
- Synthetic crash and boundary fixtures
- Public contract pack
- Change request CR-A06

Starter snapshot phải chứa exact **Packaged gateway core v5**, public contract, fixed synthetic crash/boundary fixtures và CR-A06. Evidence manifest ghi snapshot identifier trước mọi sửa đổi. Không thêm dữ liệu thật, credential hoặc memory dump từ process ngoài fixture.

## 📋 Yêu cầu

### Functional requirements
- FR-A06-01: Tái hiện crash bằng fixed fixture và lưu stack/backtrace evidence trước khi sửa.
- FR-A06-02: Root-cause fix giữ public API và toàn bộ A05 regression behavior.
- FR-A06-03: CMocka tests kiểm normal, boundary và error paths của production module.

FR-A06-01..03 đều map tới **ADVC-H3SD**. Backtrace phải chỉ ra state/failing frame; fix phải được regression test; mỗi CMocka case phải có input và assertion quan sát được. Việc crash biến mất đơn lẻ không chứng minh FR.

### Non-functional requirements
- NFR-A06-01: ASan+UBSan runtime không có finding; TSan được giữ cho build riêng ở concurrency increment.
- NFR-A06-02: Production line coverage đạt ít nhất 80 phần trăm; tests/generated/vendor không nằm trong denominator đã công bố.
- NFR-A06-03: cppcheck 2.7 error gate đạt và clang-tidy report không còn finding mức chặn chưa xử lý.

NFR-A06-01..03 map tới **ADVC-H3SD** và được đo bằng instrumented test exit/status, LCOV production-lines summary, cppcheck exit code và clang-tidy disposition report. Không dùng log rỗng nếu thiếu command, tool version và exit status.

### Ràng buộc và phạm vi loại trừ
- Không thay đổi fixture để che crash và không xóa error path khỏi contract
- Không blanket-disable sanitizer hoặc static-analysis diagnostics
- ASan/UBSan và TSan không nằm trong cùng binary
- Cppcheck 2.7 dùng --std=c11 do parser limitation trong khi compiler vẫn build -std=c17
- Core dump chỉ nằm trong workspace, được xem là sensitive evidence và không publish

Ngoài phạm vi: fuzzing campaign, performance benchmark, TSan workload cho code chưa concurrent và upload core dump. Không đổi denominator/exclusion policy sau khi xem coverage, không đổi fixture để né failing path và không nâng tool rolling để làm report “đẹp” hơn baseline.

> [!IMPORTANT]
> Đây là bài làm độc lập. Đề bài không cung cấp quy trình từng bước, code hoàn chỉnh hoặc đáp án. Có thể điều hướng tới khái niệm/Case Study đã học nhưng không được lộ lời giải cho change request này.

## 📦 Deliverables và cách nộp
- Quality-gated gateway core v6
- A06 quality evidence
- A06 defect and test decision note

**Submission contract:**
Nộp snapshot M06 và version-matched quality evidence; core file, absolute host paths, build cache và sensitive memory dump không thuộc submission.

- **Quality-gated gateway core v6:** source/header/build/test snapshot; đủ khi public API/A05 regression được giữ và AT-A06-01..04 đạt.
- **A06 quality evidence:** manifest liên kết pre-fix GDB record, post-fix CTest/CMocka, ASan+UBSan, LCOV, cppcheck và clang-tidy reports tới cùng snapshot/tool fingerprints.
- **A06 defect and test decision note:** nêu root cause, vì sao fix xử lý root cause, test partition, sanitizer split, coverage denominator/exclusions và disposition của từng blocking finding.

## ✅ Acceptance criteria và output mong đợi
- AT-A06-01 [ADVC-H3SD] — GDB tái hiện crash và evidence xác định đúng failing frame, invalid state và root cause; expected: Pre-fix fixture dừng tại expected failure; backtrace/watch evidence truy vết tới root cause; post-fix regression pass
- AT-A06-02 [ADVC-H3SD] — ASan+UBSan chạy toàn bộ required fixtures trên instrumented build; expected: Test processes exit 0 và không sanitizer finding thuộc project code
- AT-A06-03 [ADVC-H3SD] — CMocka regression suite đạt và LCOV production line coverage ít nhất 80 phần trăm; expected: Mọi required CMocka test pass; lcov summary lines >=80.0% với exclusion policy được lưu
- AT-A06-04 [ADVC-H3SD] — Cppcheck error gate và clang-tidy blocking-analysis gate chạy từ compile database; expected: cppcheck error exit code 0; không còn clang-analyzer/CERT finding mức chặn chưa có disposition

Given fixed pre-fix fixture, GDB diagnostic failure là evidence được kỳ vọng chứ không phải pass gate. Given post-fix snapshot, toàn bộ regression/instrumented tests phải exit 0. Coverage dưới 80.0%, accidental API change, blanket suppression hoặc finding thiếu disposition đều làm acceptance fail.

## 🧪 Cách xác minh
**Phương thức:** artifact_review

- `cmake --version && gcc --version | head -1 && clang-14 --version | head -1 && gdb --version | head -1`
- `cppcheck --version && pkg-config --modversion cmocka && apt-cache policy lcov && lcov --version`
- `cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`
- `cmake --build build/debug`
- `gdb -q -batch -ex 'set pagination off' -ex run -ex 'thread apply all bt full' --args ./build/debug/apps/gateway_crash_fixture`
- `cmake -S . -B build/asan -DCMAKE_C_COMPILER=clang-14 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS='-O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined -fno-sanitize-recover=all' -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined'`
- `cmake --build build/asan`
- `ASAN_OPTIONS=halt_on_error=1:detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 ctest --test-dir build/asan --output-on-failure`
- `cppcheck --project=build/debug/compile_commands.json --std=c11 --error-exitcode=1`
- `cmake -S . -B build/coverage -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS='-O0 -g --coverage' -DCMAKE_EXE_LINKER_FLAGS='--coverage'`
- `cmake --build build/coverage`
- `ctest --test-dir build/coverage --output-on-failure`
- `lcov --capture --directory build/coverage --output-file build/coverage/raw.info`
- `lcov --remove build/coverage/raw.info '/usr/*' '*/tests/*' '*/_deps/*' '*/generated/*' --output-file build/coverage/production.info`
- `lcov --summary build/coverage/production.info`

**Bằng chứng phải nộp:**
- Pre-fix GDB backtrace and root-cause record
- Post-fix CTest summary
- ASan+UBSan summary
- CMocka test report
- LCOV denominator policy and summary
- Cppcheck and clang-tidy reports
- A06 defect and test decision note

Lưu command, exit status, timestamp, source snapshot identifier và relative report path. GDB pre-fix command được đánh dấu expected diagnostic non-zero; các post-fix gates phải exit 0 trừ clang-tidy finding được disposition theo contract. LCOV evidence ghi Jammy package `1.15-1` và CLI fingerprint có thể là `1.14`.

## 📊 Rubric chấm điểm — tổng 100%
| ID | Tiêu chí | Trọng số | Learning Outcomes | Bằng chứng | Mức hiệu suất |
|---|---|---:|---|---|---|
| RB-A06-01 | Reproducible diagnosis, root-cause fix và regression | 30% | ADVC-H3SD | AT-A06-01 and regression report | **pass:** Crash được tái hiện, root cause có evidence và fix giữ toàn bộ required behavior<br>**fail:** Không tái hiện được, sửa triệu chứng hoặc có regression |
| RB-A06-02 | Sanitizer và static-analysis quality gates | 25% | ADVC-H3SD | AT-A06-02 and AT-A06-04 reports | **pass:** Sanitizer clean và không còn blocking analysis finding thiếu disposition<br>**fail:** Có sanitizer finding, cppcheck error hoặc blanket suppression |
| RB-A06-03 | CMocka tests và production line coverage | 30% | ADVC-H3SD | AT-A06-03 test and LCOV summaries | **pass:** Required tests pass và production line coverage >=80.0% theo policy<br>**fail:** Test fail, coverage dưới ngưỡng hoặc denominator bị thay đổi không công bố |
| RB-A06-04 | Evidence integrity và defect/test decision note | 15% | ADVC-H3SD | Version-matched evidence manifest and A06 decision note | **pass:** Finding, fix, tests, exclusions và commands truy vết cùng baseline<br>**fail:** Evidence stale/thiếu hoặc không giải thích quyết định |

**Điểm đạt:** 70%


## 📚 Nguồn đầu vào và provenance

### Nguồn đã map
- SRC-SYL — L2_MBD_ADVC_Syllabus_v1.0 1.xlsx: D:\Workspaces\FR_DN26_MBD_Simulink\L2_MBD_ADVC_Syllabus_v1.0 1.xlsx (publisher: Internal training syllabus; version: 1.0; accessed_at: 2026-08-21; license: internal_approved for this requested training-content generation; allowed_use: internal_approved)
- SRC-GCC11 — GCC 11.4 manuals: https://gcc.gnu.org/onlinedocs/gcc-11.4.0/ (publisher: GNU Project / Free Software Foundation; version: 11.4.0; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-GDB121 — Debugging with GDB: https://sourceware.org/gdb/current/onlinedocs/gdb.html (publisher: GNU Project / Free Software Foundation; version: GDB 12.1 execution baseline; current manual stable subset; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3; allowed_use: reference)
- SRC-LLVM14 — LLVM/Clang 14.0.0 Documentation: https://releases.llvm.org/14.0.0/tools/clang/docs/index.html (publisher: LLVM Project; version: 14.0.0; accessed_at: 2026-08-21; license: Apache-2.0 WITH LLVM-exception; allowed_use: reference)
- SRC-VALGRIND318 — Valgrind Memcheck Manual: https://valgrind.org/docs/manual/mc-manual.html (publisher: Valgrind Developers; version: 3.18.1 Ubuntu baseline; options constrained to that release; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.2 or later; allowed_use: reference)
- SRC-CPPCHECK27 — Cppcheck 2.7 Manual: https://github.com/cppcheck-opensource/cppcheck/blob/2.7/man/manual.md (publisher: Cppcheck project; version: 2.7; accessed_at: 2026-08-21; license: GPL-3.0; reference only; allowed_use: reference)
- SRC-CMOCKA115 — CMocka Documentation: https://api.cmocka.org/ (publisher: CMocka project; version: 1.1.5 stable API baseline; accessed_at: 2026-08-21; license: Apache-2.0; allowed_use: reference)
- SRC-LCOV115 — LCOV 1.15: https://github.com/linux-test-project/lcov/releases/tag/v1.15 (publisher: Linux Test Project; version: 1.15; accessed_at: 2026-08-21; license: GPL-2.0; reference only; allowed_use: reference)
- SRC-CERTC — SEI CERT C Coding Standard: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/ (publisher: Carnegie Mellon University Software Engineering Institute; version: online work-in-progress snapshot as accessed; claims constrained to C17; accessed_at: 2026-08-21; license: CMU/SEI terms; reference and limited quotation only; allowed_use: reference)

### Phần bổ sung/suy diễn
- **[BỔ SUNG — Ubuntu Jammy environment fingerprint]** Package lcov 1.15-1 có thể in CLI `LCOV version 1.14`; hai giá trị cùng được lưu trong evidence manifest.
- **[SUY DIỄN — từ quality-gate mechanics đã dạy]** “Blocking” và cấu trúc disposition/manifest là policy của bài; tool output tự thân không quyết định mức ảnh hưởng nghiệp vụ.
- **[SUY DIỄN — project plan đã được phê duyệt]** Process/thread teams là stakeholder mô phỏng tiêu thụ cùng artifact M06.

---

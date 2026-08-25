# Session S05: Session 05 — Preprocessor, linkage and build systems — Assignment 05

> **Khóa học:** [NFP] Advanced C Programming · **Loại khóa:** Advanced C17 and Linux/POSIX systems programming · **Thuộc:** Unit 03 — Build System, Toolchain, Debugging & Unit Testing

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASM-A05 (Assignment 05) |
| Thời lượng dự kiến | 120 phút |
| Độ khó | hard |
| Bloom levels | - evaluate |
| Mức xác thực | simulated |

## 🎯 Learning Outcomes được đánh giá
- **ADVC-H3SD** [evaluate] — Đánh giá và cải thiện build, debug, test, phân tích tĩnh, coverage, profiling và secure-coding của mã C bằng bằng chứng tái lập từ GNU/LLVM toolchain và quy tắc CERT C phù hợp. · Bằng chứng: Build/test/analysis/profile report truy vết được tới quyết định sửa; không còn finding mức chặn trong oracle và mọi ngoại lệ đều có lý do.


## 🧠 Khái niệm và best practices được đánh giá
### CA-A05-BUILD — Transfer preprocessor/linkage decisions into a reproducible package boundary
- **Khái niệm/outline:** OUT-S05-01
- **Learning Outcomes:** ADVC-H3SD
- **Scenario:** Reviewer cần link gateway core v5 ở static hoặc shared form mà không kéo theo internal symbols, duplicate definitions hay build-state ngoài workspace.
- **Inputs:** Generic gateway core v4; Public contract pack; Synthetic command and telemetry fixtures; Change request CR-A05
- **Best-practice constraints:**
  - **Giữ đúng one-definition/linkage contract: file-private definitions dùng static, public headers chỉ declaration và macro arguments không mang side effect.** — Lý do: Duplicate external definitions và unsafe macro expansion tạo link failure hoặc behavior phụ thuộc số lần evaluate; private linkage thu nhỏ symbol surface.; Concepts: OUT-S05-01; Acceptance tests: AT-A05-01, AT-A05-02, AT-A05-03; Rubric: RB-A05-01, RB-A05-02
  - **Mô tả build bằng target-scoped CMake properties, explicit C17 mode và default-hidden visibility; inspect artifact thay vì suy đoán từ file name.** — Lý do: Target usage requirements lan truyền có kiểm soát, còn ar/nm/readelf cung cấp oracle quan sát được cho package và symbol contract.; Concepts: OUT-S05-01; Acceptance tests: AT-A05-01, AT-A05-02, AT-A05-03; Rubric: RB-A05-01, RB-A05-02, RB-A05-03, RB-A05-04
- **Deliverables:** Packaged gateway core v5; A05 build and symbol evidence; A05 packaging decision note
- **Acceptance tests và oracle quan sát được:**
  - **AT-A05-01** [ADVC-H3SD] — Clean configure/build tạo đủ static library, shared library và demo với warning count bằng 0; Expected: CMake configure/build exit 0; ba target gateway_static, gateway_shared và gateway_demo tồn tại; không warning trong enabled profile; Evidence/rubric: RB-A05-01: AT-A05-01 and AT-A05-02 reports; RB-A05-02: Header review plus AT-A05-03 symbol reports; RB-A05-03: Clean build, ar, nm and readelf evidence; RB-A05-04: A05 packaging decision note and submission manifest
  - **AT-A05-02** [ADVC-H3SD] — Demo và regression suite link qua packaged core mà không đổi A04 behavior; Expected: Static/shared test variants và A04 regression fixtures đều pass với output/status giống golden oracle; Evidence/rubric: RB-A05-01: AT-A05-01 and AT-A05-02 reports; RB-A05-02: Header review plus AT-A05-03 symbol reports; RB-A05-03: Clean build, ar, nm and readelf evidence; RB-A05-04: A05 packaging decision note and submission manifest
  - **AT-A05-03** [ADVC-H3SD] — Archive, dynamic dependencies và symbol table khớp public/private contract; Expected: ar/nm/readelf evidence cho thấy archive members hợp lệ, shared object có expected dependency metadata và không export file-local/internal symbols; Evidence/rubric: RB-A05-01: AT-A05-01 and AT-A05-02 reports; RB-A05-02: Header review plus AT-A05-03 symbol reports; RB-A05-03: Clean build, ar, nm and readelf evidence; RB-A05-04: A05 packaging decision note and submission manifest


## 🧭 Bối cảnh nghề nghiệp/dự án và change request

**Bối cảnh nghề nghiệp/dự án:**
**MDB Edge Diagnostics Gateway — Simulated** — Cổng chẩn đoán và telemetry chạy local trên Linux cho thiết bị giả lập; tiếp nhận command, quản lý work records, thực thi backend process/thread và phục vụ protocol TCP loopback. Vai trò học viên: C systems developer chịu trách nhiệm phát triển và harden từng increment trong repository đào tạo. Mục tiêu: Bàn giao một gateway TCP loopback tích hợp core C17, process/thread backends và quality evidence; phục vụ ít nhất 100 client synthetic theo Assignment 09 mà không có finding mức chặn trong oracle áp dụng.

**Project increment/change request cần hoàn thành:**
- **milestone_id:** M05
- **user_story:** Là integration engineer, tôi muốn gateway core v4 được tách thành translation units và đóng gói thành static/shared libraries để application có thể link qua public contract ổn định.
- **business_value:** Tạo build/package baseline tái lập, giới hạn exported symbols và chuẩn bị một điểm kiểm soát thống nhất cho quality tooling.
- **baseline:** Generic gateway core v4 từ Assignment 04 cùng regression fixtures đã có.
- **change_scope:** - Header và translation-unit boundaries<br>- Internal/external linkage và inline helpers<br>- Portable variadic/X-macro configuration<br>- GNU Make dependency build<br>- CMake static/shared/demo targets<br>- Visibility và symbol inspection
- **inputs:** - Generic gateway core v4<br>- DC-COMMAND<br>- DC-EVENT<br>- Synthetic command and telemetry fixtures
- **integration_points:** - command dispatcher<br>- memory pool<br>- opaque event ring<br>- generic containers and flags<br>- build/package layer
- **artifacts_added:** - Packaged gateway core v5<br>- A05 build and symbol evidence
- **acceptance_criteria:** - FR-05 đạt<br>- NFR-02 đạt<br>- A04 regression behavior không đổi<br>- Shared library chỉ export public API đã công bố
- **definition_of_done:** - Project Definition of Done áp dụng cho M05

**Scenario đã chốt trong plan:**
Refactor change request CR-A05 chuyển generic gateway core v4 từ một build monolithic sang các module C17 có public/private boundary, một static library, một shared library và demo dùng cùng contract.

Bạn tiếp nhận repository M04 đã được nghiệm thu nhưng hiện toàn bộ core được biên dịch như một executable duy nhất. Nhóm tích hợp cần hai dạng package có cùng public contract: archive để link tĩnh vào công cụ kiểm thử và shared object để demo nạp động trong build tree. Nhiệm vụ của bạn là đánh giá rồi tái cấu trúc boundary, không sao chép cấu trúc của case mẫu; reviewer sẽ đối chiếu hành vi A04, artifact thật và symbol table.

## 🔗 Liên kết project xuyên suốt

**Project milestone:**
M05

**Phụ thuộc vào Assignment trước:**
- ASM-A04

**Baseline artifacts được sử dụng:**
- Generic gateway core v4

**Artifacts Assignment này tạo ra:**
- Packaged gateway core v5

**Assignment sau sẽ tái sử dụng:**
- ASM-A06

**Terminal delivery (chỉ Assignment cuối):**
Không áp dụng — đây là increment trung gian; sản phẩm được Assignment kế tiếp sử dụng.


## 🧰 Điều kiện thực hiện

### Kiến thức/kỹ năng tiên quyết
- **knowledge:** - Opaque ADT, ownership và generic-container contracts từ S03-S04
- **skills:** - Biên dịch C17 và chạy regression suite của gateway core v4
- **completed_units:** - s04
- **assets:** - starter/assignment-05/README.md

### Môi trường, công cụ và phiên bản
- **profile_ref:** ENV-ADV-C-JAMMY
- **description:** Môi trường local cô lập cho C17/Linux system programming; Ubuntu 22.04 native, VM hoặc WSL2.
- **operating_system:** Ubuntu 22.04 LTS (Jammy), native/VM/WSL2; network tests bind loopback only
- **runtimes:** - - **name:** C language mode<br>- **version:** C17<br>- - **name:** glibc<br>- **version:** 2.35
- **tools:** - - **name:** GCC<br>- **version:** 11.4 baseline<br>- - **name:** Clang<br>- **version:** 14.0 baseline<br>- - **name:** GNU Make<br>- **version:** 4.3<br>- - **name:** CMake<br>- **version:** 3.22.1<br>- - **name:** GNU Binutils<br>- **version:** 2.38<br>- - **name:** GDB<br>- **version:** 12.1<br>- - **name:** Valgrind<br>- **version:** 3.18.1<br>- - **name:** cppcheck<br>- **version:** 2.7<br>- - **name:** clang-tidy<br>- **version:** 14.0<br>- - **name:** CMocka<br>- **version:** 1.1.5<br>- - **name:** gcov<br>- **version:** 11.4<br>- - **name:** LCOV package<br>- **version:** Ubuntu Jammy 1.15-1; bundled lcov --version reports 1.14<br>- - **name:** perf<br>- **version:** Linux 5.15 toolset<br>- - **name:** Git<br>- **version:** 2.34+
- **services:** _(Không có / chưa áp dụng)_
- **overrides:** _(Không có / chưa áp dụng)_

### Input và starter assets
- Generic gateway core v4
- Synthetic command and telemetry fixtures
- Public contract pack
- Change request CR-A05

Starter snapshot phải chứa source của **Generic gateway core v4**, public contract pack, synthetic fixtures và CR-A05. Ghi commit/archive identifier của snapshot vào evidence manifest. Không dùng dữ liệu thật, credential, system library path tự tạo hoặc artifact build cũ làm input.

## 📋 Yêu cầu

### Functional requirements
- FR-A05-01: Tách declaration/definition đúng translation-unit và linkage contract mà không đổi observable A04 behavior.
- FR-A05-02: CMake tạo gateway_static, gateway_shared và gateway_demo từ clean build directory.
- FR-A05-03: Static/shared variants cung cấp cùng public API và demo chạy với scoped build-tree runtime path.

Tất cả FR-A05-01..03 map tới **ADVC-H3SD** và phải được chứng minh qua artifact/package behavior, regression output hoặc symbol evidence tương ứng; source review đơn lẻ không thay thế executable oracle.

### Non-functional requirements
- NFR-A05-01: Build dùng C17 strict mode, warning profile đã chốt và generated dependency tracking.
- NFR-A05-02: Shared object mặc định hidden visibility; chỉ public API được export và không cài vào system prefix.

Hai NFR map tới **ADVC-H3SD**. Warning log, generated dependency behavior, CMake target properties và `readelf`/`nm` output là bằng chứng đo được; nhận xét “build tốt” hoặc “đã ẩn symbol” không được tính nếu thiếu oracle.

### Ràng buộc và phạm vi loại trừ
- Không định nghĩa external object trong public header
- Header helper chỉ dùng static inline khi internal copy per translation unit là chủ ý
- X-macro được công bố là idiom suy diễn từ preprocessor C17, không mô tả như language feature chuẩn
- Không dùng global CMake flags để thay target properties
- Không sudo, không make install, không ldconfig và không ghi ngoài workspace

Ngoài phạm vi: system-wide installation, package manager metadata, cross-compilation và ABI compatibility với phiên bản không thuộc baseline. Không được thay public behavior A04 để làm build dễ hơn.

> [!IMPORTANT]
> Đây là bài làm độc lập. Đề bài không cung cấp quy trình từng bước, code hoàn chỉnh hoặc đáp án. Có thể điều hướng tới khái niệm/Case Study đã học nhưng không được lộ lời giải cho change request này.

## 📦 Deliverables và cách nộp
- Packaged gateway core v5
- A05 build and symbol evidence
- A05 packaging decision note

**Submission contract:**
Nộp snapshot M05 gồm source/CMake/Make files, tests và evidence đã redact; không nộp build cache hoặc cài library vào system prefix.

- **Packaged gateway core v5:** source/header/build descriptions và tests trong snapshot M05; đủ khi clean build sinh static/shared/demo targets và regression pass.
- **A05 build and symbol evidence:** manifest ghi command, tool version, exit status và đường dẫn log cho clean build, CTest, `ar`, `nm`, `readelf`; đủ khi mọi đường dẫn resolve về cùng snapshot.
- **A05 packaging decision note:** nêu quyết định cho macro, translation unit, linkage, static/shared, visibility và runtime path; mỗi quyết định gắn với ít nhất một bằng chứng.

## ✅ Acceptance criteria và output mong đợi
- AT-A05-01 [ADVC-H3SD] — Clean configure/build tạo đủ static library, shared library và demo với warning count bằng 0; expected: CMake configure/build exit 0; ba target gateway_static, gateway_shared và gateway_demo tồn tại; không warning trong enabled profile
- AT-A05-02 [ADVC-H3SD] — Demo và regression suite link qua packaged core mà không đổi A04 behavior; expected: Static/shared test variants và A04 regression fixtures đều pass với output/status giống golden oracle
- AT-A05-03 [ADVC-H3SD] — Archive, dynamic dependencies và symbol table khớp public/private contract; expected: ar/nm/readelf evidence cho thấy archive members hợp lệ, shared object có expected dependency metadata và không export file-local/internal symbols

Oracle bổ sung: một clean build không được phụ thuộc file sinh từ lần chạy trước; demo phải chạy khi chỉ dùng runtime path trong build tree; symbol ngoài public contract làm AT-A05-03 fail dù functional tests vẫn pass.

## 🧪 Cách xác minh
**Phương thức:** artifact_review

- `cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`
- `cmake --build build/debug --target gateway_static gateway_shared gateway_demo`
- `ctest --test-dir build/debug --output-on-failure`
- `ar t build/debug/lib/libgateway_core.a`
- `nm -g --defined-only build/debug/lib/libgateway_core.a`
- `readelf -Ws build/debug/lib/libgateway_core.so`
- `readelf -d build/debug/apps/gateway_demo`

**Bằng chứng phải nộp:**
- Clean configure/build log
- CTest regression summary
- Archive member list
- Static/shared symbol reports
- A05 packaging decision note

Chạy các lệnh từ repository root trên Ubuntu 22.04/WSL2 và lưu cả command lẫn exit status. Không chạy `sudo`, `make install` hoặc `ldconfig`. Bản nộp không cần chứa build directory nhưng manifest phải đủ để reviewer dựng lại từ clean state.

## 📊 Rubric chấm điểm — tổng 100%
| ID | Tiêu chí | Trọng số | Learning Outcomes | Bằng chứng | Mức hiệu suất |
|---|---|---:|---|---|---|
| RB-A05-01 | Module/package behavior và A04 regression | 35% | ADVC-H3SD | AT-A05-01 and AT-A05-02 reports | **pass:** Ba target build và mọi required behavior/regression fixture pass<br>**fail:** Thiếu target, có link failure hoặc observable regression |
| RB-A05-02 | Translation-unit, linkage và symbol boundary | 30% | ADVC-H3SD | Header review plus AT-A05-03 symbol reports | **pass:** One-definition, file-private linkage và exported API contract đều đạt<br>**fail:** Có duplicate definition, accidental export hoặc header implementation sai contract |
| RB-A05-03 | Reproducible build và artifact evidence | 25% | ADVC-H3SD | Clean build, ar, nm and readelf evidence | **pass:** Commands, versions, expected results và artifact reports resolve đầy đủ<br>**fail:** Evidence thiếu, stale hoặc không tái lập được |
| RB-A05-04 | Packaging decision note và bàn giao an toàn | 10% | ADVC-H3SD | A05 packaging decision note and submission manifest | **pass:** Giải thích macro/linkage/static-shared/visibility trade-offs và không có system mutation<br>**fail:** Thiếu quyết định, provenance hoặc có yêu cầu cài đặt toàn hệ thống |

**Điểm đạt:** 70%


## 📚 Nguồn đầu vào và provenance

### Nguồn đã map
- SRC-SYL — L2_MBD_ADVC_Syllabus_v1.0 1.xlsx: D:\Workspaces\FR_DN26_MBD_Simulink\L2_MBD_ADVC_Syllabus_v1.0 1.xlsx (publisher: Internal training syllabus; version: 1.0; accessed_at: 2026-08-21; license: internal_approved for this requested training-content generation; allowed_use: internal_approved)
- SRC-C17-ISO — ISO/IEC 9899:2018 — Programming languages — C: https://www.iso.org/standard/74528.html (publisher: ISO/IEC JTC 1/SC 22; version: Edition 4, C17, 2018; accessed_at: 2026-08-21; license: ISO copyright; metadata and clause references only, no reproduction; allowed_use: reference)
- SRC-C17-WG14 — WG14 N2176 proposed C17 committee draft: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2176.pdf (publisher: ISO/IEC JTC 1/SC 22/WG14; version: N2176, 2017-10-09; non-final public committee document; accessed_at: 2026-08-21; license: Publicly accessible committee document; link and paraphrase only; allowed_use: reference)
- SRC-GCC11 — GCC 11.4 manuals: https://gcc.gnu.org/onlinedocs/gcc-11.4.0/ (publisher: GNU Project / Free Software Foundation; version: 11.4.0; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3 or later; allowed_use: reference)
- SRC-MAKE43 — GNU Make Manual: https://www.gnu.org/software/make/manual/make.html (publisher: GNU Project / Free Software Foundation; version: 4.3-compatible scope; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3; allowed_use: reference)
- SRC-CMAKE322 — CMake 3.22 Documentation: https://cmake.org/cmake/help/v3.22/ (publisher: Kitware; version: 3.22; accessed_at: 2026-08-21; license: BSD 3-Clause; allowed_use: reference)
- SRC-BINUTILS238 — GNU Binutils documentation: https://sourceware.org/binutils/docs-2.38/binutils/ (publisher: GNU Project / Free Software Foundation; version: 2.38; accessed_at: 2026-08-21; license: GNU Free Documentation License 1.3; allowed_use: reference)
- SRC-CERTC — SEI CERT C Coding Standard: https://cmu-sei.github.io/secure-coding-standards/sei-cert-c-coding-standard/ (publisher: Carnegie Mellon University Software Engineering Institute; version: online work-in-progress snapshot as accessed; claims constrained to C17; accessed_at: 2026-08-21; license: CMU/SEI terms; reference and limited quotation only; allowed_use: reference)

### Phần bổ sung/suy diễn
- **[SUY DIỄN — từ preprocessor C17]** X-macro là idiom dùng lại một danh sách token qua nhiều lần macro expansion, không phải một language feature có tên trong ISO C.
- **[BỔ SUNG — CMake 3.22 và GNU Binutils 2.38]** Tên target, output directory và inspection workflow được chọn làm oracle đào tạo; chúng không phải yêu cầu đóng gói hệ thống.

---

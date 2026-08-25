# Hands-on Lab LAB-P03-01 — Điều tra crash và dựng quality gate tái lập

> **Khóa học:** [NFP] Advanced C Programming · **Unit:** Session 06 — Debugging, testing and code-quality gates · **Thuộc:** Part 3 — Build System, Toolchain, Debugging & Unit Testing

| Thuộc tính | Giá trị |
| --- | --- |
| Mã lab | LAB-P03-01 |
| Hình thức | guided_with_fading |
| Thời lượng dự kiến | 90 phút |
| Độ khó | medium |
| Mức xác thực | inherit — project simulated, dữ liệu synthetic |
| Pilot | fresher with C basics, biên thời lượng ±20% |

## 🎯 Learning Outcomes được thực hành

- **ADVC-H3SD:** đánh giá và cải thiện build, debug, test, phân tích tĩnh và coverage bằng bằng chứng tái lập. LO này được kiểm ở cả ba checkpoint qua CTest log, GDB root-cause note và quality-gate manifest.

## 🧭 Bối cảnh nghề nghiệp/dự án và project increment

Học viên đóng vai quality reviewer của **MDB Edge Diagnostics Gateway — Simulated**. Baseline là package v5 cùng một fixture legacy crash đã được cô lập. Lab tạo một evidence slice của milestone M06: chứng minh baseline test, xác định root cause của crash mà không sửa fixture để che lỗi, rồi dựng sanitizer/static-analysis/coverage gates cho production module đã có defensive contract.

Lab không triển khai change request của Assignment 06. Artifact có thể tái sử dụng ở S07 chỉ là phương pháp evidence và gate manifest, không phải code lời giải.

## 🧰 Điều kiện bắt đầu

### Kiến thức/kỹ năng tiên quyết

- Đã học S05: translation unit, Debug build, compile database và target-scoped flags.
- Biết đọc process exit status, CTest summary và stack frame cơ bản.
- Không đổi public API, test oracle hay crash input để làm gate “xanh”.

### Môi trường, công cụ và phiên bản

- Ubuntu 22.04, C17; local sandbox/container `codex/adv-c-jammy:20260821` hoặc môi trường tương đương.
- GCC/gcov 11.4, Clang/clang-tidy 14, CMake 3.22.1, GDB 12.1, cppcheck 2.7, CMocka 1.1.5, LCOV package baseline 1.15-1 (CLI có thể in 1.14).
- Không network, credential, service, sudo, core upload hoặc production endpoint.

Preflight:

```bash
gcc --version | head -1
clang-14 --version | head -1
cmake --version | head -1
gdb --version | head -1
cppcheck --version
pkg-config --modversion cmocka
lcov --version
```

### Starter asset

- [assets/s06_case](assets/s06_case/CMakeLists.txt), gồm CMake project, CMocka tests, production module đã có error contract và `fixtures/legacy_crash.c` chỉ dùng cho triage.
- Plan path: `Phan_3_Unit_03__Build_System_Toolchain_Debugging__Unit_Testing/Session_3_S06_Session_06__Debugging_testing_and_code-quality_gates/assets/s06_case/`.

Tạo bản sao cô lập; không sửa asset phát hành:

```bash
export LAB03_BUILD_ROOT="$(mktemp -d /tmp/advc-lab03.XXXXXX)"
export LAB03_EVIDENCE="$PWD/lab03-deliverables"
mkdir -p "$LAB03_EVIDENCE"
cp -a assets/s06_case "$LAB03_BUILD_ROOT/source"
printf 'build_root=%s\n' "$LAB03_BUILD_ROOT" | tee "$LAB03_EVIDENCE/lab03_environment.log"
```

### Input/trạng thái ban đầu

- Default project không build crash fixture; một CTest contract phải pass.
- Khi bật `BUILD_CRASH_FIXTURE`, chạy không argument đưa null vào `legacy_first` và tạo `SIGSEGV` có thể tái hiện.
- Production coverage denominator của lab chỉ gồm `src/gateway_stats.c`; tests và system headers không nằm trong denominator.

### Ràng buộc

- Chỉ ghi build output dưới exact `$LAB03_BUILD_ROOT`; evidence nằm trong `$LAB03_EVIDENCE`.
- Không chỉnh `legacy_crash.c`, không thay input, không suppress toàn bộ analyzer và không lọc production source khỏi coverage.
- GDB/core evidence chỉ dùng dữ liệu synthetic; không tạo hoặc nộp raw core dump.
- ASan+UBSan và coverage là build riêng; không trộn `.gcda`, report hoặc binary.

## 📚 Nguồn và provenance

- Nguồn kỹ thuật đã map: SRC-GCC11, SRC-GDB121, SRC-LLVM14, SRC-CPPCHECK27, SRC-CMOCKA115, SRC-LCOV115 và SRC-CERTC.
- **[BỔ SUNG — nguồn: SRC-USER-LABS]** Guided workflow ba checkpoint, tên deliverable, thời lượng và fading policy do người dùng yêu cầu; không tuyên bố là activity gốc của syllabus.

## 📋 Lab outline và Definition of Done

### Phạm vi

1. Cố định baseline CMake/CTest và tool fingerprint.
2. Dùng GDB xác định failing frame, bad state và violated precondition của `legacy_crash`.
3. Tự hoàn thiện sanitizer/static-analysis/coverage gate và manifest có oracle.

### Definition of Done

- Default và ASan+UBSan CTest đều pass `1/1`, exit `0`.
- Root-cause note ghi reproducer, `SIGSEGV`, `legacy_first(values=0x0)`, caller, violated precondition và remediation direction nhưng không chứa code lời giải.
- cppcheck và scoped clang-tidy exit `0`; production line coverage tối thiểu 80%. Trong pinned container, starter hiện đạt 100% (10/10 lines).
- Có đủ `lab03_root_cause.md`, `lab03_test.log`, `lab03_coverage.log`, `lab03_gate_manifest.md`; manifest phân biệt diagnostic expected-fail với release pass gate.
- Build directories được cleanup bằng exact run path; evidence được giữ cho S07.

## 🪜 Mức hướng dẫn

- **Checkpoint CP-LAB-P03-01 — guided:** command và oracle đầy đủ.
- **Checkpoint CP-LAB-P03-02 — guided:** command GDB đầy đủ; học viên tự viết diagnosis từ evidence.
- **Checkpoint CP-LAB-P03-03 — fading:** cung cấp gate boundary và command family; học viên tự tổ chức manifest, kiểm exit status và giải thích disposition.

---

## Checkpoint CP-LAB-P03-01 — Baseline CMake/CTest

### Action

Configure một Debug build từ bản sao starter, xuất compile database, build default targets và chạy test. Lưu exact command/output; không bật crash fixture ở checkpoint này.

### Verify

```bash
set -o pipefail
cmake -S "$LAB03_BUILD_ROOT/source" -B "$LAB03_BUILD_ROOT/debug" \
  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON 2>&1 | \
  tee "$LAB03_EVIDENCE/lab03_configure.log"
cmake --build "$LAB03_BUILD_ROOT/debug" 2>&1 | \
  tee "$LAB03_EVIDENCE/lab03_build.log"
ctest --test-dir "$LAB03_BUILD_ROOT/debug" --output-on-failure 2>&1 | \
  tee "$LAB03_EVIDENCE/lab03_test.log"
```

### Expected result

- Configure/build/CTest đều exit `0`.
- CMake tìm thấy CMocka 1.1.5.
- CTest có `1/1 Test #1: gateway_stats_contract ... Passed` và `100% tests passed, 0 tests failed out of 1`.
- Default build không có executable `apps/gateway_crash_fixture`.

### Evidence

Giữ `lab03_environment.log`, `lab03_configure.log`, `lab03_build.log` và `lab03_test.log`. Trong gate manifest, ghi compiler/CMake/CMocka fingerprint và SHA-256 của `lab03_test.log`.

### Troubleshooting

- `cmocka` không được tìm thấy → kiểm `pkg-config --modversion cmocka`; dùng đúng image/môi trường cấp phát, không bỏ test target.
- CTest báo “No tests” → kiểm configure source path và `BUILD_TESTING`; không gọi binary ngoài build vừa tạo.
- Compile database thiếu → clean riêng `$LAB03_BUILD_ROOT/debug`, configure lại với `CMAKE_EXPORT_COMPILE_COMMANDS=ON`.

### Reset/rollback

Chỉ reset checkpoint này:

```bash
case "$LAB03_BUILD_ROOT" in
  /tmp/advc-lab03.*) rm -rf -- "$LAB03_BUILD_ROOT/debug" ;;
  *) printf 'Refuse unsafe reset: %s\n' "$LAB03_BUILD_ROOT" >&2; exit 64 ;;
esac
```

Chạy lại configure và CTest để xác nhận baseline sạch.

---

## Checkpoint CP-LAB-P03-02 — GDB root cause của legacy crash

### Action

Tạo build triage riêng có `BUILD_CRASH_FIXTURE=ON`. Chạy fixture không argument trong GDB batch, lấy signal, frame và locals. Viết `lab03_root_cause.md` gồm: reproducer; observed bad state; violated precondition; vì sao đổi fixture là invalid fix; remediation direction và regression oracle. Không sửa source ở checkpoint này.

### Verify

```bash
cmake -S "$LAB03_BUILD_ROOT/source" -B "$LAB03_BUILD_ROOT/triage" \
  -DCMAKE_BUILD_TYPE=Debug -DBUILD_CRASH_FIXTURE=ON
cmake --build "$LAB03_BUILD_ROOT/triage" --target gateway_crash_fixture
gdb -q -batch -ex 'set pagination off' -ex run -ex 'bt full' \
  --args "$LAB03_BUILD_ROOT/triage/apps/gateway_crash_fixture" 2>&1 | \
  tee "$LAB03_EVIDENCE/lab03_gdb.log"
grep -F 'Program received signal SIGSEGV' "$LAB03_EVIDENCE/lab03_gdb.log"
grep -E '#0 .*legacy_first.*values=0x0' "$LAB03_EVIDENCE/lab03_gdb.log"
grep -E '#1 .*main' "$LAB03_EVIDENCE/lab03_gdb.log"
```

### Expected result

- Build exit `0`; GDB command exit `0` vì debugger hoàn tất batch session.
- Target nhận `SIGSEGV`; frame `#0` là `legacy_first(values=0x0)`, frame `#1` là `main`.
- Root-cause note kết luận caller cho phép null tới function dereference `values[0]`; note không coi crash line tự thân là remediation.

### Evidence

- `lab03_gdb.log` nguyên bản từ run hiện tại.
- `lab03_root_cause.md` trích exact frames, tool/build fingerprint và đề xuất regression oracle cho null/empty contract.

### Troubleshooting

- GDB hiện `??`/không có line → xác nhận `Debug`, không strip, đúng executable vừa build.
- Fixture exit `0` → kiểm có vô tình truyền argument hoặc sửa fixture; khôi phục từ starter copy.
- Container cảnh báo không tắt ASLR → vẫn dùng signal/frame/value làm oracle; không coi warning đó là failure.

### Reset/rollback

Xóa riêng triage build bằng cùng guard path như Checkpoint `CP-LAB-P03-01`. Không xóa `lab03_gdb.log` hay root-cause note; chúng là pre-fix evidence cần cho manifest.

---

## Checkpoint CP-LAB-P03-03 — Fading quality gate: sanitizer, analysis và coverage

### Action

Từ production module/test hiện có, tự tổ chức ba build độc lập: ASan+UBSan, analysis và coverage. Không build crash fixture vào pass suite. Hoàn thiện `lab03_gate_manifest.md` với cột `gate | command/tool version | expected | observed | status | evidence`.

### Verify

```bash
set -o pipefail
cmake -S "$LAB03_BUILD_ROOT/source" -B "$LAB03_BUILD_ROOT/asan" \
  -DCMAKE_C_COMPILER=clang-14 -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_C_FLAGS='-O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined' \
  -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined'
cmake --build "$LAB03_BUILD_ROOT/asan"
ASAN_OPTIONS=halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir "$LAB03_BUILD_ROOT/asan" --output-on-failure 2>&1 | \
  tee -a "$LAB03_EVIDENCE/lab03_test.log"

cmake -S "$LAB03_BUILD_ROOT/source" -B "$LAB03_BUILD_ROOT/analysis" \
  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$LAB03_BUILD_ROOT/analysis"
cppcheck --project="$LAB03_BUILD_ROOT/analysis/compile_commands.json" \
  --std=c11 --error-exitcode=1 2>&1 | tee "$LAB03_EVIDENCE/lab03_cppcheck.log"
clang-tidy-14 -p "$LAB03_BUILD_ROOT/analysis" \
  "$LAB03_BUILD_ROOT/source/src/gateway_stats.c" \
  --checks='-*,clang-analyzer-core.*,clang-analyzer-unix.*,cert-err33-c' \
  --warnings-as-errors='*' 2>&1 | tee "$LAB03_EVIDENCE/lab03_clang_tidy.log"

cmake -S "$LAB03_BUILD_ROOT/source" -B "$LAB03_BUILD_ROOT/coverage" \
  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS='-O0 -g --coverage' \
  -DCMAKE_EXE_LINKER_FLAGS='--coverage'
cmake --build "$LAB03_BUILD_ROOT/coverage"
ctest --test-dir "$LAB03_BUILD_ROOT/coverage" --output-on-failure
lcov --capture --directory "$LAB03_BUILD_ROOT/coverage" \
  --output-file "$LAB03_BUILD_ROOT/all.info" --rc lcov_branch_coverage=1
lcov --remove "$LAB03_BUILD_ROOT/all.info" '/usr/*' '*/tests/*' \
  --output-file "$LAB03_BUILD_ROOT/production.info" \
  --rc lcov_branch_coverage=1
lcov --summary "$LAB03_BUILD_ROOT/production.info" \
  --rc lcov_branch_coverage=1 2>&1 | tee "$LAB03_EVIDENCE/lab03_coverage.log"
```

### Expected result

- Sanitizer CTest pass `1/1`, exit `0`, không có ASan/UBSan report thuộc project.
- cppcheck và clang-tidy exit `0`, không có finding chưa disposition trong scoped check-set.
- `lab03_coverage.log` báo production line coverage ít nhất `80.0%`; pinned starter được kiểm thực tế ở `100.0% (10 of 10 lines)`.
- LCOV có thể in cảnh báo Perl `Subroutine ... redefined` trên Jammy nhưng command vẫn phải exit `0` và summary hợp lệ; lưu warning thay vì xóa evidence.

### Evidence

`lab03_test.log`, `lab03_cppcheck.log`, `lab03_clang_tidy.log`, `lab03_coverage.log` và `lab03_gate_manifest.md`. Manifest phải ghi diagnostic crash là `EXPECTED-FAIL-EVIDENCE`, còn default/sanitizer/analysis/coverage là pass gates.

### Troubleshooting

- ASan fail chỉ trong combined build → kiểm cùng compiler và linker sanitizer flags; không trộn binary GCC/Clang.
- Analyzer thiếu include/define → kiểm exact entry trong `compile_commands.json`, không suppress rộng.
- Coverage bằng 0/stale → xóa riêng coverage build, configure/run test/capture lại; không reuse `.gcda`.
- Coverage thấp → bổ sung behavioral test trong scratch nếu cần; không loại `src/gateway_stats.c` khỏi denominator.

### Reset/rollback

Xóa riêng build `asan`, `analysis`, `coverage` và trace tạm dưới `$LAB03_BUILD_ROOT`; giữ evidence. Nếu muốn chạy lại, copy starter vào một run root mới để tránh report stale.

## 🧪 Final validation

**Phương thức xác minh:** `executable`, fail-fast. Chạy từ thư mục Session sau khi hoàn tất ba checkpoint. `lab03_gate_manifest.md` phải chứa mỗi record máy đọc được sau trên một dòng riêng: `default=PASS`, `triage=EXPECTED-FAIL-EVIDENCE`, `asan_ubsan=PASS`, `cppcheck=PASS`, `clang_tidy=PASS`, `coverage=PASS`, `evidence_hashes=lab03_current.sha256`.

```bash
set -Eeuo pipefail
: "${LAB03_BUILD_ROOT:?Run phần Starter asset trước}"
: "${LAB03_EVIDENCE:?Run phần Starter asset trước}"
test -d "$LAB03_BUILD_ROOT/source"
test -d "$LAB03_EVIDENCE"
test -s "$LAB03_EVIDENCE/lab03_root_cause.md"
test -s "$LAB03_EVIDENCE/lab03_gate_manifest.md"

case "$LAB03_BUILD_ROOT" in
  /tmp/advc-lab03.*) ;;
  *) printf 'Unsafe learner root: %s\n' "$LAB03_BUILD_ROOT" >&2; exit 64 ;;
esac

LAB03_FINAL_ROOT="$(mktemp -d /tmp/advc-lab03-final.XXXXXX)"
lab03_final_cleanup() {
  case "${LAB03_FINAL_ROOT:-}" in
    /tmp/advc-lab03-final.*) rm -rf -- "$LAB03_FINAL_ROOT" ;;
    *) printf 'Refuse unsafe final cleanup: %s\n' \
         "${LAB03_FINAL_ROOT:-unset}" >&2; return 64 ;;
  esac
}
trap lab03_final_cleanup EXIT INT TERM
test -z "$(find "$LAB03_FINAL_ROOT" -mindepth 1 -maxdepth 1 -print -quit)"
cp -a "$LAB03_BUILD_ROOT/source" "$LAB03_FINAL_ROOT/source"
cmp -s "$LAB03_FINAL_ROOT/source/fixtures/legacy_crash.c" \
  assets/s06_case/fixtures/legacy_crash.c

source_sha256="$({
  cd "$LAB03_FINAL_ROOT/source"
  find . -type f -print0 | LC_ALL=C sort -z | xargs -0 sha256sum
} | sha256sum | awk '{print $1}')"
{
  printf 'source_sha256=%s\n' "$source_sha256"
  gcc --version | head -1
  clang-14 --version | head -1
  cmake --version | head -1
  gdb --version | head -1
  cppcheck --version
  pkg-config --modversion cmocka
  lcov --version
} > "$LAB03_EVIDENCE/lab03_final_environment.log"
: > "$LAB03_EVIDENCE/lab03_test.log"

# Default build + exact CTest oracle.
cmake -S "$LAB03_FINAL_ROOT/source" -B "$LAB03_FINAL_ROOT/default" \
  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON 2>&1 | \
  tee "$LAB03_EVIDENCE/lab03_final_configure.log"
cmake --build "$LAB03_FINAL_ROOT/default" 2>&1 | \
  tee "$LAB03_EVIDENCE/lab03_final_build.log"
ctest --test-dir "$LAB03_FINAL_ROOT/default" --output-on-failure 2>&1 | \
  tee -a "$LAB03_EVIDENCE/lab03_test.log"
test ! -e "$LAB03_FINAL_ROOT/default/apps/gateway_crash_fixture"
test "$(grep -Fxc '100% tests passed, 0 tests failed out of 1' \
  "$LAB03_EVIDENCE/lab03_test.log")" -eq 1

# Triage build: crash là expected diagnostic evidence, không phải pass gate.
cmake -S "$LAB03_FINAL_ROOT/source" -B "$LAB03_FINAL_ROOT/triage" \
  -DCMAKE_BUILD_TYPE=Debug -DBUILD_CRASH_FIXTURE=ON
cmake --build "$LAB03_FINAL_ROOT/triage" --target gateway_crash_fixture
gdb -q -batch -ex 'set pagination off' -ex run -ex 'bt full' \
  --args "$LAB03_FINAL_ROOT/triage/apps/gateway_crash_fixture" 2>&1 | \
  tee "$LAB03_EVIDENCE/lab03_gdb.log"
grep -F 'Program received signal SIGSEGV' \
  "$LAB03_EVIDENCE/lab03_gdb.log"
grep -E '#0 .*legacy_first.*values=0x0' \
  "$LAB03_EVIDENCE/lab03_gdb.log"
grep -E '#1 .*main' "$LAB03_EVIDENCE/lab03_gdb.log"
grep -F 'SIGSEGV' "$LAB03_EVIDENCE/lab03_root_cause.md"
grep -F 'legacy_first(values=0x0)' \
  "$LAB03_EVIDENCE/lab03_root_cause.md"
grep -F 'main' "$LAB03_EVIDENCE/lab03_root_cause.md"
grep -Fi 'violated precondition' \
  "$LAB03_EVIDENCE/lab03_root_cause.md"

# ASan+UBSan pass build.
cmake -S "$LAB03_FINAL_ROOT/source" -B "$LAB03_FINAL_ROOT/asan" \
  -DCMAKE_C_COMPILER=clang-14 -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_C_FLAGS='-O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined' \
  -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined'
cmake --build "$LAB03_FINAL_ROOT/asan"
ASAN_OPTIONS=halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir "$LAB03_FINAL_ROOT/asan" --output-on-failure 2>&1 | \
  tee -a "$LAB03_EVIDENCE/lab03_test.log"
test "$(grep -Fxc '100% tests passed, 0 tests failed out of 1' \
  "$LAB03_EVIDENCE/lab03_test.log")" -eq 2
! grep -E 'ERROR: AddressSanitizer|runtime error:' \
  "$LAB03_EVIDENCE/lab03_test.log"

# Static analysis trên exact learner snapshot.
cmake -S "$LAB03_FINAL_ROOT/source" -B "$LAB03_FINAL_ROOT/analysis" \
  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "$LAB03_FINAL_ROOT/analysis"
cppcheck --project="$LAB03_FINAL_ROOT/analysis/compile_commands.json" \
  --std=c11 --error-exitcode=1 2>&1 | \
  tee "$LAB03_EVIDENCE/lab03_cppcheck.log"
clang-tidy-14 -p "$LAB03_FINAL_ROOT/analysis" \
  "$LAB03_FINAL_ROOT/source/src/gateway_stats.c" \
  --checks='-*,clang-analyzer-core.*,clang-analyzer-unix.*,cert-err33-c' \
  --warnings-as-errors='*' 2>&1 | \
  tee "$LAB03_EVIDENCE/lab03_clang_tidy.log"

# LCOV production-only denominator và exact pinned oracle.
cmake -S "$LAB03_FINAL_ROOT/source" -B "$LAB03_FINAL_ROOT/coverage" \
  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS='-O0 -g --coverage' \
  -DCMAKE_EXE_LINKER_FLAGS='--coverage'
cmake --build "$LAB03_FINAL_ROOT/coverage"
ctest --test-dir "$LAB03_FINAL_ROOT/coverage" --output-on-failure
lcov --capture --directory "$LAB03_FINAL_ROOT/coverage" \
  --output-file "$LAB03_FINAL_ROOT/all.info" \
  --rc lcov_branch_coverage=1
lcov --remove "$LAB03_FINAL_ROOT/all.info" '/usr/*' '*/tests/*' \
  --output-file "$LAB03_FINAL_ROOT/production.info" \
  --rc lcov_branch_coverage=1
lcov --summary "$LAB03_FINAL_ROOT/production.info" \
  --rc lcov_branch_coverage=1 2>&1 | \
  tee "$LAB03_EVIDENCE/lab03_coverage.log"
coverage_pct="$(sed -n \
  's/.*lines[.]*:[[:space:]]*\([0-9.]*\)%.*/\1/p' \
  "$LAB03_EVIDENCE/lab03_coverage.log" | tail -1)"
test -n "$coverage_pct"
awk -v pct="$coverage_pct" 'BEGIN { exit !(pct + 0 >= 80.0) }'
grep -F 'lines......: 100.0% (10 of 10 lines)' \
  "$LAB03_EVIDENCE/lab03_coverage.log"

# Manifest phải mô tả đúng run vừa tạo; hash file khóa exact evidence hiện tại.
for gate_record in \
  default=PASS \
  triage=EXPECTED-FAIL-EVIDENCE \
  asan_ubsan=PASS \
  cppcheck=PASS \
  clang_tidy=PASS \
  coverage=PASS \
  evidence_hashes=lab03_current.sha256
do
  grep -Fx "$gate_record" "$LAB03_EVIDENCE/lab03_gate_manifest.md"
done
(
  cd "$LAB03_EVIDENCE"
  sha256sum \
    lab03_root_cause.md \
    lab03_test.log \
    lab03_gdb.log \
    lab03_cppcheck.log \
    lab03_clang_tidy.log \
    lab03_coverage.log \
    lab03_gate_manifest.md \
    lab03_final_environment.log > lab03_current.sha256
  sha256sum -c lab03_current.sha256
)

lab03_final_cleanup
trap - EXIT INT TERM
test ! -e "$LAB03_FINAL_ROOT"
printf 'LAB03_FINAL_PASS source_sha256=%s coverage=%s%%\n' \
  "$source_sha256" "$coverage_pct"
```

Final validation chỉ pass khi in `LAB03_FINAL_PASS`, mọi command exit `0`, hai CTest summary khớp exact oracle, GDB/analysis/coverage chạy lại trên cùng learner snapshot, `sha256sum -c` pass và final scratch đã bị xóa. Bất kỳ mismatch nào dừng script ngay; không được tái dùng log từ build trước.

## 📦 Deliverables

- `lab03_root_cause.md`
- `lab03_test.log`
- `lab03_coverage.log`
- `lab03_gate_manifest.md`

Các configure/build/GDB/analyzer logs là supporting evidence nên giữ cùng deliverables khi nộp.

## ♻️ Reset, cleanup và khả năng chạy lại

```bash
case "$LAB03_BUILD_ROOT" in
  /tmp/advc-lab03.*) rm -rf -- "$LAB03_BUILD_ROOT" ;;
  *) printf 'Refuse unsafe cleanup: %s\n' "$LAB03_BUILD_ROOT" >&2; exit 64 ;;
esac
test ! -e "$LAB03_BUILD_ROOT"
```

Không xóa `$LAB03_EVIDENCE`. Lab không tạo network/service/IPC resource và không dùng credential.

## 🔁 Tái sử dụng ở S07

S07 dùng `lab03_gate_manifest.md`, test log và cách ghi root-cause evidence làm baseline trước khi thêm process/signal lifecycle. Không copy crash fixture hoặc biến diagnostic expected-fail thành release test.

## 🔐 Chính sách lời giải

Learner file chỉ cung cấp command, checkpoint, oracle và hint giảm dần. Không có reference implementation hay walkthrough của Assignment 06; instructor solution, nếu có, phải lưu ngoài learner output.

## 📚 Provenance phần bổ sung

- **[BỔ SUNG — nguồn: SRC-USER-LABS]** Lab guided_with_fading, duration, deliverables, checkpoint và reuse-by-S07 được thêm theo yêu cầu người dùng.
- Command semantics dựa trên các nguồn GCC/GDB/LLVM/cppcheck/CMocka/LCOV đã map; gateway và evidence policy kế thừa project simulated.

---
<!-- QUALITY GATE: 3/3 checkpoint có Action/Verify/Expected/Evidence/Troubleshooting/Reset; network-none; synthetic-only; không lộ Assignment. -->

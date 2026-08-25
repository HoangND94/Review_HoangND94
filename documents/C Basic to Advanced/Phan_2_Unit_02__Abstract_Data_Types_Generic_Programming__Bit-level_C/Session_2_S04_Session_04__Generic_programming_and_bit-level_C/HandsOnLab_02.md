# Hands-on Lab 02 — Dựng container generic và packet bit-level có oracle

> **Lab ID:** `LAB-P02-01` · **Thời lượng:** 90 phút · **Mode:** `guided_with_fading` · **Độ khó:** medium
>
> **Provenance phạm vi:** **[BỔ SUNG — nguồn: SRC-USER-LABS]**. Lab dùng project context và nguồn kỹ thuật đã map của S04; dữ liệu và tình huống đều simulated/synthetic.

## 🎯 Learning Outcomes được thực hành

- **LO:** `ADVC-H1SD` — áp dụng generic byte contract, intrusive membership, unsigned flags và FAM boundary; kiểm chứng bằng CTest và Valgrind.
- **Project slice:** M04, nhưng chỉ fork/instrument case mẫu trong scratch; không xây Generic gateway core v4 hoặc làm thay ASM-A04.
- **Scenario:** maintainer cần một proof nhỏ cho container/packet decisions trước khi S05 đóng gói source qua translation-unit và library boundary.
- **Reused by:** S05 dùng scratch diff và evidence để xác định public/private boundary, compile options và test oracle cần giữ khi package.

## 2. Prerequisite, input và ràng buộc

### Prerequisite

- Đã đọc `OUT-S04-01` trong [material.md](material.md) và hiểu `len <= cap`, element-size contract, member lifetime, unsigned mask và FAM extent.
- Chạy được CMake/CTest trong `ENV-ADV-C-JAMMY`.
- Biết đọc exit code, stdout/stderr và Valgrind summary.

### Starter và input

- Starter duy nhất: [assets/s04_case/](assets/s04_case/CMakeLists.txt), gồm `CMakeLists.txt` và `s04_case.c`.
- Fixture có sẵn: `uint16_t {10,20,30}`, intrusive records `1/2`, flags `0x00000005`, tagged reading và packet payload `abc`.
- Deliverables: scratch fork/diff, `lab02_evidence.md`, `lab02_baseline.log`, `lab02_valgrind.log`.

### Safety và constraints

- Chỉ sửa `$LAB_P02_ROOT/work`; không sửa starter, Assignment hoặc project increment source.
- Container chạy `--network none`; source mount read-only và build tree nằm trong `/tmp` của container.
- Không copy Linux kernel macros/list implementation; không serialize raw bit-field/union representation.
- Không dùng side-effect argument trong unsafe macro; mọi byte-size/FAM extent phải được kiểm overflow trước phép tính.
- Không chạy Valgrind trên binary sanitizer; Lab này dùng debug binary riêng.

## 3. Khởi tạo scratch workspace

Chạy từ thư mục S04 chứa file Lab này:

```bash
export LAB_P02_ROOT="$(mktemp -d /tmp/lab-p02-01.XXXXXX)"
mkdir -p "$LAB_P02_ROOT/baseline" "$LAB_P02_ROOT/work"
cp -a assets/s04_case/. "$LAB_P02_ROOT/baseline/"
cp -a assets/s04_case/. "$LAB_P02_ROOT/work/"
printf 'scratch=%s\n' "$LAB_P02_ROOT"
```

`baseline/` chỉ để reset và tạo diff; mọi thay đổi phải nằm trong `work/s04_case.c`.

## 📋 Lab outline và Definition of Done

### Checkpoint CP-P02-01 — Baseline CMake/CTest (20 phút, hướng dẫn đầy đủ)

#### Action

Configure, build, chạy CTest và chạy binary trực tiếp trong container:

```bash
docker run --rm --network none \
  --mount "type=bind,source=$LAB_P02_ROOT/work,target=/lab,readonly" \
  codex/adv-c-jammy:20260821 sh -eu -c '
    cmake -S /lab -B /tmp/lab02_build -DCMAKE_BUILD_TYPE=Debug
    cmake --build /tmp/lab02_build --parallel
    ctest --test-dir /tmp/lab02_build --output-on-failure
    /tmp/lab02_build/s04_generic_case
  ' >"$LAB_P02_ROOT/lab02_baseline.log" 2>&1
baseline_source_hash="$(sha256sum "$LAB_P02_ROOT/work/s04_case.c" | awk '{print $1}')"
baseline_cmake_hash="$(sha256sum "$LAB_P02_ROOT/work/CMakeLists.txt" | awk '{print $1}')"
printf 'SOURCE_SHA256=%s\nCMAKE_SHA256=%s\n' \
  "$baseline_source_hash" "$baseline_cmake_hash" \
  >>"$LAB_P02_ROOT/lab02_baseline.log"
cat "$LAB_P02_ROOT/lab02_baseline.log"
```

#### Verify

```bash
grep -q '100% tests passed, 0 tests failed out of 1' \
  "$LAB_P02_ROOT/lab02_baseline.log"
grep -q '^vector=10,20,30$' "$LAB_P02_ROOT/lab02_baseline.log"
grep -q '^list_id_sum=3 flags=0x00000005$' \
  "$LAB_P02_ROOT/lab02_baseline.log"
grep -q '^reading_temperature=42 packet=abc$' \
  "$LAB_P02_ROOT/lab02_baseline.log"
grep -q '^S04_CASE_PASS$' "$LAB_P02_ROOT/lab02_baseline.log"
grep -Fx "SOURCE_SHA256=$baseline_source_hash" \
  "$LAB_P02_ROOT/lab02_baseline.log"
grep -Fx "CMAKE_SHA256=$baseline_cmake_hash" \
  "$LAB_P02_ROOT/lab02_baseline.log"
```

#### Expected result

Container và năm lệnh `grep` exit `0`; CTest pass `1/1`; binary in đúng vector/list/reading oracle, một dòng layout implementation-specific và `S04_CASE_PASS`. Compiler warning count là `0` vì CMake bật `-Werror`.

#### Evidence

Giữ `lab02_baseline.log`. Tạo `lab02_evidence.md` và ghi image, exact command, CMake/CTest result, program stdout/stderr, exit code và hai marker SHA-256 vừa ghi cho source/CMake starter.

#### Troubleshooting

Nếu CMake không tìm source, kiểm mount có `/lab/CMakeLists.txt` và `/lab/s04_case.c`. Nếu CTest pass nhưng grep program fail, bảo đảm binary đã được chạy trực tiếp sau CTest; CTest có thể ẩn stdout của test pass.

#### Reset

Khôi phục source làm việc bằng:

```bash
cp "$LAB_P02_ROOT/baseline/s04_case.c" \
  "$LAB_P02_ROOT/work/s04_case.c"
```

### Checkpoint CP-P02-02 — Generic/container decision (35 phút, hướng dẫn vừa)

#### Action

Mở rộng scratch fork bằng một fixture audit, không thêm API Assignment:

1. Dùng byte-vector hiện có với input `uint8_t {3,1,4}`; chứng minh `elem_size=1`, `len=3`, first `3`, last `4`.
2. Tạo một reserve-failure snapshot và chứng minh `data/len/cap` giữ nguyên.
3. Dùng list fixture hiện có để xuất `id_sum=3` và việc double-insert bị từ chối.
4. Ghi decision trong evidence: byte-copy ownership, lý do phải mang `elem_size`, valid `container_of` member/lifetime và một-node/một-membership rule.

Thêm đúng hai dòng stdout:

```text
LAB02_VECTOR elem_size=1 len=3 first=3 last=4 reserve_preserved=1
LAB02_LIST id_sum=3 double_insert_rejected=1
```

Mức gợi ý đã giảm: tái sử dụng helper của case, tự chọn fixture lifetime/cleanup; không cài remove/shrink API hoặc generic gateway adapter của ASM-A04.

#### Verify

```bash
docker run --rm --network none \
  --mount "type=bind,source=$LAB_P02_ROOT/work,target=/lab,readonly" \
  codex/adv-c-jammy:20260821 sh -eu -c '
    cmake -S /lab -B /tmp/lab02_build -DCMAKE_BUILD_TYPE=Debug
    cmake --build /tmp/lab02_build --parallel
    ctest --test-dir /tmp/lab02_build --output-on-failure
    /tmp/lab02_build/s04_generic_case
  ' >"$LAB_P02_ROOT/cp2_container.log" 2>&1
cp2_source_hash="$(sha256sum "$LAB_P02_ROOT/work/s04_case.c" | awk '{print $1}')"
printf 'SOURCE_SHA256=%s\n' "$cp2_source_hash" \
  >>"$LAB_P02_ROOT/cp2_container.log"
grep -q '^LAB02_VECTOR elem_size=1 len=3 first=3 last=4 reserve_preserved=1$' \
  "$LAB_P02_ROOT/cp2_container.log"
grep -q '^LAB02_LIST id_sum=3 double_insert_rejected=1$' \
  "$LAB_P02_ROOT/cp2_container.log"
grep -q '^S04_CASE_PASS$' "$LAB_P02_ROOT/cp2_container.log"
grep -Fx "SOURCE_SHA256=$cp2_source_hash" \
  "$LAB_P02_ROOT/cp2_container.log"
```

#### Expected result

CMake/build/CTest và ba grep exit `0`; original case oracle vẫn pass. Failed reserve không đổi pointer/content/len/cap, double-insert không corrupt list và mọi scratch allocation được cleanup.

#### Evidence

Bổ sung `lab02_evidence.md` bằng before/after vector snapshot, list membership decision, exact command/output/exit code và source hash trùng marker trong `cp2_container.log`. Ghi rõ fixture audit khác scope Assignment: không có shrink/remove, adapter hoặc reusable public module.

#### Troubleshooting

Nếu element đọc sai, kiểm offset được tính theo byte từ `index * elem_size` và cùng type đã push. Nếu failed reserve đổi state, kiểm code commit `data/cap` trước hay sau khi temporary allocation thành công. Nếu list corrupt, kiểm node đã được `list_node_init` và chưa linked trước insert.

#### Reset

Restore `work/s04_case.c` từ `baseline/`, rồi chạy lại CP-P02-01 trước khi thử thiết kế khác. Evidence/log cũ không được dùng cho source đã reset nếu hash không khớp.

### Checkpoint CP-P02-03 — Flags, FAM boundary và Valgrind (35 phút, fading)

#### Action

Tự bổ sung fixture cuối với ít gợi ý hơn:

- Tạo truth-table nhỏ cho allowed masks, giữ unsigned fixed-width storage và chứng minh reserved bit bị từ chối; xuất state cuối `0x00000005`.
- Tạo FAM packet synthetic có payload 5 byte, chứng minh length `5`, payload đúng và overflow extent bị từ chối trước allocation.
- Giữ tagged-union active-member rule và không dùng raw bit-field/union bytes làm wire oracle.
- Chạy toàn bộ CTest và Valgrind; không đổi original `S04_CASE_PASS`.

Hai dòng stdout mới bắt buộc:

```text
LAB02_FLAGS state=0x00000005 reserved_rejected=1
LAB02_PACKET len=5 overflow_rejected=1
```

Mức fading: Lab chỉ chốt contract/oracle; tự chọn payload, assertions, cleanup order và vị trí report.

#### Verify

```bash
docker run --rm --network none \
  --mount "type=bind,source=$LAB_P02_ROOT/work,target=/lab,readonly" \
  codex/adv-c-jammy:20260821 sh -eu -c '
    cmake -S /lab -B /tmp/lab02_build -DCMAKE_BUILD_TYPE=Debug
    cmake --build /tmp/lab02_build --parallel
    ctest --test-dir /tmp/lab02_build --output-on-failure
    valgrind --tool=memcheck --leak-check=full \
      --errors-for-leak-kinds=definite,indirect --error-exitcode=99 \
      /tmp/lab02_build/s04_generic_case
  ' >"$LAB_P02_ROOT/lab02_valgrind.log" 2>&1
final_source_hash="$(sha256sum "$LAB_P02_ROOT/work/s04_case.c" | awk '{print $1}')"
printf 'SOURCE_SHA256=%s\n' "$final_source_hash" \
  >>"$LAB_P02_ROOT/lab02_valgrind.log"
grep -q '^LAB02_FLAGS state=0x00000005 reserved_rejected=1$' \
  "$LAB_P02_ROOT/lab02_valgrind.log"
grep -q '^LAB02_PACKET len=5 overflow_rejected=1$' \
  "$LAB_P02_ROOT/lab02_valgrind.log"
grep -q '^S04_CASE_PASS$' "$LAB_P02_ROOT/lab02_valgrind.log"
grep -q 'ERROR SUMMARY: 0 errors' "$LAB_P02_ROOT/lab02_valgrind.log"
grep -Fx "SOURCE_SHA256=$final_source_hash" \
  "$LAB_P02_ROOT/lab02_valgrind.log"
diff -u "$LAB_P02_ROOT/baseline/s04_case.c" \
  "$LAB_P02_ROOT/work/s04_case.c" \
  >"$LAB_P02_ROOT/lab02_scratch.diff" || test "$?" -eq 1
```

#### Expected result

Container, bốn grep và diff contract exit `0`; CTest pass `1/1`; original cùng four LAB02 oracle lines xuất hiện; Valgrind báo `ERROR SUMMARY: 0 errors` và không definite/indirect leak. Diff chỉ chứa fixture/probe trong scratch, không chứa thay đổi starter hoặc Assignment.

#### Evidence

Hoàn tất `lab02_evidence.md` bằng flag truth table, FAM extent calculation/overflow decision, cleanup order, exact commands, exit codes, source hash và liên kết tới `lab02_scratch.diff`, `lab02_baseline.log`, `lab02_valgrind.log`.

#### Troubleshooting

Nếu reserved mask được nhận, kiểm complement mask đã cast về `uint32_t` và shift count nằm trong width. Nếu FAM overflow fixture crash thay vì trả `NULL`, kiểm guard `len > SIZE_MAX - sizeof(header)` trước phép cộng. Nếu Valgrind báo leak, kiểm mọi packet/vector allocation có đúng một cleanup trên cả happy và failure path.

#### Reset

Restore file từ `baseline/` và chạy lại từ CP-P02-01. Sau khi đã sao lưu deliverables, cleanup chỉ được phép với guard:

```bash
case "$LAB_P02_ROOT" in
  /tmp/lab-p02-01.*) rm -rf -- "$LAB_P02_ROOT" ;;
  *) printf 'Refuse cleanup outside lab scratch\n' >&2; exit 1 ;;
esac
```

## 🧪 Final validation

**Phương thức:** executable

Chạy từ thư mục S04 bằng shell đã giữ biến `LAB_P02_ROOT`. Gate tạo ba container/build tree mới: baseline bất biến cho CP-P02-01, learner source hiện tại cho CP-P02-02, rồi chính learner source đó dưới Valgrind cho CP-P02-03. Vì vậy không có CMake cache, binary hoặc log cũ nào được dùng thay execution hiện tại:

```bash
set -eu
case "${LAB_P02_ROOT:-}" in
  /tmp/lab-p02-01.*) ;;
  *) printf 'Invalid LAB_P02_ROOT\n' >&2; exit 64 ;;
esac

test -s "$LAB_P02_ROOT/work/s04_case.c"
test -s "$LAB_P02_ROOT/work/CMakeLists.txt"
test -s "$LAB_P02_ROOT/baseline/s04_case.c"
test -s "$LAB_P02_ROOT/baseline/CMakeLists.txt"
test -s "$LAB_P02_ROOT/lab02_evidence.md"
test -s "assets/s04_case/s04_case.c"
test -s "assets/s04_case/CMakeLists.txt"

cmp -s "assets/s04_case/s04_case.c" \
  "$LAB_P02_ROOT/baseline/s04_case.c"
cmp -s "assets/s04_case/CMakeLists.txt" \
  "$LAB_P02_ROOT/baseline/CMakeLists.txt"
cmp -s "$LAB_P02_ROOT/baseline/CMakeLists.txt" \
  "$LAB_P02_ROOT/work/CMakeLists.txt"

baseline_source_hash="$(sha256sum "$LAB_P02_ROOT/baseline/s04_case.c" | awk '{print $1}')"
baseline_cmake_hash="$(sha256sum "$LAB_P02_ROOT/baseline/CMakeLists.txt" | awk '{print $1}')"
source_hash="$(sha256sum "$LAB_P02_ROOT/work/s04_case.c" | awk '{print $1}')"

docker run --rm --network none --read-only \
  --tmpfs /tmp:rw,exec,nosuid,nodev \
  --mount "type=bind,source=$LAB_P02_ROOT/baseline,target=/lab,readonly" \
  codex/adv-c-jammy:20260821 sh -eu -c '
    cmake -S /lab -B /tmp/lab02_baseline_final -DCMAKE_BUILD_TYPE=Debug
    cmake --build /tmp/lab02_baseline_final --parallel
    ctest --test-dir /tmp/lab02_baseline_final --output-on-failure
    /tmp/lab02_baseline_final/s04_generic_case
  ' >"$LAB_P02_ROOT/lab02_baseline.log" 2>&1
printf 'SOURCE_SHA256=%s\nCMAKE_SHA256=%s\n' \
  "$baseline_source_hash" "$baseline_cmake_hash" \
  >>"$LAB_P02_ROOT/lab02_baseline.log"

docker run --rm --network none --read-only \
  --tmpfs /tmp:rw,exec,nosuid,nodev \
  --mount "type=bind,source=$LAB_P02_ROOT/work,target=/lab,readonly" \
  codex/adv-c-jammy:20260821 sh -eu -c '
    cmake -S /lab -B /tmp/lab02_cp2_final -DCMAKE_BUILD_TYPE=Debug
    cmake --build /tmp/lab02_cp2_final --parallel
    ctest --test-dir /tmp/lab02_cp2_final --output-on-failure
    /tmp/lab02_cp2_final/s04_generic_case
  ' >"$LAB_P02_ROOT/cp2_container.log" 2>&1
printf 'SOURCE_SHA256=%s\n' "$source_hash" \
  >>"$LAB_P02_ROOT/cp2_container.log"

docker run --rm --network none --read-only \
  --tmpfs /tmp:rw,exec,nosuid,nodev \
  --mount "type=bind,source=$LAB_P02_ROOT/work,target=/lab,readonly" \
  codex/adv-c-jammy:20260821 sh -eu -c '
    cmake -S /lab -B /tmp/lab02_final -DCMAKE_BUILD_TYPE=Debug
    cmake --build /tmp/lab02_final --parallel
    ctest --test-dir /tmp/lab02_final --output-on-failure
    valgrind --tool=memcheck --leak-check=full \
      --show-leak-kinds=definite,indirect \
      --errors-for-leak-kinds=definite,indirect --error-exitcode=99 \
      /tmp/lab02_final/s04_generic_case
  ' >"$LAB_P02_ROOT/lab02_valgrind.log" 2>&1
printf 'SOURCE_SHA256=%s\n' "$source_hash" \
  >>"$LAB_P02_ROOT/lab02_valgrind.log"

expect_once() {
  expected_line=$1
  evidence_file=$2
  test "$(grep -Fxc -- "$expected_line" "$evidence_file")" -eq 1
}

expect_once '100% tests passed, 0 tests failed out of 1' \
  "$LAB_P02_ROOT/lab02_baseline.log"
expect_once 'vector=10,20,30' "$LAB_P02_ROOT/lab02_baseline.log"
expect_once 'list_id_sum=3 flags=0x00000005' \
  "$LAB_P02_ROOT/lab02_baseline.log"
expect_once 'reading_temperature=42 packet=abc' \
  "$LAB_P02_ROOT/lab02_baseline.log"
expect_once 'S04_CASE_PASS' "$LAB_P02_ROOT/lab02_baseline.log"
expect_once "SOURCE_SHA256=$baseline_source_hash" \
  "$LAB_P02_ROOT/lab02_baseline.log"
expect_once "CMAKE_SHA256=$baseline_cmake_hash" \
  "$LAB_P02_ROOT/lab02_baseline.log"

expect_once '100% tests passed, 0 tests failed out of 1' \
  "$LAB_P02_ROOT/cp2_container.log"
expect_once 'LAB02_VECTOR elem_size=1 len=3 first=3 last=4 reserve_preserved=1' \
  "$LAB_P02_ROOT/cp2_container.log"
expect_once 'LAB02_LIST id_sum=3 double_insert_rejected=1' \
  "$LAB_P02_ROOT/cp2_container.log"
expect_once 'S04_CASE_PASS' "$LAB_P02_ROOT/cp2_container.log"
expect_once "SOURCE_SHA256=$source_hash" "$LAB_P02_ROOT/cp2_container.log"

expect_once '100% tests passed, 0 tests failed out of 1' \
  "$LAB_P02_ROOT/lab02_valgrind.log"
expect_once 'vector=10,20,30' "$LAB_P02_ROOT/lab02_valgrind.log"
expect_once 'list_id_sum=3 flags=0x00000005' \
  "$LAB_P02_ROOT/lab02_valgrind.log"
expect_once 'reading_temperature=42 packet=abc' \
  "$LAB_P02_ROOT/lab02_valgrind.log"
expect_once 'LAB02_VECTOR elem_size=1 len=3 first=3 last=4 reserve_preserved=1' \
  "$LAB_P02_ROOT/lab02_valgrind.log"
expect_once 'LAB02_LIST id_sum=3 double_insert_rejected=1' \
  "$LAB_P02_ROOT/lab02_valgrind.log"
expect_once 'LAB02_FLAGS state=0x00000005 reserved_rejected=1' \
  "$LAB_P02_ROOT/lab02_valgrind.log"
expect_once 'LAB02_PACKET len=5 overflow_rejected=1' \
  "$LAB_P02_ROOT/lab02_valgrind.log"
expect_once 'S04_CASE_PASS' "$LAB_P02_ROOT/lab02_valgrind.log"
expect_once "SOURCE_SHA256=$source_hash" "$LAB_P02_ROOT/lab02_valgrind.log"
grep -F 'ERROR SUMMARY: 0 errors' "$LAB_P02_ROOT/lab02_valgrind.log"
grep -F 'in use at exit: 0 bytes in 0 blocks' \
  "$LAB_P02_ROOT/lab02_valgrind.log"

set +e
diff -u "$LAB_P02_ROOT/baseline/s04_case.c" \
  "$LAB_P02_ROOT/work/s04_case.c" >"$LAB_P02_ROOT/lab02_scratch.diff"
diff_status=$?
set -e
test "$diff_status" -eq 1
test -s "$LAB_P02_ROOT/lab02_scratch.diff"

grep -F "$baseline_source_hash" "$LAB_P02_ROOT/lab02_evidence.md"
grep -F "$baseline_cmake_hash" "$LAB_P02_ROOT/lab02_evidence.md"
grep -F "$source_hash" "$LAB_P02_ROOT/lab02_evidence.md"
grep -Ei 'vector' "$LAB_P02_ROOT/lab02_evidence.md" >/dev/null
grep -Ei 'list' "$LAB_P02_ROOT/lab02_evidence.md" >/dev/null
grep -Ei 'flags' "$LAB_P02_ROOT/lab02_evidence.md" >/dev/null
grep -Ei 'FAM|flexible array' "$LAB_P02_ROOT/lab02_evidence.md" >/dev/null
grep -Ei 'cleanup' "$LAB_P02_ROOT/lab02_evidence.md" >/dev/null
```

Final validation chỉ PASS khi toàn bộ block exit `0`: baseline khớp asset bất biến và được clean-build; learner source hiện tại được clean-build/run riêng cho CP2 rồi clean-build/run lại dưới Valgrind cho CP3; mọi oracle xuất hiện đúng một lần trong log tương ứng; Valgrind không có error hoặc leak; scratch diff tồn tại; baseline/CP2/final logs vừa tái tạo có marker hash đúng; evidence chứa cả starter hashes và learner-source hash hiện tại. Không dùng cache, binary hoặc log của source hash khác.

### Deliverables

- Scratch fork `work/s04_case.c` và `lab02_scratch.diff` so với starter baseline.
- `lab02_evidence.md` — container/list/flags/FAM decisions, state snapshots, commands, outputs, exit codes và hashes.
- `lab02_baseline.log`, `cp2_container.log` và `lab02_valgrind.log` — được final gate tái tạo và gắn marker hash của đúng source đã chạy.

### Acceptance criteria

- CP-P02-01..03 đều có Action/Verify/Expected/Evidence và result resolve được.
- Strict C17 CMake build và CTest `1/1` pass; original `S04_CASE_PASS` không regression.
- Vector/list failure-state và membership oracle pass; ownership decision nhất quán với code.
- Flag reserved policy, FAM length/overflow và external-representation boundary có executable evidence.
- Valgrind exit `0`, `ERROR SUMMARY: 0 errors`, không definite/indirect leak.
- Chỉ scratch fork thay đổi; starter, ASM-A04 và upstream artifacts giữ nguyên.

### Definition of Done

Lab hoàn tất khi baseline log trỏ đúng starter hashes, CP2/final logs cùng trỏ learner-source hash hiện tại, scratch diff và evidence resolve các hash đó, toàn bộ acceptance criteria đạt; S05 có thể dùng evidence để package mà không cần suy đoán compile flags, ownership hoặc test oracle.

## ♻️ Reset, cleanup và khả năng chạy lại

- **CMake cache gây nhiễu:** build nằm trong `/tmp/lab02_build` của container mới; không tái dùng host build tree.
- **CTest pass nhưng output thiếu:** chạy executable trực tiếp hoặc đọc Valgrind log; CTest pass có thể ẩn stdout.
- **Implementation-specific layout đổi:** chỉ ghi observation; không biến `sizeof(bit-field)` thành external ABI.
- **Scratch path sai:** in resolved path và chỉ restore/cleanup khi khớp `/tmp/lab-p02-01.*`.

## 7. Provenance và solution policy

- Phạm vi guided Lab: `SRC-USER-LABS` theo nhãn bổ sung ở đầu tài liệu.
- Nguồn kỹ thuật kế thừa S04: `SRC-SYL`, `SRC-C17-ISO`, `SRC-C17-WG14`, `SRC-GNUC`, `SRC-GLIBC235`, `SRC-POSIX17`, `SRC-CERTC`, `SRC-LINUX-LIST`, `SRC-GCC11`, `SRC-LLVM14`, `SRC-VALGRIND318`.
- Authenticity: `inherit` từ project simulated; starter là code nguyên gốc của khóa và fixture synthetic.
- Learner file chỉ cung cấp oracle, checkpoint và gợi ý giảm dần. Không có reference solution; instructor solution nếu được tạo phải lưu riêng và kiểm soát truy cập.

**Pilot requirement:** đối tượng `fresher with C basics`; thời lượng mục tiêu 90 phút, variance cho phép ±20% trước khi cam kết lịch chính thức.

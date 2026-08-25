# Hands-on Lab 01 — Khảo sát memory layout và fixed-block pool an toàn

> **Lab ID:** `LAB-P01-01` · **Thời lượng:** 75 phút · **Mode:** `guided_with_fading` · **Độ khó:** medium
>
> **Provenance phạm vi:** **[BỔ SUNG — nguồn: SRC-USER-LABS]**. Lab dùng project context và nguồn kỹ thuật đã map của S02; dữ liệu và tình huống đều simulated/synthetic.

## 🎯 Learning Outcomes được thực hành

- **LO:** `ADVC-H1SD` — áp dụng contract layout, alignment, ownership và bounded allocator; kiểm chứng bằng executable oracle và Valgrind.
- **Project slice:** M02, nhưng chỉ khảo sát/instrument starter trong scratch; không xây Memory-safe command core v2 hoặc làm thay ASM-A02.
- **Scenario:** reviewer cần một probe tái lập được để phân biệt fact portable với số đo target, đồng thời chứng minh pool exhaustion và invalid-release không phá state.
- **Reused by:** S03 dùng `lab01_evidence.md` để ôn lại ownership, lifetime và failure-atomic contract trước opaque handle.

## 2. Prerequisite, input và ràng buộc

### Prerequisite

- Đã đọc `OUT-S02-01` trong [material.md](material.md) và chạy được ví dụ S02.
- Biết dùng GCC với `-std=c17 -Wall -Wextra -Wpedantic -Werror`.
- Biết phân biệt stdout, stderr và exit code.

### Starter và input

- Starter duy nhất: [assets/pool_demo.c](assets/pool_demo.c).
- Fixture có sẵn: capacity 4, block 64 byte, alignment theo `max_align_t`, reuse/double-free/foreign-pointer và big-endian encoder.
- Output bắt buộc: `lab01_pool_probe.c`, `lab01_evidence.md`, `lab01_valgrind.log`.

### Safety và constraints

- Chỉ sửa bản sao trong `/tmp/lab-p01-01.*`; không sửa starter, Assignment hoặc source project.
- Container chạy `--network none`; không dùng endpoint, credential, dữ liệu thật hoặc package download.
- Không copy implementation từ Assignment. Chỉ thêm probe, assertions và output oracle quanh starter.
- Không hard-code một `sizeof`, offset hoặc địa chỉ như fact portable; số đo target phải được ghi là observed evidence.
- Không chạy Valgrind trên binary ASan.

## 3. Khởi tạo scratch workspace

Chạy từ thư mục S02 chứa file Lab này:

```bash
export LAB_P01_ROOT="$(mktemp -d /tmp/lab-p01-01.XXXXXX)"
cp assets/pool_demo.c "$LAB_P01_ROOT/lab01_pool_probe.c"
cp "$LAB_P01_ROOT/lab01_pool_probe.c" \
  "$LAB_P01_ROOT/lab01_pool_probe.baseline.c"
printf 'scratch=%s\n' "$LAB_P01_ROOT"
```

Giữ nguyên đường dẫn được in ra. Mọi command dưới đây chỉ mount thư mục đó vào `/lab`; build output nằm trong `/tmp` của container và bị xóa khi container kết thúc.

## 📋 Lab outline và Definition of Done

### Checkpoint CP-P01-01 — Khóa baseline có thể tái lập (15 phút, hướng dẫn đầy đủ)

#### Action

Biên dịch bản sao chưa sửa bằng warning profile của khóa và chạy executable trong container network-none:

```bash
docker run --rm --network none \
  --mount "type=bind,source=$LAB_P01_ROOT,target=/lab,readonly" \
  codex/adv-c-jammy:20260821 sh -eu -c '
    gcc -std=c17 -Wall -Wextra -Wpedantic -Werror \
      /lab/lab01_pool_probe.c -o /tmp/lab01_pool_probe
    /tmp/lab01_pool_probe
  '
```

#### Verify

Command phải kết thúc với exit code `0`. Chạy lại với redirect nếu cần tách stream; compiler không được phát warning.

#### Expected result

- Compile stdout/stderr rỗng và exit code `0`.
- Run stdout chính xác `S02 POOL PASS` kèm newline, stderr rỗng và exit code `0`.

#### Evidence

Tạo `lab01_evidence.md` trong scratch và ghi: image tag, exact command, compile/run exit code, stdout, stderr và kết luận baseline. Chỉ ghi PASS khi command trên đã thực chạy.

#### Troubleshooting

Nếu Docker không mount được path, in `pwd` và `printf '%s\n' "$LAB_P01_ROOT"`, rồi xác nhận file `lab01_pool_probe.c` tồn tại. Nếu build có warning, so bản sao với starter; không bỏ `-Werror`.

#### Reset

Khôi phục source scratch về baseline bằng:

```bash
cp "$LAB_P01_ROOT/lab01_pool_probe.baseline.c" \
  "$LAB_P01_ROOT/lab01_pool_probe.c"
```

### Checkpoint CP-P01-02 — Probe layout và chốt pool decision (30 phút, hướng dẫn vừa)

#### Action

Trong `lab01_pool_probe.c`, thêm một dòng report bắt đầu bằng `LAB01_LAYOUT` và các assertions hỗ trợ quyết định sau:

1. Đo `sizeof(command_record)`, `_Alignof(command_record)` và `offsetof(command_record, code)` trên target hiện tại.
2. Xác minh mọi pointer trả về thỏa alignment pool đã công bố bằng quan hệ, không bằng địa chỉ cố định.
3. Ghi trong `lab01_evidence.md` đâu là fact C17 portable, đâu là observation của image Jammy.
4. Giải thích vì sao storage dùng `max_align_t` và vì sao wire encoder không copy raw `command_record`.

Format stdout bắt buộc:

```text
LAB01_LAYOUT size=<decimal> align=<decimal> code_offset=<decimal>
S02 POOL PASS
```

Mức gợi ý đã giảm: tự chọn vị trí probe và assertions; không đổi API hoặc state transition của starter.

#### Verify

```bash
docker run --rm --network none \
  --mount "type=bind,source=$LAB_P01_ROOT,target=/lab,readonly" \
  codex/adv-c-jammy:20260821 sh -eu -c '
    gcc -std=c17 -Wall -Wextra -Wpedantic -Werror \
      /lab/lab01_pool_probe.c -o /tmp/lab01_pool_probe
    /tmp/lab01_pool_probe
  ' >"$LAB_P01_ROOT/cp2_layout.log" 2>&1
grep -Eq '^LAB01_LAYOUT size=[0-9]+ align=[0-9]+ code_offset=[0-9]+$' \
  "$LAB_P01_ROOT/cp2_layout.log"
grep -q '^S02 POOL PASS$' "$LAB_P01_ROOT/cp2_layout.log"
```

#### Expected result

Docker, hai lệnh `grep` và mọi assertion đều exit `0`. Log có đúng hai dòng oracle nêu trên; giá trị decimal có thể phụ thuộc target nhưng quan hệ alignment/offset phải pass.

#### Evidence

Bổ sung `lab01_evidence.md` bằng ba số đo, các quan hệ đã assert, phân loại portable/target-observed và quyết định “encode field-by-field”. Đính kèm exact command và SHA-256 của `lab01_pool_probe.c` bằng `sha256sum`.

#### Troubleshooting

Nếu `offsetof` hoặc `_Alignof` không compile, kiểm include `<stddef.h>` và type được dùng sau complete definition. Nếu grep fail nhưng executable pass, so stdout với format oracle; không sửa grep để chấp nhận output mơ hồ.

#### Reset

Nếu probe làm hỏng baseline, chạy lệnh restore của CP-P01-01 rồi thêm lại từng observation. `cp2_layout.log` và evidence không được dùng để tuyên bố PASS sau khi source đã reset; chạy lại Verify.

### Checkpoint CP-P01-03 — Exhaustion, boundary và Valgrind (30 phút, fading)

#### Action

Tự bổ sung fixture nhỏ trong scratch để tạo một dòng:

```text
LAB01_BOUNDARY exhaustion=1 interior_rejected=1 state_preserved=1
```

Fixture phải chứng minh bằng assertions rằng: cấp đủ bốn slot thành công; lần cấp thứ năm trả `NULL`; pointer nội vùng nhưng không phải block start bị từ chối; một release thất bại không làm thay đổi used/free state quan sát được; slot hợp lệ vẫn reuse đúng contract. Không thêm allocator mới, không đổi capacity và không sao chép test/implementation của ASM-A02.

Mức gợi ý tối thiểu: snapshot state trước operation lỗi, so lại sau operation, rồi chạy Valgrind trên cùng binary debug.

#### Verify

```bash
docker run --rm --network none \
  --mount "type=bind,source=$LAB_P01_ROOT,target=/lab,readonly" \
  codex/adv-c-jammy:20260821 sh -eu -c '
    gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -O0 -g \
      /lab/lab01_pool_probe.c -o /tmp/lab01_pool_probe
    valgrind --tool=memcheck --leak-check=full \
      --errors-for-leak-kinds=definite,indirect --error-exitcode=99 \
      /tmp/lab01_pool_probe
  ' >"$LAB_P01_ROOT/lab01_valgrind.log" 2>&1
grep -q '^LAB01_BOUNDARY exhaustion=1 interior_rejected=1 state_preserved=1$' \
  "$LAB_P01_ROOT/lab01_valgrind.log"
grep -q '^S02 POOL PASS$' "$LAB_P01_ROOT/lab01_valgrind.log"
grep -q 'ERROR SUMMARY: 0 errors' "$LAB_P01_ROOT/lab01_valgrind.log"
```

#### Expected result

Container và ba lệnh `grep` exit `0`; stdout chứa layout, boundary và `S02 POOL PASS`; Valgrind báo `ERROR SUMMARY: 0 errors` và không có definite/indirect leak. Nhánh exhaustion/interior-pointer không crash và không làm đổi state ngoài contract.

#### Evidence

Hoàn tất `lab01_evidence.md` với bảng operation → pre-state → status → post-state cho exhaustion, interior rejection và reuse. Giữ nguyên `lab01_valgrind.log`; evidence phải ghi exact image, command, exit code và source hash khớp CP cuối.

#### Troubleshooting

Nếu Valgrind exit `99`, đọc finding đầu tiên và stack frame thuộc `lab01_pool_probe.c`; sửa lần truy cập sai trước khi chạy lại. Nếu state-preserved fail, kiểm operation lỗi có mutate `used[]` trước membership/state validation hay không; chỉ instrument scratch, không sửa starter gốc.

#### Reset

Để thử lại từ đầu, restore `lab01_pool_probe.baseline.c` như CP-P01-01 và chạy lại cả ba checkpoint. Sau khi đã sao lưu deliverables, cleanup chỉ được phép với guard:

```bash
case "$LAB_P01_ROOT" in
  /tmp/lab-p01-01.*) rm -rf -- "$LAB_P01_ROOT" ;;
  *) printf 'Refuse cleanup outside lab scratch\n' >&2; exit 1 ;;
esac
```

## 🧪 Final validation

**Phương thức:** executable

Chạy từ shell đã giữ biến `LAB_P01_ROOT`. Container mới dùng source mount read-only và build/run trong `/tmp`, vì vậy final gate không tái sử dụng binary hoặc build state của checkpoint trước:

```bash
set -eu
case "${LAB_P01_ROOT:-}" in
  /tmp/lab-p01-01.*) ;;
  *) printf 'Invalid LAB_P01_ROOT\n' >&2; exit 64 ;;
esac

test -s "$LAB_P01_ROOT/lab01_pool_probe.c"
test -s "$LAB_P01_ROOT/lab01_evidence.md"

docker run --rm --network none --read-only \
  --tmpfs /tmp:rw,exec,nosuid,nodev \
  --mount "type=bind,source=$LAB_P01_ROOT,target=/lab,readonly" \
  codex/adv-c-jammy:20260821 sh -eu -c '
    gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -O0 -g \
      /lab/lab01_pool_probe.c -o /tmp/lab01_pool_probe
    /tmp/lab01_pool_probe
    valgrind --tool=memcheck --leak-check=full \
      --show-leak-kinds=definite,indirect \
      --errors-for-leak-kinds=definite,indirect --error-exitcode=99 \
      /tmp/lab01_pool_probe
  ' >"$LAB_P01_ROOT/lab01_valgrind.log" 2>&1

source_hash="$(sha256sum "$LAB_P01_ROOT/lab01_pool_probe.c" | awk '{print $1}')"
printf 'SOURCE_SHA256=%s\n' "$source_hash" \
  >>"$LAB_P01_ROOT/lab01_valgrind.log"

test "$(grep -Ec '^LAB01_LAYOUT size=[0-9]+ align=[0-9]+ code_offset=[0-9]+$' \
  "$LAB_P01_ROOT/lab01_valgrind.log")" -eq 2
test "$(grep -Fxc 'LAB01_BOUNDARY exhaustion=1 interior_rejected=1 state_preserved=1' \
  "$LAB_P01_ROOT/lab01_valgrind.log")" -eq 2
test "$(grep -Fxc 'S02 POOL PASS' \
  "$LAB_P01_ROOT/lab01_valgrind.log")" -eq 2
grep -F 'ERROR SUMMARY: 0 errors' "$LAB_P01_ROOT/lab01_valgrind.log"
grep -F 'in use at exit: 0 bytes in 0 blocks' \
  "$LAB_P01_ROOT/lab01_valgrind.log"
grep -Fx "SOURCE_SHA256=$source_hash" "$LAB_P01_ROOT/lab01_valgrind.log"
grep -F "$source_hash" "$LAB_P01_ROOT/lab01_evidence.md"
grep -F 'encode field-by-field' "$LAB_P01_ROOT/lab01_evidence.md"
grep -Ei 'exhaustion' "$LAB_P01_ROOT/lab01_evidence.md" >/dev/null
grep -Ei 'interior' "$LAB_P01_ROOT/lab01_evidence.md" >/dev/null
grep -Ei 'reuse' "$LAB_P01_ROOT/lab01_evidence.md" >/dev/null
```

Final validation chỉ PASS khi toàn bộ block exit `0`: strict C17 build không warning; một run thường và một run Valgrind cùng tạo đúng hai bản của từng layout/boundary/original oracle; Valgrind không có error hoặc leak; ba deliverable tồn tại; log vừa tạo và evidence cùng chứa SHA-256 của learner source hiện tại; các quyết định CP-P01-01..03 resolve trong evidence. Không dùng log cũ để thay kết quả của command trên.

### Deliverables

- `lab01_pool_probe.c` — scratch probe cuối cùng, không phải source Assignment.
- `lab01_evidence.md` — baseline, layout/pool decisions, state table, commands, exit codes và hashes.
- `lab01_valgrind.log` — log final được tái tạo từ learner source hiện tại, không bị cắt hoặc sửa, có marker `SOURCE_SHA256`.

### Acceptance criteria

- CP-P01-01..03 đều có command, expected result và evidence resolve được.
- Strict C17 build warning-free; layout report không biến số đo target thành portable guarantee.
- Exhaustion/interior-pointer/reuse oracle pass và failed operation giữ state.
- Valgrind exit `0`, `ERROR SUMMARY: 0 errors`, không definite/indirect leak.
- Chỉ có dữ liệu synthetic; starter và ASM-A02 không bị sửa.

### Definition of Done

Lab hoàn tất khi ba deliverable tồn tại trong scratch, source hash trong evidence khớp file nộp, toàn bộ acceptance criteria đạt và evidence đủ để S03 xem lại ownership/failure-state mà không cần đoán command.

## ♻️ Reset, cleanup và khả năng chạy lại

- **Compiler khác baseline:** ghi `gcc --version`; dùng đúng image trước khi diễn giải warning/layout.
- **Output không ổn định:** chỉ in số đo/layout và boolean oracle, không in địa chỉ tuyệt đối.
- **Log Valgrind thiếu summary:** bỏ `--quiet`, giữ redirect cả stdout/stderr và không pipe qua bộ lọc làm mất dòng.
- **Scratch mất kiểm soát:** dừng, in resolved path và chỉ restore/cleanup khi path khớp `/tmp/lab-p01-01.*`.

## 7. Provenance và solution policy

- Phạm vi guided Lab: `SRC-USER-LABS` theo nhãn bổ sung ở đầu tài liệu.
- Nguồn kỹ thuật kế thừa S02: `SRC-SYL`, `SRC-C17-ISO`, `SRC-C17-WG14`, `SRC-GNUC`, `SRC-GLIBC235`, `SRC-LD238`, `SRC-CERTC`, `SRC-LLVM14`, `SRC-VALGRIND318`.
- Authenticity: `inherit` từ project simulated; starter là code nguyên gốc của khóa và fixture synthetic.
- Learner file chỉ cung cấp oracle, checkpoint và gợi ý giảm dần. Không có reference solution; instructor solution nếu được tạo phải lưu riêng và kiểm soát truy cập.

**Pilot requirement:** đối tượng `fresher with C basics`; thời lượng mục tiêu 75 phút, variance cho phép ±20% trước khi cam kết lịch chính thức.

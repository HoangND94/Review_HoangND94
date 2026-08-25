# Unit U04: Release Flow và ổn định MVP — Ví dụ và nghiên cứu tình huống

> **Case:** CASE-U04-01 · **Project:** NovaShop · **Mức xác thực:** simulated · **Phương thức:** artifact review

## 🎯 Learning Outcomes liên quan

- **LO4.1:** vận hành scope freeze, release-only fix, main merge, back merge và branch closure.
- **LO4.2:** tạo annotated tag và release evidence có compatibility/version rationale.

## 🧭 Liên kết với ngữ cảnh nghề nghiệp/dự án

Case mô phỏng một candidate Search–Cart–Checkout–Payment tại **M-GF-04**. Nó khác LAB-U04-01 (Order Tracking + Admin) và ASM-GF-03 (RC-401). Output là một release dossier, traceability matrix và tag/containment audit hoàn chỉnh dùng để quan sát solution pattern, không phải đáp án assessment.

## 🧰 Điều kiện chạy ví dụ

- Repo local cô lập; Git 2.40+; `main`, `develop` tồn tại; tag `v0.1.0` chưa có.
- `develop@D-cut` chứa NS-101, NS-102, NS-103, NS-202 với acceptance evidence PASS.
- Artifact Markdown/CSV synthetic; không deploy, credential, PII hoặc mã nguồn ứng dụng.

```text
git status --short --branch
git branch --list main develop
git tag --list v0.1.0
git log --graph --decorate --oneline --all
```

## 📚 Nguồn đầu vào đã map

- Git Reference Manual 2.54.0; Vincent Driessen Git branching model.
- Semantic Versioning 2.0.0; Scrum Guide 2020.
- NovaShop project brief, backlog và change cards synthetic.

### Mapping case đã chốt trong course plan

| Case | Outline refs | LO | Artifact/oracle |
| --- | --- | --- | --- |
| CASE-U04-01 | OUT-U04-01/02/03 | LO4.1, LO4.2 | frozen scope + UAT/contract/version decision + annotated tag and dual-line containment |

## Case Study 01: Payment wording fix và late Saved Cart Export

### 1. Ticket và tiêu chí thành công

Frozen candidate gồm:

- NS-101 Search / FR-01;
- NS-102 Cart / FR-02;
- NS-103 Checkout / FR-03;
- NS-202 Payment Failure / FR-03.

`UAT-PAY-02` phát hiện message của `DECLINED_RETRYABLE` nói “payment failed permanently”, trái với behavior cho phép retry. Sau scope freeze, sponsor đề nghị thêm **Saved Cart Export**, một capability chưa có PBI Done.

Success contract:

1. wording fix được nhận, Saved Cart Export bị loại khỏi release;
2. UAT chạy lại trên exact release tip và PASS;
3. compatibility/version rationale giới hạn trong sandbox CSV contract;
4. annotated `v0.1.0` trên `main`, tag commit thuộc `develop` sau back merge;
5. release branch chỉ đóng sau audit.

### 2. Input, trạng thái ban đầu và ràng buộc

Compatibility contract đã công bố:

| Contract element | Stability |
| --- | --- |
| Columns `status_id`, `domain`, `customer_meaning`, `input_behavior` | giữ nguyên trong v0.1.0 candidate |
| Published status IDs | không đổi/xóa |
| Descriptive wording | được sửa nếu ID/behavior không đổi |

UAT before-state:

| Finding | Candidate | Expected | Observed | Verdict |
| --- | --- | --- | --- | --- |
| UAT-PAY-02 | release tip R0 | retryable message và input preserved | wording nói permanent; behavior vẫn PRESERVE | REVISE |

Ràng buộc: tag không được tạo khi REVISE; release branch chỉ nhận finding fix/metadata; `develop` có thể tiếp tục cho tương lai; published tag không được di chuyển.

### 3. Phân tích lựa chọn

| Change | Capability impact | Contract impact | Release decision |
| --- | --- | --- | --- |
| Sửa wording `DECLINED_RETRYABLE` | không thêm behavior | ID/columns/PRESERVE giữ nguyên | ACCEPT như release fix |
| Saved Cart Export | capability mới | mở rộng scope/consumer behavior | EXCLUDE, trả Product Backlog |

Version rationale: `0.1.0` là first training MVP theo NovaShop policy. Declared CSV contract cho phép wording correction này; dossier không tuyên bố production maturity hoặc compatibility ngoài contract.

Topology choice: merge release vào `main`, tag exact main tip, rồi merge released `main` vào `develop`. Cách này làm chính tagged main commit trở thành ancestor của future line, đáp ứng oracle trong plan.

### 4. Cách triển khai

Release ledger hoàn chỉnh:

| Ref/change | Scope mapping | Gate evidence | Decision |
| --- | --- | --- | --- |
| D-cut | NS-101/102/103/202 | DoD/acceptance PASS | cut `release/0.1.0` |
| UAT-PAY-02 fix | NS-202/FR-03 | wording diff; ID/behavior unchanged; recheck PASS | include |
| Saved Cart Export | no Done PBI | no acceptance/review evidence | exclude |
| release metadata | dossier/changelog | traceability check PASS | include |

UAT after-state:

| Finding | Tested ref | Expected | Observed | Verdict |
| --- | --- | --- | --- | --- |
| UAT-PAY-02 | exact release tip R1 | retryable wording; input preserved | wording corrected; ID/PRESERVE unchanged | PASS |

Sau overall readiness PASS, maintainer thực hiện:

```text
git switch main
git merge --no-ff release/0.1.0 -m "merge(release): publish NovaShop v0.1.0"
git tag -a v0.1.0 -m "NovaShop v0.1.0; scope frozen; UAT PASS"
git switch develop
git merge --no-ff main -m "chore(release): back-merge v0.1.0 into develop"
```

Release branch được xóa cục bộ chỉ sau khi tag audit và containment matrix đều PASS.

### 5. Output mong đợi

Release readiness:

| Gate | Verdict |
| --- | --- |
| Frozen Done scope | PASS |
| Release-only change | PASS |
| UAT exact candidate | PASS |
| Compatibility/version rationale | PASS |
| Data safety/traceability | PASS |
| Overall | RELEASE PASS |

Containment matrix:

| Object | `main` | `develop` | Expected |
| --- | --- | --- | --- |
| release tip R1 | contained | contained | PASS |
| annotated tag commit `v0.1.0^{commit}` | contained | contained | PASS |
| UAT-PAY-02 fix | present | present | PASS |

Saved Cart Export không có trong released tree/changelog; backlog disposition nêu owner/target release sau.

### 6. Cách xác minh

```text
git tag -n --list v0.1.0
git cat-file -t v0.1.0
git rev-parse v0.1.0^{commit}
git merge-base --is-ancestor v0.1.0 main
git merge-base --is-ancestor v0.1.0 develop
git branch --contains v0.1.0
git branch --list release/0.1.0
git log --graph --decorate --oneline --all
git status --short --branch
```

Expected: annotation hiện; type=`tag`; ancestor checks exit 0; `main` và `develop` contain tagged commit; release branch query trống sau close; status sạch. Reviewer đối chiếu thêm scope manifest, exact tested ref và contract diff; Git topology không tự chứng minh UAT.

### 7. Giải thích sâu và failure modes

- **Tag trước readiness:** dấu hiệu tag target tree chứa dossier REVISE. Nguyên nhân là coi tag như release candidate. Khắc phục trong training là tái chạy ở clone sạch; không move tag đã published. Phòng tránh: tag gate sau overall PASS.
- **Lightweight tag:** tên đúng nhưng `cat-file -t` trả `commit`. Nguyên nhân dùng `git tag v0.1.0`. Khắc phục chỉ trước publication theo policy; evidence thật phải ghi failure. Phòng tránh: `tag -a` + object-type oracle.
- **Main contains, develop does not:** chưa back merge released main. Graph/ancestor check chẩn đoán. Merge main→develop, xử lý conflict theo U03, recheck rồi mới close branch.
- **UAT trên R0, release ở R1:** candidate drift. UAT verdict không áp dụng R1. Re-run UAT và ghi exact ref; không copy verdict cũ.
- **Late feature “nhỏ”:** số file/lines không quyết định release-fix classification. Capability/contract/Done evidence mới là oracle.

### 8. Bài học chuyển giao

- Scope freeze là evidence boundary, không phải lệnh Git.
- Readiness kết hợp business/quality/topology gates; một blocker REVISE giữ overall REVISE.
- Tag annotated phải trỏ exact released commit; tag name không đủ.
- Back merge bảo toàn release fix trong future line.
- Lab đổi sang Order Tracking/Admin; Assignment dùng RC-401 và một late change khác. Không sao chép scope ledger của case.

## Provenance của các case

### Nguồn được dùng

- Git Reference Manual 2.54.0; Vincent Driessen release-flow model.
- Semantic Versioning 2.0.0; Scrum Guide 2020.
- NovaShop synthetic project artifacts.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — từ kiến thức đã huấn luyện]** Saved Cart Export, UAT-PAY-02 và ref labels D-cut/R0/R1 là fixture synthetic.
- **[BỔ SUNG — nguồn: Git Reference Manual 2.54.0]** Tag object type/peeling và ancestry commands được dùng làm topology oracle.

---
<!-- QUALITY GATE: CASE-U04-01 có ticket, input/constraint, complete solution artifact, expected result, verification, trade-off/failure; khác MEX/Lab/Assignment; không code ứng dụng. -->

# Unit U04: Release Flow và ổn định MVP — Assignment 03

> **Mã:** ASM-GF-03 · **Thời lượng:** 120 phút · **Hình thức:** cá nhân · **Độ khó:** medium · **Mức xác thực:** simulated

## 🎯 Learning Outcomes được đánh giá

- **LO4.1 — Apply:** Vận hành release branch qua scope freeze, UAT fix, merge main/develop và đóng branch đúng topology.
- **LO4.2 — Create:** Gắn annotated tag và tạo evidence có version rationale, compatibility contract, traceability tới scope Done.

## 🧠 Khái niệm và best practices được đánh giá

Đây là assessment độc lập trên `RC-401`. Bảng là contract pass/fail, không phải walkthrough.

| Task | Concept / LO | Scenario/input | Best-practice constraint | Deliverable | Oracle / rubric |
| --- | --- | --- | --- | --- | --- |
| TASK-U04-01 | OUT-U04-01 / LO4.1 | Integration pack + conflict log từ ASM-GF-02; frozen candidate có Order Tracking; RC-401 và late Saved Address Auto-fill | Sau freeze chỉ nhận fix cần cho release; feature mới trở lại backlog, vì UAT cần baseline ổn định | Release dossier + scope/change ledger | AT-U04-01 / RB-U04-01 |
| TASK-U04-02 | OUT-U04-02 / LO4.2 | Published CSV column/status IDs; wording glossary inconsistent; version target v0.1.0 | Version/tag rationale dựa declared compatibility contract, vì không contract thì SemVer chỉ là nhãn | Dossier compatibility/version/UAT sections + traceability matrix | AT-U04-02 / RB-U04-02 |
| TASK-U04-03 | OUT-U04-03 / LO4.1 | main/develop shared; tag chỉ sau PASS; release fix phải có trong future line | Release phải merge main/back merge develop rồi kiểm containment, vì nếu thiếu fix có thể tái phát | Tag audit, graph, containment/branch-close evidence | AT-U04-03 / RB-U04-03 |

### TASK-U04-01 — Vận dụng OUT-U04-01

- **Concept refs / LO:** OUT-U04-01 / LO4.1.
- **Decision được đánh giá:** exact cut point, included/excluded scope, release-fix classification và late-change disposition.
- **Input:** Integration evidence pack MVP, Conflict decision log MVP, CARD-U04-ASM/RC-401, LATE-402.
- **Constraint/rationale:** only release fixes after freeze; ổn định candidate và giữ UAT provenance.
- **Deliverables:** Release dossier v0.1.0; Release traceability matrix v0.1.0.
- **Acceptance/rubric:** AT-U04-01 / RB-U04-01.

### TASK-U04-02 — Vận dụng OUT-U04-02

- **Concept refs / LO:** OUT-U04-02 / LO4.2.
- **Decision được đánh giá:** UAT expected/observed/recheck, contract impact, version rationale và giới hạn tuyên bố.
- **Input:** RC-401 states status/column IDs đã công bố; wording mô tả được sửa nếu ID/meaning contract không đổi.
- **Constraint/rationale:** contract phải có consumer-visible boundary; không tuyên bố SemVer/maturity vượt evidence.
- **Deliverables:** dossier UAT/compatibility/version; traceability matrix.
- **Acceptance/rubric:** AT-U04-02 / RB-U04-02.

### TASK-U04-03 — Vận dụng OUT-U04-03

- **Concept refs / LO:** OUT-U04-03 / LO4.1, với LO4.2 được chứng minh qua tag audit.
- **Decision được đánh giá:** main release commit, annotated tag target/message, back-merge route, containment và closure gate.
- **Input:** shared `main`/`develop`, release candidate và readiness verdict do learner tạo.
- **Constraint/rationale:** tag chỉ sau PASS; exact release commit/fix phải xuất hiện ở production/future lines.
- **Deliverables:** tag audit, final graph/containment, branch-close evidence trong hai artifacts chính.
- **Acceptance/rubric:** AT-U04-03 / RB-U04-03.

## 🧭 Bối cảnh nghề nghiệp/dự án và change request

NovaShop sponsor đưa Order Tracking `NS-104` vào target `v0.1.0`. UAT card `RC-401` phát hiện glossary không nhất quán:

- compatibility contract đã công bố column IDs và status IDs cho sandbox consumers;
- text mô tả có thể sửa khi ID và meaning/behavior contract không đổi;
- release decision chỉ PASS khi finding được đóng trên exact candidate;
- tag không được tạo sớm.

Sau scope freeze, sponsor thêm **LATE-402 Saved Address Auto-fill**. Item chưa có acceptance/review/DoD evidence. Học viên phải tạo một release candidate có thể kiểm toán mà không hạ DoD hoặc mở rộng frozen scope.

**Milestone M-GF-04:** phát hành NovaShop v0.1.0 từ Done scope, có UAT và tag để biết chính xác phiên bản được bàn giao.

## 🔗 Liên kết project xuyên suốt

| Trường | Giá trị |
| --- | --- |
| Milestone | M-GF-04 |
| Depends on | ASM-GF-02 |
| Baseline artifacts | Integration evidence pack MVP; Conflict decision log MVP |
| Produces | Release dossier v0.1.0; Release traceability matrix v0.1.0 |
| Reused by | ASM-GF-04 |

ASM-GF-04 dùng exact release tag/dossier/matrix làm production baseline cho hotfix. Vì vậy tag hoặc artifact không truy vết được làm đứt project spine.

## 🧰 Điều kiện thực hiện

### Kiến thức/kỹ năng tiên quyết

- Hoàn thành U03, U04 Material, CASE-U04-01 và LAB-U04-01.
- Có hai deliverables đạt từ ASM-GF-02.
- Đọc/kiểm được Done evidence, Git graph, tag object và containment.

### Môi trường, công cụ và phiên bản

- Clone Git local cô lập; Git 2.40+; Markdown/CSV editor.
- `main`, `develop` tồn tại; `v0.1.0` chưa tồn tại ở baseline.
- Không deploy, remote production, credential, PII, payment thật hoặc mã nguồn ứng dụng.

### Input và starter assets

1. Integration evidence pack MVP và Conflict decision log MVP từ ASM-GF-02.
2. `starter/NovaShop_Backlog.csv`, NS-104 và RC-401.
3. `starter/NovaShop_Change_Cards.md`, CARD-U04-ASM.
4. `starter/templates/GitFlow_Artifact_Templates.md`.
5. Synthetic LATE-402: Saved Address Auto-fill; status `proposed`, không acceptance/review/DoD evidence, requested after freeze.
6. Release fixture chứa exact object IDs/review refs riêng cho mỗi learner clone; dùng IDs thực, không hash mẫu.

## 📋 Yêu cầu

### Functional requirements

- **FR-ASM-U04-01 / LO4.1 / TASK-U04-01:** release bắt đầu từ exact `develop` cut; frozen scope phân biệt included Done work, RC-401 release fix và LATE-402 feature mới.
- **FR-ASM-U04-02 / LO4.2 / TASK-U04-02:** UAT finding có tested ref, expected/observed, fix/recheck; version rationale gắn declared compatibility contract.
- **FR-ASM-U04-03 / LO4.1, LO4.2 / TASK-U04-03:** readiness-PASS candidate được đưa vào `main`, gắn annotated `v0.1.0`, propagate vào `develop`, verify rồi mới đóng release branch.
- **FR-ASM-U04-04 / LO4.2:** matrix truy vết mỗi included PBI/fix tới acceptance evidence, release commit và tag; excluded item có disposition.

### Non-functional requirements

- **NFR-ASM-U04-01 — Integrity:** tag không được tạo/move khi readiness REVISE; `main`/`develop` không rewrite.
- **NFR-ASM-U04-02 — Traceability:** reviewer tái lập scope→UAT→commit→tag→containment từ submission.
- **NFR-ASM-U04-03 — Compatibility honesty:** không tuyên bố SemVer/production maturity ngoài compatibility contract.
- **NFR-ASM-U04-04 — Data safety:** release evidence không credential, PII, internal URL hoặc dữ liệu thật.

### Ràng buộc và phạm vi loại trừ

- Chỉ sửa lỗi phục vụ frozen release; không triển khai LATE-402.
- Tag chỉ sau release decision PASS trên exact candidate.
- Không dùng lightweight tag để đáp policy annotated tag.
- Không dùng branch delete/force option để vượt containment gate.
- Không yêu cầu code/app test/deploy; oracle là artifact review và Git evidence.
- Đề không chỉ định final commit graph, wording fix, version statement hoặc command sequence; học viên tự thiết kế và bảo vệ lựa chọn.

## 📦 Deliverables và cách nộp

### 1. Release dossier v0.1.0

- Frozen scope/cut ref; included/excluded ledger; UAT RC-401; compatibility/version rationale; readiness; changelog/known limitations; tag/back-merge audit; final verdict.
- Tên gợi ý: `project-artifacts/M-GF-04/release-dossier-v0.1.0.md`.
- Đủ khi mọi claim có evidence path/ref và blocker rows đều PASS.

### 2. Release traceability matrix v0.1.0

- PBI/finding → requirement/AC → review/evidence → release commit → tag → `main`/`develop` containment; excluded LATE-402 disposition.
- Tên gợi ý: `project-artifacts/M-GF-04/release-traceability-v0.1.0.md`.
- Đủ khi reviewer không gặp orphan included item, evidence hoặc ref.

### Submission contract

Nộp hai Markdown artifacts, graph/tag/containment outputs đã redact và checklist PASS/REVISE. Không nộp `.git`, credential, PII hoặc đường dẫn cá nhân. Tag hiện hữu không thay thế dossier/matrix.

## ✅ Acceptance criteria và output mong đợi

### AT-U04-01 — OUT-U04-01 / LO4.1 / RB-U04-01

**Given** approved ASM-GF-02 baseline, RC-401 và LATE-402, **when** reviewer kiểm dossier/cut-to-tip evidence, **then** exact cut point resolve; only Done scope và release fix được include; LATE-402 absent khỏi released scope/tree và có backlog disposition; mọi release change map finding/metadata.

### AT-U04-02 — OUT-U04-02 / LO4.2 / RB-U04-02

**Given** declared sandbox column/status-ID contract, **when** reviewer kiểm RC-401 before/after và version rationale, **then** UAT recheck dùng exact candidate; contract impact có evidence; version statement nêu phạm vi/limitation và không overclaim SemVer/maturity; traceability matrix nối NS-104/RC-401 tới tag.

### AT-U04-03 — OUT-U04-03 / LO4.1 / RB-U04-03

**Given** overall readiness PASS, **when** reviewer query refs, **then** `v0.1.0` là annotated tag trên released `main` commit; exact tag commit là ancestor của `main` và `develop`; RC-401 fix có trong future line; release branch chỉ đóng sau gates; working tree sạch.

## 🧪 Cách xác minh

Reviewer chạy trên submission clone/fixture với refs thực:

```text
git status --short --branch
git tag -n --list v0.1.0
git cat-file -t v0.1.0
git rev-parse v0.1.0^{commit}
git merge-base --is-ancestor v0.1.0 main
git merge-base --is-ancestor v0.1.0 develop
git branch --contains v0.1.0
git branch --list release/0.1.0
git log --graph --decorate --oneline --all
```

Artifact oracles:

- included scope count/IDs khớp approved input; LATE-402 absent và disposition present;
- UAT tested ref = final release candidate containing fix;
- compatibility table chứng minh stable IDs/columns/meaning contract;
- tag type exactly `tag`, annotation non-empty; two ancestor checks exit 0;
- matrix orphan links = 0; secret/PII findings = 0.

Kết luận REVISE nếu Git checks PASS nhưng scope/UAT/contract evidence fail.

## 📊 Rubric chấm điểm — tổng 100%

| ID | Tiêu chí | Trọng số | LO / AT | Excellent | Meets | Partial | Not met |
| --- | --- | ---: | --- | --- | --- | --- | --- |
| RB-U04-01 | Đúng topology và quyết định Git Flow | 40% | LO4.1 / AT-U04-01 | Cut/scope/main/back-merge/close tái lập hoàn chỉnh; late-change trade-off rõ | Đúng source/target, freeze/fix boundaries và evidence bắt buộc | Flow cơ bản đúng nhưng thiếu một cut/scope/closure proof | Sai branch source/target, scope creep hoặc không chứng minh topology |
| RB-U04-02 | Traceability PBI/change→UAT→release/tag | 35% | LO4.2 / AT-U04-02 | Không orphan; contract/version limitation chặt; reviewer tái lập full chain | Mỗi included item/fix có AC, UAT/ref, release commit/tag evidence | Chuỗi chính có nhưng thiếu một link/rationale/known limitation | UAT không exact candidate, version overclaim hoặc không truy vết tag |
| RB-U04-03 | An toàn lịch sử, tag/containment và edge case | 25% | LO4.1, LO4.2 / AT-U04-03 | Annotated tag/dual containment/late feature/failure defense đầy đủ | Tag type/target đúng; main/develop contain; no rewrite/secret | Đạt release chính nhưng thiếu một containment/closure/safety evidence | Lightweight/early/moved tag, thiếu back merge, rewrite hoặc data-safety violation |

**Điểm đạt:** 70%. Tổng trọng số = 100%; descriptor dựa evidence quan sát được.

## 📚 Nguồn đầu vào và provenance

### Nguồn đã map

- Git Reference Manual 2.54.0; Vincent Driessen Git branching model.
- Semantic Versioning 2.0.0; Scrum Guide 2020.
- NovaShop Project Brief, Backlog, Change Cards và templates synthetic.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — từ kiến thức đã huấn luyện]** LATE-402 và fixture refs là assessment data synthetic, không phải yêu cầu dự án thật.
- **[BỔ SUNG — nguồn: Git Reference Manual 2.54.0]** Tag object/peeling và ancestry queries là topology oracles; artifact review chứng minh scope/UAT correctness.

---
<!-- QUALITY GATE: 3 concept applications phủ OUT-U04-01..03 và LO4.1/4.2; scenario/input + rule/rationale + deliverable + AT/rubric đủ; independent, không walkthrough/solution; ASM-GF-02 → ASM-GF-03 → ASM-GF-04 resolve; rubric=100%. -->

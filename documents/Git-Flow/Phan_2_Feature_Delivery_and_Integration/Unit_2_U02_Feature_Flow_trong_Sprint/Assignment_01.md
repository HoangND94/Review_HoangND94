# Unit U02: Feature Flow trong Sprint — Assignment 01

> **Assessment ID:** `ASM-GF-01` · **Tên:** Feature dossier: lỗi hiển thị payment sandbox · **Hình thức:** cá nhân · **Thời lượng:** 90 phút · **Độ khó:** medium · **Authenticity:** simulated

Assignment này đánh giá khả năng transfer độc lập. Không dùng NS-101/NS-102 làm output và không sao chép dossier của Material/Lab. Bạn nhận change request mới `NS-202` với failure mode payment sandbox; tài liệu không cung cấp trình tự thực hiện hoặc reference solution.

## 🎯 Learning Outcomes được đánh giá

- **LO2.1 — Apply:** vận hành feature branch từ `develop` về `develop`, duy trì truy vết PBI–commit–review–acceptance evidence.
- **LO2.2 — Evaluate:** đánh giá merge readiness theo DoD, review findings và working state; đưa ra kết luận có evidence.

## 🧠 Khái niệm và best practices được đánh giá

### TASK-U02-01 — PBI/acceptance criteria → feature branch (`OUT-U02-01`, `LO2.1`)

| Thành phần truy vết | Contract đánh giá |
| --- | --- |
| Scenario/input | NS-202 / FR-03; payment sandbox trả failure code synthetic; baseline là repo M-GF-01 trên `develop` |
| Best-practice rule | Tên branch chứa issue ID và branch được tạo từ `develop` |
| Rationale đã học | Issue ID là join key; source đúng tách future work khỏi production-ready `main` |
| Required decision | included/excluded scope, branch type/source/target, branch base và target release |
| Deliverable | Feature evidence pack NS-202: issue/branch decision record + base evidence |
| Acceptance oracle | `AT-U02-01`: reviewer xác định được exact source/base, branch scope và rationale từ artifact/Git evidence |
| Rubric | `RB-U02-01` |

### TASK-U02-02 — Purposeful commits, working state và traceability (`OUT-U02-02`, `LO2.2`)

| Thành phần truy vết | Contract đánh giá |
| --- | --- |
| Scenario/input | Cùng failure code xuất hiện hai lần; checkout input phải được giữ; không dùng payment/PII thật |
| Best-practice rule | Mỗi commit thể hiện một intent kiểm tra được, có NS-202; mỗi criterion map tới artifact/evidence |
| Rationale đã học | Cohesive commits và exact evidence cho phép reviewer cô lập quyết định và tái lập kết luận |
| Required decision | commit boundaries, sync disposition, clean-state evidence và traceability rows |
| Deliverable | Commit plan + actual commit/evidence traceability trong Feature evidence pack |
| Acceptance oracle | `AT-U02-02`: commit range đúng scope; mọi NS-202 criterion có commit/artifact/evidence locator; working state được chứng minh |
| Rubric | `RB-U02-02` |

### TASK-U02-03 — Review/DoD/merge/cleanup (`OUT-U02-03`, `LO2.1`)

| Thành phần truy vết | Contract đánh giá |
| --- | --- |
| Scenario/input | Reviewer phải kiểm failure mapping, input retention và repeated-code behavior; error finding nếu có không được bỏ qua |
| Best-practice rule | Chỉ merge khi review + DoD PASS, error open = 0; containment phải có trước cleanup |
| Rationale đã học | `develop` là integration contract; safe cleanup chỉ đúng khi feature tip reachable từ target |
| Required decision | PASS hoặc REVISE có căn cứ, finding disposition, merge/containment/cleanup state |
| Deliverable | Pull-request review record NS-202 + merge/containment evidence trong dossier |
| Acceptance oracle | `AT-U02-03`: chronology và evidence không mâu thuẫn; PASS chỉ khi đủ gate; source ref được dọn an toàn nếu merge |
| Rubric | `RB-U02-03` |

Mỗi task đo một leaf riêng nhưng dùng chung change request. Không được dùng một dòng “xem branch” để thay mọi acceptance evidence.

## 🧭 Bối cảnh nghề nghiệp/dự án và change request

Customer Support báo payment sandbox có thể trả cùng failure code hai lần. NovaShop cần artifact mô tả cách hiển thị failure sao cho người mua không mất checkout input và một failure response lặp không bị trình bày như hai lỗi nghiệp vụ khác nhau.

**Baseline:** repo NovaShop có `main`, `develop`, working agreement và starter artifacts. Không giả định NS-101/NS-102 dossier là baseline của Assignment; chúng chỉ là trải nghiệm học trước.

**Stakeholders:** Product Owner cần FR-03 traceability; Customer Support cần failure behavior rõ; peer reviewer bảo vệ DoD/integration state.

**Change request NS-202:**

- dùng failure code synthetic, ví dụ `PAYMENT_DECLINED_RETRYABLE`;
- cùng code có thể xuất hiện hai lần trong sandbox trace;
- checkout input synthetic phải được giữ;
- không chứa PAN, CVV, token, endpoint/credential hoặc dữ liệu khách hàng thật;
- feature chỉ được coi merge-ready khi mọi oracle có evidence và error finding bằng 0.

## 🔗 Liên kết project xuyên suốt

| Field | Giá trị theo course plan |
| --- | --- |
| `milestone_id` | `M-GF-02` |
| `depends_on_assignments[]` | rỗng — đây là Assignment đầu tiên |
| `baseline_artifacts[]` | NovaShop project brief; NovaShop backlog baseline; Git Flow artifact templates |
| `produces_artifacts[]` | Feature evidence pack NS-202; Pull request review record NS-202 |
| `reused_by_assignments[]` | `ASM-GF-02` |

Artifact downstream contract: U03/ASM-GF-02 sử dụng feature/review evidence làm baseline khi đánh giá tích hợp và shared-history safety. Vì vậy dossier phải giữ exact issue/commit/evidence locator, không chỉ ảnh chụp.

## 🧰 Điều kiện thực hiện

### Kiến thức/kỹ năng tiên quyết

- Hoàn tất U01, Material/Example/Lab U02.
- Hiểu branch base, purposeful commit, traceability, DoD/review AND-gate, containment và safe cleanup.
- Có khả năng chỉnh Markdown/CSV và lưu output Git đã redact.

### Môi trường, công cụ và phiên bản

- Git CLI 2.40+ trong bản sao local cô lập; profile kiểm chứng của khóa: 2.54.0.windows.1.
- Markdown CommonMark, CSV UTF-8.
- Không remote production, cloud/payment thật hoặc credential; Git identity local dùng `example.invalid`.

### Input và starter assets

- [NovaShop Project Brief](../../starter/NovaShop_Project_Brief.md)
- [NovaShop Backlog](../../starter/NovaShop_Backlog.csv), row NS-202
- [NovaShop Change Cards](../../starter/NovaShop_Change_Cards.md), `CARD-U02-ASM`
- [Git Flow Artifact Templates](../../starter/templates/GitFlow_Artifact_Templates.md)
- Repo baseline M-GF-01 hoặc một bản sao tương đương có `main`/`develop`/working agreement, status sạch.

## 📋 Yêu cầu

### Functional requirements

- **FR-A1:** NS-202 có branch decision/source/base/scope truy vết được tới FR-03.
- **FR-A2:** artifact mô tả mapping failure code synthetic sang thông báo quan sát được.
- **FR-A3:** có evidence cho repeated identical failure input và checkout-input retention.
- **FR-A4:** mọi acceptance criterion map tới purposeful commit, artifact locator và review result.
- **FR-A5:** review record có findings/disposition và merge decision nhất quán với DoD/Git state.
- **FR-A6:** nếu kết luận cuối là PASS/merged, feature tip phải contained trong `develop` và cleanup có safe-delete evidence; nếu kết luận cuối là REVISE, `develop` không được chứa work chưa đạt.

### Non-functional requirements

- **NFR-A1 — Traceability:** không có row mồ côi trong PBI → AC → commit → artifact/evidence → review.
- **NFR-A2 — Integrity:** không direct commit `main`/`develop`, không rewrite/force push shared history.
- **NFR-A3 — Security/data:** synthetic-only; không PAN/CVV/token/credential/endpoint/PII thật.
- **NFR-A4 — Recoverability:** dossier ghi failure/recovery evidence; reset chỉ tác động bản sao Assignment.
- **NFR-A5 — Reviewability:** evidence text ghi command, observation và conclusion; reviewer không phụ thuộc absolute path hoặc `.git` folder nộp kèm.

### Ràng buộc và phạm vi loại trừ

- Feature bắt đầu từ `develop`; branch name chứa `NS-202`.
- Không merge khi finding severity `error` chưa đóng.
- Không dùng nội dung Cart Promotion/expired-code làm payment answer.
- Không viết mã nguồn ứng dụng, không gọi payment API và không cấu hình CI/CD.
- Không được sửa starter assets gốc hoặc nộp `.git`.
- Không bắt buộc một số lượng commit cụ thể; commit boundaries phải có rationale và cohesion.
- Git Flow/commit convention là NovaShop team policy, không được tuyên bố là quy tắc Scrum.

## 📦 Deliverables và cách nộp

### Deliverable 1 — Feature evidence pack NS-202

Một thư mục/zip logic (không chứa `.git`) gồm:

- issue/branch decision record;
- commit plan và actual-commit mapping;
- NS-202 failure-behavior specification/acceptance evidence Markdown hoặc CSV;
- traceability matrix;
- branch-base, status, commit-range, graph và containment/cleanup evidence;
- self-review data-safety checklist.

### Deliverable 2 — Pull-request review record NS-202

Record phải có source/target, issue refs, included/excluded scope, DoD evidence, graph/containment evidence, findings, dispositions, final `PASS` hoặc `REVISE`, reviewer role/date mô phỏng và rationale.

### Cách nộp

Nộp Markdown/CSV và text output Git đã redact. Không nộp `.git`, credential, absolute path cá nhân hoặc ảnh chụp thay cho evidence text. Tên file/thư mục phải cho phép reviewer tìm NS-202 và acceptance-test ID.

## ✅ Acceptance criteria và output mong đợi

### AT-U02-01 — Branch/source/scope (`OUT-U02-01`, `LO2.1`, `RB-U02-01`)

**PASS khi:**

- issue record nêu NS-202/FR-03, outcome, acceptance oracles, included/excluded scope và target release;
- branch name có NS-202; source/target là `develop` → `develop`;
- base evidence có exact command/SHA và graph/merge-base evidence không mâu thuẫn;
- reviewer có thể kết luận branch bắt đầu đúng mà không dựa riêng vào tên.

**REVISE khi:** source/base không chứng minh được, branch từ `main`, scope chứa capability ngoài NS-202 hoặc evidence chỉ là ảnh.

### AT-U02-02 — Commits/traceability/working state (`OUT-U02-02`, `LO2.2`, `RB-U02-02`)

**PASS khi:**

- commit range chỉ chứa NS-202 intents hoặc sync commit có rationale;
- mỗi commit có intent kiểm tra được và issue ID theo policy;
- failure mapping, repeated identical code và input retention đều có commit + artifact locator + evidence + status;
- status evidence chứng minh clean state tại review/merge decision;
- sync/no-sync decision có input và rationale; không rewrite shared history.

**REVISE khi:** commit “update stuff”, mixed issue scope, criterion trỏ chung “xem branch”, dirty state bị bỏ qua hoặc traceability row mồ côi.

### AT-U02-03 — Review/DoD/merge/cleanup (`OUT-U02-03`, `LO2.1`, `RB-U02-03`)

**PASS khi:**

- review record kiểm đủ branch/base, acceptance, DoD, error findings và status;
- finding disposition có exact fix/evidence; error open = 0 trước bất kỳ PASS merge decision;
- final decision khớp observed state: PASS chỉ khi gates đều đạt, REVISE nếu còn ít nhất một gate fail;
- nếu merged, saved feature tip contained trong `develop` và source branch chỉ cleanup sau evidence; nếu REVISE, không có containment giả tạo;
- main không nhận NS-202 direct commit.

**REVISE khi:** chronology đảo, “sẽ sửa sau” được coi closed, dùng `-D`, thiếu containment hoặc merge work chưa Done.

### Output mong đợi tổng thể

Reviewer tái lập được input, decisions, trạng thái Git và conclusion cho cả ba AT từ hai deliverables. Assignment đạt từ 70/100 và không vi phạm blocker về data/history; điểm số không cứu được secret/PII, source branch sai hoặc evidence giả/mâu thuẫn.

## 🧪 Cách xác minh

Các oracle sau là **công cụ chấm**, không phải trình tự giải bài. Học viên chọn thời điểm/cách tạo evidence phù hợp và ghi exact refs/SHA thực tế:

```text
git status --short --branch
git branch --show-current
git log --graph --decorate --oneline --all
git log --oneline --decorate develop..HEAD
git merge-base --is-ancestor develop HEAD
git branch --merged develop
git show-ref --heads --tags
```

Khi source branch đã cleanup, containment được kiểm bằng saved feature-tip SHA thay cho branch name. Reviewer đối chiếu thêm:

| Oracle | Evidence bắt buộc | Mapped AT/rubric |
| --- | --- | --- |
| branch base/name/scope | decision record + base SHA/graph | AT-U02-01 / RB-U02-01 |
| cohesive commit range | command output + commit plan/actual mapping | AT-U02-02 / RB-U02-02 |
| criterion traceability | matrix + artifact locators | AT-U02-02 / RB-U02-02 |
| DoD/error gate | review record + finding disposition + status | AT-U02-03 / RB-U02-03 |
| containment/cleanup | saved tip + exit result/merged list + refs | AT-U02-03 / RB-U02-03 |
| data safety | file scan/manual checklist | AT-U02-03 / RB-U02-03 |

Artifact review kết luận theo evidence quan sát được; không chạy endpoint và không cần application build.

## 📊 Rubric chấm điểm — tổng 100%

### RB-U02-01 — Đúng topology và quyết định Git Flow (40%)

| Mức | Descriptor quan sát được |
| --- | --- |
| Xuất sắc (36–40) | AT-U02-01 PASS; source/base/scope/branch/lifecycle đều có exact evidence; rationale phân biệt tên ref với ancestry và nêu trade-off. |
| Đạt (28–35) | AT-U02-01 PASS; branch/source/target và scope đúng, đủ evidence bắt buộc; rationale còn ngắn nhưng tái lập được. |
| Một phần (16–27) | Quyết định chính đúng nhưng thiếu một base/scope/exit link hoặc evidence chưa đủ context. |
| Không đạt (0–15) | Branch từ ref sai, không chứng minh base, direct commit protected branch hoặc scope không còn là NS-202. |

### RB-U02-02 — Traceability từ PBI tới commit/evidence (35%)

| Mức | Descriptor quan sát được |
| --- | --- |
| Xuất sắc (32–35) | AT-U02-02 PASS; mọi criterion có cohesive commit/artifact/evidence; sync/working-state decision rõ; không link mồ côi. |
| Đạt (25–31) | AT-U02-02 PASS; three required failure behaviors trace đầy đủ; commit range đúng scope và status evidence có thật. |
| Một phần (14–24) | Chuỗi chính có nhưng thiếu một locator/rationale hoặc commit boundary khó review. |
| Không đạt (0–13) | Không truy được NS-202 tới evidence, mixed scope nghiêm trọng, dirty state bị bỏ qua hoặc history bị rewrite trái constraint. |

### RB-U02-03 — Review gate, an toàn lịch sử và edge case (25%)

| Mức | Descriptor quan sát được |
| --- | --- |
| Xuất sắc (23–25) | AT-U02-03 PASS; chronology/finding/DoD/containment hoàn chỉnh; repeated-code edge case rõ; prevention rule và safety evidence thuyết phục. |
| Đạt (18–22) | AT-U02-03 PASS; error gate, final decision, containment/cleanup và data safety nhất quán. |
| Một phần (10–17) | Quyết định cơ bản đúng nhưng thiếu một diagnostic/prevention/cleanup evidence hoặc review locator. |
| Không đạt (0–9) | Merge khi error mở/work chưa Done, dùng destructive cleanup không chứng minh containment, chứa dữ liệu nhạy cảm hoặc review record mâu thuẫn graph. |

**Điểm đạt:** 70/100, đồng thời không có blocker data/history/topology. Tổng trọng số: **40 + 35 + 25 = 100%**.

## 📚 Nguồn đầu vào và provenance

### Nguồn đã map

- [Git Reference Manual 2.54.0](https://git-scm.com/docs/git/2.54.0).
- [Pro Git — Basic Branching and Merging](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging).
- [A successful Git branching model](https://nvie.com/posts/a-successful-git-branching-model/).
- [Conventional Commits 1.0.0](https://www.conventionalcommits.org/en/v1.0.0/).
- [Scrum Guide 2020](https://scrumguides.org/scrum-guide.html).
- NovaShop Project Brief/Backlog/Change Cards/Templates version 1.0, internal approved.

### Phần bổ sung/suy diễn

- **[BỔ SUNG — nguồn: mapped Git/Scrum sources]** Acceptance-test/rubric oracle tổ hợp các khái niệm đã dạy thành assessment contract.
- **[BỔ SUNG — nguồn: CARD-U02-ASM synthetic]** Failure code, repeated response và dossier path là dữ liệu mô phỏng; không phải payment incident thật.

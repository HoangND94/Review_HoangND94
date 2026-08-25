# Unit U05 — Assignment 04: Hotfix dossier cho duplicate payment request

| Thuộc tính | Giá trị |
| --- | --- |
| Mã assessment | ASM-GF-04 |
| Hình thức | Cá nhân, độc lập |
| Thời lượng | 90 phút |
| Độ khó / Bloom | Medium · analyze, evaluate |
| Mức xác thực | Simulated |
| Điểm đạt | 70/100 |

## 🎯 Learning Outcomes được đánh giá

- **LO5.1:** phân loại hotfix so với feature/release fix và vận hành hotfix từ `main` với regression evidence.
- **LO5.2:** chứng minh patch tag trên `main` và hotfix change commit đã tới active release, sau đó tới `develop`, không mất thay đổi.

## 🧠 Khái niệm và best practices được đánh giá

### TASK-U05-01 — OUT-U05-01: Incident triage và branch-type decision

| Contract | Nội dung |
| --- | --- |
| Learning Outcome | LO5.1 |
| Scenario/input | INC-501; production baseline `v0.1.0`; sandbox gửi lại cùng correlation ID synthetic và có thể tạo hai order artifacts; `release/0.2.0` đang UAT |
| Rule | Chỉ dùng hotfix cho lỗi production khẩn và tạo từ `main` |
| Rationale đã học | `main` đại diện production baseline; tách từ đó cô lập fix khỏi scope chưa phát hành |
| Constraint | Decision record phải phân biệt hotfix với feature và release fix; nêu included/excluded scope, stakeholder impact và closing oracle |
| Deliverables | Phần Triage/Scope trong **Hotfix dossier v0.1.1**; liên kết evidence trong **Workflow continuity audit v0.1.1** |
| Acceptance oracle | **AT-U05-01**; reviewer tái lập được baseline, production symptom, urgency, branch source và scope decision |
| Rubric | RB-U05-01, RB-U05-03 |

Positive practice là chỉ đưa payment idempotency artifact/regression vào incident scope. Negative case là tách từ `develop` hoặc gộp capability Admin/Order Tracking của `0.2.0`; khi đó AT-U05-01 REVISE dù regression payment PASS.

### TASK-U05-02 — OUT-U05-02: Regression gate, change identity và patch tag

| Contract | Nội dung |
| --- | --- |
| Learning Outcome | LO5.2 |
| Scenario/input | Hai sandbox events có cùng synthetic correlation ID; expected chỉ một order artifact; release dossier `v0.1.0` và traceability matrix từ ASM-GF-03 |
| Rule | Patch tag chỉ tạo sau regression gate PASS trên trạng thái `main`; capture SHA commit chứa incident correction/regression thành `HOTFIX_CHANGE_COMMIT` trước các merge |
| Rationale đã học | Tag là release identity trên main merge commit; change SHA là identity chung qua các merge target riêng |
| Constraint | Annotated tag theo policy NovaShop; không move tag đã chia sẻ; diff patch không có scope `0.2.0` |
| Deliverables | Phần Regression/Tag evidence trong Hotfix dossier; tag/change identity rows trong continuity audit |
| Acceptance oracle | **AT-U05-02**; business regression có expected/observed, tag type đúng, tag thuộc `main`, SHA change được ghi và tái kiểm được |
| Rubric | RB-U05-02, RB-U05-03 |

Positive practice tách “tag contained in `main`” khỏi “change commit contained in targets”. Negative case dùng `v0.1.1` để đòi containment trong active release/develop; đây là oracle sai khi có separate `--no-ff` merges.

### TASK-U05-03 — OUT-U05-03: Active-release propagation và continuity

| Contract | Nội dung |
| --- | --- |
| Learning Outcome | LO5.1 theo assessment plan; evidence đồng thời hỗ trợ LO5.2 ở cấp Assignment |
| Scenario/input | `release/0.2.0` đang mở và `develop` đã tiến thêm; hotfix change phải không bị mất khi release hoàn tất |
| Rule | Khi release branch mở, hotfix change phải tới active release; đường tới `develop` được audit sau release finish |
| Rationale đã học | Release branch đang ổn định cần fix production; back-merge khi finish truyền change sang dòng tích hợp tương lai |
| Constraint | Không yêu cầu tag-main merge commit nằm trong release/develop; kiểm `HOTFIX_CHANGE_COMMIT`; không merge mù hoặc rewrite shared history |
| Deliverables | Continuity target matrix, containment evidence, postmortem/prevention trong hai deliverables chính |
| Acceptance oracle | **AT-U05-03**; change SHA có trong `main` và `release/0.2.0`, rồi có trong `develop` sau release finish; evidence trước/sau có owner |
| Rubric | RB-U05-01, RB-U05-03 |

## 🧭 Bối cảnh và change request

Bạn là release/incident practitioner của NovaShop. Sau `v0.1.0`, payment sandbox mô phỏng gửi lại một request cùng correlation ID và có thể tạo hai order artifacts. Cùng thời điểm, `release/0.2.0` đang UAT; `develop` đã có thay đổi xa hơn. Stakeholders cần khôi phục hành vi “một logical request không tạo hai order artifacts”, phát hành patch và bảo đảm phiên bản tương lai không tái phát.

Đây là tình huống mới so với Material/Lab: lỗi payment thay vì shipping, active release thay vì chỉ `develop`, và regression oracle dựa trên duplicate request/correlation evidence. Không sao chép dossier HOTFIX-301.

## 🔗 Liên kết project xuyên suốt

| Trường | Giá trị |
| --- | --- |
| milestone_id | M-GF-05 |
| depends_on_assignments | ASM-GF-03 |
| baseline_artifacts | Release dossier v0.1.0; Release traceability matrix v0.1.0 |
| produces_artifacts | Hotfix dossier v0.1.1; Workflow continuity audit v0.1.1 |
| reused_by_assignments | Không có; đây là terminal Assignment |
| terminal consumer | CAP-GF-01 |
| terminal acceptance | AT-U05-01, AT-U05-02, AT-U05-03 |

Capstone sẽ dùng decision/evidence pattern của hai artifact, nên mọi ref, incident ID, change SHA và oracle phải tự đủ nghĩa sau khi hotfix branch bị đóng.

## 🧰 Điều kiện thực hiện và input

- Một **bản sao độc lập** của baseline Assignment, không dùng repository đã hoàn thành Lab.
- `main` và tag `v0.1.0`; active `release/0.2.0`; `develop` có thay đổi tương lai.
- Release dossier/traceability matrix từ ASM-GF-03.
- **CARD-U05-ASM / INC-501** và row backlog tương ứng.
- Template Incident/Hotfix Record, Workflow Audit Finding và Evidence Naming Convention.

Không có secret, endpoint, payment token, PAN/CVV, email hoặc order thật. Correlation ID và order IDs phải là synthetic.

> [!IMPORTANT]
> Đây là assessment độc lập. Đề bài chỉ nêu contract và oracle; không cung cấp chuỗi thao tác, merge walkthrough, nội dung dossier mẫu hoặc reference solution.

## 📋 Yêu cầu

### Functional requirements

- **FR-01 [LO5.1]:** phân loại INC-501 bằng decision record có production baseline, impact, urgency, alternatives, scope included/excluded và branch source.
- **FR-02 [LO5.1, LO5.2]:** tạo regression evidence cho ít nhất success, duplicate-same-correlation và different-correlation cases; mỗi case có input, expected, observed, PASS/REVISE và reviewer role.
- **FR-03 [LO5.2]:** định danh change bằng `HOTFIX_CHANGE_COMMIT`; phát hành annotated `v0.1.1` sau gate PASS trên `main`; chứng minh tag thuộc lịch sử `main`.
- **FR-04 [LO5.2]:** chứng minh change commit tới active `release/0.2.0` và tới `develop` sau release finish; ghi trạng thái/timestamp synthetic của từng continuity gate.
- **FR-05 [LO5.1, LO5.2]:** lập postmortem có root cause hypothesis, detection gap, prevention action, owner và review oracle.

### Non-functional requirements

- **NFR-01 — Traceability:** mọi claim phải trỏ incident, requirement FR-03 của project brief, evidence path/ref và acceptance test tương ứng; không có link mồ côi.
- **NFR-02 — History safety:** không force-push, không rebase shared history, không move tag đã chia sẻ; sai tuyến phải được ghi REVISE/escalate.
- **NFR-03 — Scope integrity:** patch diff chỉ chứa INC-501/payment regression artifacts; không có capability `0.2.0`.
- **NFR-04 — Data safety:** toàn bộ order/correlation data synthetic; log/evidence không có path, email, remote URL hoặc credential thật.

### Ràng buộc và phạm vi loại trừ

- Hotfix bắt đầu từ `main`/production baseline.
- Active release phải nhận **hotfix change commit**; tag `v0.1.1` chỉ bắt buộc thuộc `main`.
- `develop` nhận change qua release finish theo scenario; nếu có propagation sớm bổ sung, phải có decision/risk evidence, không được coi là mặc định.
- Không viết mã nguồn ứng dụng, không gọi payment endpoint, không thiết kế lại checkout và không thêm feature.

## 📦 Deliverables và cách nộp

### D1 — Hotfix dossier v0.1.1

Một Markdown artifact có:

- incident triage/branch decision;
- source/target/scope included-excluded;
- regression matrix và review decision;
- field `HOTFIX_CHANGE_COMMIT` cùng evidence capture;
- patch tag evidence, release note ngắn và postmortem.

Tên nộp: `hotfix-dossier-v0.1.1.md`.

### D2 — Workflow continuity audit v0.1.1

Một Markdown hoặc CSV+Markdown artifact có:

- ref/change containment matrix trước và sau propagation;
- tag-main oracle tách biệt với change-target oracle;
- release-finish/develop evidence;
- traceability INC-501 → requirements → evidence → AT → rubric;
- findings, severity, owner, remediation và PASS/REVISE.

Tên nộp: `workflow-continuity-audit-v0.1.1.md` (CSV phụ được phép nhưng không thay thế kết luận).

### Submission contract

Nộp D1, D2, bản graph đã redact và output validation đã redact. Không nộp `.git`; không nộp Lab dossier; mọi evidence path được liệt kê trong hai deliverables.

## ✅ Acceptance criteria và output mong đợi

### AT-U05-01 — Triage/topology decision [LO5.1]

**Given** baseline `v0.1.0`, active `release/0.2.0` và INC-501; **when** reviewer đọc D1 cùng source evidence; **then** họ xác định được vì sao đây là hotfix, source là `main`, scope patch không chứa `0.2.0`, và kết luận PASS/REVISE không cần hỏi người làm.

Oracle quan sát được:

- production baseline là ancestor của hotfix;
- decision record nêu ít nhất feature/release-fix alternatives và lý do loại;
- patch path review không có capability tương lai.

### AT-U05-02 — Regression, change identity và patch release [LO5.2]

**Given** regression records synthetic; **when** reviewer đối chiếu expected/observed và Git evidence; **then** duplicate same-correlation tạo đúng một logical order artifact, all mandatory cases PASS, `HOTFIX_CHANGE_COMMIT` resolve được, annotated tag `v0.1.1` được tạo sau gate và tag thuộc `main`.

Oracle quan sát được:

```text
git cat-file -t refs/tags/v0.1.1        → tag
git merge-base --is-ancestor v0.1.1 main → exit 0
```

Tag không được dùng làm oracle containment trên release/develop.

### AT-U05-03 — Active-release continuity [LO5.1 theo plan]

**Given** SHA `HOTFIX_CHANGE_COMMIT`; **when** reviewer chạy containment trên các mốc đã ghi; **then** change SHA có trong `main` và `release/0.2.0`, rồi có trong `develop` sau release finish. Nếu một target thiếu, D2 phải kết luận REVISE thay vì che bằng narrative.

Oracle quan sát được:

- `git branch --contains` với SHA thật liệt kê targets theo đúng thời điểm;
- graph/release-finish evidence giải thích đường tới `develop`;
- prevention action có owner và review condition.

## 🧪 Cách xác minh và evidence bắt buộc

Reviewer chạy trong bản sao assessment:

```text
git status --short --branch
git log --graph --decorate --oneline --all
git merge-base --is-ancestor v0.1.0 hotfix/0.1.1-duplicate-payment
git cat-file -t refs/tags/v0.1.1
git merge-base --is-ancestor v0.1.1 main
git branch --contains HOTFIX_CHANGE_COMMIT
git diff --name-only v0.1.0..v0.1.1
```

`HOTFIX_CHANGE_COMMIT` là SHA do học viên ghi trong D1; reviewer dán SHA đó vào lệnh. Evidence tối thiểu:

- AT-U05-01: decision record, branch graph, source/scope oracle;
- AT-U05-02: regression matrix, tag object/main containment, capture record;
- AT-U05-03: containment before/after release finish, failure-path/self-review và owner.

Một lệnh ancestor trả `1`, tag type khác `tag`, missing target, regression REVISE hoặc scope leak đều làm acceptance test liên quan REVISE.

## 📊 Rubric chấm điểm — tổng 100%

| ID | Tiêu chí | Trọng số | LO / AT | Excellent | Meets | Partial | Not met |
| --- | --- | ---: | --- | --- | --- | --- | --- |
| **RB-U05-01** | Triage và topology Git Flow | 40% | LO5.1 · AT-U05-01 | Baseline/impact/alternatives/scope đầy đủ; source-target đúng; graph/oracle tái lập được; giải thích active-release trade-off | Source/target đúng, scope hẹp và evidence bắt buộc PASS | Quyết định chính đúng nhưng thiếu một alternative, scope exclusion hoặc evidence | Sai source/route, trộn `0.2.0`, hoặc không chứng minh được |
| **RB-U05-02** | Regression, tag và traceability | 35% | LO5.2 · AT-U05-02 | Mọi case có input/expected/observed; change SHA/tag-main tách rõ; không link mồ côi | Mandatory regression PASS; annotated tag ở main; change SHA resolve được | Thiếu một edge case/link hoặc giải thích identity chưa rõ nhưng claim chính kiểm được | Tag sớm/sai type/sai line, regression không có oracle, hoặc không có change SHA |
| **RB-U05-03** | Continuity, history/data safety và edge case | 25% | LO5.1, LO5.2 · AT-U05-03 | Change contained đủ theo thời điểm; failure evidence, recovery, postmortem owner/oracle và scope/data safety đều đạt | Active release và post-finish develop chứa change; không rewrite/PII; postmortem đủ | Một evidence/owner/prevention link thiếu nhưng không có topology/safety violation | Fix bị mất, dùng tag thay change SHA để che lỗi, rewrite shared history, hoặc có dữ liệu nhạy cảm |

**Quy tắc chấm:** tổng trọng số 100%; đạt từ 70 điểm và không có violation History/Data Safety. Một descriptor mức cao không bù acceptance test bắt buộc đang REVISE.

## 📚 Nguồn và provenance

- SRC-NVIE — classic hotfix route và active-release exception.
- SRC-GIT-DOC, SRC-PROGIT — ref, tag, graph, ancestor/containment evidence.
- SRC-SEMVER — version meaning và released-content immutability.
- SRC-NS-CARDS — INC-501, synthetic và internal approved.
- [SUY DIỄN — từ Git graph semantics] Contract capture `HOTFIX_CHANGE_COMMIT`, exact evidence matrix và grading oracles được thiết kế cho assessment này.

---
<!-- QUALITY GATE: 3 concept applications map LO→scenario/input→rule/rationale→deliverables→AT/evidence→rubric; Assignment độc lập; project link resolve; tag-main tách change propagation; rubric 100%; không có walkthrough/solution. -->

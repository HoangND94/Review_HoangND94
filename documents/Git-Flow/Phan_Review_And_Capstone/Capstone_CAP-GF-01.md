# Capstone — NovaShop v0.2.0 end-to-end Git Flow và hotfix

> **Khóa học:** Git Flow thực chiến qua dự án NovaShop · **Loại khóa:** Git branching workflow, release governance và Agile/Scrum artifact delivery

| Thuộc tính | Giá trị |
| --- | --- |
| Mã capstone | CAP-GF-01 |
| Thời lượng dự kiến | 240 phút |
| Mức xác thực | simulated |

## 🎯 Learning Outcomes được đánh giá
- **LO1.1** [analyze] — Phân loại đúng vai trò, nguồn, đích và vòng đời của main, develop, feature, release và hotfix trong ít nhất 8/10 tình huống NovaShop. · Bằng chứng: Branch-routing decision table và graph có giải thích.
- **LO1.2** [apply] — Khởi tạo baseline repo tài liệu NovaShop có main, develop, tag mốc và policy kiểm chứng được. · Bằng chứng: Git refs, branch graph và baseline checklist.
- **LO2.1** [apply] — Vận hành feature branch từ develop tới develop cho một PBI NovaShop và duy trì truy vết PBI–commit–review–acceptance evidence. · Bằng chứng: Feature evidence pack và pull-request review record.
- **LO2.2** [evaluate] — Đánh giá một feature đã đủ điều kiện merge theo Definition of Done, review findings và trạng thái working tree. · Bằng chứng: Merge decision có kết luận PASS/REVISE và evidence.
- **LO3.1** [analyze] — Chẩn đoán và giải quyết conflict giữa các feature branch mà không làm mất acceptance criteria đã phê duyệt. · Bằng chứng: Conflict decision log và diff sau resolution.
- **LO3.2** [evaluate] — Lựa chọn merge, no-fast-forward, rebase cục bộ hoặc revert phù hợp với ownership và rủi ro lịch sử. · Bằng chứng: Strategy decision record và branch graph sau tích hợp.
- **LO4.1** [apply] — Vận hành release branch từ develop qua scope freeze, UAT fix, merge main/develop và đóng branch đúng topology. · Bằng chứng: Release dossier, graph và containment evidence.
- **LO4.2** [create] — Gắn annotated tag và lập release evidence có version rationale, compatibility contract và traceability tới scope Done. · Bằng chứng: Tag audit, changelog và release traceability matrix.
- **LO5.1** [analyze] — Phân loại hotfix so với feature hoặc release fix và vận hành hotfix từ main với regression evidence. · Bằng chứng: Incident triage record và hotfix branch evidence.
- **LO5.2** [evaluate] — Chứng minh hotfix đã được gắn patch tag và truyền tới main, develop hoặc release branch đang mở mà không làm mất thay đổi. · Bằng chứng: Containment audit và workflow continuity record.
- **LO6.1** [evaluate] — Audit lịch sử NovaShop để phát hiện ít nhất 5/6 vi phạm branch, review, tag hoặc back-merge và đề xuất remediation có owner. · Bằng chứng: Git Flow audit report và traceability matrix.
- **LO6.2** [create] — Viết ADR đánh giá tiếp tục Git Flow hay chuyển workflow đơn giản hơn dựa trên cadence, số version hỗ trợ, lead time và merge cost. · Bằng chứng: Workflow decision record có trade-off và trigger đánh giá lại.

> Mỗi Learning Outcome trọng tâm phải được map tới requirement, deliverable, acceptance criterion và dòng rubric tương ứng.

## 🧭 Bối cảnh dự án và nhiệm vụ capstone

**Project context:**
**NovaShop** — MVP thương mại điện tử B2C mô phỏng gồm tìm kiếm, giỏ hàng, checkout, thanh toán sandbox, theo dõi đơn và quản trị cơ bản.. Vai trò học viên: Thành viên nhóm sản phẩm chịu trách nhiệm quản lý thay đổi, review, release và hotfix trên repository artifact NovaShop.. Mục tiêu: Thiết lập và vận hành Git Flow có bằng chứng để đưa NovaShop từ backlog qua feature, release và hotfix mà không viết mã nguồn ứng dụng.

**Project increment cuối khóa:**
- **milestone_id:** M-GF-CAP
- **artifacts_added:** - NovaShop v0.2.0 release pack<br>- NovaShop v0.2.1 hotfix pack<br>- Workflow decision ADR
- **baseline:** Outputs ASM-GF-01 through ASM-GF-04 and M-GF-06
- **change_scope:** - Order Tracking/Admin features<br>- Release v0.2.0<br>- Random incident hotfix<br>- Governance decision

**Brief đã được phê duyệt:**
Tái sử dụng chuỗi Assignment để vận hành feature → integration → release v0.2.0 → hotfix v0.2.1 và bảo vệ quyết định workflow sau MVP.

Bạn là **nhóm quản lý thay đổi và release** tiếp quản NovaShop sau `v0.1.1`. Product Owner đã chọn hai lát giá trị cho `v0.2.0`: Order Tracking đã refined và `CAP-601` Bulk Update cho Admin. Release Owner cần một tag/audit trail tái lập được; Customer Support đồng thời chuẩn bị incident response. Sau khi `v0.2.0` được chấp nhận, nhóm nhận `CAP-602`: timeline đơn hàng có thể hiển thị trạng thái đi lùi và phải được xử lý như `v0.2.1` nếu đáp ứng tiêu chí hotfix.

Giá trị nghiệp vụ của bài là chứng minh nhóm có thể cô lập thay đổi, giữ acceptance evidence xuyên các lần merge và biết chính xác phiên bản nào đã bàn giao. Toàn bộ project, history, incident và dữ liệu đều có mức xác thực **simulated**; không có khách hàng, payment, credential hay repository production thật.

## 🧰 Baseline, kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết
- **completed_units:** - U01<br>- U02<br>- U03<br>- U04<br>- U05<br>- U06
- **assets:** - Feature evidence pack NS-202<br>- Integration evidence pack MVP<br>- Release dossier v0.1.0<br>- Hotfix dossier v0.1.1

### Môi trường, stack và phiên bản
- **profile_ref:** ENV-GIT-ARTIFACT
- **description:** Repo Git local cô lập chứa duy nhất artifact Markdown/CSV của NovaShop; không có mã nguồn ứng dụng, dịch vụ cloud hay credential.
- **operating_system:** Windows, macOS hoặc Linux
- **runtimes:** _(Không có / chưa áp dụng)_
- **tools:** - - **name:** Git CLI<br>- **version:** 2.40+; verified on 2.54.0.windows.1<br>- - **name:** Markdown editor<br>- **version:** CommonMark-compatible<br>- - **name:** CSV editor<br>- **version:** UTF-8 compatible
- **services:** _(Không có / chưa áp dụng)_
- **overrides:** _(Không có / chưa áp dụng)_

### Baseline/starter assets

- Starter pack: `starter/NovaShop_Project_Brief.md`, `starter/NovaShop_Backlog.csv`, `starter/NovaShop_Change_Cards.md` và `starter/templates/GitFlow_Artifact_Templates.md`.
- Output `ASM-GF-01`: Feature evidence pack NS-202 và Pull-request review record NS-202.
- Output `ASM-GF-02`: Integration evidence pack MVP và Conflict decision log MVP.
- Output `ASM-GF-03`: Release dossier v0.1.0 và Release traceability matrix v0.1.0.
- Output `ASM-GF-04`: Hotfix dossier v0.1.1 và Workflow continuity audit v0.1.1.
- Increment U06: Git Flow audit report và Workflow decision ADR draft.
- Repository làm việc phải là bản sao local mới, Git 2.40+, dùng identity `example.invalid`; không có remote bắt buộc, account, API hay secret.

## 📋 Phạm vi và yêu cầu

### Functional requirements

| ID | Yêu cầu quan sát được | LO |
| --- | --- | --- |
| CAP-FR-01 | Order Tracking và `CAP-601` đi qua feature/review/integration; mỗi acceptance oracle map tới commit và review evidence. | LO2.1, LO2.2, LO3.1 |
| CAP-FR-02 | `release/0.2.0` chỉ chứa scope Done và release fixes; kết quả được merge vào main/develop, gắn annotated tag `v0.2.0`. | LO4.1, LO4.2 |
| CAP-FR-03 | `CAP-602` được triage bằng impact/urgency/baseline; nếu chọn hotfix thì ref bắt đầu từ main, gắn `v0.2.1` sau regression và truyền về dòng tương lai. | LO5.1, LO5.2 |
| CAP-FR-04 | End-to-end matrix truy vết PBI/change → branch → commit → review → merge → tag → containment evidence. | LO1.1, LO1.2, LO6.1 |
| CAP-FR-05 | ADR cuối đánh giá giữ Git Flow hoặc chuyển flow đơn giản hơn và có decision trigger sau MVP. | LO6.2 |

### Non-functional requirements

| ID | Yêu cầu và ngưỡng | Cách đo |
| --- | --- | --- |
| CAP-NFR-01 | Không có mã nguồn ứng dụng; deliverable nghề nghiệp chỉ là Git history và Markdown/CSV. | File inventory và review scope |
| CAP-NFR-02 | Secret/PII/production remote bằng 0. | Review content, `git remote -v` và secret fingerprint scan |
| CAP-NFR-03 | Shared branch bị rewrite bằng 0; không dùng force push trong evidence. | Reflog/evidence log và peer review |
| CAP-NFR-04 | 100% claim Done/released/propagated có exact ref, output Git hoặc review evidence. | End-to-end traceability matrix |
| CAP-NFR-05 | Reset chỉ tác động bản sao Capstone; starter assets không thay đổi. | Hash/file comparison và reset record |

### Kiến trúc, contract và ràng buộc kỹ thuật

- **Ranh giới:** repository chỉ lưu artifact cho Catalog, Cart, Checkout, Payment sandbox, Order Tracking, Admin, release và incident; không dựng web app hoặc CI/CD.
- **Data contract:** ID trong backlog/change cards là khóa truy vết; status/column ID của sandbox là compatibility contract cho version rationale; chỉ dữ liệu synthetic.
- **Repository contract:** `main` là released history; `develop` là integration line; `feature/*` đi từ/về develop; `release/*` đi từ develop và kết thúc ở main/develop; `hotfix/*` đi từ main và được truyền tới các dòng bắt buộc.
- **Review contract:** finding `error` bằng 0 trước merge/tag; annotated tag chỉ tạo sau release/hotfix gate PASS.
- **Dependency:** chỉ dùng starter pack và output Assignment đã liệt kê. Conventional Commit type được phép nhưng là team convention, không phải yêu cầu của Git Flow hay Scrum.
- **Quyền tự chọn:** nhóm chọn merge commit/no-fast-forward cho feature và lựa chọn workflow trong ADR; phải giải trình ảnh hưởng tới auditability, lead time và merge cost. Không được rebase shared branch để làm graph đẹp.

### Ngoài phạm vi

- Viết hoặc chạy mã nguồn NovaShop, build/deploy, cloud, container và production CI/CD.
- Git hosting cụ thể, branch-protection API, tài khoản GitHub/GitLab hoặc pull request thật trên internet.
- Payment thật, PAN/CVV/token, dữ liệu khách hàng và remote nội bộ.
- Chứng minh SemVer cho toàn bộ sản phẩm nếu nhóm không công bố compatibility contract; khi đó version chỉ là team release convention.
- Branch môi trường `qc`, `staging`, `pre-prod` và release orchestration ngoài topology đã học.

## 🗓️ Milestones và project increments
- M-GF-01
- M-GF-02
- M-GF-03
- M-GF-04
- M-GF-05
- M-GF-06

| Checkpoint | Dependency được tái sử dụng | Increment và review oracle |
| --- | --- | --- |
| CAP-CP-01 — Baseline | M-GF-01 và output ASM-GF-01 | Routing/working agreement được áp dụng; refs baseline truy vấn được |
| CAP-CP-02 — Feature + integration | M-GF-02, M-GF-03 và output ASM-GF-02 | CAP-FR-01 đạt; conflict/merge decision có evidence; review error bằng 0 |
| CAP-CP-03 — Release `v0.2.0` | M-GF-04 và output ASM-GF-03 | CAP-FR-02 đạt; annotated tag ở main; release commit/fix contained trong develop |
| CAP-CP-04 — Incident/hotfix `v0.2.1` | M-GF-05 và output ASM-GF-04 | CAP-FR-03 đạt; incident triage, regression, tag và propagation resolve |
| CAP-CP-05 — Audit + ADR + demo | M-GF-06 và toàn bộ checkpoint trước | CAP-FR-04/05 đạt; peer reviewer tái lập kết luận và chấm rubric |

## 📦 Deliverables
- Repository evidence pack
- Release dossier v0.2.0
- Hotfix dossier v0.2.1
- End-to-end traceability matrix
- Workflow decision ADR
- Demo and defense record

| Deliverable | Requirement/LO chính | Evidence tối thiểu |
| --- | --- | --- |
| Repository evidence pack | CAP-FR-01–04; LO1–LO5 | status, graph, refs, containment và artifact diff đã rà dữ liệu |
| Release dossier v0.2.0 | CAP-FR-02; LO4.1–4.2 | scope/UAT decision, changelog, annotated tag và back-merge evidence |
| Hotfix dossier v0.2.1 | CAP-FR-03; LO5.1–5.2 | triage, regression, patch tag, containment và prevention |
| End-to-end traceability matrix | CAP-FR-04; LO1.1, LO2.1, LO4.2, LO5.2, LO6.1 | không có PBI/change/ref/oracle mồ côi |
| Workflow decision ADR | CAP-FR-05; LO6.2 | alternatives, measured drivers, consequences và review trigger |
| Demo and defense record | toàn bộ LO | reviewer score sheet, câu hỏi và exact evidence ref |

## ✅ Acceptance criteria và Definition of Done
- Feature/release/hotfix topology matches policy
- Every PBI/change maps to commit/review/tag evidence
- Release tags belong to `main`; captured hotfix change commits are contained in the required future branches
- All upstream Assignment artifacts are consumed
- ADR evaluates Git Flow fit without treating it as Scrum rule
- Definition of Done passes

Definition of Done của Capstone:

1. CAP-FR-01–05 và CAP-NFR-01–05 đều có kết luận PASS kèm evidence; một mục REVISE làm toàn bài chưa Done.
2. Working tree sạch; `main`, `develop`, `v0.2.0`, `v0.2.1` và các merge point hiện trong graph/refs evidence.
3. `v0.2.0` và `v0.2.1` là annotated tags; tag trỏ commit thuộc main; thay đổi release/hotfix nằm trong dòng phát triển bắt buộc.
4. Mọi review finding severity `error` đã đóng; warning có owner và decision.
5. Upstream artifacts ASM-GF-01–04 xuất hiện như baseline hoặc evidence trong deliverable downstream, không chỉ được nhắc tên.
6. Không có secret, PII, remote production, mã nguồn ứng dụng hoặc claim Scrum/SemVer vượt evidence.
7. Reviewer độc lập có thể tái lập routing, release, hotfix và ADR conclusion trong demo 12 phút.

## 🧪 Chiến lược xác minh
**Phương thức:** demo

- `git status --short --branch`
- `git log --graph --decorate --oneline --all`
- `git show-ref --heads --tags`
- `git branch --contains <captured-hotfix-change-commit>`

**Bằng chứng phải nộp:**
- Redacted Git outputs
- Artifact diffs
- Traceability matrix
- Reviewer score sheet
- ADR peer review

| Validation | Expected result | Requirement / LO | Evidence |
| --- | --- | --- | --- |
| `git status --short --branch` | Working tree sạch ở ref được công bố | CAP-NFR-04; LO1.2 | `status-final.txt` |
| `git log --graph --decorate --oneline --all` | Feature, release và hotfix topology giải thích được; không có scope bị kéo sai tuyến | CAP-FR-01–03; LO2.1, LO3.2, LO4.1, LO5.1 | `graph-final.txt` |
| `git show-ref --heads --tags` và tag inspection | `v0.2.0`, `v0.2.1` tồn tại dưới dạng annotated tag và ref đúng | CAP-FR-02/03; LO4.2, LO5.2 | `refs.txt`, `tag-audit.md` |
| `git branch --contains <captured-hotfix-change-commit>` | `main` và dòng tương lai bắt buộc chứa change commit; tag merge commit trên `main` không bắt buộc là ancestor của `develop` | CAP-FR-03; LO5.2 | `containment-hotfix-change.txt` |
| Traceability review | 100% PBI/change trong scope map tới branch/commit/review/tag/oracle áp dụng | CAP-FR-04; LO6.1 | matrix và reviewer check |
| No-data-risk review | 0 secret/PII/production remote; starter hash không đổi | CAP-NFR-02/05 | scan summary và checksum comparison |
| ADR peer review/demo | Decision dùng drivers, alternatives, consequences và trigger; không gọi Git Flow là Scrum rule | CAP-FR-05; LO6.2 | ADR và defense record |

## 📊 Rubric — tổng 100%
| ID | Tiêu chí | Trọng số | Learning Outcomes | Bằng chứng | Mức hiệu suất |
|---|---|---:|---|---|---|
| CAP-GF-RB-01 | Feature và integration flow | 25% | LO1.1, LO1.2, LO2.1, LO2.2, LO3.1, LO3.2 | Graph, feature/integration evidence and conflict log | **excellent:** Topology và traceability hoàn chỉnh, conflict decision có trade-off<br>**meets:** Luồng đúng và evidence đủ<br>**partial:** Có một ref/link thiếu nhưng không phá release<br>**not_met:** Sai source/target hoặc mất acceptance criteria |
| CAP-GF-RB-02 | Release v0.2.0 | 25% | LO4.1, LO4.2 | Release dossier, annotated tag and containment | **excellent:** Scope/version/tag/back-merge đều tái lập được<br>**meets:** Release topology và evidence đạt<br>**partial:** Thiếu một evidence không làm sai ref<br>**not_met:** Tag/ref sai hoặc thiếu back merge |
| CAP-GF-RB-03 | Hotfix v0.2.1 và continuity | 20% | LO5.1, LO5.2 | Incident, regression, tag and propagation audit | **excellent:** Triage, isolation và propagation đầy đủ<br>**meets:** Hotfix đúng topology và contained<br>**partial:** Fix đúng nhưng thiếu postmortem/evidence<br>**not_met:** Hotfix từ sai baseline hoặc không truyền về dòng cần thiết |
| CAP-GF-RB-04 | Governance, audit và ADR | 20% | LO6.1, LO6.2 | Audit report, remediation backlog and ADR | **excellent:** Audit chính xác và ADR dựa trên metrics/trade-off<br>**meets:** Phát hiện lỗi và có quyết định có lý do<br>**partial:** Decision hợp lý nhưng thiếu trigger/evidence<br>**not_met:** Đồng nhất Git Flow với Scrum hoặc không đánh giá alternatives |
| CAP-GF-RB-05 | Demo, an toàn và truy vết tổng thể | 10% | LO2.2, LO3.2, LO4.2, LO5.2, LO6.2 | Defense record, no-secret check and end-to-end matrix | **excellent:** Reviewer tái lập toàn bộ và learner bảo vệ bằng evidence<br>**meets:** Demo đủ, an toàn và traceability resolve<br>**partial:** Một câu trả lời thiếu evidence<br>**not_met:** Không tái lập được hoặc có dữ liệu bị cấm |

**Điểm đạt:** 70%

> **Quality gate:** Tổng trọng số phải đúng **100%**. Từng tiêu chí nêu bằng chứng quan sát được, ngưỡng đạt và mapping tới Learning Outcome/requirement; không dùng tiêu chí chung chung.

## 📚 Nguồn đầu vào và provenance

### Nguồn đã map
- SRC-GIT-DOC — Git Reference Manual: https://git-scm.com/docs/git/2.54.0 (publisher: Git Project / Software Freedom Conservancy; version: 2.54.0; accessed_at: 2026-08-25; license: GPL-2.0-only; reference use with independent explanation; allowed_use: reference)
- SRC-NVIE — A successful Git branching model: https://nvie.com/posts/a-successful-git-branching-model/ (publisher: Vincent Driessen / nvie; version: 2010-01-05; reflection 2020-03-05; accessed_at: 2026-08-25; license: Page text reference-only; separately licensed diagram is not redistributed; allowed_use: reference)
- SRC-SEMVER — Semantic Versioning 2.0.0: https://semver.org/ (publisher: Tom Preston-Werner and contributors; version: 2.0.0; accessed_at: 2026-08-25; license: CC BY 3.0; allowed_use: reference)
- SRC-SCRUM — The Scrum Guide: https://scrumguides.org/scrum-guide.html (publisher: Ken Schwaber, Jeff Sutherland / ScrumGuides.org; version: November 2020; accessed_at: 2026-08-25; license: CC BY-SA 4.0; allowed_use: adapt)
- SRC-NS-BRIEF — NovaShop simulated e-commerce project brief: starter/NovaShop_Project_Brief.md (publisher: Training artifact approved by user; version: 1.0; accessed_at: 2026-08-25; license: Internal approved for learner use; allowed_use: internal_approved)
- SRC-NS-CARDS — NovaShop Git Flow change cards: starter/NovaShop_Change_Cards.md (publisher: Training artifact created for this course; version: 1.0; accessed_at: 2026-08-25; license: Internal approved for learner use; allowed_use: internal_approved)

### Phần bổ sung/suy diễn
- `[BỔ SUNG — nguồn: Git Reference Manual 2.54.0]` Graph, ref, annotated-tag và ancestry/containment output là oracle kỹ thuật; tên branch một mình không chứng minh nguồn hoặc đích merge.
- `[BỔ SUNG — nguồn: A successful Git branching model, reflection 2020]` ADR bắt buộc đánh giá workflow đơn giản hơn vì Git Flow không phải giải pháp mặc định cho continuous delivery.
- `[BỔ SUNG — nguồn: The Scrum Guide, November 2020]` Sprint Review không được biến thành release gate và Git branch/PR/tag không thay Product Backlog, Increment hay Definition of Done.
- `[SUY DIỄN — từ project spine NovaShop]` CAP-601, CAP-602, lịch sử Git và số liệu dùng trong ADR là synthetic; không phải metric hay incident của doanh nghiệp thật.

---
<!-- QUALITY GATE: dựa trên project spine; chỉ đánh giá kiến thức đã học; FR/NFR đo được; milestones tạo artifact; validation tái lập được; rubric = 100%; mọi trường đã hoàn thiện. -->

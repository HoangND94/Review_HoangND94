# Unit U03: Tích hợp song song, conflict và lịch sử an toàn — Assignment 02

> **Mã:** ASM-GF-02 · **Thời lượng:** 120 phút · **Hình thức:** cá nhân · **Độ khó:** medium · **Mức xác thực:** simulated

## 🎯 Learning Outcomes được đánh giá

- **LO3.1 — Analyze:** Chẩn đoán và giải quyết conflict giữa các feature branch mà không làm mất acceptance criteria đã phê duyệt.
- **LO3.2 — Evaluate:** Lựa chọn merge, no-fast-forward, rebase cục bộ hoặc revert phù hợp với ownership và rủi ro lịch sử.

## 🧠 Khái niệm và best practices được đánh giá

Assignment dùng change request mới `NS-303`; không lặp message registry của Example hoặc payment-status matrix của Lab. Bảng dưới là contract đánh giá, không phải trình tự giải.

| Task | Concept / LO | Scenario và input | Best-practice constraint | Deliverable | Acceptance oracle / rubric |
| --- | --- | --- | --- | --- | --- |
| TASK-U03-01 | OUT-U03-01 / LO3.1 | Hai feature từ cùng baseline chạm cùng `changed_by`; có overlap map và review tips trong input pack | Lập integration order theo dependency và vùng artifact chồng lấn, vì thứ tự phải cô lập nguyên nhân và giảm conflict risk | Integration evidence pack MVP | AT-U03-01 / RB-U03-01 |
| TASK-U03-02 | OUT-U03-02 / LO3.2 | Checkout và Admin đưa hai nghĩa không tương thích cho cùng field; FR-03 và FR-05 đều bắt buộc | Resolution dựa trên acceptance criteria và stakeholder decision, không chỉ marker, vì Git không biết nghĩa nghiệp vụ | Conflict decision log MVP + resolved schema evidence | AT-U03-02 / RB-U03-02 |
| TASK-U03-03 | OUT-U03-03 / LO3.1 | Admin branch đã được peer fetch; exact reviewed tip có trong review record | Chỉ rebase commit local chưa chia sẻ; dùng merge/revert cho shared history, vì rewrite làm hỏng baseline review | Strategy/topology section trong Integration evidence pack | AT-U03-03 / RB-U03-03 |

### TASK-U03-01 — Vận dụng OUT-U03-01 trong change request NovaShop

- **Concept refs:** OUT-U03-01.
- **Learning Outcome:** LO3.1.
- **Input/baseline:** Feature evidence pack NS-202, Pull-request Review Record NS-202, CARD-U03-ASM và hai proposed audit-contract excerpts bên dưới.
- **Decision được đánh giá:** dependency/overlap/risk map, integration order và decision owner; không chấm theo một order duy nhất nếu evidence chứng minh lựa chọn khác vẫn giữ oracles.
- **Constraint:** integration order phải dựa trên dependency và vùng chồng lấn; không dựa riêng vào thời điểm branch hoàn thành.
- **Deliverables:** Integration evidence pack MVP; Conflict decision log MVP.
- **Acceptance-test refs:** AT-U03-01.
- **Rubric refs:** RB-U03-01.

### TASK-U03-02 — Vận dụng OUT-U03-02 trong change request NovaShop

- **Concept refs:** OUT-U03-02.
- **Learning Outcome:** LO3.2.
- **Input/baseline:** hai proposal cùng field, requirement contracts FR-03/FR-05, conflict state và stakeholder roles.
- **Decision được đánh giá:** phân biệt text/semantic conflict; options considered; chosen canonical contract; rationale/owner; before/after diff; structural và business oracle.
- **Constraint:** marker bằng 0 không đủ PASS; canonical result phải giữ acceptance behavior của Checkout lẫn Admin.
- **Deliverables:** Conflict decision log MVP và phần semantic-oracle evidence.
- **Acceptance-test refs:** AT-U03-02.
- **Rubric refs:** RB-U03-02.

### TASK-U03-03 — Vận dụng OUT-U03-03 trong change request NovaShop

- **Concept refs:** OUT-U03-03.
- **Learning Outcome:** LO3.1; strategy defense đồng thời là evidence hỗ trợ LO3.2 toàn bài.
- **Input/baseline:** reviewed tip của Admin branch đã được peer khác fetch; `develop` là shared integration branch.
- **Decision được đánh giá:** merge/no-ff/squash/rebase/revert options và tác động tới feature-tip containment, review links, rollback và shared ownership.
- **Constraint:** không rebase/force-push branch shared; mọi tuyên bố containment phải có command output.
- **Deliverables:** strategy decision, branch graph và containment evidence trong Integration evidence pack MVP.
- **Acceptance-test refs:** AT-U03-03.
- **Rubric refs:** RB-U03-03.

## 🧭 Bối cảnh nghề nghiệp/dự án và change request

NovaShop chuẩn bị release MVP. Upstream **ASM-GF-01** đã tạo Feature evidence pack và Pull-request Review Record cho `NS-202 Payment Failure`. Thay đổi mới `NS-303` chuẩn hóa audit field dùng chung cho Checkout và Admin:

- **Checkout proposal:** `changed_by` là synthetic actor reference gây ra checkout-state transition; bắt buộc khi trạng thái checkout thay đổi; phải nối được tới FR-03 evidence.
- **Admin proposal:** `changed_by` là role category của tác nhân quản trị (`ADMIN` hoặc `SYSTEM`); bắt buộc khi stock/order state thay đổi; phải nối được tới owner/audit evidence của FR-05.

Hai proposal được tạo từ cùng baseline và chạm cùng row trong schema artifact. Một branch đã được peer fetch. Release Owner cần một canonical definition duy nhất, nhưng Product Owner không cho phép bỏ acceptance contract của FR-03 hoặc FR-05.

**User story M-GF-03:** Là nhóm delivery, chúng tôi muốn tích hợp Cart, Checkout và Payment sandbox mà không làm mất quyết định đã phê duyệt.

**Business value:** giảm lỗi tích hợp và tạo baseline đáng tin cậy cho release dossier ở U04.

**Change scope:** parallel feature integration, conflict resolution và history strategy trên artifact Markdown/CSV. Không có mã nguồn ứng dụng.

## 🔗 Liên kết project xuyên suốt

| Trường | Giá trị |
| --- | --- |
| Milestone | M-GF-03 |
| Depends on | ASM-GF-01 |
| Baseline artifacts | Feature evidence pack NS-202; Pull-request Review Record NS-202 |
| Produces | Integration evidence pack MVP; Conflict decision log MVP |
| Reused by | ASM-GF-03 |

Hai output của bài này là input bắt buộc cho ASM-GF-03. Reviewer phải nhìn thấy chúng tiêu thụ exact upstream PBI/review refs, không phải hai báo cáo rời chỉ trùng tên NovaShop.

## 🧰 Điều kiện thực hiện

### Kiến thức/kỹ năng tiên quyết

- Hoàn thành Material, CASE-U03-01 và LAB-U03-01.
- Có output ASM-GF-01 hoặc fixture tương đương do giảng viên cấp.
- Có thể đọc graph, merge base, diff conflict, acceptance criteria và review record.

### Môi trường, công cụ và phiên bản

- Repo Git local cô lập chứa artifact Markdown/CSV NovaShop; Git 2.40+.
- `main` và `develop` theo working agreement; không direct commit vào branch shared.
- Không credential, remote production, PII, dữ liệu thanh toán thật hoặc mã nguồn ứng dụng.

### Input và starter assets

1. `Feature evidence pack NS-202` từ ASM-GF-01.
2. `Pull-request Review Record NS-202` từ ASM-GF-01.
3. `starter/NovaShop_Change_Cards.md`, CARD-U03-ASM.
4. `starter/NovaShop_Backlog.csv`, row NS-303.
5. `starter/templates/GitFlow_Artifact_Templates.md`, Conflict Decision Record và evidence naming convention.
6. Fixture có hai branch đề xuất:
   - `feature/NS-303-checkout-audit` — Checkout proposal;
   - `feature/NS-303-admin-audit` — Admin proposal, đã peer fetch và review record giữ exact tip.

Nếu giảng viên cung cấp object IDs khác giữa các bản sao, học viên dùng IDs thực trong evidence; không thay bằng hash mẫu hoặc mô tả tự khai.

## 📋 Yêu cầu

### Functional requirements

- **FR-ASM-U03-01 / LO3.1 / TASK-U03-01:** integration plan xác định baseline, dependency, overlap, risk, owner và order; graph cuối có đúng source→target policy.
- **FR-ASM-U03-02 / LO3.1 / TASK-U03-02:** schema sau tích hợp có đúng một canonical definition cho `changed_by` và vẫn đáp ứng FR-03 cùng FR-05.
- **FR-ASM-U03-03 / LO3.2 / TASK-U03-03:** history strategy giữ reviewed shared tip kiểm toán được; rollback option được đánh giá mà không rewrite `develop`.
- **FR-ASM-U03-04 / LO3.1, LO3.2:** mỗi quyết định liên kết PBI/AC, before/after evidence và reviewer verdict PASS/REVISE.

### Non-functional requirements

- **NFR-ASM-U03-01 — Integrity:** không force-push hoặc rebase `develop`, `main` hay Admin branch đã peer fetch.
- **NFR-ASM-U03-02 — Traceability:** reviewer từ deliverable phải mở được chuỗi NS-202/NS-303 → FR-03/FR-05 → branch tip → conflict decision → merge/containment oracle.
- **NFR-ASM-U03-03 — Recoverability:** decision log nêu recovery phù hợp cho merge dở và published merge; không dùng destructive broad reset.
- **NFR-ASM-U03-04 — Data safety:** evidence không chứa email thật, URL nội bộ, credential, PII hoặc dữ liệu khách hàng.

### Ràng buộc và phạm vi loại trừ

- Không chọn một phía chỉ để hết conflict.
- Không cung cấp/đòi hỏi mã nguồn ứng dụng, build, CI/CD hay production access.
- Không thay đổi requirement refs FR-03/FR-05 để làm resolution dễ hơn.
- Không được sửa upstream evidence để che khác biệt object ID hoặc review finding.
- Không có walkthrough/reference solution; học viên tự quyết định canonical definition, integration order và history strategy.

## 📦 Deliverables và cách nộp

### 1. Integration evidence pack MVP

- **Định dạng:** một thư mục evidence đã loại dữ liệu nhạy cảm và một index Markdown.
- **Tên gợi ý:** `project-artifacts/M-GF-03/integration-evidence-pack.md`.
- **Bắt buộc:** baseline/tips; conflict map; source→target; graph trước/sau; containment output; strategy decision; traceability to upstream ASM-GF-01; self-review verdict.
- **Được xem là đủ:** mọi evidence path trong index mở được và reviewer tái chạy được oracle trong clone chấm.

### 2. Conflict decision log MVP

- **Định dạng:** Markdown theo Conflict Decision Record template kèm resolved artifact diff.
- **Tên gợi ý:** `decisions/NS-303-conflict-decision.md`.
- **Bắt buộc:** branches/merge base, artifact, AC at risk, options, chosen canonical contract, rationale/owner, before/after evidence, structural/business oracle và prevention rule.
- **Được xem là đủ:** reviewer xác định được vì sao cả FR-03 và FR-05 còn nguyên mà không cần hỏi người làm.

### Submission contract

Nộp hai deliverables, output lệnh đã redact và ảnh hoặc bản văn của graph nếu nền tảng yêu cầu. Không nộp `.git`, credential, đường dẫn cá nhân hoặc dữ liệu thật. Commit/tag không thay thế nội dung evidence pack.

## ✅ Acceptance criteria và output mong đợi

### AT-U03-01 — OUT-U03-01 / LO3.1 / RB-U03-01

**Given** upstream evidence ASM-GF-01 và hai NS-303 branches từ một baseline, **when** reviewer đọc Integration evidence pack, **then** reviewer xác định được merge base, overlap, AC risk, owner và integration-order rationale; graph cuối có source/target đúng; mọi ref nêu trong plan resolve được.

**Evidence oracle:** conflict map + `git merge-base`/`git log --graph` output + decision verdict. Kết luận **REVISE** nếu order chỉ dựa vào “branch hoàn thành trước” hoặc thiếu risk/owner.

### AT-U03-02 — OUT-U03-02 / LO3.2 / RB-U03-02

**Given** hai proposed meanings của `changed_by`, **when** reviewer kiểm resolved artifact và Conflict decision log, **then** marker bằng 0, canonical definition xuất hiện đúng một lần, các observable contracts của FR-03/FR-05 đều map tới field result, options/rationale/decision owner và before/after evidence đầy đủ.

**Evidence oracle:** marker scan, schema diff, FR-03/FR-05 consistency checklist và conflict record. Kết luận **REVISE** nếu chỉ có syntactic resolution hoặc một acceptance contract bị bỏ.

### AT-U03-03 — OUT-U03-03 / LO3.1 / RB-U03-03

**Given** Admin branch đã peer fetch, **when** reviewer so exact reviewed tip với graph cuối, **then** old tip vẫn là commit hợp lệ và có quan hệ containment theo strategy đã tuyên bố; không có force-update/rebase evidence trên shared refs; working tree sạch và recovery decision là append-only khi history đã published.

**Evidence oracle:** reviewed tip record, `git cat-file -e <reviewed-tip>^{commit}`, `git merge-base --is-ancestor <reviewed-tip> develop`, graph và strategy decision. Nếu chọn squash, learner không được tuyên bố tip containment; phải chứng minh policy/oracle tương ứng, nhưng NovaShop working agreement ưu tiên no-ff cho bài này.

## 🧪 Cách xác minh

Reviewer dùng refs/object IDs trong submission:

```text
git status --short --branch
git diff --check
git grep -n -E '^(<<<<<<<|=======|>>>>>>>)' -- '*.md' '*.csv'
git log --graph --decorate --oneline --all
git merge-base --is-ancestor <checkout-reviewed-tip> develop
git merge-base --is-ancestor <admin-reviewed-tip> develop
git cat-file -e <admin-reviewed-tip>^{commit}
```

Artifact review bổ sung:

- canonical `changed_by` definition count = 1;
- FR-03 và FR-05 mỗi requirement có observable behavior, artifact ref và evidence;
- upstream NS-202 evidence được tiêu thụ, không copy tên mà thiếu ref;
- decision/options/owner và prevention rule không rỗng;
- secret/PII scan = 0.

`git grep` không tìm thấy marker trả exit 1 và được xem là PASS cho check đó. Mọi ancestor check được yêu cầu theo strategy phải exit 0. Lệnh không tự chứng minh semantic correctness; reviewer chấm thêm requirement checklist.

## 📊 Rubric chấm điểm — tổng 100%

| ID | Tiêu chí | Trọng số | LO / AT | Mức Excellent | Mức Meets | Mức Partial | Not met |
| --- | --- | ---: | --- | --- | --- | --- | --- |
| RB-U03-01 | Đúng topology và quyết định Git Flow | 40% | LO3.1 / AT-U03-01 | Baseline/order/topology tái lập đầy đủ; trade-off và alternate order được đánh giá bằng evidence | Source/target, merge base, order và graph đúng; evidence bắt buộc đủ | Quyết định cơ bản đúng nhưng thiếu một risk/owner/ref | Sai source/target, không có graph hoặc không tái lập được |
| RB-U03-02 | Traceability từ PBI/change tới review và conflict evidence | 35% | LO3.2 / AT-U03-02 | Không link mồ côi; canonical result giữ trọn FR-03/FR-05 và reviewer tái lập toàn chuỗi | Requirement, options, owner, resolution và oracles đầy đủ | Giữ chuỗi chính nhưng thiếu một link/evidence hoặc rationale | Mất một acceptance contract, chỉ xóa marker hoặc không có decision log |
| RB-U03-03 | An toàn lịch sử, chất lượng artifact và failure/recovery reasoning | 25% | LO3.1, LO3.2 / AT-U03-03 | Shared-tip integrity, containment và recovery được chứng minh; prevention xử lý đúng root cause | Không rewrite shared history; status sạch; recovery/secret checks đạt | Strategy hợp lý nhưng thiếu một containment/recovery evidence | Rewrite/force-push shared ref, che lịch sử hoặc vi phạm data safety |

**Điểm đạt:** 70%. Rubric chấm kết quả quan sát được; văn phong đẹp không bù cho oracle hoặc traceability thiếu.

## 📚 Nguồn đầu vào và provenance

### Nguồn đã map

- Git Reference Manual 2.54.0; Pro Git, 2nd Edition.
- Vincent Driessen, *A successful Git branching model*.
- Scrum Guide, November 2020.
- NovaShop Project Brief, Backlog, Change Cards và Git Flow Artifact Templates, dữ liệu synthetic nội bộ.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — từ kiến thức đã huấn luyện]** Hai proposed `changed_by` contracts và fixture branch là dữ liệu đánh giá synthetic; không đại diện schema của doanh nghiệp thật.
- **[BỔ SUNG — nguồn: Git Reference Manual 2.54.0]** `merge-base --is-ancestor` và `cat-file -e` được dùng làm evidence về ancestry/object existence; không thay thế business review.

---
<!-- QUALITY GATE: 3 concept applications phủ OUT-U03-01..03 và LO3.1/3.2; mỗi item có scenario/input, rule+rationale, deliverable, AT và rubric; assignment độc lập, không walkthrough/solution; project chain ASM-GF-01 → ASM-GF-02 → ASM-GF-03 resolve; rubric=100%. -->

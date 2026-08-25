# Hands-on Lab LAB-U01-01 — Khởi tạo repo tài liệu và bản đồ branch NovaShop

| Thuộc tính | Giá trị |
| --- | --- |
| Unit | U01 — Bản đồ Git Flow và baseline NovaShop |
| Hình thức | Guided practice có giảm dần hướng dẫn |
| Thời lượng dự kiến | 45 phút |
| Độ khó | Medium |
| Project slice | M-GF-01 — repository baseline, routing map, working agreement |
| Mức xác thực | Simulated; chỉ dữ liệu synthetic |
| Validation method | Artifact review + Git ref/graph oracle |

## 🎯 Learning Outcomes được thực hành

- **LO1.1:** phân loại đúng vai trò, nguồn, đích và vòng đời branch trong ít nhất 8/10 tình huống NovaShop.
- **LO1.2:** khởi tạo repo artifact có `main`, `develop`, annotated tag baseline và policy kiểm chứng được.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

| Material example | Checkpoint | LO | Changed input/recreate/debug | Evidence |
| --- | --- | --- | --- | --- |
| MEX-U01-01 | CP-U01-01 | LO1.1, LO1.2 | Tự tạo baseline và routing table từ CARD-U01 thay vì dùng bảng đã điền | status + routing artifact |
| MEX-U01-01 | CP-U01-02 | LO1.1, LO1.2 | Tự giải thích graph/SHA của repo vừa tạo | graph + refs + containment |
| MEX-U01-01 | CP-U01-03 | LO1.1, LO1.2 | Debug ref `qc` ngoài policy, lưu before/after evidence | failure/recovery evidence + decision note |

## 🧭 Bối cảnh nghề nghiệp/dự án và project increment

Bạn là thành viên Scrum Team NovaShop. Project brief và backlog đang nằm trong một thư mục chưa version hóa. Nhóm cần một baseline chung trước khi thực hiện Search, Cart, Checkout và Payment sandbox. Sponsor đề nghị thêm branch `qc` dài hạn, nhưng chưa nêu trạng thái sản phẩm riêng, owner, exit criteria hay đường merge.

**User story M-GF-01:** Là Scrum Team, chúng tôi muốn một bản đồ branch chung để mọi thay đổi NovaShop đi đúng tuyến.

**Business value:** giảm direct commit, tránh nhầm dòng production-ready với dòng tích hợp, và tạo audit trail cho các Unit sau.

**Increment:** repo local có baseline, routing decision table và working agreement. Lab không tạo mã nguồn ứng dụng, payment data hoặc remote.

## 🧰 Điều kiện bắt đầu

### Kiến thức/kỹ năng tiên quyết

- Đã đọc `material.md` và `example.md` của U01.
- Biết chỉnh Markdown/CSV và chạy lệnh Git từ repo root.
- Biết đọc PBI/acceptance oracle; không cần kinh nghiệm lập trình.

### Môi trường, công cụ và phiên bản

- Git CLI 2.40+; tài liệu được kiểm theo Git 2.54.0.windows.1.
- Markdown editor CommonMark-compatible; CSV editor UTF-8.
- Một **bản sao Lab riêng** tên `NovaShop-U01-Lab`; không chạy lệnh trong thư mục khóa học gốc.
- Danh tính Git chỉ cấu hình local: `NovaShop Learner` / `learner@example.invalid`.

### Starter assets

- [NovaShop Project Brief](../../starter/NovaShop_Project_Brief.md)
- [NovaShop Backlog](../../starter/NovaShop_Backlog.csv)
- [NovaShop Change Cards](../../starter/NovaShop_Change_Cards.md), dùng `CARD-U01`
- [Git Flow Artifact Templates](../../starter/templates/GitFlow_Artifact_Templates.md)
- Provenance version 1.0; internal approved; synthetic only.

### Input/trạng thái ban đầu

- Thư mục `NovaShop-U01-Lab` chưa có `.git`.
- Trong thư mục có `project-artifacts/baseline/` chứa bản sao Project Brief và Backlog.
- `governance/` và `evidence/M-GF-01/` chưa có artifact hoàn chỉnh.
- Sponsor muốn thêm `qc`; quyết định chưa được đưa ra.

### Ràng buộc và phạm vi được phép thay đổi

- Chỉ thao tác trong bản sao Lab; kiểm tra current directory trước mọi reset/cleanup.
- Không cấu hình remote, không force push, không dùng credential thật.
- Không nhập dữ liệu khách hàng, PAN/CVV, endpoint production hoặc email thật.
- Không viết mã nguồn ứng dụng; chỉ tạo/chỉnh Markdown, CSV và Git refs local.
- Mọi kết luận phải có output Git hoặc review criterion; không nộp ảnh chụp thay cho text evidence.

## 📚 Nguồn đầu vào đã map

- SRC-GIT-DOC — Git Reference Manual 2.54.0.
- SRC-PROGIT — Pro Git, 2nd Edition.
- SRC-NVIE — *A successful Git branching model*.
- SRC-VIBLO — *Cơ bản về Gitflow Workflow*.
- SRC-NS-BRIEF/CARDS/TPL — NovaShop starter assets version 1.0.

## 📋 Lab outline và Definition of Done

### Checklist phạm vi

- Khởi tạo baseline `main`, annotated tag `baseline-0.0.0` và `develop`.
- Tạo routing table cho 10 tình huống, đúng ít nhất 8/10 và đúng bắt buộc tuyến feature/release/hotfix.
- Viết working agreement có source/target/lifecycle, review/evidence rule, `master ≙ main` và Scrum boundary.
- Áp dụng changed constraint `qc`, lưu dấu hiệu fail và recovery.
- Chứng minh status sạch, graph/ref/containment đúng, tag type đúng.

### Checkpoint đã hoạch định từ course plan

- **CP-U01-01** · refs `MEX-U01-01` · `LO1.1`, `LO1.2` · verify `git status --short --branch`.
- **CP-U01-02** · refs `MEX-U01-01` · `LO1.1`, `LO1.2` · verify `git log --graph --decorate --oneline --all`.
- **CP-U01-03** · refs `MEX-U01-01` · `LO1.1`, `LO1.2` · verify `git show-ref --heads --tags`.

### Definition of Done

- Cả ba checkpoint đạt expected result và có evidence file.
- `main` và `develop` có vai trò phân biệt; tag baseline truy vấn được và là annotated tag.
- Supporting branch policy có source, target, lifecycle và cleanup rule.
- `qc` không còn trong refs sau recovery; decision record giải thích vì sao.
- Working tree sạch; không secret/PII; reset chỉ tác động bản sao Lab.
- Bạn giải thích được một trade-off: audit-friendly topology đổi lấy thêm merge/branch governance.

## 🪜 Các bước dự kiến và mức hướng dẫn

| Chặng | Mức hướng dẫn | Thời gian |
| --- | --- | ---: |
| Checkpoint 0 — preflight | đầy đủ lệnh và oracle | 5 phút |
| CP-U01-01 — baseline/routing | khung artifact + lệnh; tự quyết định 10 dòng | 18 phút |
| CP-U01-02 — graph/evidence | gợi ý oracle; tự diễn giải SHA/topology | 10 phút |
| CP-U01-03 — changed constraint/failure | scenario + safety gate; tự viết rationale/prevention | 8 phút |
| Final validation/packaging | checklist độc lập | 4 phút |

## Checkpoint 0 — Baseline và safety check

### Action

1. **Why:** tránh biến repo khóa học gốc thành nơi thử nghiệm. **Action:** mở terminal tại `NovaShop-U01-Lab`, xác nhận tên thư mục hiện tại bằng lệnh tương ứng hệ điều hành và kiểm tra thư mục có đúng hai starter artifact đã sao chép. **Explanation:** mọi Git command/reset từ đây chỉ được phép tác động bản sao Lab.
2. **Why:** xác nhận Git đáp ứng contract. **Action:** chạy `git --version`. **Explanation:** version phải từ 2.40 trở lên để dùng các lệnh trong Lab một cách nhất quán.
3. **Why:** phát hiện repo được khởi tạo nhầm từ trước. **Action:** chạy `git status`. **Explanation:** ở baseline mong đợi, Git trả thông báo đây chưa phải repository; nếu lệnh trả trạng thái branch, dừng và chọn bản sao sạch.
4. **Why:** ngăn dữ liệu ngoài scope đi vào commit. **Action:** mở hai starter artifact và scan thủ công tên/email/token/URL thật. **Explanation:** chỉ dữ liệu synthetic và domain `example.invalid` được phép.

### Verify

```text
git --version
git status
```

### Expected result

- Git 2.40+.
- `git status` báo không phải repository.
- Project Brief và Backlog mở được, UTF-8, không chứa credential/PII.

### Evidence

Ghi version, tên bản sao Lab và kết quả safety scan vào `evidence/M-GF-01/preflight.txt` sau khi repo được khởi tạo ở CP-U01-01; không ghi absolute path cá nhân.

### Troubleshooting

- Nếu đang ở repo khác: không tiếp tục; đóng terminal và mở tại bản sao Lab đúng.
- Nếu asset lỗi encoding: sao chép lại từ starter, chọn UTF-8; không sửa bản gốc.
- Nếu phát hiện dữ liệu thật: loại khỏi bản sao, thông báo trainer và dùng fixture synthetic.

### Reset/rollback

Checkpoint chưa thay đổi Git. Nếu baseline không đúng, bỏ bản sao này bằng thao tác quản lý file an toàn của hệ điều hành và tạo **một bản sao mới**; không xóa thư mục khóa học.

## Checkpoint 1 — CP-U01-01: Tạo baseline và routing artifact

**Material example refs:** `MEX-U01-01` · **LO:** `LO1.1`, `LO1.2`.

### Action

1. **Why:** tạo canonical production-ready ref ngay từ commit đầu. **Action:** chạy `git init -b main`, rồi cấu hình `user.name` và `user.email` với scope `--local`. **Explanation:** `-b main` loại bỏ phụ thuộc vào default branch toàn máy; local config không làm thay đổi danh tính repo khác.
2. **Why:** biến starter input thành snapshot kiểm toán. **Action:** dùng editor/file explorer xác nhận Project Brief và Backlog nằm dưới `project-artifacts/baseline/`; stage đúng thư mục và commit với message `chore(M-GF-01): establish NovaShop artifact baseline`. **Explanation:** commit chỉ chứa input baseline, chưa chứa working agreement chưa duyệt.
3. **Why:** tạo mốc bất biến có metadata. **Action:** tạo annotated tag `baseline-0.0.0` với annotation `NovaShop training baseline 0.0.0`. **Explanation:** tag gắn vào current `main` commit; chưa dùng số release sản phẩm.
4. **Why:** tách dòng tích hợp tương lai khỏi baseline. **Action:** tạo và switch `develop` từ current `main`. **Explanation:** lúc này hai branch cùng ancestry; commit governance tiếp theo làm `develop` tiến riêng.
5. **Why:** biến hiểu biết branch role thành quyết định nghề nghiệp. **Action:** trong `governance/branch-routing.md`, tạo 10 dòng cho: NS-101 Search, NS-102 Cart, release scope 0.1.0, UAT wording fix, production shipping-fee incident, Admin 0.2.0 trong lúc ổn định 0.1.0, experiment bị loại, backlog governance change, yêu cầu `qc`, direct commit vào `main`. Điền state, branch type, source, target, exit/oracle và rationale. **Explanation:** không chấm theo prefix đơn thuần; chấm theo state/source/target/lifecycle.
6. **Why:** đặt guardrail có thể audit. **Action:** tạo `governance/git-flow-working-agreement.md` với các trường canonical branch, năm role, naming, review gate, annotated tag, evidence, data safety, `master ≙ main`, Scrum boundary và dấu hiệu không nên dùng Git Flow. **Explanation:** mỗi rule phải có owner và PASS/REVISE oracle.
7. **Why:** lưu increment trên đúng dòng tương lai. **Action:** stage `governance/` và `evidence/M-GF-01/preflight.txt`, rồi commit với message `docs(M-GF-01): define Git Flow working agreement`. **Explanation:** đây là commit trên `develop`; `main` vẫn giữ baseline.

Lệnh Git dùng trong checkpoint:

```text
git init -b main
git config --local user.name "NovaShop Learner"
git config --local user.email "learner@example.invalid"
git add project-artifacts/baseline
git commit -m "chore(M-GF-01): establish NovaShop artifact baseline"
git tag -a baseline-0.0.0 -m "NovaShop training baseline 0.0.0"
git switch -c develop
git add governance evidence/M-GF-01/preflight.txt
git commit -m "docs(M-GF-01): define Git Flow working agreement"
```

### Verify

```text
git status --short --branch
git branch --show-current
git cat-file -t baseline-0.0.0
```

Review routing table bằng role table trong Material; ba dòng feature/release/hotfix là critical rows và bắt buộc đúng.

### Expected result

- current branch là `develop`;
- status không có changed/untracked file;
- tag type trả `tag`;
- routing đúng ít nhất 8/10, critical rows đúng 3/3;
- working agreement có đủ rule và oracle, không coi Git Flow là Scrum rule.

### Evidence

- `governance/branch-routing.md`;
- `governance/git-flow-working-agreement.md`;
- `evidence/M-GF-01/status-after-baseline.txt` chứa command + output + exit result;
- self-review `PASS/REVISE` kèm số dòng routing đúng.

### Troubleshooting

- **`git init -b main` không hỗ trợ:** Git version không đạt preflight; nâng cấp môi trường Lab thay vì đổi contract.
- **Commit báo identity unknown:** chạy lại hai lệnh `git config --local`; không dùng email thật.
- **Tag type trả `commit`:** bạn đã tạo lightweight tag; vì tag vẫn local/chưa chia sẻ, ghi failure evidence rồi thay bằng annotated tag theo hướng dẫn Material.
- **Routing dưới 8/10:** với mỗi dòng sai, hỏi “trạng thái production hiện hành hay tương lai nào cần thay đổi?” rồi sửa rationale, không chỉ sửa prefix.

### Reset/rollback

- Trước commit: dùng editor hoàn tác nội dung; kiểm `git status` trước khi dùng `git restore` vì lệnh có thể bỏ thay đổi chưa lưu.
- Sau commit nhưng topology sai: dừng, lưu graph và decision note; cách reset ưu tiên là tạo bản sao Lab mới và chạy lại. Không force-push/rewrite vì Lab đang dạy baseline audit.

## Checkpoint 2 — CP-U01-02: Chứng minh topology thay vì tin tên branch

**Material example refs:** `MEX-U01-01` · **LO:** `LO1.1`, `LO1.2`.

### Action

1. **Why:** graph là bằng chứng cấu trúc, không phải trang trí. **Action:** chạy graph command và sao chép nguyên output vào `evidence/M-GF-01/graph-after.txt`. **Explanation:** expected shape có governance commit trên `develop` và baseline commit mang `main` + tag.
2. **Why:** tên branch không chứng minh ancestry. **Action:** chạy `git merge-base --is-ancestor main develop`, ghi command, exit code và kết luận. **Explanation:** exit code 0 chứng minh baseline `main` nằm trong lịch sử `develop`; output rỗng là bình thường.
3. **Why:** audit cần ref inventory. **Action:** chạy `git show-ref --heads --tags` và lưu vào `evidence/M-GF-01/refs-before-qc.txt`. **Explanation:** ở thời điểm này chỉ chấp nhận `main`, `develop` và tag baseline.
4. **Why:** reviewer phải tái lập kết luận. **Action:** viết `evidence/M-GF-01/topology-review.md`, liên kết mỗi acceptance criterion với đúng evidence và kết luận PASS/REVISE. **Explanation:** không ghi “graph đúng” mà thiếu SHA/ref/oracle.
5. **Why:** evidence cũng là artifact cần version hóa. **Action:** commit evidence trên `develop` với message `docs(M-GF-01): record baseline topology evidence`. **Explanation:** commit này làm `develop` tiến, không thay `main`/tag.

### Verify

```text
git log --graph --decorate --oneline --all
git merge-base --is-ancestor main develop
git show-ref --heads --tags
git status --short --branch
```

### Expected result

- graph có một dòng lịch sử từ baseline tới các commit governance/evidence trên `develop`;
- containment exit code 0;
- refs chưa có `qc`, release hoặc hotfix;
- `main` và annotated tag vẫn trỏ baseline commit;
- status sạch sau commit evidence.

### Evidence

- `graph-after.txt`;
- `refs-before-qc.txt`;
- `topology-review.md` có command → observation → conclusion;
- branch routing và working agreement từ CP-U01-01.

### Troubleshooting

- **Containment exit code khác 0:** `develop` được tạo từ ref sai; so `git rev-parse main`, `develop` và `git merge-base main develop`; không tiếp tục CP3.
- **Graph thiếu tag:** chạy `git tag --list`; nếu tag chưa tạo, quay lại tag gate CP1; nếu tag có nhưng graph dùng option khác, dùng đúng `--all --decorate`.
- **Evidence tạo untracked file sau verify:** stage/commit evidence rồi chạy status lại; final evidence phải phản ánh trạng thái sau commit.

### Reset/rollback

Nếu chỉ sai nội dung review chưa commit, chỉnh artifact và verify lại. Nếu ancestry sai, giữ evidence chẩn đoán rồi tạo bản sao Lab mới từ starter; không dùng hard reset lên thư mục khóa học hoặc force update ref.

## Checkpoint 3 — CP-U01-03: Changed constraint `qc`, failure evidence và recovery

**Material example refs:** `MEX-U01-01` · **LO:** `LO1.1`, `LO1.2` · **Changed input:** Sponsor yêu cầu long-lived `qc` không có state/owner/exit/merge contract.

### Action

1. **Why:** học chẩn đoán ref ngoài policy bằng quan sát thật. **Action:** trong repo Lab, tạo một ref tạm cùng trỏ `develop` bằng `git branch qc develop`; không switch và không commit lên `qc`. **Explanation:** ref này mô phỏng failure mà không tạo unique work.
2. **Why:** ghi bằng chứng trước khi sửa. **Action:** chạy `git show-ref --heads --tags` và hai commit range `git log --oneline develop..qc`, `git log --oneline qc..develop`; lưu output vào `evidence/M-GF-01/qc-before.txt`. **Explanation:** hai range rỗng chứng minh cleanup sẽ không làm mất unique commit.
3. **Why:** quyết định phải dựa trên policy, không dựa vào quyền lực stakeholder. **Action:** viết `governance/qc-branch-decision.md` với context, drivers, options, decision, consequences, owner, trigger xem lại và exact evidence. **Explanation:** expected decision là không giữ `qc` trong baseline hiện tại vì thiếu contract; nếu bạn muốn chọn khác, phải chứng minh đủ state/owner/exit/merge và nhận review `PASS`.
4. **Why:** phục hồi bằng guardrail an toàn. **Action:** khi current branch là `develop` và commit ranges rỗng, chạy `git branch -d qc`. **Explanation:** `-d` từ chối nếu branch chưa merged; không dùng `-D`.
5. **Why:** chứng minh failure đã được loại bỏ. **Action:** lưu refs sau cleanup và tag type; commit decision/evidence trên `develop` với message `docs(M-GF-01): reject unowned qc branch`. **Explanation:** lịch sử giữ lại quyết định dù ref tạm đã biến mất.

### Verify

```text
git branch --show-current
git show-ref --heads --tags
git cat-file -t baseline-0.0.0
git status --short --branch
```

### Expected result

- current branch `develop`;
- không có `refs/heads/qc`;
- chỉ có long-lived branches `main`, `develop` ở baseline này;
- tag baseline tồn tại và type `tag`;
- decision note có dấu hiệu → nguyên nhân → evidence → remediation → prevention;
- status sạch.

### Evidence

- `evidence/M-GF-01/qc-before.txt`;
- `evidence/M-GF-01/qc-after.txt`;
- `governance/qc-branch-decision.md`;
- graph cuối cho thấy decision commit trên `develop` nhưng không có `qc` ref.

### Troubleshooting

- **`qc` có unique commit:** dừng cleanup, giữ branch, audit nội dung và owner; không dùng `-D`. Failure fixture đã bị thay đổi ngoài hướng dẫn.
- **Đang checkout `qc`:** switch `develop`, kiểm status sạch, chạy lại range check rồi mới cleanup.
- **Decision note chỉ ghi “không cần”:** bổ sung state/owner/exit/merge analysis và chi phí drift; không đạt nếu thiếu oracle.
- **Tag type sai:** xử lý theo CP1 trước final validation; không che lỗi bằng cách xóa evidence.

### Reset/rollback

Nếu cần tái tạo failure, chỉ tạo lại `qc` cùng trỏ `develop`; không commit unique work. Nếu checkpoint dở, current branch `develop` và ref `qc` không có unique commit, safe delete bằng `git branch -d qc`. Nếu không chắc, dừng và dùng bản sao Lab mới.

## 🧪 Final validation

Chạy từ repo root, ghi command + output + exit code vào evidence cuối:

```text
git status --short --branch
git log --graph --decorate --oneline --all
git show-ref --heads --tags
git merge-base --is-ancestor main develop
git cat-file -t baseline-0.0.0
git branch --show-current
```

| Gate | PASS | REVISE |
| --- | --- | --- |
| CP-U01-01 | routing ≥ 8/10, critical 3/3; policy đủ; annotated tag | thiếu role/source/target/lifecycle hoặc tag nhẹ |
| CP-U01-02 | graph đúng; `main` ancestor của `develop`; evidence tái lập | chỉ có ảnh hoặc containment fail |
| CP-U01-03 | ref `qc` không còn; before/after + decision/prevention đầy đủ | cưỡng ép xóa unique work hoặc thiếu rationale |
| Safety | local-only; synthetic-only; status sạch | credential/PII, remote production hoặc dirty state |

Nếu bất kỳ gate nào `REVISE`, chưa công bố DoD và chưa chuyển artifact sang U02.

## 📦 Bằng chứng và deliverables

Nộp/giữ lại trong repo Lab:

```text
project-artifacts/baseline/
governance/branch-routing.md
governance/git-flow-working-agreement.md
governance/qc-branch-decision.md
evidence/M-GF-01/preflight.txt
evidence/M-GF-01/status-after-baseline.txt
evidence/M-GF-01/graph-after.txt
evidence/M-GF-01/refs-before-qc.txt
evidence/M-GF-01/qc-before.txt
evidence/M-GF-01/qc-after.txt
evidence/M-GF-01/topology-review.md
```

Mỗi text evidence phải ghi command, observation và conclusion. Không nộp `.git`, absolute path cá nhân hoặc raw output có dữ liệu nhạy cảm.

## ♻️ Reset, cleanup và khả năng chạy lại

- **Merge dở:** nếu `git status` xác nhận merge đang diễn ra trong repo Lab, lưu failure evidence rồi dùng `git merge --abort`.
- **Ref `qc` tạm:** chỉ xóa bằng `git branch -d qc` sau khi current branch là `develop` và hai commit range rỗng.
- **Artifact chưa commit:** kiểm diff trước `git restore`; lệnh restore có thể bỏ thay đổi chưa lưu.
- **Topology không còn tin cậy:** tạo bản sao Lab mới từ starter. Không dùng recursive delete/reset trên thư mục khóa học gốc.
- **Cleanup cuối:** giữ bản sao đạt DoD để làm baseline U02; không cấu hình remote.

Smoke check sau reset/re-run: `git status --short --branch` sạch, current branch `develop`, graph/refs/tag oracle PASS.

## 🔁 Artifact được tái sử dụng ở đâu

- **U02/LAB-U02-01:** dùng repo M-GF-01, routing table và working agreement làm baseline feature flow.
- **REV-GF-01:** dùng routing/evidence để audit tình huống tích hợp.
- **CAP-GF-01:** dùng policy baseline làm mốc so sánh khi quyết định giữ hay đơn giản hóa Git Flow.

Giữ lại commit history và artifact evidence; chỉ supporting ref tạm được cleanup.

## 🔐 Chính sách lời giải

Lab cung cấp command/safety oracle nhưng không cung cấp artifact hoàn chỉnh để sao chép. Bạn phải tự điền 10 routing decisions, working agreement và decision rationale. U01 không có Assignment; nội dung này không tiết lộ lời giải `ASM-GF-01` ở U02.

## 📚 Provenance phần bổ sung

### Nguồn đã map

- [Git Reference Manual 2.54.0](https://git-scm.com/docs/git/2.54.0).
- [Pro Git — Git Branching](https://git-scm.com/book/en/v2/Git-Branching-Branches-in-a-Nutshell).
- [A successful Git branching model](https://nvie.com/posts/a-successful-git-branching-model/).
- [Cơ bản về Gitflow Workflow](https://viblo.asia/p/co-ban-ve-gitflow-workflow-4dbZNn6yZYM).
- NovaShop Project Brief, Change Cards và Artifact Templates version 1.0, internal approved.

### Phần bổ sung/suy diễn

- **[BỔ SUNG — nguồn: Git documentation/Pro Git]** Các safety gates dùng `status`, commit range, refs, ancestry và safe branch deletion.
- **[BỔ SUNG — nguồn: CARD-U01 synthetic]** Đề nghị `qc`, routing prompts và evidence layout là dữ liệu đào tạo mô phỏng.

# Unit U01: Bản đồ Git Flow và baseline NovaShop — Ví dụ và nghiên cứu tình huống

> **Case:** `CASE-U01-01` · **Project milestone:** `M-GF-01` · **Mức xác thực:** simulated · **Phương thức xác minh:** artifact review

## 🎯 Learning Outcomes liên quan

- **LO1.1:** phân loại vai trò/source/target/lifecycle của năm loại branch bằng decision table và graph.
- **LO1.2:** đưa baseline local về trạng thái có `main`, `develop`, annotated tag và policy kiểm chứng được.

**Outline mapping:** `OUT-U01-01`, `OUT-U01-02`, `OUT-U01-03`.

## 🧭 Liên kết với ngữ cảnh nghề nghiệp/dự án

NovaShop sắp bắt đầu Sprint đầu tiên. Release Owner nhận một repo artifact local do nhóm kickoff trước bàn giao. Tên branch trông hợp lý, nhưng Sponsor đã yêu cầu thêm `qc`, và tag baseline được tạo mà chưa audit type. Case này tập trung vào **chẩn đoán topology sai rồi sửa có điều kiện**, khác với happy-path `MEX-U01-01` trong Material.

Artifact hoàn tất gồm:

- `governance/baseline-audit.md`;
- `governance/git-flow-working-agreement.md` đã chốt quyết định `qc`;
- evidence refs/graph/tag trước và sau;
- baseline repo đạt acceptance criteria M-GF-01.

## 🧰 Điều kiện chạy ví dụ

- Git CLI 2.40+ trong repo local cô lập; ví dụ đã được thiết kế cho Git 2.54.0.windows.1.
- Working tree sạch; không có remote production hoặc credential.
- `qc` không có commit riêng: nó cùng trỏ commit với `develop`.
- `baseline-0.0.0` là lightweight tag local và **chưa từng được chia sẻ**. Điều kiện này quyết định việc có được thay tag hay không.
- Tất cả nội dung NovaShop là synthetic; email Git dùng `learner@example.invalid`.

Preflight evidence:

```text
git --version
git status --short --branch
git log --graph --decorate --oneline --all
git show-ref --heads --tags
git cat-file -t baseline-0.0.0
```

## 📚 Nguồn đầu vào đã map

- SRC-GIT-DOC — Git Reference Manual 2.54.0.
- SRC-PROGIT — Pro Git, 2nd Edition.
- SRC-NVIE — *A successful Git branching model*.
- SRC-VIBLO — *Cơ bản về Gitflow Workflow*.
- SRC-NS-BRIEF — NovaShop simulated project brief version 1.0.

### Mapping case đã chốt trong course plan

| Case ID | LO | Outline | Increment | Authenticity |
| --- | --- | --- | --- | --- |
| CASE-U01-01 | LO1.1, LO1.2 | OUT-U01-01, OUT-U01-02, OUT-U01-03 | M-GF-01 | simulated, inherited from NovaShop |

## Case Study 01: Audit baseline có branch `qc` và tag nhẹ

### 1. Ticket và tiêu chí thành công

- **Vai trò/stakeholder:** học viên là Release Owner; Sponsor muốn `qc`; Scrum Team cần một baseline không nhập nhằng.
- **Vấn đề:** repo có ba branch dài hạn `main`, `develop`, `qc`; tag tên đúng nhưng không có tag object; team chưa ghi phép ánh xạ `master` → `main`.
- **Constraint:** không rewrite history; không xóa branch nếu có unique commit; không di chuyển tag đã công bố; không dùng branch môi trường khi chưa có state/owner/exit/merge contract.
- **Tiêu chí thành công:** chỉ còn các ref được policy chấp nhận; `main` là ancestor của `develop`; tag baseline là annotated; audit record giải thích được mọi quyết định và ranh giới Git Flow/Scrum.

### 2. Input, trạng thái ban đầu và ràng buộc

Output giả lập ban đầu:

```text
$ git log --graph --decorate --oneline --all
* 6c17a42 (HEAD -> develop, qc) docs(M-GF-01): add draft working agreement
* 31bb98e (tag: baseline-0.0.0, main) chore(M-GF-01): import NovaShop baseline

$ git cat-file -t baseline-0.0.0
commit
```

Thông tin quản trị kèm theo:

| Input | Giá trị |
| --- | --- |
| Release cadence | theo phiên bản mô phỏng 0.1.x/0.2.x |
| QC state riêng | không có; QC chỉ kiểm ref được chỉ định |
| Owner/exit criteria của `qc` | chưa xác định |
| Unique work trên `qc` | không có; ref bằng `develop` |
| Tag đã push/chia sẻ | chưa; repo local đào tạo |
| Production data | không có |

Hai điều kiện cuối là safety gate. Nếu `qc` có unique work hoặc tag đã công bố, cách xử lý phải đổi: bảo toàn work và không âm thầm di chuyển public ref.

### 3. Phân tích lựa chọn

**Lựa chọn A — giữ `qc` vì Sponsor yêu cầu.** Nhanh về mặt giao tiếp nhưng thêm một long-lived state không có owner, exit criteria hay đường merge. Hệ quả là `qc` dễ drift khỏi `develop` và người review không biết ref nào là nguồn sự thật.

**Lựa chọn B — đổi tên `qc` thành `release/0.1.0`.** Tên trông đúng Git Flow nhưng sai semantics: chưa có scope freeze, UAT plan hay version decision. Đổi tên không biến một environment pointer thành release branch hợp lệ.

**Lựa chọn C — không dùng branch `qc`; QC kiểm feature/release ref được chỉ định.** Phù hợp baseline hiện tại vì `qc` không có state độc lập và không chứa unique work. Đây là lựa chọn được dùng.

Với tag, case cho phép thay lightweight tag bằng annotated tag vì ref chỉ tồn tại local, chưa công bố và vẫn trỏ commit baseline. Trong repo cộng tác, không được suy rộng thao tác này thành quyền di chuyển tag đã chia sẻ.

### 4. Cách triển khai

#### 4.1 Ghi audit trước khi sửa

`governance/baseline-audit.md` ghi:

| Finding | Exact evidence | Impact | Decision |
| --- | --- | --- | --- |
| F-01 `qc` ngoài policy | `develop` và `qc` cùng SHA `6c17a42`; không có state/owner/exit | tạo long-lived divergence về sau | loại ref sau safety check |
| F-02 tag nhẹ | `git cat-file -t baseline-0.0.0` → `commit` | thiếu annotation theo policy NovaShop | thay bằng annotated tag tại cùng baseline commit |
| F-03 thiếu branch-name mapping | working agreement không nói `master ≙ main` | người học có thể tạo hai production branches | bổ sung canonical mapping |

Audit lưu cả giả định “ref local chưa công bố”. Nếu giả định sai, decision F-02 phải chuyển thành `REVISE/escalate`.

#### 4.2 Chứng minh `qc` không có unique work

```text
git rev-parse develop
git rev-parse qc
git log --oneline develop..qc
git log --oneline qc..develop
```

Hai `rev-parse` phải trả cùng SHA và hai commit range phải rỗng. Chỉ khi oracle này đạt mới dùng safe delete:

```text
git switch develop
git branch -d qc
```

Option `-d` từ chối xóa branch chưa merge; case không dùng `-D` vì không cần cưỡng ép mất ref.

#### 4.3 Thay tag local theo policy đã duyệt

Trước hết chứng minh tag trỏ đúng commit `main`:

```text
git rev-parse baseline-0.0.0
git rev-parse main
```

Khi hai SHA bằng nhau và audit xác nhận tag chưa chia sẻ:

```text
git tag -d baseline-0.0.0
git tag -a baseline-0.0.0 main -m "NovaShop training baseline 0.0.0"
```

Đây là repair cho fixture local có điều kiện, không phải rule chung để thay tag published.

#### 4.4 Hoàn thiện working agreement

Các quyết định được thêm vào artifact:

| Policy item | Quyết định | Evidence owner |
| --- | --- | --- |
| Canonical production branch | `main`; từ `master` trong nguồn được ánh xạ sang `main` | Release Owner |
| Integration branch | `develop` | Scrum Team |
| Environment testing | kiểm ref/version được chọn; không tạo `qc` mặc định | Reviewer |
| Supporting branch admission | phải có state, source, target, owner, exit criteria | Release Owner |
| Baseline/release tag | annotated, immutable sau công bố | Release Owner |
| Scrum boundary | Git Flow là team workflow; không phải Scrum rule | Scrum Team |

Working agreement được commit trên `develop` bằng một commit chỉ chứa governance correction. `main` không nhận direct commit.

### 5. Output mong đợi

Ví dụ shape của graph sau case; SHA thật có thể khác:

```text
* a82de14 (HEAD -> develop) docs(M-GF-01): close baseline audit findings
* 6c17a42 docs(M-GF-01): add draft working agreement
* 31bb98e (tag: baseline-0.0.0, main) chore(M-GF-01): import NovaShop baseline
```

Expected refs:

- `refs/heads/main` tồn tại;
- `refs/heads/develop` tồn tại;
- không có `refs/heads/qc`;
- `refs/tags/baseline-0.0.0` tồn tại và object type là `tag`;
- `main` nằm trong ancestry của `develop`;
- status sạch trên `develop`.

### 6. Cách xác minh

| Tiêu chí | Cách xác minh | PASS oracle |
| --- | --- | --- |
| Baseline sạch | `git status --short --branch` | đang ở `develop`; không có dòng file thay đổi |
| Topology | `git log --graph --decorate --oneline --all` | `main`/tag ở baseline; `develop` ở governance commit |
| Ref policy | `git show-ref --heads --tags` | không có `refs/heads/qc` |
| Ancestry | `git merge-base --is-ancestor main develop` | exit code 0 |
| Annotated tag | `git cat-file -t baseline-0.0.0` | output `tag` |
| Tag target | `git rev-list -n 1 baseline-0.0.0` và `git rev-parse main` | hai SHA bằng nhau |
| Decision quality | artifact review | mỗi finding có evidence, impact, decision, owner/prevention |
| Data safety | manual scan | không secret, PII, endpoint/payment data thật |

Reviewer kết luận **PASS** chỉ khi cả Git oracle lẫn working agreement đều đạt. “Lệnh chạy không lỗi” nhưng policy thiếu rationale vẫn là `REVISE`.

### 7. Giải thích sâu và failure modes

- **Failure:** `git branch -d qc` từ chối. **Dấu hiệu:** Git báo branch chưa fully merged. **Nguyên nhân:** giả định “không unique work” sai hoặc branch không reachable từ current branch. **Chẩn đoán:** `git log develop..qc`. **Xử lý:** dừng; bảo toàn ref và audit unique commits; không chuyển sang `-D`. **Phòng tránh:** containment/range check là gate trước cleanup.
- **Failure:** SHA tag và `main` khác nhau. **Nguyên nhân:** tag gắn nhầm commit hoặc `main` đã tiến. **Chẩn đoán:** `git show --no-patch --decorate` cho cả hai ref. **Xử lý:** không tự thay tag; xác định baseline được phê duyệt và xin review decision. **Phòng tránh:** record expected baseline SHA tại lúc tag.
- **Failure:** tag đã được một peer fetch. **Nguyên nhân:** thông tin handoff không đầy đủ. **Chẩn đoán:** xác nhận publication log/remote state với owner. **Xử lý:** không di chuyển tag; tạo mốc sửa theo version/policy. **Phòng tránh:** tag publication checklist.
- **Failure:** team vẫn muốn `qc` vì deployment tooling. **Nguyên nhân:** conflating deploy environment với source state. **Chẩn đoán:** yêu cầu team chỉ ra unique state, owner, exit và merge route. **Xử lý:** nếu các driver thực sự tồn tại, lập ADR thay policy; nếu không, deploy từ immutable ref/tag. **Giới hạn:** case không thiết kế CI/CD hoặc môi trường QC.

### 8. Bài học chuyển giao

1. Tên branch không chứng minh vai trò; evidence phải dựa trên graph, refs và ancestry.
2. Cleanup chỉ an toàn sau khi chứng minh không có unique work; `-d` là guardrail tốt hơn `-D` trong case này.
3. Sửa tag local chưa công bố khác hoàn toàn di chuyển tag đã chia sẻ.
4. Branch môi trường cần decision drivers thật; nếu không, nó chỉ tạo thêm trạng thái phải đồng bộ.
5. Lab U01 sẽ dùng input thay đổi: bạn tự lập routing table CARD-U01, tạo baseline từ thư mục chưa version hóa và debug ref ngoài policy với evidence riêng.

## Provenance của các case

### Nguồn được dùng

- [Git Reference Manual 2.54.0](https://git-scm.com/docs/git/2.54.0).
- [Pro Git — Git Branching](https://git-scm.com/book/en/v2/Git-Branching-Branches-in-a-Nutshell).
- [A successful Git branching model](https://nvie.com/posts/a-successful-git-branching-model/).
- [Cơ bản về Gitflow Workflow](https://viblo.asia/p/co-ban-ve-gitflow-workflow-4dbZNn6yZYM).
- NovaShop starter project brief/change card, version 1.0, internal approved.

### Phần bổ sung/suy diễn

- **[BỔ SUNG — nguồn: Git Reference Manual và Pro Git]** Quy trình audit `rev-parse`/commit range trước safe branch deletion và kiểm tag object được ghép thành professional-artifact oracle.
- **[BỔ SUNG — nguồn: CARD-U01 synthetic]** SHA, finding và yêu cầu `qc` là dữ liệu mô phỏng riêng cho case, không đại diện repo production.

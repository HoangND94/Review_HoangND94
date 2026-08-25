# Unit U02: Feature Flow trong Sprint — Học liệu cốt lõi

> **Khóa học:** Git Flow thực chiến qua NovaShop · **Phần:** Feature Delivery and Integration · **Thực hành:** Git trên Markdown/CSV, không viết mã nguồn ứng dụng · **Mức xác thực:** simulated

## 🎯 Learning Outcomes

- **LO2.1 — Apply:** vận hành feature branch từ `develop` tới `develop` cho một PBI NovaShop và duy trì truy vết PBI–commit–review–acceptance evidence.
- **LO2.2 — Evaluate:** đánh giá feature đã đủ điều kiện merge theo Definition of Done, review findings và working state; lập quyết định `PASS` hoặc `REVISE` có bằng chứng.

## 🧭 Ngữ cảnh nghề nghiệp/dự án và phần tăng trưởng của Unit

Tại **M-GF-02**, bạn đưa PBI `NS-101 — Tìm kiếm và lọc sản phẩm` qua feature flow. Baseline kế thừa M-GF-01: repo local có `main`, `develop`, annotated tag và working agreement. Increment mới là **feature evidence pack** gồm issue record, commit plan, acceptance evidence, traceability matrix, review record và containment/cleanup evidence.

Business value không nằm ở số branch đã tạo mà ở khả năng một reviewer trả lời được: thay đổi xuất phát từ PBI nào, commit nào phục vụ acceptance criterion nào, finding nào đã được đóng, và vì sao `develop` được phép nhận feature. Artifact M-GF-02 được tái sử dụng trong U03 và Capstone.

## 📚 Nguồn đầu vào đã map

- **SRC-GIT-DOC:** Git Reference Manual 2.54.0, truy cập 2026-08-25.
- **SRC-PROGIT:** Pro Git, 2nd Edition, living web edition, truy cập 2026-08-25.
- **SRC-NVIE:** *A successful Git branching model*, 2010; reflection 2020; truy cập 2026-08-25.
- **SRC-CONV:** Conventional Commits 1.0.0, truy cập 2026-08-25.
- **SRC-SCRUM:** Scrum Guide, November 2020, CC BY-SA 4.0.
- **SRC-NS-DATA:** NovaShop synthetic backlog version 1.0, internal approved.

---

## 1. Kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết

- Hoàn tất U01/M-GF-01; đọc được graph, refs, ancestry và working tree state.
- Chỉnh sửa Markdown/CSV; đọc PBI, acceptance criteria và Definition of Done.
- Biết lưu output Git đã redact; không dùng remote/credential/PII thật.

### Môi trường, công cụ và phiên bản

- `ENV-GIT-ARTIFACT`: repo Git local cô lập, Git CLI 2.40+; course verification dùng 2.54.0.windows.1.
- Markdown CommonMark, CSV UTF-8; email local giả `learner@example.invalid`.
- Preflight: `git --version`, `git status --short --branch`, `git log --graph --decorate --oneline --all`.

### Phương thức xác minh artifact

`artifact_review`: đối chiếu nội dung dossier với graph, base/commit range, status, review finding và containment oracle. Một branch tên đúng nhưng sai ancestry không đạt.

### Hợp đồng ví dụ triển khai và thực hành

- **Mode:** `professional_artifact` vì LO yêu cầu vận hành workflow và tạo audit evidence, không yêu cầu code ứng dụng.
- **MEX-U02-01:** feature evidence pack NS-101, phủ `OUT-U02-01`–`03`, `LO2.1`–`2.2`.
- **Lab pairing:** `LAB-U02-01/CP-U02-01`–`03` dùng PBI NS-102 và finding “expired promotion”, tức input/failure khác Material.

## 2. Định vị trong lộ trình (Mental Map)

```text
PBI + acceptance criteria
        ↓ branch decision / base evidence
feature/<issue-id>-<slug> từ develop
        ↓ purposeful commits + traceability + sync
review record + DoD + clean state
        ↓ PASS mới được merge
develop chứa feature → containment evidence → cleanup ref
```

Feature branch là **workspace có scope hữu hạn**, không phải bằng chứng Done tự thân. Sprint cung cấp context cho việc lựa chọn và thích nghi công việc; Git Flow không buộc một feature phải sống đúng bằng một Sprint, cũng không biến merge thành Definition of Done. Team cần kết nối hai thế giới bằng artifact/evidence rõ ràng.

## 3. Nội dung lý thuyết cốt lõi

**📋 Checklist bắt buộc phủ — giữ nguyên văn và đúng thứ tự Content Outlines:**

- [x] Từ PBI và acceptance criteria tới feature branch và quy tắc đặt tên
- [x] Purposeful commits, working state, đồng bộ develop và traceability
- [x] Review, Definition of Done, merge về develop và dọn feature branch

#### OUT-U02-01 — Từ PBI và acceptance criteria tới feature branch và quy tắc đặt tên

**Mapping:** `OUT-U02-01` · `LO2.1` · `M-GF-02` · Artifact: issue/branch decision record và base evidence.

##### Định nghĩa rõ ràng

**PBI** mô tả nhu cầu sản phẩm trong Product Backlog; **acceptance criteria** làm rõ hành vi quan sát được cho item; **feature branch** là branch hữu hạn dùng để thực hiện một scope thay đổi cho tương lai, bắt đầu từ `develop` và kết thúc ở `develop` hoặc bị loại bỏ. Tên theo NovaShop là `feature/<issue-id>-<slug>`.

Ranh giới: branch name hỗ trợ truy vết nhưng không chứng minh source; acceptance criteria định nghĩa outcome trong scope nhưng không thay toàn bộ Definition of Done; “đã tạo branch” không có nghĩa item đã bắt đầu đúng hoặc đã Done.

##### Vấn đề/vai trò và quyết định cần đưa ra

Developer/Scrum Team phải quyết định PBI có đủ input để mở feature, branch type/source nào đúng và scope nào bị loại trừ. Product Owner làm rõ value/order; team sở hữu cách thực hiện và chất lượng. Decision record phải trả lời: issue/requirement, user outcome, acceptance oracle, target release, branch source→target và rationale.

##### Cơ chế và mental model

Branch được tạo tại commit `D0` của `develop`; lưu SHA `D0` làm base evidence. Commit trên feature làm ref tiến riêng, còn `develop` có thể tiếp tục. Tên chứa issue ID tạo join key giữa backlog, commit, review và evidence. Slug chỉ giúp người đọc; issue ID mới là định danh ổn định.

Acceptance criteria điều khiển artifact/evidence cần tạo. Với NS-101, keyword, selected filter và empty state phải có specification/evidence riêng; nếu một criterion không map tới commit/artifact/evidence, feature dossier có lỗ hổng dù branch đúng.

##### Khi dùng / khi không dùng

Dùng feature branch cho capability/change tương lai có scope review được. Không dùng feature branch cho production incident cần patch ngay (hotfix) hoặc release-only correction sau scope freeze (release fix). Không mở một branch cho nhiều PBI không liên quan; cũng không ép tách một PBI thành quá nhiều branch nếu làm mất khả năng review end-to-end.

Trade-off: branch nhỏ giảm review/merge risk nhưng có thể tăng coordination; branch lớn giảm số PR nhưng tăng drift và khó cô lập acceptance failure. Chọn scope đủ nhỏ để reviewer liên kết được từng criterion, nhưng đủ trọn để tạo increment usable theo context.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** Product Owner đưa NS-101 vào Sprint Backlog; reviewer cần trace FR-01.
- **Input/baseline/constraint:** `develop` sạch; NS-101 target 0.1.0; oracle gồm keyword, filter selected và empty state; không code ứng dụng.
- **Decision/action:** tạo `feature/NS-101-product-search` từ SHA hiện tại của `develop`; ghi scope included/excluded.
- **Artifact/output:** `features/NS-101/issue-record.md` và `evidence/NS-101/branch-base.txt`.
- **Expected result:** branch hiện tại đúng tên; `develop` là ancestor; issue record có FR-01 và ba oracle.
- **Verification/oracle:** `git merge-base --is-ancestor develop HEAD` exit 0 tại thời điểm branch chưa sync divergence; base SHA trong record bằng `git merge-base feature/NS-101-product-search develop` ở lúc tạo.

##### Ví dụ triển khai trong Material — professional artifact

Đây là lớp branch-decision của `MEX-U02-01` mục 4. Lab `CP-U02-01` tái tạo trên NS-102 và buộc tự quyết định commit boundaries; không dùng lại tên/input NS-101.

##### Best practices

- **Rule:** tên branch chứa issue ID và branch từ `develop`. **Rationale:** ID nối chuỗi traceability; source giữ production baseline tách khỏi future work. **Positive:** `feature/NS-101-product-search` với saved develop SHA. **Negative:** `feature/search` từ `main`; tên dễ hiểu nhưng base sai, reviewer không truy issue ổn định.
- **Rule:** ghi included/excluded scope trước commit đầu. **Rationale:** ngăn scope creep và giúp review diff. **Positive:** included search/filter/empty state; excluded recommendation. **Negative:** thêm recommendation vì “tiện”, kéo requirement ngoài PBI vào release.
- **Rule:** acceptance oracle phải quan sát được. **Rationale:** câu “search tốt” không thể chấm. **Positive:** query không có kết quả tạo empty-state record. **Negative:** “UX thân thiện”; reviewer không có PASS/REVISE criterion.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** `develop` không phải ancestor/base dự kiến. **Nguyên nhân:** tạo từ `main` hoặc branch cũ. **Chẩn đoán:** graph, merge-base và saved D0 SHA. **Sửa:** dừng work; nếu chưa chia sẻ, tạo branch đúng từ `develop` và đưa lại artifact đã review; không force-push shared branch. **Phòng tránh:** branch-base evidence ngay lúc tạo.
- **Dấu hiệu:** commit range chứa nhiều issue ID. **Nguyên nhân:** scope branch không rõ. **Chẩn đoán:** `git log develop..HEAD` và diff. **Sửa:** tách work chưa chia sẻ theo decision được review hoặc trả scope ngoài về backlog. **Phòng tránh:** issue record + commit plan trước thay đổi.
- **Dấu hiệu:** PBI có câu mô tả nhưng không có oracle. **Nguyên nhân:** refinement chưa đủ. **Chẩn đoán:** traceability matrix có acceptance column rỗng. **Sửa:** làm rõ criterion với Product Owner trước merge. **Phòng tránh:** readiness check không đồng nghĩa Scrum gate bắt buộc, nhưng là team practice minh bạch.

#### OUT-U02-02 — Purposeful commits, working state, đồng bộ develop và traceability

**Mapping:** `OUT-U02-02` · `LO2.1`, `LO2.2` · `M-GF-02` · Artifact: commit plan, traceability matrix và sync evidence.

##### Định nghĩa rõ ràng

**Purposeful commit** là snapshot có một intent kiểm tra được, message truy vết tới issue và diff không trộn mục đích không liên quan. NovaShop dùng pattern `<type>(<issue-id>): <imperative summary>`. Conventional Commits cung cấp cấu trúc type/scope/description; NovaShop chọn issue ID làm scope và bổ sung type `docs`, `test`, `chore`, `merge` như team policy.

**Working state** gồm working tree và index. “Clean” nghĩa không còn changed/untracked file ngoài chủ đích. **Đồng bộ develop** là đưa thay đổi integration mới vào feature theo chiến lược đã thống nhất. U02 dùng merge `develop` vào feature cho lịch sử local/shared an toàn; rebase/shared-history trade-off được đào sâu ở U03.

**Traceability** là quan hệ PBI/criterion → commit → artifact → evidence → review result, không phải việc nhắc issue ID ở một nơi rồi thôi.

##### Vấn đề/vai trò và quyết định cần đưa ra

Người thực hiện phải chọn commit boundary, xác định dirty state có thuộc scope, và quyết định khi nào cần sync `develop`. Reviewer cần biết một commit có thể đánh giá/hoàn tác theo intent hay không, và mỗi criterion đã có evidence chưa.

##### Cơ chế và mental model

Index cho phép chọn snapshot có chủ đích. Mỗi commit tiến feature ref và trở thành một node có thể nối tới criterion. Khi `develop` tiến, feature diverges. Merge `develop` vào feature tạo một sync point; lợi ích là không rewrite SHA đã chia sẻ, đổi lại graph có merge commit. Sync không thay thế review và có thể gây conflict; phải chạy acceptance consistency sau sync.

Traceability matrix hoạt động như join table: issue/AC là khóa business, commit SHA là khóa history, artifact/evidence là oracle. Missing link ở bất kỳ cột nào làm kết luận không tái lập được.

##### Khi dùng / khi không dùng

Commit khi một intent nhỏ đã ở trạng thái nhất quán và có mô tả đúng; không commit file tạm, absolute path hay secret. Sync khi `develop` có thay đổi liên quan hoặc trước final review theo policy; không sync theo lịch máy móc nếu không có new commit. Không dùng commit message để thay evidence nội dung.

Trade-off: commit rất lớn khó review; commit quá vụn theo từng thao tác tạo noise. Merge sync giữ SHA nhưng thêm topology; rebase làm graph tuyến tính nhưng rewrite commit, không phù hợp branch đã được peer fetch nếu không có coordination.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** reviewer NS-101 cần thấy keyword/filter/empty state không bị trộn với governance.
- **Input/baseline/constraint:** feature có ba acceptance oracles; develop có một governance update; branch có thể đã được reviewer fetch.
- **Decision/action:** chia commit theo specification và acceptance evidence; merge `develop` vào feature, không rebase shared work.
- **Artifact/output:** commit plan + traceability table + `commit-range-before-review.txt`.
- **Expected result:** feature-only range chứa đúng NS-101 intents; status sạch; mỗi oracle map tới commit/evidence.
- **Verification/oracle:** `git log --oneline --decorate develop..HEAD`, `git status --short`, review từng row traceability không rỗng.

##### Ví dụ triển khai trong Material — professional artifact

Đây là lớp commit/traceability của `MEX-U02-01`. Lab `CP-U02-02` thay input bằng expired-promotion failure và không cung cấp sẵn commit boundaries.

##### Best practices

- **Rule:** một commit = một intent kiểm tra được, có issue ID. **Rationale:** reviewer cô lập nguyên nhân và evidence. **Positive:** `docs(NS-101): define search and filter behavior`; `test(NS-101): record empty-state acceptance evidence`. **Negative:** `update stuff` trộn backlog, spec và review; không biết revert phần nào.
- **Rule:** status/diff sạch và đúng scope trước switch/sync/review. **Rationale:** unstaged input có thể bị mang nhầm qua context. **Positive:** review `git diff --cached` rồi commit. **Negative:** file export chứa đường dẫn cá nhân bị stage cùng evidence.
- **Rule:** trace từng criterion tới evidence quan sát được. **Rationale:** ID trong message chỉ chứng minh association, không chứng minh acceptance. **Positive:** AC-empty → commit SHA → example table → review PASS. **Negative:** tất cả AC trỏ chung “xem branch”; evidence không xác định.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** commit range chứa file ngoài NS-101. **Nguyên nhân:** stage cả repo hoặc branch reuse. **Chẩn đoán:** `git show --stat`/diff theo commit. **Sửa:** trước khi chia sẻ, sửa commit theo review policy; sau khi chia sẻ, dùng follow-up/revert có evidence thay vì force push. **Phòng tránh:** stage path có chủ đích và commit plan.
- **Dấu hiệu:** switch/merge bị chặn vì local changes. **Nguyên nhân:** dirty working tree. **Chẩn đoán:** `git status --short`. **Sửa:** commit hợp lệ, stash có ghi chú nếu policy cho phép, hoặc discard chỉ sau khi review diff. **Phòng tránh:** checkpoint clean-state.
- **Dấu hiệu:** sync xong AC trước đó fail. **Nguyên nhân:** develop thay đổi shared contract. **Chẩn đoán:** compare evidence trước/sau sync và affected artifact. **Sửa:** cập nhật feature trong scope hoặc escalate conflict; không merge khi oracle fail. **Phòng tránh:** sync đủ sớm và chạy consistency oracle.

#### OUT-U02-03 — Review, Definition of Done, merge về develop và dọn feature branch

**Mapping:** `OUT-U02-03` · `LO2.1`, `LO2.2` · `M-GF-02` · Artifact: review record, merge decision, containment và cleanup evidence.

##### Định nghĩa rõ ràng

**Review** là hoạt động xem xét scope, evidence, rủi ro và findings; NovaShop yêu cầu ít nhất một peer review theo team policy. **Definition of Done (DoD)** là commitment chất lượng cho Increment trong Scrum; item không đạt DoD không được coi là Increment Done. **Merge decision** là kết luận `PASS`/`REVISE` dựa trên DoD, findings và Git state. **Cleanup** xóa feature ref sau khi chứng minh feature tip đã nằm trong `develop`.

Ranh giới: pull request/merge request và branch policy không do Scrum Guide quy định; Sprint Review không phải branch merge gate bắt buộc. Một feature có thể có review record tốt nhưng chưa đạt DoD, hoặc đạt business acceptance nhưng dirty state/evidence khiến merge gate vẫn `REVISE`.

##### Vấn đề/vai trò và quyết định cần đưa ra

Reviewer phải quyết định merge có an toàn và minh bạch hay không. Inputs tối thiểu: source/target, included/excluded scope, DoD evidence, graph/containment, findings/disposition, clean state. Severity `error` chưa đóng luôn làm kết luận `REVISE` theo NovaShop policy.

##### Cơ chế và mental model

Review gate là hàm AND:

```text
branch/base đúng
AND acceptance evidence đầy đủ
AND DoD đạt
AND error findings = 0
AND working tree sạch
→ PASS; ngược lại REVISE
```

Sau PASS, merge `--no-ff` giữ merge boundary theo policy. Trước cleanup, `git branch --merged develop` phải liệt kê feature hoặc `git merge-base --is-ancestor <feature-tip> develop` phải exit 0. Xóa ref không xóa commit đã reachable.

##### Khi dùng / khi không dùng

Dùng review gate trước mọi merge vào `develop`. Không merge “để tester xem” nếu policy yêu cầu feature branch/review ref có thể kiểm trực tiếp. Không xóa branch trước khi lưu feature-tip/containment evidence. Không giữ branch đã merge chỉ vì sợ mất code; giữ evidence và graph, dọn ref theo policy.

Trade-off: `--no-ff` giúp audit feature boundary/revert theo group nhưng thêm merge commits. Cleanup giảm clutter nhưng branch label biến mất; vì vậy phải lưu review/merge evidence trước.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** NS-101 review phát hiện empty-state evidence thiếu.
- **Input/baseline/constraint:** branch/source đúng; keyword/filter PASS; finding E-01 severity error còn open.
- **Decision/action:** kết luận `REVISE`, không merge; sau khi artifact/evidence được bổ sung và finding đóng có evidence, review lại rồi mới PASS.
- **Artifact/output:** review record v1/v2, containment và cleanup output.
- **Expected result:** error open = 0 trước merge; `develop` chứa feature tip; source branch xuất hiện trong merged list trước safe delete.
- **Verification/oracle:** review table, `git status --short`, `git branch --merged develop`, `git merge-base --is-ancestor <saved-feature-tip> develop`.

##### Ví dụ triển khai trong Material — professional artifact

Đây là lớp gate/merge của `MEX-U02-01`. Lab `CP-U02-03` thay finding thành missing expired-promotion failure example. Assignment NS-202 dùng duplicate sandbox failure input và không có walkthrough.

##### Best practices

- **Rule:** chỉ merge khi review và DoD cùng PASS, error findings = 0. **Rationale:** `develop` là integration contract cho cả team. **Positive:** finding E-01 có fix commit/evidence và disposition `CLOSED` trước decision. **Negative:** ghi “sẽ bổ sung sau”, merge ngay; `develop` chứa work chưa Done.
- **Rule:** review record phải liên kết exact evidence, không chỉ “LGTM”. **Rationale:** future audit cần tái lập. **Positive:** AC-empty → evidence row → finding disposition → PASS. **Negative:** approval emoji không nêu scope/failure check.
- **Rule:** containment trước cleanup. **Rationale:** branch ref là điểm giữ tip; xóa sớm có thể làm audit khó và mất unmerged work. **Positive:** lưu tip SHA, merged list/exit 0 rồi `git branch -d`. **Negative:** dùng `-D` ngay sau review, sau đó phát hiện merge chưa xảy ra.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** merge decision PASS nhưng error finding còn open. **Nguyên nhân:** review được coi là ceremony. **Chẩn đoán:** đếm findings theo severity/status. **Sửa:** đổi `REVISE`, đóng finding bằng evidence rồi review lại. **Phòng tránh:** decision formula trong template.
- **Dấu hiệu:** `git branch -d` từ chối. **Nguyên nhân:** feature chưa contained hoặc current branch sai. **Chẩn đoán:** `git branch --show-current`, `git branch --merged develop`. **Sửa:** không dùng `-D`; quay lại merge/containment gate. **Phòng tránh:** cleanup checklist.
- **Dấu hiệu:** feature merged nhưng review record không nằm trong history. **Nguyên nhân:** record tạo sau merge hoặc chưa commit. **Chẩn đoán:** `git log -- <review-file>`. **Sửa:** ghi follow-up governance evidence theo policy và đánh dấu audit gap; không giả mạo thời điểm review. **Phòng tránh:** review record/final disposition là input merge.

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### MEX-U02-01 — Feature evidence pack cho NS-101 Product Search

**Stable ID:** `MEX-U02-01` · **LO:** `LO2.1`, `LO2.2` · **Outline:** `OUT-U02-01`–`03` · **Artifact type:** issue record, commit plan, review record và merge evidence.

### Input/trạng thái ban đầu

- `develop` từ M-GF-01, status sạch; `main` không đổi.
- PBI NS-101 / FR-01; target 0.1.0.
- Oracles: keyword reflected, selected filter visible, empty state observable.
- Constraints: local-only, no application code, no direct commit `main`/`develop`, error finding = 0 trước merge.

### Cách thực hiện

**1. Branch decision artifact**

| Field | Filled decision |
| --- | --- |
| Issue/requirement | NS-101 / FR-01 |
| Outcome | Người mua tìm/lọc catalog bằng input synthetic |
| Included | keyword, selected filter, empty state specification/evidence |
| Excluded | recommendation, production catalog, analytics implementation |
| Branch | `feature/NS-101-product-search` |
| Source → target | `develop` → `develop` |
| Exit | DoD + review PASS; contained; safe cleanup |

```text
git switch develop
git status --short
git rev-parse develop
git switch -c feature/NS-101-product-search
```

Saved `develop` SHA là base evidence. Status phải sạch trước branch creation.

**2. Commit plan và traceability**

| Intent | AC | Artifact | Expected change | Commit message |
| --- | --- | --- | --- | --- |
| Define behavior | keyword, filter | `features/NS-101/search-spec.md` | input/output rules cụ thể | `docs(NS-101): define search and filter behavior` |
| Record failure example | empty state | `features/NS-101/acceptance-evidence.csv` | zero-result case có expected message | `test(NS-101): record empty-state acceptance evidence` |
| Close review | all | `reviews/NS-101-review.md` | findings closed, decision PASS | `docs(NS-101): close feature review evidence` |

Các file được tạo bằng editor. Mỗi commit chỉ stage artifact của intent tương ứng. `type` phản ánh artifact work; issue ID làm scope. Conventional Commits không bắt buộc type `docs/test` cho mọi dự án — đây là NovaShop policy.

**3. Review record có failure path**

Review lần 1:

| Finding | Severity | Evidence | Status | Merge decision |
| --- | --- | --- | --- | --- |
| E-01 thiếu zero-result evidence | error | AC-empty row absent | OPEN | REVISE |

Không merge. Sau commit acceptance evidence, review lần 2 đóng E-01 bằng exact row/commit; DoD, status và scope đều PASS. Quyết định chuyển thành PASS.

**4. Merge và cleanup có guardrail**

```text
git status --short --branch
git switch develop
git merge --no-ff feature/NS-101-product-search -m "merge(NS-101): integrate product search artifacts"
git branch --merged develop
git branch -d feature/NS-101-product-search
```

Trước delete, lưu feature tip SHA và merged-list output. Sau delete, dùng saved SHA cho containment audit.

### Output mong đợi

- NS-101 đi `develop` → feature → `develop`; `main` vẫn baseline.
- Feature-only commits đều mang NS-101 và đúng artifact intent.
- Ba acceptance criteria có evidence; error open = 0 trước merge.
- Merge commit giữ boundary; feature ref được xóa an toàn sau containment.
- Working tree sạch; không secret/PII.

### Cách xác minh

```text
git status --short --branch
git log --graph --decorate --oneline --all
git log --oneline --decorate develop..feature/NS-101-product-search
git branch --merged develop
git merge-base --is-ancestor <saved-feature-tip-sha> develop
```

Oracle cuối: containment exit 0; review record có `PASS`, error open 0; traceability row cho keyword/filter/empty-state không rỗng. Failure behavior: nếu E-01 còn open, expected decision là `REVISE` và `develop` chưa nhận feature.

### Mapping Material worked example → Hands-on Lab tương ứng

- **MEX-U02-01** → **LAB-U02-01/CP-U02-01** (`LO2.1`, `LO2.2`): branch/base NS-102 từ `develop`.
- **MEX-U02-01** → **LAB-U02-01/CP-U02-02** (`LO2.1`, `LO2.2`): tự thiết kế commits/traceability cho promotion-expiry input.
- **MEX-U02-01** → **LAB-U02-01/CP-U02-03** (`LO2.1`, `LO2.2`): debug error finding, review lại, containment/cleanup.

Lab không copy NS-101: PBI, acceptance failure, artifact rows và commit decisions đều đổi.

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

| Dấu hiệu | Nguyên nhân | Chẩn đoán | Sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| feature sai base | branch từ `main`/stale ref | saved base + merge-base + graph | dừng; tạo work đúng từ `develop` nếu an toàn | capture develop SHA lúc tạo |
| commit không truy vết | message chung hoặc mixed scope | `git log develop..HEAD`, `git show --stat` | follow-up/rework theo shared-history policy | commit plan + issue scope |
| dirty state trước review | file chưa stage/untracked | `git status --short` | phân loại commit/discard sau khi xem diff | clean-state gate |
| sync gây regress artifact | shared contract đổi | evidence before/after sync | sửa trong scope hoặc escalate | sync sớm + recheck AC |
| PASS khi error open | gate logic sai | review finding count | REVISE, đóng bằng evidence | AND-gate template |
| branch cleanup bị chặn | chưa merged/current branch sai | merged list + current branch | quay lại containment; không `-D` | capture tip + safe delete |

## 6. Từ điển thuật ngữ và mô hình tư duy

| Thuật ngữ | Nghĩa |
| --- | --- |
| PBI | Item trong Product Backlog; không đồng nghĩa branch. |
| Acceptance criterion/oracle | Điều kiện business quan sát được cho scope PBI. |
| Feature branch | Supporting branch hữu hạn từ/đến `develop`. |
| Branch base | Commit của source tại điểm mở work, được lưu làm evidence. |
| Purposeful commit | Snapshot có một intent kiểm tra được. |
| Commit range | Tập commit có ở feature nhưng chưa có ở target. |
| Traceability | Chuỗi PBI/AC → commit → artifact/evidence → review. |
| Finding disposition | OPEN/CLOSED với evidence và rationale. |
| DoD | Commitment chất lượng cho Increment theo Scrum; cụ thể hóa theo team/product. |
| Containment | Feature tip reachable từ `develop` sau merge. |

Mental model: **branch đúng là điều kiện cần; evidence + DoD + review PASS mới là điều kiện đủ để merge**.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

- [Git Reference Manual 2.54.0](https://git-scm.com/docs/git/2.54.0).
- [Pro Git — Basic Branching and Merging](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging).
- [A successful Git branching model](https://nvie.com/posts/a-successful-git-branching-model/).
- [Conventional Commits 1.0.0](https://www.conventionalcommits.org/en/v1.0.0/).
- [Scrum Guide 2020](https://scrumguides.org/scrum-guide.html).
- `starter/NovaShop_Backlog.csv`, version 1.0, internal approved.

### Phần bổ sung/suy diễn

- **[BỔ SUNG — nguồn: Git/Conventional Commits/Scrum Guide]** Dossier, AND-gate và oracle mapping là cách vận hành NovaShop; `docs/test/merge` là team policy, không phải các type bắt buộc phổ quát.
- **[BỔ SUNG — nguồn: NovaShop synthetic backlog]** NS-101 artifacts, review finding E-01 và các SHA minh họa là dữ liệu đào tạo; không tuyên bố repo thật.

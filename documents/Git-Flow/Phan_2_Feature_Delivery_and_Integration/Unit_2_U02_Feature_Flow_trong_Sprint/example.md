# Unit U02: Feature Flow trong Sprint — Ví dụ và nghiên cứu tình huống

> **Case:** `CASE-U02-01` · **Milestone:** `M-GF-02` · **Authenticity:** simulated · **Validation:** artifact review

## 🎯 Learning Outcomes liên quan

- **LO2.1:** vận hành feature từ `develop` về `develop`, giữ traceability PBI–commit–review–acceptance evidence.
- **LO2.2:** đánh giá merge readiness theo DoD, findings và working state.

**Outline mapping:** `OUT-U02-01`, `OUT-U02-02`, `OUT-U02-03`.

## 🧭 Liên kết với ngữ cảnh nghề nghiệp/dự án

NS-101 Product Search đã có feature branch và hai commit artifact. Trong lúc feature được làm, `develop` nhận một glossary governance update. Review lần đầu phát hiện acceptance evidence cho empty state bị thiếu. Case minh họa quyết định **không merge khi tên branch/commits trông đúng nhưng gate chưa đạt**, sau đó sync, đóng finding và chứng minh containment.

Đây là failure-centered case riêng; Material MEX trình bày toàn bộ dossier end-to-end, còn case này tập trung vào review/sync decision dưới thay đổi `develop`.

## 🧰 Điều kiện chạy ví dụ

- Repo local cô lập, Git CLI 2.40+; current branch ban đầu `feature/NS-101-product-search`.
- Feature branch đã được một reviewer đọc; không rewrite SHA.
- Không có mã nguồn ứng dụng, remote hoặc credential; chỉ Markdown/CSV synthetic.
- `develop` chứa một commit glossary mới sau branch base; thay đổi này không mâu thuẫn nội dung nhưng phải được feature sync trước final review theo NovaShop policy.

## 📚 Nguồn đầu vào đã map

- SRC-GIT-DOC, SRC-PROGIT, SRC-NVIE — Git graph/feature flow.
- SRC-CONV — commit-message structure 1.0.0.
- SRC-SCRUM — Definition of Done trong Scrum Guide 2020.
- SRC-NS-DATA — NovaShop backlog synthetic version 1.0.

### Mapping case đã chốt trong course plan

| Case ID | LO | Outline | Increment | Authenticity |
| --- | --- | --- | --- | --- |
| CASE-U02-01 | LO2.1, LO2.2 | OUT-U02-01, OUT-U02-02, OUT-U02-03 | M-GF-02 | simulated |

## Case Study 01: NS-101 — Review bị chặn bởi empty-state evidence

### 1. Ticket và tiêu chí thành công

- **Stakeholders:** Product Owner cần FR-01 minh bạch; peer reviewer bảo vệ integration contract của `develop`.
- **Ticket:** NS-101 — tìm kiếm và lọc sản phẩm.
- **Acceptance oracles:** keyword phản ánh trong kết quả; filter đang chọn hiển thị; query không có kết quả tạo empty state quan sát được.
- **Initial finding:** `E-01`, severity `error`, missing evidence cho empty state.
- **Constraints:** feature đã được reviewer fetch; không rebase/force push; không merge khi error còn open; sync `develop` trước review cuối.
- **Success:** commit range chỉ chứa NS-101; traceability đủ ba oracle; E-01 closed; status sạch; feature contained trong `develop`; safe cleanup có evidence.

### 2. Input, trạng thái ban đầu và ràng buộc

Graph shape:

```text
* 91d2e40 (feature/NS-101-product-search) docs(NS-101): define filter behavior
* 735bca1 docs(NS-101): define keyword behavior
| * 3f4aa60 (develop) docs(M-GF-01): clarify product glossary
|/
* 07ae8cd feature base
* 5d0b7b1 (main, tag: baseline-0.0.0) baseline
```

Traceability trước review:

| Criterion | Commit | Artifact/evidence | Status |
| --- | --- | --- | --- |
| keyword | `735bca1` | search-spec row KEYWORD | PASS |
| selected filter | `91d2e40` | search-spec row FILTER | PASS |
| empty state | không có | không có | FAIL |

Working tree sạch. Branch name/source decision đúng, nhưng `develop` đã tiến và DoD “mọi acceptance criterion có evidence” chưa đạt.

### 3. Phân tích lựa chọn

**Merge ngay rồi bổ sung trên `develop`:** bị loại vì biến integration branch thành nơi hoàn thiện feature và vi phạm error-finding gate.

**Rebase feature lên `develop`:** có thể tạo graph tuyến tính nhưng rewrite hai SHA mà reviewer đã fetch. Điều này vi phạm constraint shared history.

**Merge `develop` vào feature, recheck rồi đóng finding:** giữ SHA feature đã chia sẻ và đưa glossary update vào review context; trade-off là có thêm merge commit. Đây là lựa chọn được dùng.

**Không sync vì glossary không conflict:** giảm một merge commit nhưng bỏ qua policy final-sync và không chứng minh feature đã được review trên integration state mới. Với case này, lựa chọn không đạt team agreement.

### 4. Cách triển khai

#### 4.1 Ghi review decision trước thay đổi

`reviews/NS-101-review.md`:

| Field | Giá trị |
| --- | --- |
| Source → target | `feature/NS-101-product-search` → `develop` |
| Base evidence | `07ae8cd` |
| Finding | E-01 / error / empty-state evidence absent |
| Working state | clean |
| DoD | FAIL: acceptance evidence incomplete |
| Decision | REVISE; merge prohibited |

Review record được commit trên feature để lịch sử thể hiện gate đã diễn ra trước merge.

#### 4.2 Đồng bộ không rewrite

```text
git status --short --branch
git switch feature/NS-101-product-search
git merge develop -m "merge(NS-101): sync develop before final review"
```

Sau merge, kiểm glossary constraint vẫn nhất quán trong search spec. Vì không có content conflict, Git merge thành công; vẫn phải review diff/acceptance, không suy ra chất lượng chỉ từ exit code.

#### 4.3 Đóng đúng finding

Feature bổ sung `features/NS-101/acceptance-evidence.csv` với một row synthetic:

| case_id | input | selected_filter | expected_observable |
| --- | --- | --- | --- |
| NS101-EMPTY-01 | `nomatch-synthetic` | `brand=NovaDemo` | empty-state message; selected filter remains visible |

Commit:

```text
git add features/NS-101/acceptance-evidence.csv
git commit -m "test(NS-101): record empty-state acceptance evidence"
```

Review record được cập nhật: E-01 `CLOSED`, evidence row + commit SHA; DoD PASS; error open = 0; final decision PASS. Review update cũng được commit trước merge.

#### 4.4 Merge và containment

Lưu feature-tip SHA, rồi:

```text
git status --short --branch
git switch develop
git merge --no-ff feature/NS-101-product-search -m "merge(NS-101): integrate product search artifacts"
git branch --merged develop
git merge-base --is-ancestor feature/NS-101-product-search develop
git branch -d feature/NS-101-product-search
```

Merged-list và containment được lưu **trước** cleanup. Xóa branch bằng `-d`, không `-D`.

### 5. Output mong đợi

- `develop` có glossary update, merge-sync history và toàn bộ NS-101 artifacts.
- `main`/baseline tag không đổi.
- Review chronology thể hiện `REVISE` trước, `PASS` sau khi E-01 có evidence.
- Feature tip reachable từ `develop`; feature ref được dọn an toàn.
- Traceability đủ ba rows; status sạch; không PII/secret.

Graph có một merge boundary cho feature và có thể có merge-sync node bên trong feature. Đây là trade-off có chủ đích để không rewrite shared SHA.

### 6. Cách xác minh

| Check | Command/artifact | PASS oracle |
| --- | --- | --- |
| Working state | `git status --short --branch` | current `develop`, không changed file |
| Scope | `git log --oneline <feature-base-sha>..<saved-feature-tip-sha>` | intents liên quan NS-101 hoặc sync develop có giải thích |
| Base | branch decision + graph | base là `develop` commit tại lúc mở feature |
| Traceability | three-row matrix | keyword/filter/empty-state đều có commit + evidence |
| Finding gate | review record | E-01 closed trước PASS; open error = 0 |
| Containment | `git merge-base --is-ancestor <saved-feature-tip-sha> develop` | exit code 0 |
| Cleanup | refs/branch list | source ref không còn sau safe delete |
| Main isolation | `git log --oneline main..develop` và graph | NS-101 ở `develop`, không direct commit `main` |

### 7. Giải thích sâu và failure modes

- **Merge develop conflict:** dấu hiệu `git status` có unmerged paths; nguyên nhân glossary và search spec chạm cùng vùng; chẩn đoán bằng conflict markers/diff; sửa bằng quyết định giữ cả business contracts, stage và commit; nếu chưa chắc, `git merge --abort`; phòng tránh sync nhỏ/sớm.
- **Evidence row có nhưng không map commit:** finding chưa thật sự closed; thêm exact SHA/artifact row vào review/traceability rồi review lại; phòng tránh yêu cầu evidence locator trong template.
- **Status dirty trước merge:** file review chưa commit hoặc output evidence mới; phân loại/stage commit đúng intent, hoặc loại file ngoài scope sau khi xem diff; không merge dirty state.
- **Containment fail:** merge chưa xảy ra hoặc kiểm sai saved tip; không cleanup và không dùng `-D`; đọc graph/merged list rồi sửa merge process.
- **Reviewer đã fetch nhưng người thực hiện rebase:** SHA trong review mồ côi; không force push để che; ghi incident/audit gap và phối hợp chiến lược phục hồi. Phòng tránh ghi shared-history status trong issue record.

Giới hạn: case không dạy conflict resolution chi tiết hoặc rebase strategy; U03 xử lý các chủ đề đó.

### 8. Bài học chuyển giao

- Readiness là phép AND, không phải “đa số gate đã pass”.
- Sync choice phụ thuộc ownership/shared history, không phụ thuộc sở thích graph.
- Finding chỉ được đóng bằng exact evidence; commit message không thay acceptance oracle.
- Containment phải được chứng minh trước cleanup.
- Lab chuyển sang NS-102/Cart Promotion và lỗi expired-code; Assignment chuyển sang NS-202/payment duplicate failure, vì vậy người học phải transfer thay vì lặp case.

## Provenance của các case

### Nguồn được dùng

- [Git Reference Manual 2.54.0](https://git-scm.com/docs/git/2.54.0).
- [Pro Git — Basic Branching and Merging](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging).
- [A successful Git branching model](https://nvie.com/posts/a-successful-git-branching-model/).
- [Conventional Commits 1.0.0](https://www.conventionalcommits.org/en/v1.0.0/).
- [Scrum Guide 2020](https://scrumguides.org/scrum-guide.html).
- NovaShop Backlog version 1.0, internal approved.

### Phần bổ sung/suy diễn

- **[BỔ SUNG — nguồn: mapped Git/Scrum sources]** Review chronology, AND-gate và sync decision record là cách hiện thực hóa policy NovaShop.
- **[BỔ SUNG — nguồn: NovaShop synthetic data]** SHA, evidence row và finding E-01 đều là fixture mô phỏng, không phải lịch sử dự án thật.

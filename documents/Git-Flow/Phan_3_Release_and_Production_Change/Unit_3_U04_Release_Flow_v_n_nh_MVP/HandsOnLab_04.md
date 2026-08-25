# Hands-on Lab LAB-U04-01 — Phát hành Order Tracking và Admin cơ bản

> **Thời lượng:** 75 phút · **Độ khó:** medium · **Mode:** guided with fading · **Mức xác thực:** simulated

## 🎯 Learning Outcomes được thực hành

- **LO4.1:** cắt/ổn định release, merge main, back merge develop và đóng branch đúng gate.
- **LO4.2:** lập compatibility/version evidence và tạo/kiểm annotated tag.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

| MEX | Checkpoint | Changed input/failure | Evidence |
| --- | --- | --- | --- |
| MEX-U04-01 | CP-U04-01 | Order Tracking + Admin; UAT wording `Delivered`; late Bulk Export | dossier, UAT recheck, annotated tag query |
| MEX-U04-01 | CP-U04-02 | tự lập traceability và prove exact tagged commit on main | tag audit, main containment, scope matrix |
| MEX-U04-01 | CP-U04-03 | quan sát develop containment FAIL trước back merge rồi đưa về PASS | failure/recovery graph, decision note |

## 🧭 Bối cảnh nghề nghiệp/dự án và project increment

Tại **M-GF-04**, candidate gồm Search, Cart, Checkout, Payment, Order Tracking (`NS-104`) và Admin cơ bản (`NS-105`). UAT phát hiện text `Delivered` đang gắn cho `OUT_FOR_DELIVERY`, dù đơn chưa bàn giao. Sponsor đề nghị thêm Bulk Export sau freeze. Oracle: wording fix được phép; Bulk Export trở lại Product Backlog; annotated `v0.1.0` phải thuộc `main` và `develop` sau back merge.

## 🧰 Điều kiện bắt đầu

### Kiến thức/kỹ năng tiên quyết

- Hoàn thành U03, đọc MEX-U04-01 và CASE-U04-01.
- Biết kiểm graph/containment và resolve conflict theo business oracle.

### Môi trường, công cụ và phiên bản

- Clone Lab local riêng; Git 2.40+; Markdown/CSV editor.
- `main`, `develop` tồn tại; working tree sạch; `v0.1.0` chưa tồn tại.
- Không deploy/remote production, credential, PII hoặc mã nguồn ứng dụng.

### Starter assets

- `starter/NovaShop_Project_Brief.md`
- `starter/NovaShop_Backlog.csv`, NS-104/NS-105
- `starter/NovaShop_Change_Cards.md`, CARD-U04-LAB
- `starter/templates/GitFlow_Artifact_Templates.md`, Release Readiness và Tag Audit

### Input/trạng thái ban đầu

`develop` có acceptance evidence PASS cho NS-101/102/103/202 và hai artifact Done sau. Lưu glossary tại `project-artifacts/order-tracking/order-status-glossary.csv`:

```csv
status_id,display_text,meaning,requirement_ref
ORDER_PLACED,Order placed,Order artifact has been accepted,FR-04
OUT_FOR_DELIVERY,Delivered,Courier has the package but customer has not received it,FR-04
DELIVERED,Delivered,Customer delivery has been confirmed,FR-04
```

Lưu Admin scope tại `project-artifacts/admin/admin-basic-scope.md`:

```text
ADMIN-PRODUCT-UPDATE | update product/stock | audit owner required | FR-05 | PASS
ADMIN-ORDER-STATE    | update order status  | audit owner required | FR-05 | PASS
```

Nếu clone từ U03 chưa có hai artifact, dùng editor tạo đúng hai input block trên qua feature flow sau; không direct commit `develop`:

```text
git switch develop
git switch -c feature/NS-104-order-tracking
git add project-artifacts/order-tracking/order-status-glossary.csv
git commit -m "docs(NS-104): add order status glossary"
git switch develop
git merge --no-ff feature/NS-104-order-tracking -m "merge(NS-104): integrate order tracking artifact"
git switch -c feature/NS-105-admin-basic
git add project-artifacts/admin/admin-basic-scope.md
git commit -m "docs(NS-105): add basic admin scope"
git switch develop
git merge --no-ff feature/NS-105-admin-basic -m "merge(NS-105): integrate admin artifact"
```

Đối chiếu acceptance rows với backlog rồi ghi review PASS cho fixture trước khi cắt release.

### Ràng buộc và phạm vi được phép thay đổi

- Release branch bắt đầu từ exact `develop` cut point.
- Sau freeze chỉ sửa UAT wording/metadata; Bulk Export không được vào released tree.
- Status IDs/columns là compatibility contract; wording mô tả được sửa nếu meaning/ID không đổi.
- Tag chỉ tạo sau readiness PASS; không xóa/di chuyển tag để che lỗi.
- Reset chỉ tác động clone Lab xác định.

## 📚 Nguồn đầu vào đã map

Git Reference Manual 2.54.0; Vincent Driessen Git branching model; SemVer 2.0.0; Scrum Guide 2020; NovaShop synthetic assets.

## 📋 Lab outline và Definition of Done

### Các mốc phải đạt

- CP0: preflight, baseline và cut point có evidence.
- CP-U04-01: frozen scope/UAT fix/readiness PASS và annotated tag tồn tại.
- CP-U04-02: exact tag commit thuộc `main`, traceability không mồ côi.
- CP-U04-03: failure-before-back-merge được khôi phục; tag commit thuộc `develop`; branch đóng.
- Final validation và evidence pack PASS.

### Checkpoint đã hoạch định từ course plan

| ID | MEX ref | Verify | Expected |
| --- | --- | --- | --- |
| CP-U04-01 | MEX-U04-01 | `git tag -n --list v0.1.0` | annotation mô tả release hiện diện |
| CP-U04-02 | MEX-U04-01 | `git merge-base --is-ancestor v0.1.0 main` | exit 0 |
| CP-U04-03 | MEX-U04-01 | `git merge-base --is-ancestor v0.1.0 develop` | exit 0 sau back merge |

### Definition of Done

- Frozen scope include NS-101/102/103/104/105/202; Bulk Export excluded có owner/disposition.
- UAT wording finding có before→fix→recheck PASS; ID/meaning/columns không đổi.
- Tag type=`tag`, exact tag commit contained trong `main` và `develop`.
- Release branch đóng sau gates; working tree sạch; không secret/PII.

## 🪜 Các bước dự kiến và mức hướng dẫn

- CP0/CP-U04-01: hướng dẫn đầy đủ.
- CP-U04-02: học viên tự chọn evidence layout theo oracle.
- CP-U04-03: failure/recovery có gợi ý giảm dần, không cung cấp Assignment solution.

## Checkpoint 0 — Baseline và safety check

### Why

Release name chỉ đáng tin khi exact cut point, scope evidence và tag namespace được kiểm trước mutation.

### Action

1. Chạy preflight:

   ```text
   git --version
   git status --short --branch
   git branch --list main develop
   git tag --list v0.1.0
   git log --graph --decorate --oneline --all
   ```

2. Xác nhận NS-104/NS-105 artifact và acceptance evidence có trên `develop`. Lưu `git rev-parse develop` làm D-cut.
3. Tạo release branch từ exact `develop`:

   ```text
   git switch develop
   git switch -c release/0.1.0
   git rev-parse HEAD
   ```

4. Trong `project-artifacts/M-GF-04/release-dossier-v0.1.0.md`, ghi included scope, evidence refs và Bulk Export là `EXCLUDE — capability mới, chưa Done, quay lại Product Backlog`; sau đó lưu frozen baseline:

   ```text
   git add project-artifacts/M-GF-04/release-dossier-v0.1.0.md
   git commit -m "docs(release): freeze NovaShop v0.1.0 scope"
   ```

### Explanation

`release/0.1.0` và `develop` phải cùng object ID tại cut. Scope manifest là semantic boundary; branch command không tự ngăn sponsor thêm feature.

### Verify

```text
git merge-base --is-ancestor develop release/0.1.0
git status --short --branch
```

### Expected result

Tại thời điểm cut, release tip bằng recorded D-cut; scope table có six included IDs và một explicitly excluded request; working tree sạch sau khi commit dossier baseline.

### Evidence

Lưu preflight, D-cut, frozen-scope table và status trong `evidence/LAB-U04-01/CP0/`.

### Troubleshooting

- Tag đã tồn tại: dừng và dùng clone Lab mới; không delete tag.
- NS-104/105 chưa Done: không đưa vào release; hoàn tất fixture/prerequisite qua feature flow hoặc xin baseline đúng.
- Release branch từ ref sai: chưa share thì bỏ clone Lab và tạo lại; không rewrite shared refs.

### Reset/rollback

Bỏ clone Lab hiện tại và tạo clone mới từ baseline đã xác định. Không xóa repository khóa học hoặc recursive-delete đường dẫn chưa kiểm chứng.

## Checkpoint 1 — CP-U04-01: Scope freeze, UAT fix, main merge và annotated tag

**Material example refs:** MEX-U04-01 · **LO:** LO4.1, LO4.2

### Why

Checkpoint tái tạo MEX với contract Order Tracking khác: cùng text `Delivered` đang diễn đạt hai states khác nhau. Release fix phải sửa wording mà không đổi published status ID/meaning.

### Action

1. Ghi UAT finding với tested release ref, expected `OUT_FOR_DELIVERY` khác `DELIVERED`, observed wording và verdict REVISE.
2. Trên release branch, đổi riêng `display_text` của `OUT_FOR_DELIVERY` thành `Out for delivery`; giữ ID, meaning, requirement ref và row `DELIVERED`. Ghi compatibility diff và commit:

   ```text
   git add project-artifacts/order-tracking/order-status-glossary.csv project-artifacts/M-GF-04/release-dossier-v0.1.0.md
   git commit -m "fix(RC-U04): correct out-for-delivery wording"
   ```

3. Re-run artifact UAT trên exact release tip; ghi expected/observed PASS, candidate ID và overall readiness. Chỉ khi mọi blocking row PASS mới tiếp tục.
4. Merge release vào main và tạo annotated tag:

   ```text
   git switch main
   git merge --no-ff release/0.1.0 -m "merge(release): publish NovaShop v0.1.0"
   git tag -a v0.1.0 -m "NovaShop v0.1.0; Order Tracking and Admin; UAT PASS"
   ```

### Explanation

Wording correction đóng finding của scope hiện có; Bulk Export tạo capability mới nên bị loại. Tag được tạo trên `main` sau readiness PASS, không trên release tip trước main merge. Annotated object mang release message và peel tới exact main commit.

### Verify

```text
git tag -n --list v0.1.0
git cat-file -t v0.1.0
git rev-parse v0.1.0^{commit}
git status --short --branch
```

### Expected result

Tag annotation mô tả release; object type là `tag`; peeled target bằng current released `main` commit; status sạch. Dossier thể hiện UAT REVISE→fix→recheck PASS và Bulk Export absent.

### Evidence

Nộp frozen-scope diff, UAT before/after, compatibility diff, readiness table, main merge graph, tag annotation/type/target trong `evidence/LAB-U04-01/CP-U04-01/`.

### Troubleshooting

- Tag command chạy khi dossier còn REVISE: không tiếp tục/backfill evidence; dùng clone sạch và tái chạy đúng gate.
- `cat-file -t` trả `commit`: lightweight tag; không tuyên bố PASS hoặc di chuyển tag đã published.
- Merge main có file ngoài release ledger: dừng, lưu evidence, review cut-to-tip diff.

### Reset/rollback

Trước main merge, release edit chưa commit có thể khôi phục exact file bằng `git restore -- <path>`. Sau main/tag mutation, reset hợp lệ của Lab là dùng clone sạch; không xóa/move release tag để che lần chạy sai.

## Checkpoint 2 — CP-U04-02: Tag audit, main containment và release traceability

**Material example refs:** MEX-U04-01 · **LO:** LO4.1, LO4.2

### Why

Tag có đúng tên chưa chứng minh đúng object/commit/scope. Reviewer phải đi từ PBI và UAT evidence tới exact tagged tree trên `main`.

### Action

1. Lập Release traceability matrix cho six included IDs và wording fix: requirement, acceptance evidence, release commit/ref, tag và verdict.
2. Chứng minh excluded Bulk Export không có release commit/changelog entry và có backlog disposition.
3. Lưu tag object type, annotation, peeled commit, main containment và graph. Tự ghi PASS/REVISE cho từng row.

### Explanation

Checkpoint giảm hướng dẫn: learner chọn layout, nhưng không được dùng tag message như bằng chứng duy nhất. Exact target/ancestry và artifact tree phải khớp dossier.

### Verify

```text
git merge-base --is-ancestor v0.1.0 main
git branch --contains v0.1.0
git show --no-patch --decorate v0.1.0
git log --graph --decorate --oneline --all
```

### Expected result

Ancestor check exit 0; `main` contains tag commit; annotation/release commit/dossier cùng version/scope; traceability matrix không orphan link.

### Evidence

Nộp Release traceability matrix, `tag-audit.txt`, `main-containment.txt`, graph và reviewer checklist trong `evidence/LAB-U04-01/CP-U04-02/`.

### Troubleshooting

- Tag target không chứa final dossier/fix: candidate drift hoặc tag sớm; verdict REVISE và clone lại.
- Matrix có PBI không có acceptance evidence: item không đủ release scope; không điền “PASS” bằng commit tồn tại.
- `branch --contains` thiếu main: kiểm tag peeling/graph và source→target merge.

### Reset/rollback

Checkpoint đọc refs/tạo evidence. Sửa evidence artifact nếu mapping sai nhưng giữ raw outputs. Topology/tag sai yêu cầu clone Lab mới, không rewrite/move tag.

## Checkpoint 3 — CP-U04-03: Failure trước back merge, recovery và đóng release branch

**Material example refs:** MEX-U04-01 · **LO:** LO4.1, LO4.2

### Why

Ngay sau tag, exact main merge commit thường chưa thuộc `develop`. Quan sát failure này chứng minh vì sao back merge là continuity gate, không phải thao tác trang trí.

### Action

1. Trước back merge, chạy develop containment check và lưu exit/result là failure evidence; không giả vờ PASS.
2. Đánh giá graph và chọn route đáp ứng course oracle: released `main` phải trở thành ancestor của `develop`.
3. Thực hiện back merge. Nếu conflict, dùng U03 conflict record/oracle; không chọn một phía mặc định:

   ```text
   git switch develop
   git merge --no-ff main -m "chore(release): back-merge v0.1.0 into develop"
   ```

4. Rerun containment/tag/fix checks. Chỉ sau all PASS mới đóng local release branch:

   ```text
   git branch -d release/0.1.0
   ```

### Explanation

Before-state exit 1 là expected negative test. Back merge đưa exact tagged main commit và release-only wording fix vào future line. `branch -d` an toàn hơn `-D`: Git từ chối nếu branch chưa được merge theo ancestry mà nó kiểm.

### Verify

Before recovery:

```text
git merge-base --is-ancestor v0.1.0 develop
```

After recovery/close:

```text
git merge-base --is-ancestor v0.1.0 develop
git branch --contains v0.1.0
git branch --list release/0.1.0
git status --short --branch
```

### Expected result

Before-state exit 1 và verdict REVISE; after-state exit 0; `main`/`develop` contain tag commit; release branch query empty; status sạch. Decision note giải thích failure→cause→back merge→prevention.

### Evidence

Nộp before/after containment, back-merge graph/diff, conflict record nếu có, closed-branch output và troubleshooting note trong `evidence/LAB-U04-01/CP-U04-03/`.

### Troubleshooting

- Back merge conflict: lưu status/diff; resolve theo AC/compatibility oracle hoặc `git merge --abort` nếu thiếu authority.
- `branch -d` từ chối: containment/merge chưa thỏa; không dùng `-D` để vượt gate.
- Develop check vẫn fail: graph cho thấy main merge commit chưa là ancestor; kiểm merge direction/commit completion.

### Reset/rollback

Merge đang dở: lưu evidence rồi `git merge --abort`. Tag/topology sai sau publication simulation: dùng clone Lab mới. Không force-push `main`/`develop`, không move/delete tag để sửa evidence.

## 🧪 Final validation

```text
git tag -n --list v0.1.0
git cat-file -t v0.1.0
git merge-base --is-ancestor v0.1.0 main
git merge-base --is-ancestor v0.1.0 develop
git branch --contains v0.1.0
git branch --list release/0.1.0
git log --graph --decorate --oneline --all
git status --short --branch
```

Final PASS khi tag annotated; two ancestor checks exit 0; main/develop contained; release branch đóng; working tree sạch; dossier/matrix chứng minh scope, UAT, contract/version và Bulk Export exclusion.

## 📦 Bằng chứng và deliverables

1. Git evidence pack: preflight, cut, main/tag/back-merge graph, before/after containment, close/status.
2. Release dossier v0.1.0: frozen scope, UAT, compatibility/version, readiness, known limitations.
3. Release traceability matrix v0.1.0.
4. Decision/troubleshooting note và checklist PASS/REVISE.

Không nộp `.git`, remote URL, email thật, credential hoặc PII.

## ♻️ Reset, cleanup và khả năng chạy lại

- Trước merge: khôi phục exact uncommitted artifact bằng `git restore -- <path>`.
- Merge dở: `git merge --abort` sau khi lưu evidence.
- Tag/main/develop sai: bỏ clone Lab đã xác định và tạo clone mới; không rewrite shared refs/tag.
- Cleanup đạt khi không merge in progress, status sạch, evidence đã sao lưu và release branch chỉ bị đóng sau audit.

## 🔁 Artifact được tái sử dụng ở đâu

- ASM-GF-03 dùng kỹ năng/dossier structure nhưng change request RC-401 độc lập.
- ASM-GF-04 dùng release dossier/matrix làm production baseline cho hotfix.
- CAP-GF-01 tái dùng annotated-tag và dual-line containment defense.

## 🔐 Chính sách lời giải

Lab giải Order Tracking/Admin card. Assignment dùng baseline/output khác và yêu cầu learner tự quyết định release candidate dossier; không có final RC-401 solution trong file này.

## 📚 Provenance phần bổ sung

### Nguồn đã map

Git Reference Manual 2.54.0; Vincent Driessen; Semantic Versioning 2.0.0; Scrum Guide 2020; NovaShop synthetic assets.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — từ kiến thức đã huấn luyện]** Inline glossary/admin fixture và Bulk Export request là dữ liệu đào tạo synthetic.
- **[BỔ SUNG — nguồn: Git Reference Manual 2.54.0]** Negative containment test, annotated tag object audit và safe branch deletion được dùng làm observable oracles.

---
<!-- QUALITY GATE: MEX-U04-01 map CP-U04-01..03; mỗi checkpoint có numbered microsteps + Why/Action/Explanation/Verify/Expected/Evidence/Troubleshooting/Reset; failure-before-back-merge và recovery thật; không lộ ASM-GF-03 solution. -->

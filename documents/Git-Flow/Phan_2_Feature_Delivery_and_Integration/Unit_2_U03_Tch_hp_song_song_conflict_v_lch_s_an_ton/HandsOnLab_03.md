# Hands-on Lab LAB-U03-01 — Tích hợp Checkout và Payment sandbox với conflict có chủ đích

> **Thời lượng:** 75 phút · **Độ khó:** medium · **Mode:** guided with fading · **Mức xác thực:** simulated

## 🎯 Learning Outcomes được thực hành

- **LO3.1:** chẩn đoán và giải quyết conflict mà vẫn giữ acceptance criteria của Checkout và Payment.
- **LO3.2:** chọn no-fast-forward/merge thay vì rewrite một branch đã chia sẻ, rồi chứng minh topology bằng evidence.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

| Material example | Lab checkpoint | Biến đổi bắt buộc | Evidence |
| --- | --- | --- | --- |
| MEX-U03-01 | CP-U03-01 | Cart × Checkout đổi thành Checkout × Payment; status IDs và artifact khác | conflict map, resolved diff, `git diff --check` |
| MEX-U03-01 | CP-U03-02 | Tự đóng gói topology/traceability thay vì dùng graph mẫu | graph trước/sau, feature-tip containment, review verdict |
| MEX-U03-01 | CP-U03-03 | Chèn duplicate ID cục bộ để quan sát semantic failure rồi khôi phục | failure/recovery evidence và prevention rule |

Lab không dùng tình huống `changed_by` của ASM-GF-02 và không cung cấp canonical audit-field solution.

## 🧭 Bối cảnh nghề nghiệp/dự án và project increment

Tại **M-GF-03**, hai feature từ cùng baseline cùng thay ma trận trạng thái payment:

- Checkout `NS-103` cần `ADDRESS_INVALID`, yêu cầu lỗi validation giữ input.
- Payment `NS-202` cần `DECLINED_RETRYABLE`, yêu cầu failure code sandbox cho phép retry và giữ input.

Hai thay đổi cố ý thay cùng row `CHANGE_SLOT`, do đó merge thứ hai tạo conflict. Business oracle yêu cầu cả hai status tồn tại, ID duy nhất, nghĩa cũ không đổi và `input_behavior=PRESERVE`. Increment cuối Lab là Git evidence pack, ma trận đã tích hợp và conflict decision note; chúng được ASM-GF-02 và Capstone tái sử dụng như mẫu evidence, không như lời giải.

## 🧰 Điều kiện bắt đầu

### Kiến thức/kỹ năng tiên quyết

- Hoàn thành U02; biết tạo/switch feature branch, commit và merge `--no-ff`.
- Đã đọc `MEX-U03-01` nhưng chưa sao chép resolved artifact của ví dụ.
- Có thể chỉnh CSV UTF-8 và đọc acceptance oracle.

### Môi trường, công cụ và phiên bản

- Bản sao Git local dành riêng cho Lab; không thao tác trên repository khóa học gốc.
- Git CLI 2.40+; Markdown/CSV editor.
- Không remote production, credential thật, mã nguồn ứng dụng hoặc dữ liệu khách hàng.

### Starter assets

- `starter/NovaShop_Project_Brief.md`
- `starter/NovaShop_Backlog.csv`
- `starter/NovaShop_Change_Cards.md`, mục CARD-U03-LAB
- `starter/templates/GitFlow_Artifact_Templates.md`, mục Conflict Decision Record

### Input/trạng thái ban đầu

`develop` sạch và chứa artifact baseline sau (nếu repo U02 chưa có, CP0 đưa baseline vào qua một feature branch setup, không direct-commit `develop`):

```csv
status_id,domain,customer_meaning,input_behavior,requirement_ref
PENDING,PAYMENT,Payment is pending,PRESERVE,FR-03
VALIDATION_ERROR,CHECKOUT,Checkout input needs review,PRESERVE,FR-03
CHANGE_SLOT,UNASSIGNED,Reserved for one approved status,PRESERVE,NONE
```

Hai changed inputs của Lab:

```csv
ADDRESS_INVALID,CHECKOUT,Shipping address is invalid,PRESERVE,FR-03
DECLINED_RETRYABLE,PAYMENT,Payment was declined and retry is allowed,PRESERVE,FR-03
```

### Ràng buộc và phạm vi được phép thay đổi

- Chỉ sửa `project-artifacts/checkout/payment-status.csv`, conflict decision note và evidence của Lab.
- Hai feature phải tách từ cùng baseline trước khi feature nào được merge.
- `feature/NS-103-checkout` được coi là đã peer fetch sau commit; từ thời điểm đó không rebase/force-push.
- Không chọn `ours` hoặc `theirs` nguyên khối; result phải qua uniqueness/meaning oracle.
- Reset chỉ tác động bản sao Lab; không xóa/sửa repository khóa học.

## 📚 Nguồn đầu vào đã map

- Git Reference Manual 2.54.0: merge, status, diff, merge-base và restore.
- Pro Git, 2nd Edition và mô hình Git Flow của Vincent Driessen.
- Scrum Guide 2020 cho ranh giới Definition of Done; branch workflow là team policy.
- NovaShop project brief/backlog/change card synthetic.

## 📋 Lab outline và Definition of Done

### Các mốc phải đạt

- CP0: repo/baseline an toàn, hai feature bắt đầu từ cùng commit.
- CP-U03-01: conflict được chẩn đoán và resolve theo business oracle.
- CP-U03-02: graph, containment và traceability evidence tái lập được.
- CP-U03-03: semantic failure được phát hiện, khôi phục và ghi prevention rule.
- Final validation: working tree sạch, marker bằng 0, cả feature tip thuộc `develop`.

### Checkpoint đã hoạch định từ course plan

| ID | MEX ref | Verify | Expected |
| --- | --- | --- | --- |
| CP-U03-01 | MEX-U03-01 | `git diff --check` | không còn whitespace/conflict marker do Git phát hiện |
| CP-U03-02 | MEX-U03-01 | `git log --graph --decorate --oneline --all` | topology và merge point giải thích được |
| CP-U03-03 | MEX-U03-01 | `git merge-base --is-ancestor feature/NS-103-checkout develop` | exit 0; Checkout tip thuộc lịch sử `develop` |

### Definition of Done

- Ba checkpoint đạt expected result và có evidence riêng.
- Ma trận giữ đúng hai status mới, mỗi ID một lần, nghĩa/status cũ không đổi.
- Conflict decision note có merge base, AC at risk, options, rationale, owner, before/after evidence và prevention rule.
- Không rebase/force-push shared branch; graph và containment tái lập được.
- Working tree sạch, không secret/PII và reset không chạm repo gốc.

## 🪜 Các bước dự kiến và mức hướng dẫn

- **CP0 và CP-U03-01:** hướng dẫn đầy đủ để học cơ chế.
- **CP-U03-02:** giảm bớt lệnh, học viên tự chọn cách đóng gói evidence nhưng phải đạt oracle.
- **CP-U03-03:** cung cấp failure stimulus và pass/fail oracle; học viên tự viết chẩn đoán/prevention.

## Checkpoint 0 — Baseline và safety check

### Why

Conflict chỉ có ý nghĩa khi biết rõ common baseline và không có thay đổi ngoài scope. Setup qua feature branch giữ working agreement “không direct commit vào develop”.

### Action

1. Chạy preflight:

   ```text
   git --version
   git status --short --branch
   git branch --list main develop
   git config --get user.name
   git config --get user.email
   ```

2. Nếu `payment-status.csv` chưa tồn tại, switch `develop`, tạo `feature/LAB-U03-payment-status-baseline`, dùng editor tạo đúng baseline CSV ở mục Input, rồi commit:

   ```text
   git switch develop
   git switch -c feature/LAB-U03-payment-status-baseline
   git add project-artifacts/checkout/payment-status.csv
   git commit -m "docs(LAB-U03): add payment status conflict baseline"
   git switch develop
   git merge --no-ff feature/LAB-U03-payment-status-baseline -m "merge(LAB-U03): add payment status baseline"
   ```

3. Ghi common baseline bằng `git rev-parse develop`. Từ baseline này, tạo Checkout branch, nhưng chưa edit:

   ```text
   git switch -c feature/NS-103-checkout
   git switch develop
   git switch -c feature/NS-202-payment-failure
   ```

4. Xác nhận hai branch có cùng tip rồi trở lại Checkout:

   ```text
   git rev-parse feature/NS-103-checkout
   git rev-parse feature/NS-202-payment-failure
   git switch feature/NS-103-checkout
   ```

### Explanation

Tạo cả hai branch trước khi sửa bảo đảm chúng có cùng merge base. Object IDs của hai lệnh `rev-parse` phải giống nhau tại thời điểm này. Setup branch có merge record riêng; không chỉnh trực tiếp `develop`.

### Verify

```text
git merge-base feature/NS-103-checkout feature/NS-202-payment-failure
git status --short --branch
```

### Expected result

`merge-base` trả đúng baseline đã ghi; `HEAD` là Checkout branch và không có file chưa commit.

### Evidence

Lưu `preflight.txt`, `common-baseline.txt` và trạng thái branch ban đầu trong `evidence/LAB-U03-01/CP0/`.

### Troubleshooting

- Hai tip khác nhau trước khi edit: một branch được tạo từ ref sai. Không reset shared refs; bỏ bản sao Lab và làm lại từ baseline sạch.
- Working tree không sạch: xác định file ngoài scope; không stash mù. Dùng bản sao mới nếu không chứng minh được ownership.
- Thiếu `develop`: quay lại U01/U02 baseline; không tự đổi `main` thành integration branch.

### Reset/rollback

Trước khi có commit Lab, đóng editor và bỏ bản sao Lab. Sau setup commit, có thể tạo một bản sao mới từ repo Lab baseline; không chạy recursive delete vào workspace khóa học.

## Checkpoint 1 — CP-U03-01: Tái tạo MEX trên Checkout × Payment và resolve theo oracle

**Material example refs:** MEX-U03-01 · **LO:** LO3.1, LO3.2

### Why

Checkpoint thay toàn bộ domain input của MEX. Học viên phải chứng minh mình hiểu merge base/ours/theirs và business oracle, không chỉ chép Cart–Checkout result.

### Action

1. Trên `feature/NS-103-checkout`, dùng editor thay duy nhất row `CHANGE_SLOT` bằng row `ADDRESS_INVALID` ở mục Input. Kiểm diff và commit:

   ```text
   git diff -- project-artifacts/checkout/payment-status.csv
   git add project-artifacts/checkout/payment-status.csv
   git commit -m "docs(NS-103): define invalid address status"
   git rev-parse HEAD
   ```

   Lưu object ID này là reviewed Checkout tip. Từ đây coi branch đã peer fetch và không rewrite.

2. Switch Payment branch, thay cùng row baseline bằng `DECLINED_RETRYABLE`, kiểm diff và commit:

   ```text
   git switch feature/NS-202-payment-failure
   git diff -- project-artifacts/checkout/payment-status.csv
   git add project-artifacts/checkout/payment-status.csv
   git commit -m "docs(NS-202): define retryable decline status"
   git rev-parse HEAD
   ```

3. Trước merge, tạo conflict map trong `decisions/LAB-U03-conflict.md`: branches/merge base, overlap row, FR-03 behaviors, owner, Checkout-first order và lý do. Commit bản before-state này ngay trên Payment branch để merge sau mang decision artifact vào cùng change set:

   ```text
   git add decisions/LAB-U03-conflict.md
   git commit -m "docs(NS-202): record integration conflict forecast"
   ```

4. Merge Checkout trước:

   ```text
   git switch develop
   git merge --no-ff feature/NS-103-checkout -m "merge(NS-103): integrate checkout status artifact"
   ```

5. Bắt đầu merge Payment. Lệnh phải dừng ở conflict:

   ```text
   git merge --no-ff feature/NS-202-payment-failure -m "merge(NS-202): integrate payment failure artifact"
   git status --short
   git diff --name-only --diff-filter=U
   ```

6. Trước khi sửa, lưu status và conflict diff. Dùng editor thay toàn bộ marker block bằng hai row `ADDRESS_INVALID` và `DECLINED_RETRYABLE`, mỗi row đúng một lần; giữ hai baseline row không đổi.

7. Cập nhật chính `decisions/LAB-U03-conflict.md` thành Conflict Decision Record after-state: ba options (ours, theirs, combined), chọn combined, nêu Product Owner/domain reviewer là decision role, AC/ID oracle và rule phòng ngừa. Rà resolved diff rồi hoàn tất merge:

   ```text
   git diff --check
   git add project-artifacts/checkout/payment-status.csv decisions/LAB-U03-conflict.md
   git diff --cached
   git commit
   ```

### Explanation

Checkout merge trước làm `ours` chứa `ADDRESS_INVALID`; Payment là `theirs`. Tuy nhiên hai nhãn chỉ mô tả hướng merge. Combined result được chọn vì cả hai behaviors độc lập đều thuộc FR-03. `--no-ff` giữ exact feature tips trong ancestry; rebase Payment/Checkout không cần thiết và Checkout đã shared.

### Verify

```text
git diff --check
git grep -n '^ADDRESS_INVALID,' -- project-artifacts/checkout/payment-status.csv
git grep -n '^DECLINED_RETRYABLE,' -- project-artifacts/checkout/payment-status.csv
git grep -n -E '^(<<<<<<<|=======|>>>>>>>)' -- '*.md' '*.csv'
git status --short --branch
```

### Expected result

- `git diff --check` không có output, exit 0.
- Hai status query mỗi lệnh trả đúng một row với `PRESERVE`.
- Marker query không có output, exit 1 vì không tìm thấy.
- Working tree sạch sau merge commit.

### Evidence

Nộp conflict map, `status-conflict.txt`, conflict diff, resolved diff, completed Conflict Decision Record và `status-after-resolution.txt` trong `evidence/LAB-U03-01/CP-U03-01/`.

### Troubleshooting

- Merge không conflict: kiểm hai branch có cùng baseline và cùng thay `CHANGE_SLOT`; nếu fixture sai, không giả lập marker bằng tay — tạo bản sao Lab đúng input.
- `git commit` báo còn unmerged path: dùng `git diff --name-only --diff-filter=U`; stage mọi artifact đã resolve sau khi oracle PASS.
- Một query trả zero/two row: resolution làm mất hoặc trùng ID; sửa CSV trước commit.
- Conflict chạm file ngoài scope: lưu evidence và `git merge --abort`; kiểm branch diff/merge base trước khi thử lại.

### Reset/rollback

Nếu merge đang dở và quyết định chưa được phê duyệt:

```text
git status --short
git merge --abort
```

Sau abort, xác minh working tree sạch và `develop` vẫn chứa Checkout merge. Không reset/force-push. Nếu merge đã commit sai và chưa được dùng tiếp, tạo bản sao Lab mới từ checkpoint trước; không sửa shared evidence để che lịch sử.

## Checkpoint 2 — CP-U03-02: Chứng minh topology và traceability

**Material example refs:** MEX-U03-01 · **LO:** LO3.1, LO3.2

### Why

Một resolved CSV đúng chưa chứng minh đúng branch/strategy. Reviewer phải tái lập được feature tips, merge point, AC mapping và trạng thái cuối từ evidence độc lập.

### Action

1. Từ graph hiện tại, xác định common baseline, Checkout tip, Payment tip và hai merge commits. Không dùng labels D0/M1/M2 của Example làm object ID.
2. Hoàn thiện Integration Evidence Pack với các cột: ref/commit, source→target, PBI/AC, artifact changed, review verdict, containment result và evidence path.
3. Tạo traceability rows cho `NS-103 → FR-03 → ADDRESS_INVALID → resolution decision → containment` và `NS-202 → FR-03 → DECLINED_RETRYABLE → resolution decision → containment`.
4. Lưu output của graph và hai containment checks; ghi kết luận PASS/REVISE dựa trên oracle.

### Explanation

Checkpoint giảm hướng dẫn: hình thức evidence pack có thể khác, nhưng chuỗi PBI→AC→tip→decision→merge→oracle phải resolve. Squash sẽ làm tip containment fail; no-ff merge giữ boundary để reviewer quan sát được.

### Verify

```text
git log --graph --decorate --oneline --all
git merge-base --is-ancestor feature/NS-103-checkout develop
git merge-base --is-ancestor feature/NS-202-payment-failure develop
git branch --contains feature/NS-103-checkout
git branch --contains feature/NS-202-payment-failure
```

### Expected result

Graph có merge point giải thích được; hai `merge-base --is-ancestor` trả exit 0; `develop` xuất hiện trong containment output. Evidence pack không có PBI/AC/commit/oracle link mồ côi.

### Evidence

Nộp `graph-after.txt`, `containment-checks.txt`, Integration Evidence Pack và reviewer checklist trong `evidence/LAB-U03-01/CP-U03-02/`.

### Troubleshooting

- Tip containment fail nhưng content có mặt: có thể đã squash. Đối chiếu strategy/graph; nếu no-ff là DoD, làm lại trong bản sao Lab thay vì tuyên bố PASS.
- Graph quá khó đọc: giới hạn evidence bằng refs liên quan nhưng giữ `--graph --decorate`; không thay graph bằng mô tả tự khai.
- Decision row thiếu owner/AC: quay lại conflict record và review; không suy ra approval chỉ từ commit message.

### Reset/rollback

Checkpoint chủ yếu đọc và tạo evidence. Nếu ghi sai evidence, sửa artifact evidence và giữ raw output ban đầu; không thay đổi refs. Nếu topology sai, dùng bản sao Lab từ cuối CP0 để tái chạy workflow.

## Checkpoint 3 — CP-U03-03: Negative validation, recovery và shared-history safety

**Material example refs:** MEX-U03-01 · **LO:** LO3.1, LO3.2

### Why

Git có thể báo working tree hợp lệ trong khi artifact vi phạm uniqueness. Failure path này buộc học viên phân biệt structural oracle với business oracle và thực hành recovery không rewrite history.

### Action

1. Trên `develop` sạch, dùng editor chèn tạm một row thứ hai có `status_id=ADDRESS_INVALID` nhưng nghĩa khác. Không stage và không commit.
2. Chạy uniqueness query, lưu output failure và ghi chẩn đoán: dấu hiệu, nguyên nhân, impact tới FR-03, oracle fail.
3. Tự chọn thao tác recovery an toàn cho một local uncommitted edit; sau recovery, chạy lại uniqueness query.
4. Ghi prevention rule vào troubleshooting note: ID registry review trước merge và semantic oracle sau resolution.
5. Chứng minh Checkout reviewed tip vẫn thuộc `develop` và working tree sạch.

### Explanation

Changed input không tạo marker. Đây là semantic failure: cùng ID có hai nghĩa. Vì thay đổi chỉ là local/uncommitted stimulus, recovery đúng phải loại riêng edit đó; không reset/force-push shared refs. Nếu learner đã stage hoặc commit nhầm, phải dừng và xin review strategy thay vì che evidence.

### Verify

Trong trạng thái failure:

```text
git grep -n '^ADDRESS_INVALID,' -- project-artifacts/checkout/payment-status.csv
git status --short
```

Sau recovery:

```text
git grep -n '^ADDRESS_INVALID,' -- project-artifacts/checkout/payment-status.csv
git merge-base --is-ancestor feature/NS-103-checkout develop
git diff --check
git status --short --branch
```

### Expected result

- Failure evidence có hai row `ADDRESS_INVALID` và verdict REVISE.
- Recovery evidence có đúng một row; `merge-base --is-ancestor` exit 0; `git diff --check` sạch; working tree không còn thay đổi.
- Troubleshooting note nêu recovery chỉ tác động file stimulus và không rewrite shared history.

### Evidence

Nộp `duplicate-id-failure.txt`, `recovery-result.txt`, status trước/sau và decision/troubleshooting note trong `evidence/LAB-U03-01/CP-U03-03/`.

### Troubleshooting

- Duplicate edit đã stage: kiểm `git diff --cached`; unstage đúng file rồi khôi phục working copy, không reset cả branch.
- Duplicate edit đã commit: dừng; không amend/rebase nếu commit đã shared. Ghi incident và đề xuất revert/corrective commit để reviewer quyết định.
- Containment fail sau recovery: recovery đã tác động refs thay vì file; bỏ bản sao Lab và chạy lại từ baseline sạch.

### Reset/rollback

Với stimulus chưa stage, khôi phục đúng artifact tracked:

```text
git restore -- project-artifacts/checkout/payment-status.csv
```

Xác minh status sạch ngay sau đó. Không dùng `git reset --hard`, force push hoặc recursive delete.

## 🧪 Final validation

Chạy từ `develop`:

```text
git status --short --branch
git diff --check
git grep -n -E '^(<<<<<<<|=======|>>>>>>>)' -- '*.md' '*.csv'
git grep -n '^ADDRESS_INVALID,' -- project-artifacts/checkout/payment-status.csv
git grep -n '^DECLINED_RETRYABLE,' -- project-artifacts/checkout/payment-status.csv
git merge-base --is-ancestor feature/NS-103-checkout develop
git merge-base --is-ancestor feature/NS-202-payment-failure develop
git log --graph --decorate --oneline --all
```

Final verdict **PASS** khi status/diff sạch; marker query không tìm thấy; mỗi ID query có đúng một row `PRESERVE`; cả ancestor checks exit 0; graph và decision record nhất quán. Nếu một điều kiện fail, verdict là **REVISE**, không sửa log để tuyên bố PASS.

## 📦 Bằng chứng và deliverables

1. **Git evidence pack của Lab**
   - preflight/common baseline;
   - graph/status trước conflict;
   - conflict và resolved diff;
   - graph/containment/status sau merge;
   - negative validation và recovery evidence.
2. **Artifact NovaShop đã cập nhật**
   - `project-artifacts/checkout/payment-status.csv` đạt business oracle.
3. **Decision/troubleshooting note**
   - conflict map, options, owner/rationale, chosen result, oracle và prevention.
4. **Checklist PASS/REVISE**
   - từng checkpoint map tới LO, MEX, expected result và evidence path.

Không nộp thư mục `.git`; output phải loại đường dẫn cá nhân, email thật và remote URL nội bộ.

## ♻️ Reset, cleanup và khả năng chạy lại

- Merge đang dở: lưu evidence, chạy `git merge --abort`, xác minh status sạch.
- Local negative stimulus: `git restore -- <exact-path>` sau khi xác nhận đúng file.
- Topology/setup sai: bỏ **bản sao Lab đã xác định** và tạo bản sao mới từ starter/baseline; không xóa repo khóa học.
- Không xóa branch trước khi evidence được review; không reset hard/force-push shared refs.
- Cleanup hoàn tất khi working tree sạch, không còn merge in progress và evidence pack đã được sao ra khỏi clone dùng lại.

## 🔁 Artifact được tái sử dụng ở đâu

- **ASM-GF-02:** dùng cấu trúc evidence/decision record, nhưng change request `NS-303` và resolution do học viên tự làm.
- **ASM-GF-03:** tiêu thụ Integration evidence pack MVP và Conflict decision log MVP làm release baseline.
- **CAP-GF-01:** tái dùng pattern conflict-to-oracle và history-safety defense.

## 🔐 Chính sách lời giải

Lab cung cấp resolution cho Checkout × Payment để dạy cơ chế. Assignment dùng Checkout × Admin với canonical `changed_by` contract khác; tài liệu này không chỉ ra schema resolution, integration order hoặc final graph cho Assignment.

## 📚 Provenance phần bổ sung

### Nguồn đã map

- Git Reference Manual 2.54.0; Pro Git 2nd Edition; Vincent Driessen Git branching model.
- Scrum Guide 2020.
- NovaShop Project Brief, Backlog, Change Cards và Git Flow Artifact Templates synthetic.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — từ kiến thức đã huấn luyện]** Fixture `CHANGE_SLOT` được thiết kế để conflict tái lập trong môi trường đào tạo; không đại diện cho schema production.
- **[BỔ SUNG — nguồn: Git Reference Manual 2.54.0]** Các lệnh `merge --abort`, `restore`, `diff --check`, `merge-base --is-ancestor` được dùng trong phạm vi clone Lab an toàn.

---
<!-- QUALITY GATE: MEX-U03-01 map CP-U03-01..03; mỗi checkpoint có numbered microsteps + Why/Action/Explanation/Verify/Expected/Evidence/Troubleshooting/Reset; changed input và semantic failure/recovery có thật; không lộ ASM-GF-02 solution. -->

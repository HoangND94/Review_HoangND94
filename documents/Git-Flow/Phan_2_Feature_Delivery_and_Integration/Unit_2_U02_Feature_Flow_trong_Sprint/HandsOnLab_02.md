# Hands-on Lab LAB-U02-01 — Feature flow cho Cart Promotion trên repo tài liệu

| Thuộc tính | Giá trị |
| --- | --- |
| Unit | U02 — Feature Flow trong Sprint |
| Hình thức | Guided with fading |
| Thời lượng | 75 phút |
| Độ khó | Medium |
| Scenario | NS-102 Cart Promotion + review finding về mã hết hạn |
| Project increment | M-GF-02 — feature evidence pack và review record |
| Authenticity | Simulated, synthetic only |

## 🎯 Learning Outcomes được thực hành

- **LO2.1:** vận hành NS-102 từ `develop` về `develop`, giữ PBI–commit–review–acceptance traceability.
- **LO2.2:** ra quyết định `PASS/REVISE` dựa trên DoD, findings và working state.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

| MEX | Checkpoint | LO | Biến thể bắt buộc | Evidence |
| --- | --- | --- | --- | --- |
| MEX-U02-01 | CP-U02-01 | LO2.1, LO2.2 | NS-102 thay NS-101; tự thiết kế branch/issue record | base SHA + decision artifact |
| MEX-U02-01 | CP-U02-02 | LO2.1, LO2.2 | promotion valid/invalid/expired; tự quyết định commit boundaries | commit range + traceability |
| MEX-U02-01 | CP-U02-03 | LO2.1, LO2.2 | error finding “expired failure absent” | review before/after + containment/cleanup |

## 🧭 Bối cảnh nghề nghiệp/dự án và project increment

PBI `NS-102` yêu cầu giỏ hàng và mã khuyến mãi: tổng tiền cập nhật, mã không hợp lệ có thông báo và sản phẩm đã chọn không bị mất. `CARD-U02-LAB` bổ sung failure mode mới: mã giảm giá **hết hạn** chưa có acceptance example; finding severity `error` phải đóng trước merge.

Baseline mô phỏng: `develop` đã chứa Search specification được review. Bạn tạo Cart Promotion feature evidence pack, không code ứng dụng. Artifact được dùng để chuẩn bị Assignment NS-202 nhưng không cung cấp lời giải payment.

## 🧰 Điều kiện bắt đầu

### Kiến thức/kỹ năng tiên quyết

- Hoàn tất U01 và đọc Material/Example U02.
- Biết status, graph, merge-base, commit range, safe branch delete.
- Đọc acceptance criteria và viết Markdown/CSV evidence.

### Môi trường, công cụ và phiên bản

- Bản sao riêng của repo M-GF-01; Git CLI 2.40+ (verified profile: 2.54.0.windows.1).
- Markdown CommonMark, CSV UTF-8; Git identity local dùng `example.invalid`.
- Không remote, cloud, service/payment thật hoặc mã nguồn ứng dụng.

### Starter assets

- [Project Brief](../../starter/NovaShop_Project_Brief.md)
- [Backlog](../../starter/NovaShop_Backlog.csv)
- [Change Cards](../../starter/NovaShop_Change_Cards.md), dùng `CARD-U02-LAB`
- [Artifact Templates](../../starter/templates/GitFlow_Artifact_Templates.md)
- Repo/baseline artifact đã hoàn tất LAB-U01-01.

### Input/trạng thái ban đầu

- `main`, `develop`, tag baseline; current branch `develop`; working tree sạch.
- Search baseline trên `develop`, do trainer cung cấp dưới dạng bản sao repo đã review. Nếu bản sao chưa có fixture, dựng `features/NS-101/search-spec.md` qua branch `feature/NS-101-reviewed-search-baseline` từ `develop`, commit `docs(NS-101): establish reviewed search baseline`, tạo review record `PASS`, merge `--no-ff` về `develop`, chứng minh containment rồi safe-delete bằng `-d`. Fixture chỉ dựng precondition, không phải checkpoint NS-102; tuyệt đối không direct commit vào `develop`.
- NS-102 ready, target 0.1.0; change card yêu cầu expired-code failure evidence.

### Ràng buộc và phạm vi được phép thay đổi

- Feature phải bắt đầu từ `develop`, kết thúc tại `develop`; không direct commit vào `main` hoặc `develop`, kể cả khi dựng setup fixture.
- Tự quyết định commit boundaries và finding disposition; hướng dẫn không cung cấp feature dossier hoàn chỉnh.
- Error finding = 0 trước merge; không rewrite/force push; không `git branch -D`.
- Chỉ synthetic data; reset chỉ trong bản sao Lab.

## 📚 Nguồn đầu vào đã map

SRC-GIT-DOC, SRC-PROGIT, SRC-NVIE, SRC-CONV, SRC-SCRUM và NovaShop synthetic starter assets version 1.0.

## 📋 Lab outline và Definition of Done

### Checklist phạm vi

- CP0: xác minh baseline/search fixture/safety.
- CP-U02-01: branch decision và base evidence cho NS-102.
- CP-U02-02: purposeful commits, sync policy và traceability cho valid/invalid/expired inputs.
- CP-U02-03: review `REVISE` khi missing expired evidence; đóng finding; merge/containment/cleanup.
- Final: status/graph/commit-range/review/data-safety gates.

### Checkpoint đã hoạch định từ course plan

- **CP-U02-01:** verify `git merge-base --is-ancestor develop HEAD`; expected feature có `develop` ancestor và saved base đúng.
- **CP-U02-02:** verify `git log --oneline --decorate develop..HEAD`; expected range chỉ có NS-102/sync intent được giải thích.
- **CP-U02-03:** verify `git branch --merged develop`; expected feature được liệt kê trước cleanup hoặc có containment evidence tương đương.

### Definition of Done

- Ba checkpoint có action, verify, expected result và evidence.
- NS-102 source/target đúng; mọi acceptance/failure criterion có traceability.
- Review chronology trung thực: error mở → `REVISE`; error đóng bằng evidence → mới có thể `PASS`.
- Feature contained trong `develop`, branch cleanup an toàn, status sạch.
- Không secret/PII/remote; artifact mở được; learner giải thích được commit/sync/merge trade-off.

## 🪜 Các bước dự kiến và mức hướng dẫn

| Chặng | Hướng dẫn | Thời gian |
| --- | --- | ---: |
| CP0 | đầy đủ preflight/oracle | 8 phút |
| CP-U02-01 | khung fields; tự ra branch/scope decision | 17 phút |
| CP-U02-02 | oracle rõ; tự chia commit và trace rows | 22 phút |
| CP-U02-03 | failure injected; tự disposition/sửa artifact | 23 phút |
| Final/packaging | checklist | 5 phút |

## Checkpoint 0 — Baseline và safety check

### Action

1. **Why:** bảo vệ output U01 và course repo. **Action:** tạo/mở bản sao Lab U02 riêng; xác nhận current directory thuộc bản sao đó. **Explanation:** mọi reset/cleanup chỉ áp dụng bản sao.
2. **Why:** kiểm integration baseline. **Action:** switch `develop`, chạy status, graph và `git log --oneline main..develop`. **Explanation:** `main` phải giữ baseline; `develop` có governance và Search fixture.
3. **Why:** xác nhận NS-102 input. **Action:** đọc Backlog và CARD-U02-LAB; ghi bốn oracle: total update, invalid message, products retained, expired failure. **Explanation:** expired là changed input so với MEX NS-101.
4. **Why:** ngăn dữ liệu nhạy cảm. **Action:** scan fixture; chỉ dùng product/promotion identifier synthetic. **Explanation:** không nhập coupon thật hay customer/payment data.

### Verify

```text
git branch --show-current
git status --short --branch
git log --graph --decorate --oneline --all
git log --oneline -- features/NS-101/search-spec.md
```

### Expected result

Current `develop`, status sạch, Search fixture có commit reviewed, `main` không chứa feature work, input NS-102 đủ bốn oracle.

### Evidence

`evidence/NS-102/preflight.txt` ghi command/output/kết luận và checklist synthetic-only.

### Troubleshooting

- Search fixture thiếu: dùng bản sao trainer đã chuẩn bị hoặc bootstrap qua feature branch/review/merge/containment đúng mô tả ở phần input; ghi rõ `SETUP`, rồi chạy preflight lại.
- Status dirty: xem diff, commit setup hợp lệ hoặc loại file ngoài scope; không mở feature khi dirty.
- Đang ở repo gốc: dừng và dùng bản sao.

### Reset/rollback

Không reset course repo. Nếu fixture/preflight sai, dùng bản sao mới của M-GF-01 và dựng lại setup fixture; không force-update refs.

## Checkpoint 1 — CP-U02-01: Từ NS-102 tới branch/base evidence

**Material example refs:** `MEX-U02-01` · **LO:** `LO2.1`, `LO2.2`.

### Action

1. **Why:** đặt business scope trước Git mechanics. **Action:** tạo `features/NS-102/issue-record.md` từ template, điền requirement `FR-02`, target 0.1.0, four oracles, included/excluded scope, branch type/source/target và rationale. **Explanation:** không copy NS-101; Cart/PROMO expiry là input mới.
2. **Why:** chứng minh source bằng SHA. **Action:** khi status sạch trên `develop`, lưu `git rev-parse develop` vào `evidence/NS-102/branch-base.txt`, rồi tạo feature theo naming policy. **Explanation:** tên đúng không đủ; saved base là audit evidence.
3. **Why:** commits cần kế hoạch có intent. **Action:** tạo commit plan với tối thiểu hai intent hợp lý nhưng tự chọn boundaries; mỗi row có AC ref, artifact, observable change, evidence. **Explanation:** không chấm số commit cố định; chấm cohesion và traceability.
4. **Why:** issue/base artifact phải nằm trên feature, không direct commit target. **Action:** stage đúng NS-102 paths và commit purposeful message theo NovaShop pattern. **Explanation:** issue ID là stable scope key.

### Verify

```text
git branch --show-current
git merge-base --is-ancestor develop HEAD
git log --oneline --decorate develop..HEAD
git status --short --branch
```

So `branch-base.txt` với merge base/current graph; ghi exit code của ancestor check.

### Expected result

- current branch khớp `feature/NS-102-...` và chứa exact issue ID;
- `develop` là ancestor; saved base là commit `develop` tại lúc mở branch;
- feature-only range mới chứa issue/base/plan intent của NS-102;
- status sạch.

### Evidence

Issue record, commit plan, `branch-base.txt`, status và initial commit-range output.

### Troubleshooting

- Feature tạo nhầm từ `main`: không tiếp tục; nếu chưa chia sẻ, tạo branch mới từ saved `develop` và đưa lại artifact đúng scope; ghi failure evidence.
- Merge-base khác saved base vì `develop` đã tiến: dùng graph và timestamp để phân biệt base-at-creation với current target; không sửa evidence cho “đẹp”.
- Commit range chứa unrelated issue: dừng, review staged paths/commit history; không force rewrite nếu peer đã fetch.

### Reset/rollback

Trước commit, switch về `develop` chỉ khi working tree sạch rồi safe-delete branch nếu không có unique work. Sau commit, ưu tiên bản sao mới nếu topology sai; không dùng `-D` hay force push.

## Checkpoint 2 — CP-U02-02: Purposeful commits và traceability dưới input mới

**Material example refs:** `MEX-U02-01` · **LO:** `LO2.1`, `LO2.2` · **Changed input:** promotion `VALID`, `INVALID`, `EXPIRED` và “products retained”.

### Action

1. **Why:** artifact phải mô tả behavior quan sát được. **Action:** tạo NS-102 specification/acceptance-evidence Markdown/CSV cho total update, invalid message và retained products; **cố ý chưa thêm expired row** để CP3 có failure thật. **Explanation:** đây là controlled omission, không được đánh dấu PASS.
2. **Why:** commit boundary phải thể hiện intent. **Action:** hiện thực commit plan bạn đã chọn; trước mỗi commit xem status/diff, stage đúng paths và dùng message có NS-102. **Explanation:** tự quyết định gộp/tách dựa trên reviewability, không dựa vào số file.
3. **Why:** traceability phải có lỗ hổng nhìn thấy được. **Action:** tạo matrix PBI/AC → commit → artifact row → evidence → current status. Với expired criterion, ghi `MISSING/FAIL`, không để trống hoặc giả PASS. **Explanation:** evidence trung thực quan trọng hơn bảng “xanh”.
4. **Why:** kiểm xem `develop` có tiến. **Action:** so graph/current `develop`; nếu có commit mới liên quan, merge `develop` vào feature và recheck artifacts; nếu không, ghi `NO_SYNC_NEEDED` cùng SHA. **Explanation:** không rebase branch đã chia sẻ; không tạo merge rỗng chỉ để đủ bước.
5. **Why:** chuẩn bị review range sạch. **Action:** lưu commit-range và status output. **Explanation:** range chỉ chứa NS-102 và sync commit có rationale.

### Verify

```text
git log --oneline --decorate develop..HEAD
git status --short --branch
git diff --stat develop...HEAD
```

Artifact review: valid/invalid/retained có evidence; expired phải hiện rõ `MISSING/FAIL` trước CP3.

### Expected result

- purposeful commits có NS-102 và intent kiểm tra được;
- range/diff không chứa PBI khác ngoài sync evidence được giải thích;
- traceability trung thực: ba criterion có evidence, expired là failure đã biết;
- status sạch.

### Evidence

`evidence/NS-102/commit-range-before-review.txt`, diff stat, traceability matrix và commit plan thực tế-vs-dự kiến.

### Troubleshooting

- Commit message thiếu issue ID: ghi review finding; sửa chỉ theo shared-history policy. Nếu đã chia sẻ, dùng follow-up evidence thay vì force push.
- Dirty state: xem từng path, commit đúng intent hoặc loại file tạm sau khi xác nhận; không stash mơ hồ rồi quên.
- Expired row vô tình đã được thêm: đổi changed input thành một failure example khác được CARD cho phép chỉ khi trainer phê duyệt; phải vẫn có review error thật.

### Reset/rollback

Merge sync conflict: lưu status, dùng `git merge --abort` nếu chưa có quyết định, rồi quay lại clean feature. Artifact edit chưa commit chỉ discard sau khi xem diff; cách phục hồi chắc chắn là bản sao Lab mới.

## Checkpoint 3 — CP-U02-03: Review gate, đóng finding và cleanup

**Material example refs:** `MEX-U02-01` · **LO:** `LO2.1`, `LO2.2`.

### Action

1. **Why:** review phải phát hiện failure chứ không hợp thức hóa merge. **Action:** dùng review template, kiểm branch/source, four oracles, traceability, DoD và status. Ghi finding `E-NS102-01`: expired promotion failure example absent, severity `error`, status `OPEN`. **Explanation:** expected merge decision ở thời điểm này là `REVISE`.
2. **Why:** chứng minh gate chặn thay đổi. **Action:** lưu review-before và graph/status; không switch/merge `develop`. **Explanation:** “sẽ sửa sau” không đóng finding.
3. **Why:** remediation phải gắn exact evidence. **Action:** tự bổ sung expired behavior/example vào artifact phù hợp, commit với purposeful message, cập nhật traceability. **Explanation:** hướng dẫn không cung cấp row cuối; output phải thỏa oracle “mã hết hạn có failure message và không làm mất sản phẩm”.
4. **Why:** disposition cần review lại. **Action:** cập nhật finding với fix commit, artifact locator và recheck; chỉ chuyển `CLOSED`/decision `PASS` nếu DoD, status và error-count đều đạt. **Explanation:** nếu gate khác fail, giữ `REVISE` dù expired đã sửa.
5. **Why:** integrate và cleanup có thứ tự an toàn. **Action:** lưu feature tip; khi PASS, switch `develop`, merge `--no-ff`, capture merged list + containment, rồi safe-delete bằng `-d`. **Explanation:** capture trước cleanup; không dùng `-D`.

### Verify

```text
git status --short --branch
git branch --merged develop
git log --graph --decorate --oneline --all
```

Trước cleanup, chạy thêm `git merge-base --is-ancestor feature/NS-102-<chosen-slug> develop`; sau cleanup dùng saved tip SHA.

### Expected result

- review-before: E-NS102-01 open/error, decision REVISE, feature chưa contained;
- review-after: exact fix/evidence, error open 0, DoD PASS, decision PASS;
- feature xuất hiện trong `git branch --merged develop` trước cleanup;
- saved tip contained trong `develop`; branch ref được safe-delete; status sạch.

### Evidence

- review record có chronology before/after;
- expired artifact row + fix commit;
- `review-state-before.txt`, `merged-list.txt`, `containment.txt`, `graph-after.txt`;
- decision/troubleshooting note nêu prevention rule.

### Troubleshooting

- Merge đã chạy khi review còn REVISE: ghi audit failure; không che bằng sửa timestamp. Trong Lab chưa chia sẻ, tạo bản sao sạch để tái lập đúng chronology.
- `branch -d` từ chối: không dùng `-D`; kiểm current branch, merged list và containment.
- Finding closed nhưng trace row thiếu commit/evidence: mở lại finding; bổ sung locator và review lại.
- Error count 0 nhưng dirty state: decision vẫn REVISE; commit/loại file đúng scope rồi rerun gate.

### Reset/rollback

Merge đang dở: capture status rồi `git merge --abort`. Nếu merge sai đã commit, không hard-reset history học tập; dùng bản sao pre-merge hoặc tạo bản sao mới và chạy lại CP3. Cleanup chỉ bằng `-d` sau containment.

## 🧪 Final validation

```text
git status --short --branch
git log --graph --decorate --oneline --all
git log --oneline --decorate main..develop
git branch --merged develop
git show-ref --heads --tags
```

| Gate | PASS oracle |
| --- | --- |
| CP-U02-01 | source/base evidence đúng; feature name có NS-102 |
| CP-U02-02 | commit range cohesive; four criteria trace được, failure state trung thực |
| CP-U02-03 | REVISE-before/PASS-after chronology; error open 0; containment/cleanup |
| Data | synthetic-only, no credential/PII/production endpoint |
| Repository | current `develop`, clean; `main` không nhận NS-102 direct commit |

## 📦 Bằng chứng và deliverables

- Feature evidence pack NS-102: issue record, commit plan, specification/acceptance CSV, traceability matrix.
- Pull-request review record NS-102 với before/after finding disposition.
- Evidence: preflight, branch base, commit range, review state, merged list, containment, graph.
- Troubleshooting/prevention note.

Mỗi evidence file ghi command, observation, conclusion; không nộp `.git`, absolute path cá nhân hoặc ảnh thay text output.

## ♻️ Reset, cleanup và khả năng chạy lại

- Chỉ reset trong bản sao Lab đã xác nhận; giữ repo M-GF-01 gốc.
- Dùng `git merge --abort` chỉ khi status xác nhận merge đang dở.
- Dùng `git branch -d`, không `-D`; nếu safe delete fail, coi đó là evidence chưa contained.
- Không rebase/force push branch reviewer đã fetch.
- Khi topology/chronology không còn đáng tin, tạo bản sao mới từ baseline; không recursive-delete course root.

## 🔁 Artifact được tái sử dụng ở đâu

- Kỹ năng và template được vận dụng độc lập trong `ASM-GF-01` (NS-202), nhưng không tái sử dụng nội dung Cart/expired row làm đáp án.
- Evidence pack làm mẫu cấu trúc đầu vào cho U03 integration audit.
- Capstone dùng pattern PBI → feature dossier → review → containment.

## 🔐 Chính sách lời giải

Lab nêu oracle và safety gates nhưng không cho sẵn commit boundaries, expired artifact row hoặc review-after record. Assignment dùng payment sandbox/duplicate error input khác và phải được làm độc lập.

## 📚 Provenance phần bổ sung

### Nguồn đã map

- [Git Reference Manual 2.54.0](https://git-scm.com/docs/git/2.54.0).
- [Pro Git — Basic Branching and Merging](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging).
- [A successful Git branching model](https://nvie.com/posts/a-successful-git-branching-model/).
- [Conventional Commits 1.0.0](https://www.conventionalcommits.org/en/v1.0.0/).
- [Scrum Guide 2020](https://scrumguides.org/scrum-guide.html).
- NovaShop Backlog/Change Cards/Templates version 1.0, internal approved.

### Phần bổ sung/suy diễn

- **[BỔ SUNG — nguồn: mapped Git/Scrum sources]** Checkpoint gates, evidence naming và controlled failure được tạo cho mục tiêu đào tạo.
- **[BỔ SUNG — nguồn: CARD-U02-LAB synthetic]** NS-102 expired-promotion finding là scenario mô phỏng, không phải incident thật.

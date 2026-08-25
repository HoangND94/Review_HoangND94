# Hands-on Lab LAB-U05-01 — Hotfix phí vận chuyển khi `develop` đã tiến về phía trước

| Thuộc tính | Giá trị |
| --- | --- |
| Unit | U05 — Hotfix Flow và continuity |
| Hình thức | Guided professional-artifact lab, hướng dẫn giảm dần |
| Thời lượng | 60 phút |
| Mức xác thực | Simulated |
| Không thuộc phạm vi | Viết/chạy mã ứng dụng, remote production, credential thật |

## 🎯 Learning Outcomes được thực hành

- **LO5.1:** phân loại HOTFIX-301, tạo hotfix từ `main` và đóng regression gate.
- **LO5.2:** tạo patch tag trên `main`, capture `HOTFIX_CHANGE_COMMIT`, propagate và audit change commit trên `main`/`develop`.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

| Worked example | Checkpoint | Cách chuyển giao, không copy |
| --- | --- | --- |
| MEX-U05-01 | CP-U05-01 | Tái tạo branch decision từ change card; chẩn đoán một wrong-source branch chứa Admin vNext |
| MEX-U05-01 | CP-U05-02 | Thêm boundary input đúng `500000`, bắt đầu ở trạng thái REVISE; tự tạo dossier/CSV rồi capture change SHA |
| MEX-U05-01 | CP-U05-03 | Quan sát failure “change chưa ở dòng tương lai”, propagate rồi chứng minh bằng change SHA thay vì tag |

## 🧭 Project slice

Production baseline là `v0.1.0`; `develop` đã có Admin cho phiên bản kế tiếp. Card **CARD-U05-LAB / HOTFIX-301** báo bảng phí synthetic áp sai ngưỡng miễn phí. Học viên tạo project increment M-GF-05 trên một bản sao repository: hotfix dossier, regression evidence, annotated patch tag và continuity audit. Stakeholder duyệt là incident/release reviewer mô phỏng.

## 🧰 Điều kiện bắt đầu

### Prerequisite và starter assets

- Đã hoàn thành repository của U04: `main`, `develop`, tag `v0.1.0`, working tree sạch.
- Đọc `starter/NovaShop_Project_Brief.md`, row HOTFIX-301 trong `starter/NovaShop_Backlog.csv`, `starter/NovaShop_Change_Cards.md` và mục 6–9 của `starter/templates/GitFlow_Artifact_Templates.md`.
- Tạo một bản sao thư mục repository U04 bằng chức năng copy của hệ điều hành, đặt tên `novashop-u05-lab`; mọi lệnh dưới đây chạy trong bản sao này.

### Input mới so với Material

1. Review yêu cầu có case đúng boundary `500000`, không chỉ giá trị trên/dưới boundary.
2. Một nhánh thử sai nguồn `practice/wrong-source-shipping` sẽ được tạo để học viên chẩn đoán.
3. Continuity được kiểm bằng SHA change commit; lệnh kiểm tag trên `develop` không được dùng làm oracle.

### Constraints

- Chỉ thay đổi artifact Markdown/CSV trong `project-artifacts/M-GF-05` và refs của bản sao Lab.
- Không force-push, không move tag đã chia sẻ, không dùng remote/credential thật.
- Không đưa Admin vNext vào patch.
- Mỗi kết luận phải có output Git hoặc review evidence; output phải được rà soát để không lộ path/email cá nhân.

## 📋 Lab outline và Definition of Done

- CP-U05-01..03 đều có Action, Verify, Expected, Evidence và kết luận PASS.
- `v0.1.0` là ancestor của hotfix; `v0.1.1` là annotated tag và ancestor của `main`.
- Dossier lưu SHA `HOTFIX_CHANGE_COMMIT`; branch containment của SHA liệt kê `main` và `develop`.
- Regression có dưới/đúng/trên boundary và Cart/Checkout consistency, tất cả PASS.
- Patch diff không có Admin vNext; working tree sạch; postmortem có prevention owner/oracle.

---

## Checkpoint 0 — Baseline và safety check

### Numbered microsteps — Why / Action / Explanation

1. **Why:** bảo đảm không thao tác trên repository khóa học hoặc bản U04 gốc. **Action:** mở terminal tại thư mục `novashop-u05-lab`; xác nhận đường dẫn hiện tại bằng lệnh tương ứng của terminal. **Explanation:** reset của Lab dựa trên việc bỏ riêng bản sao này, nên tên/phạm vi phải rõ trước khi tạo ref.
2. **Why:** xác nhận công cụ và danh tính đào tạo. **Action:** chạy `git --version`, `git config --get user.name`, `git config --get user.email`. **Explanation:** dừng nếu output chứa danh tính không được phép dùng trong evidence.
3. **Why:** khóa baseline. **Action:** chạy `git status --short --branch`, `git show-ref --verify refs/heads/main`, `git show-ref --verify refs/heads/develop`, `git show-ref --verify refs/tags/v0.1.0`. **Explanation:** thiếu một ref làm mọi oracle sau vô nghĩa.
4. **Why:** lưu graph trước thay đổi. **Action:** chạy `git log --graph --decorate --oneline --all`; lưu bản đã rà soát vào evidence note `evidence/HOTFIX-301/baseline.md`. **Explanation:** before/after graph giúp reviewer phát hiện scope leak và route sai.

### Verify

```text
git status --short --branch
git merge-base --is-ancestor v0.1.0 main
```

### Expected result

Working tree sạch; exit code ancestor là `0`; `main`, `develop`, `v0.1.0` tồn tại; graph cho thấy `develop` có thay đổi tương lai.

### Evidence

`evidence/HOTFIX-301/baseline.md` chứa version, ref list, status và graph đã redact.

### Troubleshooting

- Ref thiếu → đang dùng sai bản U04 hoặc copy thiếu `.git`; dừng và tạo lại bản sao.
- Working tree bẩn → không tự xóa thay đổi; quay lại bản U04 sạch rồi copy lại.
- Danh tính thật xuất hiện → cấu hình danh tính đào tạo trong bản sao trước khi tiếp tục, không chụp output cũ vào bài nộp.

### Reset/rollback

Không sửa bản U04 gốc. Nếu baseline không đạt, đóng terminal, đưa đúng thư mục `novashop-u05-lab` vào thùng rác sau khi xác nhận tên tuyệt đối, rồi tạo lại bản sao.

---

## Checkpoint CP-U05-01 — Triage và sửa wrong-source decision

**material_example_refs:** MEX-U05-01 · **LO:** LO5.1, LO5.2.

### Numbered microsteps — Why / Action / Explanation

1. **Why:** trải nghiệm dấu hiệu của nguồn branch sai. **Action:** chuyển sang `develop`, tạo `practice/wrong-source-shipping`, rồi chạy `git diff --name-only v0.1.0..practice/wrong-source-shipping`. **Explanation:** output có artifact vNext cho thấy nhánh thừa scope dù `v0.1.0` vẫn có thể là ancestor.
2. **Why:** không biến nhánh sai thành hotfix thật. **Action:** lưu diff vào `evidence/HOTFIX-301/wrong-source.md`; chuyển về `develop`, xóa an toàn local branch bằng `git branch -d practice/wrong-source-shipping`, rồi chuyển sang `main`. **Explanation:** branch fixture chỉ trỏ commit đã reachable từ `develop`, nên safe-delete xác nhận không làm mất change; thao tác được giới hạn ở branch thực hành trong bản sao và không rewrite shared history.
3. **Why:** đưa ra branch-type decision có thể review. **Action:** tạo `project-artifacts/M-GF-05/hotfix-dossier-v0.1.1.md` từ template Incident/Hotfix Record; điền incident ID, production baseline, observed impact, lý do hotfix, included/excluded scope và source/targets. **Explanation:** ticket “urgent” không đủ; record phải chỉ ra production symptom và scope khôi phục hành vi.
4. **Why:** tạo branch đúng. **Action:** từ `main`, tạo `hotfix/0.1.1-shipping-fee`; chưa sửa artifact khác. **Explanation:** branch mới phải đại diện chính production baseline trước commit hotfix.

### Verify

```text
git merge-base --is-ancestor v0.1.0 hotfix/0.1.1-shipping-fee
git diff --name-only main..hotfix/0.1.1-shipping-fee
git branch --list practice/wrong-source-shipping
git status --short --branch
```

### Expected result

Ancestor command exit `0`; diff giữa `main` và hotfix rỗng trước khi sửa; lệnh `branch --list` không còn trả về nhánh fixture; current branch là hotfix; dossier có decision/rationale và loại trừ Admin.

### Evidence

- `evidence/HOTFIX-301/wrong-source.md`: diff cho nhánh sai và chẩn đoán.
- `hotfix-dossier-v0.1.1.md`: triage/branch decision.
- `evidence/HOTFIX-301/cp01.md`: lệnh, exit status, PASS/REVISE.

### Troubleshooting

- Wrong-source diff rỗng → kiểm `develop` có thực sự tiến sau `v0.1.0`; nếu fixture không có vNext, ghi fixture defect và dừng.
- Không xóa được practice branch → bảo đảm đã switch về `develop` và branch tip vẫn reachable từ `develop`; không đổi sang `-D` hoặc force thao tác lên ref khác.
- Correct hotfix đã chứa Admin path → tạo lại bản sao Lab; không “sửa” bằng history rewrite.

### Reset/rollback

Trước commit đầu, có thể switch `main` và xóa đúng branch `hotfix/0.1.1-shipping-fee`. Sau khi có commit, dùng reset toàn Lab bằng bản sao mới thay vì sửa lịch sử tùy tiện.

---

## Checkpoint CP-U05-02 — Đóng boundary regression, capture change commit và tag patch

**material_example_refs:** MEX-U05-01 · **LO:** LO5.1, LO5.2.

### Numbered microsteps — Why / Action / Explanation

1. **Why:** tạo artifact nghề nghiệp thay vì mã ứng dụng. **Action:** trong `project-artifacts/M-GF-05`, tạo `shipping-rule.md` ghi rule ID, baseline rule, corrected rule “subtotal từ 500000 trở lên có fee 0”, scope và approval oracle. **Explanation:** rule là contract được review; không tuyên bố đã sửa một hệ thống chạy thật.
2. **Why:** kiểm failure path tại boundary. **Action:** tạo `shipping-regression.csv` với cột `case_id,input_subtotal,expected_fee,observed_artifact_fee,result`; thêm các input `499999`, `500000`, `650000`. Lần review đầu cố ý ghi observed của `500000` là `30000` và result `REVISE`. **Explanation:** changed input chứng minh checklist một happy path là chưa đủ.
3. **Why:** đóng finding dựa trên artifact. **Action:** đối chiếu rule; chỉnh artifact/observed để case boundary phản ánh fee `0`; thêm row kiểm Cart/Checkout cùng tham chiếu rule ID; peer-review và chỉ đánh PASS khi expected=observed. **Explanation:** learner phải biến REVISE thành PASS bằng consistency evidence, không chỉ đổi nhãn result.
4. **Why:** giữ thay đổi hẹp và traceable. **Action:** stage chỉ thư mục M-GF-05, review `git diff --cached --name-only`, commit incident artifacts với message tham chiếu HOTFIX-301. **Explanation:** staged-path review là gate chống scope leak.
5. **Why:** tạo identity chung qua các merge mà không tự tham chiếu. **Action:** ngay sau commit chứa shipping correction/regression, chạy `git rev-parse HEAD`; sao chép SHA vào field `HOTFIX_CHANGE_COMMIT` trong dossier và `evidence/HOTFIX-301/hotfix-change-commit.md`, rồi commit riêng phần metadata này. **Explanation:** `HOTFIX_CHANGE_COMMIT` vẫn là commit fix trước đó; metadata commit theo sau không thay đổi identity của incident correction.
6. **Why:** phát hành chỉ sau gate. **Action:** merge hotfix vào `main` với merge commit; review regression và patch diff trên `main`; khi PASS, tạo annotated tag `v0.1.1` với message tham chiếu HOTFIX-301. **Explanation:** tag định danh main release commit, không phải change commit chung.

### Verify

```text
git merge-base --is-ancestor v0.1.0 hotfix/0.1.1-shipping-fee
git diff --name-only v0.1.0..v0.1.1
git cat-file -t refs/tags/v0.1.1
git merge-base --is-ancestor v0.1.1 main
```

### Expected result

Hai ancestor commands exit `0`; tag type in `tag`; diff chỉ có HOTFIX-301 artifacts; regression có bốn rows PASS. Evidence note ghi một SHA hợp lệ làm `HOTFIX_CHANGE_COMMIT`, và `git show --name-only` của SHA đó chứa correction/regression artifacts.

### Evidence

- `shipping-rule.md`, `shipping-regression.csv`, updated dossier.
- `evidence/HOTFIX-301/regression-before-after.md` thể hiện boundary REVISE → PASS.
- `evidence/HOTFIX-301/hotfix-change-commit.md` ghi SHA và lệnh capture.
- `evidence/HOTFIX-301/cp02.md` ghi tag type, ancestor exits và patch paths.

### Troubleshooting

- Tag đã tồn tại trước gate → dừng; nếu chỉ local/chưa chia sẻ, xử lý theo policy của facilitator; không tự move một tag đã chia sẻ.
- `cat-file` in `commit` → lightweight tag không đạt policy; giữ evidence REVISE và xin review trước khi sửa.
- Patch diff có Admin → không tag/publish; kiểm staged commit và nguồn branch, quay lại bản sao sạch nếu scope đã trộn sâu.
- Field SHA trỏ metadata commit thay vì fix commit → kiểm thứ tự hai commits; field phải giữ SHA commit correction/regression được capture trước metadata commit.

### Reset/rollback

Nếu merge đang dang dở, lưu `git status` rồi dùng `git merge --abort`. Nếu tag/merge đã hoàn tất nhưng sai, không rewrite; dừng Lab và tạo bản sao mới từ U04 baseline.

---

## Checkpoint CP-U05-03 — Debug missing propagation và hoàn tất continuity audit

**material_example_refs:** MEX-U05-01 · **LO:** LO5.1, LO5.2.

### Numbered microsteps — Why / Action / Explanation

1. **Why:** quan sát failure trước remediation. **Action:** dùng SHA trong `evidence/HOTFIX-301/hotfix-change-commit.md` với `git branch --contains`; lưu output trước propagation. **Explanation:** tại thời điểm này, `develop` chưa được merge nên absence của `develop` là failure evidence mong đợi.
2. **Why:** chọn target đúng scenario. **Action:** xác nhận không có `release/*` đang mở bằng `git branch --list 'release/*'`; vì danh sách rỗng, switch `develop` và merge `hotfix/0.1.1-shipping-fee` bằng merge commit. **Explanation:** nếu có active release, dừng và chuyển sang rule active-release; không tiếp tục route này.
3. **Why:** chứng minh change, không chứng minh nhầm tag. **Action:** chạy lại `git branch --contains` với `HOTFIX_CHANGE_COMMIT`; không dùng `git merge-base --is-ancestor v0.1.1 develop` làm gate. **Explanation:** tag ở main merge commit không nhất thiết nằm trong develop sau two separate no-ff merges.
4. **Why:** đóng vòng học tập. **Action:** tạo `workflow-continuity-audit-v0.1.1.md` gồm target, change SHA, observed branches, patch scope, PASS/REVISE; thêm postmortem root cause, detection gap, prevention “dưới/đúng/trên boundary”, owner và review condition. **Explanation:** topology và prevention phải cùng có bằng chứng.
5. **Why:** bàn giao trạng thái sạch. **Action:** commit continuity artifacts trên `develop` theo workflow của Lab; chạy final graph/status; rà log để loại path/email cá nhân khỏi bản evidence nộp. **Explanation:** artifact evidence được giữ, workspace Lab có thể bỏ sau review.

### Verify

```text
git branch --contains HOTFIX_CHANGE_COMMIT
git merge-base --is-ancestor v0.1.1 main
git cat-file -t refs/tags/v0.1.1
git diff --name-only v0.1.0..v0.1.1
git status --short --branch
```

`HOTFIX_CHANGE_COMMIT` ở lệnh đầu là SHA thật đã lưu tại CP-U05-02; người học dán SHA đó vào lệnh hoặc gán chính giá trị đã lưu cho một biến terminal riêng. Không lấy lại tip branch sau metadata commit để thay thế change SHA.

### Expected result

- Containment của change SHA liệt kê `main` và `develop` (có thể còn liệt kê hotfix branch).
- Tag ancestor của `main`, tag type `tag`.
- Patch diff không có Admin; status sạch.
- Continuity audit và postmortem có owner/oracle; failure-before và recovery-after đều được lưu.

### Evidence

- `evidence/HOTFIX-301/containment-before.md` và `containment-after.md`.
- `workflow-continuity-audit-v0.1.1.md`.
- `evidence/HOTFIX-301/graph-after.md` và `cp03.md`.

### Troubleshooting

- `develop` vẫn thiếu change SHA → kiểm merge target và merge completion; không dùng tag containment để thay thế.
- Có `release/*` mở → ghi decision REVISE cho route hiện tại; merge hotfix vào active release theo policy rồi audit change SHA, không tự merge mọi target.
- Conflict với Admin → lưu status/diff, đối chiếu shipping oracle và Admin preservation; nếu không giải quyết an toàn trong thời gian Lab, abort merge và ghi evidence thay vì đoán.
- Branch containment có thêm branch → không tự coi là lỗi; đánh giá các branch bắt buộc có xuất hiện hay không.

### Reset/rollback

Nếu merge đang dang dở, lưu evidence rồi `git merge --abort`. Với sai lệch sau merge/tag, không rewrite; đóng bản sao, xác nhận tuyệt đối thư mục `novashop-u05-lab`, đưa riêng bản sao vào thùng rác và copy lại U04 baseline.

## 🧪 Final validation

Reviewer chấm theo thứ tự:

1. `git merge-base --is-ancestor v0.1.0 hotfix/0.1.1-shipping-fee` → exit `0`.
2. `git cat-file -t refs/tags/v0.1.1` → `tag`.
3. `git merge-base --is-ancestor v0.1.1 main` → exit `0`.
4. `git branch --contains` với SHA `HOTFIX_CHANGE_COMMIT` → có `main`, `develop`.
5. `git diff --name-only v0.1.0..v0.1.1` → chỉ incident scope.
6. Regression checklist → 4/4 PASS; dossier, continuity audit, postmortem đầy đủ.
7. `git status --short --branch` → working tree sạch.

Nếu một gate không đạt, kết luận Lab là REVISE; không bù topology sai bằng checklist hoặc ngược lại.

## 📦 Deliverables và tái sử dụng

- Git evidence pack dưới `evidence/HOTFIX-301` đã redact.
- `hotfix-dossier-v0.1.1.md`, `shipping-rule.md`, `shipping-regression.csv`.
- `workflow-continuity-audit-v0.1.1.md` và postmortem.

Giữ các artifact này cho **ASM-GF-04** như prerequisite về kỹ năng, nhưng Assignment dùng incident/input khác và không cho phép sao chép dossier. Capstone **CAP-GF-01** tái sử dụng cấu trúc evidence/continuity.

## ♻️ Reset, cleanup và khả năng chạy lại

Sau khi reviewer xác nhận evidence đã lưu, có thể đưa riêng bản sao `novashop-u05-lab` vào thùng rác. Trước thao tác, đóng terminal/editor và xác nhận đường dẫn tuyệt đối kết thúc đúng bằng tên bản sao; không xóa U04 source hoặc thư mục khóa học.

## 📚 Provenance

- SRC-NVIE — hotfix route và active-release exception.
- SRC-GIT-DOC — `merge-base`, `branch --contains`, tag/ref inspection.
- SRC-NS-CARDS — HOTFIX-301 và Admin vNext synthetic.
- [SUY DIỄN — từ Git graph semantics] Wrong-source branch, boundary REVISE và before/after containment là failure fixtures đào tạo.

---
<!-- QUALITY GATE: MEX-U05-01 map đủ CP-U05-01..03; mỗi checkpoint có numbered Why/Action/Explanation + Verify/Expected/Evidence/Troubleshooting/Reset; có changed input và failure path; tag-main tách change-containment; không lộ lời giải INC-501. -->

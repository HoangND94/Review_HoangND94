# Hands-on Lab LAB-U06-01 — Audit lịch sử và đề xuất workflow sau MVP

| Thuộc tính | Giá trị |
| --- | --- |
| Unit | U06 — Governance, Scrum traceability và quyết định workflow |
| Hình thức | Guided professional-artifact lab, guidance giảm dần |
| Thời lượng | 45 phút |
| Mức xác thực | Simulated |
| Validation | Artifact review + read-only Git evidence |

## 🎯 Learning Outcomes được thực hành

- **LO6.1:** audit đủ sáu supplied signs, phát hiện đúng ít nhất 5/6, phân loại rule layer và tạo remediation có owner.
- **LO6.2:** viết ADR chọn giữ Git Flow hoặc flow đơn giản hơn từ changed cadence/version/lead-time/merge-cost inputs.

## 🔗 Mapping từ ví dụ triển khai trong Material tới Lab checkpoints

| MEX | Checkpoint | Variation/transfer |
| --- | --- | --- |
| MEX-U06-01 | CP-U06-01 | Dùng raw CARD-U06/evidence mới; học viên tự classify 6 signs và không copy audit matrix mẫu |
| MEX-U06-01 | CP-U06-02 | Dùng U05 `HOTFIX_CHANGE_COMMIT`; sửa false tag-containment và Scrum boundary trong traceability map |
| MEX-U06-01 | CP-U06-03 | Changed metrics; ambiguous unreachable object; tự chọn decision/trigger thay vì dùng decision của MEX |

## 🧭 Project slice và stakeholder

Sau `v0.1.1`, NovaShop cần một workflow audit và ADR cho M-GF-06. Học viên là workflow reviewer; release owner, Scrum Master và Product Owner là consumers của finding/decision, nhưng tên vai trò không biến Git Flow thành thành phần Scrum. Outputs được Review REV-GF-01 và Capstone CAP-GF-01 tái sử dụng.

## 🧰 Điều kiện bắt đầu

### Starter state/assets

- Bản sao repository đã hoàn thành U05, đặt tên `novashop-u06-lab`; U05 source vẫn nguyên vẹn.
- `starter/NovaShop_Change_Cards.md` — CARD-U06.
- `starter/templates/GitFlow_Artifact_Templates.md` — Workflow Audit Finding và Workflow Decision ADR.
- `starter/NovaShop_Project_Brief.md`, backlog CSV và U05 hotfix dossier/continuity audit.
- Git CLI 2.40+, editor Markdown/CSV UTF-8; không cần hosting platform hoặc network.

CARD-U06 là **supplied audit evidence packet**. Nếu local graph không tái hiện một sign, ghi nguồn observation là CARD-U06; không tạo/fabricate output. Các Git commands chỉ xác minh refs thực sự có trong bản sao.

### Changed inputs so với Material

- cadence mỗi 2 tuần;
- một supported production version;
- median ready-to-release lead time 5 ngày, gồm 3 ngày chờ release branch;
- merge/back-merge cost 7 person-hours/release;
- `git fsck` có thể không in gì; failure card giả định có một unreachable commit sau branch thực hành được xóa hợp lệ.

Các số liệu là synthetic và không phải benchmark.

### Constraints

- Chỉ dùng read-only Git inspection; không rewrite, force-update hoặc “tái tạo lỗi” trên refs.
- Mọi finding ghi exact evidence, tầng rule, severity, impact, remediation, owner và closure oracle.
- Git evidence chỉ hỗ trợ Scrum transparency; không thay thế artifact, commitment, event hoặc accountability.
- Không có secret/PII; evidence output được redact.

## 📋 Lab outline và Definition of Done

- CP-U06-01..03 có evidence và PASS/REVISE rõ.
- Audit cover 6/6 sample signs, phát hiện đúng ≥5/6 và không tự gọi unreachable object là violation.
- Traceability map sửa đúng tag-main/change-target nuance và Scrum boundary.
- ADR có 4 drivers, ≥2 options, decision/consequences, Scrum boundary, owner và trigger/review condition.
- Working tree sạch sau commit artifacts; reset chỉ tác động `novashop-u06-lab`.

---

## Checkpoint 0 — Preflight và evidence boundary (5 phút)

### Numbered microsteps — Why / Action / Explanation

1. **Why:** bảo vệ U05 source. **Action:** mở terminal tại `novashop-u06-lab`, xác nhận tên/path của bản sao. **Explanation:** mọi artifact/ref của Lab ở bản sao, cleanup có target rõ.
2. **Why:** xác nhận readable baseline. **Action:** chạy `git --version`, `git status --short --branch`, `git log --graph --decorate --oneline --all`, `git show-ref --heads --tags`. **Explanation:** đây là smoke check, không phải bằng chứng cho sign CARD-U06 chưa tồn tại local.
3. **Why:** giữ audit work tách biệt. **Action:** từ `develop`, tạo `feature/u06-workflow-audit`; tạo thư mục `project-artifacts/M-GF-06` và `decisions` bằng editor/file manager. **Explanation:** governance artifacts cũng là product work được version hóa; branch source tuân feature flow đã học.
4. **Why:** không lẫn observed với supplied evidence. **Action:** mở report mới, tạo cột `Evidence source` với giá trị chỉ được là `local Git`, `review record` hoặc `CARD-U06 supplied`. **Explanation:** reviewer phải biết claim nào chạy lại được local.

### Verify

```text
git status --short --branch
git log --graph --decorate --oneline --all
```

### Expected result

Current branch `feature/u06-workflow-audit`; baseline refs đọc được; report skeleton có cột nguồn evidence; chưa có history mutation ngoài branch/artifact work.

### Evidence

`evidence/U06/preflight.md`: version, status, ref summary, scope statement “local vs supplied”.

### Troubleshooting

- U05 dossier thiếu `HOTFIX_CHANGE_COMMIT` → quay lại U05 evidence, không thay bằng tag `v0.1.1`.
- Working tree bẩn trước Lab → dừng và copy lại U05 source sạch.
- Local tag type khác CARD-U06 sign → giữ hai observations tách nguồn; không sửa local tag để giống card.

### Reset/rollback

Nếu chưa commit, có thể đóng editor và bỏ bản sao. Không reset/rewrite U05 source. Khi không chắc trạng thái, tạo lại `novashop-u06-lab` từ bản U05 sạch.

---

## Checkpoint CP-U06-01 — Audit và phân loại 6/6 supplied signs (12 phút)

**material_example_refs:** MEX-U06-01 · **LO:** LO6.1, LO6.2 · **Guidance:** cao ở cấu trúc, tự chủ ở verdict.

### Numbered microsteps — Why / Action / Explanation

1. **Why:** tránh finding chung chung. **Action:** tạo `project-artifacts/M-GF-06/git-flow-audit-report.md` với các cột `ID, expected rule, rule layer/source, exact evidence, observed, severity, impact, remediation, owner, closure oracle, status`. **Explanation:** đây là semantic contract audit.
2. **Why:** bảo đảm coverage. **Action:** chuyển nguyên sáu sign CARD-U06 thành F-01..F-06; đánh dấu `Evidence source = CARD-U06 supplied`; không sao chép verdict từ Material. **Explanation:** mỗi sign chỉ được tick covered sau khi có classification và oracle.
3. **Why:** phân biệt các tầng. **Action:** với từng row, chọn một tầng chính: Git capability/integrity, Git Flow convention, team policy, Scrum definition; nếu có tầng phụ, ghi riêng. **Explanation:** direct commit/lightweight tag có thể hợp lệ về Git nhưng vi phạm team policy; Sprint Review statement thuộc Scrum boundary.
4. **Why:** biến finding thành work có thể đóng. **Action:** tự chấm status/severity và điền remediation + owner + closure oracle. **Explanation:** “hãy sửa” hoặc “đào tạo lại” không đủ nếu không có observable close condition.
5. **Why:** kiểm threshold LO6.1. **Action:** peer/self-review 6 rows; đếm rows đúng dựa trên rule/source; nếu dưới 5, đánh dấu CP REVISE và sửa reasoning trước khi tiếp tục.

### Verify

```text
git log --graph --decorate --oneline --all
```

Kết hợp output local với CARD-U06 supplied packet; không tuyên bố graph local chứng minh sign không hiện diện trong đó.

### Expected result

- 6/6 rows covered; ít nhất 5/6 classification/verdict đúng.
- Mỗi row có evidence source, owner và closure oracle.
- F-06 ghi rõ phát biểu Scrum sai; F-03 ghi rõ lightweight tag là policy violation, không phải Git corruption.

### Evidence

- `git-flow-audit-report.md` bản đầu.
- `evidence/U06/cp01-coverage.md` gồm count, peer/self-review notes và graph đã redact.

### Troubleshooting

- Không biết severity → bắt đầu từ impact tới production/history/traceability, không từ cảm xúc.
- Không biết owner → chọn role có quyền hoàn tất remediation, không mặc định Scrum Master sở hữu technical fix.
- Exact evidence trống → giữ REVISE; không nâng status bằng narrative.

### Reset/rollback

Giữ bản report trước sửa trong Git diff/evidence; sửa forward trên feature branch. Không rewrite graph để xóa dấu hiệu audit.

---

## Checkpoint CP-U06-02 — Continuity audit và Scrum boundary map (10 phút)

**material_example_refs:** MEX-U06-01 · **LO:** LO6.1, LO6.2 · **Guidance:** trung bình.

### Numbered microsteps — Why / Action / Explanation

1. **Why:** dùng đúng identity propagation. **Action:** lấy SHA `HOTFIX_CHANGE_COMMIT` từ U05 dossier/evidence; chạy `git branch --contains` với SHA đó; lưu output. **Explanation:** tag `v0.1.1` ở main merge commit có thể không contained trong `develop`; tag containment trên nhánh tương lai là false oracle.
2. **Why:** tách release identity và change continuity. **Action:** bổ sung hai rows trong report: `v0.1.1 ancestor main` và `HOTFIX_CHANGE_COMMIT contained required future target`; ghi PASS/REVISE độc lập. **Explanation:** một row PASS không bù row kia.
3. **Why:** kiểm traceability hai chiều. **Action:** tạo mapping `PBI/incident → change SHA → review evidence → release tag → business oracle`; đi ngược từ tag tới incident. **Explanation:** missing reverse link là finding, dù commit message có issue ID.
4. **Why:** giữ Scrum boundary. **Action:** tạo bảng `Scrum element / supporting Git evidence / does-not-replace`; phủ Product Backlog/Product Goal, Sprint Backlog/Sprint Goal, Increment/DoD và Sprint Review; sửa F-06 thành statement phân biệt Scrum purpose với NovaShop team release policy. **Explanation:** Git Flow là practice context-specific.

### Verify

```text
git merge-base --is-ancestor v0.1.1 main
git branch --contains HOTFIX_CHANGE_COMMIT
git status --short --branch
```

Người học thay `HOTFIX_CHANGE_COMMIT` bằng SHA thật hoặc dùng biến terminal. Không dùng `git branch --contains v0.1.1` làm propagation gate.

### Expected result

- Tag-main ancestor exit `0`.
- Change SHA containment được đánh giá theo targets của U05; nếu thiếu target, finding REVISE có owner/remediation.
- Traceability đi xuôi/ngược không có link mồ côi trong sample.
- Boundary map không gọi branch/PR/tag/Git Flow là Scrum artifact/commitment/event và không gọi Sprint Review là mandatory release gate.

### Evidence

`evidence/U06/containment.md`, traceability table, corrected F-06 statement và `evidence/U06/cp02-review.md`.

### Troubleshooting

- Tag không ở main → đây là release finding riêng; không “sửa” bằng cách move tag đã chia sẻ.
- Change SHA không resolve → kiểm copy/redaction; không đoán SHA từ tag.
- Boundary table ghi “tag = Increment” → đổi quan hệ thành “tag hỗ trợ truy vết”; kiểm DoD evidence độc lập.

### Reset/rollback

Các lệnh là read-only. Nếu artifact mapping sai, sửa forward và giữ before/after diff. Nếu vô tình bắt đầu merge, lưu status rồi `git merge --abort`; Lab này không yêu cầu merge.

---

## Checkpoint CP-U06-03 — Phân loại ambiguous failure và viết ADR (13 phút)

**material_example_refs:** MEX-U06-01 · **LO:** LO6.1, LO6.2 · **Guidance:** thấp; learner tự chọn decision.

### Numbered microsteps — Why / Action / Explanation

1. **Why:** không biến diagnostic output thành verdict tự động. **Action:** chạy `git fsck --no-reflogs --unreachable`; nếu không có output, dùng changed failure card: “một unreachable commit xuất hiện sau khi branch thực hành đã được xóa có chủ đích”. **Explanation:** unreachable nói về reachability trong tập refs được xét, chưa chứng minh corruption/force-push violation.
2. **Why:** ghi reasoning kiểm chứng được. **Action:** thêm context note gồm sign, plausible causes, evidence còn thiếu, next diagnostic và prevention; chỉ tạo finding nếu có causal evidence ngoài unreachable line. **Explanation:** audit phải quản lý uncertainty.
3. **Why:** tránh copy ADR decision từ MEX. **Action:** tạo `decisions/ADR-GF-001-workflow-after-mvp.md`; dùng changed metrics 2-week cadence, one supported version, 5-day lead time/3-day release wait, 7 person-hours merge cost. **Explanation:** input nghiêng khác MEX nhưng không tự động quyết định.
4. **Why:** cân nhắc lựa chọn thật. **Action:** mô tả ít nhất Option A giữ Git Flow và Option B main + short-lived topic branches; tự chọn, nêu consequences, main-readiness/transition guardrails và Scrum boundary. **Explanation:** option không được chọn vẫn phải viable.
5. **Why:** làm decision có thể thay đổi. **Action:** thêm owner, metric definition/sample limitation, trigger đo được và review condition/date tương đối theo release (ví dụ “sau hai releases”), rồi peer/self-review. **Explanation:** trigger ngăn ADR thành giáo điều.

### Verify

```text
git fsck --no-reflogs --unreachable
git diff --check
git status --short --branch
```

Sau review artifact, stage/commit report và ADR trên feature branch rồi chạy lại status.

### Expected result

- Unreachable output được ghi “needs context” nếu thiếu causal evidence; không tự động thành release violation.
- ADR có 4 drivers với definition/window, ≥2 alternatives, decision, positive/negative consequences, transition guardrails, Scrum boundary, owner và trigger.
- Decision có thể là keep hoặc simplify; PASS phụ thuộc reasoning/evidence, không phụ thuộc đáp án được ưa thích.
- Markdown không có whitespace error từ `git diff --check`; working tree sạch sau commit.

### Evidence

- `evidence/U06/fsck-classification.md` (output đã redact hoặc “no output observed” + supplied failure card).
- `decisions/ADR-GF-001-workflow-after-mvp.md`.
- `evidence/U06/cp03-adr-review.md` với PASS/REVISE và rationale.

### Troubleshooting

- `fsck` báo lỗi object nghiêm trọng, không chỉ unreachable → dừng, không sửa repository; lưu redacted output và xin facilitator reset fixture.
- ADR chỉ có option được chọn → REVISE; bổ sung viable alternative/trade-off.
- Metrics không có window/definition → ghi rõ synthetic sample và uncertainty trước khi kết luận.
- Decision “bỏ Git Flow vì cũ” → REVISE; trace lại cadence/version/lead-time/merge-cost.

### Reset/rollback

Không chạy garbage collection hoặc xóa object. Nếu fixture nghi ngờ hỏng, bỏ riêng bản sao Lab và tạo lại từ U05 source. Artifact edits được reset bằng bản sao mới; không rewrite U05 history.

## 🧪 Final validation (5 phút)

Reviewer dùng checklist:

1. Audit coverage `6/6`; correct detections `≥5/6`; mỗi finding có evidence source/layer/severity/owner/closure oracle.
2. `v0.1.1` được kiểm trên `main`; hotfix propagation được kiểm bằng `HOTFIX_CHANGE_COMMIT`.
3. Scrum boundary map giữ nguyên 3 artifact/commitment pairs và event purposes; Git evidence chỉ là supporting evidence.
4. `fsck` failure được phân loại theo context, không auto-violation.
5. ADR có 4 drivers, ≥2 options, decision/consequences/guardrails, owner/trigger/review condition.
6. `git diff --check` không báo lỗi; `git status --short --branch` sạch sau commit.

Một row thiếu exact evidence/owner/oracle hoặc ADR thiếu driver/trigger làm Lab REVISE.

## 📦 Deliverables và downstream reuse

- `project-artifacts/M-GF-06/git-flow-audit-report.md` gồm audit, traceability và Scrum boundary map.
- `decisions/ADR-GF-001-workflow-after-mvp.md`.
- `evidence/U06` gồm preflight, coverage, containment, fsck classification và ADR review notes.

Review **REV-GF-01** dùng report để kiểm integrated reasoning; Capstone **CAP-GF-01** dùng ADR structure/trigger với metrics cuối, không mặc định tái dùng cùng decision.

## ♻️ Reset, cleanup và khả năng chạy lại

Sau khi lưu deliverables theo quy định, đóng terminal/editor, xác nhận đường dẫn tuyệt đối kết thúc bằng `novashop-u06-lab`, rồi đưa riêng bản sao vào thùng rác nếu không còn cần. Không xóa U05 source, khóa học hoặc repository khác; không chạy `git gc` để “làm sạch” failure evidence.

## 📚 Provenance

- SRC-NVIE — context fit và Git Flow/simpler-flow decision.
- SRC-GIT-DOC — log, tag, branch containment, fsck semantics.
- SRC-SCRUM — artifacts, commitments, events và boundary.
- SRC-NS-TPL/CARD-U06 — professional artifact structure và six signs.
- [SUY DIỄN — từ scenario] Changed metrics, ambiguous failure card và timebox là fixtures đào tạo.

---
<!-- QUALITY GATE: MEX-U06-01 map CP-U06-01..03; every checkpoint có numbered Why/Action/Explanation + Verify/Expected/Evidence/Troubleshooting/Reset; changed metrics + failure path; audit/Scrum boundary/ADR đầy đủ; không có Assignment solution. -->

# Unit U04: Release Flow và ổn định MVP — Học liệu cốt lõi

> **Khóa học:** Git Flow thực chiến qua dự án NovaShop · **Thuộc:** Release and Production Change · **Mức xác thực:** simulated

## 🎯 Learning Outcomes

- **LO4.1 — Apply:** Vận hành release branch từ `develop` qua scope freeze, UAT fix, merge `main`/`develop` và đóng branch đúng topology.
- **LO4.2 — Create:** Gắn annotated tag và lập release evidence có version rationale, compatibility contract và traceability tới scope Done.

## 🧭 Ngữ cảnh nghề nghiệp/dự án và phần tăng trưởng của Unit

NovaShop đã hoàn tất integration milestone M-GF-03. Tại **M-GF-04**, Release Owner cần phát hành một MVP có mốc Git kiểm toán được mà không để feature mới chen vào giai đoạn ổn định.

Project increment gồm:

- **Release dossier v0.1.0:** frozen scope, release-only fixes, UAT/readiness decision, version rationale, changelog, tag audit và known limitations;
- **Release traceability matrix v0.1.0:** PBI/requirement → acceptance evidence → release commit → tag;
- evidence chứng minh annotated tag `v0.1.0` trỏ commit trên `main`, chính commit được tag thuộc lịch sử `develop` sau back merge, và release branch chỉ được đóng sau mọi gate.

Git Flow là team policy cho vòng đời release; Sprint không đồng nhất với release branch. Công việc chưa đạt Definition of Done trở lại Product Backlog, không được đưa vào release chỉ vì Sprint kết thúc hoặc sponsor gây áp lực.

## 📚 Nguồn đầu vào đã map

- **SRC-GIT-DOC:** Git Reference Manual 2.54.0, Git Project, truy cập 2026-08-25.
- **SRC-NVIE:** *A successful Git branching model*, Vincent Driessen, bản gốc 2010 và ghi chú 2020, truy cập 2026-08-25.
- **SRC-SEMVER:** Semantic Versioning 2.0.0, truy cập 2026-08-25.
- **SRC-SCRUM:** Scrum Guide, November 2020, truy cập 2026-08-25.
- **SRC-NS-CARDS:** NovaShop Git Flow change cards, artifact đào tạo nội bộ phiên bản 1.0.

---

## 1. Kiến thức tiên quyết và môi trường

### Kiến thức/kỹ năng tiên quyết

- Hoàn thành U03; đọc được branch graph, containment và conflict evidence.
- Biết `main` là production/released line, `develop` là integration line theo NovaShop policy.
- Có thể sửa Markdown/CSV, đọc Done scope, UAT finding và acceptance evidence.

### Môi trường, công cụ và phiên bản

- Repo Git local cô lập chỉ chứa artifact Markdown/CSV synthetic.
- Git CLI 2.40+; course verification dùng Git 2.54.0.windows.1.
- Markdown editor CommonMark-compatible và CSV editor UTF-8.
- Không remote production, deploy, credential, payment thật, PII hoặc mã nguồn ứng dụng.

Preflight:

```text
git --version
git status --short --branch
git branch --list main develop
git tag --list v0.1.0
git config --get user.name
git config --get user.email
```

Chỉ bắt đầu trên bản sao sạch khi `main`/`develop` tồn tại và tag mục tiêu chưa có. Nếu tag đã tồn tại, dùng clone Lab mới; không xóa/di chuyển một release tag đã công bố để “làm lại”.

### Phương thức xác minh artifact

`artifact_review`: reviewer kiểm release dossier/matrix cùng graph, tag object type, tag target và containment. Git evidence chứng minh topology; UAT/compatibility correctness vẫn cần artifact oracle.

### Hợp đồng ví dụ triển khai và thực hành

- **Mode:** `professional_artifact`.
- **Rationale:** Unit tạo release dossier, UAT/readiness decision, tag audit và traceability; không phát triển mã nguồn.
- **Worked example:** `MEX-U04-01` phủ LO4.1, LO4.2 và OUT-U04-01/02/03.
- **Lab pairing:** `MEX-U04-01` được biến đổi sang Order Tracking + Admin ở `LAB-U04-01`, checkpoint `CP-U04-01..03`.

## 2. Định vị trong lộ trình (Mental Map)

```text
develop có scope Done
        │ cut release/<version>
        ▼
scope freeze ── late feature ──► Product Backlog / develop cho release sau
        │
        ▼
UAT → release-only fix → recheck → readiness PASS
        │
        ▼
merge vào main → annotated tag
        │
        ▼
back merge released main vào develop → containment PASS → đóng release branch
        │
        ▼
U05: hotfix bắt đầu từ production baseline tag/main
```

Release branch là **stabilization lane**, không phải nơi tiếp tục phát triển mọi ý tưởng. Tag là tên bất biến của release object; branch là ref di động. Release dossier kết nối hai thế giới: quyết định nghiệp vụ (scope/UAT) và topology Git (merge/tag/back merge).

## 3. Nội dung lý thuyết cốt lõi

**Checklist bắt buộc phủ — giữ nguyên văn và đúng thứ tự Content Outlines:**

- [x] Cắt release từ develop, scope freeze và ranh giới release fix
- [x] UAT, release readiness, compatibility contract và version rationale
- [x] Merge release vào main/develop, annotated tag, đóng branch và kiểm chứng

#### OUT-U04-01 — Cắt release từ develop, scope freeze và ranh giới release fix

**Mapping:** OUT-U04-01 · LO4.1 · M-GF-04 / frozen scope + release dossier · MEX-U04-01

##### Định nghĩa rõ ràng

Release branch là branch ngắn hạn được cắt từ exact `develop` commit chứa scope Done dự kiến phát hành. **Scope freeze** là snapshot quyết định included/excluded scope và acceptance evidence tại cut point; nó không cấm mọi commit. Sau freeze, chỉ nhận thay đổi cần thiết để đưa candidate đã chọn tới release readiness: sửa UAT finding, metadata/version/changelog hoặc correction trực tiếp cho scope đã chọn.

Feature mới, redesign hoặc capability chưa thuộc frozen scope không phải release fix, dù thay đổi trông nhỏ. Chúng quay lại Product Backlog và dòng `develop` cho release tương lai.

##### Vấn đề/vai trò và quyết định cần đưa ra

Release Owner cần quyết định exact cut point; Product Owner xác nhận outcome/scope; nhóm xác nhận DoD/evidence. Mỗi late change được phân loại:

- **release fix:** đóng finding của scope hiện có, không mở rộng capability/contract;
- **new feature:** bổ sung behavior/value mới;
- **not ready:** thiếu DoD/UAT evidence, không thể hợp thức hóa bằng release branch.

Quyết định phải ghi included/excluded, rationale, owner và target release sau cho item bị loại.

##### Cơ chế và mental model

Khi tạo `release/0.1.0` từ `develop@D-cut`, ref release và develop cùng trỏ D-cut. Sau đó:

- `develop` có thể nhận feature cho tương lai;
- release branch chỉ tiến bằng release fixes;
- frozen scope manifest nối mỗi included PBI với exact commit/evidence tại D-cut;
- diff `D-cut..release-tip` phải chỉ chứa release fixes/metadata được phê duyệt.

Scope freeze là content/evidence boundary; branch name tự nó không ngăn scope creep.

##### Khi dùng / khi không dùng

- **Dùng:** release có giai đoạn ổn định/UAT độc lập, nhiều version cần coordination, hoặc `develop` phải tiếp tục tiến.
- **Không dùng như Sprint branch:** Sprint có thể tạo một hoặc nhiều increments; release cadence có thể khác Sprint cadence.
- **Không cần thiết:** nhóm continuous delivery đơn giản, một version, release từ `main` thường xuyên; workflow nhẹ hơn có thể phù hợp.
- **Trade-off:** release branch cô lập stabilization nhưng tạo thêm merge/back-merge cost và rủi ro divergence.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** Release Owner chuẩn bị NovaShop Search, Cart, Checkout và Payment sandbox.
- **Input/baseline/constraint:** bốn PBI Done tại `develop@D-cut`; sponsor đề nghị thêm Wishlist Export sau freeze; UAT chỉ phát hiện wording của Payment failure.
- **Decision/action:** cắt `release/0.1.0`; include bốn PBI; classify wording correction là release fix; exclude Wishlist Export về backlog.
- **Artifact/output:** frozen-scope table và release-change ledger.
- **Expected result:** diff sau cut không chứa Wishlist capability; mỗi release commit map tới UAT finding hoặc release metadata.
- **Verification/oracle/evidence:** `git merge-base --is-ancestor D-cut release/0.1.0`, changed-file review và scope table PASS/REVISE.

##### Ví dụ triển khai trong Material — MEX-U04-01, phần scope freeze

| Item | State at cut | Decision | Evidence/rationale |
| --- | --- | --- | --- |
| NS-101 Search | Done | INCLUDE | FR-01 acceptance evidence PASS |
| NS-102 Cart | Done | INCLUDE | FR-02 acceptance evidence PASS |
| NS-103 Checkout | Done | INCLUDE | FR-03 validation evidence PASS |
| NS-202 Payment failure | Done | INCLUDE | retry/input-preservation evidence PASS |
| UAT-PAY-01 wording | Finding on included behavior | RELEASE FIX | chỉ sửa mô tả, không đổi status ID/columns |
| Wishlist Export | Not in frozen baseline | EXCLUDE | capability mới; Product Backlog cho release sau |

`MEX-U04-01` bắt đầu từ table này. LAB-U04-01 thay scope bằng Order Tracking/Admin và late request Bulk Export (`CP-U04-01`).

##### Best practices

- **Rule:** release branch luôn cắt từ exact `develop` commit đã readiness-review. **Rationale:** cut point là provenance của scope. **Positive:** dossier lưu D-cut object ID. **Negative:** tạo release từ local feature tip làm scope chứa item chưa tích hợp.
- **Rule:** sau freeze chỉ nhận fix cần cho release; feature mới trở lại backlog/develop. **Rationale:** UAT cần baseline ổn định. **Positive:** wording fix có finding→commit→recheck. **Negative:** Wishlist Export chen vào vì “chỉ là một file”.
- **Rule:** mọi excluded item có reason/owner/next disposition. **Rationale:** loại khỏi release không đồng nghĩa làm mất Product Backlog transparency. **Positive:** late feature map release sau. **Negative:** xóa item khỏi manifest để giảm số finding.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** release diff có artifact không map finding/scope. **Nguyên nhân:** scope creep. **Chẩn đoán:** so `D-cut..release-tip` với change ledger. **Sửa:** loại capability khỏi release bằng reviewed revert/corrective change; giữ audit trail. **Phòng tránh:** release-only change gate.
- **Dấu hiệu:** PBI được ghi INCLUDE nhưng evidence còn REVISE. **Nguyên nhân:** nhầm Sprint completion với Done. **Chẩn đoán:** trace PBI→DoD evidence. **Sửa:** exclude và trả backlog. **Phòng tránh:** readiness review trước cut.
- **Dấu hiệu:** không biết release bắt đầu ở commit nào. **Nguyên nhân:** không lưu cut ref. **Chẩn đoán:** merge-base/graph, nhưng có thể mơ hồ nếu branch tiến xa. **Sửa:** reviewer xác nhận best available baseline và ghi limitation. **Phòng tránh:** lưu `git rev-parse release/<version>` ngay khi cut.

#### OUT-U04-02 — UAT, release readiness, compatibility contract và version rationale

**Mapping:** OUT-U04-02 · LO4.2 · M-GF-04 / UAT decision + version rationale · MEX-U04-01

##### Định nghĩa rõ ràng

**UAT** trong course là artifact-based acceptance exercise: stakeholder dùng scenario/expected behavior để kết luận PASS/REVISE cho candidate. **Release readiness** tổng hợp scope, DoD, UAT, known limitations, security/data checks và Git evidence thành quyết định release.

**Compatibility contract** xác định phần mà consumer được phép phụ thuộc, ví dụ CSV column IDs/status IDs của sandbox artifact. **Version rationale** giải thích tên phiên bản dựa trên contract và change type. Semantic Versioning chỉ có nghĩa khi public API/contract đã được tuyên bố; không được gắn nhãn MAJOR/MINOR/PATCH theo cảm tính rồi tuyên bố tuân SemVer.

##### Vấn đề/vai trò và quyết định cần đưa ra

UAT owner quyết định finding đã đóng; Release Owner quyết định candidate đủ gate; contract owner xác định thay đổi breaking/compatible so với phần đã công bố. Cần trả lời:

- scenario nào được chạy, expected/observed ra sao;
- finding nào block release và fix nào đóng nó;
- consumer contract nào ổn định;
- version label biểu đạt điều gì và điều gì **không** được tuyên bố.

##### Cơ chế và mental model

Readiness là conjunction: scope PASS **và** UAT PASS **và** contract/version rationale có căn cứ **và** evidence safety PASS. Một gate REVISE khiến overall REVISE; trung bình điểm không thay thế blocker.

Với NovaShop sandbox, contract công bố cho MEX gồm:

- column IDs: `status_id`, `domain`, `customer_meaning`, `input_behavior`;
- status IDs đã publish không đổi nghĩa;
- wording mô tả có thể sửa nếu ID/behavior không đổi.

Do đó sửa wording Payment có thể tương thích theo contract; đổi status ID hoặc xóa column là breaking theo contract. Vì version còn `0.y.z`, không suy ra production stability; dossier chỉ tuyên bố đây là first training MVP release theo policy nội bộ.

##### Khi dùng / khi không dùng

- **Dùng UAT/readiness gate:** có stakeholder acceptance và release handoff cần evidence.
- **Không dùng UAT để thay DoD:** UAT PASS không hợp thức hóa security/review finding chưa đóng.
- **Dùng SemVer claim:** chỉ khi public compatibility contract rõ và change classification được chứng minh.
- **Không dùng SemVer claim:** không có contract hoặc chỉ đổi số theo lịch; gọi đó là release naming policy.
- **Trade-off:** contract hẹp dễ giữ compatibility nhưng ít bảo đảm cho consumer; contract rộng hữu ích hơn nhưng làm thay đổi breaking khó hơn.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** sandbox consumer đọc Payment status CSV; UAT reviewer thấy wording khó hiểu.
- **Input/baseline/constraint:** ID `DECLINED_RETRYABLE` và columns đã publish; fix chỉ đổi `customer_meaning`; no PII/credential.
- **Decision/action:** giữ ID/columns/behavior; cập nhật wording; chạy UAT scenario retry/input preservation; ghi version rationale cho `v0.1.0` như first MVP under declared sandbox contract.
- **Artifact/output:** UAT finding→fix→recheck row, compatibility diff table, readiness verdict.
- **Expected result:** UAT PASS; contract diff compatible; không tuyên bố maturity hoặc universal SemVer compliance quá evidence.
- **Verification/oracle/evidence:** before/after schema comparison, UAT expected/observed, reviewer signature/role và release gate table.

##### Ví dụ triển khai trong Material — MEX-U04-01, phần readiness

| Gate | Expected | Observed | Verdict |
| --- | --- | --- | --- |
| Frozen scope | 4 Done PBIs, Wishlist excluded | refs/evidence đủ; late feature absent | PASS |
| UAT-PAY-01 | retryable decline wording rõ; input preserved | wording corrected; ID/behavior unchanged | PASS |
| Compatibility | columns/status IDs unchanged | only descriptive wording changed | PASS |
| Data safety | no PII/secret/real payment | synthetic content only | PASS |
| Known limitations | pre-1.0 training MVP disclosed | recorded in dossier | PASS |
| Overall readiness | all blocking gates PASS | all rows PASS | RELEASE PASS |

Version rationale: `0.1.0` là release đầu tiên của MVP đào tạo theo NovaShop policy; compatibility statement chỉ áp dụng declared sandbox CSV contract. Lab thay Payment wording bằng Order Tracking status semantics; Assignment dùng RC-401 với glossary contract khác.

##### Best practices

- **Rule:** tag/version rationale dựa trên compatibility contract đã công bố. **Rationale:** consumer impact mới quyết định compatibility, không phải số file đổi. **Positive:** wording đổi, ID/columns giữ nguyên được ghi compatible. **Negative:** đổi ID rồi gọi patch vì diff nhỏ.
- **Rule:** UAT finding phải có expected→observed→fix→recheck chain. **Rationale:** “đã sửa” không chứng minh behavior. **Positive:** finding ID map exact commit và recheck PASS. **Negative:** đóng ticket không có observed evidence.
- **Rule:** overall readiness fail khi một blocking gate fail. **Rationale:** DoD/release integrity không phải điểm trung bình. **Positive:** trì hoãn tag tới khi UAT PASS. **Negative:** tạo tag trước rồi sửa tag target sau.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** dossier ghi “SemVer patch” nhưng không nêu public contract. **Nguyên nhân:** dùng version như nhãn marketing. **Chẩn đoán:** tìm contract/consumer/change classification evidence. **Sửa:** công bố contract hợp lệ hoặc hạ claim thành naming policy. **Phòng tránh:** version-rationale template bắt buộc contract ref.
- **Dấu hiệu:** UAT PASS nhưng fix commit sau UAT. **Nguyên nhân:** evidence chạy trên candidate cũ. **Chẩn đoán:** so tested commit với release tip. **Sửa:** re-run UAT trên exact candidate. **Phòng tránh:** record candidate object ID trong mỗi run.
- **Dấu hiệu:** tag tồn tại khi readiness còn REVISE. **Nguyên nhân:** tag được tạo sớm. **Chẩn đoán:** tag target vs dossier commit chronology/content. **Sửa:** trên training clone chưa published, bỏ clone và tái chạy; không di chuyển tag đã công bố. **Phòng tránh:** tag creation là gate sau RELEASE PASS.

#### OUT-U04-03 — Merge release vào main/develop, annotated tag, đóng branch và kiểm chứng

**Mapping:** OUT-U04-03 · LO4.1, LO4.2 · M-GF-04 / tag audit + containment matrix · MEX-U04-01

##### Định nghĩa rõ ràng

Hoàn tất release gồm bốn trạng thái quan sát được:

1. release candidate đã readiness PASS được merge vào `main`;
2. annotated tag được tạo trên exact released commit;
3. released commit/fixes được back-merge vào `develop`;
4. release branch chỉ đóng sau containment/evidence PASS.

Annotated tag là một tag object có annotation/tagger metadata và trỏ tới object; lightweight tag chỉ là ref trực tiếp. `git tag -n` cho thấy annotation summary nhưng `git cat-file -t <tag>` mới phân biệt object type (`tag` đối với annotated tag).

##### Vấn đề/vai trò và quyết định cần đưa ra

Release Owner chọn exact target commit và annotation; maintainer chọn back-merge route; reviewer quyết định branch có thể đóng. NovaShop course policy back-merge **released `main` vào `develop`** sau tag để oracle `v0.1.0` là ancestor của cả hai branches. Cách này giữ exact main merge commit trong future line; trade-off là graph có thêm merge relation giữa long-lived branches.

##### Cơ chế và mental model

Topology dự kiến:

```text
R0──R1───────────────┐ release/0.1.0
 \                   ▼
  D-cut──D-next──────M-back (develop)
    \               /
     R0──R1──M-main (main, tag v0.1.0)
```

Thực tế parent layout phụ thuộc baseline, nhưng invariant là:

- tag object annotated;
- peeled tag commit thuộc `main`;
- tag commit thuộc `develop` sau back merge;
- release-only fix nằm trong cả hai future/prod lines;
- branch release không còn cần thiết sau gate.

##### Khi dùng / khi không dùng

- **Annotated tag:** dùng cho release cần annotation/audit; lightweight tag có thể phù hợp mốc local tạm nhưng không đạt NovaShop release policy.
- **Back merge:** bắt buộc khi release branch có fix không có trong `develop` hoặc course oracle yêu cầu exact released commit continuity.
- **Không đóng branch sớm:** giữ đến khi main/tag/develop containment đều PASS.
- **Không di chuyển published tag:** tag release là immutable contract; correction cần version/tag mới theo policy.
- **Trade-off:** merge `main` vào `develop` chứng minh exact tag ancestry nhưng có thể conflict với future work; conflict phải resolve theo U03 oracle.

##### Ví dụ thực tế cụ thể và có thể kiểm chứng

- **Context/stakeholder:** Release Owner bàn giao first NovaShop MVP.
- **Input/baseline/constraint:** `release/0.1.0` readiness PASS; Payment wording fix chỉ nằm trên release; `main` là released line; tag phải annotated.
- **Decision/action:** no-ff merge release→main; tag exact `main` tip; no-ff back merge main→develop; verify rồi đóng release branch.
- **Artifact/output:** tag audit, containment matrix, final graph và closed-branch evidence.
- **Expected result:** `git cat-file -t v0.1.0` = `tag`; tag commit ancestor `main` và `develop`; Payment fix present in both; release branch absent locally sau close.
- **Verification/oracle/evidence:** tag query, `merge-base --is-ancestor`, `branch --contains`, graph và artifact diff.

##### Ví dụ triển khai trong Material — MEX-U04-01, phần completion audit

| Check | Expected evidence | PASS result |
| --- | --- | --- |
| Main merge | release tip/commit contained in main | `merge-base --is-ancestor release-tip main` exit 0 |
| Annotated tag | tag object + annotation + peeled commit | type `tag`; annotation names scope/UAT; target = released main commit |
| Back merge | exact tag commit in develop | `merge-base --is-ancestor v0.1.0 develop` exit 0 |
| Release fix | UAT-PAY-01 correction in main/develop | artifact review and containment matrix PASS |
| Close | release branch removed only after gates | `git branch --list release/0.1.0` empty |

Course-policy sequence dùng trong MEX:

```text
git switch main
git merge --no-ff release/0.1.0 -m "merge(release): publish NovaShop v0.1.0"
git tag -a v0.1.0 -m "NovaShop v0.1.0; frozen scope and UAT PASS"
git switch develop
git merge --no-ff main -m "chore(release): back-merge v0.1.0 into develop"
```

Chỉ sau tag/containment review PASS mới xóa local release branch. Lab tái tạo flow với Order Tracking/Admin và chủ động quan sát containment FAIL trước back merge tại `CP-U04-03`.

##### Best practices

- **Rule:** annotated tag chỉ tạo sau readiness PASS trên exact `main` release commit. **Rationale:** tag là immutable handoff point. **Positive:** tag target tree chứa dossier PASS và UAT fix. **Negative:** tag release tip trước main merge hoặc khi UAT REVISE.
- **Rule:** release hoàn tất phải propagate fix vào `develop` và kiểm containment. **Rationale:** nếu không, future release có thể tái phát lỗi. **Positive:** exact tag commit ancestor của develop sau back merge. **Negative:** xóa release branch ngay sau main merge, để fix chỉ ở production line.
- **Rule:** phân biệt annotated với lightweight bằng object type. **Rationale:** tên/`tag -n` không đủ chứng minh tag object. **Positive:** `cat-file -t` trả `tag`. **Negative:** lightweight tag có đúng tên nhưng type là `commit` khi dereference trực tiếp.

##### Anti-pattern, failure modes và troubleshooting

- **Dấu hiệu:** `git cat-file -t v0.1.0` trả `commit`. **Nguyên nhân:** lightweight tag. **Chẩn đoán:** `git for-each-ref`/`cat-file`. **Sửa:** trên clone đào tạo chưa published, tái tạo release trong clone mới theo policy; không âm thầm thay published tag. **Phòng tránh:** dùng `git tag -a` và tag audit gate.
- **Dấu hiệu:** tag thuộc main nhưng ancestor check với develop fail. **Nguyên nhân:** chưa back merge exact released main. **Chẩn đoán:** graph và merge-base. **Sửa:** review/back merge `main` vào `develop`, resolve conflict và recheck. **Phòng tránh:** completion checklist bắt buộc containment cả hai lines.
- **Dấu hiệu:** back merge conflict với future feature. **Nguyên nhân:** `develop` tiến sau cut. **Chẩn đoán:** U03 conflict map, AC at risk và diff. **Sửa:** resolve theo business oracle hoặc abort để xin decision; không chọn một phía mặc định. **Phòng tránh:** nhỏ hóa release fixes và back merge ngay sau release.

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### MEX-U04-01 — Release dossier NovaShop v0.1.0

**Mapping:** LO4.1, LO4.2 · OUT-U04-01/02/03 · professional artifact · `LAB-U04-01/CP-U04-01..03`

#### Input/trạng thái ban đầu

- `develop@D-cut` chứa Search, Cart, Checkout và Payment artifacts Done.
- UAT-PAY-01 phát hiện wording Payment chưa rõ; IDs/columns/behavior đúng.
- Wishlist Export được đề nghị sau freeze và chưa có DoD evidence.
- `main` là released baseline cũ; tag `v0.1.0` chưa tồn tại.

#### Release dossier hoàn chỉnh

| Section | Decision/evidence |
| --- | --- |
| Scope | 4 Done PBIs INCLUDE; Wishlist Export EXCLUDE với backlog disposition |
| Release fix | UAT-PAY-01 wording-only; finding→commit→recheck PASS |
| Compatibility | declared CSV IDs/columns unchanged; wording compatible trong contract |
| Version | `0.1.0` first training MVP; không tuyên bố production maturity |
| UAT/readiness | all blocking rows PASS trước tag |
| Main/tag | release merged to main; annotated tag on exact released main commit |
| Back merge | released main merged into develop; tag commit/fix contained |
| Close | release branch đóng sau final audit |

#### Output mong đợi

- feature mới absent khỏi release scope/tree;
- annotated `v0.1.0` trên `main`;
- exact tagged commit là ancestor của `main` và `develop`;
- release fix hiện diện trong future line;
- release matrix không có orphan PBI/evidence/tag link.

#### Cách xác minh

```text
git tag -n --list v0.1.0
git cat-file -t v0.1.0
git rev-parse v0.1.0^{commit}
git merge-base --is-ancestor v0.1.0 main
git merge-base --is-ancestor v0.1.0 develop
git branch --contains v0.1.0
git branch --list release/0.1.0
git log --graph --decorate --oneline --all
git status --short --branch
```

PASS conditions: annotation hiện; object type `tag`; two ancestor checks exit 0; `main`/`develop` nằm trong containment output; local release branch query trống sau close; working tree sạch. Reviewer đồng thời kiểm frozen scope/UAT/contract matrix.

### Mapping Material worked example → Hands-on Lab tương ứng

- `MEX-U04-01` → `LAB-U04-01/CP-U04-01`: tái tạo dossier/tag với Order Tracking + Admin và late Bulk Export.
- `MEX-U04-01` → `LAB-U04-01/CP-U04-02`: chứng minh exact tag commit thuộc `main`, scope/UAT traceability đầy đủ.
- `MEX-U04-01` → `LAB-U04-01/CP-U04-03`: quan sát failure trước back merge, khôi phục continuity và đóng release branch.

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

| Dấu hiệu | Nguyên nhân | Chẩn đoán/bằng chứng | Khắc phục an toàn | Phòng tránh |
| --- | --- | --- | --- | --- |
| Tag đã có trước UAT PASS | Tag quá sớm | tag target tree vs dossier verdict | dùng clone đào tạo mới; không move published tag | tag gate sau readiness |
| Candidate chứa late feature | scope freeze chỉ là lời nói | cut-to-tip diff vs ledger | reviewed revert/exclude rồi re-UAT | every commit maps finding/metadata |
| Tag type là commit | lightweight tag | `git cat-file -t` | tái chạy release trên clone chưa published | `tag -a` + object-type audit |
| Main PASS, develop FAIL | thiếu back merge | ancestor check/graph | merge released main vào develop, resolve/recheck | back merge ngay sau release |
| UAT evidence trỏ commit cũ | candidate thay sau test | compare tested SHA/release tip | re-run UAT on exact tip | record candidate ID per run |
| Release branch đã xóa, gate fail | close quá sớm | refs/graph/evidence | dùng tagged/main refs để recovery có review; không dựng lịch sử giả | close là bước cuối sau audit |

## 6. Từ điển thuật ngữ và mô hình tư duy

| Thuật ngữ | Nghĩa trong Unit |
| --- | --- |
| Release branch | stabilization branch ngắn hạn cắt từ Done `develop` baseline |
| Scope freeze | snapshot included/excluded scope và evidence tại cut point |
| Release fix | thay đổi cần thiết để scope đã chọn đạt release gate, không mở capability mới |
| UAT | stakeholder acceptance trên exact candidate với expected/observed evidence |
| Compatibility contract | phần interface/artifact consumers được phép phụ thuộc |
| Version rationale | lý do version dựa trên contract/change, không dựa cảm tính |
| Annotated tag | Git tag object có annotation/tagger, dùng làm release handoff |
| Peeling | resolve annotated tag qua tag object tới commit target |
| Back merge | đưa released state/fix trở lại dòng phát triển tương lai |
| Containment | ancestor proof rằng tag/commit thuộc branch history |

Mô hình nhớ: **Freeze → Fix only → Accept → Tag exact commit → Back merge → Prove → Close**.

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

- Git Reference Manual 2.54.0: `git branch`, `git merge`, `git tag`, `git cat-file`, `git rev-parse`, `git merge-base`.
- Vincent Driessen, *A successful Git branching model*: release branch roles và merge-back concept.
- Semantic Versioning 2.0.0: public API/compatibility premise và `0.y.z` semantics.
- Scrum Guide 2020: Definition of Done/Increment; release branch không phải Scrum component.
- NovaShop Change Cards/Backlog synthetic: M-GF-04 scenarios và acceptance oracle.

### Phần bổ sung/suy diễn

- **[BỔ SUNG — nguồn: Git Reference Manual 2.54.0]** NovaShop course policy back-merges tagged `main` into `develop` để exact tag commit thỏa containment oracle của plan.
- **[BỔ SUNG — nguồn: Semantic Versioning 2.0.0]** Version claim chỉ có nghĩa trong declared compatibility contract; `0.1.0` không tự chứng minh maturity.
- **[SUY DIỄN — từ kiến thức đã huấn luyện]** Release dossier table, Wishlist request và UAT-PAY-01 là fixture synthetic cho đào tạo; không đại diện release production thật.

---
<!-- QUALITY GATE: 3/3 outline leaf đã tick đúng thứ tự; từng leaf đủ semantic contract và concrete oracle; MEX-U04-01 phủ LO/outline, map CP-U04-01..03; tag/back-merge semantics khớp plan; không mã nguồn ứng dụng. -->

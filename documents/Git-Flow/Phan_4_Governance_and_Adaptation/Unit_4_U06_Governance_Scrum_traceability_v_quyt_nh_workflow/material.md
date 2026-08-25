# Unit U06: Governance, Scrum traceability và quyết định workflow — Học liệu cốt lõi

> **Khóa học:** Git Flow thực chiến qua dự án NovaShop · **Hình thức:** project-based, không lập trình ứng dụng · **Thuộc:** Governance and Adaptation

## 🎯 Learning Outcomes

- **LO6.1** [evaluate] — Audit lịch sử NovaShop để phát hiện ít nhất 5/6 vi phạm branch, review, tag hoặc back-merge và đề xuất remediation có owner.
- **LO6.2** [create] — Viết ADR đánh giá tiếp tục Git Flow hay chuyển workflow đơn giản hơn dựa trên cadence, số version hỗ trợ, lead time và merge cost.

## 🧭 Ngữ cảnh dự án và phần tăng trưởng của Unit

NovaShop đã có lịch sử feature, release `v0.1.0`, hotfix `v0.1.1` và evidence packs. Nhóm không được mặc định “đã dùng Git Flow thì phải dùng mãi”. Học viên đóng vai workflow reviewer: phân loại evidence theo đúng tầng quy tắc, sửa phát biểu sai về Scrum, tạo remediation backlog có owner và viết ADR có trigger đánh giá lại.

Project increment **M-GF-06**:

- `project-artifacts/M-GF-06/git-flow-audit-report.md`;
- `decisions/ADR-GF-001-workflow-after-mvp.md`;
- remediation backlog có finding, severity, owner, closure oracle;
- statement ranh giới rõ: Git Flow/Git evidence có thể hỗ trợ transparency nhưng không thay thế Scrum artifact, commitment hoặc event.

Increment đạt khi audit phủ 100% sáu dấu hiệu supplied, phát hiện đúng ít nhất 5/6, không đánh đồng capability của Git với policy, ADR có alternatives/trade-off/cadence/version/lead-time/merge-cost và trigger. Bối cảnh, số liệu và lịch sử là **simulated**.

## 📚 Nguồn đầu vào đã map

- **SRC-NVIE** — *A successful Git branching model* (2010; reflection 2020).
- **SRC-GIT-DOC** — Git Reference Manual 2.54.0.
- **SRC-PROGIT** — Pro Git, 2nd Edition.
- **SRC-CONV** — Conventional Commits 1.0.0.
- **SRC-SCRUM** — Scrum Guide, November 2020.
- **SRC-NS-TPL** — NovaShop professional artifact templates 1.0, internal approved.

---

## 1. Kiến thức tiên quyết và môi trường

Học viên đã hoàn thành U05; biết đọc graph, ref, ancestor/containment, tag object và review record. Dùng Git CLI 2.40+, Markdown/CommonMark, CSV UTF-8 trong bản sao local không có remote production.

Preflight:

```text
git --version
git status --short --branch
git log --graph --decorate --oneline --all
git show-ref --heads --tags
```

Môi trường sẵn sàng khi repository mở được, refs trong sample tồn tại và output đã được rà soát để không lộ email/path/remote URL. “Branch protection” trong Unit được đánh giá qua working agreement, review evidence và audit fixture; khóa không tuyên bố đã cấu hình một hosting platform cụ thể.

## 2. Định vị trong lộ trình (Mental Map)

U01–U05 trả lời “vận hành Git Flow thế nào”; U06 trả lời hai câu khó hơn: “workflow có đang được tuân thủ bằng evidence không?” và “workflow này còn phù hợp với bối cảnh không?”. Review/Capstone sẽ dùng report/ADR để giải thích quyết định cuối.

```text
Expected rule/policy
   + observed Git/artifact evidence
   → classify rule layer
   → finding + severity + impact
   → remediation + owner + closure oracle
   → delivery metrics/context
   → ADR: keep / simplify / transition
   → review trigger
```

## 3. Nội dung lý thuyết cốt lõi

**📋 Checklist bắt buộc phủ — giữ nguyên văn và đúng thứ tự Content Outlines:**

- [x] Branch protection, review policy, traceability và anti-pattern audit
- [x] Ánh xạ Git evidence với Scrum mà không thay thế artifact, commitment hoặc event
- [x] Đánh giá độ phù hợp và ADR Git Flow so với workflow đơn giản hơn

#### OUT-U06-01 Branch protection, review policy, traceability và anti-pattern audit

**Mapping:** OUT-U06-01 · LO6.1 · M-GF-06, audit report và remediation backlog.

##### Định nghĩa và ranh giới

- **Branch protection** là policy hạn chế cách ref quan trọng được cập nhật, ví dụ yêu cầu review hoặc cấm force update. Git local tự thân không biết “approved PR”; enforcement thường thuộc hosting/process. Trong khóa, chỉ audit policy/evidence, không giả định một vendor.
- **Review policy** định nghĩa ai review, evidence nào bắt buộc, finding severity nào chặn merge và cách disposition.
- **Traceability** là quan hệ có thể đi hai chiều từ issue/requirement → change/commit → review → release/tag → acceptance evidence và ngược lại.
- **Anti-pattern audit** so observed evidence với rule có nguồn, phân loại chênh lệch và tạo remediation kiểm chứng được.

Một hành vi Git cho phép không tự động là hành vi team cho phép. Lightweight tag hợp lệ về Git nhưng vẫn vi phạm policy “release dùng annotated tag”. Ngược lại, object unreachable không tự động chứng minh corruption hoặc force-push violation; cần context/evidence bổ sung.

##### Vấn đề, vai trò và quyết định

Workflow reviewer phải quyết định mỗi finding thuộc tầng nào, có bằng chứng chính xác không, severity/impact là gì, ai sở hữu remediation và oracle đóng finding. Release owner dùng kết quả để giảm risk; Scrum Master có thể giúp nhóm nhìn rõ practice nhưng không trở thành approver kỹ thuật mặc định.

##### Cơ chế và mental model

Audit loop:

1. **Expected:** ghi rule và nguồn/tầng quy tắc.
2. **Observed:** ghi ref, graph, review record hoặc statement chính xác.
3. **Compare:** PASS/REVISE; không suy diễn vượt evidence.
4. **Classify:** Git integrity, Git Flow convention, team policy hay Scrum definition.
5. **Remediate:** hành động nhỏ nhất, owner và closure oracle.
6. **Recheck:** lưu before/after evidence; không rewrite lịch sử chỉ để xóa dấu vết.

| Tầng | Ví dụ | Điều không được kết luận |
| --- | --- | --- |
| Git capability/integrity | ref, object, ancestor, reachable/unreachable | “Git cấm direct commit” nếu không có policy |
| Git Flow convention | feature từ `develop`; release back-merge; hotfix targets | “Đây là rule Scrum” |
| Team policy | annotated tag, required review, no force-update shared branch | “Git object không hợp lệ” chỉ vì vi phạm policy |
| Scrum definition | artifacts, commitments, events, accountabilities | “Sprint Review là release approval gate bắt buộc” |

##### Khi dùng, khi không dùng và trade-off

- Audit theo sample refs sau release/hotfix, khi incident lặp lại hoặc trước thay đổi workflow.
- Không biến audit thành săn lỗi cá nhân; severity dựa trên impact/khả năng tái diễn.
- Không dùng commit-message format làm bằng chứng duy nhất. Conventional Commits làm intent dễ đọc/máy xử lý hơn, nhưng message `fix:` không chứng minh review, regression hay release containment.
- Governance mạnh giảm ambiguity nhưng tăng thời gian/chuyển giao; policy phải tương xứng risk và được đo bằng lead time/merge cost.

##### Ví dụ thực tế riêng và oracle

- **Context:** audit thấy release fix commit không có trong `develop`.
- **Input:** tag/release graph, SHA `RELEASE_FIX_COMMIT`, release review record.
- **Decision/action:** classify Git Flow continuity violation, severity High vì lỗi có thể tái xuất ở release sau; owner là release owner.
- **Artifact:** finding `F-04` với remediation “back-merge đúng route và chạy containment/regression”.
- **Expected:** `git merge-base --is-ancestor RELEASE_FIX_COMMIT develop` từ exit `1` thành `0` sau remediation.
- **Oracle/evidence:** before/after exit status, graph và review disposition; không xóa commit cũ.

##### Liên kết ví dụ triển khai trong Material

Phần Audit của **MEX-U06-01** hiện thực OUT-U06-01 và phát hiện 6/6 dấu hiệu. Lab **CP-U06-01/02** dùng một sample khác và yêu cầu tối thiểu 5/6, có containment changed input.

##### Best practices

| Rule | Rationale/cơ chế | Positive example | Negative example/hậu quả |
| --- | --- | --- | --- |
| Mỗi finding ghi tầng quy tắc và exact evidence | Tránh gọi team convention là Git/Scrum rule | “Policy TAG-01; `cat-file` observed `commit`” | “Tag sai” không nguồn; remediation tùy tiện |
| Closure oracle phải nhị phân/quan sát được | Owner biết khi nào đóng | ancestor exit `0` + review record PASS | “Đã xử lý”; reviewer không tái lập |
| Không rewrite shared history để làm audit sạch | Audit cần bảo toàn dấu vết và phối hợp | forward remediation + prevention | force-push che direct commit; mất traceability |

##### Anti-pattern, failure modes và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán | Cách sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| Mọi finding đều “Critical” | Không có severity model | Impact/risk không khác nhau | Calibrate severity theo release/data/history impact | Severity rubric trong policy |
| `git fsck` có unreachable object và audit gọi corruption | Nhầm reachability với integrity | Đọc loại message, reflog/branch-deletion context | Ghi “needs context”; chỉ kết luận khi có evidence | Failure classification checklist |
| Commit message có issue ID nhưng requirement vẫn mồ côi | Traceability một chiều | Đi ngược release → evidence → requirement | Bổ sung bidirectional matrix | Review link completeness gate |

#### OUT-U06-02 Ánh xạ Git evidence với Scrum mà không thay thế artifact, commitment hoặc event

**Mapping:** OUT-U06-02 · LO6.1 · M-GF-06, Scrum boundary statement và corrected working agreement.

##### Định nghĩa và ranh giới

Scrum Guide 2020 định nghĩa ba artifacts và commitments tương ứng: Product Backlog ↔ Product Goal, Sprint Backlog ↔ Sprint Goal, Increment ↔ Definition of Done; đồng thời định nghĩa các events trong Sprint. Git branches, commits, pull requests, release tags và Git Flow **không** là artifact, commitment hay event của Scrum. Chúng là practices có thể hỗ trợ transparency/inspection khi phù hợp.

“Map” nghĩa là chỉ ra evidence nào giúp inspect một Scrum concern, không đổi tên evidence thành Scrum element. Một tag có thể hỗ trợ truy vết release nhưng không chứng minh Increment usable hoặc DoD đạt. Sprint Review nhằm inspect outcome và quyết định adaptation; nó không được Scrum định nghĩa là release approval gate.

##### Vấn đề, vai trò và quyết định

Nhóm phải quyết định working agreement nào là team policy và statement nào mô tả Scrum. Product Owner quản lý Product Backlog/value; Developers tạo usable Increment và tuân DoD; Scrum Master giúp hiểu/enact Scrum. Git review permissions không được dùng để âm thầm thay đổi các accountability này.

##### Cơ chế và mental model

Dùng hai cột “Scrum concern” và “supporting evidence”, rồi thêm guardrail “không thay thế”:

| Scrum concern | Git/project evidence có thể hỗ trợ | Không thay thế |
| --- | --- | --- |
| Product Backlog transparency | Issue ID, backlog CSV change history | Product Backlog, Product Goal, Product Owner ordering |
| Sprint plan/goal inspection | Branch/PR links tới selected PBI | Sprint Backlog hoặc Sprint Goal |
| Increment/DoD transparency | reviewed diff, regression record, tag/release note | Usable Increment và Definition of Done evidence tổng thể |
| Sprint Review adaptation | graph/release outcome làm input thảo luận | Sprint Review event hoặc stakeholder collaboration |
| Retrospective improvement | audit metrics/findings | Sprint Retrospective event/inspection của cách làm |

Oracle boundary dùng câu hỏi: “Nếu Git ref biến mất, Scrum element có còn được định nghĩa độc lập không?” Nếu không, mapping đang thay thế sai.

##### Khi dùng, khi không dùng và trade-off

- Dùng Git evidence để tăng transparency của work/release khi evidence được giải thích và liên kết.
- Không định nghĩa Done bằng “đã merge”; DoD có thể yêu cầu evidence ngoài Git.
- Không trì hoãn release đến Sprint Review chỉ vì gọi đó là rule Scrum; nếu business chọn review gate, ghi rõ là organization/team release policy.
- Mapping quá nhiều làm Scrum artifact thành report kỹ thuật khó dùng; chỉ giữ evidence phục vụ decision/inspection.

##### Ví dụ thực tế riêng và oracle

- **Context:** working agreement ghi “Sprint Review là release gate bắt buộc của Scrum”.
- **Input:** statement, Scrum event purpose, NovaShop release policy.
- **Decision/action:** audit REVISE; tách thành hai câu: Sprint Review inspect outcome/adaptation; NovaShop **team policy** có thể yêu cầu release review riêng trước publish.
- **Artifact:** corrected boundary statement với owner Scrum Master cho coaching và release owner cho policy.
- **Expected:** không còn câu gọi Git Flow/release gate là Scrum requirement; mapping vẫn giữ Git evidence làm input inspection.
- **Oracle:** reviewer đối chiếu danh mục Scrum artifacts/commitments/events và tìm không thấy Git Flow/tag/PR; working agreement ghi đúng nguồn policy.

##### Liên kết ví dụ triển khai trong Material

Phần Scrum boundary của **MEX-U06-01** hiện thực OUT-U06-02. Lab **CP-U06-01** phân loại finding F-06; **CP-U06-02** sửa traceability map mà không biến tag thành Increment.

##### Best practices

| Rule | Rationale/cơ chế | Positive example | Negative example/hậu quả |
| --- | --- | --- | --- |
| Gắn nhãn “Scrum definition” hoặc “team practice” | Ngăn governance tự tạo rule giả | “Required PR review — NovaShop policy” | “Scrum yêu cầu PR approval” |
| Dùng Git evidence làm input inspection, không proxy duy nhất | Git không quan sát toàn bộ usability/value | Tag + DoD evidence + stakeholder outcome | “Có tag nên Increment Done” |
| Release decision tách khỏi Sprint Review purpose | Scrum cho phép practice context-specific; Review không phải approval gate | Release review riêng, Review inspect outcome | Hoãn value vô lý hoặc biến Review thành sign-off meeting |

##### Anti-pattern, failure modes và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán | Cách sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| Sprint Goal được suy từ tên branches | Nhầm work decomposition với commitment | So Sprint Backlog/Goal statement | Khôi phục explicit Sprint Goal; branch chỉ link PBI | Boundary table trong working agreement |
| “Merged = Done” | Dùng Git state thay DoD | Đối chiếu DoD evidence còn thiếu | Trả PBI về trạng thái phù hợp, không hạ DoD | DoD checklist độc lập |
| Sprint Review chỉ đọc release log | Evidence lấn át outcome/adaptation | Agenda thiếu stakeholder outcome/next decision | Dùng log làm input, phục hồi working session | Review purpose check |

#### OUT-U06-03 Đánh giá độ phù hợp và ADR Git Flow so với workflow đơn giản hơn

**Mapping:** OUT-U06-03 · LO6.2 · M-GF-06, ADR-GF-001.

##### Định nghĩa và ranh giới

**ADR (Architecture/Workflow Decision Record)** lưu context, drivers, options, decision, consequences và trigger review. Ở đây:

- **Git Flow:** `main` + `develop` dài hạn; feature/release/hotfix branches có routing riêng.
- **Flow đơn giản hơn:** một `main` luôn sẵn sàng phát hành, topic branches ngắn hạn từ `main`, review/merge lại `main`, release/tag từ `main`; không có `develop`/release branch dài hạn mặc định.

Đây là lựa chọn process context-specific, không phải “workflow hiện đại luôn tốt hơn”. Reflection 2020 của mô hình Git Flow khuyến nghị cân nhắc flow đơn giản cho continuous delivery/web app và vẫn xem Git Flow phù hợp khi explicit versioning hoặc hỗ trợ nhiều versions thực sự cần thiết.

##### Vấn đề, vai trò và quyết định

Nhóm phải quyết định governance có tương xứng với cadence/risk không. ADR owner tổng hợp evidence; team góp dữ liệu; stakeholder chấp nhận consequence. Quyết định không dựa trên sở thích diagram hay số branch, mà dựa trên drivers đã định nghĩa.

##### Cơ chế và mental model

| Driver | Cách đo trong scenario | Git Flow thuận lợi khi | Flow đơn giản thuận lợi khi |
| --- | --- | --- | --- |
| Release cadence | Khoảng thời gian giữa releases | planned stabilization window có giá trị | release thường xuyên/continuous |
| Concurrent supported versions | Số version lines cần patch song song | ≥2 lines thực sự được hỗ trợ | một production line |
| Lead time | Từ change ready tới release | release batching là chủ đích | waiting trên release branch chiếm phần lớn |
| Merge cost | Conflict/giờ coordination/back-merge | cost đổi lấy isolation cần thiết | cost lặp vượt giá trị isolation |

Không có ngưỡng phổ quát. ADR phải ghi số liệu scenario, định nghĩa phép đo, thời gian quan sát và uncertainty. Decision matrix hỗ trợ suy nghĩ, không tự động ra quyết định.

##### Khi dùng, khi không dùng và trade-off

- Viết ADR sau có đủ release/hotfix evidence hoặc khi context đổi đáng kể.
- Không đổi workflow giữa incident chỉ để giảm áp lực tức thời.
- Git Flow tạo isolation/version governance nhưng tăng branch aging/back-merge cost.
- Flow đơn giản giảm topology/lead time nhưng đòi `main` readiness, review/automation/rollback discipline mạnh; “ít branch” không đồng nghĩa ít kiểm soát.
- Luôn có migration scope, owner, success metrics và trigger quay lại/đánh giá lại.

##### Ví dụ thực tế riêng và oracle

- **Context:** sau MVP, NovaShop là web app mô phỏng với một production line, cadence mục tiêu hàng tuần.
- **Input:** 4 releases synthetic; median ready-to-release lead time `3.5 ngày`, trong đó `2 ngày` chờ release branch; merge/back-merge cost `5 person-hours/release`; không có yêu cầu support hai versions.
- **Decision/action:** ADR chọn thử flow đơn giản sau `v0.2.1`, giữ annotated tag/review/DoD gates; transition không diễn ra giữa hotfix.
- **Artifact:** ADR có Option A giữ Git Flow, Option B flow đơn giản, decision, consequences, owner và review trigger.
- **Expected:** reviewer truy ngược được mỗi conclusion tới driver; trigger “hỗ trợ ≥2 version lines hoặc compliance cần stabilization branch” khiến ADR được xem lại.
- **Oracle:** đủ 4 drivers, ≥2 alternatives, consequence thuận/nghịch, trigger đo được, peer review PASS.

##### Liên kết ví dụ triển khai trong Material

Phần ADR của **MEX-U06-01** hiện thực OUT-U06-03. Lab **CP-U06-03** dùng changed metrics khác, có ambiguous `git fsck` output và buộc học viên tự chọn/biện minh thay vì copy decision.

##### Best practices

| Rule | Rationale/cơ chế | Positive example | Negative example/hậu quả |
| --- | --- | --- | --- |
| Decision trace tới driver/evidence | Tránh workflow-by-fashion | “one version + weekly cadence + 2-day wait” | “Git Flow nhiều branch nên bỏ” |
| Nêu consequence và migration guardrail | Mọi option đổi loại risk | Giữ tag/review/DoD khi bỏ `develop` | Xóa governance cùng branch model |
| ADR có trigger/review date | Context thay đổi làm decision cũ hết phù hợp | Revisit khi hỗ trợ ≥2 lines | “Quyết định vĩnh viễn”; team áp giáo điều |

##### Anti-pattern, failure modes và troubleshooting

| Dấu hiệu | Nguyên nhân | Chẩn đoán | Cách sửa | Phòng tránh |
| --- | --- | --- | --- | --- |
| ADR chỉ có option được chọn | Confirmation bias | Alternatives/trade-offs rỗng | Bổ sung ≥2 viable options | ADR review checklist |
| Metrics không có định nghĩa/window | Số liệu không so sánh được | Không biết lead time bắt đầu/kết thúc | Ghi definition, sample, uncertainty | Metric glossary |
| Chọn flow đơn giản nhưng `main` không release-ready | Bỏ branch mà không chuyển controls | Audit main/review/DoD gaps | Transition có guardrails/pilot | Readiness gate trước migration |

## 4. Ví dụ tích hợp liên khái niệm có thể kiểm chứng

### MEX-U06-01 — Audit report và workflow ADR sau NovaShop MVP

**Mode:** professional artifact · **LO:** LO6.1, LO6.2 · **Outline:** OUT-U06-01..03 · **Mức xác thực:** simulated.

#### Input/trạng thái ban đầu

- CARD-U06 cung cấp sáu dấu hiệu audit.
- Graph/review/tag/containment outputs đã redact.
- Delivery metrics synthetic: weekly target cadence; một supported production line; median lead time `3.5 ngày`; release-branch waiting `2 ngày`; merge/back-merge `5 person-hours/release`.

#### Professional artifact A — Audit matrix hoàn chỉnh

| ID | Observed evidence | Classification | Severity | Remediation / owner / closure oracle |
| --- | --- | --- | --- | --- |
| F-01 | Direct commit trên `main`, không review record | Team branch/review policy; Git cho phép kỹ thuật | High | Release owner: forward remediation + protection review; close khi mọi sampled main update có review evidence |
| F-02 | Feature tách từ `main` | Git Flow routing violation | Medium | Practitioner: tạo feature đúng source ở change kế; close bằng graph/source oracle, không rewrite shared branch |
| F-03 | `cat-file` cho release tag ra `commit` | Annotated-tag team policy; lightweight tag vẫn hợp lệ Git | Medium | Release owner: ghi finding, không move shared tag; next tag type phải `tag` |
| F-04 | Release fix không ancestor của `develop` | Git Flow back-merge/continuity violation | High | Release owner: back-merge + regression; close khi ancestor exit `0` |
| F-05 | Evidence log có shared rebase/force-update | Team history-safety policy | High | Team owner: coordinate restore/forward fix, add no-force rule; close bằng ref/review evidence |
| F-06 | “Sprint Review là release gate bắt buộc của Scrum” | Sai Scrum boundary | Medium | Scrum Master + release owner: sửa statement; close khi Scrum purpose và team release policy tách rõ |

Kết quả: **6/6 signs được phát hiện và phân loại**, vượt oracle LO6.1 tối thiểu 5/6. Không finding nào chỉ dựa trên tên branch hoặc `fsck` output đơn lẻ.

#### Professional artifact B — Scrum boundary map

| Git evidence | Hỗ trợ inspect | Không thay thế | Status |
| --- | --- | --- | --- |
| Issue/commit/review links | Product/Sprint Backlog transparency | Product Backlog, Sprint Backlog, Goals | PASS nếu links đủ; không rename |
| Regression/tag/release note | Increment/DoD transparency | Usable Increment, DoD | PASS khi DoD evidence riêng tồn tại |
| Audit findings/metrics | Retrospective input | Sprint Retrospective | PASS khi dùng làm input adaptation |
| Sprint Review release-gate statement | Không áp dụng | Sprint Review purpose | REVISE; tách team policy |

#### Professional artifact C — ADR-GF-001 excerpt

| Trường | Nội dung mẫu |
| --- | --- |
| Context | Web MVP, một supported line, weekly cadence; Git Flow back-merge tạo waiting/cost |
| Option A | Giữ classic Git Flow: isolation rõ, nhưng tiếp tục release/back-merge overhead |
| Option B | Main + short-lived topic branches: giảm waiting; cần stronger main readiness |
| Decision | Pilot Option B sau `v0.2.1`; không đổi giữa incident; giữ review, annotated tags, DoD/evidence gates |
| Consequences | Bỏ `develop`/release branch mặc định; policy/source-target/evidence naming phải cập nhật |
| Scrum boundary | Đây là workflow decision của team, không phải thay đổi Scrum |
| Trigger | Review lại nếu cần hỗ trợ ≥2 version lines, audit risk tăng, hoặc main readiness gate không đạt |

#### Verification oracle

MEX PASS khi:

1. audit có 6 rows, exact evidence, classification, severity, owner và closure oracle; ít nhất 5 rows đúng;
2. boundary map không gọi Git Flow/tag/PR là Scrum element và không gọi Sprint Review là release gate bắt buộc;
3. ADR có cadence, version count, lead time, merge cost, ≥2 options, decision/consequences/trigger;
4. peer reviewer có thể kết luận PASS/REVISE mà không hỏi tác giả.

### Mapping Material worked example → Hands-on Lab tương ứng

- **MEX-U06-01 → LAB-U06-01/CP-U06-01:** tái tạo audit trên sample refs mới và phân loại sáu dấu hiệu.
- **MEX-U06-01 → LAB-U06-01/CP-U06-02:** thay containment input, sửa traceability/Scrum boundary bằng before-after evidence.
- **MEX-U06-01 → LAB-U06-01/CP-U06-03:** changed delivery metrics + ambiguous unreachable object; tạo ADR độc lập và prevention rule.

## 5. Lỗi thường gặp, troubleshooting và quy tắc áp dụng

1. **Không phân biệt policy với Git capability:** luôn ghi cột Rule layer/source; “Git cho phép” và “team cho phép” là hai câu khác nhau.
2. **Đọc `--is-ancestor` bằng stdout:** command dùng exit status `0/1`; lưu exit status trong evidence.
3. **Coi mọi unreachable object là violation:** `git fsck --no-reflogs --unreachable` cần context; branch deletion hợp lệ cũng có thể để object unreachable.
4. **Traceability chỉ xuôi:** lấy một tag/release bất kỳ và đi ngược tới requirement/oracle; link thiếu làm finding REVISE.
5. **ADR chọn flow trước rồi mới tìm metrics:** khóa decision drivers/options trước khi score; peer-review assumption và uncertainty.
6. **Nhầm Scrum với release governance:** dùng boundary checklist: artifact, commitment, event/accountability có trong Scrum Guide hay là practice context-specific?

## 6. Từ điển thuật ngữ và mô hình tư duy

| Thuật ngữ | Nghĩa trong Unit |
| --- | --- |
| Protection | Policy kiểm ref update; enforcement phụ thuộc platform/process |
| Review gate | Team policy về evidence/approval trước merge/release |
| Traceability | Điều hướng hai chiều requirement–change–review–release–oracle |
| Finding | Chênh lệch expected/observed có evidence và remediation |
| Rule layer | Git capability, Git Flow convention, team policy hoặc Scrum definition |
| Closure oracle | Điều kiện quan sát để đổi finding thành closed |
| Scrum boundary | Phân biệt Scrum elements với practices/evidence hỗ trợ |
| ADR | Record context, drivers, options, decision, consequences, trigger |
| Supported version line | Dòng phiên bản đang cần nhận patch song song |
| Lead time | Khoảng thời gian được định nghĩa từ change ready tới released |
| Merge cost | Conflict/coordination/back-merge effort theo sample window |

## 7. Nguồn tham khảo và provenance phần bổ sung

### Nguồn được dùng

- https://nvie.com/posts/a-successful-git-branching-model/ — Git Flow model và reflection về simpler flow/context.
- https://git-scm.com/docs/git — refs, tags, log, branch, fsck, ancestor evidence.
- https://git-scm.com/book/en/v2 — branching/history mental model.
- https://www.conventionalcommits.org/en/v1.0.0/ — intent-readable commit convention và giới hạn của message evidence.
- https://scrumguides.org/scrum-guide.html — Scrum artifacts, commitments, events, purposes/accountabilities.
- `starter/templates/GitFlow_Artifact_Templates.md` và `starter/NovaShop_Change_Cards.md` — internal approved.

### Phần bổ sung/suy diễn

- [BỔ SUNG — nguồn: NovaShop Change Cards] Sáu audit signs là fixture synthetic.
- [SUY DIỄN — từ project evidence] Metrics, severity, owners, transition decision và trigger trong MEX được thiết kế cho scenario; không phải benchmark ngành.

---
<!-- QUALITY GATE: 3/3 outline leaf đã tick và đủ semantic contract; MEX-U06-01 phủ LO6.1/LO6.2, map CP-U06-01..03; audit/Scrum boundary/ADR có oracle; không có mã nguồn ứng dụng. -->

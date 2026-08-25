# NovaShop — Git Flow Artifact Templates

> Các khung dưới đây là starter trống có chủ đích. Người học điền bằng dữ liệu synthetic của change card; không dùng tên, email, token hoặc URL production.

## 1. Issue / PBI Record

| Trường | Nội dung làm việc |
| --- | --- |
| Issue ID | — |
| Requirement ref | — |
| User/stakeholder outcome | — |
| Acceptance oracle | — |
| Target release | — |
| Branch type decision | — |
| Branch source → target | — |
| Decision rationale | — |

## 2. Commit Plan và Evidence

| Commit intent | Issue/AC ref | Artifact touched | Expected observable change | Evidence after commit |
| --- | --- | --- | --- | --- |
| — | — | — | — | — |

## 3. Pull-request / Merge-request Review Record

| Trường | Nội dung làm việc |
| --- | --- |
| Source branch | — |
| Target branch | — |
| Issue/change refs | — |
| Scope included / excluded | — |
| DoD evidence | — |
| Graph/containment evidence | — |
| Reviewer findings | — |
| Finding disposition | — |
| Merge decision: PASS hoặc REVISE | — |
| Reviewer role và review date | — |

## 4. Conflict Decision Record

| Trường | Nội dung làm việc |
| --- | --- |
| Branches / merge base | — |
| Conflicted artifact | — |
| Acceptance criteria at risk | — |
| Options considered | — |
| Chosen resolution và rationale | — |
| Evidence before / after | — |
| Regression or consistency oracle | — |
| Prevention rule | — |

## 5. Release Readiness và Tag Audit

| Gate | Expected evidence | Observed evidence | PASS / REVISE |
| --- | --- | --- | --- |
| Scope freeze | Done scope list; new feature excluded | — | — |
| Release-only fixes | Finding → fix → recheck | — | — |
| UAT | Scenario and result | — | — |
| Main merge | Release commit contained in main | — | — |
| Develop back merge | Release fixes contained in develop | — | — |
| Annotated tag | Tag name, object type, annotation | — | — |
| Changelog | PBI/fix refs and known limitations | — | — |

## 6. Incident và Hotfix Record

| Trường | Nội dung làm việc |
| --- | --- |
| Incident ID / severity | — |
| Production baseline tag | — |
| Observable impact | — |
| Why hotfix instead of feature/release fix | — |
| Hotfix source and targets | — |
| Regression evidence | — |
| Patch tag evidence | — |
| Propagation / containment evidence | — |
| Root cause and prevention | — |

## 7. Workflow Audit Finding

| Finding ID | Rule / source | Exact evidence | Severity | Impact | Remediation | Owner | Status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| — | — | — | — | — | — | — | — |

## 8. Workflow Decision ADR

| Trường | Nội dung làm việc |
| --- | --- |
| ADR ID và status | — |
| Context / decision driver | — |
| Current release cadence | — |
| Concurrent supported versions | — |
| Lead-time and merge-cost evidence | — |
| Option A: giữ Git Flow | — |
| Option B: flow đơn giản hơn | — |
| Decision và consequences | — |
| Scrum boundary statement | — |
| Trigger và review date | — |

## 9. Evidence Naming Convention

- `evidence/<issue-id>/status-before.txt`
- `evidence/<issue-id>/graph-after.txt`
- `evidence/<issue-id>/containment.txt`
- `project-artifacts/<milestone>/<artifact-name>.md`
- `decisions/<decision-id>.md`

Output lệnh phải được rà soát trước khi nộp. Không lưu đường dẫn cá nhân, remote URL nội bộ, credential, email thật hoặc dữ liệu khách hàng.

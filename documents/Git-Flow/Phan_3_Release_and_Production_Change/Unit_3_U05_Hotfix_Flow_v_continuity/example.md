# Unit U05: Hotfix Flow và continuity — Ví dụ và nghiên cứu tình huống

> **Khóa học:** Git Flow thực chiến qua dự án NovaShop · **Case:** CASE-U05-01 · **Mức xác thực:** simulated

## 🎯 Learning Outcomes liên quan

- **LO5.1** — Phân loại hotfix và vận hành từ `main` với regression evidence.
- **LO5.2** — Chứng minh patch tag trên `main` và propagation của hotfix change commit tới dòng tương lai.

## 🧭 Liên kết dự án

Case dùng project increment **M-GF-05**, nhưng mục tiêu khác MEX trong Material: MEX trình bày dossier chuẩn; case này điều tra một **kết luận continuity sai** do reviewer dùng tag merge commit thay cho hotfix change commit. Artifact tạo ra là corrected audit note và prevention rule cho NovaShop.

## 🧰 Điều kiện chạy ví dụ

- Repository artifact local, Git 2.40+; có `main`, `develop`, tag `v0.1.0`, hotfix đã merge `--no-ff` riêng vào hai nhánh và tag `v0.1.1` trên merge commit của `main`.
- Không có mã nguồn ứng dụng, remote production, credential hoặc dữ liệu thật.
- Xác minh bằng branch graph, object/ref queries và artifact review.

## 📚 Nguồn đầu vào đã map

- SRC-GIT-DOC, SRC-PROGIT — graph, refs, tag và ancestor queries.
- SRC-NVIE — nguồn/đích của hotfix và separate merges.
- SRC-SEMVER — patch release convention và bất biến release.
- SRC-SCRUM — Git Flow là practice ngoài định nghĩa Scrum.
- SRC-NS-CARDS — HOTFIX-301 synthetic.

---

## Case Study 01 — False negative: “v0.1.1 không có trong develop”

**Mapping:** CASE-U05-01 · OUT-U05-01, OUT-U05-02, OUT-U05-03 · LO5.1, LO5.2 · M-GF-05.

### 1. Ticket và tiêu chí thành công

- **Stakeholders:** incident owner, release owner, reviewer của NovaShop.
- **Vấn đề:** HOTFIX-301 đã được xử lý, nhưng continuity audit ghi REVISE vì lệnh kiểm tag trên `develop` trả false. Nhóm cần xác định đây là fix bị mất hay oracle bị chọn sai.
- **Business state:** lỗi ngưỡng shipping production đã được phân loại hotfix; regression dưới/đúng/trên boundary đều PASS.
- **Tiêu chí thành công:** phân biệt tag release commit với change commit; chứng minh tag ở `main`; chứng minh cùng change commit ở `main` và `develop`; sửa audit mà không rewrite lịch sử.

### 2. Input, trạng thái ban đầu và ràng buộc

Graph rút gọn:

```text
                         M1 (main, tag v0.1.1)
                        /  \
v0.1.0 ----------------     H (HOTFIX_CHANGE_COMMIT)
   \
    D0 --- A (Admin vNext) --- M2 (develop)
                               /
                              H
```

`M1` và `M2` là hai merge commit khác nhau; `H` là commit chứa incident correction/regression và được lưu thành `HOTFIX_CHANGE_COMMIT`. Reviewer đã chạy:

```text
git merge-base --is-ancestor v0.1.1 develop
```

Lệnh trả exit `1`. Ràng buộc:

- không di chuyển tag `v0.1.1`;
- không rebase/force-push hai nhánh đã chia sẻ;
- chỉ dùng Git evidence và dossier synthetic;
- Admin vNext phải còn trên `develop` nhưng không được có trong patch `v0.1.0..v0.1.1`.

### 3. Phân tích lựa chọn

| Phương án | Phân tích | Kết luận |
| --- | --- | --- |
| Merge tag `v0.1.1` vào `develop` chỉ để lệnh cũ PASS | Có thể kéo main merge topology vào nhánh tương lai mà không giải quyết nhu cầu nghiệp vụ; thay đổi lịch sử chỉ để hợp oracle | Loại |
| Force-move tag tới `H` | Phá định danh release đã chia sẻ và làm evidence cũ không tái lập | Loại |
| Kiểm tag trên `main`, kiểm `H` trên các target | Tách đúng hai claim: release identity và change propagation | Chọn |

Exit `1` của lệnh cũ không chứng minh fix bị mất. Nó chỉ chứng minh merge commit `M1` được tag trên `main` không phải ancestor của `develop`. Với hai merge `--no-ff` riêng, đây là trạng thái hợp lệ.

### 4. Cách triển khai professional artifact

#### 4.1 Xác nhận triage và scope

Reviewer giữ nguyên quyết định hotfix vì dossier có production symptom tại `v0.1.0`, urgency P1 synthetic, scope chỉ shipping rule và regression evidence. `git diff --name-only v0.1.0..v0.1.1` được review để xác nhận không có Admin vNext.

#### 4.2 Tách hai identity cần audit

1. `RELEASE_TAG_COMMIT` được quan sát bằng `git rev-parse v0.1.1^{commit}`.
2. `HOTFIX_CHANGE_COMMIT` lấy từ field đã capture trong dossier trước khi xóa hotfix branch.
3. Reviewer không giả định hai giá trị phải giống nhau; tag trỏ main merge commit, còn hotfix change commit là parent chung của hai merge.

#### 4.3 Chạy oracle đúng

```text
git cat-file -t refs/tags/v0.1.1
git merge-base --is-ancestor v0.1.1 main
git branch --contains HOTFIX_CHANGE_COMMIT
git log --graph --decorate --oneline --all
git status --short --branch
```

Trong lệnh containment, reviewer thay ký hiệu `HOTFIX_CHANGE_COMMIT` bằng SHA đã ghi trong dossier. Corrected audit record:

| Claim | Evidence | Observed | Kết luận |
| --- | --- | --- | --- |
| Incident đúng loại | production symptom + scope/urgency | Đủ | PASS |
| Patch tag annotated | object type của `refs/tags/v0.1.1` | `tag` | PASS |
| Patch tag ở main | ancestor exit status | `0` | PASS |
| Change ở main | branches containing `H` | có `main` | PASS |
| Change ở develop | branches containing `H` | có `develop` | PASS |
| Admin không lọt patch | patch diff + scope review | không có Admin path | PASS |

### 5. Output mong đợi

- `workflow-continuity-audit-v0.1.1.md` đổi finding từ “fix missing” thành “oracle mismatch corrected”.
- `HOTFIX_CHANGE_COMMIT` được ghi rõ, không chỉ ghi tên branch có thể bị xóa.
- Tag `v0.1.1` vẫn thuộc lịch sử `main`; không có yêu cầu tag commit phải nằm trong `develop`.
- Prevention rule: mọi hotfix dossier phải capture SHA incident correction commit trước merge và audit change SHA trên target tương lai.
- Working tree sạch; không có history rewrite.

### 6. Cách xác minh

| Tiêu chí | Oracle | PASS khi |
| --- | --- | --- |
| Tag type đúng policy | `git cat-file -t refs/tags/v0.1.1` | in `tag` |
| Tag thuộc production line | `git merge-base --is-ancestor v0.1.1 main` | exit `0` |
| Change propagation | `git branch --contains` với SHA đã lưu | liệt kê `main` và `develop` |
| Scope hẹp | `git diff --name-only v0.1.0..v0.1.1` | chỉ incident artifacts |
| Repository an toàn | `git status --short --branch` + graph review | sạch, ref không bị rewrite |

Reviewer dùng `git show --name-only` với SHA trong field `HOTFIX_CHANGE_COMMIT` để xác nhận commit đó chứa correction/regression artifacts. Nếu branch đã xóa, dossier SHA vẫn là evidence bền cần review cùng graph.

### 7. Giải thích sâu và failure modes

#### Failure A — Dossier không capture change SHA

- **Dấu hiệu:** hotfix branch đã xóa; audit chỉ có tag main.
- **Nguyên nhân:** template không tách release identity và change identity.
- **Chẩn đoán:** graph có thể cho thấy parent hotfix, nhưng reviewer phải điều tra thay vì có ref trực tiếp.
- **Xử lý:** xác định commit từ merge parents/review record, peer-review lại, rồi ghi SHA và provenance của cách xác định.
- **Phòng tránh:** capture SHA change commit trước merge trong hotfix checklist.

#### Failure B — `main` có change nhưng `develop` không có

- **Dấu hiệu:** `git branch --contains` SHA chỉ liệt kê `main`.
- **Nguyên nhân:** propagation bị bỏ quên hoặc target sai.
- **Xử lý:** đánh dấu continuity REVISE; merge hotfix vào `develop` nếu không có release mở, hoặc vào active release theo Git Flow; chạy regression/containment lại.

#### Failure C — Tag object type là `commit`

- **Dấu hiệu:** tag tồn tại nhưng không phải annotated tag.
- **Nguyên nhân:** lightweight tag được tạo trong khi NovaShop policy yêu cầu annotated.
- **Xử lý:** nếu chưa chia sẻ, sửa theo release policy; nếu đã chia sẻ, không tự ý di chuyển tag—escalate release decision và lưu audit finding.

### 8. Trade-off và bài học chuyển giao

Separate `--no-ff` merges giữ event trên từng target dễ audit nhưng tạo hai merge commit, nên tag containment không phải oracle propagation. Capture change SHA thêm một trường vào dossier nhưng loại bỏ false negative và vẫn hoạt động sau khi branch bị xóa.

Trong Lab, học viên tự xử lý wrong-source branch, changed boundary input và missing propagation. Trong Assignment, học viên chuyển nguyên tắc này sang incident duplicate payment với active release; case không cung cấp dossier hay chuỗi thao tác cho bài đó.

## Provenance của các case

- https://nvie.com/posts/a-successful-git-branching-model/ — merge targets của hotfix và ngoại lệ active release.
- https://git-scm.com/docs/git-merge-base — ancestor semantics.
- https://git-scm.com/docs/git-tag — tag object.
- [BỔ SUNG — nguồn: NovaShop Change Cards] HOTFIX-301, Admin vNext và shipping oracle là synthetic.
- [SUY DIỄN — từ Git graph semantics] Graph `M1/M2/H`, corrected audit note và prevention rule được dựng riêng để minh họa false negative.

---
<!-- QUALITY GATE: CASE-U05-01 map đủ 2 LO/3 outline; có ticket, input, constraint, professional artifact, expected output, validation, trade-off và failure modes; tag-main tách khỏi change propagation. -->

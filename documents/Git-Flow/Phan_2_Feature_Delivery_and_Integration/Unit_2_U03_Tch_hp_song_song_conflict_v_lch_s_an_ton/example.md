# Unit U03: Tích hợp song song, conflict và lịch sử an toàn — Ví dụ và nghiên cứu tình huống

> **Case:** CASE-U03-01 · **Project:** NovaShop · **Mức xác thực:** simulated · **Phương thức:** artifact review

## 🎯 Learning Outcomes liên quan

- **LO3.1:** Chẩn đoán và giải quyết conflict mà không làm mất acceptance criteria.
- **LO3.2:** Đánh giá history strategy theo ownership, traceability và rủi ro rewrite.

## 🧭 Liên kết với ngữ cảnh nghề nghiệp/dự án

Case này diễn ra tại **M-GF-03** nhưng không dùng lại dữ liệu của Material, Lab hoặc Assignment. Search (`NS-101`) và Cart Promotion (`NS-102`) cùng đăng ký customer-message key. Release Owner muốn một integration result có thể kiểm toán trước khi U04 cắt release.

Artifact case tạo ra:

- conflict map và integration-order decision;
- conflict decision record có domain owner;
- resolved message registry;
- graph/containment evidence và review verdict.

CASE-U03-01 minh họa OUT-U03-01, OUT-U03-02, OUT-U03-03 và chuẩn bị cách tư duy cho Lab; nó không cung cấp đáp án cho change request `NS-303` của Assignment.

## 🧰 Điều kiện chạy ví dụ

- Repo Git local cô lập, Git 2.40+ và working tree sạch.
- `main`, `develop`, `feature/NS-101-search-empty-state`, `feature/NS-102-cart-promo-message` tồn tại.
- Hai feature bắt đầu từ cùng baseline `develop@D0`; Cart branch đã được peer fetch.
- Artifact là CSV/Markdown synthetic; không có mã nguồn, credential, PII hoặc remote production.

Preflight và evidence baseline:

```text
git status --short --branch
git branch --list develop feature/NS-101-search-empty-state feature/NS-102-cart-promo-message
git merge-base feature/NS-101-search-empty-state feature/NS-102-cart-promo-message
git log --graph --decorate --oneline --all
```

## 📚 Nguồn đầu vào đã map

- Git Reference Manual 2.54.0 và Pro Git, 2nd Edition: merge, merge-base, diff, status và graph.
- Vincent Driessen, *A successful Git branching model*: feature branch và `develop` trong Git Flow.
- Scrum Guide 2020: Definition of Done là quality commitment; branch strategy không phải quy tắc Scrum.
- NovaShop backlog/change cards synthetic và FR-01/FR-02.

### Mapping case đã chốt trong course plan

| Case ID | Outline refs | LO | Scenario artifact | Oracle chính |
| --- | --- | --- | --- | --- |
| CASE-U03-01 | OUT-U03-01/02/03 | LO3.1, LO3.2 | message-key registry + conflict/strategy record | key duy nhất, hai AC còn nguyên, feature tips contained, no rewrite |

## Case Study 01: Search và Cart tranh chấp customer-message key

### 1. Ticket và tiêu chí thành công

**Ticket A — NS-101 Search empty state**

- Requirement: FR-01.
- Thay đổi: thêm key `SEARCH_NO_RESULT` với context `SEARCH`.
- Oracle: tìm kiếm không có kết quả hiển thị thông điệp đúng context và không làm mất bộ lọc đang chọn.

**Ticket B — NS-102 Cart Promotion**

- Requirement: FR-02.
- Thay đổi được đề xuất ban đầu: dùng cùng dòng dự phòng để thêm thông điệp mã giảm giá không hợp lệ.
- Oracle: thông điệp sai mã quan sát được và sản phẩm trong giỏ vẫn được giữ.

**Success contract của integration:** registry có hai key duy nhất, mỗi key map đúng requirement/context, hai feature tip là ancestor của `develop`, và old Cart tip đã review vẫn query được.

### 2. Input, trạng thái ban đầu và ràng buộc

Baseline `project-artifacts/shared/customer-message-registry.csv`:

```csv
message_key,context,meaning,preserve_state,requirement_ref
PAYMENT_PENDING,PAYMENT,Payment is pending,YES,FR-03
CHANGE_SLOT,UNASSIGNED,Reserved for one approved message,YES,NONE
```

Search branch thay `CHANGE_SLOT` bằng:

```csv
SEARCH_NO_RESULT,SEARCH,No products match the current search,YES,FR-01
```

Cart branch, từ cùng baseline, thay đúng row đó bằng đề xuất:

```csv
CART_PROMO_INVALID,CART,Promotion code is invalid,YES,FR-02
```

Ràng buộc:

- không được chọn nguyên một phía chỉ để marker biến mất;
- `message_key` phải duy nhất và không đổi key đã công bố;
- Cart branch đã được peer fetch nên không rebase/force-push;
- mỗi merge vào `develop` cần no-fast-forward theo working agreement.

### 3. Phân tích lựa chọn

Conflict map:

| Driver | Search | Cart | Kết luận |
| --- | --- | --- | --- |
| Dependency | độc lập | độc lập | Không có thứ tự bắt buộc theo dependency |
| Overlap | thay `CHANGE_SLOT` | thay `CHANGE_SLOT` | Text conflict chắc chắn ở cùng row |
| Readiness | review PASS trước | review PASS sau | Merge Search trước để cô lập thay đổi thứ hai |
| AC risk | FR-01 | FR-02 | Resolution phải giữ cả hai row |
| History | local review complete | peer đã fetch | Không rebase Cart; merge result trên `develop` |

Các phương án được cân nhắc:

1. **Chọn Search:** marker hết nhưng FR-02 mất — REJECT.
2. **Chọn Cart:** marker hết nhưng FR-01 mất — REJECT.
3. **Giữ hai row với key/context riêng:** cả hai AC còn nguyên và schema cho phép nhiều row — ACCEPT.
4. **Rebase Cart rồi force-update:** có thể dời conflict nhưng phá reviewed tip — REJECT.

### 4. Cách triển khai

Case được thực hiện như một merge có audit trail:

```text
git switch develop
git merge --no-ff feature/NS-101-search-empty-state -m "merge(NS-101): integrate search empty-state artifact"
git merge --no-ff feature/NS-102-cart-promo-message -m "merge(NS-102): integrate cart promotion message"
```

Lệnh thứ hai dừng ở conflict. Trước khi sửa, evidence pack ghi `git status --short`, `git diff --name-only --diff-filter=U` và diff vùng conflict. Domain owner xác nhận phương án 3. Resolved registry là:

```csv
message_key,context,meaning,preserve_state,requirement_ref
PAYMENT_PENDING,PAYMENT,Payment is pending,YES,FR-03
SEARCH_NO_RESULT,SEARCH,No products match the current search,YES,FR-01
CART_PROMO_INVALID,CART,Promotion code is invalid,YES,FR-02
```

Sau khi đối chiếu oracle, artifact và decision record được stage, merge commit được hoàn tất. Không có thao tác rewrite nào trên Cart branch.

Conflict Decision Record hoàn chỉnh:

| Trường | Giá trị |
| --- | --- |
| Branches / merge base | `develop` nhận Search trước, Cart sau; common base D0 |
| Conflicted artifact | `project-artifacts/shared/customer-message-registry.csv` |
| Acceptance criteria at risk | FR-01 empty state và FR-02 invalid promotion |
| Options considered | chỉ Search; chỉ Cart; giữ hai key; rebase shared Cart |
| Chosen resolution | giữ `SEARCH_NO_RESULT` và `CART_PROMO_INVALID` thành hai row |
| Rationale | hai message phục vụ context khác nhau; schema hỗ trợ key duy nhất theo row |
| Decision owner | Product Owner xác nhận scope; domain reviewer xác nhận key/context |
| Regression oracle | mỗi key xuất hiện đúng một lần; `preserve_state=YES`; requirement refs đúng |
| History strategy | no-ff merge; không squash/rebase branch đã shared |
| Prevention | reserve key trước khi sửa shared registry; conflict map trong review |

### 5. Output mong đợi

- `develop` chứa merge boundary của Search và Cart.
- `SEARCH_NO_RESULT` và `CART_PROMO_INVALID` mỗi key đúng một lần.
- Không còn marker; working tree sạch.
- Tip đã review của cả hai feature là ancestor của `develop`.
- Decision record nêu đủ AC at risk, options, owner, chosen resolution và prevention rule.

Graph rút gọn hợp lệ có hình dạng tương đương:

```text
*   M2 (develop) merge NS-102
|\
| * C1 (feature/NS-102-cart-promo-message)
* | M1 merge NS-101
|\|
| * S1 (feature/NS-101-search-empty-state)
|/
* D0 common baseline
```

Object IDs thực tế khác giữa các repo; oracle dùng quan hệ parent/ancestor, không so chuỗi hash mẫu.

### 6. Cách xác minh

| Check | Lệnh/review | Expected result |
| --- | --- | --- |
| Whitespace/marker trong diff | `git diff --check` | không có output, exit 0 |
| Marker tracked | `git grep -n -E '^(<<<<<<<|=======|>>>>>>>)' -- '*.md' '*.csv'` | không có output, exit 1 vì không tìm thấy |
| Search contained | `git merge-base --is-ancestor feature/NS-101-search-empty-state develop` | exit 0 |
| Cart contained | `git merge-base --is-ancestor feature/NS-102-cart-promo-message develop` | exit 0 |
| Topology | `git log --graph --decorate --oneline --all` | hai feature và merge point giải thích được |
| Working tree | `git status --short --branch` | chỉ header branch, không có file thay đổi |
| Business contract | review resolved CSV | hai key unique; đúng context/FR; `preserve_state=YES` |

Reviewer kết luận **PASS** chỉ khi cả structural oracle và business oracle đạt. Marker bằng 0 nhưng thiếu một key vẫn là **REVISE**.

### 7. Giải thích sâu và failure modes

**Vì sao no-fast-forward thay vì squash?** Case cần chứng minh exact reviewed feature tips đã vào `develop`. Squash có thể giữ final content nhưng khiến tip không là ancestor; khi đó containment oracle của case fail.

**Vì sao không rebase Cart?** Cart tip đã được peer fetch và ghi vào review record. Rebase tạo commit mới, làm evidence trỏ tới lịch sử cũ. Conflict không biến mất về mặt nghiệp vụ; nó chỉ chuyển nơi giải quyết.

**Failure: Git merge sạch nhưng key bị trùng.** Nếu hai branch thêm ở hai vùng khác nhau, Git có thể không tạo marker. Registry vẫn fail semantic oracle. Cách chẩn đoán là review uniqueness/requirement map, không chỉ `git status`.

**Failure: chọn “ours”.** Dấu hiệu là Search row tồn tại nhưng Cart row mất. Nguyên nhân là coi `ours` là “đúng”. Khắc phục: phục hồi kết quả chưa commit theo hai AC; nếu merge đã công bố, review một corrective commit/revert thay vì rewrite `develop`. Phòng tránh: decision record phải liệt kê từng AC at risk trước edit.

**Failure: merge nhầm hướng.** `ours/theirs` bị hiểu ngược. Dùng `git status`, `git show :1:<path>`, `:2:<path>`, `:3:<path>` để xác định base/ours/theirs trong merge đang dở. Nếu source/target sai, lưu evidence rồi abort trong bản sao Lab.

### 8. Bài học chuyển giao

- Integration order là quyết định risk/dependency, không phải hàng đợi theo thời điểm hoàn thành.
- Conflict resolution là một quyết định nghiệp vụ có audit trail; marker scan chỉ là một oracle cấu trúc.
- History strategy phải được chọn trước merge theo ownership và acceptance evidence.
- Lab thay key registry bằng payment-status matrix; Assignment thay bằng canonical audit-field contract. Học viên phải tái áp dụng mental model, không dùng lại resolved rows của case này.

## Provenance của các case

### Nguồn được dùng

- Git Reference Manual 2.54.0: semantics của merge, index conflict stages, merge-base, diff và status.
- Pro Git, 2nd Edition: three-way merge và branch topology.
- Vincent Driessen: feature branch tích hợp vào `develop` trong Git Flow.
- NovaShop project brief/backlog synthetic: FR-01, FR-02 và dữ liệu case.

### Phần bổ sung/suy diễn

- **[SUY DIỄN — từ kiến thức đã huấn luyện]** Message registry và commit labels D0/S1/C1/M1/M2 là fixture synthetic để dạy resolution; không đại diện cho repository thật.
- **[BỔ SUNG — nguồn: Git Reference Manual 2.54.0]** Exit code của `merge-base --is-ancestor` và quan hệ ancestry được dùng làm pass/fail oracle; business correctness vẫn cần artifact review.

---
<!-- QUALITY GATE: CASE-U03-01 có ticket, input, constraint, complete solution artifact, expected result, verification, trade-off và failure paths; khác Material/Lab/Assignment; không có credential/PII hoặc mã nguồn ứng dụng. -->

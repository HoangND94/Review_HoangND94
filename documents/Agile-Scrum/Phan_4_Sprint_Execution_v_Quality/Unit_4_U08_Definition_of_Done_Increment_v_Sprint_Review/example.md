# Unit U08: Definition of Done, Increment và Sprint Review — Ví dụ và nghiên cứu tình huống

## 🎯 Learning Outcomes liên quan

> **Case:** CASE-U08-01 · **LO:** LO8.1, LO8.2 · **Outline:** OUT-U08-01, OUT-U08-02 · **Mức xác thực:** simulated

## Case Study 01 — Catalog filter usable nhưng audit trail còn thiếu

### 1. Ticket và tiêu chí thành công

NovaShop kết thúc Sprint cải thiện catalog/filter. Scrum Team phải phân loại ba PBI, chỉ inspect phần thật sự Done và xử lý feedback về “lọc sản phẩm hết hàng”. Thành công khi evidence pack giải thích được mọi decision; Review tạo backlog diff; claim accessibility/security không vượt selected-test scope.

### 2. Input, trạng thái ban đầu và ràng buộc

DoD `DOD-NS-1.0` yêu cầu: AC PASS; peer review; integration evidence; selected responsive/accessibility/security checks theo scope; documentation/audit evidence khi áp dụng; không Critical/High mở.

| PBI | AC evidence | DoD evidence |
| --- | --- | --- |
| CAT-41 keyword + brand filter | 4/4 PASS | review/integration PASS; selected keyboard navigation PASS; docs PASS |
| CAT-42 admin inventory edit | 3/3 PASS | authorization PASS; audit event file MISSING |
| CAT-43 empty-results message | 2/2 PASS | review/integration/selected keyboard PASS; docs PASS |

Selected accessibility test chỉ bao phủ filter controls và empty-results state trên Firefox/Windows bằng keyboard. Selected security test chỉ bao phủ customer role bị từ chối ở admin edit. Không có basis cho whole-site/whole-standard conformance.

Feedback cards: `FC-41` ẩn hết hàng mặc định; `FC-42` thêm marketplace sellers; `FC-43` giữ bộ lọc khi quay lại từ product detail. Product Goal vẫn là giảm ma sát tìm/checkout trong MVP B2C một nhà bán.

### 3. Phân tích lựa chọn

`CAT-42` không thể được cứu bằng cách gọi audit trail “documentation phụ”: DoD nêu rõ audit evidence khi áp dụng. Review có thể minh bạch gap nhưng không approve nó thành Increment. Với feedback, `FC-41` có thể làm người mua bỏ lỡ lựa chọn và cần evidence; `FC-42` nằm ngoài boundary; `FC-43` liên quan trực tiếp journey và có failure evidence từ session replay synthetic.

### 4. Artifact triển khai

#### Quality-gate matrix

| PBI | Decision | Evidence/rationale | Backlog action |
| --- | --- | --- | --- |
| CAT-41 | Done | AC + mọi DoD áp dụng PASS | Include Increment |
| CAT-42 | Not Done | `audit-event` MISSING dù AC PASS | Return backlog; attach gap `G-42` |
| CAT-43 | Done | AC + mọi DoD áp dụng PASS | Include Increment |

#### Sprint Review record

- Outcome inspected: CAT-41 và CAT-43; CAT-42 được nêu là Not Done, không demo-as-complete.
- Product Goal progress: search/filter path usable trong selected fixture; chưa có outcome production.
- Environment change: merchandising muốn giảm đơn hỏi tồn kho, evidence chưa đủ.

| Feedback | Disposition | Rationale | Backlog link/owner |
| --- | --- | --- | --- |
| FC-41 hide out-of-stock | Defer | cần measure search abandonment và customer need; nguy cơ che lựa chọn | Discovery card DISC-18/PO, review after synthetic test |
| FC-42 marketplace | Reject | ngoài system boundary và Product Goal hiện tại | Decision log DL-42/PO |
| FC-43 preserve filters | Accept | trực tiếp giảm rework trong journey; synthetic replay có failure | PB-431/PO, ordered sau critical checkout fixes |

#### Scope statement

“Selected keyboard interactions for catalog filter/empty-results passed on Firefox/Windows fixture. Selected customer→admin denial test passed. Không tuyên bố WCAG 2.2 AA conformance, ASVS 5.0.0 conformance hay production readiness ngoài evidence pack.”

### 5. Output mong đợi và verification

| Oracle | Expected |
| --- | --- |
| C8-QG | 3 PBI có decision; CAT-42 không nằm Increment; evidence links resolve |
| C8-SR | Review chỉ gọi CAT-41/CAT-43 Done; Product Goal progress có limitation |
| C8-FB | 3/3 feedback có disposition/rationale/owner/link hoặc trigger |
| C8-PB | PB-431 và gap G-42 xuất hiện trong backlog diff; DL-42/DISC-18 giữ trace |
| C8-SCOPE | Không có claim toàn diện từ selected checks |

Kết quả case: 5/5 PASS.

### 6. Failure modes và trade-off

- Mark CAT-42 Done tạo transparency giả; dấu hiệu là Increment list có item với `MISSING`; sửa bằng quality-gate invariant.
- Reject FC-41 ngay có thể bỏ learning; defer giữ option nhưng tốn discovery capacity. Trigger cụ thể ngăn defer vô thời hạn.
- Accept mọi feedback làm loãng Goal; review Product Goal/boundary và evidence trước disposition.
- Selected checks giảm rủi ro trong scope, nhưng không chứng minh mọi browser/page/role hoặc đầy đủ tiêu chí chuẩn.

### 7. Bài học chuyển giao

Done decision đi từ criterion và evidence, không từ quyền lực stakeholder. Feedback adaptation đi từ outcome/Goal và traceability, không từ applause trong demo. Lab sử dụng shipping selector và change card khác; Assignment sử dụng baseline ASM-U06 và không cung cấp classification sẵn.

## Provenance của các case

- **SRC-SG20** — [The Scrum Guide, November 2020](https://scrumguides.org/scrum-guide.html).
- **SRC-DOD** — [What is the Definition of Done?](https://www.scrum.org/resources/what-definition-done-0), snapshot 2026-08-25.
- **SRC-WCAG22** — [WCAG 2.2 Recommendation](https://www.w3.org/TR/2024/REC-WCAG22-20241212/).
- **SRC-ASVS500** — [OWASP ASVS 5.0.0](https://github.com/OWASP/ASVS/tree/v5.0.0_release).
- Fixture CASE-U08-01: **[BỔ SUNG — nguồn: SRC-PROJECT, dữ liệu mô phỏng]**.

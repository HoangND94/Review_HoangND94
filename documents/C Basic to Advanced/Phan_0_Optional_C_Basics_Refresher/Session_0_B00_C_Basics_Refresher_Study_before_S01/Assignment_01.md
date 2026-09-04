# Assignment B00 — Bounded Sensor Summary

**Thời lượng:** 60 phút · **Mức:** Apply · **Độc lập:** không sao chép walkthrough Lab.

| Thuộc tính | Giá trị |
| --- | --- |
| Mã bài | ASG-B00-01 |
| Độ khó / Bloom | Foundation / Apply |
| Mức xác thực | simulated — dữ liệu cảm biến synthetic |
| Liên kết project | NOT_APPLICABLE — khóa học theo từng unit |

## 🎯 Learning Outcomes được đánh giá

`ADVC-H1SD`: viết và kiểm chứng một mô-đun C17 có contract dữ liệu, ranh giới mảng và xử lý lỗi xác định. Evidence: source tách hàm, transcript success/failure và strict build.

## 🧠 Khái niệm và best practices được đánh giá

| Concept / LO | Scenario, rule và deliverable | Acceptance tiêu chí kiểm chứng |
| --- | --- | --- |
| Program/type/control flow · H1SD | Parse tối đa 12 token; **rule:** kiểm `endptr`, range trước cast; không dùng `atoi`. | AT-02 |
| Function/prototype/scope · H1SD | Tách parser/calculation/presentation; input array là `const`. | AT-03 |
| Array/string bounded · H1SD | Chỉ truy cập `0 <= i < count`; không có partial summary. | AT-01, AT-02 |

## 🧭 Bối cảnh và change request

Bạn là C developer cho diagnostic gateway mô phỏng. Thay vì sample statistics ở Lab, gateway phải tóm tắt nhiệt độ từ command line với capacity và invalid-input policy mới. Đây là bài làm độc lập; đề không cung cấp thuật toán hay code khung.

## 🧰 Điều kiện thực hiện

**Tiên quyết:** B00 Lab. **Môi trường:** ISO C17, GCC/Clang hoặc compiler tương thích, `-Wall -Wextra -Wpedantic -Werror`. **Input/starter assets:** tự tạo source mới; chỉ dùng số nguyên synthetic, không dùng secret/PII.

## 📋 Yêu cầu

### Functional requirements

- FR-01: nhận 1–12 integer và in count/min/max/mean hai chữ số.
- FR-02: báo lỗi xác định cho input rỗng, token sai/range sai hoặc vượt capacity.
- FR-03: tách interface parser, calculation, presentation.

### Non-functional requirements

- NFR-01: strict build không warning.
- NFR-02: failure không in stdout summary hoặc sửa input array.

### Ràng buộc và ngoài phạm vi

Không dùng cấp phát động, file I/O, extension compiler hoặc hướng dẫn giải; không chấm theo số dòng code.

## Bối cảnh và yêu cầu

Thiết bị gateway nhận 1–12 số đo nhiệt độ nguyên từ command line. Viết CLI C17 in số lượng, min, max và mean chính xác hai chữ số thập phân. Mỗi token phải được parse có kiểm soát; input trống, quá 12 phần tử, token dư, hoặc vượt `int` phải thất bại mà không in summary. Tách parser, calculation và presentation thành các hàm có prototype; hàm calculation không sửa mảng input.

## Deliverables

Source `.c/.h`, `README.md` chứa build/run command, và `evidence.txt` cho một happy case, một negative case, hai boundary case. Compile bằng `-std=c17 -Wall -Wextra -Wpedantic -Werror`.

**Submission contract:** nộp source, README và evidence trong một thư mục `ASG-B00-01`; evidence ghi command, exit code, stdout/stderr thực tế.

## Acceptance tests

- `AT-01`: 1 và 12 số hợp lệ tạo summary đúng, exit 0.
- `AT-02`: token `12x`, overflow và quá 12 phần tử có stdout rỗng, exit khác 0.
- `AT-03`: parser không dùng `atoi`; interface thể hiện rõ `const`/count/output contract.

## Rubric (100%)

| Tiêu chí | Điểm |
|---|---:|
| Contract hàm, kiểu dữ liệu và ranh giới mảng | 30 |
| Parser và xử lý lỗi xác định | 30 |
| Kết quả/statistics đúng ở happy + boundary | 25 |
| Strict build, README và evidence tái lập | 15 |

## 🧪 Cách xác minh, nguồn và provenance

Chạy strict build rồi thực hiện AT-01..03; lưu expected/actual. Nguồn đã map: `material.md`, `example.md`, `assets/basic_refresher_demo.c`. `[SUY DIỄN — từ kiến thức đã huấn luyện]` Change request dùng dữ liệu cảm biến synthetic để đánh giá transfer.

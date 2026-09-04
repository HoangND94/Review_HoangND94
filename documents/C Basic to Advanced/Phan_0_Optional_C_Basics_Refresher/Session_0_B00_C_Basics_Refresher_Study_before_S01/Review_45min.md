# B00 — Review chéo cuối ngày (45 phút)

## Checklist bám Material và Example

- [ ] Đọc `OUT-B00-01`: cấu trúc C17, type, operator, control flow; chỉ được success/error path của example.
- [ ] Đọc `OUT-B00-02`: prototype, scope, storage duration; giải thích API input/count/output.
- [ ] Đọc `OUT-B00-03`: array/string bounded; chỉ ra invariant `0 <= index < count`.
- [ ] Đọc `OUT-B00-04`: pointer/`const`, strict GCC build/debug.
- [ ] Chạy happy và invalid path của `CASE-B00-01`; lưu stdout, stderr, exit code.
- [ ] Hoàn thành Lab: `strtol`, test 1/8/9 values và token dư.
- [ ] Hoàn thành Assignment; peer chạy README từ trạng thái sạch.

## 15 câu hỏi và đáp án

1. **Hỏi:** Luồng example?  
   **Đáp án:** `main` parse toàn bộ input, chỉ tính sau khi hợp lệ và tách success/error path.
2. **Hỏi:** Vì sao `strtol` hơn `atoi`?  
   **Đáp án:** có `endptr`, `errno` và range check; `atoi` không báo lỗi đáng tin.
3. **Hỏi:** Khi nào cast sang `int`?  
   **Đáp án:** sau khi token hết và giá trị nằm trong range `int`.
4. **Hỏi:** count/capacity?  
   **Đáp án:** số phần tử hợp lệ/số slot cấp phát.
5. **Hỏi:** Index hợp lệ?  
   **Đáp án:** từ 0 đến `count-1`; `count` là one-past-end.
6. **Hỏi:** `const int values[]` nói gì?  
   **Đáp án:** callee không sửa input; caller vẫn sở hữu array.
7. **Hỏi:** Prototype có tác dụng?  
   **Đáp án:** compiler kiểm kiểu và số parameter trước call.
8. **Hỏi:** Automatic lifetime?  
   **Đáp án:** kết thúc khi block kết thúc; không giữ pointer sau đó.
9. **Hỏi:** Mean tránh integer division thế nào?  
   **Đáp án:** cast một operand sang floating-point trước phép chia.
10. **Hỏi:** stdout/stderr?  
    **Đáp án:** result/error tách stream để script kiểm chứng.
11. **Hỏi:** tiêu chí kiểm chứng cho trường hợp hợp lệ gồm gì?  
    **Đáp án:** command, exit 0, exact stdout và stderr rỗng.
12. **Hỏi:** Invalid tiêu chí kiểm chứng chứng minh gì?  
    **Đáp án:** fail trước calculation, stdout rỗng, status lỗi tái lập.
13. **Hỏi:** Scope/lifetime khác gì?  
    **Đáp án:** visibility của tên/thời gian object tồn tại.
14. **Hỏi:** Capacity 8 test gì?  
    **Đáp án:** 0, 1, 8, 9 values và boundary numeric.
15. **Hỏi:** Evidence đạt?  
    **Đáp án:** strict build, happy/invalid/boundary logs và README tái lập.

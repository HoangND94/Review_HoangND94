# B05 — Review chéo cuối ngày (45 phút)
## Checklist
- [ ] Đọc memory layout/lifetime, pointer, allocation và pointer arithmetic trong `material.md`.
- [ ] Chạy CASE-B05 vector: normal, capacity, allocation failure; kiểm ownership/cleanup evidence.
- [ ] Peer review Lab vector và Assignment reading buffer: `realloc`, bounds, sanitizer result.
## 15 câu hỏi và đáp án
1. **Hỏi:** Pointer có tự biết size/owner không?  
   **Đáp án:** Không; API truyền count/capacity và ghi ownership/lifetime riêng.
2. **Hỏi:** Vì sao không return pointer tới local automatic object?  
   **Đáp án:** object hết lifetime khi hàm return, pointer trở thành dangling.
3. **Hỏi:** `malloc` fail phải làm gì?  
   **Đáp án:** trả error, không dereference NULL và không công bố state success.
4. **Hỏi:** Vì sao gán thẳng `p = realloc(p,n)` nguy hiểm?  
   **Đáp án:** fail trả NULL làm mất pointer cũ; dùng temporary rồi commit sau success.
5. **Hỏi:** Failure atomic vector nghĩa gì?  
   **Đáp án:** khi grow fail, data/size/capacity cũ vẫn dùng được; hash/state test chứng minh.
6. **Hỏi:** `size`/`capacity` khác gì?  
   **Đáp án:** số element hợp lệ/số slot allocated; write chỉ khi size < capacity.
7. **Hỏi:** One-past pointer dùng được không?  
   **Đáp án:** có thể hình thành/so sánh nhưng không dereference.
8. **Hỏi:** Pointer arithmetic hợp lệ khi nào?  
   **Đáp án:** trong cùng array object hoặc one-past; ngoài phạm vi là UB.
9. **Hỏi:** `free(NULL)` có an toàn không?  
   **Đáp án:** có; nhưng double-free non-NULL vẫn là UB, reset pointer sau free giúp contract rõ.
10. **Hỏi:** Leak thường ở đâu?  
    **Đáp án:** error/early-return path; dùng cleanup matrix kiểm từng owner.
11. **Hỏi:** Stack/heap có phải layout portable C?  
    **Đáp án:** không; C chuẩn nói storage duration/lifetime, layout host chỉ quan sát.
12. **Hỏi:** `const` pointer parameter có ích gì?  
    **Đáp án:** phân biệt read-only view với quyền mutate, giảm lỗi API.
13. **Hỏi:** Sanitizer pass chứng minh gì?  
    **Đáp án:** không thấy lỗi trên paths/fixture chạy, không chứng minh mọi input đúng.
14. **Hỏi:** Boundary tests vector?  
    **Đáp án:** empty, one, capacity, grow, invalid index và forced allocation failure.
15. **Hỏi:** Peer evidence cần gì?  
    **Đáp án:** strict build, ownership table, happy/failure logs và cleanup/sanitizer evidence nếu có.

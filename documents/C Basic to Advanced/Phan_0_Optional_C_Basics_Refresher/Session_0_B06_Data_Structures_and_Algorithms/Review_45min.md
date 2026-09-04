# B06 — Review chéo cuối ngày (45 phút)
## Checklist
- [ ] Đọc classification, array/list/tree/hash, stack/queue, sort/search và complexity.
- [ ] Chạy CASE-B06 empty/duplicate/missing lookup; kiểm invariant/ownership.
- [ ] Review Lab collection và Assignment Incident Index: workload rationale + tests.
## 15 câu hỏi và đáp án
1. **Hỏi:** Chọn structure bắt đầu từ đâu?  
   **Đáp án:** workload và invariant, không phải cấu trúc quen thuộc.
2. **Hỏi:** Array/list trade-off?  
   **Đáp án:** array index tốt/resize-insert tốn; list insert khi đã có node tốt/search cache locality kém.
3. **Hỏi:** Hash phù hợp case nào?  
   **Đáp án:** lookup key nhanh trung bình; cần collision/load-factor contract.
4. **Hỏi:** Tree hữu ích khi nào?  
   **Đáp án:** hierarchy hoặc ordered traversal; balance quyết định cost thực tế.
5. **Hỏi:** Stack/queue khác gì?  
   **Đáp án:** LIFO/FIFO; chọn theo order phục vụ workload.
6. **Hỏi:** Invariant unique ID là gì?  
   **Đáp án:** không có hai element cùng key; add phải check trước commit.
7. **Hỏi:** Vì sao `bsearch` có thể fail dù key tồn tại?  
   **Đáp án:** array chưa sort hoặc comparator/key contract khác nhau.
8. **Hỏi:** Comparator không nên `a-b` vì sao?  
   **Đáp án:** subtraction có thể overflow; dùng compare nhánh.
9. **Hỏi:** Complexity có phải timing guarantee?  
   **Đáp án:** không; là model, timing phụ thuộc implementation/hardware/data.
10. **Hỏi:** Ownership linked list?  
    **Đáp án:** container sở hữu node và free từng node exactly once.
11. **Hỏi:** Empty operation phải thế nào?  
    **Đáp án:** return status/result xác định, không dereference head NULL.
12. **Hỏi:** Duplicate test chứng minh gì?  
    **Đáp án:** invariant giữ và state không partial update.
13. **Hỏi:** Khi nào không dùng hash?  
    **Đáp án:** cần ordered traversal/range query hoặc memory constraint không phù hợp.
14. **Hỏi:** Workload change FIFO dẫn tới gì?  
    **Đáp án:** queue phù hợp hơn index structure; nêu rationale trước rewrite.
15. **Hỏi:** Evidence review?  
    **Đáp án:** design comparison, invariant tests, strict build và cleanup logs.

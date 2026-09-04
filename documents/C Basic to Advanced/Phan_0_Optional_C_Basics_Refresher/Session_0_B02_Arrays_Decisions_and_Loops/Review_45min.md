# B02 — Review chéo cuối ngày (45 phút)
## Checklist
- [ ] Đối chiếu `OUT-B02-01..17`: array, memory, decision, switch, loop/break.
- [ ] Chạy mixed/empty/capacity/invalid cases của `CASE-B02-01`.
- [ ] Review Lab classifier và Assignment: invariant, sentinel, no-partial-output.
## 15 câu hỏi và đáp án
1. **Hỏi:** Array decay là gì khi truyền vào function?  
   **Đáp án:** array thành pointer phần tử đầu; size bị mất nên API cần `pointer + count`.
2. **Hỏi:** Vì sao `sizeof(values)` trong callee sai để suy count?  
   **Đáp án:** nó cho size pointer; lỗi gây bounds sai, kiểm bằng 1/capacity/over-capacity test.
3. **Hỏi:** `count`/capacity khác gì?  
   **Đáp án:** data hợp lệ/slot cấp sẵn; write chỉ khi count nhỏ hơn capacity.
4. **Hỏi:** Vì sao `i <= count` lỗi?  
   **Đáp án:** đọc one-past-end; loop dùng `i < count`.
5. **Hỏi:** Khi nào dùng `if` thay `switch`?  
   **Đáp án:** range/compound condition; switch hợp discrete enum/code.
6. **Hỏi:** Fall-through gây case bug thế nào?  
   **Đáp án:** chạy action case sau; dùng `break` hoặc chú thích chủ ý.
7. **Hỏi:** Sentinel `--end` phải parse thế nào?  
   **Đáp án:** nhận trước numeric parser, kết thúc intake, token sau không là data.
8. **Hỏi:** Loop invariant của classifier?  
   **Đáp án:** trước mỗi iteration, bucket phản ánh đúng các phần tử `[0,i)`.
9. **Hỏi:** `break` hay `continue`?  
   **Đáp án:** break chấm dứt loop; continue bỏ phần thân còn lại, cần không phá update index.
10. **Hỏi:** 2D array parameter cần gì?  
    **Đáp án:** dimension sau để compiler tính stride.
11. **Hỏi:** No-high output chứng minh gì?  
    **Đáp án:** empty result là state hợp lệ, không dùng uninitialized first index.
12. **Hỏi:** Why capacity test 24/25?  
    **Đáp án:** xác minh exact boundary và reject trước write 25.
13. **Hỏi:** Ternary khi nào tránh?  
    **Đáp án:** nested decision làm khó review; if/else rõ hơn.
14. **Hỏi:** Invalid input không được in summary vì sao?  
    **Đáp án:** tránh consumer tin partial result; error stream/exit phải rõ.
15. **Hỏi:** Evidence review?  
    **Đáp án:** strict build và transcript mixed/no-high/boundary/malformed.

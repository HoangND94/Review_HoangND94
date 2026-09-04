# B07 — Review chéo cuối ngày (45 phút)
## Checklist
- [ ] Đọc pointer address/lifetime, function pointer và callback context.
- [ ] Chạy CASE-B07 accepted, no-match và invalid callback/context paths.
- [ ] Review Lab filter và Assignment alert subscription: signature, ownership, null contract.
## 15 câu hỏi và đáp án
1. **Hỏi:** Address hợp lệ có kéo dài lifetime không? **Đáp án:** Không; object phải sống suốt call/use.  
2. **Hỏi:** Function pointer cast để khớp signature? **Đáp án:** Không an toàn; dùng typedef exact signature.  
3. **Hỏi:** Callback context để làm gì? **Đáp án:** truyền criterion state mà không dùng global mutable state.  
4. **Hỏi:** Ai sở hữu context? **Đáp án:** caller; nó phải sống tới callback return.  
5. **Hỏi:** Callback được giữ pointer context sau call? **Đáp án:** không nếu API không transfer ownership.  
6. **Hỏi:** `const void *context` có ý nghĩa? **Đáp án:** callback đọc criterion, không sửa nó.  
7. **Hỏi:** Null callback policy? **Đáp án:** reject deterministic trước iteration.  
8. **Hỏi:** Empty input là lỗi? **Đáp án:** không nhất thiết; contract có thể success empty output.  
9. **Hỏi:** No-match khác error? **Đáp án:** predicate chạy hợp lệ nhưng selection rỗng.  
10. **Hỏi:** Pointer-to-pointer khi nào? **Đáp án:** callee cần replace pointer của caller.  
11. **Hỏi:** Output ownership cần ghi gì? **Đáp án:** creator, owner, cleanup time và failure state.  
12. **Hỏi:** Global state làm case khó test sao? **Đáp án:** hidden dependency/không reentrant; context tường minh hơn.  
13. **Hỏi:** Crash sau callback thường do? **Đáp án:** dangling context/output lifetime.  
14. **Hỏi:** Evidence negative path? **Đáp án:** exit/status, stdout/stderr và no leak trên path đã chạy.  
15. **Hỏi:** Peer kiểm gì? **Đáp án:** typedef, null checks, context lifetime, output free và test matrix.

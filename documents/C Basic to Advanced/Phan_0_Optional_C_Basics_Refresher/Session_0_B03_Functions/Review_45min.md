# B03 — Review chéo cuối ngày (45 phút)
## Checklist
- [ ] Đọc `OUT-B03-01..20`: prototype, linkage, inline/macro, arguments, arrays, recursion.
- [ ] Chạy CASE-B03 valid/null/boundary; review Lab API và Assignment calibration.
## 15 câu hỏi và đáp án
1. **Hỏi:** Prototype trước call vì sao? **Đáp án:** compiler kiểm signature, chặn call sai.  
2. **Hỏi:** Declaration/definition? **Đáp án:** contract/body implementation.  
3. **Hỏi:** Array parameter cần count? **Đáp án:** decay mất length; pass explicit size.  
4. **Hỏi:** Output pointer cần policy? **Đáp án:** null/failure/ownership phải rõ.  
5. **Hỏi:** Pass-by-value? **Đáp án:** copy value; không sửa caller.  
6. **Hỏi:** Multi-output? **Đáp án:** output pointers + status return.  
7. **Hỏi:** `const` input? **Đáp án:** cấm mutation qua API.  
8. **Hỏi:** `static` function? **Đáp án:** internal linkage trong translation unit.  
9. **Hỏi:** Inline guarantee? **Đáp án:** không bảo đảm speed/inlining.  
10. **Hỏi:** Macro-like function risk? **Đáp án:** repeated evaluation/no type check.  
11. **Hỏi:** Varargs risk? **Đáp án:** caller/callee tự giữ type contract.  
12. **Hỏi:** Recursion base case? **Đáp án:** dừng; thiếu nó stack overflow.  
13. **Hỏi:** Recursion guard? **Đáp án:** bound depth/input size.  
14. **Hỏi:** Null case tiêu chí kiểm chứng? **Đáp án:** status lỗi, output không đổi.  
15. **Hỏi:** Evidence? **Đáp án:** strict build, valid/null/empty/limit logs.

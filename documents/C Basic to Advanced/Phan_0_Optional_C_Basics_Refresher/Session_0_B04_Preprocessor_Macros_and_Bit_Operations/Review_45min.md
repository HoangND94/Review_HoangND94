# B04 — Review chéo cuối ngày (45 phút)
## Checklist
- [ ] Đọc preprocessor, macro/directive, bit operators/mask/shift và portable register image.
- [ ] Chạy CASE/Lab golden và invalid field; review Assignment config editor.
## 15 câu hỏi và đáp án
1. **Hỏi:** Preprocessor khi nào? **Đáp án:** trước compiler, trên token.  
2. **Hỏi:** Header guard? **Đáp án:** chặn declaration lặp.  
3. **Hỏi:** Macro side effect? **Đáp án:** operand có thể evaluate nhiều lần.  
4. **Hỏi:** Parentheses? **Đáp án:** tránh precedence thay nghĩa expression.  
5. **Hỏi:** `#if`/`if`? **Đáp án:** compile-time/runtime.  
6. **Hỏi:** AND? **Đáp án:** test/clear bits bằng mask.  
7. **Hỏi:** OR? **Đáp án:** set selected bits.  
8. **Hỏi:** XOR? **Đáp án:** toggle, không phải set idempotent.  
9. **Hỏi:** Shift rule? **Đáp án:** unsigned, index/range valid trước shift.  
10. **Hỏi:** Mask? **Đáp án:** cô lập bit/field.  
11. **Hỏi:** Field write? **Đáp án:** clear field rồi OR shifted validated value.  
12. **Hỏi:** Neighbor bits? **Đáp án:** golden test chứng minh không đổi.  
13. **Hỏi:** Macro/inline? **Đáp án:** function giữ type/evaluate once.  
14. **Hỏi:** MMIO thuộc case? **Đáp án:** không; chỉ memory image portable.  
15. **Hỏi:** Evidence? **Đáp án:** preprocess/strict build/golden-invalid logs.

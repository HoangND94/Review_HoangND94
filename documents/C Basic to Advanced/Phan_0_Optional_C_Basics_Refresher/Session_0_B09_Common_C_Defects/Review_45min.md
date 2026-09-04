# B09 — Review chéo cuối ngày (45 phút)
## Checklist
- [ ] Đọc alignment/packing, macro, integer, const, string, precedence, dynamic-memory defects.
- [ ] Chạy CASE-B09 golden và tiêu chí kiểm chứng cho trường hợp lỗis; đọc sanitizer/diagnostic evidence.
- [ ] Review Lab defect matrix và Assignment decoder cleanup matrix.
## 15 câu hỏi và đáp án
1. **Hỏi:** Vì sao không cast byte buffer thành struct? **Đáp án:** alignment, padding, endian và aliasing có thể sai; decode field-by-field.  
2. **Hỏi:** `{0x34,0x12}` decode LE? **Đáp án:** 4660; byte thấp OR byte cao shift 8.  
3. **Hỏi:** Packed struct portable không? **Đáp án:** không; extension/ABI-specific và có thể unaligned.  
4. **Hỏi:** Overflow check khi nào? **Đáp án:** trước arithmetic/cast, không sau khi value đã wrap.  
5. **Hỏi:** Signed/unsigned comparison risk? **Đáp án:** signed có thể convert unsigned thành huge value.  
6. **Hỏi:** Pointer-to-const/const pointer? **Đáp án:** object read-only qua pointer/pointer itself không đổi.  
7. **Hỏi:** String defect phổ biến? **Đáp án:** thiếu capacity/NUL; track destination length và terminate.  
8. **Hỏi:** Macro precedence fix? **Đáp án:** parenthesize parameters/full expression; tránh side effects.  
9. **Hỏi:** `sizeof` string pointer? **Đáp án:** pointer size, không string length; dùng bounded length logic.  
10. **Hỏi:** Leak origin? **Đáp án:** owner exit error path không cleanup.  
11. **Hỏi:** Sanitizer clean proof? **Đáp án:** chỉ fixture ran clean, không proof toàn bộ input.  
12. **Hỏi:** Defect matrix? **Đáp án:** input class→expected error/evidence, tránh claim mơ hồ.  
13. **Hỏi:** Precedence case? **Đáp án:** add parentheses/test expected expression.  
14. **Hỏi:** Failure-atomic parser? **Đáp án:** reject không publish partial record.  
15. **Hỏi:** Peer evidence? **Đáp án:** golden, malformed/boundary, cleanup matrix, strict/sanitizer logs.

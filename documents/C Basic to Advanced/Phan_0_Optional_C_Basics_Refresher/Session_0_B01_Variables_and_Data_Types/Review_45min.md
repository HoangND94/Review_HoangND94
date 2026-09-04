# B01 — Review chéo cuối ngày (45 phút)
## Checklist
- [ ] Đối chiếu `OUT-B01-02..10`: basic types, storage, keywords, pointer, struct/union/enum/cast.
- [ ] Chạy valid và invalid state/tag của `CASE-B01-01`; lưu ba stream evidence.
- [ ] Review Lab typed record và Assignment: type choice, range check, union tag, strict build.
## 15 câu hỏi và đáp án
1. **Hỏi:** Vì sao ID case dùng fixed-width unsigned?  
   **Đáp án:** contract cần range/format ổn định; dùng signed có thể làm ID âm và format sai.
2. **Hỏi:** `enum` giải quyết lỗi nào?  
   **Đáp án:** thay magic number bằng tập state có tên; vẫn phải validate input vì C cho phép cast value ngoài enum.
3. **Hỏi:** Struct khác union trong record?  
   **Đáp án:** struct giữ đồng thời fields; union chia storage nên chỉ member do tag chỉ định mới được đọc.
4. **Hỏi:** Nếu đọc union sai tag?  
   **Đáp án:** interpretation không có contract; reject input trước formatting và test tag mismatch.
5. **Hỏi:** Cast `long` sang `uint8_t` trước range check gây gì?  
   **Đáp án:** truncation/wrap; kiểm `0..UINT8_MAX` trước cast.
6. **Hỏi:** Khi nào dùng `static`?  
   **Đáp án:** khi cần storage duration hoặc internal linkage; không phải tối ưu mặc định.
7. **Hỏi:** Pointer field có sở hữu object không?  
   **Đáp án:** không; ownership/lifetime phải ghi trong API.
8. **Hỏi:** Vì sao format specifier là contract?  
   **Đáp án:** mismatch signedness/width làm output sai hoặc UB; dùng `<inttypes.h>` khi cần.
9. **Hỏi:** Flags nên dùng type gì?  
   **Đáp án:** unsigned fixed-width để shift/mask có domain rõ.
10. **Hỏi:** Storage duration khác scope?  
    **Đáp án:** object sống bao lâu/ tên nhìn thấy ở đâu.
11. **Hỏi:** Valid case chứng minh gì?  
    **Đáp án:** tag, state, flag và output label khớp contract.
12. **Hỏi:** Invalid severity test chứng minh gì?  
    **Đáp án:** validation xảy ra trước record success và stdout rỗng.
13. **Hỏi:** `const` có nghĩa record bất biến tuyệt đối?  
    **Đáp án:** chỉ cấm mutation qua view đó; object có thể đổi qua non-const owner.
14. **Hỏi:** Khi nào không dùng union?  
    **Đáp án:** khi mọi field phải cùng tồn tại hoặc không có discriminator tin cậy.
15. **Hỏi:** Evidence peer cần?  
    **Đáp án:** strict build, valid/invalid transcripts và README type/range rationale.

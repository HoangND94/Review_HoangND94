# B10 — Review chéo cuối ngày (45 phút)
## Checklist
- [ ] Đọc disk/OS mental model, `FILE*`, text/binary, position, APIs, `fflush`, S-record.
- [ ] Chạy CASE-B10 valid/missing/bad checksum; kiểm exact streams and exit.
- [ ] Review Lab read/write/reopen và Assignment CSV/S-record contracts.
## 15 câu hỏi và đáp án
1. **Hỏi:** `fopen` success chứng minh file hợp lệ? **Đáp án:** không; chỉ stream mở, schema/checksum vẫn cần validate.  
2. **Hỏi:** Text/binary khác gì? **Đáp án:** translation/contract stream khác; reopen đúng mode.  
3. **Hỏi:** Vì sao không loop `while(!feof)`? **Đáp án:** EOF chỉ set sau read fail; loop theo return read.  
4. **Hỏi:** Line truncation detect sao? **Đáp án:** bounded buffer không có newline khi chưa EOF; reject/read remainder theo contract.  
5. **Hỏi:** `feof`/`ferror` khi nào hỏi? **Đáp án:** sau read không trả expected data.  
6. **Hỏi:** Mỗi `FILE*` close mấy lần? **Đáp án:** exactly once sau open success, trên mọi path.  
7. **Hỏi:** `fflush` input stream? **Đáp án:** không dùng để xóa input; portable contract không định nghĩa như vậy.  
8. **Hỏi:** Vì sao check `fclose`? **Đáp án:** buffered write failure có thể xuất hiện muộn.  
9. **Hỏi:** Active position đổi khi nào? **Đáp án:** read/write/seek; update semantics theo stream mode.  
10. **Hỏi:** CSV parser reject partial vì sao? **Đáp án:** consumer không được dùng data chưa validated.  
11. **Hỏi:** Duplicate ID xử lý? **Đáp án:** reject before commit/publish collection.  
12. **Hỏi:** Checksum S-record chứng minh gì? **Đáp án:** phát hiện corruption ngẫu nhiên, không phải security signature.  
13. **Hỏi:** S1/S9 profile test? **Đáp án:** valid, bad hex/count/checksum, missing/end ordering.  
14. **Hỏi:** Write-roundtrip tiêu chí kiểm chứng? **Đáp án:** write→flush→close→reopen→byte compare exact payload.  
15. **Hỏi:** Peer evidence? **Đáp án:** command, exit code, stdout/stderr, fixture hash và output files dưới scratch.

# B08 — Review chéo cuối ngày (45 phút)
## Checklist
- [ ] Đọc baseline, trade-off, compiler transformations, flags, MAP/profile.
- [ ] Chạy CASE-B08 ở `-O0`/`-O2`; so output/checksum trước timing.
- [ ] Review Lab/Assignment: measurement conditions, decision keep/drop, limitation.
## 15 câu hỏi và đáp án
1. **Hỏi:** Vì sao correctness trước optimization? **Đáp án:** fast wrong output là regression; golden tiêu chí kiểm chứng khóa semantics.  
2. **Hỏi:** O0/O2 output khác nói gì? **Đáp án:** nghi UB/uninitialized/tiêu chí kiểm chứng trước performance claim.  
3. **Hỏi:** Baseline gồm gì? **Đáp án:** source, flags, input, environment, output/checksum và measurement method.  
4. **Hỏi:** Một timing đủ kết luận? **Đáp án:** không; lặp cùng condition, ghi nhiễu/limitation.  
5. **Hỏi:** CSE là gì? **Đáp án:** reuse expression chung nếu semantics cho phép.  
6. **Hỏi:** Constant propagation? **Đáp án:** thay value biết trước, compiler/source có thể làm.  
7. **Hỏi:** Dead code elimination risk? **Đáp án:** không bỏ observable side effect.  
8. **Hỏi:** Loop invariant motion? **Đáp án:** move expression không đổi ra ngoài loop sau chứng minh.  
9. **Hỏi:** Unrolling trade-off? **Đáp án:** giảm overhead nhưng tăng code size/cache pressure.  
10. **Hỏi:** Inline guarantee? **Đáp án:** không; compiler quyết định.  
11. **Hỏi:** Strength reduction? **Đáp án:** thay operation đắt bằng tương đương rẻ khi safe.  
12. **Hỏi:** Profile dùng sao? **Đáp án:** evidence hotspot trên workload, không phải truth mọi workload.  
13. **Hỏi:** MAP/size evidence? **Đáp án:** báo footprint toolchain-specific, không C guarantee.  
14. **Hỏi:** Khi bỏ candidate? **Đáp án:** output đổi, gain không tái lập hoặc trade-off không đáng.  
15. **Hỏi:** Peer evidence? **Đáp án:** compare outputs, ≥3 runs, flags/environment, size/profile report.

# So sánh kiến trúc CISC và RISC

## 1. Giới thiệu khái niệm

### CISC (Complex Instruction Set Computer)
- **Kiến trúc "tập lệnh phức tạp"** - bộ xử lý hỗ trợ nhiều lệnh đa dạng
- Mỗi lệnh có thể thực hiện nhiều chức năng (truy cập bộ nhớ, phép tính, lưu kết quả) trong một lệnh duy nhất
- Một lệnh CISC có thể "đọc - xử lý - ghi" trong cùng một câu lệnh
- Chứa nhiều bước vi mô bên trong

### RISC (Reduced Instruction Set Computer)
- **Kiến trúc "tập lệnh giảm thiểu"** - mỗi lệnh thực hiện chức năng đơn giản
- Thường chỉ một phép toán cơ bản hoặc một bước
- Được thực hiện trong một chu kỳ nếu có thể
- Sử dụng mô hình **load-store** (chỉ có lệnh LOAD/STORE truy cập bộ nhớ)

**Mục tiêu của RISC**: Giảm độ phức tạp phần cứng, dễ pipeline, tăng khả năng tối ưu của compiler, đạt hiệu suất cao hơn.

## 2. Ưu điểm và nhược điểm

### 2.1 CISC

**Ưu điểm:**
- Kích thước mã (code density) nhỏ hơn
- Compiler bớt "gánh nặng"
- Tương thích phần mềm rộng (đặc biệt x86)
- Hỗ trợ nhiều chế độ địa chỉ phong phú

**Nhược điểm:**
- Phức tạp trong phần cứng
- Mỗi lệnh cần nhiều chu kỳ để thực thi
- Tiêu thụ năng lượng cao hơn
- Khó tối ưu pipeline và parallelism

### 2.2 RISC

**Ưu điểm:**
- Pipeline dễ thiết kế (lệnh đơn giản, thời gian thực thi đồng đều)
- Phần cứng đơn giản hơn
- Hiệu quả năng lượng cao hơn
- Dễ tối ưu hóa pipeline và đa luồng
- Compiler đóng vai trò quan trọng

**Nhược điểm:**
- Số lệnh cần dùng nhiều hơn → tăng độ dài chương trình
- Tăng nhu cầu truy cập bộ nhớ
- Phụ thuộc nhiều vào compiler
- Mất ưu thế nếu không được tối ưu tốt

## 3. So sánh theo tiêu chí

| Tiêu chí | CISC | RISC |
|----------|------|------|
| **Cấu trúc tập lệnh** | Nhiều lệnh, kích thước biến đổi, nhiều chế độ địa chỉ phức tạp | Tập lệnh ít, định dạng cố định, địa chỉ đơn giản, chỉ load/store truy cập bộ nhớ |
| **Tốc độ xử lý** | Lệnh phức tạp cần nhiều chu kỳ, giải mã chậm | Lệnh đơn giản, thời gian thực thi cân bằng, dễ pipeline, throughput cao |
| **Kích thước chương trình** | Nhỏ hơn (lệnh làm nhiều việc) | Lớn hơn (cần nhiều lệnh) |
| **Độ phức tạp phần cứng** | Cao (giải mã phức tạp, microcode) | Thấp hơn (giải mã đơn giản, logic gọn) |
| **Ứng dụng thực tế** | x86 (Intel/AMD) - máy cá nhân, máy chủ, desktop | ARM (di động, nhúng), MIPS, SPARC, RISC-V - điện thoại, máy tính bảng, IoT |

## 4. Kết luận

- **CISC**: Ưu thế giảm số lệnh, thuận tiện cho compiler, nhưng phức tạp phần cứng, khó tối ưu pipeline
- **RISC**: Đơn giản hóa lệnh, dễ pipeline, hiệu suất cao, tiết kiệm năng lượng, nhưng cần compiler mạnh

**Thực tế hiện nay**: Các kiến trúc thương mại (như x86) đã pha trộn kỹ thuật - giải mã lệnh CISC thành micro-ops kiểu RISC, nên ranh giới giữa hai kiến trúc không còn rõ rệt như trước.
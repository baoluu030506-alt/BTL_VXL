# BÀI TẬP LỚN VI XỬ LÝ - VI ĐIỀU KHIỂN (CO3009)
**Đề tài:** Hệ thống đèn giao thông 2 tuyến đường trên mạch XNUCLEO-F103RB.

## 1. Hướng dẫn làm việc nhóm (Quy trình Git)
Lịch sử commit là căn cứ để giảng viên chấm điểm cá nhân. Mọi thành viên phải tuân thủ luồng làm việc sau:

**Bước 1: Clone và cấu hình tài khoản (Chỉ làm 1 lần đầu tiên)**
Mỗi thành viên clone nhánh `dev` về máy và BẮT BUỘC cài đặt tên/email của mình:
```bash
git clone -b dev https://github.com/baoluu030506-alt/BTL_VXL.git
cd BTL_VXL
git config --local user.name "Họ Tên Của Bạn"
git config --local user.email "email_truong@hcmut.edu.vn"
```

**Bước 2: Tạo nhánh tính năng (Feature Branch)**
Không ai code trực tiếp lên nhánh `main` hay `dev`. Khi được phân công làm phần nào, hãy tạo nhánh mới từ nhánh `dev`:
```bash
git checkout dev
git pull origin dev
git checkout -b feature/ten-tinh-nang  # Ví dụ: feature/scheduler, feature/button
```

**Bước 3: Code và Commit**
* Commit thường xuyên, mỗi commit chứa 1 thay đổi có ý nghĩa.
* Thông điệp commit (Message) phải rõ ràng, ví dụ: `scheduler: add one-shot task support`.
```bash
git add .
git commit -m "ten_module: mo ta ngan gon viec da lam"
git push origin feature/ten-tinh-nang
```
Sau khi code xong và test chạy ổn định, tạo Pull Request (PR) trên GitHub để gộp vào nhánh `dev`.

## 2. Quy ước viết code (Coding Convention)
* **Tên file:** Dùng chữ thường, nối bằng dấu gạch dưới (VD: `fsm_automatic.c`, `button.c`).
* **Tên hàm:** Theo định dạng `<module>_<hành_động>` (VD: `button_read()`, `traffic_set_state()`).
* **Không dùng hàm HAL_Delay():** Kể từ Bước 4, cấm sử dụng `HAL_Delay()` trong chương trình chính, mọi tác vụ phải chạy qua Scheduler.
* **Tách biệt phần cứng:** Lệnh gọi HAL (như `HAL_GPIO_...`) chỉ được nằm trong các file module phụ trợ và `main.c`. Các file máy trạng thái (`fsm_*.c`) tuyệt đối KHÔNG chứa lệnh HAL phần cứng.

## 3. Hướng dẫn Build và Nạp (Dành cho Demo)
1. Mở dự án bằng **STM32CubeIDE**.
2. Nhấn biểu tượng cây búa (Build) hoặc `Ctrl + B` để biên dịch dự án.
3. Cắm mạch XNUCLEO-F103RB vào máy tính.
4. Nhấn biểu tượng con bọ (Debug) hoặc `F11`. Đảm bảo cấu hình Debug trong `.ioc` là **Serial Wire**.
5. Nhấn Resume (`F8`) để chương trình bắt đầu chạy trên mạch.

# BRANCH: FS - FILE SYSTEM

Nhánh này chứa mã nguồn thực hiện yêu cầu của phần 4.2: File System trong Đồ án 2.

## 1. Nội dung thực hiện

### Thêm hỗ trợ tệp kích thước lớn
- **Vấn đề ban đầu:** Hệ thống xv6 mặc định giới hạn tệp ở mức 268 blocks. Lệnh `bigfile` mặc định sẽ báo lỗi "file is too small".
- **Kết quả:** Tăng kích thước tối đa của tệp lên **65803 blocks** mà không làm thay đổi kích thước của `on-disk inode`.

## 2. Hướng dẫn Cài đặt & Môi trường

Để biên dịch và chạy XV6, cần chuẩn bị môi trường trên Ubuntu (hoặc WSL).

**Bước 1: Cài đặt các công cụ cần thiết**

Mở terminal và chạy các lệnh sau:
```bash
sudo apt update
sudo apt install build-essential
sudo apt install gcc-riscv64-linux-gnu
sudo apt install binutils-riscv64-linux-gnu
sudo apt install qemu-system-misc
```

**Bước 2: Lấy source code XV6**
```bash
git clone https://github.com/ltny24/PROJECT-2-Page-Table-and-File-System.git
cd PROJECT-2-Page-Table-and-File-System
```

---

## 3. Hướng dẫn chạy test

Đảm bảo đang ở nhánh `fs`. Nếu không, cần tải và chuyển sang branch `fs`:
```bash
git fetch
git checkout fs
```
Khởi tạo và chạy xv6:
```bash
make clean
make qemu
```
Bên trong hệ điều hành xv6, chạy tuần tự các lệnh sau (Lệnh `bigfile` sẽ mất hơn 1.5 phút để hoàn thành việc ghi dữ liệu):
```bash
bigfile
usertests
```

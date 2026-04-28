# BRANCH: PGTBL - PAGE TABLE

Nhánh này chứa mã nguồn thực hiện các yêu cầu của phần 4.1: Page Table trong Đồ án 2

## 1. Nội dung thực hiện

### 1.1. Speed up system calls
- **Mục tiêu:** Tối ưu hóa lời gọi hệ thống.
- **Cơ chế:** Map một trang read-only tại địa chỉ `USYSCALL` khi mỗi tiến trình được tạo ra. Lưu trữ `struct usyscall` chứa PID của tiến trình tại đầu trang này.
- **Kết quả:** Loại bỏ nhu cầu chuyển đổi khi thực thi system call.

### 1.2. Print a page table
- **Mục tiêu:** Hỗ trợ debug và trực quan hóa bảng trang RISC-V.
- **Cơ chế:** Viết hàm `vmprint()` nhận đối số `pagetable_t` và in ra cấu trúc phân cấp (cây) của bảng trang với các dòng định dạng độ sâu bằng `..`. Hàm bỏ qua các PTE không hợp lệ.

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
Đảm bảo đang ở nhánh `pgtbl`. Nếu không, cần tải và chuyển sang branch `pgtbl`:
```bash
git fetch
git checkout pgtbl
```
Khởi tạo và chạy xv6:
```bash
make clean
make qemu
```
Trong môi trường xv6, chạy lệnh sau để test Task 1:
```bash
pgtbltest
test_usyscall
```

Để test Task 2:
```bash
make grade
```

---


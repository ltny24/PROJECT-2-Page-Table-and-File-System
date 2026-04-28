# ĐỒ ÁN 2: PAGE TABLE VÀ FILE SYSTEM

**## 1. Thông tin chung**
- **Môn học:** Hệ điều hành  
- **Môi trường:** Linux

Đồ án này tập trung vào việc tùy chỉnh bộ nhớ ảo (Page Table) và hệ thống tệp (File System) trên hệ điều hành xv6:
- **Page Table:** Tăng tốc độ system calls và in bảng trang.
- **File System:** Hỗ trợ các tệp tin có kích thước lớn.

---

**## 2. Thành viên nhóm**

| STT | Họ và tên | MSSV | Công việc | Hoàn thành |
|:--:|:--|:--:|:--|:--:|
| 1 | Hồ Thị Như Ngọc | 24127089 | `speed up system calls`, README, báo cáo | 100% |
| 2 | Phan Đình Minh Quân | 24127517 | `file system` | 100% |
| 3 | Lê Thị Như Ý | 24127595 | `print a page table`, GitHub | 100% |

---

**## 3. Chức năng chính đã cài đặt**

### Phần 1: Page Table (Nhánh `pgtbl`)
- **Speed up system calls:** Tối ưu hóa lời gọi hệ thống `getpid()` bằng cách chia sẻ dữ liệu trong vùng read-only giữa userspace và kernel.
- **Print a page table:** Cài đặt hàm `vmprint()` để in nội dung của bảng trang (page table) RISC-V.

### Phần 2: File System (Nhánh `fs`)
- **Large file:** Mở rộng kích thước tệp tối đa của xv6 từ 268 blocks lên 65803 blocks bằng cách cài đặt "doubly-indirect block".

---

**## 4. Hướng dẫn Cài đặt & Môi trường**

Để biên dịch và chạy XV6, cần chuẩn bị môi trường trên Ubuntu (hoặc WSL).

**Bước 1: Cài đặt các công cụ cần thiết**
Mở terminal và chạy các lệnh sau:
```bash
sudo apt update
sudo apt install build-essential
sudo apt install gcc-riscv64-linux-gnu
sudo apt install binutils-riscv64-linux-gnu
sudo apt install qemu-system-misc

**Bước 2: Lấy source code XV6**
```bash
git clone https://github.com/ltny24/PROJECT-2-Page-Table-and-File-System.git
cd PROJECT-2-Page-Table-and-File-System
```

---

## 5. Hướng dẫn Test các chức năng

Đồ án này được chia làm 2 phần thực hiện trên 2 nhánh (branch) khác nhau.

### Page Table
Đầu tiên, cần tải và chuyển sang branch `pgtbl`:
```bash
git fetch
git checkout pgtbl
```

**Kiểm thử Task 1 - Speed up system calls:**
Khởi tạo và chạy xv6:
```bash
make clean
make qemu
```
Tại màn hình dòng lệnh của xv6, chạy các lệnh test:
```bash
pgtbltest
test_usyscall
```

**Kiểm thử Task 2 - Print a page table:**
Thoát xv6 (nếu đang chạy), sau đó biên dịch và chấm điểm tự động:
```bash
make qemu
make grade
```

### File system
Tiếp theo, chuyển sang nhánh `fs` để kiểm thử hệ thống tệp:
```bash
git fetch
git checkout fs
```

Khởi tạo hệ thống tệp mới và chạy xv6:
```bash
make clean
make qemu
```
Tại màn hình dòng lệnh của xv6, chạy các bài test:
```bash
bigfile
usertests
```
---

## 7. Tài liệu tham khảo
- Sách xv6 (xv6 Book).
- Tài liệu lý thuyết và thực hành môn học (Moodle).
---


#pragma once
#include "init.h"

// Viết stack để lưu phép toán trong quá trình chuyển biểu thức trung tố
// thành biểu thức hậu tố
struct node
{
	char data;
	node * next;
};

// Viết stack để lưu toán hạng trong quá trình tính kết quả biểu thức hậu tố của số thực
struct Fnode
{
	bigNum data;
	Fnode * next;
};

bool isEmpty(node* head); // hàm kiểm tra stack node có phải là chuỗi rỗng, nếu có trả về 1, ngược lại thì trả về 0
char peek(node *head); // hàm đọc giá trị ở đầu stack node
void push(node *&head, char x); // hàm thêm vào đầu stack node một phần tử có giá trị là x
char pop(node *&head); // hàm lấy ra stack node 1 phần tử kiểu char

void xoaDauCachThua(char *s); // hàm xóa dấu cách thừa của biểu thức hậu tố
bool soPhepToan(char a, char b); // hàm so sánh thứ tự ưu tiên của phép toán a và b
								 // nếu thứ tự ưu tiên của a lớn hơn hoặc bằng b thì trả về 1
								 // ngược lại thì trả về 0

bool isoperator(char x);

bool KiemTraBieuThucPhuHop(char *T); // hàm kiểm tra biểu thức trung tố nhập vào có phải là biểu thức đúng không
									 // nếu có thì trả về 1, ngược lại trả về 0

char * nhapBieuThucTrungTo(); // hàm nhập biểu thức trung tố

bool isEmpty(Fnode* head); // hàm kiểm tra stack Fnode có phải là chuỗi rỗng, nếu có trả về 1, ngược lại thì trả về 0
bigNum peek(Fnode *head); // hàm đọc giá trị ở đầu stack Fnode
void push(Fnode *&head, bigNum x); // hàm thêm vào đầu stack Fnode một phần tử có giá trị là x
bigNum pop(Fnode *&head); // hàm lấy ra stack Fnode 1 phần tử kiểu char

char * chuyenBieuThucTrungToThanhBieuThucHauTo(char *T);// hàm chuyển biểu thức trung tố thành biểu thức hậu tố của số thực
															 // input là biểu thức trung tố, output là biểu thức hậu tố

bigNum thucHienPhepToan(bigNum ToanHang1, char PhepToan, bigNum ToanHang2); // hàm thực hiện phép tính toán số thực
																						   // lấy toán hạng 1 thực hiện phép toán với toán hạng 2 
bigNum thucHienPhepToan(bigNum ToanHang, char PhepToan); // hàm thực hiện phép tính toán số thực với một đối số toán hạng

bigNum tinhGiaTriBieuThucHauTo(char *H);// hàm tính giá trị của biểu thức hậu tố số thực
												  // input là biểu thức hậu tố, output là số thực bigNum

bigNum tinhBieuThuc(char *T); // hàm tổng hợp lại để sử dụng giao diện số thực gọn gàng hơn
bigNum doiChuoiSangNum(char *&s); // hàm chuyển từ chuỗi sang số thực bigNum
										   // dùng để chuyển chuỗi sang số trong quá trình tính giá trị biểu thức hậu tố
bool laSoPi(char *s); // hàm kiểm tra chuỗi có phải là chuỗi số pi hay không
					  // trả về 1 khi chuỗi s là số pi hợp lệ, ngược lại trả về 0
bool laSoE(char *s);  // hàm kiểm tra chuỗi có phải là chuỗi số e hay không
					  // trả về 1 khi chuỗi s là số e hợp lệ, ngược lại trả về 0
bigNum doiChuoiSangSoPi(char *&s); // hàm chuyển từ chuỗi sang số pi
									   // dùng để chuyển chuỗi sang số trong quá trình tính giá trị biểu thức hậu tố
bigNum doiChuoiSangSoE(char *&s); // hàm chuyển từ chuỗi sang số e
									  // dùng để chuyển chuỗi sang số trong quá trình tính giá trị biểu thức hậu tố


void deleteChar(char *&s);
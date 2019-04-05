#pragma once
#define MAUNEN 132
#define MAUBIEUTHUC 7
#define MAUNENDAPAN 240
#define MAUNENDAPANHOPLE 155
#define MAUCHUDAPANHOPLE 158	
#define MAUNENDAPANLOI 204
#define MAUCHUDAPANLOI 206
#define MAUHIS 143
#define MAUESC 226
#define MAUCAL 31
#define NENCAL 115
#define MAUPAUSE 136
#define SIZE_X 1200
#define SIZE_Y 550

// Nguồn Internet
void resizeConsole(int width, int height);
void textcolor(int x);
void gotoxy(int x, int y);
void XoaManHinh();
void ToMau(int x, int y, char *a, int color);

// Tự viết
void toMauNenCal();
void inCal();
void taoKhung();
void run();
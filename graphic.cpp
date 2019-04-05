#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "init.h"
#include "expression.h"
#include "graphic.h"
using namespace std;

// Hàm thay đổi kích cỡ của khung cmd với tham số truyền vào là chiều cao, chiều rộng.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

// Hàm dịch chuyển con trỏ đến tọa độ x, y.
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

// Hàm xóa màn hình.
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

// Hàm tự viết
void ToMau(int x, int y, char *a, int color) // x, y là tọa độ con trỏ cần nhảy đến để viết, a là chuỗi cần truyền vào, color là màu truyền vào.
{
	gotoxy(x, y);
	textcolor(color);
	cout << a;
	textcolor(MAUBIEUTHUC);
}

void ToMau(int x, int y, char a, int color) // x, y là tọa độ con trỏ cần nhảy đến để viết, a là chuỗi cần truyền vào, color là màu truyền vào.
{
	gotoxy(x, y);
	textcolor(color);
	cout << a;
	textcolor(MAUBIEUTHUC);
}

// Moi viet
void toMauNenCal()
{
	for (int y = 0; y < 10; y++)
		ToMau(105, 20 + y, (char *) "                                    ", NENCAL);
}

void inCal()
{
	ToMau(110 + 6, 22, (char *) "    ", MAUCAL);
	ToMau(110 + 17, 22, (char *) " ", MAUCAL);
	ToMau(110 + 24, 22, (char *) " ", MAUCAL);

	ToMau(110 + 4, 23, (char *) " ", MAUCAL);
	ToMau(110 + 9, 23, (char *) " ", MAUCAL);
	ToMau(110 + 15, 23, (char *) " ", MAUCAL);
	ToMau(110 + 17, 23, (char *) " ", MAUCAL);
	ToMau(110 + 23, 23, (char *) " ", MAUCAL);

	ToMau(110 + 3, 24, (char *) " ", MAUCAL);
	ToMau(110 + 13, 24, (char *) " ", MAUCAL);
	ToMau(110 + 17, 24, (char *) " ", MAUCAL);
	ToMau(110 + 22, 24, (char *) " ", MAUCAL);

	ToMau(110 + 2, 25, (char *) " ", MAUCAL);
	ToMau(110 + 11, 25, (char *) "       ", MAUCAL);
	ToMau(110 + 21, 25, (char *) " ", MAUCAL);

	ToMau(110 + 1, 26, (char *) " ", MAUCAL);
	ToMau(110 + 6, 26, (char *) " ", MAUCAL);
	ToMau(110 + 10, 26, (char *) " ", MAUCAL);
	ToMau(110 + 16, 26, (char *) " ", MAUCAL);
	ToMau(110 + 20, 26, (char *) " ", MAUCAL);

	ToMau(110 + 1, 27, (char *) "    ", MAUCAL);
	ToMau(110 + 9, 27, (char *) " ", MAUCAL);
	ToMau(110 + 15, 27, (char *) " ", MAUCAL);
	ToMau(110 + 19, 27, (char *) "      ", MAUCAL);
}

void taoKhung()
{
	resizeConsole(SIZE_X, SIZE_Y); // 145 chữ ngang, 31

	ToMau(1, 1, (char *) "     ", MAUNEN);// In thanh trên
	for (int x = 1; x <= 28; x++)
		ToMau(x * 5 + 1, 1, (char *) "     ", MAUNEN);
	ToMau(1, 2, (char *) "     ", MAUNEN);// In thanh trên
	for (int x = 1; x <= 28; x++)
		ToMau(x * 5 + 1, 2, (char *) "     ", MAUNEN);

	ToMau(1, 30, (char *) "     ", MAUNEN);// In thanh dưới
	for (int x = 1; x <= 28; x++)
		ToMau(x * 5 + 1, 30, (char *) "     ", MAUNEN);
	ToMau(1, 31, (char *) "     ", MAUNEN);// In thanh dưới
	for (int x = 1; x <= 28; x++)
		ToMau(x * 5 + 1, 31, (char *) "     ", MAUNEN);

	for (int y = 3; y <= 29; y++)// In thanh trái
		ToMau(1, y, (char *) "     ", MAUNEN);

	for (int y = 3; y <= 29; y++)// In thanh phải
		ToMau(141, y, (char *) "     ", MAUNEN);

	for (int y = 3; y <= 29; y++)// In thanh ngăn giữa
		ToMau(100, y, (char *) "     ", MAUNEN);	

	for (int x = 1; x <= 19; x++)// In khung ngăn đáp án
		if (x == 1) ToMau(x * 5 + 1, 22, (char *) "     ", MAUNEN);
		else ToMau(x * 5, 22, (char *) "     ", MAUNEN);

	ToMau(105, 15, (char *) "                                    ", MAUNEN);// In thanh ngăn History


	for (int y = 0; y < 7; y++)// In khung đáp án
	{
		for (int x = 1; x <= 19; x++)
			if (x == 1) ToMau(x * 5 + 1, 23 + y, (char *) "     ", MAUNENDAPAN);
			else ToMau(x * 5, 23 + y, (char *) "     ", MAUNENDAPAN);
	}

	ToMau(120, 2, (char *) "History", MAUHIS);

	gotoxy(1, 1); // Trở lại full khung hình
}


void run()
{
	taoKhung();
	toMauNenCal();
	inCal();
	gotoxy(6, 3);

	//gotoxy(100, 3);//

	bool calState = 0, printState = 0, clrState = 0, hisState = 0;
	char *exp = NULL, *result = NULL;
	bigNum re;
	initBigNum(re);
	int Xpos = 6, Ypos = 3;

	while (1)
	{
		char x;
		if (_kbhit())
		{
			// input processing

			x = _getch();
			if (x < -1 || x > 255) continue;
			if (x != 0 && x != 13)
			{
				if (isalnum(x) || isoperator(x))
				{
					Xpos++;
					cout << x;
					if (Xpos >= 94 + 6 && Ypos < 21)
					{
						Xpos = 6;
						gotoxy(Xpos, ++Ypos);
					}

					if (Xpos >= 94 + 6 && Ypos == 21)
						ToMau(94 + 2, 21, (char *)"...", MAUBIEUTHUC);

					pushString(exp, x);
				}
			}

			if (x == 8) // Phím xoá backspace
			{
				if (exp != NULL && strlen(exp) > 0)
				{
					x = popString(exp); // 
					if (Xpos == 6)
					{
						Xpos = 94 + 5;
						Ypos--;
						ToMau(Xpos, Ypos, (char *) " ",MAUBIEUTHUC);
						gotoxy(Xpos, Ypos);
					}
					else
					{
						if (Xpos >= 94 + 3 && Ypos == 21)
						{
							Xpos--;
							if (Xpos > 94 + 6)
							{
								ToMau(94 + 5, 21, exp[strlen(exp) - 1], MAUBIEUTHUC);
								gotoxy(94 + 5, 21);
							}
							else
							{
								if (Xpos == 94 + 6)
								{
									ToMau(94 + 2, 21, exp[strlen(exp) - 4], MAUBIEUTHUC);
									ToMau(94 + 3, 21, exp[strlen(exp) - 3], MAUBIEUTHUC);
									ToMau(94 + 4, 21, exp[strlen(exp) - 2], MAUBIEUTHUC);
									ToMau(94 + 5, 21, exp[strlen(exp) - 1], MAUBIEUTHUC);
									gotoxy(94 + 5, Ypos);
								}
								else
								{
									ToMau(Xpos, 21, ' ', MAUBIEUTHUC);
									gotoxy(Xpos, Ypos);
								}
							}
						}
						else // Trường hợp bình thường
						{
							Xpos--;
							ToMau(Xpos, Ypos, (char *) " ", MAUBIEUTHUC);
							gotoxy(Xpos, Ypos);
						}
					}
				}
			}

			if (x == 13 && exp != NULL && strlen(exp) > 0)
			{
				if (KiemTraBieuThucPhuHop(exp) == 0)
				{
					catString(result, (char *) "Invalid expression!\n");

					printState = 1;
				}
				else calState = 1;
			}

			if (x == 27) // Escape
			{
				cout << (char)7;
				for (int y = 0; y < 7; y++)// In lại khung đáp án
				{
					// câu lệnh dài :))
					ToMau(6, 23 + y, (char *) "                                                                                              ",
						MAUESC);
				}
				ToMau(6, 23, (char *) "Are you want to quit? Y\\N: ", MAUESC);
				textcolor(MAUESC);

				while (1)
				{
					if (_kbhit())
					{
						x = _getch();
						if (x == 'Y' || x == 'y') exit(0);
						if (x == 'N' || x == 'n')
						{
							for (int y = 0; y < 7; y++)// In lại khung đáp án
							{
								// câu lệnh dài :))
								ToMau(6, 23 + y, (char *) "                                                                                              ",
									MAUNENDAPAN);
							}

							gotoxy(Xpos, Ypos);

							break;
						}
					}
				}
			}
		}

		if (calState == 1)
		{
			// cal processing

			re = tinhBieuThuc(exp);
			deleteZeroUnnecessary(re);
			result = convertBigNumToString(re);
			freeBigNum(re);

			calState = 0;
			printState = 1;
		}

		if (printState == 1)
		{
			// print processing

			cout << (char)7; // Kêu vui tai <3
			printState = 0;
			clrState = 1;

			if (result != NULL && result[0] != 'W' && result[0] != 'I')
			{
				for (int y = 0; y < 7; y++)// In khung đáp án hợp lệ
				{
					// câu lệnh dài :))
					ToMau(6, 23 + y, (char *) "                                                                                              ", 
						MAUNENDAPANHOPLE);
				}

				textcolor(MAUCHUDAPANHOPLE);
			}
			else
			{
				for (int y = 0; y < 7; y++)// In khung đáp án hợp lệ
				{
					// câu lệnh dài :))
					ToMau(6, 23 + y, (char *) "                                                                                              ",
						MAUNENDAPANLOI);
				}

				textcolor(MAUCHUDAPANLOI);

			}

			if (result != NULL && strlen(result) > 658)// ngắt bớt đáp án quá dài
			{
				result = (char *)realloc(result, 659);
				result[658] = 0;
				result[655] = result[656] = result[657] = '.';
			}

			gotoxy(6, 23); // In đáp án
			int XDA = 6, YDA = 23, iDA = 0;
			while (1)
			{
				XDA++;
				if (result[iDA] == 0) break;// In hết đáp án
				cout << result[iDA++];
				if (XDA >= 94 + 6)
				{
					XDA = 6;
					gotoxy(XDA, ++YDA);
				}
			}


			gotoxy(70, 22);
			textcolor(MAUPAUSE);
			system("pause");
			textcolor(MAUBIEUTHUC);
		}

		if (clrState == 1)
		{
			// clear screen processing
			for (int y = 0; y < 19; y++)// In lại khung biểu thức
			{
				// câu lệnh dài :))
				ToMau(6, 3 + y, (char *) "                                                                                              ",
					MAUBIEUTHUC);
			}

			for (int y = 0; y < 7; y++)// In lại khung đáp án
			{
				// câu lệnh dài :))
				ToMau(6, 23 + y, (char *) "                                                                                              ",
					MAUNENDAPAN);
			}

			Xpos = 6;
			Ypos = 3;

			clrState = 0;
			hisState = 1;
		}

		if (hisState == 1)
		{
			// In biểu thức lịch sử
			{
				for (int y = 0; y < 12; y++)
				{
					// câu lệnh dài :))
					ToMau(105, 3 + y, (char *) "                                    ",
						MAUBIEUTHUC);
				}

				textcolor(MAUBIEUTHUC);

				if (exp != NULL && strlen(exp) > 432)// ngắt bớt biểu thức quá dài
				{
					exp = (char *)realloc(exp, 433);
					exp[432] = 0;
					exp[429] = exp[430] = exp[431] = '.';
				}

				gotoxy(105, 3); // In biểu thức
				int XDA = 105, YDA = 3, iDA = 0;
				while (1)
				{
					XDA++;
					if (exp[iDA] == 0) break;// In hết đáp án
					cout << exp[iDA++];
					if (XDA >= 105 + 36)
					{
						XDA = 105;
						gotoxy(XDA, ++YDA);
					}
				}
			}

			// In đáp án lịch sử
			{
				if (result != NULL && result[0] != 'W' && result[0] != 'I')
				{
					for (int y = 0; y < 4; y++)// In khung đáp án hợp lệ
					{
						// câu lệnh dài :))
						ToMau(105, 16 + y, (char *) "                                    ",
							MAUNENDAPANHOPLE);
					}

					textcolor(MAUCHUDAPANHOPLE);
				}
				else
				{
					for (int y = 0; y < 4; y++)// In khung đáp án hợp lệ
					{
						// câu lệnh dài :))
						ToMau(105, 16 + y, (char *) "                                    ",
							MAUNENDAPANLOI);
					}

					textcolor(MAUCHUDAPANLOI);

				}

				if (result != NULL && strlen(result) > 144)// ngắt bớt đáp án quá dài
				{
					result = (char *)realloc(result, 145);
					result[144] = 0;
					result[141] = result[142] = result[143] = '.';
				}

				gotoxy(105, 16); // In đáp án
				int XDA = 105, YDA = 16, iDA = 0;
				while (1)
				{
					XDA++;
					if (result[iDA] == 0) break;// In hết đáp án
					cout << result[iDA++];
					if (XDA >= 105 + 36)
					{
						XDA = 105;
						gotoxy(XDA, ++YDA);
					}
				}
			}

			freeString(exp);
			freeString(result);

			gotoxy(6, 3);
			textcolor(MAUBIEUTHUC);
			hisState = 0;
		}
	}
}
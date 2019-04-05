#include "expression.h"
#include "operation.h"
#include "warnings.h"
#include "compare.h"
#include <iostream>
#include <malloc.h>

using namespace std;

node * taoNode(char x)
{
	node *p = (node *)malloc(sizeof(node) * 1);
	if (p == NULL) malloc_ERROR();
	p->data = x;
	p->next = NULL;
	return p;
}

void push(node *&head, char x)
{
	node *p = taoNode(x);
	p->next = head;
	head = p;
}

char peek(node *head)
{
	node *p = head;
	if (p == NULL) return ' ';
	return p->data;
}

char pop(node *&head)
{
	if (head == NULL) return ' ';

	char x = head->data;
	node* p = head;
	head = head->next;
	free(p);
	return x;
}

bool isEmpty(node *head)
{
	return head == NULL;
}

void xoaDauCachThua(char *s)
{
	int len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		if (i > 0 && s[i] == ' ' && s[i - 1] == ' ')
		{
			for (int j = i; j < len; j++)
			{
				s[j] = s[j + 1];
			}
			i--;
		}
	}
}

bool soPhepToan(char a, char b)
{
	int ba = 0, bb = 0;
	if (a == '!') ba = 5;
	else if (a == '^') ba = 4;
	else if (a == '*' || a == '/' || a == '%') ba = 3;
	else if (a == '+' || a == '-') ba = 2;
	else if (a == '<' || a == '>' || a == '=') ba = 1;
	else if (a == '(') ba = 0;
	else ba = 6;

	if (b == '!') bb = 5;
	else if (b == '^') bb = 4;
	else if (b == '*' || b == '/' || b == '%') bb = 3;
	else if (b == '+' || b == '-') bb = 2;
	else if (b == '<' || b == '>' || b == '=') bb = 1;
	else if (b == '(') bb = 0;
	else bb = 6;

	bool so = ba >= bb;
	return so;
}

bool isoperator(char x)
{
	if (x == ',' || x == '+' || x == '-' || x == '*' || x == '/' || x == '%' ||
		x == '!' || x == '^' || x == '(' || x == ')' || x == '>' || x == '<' || x == '=')
		return 1;
	return 0;
}

bool KiemTraBieuThucPhuHop(char *T)
{
	// Kiểm tra dấu ngoặc hợp lệ
	node *stack = NULL;
	for (int i = 0; T[i] != 0; i++)
	{
		if (T[i] == '(') push(stack, '(');
		else if (T[i] == ')')
		{
			if (isEmpty(stack)) return 0;
			else pop(stack);
		}
	}
	if (!isEmpty(stack))
	{
		while (!isEmpty(stack))
		{
			pop(stack);
		}
		return 0;
	}

	for (int i = 0; T[i] != 0; i++)
	{
		if ((T[i] >= '0' && T[i] <= '9') || T[i] == '+' || T[i] == '-' ||
			T[i] == '*' || T[i] == '/' || T[i] == '%' || T[i] == '!' || T[i] == '^' ||
			T[i] == '(' || T[i] == ')' || T[i] == '>' || T[i] == '<' || T[i] == '=' ||
			T[i] == 'p' || T[i] == 'i' || T[i] == 'e' ||
			(T[i] == ',' && (i + 1 >= strlen(T) || T[i + 1] != ','))) 1;
		else return 0;

		// kiểm tra biểu thức phù hợp với pi và e
		if (i > 0 && (T[i] == 'e' || T[i] == 'p') && ((T[i - 1] >= '0' && T[i - 1] <= '9') ||
			T[i - 1] == 'e' || T[i - 1] == 'p' || T[i - 1] == 'i' || T[i - 1] == ',' || T[i - 1] == ')')) return 0;
		if (i < strlen(T) - 1 && T[i] == 'p' && T[i + 1] != 'i') return 0;
		if (i < strlen(T) - 1 && (T[i] == 'e' || T[i] == 'i') && (T[i + 1] < '0' || T[i + 1] > '9')) return 0;
		if (i == strlen(T) - 1 && (T[i] == 'e' || T[i] == 'i')) return 0;
		if (T[i] == 'e' || T[i] == 'i')
			for (int j = i + 1; T[j] != 0; j++)
			{
				if (T[j] == '+' || T[j] == '-' ||
					T[j] == '*' || T[j] == '/' || T[j] == '%' || T[j] == '!' || T[j] == '^' ||
					T[j] == ')' || T[j] == '>' || T[j] == '<' || T[j] == '=') break;
				if (T[j] == ',' || T[j] == '(' || T[j] == 'p' || T[j] == 'i' || T[j] == 'e') return 0;
			}

		// kiểm tra biểu thức phù hợp với các phép toán
		if (i < strlen(T) - 1 && ((T[i] == '*' || T[i] == '/' || T[i] == '%' || T[i] == '^' ||
			T[i] == '>' || T[i] == '<' || T[i] == '=' || T[i] == '+' || T[i] == '-' || T[i] == '(')
			&& (T[i + 1] == '*' || T[i + 1] == '/' || T[i + 1] == '%' || T[i + 1] == '!' || T[i + 1] == '^' ||
				T[i + 1] == '>' || T[i + 1] == '<' || T[i + 1] == ')'))) return 0;
		if (i == strlen(T) - 1 && (T[i] == '+' || T[i] == '-' ||
			T[i] == '*' || T[i] == '/' || T[i] == '%' || T[i] == '^' ||
			T[i] == '>' || T[i] == '<' || T[i] == '=')) return 0;
		if (i == 0 &&
			(T[i] == '*' || T[i] == '/' || T[i] == '%' || T[i] == '!' || T[i] == '^' ||
				T[i] == '>' || T[i] == '<' || T[i] == '=')) return 0;
		if (T[i] == '=' && (i > 0 && T[i - 1] == '=') && (i < strlen(T) - 1 && T[i + 1] == '=')) return 0;

		// kiểm tra biểu thức phù hợp với toán hạng
		if ((T[i] >= '0' && T[i] <= '9'))
		{
			int demDauPhay = 0;
			for (int j = i + 1; T[j] != 0; j++)
			{
				if (T[j] == ',') demDauPhay++;
				if (T[j] == '+' || T[j] == '-' ||
					T[j] == '*' || T[j] == '/' || T[j] == '%' || T[j] == '!' || T[j] == '^' ||
					T[j] == ')' || T[j] == '>' || T[j] == '<' || T[j] == '=') break;
				if (T[j] == '(') return 0;
			}
			if (demDauPhay > 1) return 0;
		}
	}
	return 1;
}

char * nhapBieuThucTrungTo()
{
	char *T = NULL;
	getString(T);
	if (KiemTraBieuThucPhuHop(T) == 0)
	{
		cout << "Invalid expression!\n";
		freeString(T);
		return NULL;
	}

	return T;
}

Fnode * taoNode(bigNum x)
{
	Fnode *p = (Fnode *)malloc(sizeof(Fnode) * 1);
	if (p == NULL) malloc_ERROR();

	p->data = x;
	p->next = NULL;
	return p;
}

void push(Fnode *&head, bigNum x)
{
	Fnode *p = taoNode(x);
	p->next = head;
	head = p;
}

bigNum peek(Fnode *head)
{
	Fnode *p = head;
	if (p == NULL)
	{
		bigNum result;
		initBigNum(result);
		dupBigNum(result, zero);

		return result;
	}
	return p->data;
}

bigNum pop(Fnode *&head)
{
	if (head == NULL)
	{
		bigNum result;
		initBigNum(result);
		dupBigNum(result, zero);

		return result;
	}
	bigNum x = head->data;
	Fnode* p = head;
	head = head->next;
	free(p);
	return x;
}

bool isEmpty(Fnode *head)
{
	return head == NULL;
}

char* chuyenBieuThucTrungToThanhBieuThucHauTo(char *T)
{
	char *H = NULL;
	node *stack = NULL;

	int lenT = strlen(T);
	for (int i = 0; i < lenT; i++)
	{
		if (T[i] == '(')
		{
			push(stack, '(');

			
			if (i + 1 < lenT && (T[i + 1] == '+' || T[i + 1] == '-'))
			{
				int demdau = 0; // dau '+' thi +0, dau '-' thi +1
				i++;
				while (i < lenT && (T[i] == '+' || T[i] == '-'))
				{
					demdau += (T[i] == '+') ? 0 : 1;
					i++;
				}

				i--;
				pushString(H, (demdau % 2 == 0) ? '+' : '-');
			}
			

			continue;
		}
		if (T[i] == ')')
		{
			char x = pop(stack);
			while (x != '(')
			{
				pushString(H, x);
				pushString(H, ' ');
				x = pop(stack);
			}
			continue;
		}
		if (T[i] == '+' || T[i] == '-' || T[i] == '*' || T[i] == '/' ||
			T[i] == '%' || T[i] == '!' || T[i] == '^' ||
			T[i] == '>' || T[i] == '<' || T[i] == '=')
		{
			if (T[i] == '=' && i + 1 < lenT && T[i + 1] == '=') i++;

			while (peek(stack) != ' ' && soPhepToan(peek(stack), T[i]))
			{
				pushString(H, pop(stack));
				pushString(H, ' ');
			}
			push(stack, T[i]);

			//
			if (i + 1 < lenT && T[i] != '!' && (T[i + 1] == '+' || T[i + 1] == '-'))
			{
				int demdau = 0; // dau '+' thi +0, dau '-' thi +1
				i++;
				while (i < lenT && (T[i] == '+' || T[i] == '-'))
				{
					demdau += (T[i] == '+') ? 0 : 1;
					i++;
				}

				i--;
				pushString(H, (demdau % 2 == 0) ? '+' : '-');
			}
			//
			continue;
		}

		if ((T[i] >= '0' && T[i] <= '9') || T[i] == ',' || T[i] == 'e' || T[i] == 'p' || T[i] == 'i')
		{
			do
			{
				if (T[i] != 'i')	pushString(H, T[i]);
				i++;
			} while ((T[i] >= '0' && T[i] <= '9') || T[i] == ',' || T[i] == 'e' || T[i] == 'p' || T[i] == 'i');
			pushString(H, ' ');
			i--;
		}
	}

	if (isEmpty(stack) == 0) pushString(H, ' ');
	char temp = pop(stack);
	while (temp != ' ' && temp != '(')
	{
		pushString(H, temp);
		pushString(H, ' ');
		temp = pop(stack);
	}

	xoaDauCachThua(H);

	return H;
}


bigNum thucHienPhepToan(bigNum ToanHang1, char PhepToan, bigNum ToanHang2)
{
	bigNum result;
	initBigNum(result);
	switch (PhepToan)
	{
	case '+':
		plusBigNum(ToanHang1, ToanHang2, result);
		break;
	case '-':
		subBigNum(ToanHang1, ToanHang2, result);
		break;
	case '*':
		mulBigNum(ToanHang1, ToanHang2, result);
		break;
	case '/':
		divBigNum(ToanHang1, ToanHang2, result);
		break;
	case '%':
		modBigNum(ToanHang1, ToanHang2, result);
		break;
	case '^':
		expBigNum(ToanHang1, ToanHang2, result);
		break;
	case '>':
		if (ToanHang1 > ToanHang2)
		{
			dupBigNum(result, one);
		}
		else
		{
			dupBigNum(result, zero);
		}
		break;
	case '<':
		if (ToanHang1 < ToanHang2)
		{
			dupBigNum(result, one);
		}
		else
		{
			dupBigNum(result, zero);
		}
		break;
	case '=':
		if (ToanHang1 == ToanHang2)
		{
			dupBigNum(result, one);
		}
		else
		{
			dupBigNum(result, zero);
		}
		break;
	}
	return result;
}

bigNum thucHienPhepToan(bigNum ToanHang, char PhepToan)
{
	bigNum result;
	initBigNum(result);
	factorialBigNum(ToanHang, result);
	return result;
}

bigNum tinhGiaTriBieuThucHauTo(char *H)
{
	char *temp = NULL;
	Fnode *stack = NULL;


	int lenH = strlen(H);
	for (int i = 0; i < lenH; i++)
	{
		if ((H[i] >= '0' && H[i] <= '9') || H[i] == ',' || H[i] == 'e' || H[i] == 'p' || H[i] == 'i')
		{
			do
			{
				pushString(temp, H[i]);
				i++;
			} while ((H[i] >= '0' && H[i] <= '9') || H[i] == ',' || H[i] == 'e' || H[i] == 'p' || H[i] == 'i');
			i--;

			bigNum a;
			initBigNum(a);
			if (laSoPi(temp))
			{
				a = doiChuoiSangSoPi(temp);
			}
			else if (laSoE(temp))
			{
				a = doiChuoiSangSoE(temp);
			}
			else
			{
				a = doiChuoiSangNum(temp);
			}

			push(stack, a);

			temp = NULL; // Tao lai temp moi

			continue;
		}

		if (H[i] == '+' || H[i] == '-' || H[i] == '*' || H[i] == '/' ||
			H[i] == '%' || H[i] == '!' || H[i] == '^' ||
			H[i] == '<' || H[i] == '>' || H[i] == '=')
		{
			if (H[i + 1] != ' ')//
			{
				char sign = H[i];
				i++;
				do
				{
					pushString(temp, H[i]);
					i++;
				} while ((H[i] >= '0' && H[i] <= '9') || H[i] == ',');
				i--;
				bigNum a;
				initBigNum(a);
				a = doiChuoiSangNum(temp);
				a.sign = (sign == '+') ? POSITIVE : NEGATIVE;
				push(stack, a);

				temp = NULL; // Tao lai temp moi

				continue;
			}
			else//
			{//
				if (H[i] == '!')
				{
					bigNum ToanHang = pop(stack);
					bigNum tempResult = thucHienPhepToan(ToanHang, H[i]);
					push(stack, tempResult);
					freeBigNum(ToanHang);
				}
				else
				{
					bigNum ToanHang1 = pop(stack), ToanHang2 = pop(stack);

					bigNum tempResult = thucHienPhepToan(ToanHang2, H[i], ToanHang1);

					push(stack, tempResult);
					freeBigNum(2, &ToanHang1, &ToanHang2);
				}
			}
		}
	}

	return pop(stack);
}



bigNum tinhBieuThuc(char *T)
{
	char *H = chuyenBieuThucTrungToThanhBieuThucHauTo(T);
	bigNum result = tinhGiaTriBieuThucHauTo(H);

	freeString(H);
	return result;
}

bool laSoPi(char *s)
{
	if (s == NULL) return 0;
	for (int i = 0; s[i] != 0; i++)
		if (s[i] == 'p') return 1;
	return 0;
}

bool laSoE(char *s)
{
	if (s == NULL) return 0;
	for (int i = 0; s[i] != 0; i++)
		if (s[i] == 'e') return 1;
	return 0;
}

bigNum doiChuoiSangSoPi(char *&s)
{
	bigNum n;
	initBigNum(n);
	if (s[0] == '-')
	{
		n.sign = NEGATIVE;
		deleteChar(s);		//Xoa dau cua temp (cho de thao tac tiep)
	}
	else	n.sign = POSITIVE;
	int i, tong = 0;
	for (i = 0; s[i] != ',' && s[i] != '\0'; i++)
	{
		if (s[i] == 'p') continue;
		tong = tong * 10 + s[i] - '0';
	}

	pi(tong, n);
	return n;
}

bigNum doiChuoiSangSoE(char *&s)
{
	bigNum n;
	initBigNum(n);
	if (s[0] == '-')
	{
		n.sign = NEGATIVE;
		deleteChar(s);		//Xoa dau cua temp (cho de thao tac tiep)
	}
	else	n.sign = POSITIVE;
	int i, tong = 0;
	for (i = 0; s[i] != ',' && s[i] != '\0'; i++)
	{
		if (s[i] == 'e') continue;
		tong = tong * 10 + s[i] - '0';
	}

	e(tong, n);
	return n;
}

bigNum doiChuoiSangNum(char *&s)
{
	bigNum n;

	initBigNum(n);
	if (s[0] == '-')
	{
		n.sign = NEGATIVE;
		deleteChar(s);		//Xoa dau cua temp (cho de thao tac tiep)
	}
	else	n.sign = POSITIVE;
	int i;
	for (i = 0; s[i] != ',' && s[i] != '\0'; i++)
	{
		pushString(n.num, s[i]);
	}
	if (s[i] == 0)
		pushString(n.tail, '0');
	else
		for (i = i + 1; s[i] != '\0'; i++)
		{
			pushString(n.tail, s[i]);
		}
	return n;
}

void deleteChar(char *&s)
{
	if (s == NULL) return;
	char *temp = NULL;
	temp = _strdup(s + 1);
	if (temp == NULL)
	{
		malloc_ERROR();
	}
	freeString(s);
	s = temp;
}
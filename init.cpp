#define _CRT_SECURE_NO_WARNINGS
#include "init.h"
#include "warnings.h"
#include <stdarg.h>
#include <string.h>
#include <iostream>
#include <malloc.h>
using namespace std;

void freeString(char *&s)
{
	if (s != NULL)
	{
		free(s);
		s = NULL;
	}
}

void freeString(int num_args, ...)
{
	va_list ap;
	va_start(ap, num_args);

	for (int i = 0; i < num_args; i++)
	{
		char * s = va_arg(ap, char *);
		if (s != NULL)
		{
			free(s);
			s = NULL;
		}
	}
	va_end(ap);
}

void getString(char *&s)
{
	freeString(s);

	char *temp = (char *)malloc(0), x = 1;
	if (temp == NULL)
	{
		freeString(s);
		malloc_ERROR();
		return;
	}
	int len = 0;

	while (x != '\n' || len == 0)
	{
		cin.get(x);
		temp = (char *)realloc(s, len + 1);
		if (temp == NULL)
		{
			freeString(s);
			malloc_ERROR();
		}

		if (x == '\n')
		{
			temp[len] = 0;
		}
		else
		{
			temp[len] = x;
		}

		s = temp;
		len++;
	}
}

void pushString(char *&s, char ch)
{
	int n;
	char *temp;

	if (s != NULL)
	{
		n = strlen(s) + 1;
		temp = (char *)realloc(s, n + 1);

		if (temp == NULL)
		{
			freeString(s);
			malloc_ERROR();
		}
		temp[n - 1] = ch;
		temp[n] = 0;
		s = temp;
	}
	else
	{
		temp = (char *)malloc(2);
		if (temp == NULL) malloc_ERROR();

		temp[0] = ch;
		temp[1] = 0;
		s = temp;
	}	
}

void catString(char *&des, const char* src)
{
	if (src == NULL) return;
	for (int i = 0, len = strlen(src); i < len; i++)
	{
		pushString(des, src[i]);
	}
}

char popString(char *&s)
{
	if (s == NULL || strlen(s) == 0)
	{
		freeString(s);
		popEmptyString_ERROR();
	}

	int len = strlen(s) - 1;
	char ch = s[len], *temp = (char *)realloc(s, len + 1);
	if (temp == NULL)
	{
		freeString(s);
		malloc_ERROR();
	}
	temp[len] = 0;
	s = temp;

	return ch;
}



void initBigNum(bigNum &a)
{
	a.sign = POSITIVE;
	a.num = NULL;
	a.tail = NULL;
}

void initBigNum(int num_args, ...)
{
	va_list ap;
	va_start(ap, num_args);
	for (int i = 0; i < num_args; i++)
	{
		bigNum *a = va_arg(ap, bigNum *);
		
		a->sign = POSITIVE;
		a->num = NULL;
		a->tail = NULL;
	}
	va_end(ap);
}

void freeBigNum(bigNum &a)
{
	a.sign = POSITIVE;
	if (a.num != NULL)
	{
		free(a.num);
		a.num = NULL;
	}
	if (a.tail != NULL)
	{
		free(a.tail);
		a.tail = NULL;
	}
}

void freeBigNum(int num_args, ...)
{
	va_list ap;
	va_start(ap, num_args);
	for (int i = 0; i < num_args; i++)
	{
		bigNum *a = va_arg(ap, bigNum *);

		a->sign = POSITIVE;
		if (a->num != NULL)
		{
			free(a->num);
			a->num = NULL;
		}
		if (a->tail != NULL)
		{
			free(a->tail);
			a->tail = NULL;
		}
	}
	va_end(ap);
}

void dupBigNum(bigNum &a, const bigNum b)
{
	freeBigNum(a);
	
	a.sign = b.sign;
	a.num = (b.num != NULL) ? _strdup(b.num) : NULL;

	if (a.num == NULL && b.num != NULL)
	{
		freeBigNum(a);
		malloc_ERROR();
	}

	a.tail = (b.tail != NULL) ? _strdup(b.tail) : NULL;
	if (a.tail == NULL && b.tail != NULL)
	{
		freeBigNum(a);
		malloc_ERROR();
	}
}

void deleteZeroUnnecessary(bigNum &a)
{
	int i = 0;
	// xoa so 0 o num
	if (a.num != NULL)
	{
		while (a.num[i] == '0')
		{
			i++;
		}
		if (i != 0)
		{
			char *num = _strdup(a.num + i);
			if (num == NULL)
			{
				freeBigNum(a);
				malloc_ERROR();
			}

			free(a.num);
			a.num = NULL;
			a.num = num;
		}
	}
	if (a.num != NULL && strlen(a.num) == 0) freeString(a.num);
	// xoa so 0 o tail
	if (a.tail != NULL)
	{
		i = strlen(a.tail);
		while (a.tail[i - 1] == '0')
		{
			i--;
		}
		if (i != strlen(a.tail))
		{
			char *num = (char*)realloc(a.tail, (i + 1));
			if (num == NULL)
			{
				freeBigNum(a);
				malloc_ERROR();
			}

			num[i] = 0;
			a.tail = num;
		}
	}
	if (a.tail != NULL && strlen(a.tail) == 0) freeString(a.tail);
}

void deleteZeroUnnecessary(int num_args, ...)
{
	va_list ap;
	va_start(ap, num_args);
	for (int j = 0; j < num_args; j++)
	{
		bigNum *a = va_arg(ap, bigNum *);

		int i = 0;
		// xoa so 0 o num
		if (a->num != NULL)
		{
			while (a->num[i] == '0')
			{
				i++;
			}
			if (i != 0)
			{
				char *num = _strdup(a->num + i);
				if (num == NULL)
				{
					freeBigNum(*a);
					malloc_ERROR();
				}

				free(a->num);
				a->num = NULL;

				a->num = num;
			}
		}
		if (a->num != NULL && strlen(a->num) == 0) freeString(a->num);
		// xoa so 0 o tail
		if (a->tail != NULL)
		{
			i = strlen(a->tail);
			while (a->tail[i - 1] == '0')
			{
				i--;
			}
			if (i != strlen(a->tail))
			{
				char *num = (char*)realloc(a->tail, (i + 1));
				if (num == NULL)
				{
					freeBigNum(*a);
					malloc_ERROR();
				}

				num[i] = 0;
				a->tail = num;
			}
		}
		if (a->tail != NULL && strlen(a->tail) == 0) freeString(a->tail);
	}
	va_end(ap);
}

void adjustAandB(bigNum &a, bigNum &b)
{
	char *temp = NULL;
	int lena_num = (a.num == NULL) ? 0 : strlen(a.num),
		lenb_num = (b.num == NULL) ? 0 : strlen(b.num),
		lena_tail = (a.tail == NULL) ? 0 : strlen(a.tail),
		lenb_tail = (b.tail == NULL) ? 0 : strlen(b.tail);

	int len_num = (lena_num > lenb_num) ? lena_num : lenb_num,
		len_tail = (lena_tail > lenb_tail) ? lena_tail : lenb_tail;
	if (lena_num < len_num)
	{
		for (int i = 0; i < len_num - lena_num; i++)
		{
			pushString(temp, '0');
		}

		if (a.num != NULL) catString(temp, a.num);

		freeString(a.num);
		a.num = temp;
		temp = NULL;
	}

	if (lenb_num < len_num)
	{
		for (int i = 0; i < len_num - lenb_num; i++)
		{
			pushString(temp, '0');
		}
		if(b.num != NULL)	catString(temp, b.num);

		freeString(b.num);
		b.num = temp;
		temp = NULL;
	}

	if (lena_tail < len_tail)
	{
		for (int i = 0; i < len_tail - lena_tail; i++)
		{
			pushString(a.tail, '0');
		}
	}

	if (lenb_tail < len_tail)
	{
		for (int i = 0; i < len_tail - lenb_tail; i++)
		{
			pushString(b.tail, '0');
		}
	}
}



void divideByExpTen(bigNum &a, int num)
{
	int sizeold = (a.tail == NULL) ? 0 : strlen(a.tail),
		sizenum = (a.num == NULL) ? 0 : strlen(a.num);
	int sizeTail = num;

	char *temp, *oldTail = (a.tail != NULL) ? _strdup(a.tail) : NULL;
	if (oldTail == NULL && a.tail != NULL)
	{
		freeBigNum(a);
		malloc_ERROR();
	}

	if (a.tail == NULL)
	{
		temp = (char *)calloc(sizeTail + 1, sizeof(char));
	}
	else temp = (char *)realloc(a.tail, sizeTail + 1);
	if (temp == NULL) malloc_ERROR();
	a.tail = temp;

	for (int i = num - 1; i >= 0; i--)
	{
		if (i < sizeTail)
		{
			if (sizenum - 1 - (num - 1 - i) >= 0)
				a.tail[i] = a.num[sizenum - 1 - (num - 1 - i)];
			else a.tail[i] = '0';
		}
	}
	a.tail[num] = 0;

	if (oldTail != NULL)
	{
		catString(a.tail, oldTail);
		freeString(oldTail);
	}

	if (a.num == NULL)
	{
		temp = (char *)malloc(1);
		temp[0] = 0;
	}
	else temp = (char *)realloc(a.num, sizenum - num + 1);

	if (temp == NULL)
	{
		temp = (char *)malloc(1);
		if (temp == NULL) malloc_ERROR();
		temp[0] = 0;
	}
	if(sizenum - num >= 0) //
		temp[sizenum - num] = 0;
	a.num = temp;
}

void outputBigNum(bigNum a)//
{
	cout << endl;
	if (a.sign == NEGATIVE) cout << "-";
	if (a.num == NULL || strlen(a.num) == 0) cout << "0";
	else cout << a.num;
	if (a.tail == NULL || strlen(a.tail) == 0);
	else cout << ',' << a.tail;
	cout << endl;
}

int convertBigNumToInt(const bigNum a)
{
	int aint = 0;
	if (a.num == NULL) return aint;

	for (int i = 0, lena = strlen(a.num); i < lena; i++)
		aint = aint * 10 + a.num[i] - '0';
	return aint;
}

char* convertBigNumToString(bigNum a) //
{
	char *s = NULL;
	if (a.sign == NEGATIVE) pushString(s, '-');
	if (a.num == NULL || strlen(a.num) == 0) pushString(s, '0');
	else catString(s, a.num);
	if (a.tail == NULL || strlen(a.tail) == 0);
	else
	{
		pushString(s, ',');
		catString(s, a.tail);
	}
	return s;
}
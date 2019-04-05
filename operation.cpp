#define _CRT_SECURE_NO_WARNINGS
#include "init.h"
#include "compare.h"
#include "warnings.h"
#include "operation.h"
#include <malloc.h>
#include <string.h>

using namespace std;

void plusBigNum (bigNum a, bigNum b, bigNum &result)
{
	if (a.num != 0 && a.num[0] == 'W')
	{
		dupBigNum(result, a);
		return;
	}
	if (b.num != 0 && b.num[0] == 'W')
	{
		dupBigNum(result, b);
		return;
	}

	if (a.sign == NEGATIVE && b.sign == NEGATIVE) // a < 0 && b < 0
	{
		a.sign = b.sign = POSITIVE;
		plusBigNum(a, b, result);
		result.sign = NEGATIVE;
		return;
	}

	if (a.sign == POSITIVE && b.sign == POSITIVE) // a >=0 && b >= 0
	{
		bigNum atemp, btemp;
		initBigNum(2, &atemp, &btemp);
		dupBigNum(atemp, a);
		dupBigNum(btemp, b);
		deleteZeroUnnecessary(2, &atemp, &btemp);

		adjustAandB(atemp, btemp);

		char *inta = NULL, *intb = NULL, *intResult = NULL;
		// Dua hai so thuc ve hai so nguyen va thuc hien phep toan
		// sau do dich dau phay lai ban dau

		// dua so a ve so nguyen
		if (atemp.num != NULL)
		{
			inta = _strdup(atemp.num);
			if (inta == NULL)
			{
				freeBigNum(2, &atemp, &btemp);
				malloc_ERROR();
			}
		}

		if (atemp.tail != NULL)
		{
			if (inta == NULL)
			{

				inta = _strdup(atemp.tail);
				if (inta == NULL)
				{
					freeBigNum(2, &atemp, &btemp);
					malloc_ERROR();
				}
			}
			else
			{
				catString(inta, atemp.tail);
				if (inta == NULL)
				{
					freeBigNum(2, &atemp, &btemp);
					malloc_ERROR();
				}
			}
		}
		// dua so b ve so nguyen
		if (btemp.num != NULL)
		{
			intb = _strdup(btemp.num);
			if (intb == NULL)
			{
				freeBigNum(2, &atemp, &btemp);
				freeString(inta);
				malloc_ERROR();
			}
		}

		if (btemp.tail != NULL)
		{
			if (intb == NULL)
			{

				intb = _strdup(btemp.tail);
				if (intb == NULL)
				{
					freeBigNum(2, &atemp, &btemp);
					freeString(intb);
					malloc_ERROR();
				}
			}
			else
			{
				catString(intb, btemp.tail);
				if (intb == NULL)
				{
					freeBigNum(2, &atemp, &btemp);
					freeString(intb);
					malloc_ERROR();
				}
			}
		}

		// Truong hop 2 chuoi NULL
		if (inta == NULL || intb == NULL)
		{
			freeBigNum(2, &atemp, &btemp);
			dupBigNum(result, zero);
			return;
		}

		// Thuc hien phep cong
		int temp = 0;
		for (int i = strlen(inta) - 1; i >= 0; i--)
		{
			temp += inta[i] - '0' + intb[i] - '0';
			pushString(intResult, temp % 10 + '0');
			temp /= 10;
		}
		while (temp > 0)
		{
			pushString(intResult, temp % 10 + '0');
			temp /= 10;
		}
		_strrev(intResult);

		// Dua intResult thanh bigNum result
		result.num = intResult;
		if (atemp.tail != NULL) divideByExpTen(result, strlen(atemp.tail));

		freeBigNum(2, &atemp, &btemp);
		freeString(inta);
		freeString(intb);
		deleteZeroUnnecessary(result);
		return;
	}

	if (a.sign == NEGATIVE && b.sign == POSITIVE) // a < 0 && b >= 0
	{
		a.sign = POSITIVE;
		b.sign = NEGATIVE;
		plusBigNum(a, b, result);
		result.sign = !result.sign;
		return;
	}

	if (a.sign == POSITIVE && b.sign == NEGATIVE) // a >= 0 && b < 0
	{
		b.sign = POSITIVE;
		if (a > b || a == b) // |a| >= |b|
		{
			bigNum atemp, btemp;
			initBigNum(2, &atemp, &btemp);
			dupBigNum(atemp, a);
			dupBigNum(btemp, b);
			deleteZeroUnnecessary(2, &atemp, &btemp);

			adjustAandB(atemp, btemp);

			char *inta = NULL, *intb = NULL, *intResult = NULL;
			// Dua hai so thuc ve hai so nguyen va thuc hien phep toan
			// sau do dich dau phay lai ban dau

			// dua so a ve so nguyen
			if (atemp.num != NULL)
			{
				inta = _strdup(atemp.num);
				if (inta == NULL)
				{
					freeBigNum(2, &atemp, &btemp);
					malloc_ERROR();
				}
			}

			if (atemp.tail != NULL)
			{
				if (inta == NULL)
				{

					inta = _strdup(atemp.tail);
					if (inta == NULL)
					{
						freeBigNum(2, &atemp, &btemp);
						malloc_ERROR();
					}
				}
				else
				{
					catString(inta, atemp.tail);
					if (inta == NULL)
					{
						freeBigNum(2, &atemp, &btemp);
						malloc_ERROR();
					}
				}
			}
			// dua so b ve so nguyen
			if (btemp.num != NULL)
			{
				intb = _strdup(btemp.num);
				if (intb == NULL)
				{
					freeBigNum(2, &atemp, &btemp);
					freeString(inta);
					malloc_ERROR();
				}
			}

			if (btemp.tail != NULL)
			{
				if (intb == NULL)
				{

					intb = _strdup(btemp.tail);
					if (intb == NULL)
					{
						freeBigNum(2, &atemp, &btemp);
						freeString(intb);
						malloc_ERROR();
					}
				}
				else
				{
					catString(intb, btemp.tail);
					if (intb == NULL)
					{
						freeBigNum(2, &atemp, &btemp);
						freeString(intb);
						malloc_ERROR();
					}
				}
			}

			// Truong hop 2 chuoi NULL
			if (inta == NULL || intb == NULL)
			{
				freeBigNum(2, &atemp, &btemp);
				dupBigNum(result, zero);
				return;
			}

			// Thuc hien phep cong
			int temp = 0;
			for (int i = strlen(inta) - 1; i >= 0; i--)
			{
				temp += inta[i] - '0' - (intb[i] - '0');
				if (temp >= 0)
				{
					pushString(intResult, temp % 10 + '0');
					temp /= 10;
				}
				else
				{
					temp += 10;
					pushString(intResult, temp % 10 + '0');
					temp /= 10;
					temp -= 1;
				}
			}
			while (temp != 0)
			{
				if (temp >= 0)
				{
					pushString(intResult, temp % 10 + '0');
					temp /= 10;
				}
				else
				{
					temp += 10;
					pushString(intResult, temp % 10 + '0');
					temp /= 10;
					result.sign = NEGATIVE;
				}
			}

			_strrev(intResult);

			// Dua intResult thanh bigNum result
			result.num = intResult;
			if (atemp.tail != NULL) divideByExpTen(result, strlen(atemp.tail));

			freeBigNum(2, &atemp, &btemp);
			freeString(inta);
			freeString(intb);
			deleteZeroUnnecessary(result);
			return;
		}
		else // |a| < |b|
		{
			a.sign = NEGATIVE;
			plusBigNum(b, a, result);
			result.sign = NEGATIVE;
			return;
		}
	}
}

void subBigNum(bigNum a, bigNum b, bigNum &result)
{
	if (a.num != 0 && a.num[0] == 'W')
	{
		dupBigNum(result, a);
		return;
	}
	if (b.num != 0 && b.num[0] == 'W')
	{
		dupBigNum(result, b);
		return;
	}

	if (a.sign == NEGATIVE && b.sign == NEGATIVE)
	{
		b.sign = POSITIVE;
		plusBigNum(a, b, result);
		return;
	}

	if (a.sign == POSITIVE && b.sign == POSITIVE)
	{
		b.sign = NEGATIVE;
		plusBigNum(a, b, result);
		return;
	}

	if (a.sign == NEGATIVE && b.sign == POSITIVE)
	{
		b.sign = NEGATIVE;
		plusBigNum(a, b, result);
		return;
	}

	if (a.sign == POSITIVE && b.sign == NEGATIVE)
	{
		b.sign = POSITIVE;
		plusBigNum(a, b, result);
		return;
	}
}

void TempMulFunc(bigNum &a, bigNum &b, bigNum &result)
{
	dupBigNum(result, zero);
	int l, exp = 0;
	bigNum temp;
	initBigNum(temp);
	dupBigNum(temp, zero);

	while (!(b == zero))
	{
		l = popString(b.num) - '0';
		for (int i = 0; i < l; i++)
		{
			plusBySelf(temp, a);
		}
		for (int i = 0; i < exp; i++)
		{
			pushString(temp.num, '0');
		}
		exp++;

		plusBySelf(result, temp);
		freeBigNum(temp);
	}
}

void mulBigNum(bigNum a, bigNum b, bigNum &result)
{
	if (a.num != 0 && a.num[0] == 'W')
	{
		dupBigNum(result, a);
		return;
	}
	if (b.num != 0 && b.num[0] == 'W')
	{
		dupBigNum(result, b);
		return;
	}

	bigNum atemp, btemp;
	initBigNum(2, &atemp, &btemp);
	dupBigNum(atemp, a);
	dupBigNum(btemp, b);
	deleteZeroUnnecessary(2, &atemp, &btemp);

	int lentail = (atemp.tail != NULL) ? strlen(atemp.tail) : 0;
	lentail += (btemp.tail != NULL) ? strlen(btemp.tail) : 0;
	atemp.sign = btemp.sign = POSITIVE;
	catString(atemp.num, atemp.tail);
	catString(btemp.num, btemp.tail);
	freeString(atemp.tail);
	freeString(btemp.tail);
	if (atemp.num == NULL || btemp.num == NULL)
	{
		freeBigNum(2, &atemp, &btemp);
		dupBigNum(result, zero);
		return;
	}

	TempMulFunc(atemp, btemp, result);
	if (a.sign != b.sign) result.sign = NEGATIVE;
	freeBigNum(2, &atemp, &btemp);

	divideByExpTen(result, lentail);
	deleteZeroUnnecessary(result);
}

void TempDivFunc (bigNum a, bigNum b, bigNum &result)
{
	bigNum tempCong;
	initBigNum(tempCong);

	if (b == zero)
	{
		result.num = div_mod_by_0_ERROR(); // Báo lỗi chia cho số 0
		return;
	}

	result.sign = a.sign + b.sign - 2 * a.sign*b.sign; // Xác định dấu cho kết quả
	a.sign = b.sign = tempCong.sign = 0; // Cho dấu a, b thành dương để dễ tính

	int lena_num = (a.num == NULL) ? 0 : strlen(a.num);
	for (int i = 0; i < lena_num; i++)
	{
		pushString(tempCong.num, a.num[i]);
		if (tempCong > b || tempCong == b)
		{
			bigNum temp;

			for (int i = 1; i <= 10; i++)
			{
				initBigNum(temp);

				subBigNum(tempCong, b, temp);
				freeBigNum(tempCong);
				tempCong = temp;

				if (temp < zero)
				{
					initBigNum(temp);
					plusBigNum(tempCong, b, temp);
					freeBigNum(tempCong);
					tempCong = temp;
					if (tempCong.sign == NEGATIVE) tempCong.sign = POSITIVE; //

					deleteZeroUnnecessary(tempCong);

					pushString(result.num, '0' + i - 1);

					break;
				}
			}
		}
		else pushString(result.num, '0');
	}
	freeBigNum(tempCong);
	deleteZeroUnnecessary(result);
}

void divBigNum (bigNum a, bigNum b, bigNum &result)
{
	if (a.num != 0 && a.num[0] == 'W')
	{
		dupBigNum(result, a);
		return;
	}
	if (b.num != 0 && b.num[0] == 'W')
	{
		dupBigNum(result, b);
		return;
	}

	if (b == zero)
	{
		result.num = div_mod_by_0_ERROR(); // Báo lỗi chia cho số 0
		return;
	}

	if (a == zero)
	{
		dupBigNum(result, zero);
		return;
	}

	bigNum atemp, btemp;
	initBigNum(2, &atemp, &btemp);
	atemp.sign = a.sign;
	btemp.sign = b.sign;

	char *numa, *numb, *duoi;
	int numdich = MAXTAIL;
	numdich += (a.tail == NULL) ? 0 : strlen(a.tail);
	numdich += (b.num == NULL) ? 0 : strlen(b.num);
	a.sign = b.sign = POSITIVE; // tạm giả sử 2 số có dấu dương để so sánh phần nguyên

	int size = (a.num == NULL) ? 0 : strlen(a.num);
	size += (b.tail == NULL) ? 0 : strlen(b.tail);
	size += numdich;

	numa = (char *)malloc(size + 1);

	size = (b.num == NULL) ? 0 : strlen(b.num);
	size += (b.tail == NULL) ? 0 : strlen(b.tail);

	numb = (char *)malloc(size + 1);

	duoi = (char *)calloc(size + MAXTAIL + 1, 1);
	if (numa == NULL || numb == NULL || duoi == NULL)
	{
		freeString(3, &numa, &numb, &duoi);
		malloc_ERROR();
	}
	int lenduoi = size + MAXTAIL;
	for (int i = 0; i < lenduoi; i++)
	{
		duoi[i] = '0';
	}

	numa[0] = numb[0] = 0;

	catString(numa, a.num);
	catString(numa, a.tail);
	catString(numa, duoi); // thêm số 0 vào numa để thực hiện phép chia số thực
	catString(numb, b.num);
	catString(numb, b.tail);


	atemp.num = numa;
	btemp.num = numb;

	bigNum tempresult;
	initBigNum(tempresult);
	TempDivFunc(atemp, btemp, tempresult);

	result.sign = tempresult.sign;
	result.num = tempresult.num;
	divideByExpTen(result, numdich);
	deleteZeroUnnecessary(result);

	freeBigNum(2, &atemp, &btemp);
	freeString(duoi);

	lamTronSo(result, MAXTAIL);
}

void TempModFunc(bigNum a, bigNum b, bigNum &result)
{
	bigNum div;
	initBigNum(div);
	TempDivFunc(a, b, div);
	if (div.num == NULL || div.num[0] == 0)
	{
		pushString(div.num, '0');
	}

	bigNum temp;
	initBigNum(temp);

	mulBigNum(div, b, temp);
	subBigNum(a, temp, result);
	freeBigNum(2, &temp, &div);

	if (result < zero)
	{
		b.sign = 0;
		plusBigNum(result, b, temp);
		freeBigNum(result);
		result = temp;
	}

	deleteZeroUnnecessary(result);
}

void modBigNum (bigNum a, bigNum b, bigNum &result)
{
	if (a.num != 0 && a.num[0] == 'W')
	{
		dupBigNum(result, a);
		return;
	}
	if (b.num != 0 && b.num[0] == 'W')
	{
		dupBigNum(result, b);
		return;
	}

	bigNum tempa, tempb;
	initBigNum(2, &tempa, &tempb);
	tempa = { 0, a.tail }, tempb = { 0, b.tail };
	if (!(tempa == zero) || !(tempb == zero))
	{
		result.num = mod_by_float_ERROR();
		return;
	}

	tempa = { a.sign, a.num }, tempb = { b.sign, b.num };

	bigNum resulttemp;
	initBigNum(resulttemp);
	TempModFunc(tempa, tempb, resulttemp);
	result = resulttemp;
}

void TempExpFunc(bigNum a, bigNum b, bigNum &result)
{
	if (b == zero)
	{
		dupBigNum(result, one);
		return;
	}

	bigNum temp;
	initBigNum(temp);
	modBigNum(b, two, temp);

	if (temp == zero) // Trường hợp b = 2n -> (a^2)^(b/2)
	{
		bigNum square, half;
		initBigNum(2, &square, &half);
		mulBigNum(a, a, square);
		divBigNum(b, two, half);
		lamTronSo(square, 2 * MAXTAIL);

		TempExpFunc(square, half, result);

		freeBigNum(2, &square, &half);
	}
	else // Trường hợp b = 2n + 1 -> a * a^(b-1)
	{
		bigNum bprev, t_exp;
		initBigNum(2, &bprev, &t_exp);
		subBigNum(b, one, bprev);

		TempExpFunc(a, bprev, t_exp);
		mulBigNum(t_exp, a, result);

		freeBigNum(2, &bprev, &t_exp);
	}

	freeBigNum(temp);
}

void expBigNum(bigNum a, bigNum b, bigNum &result)
{
	if (a.num != 0 && a.num[0] == 'W')
	{
		dupBigNum(result, a);
		return;
	}
	if (b.num != 0 && b.num[0] == 'W')
	{
		dupBigNum(result, b);
		return;
	}
	if (b.tail != NULL && strlen(b.tail) != 0 && strcmp(b.tail, (char *) "0") != 0)
	{
		result.num = real_exp_ERROR();
		return;
	}

	if (b < zero)
	{
		bigNum tempResult;
		initBigNum(tempResult);
		b.sign = POSITIVE;
		TempExpFunc(a, b, tempResult);
		divBigNum(one, tempResult, result);
		freeBigNum(tempResult);
	}
	else
	{
		TempExpFunc(a, b, result);
	}
}

void TempFactorialFunc(bigNum &a, bigNum &result)
{
	dupBigNum(result, one);

	for (;; decreaseByOne(a))
	{
		if (a == zero)
		{
			break;
		}
		else
		{
			mulBySelf(result, a);
		}
	}
}

void factorialBigNum(bigNum a, bigNum &result)
{
	if (a.num != 0 && a.num[0] == 'W')
	{
		dupBigNum(result, a);
		return;
	}

	if (a < zero) // Báo lỗi giai thừa số âm
	{
		result.num = factorial_negative_ERROR();
		return;
	}

	// Báo lỗi giai thừa số không nguyên
	bigNum atemp;
	initBigNum(atemp);
	dupBigNum(atemp, a);
	deleteZeroUnnecessary(atemp);
	if (atemp.tail != NULL)
	{
		freeBigNum(atemp);
		result.num = factorial_float_ERROR();
		return;
	}

	TempFactorialFunc(atemp, result);

	freeBigNum(atemp);
}

void pi(int k, bigNum &result)
{
	bigNum temp, temp2, temp3, temp4, num4096, i;
	initBigNum(7, &result, &temp, &temp2, &temp3, &temp4, &num4096, &i);
	dupBigNum(temp, zero);
	dupBigNum(result, zero);
	dupBigNum(num4096, one);

	for (; convertBigNumToInt(i) < MAX_PI; plusBySelf(i, one))
	{
		{
			mulBigNum(eight, i, temp2);
			plusBySelf(temp2, three);
			divBigNum(one, eight, temp3);
			divBigNum(temp3, temp2, temp4);
			plusBySelf(temp, temp4);
			freeBigNum(3, &temp2, &temp3, &temp4);

			mulBigNum(eight, i, temp2);
			plusBySelf(temp2, two);
			divBigNum(one, six, temp3);
			divBigNum(temp3, temp2, temp4);
			plusBySelf(temp, temp4);
			freeBigNum(3, &temp2, &temp3, &temp4);

			mulBigNum(eight, i, temp2);
			plusBySelf(temp2, one);
			divBigNum(one, temp2, temp4);
			plusBySelf(temp, temp4);
			freeBigNum(3, &temp2, &temp3, &temp4);

			mulBigNum(twelve, i, temp2);
			plusBySelf(temp2, five);
			divBigNum(one, eight, temp3);
			divBigNum(temp3, temp2, temp4);
			plusBySelf(temp, temp4);
			freeBigNum(3, &temp2, &temp3, &temp4);

			mulBigNum(twelve, i, temp2);
			plusBySelf(temp2, one);
			divBigNum(two, temp2, temp4);
			plusBySelf(temp, temp4);
			freeBigNum(3, &temp2, &temp3, &temp4);

			mulBigNum(eight, i, temp2);
			plusBySelf(temp2, seven);
			divBigNum(one, fiveandtwelve, temp3);
			divBigNum(temp3, temp2, temp4);
			temp4.sign = 1;
			plusBySelf(temp, temp4);
			freeBigNum(3, &temp2, &temp3, &temp4);

			mulBigNum(eight, i, temp2);
			plusBySelf(temp2, six);
			divBigNum(one, threeandeightyfour, temp3);
			divBigNum(temp3, temp2, temp4);
			temp4.sign = 1;
			plusBySelf(temp, temp4);
			freeBigNum(3, &temp2, &temp3, &temp4);

			mulBigNum(eight, i, temp2);
			plusBySelf(temp2, five);
			divBigNum(one, sixtyfour, temp3);
			divBigNum(temp3, temp2, temp4);
			temp4.sign = 1;
			plusBySelf(temp, temp4);
			freeBigNum(3, &temp2, &temp3, &temp4);

			mulBigNum(twelve, i, temp2);
			plusBySelf(temp2, eleven);
			divBigNum(one, fiveandtwelve, temp3);
			divBigNum(temp3, temp2, temp4);
			temp4.sign = 1;
			plusBySelf(temp, temp4);
			freeBigNum(3, &temp2, &temp3, &temp4);

			mulBigNum(twelve, i, temp2);
			plusBySelf(temp2, seven);
			divBigNum(one, thirtytwo, temp3);
			divBigNum(temp3, temp2, temp4);
			temp4.sign = 1;
			plusBySelf(temp, temp4);
			freeBigNum(3, &temp2, &temp3, &temp4);
		}

		mulBySelf(temp, num4096);
		divBySelf(num4096, fourtyandninetysix);

		plusBySelf(result, temp);
		freeBigNum(temp);
		dupBigNum(temp, zero);
	}

	freeBigNum(3, &num4096, &i, &temp);

	lamTronSo(result, k);
	//result.tail = (char *)realloc(result.tail, k + 1);
	//result.tail[k] = 0;
}

void e(int k, bigNum &result)
{
	bigNum nfactorial, divideByFactorial, temp;
	initBigNum(3, &nfactorial, &divideByFactorial, &temp);
	dupBigNum(nfactorial, one);
	dupBigNum(divideByFactorial, one);
	dupBigNum(result, one);
	for (; convertBigNumToInt(nfactorial) < MAX_E; plusBySelf(nfactorial, one), divBySelf(divideByFactorial, nfactorial))
	{
		plusBySelf(result, divideByFactorial);
	}

	freeBigNum(2, &nfactorial, &divideByFactorial);


	lamTronSo(result, k);
	//result.tail = (char *)realloc(result.tail, k + 1);
	//result.tail[k] = 0;
}

void decreaseByOne(bigNum &a)
{
	bigNum temp;
	initBigNum(temp);
	
	subBigNum(a, one, temp);
	freeBigNum(a);

	a = temp;
}

void decreaseByTwo(bigNum &a)
{
	bigNum temp;
	initBigNum(temp);

	subBigNum(a, two, temp);
	freeBigNum(a);

	a = temp;
}

void increaseByTwo(bigNum &a)
{
	bigNum temp;
	initBigNum(temp);

	plusBigNum(a, two, temp);
	freeBigNum(a);

	a = temp;
}

void plusBySelf(bigNum &result, const bigNum a)
{
	bigNum temp;
	initBigNum(temp);

	plusBigNum(result, a, temp);
	freeBigNum(result);

	result = temp;
}

void mulBySelf(bigNum &result, const bigNum a)
{
	bigNum temp;
	initBigNum(temp);

	mulBigNum(result, a, temp);
	freeBigNum(result);

	result = temp;
}

void divBySelf(bigNum &result, const bigNum a)
{
	bigNum temp;
	initBigNum(temp);

	divBigNum(result, a, temp);
	freeBigNum(result);

	result = temp;
}

void lamTronSo(bigNum &a, int k)
{
	if (k <= 0)
	{
		if (a.tail[0] >= '5')
		{
			for (int i = (a.num == NULL) ? 0 : strlen(a.num) - 1; i >= 0; i--)
			{
				if (a.num[i] == '9')
				{
					a.num[i] = '0';

					if (i == 0)
					{
						char *num = _strdup("1");
						catString(num, a.num);
						freeString(a.num);
						a.num = num;
					}
				}
				else
				{
					a.num[i]++;
					break;
				}
			}
		}

		freeString(a.tail);
	}
	else
	{
		if (k >= ((a.tail == NULL) ? 0 : strlen(a.tail)))
		{
			return;
		}

		if (a.tail[k] >= '5')
		{
			for (int i = k - 1; i >= 0; i--)
			{
				if (a.tail[i] == '9')
				{
					if (i == 0) freeString(a.tail);
					else
					{
						a.tail = (char *)realloc(a.tail, i + 1);
						if (a.tail == NULL) malloc_ERROR();
						a.tail[i] = 0;
					}

					if (i == 0)
					{
						for (int j = (a.num == NULL) ? 0 : strlen(a.num) - 1; j >= 0; j--)
						{
							if (a.num[j] == '9')
							{
								a.num[j] = '0';

								if (j == 0)
								{
									char *num = _strdup("1");
									catString(num, a.num);
									freeString(a.num);
									a.num = num;
								}
							}
							else
							{
								a.num[j]++;

								break;
							}
						}

						freeString(a.tail);
					}
				}
				else
				{
					a.tail[i]++;

					a.tail = (char *)realloc(a.tail, i + 2);
					if (i + 2 > 0 && a.tail == NULL) malloc_ERROR();
					a.tail[i + 1] = 0;

					break;
				}
			}
		}
		else
		{
			a.tail = (char *)realloc(a.tail, k + 1);
			if (k + 1 > 0 && a.tail == NULL) malloc_ERROR();
			a.tail[k] = 0;
		}
	}
}
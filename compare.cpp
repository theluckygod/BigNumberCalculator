#include "compare.h"
#include "init.h"
#include <string.h>
#include "warnings.h"

bool operator ==(bigNum a, bigNum b)
{
	bigNum atemp, btemp;
	initBigNum(2, &atemp, &btemp);
	dupBigNum(atemp, a);
	dupBigNum(btemp, b);

	deleteZeroUnnecessary(2, &atemp, &btemp);
	
	if (atemp.num == NULL && atemp.tail == NULL
		&& btemp.num == NULL && btemp.tail == NULL) return 1; // 0 == 0

	if (atemp.sign != btemp.sign)
	{
		freeBigNum(2, &atemp, &btemp);
		return 0;
	}

	if (((atemp.num == NULL && btemp.num == NULL) ||
		(atemp.num != NULL && btemp.num != NULL && strcmp(atemp.num, btemp.num) == 0))
		&& ((atemp.tail == NULL && btemp.tail == NULL) ||
		(atemp.tail != NULL && btemp.tail != NULL && strcmp(atemp.tail, btemp.tail) == 0)))
	{
		freeBigNum(2, &atemp, &btemp);
		return 1;
	}
	else 
	{
		freeBigNum(2, &atemp, &btemp);
		return 0;
	}
}

bool operator >(bigNum a, bigNum b)
{
	bigNum atemp, btemp;
	initBigNum(2, &atemp, &btemp);

	if (a == zero)
	{
		dupBigNum(atemp, zero);
	}
	else
	{
		dupBigNum(atemp, a);
	}


	if (b == zero)
	{
		dupBigNum(btemp, zero);
	}
	else
	{
		dupBigNum(btemp, b);
	}

	deleteZeroUnnecessary(2, &atemp, &btemp);

	if (atemp == btemp) // a == b
	{
		freeBigNum(2, &atemp, &btemp);
		return 0;
	}
	if (atemp.sign < btemp.sign) // a >= 0 and b < 0
	{
		freeBigNum(2, &atemp, &btemp);
		return 1;
	}
	if (atemp.sign > btemp.sign) // a < 0 and b >= 0
	{
		freeBigNum(2, &atemp, &btemp);
		return 0;
	}

	// a < 0 and b < 0
	if (atemp.sign == NEGATIVE)
	{
		bool result;
		atemp.sign = btemp.sign = POSITIVE;
		result = !(atemp > btemp);
		freeBigNum(2, &atemp, &btemp);
		return result;
	}

	int lena_num = (atemp.num == NULL) ? 0 : strlen(atemp.num),
		lenb_num = (btemp.num == NULL) ? 0 : strlen(btemp.num),
		lena_tail = (atemp.tail == NULL) ? 0 : strlen(atemp.tail),
		lenb_tail = (btemp.tail == NULL) ? 0 : strlen(btemp.tail);

	// a >= 0 and b >= 0
	if (atemp.sign == POSITIVE)
	{
		// so sanh phan truoc dau phay
		if (lena_num > lenb_num)
		{
			freeBigNum(2, &atemp, &btemp);
			return 1;
		}
		if (lena_num < lenb_num)
		{
			freeBigNum(2, &atemp, &btemp);
			return 0;
		}

		for (int i = 0; i < lena_num; i++)
		{
			if (atemp.num[i] > btemp.num[i])
			{
				freeBigNum(2, &atemp, &btemp);
				return 1;
			}
			if (atemp.num[i] < btemp.num[i])
			{
				freeBigNum(2, &atemp, &btemp);
				return 0;
			}
		}

		// so sanh phan sau dau phay
		if (atemp.tail == NULL) 
		{
			freeBigNum(2, &atemp, &btemp);
			return 0;
		}
		if (atemp.tail != NULL && btemp.tail == NULL) 
		{
			freeBigNum(2, &atemp, &btemp);
			return 1;
		}

		for (int i = 0, len = ((lena_tail > lenb_tail) ? lena_tail : lenb_tail)
			; i < len; i++)
		{
			if (atemp.tail[i] > btemp.tail[i])
			{
				freeBigNum(2, &atemp, &btemp);
				return 1;
			}
			if (atemp.tail[i] < btemp.tail[i])
			{
				freeBigNum(2, &atemp, &btemp);
				return 0;
			}
		}
	}

	freeBigNum(2, &atemp, &btemp);
	return 0;
}

bool operator <(bigNum a, bigNum b)
{
	return !(a > b || a == b);
}
#include "warnings.h"
#include <iostream>

void popEmptyString_ERROR()
{
	/*xuatKetQua((char *) "WARNINGS! Allocation errors", 0);
	xuatKetQua("", 1);*/
	std::cout << "WARNINGS! pop a empty string";//
	system("pause");
	exit(0);
}

void malloc_ERROR()
{
	/*xuatKetQua((char *) "WARNINGS! Allocation errors", 0);
	xuatKetQua("", 1);*/
	std::cout << "WARNINGS! Allocation errors";//
	system("pause");
	exit(0);
}

char * div_mod_by_0_ERROR()
{
	char *re = NULL;
	re = _strdup((char *) "WARNINGS! Div or mod by zero");
	return re;
}

char * factorial_float_ERROR()
{
	char *re = NULL;
	re = _strdup((char *) "WARNINGS! factorial input is a float number");
	return re;
}

char * mod_by_float_ERROR()
{
	char *re = NULL;
	re = _strdup((char *) "WARNINGS! mod input is a float number");
	return re;
}

char * factorial_negative_ERROR()
{
	char *re = NULL;
	re = _strdup((char *) "WARNINGS! factorial input is a negative number");
	return re;
}

char * real_exp_ERROR()
{
	char *re = NULL;
	re = _strdup((char *) "WARNINGS! unable to resolve the real power");
	return re;
}

char * read_file_ERROR()
{
	char *re = NULL;
	re = _strdup((char *) "WARNINGS! read a error file");
	return re;
}
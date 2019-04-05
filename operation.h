#pragma once
#include "init.h"
void plusBigNum(bigNum a, bigNum b, bigNum &result);
void subBigNum(bigNum a, bigNum b, bigNum &result);
void TempMulFunc(bigNum &a, bigNum &b, bigNum &result);
void mulBigNum(bigNum a, bigNum b, bigNum &result);
void divBigNum(bigNum a, bigNum b, bigNum &result);
void modBigNum(bigNum a, bigNum b, bigNum &result);
void expBigNum(bigNum a, bigNum b, bigNum &result);
void factorialBigNum(bigNum a, bigNum &result);
void pi(int k, bigNum &result);
void e(int k, bigNum &result);

void decreaseByOne(bigNum &a);
void decreaseByTwo(bigNum &a);
void increaseByTwo(bigNum &a);
void plusBySelf(bigNum &result, const bigNum a);
void mulBySelf(bigNum &result, const bigNum a);
void divBySelf(bigNum &result, const bigNum a);

void lamTronSo(bigNum &a, int k);
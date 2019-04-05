#pragma once
#include <iostream>
#define POSITIVE 0
#define NEGATIVE 1
#define MAXTAIL 100
#define MAX_PI 30
#define MAX_E 100

#pragma pack(1)
struct bigNum
{
	bool sign;
	char *num;
	char *tail;
};

const bigNum zero = { 0, NULL , NULL };
const bigNum one = { 0, (char *)"1", NULL };
const bigNum two = { 0, (char *)"2", NULL };
const bigNum three = { 0, (char *)"3", NULL };
const bigNum four = { 0, (char *)"4", NULL };
const bigNum five = { 0, (char *)"5", NULL };
const bigNum six = { 0, (char *)"6", NULL };//Addition to pi()
const bigNum seven = { 0, (char *)"7", NULL };//Addition to pi()
const bigNum eight = { 0, (char *)"8", NULL };//Addition to pi()
const bigNum nine = { 0, (char *)"9", NULL };//Addition to pi()
const bigNum eleven = { 0, (char *)"11", NULL };//Addition to pi()
const bigNum twelve = { 0, (char *)"12", NULL };//Addition to pi()
const bigNum thirtytwo = { 0, (char *)"32", NULL };//Addition to pi()
const bigNum sixtyfour = { 0, (char *)"64", NULL };//Addition to pi()
const bigNum onehundred = { 0, (char *) "10", NULL };//Addition to e()
const bigNum oneandtwentyeight = { 0, (char *)"128", NULL };//Addition to pi()
const bigNum threeandeightyfour = { 0, (char *)"384", NULL };//Addition to pi()
const bigNum fiveandtwelve = { 0, (char *)"512", NULL };//Addition to pi()
const bigNum fourtyandninetysix = { 0, (char *)"4096", NULL };//Addition to pi()

void freeString(char *&s);
void freeString(int num_args, ...);
void getString(char *&s);
void pushString(char *&s, char ch);
void catString(char *&des, const char* src);
char popString(char *&s);

void initBigNum(bigNum &a);
void initBigNum(int num_args, ...);
void freeBigNum(bigNum &a);
void freeBigNum(int num_args, ...);
void dupBigNum(bigNum &a, const bigNum b);
void deleteZeroUnnecessary(bigNum &a);
void deleteZeroUnnecessary(int num_args, ...);
void adjustAandB(bigNum &a, bigNum &b);
void divideByExpTen(bigNum &a, int num);

int convertBigNumToInt(const bigNum a);
void outputBigNum(bigNum a);//
char* convertBigNumToString(bigNum a);//
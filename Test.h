#pragma once
#include"Formula.h"
#include"Functions.h"
#include"Print.h"
#include"Types.h"
#include <iostream>
#include "ConsoleOp.h"
using namespace std;
void fun1(bool IsRunning) {
	if (!IsRunning)return;
	PrintSetup(1);
	string str = "314.15926897932384626";
	cout << StringToNum(str);
}
void fun2(bool IsRunning) {
	if (!IsRunning)return;/*
	SetupPrint(2);
	pMon ones[MON_SIZE] = {};
	ones[0] = NewMon(9, 4, 'x', 8, 'y', 6);
	ones[1] = NewMon(-7, 4, 'x', 8, 'y', 6);
	ones[2] = NewMon(0, 0);
	ones[3] = NewMon(4, 2, 'x', 3);
	ones[4] = NewMon(-6, 2, 'x', 3);
	ones[5] = NewMon(-1, 0);
	ones[6] = NewMon(7, 2, 'x', 3);
	ones[7] = NewMon(7, 2, 'y', 3);
	pMon ones2[MON_SIZE] = {};
	ones2[0] = NewMon(8, 4, 'x', 8, 'y', 6);
	ones2[1] = NewMon(-8, 4, 'x', 8, 'y', 6);
	ones2[2] = NewMon(-1, 0);
	ones2[3] = NewMon(3, 2, 'x', 3);
	ones2[4] = NewMon(-7, 2, 'x', 3);
	ones2[5] = NewMon(-2, 0);
	ones2[6] = NewMon(6, 2, 'x', 3);
	ones2[7] = NewMon(6, 2, 'y', 3);
	//MonPrint(ones[0]);
	printf("1:\n");
	Simp1(ones, slen(ones));
	Simp2(ones, slen(ones));
	MonsPrint(ones, MON_SIZE);
	printf("\n2:\n");
	Simp1(ones2, MON_SIZE);
	Simp2(ones2, MON_SIZE);
	MonsPrint(ones2, MON_SIZE);
	printf("\nplus:\n");
	pMon back[MON_SIZE] = {};
	MonsAdd(ones, ones2, back, MON_SIZE);
	MonsPrint(ones2, MON_SIZE);
	printf("\n1:\n");
	Simp1(ones, slen(ones));
	Simp2(ones, slen(ones));
	MonsPrint(ones, MON_SIZE);
	printf("\n2:\n");
	Simp1(ones2, MON_SIZE);
	Simp2(ones2, MON_SIZE);
	MonsPrint(ones2, MON_SIZE);
	printf("\nsub:\n");
	MonsSub(ones, ones2, back, MON_SIZE);
	MonsPrint(back, MON_SIZE);
	printf("\nopp:\n");
	MonsOpp(ones, back, MON_SIZE);
	MonsPrint(back, MON_SIZE);
	printf("\n0:\n");
	pMon back1[MON_SIZE] = {};
	MonsAdd(ones, back, back1, MON_SIZE);
	MonsPrint(back1, MON_SIZE);
	printf("\nmul:\n");
	MonsMul(ones, ones2, back, MON_SIZE);
	MonsPrint(back, MON_SIZE);*/
}
void fun3(bool IsRunning) {
	if (!IsRunning) return;
	system("mode con cols=200 lines=50");
	PrintSetup(3);
	string str = "324a^4/5b+(3456.3549387c*6754/(54^9+((5x/6/8t/9z^8))))";//+、-、*、/、^都是二目运算，需要二叉树，多目运算符考虑增加或归一
	pNode node = NewNode();
	pPol p15 = NewPol();
	SplitString(str, 0, 0, node->exp, false);
	Parse3_End(node, p15);
	Parse3_Print(node, 0, ConsoleOp::getxy());
	printf("\n");
	PolDebug(p15);
}
void fun4(bool IsRunning) {
	if (!IsRunning) return;
	PrintSetup(4);

	char n14[50] = "1";
	pMon m14 = CharToMon(n14);
	MonPrint(m14);
}
void fun5(bool IsRunning) {
	if (!IsRunning)return;/*
	SetupPrint(5);
	pMon ones[MON_SIZE] = {};
	ones[0] = NewMon(9, 4, 'x', 6, 'y', 6);
	ones[1] = NewMon(-7, 4, 'x', 8, 'y', 6);
	pMon ones2[MON_SIZE] = {};
	ones2[0] = NewMon(8, 4, 'x', 8, 'y', 6);
	ones2[7] = NewMon(6, 2, 'y', 3);
	//MonPrint(ones[0]);
	printf("1:\n");
	Simp1(ones, MON_SIZE);
	Simp2(ones, MON_SIZE);
	MonsPrint(ones, MON_SIZE);
	printf("\n2:\n");
	Simp1(ones2, MON_SIZE);
	Simp2(ones2, MON_SIZE);
	MonsPrint(ones2, MON_SIZE);
	pMon back[MON_SIZE] = {};
	printf("\nmul:\n");
	MonsMul(ones, ones2, back, MON_SIZE);
	MonsPrint(back, MON_SIZE);*/
}
void fun6(bool IsRunning) {
	if (!IsRunning)return;
	PrintSetup(7);
	pUnks uk = NewUnk(3, 5);
	uk = UnkInsert(uk, 2, 9);
	uk = UnkInsert(uk, 5, 10);
	uk = UnkInsert(uk, 3, 6);
	uk = UnkInsert(uk, 4, 7);
	cout << UnkTurnU(uk, 3)->exp;
	cout << UnkTurnI(uk, 2)->exp;
}
void test() {
	fun1(0);
	fun2(0);
	fun3(0);
	fun4(0);
	fun5(0);
	fun6(0);
}
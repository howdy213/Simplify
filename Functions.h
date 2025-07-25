#pragma once
#include"Formula.h"
#include"Print.h"
#include"Types.h"
#include<iostream>
#include<math.h>
#include<stdarg.h>
#include<string>
#include<string.h>
#include<windows.h>
using namespace std;
struct Unks {
	pUnks next = nullptr;
	short unk = 0;
	integer exp = 1;
};
struct Mon { //����ʽ,����ʽ������ʽ����
	integer coe = 0;//ϵ��
	pUnks unks = nullptr;
	pMon next = nullptr;
};
struct Node {
	int op = 0;
	pNode next[MON_NUM] = {};
	string exp;
};
struct Pol { //����ʽ
	int op = 0;//�������
	pPol next[MON_NUM] = {};//������
	pMon exp[2];//���ӷ�ĸ
};
//-------------------------------------------------------//
bool kd(int x);
rational pow(rational x, integer y);
//-------------------------------------------------------//
rational StringToNum(string str);
bool SplitString(string exp, int start, int end, string& res, bool mode);
int FindBracket(int pos, string str);
int CharToOp(string str);
void OpToChar(int op, string& str);
//-------------------------------------------------------//
pUnks NewUnk(short unk, integer exp);
int UnkLen(pUnks head);
pUnks UnkTurnI(pUnks head, integer index);
pUnks UnkTurnU(pUnks head, short unk);
pUnks UnkInsert(pUnks head, short unk, integer exp, bool ReHead = true);
bool UnkDelete(pUnks head, short unk);
void UnkSort(pUnks head);
pUnks UnksMul(pUnks first, pUnks second);
void UnksDel(pUnks head);
rational UnksCulc(pUnks head, Frame* fs);
//-------------------------------------------------------//
pNode NewNode();
int Parse3_op(string in, bool* next, pNode node, char op1, char op2, int op11, int op22);
int Parse3_Root(pNode node);
void Parse3_End(pNode head, pPol pol);//����(�ݹ�)
void Parse3_Print(pNode head, int mode, POINT xy);//TODO
void NodeDebug(pNode node);
//-------------------------------------------------------//
bool IsMonExist(pMon one);
pMon NewMon(integer coe = 0, int num = 0, ...);//��ʼ��
void MonClear(pMon one);
pMon CopyMon(pMon one);
pMon CharToMon(string exp);
bool IsMonSame(pMon first, pMon second);
void MonPrint(pMon one, bool PrintH = true);//�������ʽ
//-------------------------------------------------------//
void MonsPrint(pMon ones);//�������ʽ����
//void MonsPrintDebug(pMon ones, int length);//�������
pMon MonsAdd(pMon first, pMon second);//+
pMon MonsOpp(pMon one);//-
pMon MonsSub(pMon first, pMon second);//-
pMon MonMul(pMon first, pMon second);//*
pMon MonsMul(pMon first, pMon second);//*
void MonsDel(pMon head);
rational MonCulc(pMon mon, Frame* fs);
//-------------------------------------------------------//
pPol NewPol();//��ʼ��
void PolAdd(pPol first, pPol second, pPol back);
void PolSub(pPol first, pPol second, pPol back);
void PolMul(pPol first, pPol second, pPol back);
void PolDiv(pPol first, pPol second, pPol back);
void PolDel(pPol head);
void PolsDel(pPol head);
void PolPrint(pPol node);
void PolsPrint(pPol node);
void Parse4_Print(pPol head, int mode, POINT xy);
void PolDebug(pPol node);
void PolSimp(pPol head);
rational PolCulc(pPol head, Frame* fs);
//-------------------------------------------------------//

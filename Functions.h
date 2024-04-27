#pragma once
#include <iostream>
#include<string.h>
#include"Print.h"
#include<math.h>
#include<windows.h>
#include<stdarg.h>
#include"Formula.h"
#define kd(x) ((GetAsyncKeyState(x)&0x8000)?1:0)
#define color(color1,color2) (SetConsoleTextAttribute(wout, FOREGROUND_INTENSITY|color1*16+color2))
#define slen(array) (sizeof(array)/sizeof(array[0]))
#define CHAR_SIZE 200
#define MON_SIZE 50
#define MON_NUM 2
enum OPERATOR {ADD=1, SUB, MUL, DIV, POW, SIN, COS, TAN, ASIN, ACOS, ATAN , NONE};
struct Unks {
	Unks* next;
	short unk;
	int exp;
};
struct Mon { //单项式
	int coe;//系数
	Unks* unks;
	Mon* next;
};
struct Node {
	int op;
	Node* next[MON_NUM];
	char exp[CHAR_SIZE];
};
struct Pol { //多项式
	int op;//运算符号
	Pol* next[MON_NUM];//二叉树
	Mon* exp[2];//分子分母
};
//-------------------------------------------------------//
double CharToNum(char* str);
bool CutString(char* exp, int start, int end, char* back, bool mode);
int FindPairBra(int pos, char* str);
int CharToOp(char* str);
void OpToChar(int op, char* str);
//-------------------------------------------------------//
Unks* NewUnk(short unk,int exp);
int UnkLen(Unks* head);
Unks* UnkTurnI(Unks* head, int index);
Unks* UnkTurnU(Unks* head, short unk);
Unks* UnkInsert(Unks* head, short unk, int exp,bool ReHead=true);
bool UnkDelete(Unks* head,short unk);
void UnkSort(Unks* head);
Unks* UnksMul(Unks* first, Unks* second);
void UnksDel(Unks* head);
double UnksCulc(Unks* head, Frame* fs);
//-------------------------------------------------------//
Node* NewNode();
int Parse3_Root(Node* node);
void Parse3_End(Node* head, Pol* pol);//遍历(递归)
void Parse3_Print(Node* head, int mode, POINT xy);//TODO
void NodeDebug(Node* node);
//-------------------------------------------------------//
bool IsMonExist(Mon* one);
Mon* NewMon(int coe = 0, int num = 0, ...);//初始化
void MonClear(Mon* one);
Mon* CopyMon(Mon* one);
Mon* CharToMon(char* exp);
bool IsMonSame(Mon* first, Mon* second);
void MonPrint(Mon* one,bool PrintH=true);//输出单项式
//-------------------------------------------------------//
void MonsPrint(Mon* ones);//输出单项式数组
//void MonsPrintDebug(Mon* ones, int length);//调试输出
Mon* MonsAdd(Mon* first, Mon* second);//+
Mon* MonsOpp(Mon* one);//-
Mon* MonsSub(Mon* first, Mon* second);//-
Mon* MonMul(Mon* first, Mon* second);//*
Mon* MonsMul(Mon* first, Mon* second);///
void MonsDel(Mon* head);
double MonCulc(Mon* mon, Frame* fs);
//-------------------------------------------------------//
Pol* NewPol();//初始化
void PolAdd(Pol* first, Pol* second, Pol* back);
void PolSub(Pol* first, Pol* second, Pol* back);
void PolMul(Pol* first, Pol* second, Pol* back);
void PolDiv(Pol* first, Pol* second, Pol* back);
void PolDel(Pol* head);
void PolsDel(Pol* head);
void PolPrint(Pol* node);
void PolsPrint(Pol* node);
void Parse4_Print(Pol* head, int mode, POINT xy);
void PolDebug(Pol* node);
void PolSimp(Pol* head);
double PolCulc(Pol* head, Frame* fs);
//-------------------------------------------------------//

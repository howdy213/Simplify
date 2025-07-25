#pragma once
#include<Windows.h>
class ConsoleOp
{
public:
	static void gotoxy(short x, short y);
	static POINT getxy();
private:
	static HANDLE wout;
};


#include"Print.h"
#include<iostream>
HANDLE wout = GetStdHandle(STD_OUTPUT_HANDLE);
void SetupPrint(int num) {
	printf("\n----------setup_%d----------\n", num);
}
void CyclePrint(int num, char c) {
	int n = 0;
	for (n = 1; n <= num; n++)printf("%c", c);
}
void gotoxy(short x, short y) {
	COORD coord = { x,y };
	SetConsoleCursorPosition(wout, coord);
};
POINT getxy() {
	POINT* cursor = new POINT;
	CONSOLE_SCREEN_BUFFER_INFO sinfo;
	if (GetConsoleScreenBufferInfo(wout, &sinfo)) {
		cursor->x = sinfo.dwCursorPosition.X;
		cursor->y = sinfo.dwCursorPosition.Y;
	}
	return *cursor;
}
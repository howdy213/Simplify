#include "ConsoleOp.h"

HANDLE ConsoleOp::wout = GetStdHandle(STD_OUTPUT_HANDLE);
void ConsoleOp::gotoxy(short x, short y) {
	COORD coord = { x,y };
	SetConsoleCursorPosition(wout, coord);
};

POINT ConsoleOp::getxy() {
	POINT cursor = {};
	CONSOLE_SCREEN_BUFFER_INFO sinfo;
	if (GetConsoleScreenBufferInfo(wout, &sinfo)) {
		cursor.x = sinfo.dwCursorPosition.X;
		cursor.y = sinfo.dwCursorPosition.Y;
	}
	return cursor;
}
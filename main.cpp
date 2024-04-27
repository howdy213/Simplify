#include"Test.h"
using namespace std;
int main() {
	test();
		system("cls");

		Frame fmain;
		Formula ExpA('a');
		Formula ExpX('x');
		ExpA.AddToFrame(&fmain);
		ExpX.AddToFrame(&fmain);
		printf("Formula a;\na:=");
		char StrA[CHAR_SIZE];
		scanf_s("%s", StrA, CHAR_SIZE);
		ExpA.Init(StrA);
		ExpA.Simplify();
		printf("Simplify(a);\n");
		ExpA.Print();
		printf("a=");
		double va = 0.0;
		cin >> va;
		ExpA.Assign(va);

	while (1) {
		gotoxy(0, 10);
		printf("x=                                                                                                                                                                        ");
		gotoxy(2, 10);
		double vx = 0.0;
		cin >> vx;
		ExpX.Assign(vx);
		ExpA.Culc();
		gotoxy(0, 6);
		printf("a=%lf                                                                                                                                              ", ExpA.value);
	}
}
#include"Test.h"
using namespace std;
int main() {
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	test();
	system("cls");

	Frame fmain;
	Formula ExpA('a');
	Formula ExpX('x');

	ExpA.AddToFrame(&fmain);
	ExpX.AddToFrame(&fmain);
	printf("Formula a;\na:=");
	string StrA;
	cin >> StrA;
	ExpA.Init(StrA);
	ExpA.Simplify();
	printf("Simplify(a);\n");
	ExpA.Print();
	printf("Assign a=");
	rational va = 0.0;
	cin >> va;
	ExpA.Assign(va);

	while (1) {
		system("cls");
		ConsoleOp::gotoxy(0, 0);
		cout <<"The value of a is:\n"<<ExpA.GetValue();
		ConsoleOp::gotoxy(0, 5);
		cout << "a:\n";
		ExpA.Print();
		ConsoleOp::gotoxy(0, 9);
		printf("Assign x=                                                                                                                                                                        ");
		ConsoleOp::gotoxy(10, 9);
		rational vx = 0.0;
		cin >> vx;
		ExpX.Assign(vx);
		ExpA.Culc();
	}
}
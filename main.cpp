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
	string strVa;
	cin >> strVa;
	rational va = StringToNum(strVa);

	ExpA.Assign(va);

	while (1) {
		system("cls");
		ConsoleOp::gotoxy(0, 0);
		cout << "a:\n";
		ExpA.Print();
		cout << "\nThe value of a is:\n" << ExpA.GetValue() << "\nAssign x= \n";
		string strVx;
		cin >> strVx;
		if (strVx == "quit")return 0;
		ExpX.Assign(StringToNum(strVx));
		ExpA.Culc();
	}
}
#include "ConsoleOp.h"
#include "Frame.h"
#include "Functions.h"
#include <cassert>

#ifdef  _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

int Floor = -1;
int Pos3 = (int)pow(2, 7);

//-------------------------------------------------------//

bool kd(int x) {
	return(GetAsyncKeyState(x) & 0x8000) ? 1 : 0;
}

rational pow(rational a, integer n) {
	rational ans = 1;
	while (n) {
		if (n & 1)
			ans *= a;
		a *= a;
		n >>= 1;
	}
	return ans;
}

rational StringToNum(string str) {
	bool sign = true;
	bool hasSign = false;
	if (str[0] == '-' || str[0] == '+') {
		hasSign = true;
		if (str[0] == '-')sign = false;
		str = str.substr(1);
	}
	int dot = str.find('.');
	if (dot == -1)return sign ? rational(str) : -rational(str);
	string str2 = str.substr(dot + 1);
	if (str2.find('.') != -1)return false;
	str = str.substr(0, dot) + str2;
	rational res(str);
	res /= pow(10, str.length() - dot);
	return sign ? res : -res;
}

//从start至end(包括end),当mode==false时，代表倒数
bool SplitString(string exp, int start, int end, string& res, bool mode) {
	if (start < 0 || end < 0)return false;
	int length = exp.length() - 1;//末尾下标
	if (end > length || start > length)return false;
	if (mode == false)end = length - end;
	res = exp.substr(start, end - start + 1);
	return true;
}

//)->(,返回（的位置
int FindBracket(int pos, string str) {
	pos--;
	int bra = 1;
	for (; bra != 0 && pos >= 0; pos--)bra = bra + (str[pos] == ')') - (str[pos] == '(');
	pos++;
	if (bra != 0 && pos == 0) {
		pos = -1;
		assert(1);
	}
	return pos;
}
//-------------------------------------------------------//
//-TODO:add more operators
int CharToOp(string str) {
	int length = str.length();
	switch (str[0]) {
	case '+':
		return ADD;
	case '-':
		return SUB;
	case '*':
		return MUL;
	case '/':
		return DIV;
	case '^':
		return POW;
	case 's':
		if (length >= 3)if (str[1] == 'i' && str[2] == 'n')return SIN;
		else return -1;
	default:
		return -1;
	}
}
//TODO:add more operators
void OpToChar(int op, string& str) {
	switch (op) {
	case ADD:
		str[0] = '+';
		break;
	case SUB:
		str[0] = '-';
		break;
	case MUL:
		str[0] = '*';
		break;
	case DIV:
		str[0] = '/';
		break;
	case POW:
		str[0] = '^';
	default:
		str = "";
		break;
	}
}
//-------------------------------------------------------//
pUnks NewUnk(short unk, integer exp) {
	pUnks res(new Unks);
	res->next = nullptr;
	res->exp = exp;
	res->unk = unk;
	return res;
}
pUnks CopyUnks(pUnks unks) {
	if (unks == nullptr)return nullptr;
	pUnks res = NewUnk(unks->unk, unks->exp);
	pUnks bak = res;
	while (true) {
		unks = unks->next;
		if (unks != nullptr)res->next = NewUnk(unks->unk, unks->exp);
		else return bak;
		res = res->next;
	}
}
bool IsUnksSame(pUnks first, pUnks second) {
	if (first == second)return true;
	if (first == nullptr || second == nullptr)return false;
	while (first->exp == second->exp && first->unk == second->unk) {
		first = first->next;
		second = second->next;
		if (first == nullptr && second == nullptr)return true;
		if (first == nullptr || second == nullptr)return false;
	}
	return false;
}
void UnksPrint(pUnks unks) {
	while (unks != nullptr) {
		cout << (char)((char)unks->unk + 'a');
		if (unks->exp != 1)cout << '^' << unks->exp;
		unks = unks->next;
	}
}

pUnks UnkTurnI(pUnks head, integer index) {
	while (index >= 2 && head != nullptr) {//第n个只需执行n-2次
		index--;
		head = head->next;
	}
	return head;
}

pUnks UnkTurnU(pUnks head, short unk) {
	while (head != nullptr) {
		if (head->unk > unk)return nullptr;
		else if (head->unk == unk)return head;
		else head = head->next;
	}
	return nullptr;
}

int UnkLen(pUnks head) {
	int len = 0;
	while (head != nullptr) {
		head->next;
		len++;
	}
	return len;
}
//ReHead 返回头指针
pUnks UnkInsert(pUnks head, short unk, integer exp, bool ReHead) {
	if (head == nullptr)return NewUnk(unk, exp);
	pUnks rhead = head;
	pUnks lhead = nullptr;
	while (head != nullptr) {
		if (head->unk < unk) {
			lhead = head;
			head = head->next;
		}
		else if (head->unk == unk) {
			head->exp += exp;
			return ReHead ? rhead : head;
		}
		else {
			pUnks u = NewUnk(unk, exp);
			u->next = head;
			if (lhead != nullptr) {
				lhead->next = u;
				return ReHead ? rhead : u;
			}
			else return u;
		}
	}
	lhead->next = NewUnk(unk, exp);//此时，unk是最后一项
	return rhead;
}
bool UnkDelete(pUnks head, short unk) {
	return false;
}
void UnkSort(pUnks head) {
	return;
}
pUnks UnksMul(pUnks first, pUnks second) {
	if (first == nullptr && second == nullptr)return nullptr;
	if (first == nullptr || second == nullptr) {
		pUnks re = (first != nullptr) ? first : second;
		return CopyUnks(re);
	}
	pUnks res = CopyUnks(first);
	if (res->unk > second->unk) {
		res = UnkInsert(res, second->unk, second->exp, false);
		second = second->next;
	}
	pUnks head = res;
	while (second != nullptr) {
		res = UnkInsert(res, second->unk, second->exp, false);
		second = second->next;
	}
	return head;
}
void UnksDel(pUnks head) {
	if (head == nullptr)return;
	UnksDel(head->next);
	//delete head;
}
rational UnksCulc(pUnks head, Frame* fs) {
	if (head == nullptr)return 1.0;
	return UnksCulc(head->next, fs) * pow(fs->GetValue(head->unk + 'a'), head->exp);
}
//-------------------------------------------------------//
bool IsMonExist(pMon one) {
	if (one == nullptr)return false;
	else if (one->coe == 0)return false;
	else return true;
}
//初始化
pMon NewMon(integer coe, int num, ...) {
	pMon mon(new Mon);
	mon->unks = nullptr;
	mon->coe = coe;
	mon->next = nullptr;
	if (!num)return mon;
	va_list arg;
	va_start(arg, num);
	for (int m = 0; m < num / 2; m++) {
		char c = (char)va_arg(arg, int);
		int i = va_arg(arg, int);
		UnkInsert(mon->unks, c - 'a', i, true);
	}
	va_end(arg);
	return mon;
}
pMon NewMon(integer coe, pUnks unks) {
	pMon re(new Mon);
	re->coe = coe;
	re->unks = unks;
	re->next = nullptr;
	return re;
}
void MonClear(pMon one) {
	if (one == nullptr)return;
	one->coe = 0;
	one->unks = nullptr;
}
//TODO:插入时自动排序，而非末尾
pMon MonInsert(pMon mon, integer coe, pUnks unks) {
	if (mon == nullptr)return NewMon(coe, unks);
	pMon rmon = mon;
	if (IsUnksSame(mon->unks, unks)) {
		mon->coe += coe;
		if (mon->coe == 0) {
			rmon = mon->next;
			return rmon;
		}
		return mon;
	}
	while (mon->next != nullptr) {
		if (IsUnksSame(mon->next->unks, unks)) {
			mon->next->coe += coe;
			if (mon->next->coe == 0) {
				pMon nmon = mon->next->next;
				mon->next = nmon;
			}
			return rmon;
		}
		else mon = mon->next;
	}
	mon->next = NewMon(coe, unks);
	return rmon;
}
pMon CopyMon(pMon one) {
	if (!IsMonExist(one))return nullptr;
	pMon back(new Mon);
	back->coe = one->coe;
	back->unks = CopyUnks(one->unks);
	return back;
}
pMon StringToMon(string exp) {
	if (exp == "")return nullptr;
	int coe = 0;
	pUnks unks = nullptr;
	string str1;
	int length = exp.length();
	int pos1 = 0;
	int LetterPos = 0;
	bool dot1 = false;
	for (; pos1 <= length && ((exp[pos1] >= 48 && exp[pos1] <= 57)) || (exp[pos1] == '.'); pos1++) {
		if (exp[pos1] == '.') {
			if (dot1)return nullptr;
			else dot1 = true;
		}
	}
	SplitString(exp, 0, pos1 - 1, str1, true);
	int a = str1.length();
	if (a == 0)coe = 1;
	else coe = (int)StringToNum(str1);

	for (; pos1 <= length - 1;) {
		char unk = exp[pos1];
		pos1++;
		if (exp[pos1] <= 'z' && exp[pos1] >= 'a' || exp[pos1] == '\0') {
			if (unk > 'z' || unk < 'a')return nullptr;
			unks = UnkInsert(unks, unk - 'a', 1, true);
			continue;
		}
		else if (exp[pos1] == '^') {
			pos1++;
			int pos2 = pos1;
			bool dot2 = false;
			for (; pos2 <= length && ((exp[pos2] >= 48 && exp[pos2] <= 57)) || (exp[pos2] == '.');) {
				if (exp[pos2] == '.') {
					if (dot2)return nullptr;
					else dot2 = true;
				}
				pos2++;
			}
			string str2;
			SplitString(exp, pos1, pos2 - 1, str2, true);
			int expo = (int)StringToNum(str2);
			if (unk > 'z' || unk < 'a')return nullptr;//
			unks = UnkInsert(unks, unk - 'a', expo, true);
			pos1 = pos2;
		}
		else return nullptr;
	}
	return NewMon(coe, unks);
}
bool IsMonSame(pMon first, pMon second) {
	if (first == nullptr || second == nullptr)return false;
	if (first->coe == 0 || second->coe == 0)return false;
	return IsUnksSame(first->unks, second->unks);
}
//输出单项式
void MonPrint(pMon one, bool PrintH) {
	if (!IsMonExist(one))return;
	else {
		if (one->coe > 0 && PrintH)printf("+");
		if (one->coe == 1 && one->unks == nullptr)printf("1");
		else if (one->coe != 1)cout << one->coe;
		UnksPrint(one->unks);
	}
}
//-------------------------------------------------------//
//输出单项式数组
pMon CopyMons(pMon mons) {
	if (!IsMonExist(mons))return nullptr;
	pMon head = CopyMon(mons);
	pMon re = head;
	while (mons != nullptr) {
		mons = mons->next;
		head->next = CopyMon(mons);
		head = head->next;
	}
	return re;
}
void MonsPrint(pMon mons) {
	while (mons != nullptr) {
		MonPrint(mons);
		mons = mons->next;
	}
}
//TODO:在MonInsert重构能保证pMon有序性后，插入不再从头开始
pMon MonsAdd(pMon first, pMon second) {
	if (first == nullptr && second == nullptr)return nullptr;
	if (first == nullptr || second == nullptr) {
		pMon re = (first != nullptr) ? first : second;
		return CopyMons(re);
	}
	pMon res = CopyMons(first);
	while (second != nullptr) {
		res = MonInsert(res, second->coe, second->unks);
		second = second->next;
	}
	return res;
};
//+
pMon MonsOpp(pMon mon) {
	pMon re = NewMon(mon->coe, mon->unks);
	while (mon != nullptr) {
		re->next = NewMon(-mon->coe, mon->unks);
		mon = mon->next;
		re = re->next;
	}
	return re;
}
//-
pMon MonsSub(pMon first, pMon second) {
	pMon opp = MonsOpp(second);
	return MonsAdd(first, opp);
}
pMon MonMul(pMon first, pMon second) {
	if (!(IsMonExist(first) && IsMonExist(second)))return nullptr;
	return NewMon(first->coe * second->coe, UnksMul(first->unks, second->unks));
}
pMon MonsMul(pMon first, pMon second) {
	pMon re = MonMul(first, second);
	pMon head = re;
	pMon shead = second;
	second = second->next;
	while (first != nullptr) {//交叉相乘
		while (second != nullptr) {
			pMon mul = MonMul(first, second);
			MonInsert(re, mul->coe, mul->unks);
			second = second->next;
		}
		second = shead;
		first = first->next;
	}
	return head;
}
void MonsDel(pMon head) {
	if (head == nullptr)return;
	MonsDel(head->next);
	head->coe = 0;
	//delete head->next;
	UnksDel(head->unks);
}
rational MonCulc(pMon mon, Frame* fs)
{
	if (mon == nullptr)return 0.0;
	return MonCulc(mon->next, fs) + mon->coe * UnksCulc(mon->unks, fs);
}
//-------------------------------------------------------//
//node
//新建并返回Node
pNode NewNode() {
	pNode node(new Node);
	node->op = 0;
	for (int n = 0; n <= MON_NUM - 1; n++)node->next[n] = nullptr;
	return node;
}
//返回操作的位置
int Parse3_op(string in, bool* next, pNode node, char op1, char op2, int op11, int op22) {
	int length = in.length();
	int pos = 0;
	for (pos = length - 1; pos >= 0; pos--) {
		if (in[pos] == ')')pos = FindBracket(pos, in) - 1;//跳过（）
		if (pos == -1)break;
		if (in[pos] == op1)node->op = op11;
		if (in[pos] == op2)node->op = op22;
		if (in[pos] == op1 || in[pos] == op2) {
			*next = false;
			break;
		}
	}
	return pos;
}
int Parse3_Root(pNode node) {
	string in;
	SplitString(node->exp, 0, 0, in, false);
	int length = in.length();
	int bra = 0, pos = 0;
	bool next = true;
	if (next) {
		pos = Parse3_op(in, &next, node, '+', '-', ADD, SUB);
	}//+ -
	if (next) {
		pos = Parse3_op(in, &next, node, '*', '/', MUL, DIV);
	}//* /
	if (next) {
		pos = Parse3_op(in, &next, node, '^', '\0', POW, NONE);
	}
	if (!next) {
		node->next[0] = NewNode();
		if (SplitString(in, 0, pos - 1, node->next[0]->exp, true));
		else printf("ERROR_2\n");
		node->next[1] = NewNode();
		if (SplitString(in, pos + 1, 0, node->next[1]->exp, false));
		else printf("ERROR_3\n");
		for (int m = 0; m <= length - 1; m++)node->exp[m] = '\0';
		return pos;
	}
	else {
		SplitString(in, 0, 0, node->exp, false);
		return -1;
	};
};
void Parse3_End(pNode head, pPol pol) {
	//()并不参加运算，所以要除去，[]/{}同理
	//if (!head)return;
	if (head == nullptr)assert(1);
	if (head->exp != "")while (head->exp[head->exp.length() - 1] == ')' && FindBracket(head->exp.length() - 1, head->exp) == 0)SplitString(head->exp, 1, 1, head->exp, false);
	//如果是单项式
	if (StringToMon(head->exp) != nullptr) {
		pol->exp[0] = StringToMon(head->exp);
		pol->exp[1] = NewMon(1);
		pol->op = NONE;
		return;
	}
	else {
		Parse3_Root(head);
		pol->op = head->op;
		pol->next[0] = NewPol();
		pol->next[1] = NewPol();
		for (int n = 0; n <= MON_NUM - 1; n++)Parse3_End(head->next[n], pol->next[n]);
	}
};//遍历
void Parse3_Print(pNode head, int mode, POINT xy) {
	Floor++;
	if (mode == 1) {
		Pos3 += (int)pow(2, 6 - Floor);
	}
	else {
		Pos3 -= (int)pow(2, 6 - Floor);
	}
	ConsoleOp::gotoxy(Pos3 + (int)xy.x, Floor + (int)xy.y);
	if (head->exp[0] == '\0') {
		string c = "\0\0\0\0\0";
		OpToChar(head->op, c);
		printf("%s", c.c_str());
		Parse3_Print(head->next[0], 0, xy);
		Parse3_Print(head->next[1], 1, xy);
		Floor--;
		Pos3 += (int)pow(2, 6 - Floor - 1);
	}
	else {
		printf("%s", head->exp.c_str());
		if (mode == 1) {
			Pos3 -= (int)pow(2, 6 - Floor);
		}
		else {
			Pos3 += (int)pow(2, 6 - Floor);
		}
		Floor--;
		return;
	};
}
void NodeDebug(pNode node) {
	while (1) {
		if (node == nullptr) {
			printf("-to-");
			return;
		}
		string c = "\0\0\0\0\0";
		OpToChar(node->op, c);
		printf("%s%s\n", node->exp.c_str(), c.c_str());
		while (1) {
			if (kd(VK_LEFT)) {
				while (kd(VK_LEFT))Sleep(1);
				NodeDebug(node->next[0]);
				break;
			}
			if (kd(VK_RIGHT)) {
				while (kd(VK_RIGHT))Sleep(1);
				NodeDebug(node->next[1]);
				break;
			}
			if (kd(VK_UP)) {
				while (kd(VK_UP))Sleep(1);
				return;
			}
		}
	}
}
//-------------------------------------------------------//
//初始化
pPol NewPol() {
	pPol mons(new Pol);
	mons->op = 0;
	mons->exp[0] = nullptr;
	mons->exp[1] = nullptr;
	mons->next[0] = nullptr;
	mons->next[1] = nullptr;
	return mons;
}
bool DeleteNode(pNode head) {
	return false;
}
void PolPrint(pPol node) {
	//char c[5] = {};
	//OpToChar(node->op, c);
	//printf("%s", c);

	MonsPrint(node->exp[0]);
	printf("\n--------------------------------\n");
	MonsPrint(node->exp[1]);
	printf("\n");
}
//TODO:
void PolsPrint(pPol node) {
	PolPrint(node);
}

void PolAdd(pPol first, pPol second, pPol back) {
	pMon b = MonsSub(first->exp[1], second->exp[1]);
	if (!IsMonExist(b)) {
		back->exp[0] = MonsAdd(first->exp[0], second->exp[0]);
		back->exp[1] = MonsAdd(first->exp[1], nullptr);
		return;
	}
	back->exp[1] = MonsMul(first->exp[1], second->exp[1]);
	pMon u1 = MonsMul(first->exp[0], second->exp[1]);
	pMon u2 = MonsMul(first->exp[1], second->exp[0]);
	back->exp[0] = MonsAdd(u1, u2);
}
void PolSub(pPol first, pPol second, pPol back) {
	pPol op = NewPol();
	op->exp[0] = MonsOpp(second->exp[0]);
	op->exp[1] = MonsAdd(second->exp[1], nullptr);
	PolAdd(first, op, back);
	//delete op;
	return;
}
void PolMul(pPol first, pPol second, pPol back) {
	back->exp[0] = MonsMul(first->exp[0], second->exp[0]);
	back->exp[1] = MonsMul(first->exp[1], second->exp[1]);
}
void PolDiv(pPol first, pPol second, pPol back) {
	back->exp[0] = MonsMul(first->exp[0], second->exp[1]);
	back->exp[1] = MonsMul(first->exp[1], second->exp[0]);
}

void PolDel(pPol head)
{
	if (head == nullptr)return;
	head->op = 0;
	MonsDel(head->exp[0]);
	head->exp[0] = nullptr;
	MonsDel(head->exp[1]);
	head->exp[1] = nullptr;
	//delete head;
	return;
}

void PolsDel(pPol head) {
	if (head == nullptr)return;
	PolsDel(head->next[0]);
	PolsDel(head->next[1]);
	PolDel(head->next[0]);
	PolDel(head->next[1]);
	return;
}
void Parse4_Print(pPol head, int mode, POINT xy) {
	Floor++;
	if (mode == 1) {
		Pos3 += pow(2, 6 - Floor);
	}
	else {
		Pos3 -= pow(2, 6 - Floor);
	}
	ConsoleOp::gotoxy(Pos3 + (int)xy.x, Floor + (int)xy.y);
	if (IsMonExist(head->exp[0])) {
		string c = "\0\0\0\0\0";
		OpToChar(head->op, c);
		printf("%s", c.c_str());
		Parse4_Print(head->next[0], 0, xy);
		Parse4_Print(head->next[1], 1, xy);
		Floor--;
		Pos3 += pow(2, 6 - Floor - 1);
	}
	else {
		printf("(");
		MonsPrint(head->exp[0]);
		printf(")/(");
		MonsPrint(head->exp[1]);
		printf(")");
		if (mode == 1) {
			Pos3 -= pow(2, 6 - Floor);
		}
		else {
			Pos3 += pow(2, 6 - Floor);
		}
		Floor--;
		return;
	};
}
void PolDebug(pPol node) {
	while (1) {
		if (node == nullptr) {
			printf("-to-\n");
			return;
		}
		PolPrint(node);
		while (1) {
			if (kd(VK_LEFT)) {
				while (kd(VK_LEFT))Sleep(1);
				PolDebug(node->next[0]);
				break;
			}
			if (kd(VK_RIGHT)) {
				while (kd(VK_RIGHT))Sleep(1);
				PolDebug(node->next[1]);
				break;
			}
			if (kd(VK_UP)) {
				while (kd(VK_UP))Sleep(1);
				return;
			}
		}
	}
}
//culc
void PolSimp(pPol head) {
	if (head == nullptr)return;
	for (int n = 0; n <= 1; n++)PolSimp(head->next[n]);
	bool IsOp = false;
	switch (head->op) {
	case ADD:
		PolAdd(head->next[0], head->next[1], head);
		IsOp = true;
		break;
	case SUB:
		PolSub(head->next[0], head->next[1], head);
		IsOp = true;
		break;
	case MUL:
		PolMul(head->next[0], head->next[1], head);
		IsOp = true;
		break;
	case DIV:
		PolDiv(head->next[0], head->next[1], head);
		IsOp = true;
		break;
	default:
		break;
	}
	//if (IsOp)for (int n = 0; n <= 1; n++)PolDel(head->next[n]);
	return;
}
rational PolCulc(pPol head, Frame* fs)
{
	if (head == nullptr)return 0.0;
	rational a = PolCulc(head->next[0], fs);
	rational b = PolCulc(head->next[1], fs);
	switch (head->op) {
	case NONE:
		return MonCulc(head->exp[0], fs) / MonCulc(head->exp[1], fs);
	case ADD:
		return a + b;
	case SUB:
		return a - b;
	case MUL:
		return a * b;
	case DIV:
		return a / b;
	default:
		return 0.0;
	}
}

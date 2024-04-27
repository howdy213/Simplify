#include"Functions.h"
#include"Frame.h"
int Floor = -1;
int Pos3 = (int)pow(2, 7);
//-------------------------------------------------------//
//sscanf
double CharToNum(char* str) {
	int length = strlen(str);
	length = (length >= 17) ? 17 : length;
	double num = 0.0;
	int point = 0;
	for (; point <= length - 1 && str[point] != '.'; point++)if (!(48 <= str[point] && str[point] <= 57))return 0;
	for (int n = 0; n <= length - 1; n++) {
		if (n == point)continue;
		num += ((str[n] - 48) * pow(10, -n + point - (int)(n <= point)));
	}
	return num;
}
//从start至end(包括end),当mode==false时，代表倒数

bool CutString(char* exp, int start, int end, char* back, bool mode) {
	if (start < 0 || end < 0)return false;
	int elength = strlen(exp) - 1;//末尾下标
	if (mode == false)end = elength - end;
	int blength = end - start + 1;
	int pos = 0;
	if (end > elength || start > elength)return false;
	char* wait = new char[elength + 1];
	for (; pos <= elength; pos++)wait[pos] = exp[pos];//交换；
	for (pos = 0; pos < CHAR_SIZE; pos++)back[pos] = '\0';
	for (pos = 0; pos <= blength - 1; pos++)back[pos] = wait[start + pos];
	delete[] wait;
	wait = nullptr;
	return true;
}/*
bool CutString(char* exp, int start, int end, char* back, bool mode) {
	if (start < 0 || end < 0)return false;
	int elength = strlen(exp) - 1;//末尾下标
	if (mode == false)end = elength - end;
	int blength = end - start;
	if (end > elength || start > elength)return false;
	int pos = 0;
	for (; (pos <= blength) && (start + pos <= elength); pos++)back[pos] = exp[start + pos];
	for (; pos <= blength; pos++)back[pos] = '\0';
	return true;
}*/
//)->(,返回（的位置
int FindPairBra(int pos, char* str) {
	pos--;
	int bra = 1;
	for (; bra != 0 && pos >= 0; pos--)bra = bra + (str[pos] == ')') - (str[pos] == '(');
	pos++;
	if (bra != 0 && pos == 0) {
		pos = -1;
		printf("ERROR_1\n");
	}
	return pos;
}
//-TODO:add more operators
int CharToOp(char* str) {
	int length = strlen(str);
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
void OpToChar(int op, char* str) {
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
		str = nullptr;
		break;
	}
}
//-------------------------------------------------------//
Unks* NewUnk(short unk, int exp) {
	Unks* res = new Unks;
	res->next = nullptr;
	res->exp = exp;
	res->unk = unk;
	return res;
}
Unks* CopyUnks(Unks* unks) {
	if (unks == nullptr)return nullptr;
	Unks* res = NewUnk(unks->unk, unks->exp);
	Unks* bak = res;
	while (true) {
		unks = unks->next;
		if (unks != nullptr)res->next = NewUnk(unks->unk, unks->exp);
		else return bak;
		res = res->next;
	}
}
bool IsUnksSame(Unks* first, Unks* second) {
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
void UnksPrint(Unks* unks) {
	while (unks != nullptr) {
		printf("%c", (char)unks->unk + 'a');
		if (unks->exp != 1)printf("^%d", unks->exp);
		unks = unks->next;
	}
}

Unks* UnkTurnI(Unks* head, int index) {
	while (index >= 2 && head != nullptr) {//第n个只需执行n-2次
		index--;
		head = head->next;
	}
	return head;
}
Unks* UnkTurnU(Unks* head, short unk) {
	while (head != nullptr) {
		if (head->unk > unk)return nullptr;
		else if (head->unk == unk)return head;
		else head = head->next;
	}
	return nullptr;
}
int UnkLen(Unks* head) {
	int len = 0;
	while (head != nullptr) {
		head->next;
		len++;
	}
	return len;
}
Unks* UnkInsert(Unks* head, short unk, int exp, bool ReHead) {
	if (head == nullptr)return NewUnk(unk, exp);
	Unks* rhead = head;
	Unks* lhead = nullptr;
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
			Unks* u = NewUnk(unk, exp);
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
bool UnkDelete(Unks* head, short unk) {
	return false;
}
void UnkSort(Unks* head) {
	return;
}
Unks* UnksMul(Unks* first, Unks* second) {
	if (first == nullptr && second == nullptr)return nullptr;
	if (first == nullptr || second == nullptr) {
		Unks* re = (first != nullptr) ? first : second;
		return CopyUnks(re);
	}
	Unks* res = CopyUnks(first);
	if (res->unk > second->unk) {
		res = UnkInsert(res, second->unk, second->exp, false);
		second = second->next;
	}
	Unks* head = res;
	while (second != nullptr) {
		res = UnkInsert(res, second->unk, second->exp, false);
		second = second->next;
	}
	return head;
}
void UnksDel(Unks* head) {
	if (head == nullptr)return;
	UnksDel(head->next);
	delete head;
}
double UnksCulc(Unks* head, Frame* fs){
	if (head == nullptr)return 1.0;
	return UnksCulc(head->next, fs) * pow(fs->GetValue(head->unk + 'a'), head->exp);
}
//-------------------------------------------------------//
bool IsMonExist(Mon* one) {
	if (one == nullptr)return false;
	else if (one->coe == 0)return false;
	else return true;
}
//初始化
Mon* NewMon(int coe, int num, ...) {
	Mon* mon = new Mon;
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
Mon* NewMon(int coe, Unks* unks) {
	Mon* re = new Mon;
	re->coe = coe;
	re->unks = unks;
	re->next = nullptr;
	return re;
}
void MonClear(Mon* one) {
	if (one == nullptr)return;
	one->coe = 0;
	one->unks = nullptr;
}
Mon* MonInsert(Mon* mon, int coe, Unks* unks) {
	if (mon == nullptr)return NewMon(coe, unks);
	Mon* lmon = nullptr;
	Mon* rmon = mon;
	if (IsUnksSame(mon->unks, unks)) {
		mon->coe += coe;
		if (mon->coe == 0) {
			rmon = mon->next;
			delete[] mon;
			return rmon;
		}
		return mon;
	}
	while (mon->next != nullptr) {
		if (IsUnksSame(mon->next->unks, unks)) {
			mon->next->coe += coe;
			if (mon->next->coe == 0) {
				Mon* nmon = mon->next->next;
				delete[] mon->next;
				mon->next = nmon;
			}
			return rmon;
		}
		else {
			lmon = mon;
			mon = mon->next;
		}
	}
	mon->next = NewMon(coe, unks);
	return rmon;
}
Mon* CopyMon(Mon* one) {
	if (!IsMonExist(one))return nullptr;
	Mon* back = new Mon;
	back->coe = one->coe;
	back->unks = CopyUnks(one->unks);
	return back;
}
Mon* CharToMon(char* exp) {
	if (exp == "")return nullptr;
	int coe = 0;
	Unks* unks = nullptr;
	char str1[CHAR_SIZE] = {};
	int length = strlen(exp);
	int pos1 = 0;
	int LetterPos = 0;
	bool dot1 = false;
	for (; pos1 <= length && ((exp[pos1] >= 48 && exp[pos1] <= 57)) || (exp[pos1] == '.'); pos1++) {
		if (exp[pos1] == '.') {
			if (dot1)return nullptr;
			else dot1 = true;
		}
	}
	CutString(exp, 0, pos1 - 1, str1, true);
	int a = strlen(str1);
	if (strlen(str1) == 0)coe = 1;
	else coe = (int)CharToNum(str1);

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
			char* str2 = new char[CHAR_SIZE];
			CutString(exp, pos1, pos2 - 1, str2, true);
			int expo = (int)CharToNum(str2);
			delete[]str2;
			str2 = nullptr;
			if (unk > 'z' || unk < 'a')return nullptr;//
			unks = UnkInsert(unks, unk - 'a', expo, true);
			pos1 = pos2;
		}
		else return nullptr;
	}
	return NewMon(coe, unks);
}
bool IsMonSame(Mon* first, Mon* second) {
	if (first == nullptr || second == nullptr)return false;
	if (first->coe == 0 || second->coe == 0)return false;
	return IsUnksSame(first->unks, second->unks);
}
//输出单项式
void MonPrint(Mon* one, bool PrintH) {
	if (!IsMonExist(one))return;
	else {
		if (one->coe > 0 && PrintH)printf("+");
		if (one->coe == 1 && one->unks == nullptr)printf("1");
		else if (one->coe != 1)printf("%d", one->coe);
		UnksPrint(one->unks);
	}
}
//-------------------------------------------------------//
//输出单项式数组
Mon* CopyMons(Mon* mons) {
	if (!IsMonExist(mons))return nullptr;
	Mon* head = CopyMon(mons);
	Mon* re = head;
	while (mons != nullptr) {
		mons = mons->next;
		head->next = CopyMon(mons);
		head = head->next;
	}
	return re;
}
void MonsPrint(Mon* mons) {
	while (mons != nullptr) {
		MonPrint(mons);
		mons = mons->next;
	}
}
/*
void Simp1(Mon** ones, int length) {
	if (ones == nullptr)return;
	int pos = 0;
	for (int m = 0; m <= length - 1; m++)
		for (int n = m + 1; n <= length - 1; n++) {
			if (IsSame(ones[m], ones[n])) {
				ones[m]->coe += ones[n]->coe;
				ones[n] = nullptr;
			};
		};
};//合并同类项
void Simp2(Mon** ones, int length) {
	if (ones == nullptr)return;
	Mon** mons = new Mon * [length];
	int pos = 0;
	for (int n = 0; n <= length - 1; n++) {
		mons[n] = nullptr;
		if (IsExist(ones[n])) {
			mons[pos] = ones[n];
			pos++;
		}
		ones[n] = nullptr;
	}
	for (int n = 0; n <= length - 1; n++)ones[n] = mons[n];
	delete[] mons;
	mons = nullptr;
	return;
}//整理
void Simp(Mon** ones, int length) {
	Simp1(ones, length);
	Simp2(ones, length);
}*/
//要求三个数组长度皆为length(=MON_SIZE),
Mon* MonsAdd(Mon* first, Mon* second) {
	if (first == nullptr && second == nullptr)return nullptr;
	if (first == nullptr || second == nullptr) {
		Mon* re = (first != nullptr) ? first : second;
		return CopyMons(re);
	}
	Mon* res = CopyMons(first);
	while (second != nullptr) {
		res = MonInsert(res, second->coe, second->unks);
		second = second->next;
	}
	return res;
};//+
Mon* MonsOpp(Mon* mon) {
	Mon* re = NewMon(mon->coe, mon->unks);
	while (mon != nullptr) {
		re->next = NewMon(-mon->coe, mon->unks);
		mon = mon->next;
		re = re->next;
	}
	return re;
}
//
Mon* MonsSub(Mon* first, Mon* second) {
	Mon* opp = MonsOpp(second);
	return MonsAdd(first, opp);
}
Mon* MonMul(Mon* first, Mon* second) {
	if (!(IsMonExist(first) && IsMonExist(second)))return nullptr;
	return NewMon(first->coe * second->coe, UnksMul(first->unks, second->unks));
}
Mon* MonsMul(Mon* first, Mon* second) {
	Mon* re = MonMul(first, second);
	Mon* head = re;
	Mon* shead = second;
	second = second->next;
	while (first != nullptr) {
		while (second != nullptr) {
			Mon* mul = MonMul(first, second);
			MonInsert(re, mul->coe, mul->unks);
			second = second->next;
		}
		second = shead;
		first = first->next;
	}
	return head;
}
void MonsDel(Mon* head) {
	if (head == nullptr)return;
	MonsDel(head->next);
	head->coe = 0;
	delete head->next;
	UnksDel(head->unks);
}
double MonCulc(Mon* mon, Frame* fs)
{
	if (mon == nullptr)return 0.0;
	return MonCulc(mon->next, fs) + mon->coe*UnksCulc(mon->unks, fs);
}
//-------------------------------------------------------//
//node
//新建并返回Node
Node* NewNode() {
	Node* node = new Node;
	node->op = 0;
	for (int pos = 0; pos <= MON_SIZE - 1; node->exp[pos] = '\0', pos++);
	for (int n = 0; n <= MON_NUM - 1; n++)node->next[n] = nullptr;
	return node;
}
//返回操作的位置
int Parse3_op(int length, char* in, bool* next, Node* node, char op1, char op2, int op11, int op22) {
	int pos = 0;
	for (pos = length - 1; pos >= 0; pos--) {
		if (in[pos] == ')')pos = FindPairBra(pos, in) - 1;//跳过（）
		if (in[pos] == op1)node->op = op11;
		if (in[pos] == op2)node->op = op22;
		if (in[pos] == op1 || in[pos] == op2) {
			*next = false;
			break;
		}
	}
	return pos;
}
int Parse3_Root(Node* node) {
	char in[CHAR_SIZE] = {};
	CutString(node->exp, 0, 0, in, false);
	int length = strlen(in);
	int bra = 0, pos = 0;
	bool next = true;
	if (next) {
		pos = Parse3_op(length, in, &next, node, '+', '-', ADD, SUB);
	}//+ -
	if (next) {
		pos = Parse3_op(length, in, &next, node, '*', '/', MUL, DIV);
	}//* /
	if (next) {
		pos = Parse3_op(length, in, &next, node, '^', '\0', POW, NONE);
	}
	if (!next) {
		node->next[0] = NewNode();
		if (CutString(in, 0, pos - 1, node->next[0]->exp, true));
		else printf("ERROR_2\n");
		node->next[1] = NewNode();
		if (CutString(in, pos + 1, 0, node->next[1]->exp, false));
		else printf("ERROR_3\n");
		for (int m = 0; m <= length - 1; m++)node->exp[m] = '\0';
		return pos;
	}
	else {
		CutString(in, 0, 0, node->exp, false);
		return -1;
	};
};
void Parse3_End(Node* head, Pol* pol) {
	//()并不参加运算，所以要除去，[]/{}同理
	while (head->exp[strlen(head->exp) - 1] == ')' && FindPairBra(strlen(head->exp) - 1, head->exp) == 0)CutString(head->exp, 1, 1, head->exp, false);
	//如果是单项式
	if (CharToMon(head->exp) != nullptr) {
		pol->exp[0] = CharToMon(head->exp);
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
void Parse3_Print(Node* head, int mode, POINT xy) {
	Floor++;
	if (mode == 1) {
		Pos3 += (int)pow(2, 6 - Floor);
	}
	else {
		Pos3 -= (int)pow(2, 6 - Floor);
	}
	gotoxy(Pos3 + (int)xy.x, Floor + (int)xy.y);
	if (head->exp[0] == '\0') {
		char c[5] = {};
		OpToChar(head->op, c);
		printf("%s", c);
		Parse3_Print(head->next[0], 0, xy);
		Parse3_Print(head->next[1], 1, xy);
		Floor--;
		Pos3 += (int)pow(2, 6 - Floor - 1);
	}
	else {
		printf("%s", head->exp);
		if (mode == 1) {
			Pos3 -= (int)pow(2, 6 - Floor);
		}
		else {
			Pos3 += (int)pow(2, 6 - Floor);
		}
		Floor--;
		return;
	};
}//TODO
void NodeDebug(Node* node) {
	while (1) {
		if (node == nullptr) {
			printf("-to-");
			return;
		}
		char c[5] = {};
		OpToChar(node->op, c);
		printf("%s%s\n", node->exp, c);
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
Pol* NewPol() {
	Pol* mons = new Pol;
	mons->op = 0;
	mons->exp[0] = nullptr;
	mons->exp[1] = nullptr;
	mons->next[0] = nullptr;
	mons->next[1] = nullptr;
	return mons;
}
bool DeleteNode(Node* head) {
	return false;
}
void PolPrint(Pol* node) {
	//char c[5] = {};
	//OpToChar(node->op, c);
	//printf("%s", c);

	MonsPrint(node->exp[0]);
	printf("\n--------------------------------\n");
	MonsPrint(node->exp[1]);
	printf("\n");
}
//TODO:
void PolsPrint(Pol* node) {
	PolPrint(node);
}
void PolAdd(Pol* first, Pol* second, Pol* back) {
	Mon* b = MonsSub(first->exp[1], second->exp[1]);
	if (!IsMonExist(b)) {
		back->exp[0] = MonsAdd(first->exp[0], second->exp[0]);
		back->exp[1] = MonsAdd(first->exp[1], nullptr);
		return;
	}
	back->exp[1] = MonsMul(first->exp[1], second->exp[1]);
	Mon* u1 = MonsMul(first->exp[0], second->exp[1]);
	Mon* u2 = MonsMul(first->exp[1], second->exp[0]);
	back->exp[0] = MonsAdd(u1, u2);
}
void PolSub(Pol* first, Pol* second, Pol* back) {
	Pol* op = NewPol();
	op->exp[0] = MonsOpp(second->exp[0]);
	op->exp[1] = MonsAdd(second->exp[1], nullptr);
	PolAdd(first, op, back);
	delete[] op;
	return;
}
void PolMul(Pol* first, Pol* second, Pol* back) {
	back->exp[0] = MonsMul(first->exp[0], second->exp[0]);
	back->exp[1] = MonsMul(first->exp[1], second->exp[1]);
}
void PolDiv(Pol* first, Pol* second, Pol* back) {
	back->exp[0] = MonsMul(first->exp[0], second->exp[1]);
	back->exp[1] = MonsMul(first->exp[1], second->exp[0]);
}

void PolDel(Pol* head)
{
	if (head == nullptr)return;
	head->op = 0;
	MonsDel(head->exp[0]);
	head->exp[0] = nullptr;
	MonsDel(head->exp[1]);
	head->exp[1] = nullptr;
	free(head);
	return;
}

void PolsDel(Pol* head) {
	if (head == nullptr)return;
	PolsDel(head->next[0]);
	PolsDel(head->next[1]);
	PolDel(head->next[0]);
	PolDel(head->next[1]);
	return;
}
void Parse4_Print(Pol* head, int mode, POINT xy) {
	Floor++;
	if (mode == 1) {
		Pos3 += pow(2, 6 - Floor);
	}
	else {
		Pos3 -= pow(2, 6 - Floor);
	}
	gotoxy(Pos3 + (int)xy.x, Floor + (int)xy.y);
	if (IsMonExist(head->exp[0])) {
		char c[5] = {};
		OpToChar(head->op, c);
		printf("%s", c);
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
void PolDebug(Pol* node) {
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
void PolSimp(Pol* head) {
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
double PolCulc(Pol* head, Frame* fs)
{
	if (head == nullptr)return 0.0;
	double a = PolCulc(head->next[0], fs);
	double b = PolCulc(head->next[1], fs);
	switch (head->op) {
	case NONE:
		return MonCulc(head->exp[0],fs)/MonCulc(head->exp[1],fs);
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

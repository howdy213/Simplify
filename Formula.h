#pragma once
#include"Frame.h"
#include"Types.h"
#include<string>
using namespace std;
class Formula {
public:
	Formula(char id);
	~Formula();
	void AddToFrame(Frame* fs);
	void Init(string str);
	void Init(pPol root);
	void Init(Formula exp);
	void Assign(rational value);
	void Culc();
	rational GetValue();
	void Simplify();
	void Print();
private:
	friend Frame;
	char id = 0;
	pPol root = nullptr;
	rational value = 0;
	bool IsUpdated;
	Frame* fs;
};
#pragma once
#include"Frame.h"
struct Pol;
class Formula {
public:
	Pol* root = nullptr;
	double value = 0;
	bool IsUpdated;
	char id = 0;
	Formula(char id);
	~Formula();
	void AddToFrame(Frame* fs);
	void Init(char* str);
	void Init(Pol* root);
	void Init(Formula exp);
	void Assign(double value);
	void Culc();
	void Simplify();
	void Print();
private:
	Frame* fs;
};
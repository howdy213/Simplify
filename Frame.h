#pragma once
#include"Functions.h"
#include"Types.h"
#define FOR_NUM 10
#define DEFAULT_VALUE 1.0
class Frame {
public:
	void AddFormula(Formula* f);
	bool DeleteFormula(char id);
	void Culc();
	rational GetValue(char id);
	int FindFormula(char id);
private:
	void FsInvalid();
	std::vector<Formula*> fs;
};
#pragma once
class Formula; 
#define FOR_NUM 10
#define DEFAULT_VALUE 1.0
class Frame {
public:
	void AddFormula(Formula* f);
	bool DeleteFormula(char id);
	void Culc();
	double GetValue(char id);
	Formula* fs[FOR_NUM] = {};
private:
	int FindFormula(char id);
	void FsInvalid();
};
#include<iostream>
#include<windows.h>
#include<stdarg.h>
#include"Formula.h"
#include"Functions.h"
#include"Print.h"
Formula::Formula(char id) {
	this->id = id;
	this->fs = nullptr;
	this->IsUpdated = 0;
	return;
}
Formula::~Formula()
{
}
void Formula::AddToFrame(Frame* fs)
{
	this->fs = fs;
	fs->AddFormula(this);
}
void Formula::Init(string exp) {
	pNode node = NewNode();
	this->root = NewPol();
	SplitString(exp, 0, 0, node->exp, false);
	Parse3_End(node, this->root);
	return;
}

void Formula::Init(pPol root)
{
}

void Formula::Init(Formula exp)
{
}

void Formula::Assign(rational value)
{
	this->IsUpdated = true;
	this->value = value;
}

void Formula::Culc()
{
	this->IsUpdated = true;
	this->value = PolCulc(this->root, this->fs);
}

rational Formula::GetValue()
{
	return this->value;
}

void Formula::Simplify()
{
	PolSimp(this->root);
	return;
}

void Formula::Print()
{
	PolsPrint(this->root);
}


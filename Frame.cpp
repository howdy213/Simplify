#include"Frame.h"
#include"Formula.h"
void Frame::AddFormula(Formula* f)
{
	int pos = 0;
	for (; pos <= FOR_NUM; pos++)if (this->fs[pos] == nullptr)break;
	this->fs[pos] = f;
}

bool Frame::DeleteFormula(char id)
{
	int pos = this->FindFormula(id);
	if (pos == -1)return false;
	delete this->fs[pos];
	this->fs[pos] = nullptr;
	return true;
}

void Frame::Culc()
{
	this->FsInvalid();
	int pos = 0;
	while (pos<=FOR_NUM)
	{
		if (this->fs[pos] != nullptr) {
			this->fs[pos]->Culc();
		}

	}
}

void Frame::FsInvalid()
{
	int pos = 0;
	while (pos <= FOR_NUM - 1) {
		if (this->fs[pos] != nullptr) {
			this->fs[pos]->IsUpdated = false;
		}
	}
}

double Frame::GetValue(char id)
{
	int pos = this->FindFormula(id);
	if (pos == -1)return DEFAULT_VALUE;
	if (this->fs[pos]->IsUpdated == false)this->fs[pos]->Culc();
	return this->fs[pos]->value;
}

int Frame::FindFormula(char id)
{
	int pos = 0;
	for (; pos <= FOR_NUM - 1; pos++)if(this->fs[pos]!=nullptr)if (this->fs[pos]->id == id)break;
	return (pos == FOR_NUM) ? -1 : pos;
}

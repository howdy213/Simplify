#include"Formula.h"
#include"Frame.h"
void Frame::AddFormula(Formula* f)
{
	if (!f)return;
	for (int i = 0; i <= (int)fs.size() - 1; i++) {
		if (fs[i] == nullptr) {
			fs[i] = f;
			return;
		}
	}
	fs.push_back(f);
}

bool Frame::DeleteFormula(char id)
{
	int pos = FindFormula(id);
	if (pos == -1)return false;
	delete fs[pos];
	fs[pos] = nullptr;
	return true;
}

void Frame::Culc()
{
	this->FsInvalid();
	for (int i = 0; i <= (int)fs.size() - 1; i++) {
		if (this->fs[i] != nullptr) {
			this->fs[i]->Culc();
		}
	}
}

void Frame::FsInvalid()
{
	for (int i = 0; i <= (int)fs.size() - 1; i++) {
		if (this->fs[i] != nullptr) {
			this->fs[i]->IsUpdated = false;
		}
	}
}

rational Frame::GetValue(char id)
{
	int pos = this->FindFormula(id);
	if (pos == -1)return DEFAULT_VALUE;
	if (this->fs[pos]->IsUpdated == false)this->fs[pos]->Culc();
	return this->fs[pos]->value;
}

int Frame::FindFormula(char id)
{
	for (int i = 0; i <= (int)fs.size() - 1; i++) {
		if (this->fs[i] != nullptr) {
			if(fs[i]->id == id)return i;
		}
	}
	return -1;
}

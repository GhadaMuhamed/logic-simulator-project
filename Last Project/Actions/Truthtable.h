#pragma once
#include "Action.h"
#include "../Components\Component.h"
# include <string>
class Truthtable :public Action
{
public:
	Truthtable(ApplicationManager *pApp);
	virtual void Execute();
	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();
	string * calc(int number_of_switchs);
	~Truthtable();
};

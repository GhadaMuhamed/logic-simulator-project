#pragma once
#include "Action.h"

class Cut:public Action
{
public:
	Cut(ApplicationManager *pApp);
	virtual void Execute();
	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();
	~Cut();
};


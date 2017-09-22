#pragma once
#include "Action.h"

class deleting:public Action
{
public:
	deleting(ApplicationManager *pApp);
	virtual void Execute();
	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();
	~deleting();
};


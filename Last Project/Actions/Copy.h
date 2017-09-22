#pragma once
#include "Action.h"
class Copy:public Action
{
public:
	Copy(ApplicationManager *pApp);
	virtual void Execute();
	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();
	~Copy();
};


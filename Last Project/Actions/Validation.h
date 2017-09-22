#pragma once
#include "Action.h"
#include "..\Components\Component.h"
class Validation:public Action
{
public:
	Validation(ApplicationManager *pApp);
	virtual void Execute();
	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();
	~Validation();
};


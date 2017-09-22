#pragma once
#include "Action.h"
#include "..\Components\Component.h"
class Past:public Action
{
public:
	Past(ApplicationManager *pApp);
	virtual void Execute();
	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();
	~Past();
	
};


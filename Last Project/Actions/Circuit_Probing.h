#pragma once
#include"Action.h"
#include "..\Components\Component.h"

class Circuit_Probing :public Action
{
	int x1, y1;
public:
	Circuit_Probing(ApplicationManager *pApp);
	virtual void Execute();

	virtual void ReadActionParameters();
	virtual void Undo();
	virtual void Redo();
	~Circuit_Probing();
};


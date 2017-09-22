
#pragma once
#include "Action.h"
#include "..\Components\Connection.h"
class AddConnection:public Action
{
	int x1, y1, x2, y2;

public:
	AddConnection(ApplicationManager *pApp);

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
	virtual ~AddConnection(void);

};


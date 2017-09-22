#pragma once
#include"..\ApplicationManager.h"
#include "Action.h"
class Select:public Action
{
private:
	int x1, y1;
public:
	Select(ApplicationManager *pApp);
	virtual ~Select(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	//virtual void Execute2(int i, ApplicationManager *pApp);
	virtual void Undo();
	virtual void Redo();


};


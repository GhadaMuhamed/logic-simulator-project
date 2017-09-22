#pragma once
#include"..\ApplicationManager.h"
#include "Action.h"
class multiselect :public Action
{
private:
	int x1;
	int y1;
public:
	multiselect(ApplicationManager *pApp);
	virtual ~multiselect(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();


};


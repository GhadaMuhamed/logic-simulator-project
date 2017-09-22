#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include <fstream>
class Load:public Action
{
public:
	Load(ApplicationManager *pApp);
	Load(ApplicationManager *pApp, string s);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters() {};
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo() {};
	virtual void Redo() {};
	~Load();
};


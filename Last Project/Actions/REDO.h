#pragma once
#include "UNDO.h"
class REDO:public Action
{
public:
	REDO(ApplicationManager *pApp);
	string nameToLoad();
	void Execute();
	virtual void ReadActionParameters();
	~REDO();
};


#pragma once
#include "../Actions/Action.h"
# include "../Components/Component.h"
# include "AddConnection.h"
# include <iostream>
# include <string>
# include <vector>
# include "../ApplicationManager.h"
using namespace std;

class AddLabel :public Action
{
	int numofcom;
public:
	AddLabel(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	void setlabel(string s);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
	~AddLabel();
};




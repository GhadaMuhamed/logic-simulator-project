#pragma once
#include "Action.h"
#include "..\Components\Connection.h"
#include <string>
using namespace std;

class Edit :public Action
{
	string name;
	int x1, y1;
	int numofcom;
	Component** co;
	int **A;

public:
	Edit(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	void setlabel(string s);
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
	~Edit();
};



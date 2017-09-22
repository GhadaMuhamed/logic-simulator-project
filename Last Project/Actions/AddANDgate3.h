#pragma once
#include "Action.h"
#include "..\Components\AND3.h"
class AddANDgate3:public Action
{
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	AddANDgate3(ApplicationManager *pApp);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	bool check(GraphicsInfo GInfo);

	virtual void Undo();
	virtual void Redo();
	virtual ~AddANDgate3(void);

};


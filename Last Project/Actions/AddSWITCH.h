#pragma once
#include"..\Components\SWITCH.h"
#include "Action.h"
class AddSWITCH:public Action
{
	private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	AddSWITCH(ApplicationManager *pApp);
	virtual~AddSWITCH(void);
	bool check(GraphicsInfo GInfo);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};


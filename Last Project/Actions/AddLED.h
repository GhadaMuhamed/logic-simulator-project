#pragma once
#include "Action.h"
# include "..\Components\LED.h"
class AddLED :public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;
public:
	
	AddLED(ApplicationManager *pApp);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
	bool check(GraphicsInfo GInfo);

	virtual ~AddLED(void);

};


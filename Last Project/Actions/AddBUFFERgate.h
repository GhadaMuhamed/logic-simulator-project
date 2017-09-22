#pragma once
#include "Action.h"
#include "..\Components\BUFFER.h"
class AddBUFFERgate :public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	
public:
	AddBUFFERgate(ApplicationManager *pApp);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	bool check(GraphicsInfo GInfo);
	//virtual void Execute2(int i, ApplicationManager *pApp);
	virtual void Undo();
	virtual void Redo();
	 virtual ~AddBUFFERgate(void);
	
};


#pragma once
#include"..\ApplicationManager.h"
#include "Action.h"
class moveing :public Action
{
private:
	Component**y;//selected array
	int x1;
	int y1;
	int numofselected;//number of component whch selected and gate;
	vector<GraphicsInfo> vec;
public:
	moveing(ApplicationManager *pApp);
	virtual ~moveing(void);
	void moveconnection( Component*u);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	void counting_selected();
	Component** selectedarr();
	Component* getminx_y(Component**r);
	virtual void Undo();
	virtual void Redo();


};


#pragma once
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"

class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
	bool gate; // To know which tool bar is selected
public:
	Input(window*);
	void GetPointClicked(int &, int &);	//Get coordinate where user clicks
	string GetSrting(Output*);		//Returns a string entered by the user
	ActionType GetUserAction(); //Reads the user click and maps it to an action
	void ChangeToolBar(bool); // to change tool bar between actions and gates
	bool getToolbar(); // to get tool bar type
	~Input();
};

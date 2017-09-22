#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.H"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)

	static const int	width = 1300, height = 700,	//Window width and height
		wx = 15, wy = 15,			//Window starting coordinates
		StatusBarHeight = 50,	//Status Bar Height
		ToolBarHeight = 120,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		ToolItemWidth = 86, 		//Width of each item in toolbar menu
		Toolitemheight = 70;

	color DrawColor;		//Drawing color
	color SelectColor;		//Highlighting color
	color ConnColor;		//Connector color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Back ground color


							//This should be calculated accurately because it will be used later to create connections between gates
							//For now, we will assume that rect width = 50 and height = 50
	static const int	AND2_Width = 60,		//AND2 Gate Image default width
		AND2_Height = 40;		//AND2 Gate Image default height

	static const int	NAND2_Width = 60,		//NAND2 Gate Image default width
		NAND2_Height = 40;		//NAND2 Gate Image default height

	static const int	OR2_Width = 60,
		OR2_Height = 40;

	static const int	NOR2_Width = 60,
		NOR2_Height = 40;

	static const int	XNOR2_Width = 60,
		XNOR2_Height = 40;

	static const int	XOR2_Width = 60,
		XOR2_Height = 40;

	static const int	NOR3_Width = 60,
		NOR3_Height = 40;

	static const int	XOR3_Width = 60,
		XOR3_Height = 40;

	static const int	AND3_Width = 60,
		AND3_Height = 40;

	static const int	BUF_Width = 60,
		BUF_Height = 40;
	static const int	NOT_Width = 60,
		NOT_Height = 40;

	static const int	SWITCH_Width = 60,
		SWITCH_Height = 40;

	static const int	LED_Width = 60,
		LED_Height = 40;

}UI;	//create a single global object UI

#endif
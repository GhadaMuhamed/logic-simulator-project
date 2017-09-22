#pragma once
#include "..\Defs.h"
#include "Input.h"
#include <vector>
class Output	//The application manager should have a pointer to this class
{
private:
	int** grid;
	window* pWind, *pWind1;	//Pointer to the Graphics Window
public:
	Output(); // Performs the Window Initialization
	Input* CreateInput() const; //creates a pointer to the Input object
	void ChangeTitle(string Title) const;
	vector <GraphicsInfo> Make_path(GraphicsInfo, int arc[][135], pair<int,int> vis[][135]);
	vector <GraphicsInfo> Find_shortestPath(int ID, GraphicsInfo gfx_info, int arc[75][135],GraphicsInfo,GraphicsInfo);
	void CreateDesignToolBar() const;	//Tool bar of the design mode
	void CreateSimulationToolBar() const;//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar
	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area
	window* CreateWind(int wd, int h, int x, int y) const; //Creates user interface window
	void CreateActionsToolBar() const;
	// Draws 2-input AND gate
	void ClearGrid();
	void DrawConnection(GraphicsInfo, int, vector <GraphicsInfo>&,bool& PathChanged,int arc[75][135],GraphicsInfo,GraphicsInfo, bool selected = false);
	void DrawAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawAND3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawBUF(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOT(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawSWITCH_Off(GraphicsInfo r_GfxInfo, bool selected=false) const;
	void DrawSWITCH_On(GraphicsInfo r_GfxInfo, bool selected=false) const;
    void DrawLED_OFF(GraphicsInfo r_GfxInfo, bool selected=false) const;
		///TODO: Make similar functions for drawing all other gates, switch, and LED, .. etc
	void DrawLED_ON(GraphicsInfo r_GfxInfo, bool selected=false) const;
	window* getwind();
	void setbuffer(bool);
	void updatebuffer();
	// Draws Connection
	void PrintMsg(string msg) const;	//Print a message on Status bar
	void DrawMsg(string, int, int) const;
	void drawrect1(int x, int y, bool t);
	void drawrect2(int x, int y);
	image storeimage();
	void drawimage(image);
	void DrawConnection2(vector<GraphicsInfo> Connection_path, bool selected = false) const;
	int** getgrid();
		void createtruthtablewindow();
	void del_pwind1();
	void DrawMsg1(string, int, int) const;
		void ChangeTitle1(string Title) const;

	~Output();
};


#include "Output.h"
#include <queue>
Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode
							//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;
	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	ChangeTitle("Programming Techniques Project");
	pWind->SetBuffering(1);
	for (int i = 0; i < UI.height - UI.StatusBarHeight; i += 10)
	{
		pWind->SetPen(LIGHTGREY, 1);
		pWind->DrawLine(0, i, UI.width, i);
	}
	for (int i = 10; i < UI.width; i += 10)
	{
		pWind->SetPen(LIGHTGREY, 1);
		pWind->DrawLine(i, 0, i, UI.height - UI.StatusBarHeight);

	}
	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
	grid = new int*[75];
	for (int i = 0; i < 75; i++)
		grid[i] = new int[135];
	for (int i = 0; i < 75; i++)
		for (int j = 0; j < 135; j++)
			grid[i][j] = -1;
	pWind->UpdateBuffer();
	
}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
vector<GraphicsInfo> Output::Make_path(GraphicsInfo gfx_info, int arc[][135], pair<int,int> vis[][135])
{
	int x1 = gfx_info.x1; int x2 = gfx_info.x2;
	int y1 = gfx_info.y1; int y2 = gfx_info.y2;
	vector <GraphicsInfo> vec;
	int cur_x = x2;	int cur_y = y2;
	int last_x1 = x2;	int last_y1 = y2;	int last_x2 = x2;	int last_y2 = y2;
	GraphicsInfo gi;
	do
	{
		int temp1 = cur_x;
		cur_x = vis[cur_y][cur_x].first;
		cur_y = vis[cur_y][temp1].second;
		if (arc[cur_y][cur_x] != -1)
		{
			if ((cur_y == last_y2 && grid[cur_y][min(cur_x, last_x2) + 1] > 0) || (cur_x == last_x2 && grid[min(cur_y, last_y2) + 1][cur_x] > 0))
			{
				arc[cur_y][cur_x]++;
				arc[cur_y][cur_x] *= -1;
				gi.x1 = last_x1;	gi.x2 = last_x2;	gi.y1 = last_y1;		gi.y2 = last_y2;
				vec.push_back(gi);
				gi.x1 = last_x2;	gi.x2 = cur_x;	gi.y1 = last_y2;	gi.y2 = cur_y;
				vec.push_back(gi);
				last_x1 = cur_x;	last_y1 = cur_y;	last_y2 = cur_y;	last_x2 = cur_x;
				continue;

			}
		}
		if (cur_x == last_x1 && cur_y != last_y2)
		{

			last_y2 = cur_y;
		}
		else if (cur_y == last_y1 && cur_x != last_x2)
		{

			last_x2 = cur_x;
		}
		else
		{
			gi.x1 = last_x1; gi.x2 = last_x2; gi.y1 = last_y1; gi.y2 = last_y2;
			vec.push_back(gi);
			gi.x1 = last_x2;	gi.x2 = cur_x;	gi.y1 = last_y2;	gi.y2 = cur_y;
			vec.push_back(gi);
			last_x1 = cur_x;	last_x2 = cur_x;	last_y1 = cur_y;	last_y2 = cur_y;
		}
	} while (cur_x != x1 || cur_y != y1);
	gi.x1 = last_x1;	gi.x2 = last_x2;	gi.y1 = last_y1;	gi.y2 = last_y2;
	vec.push_back(gi);
	return vec;
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
						// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.MsgColor);
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
	pWind->UpdateBuffer();
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	for (int i = UI.ToolBarHeight; i < UI.height - UI.StatusBarHeight; i += 10)
	{
		pWind->SetPen(LIGHTGREY, 1);
		pWind->DrawLine(0, i, UI.width, i);
	}
	for (int i = 10; i < UI.width; i += 10)
	{
		pWind->SetPen(LIGHTGREY, 1);
		pWind->DrawLine(i, UI.ToolBarHeight, i, UI.height - UI.StatusBarHeight);

	}
	pWind->UpdateBuffer();
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode						//You can draw the tool bar icons in any way you want.
	pWind->DrawImage("images\\Menu\\gate.jpg", 0, 0, UI.width - 10, UI.ToolBarHeight);
	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "Images\\Menu\\and2.jpg";
	MenuItemImages[ITM_AND3] = "Images\\Menu\\and3.jpg";
	MenuItemImages[ITM_OR2] = "Images\\Menu\\or2.jpg";
	MenuItemImages[ITM_NAND2] = "Images\\Menu\\nand2.jpg";
	MenuItemImages[ITM_NOR2] = "Images\\Menu\\nor2.jpg";
	MenuItemImages[ITM_NOR3] = "Images\\Menu\\nor3.jpg";
	MenuItemImages[ITM_XOR2] = "Images\\Menu\\xor2.jpg";
	MenuItemImages[ITM_XOR3] = "Images\\Menu\\xor3.jpg";
	MenuItemImages[ITM_XNOR2] = "Images\\Menu\\xnor2.jpg";
	MenuItemImages[ITM_NOT] = "images\\Menu\\invert.jpg";
	MenuItemImages[ITM_BUFF] = "images\\Menu\\buff.jpg";
	MenuItemImages[ITM_LED] = "images\\Menu\\led.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\Menu\\sw.jpg";
	MenuItemImages[ITM_wire] = "images\\Menu\\wires.jpg";
	//TODO: Prepare imagee for each menu item and add it to the list
	//Draw menu item one image at a time
	for (int i = 0; i<14; i++)
		pWind->DrawImage(MenuItemImages[i], (i)*UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.Toolitemheight);
}
void Output::CreateActionsToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode
							//You can draw the tool bar icons in any way you want.
	pWind->DrawImage("images\\Menu\\actions.jpg", 0, 0, UI.width - 10, UI.ToolBarHeight);
	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_del] = "images\\Menu\\del.jpg";
	MenuItemImages[ITM_edit] = "images\\Menu\\edit.jpg";
	MenuItemImages[ITM_Select] = "images\\Menu\\sel.jpg";
	MenuItemImages[ITM_load] = "images\\Menu\\load.jpg";
	MenuItemImages[ITM_label] = "images\\Menu\\label.jpg";
	MenuItemImages[ITM_save] = "images\\Menu\\save.jpg";
	MenuItemImages[ITM_move] = "images\\Menu\\move.jpg";
	MenuItemImages[ITM_undo] = "images\\Menu\\undo.jpg";
	MenuItemImages[ITM_redo] = "images\\Menu\\redo.jpg";
	MenuItemImages[ITM_MultiS] = "images\\Menu\\ms.jpg";
	MenuItemImages[ITM_Cut] = "images\\Menu\\cut.jpg";
	MenuItemImages[ITM_Copy] = "images\\Menu\\copy.jpg";
	MenuItemImages[ITM_Paste] = "images\\Menu\\paste.jpg";
	MenuItemImages[ITM_Sim] = "images\\Menu\\sim.jpg";
	MenuItemImages[ITM_exit] = "images\\Menu\\exit.jpg";

	//MenuItemImages[ITM_change_switch] = "images\\Menu\\change_switch.jpg";
	//TODO: Prepare imagee for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 14; i<ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], (i - 14)*UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.Toolitemheight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode
								//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)
	pWind->DrawImage("images\\menu\\f.jpg", 0, 0, UI.width - 10, UI.ToolBarHeight);
	PrintMsg("If you want to change any switch Double click on it ..");
}
//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//
void  Output::ClearGrid()
{
	for (int i=0;i<75;i++)
		for (int j=0;j<135;j++)
			grid[i][j]=-1;
}
void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\and_h.jpg";
	else
		GateImage = "Images\\menu\\and.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;
	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.AND2_Width - 1, UI.AND2_Height - 1);
}
void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\2nand_h.jpg";
	else
		GateImage = "Images\\menu\\2nand.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.NAND2_Width - 1, UI.NAND2_Height - 1);
	
}
//TODO: Add similar functions to draw all components


void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\2or_h.jpg";
	else
		GateImage = "Images\\menu\\2or.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.OR2_Width - 1, UI.OR2_Height - 1);

}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\2nor_h.jpg";
	else
		GateImage = "Images\\menu\\2nor.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.NOR2_Width - 1, UI.NOR2_Height - 1);

}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\2xor_h.jpg";
	else
		GateImage = "Images\\menu\\2xor.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.NOR2_Width - 1, UI.NOR2_Height - 1);

}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\2xnor_h.jpg";
	else
		GateImage = "Images\\menu\\2xnor.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.NOR2_Width - 1, UI.NOR2_Height - 1);

}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\3nor_h.jpg";
	else
		GateImage = "Images\\menu\\3nor.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.NOR2_Width - 1, UI.NOR2_Height - 1);

}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\3xor.h.jpg";
	else
		GateImage = "Images\\menu\\3xor.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.NOR2_Width - 1, UI.NOR2_Height - 1);

}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\3and_h.jpg";
	else
		GateImage = "Images\\menu\\3and.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.NOR2_Width - 1, UI.NOR2_Height - 1);

}


void Output::DrawBUF(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\buffer_h.jpg";
	else
		GateImage = "Images\\menu\\buffer.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.NOR2_Width - 1, UI.NOR2_Height - 1);

}

void Output::DrawNOT(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\inverter_h.jpg";
	else
		GateImage = "Images\\menu\\inverter.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.NOR2_Width - 1, UI.NOR2_Height - 1);

}


void Output::DrawLED_ON(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\led_h.jpg";
	else
		GateImage = "Images\\menu\\led2On.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.NOR2_Width - 1, UI.NOR2_Height - 1);

}
void Output::DrawLED_OFF(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\led_h.jpg";
	else
		GateImage = "Images\\menu\\led2Off.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.NOR2_Width - 1, UI.NOR2_Height - 1);

}

void Output::DrawSWITCH_Off(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\SwitchOff_h.jpg";
	else
		GateImage = "Images\\menu\\SwitchOff.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.NOR2_Width - 1, UI.NOR2_Height - 1);

}
void Output::DrawSWITCH_On(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\switchOn_h.jpg";
	else
		GateImage = "Images\\menu\\switchOn.jpg";
	if (r_GfxInfo.y2>=UI.height-UI.StatusBarHeight-5 || r_GfxInfo.y1<=UI.ToolBarHeight+5) return;

	pWind->DrawImage(GateImage, r_GfxInfo.x1 + 1, r_GfxInfo.y1 + 1, UI.NOR2_Width - 1, UI.NOR2_Height - 1);

}

vector <GraphicsInfo> Output::Find_shortestPath(int ID, GraphicsInfo gfx_info, int arc[75][135],GraphicsInfo g1,GraphicsInfo g2)
{
	for (int i=g1.x1/10;i<=g1.x2/10;i++)
		for (int j=g1.y1/10;j<=g1.y2/10;j++)
			grid[j][i]=-5;
	for (int i=g2.x1/10;i<=g2.x2/10;i++)
		for (int j=g2.y1/10;j<=g2.y2/10;j++)
			grid[j][i]=-5;
			
	vector <GraphicsInfo> ans;
	pair<int, int> vis[75][135];
	memset(vis, -1, sizeof(vis));
	int x1 = gfx_info.x1;	int x2 = gfx_info.x2;
	int y1 = gfx_info.y1;   int y2 = gfx_info.y2;
	int direcx[] = { -1,1,0,0 };
	int direcy[] = { 0,0,-1,1 };
	memset(vis, -1, sizeof(vis));
	queue<pair<int, int>>q;
	q.push(make_pair( x1, y1 ));
	vis[y1][x1].first = x1;
	vis[y1][x1].second = y1;
	grid[y1][x1]=-1;
	grid[y2][x2]=-1;
	while (!q.empty())
	{
		int cur_x = q.front().first;
		int cur_y = q.front().second;
		q.pop();

		if (cur_x == x2 && cur_y == y2)
		{
			for (int i=g1.x1/10;i<=g1.x2/10;i++)
		for (int j=g1.y1/10;j<=g1.y2/10;j++)
			grid[j][i]=0;
	for (int i=g2.x1/10;i<=g2.x2/10;i++)
		for (int j=g2.y1/10;j<=g2.y2/10;j++)
			grid[j][i]=0;
			ans = Make_path(gfx_info, arc, vis);
			return ans;
		}
		for (int i = 0; i < 4; i++)
		{
			int child1 = cur_x + direcx[i];
			int child2 = cur_y + direcy[i];
			if ((child1-2>0 && grid[child2][child1-2]==0) || (child1+3<130 && grid[child2][child1+3]==0)) continue;
			if (child1 < 0 || child2 < 13 || child1>130 || child2>64) continue;
			if (grid[child2][child1] == 0 ||grid[child2][child1] == -5 ||  vis[child2][child1].first != -1) continue;
			else if (grid[child2][child1]>0 && grid[child2][child1] != ID)// cur_x==child1 -> vertical line ,, cur_y==child2 ->horizontal line
			{
				vis[child2][child1].first = cur_x;
				vis[child2][child1].second = cur_y;
				bool vertical;
				bool horizontal;
				if (cur_x == child1)
				{
					vertical = true;
					horizontal = false;
				}
				else
				{
					vertical = false;
					horizontal = true;
				}
				// edge
				/*if (grid[child2 + 1][child1] == grid[child2][child1 - 1] || grid[child2][child1 + 1] == grid[child2 + 1][child1] || grid[child2][child1 - 1] == grid[child2 - 1][child1] || grid[child2][child1 + 1] == grid[child2 - 1][child1])
				{
					//vis[child2][child1].first = vis[vis[child2][child1].second][vis[child2][child1].first].first;
					//vis[child2][child1].second = vis[vis[child2][child1].second][vis[child2][child1].first].second;
					q.push(make_pair( child1, child2 ));
				}*/
				if (vertical && (grid[child2][child1] == grid[child2][child1 + 1] || (child1 - 1 >= 0 && grid[child2][child1] == grid[child2][child1 - 1])))
				{
					int dest = child2;
					if (cur_y > child2)
					{
						dest--;
					}
					else {
						dest++;
					}
					if (dest > 70 || dest < 0 || grid[dest][child1] == 0) continue;
					int mid = (cur_y + dest) / 2;
					bool fnd = true;
					if (cur_x + 1 <= 130)
					{
						int dest_x = cur_x + 1;
						if (grid[mid][dest_x] >0)
						{
							arc[cur_y][cur_x] = 4;
							//	arc_point[mid][dest_x] = -5;

						}
						else fnd = false;
					}
					if (!fnd && cur_x - 1 >= 0)
					{
						fnd = true;
						int dest_x = cur_x - 1;
						if (grid[mid][dest_x] > 0)
						{
							arc[cur_y][cur_x] = 3;
							//arc_point[mid][dest_x] = -4;

						}
						else fnd = false;
					}
					if (!fnd)continue;
					if (grid[cur_y][cur_x] > 0)
					{
						vis[dest][child1].first = vis[cur_y][cur_x].first;
						vis[dest][child1].second = vis[cur_y][cur_x].second;
					}
					else
					{
						vis[dest][child1].first = cur_x;
						vis[dest][child1].second = cur_y;
					}
					q.push(make_pair( child1,dest ));
				}
				else if (horizontal && (grid[child2][child1] == grid[child2 + 1][child1] || (child2 - 1 >= 0 && grid[child2][child1] == grid[child2 - 1][child1])))
				{
					int dest = child1;
					if (cur_x > child1)
					{


						dest--;
					}
					else {

						dest++;
					}
					if (dest > 130 || dest < 0 || grid[child2][dest] == 0) continue;
					int mid = (cur_x + dest) / 2;
					bool fnd = true;
					if (cur_y + 1 <= 70)
					{
						int dest_y = cur_y + 1;
						if (grid[dest_y][mid] >0)
						{
							arc[cur_y][cur_x] = 2;
							//	arc_point[dest_y][mid] = -3;
						}
						else fnd = false;
					}
					if (!fnd && cur_y - 1 >= 0)
					{
						fnd = true;
						int dest_y = cur_y - 1;
						if (grid[dest_y][mid] > 0)
						{
							arc[cur_y][cur_x] = 1;
							//	arc_point[dest_y][mid] = -2;
						}

						else fnd = false;
					}
					if (!fnd)continue;

					if (grid[cur_y][cur_x] > 0)
					{
						vis[child2][dest].first = vis[cur_y][cur_x].first;

						vis[child2][dest].second = vis[cur_y][cur_x].second;
					}
					else
					{
						vis[child2][dest].first = cur_x;
						vis[child2][dest].second = cur_y;
					}




					q.push(make_pair(dest,child2 ));
				}
				continue;
			}
			q.push(make_pair( child1,child2 ));
			if (grid[cur_y][cur_x] > 0)
			{
				vis[child2][child1].first = vis[cur_y][cur_x].first;
				vis[child2][child1].second = vis[cur_y][cur_x].second;
			}
			else {
				vis[child2][child1].first = cur_x;
				vis[child2][child1].second = cur_y;
			}

			vis[child2][child1].first = cur_x;
			vis[child2][child1].second = cur_y;
			q.push(make_pair( child1,child2 ));
		}

	}

	for (int i=g1.x1/10;i<=g1.x2/10;i++)
		for (int j=g1.y1/10;j<=g1.y2/10;j++)
			grid[j][i]=0;
	for (int i=g2.x1/10;i<=g2.x2/10;i++)
		for (int j=g2.y1/10;j<=g2.y2/10;j++)
			grid[j][i]=0;
	return ans;
}
void Output::DrawConnection(GraphicsInfo gfx_info, int ID,vector <GraphicsInfo>& Connection_path, bool& PathChanged, int arc[75][135],GraphicsInfo g1,GraphicsInfo g2, bool selected)
{
	if (PathChanged)
	{
		PathChanged = false;
		for (int i = 0; i < 75; i++)
			for (int j = 0; j < 135; j++)
				arc[i][j] = -1;
		Connection_path.clear();
		Connection_path = Find_shortestPath(ID, gfx_info, arc,g1,g2);
	}
	if (Connection_path.size() == 0)
	{
		PrintMsg("Can't find a path for this connection ,, please move the gates ..");
		return;
	}
	//TODO: Add code to draw connection
	if (selected == false)
	{
		pWind->SetPen(BLACK, 2);
	}
	else if (selected == true)
	{
		pWind->SetPen(YELLOW, 2);
	}
	for (int i = 0; i <(int)Connection_path.size(); i++)
	{
		int x1 = Connection_path[i].x1;
		int x2 = Connection_path[i].x2;
		int y1 = Connection_path[i].y1;
		int y2 = Connection_path[i].y2;
		if (arc[y2][x2] != -1)
		{
			int x = arc[y2][x2];

			if (y1 == y2)
			{
				if (x == -2)
					pWind->DrawArc((min(x1, x2)) * 10, (y1) * 10, (max(x1, x2)) * 10, (y1 + 1) * 10 + 3, 0, 180);
				else if (x == -3)	pWind->DrawArc(min(x1, x2) * 10, y1 * 10, max(x1, x2) * 10, (y1 + 1) * 10 - 3, 180, 0);
				else 			pWind->DrawLine(x1 * 10, y1 * 10, x2 * 10, y2 * 10);

			}
			else if (x1 == x2)
			{

				if (x == -4)
					pWind->DrawArc(x1 * 10, min(y1, y2) * 10, (x1 - 1) * 10 + 3, max(y1, y2) * 10, 90, 270);
				else if (x == -5) pWind->DrawArc(x1 * 10, min(y1 * 10, y2 * 10), (x1 + 1) * 10 - 3, max(y1, y2) * 10, 270, 90);
				else			pWind->DrawLine(x1 * 10, y1 * 10, x2 * 10, y2 * 10);

			}
			else
			{
				pWind->DrawLine(x1 * 10, y1 * 10, x2 * 10, y1 * 10);
				pWind->DrawLine(x2 * 10, y1 * 10, x2 * 10, y2 * 10);

			}
			continue;
		}
		pWind->DrawLine(Connection_path[i].x1 * 10, Connection_path[i].y1 * 10, Connection_path[i].x2 * 10, Connection_path[i].y2 * 10);
	}
	for (int i = 0; i < (int)Connection_path.size(); i++)
	{
		int x1 = Connection_path[i].x1;
		int x2 = Connection_path[i].x2;
		int y1 = Connection_path[i].y1;
		int y2 = Connection_path[i].y2;
		if (x1 == x2)
		{
			if (arc[y2][x2] < -1)
			{
				grid[y1][x1] = ID;
				grid[y2][x2] = ID;
			}
			else 	for (int j = min(y1, y2); j <= max(y1, y2); j++)
			{
				grid[j][x1] = ID;
			}
		}
		else
		{
			if (arc[y2][x2] < -1)
			{
				grid[y1][x1] = ID;
				grid[y2][x2] = ID;

			}
			else for (int j = min(x1, x2); j <= max(x1, x2); j++)
			{

				grid[y1][j] = ID;
			}
		}
	}
	grid[Connection_path[0].y1][Connection_path[0].x1] = 0;
	grid[Connection_path[Connection_path.size() - 1].y2][Connection_path[Connection_path.size() - 1].x2] = 0;
}
window* Output::getwind(){
	return pWind;
}

void Output::setbuffer(bool a)
{
	pWind->SetBuffering(a);
}

void Output::updatebuffer()
{
	pWind->UpdateBuffer();
}

void Output::drawrect1(int x, int y, bool t)

{
	pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	if (t == true)   // not a connection
	{
		pWind->DrawRectangle(x, y, x + 60, y + 20);
		for (int i = x; i < x + 60; i += 10)
		{
			pWind->SetPen(LIGHTGREY, 1);
			pWind->DrawLine(i, y, i, y + 20);
		}
		for (int i = y; i <= y + 20; i += 10)
		{
			pWind->SetPen(LIGHTGREY, 1);
			pWind->DrawLine(x, i, x + 60, i);

		}
	}
	else
	{
		pWind->DrawRectangle(x - 10, y, x + 70, y + 18);
		for (int i = x - 10; i <= x + 70; i += 10)    // vertical
		{
			pWind->SetPen(LIGHTGREY, 1);
			pWind->DrawLine(i, y, i, y + 19);
		}
		// horiozontal

		pWind->SetPen(LIGHTGREY, 1);
		pWind->DrawLine(x - 10, y, x + 70, y);
		pWind->DrawLine(x - 10, y + 10, x + 70, y + 10);

	}
}
void Output::drawrect2(int x, int y)
{
	pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(x, y, x + 60, y + 40);
	for (int i = x; i < x + 60; i += 10)
	{
		pWind->SetPen(LIGHTGREY, 1);
		pWind->DrawLine(i, y, i, y + 40);
	}
	for (int i = y; i <= y + 40; i += 10)
	{
		pWind->SetPen(LIGHTGREY, 1);
		pWind->DrawLine(x, i, x + 60, i);

	}

}
image Output::storeimage()
{
	image i;
	pWind->StoreImage(i, 0, UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
	return i;
}
void Output::drawimage(image i)
{
	pWind->DrawImage(i, 0,UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
void Output::DrawMsg(string msg, int msgx, int msgy) const
{
	pWind->FlushKeyQueue();
	pWind->FlushMouseQueue();
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(DEEPPINK);
	pWind->DrawString(msgx, msgy, msg);
	pWind->UpdateBuffer();

}
void Output::DrawMsg1(string msg, int msgx, int msgy) const
{
	pWind1->FlushKeyQueue();
	pWind1->FlushMouseQueue();
	pWind1->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind1->SetPen(DEEPPINK);
	pWind1->DrawString(msgx, msgy, msg);

}
void Output::ChangeTitle1(string Title) const
{
	pWind1->ChangeTitle(Title);
}
void Output::del_pwind1()
{
	int x, m;
	pWind1->GetMouseClick(x, m);
	delete pWind1;
}
void Output::createtruthtablewindow()
{
	pWind1 = CreateWind(700, 550, 10, 10);
	ChangeTitle1("truth table window");
	pWind1->SetPen(BLACK, 3);
	pWind1->DrawLine(0, 30, 700, 30);  // horizontal
	pWind1->DrawLine(350, 0, 350, 550);
	DrawMsg1("The inputs : ", 5, 5);
	DrawMsg1("The outputs : ", 400, 5);
}
void Output::DrawConnection2(vector <GraphicsInfo> Connection_path, bool selected) const
{
	//TODO: Add code to draw connection
	if (selected == false)
	{

		pWind->SetPen(WHITE, 2);
		for (int i = 0; i < Connection_path.size(); i++)
		{
			pWind->DrawLine(Connection_path[i].x1 * 10, Connection_path[i].y1 * 10, Connection_path[i].x2 * 10, Connection_path[i].y2 * 10);
		}
	}
	if (selected == false)
	{

		pWind->SetPen(LIGHTGREY, 1);
		for (int i = 0; i < Connection_path.size(); i++)
		{
			pWind->DrawLine(Connection_path[i].x1 * 10, Connection_path[i].y1 * 10, Connection_path[i].x2 * 10, Connection_path[i].y2 * 10);
		}
	}
}
int ** Output::getgrid()
{
	return grid;
}
Output::~Output()
{
	for (int i = 0; i < 75; i++)
		delete grid[i];
	delete[] grid;
	delete pWind;
}
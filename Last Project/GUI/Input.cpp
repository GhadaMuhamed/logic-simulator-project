#include "Input.h"
#include "Output.h"
Input::Input(window* pW)
{
	gate = true;
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pOut)
{
	pWind->FlushKeyQueue();
	pWind->FlushMouseQueue();
	char in;
	keytype key = pWind->GetKeyPress(in);
	string s = "";
	bool exit = false;
	while (!exit)
	{
		if (key == ESCAPE) return "";
		else if (int(in) == 13) exit = true;
		else if (key == ASCII)
		{
			if (int(in) != 8)
				s += in;
			else if (s.size()>0) s.erase(s.size() - 1, 1);
			pOut->PrintMsg(s);
		}
		key = pWind->GetKeyPress(in);
	}
	return s;
}



void Input::ChangeToolBar(bool b)
{
	gate = b;
}

bool Input::getToolbar()
{
	return gate;
}


//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction()
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{

			if (gate)
			{
				if (x >= 61 && x <= 205 && y >= 70 && y <= 106) { return Gate_bar; }
				if (x >= 296 && x <= 452 && y >= 71 && y <= 107) {
					gate = false;
					return Actions_bar;
				}
				if (y > UI.ToolBarHeight - 40) return SELECT;
				//Check which Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				int ClickedItemOrder = (x / UI.ToolItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

				switch (ClickedItemOrder)
				{
				case ITM_AND2:       return ADD_AND_GATE_2;
				case ITM_OR2:        return ADD_OR_GATE_2;
				case ITM_NAND2:      return ADD_NAND_GATE_2;
				case ITM_NOR2:       return ADD_NOR_GATE_2;
				case ITM_XOR2:       return ADD_XOR_GATE_2;

				case ITM_XOR3:       return ADD_XOR_GATE_3;
				case ITM_XNOR2:      return ADD_XNOR_GATE_2;
				case ITM_NOR3:       return ADD_NOR_GATE_3;
				case ITM_NOT:        return ADD_INV;
				case ITM_BUFF:       return ADD_Buff;
				case ITM_LED:        return ADD_LED;
				case ITM_AND3: return ADD_AND_GATE_3;
				case ITM_SWITCH:      return ADD_Switch;
				case ITM_wire:        return ADD_CONNECTION;
				default:        return DSN_TOOL;	//A click on empty place in desgin toolbar
				}
			}
			else
			{
				if (x >= 61 && x <= 205 && y >= 70 && y <= 106) return Actions_bar;
				if (x >= 296 && x <= 452 && y >= 71 && y <= 107) { gate = true; return Gate_bar; }
				if (y > UI.ToolBarHeight - 40) return SELECT;
				int ClickedItemOrder2 = (x / UI.ToolItemWidth);
				if (y >= 0 && y < UI.ToolBarHeight)
				{
					switch (ClickedItemOrder2 + 14)
					{

					case ITM_undo:        return UNdO;
					case ITM_redo:        return REdO;

					case ITM_del:         return DEL;
					case ITM_label:       return ADD_Label;
					case ITM_edit:        return EDIT_Label;
					case ITM_exit:        return EXIT;
					case ITM_Cut:         return CUT;
					case ITM_Paste:       return PASTE;
					case ITM_Copy:        return COPY;
					case ITM_MultiS:      return MULTI_S;
					case ITM_save:        return SAVE;
					case ITM_load:        return LOAD;
					case ITM_move:        return MOVE;
					case ITM_Select:      return SELECT_item;
					case ITM_Sim:         return SIM_MODE;
					default:              return DSN_TOOL;	//A click on empty place in desgin toolbar
					}
				}

			}
		}

		//[2] User clicks on the drawing area
		if (y > UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a statement in the flowchart
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else if (UI.AppMode == SIMULATION)
	{
		if (y >= 0 && y <= UI.ToolBarHeight - 40)
		{
			if (x >= 20 && x <= 243) return circut_validation;
			else
				if (x >= 286 && x <= 489) return simualte_circut;
				else
					if (x >= 539 && x <= 782) return Create_TruthTable;
					else
						if (x >= 821 && x <= 1017) return circut_probing;
						else
							if (x >= 1070 && x <= 1249) return DSN_MODE;
							else return SIM_TOOL;
		}
		if (x >= 61 && x <= 205 && y >= 70 && y <= 106) return SIM_Bar;
		else if (y > UI.ToolBarHeight - 40 && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;
		}
		return STATUS_BAR;
	}
}

Input::~Input()
{
}

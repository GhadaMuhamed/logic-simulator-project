#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddANDgate3.h"
#include "Actions\AddBUFFERgate.h"
#include "Actions\AddINVERTER.h"
#include "Actions\AddLED.h"
#include "Actions\AddNANDgate2.h"
#include "Actions\AddNANDgate2.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddNORgate3.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddSWITCH.h"
#include "Actions\AddXNORgate2.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddXORgate3.h"
#include "Actions\Save.h"
#include "Actions\Load.h"
#include "Actions\AddLabel.h"
#include"Actions\Edit.h"
#include "Actions\select.h"
#include "Actions\multiselect.h"
#include "Actions\AddConnection.h"
#include "Actions\SimulateCircuit.h"
#include "Actions\UNDO.h"
#include "Actions\REDO.h"
#include "Actions\deleting.h"
#include "Actions\Copy.h"
#include "Actions\Cut.h"
#include "Actions\Past.h"
#include "Actions\Validation.h"
#include"Actions\move.h"
#include "Actions\Circuit_Probing.h"
#include "Actions\Truthtable.h"
#include <algorithm>
ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	sim=true;
	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
	UnDo(NULL);
	update=false;
	//OutputInterface->setbuffer(true);
}
////////////////////////////////////////////////////////////////////
Component* ApplicationManager::FindComp1(int x, int y)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (x >= CompList[i]->get_info().x1 && x <= CompList[i]->get_info().x2 && y >= CompList[i]->get_info().y1 && y <= CompList[i]->get_info().y2)
		{
			return CompList[i];
		}
	}
	return NULL;
}

Connection* ApplicationManager::find_conn(int x1, int y1)
{
	bool found = false;  bool enter = false;
	for (int i = 0; i < CompCount; i++)
	{
		Connection*con = is_connection(CompList[i]);
		if (con)
		{
			enter = true;
			Correct(x1, y1);
			x1/=10;
			y1/=10;
			vector <GraphicsInfo> getpath;
			getpath = con->get_ConnPath();
			for (int k = 0; k < getpath.size(); k++)
			{
				if ((x1 >= getpath[k].x1 && x1 <= getpath[k].x2 && y1 >= getpath[k].y1 && y1 <= getpath[k].y2) || (x1 <= getpath[k].x1 && x1 >= getpath[k].x2 && y1 <= getpath[k].y1 && y1 >= getpath[k].y2))
				{
					found = true;
					return con;
					break;
				}
			}
		}
		if (enter)   { x1 *= 10;     y1 *= 10; }
	}
	return NULL;
}
void ApplicationManager::cut()
{
	 int y = 0;
	//Print Action Message
	OutputInterface->PrintMsg("Cuting component");
	{for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->IsSelected())
		{
			cut_copy = CompList[i];

			cut_copy->setcut(true);
			Gate *ptr1;
			Connection **temp1;

			if (ptr1 = dynamic_cast <Gate*> (cut_copy))
			{

				temp1 = ptr1->Gate_oPin()->GetConn();
				for (int k = 0; k < ptr1->Gate_oPin()->NumOfConnection(); k++)
				{
					for (int h = 0; h < CompCount; h++)
					{
						if (CompList[h] == temp1[k])
						{
							temp1[k]->getDestPin()->set_connection(false);
							CompList[h]->clear(OutputInterface->getgrid());
								CompList[h] = CompList[CompCount - 1];
							CompList[CompCount - 1] = NULL;
							CompCount--;
						
							break;
						}
					}
					temp1[k] = temp1[ptr1->Gate_oPin()->NumOfConnection() - 1];
					temp1[k] = NULL;
					y = ptr1->Gate_oPin()->NumOfConnection();
					y--;
					ptr1->Gate_oPin()->setm_Conn(y);

				}
				
				for (int k = 0; k < ptr1->GetInNum(); k++)
				{
					InputPin* input = ptr1->getIpin(k);
					if (input != NULL)
					{
						for (int w = 0; w < CompCount; w++)
						{
							Connection* tmp = dynamic_cast<Connection*>(CompList[w]);
							if (tmp)
							{
								if (tmp->getDestPin() == input)
								{
																CompList[w]->clear(OutputInterface->getgrid());

									CompList[w] = CompList[CompCount - 1];
									CompList[ CompCount - 1] = NULL;
									 CompCount--;
									
								}
							}
						}
						input = NULL;
					}
				}
				
										CompList[i]->clear(OutputInterface->getgrid());

			CompList[i] = CompList[CompCount - 1];
			CompList[CompCount - 1] = NULL;
			CompCount--;
			}
			}

	}}
	
  	OutputInterface->ClearDrawingArea();
	OutputInterface->ClearStatusBar();
	}
void ApplicationManager::copy()
{
	OutputInterface->PrintMsg("Copying component");
		for(int i=0;i<CompCount;i++)
	{
		if(CompList[i]->IsSelected())
	   {
		 cut_copy= CompList[i];
		
		}
	}
	OutputInterface->ClearStatusBar();

}


bool ApplicationManager::check(GraphicsInfo GInfo)
{
	int** grid =OutputInterface->getgrid();
if (GInfo.x1 < 40 || GInfo.x2>1250 || GInfo.y1<UI.ToolBarHeight || GInfo.y2>UI.height - UI.StatusBarHeight - 10)
		return false;
	for (int i = (GInfo.x1 / 10); i <= (GInfo.x2 / 10) ; i++)
		for (int j = (GInfo.y1 / 10); j <= (GInfo.y2 / 10); j++)
		{
	if (grid[j][i]!=-1) return false;
		}
		for (int i=1;i<=3;i++)
		{
			if (grid[(GInfo.y1 / 10)-i][(GInfo.x1 / 10)-i]==0 || grid[(GInfo.y2 / 10)-i][(GInfo.x1 / 10)-i]==0 || grid[(GInfo.y1 / 10)-i][(GInfo.x2 / 10)-i]==0 || grid[(GInfo.y2 / 10)-i][(GInfo.x2 / 10)-i]==0)
				return false;
		}
	return true;
}
void ApplicationManager::paste()
{
		int Cx,Cy;	
		//Print Action Message
	 OutputInterface->PrintMsg("Click on the new position that you want to paste the component on ...");
	InputInterface->GetPointClicked(Cx, Cy);
	 OutputInterface->ClearStatusBar();
	 GraphicsInfo W;
	 Gate *ptr;
	 Correct(Cx, Cy);
	 int Len = UI.AND2_Width;
	 int Wdth = UI.AND2_Height;


	 W.x1 = Cx - Len / 2;
	 W.x2 = Cx + Len / 2;
	 W.y1 = Cy - Wdth / 2;
	 W.y2 = Cy + Wdth / 2;
	 
	 OutputInterface->ClearDrawingArea();

	 
	  if (!cut_copy) return;
	  if(!check(W))
		  {OutputInterface->PrintMsg("You can't paste the component here choose another place!");
	  return;}
	  if (ptr = dynamic_cast <Gate*> (cut_copy))
		  {

			  cut_copy->Sel();
			 

			   if (cut_copy->getcut())        // cut 
				  {
					  cut_copy->setcut(false);
					  cut_copy->setinfo(W);
					  AddComponent(cut_copy);
			   }
			   else //Copy 
			   {
			    AddComponent(  ptr->COPY(W));
				 ptr->COPY(W)->setinfo(W);
					
			   }			   
	 }
}
int ApplicationManager::num_of_sw()
{
	int number_of_switchs = 0;
	for (int i = 0; i < CompCount; i++)     // first knowing the number of switchs
	{
		SWITCH * s = dynamic_cast<SWITCH *>(CompList[i]);
		if (s)  number_of_switchs++;
	}
	return number_of_switchs;
}
void ApplicationManager::set_label(Component* c, string s)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] == c)
		{
			CompList[i]->setlabel(s);
			break;
		}
	}
}
void ApplicationManager::Deleteing()
{

	int y = 0;
	
	

	//Print Action Message
	OutputInterface->PrintMsg("Deleting componant...");
	bool exit = false;
	
	while (!exit)

	{
		exit = true;
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i]->IsSelected())
			{
				exit = false;
				Gate *ptr;
				Connection **temp;

				if (ptr = dynamic_cast <Gate*> (CompList[i]))
				{

					temp = ptr->Gate_oPin()->GetConn();
					int f = ptr->Gate_oPin()->NumOfConnection();
					for (int k = 0; k < f; k++)
					{
						for (int h = 0; h < CompCount; h++)
						{
							if (CompList[h] == temp[k])
							{
								temp[k]->getDestPin()->set_connection(false);
								CompList[h]->clear(OutputInterface->getgrid());

								CompList[h] = CompList[CompCount-1];
								CompList[CompCount-1] = NULL;
								CompCount--;								
								
								break;
							}
						}
						temp[k] = temp[ptr->Gate_oPin()->NumOfConnection()-1];
						temp[k] = NULL;
						y = ptr->Gate_oPin()->NumOfConnection();
						y--;
						ptr->Gate_oPin()->setm_Conn(y);

					}

					for (int k = 0; k < ptr->GetInNum(); k++)
					{
						InputPin* input = ptr->getIpin(k);
						if (input != NULL)
						{
							for (int w = 0; w <  CompCount; w++)
							{
								Connection* tmp = dynamic_cast<Connection*>(CompList[w]);
								if (tmp)
								{
									if (tmp->getDestPin() == input)
									{				CompList[w]->clear(OutputInterface->getgrid());

										CompList[w] =CompList[ CompCount - 1];
										CompList[CompCount-1] = NULL;
										CompCount--;
										
										input->set_connection(false);
									}
								}
							}
						}
					}

				}
				else 
				{
					Connection* c=dynamic_cast<Connection*>(CompList[i]);
					c->getDestPin()->set_connection(false);
					c->getSourcePin()->DelConnection(c);
				}				
				CompList[i]->clear(OutputInterface->getgrid());
				CompList[i] = CompList[CompCount- 1];
				CompList[CompCount - 1] = NULL;
				CompCount--;
				
			}

		}
	}
	OutputInterface->ClearDrawingArea();
	OutputInterface->ClearStatusBar();

}


int ApplicationManager::counting_selected()
{
	int numofselected = 0;
	for (int i = 0; i < CompCount; i++)
	{
		Connection* con = dynamic_cast<Connection*>(CompList[i]);
		if (CompList[i]->IsSelected() == true && !con)
		{
			numofselected++;
		}

	}
	return numofselected;
}
Component** ApplicationManager::selectedarr(){

	Component**s = new Component*[100];
	int co = 0;

	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->IsSelected() == true)
		{
			s[co] = CompList[i];
			co++;
		}
	}
	return s;
}
Component*ApplicationManager::selectedcomp()
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->IsSelected() == true)
			return CompList[i];
	}
	return NULL;
}
Component* ApplicationManager::set_label_tocon(Connection*cc){
	for (int i = 0; i < CompCount; i++)
	{
		Connection*con = is_connection(CompList[i]);
		if (con == cc)
		{
			return CompList[i];
			break;
		}
	}
}
void ApplicationManager::AddComponent(Component* pComp)
{
		int** grid=OutputInterface->getgrid();
	    CompList[CompCount++] = pComp;	
		pComp->add(grid);
}

bool ApplicationManager::getlabel(Component *c)
{
	for (int i = 0; i < CompCount; i++)
	{
		Connection* con = is_connection(CompList[i]);
		if (CompList[i] == c && con)
		{
			if (CompList[i]->getlabel() == "")
			{
				return true;  break;
			}
			else {
				return false; break;
			}
		}
		else if (CompList[i] == c)
		{
			if (CompList[i]->getlabel() == "")
			{
				return true;  break;
			}
			else {
				return false; break;
			}
		}
	}
	return NULL;
}
void ApplicationManager::setxy_label(int x, int y, Component*c)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] == c)
		{
			CompList[i]->setx(x);
			CompList[i]->sety(y);
			break;
		}
	}
}
Connection * ApplicationManager::is_connection(Component*c)
{
	Connection * con = dynamic_cast<Connection *>(c);
	return con;

}
////////////////////////////////////////////////////////////////////
void ApplicationManager::setSim(bool a)
{
	sim=a;
}

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction(); 	
}
Component*  ApplicationManager::getcut_copy()
{
	return cut_copy;
}
void ApplicationManager::setcompcount(int x)
{
	CompCount = x;
}

void ApplicationManager::setcut_copy(Component* T)
{
	cut_copy = T;
}

////////////////////////////////////////////////////////////////////
Component* ApplicationManager::FindComp(int x, int y)
{
	Correct(x, y);
	for (int i = 0; i < CompCount; i++)
	{
		Connection* con = dynamic_cast<Connection*>(CompList[i]);
		if (con)
		{
			vector <GraphicsInfo> getpath;
			getpath = con->get_ConnPath();
			for (int k = 0; k < getpath.size(); k++)
			{
				GraphicsInfo g = getpath[k];
				if (g.x1 == g.x2)
				{
					if (x == g.x1*10 && y >= min(g.y1, g.y2)*10 && y <= max(g.y1, g.y2)*10)
						return CompList[i];
				}
				else if (g.y1 == g.y2)
				{
					if (y == g.y1*10 && x >= min(g.x1, g.x2)*10 && x <= max(g.x1, g.x2)*10)
						return CompList[i];
				}
			}
		}
				
		else if (x >= CompList[i]->get_info().x1 && x <= CompList[i]->get_info().x2 && y >= CompList[i]->get_info().y1 && y <= CompList[i]->get_info().y2)
		{
			return CompList[i];
		}
	}
	return NULL;
}

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			break;
		case ADD_AND_GATE_3:
			pAct = new AddANDgate3(this);
			break;
		case ADD_NOR_GATE_3:
			pAct = new AddNORgate3(this);
			break;
		case ADD_XOR_GATE_3:
			pAct = new AddXORgate3(this);
			break;
		case Actions_bar:
			OutputInterface->CreateActionsToolBar();
			break;
		case Gate_bar:
			OutputInterface->CreateDesignToolBar();
			break;
		case ADD_LED:
			pAct = new AddLED(this);
			break;
		case ADD_XNOR_GATE_2:
			pAct = new AddXNORgate2(this);
			break;
		case ADD_Switch:
			pAct = new AddSWITCH(this);
			break;
		case ADD_INV:
			pAct = new AddINVERTER(this);
			break;
		case ADD_NAND_GATE_2:
			pAct = new AddNANDgate2(this);
			break;
		case ADD_NOR_GATE_2:
			pAct = new AddNORgate2(this);
			break;
		case ADD_OR_GATE_2:
			pAct = new AddORgate2(this);
			break;
		case ADD_XOR_GATE_2:
			pAct = new AddXORgate2(this);
			break;
		case SELECT_item:
			pAct = new Select(this);
			break;
		case MULTI_S:
			pAct = new multiselect(this);
			break;
		case simualte_circut:
			SimulateCirc();
			break;
		case MOVE:
			pAct = new moveing(this);
			break;
		case SIM_MODE:
		{	InputInterface->ChangeToolBar(true);
		    OutputInterface->CreateSimulationToolBar(); 
		    pAct= new Validation(this);
		}
			break;
		case DEL:
			pAct = new deleting(this);
			break;
		case ADD_Label:
			pAct = new AddLabel(this);
			pAct->ReadActionParameters();
			break;
		case CUT:
			pAct = new Cut(this);
			break;

		case COPY:
			pAct = new Copy(this);
			break;
		case DSN_MODE:
		{
			sim=true;
			SimulateCircuit::setfeed(false);
			OutputInterface->CreateDesignToolBar();
		break;
		}
		case circut_validation:
			pAct = new Validation(this);
			break;
		case SAVE:
			pAct = new Save(this);
		break;
		case UNdO:
			pAct = new UNDO(this); 	
			break;
			case circut_probing:
			pAct = new Circuit_Probing(this);
			break;
					case Create_TruthTable:
			pAct = new Truthtable(this);
			OutputInterface->createtruthtablewindow();
			break;
		case REdO:
			pAct = new REDO(this); 
			break;
		case SELECT:
			simulate();
			break;
		case LOAD:
			pAct = new Load(this);
			break; 
		case ADD_Buff:
			pAct = new AddBUFFERgate(this);
			break;
		case ADD_CONNECTION:
			pAct = new AddConnection(this);
			break;
		case EDIT_Label:
			pAct = new Edit(this);
				break;
		case PASTE:
			pAct = new Past(this);
			break;
		case EXIT:
			///TODO: create ExitAction here
			break;
	}
	if (pAct)
	{
		pAct->Execute();
			UnDo(pAct);
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::cmp_del()
{
	OutputInterface->ClearGrid();
	update=true;
	cut_copy = NULL;
	for (int i = 0; i < CompCount; i++)
	{
		delete CompList[i];
		CompList[i] = NULL;
	}
	CompCount = 0;
}

void ApplicationManager::Correct(int&x, int&y)
{
	if (x % 10 >= 5)
	{
		int temp = x / 10;
		x = temp * 10 + 10;
	}
	else {
		int temp = x / 10;
		x = temp * 10;
	}
	if (y % 10 >= 5)
	{
		int temp = y / 10;
		y = temp * 10 + 10;
	}
	else {
		int temp = y / 10;
		y = temp * 10;
	}	
}

void ApplicationManager::load(ifstream& fin)
{
	if (fin.eof()) return;
	int size;
	fin >> size;
	if (size == -1) return;
	string name;
	string label;
	int ID;
	int mx = -1;
	GraphicsInfo GI;
	fin >> name; // Name ,, ID ,, Label(noname) ,, graphics info
	while (name != "Connections")
	{

		fin >> ID >> label >> GI.x1 >> GI.y1 >> GI.x2 >> GI.y2;
		mx = max(mx, ID);
		if (name == "AND2")
		{
			AND2 *pA = new AND2(GI, AND2_FANOUT);
			pA->load(label, ID);
			this->AddComponent(pA);
		}
		else if (name == "AND3")
		{
			AND3 *pA = new AND3(GI, AND2_FANOUT);
			pA->load(label, ID);
			this->AddComponent(pA);
		}
		else if (name == "NOR2")
		{
			NOR2 *pA = new NOR2(GI, AND2_FANOUT);
			pA->load(label, ID);
			this->AddComponent(pA);
		}
		else if (name == "NOR3")
		{
			NOR3 *pA = new NOR3(GI, AND2_FANOUT);
			pA->load(label, ID);
			this->AddComponent(pA);
		}
		else if (name == "BUFFER")
		{
			BUFFER *pA = new BUFFER(GI, AND2_FANOUT);
			pA->load(label, ID);
			this->AddComponent(pA);
		}
		else if (name == "INVERTER")
		{
			INVERTER *pA = new INVERTER(GI, AND2_FANOUT);
			pA->load(label, ID);
			this->AddComponent(pA);
		}
		else if (name == "LED")
		{
			LED *pA = new LED(GI);
			pA->load(label, ID);
			this->AddComponent(pA);
		}
		else if (name == "NAND2")
		{
			NAND2 *pA = new NAND2(GI, AND2_FANOUT);
			pA->load(label, ID);
			this->AddComponent(pA);
		}
		else if (name == "OR2")
		{
			OR2 *pA = new OR2(GI, AND2_FANOUT);
			pA->load(label, ID);
			this->AddComponent(pA);
		}
		else if (name == "SWITCH")
		{
			SWITCH *pA = new SWITCH(GI, AND2_FANOUT);
			pA->load(label, ID);
			this->AddComponent(pA);
		}
		else if (name == "XNOR2")
		{
			XNOR2 *pA = new XNOR2(GI, AND2_FANOUT);
			pA->load(label, ID);
			this->AddComponent(pA);
		}
		else if (name == "XOR2")
		{
			XOR2 *pA = new XOR2(GI, AND2_FANOUT);
			pA->load(label, ID);
			this->AddComponent(pA);
		}
		else if (name == "XOR3")
		{
			XOR3 *pA = new XOR3(GI, AND2_FANOUT);
			pA->load(label, ID);
			this->AddComponent(pA);
		}
		fin >> name;
	}
	mx++;
	int src_id, dst_id, num_ofPin;
	fin >> src_id;
	Component::set_IDCnt(mx);
	while (src_id != -1)
	{
		
		fin >> dst_id >> num_ofPin >> name;
		Component* temp1 = NULL;
		Component* temp2 = NULL;
		int input=-1;
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i]->get_ID() == src_id)
			{
				temp2 = CompList[i];
			}
			if (CompList[i]->get_ID() == dst_id)
			{
				temp1 = CompList[i];
			}

		}
		GI.x1 = temp1->get_info().x1;
		GI.x1 /= 10;
		GI.x2 = temp2->get_info().x2;
		GI.x2 /= 10;
		GI.y2 = temp2->get_info().y1 + UI.AND2_Height / 2;
		GI.y2 /= 10;
		Gate* G1 = dynamic_cast<Gate*>(temp1);
		Gate* G2 = dynamic_cast<Gate*>(temp2);
		int y2 = G1->get_info().y1 + UI.AND2_Height / 2;
		if (num_ofPin == 1 )
		{
			if (G1->GetInNum() == 1)
				GI.y1 = y2 / 10;
			else GI.y1 = (y2 - 10) / 10;
		}
		else if (num_ofPin == 2 && G1->GetInNum() == 3)
		{
			GI.y1= y2 / 10;
		}
		else if (num_ofPin == 2 && G1->GetInNum() == 2)
		{
			GI.y1 = (y2 / 10 + 1);
		}
		else GI.y1 = (y2 / 10 + 1);
		Connection* pA = new Connection(GI, G2->Gate_oPin(), G1->getIpin(num_ofPin - 1));
		this->AddComponent(pA);
		pA->load(name,ID);
		fin >> src_id;
	}
}

void ApplicationManager::save(ofstream& fout)
{
	fout << CompCount << endl;
	for (int i = 0; i < CompCount; i++)
	{
		Connection* c = dynamic_cast<Connection*>(CompList[i]);
		if (!c)
		{
			CompList[i]->save(fout);
		}
	}
	fout << "Connections" << endl;
	for (int i = 0; i < CompCount; i++)
	{
		Connection* c = dynamic_cast<Connection*>(CompList[i]);
		if (c)
		{
			c->save(fout);
		}
	}
	fout << -1 << endl;
}

void ApplicationManager::replaceComponent(Component*p, int i, ApplicationManager *pApp)
{
	for (int k = 0; k < CompCount; k++)
	{
		if (k == i)
		{
			Output* pOut = pApp->GetOutput();
			Connection* Conn = dynamic_cast<Connection*>(CompList[k]);
			pOut->DrawConnection2(Conn->get_ConnPath());
			delete CompList[k];
					break;
			}
		
	}
}
void ApplicationManager::simulate()
{
	if (UI.AppMode == SIMULATION)
	{
		if(!sim) {OutputInterface->PrintMsg("This Circuit is not valid and can't be simulated ,, Please return back to design mode"); return ;}
		int x, y;
		OutputInterface->PrintMsg("Double click on the switch you want to change it ..");
		InputInterface->GetPointClicked(x, y);
		Component* com = FindComp(x, y);
		SWITCH* swi = dynamic_cast<SWITCH*> (com);
		if (swi)
		{
			swi->change();
			SimulateCirc();
			
		}
	}
	else return;
}
void ApplicationManager::SimulateCirc()
{

for (int i=0;i<CompCount;i++)
			{
				if (CompList[i]->GetOutPinStatus()==-1)
			{
				Action* a = new SimulateCircuit(this,CompList[i]);
				a->Execute();
				delete a;
				a=NULL;
			}
			}
			for (int i=0;i<CompCount;i++)
			{
				CompList[i]->uncalc();
		    }
}
void ApplicationManager::UpdateInterface()
{
	if (update)
	{OutputInterface->ClearDrawingArea();update=false;}
		for(int i=0; i<CompCount; i++)
		{	CompList[i]->Draw(OutputInterface);
	}
			OutputInterface->updatebuffer();


}
void ApplicationManager::UnDo(Action* pAct)
{
	if (pAct == NULL)
	{
		string s = UNDO::getname();
	    Save* a = new Save(this, s);
		delete a;
		a=NULL;
	    return;
     }
	if (UI.AppMode != DESIGN || (dynamic_cast<UNDO*>(pAct)) || (dynamic_cast<REDO*>(pAct)) || (dynamic_cast<Copy*>(pAct)) || (dynamic_cast<Select*>(pAct))|| (dynamic_cast<multiselect*>(pAct)) || (dynamic_cast<Save*>(pAct))) return;
	string s = UNDO::getname();
	if (s == "") return;
	Save* a = new Save(this, s);
	delete a;
		a=NULL;
}

////////////////////////////////////////////////////////////////////
int ApplicationManager::GetCount()
{
	return CompCount;
}
void ApplicationManager::SetCount(int x)
{
	CompCount = x;
}
Component** ApplicationManager::GetComp()
{
	return CompList;
}
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}
////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	UNDO::DeleF();
	OutputInterface->setbuffer(false);
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}
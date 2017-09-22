#include "Edit.h"
# include <vector>
#include "..\ApplicationManager.h"
#include "..\Components\Gate.h"
#include "..\Components\OutputPin.h"
#include "..\Components\InputPin.h"
#include <algorithm>
using namespace std;

Edit::Edit(ApplicationManager *pApp) :Action(pApp)
{
	
}

void Edit::ReadActionParameters(){

}
void Edit::Execute()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("editing.. , click on the component you want to edit your label to..");
	int x1, y1;
	pIn->GetPointClicked(x1, y1);
	pOut->ClearStatusBar();
	bool found = false;
	Component*temp;
	Component* co = pManager->FindComp1(x1, y1);
	Connection *con = NULL;
	if (co == NULL)
	{
		con = pManager->find_conn(x1, y1);
		temp = pManager->set_label_tocon(con);
	}

		if (co != NULL && !con)
		{
			found = true;
			pOut->drawrect1(co->get_info().x1, co->get_info().y1 - 20, true);
			pOut->PrintMsg("Now enter your label. maximum six characters..");
			string s = pIn->GetSrting(pOut);
			s = s.substr(0, 6);
			pOut->DrawMsg(s, co->get_info().x1, (co->get_info().y1 - 20));
			co->setlabel(s);
			
		}

		else if (con)
		{
			found = true;
			pOut->PrintMsg("to edit the label press 1 , otherwise press 2");
			string s2 = pIn->GetSrting(pOut);
			if (s2 == "1")
			{
				if (!pManager->getlabel(temp))       // change the old label
				{
					//pOut->ClearDrawingArea();
					
		         	pOut->drawrect1(temp->getx(), temp->gety(), false);
					pOut->PrintMsg("Now enter your label.maximum6 characters..");
					string s = pIn->GetSrting(pOut);
					s = s.substr(0, 6);

					pOut->DrawMsg(s, temp->getx(), temp->gety());
					temp->setlabel(s);
					//pManager->UpdateInterface();
					
				}
				else          // no label men el awl ka2ny ba add label
				{
					pOut->PrintMsg("please click on the new position of the label");
					int x2, y2;

					pIn->GetPointClicked(x2, y2);
					pOut->ClearStatusBar();
					pOut->PrintMsg("Now enter your label.maximum6 characters..");
					string s = pIn->GetSrting(pOut);
					s = s.substr(0, 6);
					pOut->DrawMsg(s, x2, y2-15);

					pManager->setxy_label(x2, y2-15, temp);
					temp->setlabel(s);
				
				}
			}
			else  // change el source or el des.
			{
				pOut->ClearStatusBar();
				con->getSourcePin()->DelConnection(con);  // deleting the old connection from the outputpin array..
				con->getDestPin()->set_connection(false);    // removing the old input pin ..
				string temp11;   bool fee = false;
				if (!pManager->getlabel(temp))
				{
					fee = true;
					pOut->drawrect1(temp->getx(), temp->gety(), false);
					temp11 = temp->getlabel();
				}
				int x3, x4, y3, y4;
				pIn->GetPointClicked(x3, y3);
				pIn->GetPointClicked(x4, y4);
				GraphicsInfo GInfo;
				Output* pOut = pManager->GetOutput();
				Component* temp1 = NULL;
				Component* temp2 = NULL;
				temp1 = pManager->FindComp(x3, y3);
				temp2 = pManager->FindComp(x4, y4);
				Gate* inGate = dynamic_cast<Gate*>(temp1);
				Gate* ouGate = dynamic_cast<Gate*>(temp2);
				if (inGate == NULL || ouGate == NULL)
				{
					pOut->PrintMsg("You should click on a source and destination pin !");
					return;
				}
				GraphicsInfo inputgate = inGate->get_info();
				GraphicsInfo outputgate = ouGate->get_info();
				if (x3 >= (inputgate.x1 + UI.AND2_Width / 2))
				{
					if (x4 < (outputgate.x1 + UI.AND2_Width / 2))
					{
						swap(inGate, ouGate);
						swap(inputgate, outputgate);
						swap(x3, x4);
						swap(y3, y4);
					}
					else { pOut->PrintMsg("You should click on a source and destination pin !"); return; }

				}
				else if (x4 < (outputgate.x1 + UI.AND2_Width / 2))
				{
					pOut->PrintMsg("You should click on a source and destination pin !");
					return;
				}
				if (ouGate->GetOutPinStatus() == -1 || inGate->GetInputPinStatus(0) == -1)
				{
					pOut->PrintMsg("You should click on a source and destination pin !");
					return;
				}
				int num;
				if (inGate->GetInNum() == 1) { num = 1; }
				else {
					int useless = 0;
					pManager->Correct(y1, useless);

					if (y3 > inputgate.y1 + (UI.AND3_Height / 2))
					{
						if (inGate->GetInNum() == 3)
							num = 3;
						else num = 2;
					}
					else if (y3 < inputgate.y1 + (UI.AND3_Height / 2))
						num = 1;
					else num = 2;
				}
				if (temp1 == NULL || temp2 == NULL || temp2->GetOutPinStatus() == -1 || temp1->GetInputPinStatus(0) == -1)
				{
					pOut->PrintMsg("You should click on a source output pin and a destination input pin !");
					return;
				}

				OutputPin* ou = ouGate->Gate_oPin();
				InputPin* In = inGate->getIpin(num - 1);
				GInfo.x1 = inputgate.x1 / 10;
				if (num == 1)
				{
					if (inGate->GetInNum() == 1)
					{
						GInfo.y1 = (inputgate.y1 + UI.AND2_Height / 2) / 10;
					}
					else
					{
						GInfo.y1 = ((inputgate.y1 + UI.AND2_Height / 2) - 10) / 10;
					}
				}
				else if (num == 2)
				{
					if (inGate->GetInNum() == 2)
						GInfo.y1 = ((inputgate.y1 + UI.AND2_Height / 2) + 10) / 10;
					else 			GInfo.y1 = (inputgate.y1 + UI.AND2_Height / 2) / 10;
				}
				else GInfo.y1 = ((inputgate.y1 + UI.AND2_Height / 2) + 10) / 10;
				GInfo.x2 = outputgate.x2 / 10;
				GInfo.y2 = (outputgate.y1 + UI.AND2_Height / 2) / 10;
				if (In->IsConnected())
				{
					pOut->PrintMsg("This pin is already connected !");
					return;
				}

				if (!(ou->ConnectTo(con)))
				{
					In->set_connection(false);
					pOut->PrintMsg("You can't add connection to this output pin !");
					return;
				}
				con->setinfo(GInfo);
				pOut->ClearDrawingArea();
				pManager->UpdateInterface();
				if (fee == true)
				{
					pOut->PrintMsg("click on the new position for your old label ...");
					int x2, y2;
					pIn->GetPointClicked(x2, y2);
					pOut->DrawMsg(temp11, x2, y2);
					pManager->set_label(temp, temp11);
					pManager->setxy_label(x2, y2, temp);
				}
		

			}
		}

	if (found == false)
	{
		pOut->PrintMsg("component not found !!!! , click to continue ...");
		pIn->GetPointClicked(x1, y1);
	}
	pOut->ClearStatusBar();

}

void Edit::Undo()
{}

void Edit::Redo()
{}


Edit::~Edit()
{
}

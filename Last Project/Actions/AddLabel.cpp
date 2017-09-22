#include "AddLabel.h"
# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include "AddConnection.h"
#include "../ApplicationManager.h"
#include "../Components/Gate.h"
#include "../Components/OutputPin.h"
#include "../Components/InputPin.h"
using namespace std;


AddLabel::AddLabel(ApplicationManager *pApp) :Action(pApp)
{
	
}

void AddLabel::ReadActionParameters(){

}

void AddLabel::Execute()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int x1, y1;

	pOut->PrintMsg("Adding label , click on the component you want to add your label to....");
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
			if (pManager->getlabel(co))       // adding label for the first time.
			{

				pOut->PrintMsg("Now enter your label. maximum six characters..");
				string s = pIn->GetSrting(pOut);
				s = s.substr(0, 6);
				pOut->DrawMsg(s, co->get_info().x1, (co->get_info().y1 - 20));
				co->setlabel(s);
				
			}
			else {

				pOut->PrintMsg(" this component has already a label ... ,click to continue.....");
				pIn->GetPointClicked(x1, y1);
			
			}
		}
		else if (pManager->getlabel(temp) && con)     // adding label to connection for the first time.
		{
			found = true;
			pOut->PrintMsg("Now enter your label.maximum6 characters..");
			string s = pIn->GetSrting(pOut);
			s = s.substr(0, 6);
			pOut->DrawMsg(s, x1, y1 - 20);
			pManager->setxy_label(x1, y1 - 20, temp);
			temp->setlabel(s);
			
		}
		

	if (found == false)
	{
		pOut->PrintMsg(" invalid use :( ,click to continue... ");
		pIn->GetPointClicked(x1, y1);
	}
	pOut->ClearStatusBar();
}
void AddLabel::Undo()
{}

void AddLabel::Redo()
{}

AddLabel::~AddLabel()
{
}


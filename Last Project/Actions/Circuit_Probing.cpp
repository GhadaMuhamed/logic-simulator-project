#include "Circuit_Probing.h"
#include "../ApplicationManager.h"
#include "../Components\Gate.h"
#include"../Components\BUFFER.h"
#include"../Components\INVERTER.h"
#include"../Components\LED.h"
#include "../Components\Connection.h"
Circuit_Probing::Circuit_Probing(ApplicationManager *pApp) :Action(pApp)
{
}


void Circuit_Probing::Execute()
{

	pManager->SimulateCirc();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Circut Probing");
	pIn->GetPointClicked(x1, y1);
	Component* com = pManager->FindComp(x1, y1);
	if (com == NULL){
		pOut->PrintMsg("you should press on outpin or inputpin......");
	}

	
	else{

		Connection* con = dynamic_cast<Connection*>(com);
		if (!con)
		{//it's outpin
			pManager->Correct(x1, y1);
			if ((x1 ==com->get_info().x2) && (y1 == (com->get_info().y1) + 20))
			{
				
				STATUS s = ((Gate*)com)->Gate_oPin()->getStatus();
				if (s == LOW)
					pOut->PrintMsg(" It's Low");
				if (s == HIGH)
					pOut->PrintMsg(" It's High");
			}
			//it first inputpin 
			else	if ((x1 == com->get_info().x1) && (y1 == (com->get_info().y1) +10))
			{
				STATUS s = ((Gate*)com)->getIpin(0)->getStatus();
				if (s == LOW)
					pOut->PrintMsg(" It's Low");
				if (s == HIGH)
					pOut->PrintMsg(" It's High");
			}
			//it med input pin
			else	if ((x1 == com->get_info().x1) && (y1 == (com->get_info().y1) + 20))
			{
				if (dynamic_cast<INVERTER*>(com))
				{
					STATUS s = ((Gate*)com)->getIpin(0)->getStatus();
					if (s == LOW)
						pOut->PrintMsg(" It's Low");
					if (s == HIGH)
						pOut->PrintMsg(" It's High");
				}
				else if (dynamic_cast<BUFFER*>(com))
				{
					STATUS s = ((Gate*)com)->getIpin(0)->getStatus();
					if (s == LOW)
						pOut->PrintMsg(" It's Low");
					if (s == HIGH)
						pOut->PrintMsg(" It's High");
				}
				else if (dynamic_cast<LED*>(com))
				{
					STATUS s = ((Gate*)com)->getIpin(0)->getStatus();
					if (s == LOW)
						pOut->PrintMsg(" It's Low");
					if (s == HIGH)
						pOut->PrintMsg(" It's High");
				}
				else	{
					STATUS s = ((Gate*)com)->getIpin(1)->getStatus();
					if (s == LOW)
						pOut->PrintMsg(" It's Low");
					if (s == HIGH)
						pOut->PrintMsg(" It's High");
				}
			}
			//its last input pin 
			else	if ((x1 == com->get_info().x1) && (y1 == (com->get_info().y1) + 30))
			{
				if (((Gate*)com)->GetInNum() == 2)
				{


					STATUS s = ((Gate*)com)->getIpin(1)->getStatus();
					if (s == LOW)
						pOut->PrintMsg(" It's Low");
					if (s == HIGH)
						pOut->PrintMsg(" It's High");
				}
				else if (((Gate*)com)->GetInNum() == 3)
				{


					STATUS s = ((Gate*)com)->getIpin(2)->getStatus();
					if (s == LOW)
						pOut->PrintMsg(" It's Low");
					if (s == HIGH)
						pOut->PrintMsg(" It's High");
				}
			}
			

		}
		if (con)
		{
		int v = con->GetOutPinStatus();
			if (v == 0)
				pOut->PrintMsg(" This connection is  Low");
			if (v == 1)
				pOut->PrintMsg(" This connection is High");
		}
	}
	//pOut->PrintMsg(" invaild");
}


void Circuit_Probing::ReadActionParameters(){}

void Circuit_Probing::Undo(){}
void  Circuit_Probing::Redo(){}
Circuit_Probing::~Circuit_Probing(void)
{
}

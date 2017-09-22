#include "AddConnection.h"
#include "..\ApplicationManager.h"
#include "..\Components\Gate.h"
AddConnection::AddConnection(ApplicationManager *pApp):Action(pApp)
{
}

void AddConnection::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//Print Action Message
	pOut->PrintMsg("Adding Connection ,, click on a source and destination pin ... ");
	//Wait for User Input
	pIn->GetPointClicked(x1, y1);
	pIn->GetPointClicked(x2, y2);
	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddConnection::Execute()
{

	ReadActionParameters();
	GraphicsInfo GInfo; 
	Output* pOut = pManager->GetOutput();
	Component* temp1=NULL;
	Component* temp2=NULL;
	temp1 = pManager->FindComp(x1, y1);
	temp2 = pManager->FindComp(x2, y2);
	Gate* inGate = dynamic_cast<Gate*>(temp1);
	Gate* ouGate = dynamic_cast<Gate*>(temp2);
	if (inGate == NULL || ouGate == NULL)
	{
		pOut->PrintMsg("You should click on a source and destination pin !");
		return;
	}
	GraphicsInfo inputgate = inGate->get_info();
	GraphicsInfo outputgate = ouGate->get_info();
	if (x1 >= (inputgate.x1 + UI.AND2_Width / 2))
	{
		if (x2 < (outputgate.x1 + UI.AND2_Width / 2))
		{
			swap(inGate, ouGate);
			swap(inputgate, outputgate);
			swap(x1, x2);
			swap(y1, y2);
		}
		else { pOut->PrintMsg("You should click on a source and destination pin !"); return; }

	}
	else if (x2 < (outputgate.x1 + UI.AND2_Width / 2))
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

		if (y1 > inputgate.y1 + (UI.AND3_Height / 2))
		{
			if (inGate->GetInNum() == 3)
				num = 3;
			else num = 2;
		}
		else if (y1 < inputgate.y1 + (UI.AND3_Height / 2))
			num = 1;
		else num = 2;
	}
	OutputPin* ou = ouGate->Gate_oPin();
	InputPin* In = inGate->getIpin(num-1);
	GInfo.x1 = inputgate.x1 / 10;
	if (num == 1 )
	{
		if (inGate->GetInNum() == 1)
		{
			GInfo.y1 = (inputgate.y1 + UI.AND2_Height / 2) / 10;
		}
		else
		{
			GInfo.y1 =( (inputgate.y1 + UI.AND2_Height / 2) - 10) / 10;
		}
	}
	else if (num == 2)
	{
		if (inGate->GetInNum() == 2)
			GInfo.y1 = ((inputgate.y1 + UI.AND2_Height / 2) + 10 )/ 10;
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
	
	Connection *pA = new Connection(GInfo, ou, In);
	if (!(ou->ConnectTo(pA)))
	{
		In->set_connection(false);
		pOut->PrintMsg("You can't add connection to this output pin !");
		delete pA;
		pA=NULL;
		return;	
	}
	pManager->AddComponent(pA);

}
void AddConnection::Undo()
{}

void AddConnection::Redo()
{}

AddConnection::~AddConnection()
{
}

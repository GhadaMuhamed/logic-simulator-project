#include "Validation.h"
#include "..\ApplicationManager.h"
#include "..\Components\Gate.h"
#include "..\Components\Connection.h"

Validation::Validation(ApplicationManager *pApp) :Action( pApp)
{
}


void Validation::Execute()
{ 
	
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	

	//Print Action Message
	pOut->ClearStatusBar();
	pOut->PrintMsg("Circut validation");

	int x=pManager->GetCount();
	Component **P=pManager->GetComp();
	 Gate *ptr=NULL;
	 	Connection *temp=NULL;
	
		for (int i = 0; i < x; i++)
		{
			if (ptr = dynamic_cast <Gate*> (P[i]))
			{
				int t = ptr->Gate_oPin()->NumOfConnection();
				int w = ptr->GetInNum();
				int h = 0;
				for (int r = 0; r < w; r++)
				{
					InputPin* input = ptr->getIpin(r);
					if (input->IsConnected())
					{
						h++;
					}
				}
				if (w != h || (t == 0 && ptr->GetOutPinStatus() != -1))
				{
								    pOut->ClearStatusBar();
					pOut->PrintMsg("Circut is not valid and can't be simulated !");
					pManager->setSim(false);
					break;
				}
				else {
					pOut->ClearStatusBar();
                    pOut->PrintMsg("Circut is  valid");}
			}
		}


}


void Validation::ReadActionParameters(){}
	 
void  Validation :: Undo(){}
void  Validation:: Redo(){}
Validation::~Validation(void)
{
}

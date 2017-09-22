#include"multiselect.h"

multiselect::multiselect(ApplicationManager *pApp) :Action(pApp)
{
}


void multiselect::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//Print Action Message
	pOut->PrintMsg("Multiselection ,, to stop enter on a empty erea....");
	pIn->GetPointClicked(x1, y1);
	pOut->ClearStatusBar();
	//Get a Pointer to the Input / Output Interfaces
}

void multiselect :: Execute()
{
	ReadActionParameters();
	Component* com=pManager->FindComp(x1,y1);
	while (com != NULL)
	{
		com->Sel();
		pManager->UpdateInterface();
		ReadActionParameters();
		com = pManager->FindComp(x1, y1);
	}
	
}

void multiselect::Undo()
{}

void multiselect::Redo()
{}

multiselect::~multiselect(void)
{
}
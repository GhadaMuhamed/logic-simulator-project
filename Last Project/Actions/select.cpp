#include"select.h"

Select::Select(ApplicationManager *pApp) :Action(pApp)
{
}

Select::~Select(void)
{
}

void Select::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//Print Action Message
	pOut->PrintMsg("selecting component , click on the component you want to select or unselect ....");
	pIn->GetPointClicked(x1, y1);
	pOut->ClearStatusBar();

}

void Select::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	Component* com=pManager->FindComp(x1, y1);
	if (com == NULL) { pOut->PrintMsg("You should click on a component..!"); return; }
	com->Sel();
}

void Select::Undo()
{}

void Select::Redo()
{}


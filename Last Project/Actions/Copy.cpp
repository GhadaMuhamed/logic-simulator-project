#include "Copy.h"
#include"..\ApplicationManager.h"

Copy::Copy(ApplicationManager *pApp) :Action( pApp)
{
}

void Copy::Execute()
{
	pManager->copy();
	
}
void Copy::ReadActionParameters(){}
	 
void Copy:: Undo(){}
void Copy:: Redo(){}

Copy::~Copy()
{
}

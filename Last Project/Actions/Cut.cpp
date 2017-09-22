#include "Cut.h"
#include"..\ApplicationManager.h"
#include "..\Components\Gate.h"
#include"..\Components\Connection.h"
Cut::Cut(ApplicationManager *pApp) :Action( pApp)
{
}

void Cut::Execute()
{
	pManager->cut();
	
}

void Cut::ReadActionParameters(){}
	 
void Cut:: Undo(){}
void Cut:: Redo(){}
Cut::~Cut()
{
}

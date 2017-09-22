
#include"..\ApplicationManager.h"
#include"deleting.h"
#include "..\Components\Gate.h"
#include"..\Components\Connection.h"
deleting::deleting(ApplicationManager *pApp) :Action( pApp)
{
}
void deleting::Execute()
{
	pManager->Deleteing();
	
}


void deleting::ReadActionParameters(){}
	 
void deleting:: Undo(){}
void deleting:: Redo(){}
deleting::~deleting()
{
}

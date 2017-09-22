#include "Load.h"



Load::Load(ApplicationManager *pApp) :Action(pApp)
{

}
Load::Load(ApplicationManager *pApp,string s) : Action(pApp)
{
	pManager->cmp_del();
	ifstream fin(s);
	pManager->load(fin);
    //pManager->GetOutput()->ClearDrawingArea();
}

void Load::Execute()
{
	Output* ou = pManager->GetOutput();
	Input* in = pManager->GetInput();
	ou->PrintMsg("Enter the file name you want to load..");
	string s = in->GetSrting(ou);
	if (!(ifstream(s))) {
		ou->PrintMsg("This name doesn't exist..");
		return; }
	pManager->cmp_del();
	ifstream fin(s);
	pManager->load(fin);
	//pManager->GetOutput()->ClearDrawingArea();

}


Load::~Load()
{
}

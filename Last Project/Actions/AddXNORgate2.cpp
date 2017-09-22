#include "AddXNORgate2.h"
#include "..\ApplicationManager.h"



AddXNORgate2::AddXNORgate2(ApplicationManager *pApp) :Action(pApp)
{
}


AddXNORgate2::~AddXNORgate2(void)
{
}

void AddXNORgate2::ReadActionParameters()
{}

bool AddXNORgate2::check(GraphicsInfo GInfo)
{
	Output* pOut = pManager->GetOutput();
	int** grid = pOut->getgrid();
if (GInfo.x1 < 40 || GInfo.x2>1250 || GInfo.y1<UI.ToolBarHeight || GInfo.y2>UI.height - UI.StatusBarHeight - 10)
		return false;
	for (int i = (GInfo.x1 / 10); i <= (GInfo.x2 / 10) ; i++)
		for (int j = (GInfo.y1 / 10); j <= (GInfo.y2 / 10); j++)
		{
	if (grid[j][i]!=-1) return false;
		}
		for (int i=1;i<=3;i++)
		{
			if (grid[(GInfo.y1 / 10)-i][(GInfo.x1 / 10)-i]==0 || grid[(GInfo.y2 / 10)-i][(GInfo.x1 / 10)-i]==0 || grid[(GInfo.y1 / 10)-i][(GInfo.x2 / 10)-i]==0 || grid[(GInfo.y2 / 10)-i][(GInfo.x2 / 10)-i]==0)
				return false;
		}
	return true;
}
void AddXNORgate2::Execute()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMsg("XNOR2 Gate: Click to add the gate ..");
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	

	int iX = 0, iY = 0;
	window* pwind;
	image im = pOut->storeimage();
	pwind = pOut->getwind();
	GraphicsInfo t_GfxInfo;
	t_GfxInfo.x1=iX;
	t_GfxInfo.y2=iY;
	t_GfxInfo.x2=UI.AND2_Width;
	t_GfxInfo.y2=UI.AND2_Height;
	int xx=0,yy=0;
	XNOR2* pA = new XNOR2(t_GfxInfo, AND2_FANOUT);
	char ckey;
		int cnt=0;
	while (pwind->GetKeyPress(ckey) !=ESCAPE)
	{
		if (pwind->GetButtonState(LEFT_BUTTON, xx, yy) == BUTTON_DOWN)
		{
			cnt++;
			if (check(t_GfxInfo))
				break;
			else {	
				for (int i=0;i<70;i++)
pOut->PrintMsg("You can't add a gate here!");
}
		}
		if (cnt==25)
			break;
		pwind->GetMouseCoord(iX, iY);
		pManager->Correct(iX, iY);

		t_GfxInfo.x1 = iX;
		t_GfxInfo.x2 = iX + 60;
		t_GfxInfo.y1 = iY;
		t_GfxInfo.y2 = iY + 40;
		pA->setinfo(t_GfxInfo);
		pOut->drawimage(im);
		pA->Draw(pOut);
	//	pOut->updatebuffer();
	}
	if (cnt==25|| cnt==0) {delete pA; pA=NULL; pOut->ClearDrawingArea(); return;}
	pManager->AddComponent(pA);
}

void AddXNORgate2::Undo()
{}

void AddXNORgate2::Redo()
{}
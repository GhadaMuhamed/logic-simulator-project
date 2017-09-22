
#include"move.h"
#include"..\Components\Gate.h"
#include"..\Components\Connection.h"
#include"AddConnection.h"
#include"..\GUI\Output.h"
#include<vector>
moveing::moveing(ApplicationManager *pApp) :Action(pApp)
{
	
}

moveing::~moveing(void)
{
	
}

void moveing::ReadActionParameters()
{
	

}

void moveing::moveconnection(Component*u)
{
	GraphicsInfo GInfo;
	Gate* gate = dynamic_cast<Gate*>(u);
	int NumberOfinputpins = gate->GetInNum();
	OutputPin* ou = gate->Gate_oPin();
	int connNum = ou->NumOfConnection();
	for (int i = 0; i < NumberOfinputpins; i++)
	{
		InputPin* in = gate->getIpin(i);
		Output* ou=pManager->GetOutput();
		if (in == NULL) continue;
		Connection* c = in->getConn();
		if (c == NULL) continue;
				c->clear(ou->getgrid());
		int num = i + 1;
		GInfo.x1 = gate->get_info().x1 / 10;
		if (num == 1)
		{
			if (NumberOfinputpins == 1)
			{
				GInfo.y1 = (gate->get_info().y1 + UI.AND2_Height / 2) / 10;
			}
			else
			{
				GInfo.y1 = ((gate->get_info().y1 + UI.AND2_Height / 2) - 10) / 10;
			}
		}
		else if (num == 2)
		{
			if (NumberOfinputpins == 2)
				GInfo.y1 = ((gate->get_info().y1 + UI.AND2_Height / 2) + 10) / 10;
			else 			GInfo.y1 = (gate->get_info().y1 + UI.AND2_Height / 2) / 10;
		}
		else GInfo.y1 = ((gate->get_info().y1 + UI.AND2_Height / 2) + 10) / 10;
		GInfo.x2 = c->get_info().x2;
		GInfo.y2 = c->get_info().y2;
		c->setinfo(GInfo);
	}
	
	Connection** c = ou->GetConn();
	
	for (int i = 0; i < connNum; i++)
	{
		GInfo.x1 = c[i]->get_info().x1;
		GInfo.y1 = c[i]->get_info().y1;
		GInfo.x2 = gate->get_info().x2 / 10;
		GInfo.y2 = (gate->get_info().y1 + UI.AND2_Height / 2) / 10;
		c[i]->setinfo(GInfo);
	}

}

Component* moveing::getminx_y(Component**r)
{
	Component*v;
	v = r[0];
	int numofselected = pManager->counting_selected();
	for (int i = 0; i < numofselected; i++)
	{
		vec.push_back(r[i]->get_info());
		if ((r[i]->get_info().x1 < v->get_info().x1) && (r[i]->get_info().y1 < v->get_info().y1))
		{v = r[i];}
		
	}


	return v;
}
void moveing::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int numofselected=0;//number of component whch selected and gate;
	//Print Action Message
	pOut->PrintMsg("Click on the new position you want to move components to  ....");
	numofselected=pManager->counting_selected();

	int** grid=pOut->getgrid();
	//case 1 if there no thing selected 
	if (numofselected == 0)
	{
		pOut->PrintMsg("You should select any gate first.......");
		
	}
	//case 2 if there only one gate selected
	else if (numofselected == 1)
	{
		pOut->PrintMsg("Moving one component ,, drag the component to the new place then press escape to stop.......");
		pIn->GetPointClicked(x1, y1);
	
				Component*compp = pManager->selectedcomp();
				compp->clear(grid);
				GraphicsInfo t_GfxInfo;
				GraphicsInfo p_GfxInfo;
				t_GfxInfo = compp->get_info();
				pOut->drawrect2(t_GfxInfo.x1, t_GfxInfo.y1);

				p_GfxInfo=t_GfxInfo;
				
				//way dragging
				bool bDragging = false;

				int iX =0, iY = 0;
				char cKeyData;
				int iXOld = 0;
				int iYOld = 0;
				window* pwind;
					image im = pOut->storeimage();
				pwind = pOut->getwind();
				compp->Sel();
				// Loop until there escape is pressed
				while (pwind->GetKeyPress(cKeyData) != ESCAPE)
				{
					
					
					if (bDragging == false) 
					{
						if (pwind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_DOWN) 
						{
							//if (iX <= 0 || iX > UI.width || iY <= UI.ToolBarHeight || iY >= UI.height - UI.StatusBarHeight) break;

							 if (((iX > t_GfxInfo.x1) && (iX < (t_GfxInfo.x1 + 60))) && ((iY >t_GfxInfo.y1) && (iY < (t_GfxInfo.y1+40)))) {
								bDragging = true;
								iXOld = iX; iYOld = iY;
							}
						}
					}
					else 
					{
						if (pwind->GetButtonState(LEFT_BUTTON, iX, iY) == BUTTON_UP)
						{
							bDragging = false;
						}
						else 
						{
						
							
							if (iX != iXOld)
							{
								t_GfxInfo.x1 = t_GfxInfo.x1 + (iX - iXOld);
								t_GfxInfo.x2 = t_GfxInfo.x1 + 60;
								iXOld = iX;
							}
							if (iY != iYOld)
							{
								t_GfxInfo.y1 = t_GfxInfo.y1 + (iY - iYOld);
								t_GfxInfo.y2 = t_GfxInfo.y1 + 40;
								iYOld = iY;
							}
						
						}
						compp->setinfo(t_GfxInfo);
						pOut->drawimage(im);
						compp->Draw(pOut);

						pOut->updatebuffer();
						
					}

				

				}
				
				GraphicsInfo gi = compp->get_info();
				pManager->Correct(gi.x1, gi.y1);
				gi.x2 = gi.x1 + UI.AND2_Width;
				gi.y2 = gi.y1 + UI.AND2_Height;
				compp->setinfo(gi);
				if (!pManager->check(gi)) 	compp->setinfo(p_GfxInfo);

				pOut->ClearStatusBar();
				pOut->ClearDrawingArea();
				moveconnection(compp);
				pManager->UpdateInterface();				
			
			}
			
	else if (numofselected > 1)
	{

		pOut->PrintMsg("Moving more than one component ,, Click on the new position.......");
		pIn->GetPointClicked(x1, y1);
		
		y = pManager->selectedarr();
		Component *mincom = getminx_y(y);
		
		bool overlapping=false;
			GraphicsInfo t_GfxInfo;
			GraphicsInfo p_GfxInfo;
			t_GfxInfo = mincom->get_info();
			pManager->Correct(x1, y1);
			p_GfxInfo.x1 = x1;
			p_GfxInfo.x2 = x1 + 60;
			p_GfxInfo.y1 = y1;
			p_GfxInfo.y2 = y1 + 40;
			if (!pManager->check(p_GfxInfo))
				overlapping=true;
			mincom->setinfo(p_GfxInfo);
			mincom->Sel();
			pOut->ClearDrawingArea();
			moveconnection(mincom);
			pManager->UpdateInterface();
			
			//move label
			if (mincom->getlabel() != "")
			{
				string r;
				r = mincom->getlabel();

				pOut->drawrect1(t_GfxInfo.x1, t_GfxInfo.y1 - 20, true);
				pOut->DrawMsg(r, p_GfxInfo.x1, p_GfxInfo.y1 - 20);

			}
			GraphicsInfo t2_GfxInfo;
			for (int i =0; i < numofselected; i++)
			{
				if (y[i] != mincom)
				{
					t2_GfxInfo = y[i]->get_info();
					p_GfxInfo.x1 = x1 + (t2_GfxInfo.x1 - t_GfxInfo.x1);
					p_GfxInfo.x2 = p_GfxInfo.x1 + 60;
					p_GfxInfo.y1 = y1 + (t2_GfxInfo.y1 - t_GfxInfo.y1);
					p_GfxInfo.y2 = p_GfxInfo.y1 + 40;
					if (!pManager->check(p_GfxInfo)) {overlapping=true;}
					y[i]->setinfo(p_GfxInfo);
					y[i]->Sel();
					pOut->ClearDrawingArea();
					moveconnection(y[i]);
					pManager->UpdateInterface();
					
					//move label
					if (y[i]->getlabel() != "")
					{
						string r;
						r = y[i]->getlabel();

						pOut->drawrect1(t2_GfxInfo.x1, t2_GfxInfo.y1 - 20, true);
						pOut->DrawMsg(r, p_GfxInfo.x1, p_GfxInfo.y1 - 20);

					}
					pOut->drawrect2(t2_GfxInfo.x1, t2_GfxInfo.y1);

				}
				

			}
			
			pOut->drawrect2(t_GfxInfo.x1, t_GfxInfo.y1);
			if (overlapping) {pOut->PrintMsg("You Can't move gates here!");
						for (int i =0; i < numofselected; i++)
						{
							y[i]->setinfo(vec[i]);

						}
																		pOut->ClearDrawingArea();



			}
	}


	
}




void moveing::Undo()
{}

void moveing::Redo()
{}




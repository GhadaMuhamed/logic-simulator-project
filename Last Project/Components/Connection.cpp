
#include "Connection.h"
#include "Gate.h"
# include <vector>
Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin,InputPin *pDstPin):Component(r_GfxInfo)	
{
	SrcPin = pSrcPin;
	DstPin = pDstPin;
	DstPin->setCon(this);
	DstPin->set_connection(true);
	PathChanged = true;
}
void Connection::Path(bool a)
{
	PathChanged = a;
}
void  Connection::uncalc()
{
	return ;
}

void Connection::clear(int** grid)
{
	PathChanged=true;
		for (int i = 0; i < (int)ConnectionPath.size(); i++)
	{
		int x1 =ConnectionPath[i].x1;
		int x2 =ConnectionPath[i].x2;
		int y1 = ConnectionPath[i].y1;
		int y2 = ConnectionPath[i].y2;
		if (x1 == x2)
		{
			if (arc[y2][x2] < -1)
			{
				grid[y1][x1] = -1;
				grid[y2][x2] = -1;
			}
			else 	for (int j = min(y1, y2); j <= max(y1, y2); j++)
			{
				grid[j][x1] = -1;
			}
		}
		else
		{
			if (arc[y2][x2] < -1)
			{
				grid[y1][x1] = -1;
				grid[y2][x2] = -1;

			}
			else for (int j = min(x1, x2); j <= max(x1, x2); j++)
			{

				grid[y1][j] = -1;
			}
		}
	}

}
void Connection::add(int** grid)
{

return ;

}
void Connection::setSourcePin(OutputPin *pSrcPin)
{	SrcPin = pSrcPin;	}

vector <GraphicsInfo> Connection::get_ConnPath()
{
	return ConnectionPath;
}

void Connection::save(ofstream &fout)
{
	fout << SrcPin->getGate()->get_ID() << " " << DstPin->getComponent()->get_ID() << " " << DstPin->get_num() << " ";
	if (m_Label == "")
		fout << "NO_NAME" << endl;
	else fout << m_Label << endl;
}
OutputPin* Connection::getSourcePin()
{	return SrcPin;	}

void Connection::setDestPin(InputPin *pDstPin)
{	DstPin = pDstPin;	}

InputPin* Connection::getDestPin()
{	return DstPin;	}


void Connection::Operate()
{
	//Status of connection destination pin = status of connection source pin

	DstPin->setStatus((STATUS)SrcPin->getStatus());
}

void Connection::Draw(Output* pOut)
{
	GraphicsInfo g1=SrcPin->getGate()->get_info();
	GraphicsInfo g2=DstPin->getComponent()->get_info();
	pOut->DrawConnection(m_GfxInfo, SrcPin->getGate()->get_ID(),ConnectionPath,PathChanged,arc,g1,g2,sel_ect);
}

int Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	return DstPin->getStatus();
}
void Connection::setinfo(GraphicsInfo g)
{
	PathChanged = true;
	m_GfxInfo = g;
}

void Connection::load(string _label,int a)
{
	if (_label == "NO_NAME")
		m_Label = "";
	else m_Label = _label;
	SrcPin->ConnectTo(this);

}

int Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
}

void Connection::setInputPinStatus(int n, STATUS s)
{
	SrcPin->setStatus(s);
}

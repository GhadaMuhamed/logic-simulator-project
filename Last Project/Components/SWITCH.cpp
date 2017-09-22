#include "SWITCH.h"

SWITCH::SWITCH(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(0, r_FanOut)
{
	m_GfxInfo = r_GfxInfo;
	status = LOW;
}

void SWITCH::change()
{
	if (status == HIGH)
		status = LOW;
	else status = HIGH;
}

void SWITCH::save(ofstream& fout)
{

	fout << "SWITCH" << " " << ID << " ";
	if (m_Label == "")
		fout << "NO_NAME" << " ";
	else fout << m_Label << " ";
	fout << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << m_GfxInfo.x2 << " " << m_GfxInfo.y2 << endl;
}
void SWITCH::clear(int** grid)
{
	for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=-1;

}
void SWITCH::add(int** grid)
{

for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=0;

}
Gate* SWITCH::COPY(GraphicsInfo W)
 {
  SWITCH*pA = new SWITCH(W, AND2_FANOUT);
  return pA;
 }
void SWITCH::setstatus(STATUS s)
{
	status = s;
}

void SWITCH::load(string _label, int _ID)
{

	ID = _ID;
	if (_label == "NO_NAME")
		m_Label = "";
	else m_Label = _label;
}

STATUS SWITCH::GetStat()
{
	return status;
}

void SWITCH::Operate()
{	
	m_OutputPin.Calculate(true);
	m_OutputPin.setStatus(status);
	//Add you code here
}
void SWITCH::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	if (status==LOW)
	pOut->DrawSWITCH_Off(m_GfxInfo,sel_ect);
	else 	pOut->DrawSWITCH_On(m_GfxInfo,sel_ect);
		pOut->DrawMsg(m_Label, m_GfxInfo.x1, (m_GfxInfo.y1 - 20));


}
int SWITCH::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int SWITCH::GetInputPinStatus(int n)
{
	return -1;
}
void SWITCH::setInputPinStatus(int n, STATUS s)
{
	status = s;
}

SWITCH::~SWITCH(void)
{
}

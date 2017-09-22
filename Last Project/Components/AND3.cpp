#include "AND3.h"


AND3::AND3(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(3,r_FanOut)
{
	m_GfxInfo = r_GfxInfo;
}
void AND3::clear(int** grid)
{
	for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=-1;

}
void AND3::add(int** grid)
{

for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=0;

}
void AND3::load(string _label, int _ID)
{

	ID = _ID;
	if (_label == "NO_NAME")
		m_Label = "";
	else m_Label = _label;
}
Gate* AND3::COPY(GraphicsInfo W)
 {
 AND3 *pA = new AND3(W, AND2_FANOUT);
  return pA;
 }
void AND3::save(ofstream& fout)
{

	fout << "AND3" << 
	" " << ID << " ";
	if (m_Label == "")
		fout << "NO_NAME" << " ";
	else fout << m_Label << " ";
	fout << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << m_GfxInfo.x2 << " " << m_GfxInfo.y2 << endl;
}

void AND3::Operate()
{
	m_OutputPin.Calculate(true);
	for (int i = 0; i < m_Inputs; i++)
	{
		if (m_InputPins[i].getStatus() == LOW)
		{
			m_OutputPin.setStatus(LOW); return;

		}
	}
	m_OutputPin.setStatus(HIGH);
}
void AND3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	if (sel_ect)
	pOut->DrawAND3(m_GfxInfo,true);
	else	pOut->DrawAND3(m_GfxInfo);
	pOut->DrawMsg(m_Label, m_GfxInfo.x1, (m_GfxInfo.y1 - 20));

}
int AND3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}
int AND3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

void AND3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

AND3::~AND3()
{
}

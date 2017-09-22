#include "INVERTER.h"

INVERTER::INVERTER(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	m_GfxInfo = r_GfxInfo;
}


void INVERTER::load(string _label, int _ID)
{
	ID = _ID;
	if (_label == "NO_NAME")
		m_Label = "";
	else m_Label = _label;
}
void INVERTER::clear(int** grid)
{
	for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=-1;

}
void INVERTER::add(int** grid)
{

for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=0;

}
void INVERTER::save(ofstream &fout)
{
	fout << "INVERTER" << " " << ID << " ";
	if (m_Label == "")
		fout << "NO_NAME" << " ";
	else fout << m_Label << " ";
	fout << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << m_GfxInfo.x2 << " " << m_GfxInfo.y2 << endl;
}
Gate* INVERTER::COPY(GraphicsInfo W)
 {
 INVERTER *pA = new INVERTER(W, AND2_FANOUT);
  return pA;
 }

void INVERTER::Operate()
{
	m_OutputPin.Calculate(true);
	for (int i = 0; i < m_Inputs; i++)
	{
		if (m_InputPins[i].getStatus() == HIGH)
		{
			m_OutputPin.setStatus(LOW); return;

		}
	}
	m_OutputPin.setStatus(HIGH);

	//caclulate the output status as the ANDing of the two input pins
	//Add you code here
}
void INVERTER::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	if (sel_ect)
	pOut->DrawNOT(m_GfxInfo,true);
	else 	pOut->DrawNOT(m_GfxInfo);


		pOut->DrawMsg(m_Label, m_GfxInfo.x1, (m_GfxInfo.y1 - 20));
}
int INVERTER::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int INVERTER::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}
void INVERTER::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
INVERTER::~INVERTER(void)
{
}

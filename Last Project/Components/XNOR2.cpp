#include "XNOR2.h"


XNOR2::XNOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo = r_GfxInfo;
}

void XNOR2::save(ofstream& fout)
{

	fout << "XNOR2" << " " << ID << " ";
	if (m_Label == "")
		fout << "NO_NAME" << " ";
	else fout << m_Label << " ";
	fout << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << m_GfxInfo.x2 << " " << m_GfxInfo.y2 << endl;
}
Gate* XNOR2::COPY(GraphicsInfo W)
 {
  XNOR2 *pA = new XNOR2(W, AND2_FANOUT);
  return pA;
 }
void XNOR2::clear(int** grid)
{
	for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=-1;

}
void XNOR2::add(int** grid)
{

for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=0;

}
void XNOR2::load(string _label, int _ID)
{

	ID = _ID;
	if (_label == "NO_NAME")
		m_Label = "";
	else m_Label = _label;
}

void XNOR2::Operate()
{
	m_OutputPin.Calculate(true);
	int cnt = 0;
	for (int i = 0; i < m_Inputs; i++)
	{
		if (m_InputPins[i].getStatus() == HIGH)
		{
			cnt++;
		}
	}
	if (cnt % 2 == 0)
		m_OutputPin.setStatus(HIGH);
	else m_OutputPin.setStatus(LOW);

	//caclulate the output status as the ANDing of the two input pins
	//Add you code here
}
void XNOR2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXNOR2(m_GfxInfo,sel_ect);
		pOut->DrawMsg(m_Label, m_GfxInfo.x1, (m_GfxInfo.y1 - 20));

}
int XNOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int XNOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}
void XNOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

XNOR2::~XNOR2()
{
}

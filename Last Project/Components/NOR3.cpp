#include "NOR3.h"


NOR3::NOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo = r_GfxInfo;
}

void NOR3::load(string _label, int _ID)
{

	ID = _ID;
	if (_label == "NO_NAME")
		m_Label = "";
	else m_Label = _label;
}
Gate* NOR3::COPY(GraphicsInfo W)
 {
 NOR3 *pA = new NOR3(W, AND2_FANOUT);
  return pA;
 }
void NOR3::clear(int** grid)
{
	for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=-1;

}
void NOR3::add(int** grid)
{

for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=0;

}
void NOR3::save(ofstream& fout)
{

	fout << "NOR3" << " " << ID << " ";
	if (m_Label == "")
		fout << "NO_NAME" << " ";
	else fout << m_Label << " ";
	fout << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << m_GfxInfo.x2 << " " << m_GfxInfo.y2 << endl;
}

void NOR3::Operate()
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
void NOR3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	if (sel_ect)
	pOut->DrawNOR3(m_GfxInfo,true);
	else 	pOut->DrawNOR3(m_GfxInfo);
		pOut->DrawMsg(m_Label, m_GfxInfo.x1, (m_GfxInfo.y1 - 20));

}
int NOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int NOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}
void NOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
NOR3::~NOR3()
{
}

#include "XOR3.h"


XOR3::XOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo = r_GfxInfo;
}

void XOR3::load(string _label, int _ID)
{

	ID = _ID;
	if (_label == "NO_NAME")
		m_Label = "";
	else m_Label = _label;
}
Gate* XOR3::COPY(GraphicsInfo W)
 {
 XOR3 *pA = new XOR3(W, AND2_FANOUT);
  return pA;
 }
void XOR3::clear(int** grid)
{
	for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=-1;

}
void XOR3::add(int** grid)
{

for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=0;

}
void XOR3::save(ofstream& fout)
{

	fout << "XOR3" << " " << ID << " ";
	if (m_Label == "")
		fout << "NO_NAME" << " ";
	else fout << m_Label << " ";
	fout << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << m_GfxInfo.x2 << " " << m_GfxInfo.y2 << endl;
}

void XOR3::Operate()
{
	m_OutputPin.Calculate(true);
	int num = 0;
	for (int i = 0; i < m_Inputs; i++)
	{
		if (m_InputPins[i].getStatus() == HIGH)
		{
			num++;
		}
	}
	if (num % 2)
		m_OutputPin.setStatus(HIGH);
	else m_OutputPin.setStatus(LOW);


	//caclulate the output status as the ANDing of the two input pins
	//Add you code here
}
void XOR3::Draw(Output* pOut)
{
	pOut->DrawXOR3(m_GfxInfo,sel_ect);
	pOut->DrawMsg(m_Label, m_GfxInfo.x1, (m_GfxInfo.y1 - 20));
}
int XOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int XOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}
void XOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

XOR3::~XOR3()
{
}

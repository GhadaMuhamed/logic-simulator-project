#include "LED.h"


LED::LED(const GraphicsInfo &r_GfxInfo):Gate(1,0)
{
	m_GfxInfo = r_GfxInfo;
	status = LOW;              // the led is intially turned off.
}
int LED::GetOutPinStatus()
{
	return -1;
}
void LED::load(string _label, int _ID)
{
	ID = _ID;
	if (_label == "NO_NAME")
		m_Label = "";
	else m_Label = _label;
}
void LED::clear(int** grid)
{
	for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=-1;

}
void LED::add(int** grid)
{

for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=0;

}
Gate* LED::COPY(GraphicsInfo W)
 {
  LED *pA = new LED(W);
  return pA;
 }
STATUS LED::getstat()
{
	return status;
}
void LED::Operate()
{
	if (m_InputPins->getStatus() == HIGH)
		status = HIGH;
	else
		status = LOW;
}

void LED::Draw(Output* pOut)
{

	if (sel_ect == false)
	{
		if (status == LOW)
			pOut->DrawLED_OFF(m_GfxInfo);   // the red one.
		else
			pOut->DrawLED_ON(m_GfxInfo);    // the black one.
	}
else if (sel_ect == true)
	{
		if (status == LOW)
			pOut->DrawLED_OFF(m_GfxInfo,true);   // the red one.
		else
			pOut->DrawLED_ON(m_GfxInfo,true);    // the black one.
	}
		pOut->DrawMsg(m_Label, m_GfxInfo.x1, (m_GfxInfo.y1 - 20));

}
int LED::GetInputPinStatus(int n)
{
	return m_InputPins->getStatus();	
}
void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPins->setStatus(s);
}
void LED::save(ofstream & fout)
{
		fout << "LED" << " " << ID << " ";
		if (m_Label == "")
			fout << "NO_NAME" << " ";
		else fout << m_Label << " ";
		fout << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << m_GfxInfo.x2 << " " << m_GfxInfo.y2 << endl;
}
LED::~LED()
{
	//delete m_InputPins;
    //m_InputPins = NULL;
}

#include "NOR2.h"




NOR2::NOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo = r_GfxInfo;
}

void NOR2::save(ofstream& fout)
{

	fout << "NOR2" << " " << ID << " ";
	if (m_Label == "")
		fout << "NO_NAME" << " ";
	else fout << m_Label << " ";
	fout << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << m_GfxInfo.x2 << " " << m_GfxInfo.y2 << endl;
}
void NOR2::clear(int** grid)
{
	for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=-1;

}
void NOR2::add(int** grid)
{

for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=0;

}
Gate* NOR2::COPY(GraphicsInfo W)
 {
 NOR2 *pA = new NOR2(W, AND2_FANOUT);
  return pA;
 }
void NOR2::load(string _label, int _ID)
{

	ID = _ID;
	if (_label == "NO_NAME")
		m_Label = "";
	else m_Label = _label;
}

void NOR2::Operate()
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


// Function Draw
// Draws 2-input AND gate
void NOR2::Draw(Output* pOut)
{
	if (sel_ect == false)
		//Call output class and pass gate drawing info to it.
		pOut->DrawNOR2(m_GfxInfo);
	else if (sel_ect == true)
		pOut->DrawNOR2(m_GfxInfo, true);
		pOut->DrawMsg(m_Label, m_GfxInfo.x1, (m_GfxInfo.y1 - 20));


}

//returns status of outputpin
int NOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

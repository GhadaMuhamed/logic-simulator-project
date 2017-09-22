#include "AND2.h"
AND2::AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo = r_GfxInfo;
}
void AND2::clear(int** grid)
{
	for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=-1;

}
void AND2::add(int** grid)
{

for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=0;

}
void AND2::save(ofstream& fout)
{

	fout << "AND2" << " " << ID << " ";
	if (this->m_Label == "")
		fout << "NO_NAME" << " ";
	else fout << m_Label << " ";
	fout<<m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << m_GfxInfo.x2 << " " << m_GfxInfo.y2 << endl;
}
 Gate* AND2::COPY(GraphicsInfo W)
 {
  AND2 *pA = new AND2(W, AND2_FANOUT);
  return pA;
 }
void AND2::load(string _label,int _ID)
{
	
	ID = _ID;
	if (_label == "NO_NAME")
		m_Label = "";
	else m_Label = _label;
}

void AND2::Operate()
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
	
	//caclulate the output status as the ANDing of the two input pins
	//Add you code here
}


// Function Draw
// Draws 2-input AND gate
void AND2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	if (sel_ect)
		pOut->DrawAND2(m_GfxInfo, true);
	else
		pOut->DrawAND2(m_GfxInfo);
	pOut->DrawMsg(m_Label, m_GfxInfo.x1, (m_GfxInfo.y1 - 20));
}

//returns status of outputpin
int AND2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int AND2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void AND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

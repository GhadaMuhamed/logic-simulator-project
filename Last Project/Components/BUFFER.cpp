# include"BUFFER.h"

BUFFER::BUFFER(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	m_GfxInfo = r_GfxInfo;
}
void BUFFER::load(string _label, int _ID)
{
	ID = _ID;
	if (_label == "NO_NAME")
		m_Label = "";
	else m_Label = _label;
}
void BUFFER::clear(int** grid)
{
	for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=-1;

}
void BUFFER::add(int** grid)
{

for (int i=m_GfxInfo.y1/10;i<=m_GfxInfo.y2/10;i++)
		for (int j=m_GfxInfo.x1/10;j<=m_GfxInfo.x2/10;j++)
			grid[i][j]=0;

}
Gate* BUFFER::COPY(GraphicsInfo W)
 {
 BUFFER *pA = new BUFFER(W, AND2_FANOUT);
  return pA;
 }
void BUFFER::save(ofstream &fout)
{
	fout << "BUFFER" << " " << ID << " ";
	if (m_Label== "")
		fout << "NO_NAME" << " ";
	else fout << m_Label << " ";
	fout << m_GfxInfo.x1 << " " << m_GfxInfo.y1 << " " << m_GfxInfo.x2 << " " << m_GfxInfo.y2 << endl;
}
void BUFFER::Operate()
{
	m_OutputPin.Calculate(true);
	for (int i = 0; i < m_Inputs; i++)
	{
		if (m_InputPins[i].getStatus() == HIGH)
			m_OutputPin.setStatus(HIGH); 
		else 
			m_OutputPin.setStatus(LOW);
	}

}
void BUFFER::Draw(Output* pOut)
{
	if (sel_ect == false)
		//Call output class and pass gate drawing info to it.
		pOut->DrawBUF(m_GfxInfo);
	else if (sel_ect == true)
	pOut->DrawBUF(m_GfxInfo, true);
		pOut->DrawMsg(m_Label, m_GfxInfo.x1, (m_GfxInfo.y1 - 20));


}

int BUFFER::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int BUFFER::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}
void BUFFER::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

BUFFER::~BUFFER()
{
}
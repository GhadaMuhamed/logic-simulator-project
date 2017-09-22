#include "Gate.h"
#include "Connection.h"
//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut):m_OutputPin(r_FanOut)
{
	//Allocate number of input pins (equals r_Inputs)
	if (m_InputPins>0)
	m_InputPins = new InputPin[r_Inputs];
	else m_InputPins = NULL;
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	
	//Associate all input pins to this gate
	for (int i = 0; i < m_Inputs; i++)
	{
		m_InputPins[i].setComponent(this);
		m_InputPins[i].set_num(i + 1);
	}
	if (r_FanOut == 0)
		m_OutputPin = NULL;
	else {m_OutputPin.setGate(this); }
}
void  Gate::uncalc()
{
	for (int i=0;i<m_Inputs;i++)
	{
	m_InputPins[i].Calculate(false);
	}
	m_OutputPin.Calculate(false);
}

void Gate::set_ID(int a)
{
	ID = a;
}
InputPin* Gate::getIpin(int a)
{
	if (a >= m_Inputs)
		return NULL;
	return &(m_InputPins[a]);
}

InputPin * Gate::getpins()
{
	return m_InputPins;
}

int Gate::GetInNum()
{
	return m_Inputs;
}

OutputPin* Gate::Gate_oPin()
{
	return &m_OutputPin;
}
	void Gate::DelAllConnc()
	{
		Connection** co=m_OutputPin.GetConn();
		for (int i=0;i<m_OutputPin.NumOfConnection();i++)
		{
			co[i]=NULL;
		}
		m_OutputPin.setm_Conn(0);
	}

void Gate::setinfo(GraphicsInfo g)
{
	for (int i = 0; i < m_Inputs; i++)
	{
		Connection* con = m_InputPins[i].getConn();
		if (con)
		con->Path(true);
	}
	Connection** co=m_OutputPin.GetConn();
	for (int i = 0; i < m_OutputPin.NumOfConnection(); i++)
		co[i]->Path(true);
	m_GfxInfo = g;
}
	Gate::~Gate()
	{
		if (m_InputPins)
			{delete m_InputPins;
		m_InputPins=NULL;}
	}



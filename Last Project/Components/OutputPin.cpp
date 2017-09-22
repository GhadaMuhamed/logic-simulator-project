#include "OutputPin.h"
#include "Connection.h"

OutputPin::OutputPin(int r_FanOut)
{
	gate = NULL;
	m_Conn = 0;		//initially Pin is not connected to anything.
	m_FanOut = r_FanOut > MAX_CONNS ? MAX_CONNS: r_FanOut;	//set the fan out of the pin.
}
void OutputPin::setm_Conn(int a)
{
	m_Conn = a;
}

Gate * OutputPin::getGate()
{
	return gate;
}

void OutputPin::setGate(Gate *a)
{
	gate = a;
}

void OutputPin::DelConnection(Connection *a)
{
	InputPin* ipin = a->getDestPin();
	ipin->set_connection(false);
	for (int i = 0; i < m_Conn; i++)
	{
		if (m_Connections[i] == a)
		{
			m_Connections[i] = NULL;
			m_Connections[i] = m_Connections[m_Conn - 1];
			m_Connections[m_Conn - 1] = NULL;
			m_Conn--;
			return;
		}
	}
}

//Functionn ConnectTo:
//Connects the ouput pin the the passed connection if the fan out permits
//if the no. of connections is already equals to the fan out, no more connections can be created.
bool OutputPin::ConnectTo(Connection *r_Conn)
{
	if(m_Conn < m_FanOut)
	{
		m_Connections[m_Conn++] = r_Conn;	//add a new connection the the array of connections
		return true;
	}
	
	return false;	//can't connect to any more connections
}

Connection** OutputPin::GetConn()
{
	return m_Connections;
}

int OutputPin::NumOfConnection()
{
	return m_Conn;
}

#include "InputPin.h"

InputPin::InputPin()
{
	Conn = NULL;
	connected = false;
}

void InputPin::setComponent(Gate *pCmp)
{
	this->pComp = pCmp;
}

int InputPin::get_num()
{
	return PinNum;
}
Connection* InputPin::getConn()
{
	return Conn;
}

void InputPin::set_num(int a)
{
	PinNum = a;
}
void InputPin::set_connection(bool a)
{
	connected = a;
}
bool InputPin::IsConnected()
{
	return connected;
}

void InputPin::setCon(Connection *a)
{
	Conn = a;
}

Gate* InputPin::getComponent()
{
	return pComp;
}
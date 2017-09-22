#include "Pin.h"

Pin::Pin()
{
    Calc = false;
	m_Status = LOW;	//Default Status is LOW
}

void Pin::setStatus(STATUS r_Status)
{
	Calc = true;
	m_Status = r_Status;
}

bool Pin::IsCalc()
{
	return Calc;
}

void Pin::Calculate(bool a)
{
	Calc = a;
}

STATUS Pin::getStatus()
{
	return m_Status;
}
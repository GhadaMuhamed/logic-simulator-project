#ifndef _PIN_H
#define _PIN_H

#include "..\Defs.h"

class Pin
{
	bool Calc;
protected:
	STATUS m_Status;	//Status of the Pin
public:
	Pin();
	void setStatus(STATUS r_Status);
	bool IsCalc();
    void Calculate(bool a);
	/*void set_x(int a);
	void set_y(int b);*/
	STATUS getStatus();
};

#endif
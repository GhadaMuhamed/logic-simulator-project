#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"
class Gate; //Forward class declaration
class Connection;	//Forward class declartion

class InputPin: public Pin	//inherited from class Pin
{
	int PinNum;
	Gate* pComp; //Component at which this pin is associated
	Connection* Conn;
	bool connected;
public:
	InputPin();
	void setComponent(Gate* pCmp);	//sets the component of this input pin
	Gate* getComponent();	//returns the component of this input pin
	int get_num();
	bool IsConnected();
	void setCon(Connection*);
	Connection* getConn();
	void set_num(int a);
	void set_connection(bool);
};

#endif
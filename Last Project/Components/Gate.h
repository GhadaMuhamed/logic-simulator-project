#ifndef _GATE_H
#define _GATE_H

#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"

class Gate:public Component
{
protected:
	InputPin* m_InputPins;	//Array of input pins of the Gate
	OutputPin m_OutputPin;	//The Gate output pin
	int m_Inputs;		//No. of input pins of that Gate.
public:
	Gate(int r_Inputs, int r_FanOut);
	virtual void save(ofstream&) = 0;
	virtual void load(string, int) = 0;
	void set_ID(int a);
	OutputPin* Gate_oPin();
	InputPin* getIpin(int a);
	InputPin* getpins();
	void DelAllConnc();
	void setinfo(GraphicsInfo g);
	virtual void uncalc();
		virtual Gate* COPY(GraphicsInfo) = 0;
virtual void clear(int**)=0;
	virtual void add(int**)=0;
	~Gate();
	/*void setopin(OutputPin* b);
	void setIpin(int x, int y);
	*/
	int GetInNum();
};

#endif

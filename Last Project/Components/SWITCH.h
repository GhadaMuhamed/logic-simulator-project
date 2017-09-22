#pragma once
#include "Gate.h"
class SWITCH:public Gate
{
	STATUS status;
public:
	SWITCH(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s);
	virtual void save(ofstream&);
	virtual void load(string label, int ID);
	void change();
	STATUS GetStat();
		virtual Gate* COPY(GraphicsInfo);
	void setstatus(STATUS s);
	virtual void clear(int**);
	virtual void add(int**);
	~SWITCH(void);
};


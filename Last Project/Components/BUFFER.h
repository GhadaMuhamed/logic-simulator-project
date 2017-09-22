#pragma once
#include "Gate.h"


class BUFFER :public Gate
{

public:
	BUFFER(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	                //Calculates the output of the AND gate
	virtual void Draw(Output* pOut);
	virtual int GetOutPinStatus();	       //returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s);	//s
	virtual void load(string label, int ID);
	virtual void save(ofstream &);
		virtual Gate* COPY(GraphicsInfo);
		virtual void clear(int**);
	virtual void add(int**);
	~BUFFER();
};


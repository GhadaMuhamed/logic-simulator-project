#pragma once
#include "Gate.h"
class XOR3:public Gate
{
public:
	XOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s);	//s
	virtual void save(ofstream& fout);
	virtual void load(string label, int ID);
		virtual Gate* COPY(GraphicsInfo);
		virtual void clear(int**);
	virtual void add(int**);
	~XOR3();
};


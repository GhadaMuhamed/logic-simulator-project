#pragma once
#include "Gate.h"
#include "InputPin.h"
using namespace std;

class LED :public Gate
{
	STATUS status;
public:
	LED(const GraphicsInfo &r_GfxInfo);
	virtual void Operate();
	virtual int GetOutPinStatus();
	virtual void Draw(Output* pOut);
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s);	//s
	void save(ofstream &fout);
	void load(string _label, int _ID);
		virtual Gate* COPY(GraphicsInfo);
	STATUS getstat();
	virtual void clear(int**);
	virtual void add(int**);
	//InputPin* Ipin();
	~LED();
};


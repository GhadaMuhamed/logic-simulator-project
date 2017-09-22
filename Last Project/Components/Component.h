#ifndef _COMPONENT_H
#define _COMPONENT_H
#include "..\Defs.h"
#include "..\GUI\Output.h"
#include <fstream>
//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	static int ID_cnt;
	int saved_x, saved_y;
protected:
	int ID;
	bool sel_ect;
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
	string m_Label;
	bool cut;
public:
	Component(const GraphicsInfo &r_GfxInfo);
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself
	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.
	virtual void save(ofstream&) = 0;
	virtual void load(string, int) = 0;
	virtual void set_ID(int a);
	static void set_IDCnt(int a);
	virtual void clear(int**)=0;
	virtual void add(int**)=0;
	void setcut(bool);
	bool getcut();
	int get_ID();
	void setlabel(string);
	string getlabel();
	GraphicsInfo get_info();
	virtual void uncalc()=0;
	virtual void setinfo(GraphicsInfo)=0;

	void setx(int l);   // beta3 el label ....
	void sety(int m);
	int gety();
	int getx();

	void Sel();//for select and unselect item
	Component();	//Destructor must be virtual
	bool IsSelected();
	virtual ~Component();
};

#endif

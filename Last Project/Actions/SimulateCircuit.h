#include "Action.h"
#include "..\Components\Gate.h"
#include <map>
class SimulateCircuit :public Action
{
	Component* led;
	static bool feedback;
	map<Gate*, int> mp;
public:
	SimulateCircuit(ApplicationManager*pApp,Component*);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
	static void setfeed(bool);
	static bool getfeed();
	void simulate(Gate*);
	~SimulateCircuit();
};

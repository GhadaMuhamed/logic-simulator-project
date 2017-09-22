#include "SimulateCircuit.h"
#include "..\ApplicationManager.h"
#include "..\Components\Connection.h"
#include "..\Components\LED.h"
#include "..\Components\SWITCH.h"
SimulateCircuit::SimulateCircuit(ApplicationManager* pApp,Component* l):Action(pApp)
{
	led=l;
}

void SimulateCircuit::ReadActionParameters()
{}
bool SimulateCircuit::getfeed()
{
	return feedback;
}

void SimulateCircuit::setfeed(bool a)
{
	feedback = a;
}

void SimulateCircuit::simulate(Gate* cur_gate)
{
	if (feedback) return;
	if (mp[cur_gate] == 1)
	{
		feedback = true;
		return;
	}
	mp[cur_gate] = 1;
	int NumberOfInputs = cur_gate->GetInNum();
	InputPin* inputs = cur_gate->getpins();
	for (int i = 0; i < NumberOfInputs; i++)
	{
		if (!inputs[i].IsCalc())
		{
			Connection* temp = inputs[i].getConn();
			OutputPin* p = temp->getSourcePin();
			Gate* g = p->getGate();
			simulate(g);
		}
	}
	cur_gate->Operate();
	OutputPin* ou=cur_gate->Gate_oPin();
	int NumberOfoutputs = ou->NumOfConnection();
	Connection** Conn = ou->GetConn();
	for (int i = 0; i < NumberOfoutputs; i++)
	{
		Conn[i]->Operate();
	}
	return;
}

void SimulateCircuit::Execute()
{
	Output* pOut = pManager->GetOutput();
	if (feedback)
	{
		pOut->PrintMsg("Error !! This circuit has feedback and can't be simulated .. please return back to design mode ");
		return;
	}
	Gate* g=dynamic_cast<Gate*>(led);
	simulate(g);
	
}

void SimulateCircuit::Undo()
{}

void SimulateCircuit::Redo()
{}

SimulateCircuit::~SimulateCircuit()
{}
bool SimulateCircuit::feedback = false;
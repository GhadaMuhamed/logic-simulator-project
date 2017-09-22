#pragma once
#include "Load.h"
#include <string>
using namespace std;
class UNDO:public Action
{
	static int lastnum;
	static int cur;
	static int mn;
public:
	UNDO(ApplicationManager *pApp);
	static string getname();
	static void setlast(int);
	virtual void ReadActionParameters();
	string nameToload();
	void Execute();
	static int getlast();
	static void DeleF();
	static int getcur();
	static void reName(int);
	~UNDO();
};


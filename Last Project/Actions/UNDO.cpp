#include "UNDO.h"
#include <sstream>

UNDO::UNDO(ApplicationManager *pApp):Action(pApp)
{
	string s = nameToload();
	if (!(ifstream(s))) s = "";
	if (s != "")
	{
		Action* ac = new Load(pApp, s);
		delete ac;
		ac=NULL;
	}
}
void UNDO::ReadActionParameters()
{}

string UNDO::getname()
{
	if (cur-mn == 39) { reName(mn); mn++;  }

	cur ++;
	lastnum = cur;
	int x = cur;
	string res = "UNDO";
	ostringstream ss;
	ss << x;
	string temp = ss.str();
	res += temp;
	return res;
}
void UNDO::setlast(int a)
{
	cur = a;
}

string UNDO::nameToload()
{
	int x = cur-1;
	if (x <= mn)
		return "";
	cur--;
	string res = "UNDO";
	ostringstream ss;
	ss << x;
	string temp = ss.str();
	res += temp;
	return res;
}

void UNDO::Execute()
{
}


int UNDO::getcur()
{
	return cur;
}
void UNDO::reName(int a)
{

	string s = "UNDO";
	int x = a;
	ostringstream ss;
	ss << x;
	string temp = ss.str();
	s += temp;
	const char* c = s.c_str();
	remove(c);
	
}
int UNDO::getlast()
{
	return lastnum;
}
void UNDO::DeleF()
{
	for (int i=mn;i<=lastnum;i++)
	{
		string s="UNDO";
	int x=i;
	ostringstream ss;
	ss << x;
	string temp = ss.str();
	s += temp;
	const char* c = s.c_str();
	remove(c);
	}
}
UNDO::~UNDO()
{
}
int  UNDO::lastnum = 0;
int  UNDO::mn = 1;
int  UNDO::cur = 0;

#include "REDO.h"
#include <sstream>
REDO::REDO(ApplicationManager * pApp):Action(pApp)
{
	string s = nameToLoad();
	if (!(ifstream(s))) s = "";
	if (s != "")
	{
		Action* p = new Load(pApp, s);
		delete p;
		p=NULL;
	}
}
void REDO::Execute()
{

}
void REDO::ReadActionParameters()
{

}
string REDO::nameToLoad()
{
	int last = UNDO::getlast();
	int cur = UNDO::getcur();
	int x = cur + 1;
	if (x > last) return "";
	UNDO::setlast(cur + 1);
	string res = "UNDO";
	ostringstream ss;
	ss << x;
	string temp = ss.str();
	res += temp;
	return  res;
}

REDO::~REDO()
{
}

#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
#include "..\Components\Connection.h"
#include <fstream>
class Save:public Action
{
	string FileName;
	static int SavedSize;
	string Saved_names[100];
	static int last;// to know the last saved name when the user didn't enter a name for the saved file
public:
	Save(ApplicationManager *pApp);
	Save(ApplicationManager *pApp, string s);

	void AddSavedFile(string& s);
	virtual void ReadActionParameters() {};//Execute action (code depends on action type)
	virtual void Execute();	//To undo this action (code depends on action type)
	virtual void Undo() ;
	//To redo this action (code depends on action type)
	virtual void Redo() ;
	~Save();
};


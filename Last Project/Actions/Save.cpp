#include "Save.h"

Save::Save(ApplicationManager *pApp) :Action(pApp)
{
	
}
Save::Save(ApplicationManager *pApp,string s) : Action(pApp)
{
	ofstream fout(s);
	pManager->save(fout);
}
void Save::AddSavedFile(string& s)
{
	bool empty = true;
	for (int i = 0; i < s.size(); i++)
		if (s[i] != ' ')empty = false;
	if (s == "" || empty)
	{
		s = "Untitled";
		int x = last;
		string temp = "";
		while (x)
		{
			temp += (x % 10 + '0');
			x /= 10;
		}
		reverse(temp.begin(), temp.end());
		last++;
		Saved_names[SavedSize] = s;
		SavedSize++;
		return;
	}
	int num = 1;
	bool exit = false;
	while (!exit)
	{
		exit = true;
		for (int i = 0; i < SavedSize; i++)
		{
			if (Saved_names[i] == s)
			{
				int x = num;
				string temp = "";
				while (x)
				{
					temp += (x % 10 + '0');
					x /= 10;
				}
				reverse(temp.begin(), temp.end());
				s += temp;
				exit = false;
				num++;
			}
		}
	}
	Saved_names[SavedSize] = s;
	SavedSize++;
}
void Save::Execute()
{
	if (SavedSize == 100)
	{
		pManager->GetOutput()->PrintMsg("you can't save more files ...");
		return;
	}
	Output* Pout = pManager->GetOutput();
	Input* Pin = pManager->GetInput();
	Pout->PrintMsg("Enter the file name ...");
	FileName = Pin->GetSrting(Pout);
	AddSavedFile(FileName);
	ofstream fout(FileName);
	pManager->save(fout);
	Pout->PrintMsg("The File has been saved");
}
void Save::Undo() {};

//To redo this action (code depends on action type)
void Save::Redo() {};
Save::~Save()
{
}
int Save::SavedSize = 0;
int Save::last = 1;

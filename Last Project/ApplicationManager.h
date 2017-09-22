#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Connection.h"
//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	bool sim; // to know if the circuit is valid or not 
	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface
	Component* cut_copy;
	bool update;
public:	
	ApplicationManager(); //constructor
	Component* FindComp(int x, int y);
	Component* FindComp1(int x, int y);
		Connection* find_conn(int x1, int y1);
	Component* set_label_tocon(Connection*);
	void paste();
	void copy();
	void cut();
	void clearComp(Component*);
	void Deleteing();
	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	void cmp_del();
	void setSim(bool a);
	void setcompcount(int);
	Component* getcut_copy();
	void setcut_copy(Component*);
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	void save(ofstream& fout);
	void load(ifstream& fin);
	void UpdateInterface();	//Redraws all the drawing window
	void simulate();
	void Correct(int&, int&);
	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();
	int GetCount();
	void SetCount(int);
		void set_label(Component*, string);
	void SimulateCirc();
	bool check(GraphicsInfo GInfo);

		int num_of_sw();
	Component** GetComp();
	void UnDo(Action*);
		int counting_selected();
	Component** selectedarr();
	Component*selectedcomp();
		void setxy_label(int, int, Component*);
		Connection * is_connection(Component*);
		bool getlabel(Component *);
	//Adds a new component to the list of components
	void AddComponent(Component* pComp);
	void replaceComponent(Component*p, int i, ApplicationManager *pApp);
	//destructor
	~ApplicationManager();
};

#endif
#include "Past.h"
#include "../ApplicationManager.h"
#include "../Components/Gate.h"
#include "AddConnection.h"
#include "AddANDgate2.h"
#include "AddANDgate3.h"
#include"AddINVERTER.h"
#include"AddNORgate3.h"
#include"AddXNORgate2.h"
#include"AddXORgate3.h"
#include"AddSWITCH.h"

# include "AddBUFFERgate.h"
#include"AddLED.h"
#include"AddNANDgate2.h"
#include"AddNORgate2.h"
#include"AddORgate2.h"
#include"AddXORgate2.h"

#include <iostream>
using namespace std;

Past::Past(ApplicationManager *pApp) :Action( pApp)
{
}


void Past::Execute()
{ 

	pManager->paste();
	



}
void Past::ReadActionParameters(){}
	 
void Past :: Undo(){}
void Past:: Redo(){}
Past::~Past()
{
}

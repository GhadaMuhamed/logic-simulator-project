#include "Truthtable.h"
# include "..\ApplicationManager.h"
# include "../Components\SWITCH.h"
# include "SimulateCircuit.h"
# include "../GUI\Output.h"
# include <cmath>
# include "../Components\LED.h"
# include <string>
# include <fstream>
# include <bitset>


Truthtable::Truthtable(ApplicationManager *pApp) :Action(pApp)
{

}

void Truthtable::ReadActionParameters()
{

}

void Truthtable::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	bool count5 = false;
	int x1 = 5;    int y = 30;
	int x_output = 400;
	pOut->PrintMsg("creating truth table");

	
	int number_of_switchs = 0;
	int num = pManager->GetCount();
	string *arr;
	number_of_switchs= pManager->num_of_sw(); 

	arr = calc(number_of_switchs);     // all possible combinations..
	Component ** c = pManager->GetComp();
	if (number_of_switchs <= 4)   // 3la el window 
	{
		count5 = true;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
		{
			int x = number_of_switchs - 1;
			string temp = arr[m];
			for (int i = 0; i < num; i++)
			{
				SWITCH * s = dynamic_cast<SWITCH *>(c[i]);
				if (s)
				{
					if (temp[x] == '0') {
						s->setstatus(LOW);   pOut->DrawMsg1("low.", x1, y);   x1 += 40;
					}
					else
					{
						s->setstatus(HIGH);    pOut->DrawMsg1("high. ", x1, y);   x1 += 40;
					}
					x--;
				}
			}
			pManager->SimulateCirc();

			for (int i = 0; i < num; i++)
			{
				LED * L = dynamic_cast<LED *>(c[i]);
				if (L)
				{
					if (L->getstat() == LOW)
					{
						pOut->DrawMsg1("LED :low ..", x_output, y);  x_output += 10;
					}
					else
					{
						pOut->DrawMsg1("LED :high ..", x_output, y);  x_output += 10;
					}

				}

			}
			y += 30;
			x1 = 5;
			x_output = 400;

		} // for 
	} // beta3et el if <= 4
	else
	{
		ofstream fout;    fout.open("C:\\Users\\SHAIMAA\\Desktop\\nemo\\final\\truthtable.txt", ios::out);
		int num1 = 1;    int num2 = 1;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
		{
			int x = number_of_switchs - 1;
			string temp = arr[m];
			for (int i = 0; i < num; i++)
			{
				SWITCH * s = dynamic_cast<SWITCH *>(c[i]);
				if (s)
				{
					if (temp[x] == '0') {
						s->setstatus(LOW);  fout << "switch" << num1 << "is low.";  num1++;
					}
					else
					{
						s->setstatus(HIGH);    fout << "switch" << num1 << "is high."; num1++;
					}

					x--;
				}
			}
			pManager->SimulateCirc();

			num1 = 1;
			fout << endl << endl;
			for (int i = 0; i < num; i++)
			{
				LED * L = dynamic_cast<LED *>(c[i]);
				if (L)
				{
					if (L->getstat() == LOW)
					{
						fout << "LED:" << num2 << "is low.";  num2++;
					}
					else
					{
						fout << "LED: " << num2 << "is high"; num2++;
					}

				}

			}
			num2 = 1;
			fout << endl << endl;

		} // for 
		fout.close();
	}
	if (count5)
		Sleep(7000);
	else {
		pOut->DrawMsg1("check the notepad file for the results....", 5, 100); Sleep(3000);
	}
	pOut->del_pwind1();
}

void  Truthtable::Undo(){}
void  Truthtable::Redo(){}


string * Truthtable::calc(int number_of_switchs)
{
	string *arr = new string[100];
	if (number_of_switchs == 1)
	{
		bitset <1> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<1>(m).to_string();
	}
	else if (number_of_switchs == 2)   {
		bitset <2> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<2>(m).to_string();
	}
	else if (number_of_switchs == 3)
	{
		bitset <3> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<3>(m).to_string();
	}
	else if (number_of_switchs == 4)
	{
		bitset <4> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<4>(m).to_string();
	}
	else if (number_of_switchs == 5)
	{
		bitset <5> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<5>(m).to_string();
	}
	else if (number_of_switchs == 6)
	{
		bitset <6> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<6>(m).to_string();
	}
	else if (number_of_switchs == 7)
	{
		bitset <7> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<7>(m).to_string();
	}
	else if (number_of_switchs == 8)
	{
		bitset <8> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<8>(m).to_string();
	}
	else if (number_of_switchs == 9)
	{
		bitset <9> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<9>(m).to_string();
	}
	else if (number_of_switchs == 10)
	{
		bitset <10> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<10>(m).to_string();
	}
	else if (number_of_switchs == 11)    {
		bitset <11> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<11>(m).to_string();
	}
	else if (number_of_switchs == 12)
	{
		bitset <12> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<12>(m).to_string();
	}
	else if (number_of_switchs == 13)  {
		bitset <13> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<13>(m).to_string();
	}
	else if (number_of_switchs == 14)
	{
		bitset <14> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<14>(m).to_string();
	}
	else if (number_of_switchs == 15)
	{
		bitset <15> mybits;
		for (int m = 0; m < pow(2, number_of_switchs); m++)
			arr[m] = bitset<15>(m).to_string();
	}

	return arr;
}
Truthtable::~Truthtable(void)
{

}


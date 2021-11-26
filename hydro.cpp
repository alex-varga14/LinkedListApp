// file: hydro.cpp
// author: Alex Varga
// version: 1.1
// date: 12th november 2020
#include "list.h"
#include "hydro.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

int main ()
{
	FlowList list;
	displayHeader();
	int numRecords = readData(list);
	int quit = 0;
	//Switch statement to implement menu
	while(1)
	{
		switch(menu()){
			case 1:
				display(list);
				pressEnter();
				break;
			case 2:
				addData(list);
				pressEnter();
				break;
			case 3:
				saveData(list);
				pressEnter();
				break;
			case 4:
				removeData(list);
				pressEnter();
				break;
			case 5:
				cout <<"\nProgram Terminated!\n";
				quit = 1;
				break;
			default:
				cout << "\nNot a valid input\n";
				pressEnter();
		}
		if(quit == 1) break;
	}
}
/*
 * Menu functions
 */ 
void displayHeader()
{
	cout << "Program: Flow Studies" << endl << "Version 1.1" << endl << "Produced By: Alex Varga" << endl << "<<< Press Enter to Continue>>>" << endl;
}
	
int readData(FlowList& aList)
{
	int count = 0;
	int year = 0;
	double flow = 0.0;
	ifstream infile;
	infile.open(filename);
	if(infile.fail())
	{
		cerr << "File could not be opened properly" << endl;
		exit(1);
	}
	while(!infile.eof())
	{
		infile >> year >> flow;
		aList.insert(year, flow);
		count++;
	}
	infile.close();
	return count;
}

int menu()
{
	int user;
	cout << "Please select on the following operations" << endl;
	cout << "1. Display flow list, and the average" << endl;
	cout << "2. Add Data" << endl;
	cout << "3. Save Data into the file" << endl;
	cout << "4. Remove data" << endl;
	cout << "5. Quit" << endl;
	cout << "Enter your choice (1, 2, 3, 4, 5):" << endl;
	cin >> user;
	return user;
}

void display(const FlowList& aList)
{
	Node *p = aList.front();
	cout << "Year       Flow (in billions of cubic meters)" << endl;
	while(p != NULL)
	{
		cout << p->item.year << "        " << p->item.flow << endl;
		p = p->next;
	}
	cout << "The annual average of the flow is: " << average(aList) << " million cubic meter\n" << endl;
}

FlowList& addData(FlowList& aList)
{
	int newyear;
	double newflow;
	cout << "Please enter a year: " << endl;
	cin >> newyear;
	cout << "Please enter the flow " << endl;
	cin >> newflow;
	aList.insert(newyear, newflow);
	return aList;
}
	
FlowList& removeData(FlowList& aList)
{
	int deadyear;
	cout << "Enter Year To Remove: ";
	cin >> deadyear;
	aList.remove(deadyear);
	return aList;
}

void saveData(FlowList& aList)
{
	ofstream outfile;
	outfile.open(filename);
	if(outfile.fail())
	{
		cerr << "\nFailed to Open File" << endl;
		exit(1);
	}
	Node *p = aList.front();
	while(p != NULL)
	{
		outfile << p->item.year << "        " << p->item.flow << endl;
		p = p->next;
	}
	outfile.close();
	cout << "Data Saved Into File";
	
}

void pressEnter()
{
	cout << "\n<<<Press Enter to Continue>>>\n" << endl;
	cin.get();
	
	if(cin.get() == '\n')
	{
		ifstream input(filename);
		
		if(input.fail())
		{
			cerr <<"Error Opening File. Terminated.\n";
			exit(1);
		}
		input.close();
	}
}

double average(const FlowList& aList)
{
	Node *p = aList.front();
	double count = 0.0;
	double sum;
	while(p != NULL)
	{
		sum += p->item.flow;
		count++;
		p = p->next;
	}
	return sum/=count;
}	
// file: hydro.h
// author: Alex Varga
// version: 1.0
// date: 12th november 2020
#ifndef HYDRO_H
#define HYDRO_H
#include "list.h"
#include<fstream>
using namespace std;

//Input file read by hydro.cpp
const char* filename = "C:\\C\\labs\\lab8\\flow.txt";

//Function prototypes

void displayHeader(); 

int readData (FlowList& aList); 

int menu();

void display(const FlowList& aList);

FlowList& addData(FlowList& aList);

FlowList& removeData(FlowList& aList); 

double average(const FlowList& aList); 

void saveData(FlowList& aList); 

void pressEnter(); 

#endif
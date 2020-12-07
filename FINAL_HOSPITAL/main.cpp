#include "mainFunctions.h"
#include "hospital.h"
#include <iostream>
using namespace std;


void main()
{
	// declaration of variables
	int select;  // select the user action from the menu

	ifstream inFile("hospitalData.bin", ios::binary);
	Hospital hospital(inFile);
	inFile.close();
	// loop untill the user enter 11 to finish execution of actions from the menu
	do
	{
		menuPrint();  // print menu select to the screen

		cin >> select;  // get the desired action from the user
		cout << endl;
		legalSelect(select, 1, EXIT);  // check if the number of action is legal
		if ((select >= 1) && (select <= 12))
		{
			menu(select, hospital);  // execute the desired action from the menu
		}

	} while (select != EXIT);
	ofstream outFile("hospitalData.bin", ios::binary | ios::trunc);
	hospital.save(outFile);
	outFile.close();
	cout << "data saved successfully\n" << endl;
}





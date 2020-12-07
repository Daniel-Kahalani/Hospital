#ifndef __EMPLOYEE_H
#define __EMPLOYEE_H
#pragma warning(disable: 4290)
#include <iostream>
#include <fstream>
#include "employeeGenarator.h"
#include "hospitalExceptions.h"

using namespace std;

class Employee
{
private:
	static int counter;

protected:
	//attributes
	string name;
	int employeeID;
	void decreaseCounter();

public:
	//constructor function
	Employee(const string& name);
	Employee(ifstream & inFile);
	//destructor function
	virtual ~Employee();

	//set functions
	void setName(const string& name) throw (EmployeeException);

	//get functions
	const string& getName()   const;
	int getEmployeeID()   const;

	friend ostream& operator<<(ostream& os, const Employee& other);

	friend bool spellCheck(const string& newName);

	virtual Employee* clone() const = 0;

	void saveType(ofstream & outFile)const;

	virtual void save(ofstream & outFile)const=0;

};
#endif


#pragma warning(disable: 4996)

#include "employee.h"
#include <string>

//create an Employee
Employee::Employee(const string& name)
{
	setName(name);
	employeeID = ++counter;
}

Employee::Employee(ifstream & inFile) 
{
	int length;

	inFile.read((char *)&length, sizeof(length));
	name.resize(length);
	inFile.read((char*)name.c_str(), length);

	inFile.read((char *)&employeeID, sizeof(employeeID));
	counter = employeeID;
}

//delete an Employee
Employee::~Employee()
{
}

// set the employee's name
void Employee::setName(const string& name)
{

	if (spellCheck(name) == false)
	{
		throw EmployeeException(name);
	}
	this->name = name;
}

//this function return the employee's name 
const string& Employee::getName() const
{
	return name;
}

//this function return the employee's ID 
int Employee::getEmployeeID() const
{
	return employeeID;
}

ostream& operator<<(ostream& os, const Employee& other)
{
	os << "Name: " << other.getName().c_str() << "  Employee number: " << other.getEmployeeID();
	return os;
}


void Employee::save(ofstream & outFile)const
{
	int length = name.length();
	outFile.write((const char *)&length, sizeof(length));
	outFile.write(name.c_str(), length);
	outFile.write((const char *)&employeeID, sizeof(employeeID));
}

void Employee::saveType(ofstream & outFile)const
{
	EmployeeGenerator::eEmployeeType type = EmployeeGenerator::getType(this);
	outFile.write((const char *)&type, sizeof(EmployeeGenerator::eEmployeeType));
}

void Employee::decreaseCounter()
{
	counter--;
}

int Employee::counter = 0;



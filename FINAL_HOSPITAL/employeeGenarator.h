#ifndef __EMPLOYEE_GENERATOR_H
#define __EMPLOYEE_GENERATOR_H

#include <fstream>


using namespace std;

class Employee;

class EmployeeGenerator
{
public:
	enum eEmployeeType {UNKNOWN,NURSE,DOCTOR,SURGEON,REASERCHER,REASERCHER_DOCTOR, REASERCHER_SURGEON};

	static Employee* loadEmployee(ifstream & inFile);
	static eEmployeeType getType(const Employee * employee);
};
#endif 

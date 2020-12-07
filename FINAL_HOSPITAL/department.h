#ifndef __DEPARTMENT_H
#define __DEPARTMENT_H

#include "employee.h"
#include "patient.h"
#include "nurse.h"
#include "researcherDoctor.h"
#include "researcherSurgeon.h"
#include <iostream>
#include <vector>
using namespace std;

class Department
{
private:
	//attributes
	string name;
	vector<Employee*> allStaffMembers;
	vector<Patient*> allPatients;

public:
	//constructor function
	Department(string & name);
	Department(ifstream & inFile);
	//copy constructor function
	Department(const Department& other);
	//destructor function
	~Department();
	// placement operator
	const Department& operator=(const Department& other);

	//get functions
	const string & getName()               const;
	vector<Employee*> getAllStaffMembers() const;
	int getNumOfStaffMembers()             const;
	vector<Patient*> getAllPatients()      const;
	int getNumOfPatients()                 const;

	// set function
	void setName(string & name) throw (DepartmentNameException);

	// add functions
	const Department& operator+=(Employee & newStaffMember);// throw (staffMemberException);
	const Department& operator+=(Patient & newPatient); //    throw (PatientException);

	//ostream operator
	friend ostream& operator<<(ostream& os, const Department& department);

	//show function
	void showAllPatients()       const;
	void showAllStaffMembers()   const;

	// function that checks if the name of the department is legal
	friend bool spellCheck(const string & name);

	void save(ofstream & outFile) const;
};
#endif


#pragma warning(disable: 4996)

#include "department.h"
#include <iostream>
using namespace std;


//create a Department
Department::Department(string & name)
{
	setName(name);
}

Department::Department(ifstream & inFile)
{
	int length;
	inFile.read((char *)&length, sizeof(length));
	name.resize(length);
	inFile.read((char *)name.c_str(), length);
	inFile.read((char *)&length, sizeof(length));
	for (int i = 0; i < length; i++)
	{
		allStaffMembers.push_back(EmployeeGenerator::loadEmployee(inFile));
	}

	inFile.read((char *)&length, sizeof(length));
	for (int i = 0; i < length; i++)
	{
		allPatients.push_back(new Patient(inFile));
		allPatients[i]->getAllPatientVisits()[allPatients[i]->getNumOfVisits() - 1]->setDepartment(this);
	}
}

//copy a Department
Department::Department(const Department & other)
{
	*this = other;
}

//delete a Department
Department::~Department()
{
	vector<Employee*>::const_iterator itr1 = allStaffMembers.begin();
	vector<Employee*>::const_iterator itrEnd1 = allStaffMembers.end();
	for (; itr1 != itrEnd1; ++itr1)
	{
		delete (*itr1);
	}
	allStaffMembers.clear();

	vector<Patient*>::const_iterator itr2 = allPatients.begin();
	vector<Patient*>::const_iterator itrEnd2 = allPatients.end();
	for (; itr2 != itrEnd2; ++itr2)
	{
		delete (*itr2);
	}
	allPatients.clear();
}

//Placement operator
const Department&::Department::operator=(const Department& other)
{
	if (this != &other)
	{
		name = other.name;
		allStaffMembers = other.allStaffMembers;
		allPatients = other.allPatients;
	}
	return *this;
}

//this function return the department's name 
const string & Department::getName() const
{
	return name;
}

//this function return the all the employees in the department
vector<Employee*> Department::getAllStaffMembers() const
{
	return allStaffMembers;
}

//this function return how many employees in the department
int Department::getNumOfStaffMembers() const
{
	return allStaffMembers.size();
}

//this function return the all the patients in the department
vector<Patient*> Department::getAllPatients() const
{
	return allPatients;
}

//this function return how many patients in the department
int Department::getNumOfPatients() const
{
	return allPatients.size();
}

// set the department's name
void Department::setName(string & name)
{
	if (spellCheck(name) == false)
	{
		throw DepartmentNameException(name);
	}
	this->name = name;
}

// add new employee to the department
const Department& Department::operator+=(Employee & newStaffMember)
{
	allStaffMembers.push_back(&newStaffMember);
	return *this;
}

// add new patient to the department
const Department&::Department::operator+=(Patient & newPatient)
{
	allPatients.push_back(&newPatient);
	return *this;
}

// ostream operator
ostream& operator<<(ostream& os, const Department& department)
{
	os << department.getName();
	return os;
}

// this function show to the screen all the patients in the department
void Department::showAllPatients() const
{
	vector<Patient*>::const_iterator itr = allPatients.begin();
	vector<Patient*>::const_iterator itrEnd = allPatients.end();

	if (itr == itrEnd)
	{
		cout << "There are no patients in this department" << endl;
	}
	else
	{
		int i = 0;
		cout << "All the patients in the department: " << endl;
		for (; itr != itrEnd; ++itr)
		{
			cout << i + 1 << ". " << (**itr) << endl;
			i++;
		}
	}
	cout << endl;
}

// this show to the screen all the staff members of in the department
void Department::showAllStaffMembers() const
{
	vector<Employee*>::const_iterator itr = allStaffMembers.begin();
	vector<Employee*>::const_iterator itrEnd = allStaffMembers.end();

	if (itr == itrEnd)
	{
		cout << "There are no staff members in the hospital" << endl;
	}
	else
	{
		int i = 0;
		cout << "All the staff members in the department: " << endl;
		for (; itr != itrEnd; ++itr)
		{
			cout << i + 1 << ". " << (**itr) << endl;
			i++;
		}
	}
	cout << endl;
}

void Department::save(ofstream & outFile) const
{
	int length = name.length();
	outFile.write((const char *)&length, sizeof(length));
	outFile.write(name.c_str(), length);
	length = allStaffMembers.size();
	outFile.write((const char*)&length, sizeof(length));
	vector<Employee*>::const_iterator itr1 = allStaffMembers.begin();
	vector<Employee*>::const_iterator itrEnd1 = allStaffMembers.end();
	for (; itr1 != itrEnd1; ++itr1)
	{
		int objType = EmployeeGenerator::getType(*itr1);
		outFile.write((const char *)&objType, sizeof(objType));
		(*itr1)->save(outFile);
	}

	length = allPatients.size();
	outFile.write((const char*)&length, sizeof(length));
	vector<Patient*>::const_iterator itr2 = allPatients.begin();
	vector<Patient*>::const_iterator itrEnd2 = allPatients.end();
	for (; itr2 != itrEnd2; ++itr2)
	{
		(*itr2)->save(outFile);
	}
}


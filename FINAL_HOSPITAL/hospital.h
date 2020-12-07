#pragma once
#ifndef __HOSPITAL_H
#define __HOSPITAL_H

#include "researchInstitute.h"
#include "department.h"
#include "patient.h"
#include <iostream>
using namespace std;

const int NOT_EXIST = -1;

class Hospital
{
private:
	//attributes
	vector<Department*> allDepartments;
	vector<Employee*> allStaffMembers;
	vector<Patient*> allPatients;
	ResearchInstitute researchInstitute;

public:
	//constructor function
	Hospital();
	Hospital(ifstream & inFile);
	//copy constructor function
	Hospital(const Hospital & other);
	//destructor function
	~Hospital();
	// placement operator
	const Hospital& operator=(const Hospital& other);

	//get functions
	vector<Department*> getAllDepartments()      const;
	int getNumOfDepartments()                    const;
	vector<Employee*> getAllStaffMembers()       const;
	int getNumOfStaffMembers()                   const;
	vector<Patient*> getAllPatients()            const;
	int getNumOfPatients()                       const;
	ResearchInstitute  & getResearchInstitute();

	//add + set functions
	void addDepartment(Department & newDepartment);                        //     throw (departmentException);
	void addStaffMember(Employee & newStaffMember, int deparmentIndex);  //       throw (staffMemberException);
	void addPatient(Patient & newPatient, int deparmentIndex)                  throw (PatientExistException);
	void setResearchInstitute(const ResearchInstitute & newResearchInstitute);

	//show functions
	void showAllDeparments()     const;
	void showAllStaffMembers()   const;

	// search patient in hospital function
	int searchPatientIndex(int id) const;

	void save(ofstream & outFile) const;
};
#endif



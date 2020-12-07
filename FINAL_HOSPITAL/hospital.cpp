#pragma warning(disable: 4996)

#include "hospital.h"
#include <iostream>
#include <string>
using namespace std;

//create an Hospital
Hospital::Hospital()
{
	researchInstitute;
}

Hospital::Hospital(ifstream & inFile):researchInstitute(inFile)
{
	int departmentsLength;
	inFile.read((char*)&departmentsLength, sizeof(departmentsLength));
	for (int i = 0; i < departmentsLength; i++)
	{
		allDepartments.push_back(new Department(inFile));
	}
	int staffMembersLength;
	inFile.read((char*)&staffMembersLength, sizeof(staffMembersLength));
	for (int i = 0; i < staffMembersLength; i++)
	{
		allStaffMembers.push_back(EmployeeGenerator::loadEmployee(inFile));
	}
	int patientLength;
	inFile.read((char*)&patientLength, sizeof(patientLength));
	for (int i = 0; i < patientLength; i++)
	{
		allPatients.push_back(new Patient(inFile));
	//	allPatients[i]->getAllPatientVisits()[allPatients[i]->getNumOfVisits() - 1]->setStaffMember(allStaffMembers[0]);
	}
}

//copy an Hospital
Hospital::Hospital(const Hospital & other)
{
	*this = other;
}

//delete an Hospital
Hospital::~Hospital()
{
	vector<Patient*>::iterator itr1 = allPatients.begin();
	vector<Patient*>::iterator itrEnd1 = allPatients.end();
	for (; itr1 != itrEnd1; ++itr1)
	{
		delete (*itr1);
	}
	allPatients.clear();

	vector<Employee*>::const_iterator itr2 = allStaffMembers.begin();
	vector<Employee*>::const_iterator itrEnd2 = allStaffMembers.end();
	for (; itr2 != itrEnd2; ++itr2)
	{
		delete (*itr2);
	}
	allStaffMembers.clear();

	vector<Department*>::const_iterator itr3 = allDepartments.begin();
	vector<Department*>::const_iterator itrEnd3 = allDepartments.end();
	for (; itr3 != itrEnd3; ++itr3)
	{
		delete (*itr3);
	}
	allDepartments.clear();
}

const Hospital&::Hospital::operator=(const Hospital& other)
{
	if (this != &other)
	{
		allDepartments = other.allDepartments;
		allStaffMembers = other.allStaffMembers;
		allPatients = other.allPatients;
		setResearchInstitute(other.researchInstitute);
	}
	return *this;
}

//this function return all the departments in the hospital 
vector<Department*> Hospital::getAllDepartments() const
{
	return allDepartments;
}

//this function return how many departments in the hospital
int Hospital::getNumOfDepartments() const
{
	return allDepartments.size();
}

//this function return all the employees in the hospital
vector<Employee*> Hospital::getAllStaffMembers() const
{
	return allStaffMembers;
}

//this function return how many employees in the hospital
int Hospital::getNumOfStaffMembers() const
{
	return allStaffMembers.size();
}

//this function return all the patients in the hospital
vector<Patient*> Hospital::getAllPatients() const
{
	return allPatients;
}

//this function return how many patients in the hospital
int Hospital::getNumOfPatients() const
{
	return allPatients.size();
}

//this function return the research institute in the hospital 
ResearchInstitute &Hospital::getResearchInstitute()
{
	return researchInstitute;
}

// add new department to the hospital
void Hospital::addDepartment(Department & newDepartment)
{
	allDepartments.push_back(&newDepartment);
}

// add new employee to the hospital and to the department to which he belongs
void Hospital::addStaffMember(Employee & newStaffMember, int deparmentIndex)
{
	allStaffMembers.push_back(&newStaffMember);
	*allDepartments[deparmentIndex] += newStaffMember;
	Researcher * temp = dynamic_cast<Researcher*>(&newStaffMember);
	if (temp != nullptr)
	{
		researchInstitute.addResearcher(*temp->clone());
	}
}

// add new patient to the hospital and to the department to which he belongs
void Hospital::addPatient(Patient & newPatient, int deparmentIndex)
{
	bool patientExist = false;
	for (unsigned int i = 0; (i < allPatients.size()) && (patientExist == false); i++)
	{
		if (*allPatients[i] == newPatient)
		{
			patientExist = true;
			throw PatientExistException();
		}
	}
	allPatients.push_back(&newPatient);
	*allDepartments[deparmentIndex] += newPatient;
}

// set the research institute
void Hospital::setResearchInstitute(const ResearchInstitute & researchInstitute)
{
	this->researchInstitute = researchInstitute;
}

//this function show to the screen the name of all the departments in the hospital 
void Hospital::showAllDeparments() const
{
	vector<Department*>::const_iterator itr = allDepartments.begin();
	vector<Department*>::const_iterator itrEnd = allDepartments.end();

	if (itr == itrEnd)
	{
		cout << "There are no departments in the hospital" << endl;
	}
	else
	{
		int i = 0;
		cout << "All the departments in the hospital : " << endl;
		for (; itr != itrEnd; ++itr)
		{
			cout << i + 1 << ". " << (**itr) << endl;
			i++;
		}
	}
	cout << endl;
}

/*this function show to the screen the name,
employee I.D and area of residency of all the doctors in the hospital */
void Hospital::showAllStaffMembers() const
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
		cout << "All the staff members in the hospital : " << endl;
		for (; itr != itrEnd; ++itr)
		{
			cout << i + 1 << ". " << (**itr) << endl;
			i++;
		}
	}
	cout << endl;
}

/*this function get as input an id.
the function return the index of the patient in the array of all patients in the hospital.
if the patient does not exist, the function return -1. */
int Hospital::searchPatientIndex(int id) const
{
	bool found = false;
	int i = 0;
	while (((unsigned int)i < (allPatients.size())) && (found == false))
	{
		if (id == allPatients[i]->getPatientID())
		{
			found = true;
		}
		else
		{
			i++;
		}
	}
	if (i != allPatients.size())
	{
		return i;
	}
	else
	{
		return NOT_EXIST;
	}
}

void Hospital::save(ofstream & outFile) const
{
	int length = allDepartments.size();
	researchInstitute.save(outFile);
	outFile.write((const char*)&length, sizeof(length));
	for (int i = 0; i < length; i++)
	{
		allDepartments[i]->save(outFile);
	}

	length = allStaffMembers.size();
	outFile.write((const char*)&length, sizeof(length));
	for (int i = 0; i < length; i++)
	{
		int objType = EmployeeGenerator::getType(allStaffMembers[i]);
		outFile.write((const char*)&objType, sizeof(objType));
		allStaffMembers[i]->save(outFile);
	}

	length = allPatients.size();
	outFile.write((const char*)&length, sizeof(length));
	for (int i = 0; i < length; i++)
	{
		allPatients[i]->save(outFile);
	}
}


#pragma warning(disable: 4996)
#include <string>
#include <iostream>
using namespace std;

#include "patient.h"

const char* genderArr[2] = { "MALE", "FEMALE" };

//create a Patient
Patient::Patient(string & name, int patientID, int yearOfBirth, eGender gender, VisitCard & nowVisit)
{
	setName(name);
	setPatientID(patientID);
	setYearOfBirth(yearOfBirth);
	setGender(gender);
	addVisit(nowVisit);
}

Patient::Patient(ifstream & inFile)
{
	int length;
	inFile.read((char*)&length, sizeof(length));
	name.resize(length);
	inFile.read((char*)name.c_str(), length);
	inFile.read((char*)&patientID, sizeof(patientID));
	inFile.read((char*)&yearOfBirth, sizeof(yearOfBirth));
	inFile.read((char*)&gender, sizeof(int));
	inFile.read((char*)&length, sizeof(length));
	for (int i = 0; i < length; i++)
	{
		allPatientVisits.push_back(VisitGenarator::loadVisitCard(inFile));
	}
}

//copy a Patient
Patient::Patient(const Patient& other)
{
	*this = other;
}

//delete a Patient
Patient::~Patient()
{
	vector<VisitCard*>::const_iterator itr = allPatientVisits.begin();
	vector<VisitCard*>::const_iterator itrEnd = allPatientVisits.end();
	for (; itr != itrEnd; ++itr)
	{
		delete (*itr);
	}
	allPatientVisits.clear();
}

//placement operator
const Patient&::Patient::operator=(const Patient& other)
{
	if (this != &other)
	{
		name = other.name;
		patientID = other.patientID;
		yearOfBirth = other.yearOfBirth;
		gender = other.gender;
		allPatientVisits = other.allPatientVisits;
	}
	return *this;
}

//this function return the patient's name 
const string& Patient::getName() const
{
	return name;
}

//this function return the patient's id 
int Patient::getPatientID() const
{
	return patientID;
}

//this function return the patient's date of birth
int Patient::getYearOfBirth() const
{
	return yearOfBirth;
}

//this function return the patient's gender
Patient::eGender Patient::getGender() const
{
	return gender;
}

//this function return all the visits of the patient 
vector<VisitCard *> Patient::getAllPatientVisits() const
{
	return allPatientVisits;
}

//this function return how many visits the patient has
int Patient::getNumOfVisits() const
{
	return allPatientVisits.size();
}

// set the patient's name
void Patient::setName(string & name)
{
	if (spellCheck(name) == false)
	{
		throw PatientNameException(name);
	}
	this->name = name;
}

// set the patient's id
void Patient::setPatientID(int patientID)
{
	this->patientID = patientID;
}

// set the patient's year of birth
void Patient::setYearOfBirth(int yearOfBirth)
{
	this->yearOfBirth = yearOfBirth;
}

// set the patient's gender
void Patient::setGender(eGender gender)
{
	this->gender = gender;
}

// add new visit to the patient
void Patient::addVisit(VisitCard & newVisit)
{
	allPatientVisits.push_back(&newVisit);
}


// ostream operator
ostream& operator<<(ostream& os, const Patient& patient)
{
	if (typeid(*patient.getAllPatientVisits()[patient.getNumOfVisits() - 1]) == typeid(VisitCard))
	{
		os << "Patient's name: " << patient.getName() << "  Patient's ID: " << patient.getPatientID() << "  Patient's reason of visit: check - up  ";
	}
	else
	{
		os << "Patient's name: " << patient.getName() << "  Patient's ID: " << patient.getPatientID() << "  Patient's reason of visit: surgery  ";
	}

	return os;
}

bool Patient::operator==(const Patient& other) const
{
	if (patientID == other.patientID)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Patient::save(ofstream & outFile) const
{
	int length = name.length();
	outFile.write((const char *)&length, sizeof(int));
	outFile.write(name.c_str(), length);
	outFile.write((const char *)&patientID, sizeof(int));
	outFile.write((const char *)&yearOfBirth, sizeof(int));
	outFile.write((const char *)&gender, sizeof(int));
	length = allPatientVisits.size();
	outFile.write((const char *)&length, sizeof(length));
	for (int i = 0; i < length; i++)
	{
		int objType = VisitGenarator::getType(allPatientVisits[i]);
		outFile.write((const char *)&objType, sizeof(length));
		allPatientVisits[i]->save(outFile);
	}
}


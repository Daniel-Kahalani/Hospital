#ifndef __PATIENT_H
#define __PATIENT_H

//#include "date.h"
#include "visitCard.h"
#include "surgeryVisitCard.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Patient
{
public:
	enum eGender { MALE, FEMALE };
private:
	//attributes
	string name;
	int patientID;
	int yearOfBirth;
	eGender gender;
	vector<VisitCard *> allPatientVisits;

public:
	//constructor function
	Patient(string & name, int patientID, int yearOfBirth, eGender gender, VisitCard & nowVisit);
	Patient(ifstream & inFile);
	//copy constructor function
	Patient(const Patient& other);
	//destructor function
	~Patient();
	//placement operator
	const Patient& operator=(const Patient& other);

	// set functions
	void setName(string & name)          throw (PatientException);
	void setPatientID(int patientID);
	void setYearOfBirth(int yearOfBirth);
	void setGender(eGender gender);
	void addVisit(VisitCard & newVisit);

	//get functions
	const string& getName()                   const;
	int getPatientID()                        const;
	int getYearOfBirth()                      const;
	eGender getGender()                       const;
	vector<VisitCard *> getAllPatientVisits() const;
	int getNumOfVisits()                      const;

	//ostream operator
	friend ostream& operator<<(ostream& os, const Patient& patient);

	bool operator==(const Patient& other)   const;

	friend bool spellCheck(const string& name);

	void save(ofstream & outFile) const;
};
#endif


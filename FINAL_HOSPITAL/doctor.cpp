#pragma warning(disable: 4996)

#include "doctor.h"
#include <iostream>
#include <string>
using namespace std;

//create a Doctor
Doctor::Doctor(const string& name, const string&  areaOfResidency) : Employee(name)
{
	setAreaOfResidency(areaOfResidency);
}

Doctor::Doctor(ifstream & inFile) : Employee(inFile)
{
	int length;

	inFile.read((char *)&length, sizeof(length));
	areaOfResidency.resize(length);
	inFile.read((char*)areaOfResidency.c_str(), length);
}

//delete a Doctor
Doctor::~Doctor()
{
}


// set the doctor's area of residency
void Doctor::setAreaOfResidency(const string& areaOfResidency)
{
	if (spellCheck(areaOfResidency) == false)
	{
		this->decreaseCounter();
		throw DoctorException(areaOfResidency);
	}
	this->areaOfResidency = areaOfResidency;
}

//this function return the doctor's area of residency 
const string& Doctor::getAreaOfResidency() const
{
	return areaOfResidency;
}

Employee* Doctor::clone()const
{
	return new Doctor(*this);
}

void Doctor::save(ofstream & outFile)const
{
	Employee::save(outFile);
	int length = areaOfResidency.length();
	outFile.write((const char *)&length, sizeof(length));
	outFile.write(areaOfResidency.c_str(), length);
}
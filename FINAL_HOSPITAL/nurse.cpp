#pragma warning(disable: 4996)

#include "nurse.h"
#include <iostream>
#include <string>

using namespace std;

//create a Nurse
Nurse::Nurse(const string& name, int yearsOfExperience) : Employee(name)
{
	setYearsOfExperience(yearsOfExperience);
}

Nurse::Nurse(ifstream & inFile):Employee(inFile)
{
	inFile.read((char *)&yearsOfExperience, sizeof(yearsOfExperience));
}

// set the nurse's years of experience
void Nurse::setYearsOfExperience(int yearsOfExperience)
{
	if (yearsOfExperience < 0)
	{
		this->decreaseCounter();
		throw NurseException(yearsOfExperience);
	}
	this->yearsOfExperience = yearsOfExperience;
}

//this function return the nurse's years of experience 
int Nurse::getYearsOfExperience() const
{
	return yearsOfExperience;
}

Employee* Nurse::clone()const
{
	return new Nurse(*this);
}

void Nurse::save(ofstream & outFile)const
{
	Employee::save(outFile);
	outFile.write((const char *)&yearsOfExperience, sizeof(yearsOfExperience));
}

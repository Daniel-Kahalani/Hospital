#include "surgeon.h"
#include <iostream>
#include <string>

using namespace std;

//create a Surgeon
Surgeon::Surgeon(const Doctor& doctor, int numOfSurgeries) : Employee(doctor.getName()), Doctor(doctor)
{
	this->employeeID--;
	decreaseCounter();
	setNumOfSurgeries(numOfSurgeries);
}

Surgeon::Surgeon(ifstream & inFile) : Employee(inFile), Doctor(inFile)
{
	inFile.read((char *)&numOfSurgeries, sizeof(numOfSurgeries));
}

// set the Surgeon's number of surgeries
void Surgeon::setNumOfSurgeries(int numOfSurgeries)
{
	if (numOfSurgeries < 0)
	{
		this->decreaseCounter();
		throw SurgeonException(numOfSurgeries);
	}
		this->numOfSurgeries = numOfSurgeries;
}

//this function return the surgeon's number of surgeries 
int Surgeon::getNumOfSurgeries() const
{
	return numOfSurgeries;
}

Employee* Surgeon::clone()const
{
	return new Surgeon(*this);
}

void Surgeon::save(ofstream & outFile)const
{
	Doctor::save(outFile);
	outFile.write((const char *)&numOfSurgeries, sizeof(numOfSurgeries));
}
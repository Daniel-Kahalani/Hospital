#ifndef __NURSE_H
#define __NURSE_H

#include "employee.h"
using namespace std;

class Nurse : public Employee
{
private:
	//attribute
	int yearsOfExperience;

public:
	//constructor function
	Nurse(const string& name, int yearsOfExperience = 0);
	Nurse(ifstream & inFile);

	//set function
	void setYearsOfExperience(int yearsOfExperience)throw (NurseException);

	//get function
	int getYearsOfExperience()   const;

	virtual Employee* clone() const override;

	virtual void save(ofstream & outFile)const;
};
#endif



#ifndef __DOCTOR_H
#define __DOCTOR_H

#include "employee.h"
using namespace std;

class Doctor : virtual public Employee
{

protected:
	//attribute
	string areaOfResidency;

public:
	//constructor function
	Doctor(const string& name,const string& areaOfResidency);
	Doctor(ifstream & inFile);
	//destructor function
	virtual ~Doctor();

	//set functions
	void setAreaOfResidency(const string& areaOfResidency)throw (DoctorException);

	//get functions
	const string& getAreaOfResidency()   const;

	virtual Employee* clone() const override;

	virtual void save(ofstream & outFile)const;
};
#endif


#ifndef __SURGEON_H
#define __SURGEON_H

#include "doctor.h"

class Surgeon : public Doctor
{
private:
	//attribute
	int numOfSurgeries;

public:
	//constructor function
	Surgeon(const Doctor& doctor, int numOfSurgeries = 0);
	Surgeon(ifstream & inFile);

	//set function
	void setNumOfSurgeries(int numOfSurgeries)throw (SurgeonException);

	//get function
	int getNumOfSurgeries()   const;

	virtual Employee* clone() const override;
	virtual void save(ofstream & outFile)const;
};
#endif


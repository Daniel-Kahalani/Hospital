#ifndef __RESEARCHER_DOCTOR_H
#define __RESEARCHER_DOCTOR_H

#include "doctor.h"
#include "researcher.h"

class ResearcherDoctor : public Doctor, public Researcher
{

public:
	//constructor function
	ResearcherDoctor(const Doctor& doctor);
	ResearcherDoctor(ifstream & inFile);

	virtual Employee* clone() const override;

	virtual void save(ofstream & outFile)const;
};
#endif



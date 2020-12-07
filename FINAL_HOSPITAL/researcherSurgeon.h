#ifndef __RESEARCHER_SURGEON_H
#define __RESEARCHER_SURGEON_H

#include "surgeon.h"
#include "researcher.h"

class ResearcherSurgeon : public Surgeon, public Researcher
{

public:
	//constructor function
	ResearcherSurgeon(const Surgeon& surgeon);
	ResearcherSurgeon(ifstream & inFile);

	virtual Employee* clone() const override;
	virtual void save(ofstream & outFile)const;
};
#endif



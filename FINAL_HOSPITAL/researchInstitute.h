#ifndef __RESEARCH_INSTITUTE_H
#define __RESEARCH_INSTITUTE_H

#include "researcher.h"
#include <vector>
class ResearchInstitute
{
private:
	//attributes
	vector<Employee*> allResearchers;

public:
	//constructor function
	ResearchInstitute();
	ResearchInstitute(ifstream & inFile);
	//copy constructor function
	ResearchInstitute(const ResearchInstitute& other);
	//destructor function
	~ResearchInstitute();

	const ResearchInstitute& operator=(const ResearchInstitute& other);

	//set function
	void addResearcher(Employee& newResearcher);

	//get functions
	vector<Employee*> getAllResearchers()const;
	int getNumOfResearchers() const;

	//show function
	void showAllResearchers() const;

	virtual void save(ofstream & outFile)const;

};
#endif



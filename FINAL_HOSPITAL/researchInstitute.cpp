#include "researchInstitute.h"
#include <iostream>
using namespace std;

//create a ResearchInstitute
ResearchInstitute::ResearchInstitute() 
{
}

ResearchInstitute::ResearchInstitute(ifstream & inFile) 
{
	int length;
	inFile.read((char *)&length, sizeof(length));
	for (int i = 0; i < length; i++)
	{
		allResearchers.push_back(EmployeeGenerator::loadEmployee(inFile));
	}
}

//copy a ResearchInstitute
ResearchInstitute::ResearchInstitute(const ResearchInstitute& other)
{
	*this = other;
}

//delete a ResearchInstitute
ResearchInstitute::~ResearchInstitute()
{
	vector<Employee*>::const_iterator itr = allResearchers.begin();
	vector<Employee*>::const_iterator itrEnd = allResearchers.end();
	for (; itr != itrEnd; ++itr)
	{
		delete (*itr);
	}
	allResearchers.clear();
}

const ResearchInstitute& ResearchInstitute::operator=(const ResearchInstitute& other)
{
	if (this != &other)
	{
		allResearchers = other.allResearchers;
	}
	return *this;
}

// add new researcher to the research institute
void ResearchInstitute::addResearcher(Employee& newResearcher)
{
	allResearchers.push_back(newResearcher.clone());
}

//this function return all the researchers of the research institute 
vector<Employee*> ResearchInstitute::getAllResearchers() const
{
	return allResearchers;
}

//this function return how many researchers in the research institute 
int ResearchInstitute::getNumOfResearchers() const
{
	return allResearchers.size();
}

//this function show to the screen the name and employee id of all the researchers in the research institute
void ResearchInstitute::showAllResearchers() const
{
	if (getNumOfResearchers() != 0)
	{
		cout << "The research institute has these researchers:\n" << endl;
		int length = getNumOfResearchers();
		for (int i = 0; i < length; i++)
		{
			cout << i + 1 << ". " << *allResearchers[i] << endl;
		}
		cout << endl;

	}
	else
	{
		cout << "There are not researchers in the research institute\n" << endl;
	}
}

void ResearchInstitute::save(ofstream & outFile)const
{
	int length = allResearchers.size();
	outFile.write((const char *)&length, sizeof(length));
	for (int i = 0; i < length; i++)
	{
		int objType = EmployeeGenerator::getType(allResearchers[i]);
		outFile.write((const char *)&objType, sizeof(length));
		allResearchers[i]->save(outFile);
	}

}

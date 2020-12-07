#pragma warning(disable: 4996)

#include "researcherDoctor.h"
#include <iostream>
#include <string>

using namespace std;

//create a ResearcherDoctor
ResearcherDoctor::ResearcherDoctor(const Doctor& doctor) : Employee(doctor.getName()), Doctor(doctor), Researcher(doctor.getName())
{
	this->employeeID = employeeID - 1;
	decreaseCounter();
}

ResearcherDoctor::ResearcherDoctor(ifstream & inFile) : Employee(inFile),Doctor(inFile),Researcher(inFile)
{
}

Employee* ResearcherDoctor::clone()const
{
	return new ResearcherDoctor(*this);
}

void ResearcherDoctor::save(ofstream & outFile)const
{
	Doctor::save(outFile);

	int length = allArticles.size();
	outFile.write((const char *)&length, sizeof(length));
	vector<Article*>::const_iterator itr = allArticles.begin();
	vector<Article*>::const_iterator itrEnd = allArticles.end();
	for (; itr != itrEnd; ++itr)
	{
		(*itr)->save(outFile);
	}
}
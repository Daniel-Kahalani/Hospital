#include "researcherSurgeon.h"
#include <iostream>
#include <string>

using namespace std;

//create a ResearcherDoctor
ResearcherSurgeon::ResearcherSurgeon(const Surgeon& surgeon) : Employee(surgeon.getName()), Surgeon(surgeon), Researcher(surgeon.getName())
{
	this->employeeID--;
	decreaseCounter();
}

ResearcherSurgeon::ResearcherSurgeon(ifstream & inFile) : Employee(inFile), Surgeon(inFile), Researcher(inFile)
{
}

Employee* ResearcherSurgeon::clone()const
{
	return new ResearcherSurgeon(*this);
}

void ResearcherSurgeon::save(ofstream & outFile)const
{
	Surgeon::save(outFile);

	int length = allArticles.size();
	outFile.write((const char *)&length, sizeof(length));
	vector<Article*>::const_iterator itr = allArticles.begin();
	vector<Article*>::const_iterator itrEnd = allArticles.end();
	for (; itr != itrEnd; ++itr)
	{
		(*itr)->save(outFile);
	}
}


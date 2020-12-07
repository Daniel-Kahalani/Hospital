#pragma warning(disable: 4996)

#include "researcher.h"
#include <iostream>
using namespace std;

//create a Researcher
Researcher::Researcher(const string& name) :Employee(name)
{

}

Researcher::Researcher(ifstream & inFile) : Employee(inFile)
{
	int length;
	inFile.read((char *)&length, sizeof(length));
	for (int i = 0; i < length; i++)
	{
		allArticles.push_back(new Article(inFile));
	}
}

//copy a Researcher
Researcher::Researcher(const Researcher& other) : Employee(other)
{
	*this = other;
}

//delete a Researcher
Researcher::~Researcher()
{
	vector<Article*>::const_iterator itr = allArticles.begin();
	vector<Article*>::const_iterator itrEnd = allArticles.end();
	for (; itr != itrEnd; ++itr)
	{
		delete (*itr);
	}
	allArticles.clear();
}

const Researcher& Researcher::operator=(const Researcher& other)
{
	if (this != &other)
	{
		this->Employee::operator=(other);
		allArticles = other.allArticles;
	}
	return *this;
}

// add new article to the researcher
bool Researcher::addArticle(Article& newArticle)
{
	allArticles.push_back(&newArticle);
	return true;
}

//this function return how many articles the researcher has
vector<Article*> Researcher::getAllArticles()
{
	return allArticles;
}

//this function return all the articles of the researcher 
int Researcher::getNumOfArticles() const
{
	return allArticles.size();
}

bool Researcher::operator>(const Researcher& other) const
{
	return allArticles.size() > other.allArticles.size();
}

Employee* Researcher::clone() const
{
	return new Researcher(*this);
}

void Researcher::save(ofstream & outFile)const
{
	Employee::save(outFile);
	int length = allArticles.size();
	outFile.write((const char *)&length, sizeof(length));
	vector<Article*>::const_iterator itr = allArticles.begin();
	vector<Article*>::const_iterator itrEnd = allArticles.end();
	for (; itr != itrEnd; ++itr)
	{
		(*itr)->save(outFile);
	}
}

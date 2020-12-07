#ifndef __RESEARCHER_H
#define __RESEARCHER_H

#include "article.h"
#include "employee.h"
#include <vector>

class Researcher : virtual public Employee
{
protected:

	//attributes
	vector<Article*> allArticles;

public:

	//constructor function
	Researcher(const string& name);
	Researcher(ifstream & inFile);
	//copy constructor function
	Researcher(const Researcher& other);

	//destructor function
	virtual ~Researcher();

	const Researcher& operator=(const Researcher& other);

	//set function
	bool addArticle(Article& newArticle);

	//get functions
	vector<Article*> getAllArticles();
	int getNumOfArticles() const;

	bool operator>(const Researcher& other) const;

	virtual Employee* clone() const override;

	virtual void save(ofstream & outFile)const;
};
#endif


#ifndef __ARTICLE_H
#define __ARTICLE_H
#include "date.h"

using namespace std;

class Article
{
private:
	//attributes
	string name;
	string magazineName;
	Date  datePublished;

	//	bool spellCheck(const char* newName) const;//לברר פונקציית friend בעובד

public:

	//constructor function
	Article(const string& name, const string& magazineName, Date datePublished);
	Article(ifstream & inFile);

	//set functions
	void setName(const string& name) throw (ArticleException);
	void setMagazineName(const string& magazineName);
	void setDatePublished(Date datePublished);

	//get functions
	const string& getName()   const;
	const string& getMagazineName()   const;
	Date getDatePublished()   const;

	friend bool spellCheck(const string& newName);

	void save(ofstream & outFile)const;
};
#endif


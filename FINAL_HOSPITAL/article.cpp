#include "article.h"
#include <iostream>
#include <string>

//create an Article
Article::Article(const string& name, const string& magazineName, Date datePublished) : name(name), magazineName(magazineName), datePublished(datePublished)
{
	setName(name);
}

Article::Article(ifstream & inFile):datePublished(inFile)
{
	int length;

	inFile.read((char *)&length, sizeof(length));
	name.resize(length);
	inFile.read((char*)name.c_str(), length);

	inFile.read((char *)&length, sizeof(length));
	magazineName.resize(length);
	inFile.read((char*)magazineName.c_str(), length);
}

// set the article's name
void Article::setName(const string& name)
{
	if (spellCheck(name) == false)
	{
		throw ArticleException(name);
	}
	this->name = name;

}

// set the name of the magazine that the article was published 
void Article::setMagazineName(const string& magazineName)
{
	this->magazineName = magazineName;
}

// set the article's publication date 
void Article::setDatePublished(Date datePublished)
{
	this->datePublished = datePublished;
}

//this function return the article's name 
const string& Article::getName() const
{
	return name;
}

//this function return the name of the magazine that the article was published
const string& Article::getMagazineName() const
{
	return magazineName;
}

//this function return the article's publication date
Date Article::getDatePublished() const
{
	return datePublished;
}

//this function return true if the name contains only legal characters otherwise return false

bool spellCheck(const string& newName)
{
	int i = 0;
	bool check = true;
	while ((newName[i] != NULL)&&(check==true))
	{
		if (((newName[i] >= 'a') && (newName[i] <= 'z')) || ((newName[i] >= 'A') && (newName[i] <= 'Z')) || (newName[i] == ' '))
		{
			check = true;
		}
		else
		{
			check = false;
		}
		i++;
	}
	return check;
}

void Article::save(ofstream & outFile)const
{
	int length = name.length();
	datePublished.save(outFile);
	outFile.write((const char *)&length, sizeof(length));
	outFile.write(name.c_str(), length);
	length = magazineName.length();
	outFile.write((const char *)&length, sizeof(length));
	outFile.write(magazineName.c_str(), length);
}
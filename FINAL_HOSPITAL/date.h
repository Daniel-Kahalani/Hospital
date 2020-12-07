#ifndef __DATE_H
#define __DATE_H
#pragma warning(disable: 4290)
#include <fstream>
#include "hospitalExceptions.h"

using namespace std;


const int LEAP_YEAR = 0;
const int MAX_DAY_IN_MONTH = 31;
const int MAX_DAY_IN_EDATE_MONTH = 30;
const int MAX_DAY_IN_FEBRUARY = 28;
const int MAX_DAY_IN_FEBRUARY_LEAP_YEAR = 29;
const int MAX_MONTH_IN_YEAR = 12;

class Date
{
private:
	//attributes
	int day, month, year;
	int howManyDays() const;
	enum eDate {FEBRUARY=2,APRIL=4, JUNE=6, SEPTEMBER=9, NOVEMBER=11};

public:

	//constructor function
	Date(int day, int month, int year);
	Date(ifstream & inFile);

	//set functions
	void setDay(int day) throw (DayException);
	void setMonth(int month) throw (MonthException);
	void setYear(int year) throw (YearException);

	//get functions
	int getDay()   const;
	int getMonth() const;
	int getYear()  const;

	//ostream operator
	friend ostream& operator<<(ostream& os, const Date& other);
	void save(ofstream & outFile)const;
};
#endif



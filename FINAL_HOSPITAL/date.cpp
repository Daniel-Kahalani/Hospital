#include "date.h"

//create a Date
Date::Date(int day, int month, int year)
{
	setYear(year);
	setMonth(month);
	setDay(day);
}

Date::Date(ifstream & inFile)
{
	inFile.read((char *)this, sizeof(*this));
}

//this function return the date's day 
int Date::getDay() const
{
	return day;
}

//this function return the date's month 
int Date::getMonth() const
{
	return month;
}

//this function return the date's year 
int Date::getYear() const
{
	return year;
}

// set the date's day 
void Date::setDay(int day)
{
	int daylimit = howManyDays();
	if ((day < 1) || (day > daylimit))
	{
		throw DayException(day, daylimit);
	}
	this->day = day;
	
}

// set the date's month 
void Date::setMonth(int month)
{
	if ((month < 1 )|| (month > MAX_MONTH_IN_YEAR))
	{
		throw MonthException(month);
	}
	this->month = month;
}

// set the date's year 
void Date::setYear(int year)
{
	if (year < 0)
	{
		throw YearException(year);
	}
	this->year = year;
}

//this function returns how many days there is in the month
int Date::howManyDays() const
{
	if ((month == APRIL) || (month == JUNE) || (month == SEPTEMBER) || (month == NOVEMBER))
	{
		return MAX_DAY_IN_EDATE_MONTH;
	}
	if (month == FEBRUARY)
	{
		if (year % 4 == LEAP_YEAR)
		{
			return MAX_DAY_IN_FEBRUARY_LEAP_YEAR;
		}
		else
		{
			return MAX_DAY_IN_FEBRUARY;
		}
	}
	else
	{
		return MAX_DAY_IN_MONTH;
	}
}

//ostream operator
ostream& operator<<(ostream& os, const Date& other)
{
	os << other.getDay() << "/" << other.getMonth() << "/" << other.getYear();
	return os;
}

void Date::save(ofstream & outFile)const
{
	outFile.write((const char *)this, sizeof(*this));
}
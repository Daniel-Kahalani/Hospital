#ifndef __HOSPITAL_EXCEPTIONS_H_
#define __HOSPITAL_EXCEPTIONS_H_

#include <iostream>
#include <string>
using namespace std;

class HospitalExceptions
{
public:
	virtual void show() const = 0;
};

class EmployeeException :public HospitalExceptions
{
private:
	string name;
public:

	EmployeeException(const string &name) :name(name) {}

	virtual void show() const override
	{
		cout << "Error: the name " << name << " is not valid for an employee,must contain only letters (a-z,A-Z)" << endl;
	}
};

class StaffMemberException :public HospitalExceptions//כנראה מותר
{
public:
	virtual void show() const override
	{
		cout << "Error: this staff member is not exist" << endl;
	}
};

class StaffMemberExistException :public HospitalExceptions//כנראה מיותר
{
public:
	virtual void show() const override
	{
		cout << "Error: this staff member is already exist" << endl;
	}
};

class NurseException :public HospitalExceptions
{
private:
	int yearsOfExperience;
public:

	NurseException(int yearsOfExperience) :yearsOfExperience(yearsOfExperience) {}

	virtual void show() const override
	{
		cout << "Error: years of experience " << yearsOfExperience << " is not valid for a nurse, must be equel to or bigger than zero" << endl;
	}
};

class DoctorException :public HospitalExceptions
{
private:
	string areaOfResidency;
public:

	DoctorException(const string& areaOfResidency) :areaOfResidency(areaOfResidency) {}

	virtual void show() const override
	{
		cout << "Error: the area of residency " << areaOfResidency << " is not valid for a doctor, must contain only letters (a-z,A-Z)" << endl;
	}
};

class SurgeonException :public HospitalExceptions
{
private:
	int numOfSurgeries;
public:

	SurgeonException(int numOfSurgeries) :numOfSurgeries(numOfSurgeries) {}

	virtual void show() const override
	{
		cout << "Error: the num of surgeries " << numOfSurgeries << " is not valid for a surgeon, must be equel to or bigger than zero" << endl;
	}
};

class DepartmentException :public HospitalExceptions//כנראה מיותר
{
public:
	virtual void show() const override
	{
		cout << "Error: this department is not exist" << endl;
	}
};

class DepartmentNameException :public HospitalExceptions
{
private:
	string name;
public:

	DepartmentNameException(const string& name) : name(name) {}

	virtual void show() const override
	{
		cout << "Error: the name " << name << " is not valid for a department, must contain only letters (a-z,A-Z)" << endl;
	}
};

class ArticleException :public HospitalExceptions
{
private:
	string magazineName;
public:

	ArticleException(const string& magazineName) :magazineName(magazineName) {}

	void show() const override
	{
		cout << "Error: the magazine name " << magazineName << " is not valid for an article, must contain only letters (a-z,A-Z)" << endl;
	}
};

class YearException :public HospitalExceptions
{
private:
	int year;
public:

	YearException(int year) :year(year) {}

	virtual void show() const override
	{
		cout << "Error: the year " << year << " is not valid for a date, must be bigger than zero" << endl;
	}
};

class MonthException :public HospitalExceptions
{
private:
	int month;
public:

	MonthException(int month) :month(month) {}

	virtual void show() const override
	{
		cout << "Error: the month " << month << " is not valid for a date, must be between 1 - 12" << endl;
	}
};

class DayException :public HospitalExceptions
{
private:
	int day;
	int maxDays;
public:

	DayException(int day, int maxDays) :day(day), maxDays(maxDays) {}

	virtual void show() const override
	{
		cout << "Error: the day " << day << " is not valid for this month, must be between 1 - " << maxDays << endl;
	}
};

class PatientException :public HospitalExceptions//לברר אם צריך
{
public:

	virtual void show() const override
	{
		cout << "Error: this patient is not exist" << endl;
	}
};

class PatientExistException :public HospitalExceptions
{
public:

	virtual void show() const override
	{
		cout << "Error: A patient with this i.d is already exist\n" << endl;
	}
};

class PatientNameException :public HospitalExceptions
{
private:
	string name;
public:

	PatientNameException(const string &name) :name(name) {}

	virtual void show() const override
	{
		cout << "Error: the name " << name << " is not valid for a patient,must contain only letters (a-z,A-Z) " << endl;
	}
};

class OperatingRoomException :public HospitalExceptions
{
private:
	int operatingRoom;
public:

	OperatingRoomException(int operatingRoom) : operatingRoom(operatingRoom) {}

	virtual void show() const override
	{
		cout << "Error: room number " << operatingRoom << " is not valid for an operating room, room number must be a positive number" << endl;
	}
};
#endif
#pragma once
#ifndef __VISIT_CARD_H
#define __VISIT__CARD_H

class Employee;
class Department;

#include "date.h"
#include "visitGenarator.h"
#include <iostream>
#include <fstream>
using namespace std;

class VisitCard
{
public:
	enum  eVisitEnded { YES, NO };
private:
	//attributes
	Date arrivalDate;
	eVisitEnded visitEnded;
	Employee * staffMember;
	Department * department;
//	int staffMemberId;
//	string departmentName;

public:

	//constructor function
	VisitCard(Date arrivalDate, eVisitEnded visitEnded, Employee * staffMember, Department * department);
	VisitCard(ifstream & inFile);
	virtual ~VisitCard();

	//set functions
	void setArrivalDate(Date arivalDate);
	void setVisitEnded(eVisitEnded visitEnded);
	void setStaffMember(Employee * staffMember);// throw (staffMemberException);
	void setDepartment(Department * department);// throw (departmentException);

	//get functions
	Date getArrivalDate()                  const;
	eVisitEnded getVisitEnded()            const;
	Employee * getStaffMember()            const;
	Department * getDepartment()           const;

	// clone function 
	virtual VisitCard* clone()             const;

	void saveType(ofstream & outFile)      const;

	virtual void save(ofstream & outFile)  const;
};
#endif#pragma once


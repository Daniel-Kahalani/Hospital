#pragma warning(disable: 4996)
#include <iostream>
#include <string>
using namespace std;

#include "visitCard.h"
#include "department.h"


const char * reasonOfVisitArr[2] = { "EXAMINATION" , "SURGERY" };
const char * visitEndedArr[2] = { "YES" , "NO" };

//create a VisitCard
VisitCard::VisitCard(Date arrivalDate, eVisitEnded visitEnded, Employee * staffMember, Department * department)
	: arrivalDate(arrivalDate), staffMember(nullptr), department(nullptr)
{
	setArrivalDate(arrivalDate);
	setVisitEnded(visitEnded);
	setStaffMember(staffMember);
	setDepartment(department);
}

VisitCard::VisitCard(ifstream & inFile) : arrivalDate(inFile)
{
//	int length;
	inFile.read((char *)&visitEnded, sizeof(visitEnded));
//	inFile.read((char *)&length, sizeof(length));
//	departmentName.resize(length);
//	inFile.read((char *)departmentName.c_str(), length);
//	inFile.read((char *)&staffMemberId, sizeof(staffMemberId));

}

VisitCard:: ~VisitCard()
{
}

//this function return the visit's date 
Date VisitCard::getArrivalDate() const
{
	return arrivalDate;
}

//this function return if the visit end  or not
VisitCard::eVisitEnded VisitCard::getVisitEnded() const
{
	return visitEnded;
}

//this function return the doctor that treat the patient  לבדוק אם מיותר
Employee * VisitCard::getStaffMember() const
{
	return staffMember;
}

//this function return the deparment that the patient treat in לבדוק אם מיותר
Department * VisitCard::getDepartment() const
{
	return department;
}

// set the visit's date 
void VisitCard::setArrivalDate(Date arivalDate)
{
	this->arrivalDate = arrivalDate;
}

// set if the visit end or not
void VisitCard::setVisitEnded(eVisitEnded visitEnded)
{
	this->visitEnded = visitEnded;
}

// set the doctor that treat the patient
void VisitCard::setStaffMember(Employee * staffMember)
{
//	if (staffMember == nullptr)
//	{
//		throw staffMemberException();
//	}
	this->staffMember = staffMember;
}

// set the deparment that the patient treat in
void VisitCard::setDepartment(Department * department)
{
//	if (department == nullptr)
//	{
//		throw departmentException();
//	}
	this->department = department;
}

VisitCard * VisitCard::clone() const
{
	return new VisitCard(*this);
}

void VisitCard::saveType(ofstream & outFile) const
{
	VisitGenarator::eVisitType type = VisitGenarator::getType(this);
	outFile.write((const char *)&type, sizeof(VisitGenarator::eVisitType));
}

void VisitCard::save(ofstream & outFile) const
{
	arrivalDate.save(outFile);
	outFile.write((const char *)&visitEnded, sizeof(visitEnded));
//	string name=department->getName();
//	int length = name.length();
//	outFile.write((const char *)&length, sizeof(length));
//	outFile.write(name.c_str(), length);
//	int id = staffMember->getEmployeeID();
//	outFile.write((const char *)&id, sizeof(id));

}




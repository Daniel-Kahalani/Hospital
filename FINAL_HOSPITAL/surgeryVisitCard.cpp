#pragma warning(disable: 4996)
#include <iostream>
#include <string>
using namespace std;

#include "surgeryVisitCard.h"

const char * patientFastingArr[2] = { "YES" , "NO" };

// create a surgery visit card
SurgeryVisitCard::SurgeryVisitCard(const VisitCard& visitCard, int operatingRoom, ePatientFasting patientFasting)
	: VisitCard(visitCard)
{
	setOperatingRoom(operatingRoom);
	setPatientFasting(patientFasting);
}

SurgeryVisitCard::SurgeryVisitCard(ifstream & inFile) : VisitCard(inFile)
{
	inFile.read((char *)&operatingRoom, sizeof(int));
	inFile.read((char *)&patientFasting, sizeof(int));
}

// set the surgery room number
void SurgeryVisitCard::setOperatingRoom(int operatingRoom)
{
	if (operatingRoom <= 0)
	{
		throw OperatingRoomException(operatingRoom);
	}
	this->operatingRoom = operatingRoom;
}

// set if the patient in fast
void SurgeryVisitCard::setPatientFasting(ePatientFasting patientFasting)
{
	this->patientFasting = patientFasting;
}

// this function return the surgery room number
int SurgeryVisitCard::getOperatingRoom() const
{
	return operatingRoom;
}

// this function return if the patient in fast
SurgeryVisitCard::ePatientFasting SurgeryVisitCard::getPatientFasting() const
{
	return patientFasting;
}

VisitCard*::SurgeryVisitCard::clone() const
{
	return new SurgeryVisitCard(*this);
}

void SurgeryVisitCard::save(ofstream & outFile) const
{
	VisitCard::save(outFile);
	outFile.write((const char *)&operatingRoom, sizeof(int));
	outFile.write((const char *)&patientFasting, sizeof(int));
}
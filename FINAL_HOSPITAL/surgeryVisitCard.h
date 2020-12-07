#pragma once
#ifndef __SURGERY_VISIT_CARD_H
#define __SURGERY_VISIT_CARD_H

#include "visitCard.h"
#include <iostream>
using namespace std;

class SurgeryVisitCard : public VisitCard
{
public:
	enum  ePatientFasting { YES, NO };
private:
	//attributes
	int operatingRoom;
	ePatientFasting patientFasting;

public:

	//constructor function
	SurgeryVisitCard(const VisitCard& visitCard, int operatingRoom, ePatientFasting patientFasting);
	SurgeryVisitCard(ifstream & inFile);

	//set functions
	void setOperatingRoom(int operatingRoom) throw (OperatingRoomException);
	void setPatientFasting(ePatientFasting patientFasting);

	//get functions
	int getOperatingRoom()                 const;
	ePatientFasting getPatientFasting()    const;

	// clone function 
	virtual VisitCard* clone()             const override;

	virtual void save(ofstream & outFile)  const;

};
#endif



#include "employeeGenarator.h"
#include "researcherDoctor.h"
#include "researcherSurgeon.h"
#include "nurse.h"


Employee* EmployeeGenerator::loadEmployee(ifstream & inFile)
{
	eEmployeeType type;
	inFile.read((char *)&type, sizeof(int));
	switch (type)
	{
	case NURSE:
	{
		return new Nurse(inFile);
	}
	break;
	case DOCTOR:
	{
		return new Doctor(inFile);
	}
	break;
	case SURGEON:
	{
		return new Surgeon(inFile);
	}
	break;
	case REASERCHER:
	{
		return new Researcher(inFile);
	}
	break;
	case REASERCHER_DOCTOR:
	{
		return new ResearcherDoctor(inFile);
	}
	break;
	case REASERCHER_SURGEON:
	{
		return new ResearcherSurgeon(inFile);
	}
	break;
	default :
	{
		return NULL;
	}
	break;
	}
}

EmployeeGenerator::eEmployeeType EmployeeGenerator::getType(const Employee * employee)
{
	if (typeid(*employee) == typeid(Nurse))
	{
		return NURSE;
	}
	else if (typeid(*employee) == typeid(Doctor))
	{
		return DOCTOR;
	}
	else if (typeid(*employee) == typeid(Surgeon))
	{
		return SURGEON;
	}
	else if (typeid(*employee) == typeid(Researcher))
	{
		return REASERCHER;
	}
	else if (typeid(*employee) == typeid(ResearcherDoctor))
	{
		return REASERCHER_DOCTOR;
	}
	else if (typeid(*employee) == typeid(ResearcherSurgeon))
	{
		return REASERCHER_SURGEON;
	}
	else
	{
		return UNKNOWN;
	}

}
#pragma warning(disable: 4996)

#include "visitGenarator.h"
#include "visitCard.h"
#include "surgeryVisitCard.h"

VisitCard * VisitGenarator::loadVisitCard(ifstream & inFile)
{
	eVisitType type;
	inFile.read((char *)&type, sizeof(int));
	switch (type)
	{
	case VISIT_CARD:
		return new VisitCard(inFile);
		break;

	case SURGERY_VISIT_CARD:
		return new SurgeryVisitCard(inFile);
		break;

	default:
		return NULL;
		break;
	}
}

VisitGenarator::eVisitType VisitGenarator::getType(const VisitCard * visit)
{
	if (typeid(*visit) == typeid(VisitCard))
	{
		return VISIT_CARD;
	}
	else if (typeid(*visit) == typeid(SurgeryVisitCard))
	{
		return SURGERY_VISIT_CARD;
	}
	else
	{
		return UNKNOWN;
	}
}
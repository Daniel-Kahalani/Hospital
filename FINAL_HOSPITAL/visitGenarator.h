#ifndef __VISIT_GENERATOR_H
#define __VISIT_GENERATOR_H

#include <fstream>


using namespace std;

class VisitCard;

class VisitGenarator
{
public:
	enum eVisitType { UNKNOWN, VISIT_CARD, SURGERY_VISIT_CARD };

	static VisitCard * loadVisitCard(ifstream & inFile);
	static eVisitType getType(const VisitCard * visit);
};
#endif 

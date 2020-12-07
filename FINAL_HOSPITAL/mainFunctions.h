
#ifndef Hospital
#define Hostpital
#include "hospital.h"
#include <stdio.h>
#include <string.h>
#include <vector>

const int NAME_LENGTH = 20;   // maximum characters in any name
const int DOCTOR = 1;
const int SURGEON = 2;
const int RESEARCHER_DOCTOR = 3;
const int RESEARCHER_SURGEON = 4;
const int CHECKUP = 0;
const int SURGERY = 1;
const int EMPTY_ERROR = -1;
const int NEW_PATIENT = -2;
const int NOT_VISITED = 0;
const int VISITED = 1;
const int EXIT = 13;

// assistance functions
void menu(int select, Hospital & hospital);
void menuPrint();

void addDoctor(Hospital & hospital);
void addPatient(Hospital & hospital);
void searchPatient(Hospital & hospital);
void compareTwoResearchers(Hospital & hospital);

int chooseResearcher(ResearchInstitute & resIns);
int chooseStaffMember(Hospital & hospital, int departmentIndex);
int chooseDeparment(Hospital & hospital);
int chooseDoctorType();
int chooseVisitType();
Patient::eGender choosePatientGender();
SurgeryVisitCard::ePatientFasting IsPatientFest();
bool staffMemberExits(Hospital & hospital, int departmentIndex);

//general functions
void legalSelect(int &select, int leftRange, int rightRange);
void cleanBuffer();


// functions that gets input from the user
Department* readDeparment();
Nurse* readNurse();
Doctor* readDoctor();
Researcher* readResearcher();
Surgeon* readSurgeon();
ResearcherSurgeon* readResearcherSurgeon();
ResearcherDoctor* readResearcherDoctor();
Patient* readPatient(Hospital & hospital, int departmentIndex);
VisitCard* readVisitCard(Hospital & hospital, int departmentIndex);
SurgeryVisitCard* readSurgeryVisitCard(Hospital & hospital, int departmentIndex);
Article* readArticle();
Date* readDate();

#endif


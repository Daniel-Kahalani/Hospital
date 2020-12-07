#pragma warning(disable: 4996)//אפשר לבטל לבדוקק
#pragma warning(disable: 4715)///לבדוק
#include "mainFunctions.h"
#include <iostream>
using namespace std;


/*----------------------Assistance functions--------------------------*/

/* this function gets a reference to hospital and a choice of desired action.
the function execute the desired action from the menu. */

void menu(int select, Hospital & hospital)
{
	switch (select)
	{
	// add a department to the hospital
	case 1:
	{
		hospital.addDepartment(*readDeparment());
	}
	break;
	// add a nurse to the hospital and to the department to which she belongs
	case 2:
	{
		int deparmentIndex = chooseDeparment(hospital);
		if (deparmentIndex != EMPTY_ERROR)
		{
			hospital.addStaffMember(*readNurse(), deparmentIndex);
		}
	}
	break;
	// add a doctor to the hospital and to the department to which he belongs
	case 3:
	{
		addDoctor(hospital);
	}
	break;
	// add new visit to a patient - if the patient does not exist add new patient to the hospital and to the department to which he belongs
	case 4:
	{
		addPatient(hospital);
	}
	break;
	// add a researcher to the research institute
	case 5:
	{
		hospital.getResearchInstitute().addResearcher(*readResearcher());
	}
	break;
	// add an article to a researcher
	case 6:
	{
		int researcherIndex = chooseResearcher(hospital.getResearchInstitute());
		if (researcherIndex != EMPTY_ERROR)
		{
			Researcher* temp = dynamic_cast<Researcher*>(hospital.getResearchInstitute().getAllResearchers()[researcherIndex]);
			if (temp != NULL)
			{
				temp->addArticle(*readArticle());
			}
		}
	}
	break;
	// show all patients associated with a particular department
	case 7:
	{
		int deparmentIndex = chooseDeparment(hospital);
		if (deparmentIndex != EMPTY_ERROR)
		{
			hospital.getAllDepartments()[deparmentIndex]->showAllPatients();
		}
	}
	break;
	// show all the medical staff in the hospital
	case 8:
	{
		hospital.showAllStaffMembers();
	}
	break;
	// show all the researchers in the hospital
	case 9:
	{
		hospital.getResearchInstitute().showAllResearchers();
	}
	break;
	// search patient in the hospital by i.d - if the patient exists, show his name and the department to which he belongs
	case 10:
	{
		searchPatient(hospital);
	}
	break;
	// show all the researchers in the hospital that are also doctors
	case 11:
	{
		vector<Employee *> allReseaarcher = hospital.getResearchInstitute().getAllResearchers();
		int length = hospital.getResearchInstitute().getNumOfResearchers();
		for (int i = 0; i < length; i++)
		{
			if (typeid(*allReseaarcher[i]) != typeid(Researcher))
			{
				cout << *allReseaarcher[i] << endl;
			}

		}
		cout << endl;
	}
	break;
	// check operator '>' that compares between two researchers by the amount of their articles
	case 12:
	{
		compareTwoResearchers(hospital);
	}
	break;
	}
}


// this function show to the screen all the menu actions
void menuPrint()
{
	cout << "Please choose the desired action:\n" << "1. Add a deparment to the hospital\n" << "2. Add a nurse to the hospital\n" <<
		"3. Add a doctor to the hospital\n" << "4. Add a visit to a certain patient\n" << "5. Add a researcher to the research institute\n" <<
		"6. Add an article to a certain researcher\n" << "7. Show all the patients of a certain deparment\n" << "8. Show all the staff of the hospital\n" <<
		"9. Show all the researchers\n" << "10. Search for a patient by I.D\n" << "11. Show all the researchers who are also doctors\n" <<
		"12. Check operator '>' that compares between two researchers by the amount of their articles\n" << "13. Save and exit\n" << endl;
	cout << "the chosen number is: ";
}

void addDoctor(Hospital & hospital)
{
	int deparmentIndex = chooseDeparment(hospital);
	if (deparmentIndex != EMPTY_ERROR)
	{
		int doctortType = chooseDoctorType();
		switch (doctortType)
		{
		case 1:
		{
			hospital.addStaffMember(*readDoctor(), deparmentIndex);
		}
		break;
		case 2:
		{
			hospital.addStaffMember(*readSurgeon(), deparmentIndex);
		}
		break;
		case 3:
		{
			hospital.addStaffMember(*readResearcherDoctor(), deparmentIndex);
		}
		break;
		case 4:
		{
			hospital.addStaffMember(*readResearcherSurgeon(), deparmentIndex);
		}
		break;
		}
	}
}

void addPatient(Hospital & hospital)
{
	int visitedPatient, patientID, patientIndex, departmentIndex;
	cout << "Please enter if the patient has been visited in the hospital before: 1 - visited / 0 - not visited: ";
	cin >> visitedPatient;
	cout << endl;
	legalSelect(visitedPatient, NOT_VISITED, VISITED);
	if (visitedPatient == VISITED)
	{
		cout << "Please insert the patient's I.D : ";
		cin >> patientID;
		cout << endl;
		patientIndex = hospital.searchPatientIndex(patientID);
		if (patientIndex == NOT_EXIST)
		{
			cout << "Error: There is no patient with this i.d number\n" << endl;
		}
		else
		{
			departmentIndex = chooseDeparment(hospital); // choose the department to which the patient belongs
			if ((departmentIndex != EMPTY_ERROR) && (staffMemberExits(hospital, departmentIndex) == true)) // if it is legel choise of department 
			{
				// add new visit to the patient
				if (chooseVisitType() == CHECKUP)
				{
					hospital.getAllPatients()[patientIndex]->addVisit(*readVisitCard(hospital, departmentIndex));
				}
				else
				{
					hospital.getAllPatients()[patientIndex]->addVisit(*readSurgeryVisitCard(hospital, departmentIndex));
				}
			}
		}
	}
	else
	{
		departmentIndex = chooseDeparment(hospital); // choose the department to which the patient belongs
		if ((departmentIndex != EMPTY_ERROR) && (staffMemberExits(hospital, departmentIndex) == true)) // if it is legel choise of department
		{
			// add new patient 
			try
			{
				hospital.addPatient(*readPatient(hospital, departmentIndex), departmentIndex);
			}
			catch (PatientExistException exp)
			{
				exp.show();
			}
		}
	}
}

/* this function searches patient in the hospital by i.d number.
if the patient exists, the function shows his name and the department to which he belongs,
otherwise, print a suitable message to the screen. */

void searchPatient(Hospital & hospital)
{
	int id, patientIndex;
	cout << "Please enter the patient i.d number: ";
	cin >> id;
	cout << endl;
	patientIndex = hospital.searchPatientIndex(id);
	if (patientIndex != NOT_EXIST)
	{
		cout << *(hospital.getAllPatients()[patientIndex]) << endl;
	}
	else
	{
		cout << "Error: There is no patient with this i.d number" << endl;
	}
	cout << endl;
}


//this function compares between two researchers by the amount of their articles
void compareTwoResearchers(Hospital & hospital)
{
	int numOfResearchers = hospital.getResearchInstitute().getNumOfResearchers();
	if (numOfResearchers >= 2)
	{
		cout << "researcher number 1: ";
		int researcherIndex1 = chooseResearcher(hospital.getResearchInstitute());
		cout << "researcher number 2: ";
		int researcherIndex2 = chooseResearcher(hospital.getResearchInstitute());
		if (researcherIndex1 != researcherIndex2)
		{
			Researcher * researcher1 = dynamic_cast<Researcher*>(hospital.getResearchInstitute().getAllResearchers()[researcherIndex1]);
			Researcher * researcher2 = dynamic_cast<Researcher*>(hospital.getResearchInstitute().getAllResearchers()[researcherIndex2]);
			if (*researcher1 > *researcher2)
			{
				cout << "Researcher 1 have more articles than researcher 2\n" << endl;
			}
			else
			{
				cout << "Researcher 1  dont have more articles than researcher 2\n" << endl;
			}
		}
		else
		{
			cout << "ERROR: Please choose two different researchers\n" << endl;
		}
	}
	else
	{
		cout << "ERROR: There is not enough researchers to run the test, there must be at least 2 researchers in the hospital\n" << endl;
	}
}

/* this function gets from the user a choise of desirable researcher
and return his index in the array of all researchers in the researchInstitute.
if there is not any researchers in the researchInstitute the function prints a suitable message to the screen. */

int chooseResearcher(ResearchInstitute &resIns)
{
	int select;
	int length = resIns.getNumOfResearchers();
	if (length != 0)
	{
		cout << "Please choose the desired researcher\n" << endl;
		resIns.showAllResearchers();
		cout << "the chosen number is: ";
		cin >> select;
		legalSelect(select, 1, length);
		cout << endl;
		select--;
	}
	else
	{
		cout << "Error: There are no researchers in the research institute, please first enter a researcher\n" << endl;
		select = EMPTY_ERROR;
	}
	return select;
}

// this function gets from the user a choise of desirable staff member and return his index  

int chooseStaffMember(Hospital & hospital, int departmentIndex)
{
	int select = 0;
	int length = hospital.getAllDepartments()[departmentIndex]->getNumOfStaffMembers();
	if (length != 0)
	{
		cout << "Please choose the desired staff member" << endl;
		hospital.getAllDepartments()[departmentIndex]->showAllStaffMembers();
		cout << "the chosen number is: ";
		cin >> select;
		legalSelect(select, 1, length);
		cout << endl;
	}
	else
	{
		cout << "Error: There are no staff members in this deparment, please first enter a doctor or a nurse\n" << endl;
	}
	return select - 1;
}

/* this function gets from the user a choise of desirable deparment
and return his index in the array of all deparments in the hospital.
if there is not any deparments in the hospital the function prints a suitable message to the screen. */

int chooseDeparment(Hospital & hospital)
{
	int select;
	int length = hospital.getNumOfDepartments();
	if (length != 0)
	{
		cout << "Please choose the desired deparment" << endl;
		hospital.showAllDeparments();
		cout << "the chosen number is: ";
		cin >> select;
		legalSelect(select, 1, length);
		cout << endl;
		select--;
	}
	else
	{
		cout << "Error: There are not deparments in the hospital, please first enter a deparment\n" << endl;
		select = EMPTY_ERROR;
	}
	return select;
}

// this function gets from the user a choise of desirable doctor type and return it
int chooseDoctorType()
{
	int select;
	cout << "Please choose the desired doctor type:\n" << "1. Doctor\n" << "2. Surgeon\n" << "3. Researcher-Doctor\n" << "4. Researcher-Surgeon\n" << endl;
	cout << "the chosen number is: ";
	cin >> select;
	legalSelect(select, 1, 4);
	cout << endl;
	return select;
}

// this function gets from the user a choise of desirable visit type and return it
int chooseVisitType()
{
	int select;
	cout << "Please choose the reason of visit:" << "0 - Checkup / 1 - Surgery: ";
	cin >> select;
	cout << endl;
	legalSelect(select, 0, 1);
	return select;
}

Patient::eGender choosePatientGender()
{
	int select;
	cout << "Please insert patient's gender:" << "0 - Male / 1 - Female: ";
	cin >> select;
	cout << endl;
	legalSelect(select, 0, 1);
	return (Patient::eGender)select;
}

SurgeryVisitCard::ePatientFasting IsPatientFest()
{
	int select;
	cout << "Please insert if the patient fest:" << "0 - YES / 1 - NO: ";
	cin >> select;
	cout << endl;
	legalSelect(select, 0, 1);
	return (SurgeryVisitCard::ePatientFasting)select;
}

//this function check if in the desirable deparment there are doctors

bool staffMemberExits(Hospital & hospital, int departmentIndex)
{
	if (hospital.getAllDepartments()[departmentIndex]->getNumOfStaffMembers() != 0)
	{
		return true;
	}
	else
	{
		cout << "Error: There are no staff members in this deparment, please first enter a doctor or a nurse\n" << endl;
		return false;
	}
}

/* this function gets a desired action number from left range to right range.
if the choise of the user is ilegal(not from the range), the function will print a suitable error message
and continue getting intput from the user untill the user will enter a legal choise. */

void legalSelect(int &select, int leftRange, int rightRange)
{
	bool check = false;
	do
	{
		if ((select >= leftRange) && (select <= rightRange))
		{
			check = true;
		}
		else
		{
			cout << "Error: Please choose a number from " << leftRange << " to " << rightRange << endl;
			cout << "the chosen number is: ";
			cin >> select;
			cout << endl;
		}
	} while (check == false);
}

//this function clean the buffer
void cleanBuffer()
{
	int c;
	do
	{
		c = getchar();
	} while (c != EOF && c != '\n');
}


/*----------------------Functions that gets input from the user--------------------------*/


// this function gets a department from the user
Department* readDeparment()
{
	bool isDataVailid = false;
	cleanBuffer();
	while (!isDataVailid)
	{
		try
		{
			string name;
			cout << "Please insert the deparment's name: ";
			getline(cin, name);
			cout << endl;
			return new Department(name);
		}
		catch (DepartmentNameException& exp)
		{
			exp.show();
		}
		if ((!isDataVailid))
		{
			cout << "\nYou need to enter data again" << endl;
		}
	}

}

// this function gets a nurse from the user
Nurse* readNurse()
{
	bool isDataVailid = false;
	cleanBuffer();
	while (!isDataVailid)
	{
		try
		{
			int yearsOfExperience;
			string name;
			cout << "Please insert the nurse's name: ";
			getline(cin, name);
			cout << "Please insert the nurse's years of experience: ";
			cin >> yearsOfExperience;
			cout << endl;
			return new Nurse(name, yearsOfExperience);
		}
		catch (EmployeeException& exp)
		{
			exp.show();
		}
		catch (NurseException& exp)
		{
			exp.show();
		}
		if ((!isDataVailid))
		{
			cout << "\nYou need to enter data again" << endl;
		}
	}
}

// this function gets a doctor from the user
Doctor* readDoctor()
{
	bool isDataVailid = false;
	cleanBuffer();
	while (!isDataVailid)
	{
		try
		{
			string name, areaOfResidency;
			cout << "Please insert the doctor name: ";
			getline(cin, name);
			cout << "Please insert the doctor's area of residency: ";
			getline(cin, areaOfResidency);
			cout << endl;
			return new Doctor(name, areaOfResidency);
		}
		catch (EmployeeException& exp)
		{
			exp.show();
		}
		catch (DoctorException& exp)
		{
			exp.show();
		}
		if ((!isDataVailid))
		{
			cout << "\nYou need to enter data again" << endl;
		}
	}
}

// this function gets a researcher from the user
Researcher* readResearcher()
{
	bool isDataVailid = false;
	cleanBuffer();
	while (!isDataVailid)
	{
		try
		{
			string name;
			cout << "Please insert the reseacher's name: ";
			getline(cin, name);
			cout << endl;
			return new Researcher(name);
		}
		catch (EmployeeException& exp)
		{
			exp.show();
		}
		if ((!isDataVailid))
		{
			cout << "\nYou need to enter data again" << endl;
		}
	}
}

// this function gets a surgeon from the user
Surgeon* readSurgeon()
{
	bool isDataVailid = false;
	while (!isDataVailid)
	{
		try
		{
			int numOfSurgeries;
			cout << "Please insert the surgeon's number of surgeries: ";
			cin >> numOfSurgeries;
			return new Surgeon(*readDoctor(), numOfSurgeries);
		}
		catch (SurgeonException& exp)
		{
			exp.show();
		}
		if ((!isDataVailid))
		{
			cout << "\nYou need to enter data again" << endl;
		}
	}

}

// this function gets a researcher-surgeon from the user
ResearcherSurgeon* readResearcherSurgeon()
{
	return new ResearcherSurgeon(*readSurgeon());
}

// this function gets a researcher-doctor from the user
ResearcherDoctor* readResearcherDoctor()
{
	return new ResearcherDoctor(*readDoctor());
}

// this function gets a patient from the user
Patient* readPatient(Hospital & hospital, int departmentIndex)
{
	bool isDataVailid = false;
	cleanBuffer();
	while (!isDataVailid)
	{
		try
		{
			string name;
			int patientID, yearOfBirth;
			cout << "Please insert the patient's name: ";
			getline(cin, name);
			cout << "Please insert the patient's I.D : ";
			cin >> patientID;
			cout << "Please insert the patient's year of birth: ";
			cin >> yearOfBirth;
			if (chooseVisitType() == CHECKUP)
			{
				return new Patient(name, patientID, yearOfBirth, choosePatientGender(), *readVisitCard(hospital, departmentIndex));
			}
			else
			{
				return new Patient(name, patientID, yearOfBirth, choosePatientGender(), *readSurgeryVisitCard(hospital, departmentIndex));
			}
		}
		catch (PatientNameException& exp)
		{
			exp.show();
		}
		if ((!isDataVailid))
		{
			cout << "\nYou need to enter data again" << endl;
			cleanBuffer();
		}
	}
}

// this function gets a visit card from the user

VisitCard * readVisitCard(Hospital & hospital, int departmentIndex)
{
	
	int staffMemberIndex = chooseStaffMember(hospital, departmentIndex);
	cout << "Please insert the date of arrival of the patient " << endl;
	return new VisitCard(*readDate(), VisitCard::eVisitEnded::NO, hospital.getAllDepartments()[departmentIndex]->getAllStaffMembers()[staffMemberIndex], hospital.getAllDepartments()[departmentIndex]);
}

// this function gets a surgery visit card from the user

SurgeryVisitCard * readSurgeryVisitCard(Hospital & hospital, int departmentIndex)
{
	bool isDataVailid = false;
	cleanBuffer();
	while (!isDataVailid)
	{
		try
		{
			int operatingRoom;
			cout << "Please insert the operating room number : ";
			cin >> operatingRoom;
			return new SurgeryVisitCard(*readVisitCard(hospital, departmentIndex), operatingRoom, IsPatientFest());
		}
		catch (OperatingRoomException& exp)
		{
			exp.show();
		}
		if ((!isDataVailid))
		{
			cout << "\nYou need to enter data again" << endl;
		}
	}

}

// this function gets an article from the user
Article* readArticle()
{
	bool isDataVailid = false;
	cleanBuffer();
	while (!isDataVailid)
	{
		try
		{
			string name, magazineName;
			cout << "Please insert the article's name: ";
			getline(cin, name);
			cout << "Please insert the magazine's name where the article was published: ";
			getline(cin, magazineName);
			cout << "Please insert the article's date of published in the format of DD/MM/YYYY: " << endl;
			return new Article(name, magazineName, *readDate());
		}
		catch (ArticleException& exp)
		{
			exp.show();
		}
		if ((!isDataVailid))
		{
			cout << "\nYou need to enter data again" << endl;
		}
	}

}

// this function gets a date from the user
Date* readDate()
{
	bool isDataVailid = false;
	while (!isDataVailid)
	{
		try
		{
			int day, month, year;
			cout << "Please insert the day (1-31) : ";
			cin >> day;
			cout << "Please insert the month (1-12) : ";
			cin >> month;
			cout << "Please insert the year : ";
			cin >> year;
			cout << endl;
			return new Date(day, month, year);
		}
		catch (DayException& exp)
		{
			exp.show();
		}
		catch (MonthException& exp)
		{
			exp.show();
		}
		catch (YearException& exp)
		{
			exp.show();
		}
		if ((!isDataVailid))
		{
			cout << "\nYou need to enter data again" << endl;
		}
	}

}













#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>

struct node {
	int ppsn;
	char firstName[30];
	char secondName[30];
	int yearBorn;
	char gender;
	char email[40];
	char nokName[30];
	int lastAppointment; // dd mm yyyy
	float weight; // Kgs
	float height; // meters
	float bmi;
	char allergies;
	char cigaretters;
	char alcohol;
	char exercise;

	struct node* NEXT;
};

void AddElementAtStart(struct node** top, int ppsNumber);
void AddElementAtEnd(struct node* top, int ppsNumber);
void DeleteElementAtStart(struct node** top);
void DisplayList(struct node* top);
void loadDatabase(struct node** top);
int Listlength(struct node* top);
int searchList(struct node* top, int searchPPS);
void DeleteElementAtPos(struct node* top, int position);
void saveDatabase(struct node* top);

void login();
void displayPatient(struct node* top);
void updatePatient(struct node** top);
void updatePatientAtAdding(struct node** top, int ppsNumber);
float calculateBMI(float weight, float height);
int ppsnToPos(struct node* top, int searchPPS);
void generateStats(struct node* top);


void main()
{
	// Login system
	login();

	struct node* headPtr = NULL;
	int choice;
	int position = 0;
	int pps = 0;
	int posFound = 0;
	int patientUpdate = 0;

	// Loading database from file
	loadDatabase(&headPtr);

	do
	{
		printf("  Welcome select an option:\n");
		printf("=============================================\n");
		printf("  1 - To add a new patient\n");
		printf("  2 - To display all patients\n");
		printf("  3 - To search and display a patient details\n");
		printf("  4 - To search and update patient details\n");
		printf("  5 - To delete a patient with the patient PPSN\n");
		printf("  6 - To generate statistics\n");
		printf("  7 - To save the database\n");
		printf(" -1 - To exit\n");
		printf("=============================================\n\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("\nPlease enter patient PPSN: \n");
			scanf("%d", &pps);

			if (searchList(headPtr, pps) == 1)
			{
				printf("\nPatient already exists, enter 1 to update patient details:\n");
				scanf("%d", &patientUpdate);

				if (patientUpdate == 1)
				{
					updatePatientAtAdding(&headPtr, pps);
				}
				printf("\n");
			}
			else
			{
				if (headPtr == NULL)
					AddElementAtStart(&headPtr , pps);
				else
				{
					AddElementAtEnd(headPtr, pps);
				}
			}
			break;
		case 2:
			DisplayList(headPtr);
			break;
		case 3:
			displayPatient(headPtr);
			break;
		case 4:
			updatePatient(&headPtr);
			break;
		case 5:
			printf("Please enter the PPSN of the patient you wish to delete: ");
			scanf("%d", &pps);
			posFound = ppsnToPos(headPtr, pps);

			if (posFound < 1 || posFound>Listlength(headPtr))
				printf("\nSorry patient not found...\n\n");
			else if (posFound == 1)
				DeleteElementAtStart(&headPtr);
			else
				DeleteElementAtPos(headPtr, posFound);
			break;
		case 6:
			generateStats(headPtr);
			break;
		case 7:
			saveDatabase(headPtr);
			break;
		default:
			break;
		}

	} while (choice != -1);

}// main

// Add patient at the start of the list
void AddElementAtStart(struct node** top, int ppsNumber)
{
	struct node* newNode;

	newNode = (struct node*)malloc(sizeof(struct node));

	newNode->ppsn = ppsNumber;

	printf("Please enter patient first name\n");
	scanf("%s", newNode->firstName);

	printf("Please enter patient second name\n");
	scanf("%s", newNode->secondName);

	printf("Please enter patient year born\n");
	scanf("%d", &newNode->yearBorn);

	printf("Please enter patient gender(m for male or f for female)\n");
	scanf(" %c", &newNode->gender);

	printf("Please enter patient email\n");
	scanf("%s", newNode->email);

	printf("Please enter patient next of kin name\n");
	scanf("%s", newNode->nokName);

	printf("Please enter patient last appointment(ddmmyyyy format)\n");
	scanf("%d", &newNode->lastAppointment);

	printf("Please enter patient weight in kgs\n");
	scanf("%f", &newNode->weight);

	printf("Please enter patient height in meters\n");
	scanf("%f", &newNode->height);

	newNode->bmi = calculateBMI(newNode->weight, newNode->height);

	printf("Does the patient has any allergies to any medications? Enter 'y' for yes or 'n' for no\n");
	scanf(" %c", &newNode->allergies);

	printf("How many cigarettes would you smoke per day? Enter 'n' for none\n'l' for less than 10 or 'm' for more than 10\n");
	scanf(" %c", &newNode->cigaretters);

	printf("How much alcohol would you drink per week? Enter 'n' for none\n'l' for less than 10 units or 'm' for more than 10 units\n");
	scanf(" %c", &newNode->alcohol);

	printf("How often do you exercise? Enter 'n' for never\n'l' for less than twice per week or 'm' for more than than twice per week\n");
	scanf(" %c", &newNode->exercise);

	newNode->NEXT = *top;
	*top = newNode;
}// AddElementAtStart

// Add patient at the end of the list
void AddElementAtEnd(struct node* top, int ppsNumber)
{
	struct node* temp = top;
	struct node* newNode;

	while (temp->NEXT != NULL)
	{
		temp = temp->NEXT;
	}

	newNode = (struct node*)malloc(sizeof(struct node));

	newNode->ppsn = ppsNumber;

	printf("Please enter patient first name\n");
	scanf("%s", newNode->firstName);

	printf("Please enter patient second name\n");
	scanf("%s", newNode->secondName);

	printf("Please enter patient year born\n");
	scanf("%d", &newNode->yearBorn);

	printf("Please enter patient gender(m for male or f for female)\n");
	scanf(" %c", &newNode->gender);

	printf("Please enter patient email\n");
	scanf("%s", newNode->email);

	printf("Please enter patient next of kin name\n");
	scanf("%s", newNode->nokName);

	printf("Please enter patient last appointment (ddmmyyyy format)\n");
	scanf("%d", &newNode->lastAppointment);

	printf("Please enter patient weight in kgs\n");
	scanf("%f", &newNode->weight);

	printf("Please enter patient height in meters\n");
	scanf("%f", &newNode->height);

	newNode->bmi = calculateBMI(newNode->weight, newNode->height);

	printf("Does the patient has any allergies to any medications? Enter 'y' for yes or 'n' for no\n");
	scanf(" %c", &newNode->allergies);

	printf("How many cigarettes would you smoke per day? Enter 'n' for none\n'l' for less than 10 or 'm' for more than 10\n");
	scanf(" %c", &newNode->cigaretters);

	printf("How much alcohol would you drink per week? Enter 'n' for none\n'l' for less than 10 units or 'm' for more than 10 units\n");
	scanf(" %c", &newNode->alcohol);

	printf("How often do you exercise? Enter 'n' for never\n'l' for less than twice per week or 'm' for more than than twice per week\n");
	scanf(" %c", &newNode->exercise);

	newNode->NEXT = NULL;
	temp->NEXT = newNode;
}

// Delete patient at the start of the list
void DeleteElementAtStart(struct node** top)
{
	struct node* temp;

	temp = *top;

	*top = temp->NEXT;

	free(temp);
}

// Delete patient at a pos in the list
void DeleteElementAtPos(struct node* top, int position)
{
	int i;
	struct node* temp;
	struct node* prev_temp;
	struct node* newNode;

	temp = top;

	for (i = 0; i < position - 1; i++)
	{
		prev_temp = temp;
		temp = temp->NEXT;
	}


	prev_temp->NEXT = temp->NEXT;
	free(temp);

}

// Search list for a ppsn and returns position found if ppsn found
int ppsnToPos(struct node* top, int searchPPS)
{
	int counter = 0;
	int posFound = 0;
	struct node* temp = top;

	while (temp != NULL)
	{
		counter++;
		if (temp->ppsn == searchPPS)
		{
			posFound = counter;
			return posFound;
		}

		temp = temp->NEXT;
	}// while

	return posFound;
}

// Displays all the details to the screen
void DisplayList(struct node* top)
{
	struct node* temp = top;
	
	printf("\n");

	while (temp != NULL)
	{
		printf("%d  %s %s  %d %c %s %s %d %.2f %.2f %.2f %c %c %c %c \n", temp->ppsn, temp->firstName, temp->secondName, temp->yearBorn, temp->gender, temp->email, temp->nokName, temp->lastAppointment, temp->weight, temp->height, temp->bmi, temp->allergies, temp->cigaretters, temp->alcohol, temp->exercise);
		temp = temp->NEXT;
	}
	printf("\n");
}

// Search the list for a ppsn returns 1 if found or 0 if not found
int searchList(struct node* top, int searchPPS)
{
	int found = 0;
	struct node* temp = top;

	while (temp != NULL)
	{
		if (temp->ppsn == searchPPS)
		{
			found = 1;
			return found;
		}

		temp = temp->NEXT;
	}

	return found;
}

// Calculates bmi and returns it as a float
float calculateBMI(float weight, float height)
{
	float bmi = 0;

	bmi = weight / (height * height);

	return bmi;
}

// Loads patient.txt into a link list
void loadDatabase(struct node** top)
{
	FILE* inPatientFile;

	inPatientFile = fopen("patient.txt", "r");

	if (inPatientFile == NULL)
	{
		printf("Apologies the file could not be opened\n");
	}
	else
	{
		struct node* newNode;
		int pps;

		
		while (fscanf(inPatientFile, "%d", &pps) == 1)
		{
			fscanf(inPatientFile, "%d", &pps);

			if (searchList(*top, pps) == 1)
			{
				printf("Sorry the PPS already exists\n");
				return;
			}

			newNode = (struct node*)malloc(sizeof(struct node));

			newNode->ppsn = pps;

			fscanf(inPatientFile, "%s", newNode->firstName);

			fscanf(inPatientFile, "%s", newNode->secondName);

			fscanf(inPatientFile, "%d", &newNode->yearBorn);

			fscanf(inPatientFile, " %c", &newNode->gender);

			fscanf(inPatientFile, "%s", newNode->email);

			fscanf(inPatientFile, "%s", newNode->nokName);

			fscanf(inPatientFile, "%d", &newNode->lastAppointment);

			fscanf(inPatientFile, "%f", &newNode->weight);

			fscanf(inPatientFile, "%f", &newNode->height);
			
			fscanf(inPatientFile, "%f", &newNode->bmi);

			fscanf(inPatientFile, " %c", &newNode->allergies);

			fscanf(inPatientFile, " %c", &newNode->cigaretters);

			fscanf(inPatientFile, " %c", &newNode->alcohol);

			fscanf(inPatientFile, " %c", &newNode->exercise);


			newNode->NEXT = *top;
			*top = newNode;
		}// while

		fclose(inPatientFile);
		printf("Successfully loaded the database patient.txt\n\n");
	}// else	
}// initialiseDatabase

// Display patient details according to ppsn or name (case sensitive)
void displayPatient(struct node* top)
{
	struct node* temp = top;
	int pps;
	char fName[30];
	char sName[30];
	int choice;

	// Validate only for option 1 or 2
	do
	{
		printf("\n\nPlesase enter...");
		printf("===========================\n");
		printf("  1 - To search by patient PPSN\n");
		printf("  2 - To search by patient Name\n");
		printf("===========================\n\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("\nEnter patient PPSN:");
			scanf("%d", &pps);
			break;
		case 2:
			printf("\nEnter patient first name: ");
			scanf("%s", fName);
			printf("Enter patient second name: ");
			scanf("%s", sName);
			break;
		default:
			printf("\n\nInvalid option, please try again...\n");
			break;
		}

	} while (choice != 1 && choice != 2);

	printf("\n");

	while (temp != NULL)
	{
		if (choice == 1)
		{
			if (temp->ppsn == pps)
			{
				printf("%d  %s %s  %d %c %s %s %d %.2f %.2f %.2f %c %c %c %c \n\n", temp->ppsn, temp->firstName, temp->secondName, temp->yearBorn, temp->gender, temp->email, temp->nokName, temp->lastAppointment, temp->weight, temp->height, temp->bmi, temp->allergies, temp->cigaretters, temp->alcohol, temp->exercise);
				return;
			}// if
		}
		else
		{
			if ((strcmp(temp->firstName, fName) == 0) && (strcmp(temp->secondName, sName) == 0))
			{
				printf("%d  %s %s  %d %c %s %s %d %.2f %.2f %.2f %c %c %c %c \n\n", temp->ppsn, temp->firstName, temp->secondName, temp->yearBorn, temp->gender, temp->email, temp->nokName, temp->lastAppointment, temp->weight, temp->height, temp->bmi, temp->allergies, temp->cigaretters, temp->alcohol, temp->exercise);
				return;
			}// if
		}
		
		temp = temp->NEXT;
	}// while

	printf("Sorry could not find the patient, please try again...\n\n");
}// displayPatient

// Returns the length of the list
int Listlength(struct node* top)
{
	struct node* temp;
	int count = 0;
	temp = top;

	while (temp != NULL)
	{
		count++;
		temp = temp->NEXT;
	}

	return count;
}

// Update patient details according to ppsn or name (case sensitive)
void updatePatient(struct node** top)
{
	struct node* temp = *top;
	int pps;
	char fName[30];
	char sName[30];
	int choice;

	// Validate only for option 1 or 2
	do
	{
		printf("\n\nPlesase enter...");
		printf("===========================\n");
		printf("  1 - To search by patient PPSN\n");
		printf("  2 - To search by patient Name\n");
		printf("===========================\n\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("\nEnter patient PPSN:");
			scanf("%d", &pps);
			break;
		case 2:
			printf("\nEnter patient first name: ");
			scanf("%s", fName);
			printf("Enter patient second name: ");
			scanf("%s", sName);
			break;
		default:
			printf("\n\nInvalid option, please try again...\n");
			break;
		}

	} while (choice != 1 && choice != 2);

	printf("\n");

	while (temp != NULL)
	{
		if (choice == 1)
		{
			if (temp->ppsn == pps)
			{	
				printf("Please enter patient PPSN\n");
				scanf("%d", &temp->ppsn);

				printf("Please enter patient first name\n");
				scanf("%s", temp->firstName);

				printf("Please enter patient second name\n");
				scanf("%s", temp->secondName);

				printf("Please enter patient year born\n");
				scanf("%d", &temp->yearBorn);

				printf("Please enter patient gender(m for male or f for female)\n");
				scanf(" %c", &temp->gender);

				printf("Please enter patient email\n");
				scanf("%s", temp->email);

				printf("Please enter patient next of kin name\n");
				scanf("%s", temp->nokName);

				printf("Please enter patient last appointment(ddmmyyyy format)\n");
				scanf("%d", &temp->lastAppointment);

				printf("Please enter patient weight in kgs\n");
				scanf("%f", &temp->weight);

				printf("Please enter patient height in meters\n");
				scanf("%f", &temp->height);

				temp->bmi = calculateBMI(temp->weight, temp->height);

				printf("Does the patient has any allergies to any medications?\n Enter 'y' for yes or 'n' for no\n");
				scanf(" %c", &temp->allergies);

				printf("How many cigarettes would you smoke per day?\n Enter 'n' for none\n'l' for less than 10 or 'm' for more than 10\n");
				scanf(" %c", &temp->cigaretters);

				printf("How much alcohol would you drink per week?\n Enter 'n' for none\n'l' for less than 10 units or 'm' for more than 10 units\n");
				scanf(" %c", &temp->alcohol);

				printf("How often do you exercise?\n Enter 'n' for never\n'l' for less than twice per week or 'm' for more than than twice per week\n");
				scanf(" %c", &temp->exercise);

				printf("\n\nSuccessfully updated patient %d details.\n\n", pps);
				return;
			}// if
		}
		else
		{
			if ((strcmp(temp->firstName, fName) == 0) && (strcmp(temp->secondName, sName) == 0))
			{
				printf("Please enter patient PPSN\n");
				scanf("%d", &temp->ppsn);

				printf("Please enter patient first name\n");
				scanf("%s", temp->firstName);

				printf("Please enter patient second name\n");
				scanf("%s", temp->secondName);

				printf("Please enter patient year born\n");
				scanf("%d", &temp->yearBorn);

				printf("Please enter patient gender(m for male or f for female)\n");
				scanf(" %c", &temp->gender);

				printf("Please enter patient email\n");
				scanf("%s", temp->email);

				printf("Please enter patient next of kin name\n");
				scanf("%s", temp->nokName);

				printf("Please enter patient last appointment(ddmmyyyy format)\n");
				scanf("%d", &temp->lastAppointment);

				printf("Please enter patient weight in kgs\n");
				scanf("%f", &temp->weight);

				printf("Please enter patient height in meters\n");
				scanf("%f", &temp->height);

				temp->bmi = calculateBMI(temp->weight, temp->height);

				printf("Does the patient has any allergies to any medications?\n Enter 'y' for yes or 'n' for no\n");
				scanf(" %c", &temp->allergies);

				printf("How many cigarettes would you smoke per day?\n Enter 'n' for none\n'l' for less than 10 or 'm' for more than 10\n");
				scanf(" %c", &temp->cigaretters);

				printf("How much alcohol would you drink per week?\n Enter 'n' for none\n'l' for less than 10 units or 'm' for more than 10 units\n");
				scanf(" %c", &temp->alcohol);

				printf("How often do you exercise?\n Enter 'n' for never\n'l' for less than twice per week or 'm' for more than than twice per week\n");
				scanf(" %c", &temp->exercise);

				printf("\n\nSuccessfully updated patient %s %s details.\n\n", fName, sName);
				return;
			}// if
		}

		temp = temp->NEXT;
	}// while

}// updatePatient

// Update patient if ppsn already exists when adding a new patient
void updatePatientAtAdding(struct node** top, int ppsNumber)
{
	struct node* temp = *top;

	printf("\n");

	while (temp != NULL)
	{
		
		if (temp->ppsn == ppsNumber)
		{
			printf("Please enter patient PPSN\n");
			scanf("%d", &temp->ppsn);

			printf("Please enter patient first name\n");
			scanf("%s", temp->firstName);

			printf("Please enter patient second name\n");
			scanf("%s", temp->secondName);

			printf("Please enter patient year born\n");
			scanf("%d", &temp->yearBorn);

			printf("Please enter patient gender(m for male or f for female)\n");
			scanf(" %c", &temp->gender);

			printf("Please enter patient email\n");
			scanf("%s", temp->email);

			printf("Please enter patient next of kin name\n");
			scanf("%s", temp->nokName);

			printf("Please enter patient last appointment(ddmmyyyy format)\n");
			scanf("%d", &temp->lastAppointment);

			printf("Please enter patient weight in kgs\n");
			scanf("%f", &temp->weight);

			printf("Please enter patient height in meters\n");
			scanf("%f", &temp->height);

			temp->bmi = calculateBMI(temp->weight, temp->height);

			printf("Does the patient has any allergies to any medications?\n Enter 'y' for yes or 'n' for no\n");
			scanf(" %c", &temp->allergies);

			printf("How many cigarettes would you smoke per day?\n Enter 'n' for none\n'l' for less than 10 or 'm' for more than 10\n");
			scanf(" %c", &temp->cigaretters);

			printf("How much alcohol would you drink per week?\n Enter 'n' for none\n'l' for less than 10 units or 'm' for more than 10 units\n");
			scanf(" %c", &temp->alcohol);

			printf("How often do you exercise?\n Enter 'n' for never\n'l' for less than twice per week or 'm' for more than than twice per week\n");
			scanf(" %c", &temp->exercise);

			printf("\n\nSuccessfully updated patient %d details.\n\n", ppsNumber);
			return;
		}// if

		temp = temp->NEXT;
	}// while

}

// Saves the link list to the patient.txt file
void saveDatabase(struct node* top)
{
	struct node* temp = top;
	FILE* outPatientFile;

	outPatientFile = fopen("patient.txt", "w");

	if (outPatientFile == NULL)
	{
		printf("Apologies the file could not be opened\n");
	}
	else
	{
		while (temp != NULL)
		{

			fprintf(outPatientFile,"%d  %s %s  %d %c %s %s %d %.2f %.2f %.2f %c %c %c %c \n", temp->ppsn, temp->firstName, temp->secondName, temp->yearBorn, temp->gender, temp->email, temp->nokName, temp->lastAppointment, temp->weight, temp->height, temp->bmi, temp->allergies, temp->cigaretters, temp->alcohol, temp->exercise);
			temp = temp->NEXT;
		}

		fclose(outPatientFile);
	}// else
	printf("\n");
}

// Login Validation 
void login() 
{
	char password[7];
	char username[7];
	char checkUser[7];
	char checkPassword[7];
	char ch;
	int i;
	int attemptNumber;
	int correctPass = 0;

	FILE* inLoginFile;

	//OpenFile
	inLoginFile = fopen("login.txt", "r");

	if (inLoginFile == NULL)
	{
		printf("Could not open the login file...\n\n");
		system("pause");
		exit(0);
	}
	else
	{
		for (attemptNumber = 0; attemptNumber < 3; attemptNumber++)
		{

			// Input username and password
			printf("Enter username: ");
			scanf("%s", username);

			printf("Enter password: ");

			for (i = 0; i < 6; i++)
			{
				ch = getch();
				password[i] = ch;
				ch = '*';
				printf("%c", ch);
			}

			password[i] = '\0';

			// Validate username and password
			while (!feof(inLoginFile))
			{
				fscanf(inLoginFile, "%s %s", checkUser, checkPassword);

				if (strcmp(checkUser, username) == 0 && strcmp(checkPassword, password) == 0)
				{
					attemptNumber = 3;
					correctPass = 1;
				}//if

			}// while

			// If wrong password...
			if (correctPass == 0)
			{
				printf("\n\nWrong username or password, please try again (attempt: %d)\n\n", attemptNumber+1);
				
				// Close file
				fclose(inLoginFile);
		
				// and Reopen file
				inLoginFile = fopen("login.txt", "r");
			}

		}// for

		// Close file
		fclose(inLoginFile);
	
		// if wrong password after 3 attempts...
		if(correctPass == 0)
		{
			printf("You have entered wrong credentials too many times, please try again later...\n\n");
			system("pause");
			exit(0);
		}// if

	}// else

	// Clear the screen
	system("cls"); 
}// login 

// Generate stats
void generateStats(struct node* top)
{
	struct node* temp = top;
	int criteria = 0;
	char answer;
	float less18 = 0, less25 = 0, less30 = 0, more30 = 0;
	float total = 0;
	float stat1 =0, stat2 =0, stat3 = 0, stat4 = 0;

	do
	{
		printf("\n\nSelect a criteria to generate stats on:\n");
		printf("===============================================\n");
		printf(" 1 - How many cigarettes would you smoke per day\n");
		printf(" 2 - How often do you exercise\n");
		printf("===============================================\n");
		scanf("%d", &criteria);

	} while (criteria != 1 && criteria !=2);

	// if criteria is exercise ...
	if (criteria == 2)
	{
		do
		{
			printf("\nHow often do you exercise? (case sensitive)\n\n");
			printf(" Enter 'n' for never\n");
			printf(" Enter 'l' for less than twice per week\n");
			printf(" Enter 'm' for more than twice per week\n");
			scanf(" %c", &answer);
		} while (answer != 'n' && answer != 'l' && answer != 'm');
	
		while (temp != NULL)
		{
			if (temp->exercise == answer)
			{
				// check bmi
				if (temp->bmi < 18.5)
				{
					less18++;
				}
				else if (temp->bmi < 25)
				{
					less25++;
				}
				else if (temp->bmi < 30)
				{
					less30++;
				}
				else
				{
					more30++;
				}
			}
			

			temp = temp->NEXT;
		}

		// Total from the patients that count towards stats
		total = less18 + less25 + less30 + more30;

		stat1 = (less18 / total) * 100;
		stat2 = (less25 / total) * 100;
		stat3 = (less30 / total) * 100;
		stat4 = (more30 / total) * 100;

		// output stats to screen
		printf("\n %.0f%% of patients with a BMI of less than 18.5\n", stat1);
		printf(" %.0f%% of patients with a BMI of less than 25\n", stat2);
		printf(" %.0f%% of patients with a BMI of less than 30\n", stat3);
		printf(" %.0f%% of patients with a BMI of greater than 30\n\n", stat4);
	}
	else // if criteria is cigarettes
	{
		do
		{
			printf("\nHow many cigarettes would you smoke per day? (case sensitive)\n\n");
			printf(" Enter 'n' for none\n");
			printf(" Enter 'l' for less than ten\n");
			printf(" Enter 'm' for more than ten\n");
			scanf(" %c", &answer);
		} while (answer != 'n' && answer != 'l' && answer != 'm');

		while (temp != NULL)
		{
			printf("\n\nDEBUGG INSIDE ARRAY\n\n");

			if (temp->cigaretters == answer)
			{
				printf("\n\nDEBUGG INSIDE if %c %.2f\n\n", temp->cigaretters, temp->bmi);

				// check bmi
				if (temp->bmi < 18.5)
				{
					less18++;
					printf("\n\nDEBUGG INSIDE 18 %f\n\n", less18);

				}
				else if (temp->bmi < 25)
				{
					less25++;
					printf("\n\nDEBUGG INSIDE 25 %f\n\n", less25);
				}
				else if (temp->bmi < 30)
				{
					less30++;
				}
				else
				{
					more30++;
					printf("\n\nDEBUGG INSIDE 30+ %f\n\n", more30);
				}
			}


			temp = temp->NEXT;
		}

		// Total from the patients that count towards stats
		total = less18 + less25 + less30 + more30;
		printf("\n\nDEBUGG TOTAL %f\n\n", total);

		stat1 = (less18 / total) * 100;
		stat2 = (less25 / total) * 100;
		stat3 = (less30 / total) * 100;
		stat4 = (more30 / total) * 100;

		printf("\n %.0f%% of patients with a BMI of less than 18.5\n", stat1);
		printf(" %.0f%% of patients with a BMI of less than 25\n", stat2);
		printf(" %.0f%% of patients with a BMI of less than 30\n", stat3);
		printf(" %.0f%% of patients with a BMI of greater than 30\n\n", stat4);


	}// if else

}
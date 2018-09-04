/* -------------------------------------------
Name: Shomari Malcolm
Student number: 107 688 178
Email: smalcolm3@myseneca.ca
Section: GG
Date: July 23rd, 2018
----------------------------------------------
Assignment: 2
Milestone:  4
---------------------------------------------- */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// This source file needs to "know about" the SYSTEM string library functions.
// HINT: The library name is string.h.
//       #include the string.h header file on the next line:
#include <string.h>
#include <ctype.h>

// ----------------------------------------------------------
// Include your contactHelpers header file on the next line:
#include "contacts.h"
#include "contactHelpers.h"


// ----------------------------------------------------------
// define MAXCONTACTS for sizing contacts array (5):
#define MAXCONTACTS 5


//------------------------------------------------------
// Function Definitions
//------------------------------------------------------

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        function definitions below...            |
// +-------------------------------------------------+

// clearKeyboard:
void clearKeyboard(void)
{
	while (getchar() != '\n'); // empty execution code block on purpose
}

// pause:
void pause(void)
{
	printf("(Press Enter to Continue)");
	clearKeyboard();
}

// getInt:
int getInt(void)
{
	int intVal;
	char afterIntVal;

	scanf("%d%c", &intVal, &afterIntVal);

	while (afterIntVal != '\n') {
		clearKeyboard();
		printf("*** INVALID INTEGER *** <Please enter an integer>: ");
		scanf("%d%c", &intVal, &afterIntVal);
	}

	return intVal;
}

// getIntInRange:
int getIntInRange(int min, int max)
{
	int numVal;

	numVal = getInt();

	while (numVal < min || numVal > max) {
		printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
		numVal = getInt();
	}

	return numVal;
}

// yes:
int yes(void)
{
	char response;
	char afterResponse;
	int isYes;

	scanf(" %c%c", &response, &afterResponse);

	while ((afterResponse != '\n') ||
		(response != 'Y' && response != 'y' && response != 'N' && response != 'n')) {
		clearKeyboard();
		printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
		scanf(" %c%c", &response, &afterResponse);
	}

	isYes = (response == 'Y' || response == 'y') ? 1 : 0;

	return isYes;
}


// menu:
int menu(void)
{
	int selectedOption;

	printf("Contact Management System\n");
	printf("-------------------------\n");
	printf("1. Display contacts\n");
	printf("2. Add a contact\n");
	printf("3. Update a contact\n");
	printf("4. Delete a contact\n");
	printf("5. Search contacts by cell phone number\n");
	printf("6. Sort contacts by cell phone number\n");
	printf("0. Exit\n");

	printf("\n");
	printf("Select an option:> ");

	selectedOption = getIntInRange(0, 6);

	return selectedOption;
}


// ContactManagerSystem:
void ContactManagerSystem(void)
{
	int selectedOption;
	int exitConfirmed = 0;
	struct Contact contactList[MAXCONTACTS] = { { { "Rick",{ '\0' }, "Grimes" },
	{ 11, "Trailer Park", 0, "A7A 2J2", "King City" },{ "4161112222", "4162223333", "4163334444" } },
	{ { "Maggie", "R.", "Greene" },{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
	{ "9051112222", "9052223333", "9053334444" } },{ { "Morgan", "A.", "Jones" },
	{ 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },{ "7051112222", "7052223333", "7053334444" } },
	{ { "Sasha",{ '\0' }, "Williams" },{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
	{ "9052223333", "9052223333", "9054445555" } } };

	selectedOption = menu();

	while (exitConfirmed != 1) {
		switch (selectedOption) {
		case 0:
			printf("\n");
			printf("Exit the program? (Y)es/(N)o: ");
			exitConfirmed = yes();
			printf("\n");
			break;
		case 1:
			printf("\n");
			displayContacts(contactList, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 2:
			printf("\n");
			addContact(contactList, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 3:
			printf("\n");
			updateContact(contactList, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 4:
			printf("\n");
			deleteContact(contactList, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 5:
			printf("\n");
			searchContacts(contactList, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 6:
			printf("\n");
			sortContacts(contactList, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		}
		// display succesful termination message if termination is confirmed
		// if exit not confirmed, get a new option
		if (exitConfirmed == 1) {
			printf("Contact Management System: terminated\n");
		}
		else {
			selectedOption = menu();
		}


	}

}

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        empty function definitions below...      |
// +-------------------------------------------------+

// getTenDigitPhone:
void getTenDigitPhone(char telNum[])
{
	int needInput = 1;
	int allDigits = 1;
	int numberLength;
	int i;

	while (needInput == 1) {
		scanf(" %10s", telNum);
		clearKeyboard();

		// make sure the chars enetered are all digits
		numberLength = strlen(telNum);

		for (i = 0; i < numberLength; i++) {
			if (isdigit(telNum[i]) == 0) {
				allDigits = -1;
			}
		}


		// (String Length Function: validate entry of 10 characters)
		if ((numberLength == 10) && (allDigits == 1)) {
			needInput = 0;
		}
		else {
			allDigits = 1;
			printf("Enter a 10-digit phone number: ");
		}
	}
}

// findContactIndex:
int findContactIndex(const struct Contact contacts[], int size, const char cellNum[])
{
	int i;

	for (i = 0; i < size; i++) {
		if (strcmp(contacts[i].numbers.cell, cellNum) == 0) {
			return i;
		}
	}

	return -1;
}


// displayContactHeader
void displayContactHeader(void)
{
	printf("+-----------------------------------------------------------------------------+\n");
	printf("|                              Contacts Listing                               |\n");
	printf("+-----------------------------------------------------------------------------+\n");
}


// displayContactFooter
void displayContactFooter(int totalContacts)
{
	printf("+-----------------------------------------------------------------------------+\n");
	printf("Total contacts: %d\n\n", totalContacts);
}


// displayContact:
void displayContact(const struct Contact* contact)
{
	//display full name for this contact
	if (contact->name.middleInitial[0] != '\0') {
		printf(" %s %s %s\n", contact->name.firstName, contact->name.middleInitial, contact->name.lastName);
	}
	else {
		printf(" %s %s\n", contact->name.firstName, contact->name.lastName);
	}

	// display numbers for this contact
	printf("    C: %-10s   H: %-10s   B: %-10s\n", contact->numbers.cell, contact->numbers.home, contact->numbers.business);

	// display address for this contact
	printf("       %d %s, ", contact->address.streetNumber, contact->address.street);

	if (contact->address.apartmentNumber > 0) {
		printf("Apt# %d, ", contact->address.apartmentNumber);
	}

	printf("%s, %s\n", contact->address.city, contact->address.postalCode);
}


// displayContacts:
void displayContacts(const struct Contact contacts[], int size)
{
	int validContacts = 0;
	int i;

	displayContactHeader();

	for (i = 0; i < size; i++) {
		if (contacts[i].numbers.cell[0] != 0) {
			displayContact(&contacts[i]);
			validContacts++;
		}
	}

	displayContactFooter(validContacts);
}


// searchContacts:
void searchContacts(const struct Contact contacts[], int size)
{
	char queryNumber[11];
	int resultIndex;

	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(queryNumber);

	resultIndex = findContactIndex(contacts, size, queryNumber);

	if (resultIndex != -1) {
		printf("\n");
		displayContact(&contacts[resultIndex]);
		printf("\n");
	}
	else {
		printf("*** Contact NOT FOUND ***\n");
	}
}


// addContact:
void addContact(struct Contact contacts[], int size)
{
	int emptyIndex = -1;
	int i;

	// look for empty index
	for (i = 0; i < size; i++) {
		if (strlen(contacts[i].numbers.cell) == 0) {
			emptyIndex = i;
		}
	}

	if (emptyIndex == -1) {
		printf("*** ERROR: The contact list is full! ***\n");
	}
	else {
		getContact(&contacts[emptyIndex]);
		printf("--- New contact added! ---\n");
	}

}


// updateContact:
void updateContact(struct Contact contacts[], int size)
{
	int updateIndex, answer;
	char queryNumber[11];

	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(queryNumber);

	// see if contact to update exists
	updateIndex = findContactIndex(contacts, size, queryNumber);

	if (updateIndex == -1) {
		printf("*** Contact NOT FOUND ***\n");
	}
	else {
		printf("\n");
		printf("Contact found:\n");
		displayContact(&contacts[updateIndex]);
		printf("\n");

		// ask the user which part of the contact's info to update
		printf("Do you want to update the name? (y or n): ");
		answer = yes();
		if (answer == 1) {
			getName(&contacts[updateIndex].name);
		}

		printf("Do you want to update the address? (y or n): ");
		answer = yes();
		if (answer == 1) {
			getAddress(&contacts[updateIndex].address);
		}

		printf("Do you want to update the numbers? (y or n): ");
		answer = yes();
		if (answer == 1) {
			getNumbers(&contacts[updateIndex].numbers);
		}

		printf("--- Contact Updated! ---\n");
	}
}


// deleteContact:
void deleteContact(struct Contact contacts[], int size)
{
	int deleteIndex, answer;
	char queryNumber[11];

	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(queryNumber);

	// see if contact to update exists
	deleteIndex = findContactIndex(contacts, size, queryNumber);

	if (deleteIndex == -1) {
		printf("*** Contact NOT FOUND ***\n");
	}
	else {
		printf("\n");
		printf("Contact found:\n");
		displayContact(&contacts[deleteIndex]);
		printf("\n");

		// confirm action
		printf("CONFIRM: Delete this contact? (y or n): ");
		answer = yes();

		if (answer == 1) {
			// delete contact
			contacts[deleteIndex].numbers.cell[0] = '\0';
			printf("--- Contact deleted! ---\n");
		}
	}
}


// sortContacts:
void sortContacts(struct Contact contacts[], int size)
{
	int i, j, smallestElementIndex;
	struct Contact tempContact;

	for (i = 0; i < size; i++) {
		// start off with first element as smallest index
		smallestElementIndex = i;

		// compare current smallest to each item in array
		for (j = i + 1; j < size; j++) {
			if (contacts[j].numbers.cell[0] != '\0') {
				if (strcmp(contacts[j].numbers.cell, contacts[smallestElementIndex].numbers.cell) < 0) {
					smallestElementIndex = j;
				}
			}
		}

		// swap current iteration element with smallest element if they differ
		if (smallestElementIndex != i) {
			tempContact = contacts[i];
			contacts[i] = contacts[smallestElementIndex];
			contacts[smallestElementIndex] = tempContact;
		}
	}

	printf("--- Contacts sorted! ---\n");
}

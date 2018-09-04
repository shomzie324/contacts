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

// +-------------------------------------------------+
// | NOTE:  Include additional header files...       |
// +-------------------------------------------------+
#include "contacts.h"
#include "contactHelpers.h"


// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        source code below...                     |
// +-------------------------------------------------+

// getName:
void getName(struct Name *name)
{
	int middleNameExists;

	// Contact Name Input:
	printf("Please enter the contact's first name: ");
	scanf("%30[^\n]", name->firstName);

	// ask for middle initials if the user does not say they don't want to
	printf("Do you want to enter a middle initial(s)? (y or n): ");
	middleNameExists = yes();

	if (middleNameExists == 1) {
		printf("Please enter the contact's middle initial(s): ");
		scanf(" %6[^\n]", name->middleInitial);
	}
	else {
		name->middleInitial[0] = '\0';
	}

	printf("Please enter the contact's last name: ");
	scanf(" %35[^\n]", name->lastName);
}



// getAddress:
void getAddress(struct Address *ad)
{
	int hasApartmentNumber;

	// Contact Address Input:

	do {
		printf("Please enter the contact's street number: ");
		ad->streetNumber = getInt();
	} while (ad->streetNumber < 1);

	printf("Please enter the contact's street name: ");
	scanf(" %40[^\n]", ad->street);

	// ask for apartment number unless the user says they don't want to 
	printf("Do you want to enter an apartment number? (y or n): ");
	hasApartmentNumber = yes();

	if (hasApartmentNumber == 1) {
		do {
			printf("Please enter the contact's apartment number: ");
			ad->apartmentNumber = getInt();
		} while (ad->apartmentNumber < 1);
	}
	else {
		ad->apartmentNumber = 0;
	}

	printf("Please enter the contact's postal code: ");
	scanf(" %7[^\n]", ad->postalCode);

	printf("Please enter the contact's city: ");
	scanf(" %40[^\n]", ad->city);
}



// getNumbers:
void getNumbers(struct Numbers *num)
{
	int hasHomeNumber, hasBusinessNumber;

	// get cell number (now mandatory)
	printf("Please enter the contact's cell phone number: ");
	getTenDigitPhone(num->cell);


	// get home number unless user says they don't want to enter one
	printf("Do you want to enter a home phone number? (y or n): ");
	hasHomeNumber = yes();

	if (hasHomeNumber == 1) {
		printf("Please enter the contact's home phone number: ");
		getTenDigitPhone(num->home);
	}
	else {
		num->home[0] = '\0';
	}


	// get business number unless user says they don't want to enter one

	printf("Do you want to enter a business phone number? (y or n): ");
	hasBusinessNumber = yes();


	if (hasBusinessNumber == 1) {
		printf("Please enter the contact's business phone number: ");
		getTenDigitPhone(num->business);
	}
	else {
		num->business[0] = '\0';
	}
}



// getContact
void getContact(struct Contact *cntp)
{
	getName(&cntp->name);
	getAddress(&cntp->address);
	getNumbers(&cntp->numbers);
}


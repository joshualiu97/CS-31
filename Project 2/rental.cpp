/*
Program: Yentl's Rentals
Programmer: Joshua Liu
Date: October 12, 2018
*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
	// Gather input

	cout << "Odometer at start: ";
	int odometerStart;
	cin >> odometerStart;

	cout << "Odometer at end: ";
	int odometerEnd;
	cin >> odometerEnd;

	cout << "Rental days: ";
	int rentalDays;
	cin >> rentalDays;
	cin.ignore(10000, '\n');

	cout << "Customer name: ";
	string customerName;
	getline(cin, customerName);

	cout << "Luxury car? (y/n): ";
	string luxuryStatus;
	getline(cin, luxuryStatus);

	cout << "Month (1=Jan, 2=Feb, etc.): ";
	int month;
	cin >> month;

	cout << "---\n";

	// Determine whether or not input is valid
	// If not valid, print the error message of the first invalid input and end the program
	// If valid, proceed with calculations

	if (odometerStart < 0)
	{
		cout << "The starting odometer reading must be nonnegative." << endl;
		return 1;
	}
	if (odometerEnd < odometerStart)
	{
		cout << "The final odometer reading must be at least as large as the starting reading." << endl;
		return 1;
	}
	if (rentalDays <= 0)
	{
		cout << "The number of rental days must be positive." << endl;
		return 1;
	}
	if (customerName == "")
	{
		cout << "You must enter a customer name." << endl;
		return 1;
	}
	if ((luxuryStatus != "y") && (luxuryStatus != "n"))
	{
		cout << "You must enter y or n." << endl;
		return 1;
	}
	if ((month <= 0) || (month > 12))
	{
		cout << "The month number must be in the range 1 through 12." << endl;
		return 1;
	}

	// Calculate the rental price

	double rentalPrice = 0;
	int milesDriven = odometerEnd - odometerStart;

	// Base charge for first 100 miles

	if (milesDriven <= 100)
	{
		rentalPrice = milesDriven * 0.27;
		milesDriven -= 100;
	}
	else
	{
		rentalPrice = 100 * 0.27;
		milesDriven -= 100;
	}

	// Charge for next 300 miles

	if (milesDriven > 0)
	{
		if ((milesDriven <= 300) && (milesDriven > 0))
		{
			if ((month == 12) || (month == 1) || (month == 2) || (month == 3)) // Check for month
			{
				rentalPrice += milesDriven * 0.27;
			}
			else
			{
				rentalPrice += milesDriven * 0.21;
			}
		}
		else // Charge for every mile beyond 400 miles
		{
			milesDriven -= 300;

			if ((month == 12) || (month == 1) || (month == 2) || (month == 3)) // Check for month
			{
				rentalPrice += 300 * 0.27 + (milesDriven * 0.19);
			}
			else
			{
				rentalPrice += 300 * 0.21 + (milesDriven * 0.19);
			}
		}
	}

	// Add the base charge to the rental price

	if (luxuryStatus == "n")
	{
		rentalPrice += 33 * rentalDays;
	}
	else
	{
		rentalPrice += 61 * rentalDays;
	}

	// Print the customer's name and rental price

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout << "The rental charge for " + customerName + " is $" << rentalPrice << endl;
}
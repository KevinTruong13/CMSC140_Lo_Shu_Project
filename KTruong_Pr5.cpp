/*
 * Class: CMSC140 CRN 20433_22867
 * Instructor: Grigoriy A. Grinberg
 * Project 5
 * Description: write a program that determines if given arrays create a Lo Shu magic square.
 * Due Date: 12/06/21
 * I pledge that I have completed the programming assignment independently.
   I have not copied the code from a student or any source.
   I have not given my code to any student.
   Print your Full Name here: Kevin Truong
 */

#include<iostream>
#include <string>
using namespace std;

// Global constants 
const int ROWS = 3;  // The number of rows in the array
const int COLS = 3;  // The number of columns in the array
const int MIN = 1;  // The value of the smallest number
const int MAX = 9;  // The value of the largest number

const int FIRST_ROW = 1;	// The value of first row
const int FIRST_INDEX = 0;	// The value of first index
const int ROW1 = 1;
const int ROW2 = 2;
const int ROW3 = 3;
const int COLUMN1_INDEX = 0;
const int COLUMN2_INDEX = 1;
const int COLUMN3_INDEX = 2;
const int ACCUMULATOR_INITIALIZATION = 0;	// Value to initialize accumulator variables
const int PROJECT_NUMBER = 5;

const string PROGRAMMER_NAME = "Kevin Truong";
const string DUE_DATE = "12/06/2021";

// Function prototypes
bool isMagicSquare(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size);
bool checkRange(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size, int min, int max);
bool checkUnique(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size);
bool checkRowSum(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size);
bool checkColSum(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size);
bool checkDiagSum(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size);
void fillArray(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size);
void showArray(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size);
void fillRow(int[], int size);
void showRow(int[], int size);
bool checkUniqueColumn(int, int, int, int arrayRow1[], int arrayRow2[], int arrayRow3[], int size);
int getRowSum(int[], int size);
int getColumnSum(int, int arrayRow1[], int arrayRow2[], int arrayRow3[], int size);

int main()
{

	/* Define a Lo Shu Magic Square using 3 parallel arrays corresponding to each row of the grid */
	int magicArrayRow1[COLS], magicArrayRow2[COLS], magicArrayRow3[COLS];
	char repeat;

	do
	{
		fillArray(magicArrayRow1, magicArrayRow2, magicArrayRow3, COLS);	// Fills arrays
		showArray(magicArrayRow1, magicArrayRow2, magicArrayRow3, COLS);	// Displays arrays

		if (isMagicSquare(magicArrayRow1, magicArrayRow2, magicArrayRow3, COLS))	// Determines if arrays create magic square
			cout << "This is a Lo Shu magic square.\n";
		else
			cout << "This not a Lo Shu magic square.\n";

		cout << "Do you want to try again? (Please input Y or N)\n";
		cin >> repeat;
		
		while (repeat != 'y' && repeat != 'Y' && repeat != 'n' && repeat != 'N')	// Input validation
		{
			cout << "Error; please input Y or N\n";
			cin >> repeat;
		}

	} while (repeat == 'Y' || repeat == 'y');

	cout << "Name: " << PROGRAMMER_NAME << endl
		<< "Project #: " << PROJECT_NUMBER << endl
		<< "Due Date: " << DUE_DATE << endl;

	return 0;
}
// Function definitions go here

void fillArray(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size)		// This function fills each array with values
{
	fillRow(arrayRow1, size);
	fillRow(arrayRow2, size);
	fillRow(arrayRow3, size);
}

void fillRow(int arrayRow[], int size)		// This function fills an array corresponding to a row with values
{
	static int row = FIRST_ROW;

	for (int column = FIRST_INDEX; column < size; column++)
	{
		cout << "Enter the number for row " << row << " and column " << column + 1 << " : ";
		cin >> arrayRow[column];
	}

	row++;
}

void showArray(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size)	// This function prints out the arrays in Magic Square format
{
	showRow(arrayRow1, size);
	showRow(arrayRow2, size);
	showRow(arrayRow3, size);
}

void showRow(int arrayRow[], int size)		// This function prints an array as a row
{
	for (int column = FIRST_INDEX; column < size; column++)
		cout << arrayRow[column] << " ";
	cout << endl;
}

bool isMagicSquare(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size)		// This function determines whether arrays create magic square
{
	// Checks if arrays meet magic square pre-requisites
	if (checkRange(arrayRow1, arrayRow2, arrayRow3, size, MIN, MAX) && checkUnique(arrayRow1, arrayRow2, arrayRow3, size) && checkRowSum(arrayRow1, arrayRow2, arrayRow3, size) && checkColSum(arrayRow1, arrayRow2, arrayRow3, size) && checkDiagSum(arrayRow1, arrayRow2, arrayRow3, size))
		return true;
	return false;
}

bool checkRange(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size, int min, int max)	// This function checks if values are within magic square range
{
	for (int column = FIRST_INDEX; column < size; column++)
	{
		if (arrayRow1[column] < min || arrayRow2[column] < min || arrayRow3[column] < min || arrayRow1[column] > max || arrayRow2[column] > max || arrayRow3[column] > max)
			return false;
	}
	return true;
}

bool checkUnique(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size)	// This function checks if every value is unique
{
	for (int column = FIRST_INDEX; column < size; column++)
	{
		// Checks if each row of column checked is unique
		if (!checkUniqueColumn(arrayRow1[column], ROW1, column, arrayRow1, arrayRow2, arrayRow3, size))
			return false;
		if (!checkUniqueColumn(arrayRow2[column], ROW2, column, arrayRow1, arrayRow2, arrayRow3, size))
			return false;
		if (!checkUniqueColumn(arrayRow3[column], ROW3, column, arrayRow1, arrayRow2, arrayRow3, size))
			return false;
	}
	return true;
}

bool checkUniqueColumn(int checked, int row, int column, int arrayRow1[], int arrayRow2[], int arrayRow3[], int size)	// Checks if checked value is unique
{
	for (int checking = FIRST_INDEX; checking < size; checking++)
	{
		// Compares value being checked to all other values
		if (!(column == checking && row == ROW1) && checked == arrayRow1[checking])
			return false;
		if (!(column == checking && row == ROW2) && checked == arrayRow2[checking])
			return false;
		if (!(column == checking && row == ROW3) && checked == arrayRow3[checking])
			return false;
	}
	return true;
}

bool checkRowSum(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size)	// This function checks if all the row sums are equal
{
	if (getRowSum(arrayRow1, size) == getRowSum(arrayRow2, size) && getRowSum(arrayRow1, size) == getRowSum(arrayRow3, size) && getRowSum(arrayRow2, size) == getRowSum(arrayRow3, size))
		return true;
	return false;
}

int getRowSum(int arrayRow[], int size)		// This function gets the sum of a row
{
	int sum = ACCUMULATOR_INITIALIZATION;	// Accumulator variable

	for (int column = FIRST_INDEX; column < size; column++)
	{
		sum += arrayRow[column];
	}

	return sum;
}

bool checkColSum(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size)	// This function checks if all the columns are equal
{
	if (getColumnSum(COLUMN1_INDEX, arrayRow1, arrayRow2, arrayRow3, size) == getColumnSum(COLUMN2_INDEX, arrayRow1, arrayRow2, arrayRow3, size) && getColumnSum(COLUMN1_INDEX, arrayRow1, arrayRow2, arrayRow3, size) == getColumnSum(COLUMN3_INDEX, arrayRow1, arrayRow2, arrayRow3, size) && getColumnSum(COLUMN2_INDEX, arrayRow1, arrayRow2, arrayRow3, size) == getColumnSum(COLUMN3_INDEX, arrayRow1, arrayRow2, arrayRow3, size))
		return true;
	return false;
}

int getColumnSum(int column, int arrayRow1[], int arrayRow2[], int arrayRow3[], int size)	// This function gets the sum of a column
{
	int sum = ACCUMULATOR_INITIALIZATION;	// Accumulator variable
	sum += arrayRow1[column] + arrayRow2[column] + arrayRow3[column];
	return sum;
}

bool checkDiagSum(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size)	// This functions compares the sums of each diagonal
{
	int majorDiagonalSum = ACCUMULATOR_INITIALIZATION;
	int minorDiagonalSum = ACCUMULATOR_INITIALIZATION;

	majorDiagonalSum += arrayRow1[COLUMN1_INDEX] + arrayRow2[COLUMN2_INDEX] + arrayRow3[COLUMN3_INDEX];
	minorDiagonalSum += arrayRow1[COLUMN3_INDEX] + arrayRow2[COLUMN2_INDEX] + arrayRow3[COLUMN1_INDEX];

	if (majorDiagonalSum == minorDiagonalSum)
		return true;
	return false;
}
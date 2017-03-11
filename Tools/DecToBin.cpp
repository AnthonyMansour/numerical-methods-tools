/*
Name: DecToBin
Purpose: Converts decimal base numbers into binary, up to 16 bits
Functions: DecToBin
*/

#include "stdafx.h"
#include <string>
#include <iostream>
#include <limits.h>

using namespace std;

unsigned long long DecToBin(int);

void main()
{
	int intDecimalBaseNum;

	cout << "--Converts a base 10 number to base 2--" << endl << "Please enter # now: ";
	cin >> intDecimalBaseNum; //decimal input

	//protect user input between 0 and 1111111111111111 (16 bits)
	while ((intDecimalBaseNum >  USHRT_MAX) || (intDecimalBaseNum < 0)) {
		cout << "Error: Out of bounds, must be a number between 0 and " << USHRT_MAX << ": ";
		cin.clear();
		cin.ignore();
		cin >> intDecimalBaseNum;
	}

	cout << "Result: " << DecToBin(intDecimalBaseNum); //binary output

	cin.get();
	cin.get();
	return;
}

/*
Converts the decimal input into a binary output
It accepts 1 parameter: intDecimalBaseNum
It returns 1 unsigned long long int parameter
*/
unsigned long long DecToBin(int intDecimalBaseNum) {

	bool boolBinaryBaseNum[16]{};
	int i = 0;
	string strBinaryOutput;

	//division by 2 loop, stores remainders in array
	while (intDecimalBaseNum > 0) {
		boolBinaryBaseNum[i] = intDecimalBaseNum % 2;
		if (boolBinaryBaseNum[i])
			intDecimalBaseNum--;
		intDecimalBaseNum = intDecimalBaseNum / 2;
		i++;
	}

	//converts array into a string
	for (int j = (sizeof(boolBinaryBaseNum) / sizeof(*boolBinaryBaseNum)) - 1; j >= 0; j--)
		strBinaryOutput += (boolBinaryBaseNum[j] ? "1" : "0");

	//converts string into a unsigned long long, this automatically removes unnecessary leading zeros
	return stoull(strBinaryOutput);
}

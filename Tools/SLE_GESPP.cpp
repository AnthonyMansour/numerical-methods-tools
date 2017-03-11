/*
Name: SLE_GESPP
Purpose: To solve the system of linear equations using Gaussian elimination with scaled partial pivoting
Functions: voidForwardElim(), voidBackSub(), voidSwapValues()
*/

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

#define intMax 4

void voidForwardElim(double(&)[intMax][intMax], int(&)[intMax]);
void voidBackSub(double(&)[intMax][intMax], double(&)[intMax], int(&)[intMax], double(&)[intMax]);
void voidSwapValues(int &, int &);

void main()
{
	int intIndex[intMax];
	double dblCoeff[intMax][intMax] = {
		{ 2, -1, 3, 7 },
		{ 4, 4, 0, 7 },
		{ 2, 1, 1, 3 },
		{ 6, 5, 4, 17 }
	};
	double dblRightSide[intMax] = { 15, 11, 7, 31 };
	double dblVariables[intMax];
	string alphabet = "abcdefghijklmnopqrstuvwxyz";

	cout << "--Gaussian Elimination with Scaled Partial Pivoting--" << endl << endl << "System of linear equations:" << endl;
	for (int i = 0; i < intMax; i++) {
		for (int j = 0; j < intMax; j++) {
			cout << dblCoeff[i][j] << alphabet.substr(alphabet.length() - intMax + j, 1);
			if ((j < intMax - 1) && (dblCoeff[i][j + 1] >= 0))
				cout << "+";
		}
		cout << "=" << dblRightSide[i];
		if (i < intMax - 1)
			cout << ", ";
	}
	cout << endl << endl;

	voidForwardElim(dblCoeff, intIndex);
	voidBackSub(dblCoeff, dblRightSide, intIndex, dblVariables);

	cout << "STEP 2: Backward Substitution & Answer" << endl;
	for (int h = 0; h < intMax; h++) {
		cout << alphabet.substr(alphabet.length() - intMax + h, 1) << " = " << dblVariables[h];
		if (h < intMax - 1)
			cout << ", ";
	}
	cin.get();
	return;
}

/*
Completes the forward elimination process of Gaussian Elimination with Scaled Partial Pivoting
Accepts 2 parameters: &dblCoeff[][], &intIndex[]
Also uses 1 external function: voidSwapValues()
Returns nothing, but updates dblCoeff[][], intIndex[], and outputs text to the console window
*/
void voidForwardElim(double(&dblCoeff)[intMax][intMax], int(&intIndex)[intMax]) {
	int l;
	double dblScale[intMax] = { 0,0,0,0 };
	double dblRatio;
	double dblRatioMax;
	double dblXMultiplier;

	cout << "STEP 1, Part 1: Forward Elimination for A" << endl << "1:" << endl;
	for (int h = 0; h < intMax; h++) {
		intIndex[h] = h;
		for (int i = 0; i < intMax; i++) {
			dblScale[h] = max(dblScale[h], abs(dblCoeff[h][i]));
		}
	}

	cout << "I={ ";
	for (int g = 0; g < intMax; g++) {
		cout << intIndex[g] + 1;
		if (g < intMax - 1)
			cout << ", ";
	}
	cout << " }" << endl;

	cout << "S={ ";
	for (int f = 0; f < intMax; f++) {
		cout << dblScale[f];
		if (f < intMax - 1)
			cout << ", ";
	}
	cout << " }" << endl;

	for (int j = 0; j < intMax - 1; j++) {
		dblRatioMax = 0;
		cout << "R={ ";
		for (int d = 0; d < j; d++)
			cout << "- , ";
		for (int k = j; k < intMax; k++) {
			dblRatio = abs(dblCoeff[intIndex[k]][j] / dblScale[intIndex[k]]);
			cout << dblRatio;
			if (k < intMax - 1)
				cout << ", ";
			if (dblRatio > dblRatioMax) {
				dblRatioMax = dblRatio;
				l = k;
			}
		}
		cout << " }" << endl;

		voidSwapValues(intIndex[l], intIndex[j]);

		cout << endl << j + 2 << ":" << endl << "I={ ";
		for (int e = 0; e < intMax; e++) {
			cout << intIndex[e] + 1;
			if (e < intMax - 1)
				cout << ", ";
		}
		cout << " }" << endl;

		cout << "S={ ";
		for (int c = 0; c < intMax; c++) {
			cout << dblScale[intIndex[c]];
			if (c < intMax - 1)
				cout << ", ";
		}
		cout << " }" << endl;

		for (int m = j + 1; m < intMax; m++) {
			dblXMultiplier = dblCoeff[intIndex[m]][j] / dblCoeff[intIndex[j]][j];
			dblCoeff[intIndex[m]][j] = dblXMultiplier;
			for (int n = j + 1; n < intMax; n++) {
				dblCoeff[intIndex[m]][n] = dblCoeff[intIndex[m]][n] - (dblXMultiplier * dblCoeff[intIndex[j]][n]);
			}
		}
	}

	cout << "R={ ";
	for (int b = 0; b < intMax - 1; b++)
		cout << "- , ";
	cout << abs(dblCoeff[intIndex[intMax - 1]][intMax - 1] / dblScale[intIndex[intMax - 1]]);
	cout << " }" << endl << endl;
	return;
}

/*
Completes the backward substitution process of Gaussian Elimination with Scaled Partial Pivoting
Accepts 4 parameters: &dblCoeff[][], &dblRightSide[], &intIndex[], &dblVariables[]
Returns nothing, but updates dblRightSide[], dblVariables[], and outputs text to the console window
*/
void voidBackSub(double(&dblCoeff)[intMax][intMax], double(&dblRightSide)[intMax], int(&intIndex)[intMax], double(&dblVariables)[intMax]) {
	double dblSum;

	cout << "STEP 1, Part 2: Forward Elimination for B" << endl;
	for (int i = 0; i < intMax - 1; i++) {
		for (int j = i + 1; j < intMax; j++) {
			dblRightSide[intIndex[j]] = dblRightSide[intIndex[j]] - (dblCoeff[intIndex[j]][i] * dblRightSide[intIndex[i]]);
		}
	}

	cout << "B={ ";
	for (int c = 0; c < intMax; c++) {
		cout << dblRightSide[intIndex[c]];
		if (c < intMax - 1)
			cout << ", ";
	}
	cout << " }" << endl << endl;

	dblVariables[intMax - 1] = dblRightSide[intIndex[intMax - 1]] / dblCoeff[intIndex[intMax - 1]][intMax - 1];

	for (int k = intMax - 2; k > -1; k--) {
		dblSum = dblRightSide[intIndex[k]];
		for (int l = k + 1; l < intMax; l++) {
			dblSum = dblSum - (dblCoeff[intIndex[k]][l] * dblVariables[l]);
		}
		dblVariables[k] = dblSum / dblCoeff[intIndex[k]][k];
	}
	return;
}

/*
Swaps two integer values
Accepts 2 parameters: &intFirst, &dblSecond
Returns nothing, but swaps the reference for the two inputs
*/
void voidSwapValues(int &intFirst, int &intSecond) {
	int tempVal;

	tempVal = intFirst;
	intFirst = intSecond;
	intSecond = tempVal;
	return;
}

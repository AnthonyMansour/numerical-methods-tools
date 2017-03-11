/*
Name: LeastSquares
Purpose: To estimate points on a curve using the least squares method
Functions: dblEstimate(), dblError(), voidSummations(), voidForwardElim(), voidBackSub(), voidSwapValues()
*/

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

#define intN 10
#define intMax 3

double dblEstimate(int, double, double, double);
double dblError(double, double, double, double, double);
void voidSummations(double(&)[intMax][intN]);
void voidForwardElim(double(&)[intMax][intMax], int(&)[intMax]);
void voidBackSub(double(&)[intMax][intMax], double(&)[intMax], int(&)[intMax], double(&)[intMax]);
void voidSwapValues(int &, int &);

int main()
{
	//Least Squares Variable Initializations
	double dblXYCoeffs[intMax][intN] = { { 2,4,6,8,10,12,14,16,18,20 },{ 52,50.5,52,53.2,51.5,51.9,54,52.5,51.9,55 } };
	int intErrorPoint = 3, intEstimate1 = 7, intEstimate2 = 17, intIndex[intMax], intAlphaOffset = 15;
	bool boolXYFlag;
	string alphabet = "abcdefghijklmnopqrstuvwxyz";

	//Least Squares Calculations
	voidSummations(dblXYCoeffs);

	//Gaussian Elimination Variable Initializations
	double dblCoeff[intMax][intMax] = {
		{ dblXYCoeffs[2][0], dblXYCoeffs[2][1], dblXYCoeffs[2][2] },
		{ dblXYCoeffs[2][1], dblXYCoeffs[2][3], dblXYCoeffs[2][4] },
		{ dblXYCoeffs[2][2], dblXYCoeffs[2][4], dblXYCoeffs[2][5] } },
		dblRightSide[intMax] = { dblXYCoeffs[2][8], dblXYCoeffs[2][7], dblXYCoeffs[2][6] },
		dblVariables[intMax];

	//Least Squares Formatting & Console Output
	cout << "---REGRESSION USING LEAST SQUARES METHOD---" << endl << endl << "Function form: y = alnx + bsinx + c" << endl << "--------------------------------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < 2; i++) {
		if (!i)
			cout << "| Time (hrs) |";
		else
			cout << "| Temp (C)   |";
		boolXYFlag = i;
		for (int j = 0; j < intN; j++)
			cout << setprecision(3) << " " << setw(6) << dblXYCoeffs[boolXYFlag][j] << " |";
		cout << endl;
	}

	cout << setprecision(6) << endl << "-Summation Coefficients-" << endl;

	for (int i = 0; i < intN - 1; i++) {
		cout << alphabet.substr(alphabet.length() - intAlphaOffset + i, 1) << " = " << dblXYCoeffs[2][i];
		if (i < intN - 2)
			cout << ", ";
	}

	cout << endl << endl << "-Gaussian Elimination with Scaled Partial Pivoting-" << endl << "System of linear equations:" << endl;

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

	//Gaussian Elimination Calculations & Console Output
	voidForwardElim(dblCoeff, intIndex);
	voidBackSub(dblCoeff, dblRightSide, intIndex, dblVariables);

	cout << "-Coefficients a, b, c-" << endl << "a: " << dblVariables[0] << endl << "b: " << dblVariables[1] << endl << "c: " << dblVariables[2] << endl << endl;
	cout << "-Estimates-" << endl << "@ Time = 7 hours, Temperature = " << dblEstimate(intEstimate1, dblVariables[0], dblVariables[1], dblVariables[2]) << " Deg C" << endl << "@ Time = 17 hours, Temperature = " << dblEstimate(intEstimate2, dblVariables[0], dblVariables[1], dblVariables[2]) << " Deg C" << endl << endl;
	cout << "-Relative error-" << endl << "@ Time = 8 hours, Relative error = " << dblError(dblXYCoeffs[0][intErrorPoint], dblXYCoeffs[1][intErrorPoint], dblVariables[0], dblVariables[1], dblVariables[2]) << " %" << endl;

	if (abs(dblError(dblXYCoeffs[0][3], dblXYCoeffs[1][3], dblVariables[0], dblVariables[1], dblVariables[2])) > 1)
		cout << "Relative error is greater than 1, not acceptable";
	else
		cout << "Relative error is less than 1, acceptable";

	cin.get();
	return 0;
}

/*
Function estimates the temperature at a given time
Accepts 4 parameters: intTime, dblA, dblB, dblC
Returns f(intTime), with f being the function form
*/
double dblEstimate(int intTime, double dblA, double dblB, double dblC) {
	return dblA*log(intTime) + dblB*sin(intTime) + dblC;
}

/*
Finds the error in the estimate
Accepts 5 parameters: dblX, dblY, dblA, dblB, dblC
Also uses 1 external function: dblEstimate()
Returns f(dblEstimate(dblX), dblY), with f being the error equation
*/
double dblError(double dblX, double dblY, double dblA, double dblB, double dblC) {
	return ((dblEstimate(dblX, dblA, dblB, dblC) - dblY) / dblY) * 100;
}

void voidSummations(double(&dblXYCoeffs)[intMax][intN]) {
	for (int j = 0; j < intN; j++) {
		dblXYCoeffs[2][0] += pow(log(dblXYCoeffs[0][j]), 2);
		dblXYCoeffs[2][1] += sin(dblXYCoeffs[0][j])*log(dblXYCoeffs[0][j]);
		dblXYCoeffs[2][2] += log(dblXYCoeffs[0][j]);
		dblXYCoeffs[2][3] += pow(sin(dblXYCoeffs[0][j]), 2);
		dblXYCoeffs[2][4] += sin(dblXYCoeffs[0][j]);
		dblXYCoeffs[2][5] += 1;
		dblXYCoeffs[2][6] += dblXYCoeffs[1][j];
		dblXYCoeffs[2][7] += dblXYCoeffs[1][j] * sin(dblXYCoeffs[0][j]);
		dblXYCoeffs[2][8] += dblXYCoeffs[1][j] * log(dblXYCoeffs[0][j]);
	}
}

/*
Completes the forward elimination process of Gaussian Elimination with Scaled Partial Pivoting
Accepts 2 parameters: &dblCoeff[][], &intIndex[]
Also uses 1 external function: voidSwapValues()
Returns nothing, but updates dblCoeff[][], intIndex[], and outputs text to the console window
*/
void voidForwardElim(double(&dblCoeff)[intMax][intMax], int(&intIndex)[intMax]) {
	int l;
	double dblScale[intMax];
	double dblRatio;
	double dblRatioMax;
	double dblXMultiplier;

	cout << "Part 1: Forward Elimination for A" << endl << "1:" << endl;

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

	cout << "Part 2: Forward Elimination for B" << endl;

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

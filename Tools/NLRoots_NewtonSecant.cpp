/*
Name: NLRoots_NewtonSecant
Purpose: To approximate a root of non-linear formulas using the Newton's and the Secant method
Functions: voidNewtonsMethod(), voidSecantMethod(), voidSecantMethodAlt(), dblFunction(), dblFunctionPrime(), voidSwapValues()
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

void voidNewtonsMethod(int, double, double, double);
void voidSecantMethod(int, double, double, double);
void voidSecantMethodAlt(int, double, double, double);
double dblFunction(double);
double dblFunctionPrime(double);
void voidSwapValues(double &, double &);

void main()
{
	voidNewtonsMethod(10, 5, 0.00001, 0.00001);
	cout << endl;
	voidSecantMethod(10, 3.5, 5, 0.00001);
	cout << endl;
	voidSecantMethodAlt(10, 3.5, 5, 0.00001);
	cout << endl << "Please scroll up to view Newton's method";
	cin.get();
	return;
}

/*
Uses Newton's root polishing method to determine non-linear roots
Accepts 4 parameters: intMaxIterations, dblX, dblErrorTarget, dblDelta
Also uses 2 external functions: dblFunction(), dblFunctionPrime()
Returns nothing, but outputs a text table to the console window
*/
void voidNewtonsMethod(int intMaxIterations, double dblX, double dblErrorTarget, double dblDelta)
{
	double dblFunctionResult;
	double dblFunctionPrimeResult;
	double dblError;

	dblFunctionResult = dblFunction(dblX);
	dblFunctionPrimeResult = dblFunctionPrime(dblX);

	cout << right << defaultfloat << setprecision(7) << "Newton's Method, F(x) = -5 + 0.25x^2 - xSin(x-1) - 0.5Cos(2x); Ea = " << dblErrorTarget << "; d = " << dblDelta << "; nMax = " << intMaxIterations << "; X0 = " << dblX << ";" << endl << "______________________________________________________________" << endl << "|   n   |     Xn     |    F(Xn)    |    F'(Xn)   |   Error   |" << endl << "--------------------------------------------------------------" << endl;
	cout << "|" << fixed << setw(4) << 0 << "   | " << left << setw(10) << dblX << " | " << setw(11) << dblFunctionResult << " | " << setw(11) << dblFunctionPrimeResult << " |     -     |" << endl;

	for (int n = 1; n <= intMaxIterations; n++) {
		dblFunctionPrimeResult = dblFunctionPrime(dblX);

		if (abs(dblFunctionPrimeResult) < dblDelta) {
			cout << "--------------------------------------------------------------" << endl << "Error: Small derivative." << endl;
			return;
		}

		dblError = dblFunctionResult / dblFunctionPrimeResult;
		dblX = dblX - dblError;
		dblFunctionResult = dblFunction(dblX);

		cout << "|" << setw(4) << right << n << "   | " << left << setw(10) << dblX << " | " << setw(11) << dblFunctionResult << " | " << setw(11) << dblFunctionPrimeResult << " | " << setw(9) << abs(dblError) << " |" << endl;

		if (abs(dblError) < dblErrorTarget) {
			cout << "--------------------------------------------------------------" << endl << "Convergence at x = " << dblX << endl;
			return;
		}
	}
	cout << "--------------------------------------------------------------" << endl << "Error: Max iterations limit of " << intMaxIterations << " reached." << endl;
	return;
}

/*
Uses the Secant root polishing method to determine non-linear roots (derived from the pseudocode in textbook)
Accepts 4 parameters: intMaxIterations, dblA, dblB, dblErrorTarget
Also uses 2 external functions: dblFunction(), voidSwapValues()
Returns nothing, but outputs a text table to the console window
*/
void voidSecantMethod(int intMaxIterations, double dblA, double dblB, double dblErrorTarget)
{
	double dblFunctionA;
	double dblFunctionB;
	double dblError;

	dblFunctionA = dblFunction(dblA);
	dblFunctionB = dblFunction(dblB);

	if (abs(dblFunctionA) > abs(dblFunctionB)) {
		voidSwapValues(dblA, dblB);
		voidSwapValues(dblFunctionA, dblFunctionB);
	}

	dblError = dblB - dblA;

	cout << right << defaultfloat << setprecision(7) << "Secant Method (TEXTBOOK VERSION), F(x) = -5 + 0.25x^2 - xSin(x-1) - 0.5Cos(2x); Ea = " << dblErrorTarget << "; nMax = " << intMaxIterations << "; X0 = " << dblA << "; X1 = " << dblB << ";" << endl << "________________________________________________" << endl << "|   n   |     Xn     |    F(Xn)    |   Error   |" << endl << "------------------------------------------------" << endl;
	cout << "|" << fixed << setw(4) << 0 << "   | " << left << setw(10) << dblA << " | " << setw(11) << dblFunctionA << " |     -     |" << endl;
	cout << "|" << right << setw(4) << 1 << "   | " << left << setw(10) << dblB << " | " << setw(11) << dblFunctionB << " | " << setw(9) << abs(dblError) << " |" << endl;

	for (int n = 2; n <= intMaxIterations; n++) {
		if (abs(dblFunctionA) > abs(dblFunctionB)) {
			voidSwapValues(dblA, dblB);
			voidSwapValues(dblFunctionA, dblFunctionB);
		}

		dblError = ((dblB - dblA) / (dblFunctionB - dblFunctionA));
		dblB = dblA;
		dblFunctionB = dblFunctionA;
		dblError = dblError * dblFunctionA;

		if (abs(dblError) < dblErrorTarget) {
			cout << "------------------------------------------------" << endl << "Convergence at x = " << dblB << endl;
			return;
		}

		dblA = dblA - dblError;
		dblFunctionA = dblFunction(dblA);

		cout << "|" << right << setw(4) << n << "   | " << left << setw(10) << dblA << " | " << setw(11) << dblFunctionB << " | " << setw(9) << abs(dblError) << " |" << endl;
	}
	cout << "------------------------------------------------" << endl << "Error: Max iterations limit of " << intMaxIterations << " reached." << endl;
	return;
}

/*
Uses the Secant root polishing method to determine non-linear roots (derived from Endoint Convergence formulas)
Accepts 4 parameters: intMaxIterations, dblA, dblB, dblErrorTarget
Also uses 2 external functions: dblFunction(), voidSwapValues()
Returns nothing, but outputs a text table to the console window
*/
void voidSecantMethodAlt(int intMaxIterations, double dblA, double dblB, double dblErrorTarget)
{
	double dblFunctionA;
	double dblFunctionB;
	double dblError;

	dblFunctionA = dblFunction(dblA);
	dblFunctionB = dblFunction(dblB);

	if (abs(dblFunctionA) > abs(dblFunctionB)) {
		voidSwapValues(dblA, dblB);
		voidSwapValues(dblFunctionA, dblFunctionB);
	}

	dblError = dblB - dblA;

	cout << right << defaultfloat << setprecision(7) << "Secant Method (ENDPOINT CONVERGENCE VERSION), F(x) = -5 + 0.25x^2 - xSin(x-1) - 0.5Cos(2x); Ea = " << dblErrorTarget << "; nMax = " << intMaxIterations << "; X0 = " << dblA << "; X1 = " << dblB << ";" << endl << "________________________________________________" << endl << "|   n   |     Xn     |    F(Xn)    |   Error   |" << endl << "------------------------------------------------" << endl;
	cout << "|" << fixed << setw(4) << 0 << "   | " << left << setw(10) << dblA << " | " << setw(11) << dblFunctionA << " |     -     |" << endl;
	cout << "|" << right << setw(4) << 1 << "   | " << left << setw(10) << dblB << " | " << setw(11) << dblFunctionB << " | " << setw(9) << abs(dblError) << " |" << endl;

	for (int n = 2; n <= intMaxIterations; n++) {
		dblError = ((dblB - dblA) / (dblFunctionB - dblFunctionA)) * dblFunctionB;
		dblA = dblB;
		dblFunctionA = dblFunctionB;
		dblB = dblB - dblError;
		dblFunctionB = dblFunction(dblB);

		cout << "|" << right << setw(4) << n << "   | " << left << setw(10) << dblB << " | " << setw(11) << dblFunctionB << " | " << setw(9) << abs(dblError) << " |" << endl;

		if (abs(dblError) < dblErrorTarget) {
			cout << "------------------------------------------------" << endl << "Convergence at x = " << dblB << endl;
			return;
		}
	}
	cout << "------------------------------------------------" << endl << "Error: Max iterations limit of " << intMaxIterations << " reached." << endl;
	return;
}

/*
Uses a hard-coded function formula to return f(x)
Accepts 1 parameter: x
Returns 1 value: f(x) as dblResult
*/
double dblFunction(double x)
{
	double dblResult;
	dblResult = ((-5) + ((0.25) * pow(x, 2)) - (x *sin(x - 1)) - (0.5 * cos(2 * x)));
	return dblResult;
}

/*
Uses a hard-coded function prime formula to return f'(x)
Accepts 1 parameter: x
Returns 1 value: f'(x) as dblResult
*/
double dblFunctionPrime(double x)
{
	double dblResult;
	dblResult = ((0.5 * x) - (x * cos(1 - x)) + (sin(1 - x)) + (2 * cos(x) * sin(x)));
	return dblResult;
}

/*
Swaps two double values
Accepts 2 parameters: &dblFirst, &dblSecond
Returns nothing, but swaps the reference for the two inputs
*/
void voidSwapValues(double &dblFirst, double &dblSecond) {
	double tempVal;

	tempVal = dblFirst;
	dblFirst = dblSecond;
	dblSecond = tempVal;
	return;
}

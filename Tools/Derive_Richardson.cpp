/*
Name: Derive_Richardson
Purpose: To calculate the numerical derivative using the Richardson Extrapolation method
Functions: voidDerivative(), intNumOfMin(), intNumOfMax()
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>

using namespace std;

#define intN 3
#define intMax 100
#define funcF(x) pow(sqrt(exp(sin(x))+5),-cos(3*x)*sin(5*x))

void voidDerivative(double, double, double(&)[intN][intN]);
int intNumOfMin(double(&)[intMax + 1]);
int intNumOfMax(double(&)[intMax + 1]);

int main()
{
	//Variable Initializations
	double dblRichArray[intN][intN], dblYPoints[intMax + 1], dblH = 0.5, dlbStepDevisor = 10.0;
	int intTableStep = 5;

	for (int i = 0; i <= intMax; i++) {
		//Derivative Calculations
		voidDerivative(i / dlbStepDevisor, dblH, dblRichArray);

		//Point Storage for First Derivative Test
		dblYPoints[i] = dblRichArray[intN - 1][intN - 1];
	}

	//Table Formating & Output for Derivatives
	cout << "---NUMERICAL DIFFERENTIATION USING RICHARDSON EXTRAPOLATION---" << endl << endl << "Function: f(x) = (e^Sin(x) + 5)^-0.5Cos(3x)Sin(5x)" << endl << "h = " << dblH << endl << "Precision = O(h^" << intN * 2 << ")" << endl;
	for (int i = 0; i < intTableStep; i++)
		cout << "___________________ ";
	cout << endl;
	for (int i = 0; i < intTableStep; i++)
		cout << "|  X  |   f'(x)   | ";
	cout << endl;
	for (int i = 0; i < intTableStep; i++)
		cout << "------------------- ";
	cout << endl;

	for (int i = 0; i < intMax / intTableStep; i++) {
		for (int j = 0; j < intTableStep; j++)
			cout << "| " << setprecision(4) << setw(3) << (i + j * (intMax / intTableStep)) / dlbStepDevisor << " | " << setw(9) << dblYPoints[i + j * (intMax / intTableStep)] << " | ";
		cout << endl;
	}

	for (int i = 0; i < intMax - (intMax / intTableStep); i++)
		cout << " ";
	cout << "| " << setprecision(4) << setw(3) << intMax / dlbStepDevisor << " | " << setw(9) << dblYPoints[intMax] << " | " << endl << endl;

	//Calculate and output the number of local minima and maxima
	cout << "The number of local minima for the first 10 seconds is " << intNumOfMin(dblYPoints) << endl;
	cout << "The number of local maxima for the first 10 seconds is " << intNumOfMax(dblYPoints);

	cin.get();
	return 0;
}

/*
Finds the derivative at given points using Richardson Extrapolation
Accepts 3 parameters: dblX, dblH, &dblRichArray[][]
Also uses 1 defined function: funcF()
Returns nothing, but updates dblRichArray[][]
*/
void voidDerivative(double dblX, double dblH, double(&dblRichArray)[intN][intN]) {
	for (int i = 0; i < intN; i++) {
		dblRichArray[i][0] = (funcF((dblX + dblH)) - funcF((dblX - dblH))) / (2 * dblH);
		for (int j = 1; j <= i; j++)
			dblRichArray[i][j] = dblRichArray[i][j - 1] + ((dblRichArray[i][j - 1] - dblRichArray[i - 1][j - 1]) / (pow(4, j) - 1));
		dblH = dblH / 2;
	}
}

/*
Finds the number of local minima
Accepts 1 parameter: &dblYPoints[]
Returns intMins
*/
int intNumOfMin(double(&dblYPoints)[intMax + 1]) {
	int intMins = 0;
	for (int i = 1; i <= intMax; i++) {
		if ((dblYPoints[i - 1] < 0) && (dblYPoints[i] > 0))
			intMins++;
	}
	return intMins;
}

/*
Finds the number of local maxima
Accepts 1 parameter: &dblYPoints[]
Returns intMaxs
*/
int intNumOfMax(double(&dblYPoints)[intMax + 1]) {
	int intMaxs = 0;
	for (int i = 1; i <= intMax; i++) {
		if ((dblYPoints[i - 1] > 0) && (dblYPoints[i] < 0))
			intMaxs++;
	}
	return intMaxs;
}

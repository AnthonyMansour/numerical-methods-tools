/*
Name: Integral_Trap_Romberg_AdapSimps
Purpose: To calculate the numerical integral using the Trapezoid, Romberg, and Adaptive Simpson method
Functions: dblTrapezoid(), voidRomberg(), dblSimpson()
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>

using namespace std;

#define dblPI (4.0*atan(1.0))
#define funcF(x) (1/(exp(pow(x,2.0))))
#define funcG(x) (pow((sin(3*x) + sin(4*x) + sin(6*x)), 2.0))
#define intN 4

double dblTrapezoid(int, double, double);
void voidRomberg(int, double, double, double(&)[intN][intN]);
double dblSimpson(double, double, double, int, int);

int main()
{
	//Variable Initializations
	int intPoints1 = 15, intPoints2 = 41, intLvl = 0, intLvlMax = 10;
	int intPoints;
	double dblLowerLim = 0, dblUpperLim1 = 0.5, dblUpperLim2 = 1, dblMultiplier1 = 2 / sqrt(dblPI), dblMultiplier2 = 2 * dblPI, dblPrecision = 0.001;
	double dblRombergArr[intN][intN], dblTrapAns, dblRomAns, dblUpperLim;

	//Title & Formatting Output
	cout << "---NUMERICAL INTEGRATION---" << endl << "Function: erf(x) = (2/(PI^0.5)) * S(e^-(t^2) dt)[from 0 to x]" << endl << endl;

	for (int l = 1; l < 3; l++) {
		if (1 == l) {
			dblUpperLim = dblUpperLim1;
			intPoints = intPoints1;
		}
		else {
			dblUpperLim = dblUpperLim2;
			intPoints = intPoints2;
		}

		//Calculations
		dblTrapAns = dblMultiplier1*dblTrapezoid(intPoints, dblLowerLim, dblUpperLim);
		voidRomberg(intN, dblLowerLim, dblUpperLim, dblRombergArr);
		dblRomAns = dblRombergArr[intN - 1][intN - 1];

		//Calculation Output
		cout << "--Trapezoidal Method--" << endl << "Tolerance = 10^-4" << endl << endl;
		cout << "erf(" << dblUpperLim << ") = " << dblTrapAns << endl << endl;

		cout << "--Romberg Method--" << endl << "N = 4" << endl << endl;

		for (int i = 0; i < intN; i++) {
			for (int j = 0; j <= i; j++)
				cout << setw(8) << dblMultiplier1*dblRombergArr[i][j] << "  ";
			cout << endl;
		}
		cout << endl << "erf(" << dblUpperLim << ") = " << dblRomAns << endl << endl;
		cout << "Absolute Error = " << abs(dblTrapAns - dblRomAns) << endl << "-------------------------------------------------------"<< endl;
	}

	//Simpsons Calculation and Output
	cout << "--Adaptive Simpson Method--" << endl << "Functions: P = (0.5*PI) * S(x(t)^2 dt)[from 0 to 2*PI]" << endl << "	   x(t) = sin(3t) + sin(4t) + sin(6t)";
	cout << endl << endl << "P = " << dblSimpson(dblLowerLim, dblMultiplier2, dblPrecision, intLvl, intLvlMax)/ dblMultiplier2;

	cin.get();
    return 0;
}

/*
Finds the integral at given points using the Trapezoid method
Accepts 3 parameters: intPoints, dblLowerLim, dblUpperLim
Also uses 1 defined function: funcF()
Returns dblSum
*/
double dblTrapezoid(int intPoints, double dblLowerLim, double dblUpperLim) {
	double dblH = (dblUpperLim - dblLowerLim) / intPoints;
	double dblSum = 0.5*(funcF(dblLowerLim) + funcF(dblUpperLim));
	double dblAddition;
	for (int i = 1; i < intPoints; i++) {
		dblAddition = dblLowerLim + (i*dblH);
		dblSum += funcF(dblAddition);
	}
	dblSum = dblSum*dblH;
	return dblSum;
}

/*
Finds the integral at given points using the Romberg method
Accepts 4 parameters: intPoints, dblLowerLim, dblUpperLim, &dblRombergArr[][]
Also uses 1 defined function: funcF()
Returns nothing, but updates dblRombergArr[][]
*/
void voidRomberg(int intPoints, double dblLowerLim, double dblUpperLim, double(&dblRombergArr)[intN][intN]) {
	double dblH = dblUpperLim - dblLowerLim;
	double dblSum;
	dblRombergArr[0][0] = (dblH / 2)*(funcF(dblLowerLim) + funcF(dblUpperLim));
	for (int i = 1; i < intPoints; i++) {
		dblH = dblH / 2;
		dblSum = 0;
		for (int j = 1; j < pow(2, i); j += 2)
			dblSum = dblSum + funcF((dblLowerLim + (j*dblH)));
		dblRombergArr[i][0] = 0.5*dblRombergArr[i - 1][0] + (dblSum*dblH);
		for (int k = 1; k <= i; k++)
			dblRombergArr[i][k] = dblRombergArr[i][k - 1] + ((dblRombergArr[i][k - 1] - dblRombergArr[i - 1][k - 1]) / (pow(4, k) - 1));
	}
}

/*
Finds the integral at given points using the Simpson Method
Accepts 5 parameters: dblLowerLim, dblUpperLim, dblAccuracy, intLvl, intLvlMax
Also uses 1 defined function: funcG()
Returns dblSimp2 or  dblSimpLeft + dblSimpRight
*/
double dblSimpson(double dblLowerLim, double dblUpperLim, double dblAccuracy, int intLvl, int intLvlMax) {
	intLvl++;
	double dblH = dblUpperLim - dblLowerLim;
	double dblC = (dblLowerLim + dblUpperLim) / 2;
	double dblSimp1 = (dblH*(funcG(dblLowerLim) + 4 * funcG(dblC) + funcG(dblUpperLim))) / 6;
	double dblD = (dblLowerLim + dblC) / 2;
	double dblE = (dblC + dblUpperLim) / 2;
	double dblSimp2 = (dblH*(funcG(dblLowerLim) + 4 * funcG(dblD) + 2 * funcG(dblC) + 4 * funcG(dblE) + funcG(dblUpperLim))) / 12;
	if (intLvl >= intLvlMax)
		return dblSimp2;
	else {
		if (abs(dblSimp2 - dblSimp1) < 15 * dblAccuracy)
			return (dblSimp2 + (dblSimp2 - dblSimp1) / 15);
		else {
			double dblSimpLeft = dblSimpson(dblLowerLim, dblC, dblAccuracy / 2, intLvl, intLvlMax);
			double dblSimpRight = dblSimpson(dblC, dblUpperLim, dblAccuracy / 2, intLvl, intLvlMax);
			return (dblSimpLeft + dblSimpRight);
		}
	}
}

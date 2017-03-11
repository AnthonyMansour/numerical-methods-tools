/*
Name: NaturalCubicSpline
Purpose: To calculate the coefficients and evaluate points of a natural cubic spline
Functions: voidFindCoeffs(), dblEval()
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>

using namespace std;

#define intN 9

void voidFindCoeffs(double(&)[7][intN]);
double dblEval(double(&)[7][intN], double);

void main()
{
	//Initialization
	//array order = {x, y, h, b, u, v, z}
	double dblTable[7][intN] = {
		{ 0, 0.2, 0.4, 0.6, 0.8, 1.1, 1.4, 1.6, 2 },
		{ 4, 3.89, 3.14, 3.14, 3.89, 3.51, 1.24, 1.21, 4 }};
	double dblEval1 = 0.3;
	double dblEval2 = 0.7;
	double dblEval3 = 1.2;
	double dblTemp1;
	char chrArray[9] = { "iTYHBVUZ"};

	//Calculations
	voidFindCoeffs(dblTable);

	//Formatting and Output
	cout << setprecision(5) <<"---SOLVING NATURAL CUBIC SPLINES---" << endl << endl << "Coefficients (Z) and intermediate calculations (H,B,U,V) are displayed below for the given table (T,Y)" << endl << "________________________________________________________________________________________________________" << endl;

	for (int i = 0; i < 8; i++) {
		if (i == 1 || i==3 || i == 7)
			cout << "--------------------------------------------------------------------------------------------------------" << endl;
		cout << "| " << chrArray[i] << " |";
		for (int j = 0; j < intN; j++) {
			if (i == 0)
				dblTemp1 = j;
			else
				dblTemp1 = dblTable[i - 1][j];
			cout << " " << setw(8) << dblTemp1 << " |";
		}
		cout << endl;
	}

	cout << endl << "Coefficients of Si(T):" << endl << "____________________________________________________________" << endl << "| Si |      t^3 |      t^2 |        t | Constant | Interval " << endl << "------------------------------------------------------------" << endl;
	for (int i = 0; i < intN-1; i++) {
		cout << "| " << "S" << i << " |";
		cout << " " << setw(8) << (dblTable[6][i + 1] / (6 * dblTable[2][i])) - (dblTable[6][i] / (6 * dblTable[2][i])) << " |";
		cout << " " << setw(8) << (dblTable[6][i + 1] / (6 * dblTable[2][i]))*(-3 * dblTable[0][i]) + (dblTable[6][i] / (6 * dblTable[2][i]))*(3 * dblTable[0][i + 1]) << " |";
		cout << " " << setw(8) << (dblTable[6][i + 1] / (6 * dblTable[2][i]))*(3 * pow(dblTable[0][i], 2)) + (dblTable[6][i] / (6 * dblTable[2][i]))*(-3 * pow(dblTable[0][i + 1], 2)) + ((dblTable[1][i + 1] / dblTable[2][i]) - (dblTable[2][i] * dblTable[6][i + 1] / 6)) - ((dblTable[1][i] / dblTable[2][i]) - (dblTable[2][i] * dblTable[6][i] / 6)) << " |";
		cout << " " << setw(8) << (dblTable[6][i + 1] / (6 * dblTable[2][i]))*(-pow(dblTable[0][i], 3)) + (dblTable[6][i] / (6 * dblTable[2][i]))*(pow(dblTable[0][i + 1], 3)) - ((dblTable[1][i + 1] / dblTable[2][i]) - (dblTable[2][i] * dblTable[6][i + 1] / 6))*(dblTable[0][i]) + ((dblTable[1][i] / dblTable[2][i]) - (dblTable[2][i] * dblTable[6][i] / 6))*(dblTable[0][i + 1]) << " |";
		cout << " " << setprecision(2) << "[" << dblTable[0][i] << ", " << dblTable[0][i + 1] << "]" << setprecision(5) << endl;
	}

	cout << endl << "Evaluations of S(T):" << endl;
	cout << "S(" << dblEval1 << ") = " << dblEval(dblTable, dblEval1) << endl;
	cout << "S(" << dblEval2 << ") = " << dblEval(dblTable, dblEval2) << endl;
	cout << "S(" << dblEval3 << ") = " << dblEval(dblTable, dblEval3);

	cin.get();
	return;
}

/*
Finds the coefficients of a natural cubic spline
Accepts 2 parameters: intN, &dblArrays[][]
Returns nothing, but updates dblArrays[][]
*/
void voidFindCoeffs(double(&dblArrays)[7][intN]) {
	for (int i = 0; i < intN - 1; i++) {
		dblArrays[2][i] = dblArrays[0][i + 1] - dblArrays[0][i];
		dblArrays[3][i] = (dblArrays[1][i + 1] - dblArrays[1][i]) / dblArrays[2][i];
	}
	dblArrays[4][1] = 2 * (dblArrays[2][0] + dblArrays[2][1]);
	dblArrays[5][1] = 6 * (dblArrays[3][1] - dblArrays[3][0]);
	for (int i = 2; i < intN - 1; i++) {
		dblArrays[4][i] = 2 * (dblArrays[2][i] + dblArrays[2][i - 1]) - pow(dblArrays[2][i - 1], 2) / dblArrays[4][i - 1];
		dblArrays[5][i] = 6 * (dblArrays[3][i] - dblArrays[3][i - 1]) - dblArrays[2][i - 1] * dblArrays[5][i - 1] / dblArrays[4][i - 1];
	}
	dblArrays[6][intN - 1] = 0;
	for (int i = intN - 2; i > 0; i--)
		dblArrays[6][i] = (dblArrays[5][i] - dblArrays[2][i] * dblArrays[6][i + 1]) / dblArrays[4][i];
	dblArrays[6][0] = 0;
	return;
}

/*
Evaluates the spline at a given x value
Accepts 2 parameters: intN, &dblSeries[][], dblX
Returns the y value at the given x value
*/
double dblEval(double(&dblArrays)[7][intN], double dblX) {
	int i = intN - 2;
	double dblTemp1;
	double dblTemp2;

	for (i; i >= 0; i--) {
		if (dblX - dblArrays[0][i] >= 0)
			break;
	}

	dblTemp1 = dblArrays[0][i + 1] - dblArrays[0][i];
	dblTemp2 = (dblArrays[6][i] / 2) + (dblX - dblArrays[0][i])*(dblArrays[6][i + 1] - dblArrays[6][i]) / (6 * dblTemp1);
	dblTemp2 = -(dblTemp1 / 6)*(dblArrays[6][i + 1] + 2 * dblArrays[6][i]) + (dblArrays[1][i + 1] - dblArrays[1][i]) / dblTemp1 + (dblX - dblArrays[0][i])*(dblTemp2);
	return (dblArrays[1][i] + (dblX - dblArrays[0][i])*(dblTemp2));
}

/*
Name: SLE_Runge_Kutta4
Purpose: To calculate a system of differential equations using the Runge-Kutta method
Functions: voidRK4_System(), voidXP_System(), dblFindSmallest()
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>

using namespace std;

#define intN 3
#define intOrder 4

void voidRK4_System(double, double, double(&)[intN], int);
void voidXP_System(double, double(&)[intN], double(&)[intN]);
double dblFindSmallest(double, double, double(&)[intN], double);

int main()
{
	//Variable Initializations
	int intSteps = 100;
	double dblA = 0, dblB = 10, dblT = 0, dblH = (dblB - dblA) / intSteps, dblArrayX[intN] = { 25,20,10 }, dblTarget = 0.0001;

	//Title & Formatting
	cout << "---SYSTEM OF DIFFERENTIATION EQUATIONS USING THE RUNGE-KUTTA METHOD---" << endl << endl << "Functions:" << endl << "X1' = -(10 * X1 / 20)" << endl << "X2' = (10 * X1 / 20) - (10 * X2 / 40)" << endl << "X3' = (10 * X2 / 40) - (10 * X3 / 50)" << endl << "V1 = 25, V2 = 20, V3 = 10, n = 100, interval = [0,10], Order 4" << endl << endl;
	cout << "| " << setw(3) << " J " << " | " << setw(5) << " T " << " | " << setw(7) << "   X1  " << " |" << setw(7) << "   X2  " << " |" << setw(7) << "   X3  " << " |" << endl;
	cout << "-------------------------------------------" << endl;

	//Calculations & Output
		//Part A
	voidRK4_System(dblH, dblT, dblArrayX, intSteps);

		//Part B
	dblH = 0.001, dblArrayX[0] = 25, dblArrayX[1] = 20, dblArrayX[2] = 10;
	cout << endl << "The smallest value of T such that X1(T) & X2(T) & X3(T) < " << dblTarget << " and H = " << dblH << " is :" << endl << dblFindSmallest(dblH, dblT, dblArrayX, dblTarget);

	cin.get();
	return 0;
}

/*
Solves the system of differential equations using an order 4 Runge-Kutta method
Accepts 4 parameters: dblH, dblT, dblArrayX[], intSteps
Returns nothing, but outputs j, t, x1, x2, x3 for every iteration from 0 to intSteps
*/
void voidRK4_System(double dblH, double dblT, double (&dblArrayX)[intN], int intSteps) {
	double dblArrayY[intN], dblArrayK[intOrder][intN];
	cout << "| " << setw(3) << 0 << " | " << setw(5) << dblT << " | " << setprecision(4) << setw(7) << dblArrayX[0] << " |" << setw(7) << dblArrayX[1] << " |" << setw(7) << dblArrayX[2] << " |" << endl;

	for (int j = 1; j <= intSteps; j++) {
		voidXP_System(dblT, dblArrayX, dblArrayK[0]);
		for (int i = 0; i < intN; i++)
			dblArrayY[i] = dblArrayX[i] + dblH/2*dblArrayK[0][i];
		voidXP_System((dblT+(dblH/2)), dblArrayY, dblArrayK[1]);
		for (int i = 0; i < intN; i++)
			dblArrayY[i] = dblArrayX[i] + dblH/2*dblArrayK[1][i];
		voidXP_System((dblT + (dblH / 2)), dblArrayY, dblArrayK[2]);
		for (int i = 0; i < intN; i++)
			dblArrayY[i] = dblArrayX[i] + dblH*dblArrayK[2][i];
		voidXP_System((dblT + dblH), dblArrayY, dblArrayK[3]);
		for (int i = 0; i < intN; i++)
			dblArrayX[i] = dblArrayX[i] + dblH*(dblArrayK[0][i] + 2*dblArrayK[1][i] + 2*dblArrayK[2][i] + dblArrayK[3][i])/6;

		dblT = dblT + dblH;

		cout << "| " << setw(3) << j << " | " << setw(5) << dblT << " | " << setprecision(4) << setw(7) << dblArrayX[0] << " |" << setw(7) << dblArrayX[1] << " |" << setw(7) << dblArrayX[2] << " |" << endl;
	}
}

/*
Calculates the derivative of x1, x2, and x3 at a given t value
Accepts 3 parameters: dblT, dblArrayX[], dblArrayF[]
Returns nothing, but updates the 3 derivative arrays
*/
void voidXP_System(double dblT, double(&dblArrayX)[intN], double(&dblArrayF)[intN]) {
	//dblArrayF[0] = dblArrayX[0] - dblArrayX[1] + dblT*(2 - dblT*(1 + dblT));
	//dblArrayF[1] = dblArrayX[0] + dblArrayX[1] - pow(dblT, 2)*(4 - dblT);

	dblArrayF[0] = -(10 * dblArrayX[0] / 20);
	dblArrayF[1] = (10 * dblArrayX[0] / 20) - (10 * dblArrayX[1] / 40);
	dblArrayF[2] = (10 * dblArrayX[1] / 40) - (10 * dblArrayX[2] / 50);
}

/*
Finds the smallest value of dblT at which all dblArrayX[]s are < dblTarget
Accepts 4 parameters: dblH, dblT, dblArrayX[], dblTarget
Returns dblT
*/
double dblFindSmallest(double dblH, double dblT, double(&dblArrayX)[intN], double dblTarget) {
	double dblArrayY[intN], dblArrayK[intOrder][intN];

	while (dblArrayX[0] >= dblTarget || dblArrayX[1] >= dblTarget || dblArrayX[2] >= dblTarget) {
		voidXP_System(dblT, dblArrayX, dblArrayK[0]);
		for (int i = 0; i < intN; i++)
			dblArrayY[i] = dblArrayX[i] + dblH / 2 * dblArrayK[0][i];
		voidXP_System((dblT + (dblH / 2)), dblArrayY, dblArrayK[1]);
		for (int i = 0; i < intN; i++)
			dblArrayY[i] = dblArrayX[i] + dblH / 2 * dblArrayK[1][i];
		voidXP_System((dblT + (dblH / 2)), dblArrayY, dblArrayK[2]);
		for (int i = 0; i < intN; i++)
			dblArrayY[i] = dblArrayX[i] + dblH*dblArrayK[2][i];
		voidXP_System((dblT + dblH), dblArrayY, dblArrayK[3]);
		for (int i = 0; i < intN; i++)
			dblArrayX[i] = dblArrayX[i] + dblH*(dblArrayK[0][i] + 2 * dblArrayK[1][i] + 2 * dblArrayK[2][i] + dblArrayK[3][i]) / 6;

		dblT = dblT + dblH;
	}
	return dblT;
}

/*
Name: Runge_Kutta4
Purpose: To calculate the differential equation using the Runge-Kutta method
Functions: voidRK4()
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>

using namespace std;

#define dblK (6.22*pow(10, -19))
#define dblN1 (2000.0)
#define dblN2 (2000.0)
#define dblN3 (3000.0)
#define funcF(t,x) (dblK*pow((dblN1-(x/2)), 2.0)*pow((dblN2-(x/2)), 2.0)*pow((dblN3-((3*x)/4)), 3.0))

void voidRK4(double, double, double, int);

int main()
{
	//Variable Initializations
	int intN = 100;
	double dblA = 0, dblB = 1, dlbH = (dblB - dblA) / intN, dblX = 0, dblT = dblA;

	//Title & Formatting
	cout << "---DIFFERENTIATION EQUATIONS USING THE RUNGE-KUTTA METHOD---" << endl << endl << "Function: F'(x) = K*((n1 - x/2)^2)*((n2 - x/2)^2)*((n3 - 3x/4)^3)" << endl << "K = 6.22*10^-19, n1 = n2 = 2000, n3 = 3000, n = 100, interval = [0,1], Order 4" << endl << endl;
	cout << "|  J  |   t   |    x    |" << endl << "-------------------------" << endl;

	//Calculations & Output
	voidRK4(dblT, dblX, dlbH, intN);

	cin.get();
    return 0;
}

/*
Function solves the differential equation using an order 4 Runge-Kutta method
Accepts 4 parameters: dblT, dblX, dblH, intN
Also uses 1 defined function: funcF()
Returns nothing, but outputs i, t, and x every iteration from 0 to intN
*/
void voidRK4(double dblT, double dblX, double dblH, int intN) {
	cout << "| " << setw(3) << 0 << " | " << setw(5) << dblT << " | " << setw(7) << dblX << " |" << endl;
	double dblTa = dblT;
	for (int i = 1; i <= intN; i++) {
		double dblK1 = dblH*funcF(dblT, dblX);
		double dblK2 = dblH*funcF((dblT + (dblH / 2)), (dblX + (dblK1 / 2)));
		double dblK3 = dblH*funcF((dblT + (dblH / 2)), (dblX + (dblK2 / 2)));
		double dblK4 = dblH*funcF((dblT + dblH), (dblX + dblK3));
		dblX = dblX + ((dblK1 + (2 * dblK2) + (2 * dblK3) + dblK4) / 6);
		dblT = dblTa + (i*dblH);
		cout << "| " << setw(3) << i << " | " << setw(5) << dblT << " | " << setw(7) << dblX << " |" << endl;
	}
}

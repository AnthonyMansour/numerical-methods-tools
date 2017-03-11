/*
Name: PolyInterp_NDD
Purpose: To use polynomial interpolation with Newton's divided differences method to fit a curve
Functions: voidFindCoeffs(), dblEvaluate()
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>

using namespace std;

void voidFindCoeffs(int, double(&)[3][9]);
double dblEvaluate(int, double[3][9], double);

void main()
{
	//Initialization
	int intT0Size = 9;
	int intT1Size = 5;
	int intT2Size = 3;
	int intCurArray = intT0Size;
	double dblEval0 = 232;
	double dblEval1 = 255;
	double dblEval2 = 288;
	double dlbCurEval = dblEval0;
	double dblEvalErr = 250;
	double dblArrays[3][3][9] = { {
		{ 220, 230, 240, 250, 260, 270, 280, 290, 300 },
		{ 17.188, 20.78, 24.97, 29.82, 35.42, 41.85, 49.18, 57.53, 66.98 },
		{} },{
			{ 220, 240, 260, 280, 300 },
			{ 17.188, 24.97, 35.42, 49.18, 66.98 },
			{} },{
				{ 230, 260, 290 },
				{ 20.78, 35.42, 57.53 },
				{} }
	};

	//Calculations
	voidFindCoeffs(intT0Size, dblArrays[0]);
	voidFindCoeffs(intT1Size, dblArrays[1]);
	voidFindCoeffs(intT2Size, dblArrays[2]);

	//Formatting and Output
	cout << "---CURVE FITTING USING NEWTON'S DIVIDED DIFFERENCE METHOD---" << endl;

	for (int j = 0; j < 3; ++j) {
		if (j == 1)
			intCurArray = intT1Size;
		else if (j == 2)
			intCurArray = intT2Size;
		cout << endl << "__________________";
		for (int i = 0; i < intCurArray; ++i)
			cout << "_______";
		cout << endl << "|Temperature (F)||";
		for (int i = 0; i < intCurArray; ++i)
			cout << setw(6) << dblArrays[j][0][i] << "|";
		cout << endl << "|Pressure  (psi)||";
		for (int i = 0; i < intCurArray; ++i)
			cout << setw(6) << dblArrays[j][1][i] << "|";
		cout << endl << endl << "--For given table T" << (j + 1) << " above, expected to be of order " << (intCurArray - 1) << "--" << endl << "-Coefficients:" << endl;
		for (int i = 0; i < intCurArray; ++i) {
			cout << "a" << i << " = " << dblArrays[j][2][i];
			if (i < (intCurArray - 1))
				cout << ", ";
			else
				cout << endl;
		}
		cout << endl << "-Evaluations:" << endl;
		dlbCurEval = dblEval0;
		for (int i = 0; i < 3; ++i) {
			if (i == 1)
				dlbCurEval = dblEval1;
			else if (i == 2)
				dlbCurEval = dblEval2;
			cout << "P" << (j + 1) << "(" << dlbCurEval << ") = " << dblEvaluate(intCurArray, dblArrays[j], dlbCurEval) << endl;
		}
		cout << endl << "-Error:" << endl << "At T = 250: " << ((abs(dblEvaluate(intT0Size, dblArrays[0], dblEvalErr) - dblEvaluate(intCurArray, dblArrays[j], dblEvalErr)) / dblEvaluate(intT0Size, dblArrays[0], dblEvalErr)) * 100) << " %" << endl;
	}
	cin.get();;
	return;
}

/*
Finds the coefficients of the polynomial equation using the divided differences method
Accepts 2 parameters: intN, &dblSeries[][]
Returns nothing, but updates dblCoeff[][]
*/
void voidFindCoeffs(int intN, double(&dblSeries)[3][9]) {
	for (int i = 0; i < intN; ++i)
		dblSeries[2][i] = dblSeries[1][i];
	for (int j = 1; j < intN; ++j)
		for (int k = (intN - 1); k >(j - 1); --k)
			dblSeries[2][k] = ((dblSeries[2][k] - dblSeries[2][k - 1]) / (dblSeries[0][k] - dblSeries[0][k - j]));
	return;
}

/*
Evaluates a Y value for any given X value and a polynomial equation as an array of coefficients
Accepts 3 parameters: intN, dblCoeff[][], dblX
Returns the evaluated Y value
*/
double dblEvaluate(int intN, double dblSeries[3][9], double dblX) {
	double dblOutput;

	dblOutput = dblSeries[2][intN - 1];
	for (int i = (intN - 2); i > -1; --i)
		dblOutput = (dblOutput * (dblX - dblSeries[0][i])) + dblSeries[2][i];
	return dblOutput;
}

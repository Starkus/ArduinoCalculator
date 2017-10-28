// 
// 
// 

#include "polyfit.h"

//Polynomial Fit

/*
	Original code by Manas Sharma from Bragitoff.com
	http://www.bragitoff.com/2015/09/c-program-for-polynomial-fit-least-squares/
	Credits to them.
*/

float polynomialFit(int n, float* buffer, int degree, double* a)
{
	int i, j, k;

	double X[2 * degree + 1];                        //Array that will store the values of sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
	for (i=0; i < 2 * degree + 1; ++i)
	{
		X[i] = 0;
		for (j=0; j < n; ++j)
			X[i] += pow(buffer[j*2], i);        //consecutive positions of the array will store N,sigma(xi),sigma(xi^2),sigma(xi^3)....sigma(xi^2n)
	}
	double B[degree+1][degree+2];            //B is the Normal matrix(augmented) that will store the equations, 'a' is for value of the final coefficients
	for (i=0; i <= degree; ++i)
		for (j=0; j <= degree; ++j)
			B[i][j]=X[i+j];            //Build the Normal matrix by storing the corresponding coefficients at the right positions except the last column of the matrix

	double Y[degree+1];                    //Array to store the values of sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
	for (i=0; i < degree+1; ++i)
	{
		Y[i]=0;
		for (j=0; j < n; ++j)
			Y[i]=Y[i]+pow(buffer[j*2], i) * buffer[j*2+1];        //consecutive positions will store sigma(yi),sigma(xi*yi),sigma(xi^2*yi)...sigma(xi^n*yi)
	}
	for (i=0;i<=degree;i++)
	B[i][degree+1]=Y[i];                //load the values of Y as the last column of B(Normal Matrix but augmented)
	degree++;                //n is made n+1 because the Gaussian Elimination part below was for n equations, but here n is the degree of polynomial and for n degree we get n+1 equations

	for (i=0;i<degree;i++)                    //From now Gaussian Elimination starts(can be ignored) to solve the set of linear equations (Pivotisation)
		for (k=i+1;k<degree;k++)
			if (B[i][i]<B[k][i])
				for (j=0;j<=degree;j++)
				{
					double temp=B[i][j];
					B[i][j]=B[k][j];
					B[k][j]=temp;
				}
	
	for (i=0;i<degree-1;i++)            //loop to perform the gauss elimination
		for (k=i+1;k<degree;k++)
		{
			double t=B[k][i]/B[i][i];
			for (j=0;j<=degree;j++)
			B[k][j]=B[k][j]-t*B[i][j];    //make the elements below the pivot elements equal to zero or elimnate the variables
		}

	for (i=degree-1; i >= 0; i--)                //back-substitution
	{                        //x is an array whose values correspond to the values of x,y,z..
		a[i] = B[i][degree];                //make the variable to be calculated equal to the rhs of the last equation
		for (j=0; j < degree; j++)
			if (j != i)            //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
				a[i] -= B[i][j] * a[j];
		a[i] /= B[i][i];            //now finally divide the rhs by the coefficient of the variable to be calculated
	}

	String func = String();
	for (int i=0; i < degree+1; ++i) {
		if (i > 0 && a[i] >= 0)
		func += '+';
		func += String(a[i], 3);
		func += (char) 129;
		func += '^';
		func += String(i);
	}

	float e = 0; // Sum of squared errors
	for (i=0; i < n; ++i) {
		float x = buffer[i*2];
		float y = buffer[i*2+1];
		float predicted = 0;
		for (j=0; j < degree; ++j) {
			predicted += a[j] * pow(x, j);
		}
		float dy = predicted - y;
		e += dy * dy;
	}

	return e;
}

int leastSquares(int n, float* buffer, double* results) {
	
	const int tries = 5;
	float errors[tries];

	double res1[6];

	float minError;
	int minErrorIndex=-1, degree;

	for (int i=0; i < tries; ++i) {
		errors[i] = polynomialFit(n, buffer, i+1, res1);

		if (errors[i] < minError || minErrorIndex == -1) {
			minError = errors[i];
			minErrorIndex = i;

			for (int j=0; j < i+2; ++j) {
				results[j] = res1[j];
			}
		}
	}
	degree = minErrorIndex + 1;

	return degree;
}
#include "Parameters.h"
#include "Laasonen.h"
#include <vector>
#include <iomanip>

using namespace std;
using namespace parameters;

Laasonen::Laasonen()
{
	this->className = "Laasonen";
}

Laasonen::Laasonen(double dT, double dX)
	: Implicit(dT, dX)
{
	this->className = "Laasonen";
}

Laasonen::~Laasonen()
{
}

void Laasonen::solve()
{
	double* X = new double[spaceGrid];
	double* a = new double[spaceGrid];
	double* b = new double[spaceGrid];
	double* c = new double[spaceGrid];
	double* d = new double[spaceGrid];

	fillArray(a, -r);
	fillArray(b, 1 + 2 * r);
	fillArray(c, -r);
	for (auto t = 0; t < timeGrid + 1; ++t)
	{
		d[0] = T[t][1] + r * T[t][0]; //first element
		d[spaceGrid - 1] = T[t][spaceGrid] + r * T[t][spaceGrid + 1]; //last element
		for (auto i = 1; i < spaceGrid - 1; i++)
		{
			d[i] = T[t][i + 1];
		}
		this->solveTridiagonalMatrix(a, b, c, d, X, spaceGrid);
		for (auto i = 0; i < spaceGrid; i++)
		{
			T[t + 1][i + 1] = X[i];
		}
	}

	delete[] a;
	delete[] b;
	delete[] c;
	delete[] d; 
	delete[] X;
}

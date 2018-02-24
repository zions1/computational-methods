#include "CrankNicholson.h"
#include "Parameters.h"
using namespace parameters;

CrankNicholson::CrankNicholson()
{
	this->className = "CrankNicholson";
}


CrankNicholson::~CrankNicholson()
{
}

void CrankNicholson::solve()
{
	double* X = new double[spaceGrid];
	double* a = new double[spaceGrid];
	double* b = new double[spaceGrid];
	double* c = new double[spaceGrid];
	double* d = new double[spaceGrid];
	double R = r / 2;
	fillArray(a, -R);
	fillArray(b, 1 + 2 * R);
	fillArray(c, -R);

	for (auto t = 0; t < timeGrid + 1; ++t)
	{
		d[0] = 2 * R * T[t][0] + (1 - 2 * R) * T[t][1] + R * T[t][2]; //first element
		d[spaceGrid - 1] = R * T[t][spaceGrid - 1] + (1 - 2 * R) * T[t][spaceGrid] + 2 * R * T[t][spaceGrid + 1]; //last element
		for (auto i = 1; i < spaceGrid - 1; i++)
		{
			d[i] = R * T[t][i + 2] + (1 - 2 * R) * T[t][i + 1] + R * T[t][i];
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

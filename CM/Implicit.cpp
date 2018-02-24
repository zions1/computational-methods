#include "Implicit.h"
#include "Parameters.h"
using namespace parameters;

Implicit::Implicit()
{
	this->className = "Implicit";
}

Implicit::Implicit(double dT, double dX)
	: Numerical(dT, dX)
{
	this->className = "Implicit";
}


Implicit::~Implicit()
{
}

void Implicit::fillArray(double* array, const double value)
{
	for (auto i = 0; i < spaceGrid; i++)
	{
		array[i] = value;
	}
}

void Implicit::solveTridiagonalMatrix(const double* a, const double* b, double* c, double* y, double* x, const int n)
{
	auto* c1 = new double[n];
	for (auto i = 0; i < n; i++)
	{
		c1[i] = c[i];
	}	
	c1[0] = c1[0] / b[0];
	y[0] = y[0] / b[0];
	auto temp = 0.0;
	for (auto i = 1; i != n; i++)
	{
		temp = 1.0 / (b[i] - c1[i - 1] * a[i]);
		c1[i] = c1[i] * temp;
		y[i] = (y[i] - a[i] * y[i - 1]) * temp;
	}

	x[n - 1] = y[n - 1];
	for (auto i = n - 2; i != -1; i--)
	{
		x[i] = y[i] - c1[i] * x[i + 1];
	}

	delete[] c1;
}

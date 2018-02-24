#include "Analytical.h"
#include "Parameters.h"
#include <corecrt_math_defines.h>
using namespace parameters;
using namespace std;

Analytical::Analytical() : ComputionalMethod()
{
	this->className = "Analytical";
}

Analytical::Analytical(const double dT, const double dX)
	: ComputionalMethod(dT, dX)
{
	this->className = "Analytical";
}


Analytical::~Analytical()
{
}

void Analytical::solveSolution(double const time)
{
	for (int t = 0; t < timeGrid + 2; t++)
	{
		if (doubleEquals(y[t], time))
		{
			for (int i = 0; i < spaceGrid + 2; i++)
			{
				double sum = 0.0;
				for (double m = 1; m < precision + 1; m++)
				{
					sum += exp(-D * pow(m * M_PI / L, 2) * y[t]) * ((1.0 - pow(-1.0, m)) / (m * M_PI)) * sin(m * M_PI * x[i] / L);
				}
				T[t][i] = Tsur + 2 * (Tin - Tsur) * sum;
			}
		}
	}
}

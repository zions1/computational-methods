#include "DuFortFrankel.h"
#include "Parameters.h"

using namespace std;
using namespace parameters;

void DuFortFrankel::solve()
{
	for (int i = 1; i < spaceGrid + 1; i++)
	{
		T[1][i] = T[0][i] + r * (T[0][i - 1] - 2 * T[0][i] + T[0][i + 1]);
	}

	for (int t = 1; t < timeGrid + 1; t++)
	{
		for (int i = 1; i < spaceGrid + 1; i++)
		{
			T[t + 1][i] = (T[t - 1][i] + 2 * r * (T[t][i + 1] - T[t - 1][i] + T[t][i - 1])) / (1 + 2 * r);
		}
	}
}


DuFortFrankel::DuFortFrankel()
{
	this->className = "DuFortFrankel";
}


DuFortFrankel::~DuFortFrankel()
{
}

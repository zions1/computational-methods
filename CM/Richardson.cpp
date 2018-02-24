#include "Richardson.h"
#include "Parameters.h"

using namespace std;
using namespace parameters;

void Richardson::solve()
{
	for (auto i = 1; i < spaceGrid + 1; i++)
	{
		//T[1][i] = r *(T[0][i + 1] + T[0][i - 1]) + (1 - 2 * r)*T[0][i];
		T[1][i] = T[0][i] + r * (T[0][i - 1] - 2 * T[0][i] + T[0][i + 1]);
	}

	for (auto t = 1; t < timeGrid + 1; t++)
	{
		for (auto i = 1; i < spaceGrid + 1; i++)
		{
			T[t + 1][i] = T[t - 1][i] + 2 * r * (T[t][i + 1] - 2 * T[t][i] + T[t][i - 1]);
		}
	}
}

Richardson::Richardson()
{
	this->className = "Richardson";
}


Richardson::~Richardson()
{
}

#include "ComputationalMethod.h"
#include "Parameters.h"
#include <fstream>
#include <iomanip>
using namespace std;
using namespace parameters;

void ComputionalMethod::setParameters(double dt, double dx)
{
	this->dt = dt;
	this->dx = dx;
	r = D * dt / (dx * dx);
	spaceGrid = L / dx - 1;
	timeGrid = parameters::time / dt;
	T = new double*[timeGrid + 2];
	for (auto i = 0; i < timeGrid + 2; ++i)
	{
		T[i] = new double[spaceGrid + 2];
	}
	this->x = new double[spaceGrid + 2];
	this->y = new double[timeGrid + 2];
	this->divideSpaceDomain();
	this->divideTimeDomain();
	this->className = "ComputionalMethod";
}

ComputionalMethod::ComputionalMethod()
{
	setParameters(0.01, 0.05);
}

ComputionalMethod::ComputionalMethod(double dT, double dX)
{
	setParameters(dT, dX);
}

ComputionalMethod::~ComputionalMethod()
{
	for (auto i = 0; i < timeGrid + 2; ++i)
	{
		delete[] T[i];
	}
	delete[] T;
	delete[] x;
	delete[] y;
}

bool ComputionalMethod::doubleEquals(double a, double b, double epsilon)
{
	return abs(a - b) < epsilon;
}

double** ComputionalMethod::getT() const
{
	return T;
}

double* ComputionalMethod::getX() const
{
	return x;
}

double* ComputionalMethod::getY() const
{
	return y;
}


string ComputionalMethod::getClassName() const
{
	return className;
}

int ComputionalMethod::getTimeGrid() const
{
	return timeGrid;
}

int ComputionalMethod::getSpaceGrid() const
{
	return spaceGrid;
}

double ComputionalMethod::getDt() const
{
	return dt;
}

void ComputionalMethod::divideTimeDomain() const
{
	for (auto t = 0; t < timeGrid + 2; t++)
	{
		y[t] = t * dt;
	}
}

void ComputionalMethod::divideSpaceDomain() const
{
	for (auto i = 0; i < spaceGrid + 2; i++)
	{
		x[i] = i * dx;
	}
}


void ComputionalMethod::printResultToFile(const string path, const double time)
{
	ofstream file;
	file.open(path);
	file << fixed << setprecision(8);
	file << "Time: " << time << endl;
	file << "Space\t\t" << getClassName() << endl;
	for (auto t = 0; t < timeGrid + 2; t++)
	{
		if (doubleEquals(y[t], time))
		{
			for (auto i = 0; i < spaceGrid + 2; i++)
			{
				file << x[i] << "\t" << T[t][i] << endl;
			}
		}
	}
	file.close();
}

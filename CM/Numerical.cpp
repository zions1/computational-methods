#include "Numerical.h"
#include "Parameters.h"
#include <fstream>
#include <iomanip>
using namespace parameters;


Numerical::Numerical() : ComputionalMethod()
{
	this->setInitialConditions();
	this->setBoundaryConditions();
	this->className = "Numerical";
	this->errors = new double[spaceGrid + 2];
}

Numerical::Numerical(double dT, double dX)
	: ComputionalMethod(dT, dX)
{
	this->setInitialConditions();
	this->setBoundaryConditions();
	this->className = "Numerical";
	this->errors = new double[spaceGrid + 2];
}


Numerical::~Numerical()
{
	delete[] errors;
}


void Numerical::setInitialConditions()
{
	for (int i = 1; i < spaceGrid + 1; i++)
	{
		T[0][i] = Tin;
	}
}

void Numerical::setBoundaryConditions()
{
	for (int t = 0; t < timeGrid + 2; t++)
	{
		T[t][0] = Tsur;
	}

	for (int t = 0; t < timeGrid + 2; t++)
	{
		T[t][spaceGrid + 1] = Tsur;
	}
}

void Numerical::calculateErrors(double** analyticalT, double time)
{
	for (int t = 0; t < timeGrid + 2; t++)
	{
		if (doubleEquals(y[t], time))
			for (int i = 0; i < spaceGrid + 2; i++)
			{
				errors[i] = analyticalT[t][i] - T[t][i];
			}
	}
	oneNorm = calculateOneNorm(errors, spaceGrid + 2);
	twoNorm = calculateTwoNorm(errors, spaceGrid + 2);
	uniformNorm = calculateUniformNorm(errors, spaceGrid + 2);
}

double Numerical::getOneNorm()
{
	return this->oneNorm;
}

double Numerical::getTwoNorm()
{
	return this->twoNorm;
}

double Numerical::getUniformNorm()
{
	return this->uniformNorm;
}

void Numerical::printBasicResultToFile(const string path, const string name, double** analyticalT, const double time)
{
	ofstream file;
	file.open(path);
	for (int t = 0; t < timeGrid + 2; t++)
	{
		if (doubleEquals(y[t], time))
		{
			file << "Space\t Analytical\t " << name << "\t Errors" << endl;
			for (int i = 0; i < spaceGrid + 2; i++)
			{
				file << fixed << setprecision(6) << x[i] << "\t" << analyticalT[t][i] << "\t" << T[t][i] << "\t" << errors[i] <<
					endl;
			}
			file << "1-Norm: \t" << this->oneNorm << endl;
			file << "2-Norm: \t" << this->twoNorm << endl;
			file << "Uniform-Norm: " << this->uniformNorm << endl;
		}
	}
	file.close();
}


double* Numerical::getErrors()
{
	return this->errors;
}


//-----------------------NORMS---------------------------
//1 norm
double Numerical::calculateOneNorm(double* array, const int size) const
{
	auto sum = 0.0;
	for (auto i = 0; i < size; i++)
		sum += fabs(array[i]);
	return sum;
}

//2 norm
double Numerical::calculateTwoNorm(double* array, const int size) const
{
	auto sum = 0.0;
	for (auto i = 0; i < size; i++)
		sum += array[i] * array[i];
	return sqrt(sum);
}

// uniform (infinity) norm
double Numerical::calculateUniformNorm(double* array, const int size) const
{
	auto max = fabs(array[0]);
	for (auto i = 1; i < size; i++)
		if (fabs(array[i]) > max)
			max = fabs(array[i]);
	return max;
}

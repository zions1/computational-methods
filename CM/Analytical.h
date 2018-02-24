#pragma once
#include "ComputationalMethod.h"

/**
 * An Analytical class for solving problem using analytical solution.
 */
class Analytical : public ComputionalMethod
{
public:
	/**
	* Default constructor.
	*/
	Analytical();

	/**
	* Constructor.
	* \param dT The delta t. {@link #dt}.
	* \param dX The delta x. {@link #dx}.
	*/
	Analytical(const double dT, const double dX);

	/**
	* Default destructor.
	*/
	~Analytical();

	/**
	* Solves solution using Analytical method for given time.
	* \param time The time for which will be calculated the analytical solution.
	*/
	void solveSolution(double const time);
};

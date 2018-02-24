#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

/**
 * The parameters name space contain the constant value used for solving the main problem.
 */
namespace parameters
{
	/**
	 * The diffusivity of the wall in ft^2/hrs.
	 */
	const double D = 0.1;
	/**
	* The length of the wall in ft.
	*/
	const double L = 1.0;
	/**
	* The inside temparature of the wall in Fahrenheit degree.
	*/
	const double Tin = 100.0;
	/**
	* The surface temparature of the wall in Fahrenheit degree.
	*/
	const double Tsur = 300.0;
	/**
	 * The upper boundary of the time in hrs.
	 */
	const double time = 0.5;
	/**
	 * The upper bound.
	 */
	const double upperBound = L;
	/**
	 * The precision of the calculation.
	 */
	const int precision = 100;
}

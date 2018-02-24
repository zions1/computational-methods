#pragma once
#include "Numerical.h"

/**
* An Implicit class for solving problem using implicit methods.
*/
class Implicit :
	public Numerical
{
public:
	/**
	* Default constructor.
	*/
	Implicit();
	/**
	 * Constructor.
	 * \param dT The delta t. {@link #dt}.
	 * \param dX The delta x. {@link #dx}.
	 */
	Implicit(double dT, double dX);

	/**
	* Default destructor.
	*/
	~Implicit();

	/**
	 * Fills the array with given values.
	 * \param array The array.
	 * \param value The value to fill.
	 */
	void fillArray(double* array, const double value);

	/**
	 * Solves tridiagonal matrix using Thomas algorithm.
	 * \param a Subdiagonal data (lower diagonal).
	 * \param b The main diagonal data.
	 * \param c Superdiagonal data (upper diagonal).
	 * \param y The input data.
	 * \param x The solution data.
	 * \param n Number of equations.
	 */
	void solveTridiagonalMatrix(const double* a, const double* b, double* c, double* y, double* x, const int n);
};

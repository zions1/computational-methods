#pragma once
#include "ComputationalMethod.h"

/**
 * A Numerical class for solving problem using numerical methods.
 * 
 */
using namespace std;

class Numerical : public ComputionalMethod
{
protected:
	///Contains differences between analytical and numerical solution.
	double* errors;
	///Contains L1 norm data.
	double oneNorm;
	///Contains L2 norm data.
	double twoNorm;
	///Contains L-max norm data.
	double uniformNorm;

public:

	/**
	* Default constructor.
	*/
	Numerical();

	/**
	 * Constructor.
	 * \param dT The delta t. {@link #dt}.
	 * \param dX The delta x. {@link #dx}.
	 */
	Numerical(const double dT, const double dX);

	/**
	* Default destructor.
	*/
	~Numerical();

	/**
	 * Sets initial conditions.
	 */
	void setInitialConditions();

	/**
	* Sets boundary conditions.
	*/
	void setBoundaryConditions();

	/**
	 * Calculate errors, the differences between analytical and numerical solution.
	 * \param analyticalT Temperature from analytical solution.
	 * \param  time The time for which will be calculated the errors.
	 */
	void calculateErrors(double** analyticalT, double time);

	/**
	* Returns array of errors,the differences between analytical and numerical solution..
	* @return {@link #errors}.
	*/
	double* getErrors();

	/**
	* Returns L1 norm data.
	* @return {@link #oneNorm}.
	*/
	double getOneNorm();

	/**
	* Returns L2 norm data.
	* @return {@link #twoNorm}.
	*/
	double getTwoNorm();

	/**
	* Returns Uniform norm data.
	* @return {@link #uniformNorm}.
	*/
	double getUniformNorm();

	/**
	* Prints result to the file.
	* \param path Path to the file.
	* \param name Name of the file.
	* \param analyticalT Temperature from analytical solution.
	* \param time The time for which will be printed results.
	*/
	void printBasicResultToFile(const string path, const string name, double** analyticalT, const double time);

	/**
	 * Solves problem in numerical way. Virtual method. 
	 */
	virtual void solve() = 0;

	//------ NORMS -------

	/**
	* Returns L1 norm.
	* @see {@link #calculateTwoNorm(double*,int)const}
	* @see {@link #calculateUniformNorm(double*,int)const}
	* \param array Arrays with data.
	* \param size Size of array.
	* @return double L1 norm.
	*/
	double calculateOneNorm(double* array, int size) const;

	/**
	* Returns L2 norm.
	* @see {@link #calculateoneNorm(double*,int)const}
	* @see {@link #calculateUniformNorm(double*,int)const}
	* \param array Arrays with data.
	* \param size Size of array.
	* @return double L2 norm.
	*/
	double calculateTwoNorm(double* array, int size) const;

	/**
	* Returns L-max norm.
	* @see {@link #calculateOneNorm(double*,int)const}
	* @see {@link #calculateTwoNorm(double*,int)const}
	* \param array Arrays with data.
	* \param size Size of array.
	* @return double Uniform norm.
	*/
	double calculateUniformNorm(double* array, int size) const;
};

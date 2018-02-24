#pragma once
#include <string>

/**
 * A ComputionalMethod class.
 * Includes space, time and temperatures arrays and provides basic methods used for analytical and numerical solution.
 */
class ComputionalMethod
{
protected:
	///Name of the class.
	std::string className;
	///The tempetarure.
	double** T;
	///The space.
	double* x;
	///The time.
	double* y;
	///Size of time step.
	double dt;
	///Size of space step
	double dx;
	///Expression: D*dt/(dx*dx)
	double r;
	///The space grid.
	int spaceGrid;
	///The time grid.
	int timeGrid;

public:
	/**
	 * Default constructor. 
	 */
	ComputionalMethod();

	/**
	* Constructor.
	* \param dT The delta t. {@link #dt}.
	* \param dX The delta x. {@link #dx}.
	*/
	ComputionalMethod(const double dT, const double dX);

	/**
	* Default destructor.
	*/
	virtual ~ComputionalMethod();

	/**
	 * Comapre the double value.
	 * \param a The first value to comapre.
	 * \param b The second value to compare
	 * \param epsilon The accurancy of comparison.
	 * @return True if the value are equals, false if not.
	 */
	bool doubleEquals(double a, double b, double epsilon = 0.001);

	/**
	* Prints result to the file.
	* \param path The path to the file.
	* \param time The time.
	*/
	void printResultToFile(std::string path, double time);

	/**
	 * Returns name of the class.
	 * @return {@link #className}.
	 */
	std::string getClassName() const;

	/**
	* Returns array of temperatures.
	* @return {@link #T}.
	*/
	double** getT() const;

	/**
	* Returns array of space.
	* @return {@link #x}.
	*/
	double* getX() const;

	/**
	* Returns array of time.
	* @param {@link #y}.
	*/
	double* getY() const;

	/**
	* Returns time grid.
	* @return {@link #timeGrid}.
	*/
	int getTimeGrid() const;

	/**
	* Returns space grid.
	* @return {@link #spaceGrid}.
	*/
	int getSpaceGrid() const;


	/**
	* Returns delta t.
	* @return {@link #dt}.
	*/
	double getDt() const;

private:

	/**
	* Divides time domain for time grid using delta t.
	*/
	void divideTimeDomain() const;

	/**
	* Divides time space for space grid using delta x.
	*/
	void divideSpaceDomain() const;

	/*
	 * Sets the parameters.
	 * @param {@link #dt}.
	 * @param {@link #dx}.
	 */
	void setParameters(double dt, double dx);
};

#pragma once
#include "Numerical.h"
#include "Implicit.h"
using namespace std;

/**
 * A Laasonen class for solving problem using Laasonen method.
 * Laasonen Simple Implicit - Forward time, central space.
 */
class Laasonen : public Implicit
{
public:
	/**
	* Default constructor.
	*/
	Laasonen();

	/**
	* Constructor.
	* \param dT The delta t. {@link #dt}.
	* \param dX The delta x. {@link #dx}.
	*/
	Laasonen(double dT, double dX);

	/**
	* Default destructor.
	*/
	~Laasonen();

	/**
	* Solves problem using Laasonen method.
	*/
	void solve() override;
};

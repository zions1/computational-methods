#pragma once
#include "Implicit.h"

/**
 * A CrankNicholson class for solving problem using Crank-Nicholson method.
 * Trapezoidal method.
 */
class CrankNicholson : public Implicit
{
public:
	/**
	* Default constructor.
	*/
	CrankNicholson();
	/**
	* Default destructor.
	*/
	~CrankNicholson();
	/**
	* Solves problem using Crank-Nicholson method.
	*/
	void solve() override;
};

#pragma once
#include "Explicit.h"

/**
 * A Richardson class for solving problem using Richardson method.
 */
class Richardson : public Explicit
{
public:
	/**
	* Default constructor.
	*/
	Richardson();

	/**
	* Default destructor.
	*/
	~Richardson();

	/**
	* Solves problem using Richardson method.
	*/
	void solve() override;
};

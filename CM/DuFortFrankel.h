#pragma once
#include "Explicit.h"

/**
 * A DuFortFrankel class for solving problem using DuFort-Frankel method.
 */
class DuFortFrankel : public Explicit
{
public:
	/**
	* Default constructor.
	*/
	DuFortFrankel();
	/**
	* Default destructor.
	*/
	~DuFortFrankel();
	/**
	* Solves problem using DuFord-Frankel method.
	*/
	void solve() override;
};

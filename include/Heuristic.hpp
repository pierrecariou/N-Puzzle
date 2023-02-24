#pragma once

#include "Puzzle.hpp"

class Heuristic
{
public:
	virtual unsigned int calculate(Puzzle puzzle) = 0;
};

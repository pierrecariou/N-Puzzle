#pragma once

#include "Puzzle.hpp"

class Heuristic
{
public:
	virtual int calculate(Puzzle puzzle) = 0;
};

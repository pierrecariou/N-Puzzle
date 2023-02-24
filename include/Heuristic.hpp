#pragma once

#include "Puzzle.hpp"

class Heuristic
{
public:
	virtual unsigned int calculate(const Puzzle &puzzle) const = 0;
};

#pragma once

#include "Puzzle.hpp"

#include <string>

class Heuristic
{
public:
	virtual std::string name() = 0;
	virtual unsigned int calculate(Puzzle puzzle) = 0;
};

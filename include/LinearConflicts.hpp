#pragma once

#include "ManhattanDistance.hpp"

class LinearConflicts : public ManhattanDistance
{
public:
	std::string name();
	unsigned int calculate(Puzzle puzzle);
};

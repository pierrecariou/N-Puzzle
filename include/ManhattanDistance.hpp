#pragma once

#include "Heuristic.hpp"

class ManhattanDistance : public Heuristic
{
public:
	unsigned int calculate(Puzzle puzzle);
};

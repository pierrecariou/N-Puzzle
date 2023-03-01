#pragma once

#include "Heuristic.hpp"

class HammingDistance : public Heuristic
{
public:
	std::string name();
	unsigned int calculate(Puzzle puzzle);
};

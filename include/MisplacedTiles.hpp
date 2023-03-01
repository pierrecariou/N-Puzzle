#pragma once

#include "Heuristic.hpp"

class MisplacedTiles : public Heuristic
{
public:
	std::string name();
	unsigned int calculate(Puzzle puzzle);
};

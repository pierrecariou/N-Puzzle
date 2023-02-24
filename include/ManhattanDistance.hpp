#pragma once

#include "Heuristic.hpp"

class ManhattanDistance : public Heuristic
{
private:
	unsigned short distance(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) const;

public:
	unsigned int calculate(const Puzzle &puzzle) const;
};

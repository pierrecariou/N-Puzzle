#pragma once

#include "Puzzle.hpp"

#include <string>

class Heuristic
{
public:
	virtual std::string getName() = 0;
	virtual unsigned int calculate(Puzzle puzzle) = 0;
};

class MisplacedTiles : public Heuristic
{
public:
	std::string getName();
	unsigned int calculate(Puzzle puzzle);
};

class ManhattanDistance : public Heuristic
{
public:
	std::string getName();
	unsigned int calculate(Puzzle puzzle);
};

class LinearConflict : public ManhattanDistance
{
public:
	std::string getName();
	unsigned int calculate(Puzzle puzzle);
};

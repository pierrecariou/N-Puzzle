#include "LinearConflicts.hpp"

std::string LinearConflicts::name() { return "Linear Conflicts"; }
unsigned int LinearConflicts::calculate(Puzzle puzzle)
{
	return ManhattanDistance::calculate(puzzle);
}

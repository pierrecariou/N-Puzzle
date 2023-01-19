#include "FringePatternDatabase.hpp"

#include <algorithm>

#include <iostream>

int FringePatternDatabase::calculateHeuristic(NPuzzle const &currentState, std::unique_ptr<NPuzzle> const &goalState) const
{
	// TODO: Implement this function
	return (0);
}

void FringePatternDatabase::printType() const
{
	std::cout << "Fringe Pattern Database" << '\n';
}

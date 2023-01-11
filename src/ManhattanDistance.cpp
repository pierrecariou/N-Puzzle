#include "ManhattanDistance.hpp"
#include <utility>
#include <vector>
#include <iostream>

int ManhattanDistance::calculateHeuristic(NPuzzle const &currentState, const std::unique_ptr<NPuzzle> &goalState) const {
	int heuristic = 0;

	for (int i = 1; i < currentState.getSize() * currentState.getSize(); i++) {
		std::pair<int, int> currentTilePosition = currentState.getTilePosition(i);
		std::pair<int, int> goalTilePosition = goalState->getTilePosition(i);
		heuristic += abs(currentTilePosition.first - goalTilePosition.first) + abs(currentTilePosition.second - goalTilePosition.second);
	}
	return heuristic;
}

void ManhattanDistance::printType() const {
	std::cout << "Manhattan Distance" << std::endl;
}

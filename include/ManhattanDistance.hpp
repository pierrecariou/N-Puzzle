#pragma once

#include "Heuristic.hpp"

class ManhattanDistance : public Heuristic {
 public:
	ManhattanDistance() = default;
	~ManhattanDistance() = default;

  	int calculateHeuristic(NPuzzle const &currentState, std::unique_ptr<NPuzzle> const &goalState) const override;
	void printType() const override;
};

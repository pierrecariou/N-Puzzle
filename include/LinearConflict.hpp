#pragma once

#include "Heuristic.hpp"

class LinearConflict : public Heuristic {
 public:
	LinearConflict() = default;
	~LinearConflict() = default;

	int calculateHeuristic(NPuzzle const &currentState, std::unique_ptr<NPuzzle> const &goalState) const override;
	void printType() const override;
};

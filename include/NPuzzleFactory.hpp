#pragma once

#include <memory>

#include "NPuzzle.hpp"
#include "Direction.hpp"

class NPuzzleFactory
{
	public:
		NPuzzleFactory();
		~NPuzzleFactory();
		std::unique_ptr<NPuzzle> createNPuzzle(NPuzzle const &currentPuzzle, int parentIndex, Direction const &Direction) const;
		std::unique_ptr<NPuzzle> createNPuzzleInitialState(std::string const &fileName) const;
		std::unique_ptr<NPuzzle> createNPuzzleGoalState(int puzzleSize) const;
		std::unique_ptr<NPuzzle> createNPuzzleRandomState() const;
};

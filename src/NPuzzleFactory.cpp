#include <memory>

#include "NPuzzleFactory.hpp"
#include "NPuzzle.hpp"

NPuzzleFactory::NPuzzleFactory()
{
}

NPuzzleFactory::~NPuzzleFactory()
{
}

std::unique_ptr<NPuzzle> NPuzzleFactory::createNPuzzle(NPuzzle const &currentPuzzle, Direction const &direction) const
{
	return std::make_unique<NPuzzle>(currentPuzzle, direction);
}

std::unique_ptr<NPuzzle> NPuzzleFactory::createNPuzzleInitialState(std::string const &fileName) const
{
	return std::make_unique<NPuzzle>(fileName);
}

std::unique_ptr<NPuzzle> NPuzzleFactory::createNPuzzleGoalState(int puzzleSize) const
{
	return std::make_unique<NPuzzle>(puzzleSize);
}

std::unique_ptr<NPuzzle> NPuzzleFactory::createNPuzzleRandomState() const
{
	return std::make_unique<NPuzzle>();
}

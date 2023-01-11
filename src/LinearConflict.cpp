#include "LinearConflict.hpp"
#include "ManhattanDistance.hpp"
#include <algorithm>

#include <iostream>

int LinearConflict::calculateHeuristic(NPuzzle const &currentState, std::unique_ptr<NPuzzle> const &goalState) const
{
	int linear = 0;
	int manhattan = ManhattanDistance().calculateHeuristic(currentState, goalState);

	for (int i = 0; i < currentState.getSize(); i++)
	{
		for (int j = 0; j < currentState.getSize(); j++)
		{
			int value = currentState.getPuzzle()[i][j];
			if (value == 0)
				continue;
			int goalX = (value - 1) / currentState.getSize();
			int goalY = (value - 1) % currentState.getSize();
			if (goalX == i)
			{
				for (int k = j + 1; k < currentState.getSize(); k++)
				{
					int value2 = currentState.getPuzzle()[i][k];
					if (value2 == 0)
						continue;
					int goalX2 = (value2 - 1) / currentState.getSize();
					int goalY2 = (value2 - 1) % currentState.getSize();
					if (goalX2 == i && goalY2 < goalY)
						linear++;
				}
			}
			if (goalY == j)
			{
				for (int k = i + 1; k < currentState.getSize(); k++)
				{
					int value2 = currentState.getPuzzle()[k][j];
					if (value2 == 0)
						continue;
					int goalX2 = (value2 - 1) / currentState.getSize();
					int goalY2 = (value2 - 1) % currentState.getSize();
					if (goalY2 == j && goalX2 < goalX)
						linear++;
				}
			}
		}
	}

	return (manhattan + 2 * linear);
}

void LinearConflict::printType() const
{
	std::cout << "Linear Conflict" << std::endl;
}

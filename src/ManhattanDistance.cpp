#include "ManhattanDistance.hpp"

std::string ManhattanDistance::name() { return "Manhattan Distance"; }
unsigned int ManhattanDistance::calculate(Puzzle puzzle)
{
	std::vector<unsigned char> tiles = puzzle.getTiles();

	unsigned int distance = 0;
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		unsigned char tile = tiles[i];
		if (tile == 0)
			continue;

		int x = i % puzzle.getSize();
		int y = i / puzzle.getSize();

		int goalX = (tile - 1) % puzzle.getSize();
		int goalY = (tile - 1) / puzzle.getSize();

		distance += abs(x - goalX) + abs(y - goalY);
	}

	return distance;
}

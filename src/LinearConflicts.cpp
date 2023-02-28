#include "LinearConflicts.hpp"

std::string LinearConflicts::name() { return "Linear Conflicts"; }
unsigned int LinearConflicts::calculate(Puzzle puzzle)
{
	std::vector<unsigned char> tiles = puzzle.getTiles();
	int conflicts = 0;

	for (int i = 0; i < puzzle.getSize(); i++)
	{
		unsigned char max_tile = 0;
		for (int j = 0; j < puzzle.getSize(); j++)
		{
			unsigned char tile = tiles[i * puzzle.getSize() + j];
			if (tile == 0)
				continue;

			if (tile > max_tile)
				max_tile = tile;
			else
				conflicts++;
		}
	}

	for (int j = 0; j < puzzle.getSize(); j++)
	{
		unsigned char max_tile = 0;
		for (int i = 0; i < puzzle.getSize(); i++)
		{
			unsigned char tile = tiles[i * puzzle.getSize() + j];
			if (tile == 0)
				continue;

			if (tile > max_tile)
				max_tile = tile;
			else
				conflicts++;
		}
	}
	return conflicts * 2 + ManhattanDistance::calculate(puzzle);
}

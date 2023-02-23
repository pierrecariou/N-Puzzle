#include <math.h>

#include "ManhattanDistance.hpp"

int ManhattanDistance::calculate(Puzzle puzzle)
{
	unsigned char size = puzzle.getSize();
	std::vector<std::vector<unsigned char>> tiles = puzzle.getTiles();

	unsigned int distance = 0;
	for (unsigned char y = 0; y < size; y++)
		for (unsigned char x = 0; x < size; x++)
		{
			unsigned char value = tiles[y][x];
			if (value == 0)
				continue;

			unsigned char targetX = (value - 1) % size;
			unsigned char targetY = (value - 1) / size;
			distance += std::abs(targetX - x) + std::abs(targetY - y);
		}

	return distance;
}

#include "ManhattanDistance.hpp"

#include <math.h>

unsigned short ManhattanDistance::distance(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) const
{
	return std::abs(x1 - x2) + std::abs(y1 - y2);
}

unsigned int ManhattanDistance::calculate(const Puzzle &puzzle) const
{
	const unsigned char &size = puzzle.getSize();
	std::vector<unsigned char> const &tiles = puzzle.getTiles();

	unsigned int result = 0;
	for (unsigned short i = 0; i < tiles.size(); i++)
		if (tiles[i] != 0)
		{
			unsigned char x1 = i % size;
			unsigned char y1 = i / size;

			unsigned char index = tiles[i] - 1;
			unsigned char x2 = index % size;
			unsigned char y2 = index / size;

			result += distance(x1, y1, x2, y2);
		}

	return result;
}

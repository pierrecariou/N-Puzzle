#include "HammingDistance.hpp"

std::string HammingDistance::name() { return "Hamming Distance"; }
unsigned int HammingDistance::calculate(Puzzle puzzle)
{
	std::vector<unsigned char> tiles = puzzle.getTiles();
	unsigned int distance = 0;

	for (unsigned short i = 0; i < tiles.size(); i++)
		if (tiles[i] != 0 && tiles[i] != i + 1)
			distance++;

	return distance;
}

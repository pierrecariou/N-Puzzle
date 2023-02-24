#include "ManhattanDistance.hpp"
#include "AStarSearch.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <cmath>

int error(std::string message, int code = 1)
{
	std::cerr << message << std::endl;
	exit(code);
}

std::vector<unsigned char> fromFile(std::string filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		error("Could not open file " + filename);

	std::string line;
	std::vector<unsigned char> puzzle;

	std::getline(file, line);
	std::istringstream iss(line);
	unsigned int size;
	iss >> size;

	for (unsigned char i = 0; i < size; i++)
	{
		std::getline(file, line);
		std::istringstream iss(line);
		for (unsigned char j = 0; j < size; j++)
		{
			unsigned int value;
			iss >> value;
			puzzle.push_back(value);
		}
	}

	return puzzle;
}

std::string toString(Puzzle puzzle)
{
	unsigned char size = puzzle.getSize();
	std::vector<unsigned char> tiles = puzzle.getTiles();

	std::string result;
	for (unsigned short i = 0; i < tiles.size(); i++)
	{
		result += std::to_string(tiles[i]);
		if (i % size != size - 1)
			result += ' ';
		else if (i != tiles.size() - 1)
			result += '\n';
	}
	return result;
}

int main(int argc, char *argv[])
{
	if (argc > 2)
		error("Usage: " + std::string(argv[0]) + " [filename]");

	Puzzle puzzle;
	if (argc == 2)
		puzzle = fromFile(argv[1]);

	std::cout << "Initial puzzle:" << std::endl;
	std::cout << toString(puzzle) << std::endl
			  << std::endl;

	ManhattanDistance heuristic;

	AStarSearch search(heuristic);
	search.init(puzzle);

	std::cout << "Solving..." << std::endl;
	auto start = std::chrono::steady_clock::now();
	std::vector<Puzzle> path = search.solve();
	auto end = std::chrono::steady_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl
			  << std::endl;

	std::cout << "Solution:" << std::endl;
	for (Puzzle puzzle : path)
		std::cout << toString(puzzle) << std::endl
				  << std::endl;
}

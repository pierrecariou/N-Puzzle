#include "AStarSearch.hpp"
#include "ManhattanDistance.hpp"

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>

void error(std::string message, int code)
{
	std::cerr << message << std::endl;
	std::exit(code);
}

Puzzle parsePuzzle(std::string input)
{
	std::ifstream file(input);
	if (!file.is_open())
		error("Could not open file " + input, 1);

	int number;
	file >> number;
	unsigned char size = number;

	std::vector<unsigned char> tiles;
	while (file >> number)
		tiles.push_back(number);

	if (tiles.size() != size * size)
		error("Invalid puzzle size", 1);

	return Puzzle(tiles);
}

int main(int argc, char **argv)
{
	if (argc > 2)
		error("Usage: " + std::string(argv[0]) + " [puzzle]", 1);

	std::unique_ptr<Puzzle> puzzle;
	if (argc == 2)
		puzzle = std::make_unique<Puzzle>(parsePuzzle(argv[1]));
	else
		puzzle = std::make_unique<Puzzle>(3);

	std::cout << "Initial puzzle:" << std::endl
			  << *puzzle << std::endl
			  << std::endl;

	std::cout << "Solving..." << std::endl;
	AStarSearch search(std::make_unique<ManhattanDistance>());

	auto start = std::chrono::steady_clock::now();
	std::unique_ptr<std::vector<Puzzle>> path = search.solve(*puzzle);
	auto end = std::chrono::steady_clock::now();

	if (path == nullptr)
		std::cout << "No solution found" << std::endl;
	else
		std::cout << "Solution found in " << path->size() - 1 << " moves" << std::endl;
	std::cout << std::endl;

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl
			  << search;
}

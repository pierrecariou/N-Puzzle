#include "ManhattanDistance.hpp"
#include "AStarSearch.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <cmath>

int error(const std::string &message, int code = 1)
{
	std::cerr << message << std::endl;
	exit(code);
}

std::vector<unsigned char> fromFile(const std::string &filename)
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

std::string toString(const Puzzle &puzzle)
{
	const unsigned char size = puzzle.getSize();
	std::vector<unsigned char> const &tiles = puzzle.getTiles();

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

	std::unique_ptr<Puzzle> puzzle;
	if (argc == 2)
		puzzle = std::make_unique<Puzzle>(fromFile(argv[1]));
	else
		puzzle = std::make_unique<Puzzle>(3);

	std::cout << "Initial puzzle:" << std::endl;
	std::cout << toString(*puzzle) << std::endl
			  << std::endl;

	AStarSearch search(std::make_unique<ManhattanDistance>());
	search.init(*puzzle);

	std::cout << "Solving..." << std::endl;
	auto start = std::chrono::steady_clock::now();
	search.solve();
	auto end = std::chrono::steady_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl
			  << std::endl;

	if (!search.isSolved())
		error("No solution found");

	const std::vector<Puzzle> &path = search.result();
	std::cout << "Path length: " << path.size() << std::endl
			  << std::endl;

	std::string answer;
	do
	{
		std::cout << "Do you want to see the solution? (y/n) ";
		std::cin >> answer;
	} while (answer != "y" && answer != "n");

	if (answer == "n")
		return 0;

	std::cout << "Solution:" << std::endl;
	for (const Puzzle &puzzle : path)
		std::cout << toString(puzzle) << std::endl
				  << std::endl;
}

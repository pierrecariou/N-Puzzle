#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>

#include "AStarSearch.hpp"
#include "ManhattanDistance.hpp"

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

int main(int argc, char *argv[])
{
	Puzzle *puzzle;

	if (argc > 2)
		error("Usage: " + std::string(argv[0]) + " [filename]");
	else if (argc == 2)
		puzzle = new Puzzle(fromFile(argv[1]));
	else
		puzzle = new Puzzle();

	std::cout << "Initial puzzle:" << std::endl;
	std::cout << puzzle->toString() << std::endl
			  << std::endl;

	Puzzle goal({1, 2, 3, 4, 5, 6, 7, 8, 0});

	std::cout << "Goal puzzle:" << std::endl;
	std::cout << goal.toString() << std::endl
			  << std::endl;

	AStarSearch search(new ManhattanDistance());
	search.setPuzzle(*puzzle);

	std::cout << "Solving..." << std::endl;
	auto start = std::chrono::steady_clock::now();
	std::vector<Puzzle> path = search.solve(goal);
	auto end = std::chrono::steady_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl
			  << std::endl;

	std::cout << "Solution:" << std::endl;
	for (Puzzle puzzle : path)
		std::cout << puzzle.toString() << std::endl
				  << std::endl;
}
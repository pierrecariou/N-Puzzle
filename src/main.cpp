#include "AStarSearch.hpp"
#include "ManhattanDistance.hpp"
#include "LinearConflicts.hpp"
#include "HammingDistance.hpp"

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

Puzzle getPuzzle(int argc, char **argv)
{
	if (argc > 2)
		error("Usage: " + std::string(argv[0]) + " [puzzle]", 1);

	std::unique_ptr<Puzzle> puzzle;
	if (argc == 2)
		puzzle = std::make_unique<Puzzle>(argv[1]);
	else
		puzzle = std::make_unique<Puzzle>(3);

	std::cout << "Initial puzzle:" << std::endl
			  << *puzzle << std::endl
			  << std::endl;

	if (!puzzle->isSolvable())
		error("Puzzle is not solvable", 2);

	return *puzzle;
}

std::unique_ptr<Heuristic> getHeuristic()
{
	std::unique_ptr<Heuristic> heuristics[] = {
		std::make_unique<ManhattanDistance>(),
		std::make_unique<LinearConflicts>(),
		std::make_unique<HammingDistance>()};

	std::cout << "Available heuristics:" << std::endl;
	unsigned char i = 0;
	for (std::unique_ptr<Heuristic> &heuristic : heuristics)
		std::cout << (int)++i << ". " << heuristic->name() << std::endl;
	std::cout << std::endl;

	std::cout << "Select heuristic: ";
	unsigned int number;
	while (!(std::cin >> number) || number < 1 || number > (sizeof(heuristics) / sizeof(heuristics[0])))
	{
		std::cin.clear();
		std::cout << "Invalid choice. Select heuristic: ";
	}

	std::cout << "Selected heuristic: " << heuristics[number - 1]->name() << std::endl
			  << std::endl;

	return std::move(heuristics[number - 1]);
}

void solve(Puzzle puzzle, std::unique_ptr<Heuristic> heuristic)
{
	std::cout << "Solving..." << std::endl;
	AStarSearch search(std::move(heuristic));

	auto start = std::chrono::steady_clock::now();
	std::unique_ptr<std::vector<Puzzle>> path = search.solve(puzzle);
	auto end = std::chrono::steady_clock::now();

	if (path == nullptr)
	{
		std::cout << "No solution found" << std::endl;
		return;
	}
	else
	{
		std::cout << "Solution found in " << path->size() - 1 << " moves" << std::endl;

		std::ofstream file("solution.txt");
		if (!file.is_open())
			error("Could not open file solution.txt", 3);

		for (Puzzle &puzzle : *path)
			file << puzzle << std::endl
				 << std::endl;
		file.close();
	}
	std::cout << std::endl;

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl
			  << search;
}

int main(int argc, char **argv)
{
	Puzzle puzzle = getPuzzle(argc, argv);
	std::unique_ptr<Heuristic> heuristic = getHeuristic();
	solve(puzzle, std::move(heuristic));
}

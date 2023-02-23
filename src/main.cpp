#include <iostream>
#include <chrono>

#include "AStarSearch.hpp"
#include "ManhattanDistance.hpp"

int main()
{
	Puzzle puzzle(3);

	std::cout << "Initial puzzle:" << std::endl;
	std::cout << puzzle.toString() << std::endl
			  << std::endl;

	Puzzle goal({1, 2, 3, 4, 5, 6, 7, 8, 0});

	std::cout << "Goal puzzle:" << std::endl;
	std::cout << goal.toString() << std::endl
			  << std::endl;

	AStarSearch search(new ManhattanDistance());
	search.setPuzzle(puzzle);

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
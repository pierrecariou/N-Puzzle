#include "AStarSearch.hpp"
#include "ManhattanDistance.hpp"

#include <string>
#include <iostream>
#include <cstdlib>

void error(std::string message, int code)
{
	std::cerr << message << std::endl;
	std::exit(code);
}

int main()
{
	Puzzle puzzle(3);
	std::cout << "Initial puzzle:" << std::endl
			  << puzzle << std::endl
			  << std::endl;

	std::cout << "Solving..." << std::endl;

	AStarSearch search(std::make_unique<ManhattanDistance>());
	std::vector<Puzzle> path = search.solve(puzzle);

	if (path.empty())
		error("No solution found", 1);

	for (auto &puzzle : path)
		std::cout << puzzle << std::endl
				  << std::endl;
}

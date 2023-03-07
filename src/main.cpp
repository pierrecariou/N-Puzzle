#include "Search.hpp"

#include <iostream>
#include <chrono>

void error(std::string message, int code = 1)
{
	std::cerr << message << std::endl;
	exit(code);
}

unsigned char input(std::string message, unsigned char length)
{
	std::string input;
	unsigned char choice;

	do
	{
		std::cout << message;
		std::getline(std::cin, input);

		try
		{
			choice = std::stoi(input);
		}
		catch (std::exception &e)
		{
			std::cout << "That's not a number" << std::endl;
		}

		if (choice < 1 || choice > length)
			std::cout << "That's not a valid choice" << std::endl;
		else
			break;
	} while (true);
	std::cout << std::endl;

	return choice;
}

Puzzle getPuzzle(int argc, char **argv)
{
	if (argc > 2)
		error("Usage: " + std::string(argv[0]) + " [filename]", 1);

	std::unique_ptr<Puzzle> puzzle;
	try
	{
		if (argc == 2)
			puzzle = std::make_unique<Puzzle>(std::string(argv[1]));
		else
			puzzle = std::make_unique<Puzzle>();
	}
	catch (std::exception &e)
	{
		error(e.what(), 2);
	}

	std::cout << "Initial puzzle:" << std::endl
			  << *puzzle << std::endl
			  << std::endl;
	return *puzzle;
}

std::unique_ptr<Heuristic> getHeuristic()
{
	std::array<std::unique_ptr<Heuristic>, 3> heuristics = {
		std::make_unique<MisplacedTiles>(),
		std::make_unique<ManhattanDistance>(),
		std::make_unique<LinearConflict>()};

	std::cout << "Available heuristics:" << std::endl;
	for (unsigned char i = 0; i < heuristics.size(); i++)
		std::cout << i + 1 << ". " << heuristics[i]->getName() << std::endl;
	std::cout << std::endl;

	unsigned char choice = input("Choose a heuristic: ", heuristics.size());
	return std::move(heuristics[choice - 1]);
}

unsigned char getAlgorithm()
{
	std::cout << "Available algorithms:" << std::endl;

	unsigned char i = 0;
	for (std::string algorithm : {"A*", "Greedy", "Uniform cost"})
		std::cout << (int)++i << ". " << algorithm << std::endl;
	std::cout << std::endl;

	return input("Choose an algorithm: ", i);
}

void solve(std::shared_ptr<SearchBase> search, Puzzle puzzle)
{
	auto start = std::chrono::steady_clock::now();
	std::unique_ptr<std::vector<Puzzle>> path = search->solve(puzzle);
	auto end = std::chrono::steady_clock::now();

	if (path == nullptr)
	{
		std::cout << "No solution found" << std::endl;
		return;
	}

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
	std::cout << "Solution found in " << path->size() - 1 << " moves" << std::endl;
	search->printStats();
}

int main(int argc, char **argv)
{
	Puzzle puzzle = getPuzzle(argc, argv);
	std::unique_ptr<Heuristic> heuristic = getHeuristic();

	switch (getAlgorithm())
	{
	case 1:
		solve(std::make_shared<Search<AStarComparator>>(std::move(heuristic)), puzzle);
		break;
	case 2:
		solve(std::make_shared<Search<GreedyComparator>>(std::move(heuristic)), puzzle);
		break;
	case 3:
		solve(std::make_shared<Search<UniformCostComparator>>(std::move(heuristic)), puzzle);
		break;
	}
}

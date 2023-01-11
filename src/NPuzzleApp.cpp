#include "LinearConflict.hpp"
#include "NPuzzle.hpp"
#include "NPuzzleFactory.hpp"
#include "AStarAlgorithm.hpp"
#include "Heuristic.hpp"
#include "ManhattanDistance.hpp"

#include <iostream>
#include <fstream>
#include <chrono>

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./npuzzle [file]" << std::endl;
		return (1);
	}
	
	NPuzzleFactory factory;

	std::unique_ptr<NPuzzle> currentState = factory.createNPuzzleInitialState(argv[1]);
	std::cout << "Starting State: " << std::endl;
	currentState->printPuzzle();
	
	if (!currentState->isSolvable())
	{
		std::cout << "This puzzle is not solvable" << std::endl;
		return (1);
	}

	std::cout << "  |  " << std::endl;
	std::cout << "  V  " << std::endl;

	
	std::unique_ptr<NPuzzle> goalState = factory.createNPuzzleGoalState(currentState->getSize());

	std::cout << "Goal State:" << std::endl;
	goalState->printPuzzle();

	//ManhattanDistance manhattanDistance = ManhattanDistance();

	//std::cout << manhattanDistance.calculateHeuristic(currentState, goalState) << std::endl;
	
	AStarAlgorithm algorithm = AStarAlgorithm(std::move(currentState), std::move(goalState), std::move(std::make_unique<LinearConflict>()), factory);

	// print time taken to solve the algorithm
	auto start = std::chrono::high_resolution_clock::now();

	algorithm.solve();

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s	" << std::endl;

	algorithm.printSolution();

	return (0);
}

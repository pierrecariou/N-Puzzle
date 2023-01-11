#include "LinearConflict.hpp"
#include "NPuzzle.hpp"
#include "NPuzzleFactory.hpp"
#include "AStarAlgorithm.hpp"
#include "Heuristic.hpp"
#include "ManhattanDistance.hpp"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <chrono>

int	main(int argc, char **argv)
{
	NPuzzleFactory factory;
	std::unique_ptr<NPuzzle> initialState = nullptr;

	if (argc != 2)
	{
		while (!initialState || !initialState->isSolvable())
			initialState = factory.createNPuzzleRandomState();
	} else {
		initialState = factory.createNPuzzleInitialState(argv[1]);
	}
	

	std::cout << "Starting State " << std::endl;
	std::cout << "---------------" << std::endl;
	initialState->printPuzzle();
	std::cout << std::endl;
	
	if (!initialState->isSolvable())
	{
		std::cout << "This puzzle is not solvable" << std::endl;
		return (1);
	}

	std::unique_ptr<NPuzzle> goalState = factory.createNPuzzleGoalState(initialState->getSize());

	std::cout << "Goal State" << std::endl;
	std::cout << "----------" << std::endl;
	goalState->printPuzzle();
	std::cout << std::endl;

	// Ask the user for the heuristic to use
	std::cout << "Choose which heuristic to use:" << std::endl;
	std::cout << "1. Manhattan Distance" << std::endl;
	std::cout << "2. Linear Conflict" << std::endl;
	//std::cout << "3. Manhattan Distance + Linear Conflict" << std::endl;

	int heuristicChoice = 0;
	std::cin >> heuristicChoice;

	std::unique_ptr<Heuristic> heuristic = nullptr;

	switch (heuristicChoice)
	{
		case 1:
			heuristic = std::make_unique<ManhattanDistance>();
			break;
		case 2:
			heuristic = std::make_unique<LinearConflict>();
			break;
	//	case 3:
	//		heuristic = std::make_unique<ManhattanDistance>();
	//		heuristic->addHeuristic(std::make_unique<LinearConflict>());
	//		break;
		default:
			std::cout << "Invalid choice" << std::endl;
			return (1);
	}

	std::cout << std::endl;
	AStarAlgorithm algorithm = AStarAlgorithm(std::move(initialState), std::move(goalState), std::move(heuristic) , factory);

	// print time taken to solve the algorithm
	auto start = std::chrono::high_resolution_clock::now();

	algorithm.solve();

	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;
	//std::cout << std::endl << std::endl << "Elapsed time: " << elapsed.count() << " s	" << std::endl;

	algorithm.printSolution(double(elapsed.count()));

	return (0);
}

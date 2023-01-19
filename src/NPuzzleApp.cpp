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
	

	std::cout << "Starting State " << '\n';
	std::cout << "---------------" << '\n';
	initialState->printPuzzle();
	std::cout << '\n';
	
	if (!initialState->isSolvable())
	{
		std::cout << "This puzzle is not solvable" << '\n';
		return (1);
	}

	std::unique_ptr<NPuzzle> goalState = factory.createNPuzzleGoalState(initialState->getSize());

	std::cout << "Goal State" << '\n';
	std::cout << "----------" << '\n';
	goalState->printPuzzle();
	std::cout << '\n';

	// Ask the user for the heuristic to use
	std::cout << "Choose which heuristic to use:" << '\n';
	std::cout << "1. Manhattan Distance" << '\n';
	std::cout << "2. Linear Conflict" << '\n';
	//std::cout << "3. Manhattan Distance + Linear Conflict" << '\n';

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
			std::cout << "Invalid choice" << '\n';
			return (1);
	}

	std::cout << '\n';
	AStarAlgorithm algorithm = AStarAlgorithm(std::move(initialState), std::move(goalState), std::move(heuristic) , factory);

	// print time taken to solve the algorithm
	auto start = std::chrono::high_resolution_clock::now();

	algorithm.solve();

	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;
	//std::cout << '\n' << '\n' << "Elapsed time: " << elapsed.count() << " s	" << '\n';

	algorithm.printSolution(double(elapsed.count()));

	return (0);
}

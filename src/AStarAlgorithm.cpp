#include <iostream>
#include <iterator>
#include <memory>
#include <algorithm>
#include <set>

#include "AStarAlgorithm.hpp"
#include "Direction.hpp"
#include "NPuzzle.hpp"
#include "NPuzzleFactory.hpp"

AStarAlgorithm::AStarAlgorithm(std::unique_ptr<NPuzzle> currentState, std::unique_ptr<NPuzzle> goalState, std::unique_ptr<Heuristic> heuristic, NPuzzleFactory const &factory) : _goalState(std::move(goalState)), _heuristic(std::move(heuristic)), _opened(), _closed(), _success(false), _factory(factory), _startState(std::move(currentState))
{
	NPuzzle startState = *_startState;
	startState.setHeuristicValue(_heuristic->calculateHeuristic(startState, _goalState));
	startState.setG(0);
	startState.setF(startState.getHeuristicValue() + startState.getG());
	this->_opened.insert(startState);
	std::cout << "A* Algorithm initialized with the following heuristic:" << '\n';
	_heuristic->printType();
	std::cout << '\n';
}

AStarAlgorithm::~AStarAlgorithm()
{
}

void AStarAlgorithm::solve()
{
	std::cout << "Solving..." << '\n';
	while (!this->_opened.empty() && !this->_success)
	{
		this->_closed.push_back(*this->_opened.begin());
		this->_opened.erase(this->_opened.begin());

		if (*this->_closed.rbegin() == *this->_goalState)
		{
			this->_success = true;
			break;
		}

		std::multiset<NPuzzle> expanded = this->expand(*this->_closed.rbegin());
		this->_opened.merge(expanded);
	}
	reconstructPath();
}

std::multiset<NPuzzle> AStarAlgorithm::expand(NPuzzle const &puzzle)
{
	std::multiset<NPuzzle> expanded;

	for (int direction = UP; direction < END; direction++)
	{
		if (puzzle.canMove(static_cast<Direction>(direction))) {
			std::unique_ptr<NPuzzle> newPuzzle = this->_factory.createNPuzzle(puzzle, this->_closed.size() - 1, static_cast<Direction>(direction));

			if (std::find(this->_closed.begin(), this->_closed.end(), *newPuzzle) != this->_closed.end()) {
				continue;
			}
			newPuzzle->setHeuristicValue(this->_heuristic->calculateHeuristic(*newPuzzle, this->_goalState));
			newPuzzle->setG(puzzle.getG() + NPuzzle::cost);
			newPuzzle->setF(newPuzzle->getG() + newPuzzle->getHeuristicValue());
			for (auto it = this->_opened.begin(); it != this->_opened.end(); it++) {
				if (*it == *newPuzzle) {
					if (it->getG() > newPuzzle->getG()) {
						this->_opened.erase(*it);
						break;
					}
				}
			}
			expanded.insert(*newPuzzle);
		}
	}
	return expanded;
}

void AStarAlgorithm::printSolution(double elapsedTime) const
{
	if (this->_success)
	{
		std::endl(std::cout);
		std::cout << "Solution found in " << elapsedTime << " seconds" << '\n';
		std::cout << "Time complexity: " << this->_opened.size() << '\n';
		std::cout << "Space complexity: " << this->_closed.size() << '\n';
		std::cout << "Number of moves: " << this->_solution.size() << '\n' << '\n';
		// ask user if he wants to print the solution
		std::cout << "Do you want to print the solution? (y/n)" << '\n';
		char answer;
		std::cin >> answer;
		if (answer == 'y')
		{
			for (auto it = this->_solution.end() - 1; it != this->_solution.begin() - 1; --it)
			{
				(*it)->printPuzzle();
				std::cout << '\n';
			}
		}
	} else {
		std::cout << "No solution found!" << '\n';
	}
}

void AStarAlgorithm::reconstructPath()
{
	std::cout << "Reconstructing path..." << '\n';
	NPuzzle *parent = &this->_closed.back();

	while (parent->getParentIndex() != -1)
	{
		this->_solution.push_back(parent);
		parent = &this->_closed[parent->getParentIndex()];
	}
}

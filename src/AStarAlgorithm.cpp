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
	std::cout << "A* Algorithm initialized" << std::endl << std::endl;
}

AStarAlgorithm::~AStarAlgorithm()
{
}

void AStarAlgorithm::solve()
{
	std::cout << "Solving..." << std::endl;
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
			std::unique_ptr<NPuzzle> newPuzzle = this->_factory.createNPuzzle(puzzle, static_cast<Direction>(direction));
			if (std::find(this->_closed.begin(), this->_closed.end(), *newPuzzle) != this->_closed.end()) {
				continue;
			}
			newPuzzle->setHeuristicValue(this->_heuristic->calculateHeuristic(*newPuzzle, this->_goalState));
			newPuzzle->setG(puzzle.getG() + 1);
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

void AStarAlgorithm::printSolution() const
{
	if (this->_success)
	{
		std::cout << "Solution found!" << std::endl;
		std::cout << "Time complexity: " << this->_opened.size() << std::endl;
		std::cout << "Space complexity: " << this->_closed.size() << std::endl;
		std::cout << "Number of moves: " << this->_solution.size() << std::endl;
		std::cout << "Solution: " << std::endl;
		// ask user if he wants to print the solution
		std::cout << "Do you want to print the solution? (y/n)" << std::endl;
		char answer;
		std::cin >> answer;
		if (answer == 'y')
		{
			for (auto it = this->_solution.end() - 1; it != this->_solution.begin() - 1; --it)
			{
				(*it).printPuzzle();
				std::cout << std::endl;
			}
		}
	} else {
		std::cout << "No solution found!" << std::endl;
	}
}

void AStarAlgorithm::reconstructPath()
{
	std::cout << "Reconstructing path..." << std::endl;
	NPuzzle *parent = &(*this->_closed.rbegin());
	while (parent != nullptr)
	{
		this->_solution.push_back(*parent);
		parent = parent->getParent();
	}
}

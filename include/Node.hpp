#pragma once

#include "Puzzle.hpp"
#include "Heuristic.hpp"

#include <memory>

class Node
{
private:
	Puzzle puzzle;
	std::shared_ptr<Node> parent;

	unsigned int cost;
	unsigned int heuristic;

public:
	Node(const Heuristic &heuristic, Puzzle puzzle, std::shared_ptr<Node> parent);

	Puzzle getPuzzle() const;
	Node *getParent() const;

	unsigned int getCost() const;
	unsigned int getHeuristic() const;
	unsigned int getF() const;
};

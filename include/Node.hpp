#pragma once

#include "Puzzle.hpp"
#include "Heuristic.hpp"

class Node
{
private:
	Puzzle puzzle;
	Node *parent;

	unsigned int cost;
	unsigned int heuristic;

public:
	Node(const Heuristic &heuristic, Puzzle puzzle, Node *parent = nullptr);

	Puzzle getPuzzle() const;
	Node *getParent() const;

	unsigned int getCost() const;
	unsigned int getHeuristic() const;
	unsigned int getF() const;
};

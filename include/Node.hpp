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
	Node(Puzzle puzzle, Node *parent, Heuristic *heuristic);

	const Puzzle getPuzzle() const;
	const Node *getParent() const;

	unsigned int getG() const;
	unsigned int getH() const;
	unsigned int getF() const;
};

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
	Node(Puzzle puzzle, Heuristic *heuristic, Node *parent = nullptr);

	Puzzle getPuzzle();
	Node *getParent();

	unsigned int getG();
	unsigned int getH();
	unsigned int getF() const;

	bool operator<(const Node &other) const;
};

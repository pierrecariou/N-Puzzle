#pragma once

#include "Puzzle.hpp"
#include "Heuristic.hpp"

class Node
{
private:
	std::unique_ptr<Puzzle> puzzle;
	std::shared_ptr<Node> parent;

	unsigned int cost;
	unsigned int heuristic;

public:
	Node(const Heuristic &heuristic, std::unique_ptr<Puzzle> puzzle, std::shared_ptr<Node> parent = nullptr);

	const Puzzle &getPuzzle() const;
	const Node *getParent() const;

	unsigned int getCost() const;
	unsigned int getHeuristic() const;
	unsigned int getF() const;
};

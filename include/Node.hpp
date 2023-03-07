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

	Puzzle &getPuzzle();
	Node *getParent();

	unsigned int getCost() const;
	unsigned int getHeuristic() const;
	unsigned int getScore() const;
};

struct NodeComparator
{
	virtual bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const = 0;
};

struct AStarComparator : public NodeComparator
{
	bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const;
};

struct GreedyComparator : public NodeComparator
{
	bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const;
};

struct UniformCostComparator : public NodeComparator
{
	bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const;
};

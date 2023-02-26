#pragma once

#include "Node.hpp"

#include <set>

class AStarSearch
{
private:
	std::unique_ptr<Heuristic> heuristic;

	struct NodeComparator
	{
		bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const;
	};

	std::multiset<std::shared_ptr<Node>, NodeComparator> open;
	std::vector<std::shared_ptr<Node>> closed;

	void expandNode(std::shared_ptr<Node> node);
	std::vector<Puzzle> reconstructPath(Node *node);

public:
	AStarSearch(std::unique_ptr<Heuristic> heuristic);

	std::unique_ptr<std::vector<Puzzle>> solve(Puzzle puzzle);
	friend std::ostream &operator<<(std::ostream &os, const AStarSearch &search);
};

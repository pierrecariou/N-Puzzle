#pragma once

#include "Node.hpp"

#include <set>

class AStarSearch
{
private:
	std::unique_ptr<Heuristic> heuristic;

	std::vector<Puzzle> reconstructPath(Node *node);
	void expandNode(Node *node);

	std::multiset<std::shared_ptr<Node>> open;
	std::vector<std::shared_ptr<Node>> closed;

public:
	AStarSearch(std::unique_ptr<Heuristic> heuristic);

	std::unique_ptr<std::vector<Puzzle>> solve(Puzzle puzzle);
};

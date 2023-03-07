#pragma once

#include "Heuristic.hpp"
#include "Node.hpp"

#include <set>
#include <unordered_set>

class SearchBase
{
public:
	virtual std::unique_ptr<std::vector<Puzzle>> solve(Puzzle puzzle) = 0;
	virtual void printStats() = 0;
};

template <typename NodeComparator = AStarComparator>
class Search : public SearchBase
{
private:
	std::unique_ptr<Heuristic> heuristic;

	std::multiset<std::shared_ptr<Node>, NodeComparator> frontier;
	std::unordered_multiset<std::shared_ptr<Node>> closed;

	void expandNode(std::shared_ptr<Node> node);
	std::vector<Puzzle> reconstructPath(Node *node);

public:
	Search(std::unique_ptr<Heuristic> heuristic);
	std::unique_ptr<std::vector<Puzzle>> solve(Puzzle puzzle);
	void printStats();
};

template class Search<AStarComparator>;
template class Search<GreedyComparator>;
template class Search<UniformCostComparator>;

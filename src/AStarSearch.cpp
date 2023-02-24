#include "AStarSearch.hpp"

#include <algorithm>
#include <iostream>

bool AStarSearch::NodeCompare::operator()(std::shared_ptr<Node> const &a, std::shared_ptr<Node> const &b) const { return a.get()->getF() < b.get()->getF(); }

void AStarSearch::expand(const std::shared_ptr<Node> &node)
{
	for (std::unique_ptr<Puzzle> &puzzle : node.get()->getPuzzle().getMoves())
	{
		const std::shared_ptr<Node> &child = std::make_shared<Node>(*heuristic.get(), std::move(puzzle), node);

		if (std::find_if(closed.begin(), closed.end(), [&child](std::shared_ptr<Node> const &node)
						 { return node.get()->getPuzzle() == child.get()->getPuzzle(); }) != closed.end())
			continue;

		const auto &frontierNode = std::find_if(frontier.begin(), frontier.end(), [&child](std::shared_ptr<Node> const &node)
												{ return node.get()->getPuzzle() == child.get()->getPuzzle(); });

		if (frontierNode != frontier.end())
		{
			if (frontierNode->get()->getCost() > child.get()->getCost())
				frontier.erase(frontierNode);
			else
				continue;
		}

		frontier.insert(child);
	}
}

AStarSearch::AStarSearch(std::unique_ptr<Heuristic> heuristic) : heuristic(std::move(heuristic)) {}
bool AStarSearch::isSolved() { return solved; }

void AStarSearch::init(const Puzzle &puzzle)
{
	this->puzzle = puzzle;

	frontier.clear();
	closed.clear();
	solved = false;

	frontier.insert(std::make_unique<Node>(*heuristic.get(), std::make_unique<Puzzle>(puzzle)));
}

void AStarSearch::solve()
{
	while (!frontier.empty() && !solved)
	{
		closed.push_back(*frontier.begin());
		frontier.erase(frontier.begin());

		if (closed.back().get()->getHeuristic() == 0)
			solved = true;
		else
			expand(closed.back());
	}
}

const std::vector<Puzzle> AStarSearch::result()
{
	std::cout << "Frontier: " << frontier.size() << std::endl;
	std::cout << "Closed: " << closed.size() << std::endl;

	if (!solved)
		return std::vector<Puzzle>();

	const Node *node = closed.back().get();
	std::vector<Puzzle> path;

	while (node != nullptr)
	{
		path.push_back(node->getPuzzle());
		node = node->getParent();
	}

	std::reverse(path.begin(), path.end());
	return path;
}

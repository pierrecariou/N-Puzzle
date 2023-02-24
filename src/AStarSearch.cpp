#include "AStarSearch.hpp"

#include <algorithm>
#include <iostream>

bool AStarSearch::NodeCompare::operator()(std::shared_ptr<Node> const &a, std::shared_ptr<Node> const &b) const { return a.get()->getF() < b.get()->getF(); }

void AStarSearch::expand(std::shared_ptr<Node> node)
{
	for (Puzzle puzzle : node.get()->getPuzzle().getMoves())
	{
		Node child(*heuristic.get(), puzzle, node);

		if (std::find_if(closed.begin(), closed.end(), [&child](std::shared_ptr<Node> const &node)
						 { return node.get()->getPuzzle() == child.getPuzzle(); }) != closed.end())
			continue;

		auto frontierNode = std::find_if(frontier.begin(), frontier.end(), [&child](std::shared_ptr<Node> const &node)
										 { return node.get()->getPuzzle() == child.getPuzzle(); });

		if (frontierNode != frontier.end())
		{
			if (frontierNode->get()->getCost() > child.getCost())
				frontier.erase(frontierNode);
			else
				continue;
		}

		frontier.insert(std::make_shared<Node>(child));
	}
}

AStarSearch::AStarSearch(std::unique_ptr<Heuristic> heuristic) : heuristic(std::move(heuristic)) {}
bool AStarSearch::isSolved() { return solved; }

void AStarSearch::init(Puzzle puzzle)
{
	this->puzzle = puzzle;

	frontier.clear();
	closed.clear();
	solved = false;

	frontier.insert(std::make_unique<Node>(*heuristic.get(), puzzle, nullptr));
}

void AStarSearch::solve()
{
	while (!frontier.empty() && !solved)
	{
		std::shared_ptr<Node> node = *frontier.begin();
		frontier.erase(frontier.begin());
		closed.push_back(node);

		if (node->getHeuristic() == 0)
			solved = true;
		else
			expand(node);
	}
}

std::vector<Puzzle> AStarSearch::result()
{
	std::cout << "Frontier: " << frontier.size() << std::endl;
	std::cout << "Closed: " << closed.size() << std::endl;

	if (!solved)
		return std::vector<Puzzle>();

	Node *node = closed.back().get();
	std::vector<Puzzle> path;

	while (node != nullptr)
	{
		path.push_back(node->getPuzzle());
		node = node->getParent();
	}

	std::reverse(path.begin(), path.end());
	return path;
}

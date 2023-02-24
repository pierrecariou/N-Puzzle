#include "AStarSearch.hpp"

#include <algorithm>
#include <iostream>

bool AStarSearch::NodeCompare::operator()(std::shared_ptr<Node> const &a, std::shared_ptr<Node> const &b) const { return a.get()->getF() < b.get()->getF(); }

std::vector<Puzzle> AStarSearch::reconstructPath(Node node)
{
	std::cout << "Frontier: " << frontier.size() << std::endl;
	std::cout << "Closed: " << closed.size() << std::endl;

	std::vector<Puzzle> path;
	while (node.getParent() != nullptr)
	{
		path.push_back(node.getPuzzle());
		node = *node.getParent();
	}

	std::reverse(path.begin(), path.end());
	return path;
}

void AStarSearch::expand(std::shared_ptr<Node> node)
{
	for (Puzzle puzzle : node.get()->getPuzzle().getMoves())
	{
		Node child(heuristic, puzzle, node);

		if (std::find_if(closed.begin(), closed.end(), [&child](std::shared_ptr<Node> const &node)
						 { return node.get()->getPuzzle() == child.getPuzzle(); }) != closed.end())
			continue;

		auto frontierNode = std::find_if(frontier.begin(), frontier.end(), [&child](std::shared_ptr<Node> const &node)
										 { return node.get()->getPuzzle() == child.getPuzzle(); });

		if (frontierNode != frontier.end())
		{
			if (frontierNode->get()->getCost() <= child.getCost())
				continue;
			else
				frontier.erase(frontierNode);
		}

		frontier.insert(std::make_shared<Node>(child));
	}
}

AStarSearch::AStarSearch(Heuristic &heuristic) : heuristic(heuristic) {}
void AStarSearch::init(Puzzle puzzle)
{
	this->puzzle = puzzle;

	frontier.clear();
	closed.clear();

	frontier.insert(std::make_unique<Node>(heuristic, puzzle, nullptr));
}

std::vector<Puzzle> AStarSearch::solve()
{
	while (!frontier.empty())
	{
		std::shared_ptr<Node> node = *frontier.begin();
		frontier.erase(frontier.begin());
		closed.push_back(node);

		if (node->getHeuristic() == 0)
			return reconstructPath(*node);

		expand(node);
	}

	return std::vector<Puzzle>();
}

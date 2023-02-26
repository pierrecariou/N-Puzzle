#include "AStarSearch.hpp"

#include <utility>
#include <algorithm>

std::vector<Puzzle> AStarSearch::reconstructPath(Node *node)
{
	std::vector<Puzzle> path;

	while (node->getParent() != nullptr)
	{
		path.push_back(node->getPuzzle());
		node = node->getParent();
	}

	path.push_back(node->getPuzzle());

	return path;
}

void AStarSearch::expandNode(Node *node)
{
	for (auto &puzzle : node->getPuzzle().getMoves())
	{
		auto newNode = std::make_shared<Node>(puzzle, heuristic.get(), node);

		if (std::find_if(closed.begin(), closed.end(), [&newNode](const std::shared_ptr<Node> &node)
						 { return node->getPuzzle() == newNode->getPuzzle(); }) != closed.end())
			continue;

		auto openNode = std::find_if(open.begin(), open.end(), [&newNode](const std::shared_ptr<Node> &node)
									 { return node->getPuzzle() == newNode->getPuzzle(); });

		if (openNode != open.end())
		{
			if (newNode->getG() < (*openNode)->getG())
				open.erase(openNode);
			else
				continue;
		}

		open.insert(newNode);
	}
}

AStarSearch::AStarSearch(std::unique_ptr<Heuristic> heuristic) : heuristic(std::move(heuristic)) {}

std::vector<Puzzle> AStarSearch::solve(Puzzle puzzle)
{
	open.clear();
	open.insert(std::make_shared<Node>(puzzle, heuristic.get()));
	closed.clear();

	while (!open.empty())
	{
		auto node = open.begin();
		closed.insert(*node);
		open.erase(node);

		if (node->get()->getH() == 0)
			return reconstructPath(node->get());

		expandNode(node->get());
	}

	return std::vector<Puzzle>();
}

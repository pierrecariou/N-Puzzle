#include "AStarSearch.hpp"

#include <utility>
#include <algorithm>
#include <iostream>

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
	for (Puzzle puzzle : node->getPuzzle().getMoves())
	{
		std::shared_ptr<Node> newNode = std::make_shared<Node>(puzzle, heuristic.get(), node);

		if (std::find_if(closed.begin(), closed.end(), [&newNode](const std::shared_ptr<Node> &node)
						 { return node->getPuzzle() == newNode->getPuzzle(); }) != closed.end())
			continue;

		auto openNode = std::find_if(open.begin(), open.end(), [&newNode](const std::shared_ptr<Node> &node)
									 { return node->getPuzzle() == newNode->getPuzzle(); });

		if (openNode != open.end())
		{
			if (newNode->getG() < openNode->get()->getG())
				open.erase(openNode);
			else
				continue;
		}

		open.insert(newNode);
	}
}

AStarSearch::AStarSearch(std::unique_ptr<Heuristic> heuristic) : heuristic(std::move(heuristic)) {}

std::unique_ptr<std::vector<Puzzle>> AStarSearch::solve(Puzzle puzzle)
{
	open.clear();
	closed.clear();

	open.insert(std::make_shared<Node>(puzzle, heuristic.get()));
	while (!open.empty())
	{
		std::shared_ptr<Node> node = *open.begin();
		open.erase(open.begin());
		closed.push_back(node);

		if (node->getH() == 0)
			return std::make_unique<std::vector<Puzzle>>(reconstructPath(node.get()));

		expandNode(node.get());
	}

	return nullptr;
}

#include "Search.hpp"

#include <iostream>
#include <algorithm>

template <typename NodeComparator>
void Search<NodeComparator>::expandNode(std::shared_ptr<Node> node)
{
	for (Puzzle puzzle : node->getPuzzle().getChildren())
	{
		std::shared_ptr<Node> child = std::make_shared<Node>(puzzle, heuristic.get(), node.get());

		if (std::find_if(closed.begin(), closed.end(), [&child](const std::shared_ptr<Node> &node)
						 { return node->getPuzzle() == child->getPuzzle(); }) != closed.end())
			continue;

		auto it = std::find_if(frontier.begin(), frontier.end(), [&child](const std::shared_ptr<Node> &node)
							   { return node->getPuzzle() == child->getPuzzle(); });
		if (it != frontier.end())
		{
			if (child->getCost() < (*it)->getCost())
				frontier.erase(it);
			else
				continue;
		}
		frontier.insert(child);
	}
}

template <typename NodeComparator>
std::vector<Puzzle> Search<NodeComparator>::reconstructPath(Node *node)
{
	std::vector<Puzzle> path;
	while (node != nullptr)
	{
		path.insert(path.begin(), node->getPuzzle());
		node = node->getParent();
	}
	return path;
}

template <typename NodeComparator>
Search<NodeComparator>::Search(std::unique_ptr<Heuristic> heuristic) : heuristic(std::move(heuristic))
{
}

template <typename NodeComparator>
std::unique_ptr<std::vector<Puzzle>> Search<NodeComparator>::solve(Puzzle puzzle)
{
	frontier.clear();
	closed.clear();

	frontier.insert(std::make_shared<Node>(puzzle, heuristic.get()));
	while (!frontier.empty())
	{
		std::shared_ptr<Node> node = *frontier.begin();
		frontier.erase(frontier.begin());
		closed.insert(node);

		if (node->getHeuristic() == 0)
			return std::make_unique<std::vector<Puzzle>>(reconstructPath(node.get()));
		expandNode(node);

		// std::cout << "Cost: " << node->getCost() << " Heuristic: " << node->getHeuristic() << std::endl;
	}

	return nullptr;
}

template <typename NodeComparator>
void Search<NodeComparator>::printStats()
{
	std::cout << "Complexity in time: " << frontier.size() << std::endl;
	std::cout << "Complexity in size: " << closed.size() << std::endl;
}

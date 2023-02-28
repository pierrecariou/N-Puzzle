#include "AStarSearch.hpp"

#include <utility>
#include <algorithm>

bool AStarSearch::NodeComparator::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const { return lhs.get()->getF() < rhs.get()->getF(); }

void AStarSearch::expandNode(std::shared_ptr<Node> node)
{
	for (Puzzle &puzzle : node->getPuzzle().getMoves())
	{
		std::shared_ptr<Node> child = std::make_shared<Node>(puzzle, heuristic.get(), node.get());

		if (std::find_if(closed.begin(), closed.end(), [&child](const std::shared_ptr<Node> &node)
						 { return node->getPuzzle() == child->getPuzzle(); }) != closed.end())
			continue;

		auto it = std::find_if(open.begin(), open.end(), [&child](const std::shared_ptr<Node> &node)
							   { return node->getPuzzle() == child->getPuzzle(); });

		if (it != open.end())
		{
			if (child->getG() < (*it)->getG())
				open.erase(it);
			else
				continue;
		}

		open.insert(child);
	}
}

std::vector<Puzzle> AStarSearch::reconstructPath(Node *node)
{
	if (node->getParent() == nullptr)
		return std::vector<Puzzle>{node->getPuzzle()};

	std::vector<Puzzle> path = reconstructPath(node->getParent());
	path.push_back(node->getPuzzle());
	return path;
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

		expandNode(node);
	}

	return nullptr;
}

std::ostream &operator<<(std::ostream &os, const AStarSearch &search)
{
	os << "Complexity in time: " << search.open.size() << std::endl;
	os << "Complexity in size: " << search.closed.size() << std::endl;

	return os;
}
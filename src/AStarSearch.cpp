#include <algorithm>
#include <iostream>

#include "AStarSearch.hpp"

std::vector<Puzzle> AStarSearch::reconstructPath(Node node)
{
	std::cout << "Closed: " << closed.size() << std::endl;
	std::cout << "Open: " << open.size() << std::endl;

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
	for (Puzzle puzzle : node->getPuzzle().getMoves())
	{
		std::shared_ptr<Node> child(new Node(puzzle, node.get(), heuristic));

		if (std::find_if(closed.begin(), closed.end(), [child](std::shared_ptr<Node> node)
						 { return node.get()->getPuzzle() == child.get()->getPuzzle(); }) != closed.end())
			continue;

		auto openNode = std::find_if(open.begin(), open.end(), [child](std::shared_ptr<Node> node)
									 { return node.get()->getPuzzle() == child.get()->getPuzzle(); });
		if (openNode != open.end())
		{
			if (openNode->get()->getCost() <= child.get()->getCost())
				continue;
			else
				open.erase(openNode);
		}

		open.insert(child);
	}
}

AStarSearch::AStarSearch(Heuristic *heuristic) : heuristic(heuristic) {}
void AStarSearch::setPuzzle(Puzzle puzzle) { this->puzzle = puzzle; }

std::vector<Puzzle> AStarSearch::solve(Puzzle goal)
{
	closed.clear();
	open.clear();
	open.insert(std::make_shared<Node>(puzzle, nullptr, heuristic));

	while (!open.empty())
	{
		std::shared_ptr<Node> node = *open.begin();
		open.erase(open.begin());
		closed.push_back(node);

		if (node.get()->getPuzzle() == goal)
			return reconstructPath(*node);

		expand(node);
	}

	return std::vector<Puzzle>();
}

AStarSearch::Node::Node(Puzzle puzzle, Node *parent, Heuristic *heuristic)
	: puzzle(puzzle), parent(parent), cost(parent ? parent->getCost() + 1 : 0), heuristic(heuristic->calculate(puzzle)) {}

Puzzle AStarSearch::Node::getPuzzle() const { return puzzle; }
AStarSearch::Node *AStarSearch::Node::getParent() const { return parent; }

unsigned int AStarSearch::Node::getCost() const { return cost; }
unsigned int AStarSearch::Node::getHeuristic() const { return heuristic; }
unsigned int AStarSearch::Node::getF() const { return cost + heuristic; }

bool AStarSearch::NodeCompare::operator()(std::shared_ptr<Node> const &a, std::shared_ptr<Node> const &b) const
{
	return a.get()->getF() < b.get()->getF();
}

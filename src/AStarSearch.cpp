#include <algorithm>

#include "AStarSearch.hpp"

void AStarSearch::expand(Node &node)
{
	for (Puzzle puzzle : node.getPuzzle().getMoves())
	{
		Node child(this, closed.size() - 1, puzzle);

		if (std::find_if(closed.begin(), closed.end(), [&child](Node const &node)
						 { return node.getPuzzle() == child.getPuzzle(); }) != closed.end())
			continue;

		open.push(child);
	}
}

std::vector<Puzzle> AStarSearch::reconstructPath(Node node)
{
	std::vector<Puzzle> path;

	while (node.getParent() != nullptr)
	{
		path.push_back(node.getPuzzle());
		node = *node.getParent();
	}

	std::reverse(path.begin(), path.end());
	return path;
}

AStarSearch::AStarSearch(Heuristic *heuristic) : heuristic(heuristic) {}
void AStarSearch::setPuzzle(Puzzle puzzle) { this->puzzle = puzzle; }

std::vector<Puzzle> AStarSearch::solve(Puzzle goal)
{
	closed.clear();
	while (!open.empty())
		open.pop();
	open.push(Node(this, 0, puzzle));

	while (!open.empty())
	{
		Node node = open.top();
		open.pop();

		if (node.getPuzzle() == goal)
			return reconstructPath(node);

		closed.push_back(node);
		expand(node);
	}

	return std::vector<Puzzle>();
}

AStarSearch::Node::Node(AStarSearch *search, size_t parent, Puzzle puzzle) : search(search), parent(parent), puzzle(puzzle)
{
	if (search->closed.empty())
		cost = 0;
	else
		cost = search->closed[parent].getCost() + 1;
	heuristic = search->heuristic->calculate(puzzle);
}

Puzzle AStarSearch::Node::getPuzzle() const { return puzzle; }
const AStarSearch::Node *AStarSearch::Node::getParent() const { return cost == 0 ? nullptr : &search->closed[parent]; }

unsigned int AStarSearch::Node::getCost() const { return cost; }
unsigned int AStarSearch::Node::getHeuristic() const { return heuristic; }
unsigned int AStarSearch::Node::getF() const { return cost + heuristic; }

bool AStarSearch::NodeCompare::operator()(Node const &a, Node const &b) { return a.getF() > b.getF(); }
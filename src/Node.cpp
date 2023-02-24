#include "Node.hpp"

Node::Node(const Heuristic &heuristic, Puzzle puzzle, std::shared_ptr<Node> parent) : puzzle(puzzle), parent(parent)
{
	if (parent == nullptr)
		cost = 0;
	else
		cost = parent->getCost() + 1;

	this->heuristic = heuristic.calculate(puzzle);
}

Puzzle Node::getPuzzle() const { return puzzle; }
Node *Node::getParent() const { return parent.get(); }

unsigned int Node::getCost() const { return cost; }
unsigned int Node::getHeuristic() const { return heuristic; }
unsigned int Node::getF() const { return cost + heuristic; }

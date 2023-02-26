#include "Node.hpp"

Node::Node(Puzzle puzzle, Heuristic *heuristic, Node *parent) : puzzle(puzzle), parent(parent)
{
	if (parent != nullptr)
		cost = parent->getG() + 1;
	else
		cost = 0;
	this->heuristic = heuristic->calculate(puzzle);
}

Puzzle &Node::getPuzzle() { return puzzle; }
Node *Node::getParent() { return parent; }

unsigned int Node::getG() { return cost; }
unsigned int Node::getH() { return heuristic; }
unsigned int Node::getF() const { return cost + heuristic; }

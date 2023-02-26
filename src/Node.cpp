#include "Node.hpp"

Node::Node(Puzzle puzzle, Node *parent, Heuristic *heuristic) : puzzle(puzzle), parent(parent)
{
	if (parent != nullptr)
		cost = parent->getG() + 1;
	this->heuristic = heuristic->calculate(puzzle);
}

const Puzzle Node::getPuzzle() const { return puzzle; }
const Node *Node::getParent() const { return parent; }

unsigned int Node::getG() const { return cost; }
unsigned int Node::getH() const { return heuristic; }
unsigned int Node::getF() const { return cost + heuristic; }

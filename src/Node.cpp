#include "Node.hpp"

Node::Node(const Heuristic &heuristic, std::unique_ptr<Puzzle> puzzle, std::shared_ptr<Node> parent)
	: puzzle(std::move(puzzle)), parent(parent), cost(parent ? parent->getCost() + 1 : 0), heuristic(heuristic.calculate(*this->puzzle)) {}

const Puzzle &Node::getPuzzle() const { return *puzzle; }
const Node *Node::getParent() const { return parent.get(); }

unsigned int Node::getCost() const { return cost; }
unsigned int Node::getHeuristic() const { return heuristic; }
unsigned int Node::getF() const { return cost + heuristic; }

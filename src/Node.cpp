#include "Node.hpp"

Node::Node(Puzzle puzzle, Heuristic *heuristic, Node *parent) : puzzle(puzzle), parent(parent), cost(parent ? parent->getCost() + 1 : 0), heuristic(heuristic->calculate(puzzle))
{
}

Puzzle &Node::getPuzzle() { return puzzle; }
Node *Node::getParent() { return parent; }

unsigned int Node::getCost() const { return cost; }
unsigned int Node::getHeuristic() const { return heuristic; }
unsigned int Node::getScore() const { return cost + heuristic; }

bool AStarComparator::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const { return lhs->getScore() < rhs->getScore(); }
bool GreedyComparator::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const { return lhs->getHeuristic() < rhs->getHeuristic(); }
bool UniformCostComparator::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const { return lhs->getCost() < rhs->getCost(); }

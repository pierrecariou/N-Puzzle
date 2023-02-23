#include <set>
#include <memory>

#include "Puzzle.hpp"
#include "Heuristic.hpp"

class AStarSearch
{
private:
	Heuristic *heuristic;
	Puzzle puzzle;

	class Node;
	struct NodeCompare
	{
		bool operator()(std::shared_ptr<Node> const &a, std::shared_ptr<Node> const &b) const;
	};

	std::multiset<std::shared_ptr<Node>, NodeCompare> open;
	std::vector<std::shared_ptr<Node>> closed;

	std::vector<Puzzle> reconstructPath(Node node);
	void expand(std::shared_ptr<Node> node);

public:
	AStarSearch(Heuristic *heuristic);
	void setPuzzle(Puzzle puzzle);

	std::vector<Puzzle> solve(Puzzle goal);
};

class AStarSearch::Node
{
private:
	Puzzle puzzle;
	Node *parent;

	unsigned int cost;
	unsigned int heuristic;

public:
	Node(Puzzle puzzle, Node *parent, Heuristic *heuristic);

	Puzzle getPuzzle() const;
	Node *getParent() const;

	unsigned int getCost() const;
	unsigned int getHeuristic() const;
	unsigned int getF() const;
};

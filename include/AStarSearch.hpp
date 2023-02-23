#include <queue>

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
		bool operator()(Node const &a, Node const &b);
	};

	std::priority_queue<Node, std::vector<Node>, NodeCompare> open;
	std::vector<Node> closed;

	void expand(Node &node);
	std::vector<Puzzle> reconstructPath(Node node);

public:
	AStarSearch(Heuristic *heuristic);
	void setPuzzle(Puzzle puzzle);

	std::vector<Puzzle> solve(Puzzle goal);
};

class AStarSearch::Node
{
private:
	AStarSearch *search;
	size_t parent;
	Puzzle puzzle;

	unsigned int cost;
	unsigned int heuristic;

public:
	Node(AStarSearch *search, size_t parent, Puzzle puzzle);

	Puzzle getPuzzle() const;
	const Node *getParent() const;

	unsigned int getCost() const;
	unsigned int getHeuristic() const;
	unsigned int getF() const;
};

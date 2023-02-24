#include "Heuristic.hpp"
#include "Node.hpp"

#include <set>

class AStarSearch
{
private:
	std::unique_ptr<Heuristic> heuristic;
	Puzzle puzzle;

	struct NodeCompare
	{
		bool operator()(std::shared_ptr<Node> const &a, std::shared_ptr<Node> const &b) const;
	};

	std::multiset<std::shared_ptr<Node>, NodeCompare> frontier;
	std::vector<std::shared_ptr<Node>> closed;
	bool solved = false;

	void expand(const std::shared_ptr<Node> &node);

public:
	AStarSearch(std::unique_ptr<Heuristic> heuristic);
	bool isSolved();

	void init(const Puzzle &puzzle);
	void solve();
	const std::vector<Puzzle> result();
};

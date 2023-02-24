#include "Heuristic.hpp"
#include "Node.hpp"

#include <memory>
#include <set>

class AStarSearch
{
private:
	std::unique_ptr<Heuristic> heuristic;
	Puzzle puzzle;
	bool solved = false;

	struct NodeCompare
	{
		bool operator()(std::shared_ptr<Node> const &a, std::shared_ptr<Node> const &b) const;
	};

	std::multiset<std::shared_ptr<Node>, NodeCompare> frontier;
	std::vector<std::shared_ptr<Node>> closed;

	void expand(std::shared_ptr<Node> node);

public:
	AStarSearch(std::unique_ptr<Heuristic> heuristic);
	bool isSolved();

	void init(Puzzle puzzle);
	void solve();
	std::vector<Puzzle> result();
};

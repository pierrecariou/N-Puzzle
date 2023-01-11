#include "Heuristic.hpp"
#include "NPuzzle.hpp"
#include "NPuzzleFactory.hpp"

#include <memory>
#include <set>
#include <vector>

/*
struct SharedNPuzzleComparator {
    bool operator()(const std::shared_ptr<NPuzzle>& lhs,
                    const std::shared_ptr<NPuzzle>& rhs) const
    {
        return lhs->getF() < rhs->getF();
    }
};
	*/

class AStarAlgorithm {
 public:
	AStarAlgorithm(std::unique_ptr<NPuzzle> currentState, std::unique_ptr<NPuzzle> const goalState, std::unique_ptr<Heuristic> const heuristic, NPuzzleFactory const &factory);
	~AStarAlgorithm();
	
	void solve();
	void printSolution(double elapsedTime) const;
	
 private:
	void reconstructPath();

	std::multiset<NPuzzle> expand(NPuzzle const &puzzle);

	//std::unique_ptr<NPuzzle> _currentState;
	NPuzzleFactory const &_factory;

	std::unique_ptr<NPuzzle> _goalState;
	std::unique_ptr<NPuzzle> _startState;
	std::unique_ptr<Heuristic> _heuristic;

	std::multiset<NPuzzle> _opened;
	std::vector<NPuzzle> _closed;

	bool _success;
	std::vector<NPuzzle> _solution;
};

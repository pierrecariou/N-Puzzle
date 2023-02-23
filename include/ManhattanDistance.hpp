#include "Heuristic.hpp"

class ManhattanDistance : public Heuristic
{
public:
	int calculate(Puzzle puzzle);
};

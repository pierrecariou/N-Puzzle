#pragma once

#include "Heuristic.hpp"

class FringePatternDatabase : public Heuristic {
 public:
  FringePatternDatabase() = default;
  ~FringePatternDatabase() = default;

  int calculateHeuristic(NPuzzle const &currentState, std::unique_ptr<NPuzzle> const &goalState) const override;
};

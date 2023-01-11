#pragma once

#include <memory>

#include "NPuzzle.hpp"

class Heuristic {
 public:
  Heuristic() = default;
  virtual ~Heuristic() = default;

  virtual int calculateHeuristic(NPuzzle const &currentState, std::unique_ptr<NPuzzle> const &goalState) const = 0;
};

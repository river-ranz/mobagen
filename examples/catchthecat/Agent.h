#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

class World;

struct Cost {
  int cost;

  bool operator<(const Cost& rhs) const {
    return cost > rhs.cost;
  }
};

struct AStarNode {
  Point2D point;
  Cost heuristic;
  int accCost;

  bool operator<(const AStarNode& other) const {
    return heuristic.cost + accCost > other.heuristic.cost + other.accCost;
  }
};

class Agent {
private:
  std::unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element don't exist [] will give you wrong results
  std::unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);
  std::vector<Point2D> getVisitableNeighbors(World* w, Point2D p) const;

  int distanceToTheBorder(Point2D p, int sideSizeOver2);
};

#endif  // AGENT_H

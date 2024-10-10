#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

class World;

struct AStarNode {
  Point2D point;
  int accCost;
  int heuristic;

  bool operator<(const AStarNode& other) const {
    return accCost + heuristic > other.accCost + other.heuristic;
  }
};

int distanceToTheBorder(Point2D p, int SideSizeOver2) {
  // right side
  if (p.x - p.y < 0 && p.x + p.y > 0) {
    return SideSizeOver2 - p.x;
  }
  // north
  if (p.x - p.y > 0 && p.x + p.y > 0) {
    return SideSizeOver2 - p.y;
  }
  // left side
  if (p.x - p.y > 0 && p.x + p.y < 0) {
    return SideSizeOver2 + p.x;
  }
  // south
  if (p.x - p.y < 0 && p.x + p.y < 0) {
    return SideSizeOver2 + p.y;
  }
}

class Agent {
private:
  std::priority_queue<AStarNode> frontier;          // to store next ones to visit
  std::unordered_set<AStarNode> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  std::unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);
  std::vector<Point2D> getVisitableNeighbors(World* w, Point2D p);
};

#endif  // AGENT_H

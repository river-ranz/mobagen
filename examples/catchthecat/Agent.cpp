#include "Agent.h"
#include "World.h"
#include <queue>

using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  std::priority_queue<pair<AStarNode, Cost>> frontier;          // to store next ones to visit
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path

  // bootstrap state
  AStarNode catStar;
  catStar.point = w->getCat();
  catStar.heuristic.cost = distanceToTheBorder(catStar.point, w->getWorldSideSize()/2);
  catStar.accCost = 0;
  frontier.push(make_pair(catStar, catStar.heuristic));
  frontierSet.insert(catStar.point);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we don't find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    AStarNode p = frontier.top().first;
    // remove the current from frontierSet
    frontier.pop();
    frontierSet.erase(p.point);
    // mark current as visited
    visited.insert(make_pair(p.point, true));

    if (w->catWinsOnSpace(p.point)) {
      borderExit = p.point;
      break;
    }

    // getVisitableNeighbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    vector<Point2D> visitableNeighbors = getVisitableNeighbors(w, p.point);

    // iterate over the neighs:
    for (Point2D neighbor : visitableNeighbors) {
      // for every neighbor set the cameFrom
      AStarNode neighborStar;
      neighborStar.point = neighbor;
      neighborStar.heuristic.cost = distanceToTheBorder(neighborStar.point, w->getWorldSideSize() / 2);
      neighborStar.accCost = p.accCost++;
      cameFrom.insert(make_pair(neighborStar.point, p.point));

      // enqueue the neighbors to frontier and frontierSet
      frontier.push(make_pair(neighborStar, neighborStar.heuristic));
      frontierSet.insert(neighborStar.point);
      // do this up to find a visitable border and break the loop
    }
  }

  // if the border is not infinity, build the path from border to the cat using the cameFrom map
  if (borderExit != Point2D::INFINITE) {
    vector<Point2D> path;
    path.push_back(borderExit);

    while (path.back() != catStar.point) {
      vector<Point2D> visitableNeighbors = getVisitableNeighbors(w, path.back());

      for (Point2D neighbor : visitableNeighbors) {
        if (cameFrom.contains(neighbor)) {
          auto it = cameFrom.find(neighbor);
          if (path.back() != it->second)
            path.push_back(it->second);
        }
      }
    }
    return path;
  }
  // if there isn't a reachable border, just return empty vector
  return vector<Point2D>();

  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
}

std::vector<Point2D> Agent::getVisitableNeighbors(World* w, Point2D p) const {
  vector<Point2D> neighbors = World::neighbors(p);
  vector<Point2D> visitable = vector<Point2D>();
  for (auto neighbor : neighbors) {
    // if neighbor is not blocked & neighbor is not the cat position
    if (!w->getContent(neighbor) && neighbor != w->getCat()) {
      // if neighbor is not visited & not in queue
      if (!visited.contains(neighbor) && !frontierSet.contains(neighbor))
        visitable.push_back(neighbor);
    }
  }
  return visitable;
}

int Agent::distanceToTheBorder(Point2D p, int sideSizeOver2) {
  // north
  if (p.x - p.y < 0 && p.x + p.y > 0) {
    return sideSizeOver2 - p.x;
  }
  // right
  if (p.x - p.y > 0 && p.x + p.y > 0) {
    return sideSizeOver2 - p.y;
  }
  // south
  if (p.x - p.y > 0 && p.x + p.y < 0) {
    return sideSizeOver2 + p.x;
  }
  // left
  if (p.x - p.y < 0 && p.x + p.y < 0) {
    return sideSizeOver2 + p.y;
  }
  // center
  if (p.x == 0 && p.y == 0) {
    return sideSizeOver2;
  }
  if (p.x == p.y && p.x > 0) {
    return sideSizeOver2 - p.x;
  }
  if (p.x == p.y && p.x < 0) {
    return sideSizeOver2 + p.x;
  }
  if (p.x + p.y == 0 && p.x > p.y) {
    return sideSizeOver2 - p.x;
  }
  if (p.x + p.y == 0 && p.x < p.y) {
    return sideSizeOver2 + p.x;
  }
}

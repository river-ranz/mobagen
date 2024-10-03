#include "Agent.h"
#include "World.h"
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    Point2D p = frontier.front();
    // remove the current from frontierset
    frontier.pop();
    frontierSet.erase(p);
    // mark current as visited
    visited.insert(make_pair(p, true));

    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    vector<Point2D> visitableNeighbors = getVisitableNeighbors(w, p);
    // iterate over the neighs:
    for (Point2D neighbor : visitableNeighbors) {
      // for every neighbor set the cameFrom
      cameFrom.insert(make_pair(neighbor, p));
      // enqueue the neighbors to frontier and frontierset
      frontier.push(neighbor);
      frontierSet.insert(neighbor);
      // do this up to find a visitable border and break the loop
    }
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  if (borderExit != Point2D::INFINITE) {

  }
  // if there isnt a reachable border, just return empty vector
  else
    return vector<Point2D>();

  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

std::vector<Point2D> Agent::getVisitableNeighbors(World* w, Point2D p) {
  vector<Point2D> neighbors = World::neighbors(p);
  vector<Point2D> visitable = vector<Point2D>();
  for (auto neighbor : neighbors) {
    // if neighbor is not blocked & neighbor is not the cat position
    if (!w->getContent(neighbor) && neighbor != w->getCat()) {
      // if neighbor is not visited & neighbor is not in the queue
      if (!visited.contains(neighbor)) {
        visitable.push_back(neighbor);
      }
    }
  }
  return visitable;
}

#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {

  if (!stack.empty()) {
    visited[stack.back().x][stack.back().y] = true;
    if (!getVisitables(w, stack.back()).empty()) {
      w->SetNodeColor(stack.back(), Color::Lavender);
      std::vector<Point2D> visitables = getVisitables(w, stack.back());
      Point2D neighbor;


      if (visitables.size() == 1)
        neighbor = visitables[0];
      else {
        Random rand;
        neighbor = visitables[rand.Range(0, visitables.size() - 1)];
      }

      if (stack.back().Up() == neighbor) {
        w->SetNorth(stack.back(), false);
        w->SetSouth(stack.back().Up(),false);
      }

      if (stack.back().Right() == neighbor) {
        w->SetEast(stack.back(), false);
        w->SetWest(stack.back().Right(), false);
      }

      if (stack.back().Down() == neighbor) {
        w->SetSouth(stack.back(), false);
        w->SetNorth(stack.back().Down(), false);
      }

      if (stack.back().Left() == neighbor) {
        w->SetWest(stack.back(), false);
        w->SetEast(stack.back().Left(), false);
      }


      stack.push_back(neighbor);
    }
    else {
      w->SetNodeColor(stack.back(), Color::Black);
      stack.pop_back();
    }
  }
  else
    stack.push_back(randomStartPoint(w));

  return true;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  if (w->isValidPosition(p.Up()) && !visited[p.Up().x][p.Up().y])
    visitables.push_back(p.Up());
  if (w->isValidPosition(p.Right()) && !visited[p.Right().x][p.Right().y])
    visitables.push_back(p.Right());
  if (w->isValidPosition(p.Down()) && !visited[p.Down().x][p.Down().y])
    visitables.push_back(p.Down());
  if (w->isValidPosition(p.Left()) && !visited[p.Left().x][p.Left().y])
    visitables.push_back(p.Left());

  return visitables;
}

#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  std::vector<Point2D> path = generatePath(world);
  if (!path.empty() && !world->getContent(path.front()) && path.front() != world->getCat()) { return path.front(); }
  // if that is invalid, choose the next point
  if (path.size() > 2) {
    auto it = path.begin();
    ++it;
    if (it != path.end() && *it != world->getCat() && !world->getContent(*it)) {
      return *it;
    }
  }

  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }
}

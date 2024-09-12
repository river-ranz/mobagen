#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
}

bool topLeft(World& world, Point2D point) {
  if (point.y%2==0) {
    return world.Get({point.x - 1, point.y - 1});
  }
  else {
    return world.Get({point.x, point.y - 1});
  }
}

bool topRight(World& world, Point2D point) {
  if (point.y%2==0) {
    return world.Get({point.x + 1, point.y - 1});
  }
  else {
    return world.Get({point.x, point.y - 1});
  }
}

bool bottomLeft(World& world, Point2D point) {
  if (point.y%2==0) {
    return world.Get({point.x - 1, point.y + 1});
  }
  else {
    return world.Get({point.x, point.y - 1});
  }
}

bool bottomRight(World& world, Point2D point) {
  if (point.y%2==0) {
    return world.Get({point.x + 1, point.y + 1});
  }
  else {
    return world.Get({point.x, point.y - 1});
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int acc = 0;
  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      Point2D p = point + Point2D(x, y);
      acc += world.Get(p);
    }
  }
  /*acc += topLeft(world, point) ? 1 : 0;
  acc += topRight(world, point) ? 1 : 0;
  acc += bottomLeft(world, point) ? 1 : 0;
  acc += bottomRight(world, point) ? 1 : 0;*/
  return acc;
}

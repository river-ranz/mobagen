#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int acc = 0;
  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      Point2D p = point + Point2D(x, y);
      // test if p is inside bounds
      acc += world.Get(p);
    }
  }
  return acc;
}

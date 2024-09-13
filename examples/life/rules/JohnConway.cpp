#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  for (int i = 0; i < world.SideSize(); i++) {
    for (int j = 0; j < world.SideSize(); j++) {

      bool isLive = world.Get({i, j});
      int neighbors = CountNeighbors(world, Point2D(i, j));

      //living cells with 2-3 neighbors live on
      if (isLive && (neighbors == 2 || neighbors == 3))
        world.SetNext(Point2D(i, j), true);

      //dead cells with 3 neighbors get revived
      else if (!isLive && neighbors == 3)
        world.SetNext(Point2D(i, j), true);

      //all other cells will die or stay dead
      else
        world.SetNext(Point2D(i, j), false);
    }
  }
}

bool topLeft(World& world, Point2D point) {
  return world.Get({point.x - 1, point.y + 1});
}

bool topCenter(World& world, Point2D point) {
  return world.Get({point.x, point.y + 1});
}

bool topRight(World& world, Point2D point) {
  return world.Get({point.x + 1, point.y + 1});
}

bool middleLeft(World& world, Point2D point) {
  return world.Get({point.x - 1, point.y});
}

bool middleRight(World& world, Point2D point) {
  return world.Get({point.x + 1, point.y});
}

bool bottomLeft(World& world, Point2D point) {
  return world.Get({point.x - 1, point.y - 1});
}

bool bottomCenter(World& world, Point2D point) {
  return world.Get({point.x, point.y - 1});
}

bool bottomRight(World& world, Point2D point) {
  return world.Get({point.x + 1, point.y - 1});
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int acc = 0;
  //cycle through each neighbor and check if live
  //if live, + 1 otherwise + 0
  acc += topLeft(world, point) ? 1 : 0;
  acc += topCenter(world, point) ? 1 : 0;
  acc += topRight(world, point) ? 1 : 0;
  acc += middleLeft(world, point) ? 1 : 0;
  acc += middleRight(world, point) ? 1 : 0;
  acc += bottomLeft(world, point) ? 1 : 0;
  acc += bottomCenter(world, point) ? 1 : 0;
  acc += bottomRight(world, point) ? 1 : 0;
  return acc;
}

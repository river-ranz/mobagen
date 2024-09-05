#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f averageVelocity = Vector2f::zero();

  // average the velocity
  if (!neighborhood.empty()) {
    for (Boid *neighbor : neighborhood) {
      averageVelocity += neighbor->velocity;
    }
    averageVelocity += boid->velocity;
    averageVelocity /= (neighborhood.size() + 1);
  }

  return Vector2f::normalized(averageVelocity);
}
#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // find center of mass
  Vector2f centerMass = Vector2f::zero();
  if (!neighborhood.empty()) {
    for (Boid *neighbor : neighborhood) {
      centerMass += neighbor->getPosition();
    }

    centerMass += boid->getPosition();
    centerMass /= neighborhood.size() + 1;

    // Pcm - Pagent
    Vector2f agentCM = Vector2f(centerMass.x - boid->getPosition().x, centerMass.y - boid->getPosition().y);

    // check if within cohesion radius
    if (agentCM.getMagnitude() > boid->getDetectionRadius()) {
      cohesionForce = Vector2f(0,0);
    }
    else {
      cohesionForce = Vector2f(agentCM.x / boid->getDetectionRadius(), agentCM.y / boid->getDetectionRadius());
    }

    // maximum magnitude = 1
    cohesionForce = cohesionForce.normalized();
  }


  return cohesionForce;
}
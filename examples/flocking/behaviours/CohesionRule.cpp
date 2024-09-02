#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass
  float centerMassX = 0;
  float centerMassY = 0;
  if (!neighborhood.empty()) {
    for (Boid *b : neighborhood) {
      Vector2f pos = b->getPosition();
      centerMassX += pos.x;
      centerMassY += pos.y;
    }
  }

  Vector2f centerMass = Vector2f(centerMassX / neighborhood.size(), centerMassY / neighborhood.size());

  Vector2f boidPos = boid->getPosition();
  Vector2f agentCM = Vector2f(centerMass.x - boidPos.x, centerMass.y - boidPos.y);

  if (agentCM.getMagnitude() > boid->getDetectionRadius()) {
    cohesionForce = Vector2f(0,0);
  }
  else {
    cohesionForce = Vector2f(agentCM.x / boid->getDetectionRadius(), agentCM.y / boid->getDetectionRadius());
  }

  return cohesionForce;
}
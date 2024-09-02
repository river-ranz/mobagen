#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass
  float centerMassX = 0, centerMassY = 0;
  for (int i = 0; i < neighborhood.size(); i++) {
    Vector2f pos = neighborhood[i]->getPosition();
    centerMassX += pos.x;
    centerMassY += pos.y;
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
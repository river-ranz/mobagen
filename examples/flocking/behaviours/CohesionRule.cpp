#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass
  float centerMass = 0;
  for (int i = 0; i < neighborhood.size(); i++) {
    Vector2f pos = neighborhood[i]->getPosition();
    centerMass += pos.x + pos.y;
  }
  centerMass /= neighborhood.size();

  Vector2f boidPos = boid->getPosition();
  float agent = boidPos.x + boidPos.y;
  Vector2f agentCM = Vector2f(agent, centerMass);

  if (agentCM.getMagnitude() > boid->getDetectionRadius()) {
    cohesionForce = Vector2f(0,0);
  }
  else {
    cohesionForce = agentCM / boid->getDetectionRadius();
  }
  
  return cohesionForce;
}
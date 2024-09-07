#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;

  if (!neighborhood.empty()) {
    for (Boid* neighbor : neighborhood) {
      if (boid->getPosition() == neighbor->getPosition())
        continue;

      // calc separation vector
      Vector2f sepVec = { boid->getPosition().x - neighbor->getPosition().x, boid->getPosition().y - neighbor->getPosition().y };

      // calc distance between boids
      float dist = sqrt(sepVec.x * sepVec.x + sepVec.y * sepVec.y);

      // if inside the separation radius, accumluate the force
      if (dist < desiredDistance && dist > 0.001f) {
        sepVec = sepVec.normalized(sepVec);
        float force = 1 / dist;
        separatingForce = {separatingForce.x + sepVec.x * force, separatingForce.y + sepVec.y * force};
      }
    }
  }

  separatingForce = Vector2f::normalized(separatingForce);

  //mult by constant
  return separatingForce * 2;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}

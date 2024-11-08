#include "MyGenerator.h"
#include "../PerlinNoise.hpp"
#include "math/Vector2.h"
#include "math/Vector3.h"

#include <iostream>

std::vector<Color32> MyGenerator::Generate(int sideSize, float displacement) {
  std::vector<Color32> colors;

  siv::PerlinNoise perlinNoise(sideSize);
  float octave = perlinNoise.octave3D_01(1, 1, 1, 3);

  if (prevSideSize == sideSize) { //if size doesn't change (buggy)
    height = HydraulicErosion(height, sideSize);
  }
  else { //generate terrain
    for (int i = 0; i < sideSize; i++) {
      for (int j = 0; j < sideSize; j++) {

        float posY = (float)((j - sideSize / 2)) / ((float)sideSize / 2);
        float posX = (float)((i - sideSize / 2)) / ((float)sideSize / 2);

        float const islandInfluence = (1 - posX * posX) * (1 - posY * posY);

        float noise = perlinNoise.noise3D_01(posY * 2, posX * 2, displacement * 50) + 1;
        noise /= 2;

        float avg = std::lerp(avg, 0, 0.5f);

        avg *= octave * 1.8f;

        avg += islandInfluence * 0.4f + noise * 0.7f;

        height.push_back(avg);
      }
    }
  }

  // assign a color
  for (int i = 0; i < height.size(); i++) {
    if (height[i] < 1.0f) {
      colors.push_back(Color32::LerpColor(Color::DarkBlue, Color::Blue, height[i] / 1.0f));
    }
    else if (height[i] < 1.15f) {
      colors.push_back(Color32::LerpColor(Color::Blue, Color::DarkGoldenrod, (height[i] - 1.0f) / 0.3f));
    }
    else if (height[i] < 1.3f) {
      colors.push_back(Color32::LerpColor(Color::DarkGoldenrod, Color::ForestGreen, (height[i] - 1.15f) / 0.4f));
    }
    else if (height[i] < 1.45f) {
      colors.push_back(Color32::LerpColor(Color::ForestGreen, Color::Tan, (height[i] - 1.3f) / 0.5f));
    }
    else if (height[i] < 1.6f) {
      colors.push_back(Color32::LerpColor(Color::Tan, Color::White, (height[i] - 1.45f) / 0.6f));
    }
    else {
      colors.push_back(Color::White);
    }
  }
  std::cout << colors.size() << std::endl;
  prevSideSize = sideSize;
  return colors;
}

std::string MyGenerator::GetName() { return "my generator"; }

std::vector<float> MyGenerator::HydraulicErosion(std::vector<float> height, int sideSize) {
  float evaporationFactor = 0.1;

  Vector2<float> pos = Vector2<float>(rand() % sideSize, rand() % sideSize);
  float startHeight = height[pos.y * sideSize + pos.x];
  float waterRemaining = 150;

  while (waterRemaining > 0) {
    // find neighbors
    std::vector<Vector3> neighbors;
    if (pos.x - 1 >= 0) { neighbors.push_back(Vector3(pos.x - 1, pos.y, height[pos.y * sideSize + (pos.x - 1)])); } //west
    if (pos.y - 1 >= 0) { neighbors.push_back(Vector3(pos.x, pos.y - 1, height[(pos.y - 1) * sideSize + pos.x])); } //south
    if (pos.y + 1 < sideSize) { neighbors.push_back(Vector3(pos.x, pos.y + 1, height[(pos.y + 1) * sideSize + pos.x])); } //north
    if (pos.x - 1 >= 0 && pos.y - 1 >= 0 ) { neighbors.push_back(Vector3(pos.x - 1, pos.y - 1, height[(pos.y - 1) * sideSize + (pos.x - 1)])); } //southwest
    if (pos.x + 1 < sideSize && pos.y + 1 < sideSize) { neighbors.push_back(Vector3(pos.x + 1, pos.y + 1, height[(pos.y + 1) * sideSize + (pos.x + 1)])); } //northeast
    if (pos.x - 1 >= 0 && pos.y + 1 < sideSize) { neighbors.push_back(Vector3(pos.x - 1, pos.y + 1, height[(pos.y + 1) * sideSize + (pos.x - 1)])); } //northwest
    if (pos.x + 1 < sideSize && pos.y - 1 >= 0 ) { neighbors.push_back(Vector3(pos.x + 1, pos.y - 1, height[(pos.y - 1) * sideSize + (pos.x + 1)])); } //southeast

    Vector3 minLoc = Vector3(pos.x, pos.y, startHeight);
    for (auto neighbor : neighbors) {
      if (neighbor.z < minLoc.z) {
        minLoc = neighbor;
      }
    }
    // if start is the lowest point around
    if (minLoc.x == pos.x && minLoc.y == pos.y && minLoc.z == startHeight)
      break;

    if (height[minLoc.y * sideSize + minLoc.x] > 1.15f)
      height[minLoc.y * sideSize + minLoc.x] -= 0.01;

    pos.x = minLoc.x;
    pos.y = minLoc.y;
    startHeight = minLoc.z;
    waterRemaining -= evaporationFactor;
  }
  return height;
}

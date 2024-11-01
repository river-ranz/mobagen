#include "MyGenerator.h"
#include "../PerlinNoise.hpp"

#include <iostream>

std::vector<Color32> MyGenerator::Generate(int sideSize, float displacement) {
  std::vector<Color32> colors;

  siv::PerlinNoise perlinNoise(sideSize);

  for (int i = 0; i < sideSize; i++) {
    for (int j = 0; j < sideSize; j++) {

      float posY = (float)((i - sideSize / 2)) / ((float)sideSize / 2);
      float posX = (float)((j - sideSize / 2)) / ((float)sideSize / 2);

      float islandInfluence = (2 - (abs(posX) + abs(posY))) / 2;
      islandInfluence *= 255;

      float noise = perlinNoise.noise3D(i, j, displacement * 50);
      noise /= 2;
      noise *= 255;

      float avg = (noise + islandInfluence) / 2;

      if (avg < 50)
        colors.emplace_back(Color::DarkBlue);
      else if (avg < 100)
        colors.emplace_back(Color::Yellow);
      else if (avg < 150)
        colors.emplace_back(Color::Green);
      else if (avg < 200)
        colors.emplace_back(Color::Brown);
      else
        colors.emplace_back(Color::White);
    }
  }
  std::cout << colors.size() << std::endl;
  return colors;
}

std::string MyGenerator::GetName() { return "my generator"; }
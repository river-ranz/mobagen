#include "MyGenerator.h"
#include "../PerlinNoise.hpp"

#include <iostream>

std::vector<Color32> MyGenerator::Generate(int sideSize, float displacement) {
  std::vector<Color32> colors;

  siv::PerlinNoise perlinNoise(sideSize);
  float octave = perlinNoise.octave3D_01(1, 1, 1, 3);

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

      if (avg < 1.0f) {
        colors.push_back(Color32::LerpColor(Color::DarkBlue, Color::Blue, avg / 1.0f));
      }
      else if (avg < 1.15f) {
        colors.push_back(Color32::LerpColor(Color::Blue, Color::DarkGoldenrod, (avg - 1.0f) / 0.3f));
      }
      else if (avg < 1.3f) {
        colors.push_back(Color32::LerpColor(Color::DarkGoldenrod, Color::ForestGreen, (avg - 1.15f) / 0.4f));
      }
      else if (avg < 1.45f) {
        colors.push_back(Color32::LerpColor(Color::ForestGreen, Color::Tan, (avg - 1.3f) / 0.5f));
      }
      else {
        colors.push_back(Color32::LerpColor(Color::Tan, Color::White, (avg - 1.45f) / 0.6f));
      }
    }
  }
  std::cout << colors.size() << std::endl;
  return colors;
}

std::string MyGenerator::GetName() { return "my generator"; }
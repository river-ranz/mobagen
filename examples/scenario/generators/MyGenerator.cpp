#include "MyGenerator.h"
#include "../PerlinNoise.hpp"

#include <iostream>

std::vector<Color32> MyGenerator::Generate(int sideSize, float displacement) {
  std::vector<Color32> colors;

  siv::PerlinNoise perlinNoise(sideSize);
  //perlinNoise.octave3D_01(1, 1, 1, 3);

  for (int i = 0; i < sideSize; i++) {
    for (int j = 0; j < sideSize; j++) {

      float posY = (float)((j - sideSize / 2)) / ((float)sideSize / 2);
      float posX = (float)((i - sideSize / 2)) / ((float)sideSize / 2);

      float ny = (float)(2 * i / sideSize) - 1;
      float nx = (float)(2 * j / sideSize) - 1;

      // square bump distance function
      float distance = 1 - (1 - pow(ny, 2)) * (1 - pow(nx, 2));
      
      float noise = perlinNoise.noise3D_01(posY * 2, posX * 2, displacement * 50) + 1;
      noise /= 2;
      noise *= 255;

      float avg = std::lerp(noise, 1 - distance, 0.525);

      if (avg < 80) {
        colors.emplace_back(0, 0, std::lerp(255, 150, 0.5));
      }
      else if (avg < 90) {
        colors.emplace_back(std::lerp(255, 100, 0.5), std::lerp(200, 100, 0.5), 0);
      }
      else if (avg < 100) {
        colors.emplace_back(std::lerp(20, 0, 0.5), std::lerp(200, 100, 0.5), std::lerp(100, 10, 0.5));
      }
      else if (avg < 110) {
        colors.emplace_back(std::lerp(255, 100, 0.5), std::lerp(200, 100, 0.5), std::lerp(150, 100, 0.5));
      }
      else {
        colors.emplace_back(Color::White);
      }
      // if (avg < 50)
      //   colors.emplace_back(Color::DarkBlue);
      // else if (avg < 100)
      //   colors.emplace_back(Color::Yellow);
      // else if (avg < 150)
      //   colors.emplace_back(Color::Green);
      // else if (avg < 200)
      //   colors.emplace_back(Color::Brown);
      // else
      //   colors.emplace_back(Color::White);
    }
  }
  std::cout << colors.size() << std::endl;
  return colors;
}

std::string MyGenerator::GetName() { return "my generator"; }
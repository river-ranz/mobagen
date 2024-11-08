#ifndef MYGENERATOR_H
#define MYGENERATOR_H

#include "../GeneratorBase.h"

class MyGenerator : public ScenarioGeneratorBase {
public:
  std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
  std::string GetName() override;

  std::vector<float> HydraulicErosion(std::vector<float> height, int sideSize);

private:
  std::vector<float> height;
  int prevSideSize = 0;
};

#endif //MYGENERATOR_H

#ifndef MYGENERATOR_H
#define MYGENERATOR_H

#include "../GeneratorBase.h"

class MyGenerator : public ScenarioGeneratorBase {
public:
  std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
  std::string GetName() override;
};

#endif //MYGENERATOR_H

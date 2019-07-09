#ifndef RANDOM_LEVEL_GENERATOR_H
#define RANDOM_LEVEL_GENERATOR_H

#include "markovChains.h"

#include <sp2/math/vector2.h>
#include <sp2/scene/scene.h>

class RandomLevelGenerator
{
public:
    RandomLevelGenerator();
    
    void generate(sp::P<sp::Scene> scene, int seed);
private:
    void learn();
    std::u32string buildDataLine(const std::vector<int>& data, sp::Vector2i size, int x);

    std::u32string start;
    MarkovChains chains;
};

#endif//RANDOM_LEVEL_GENERATOR_H

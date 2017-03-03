//
// Created by Jakob on 2017-02-17.
//

#ifndef PROJECT_PARTICLESYSTEM_H
#define PROJECT_PARTICLESYSTEM_H


#include <vector>
#include "particle.h"
#include "Objects.h"
#include "Texture.hpp"

class particleSystem {

private:
    std::vector<particle*> fishSwarm;
    float bestCost;
    vec3Pos bestPos;
    vec3Pos target;
    int fishAmount;
    Objects fishModel;
    Texture fishTexture;

public:
    particleSystem(int amount);

    void updateSwarm();
    void render();
    void findNeighbours(particle *p, particle neighbours[]);

};

#endif //PROJECT_PARTICLESYSTEM_H
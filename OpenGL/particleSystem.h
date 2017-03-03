//
// Created by Jakob on 2017-02-17.
//

#ifndef PROJECT_PARTICLESYSTEM_H
#define PROJECT_PARTICLESYSTEM_H


#include <vector>
#include "particle.h"
#include "Objects.h"
#include "Texture.hpp"
#include <glm/gtx/transform.hpp>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
#include <glm/gtx/rotate_vector.hpp>

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
    void render(Shader shader);
    void findNeighbours(particle *p, particle neighbours[]);

};

#endif //PROJECT_PARTICLESYSTEM_H
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
    glm::vec3 bestPos;
    glm::vec3 target;
    glm::vec3 sharkPos;
    glm::vec3 ceilPos;
    int fishAmount;
    Objects fishModel, food, ground, ceiling;
    Texture fishTexture, foodTexture, ceilingTex;

public:
    particleSystem(int amount);

    void updateSwarm();
    void render(Shader shader);
    void setTarget(glm::vec3 newTarget);
    void findNeighbours(particle *p, particle neighbours[]);

};

#endif //PROJECT_PARTICLESYSTEM_H
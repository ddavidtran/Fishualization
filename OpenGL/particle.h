//
// Created by Jakob on 2017-02-17.
//

#ifndef PROJECT_PARTICLE_H
#define PROJECT_PARTICLE_H


#include <vector>
#include <cmath>
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>

const float C1 = 0.4f;   //Global best
const float C2 = 0.2f;   //Neighbour avoid
const float C3 = 0.4f;   //Neighbour attraction
const float DT = 0.05f;
const float REPULSION_RADIUS = 0.4f;
const float SPEED_CAP = 4.0f;
const float TURN_RATE = 0.02f;

class particle {
private:
    glm::vec3 pos;
    glm::vec3 vel;

    void costFunc(glm::vec3 target, float *bestCost, glm::vec3 *newBestPos);
public:
    particle();
    ~particle(){};
    void updateParticle(particle *neighbours, glm::vec3 target, glm::vec3 bestPos, glm::vec3 *newBestPos, float *bestCost);
    float dist(particle p);
	glm::vec3 getParticlePos();
    glm::vec3 getParticleVel();
};



#endif //PROJECT_PARTICLE_H
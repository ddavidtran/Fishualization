//
// Created by Jakob on 2017-02-17.
//

#ifndef PROJECT_PARTICLE_H
#define PROJECT_PARTICLE_H


#include <vector>
#include <cmath>
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>

const float C1 = 1.5f;   //Global best
const float C2 = 0.2f;   //Neighbour avoid
const float C3 = 0.3f;   //Neighbour attraction
const float C4 = 0.1f;   //Shark avoid
const float DT = 0.05f;
const float REPULSION_RADIUS = 0.1f;
const float SPEED_CAP = 0.3f;
const float TURN_RATE = 0.04f;

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
	float getVelMagnitude();
	float distToPoint(glm::vec3 point);
	glm::vec3 getParticlePos();
    glm::vec3 getParticleVel();
};



#endif //PROJECT_PARTICLE_H
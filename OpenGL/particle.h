//
// Created by Jakob on 2017-02-17.
//

#ifndef PROJECT_PARTICLE_H
#define PROJECT_PARTICLE_H


#include <vector>
#include <cmath>
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>

struct vec3Pos{
public:
    float x,y,z;
};

const float C1 = 10;   //Global best
const float C2 = 5;  //Neighbour avoid
const float C3 = 2;   //Neighbour attraction
const float DT = 0.01;
const float REPULSION_RADIUS = 0.7;

class particle {
private:
    vec3Pos pos;
    vec3Pos vel;

    void costFunc(vec3Pos target, float* bestCost, vec3Pos* bestPos);
public:
    particle();
    ~particle(){};
    void updateParticle(particle neighbours[], vec3Pos target, const vec3Pos* bestPos, vec3Pos* newBestPos, float* bestCost);
    float dist(particle p2);
	glm::vec3 getParticlePos();
    glm::vec3 getParticleVel();
};



#endif //PROJECT_PARTICLE_H
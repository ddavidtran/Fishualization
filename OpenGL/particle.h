//
// Created by Jakob on 2017-02-17.
//

#ifndef PROJECT_PARTICLE_H
#define PROJECT_PARTICLE_H


#include <vector>
#include <cmath>

struct vec3Pos{
public:
    float x,y,z;
};

const float C1 = 0.9;   //Global best
const float C2 = 0.05;  //Neighbour avoid
const float C3 = 0.2;   //Neighbour attraction
const float DT = 1;

class particle {
private:
    vec3Pos pos;
    vec3Pos vel;

    void costFunc(vec3Pos target, float* bestCost, vec3Pos* bestPos);
public:
    particle();
    ~particle(){};
    void updateParticle(particle neighbours[], vec3Pos target, vec3Pos* bestPos, float* bestCost);
    float dist(particle p2);
};


#endif //PROJECT_PARTICLE_H
//
// Created by Jakob on 2017-02-17.
//

#include "particle.h"
#include <cmath>
#include <stdlib.h>
#include <iostream>

particle::particle() {
    pos.x = rand() % 2 + 1;
    pos.y = rand() % 2 + 1;
    pos.z = rand() % 2 + 1;

    vel.x = 0;
    vel.y = 0;
    vel.z = 0;
}

//Update position, velocity of each particle
void particle::updateParticle(particle neighbours[], vec3Pos target, vec3Pos* bestPos, float* bestCost){

    //Update velocity
    this->vel.x =   this->vel.x + C1 * (bestPos->x - this->pos.x)
                    + C2 * (this->pos.x - neighbours[1].pos.x)
                    - C3 * (this->pos.x - neighbours[2].pos.x);
    this->vel.y =   this->vel.y + C1 * (bestPos->y - this->pos.y)
                    + C2 * (this->pos.y - neighbours[1].pos.y)
                    - C3 * (this->pos.y - neighbours[2].pos.y);
    this->vel.z =   this->vel.z + C1 * (bestPos->z - this->pos.z)
                    + C2 * (this->pos.z - neighbours[1].pos.z)
                    - C3 * (this->pos.z - neighbours[2].pos.z);

    //Calculate magnitude of velocity
    float velMagnitude = sqrtf(pow(this->vel.x, 2) + pow(this->vel.y, 2) + pow(this->vel.z, 2));

    //Cap velocity
    if(velMagnitude > 1.0)
        this->vel.x /= velMagnitude; this->vel.y /= velMagnitude; this->vel.z /= velMagnitude;

    //Update position
    this->pos.x =  this->pos.x + this->vel.x * DT;
    this->pos.y =  this->pos.y + this->vel.y * DT;
    this->pos.z =  this->pos.z + this->vel.z * DT;
    //Update best cost and best position
    costFunc(target, bestCost, bestPos);

    std::cout << "POSITION: " << this->pos.x << " " << this->pos.y << " " <<this->pos.z << std::endl;
}

//Distance to another particle
float particle::dist(particle p){
    return float(sqrt(pow(p.pos.x - this->pos.x, 2) + pow(p.pos.y - this->pos.y, 2) - pow(p.pos.z - this->pos.z, 2)));
}


//Cost function
void particle::costFunc(vec3Pos target, float* bestCost, vec3Pos* bestPos)
{
    float cost = pow(target.x - this->pos.x, 2) + pow(target.y - this->pos.y, 2) - pow(target.z - this->pos.z, 2);
    if(cost < *bestCost)
        *bestCost = cost; *bestPos = this->pos;
}
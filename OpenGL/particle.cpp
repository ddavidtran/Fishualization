//
// Created by Jakob on 2017-02-17.
//

#include "particle.h"
#include <cmath>
#include <stdlib.h>
#include <iostream>

particle::particle() {
    pos.x = ((float) rand() / (RAND_MAX)) * 5.0f - 2.5f;
    pos.y = ((float) rand() / (RAND_MAX)) * 5.0f - 2.5f;
    pos.z = ((float) rand() / (RAND_MAX)) * 5.0f - 2.5f;

    vel.x = 0;
    vel.y = 0;
    vel.z = 0;
}

//Update position, velocity of each particle
void particle::updateParticle(particle neighbours[], vec3Pos target, const vec3Pos* bestPos, vec3Pos* newBestPos, float* bestCost){

    float repulsion = 0;
    float slowdown = 1;
    if(this->dist(neighbours[1]) < REPULSION_RADIUS)
    {
        repulsion = 1.0f/this->dist(neighbours[1]);
        slowdown = 0.2;
    }

    //Update velocity
    this->vel.x =   this->vel.x + (C1*((float) rand() / (RAND_MAX))*(bestPos->x - this->pos.x)
                    - C2 * ((float) rand() / (RAND_MAX)) * repulsion * (this->pos.x - neighbours[1].pos.x)
                    + C3 * ((float) rand() / (RAND_MAX)) * slowdown * (this->pos.x - neighbours[2].pos.x));
    this->vel.y =   this->vel.y + (C1 * ((float) rand() / (RAND_MAX)) * (bestPos->y - this->pos.y)
                    - C2 * ((float) rand() / (RAND_MAX)) * repulsion * 1.0f/(this->pos.y - neighbours[1].pos.y)
                    + C3 * ((float) rand() / (RAND_MAX)) * slowdown * (this->pos.y - neighbours[2].pos.y));
    this->vel.z =   this->vel.z + (C1 * ((float) rand() / (RAND_MAX)) *(bestPos->z - this->pos.z)
                    - C2 * ((float) rand() / (RAND_MAX)) * repulsion * 1.0f/(this->pos.z - neighbours[1].pos.z)
                    + C3 * ((float) rand() / (RAND_MAX)) * slowdown * (this->pos.z - neighbours[2].pos.z));

    //Calculate magnitude of velocity
    float velMagnitude = sqrtf((float)pow(this->vel.x, 2) + (float)pow(this->vel.y, 2) + (float)pow(this->vel.z, 2));

    //Cap velocity
    if(velMagnitude > 1.0)
        this->vel.x /= velMagnitude; this->vel.y /= velMagnitude; this->vel.z /= velMagnitude;

    //Update position
    this->pos.x =  this->pos.x + this->vel.x * DT;
    this->pos.y =  this->pos.y + this->vel.y * DT;
    this->pos.z =  this->pos.z + this->vel.z * DT;
    //Update best cost and best position
    costFunc(target, bestCost, newBestPos);

}

//Distance to another particle
float particle::dist(particle p){
    return float(sqrt(pow(p.pos.x - this->pos.x, 2) + pow(p.pos.y - this->pos.y, 2) - pow(p.pos.z - this->pos.z, 2)));
}

glm::vec3 particle::getParticlePos()
{	
	return glm::vec3(pos.x, pos.y, pos.z);
}


//Cost function
void particle::costFunc(vec3Pos target, float* bestCost, vec3Pos* bestPos)
{
    float cost = pow(target.x - this->pos.x, 2) + pow(target.y - this->pos.y, 2) - pow(target.z - this->pos.z, 2);
    if(cost < *bestCost)
        *bestCost = cost; *bestPos = this->pos;
}

glm::vec3 particle::getParticleVel() {
    return glm::vec3(vel.x, vel.y, vel.z);
}

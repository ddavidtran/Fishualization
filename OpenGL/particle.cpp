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

    vel = glm::vec3(0,0,0);
}

//Update position, velocity of each particle
void particle::updateParticle(particle *neighbours, glm::vec3 target, glm::vec3 bestPos, glm::vec3 *newBestPos, float *bestCost,
                              glm::vec3 sharkPos) {

    float repulsion = 0.0f;
    float slowdown = 1.0f;
    float distToNeighbour = this->dist(neighbours[1]);
    if(distToNeighbour < REPULSION_RADIUS)
    {
        repulsion = 1.0f/distToNeighbour;
        slowdown = 0.2f;
    }

    //Update velocity
    vel =   vel + (C1 * ((float) rand() / (RAND_MAX))* slowdown  * glm::vec3(bestPos - pos)
                - C2 * ((float) rand() / (RAND_MAX)) * repulsion * glm::normalize(neighbours[1].pos - pos)
                + C3 * ((float) rand() / (RAND_MAX)) * slowdown  * glm::vec3(neighbours[2].pos - pos))
                * TURN_RATE;

    //Calculate magnitude of velocity
    float velMagnitude = sqrtf((float)pow(vel.x, 2) + (float)pow(vel.y, 2) + (float)pow(vel.z, 2));

    //Cap velocity
    if(velMagnitude > SPEED_CAP)
        vel = (vel / velMagnitude) * (SPEED_CAP);

    //Update position
    pos = pos + vel * DT;
    //Update best cost and best position
    costFunc(target, bestCost, newBestPos);

}

glm::vec3 particle::getParticlePos() {
	return pos;
}


//Cost function
void particle::costFunc(glm::vec3 target, float *bestCost, glm::vec3 *newBestPos)
{
    float cost = (float)pow(target.x - this->pos.x, 2) + (float)pow(target.y - this->pos.y, 2) + (float)pow(target.z - this->pos.z, 2);
    if(cost < *bestCost){
        *bestCost = cost;
        *newBestPos = pos;
    }

}

glm::vec3 particle::getParticleVel() {
    return vel;
}

float particle::dist(particle p) {
    return sqrtf((float)pow(pos.x - p.pos.x, 2) + (float)pow(pos.y - p.pos.y, 2) + (float)pow(pos.z - p.pos.z,2));
}

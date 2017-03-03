//
// Created by Jakob on 2017-02-17.
//

#include "particleSystem.h"


particleSystem::particleSystem(int amount) {
    fishAmount = amount;
    for(int i = 0; i<fishAmount; i++) { fishSwarm.push_back(new particle()); }
    target.x = 0;
    target.y = 0;
    target.z = 0;
    bestCost = 11111111;
    bestPos = target;
    fishModel.createSphere(0.1,50);
    fishTexture.createTexture("C:\\Users\\Jakob\\Documents\\TNM085\\GitProjectFishSchool\\TNM085fish\\OpenGL\\assets\\trex.tga");
}

//Update the entire swarms movement
void particleSystem::updateSwarm() {
    bestCost = 11111111;
    for(const auto it: fishSwarm){
        vec3Pos newBestPos = bestPos;
        particle neighbours[3];
        findNeighbours(it, neighbours);
        it->updateParticle(neighbours, target, &bestPos, &newBestPos, &bestCost);
    }

}

//Find neighbours to a particle
void particleSystem::findNeighbours(particle* p, particle neighbours[]){


    float distarr[3] = {100000, 100000, 100000};

    //Update neighbour if closer particle is found
    for(auto it: fishSwarm) {
        float dist = p->dist(*it);
        if(dist < distarr[0]){
            distarr[2] = distarr[1];
            distarr[1] = distarr[0];
            distarr[0] = p->dist(*it);
            neighbours[2] = neighbours[1];
            neighbours[1] = neighbours[0];
            neighbours[0] = *it;
        }
        else if(dist < distarr[1]){
            distarr[2] = distarr[1];
            distarr[1] = p->dist(*it);
            neighbours[2] = neighbours[1];
            neighbours[1] = *it;
        }
        else if(dist < distarr[2]){
            distarr[2] = p->dist(*it);
            neighbours[2] = *it;
        }
    }
}

void particleSystem::render(Shader shader) {
    for(auto it : fishSwarm)
    {
        glm::mat4 Model = glm::translate(it->getParticlePos()) * glm::orientation(it->getParticleVel(), glm::vec3(0,1,0));
        glUniformMatrix4fv(glGetUniformLocation(shader.programID, "M"), 1, GL_FALSE, glm::value_ptr(Model));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, fishTexture.textureID);
        fishModel.render();
    }

}

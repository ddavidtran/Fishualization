//
// Created by Jakob on 2017-02-17.
//

#include "particleSystem.h"


particleSystem::particleSystem(int amount) {
    fishAmount = amount;
    for(int i = 0; i<fishAmount; i++) { fishSwarm.push_back(new particle()); }
    target = glm::vec3(0,0,0);
    sharkPos = glm::vec3(0,0,0);
    sharkPosPrev = sharkPos;
    bestCost = 11111111;
    bestPos = target;
    fishModel.readOBJ("C:\\Users\\Jakob\\Documents\\TNM085\\GitProjectFishSchool\\TNM085fish\\OpenGL\\assets\\trex.obj");
    fishTexture.createTexture("C:\\Users\\Jakob\\Documents\\TNM085\\GitProjectFishSchool\\TNM085fish\\OpenGL\\assets\\trex.tga");
    shark.readOBJ("C:\\Users\\Jakob\\Documents\\TNM085\\GitProjectFishSchool\\TNM085fish\\OpenGL\\assets\\stormtrooper.obj");
    sharkTexture.createTexture("C:\\Users\\Jakob\\Documents\\TNM085\\GitProjectFishSchool\\TNM085fish\\OpenGL\\assets\\greatwhiteshark.tga");
    food.createSphere(0.1,30);
}

//Update the entire swarms movement
void particleSystem::updateSwarm() {
    bestCost = 11111111;
    glm::vec3 newBestPos = bestPos;
    for(const auto it: fishSwarm){
        particle neighbours[3];
        findNeighbours(it, neighbours);
        it->updateParticle(neighbours, target, bestPos, &newBestPos, &bestCost, glm::vec3());
    }
    bestPos = newBestPos;
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
        glm::mat4 Model = glm::translate(it->getParticlePos()) *
                          glm::orientation(it->getParticleVel(), glm::vec3(0,1,0)) *
                          glm::rotate(45.0f, glm::vec3(1.0f, 0.0f, 2.0f)) *
                          glm::scale(glm::vec3(0.2f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(shader.programID, "M"), 1, GL_FALSE, glm::value_ptr(Model));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, fishTexture.textureID);
        fishModel.render();

        Model = glm::translate(sharkPos) *
                glm::orientation(sharkPos - sharkPosPrev, glm::vec3(0,0,0)) *
                glm::scale(glm::vec3(0.4,.4,0.4));
        glUniformMatrix4fv(glGetUniformLocation(shader.programID, "M"), 1, GL_FALSE, glm::value_ptr(Model));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sharkTexture.textureID);
        shark.render();

        Model = glm::translate(target);
        glUniformMatrix4fv(glGetUniformLocation(shader.programID, "M"), 1, GL_FALSE, glm::value_ptr(Model));
        food.render();
    }

}

void particleSystem::setTarget(glm::vec3 newTarget) {
    target = newTarget;
}

void particleSystem::setShark(glm::vec3 newSharkPos) {
    sharkPosPrev = sharkPos;
    sharkPos = newSharkPos;
}

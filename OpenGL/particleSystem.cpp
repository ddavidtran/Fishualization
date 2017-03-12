//
// Created by Jakob on 2017-02-17.
//

#include "particleSystem.h"


particleSystem::particleSystem(int amount) {
    fishAmount = amount;
    for(int i = 0; i<fishAmount; i++) { fishSwarm.push_back(new particle()); }
    target = glm::vec3(0,0,0);
    sharkPos = glm::vec3(0,0,0);
    bestCost = 11111111;
    bestPos = target;
    fishModel.readOBJ("assets\\fish.obj");
    fishTexture.createTexture("assets\\fish.tga");
    ground.readOBJ("assets\\ground.obj");
    foodTexture.createTexture("assets\\Bread.tga");
    food.readOBJ("assets\\bread.obj");
    ceiling.createBox(50.0f, 50.0f, 50.0f);
    ceilingTex.createTexture("assets\\water.tga");
    ceilPos = glm::vec3(0.0f, 6.0f, 0.0f);
}

//Update the entire swarms movement
void particleSystem::updateSwarm() {
    bestCost = 11111111;
    glm::vec3 newBestPos = bestPos;

    for(const auto it: fishSwarm){
        //if(glfwGetTime() < 10) {
            particle neighbours[3];
            findNeighbours(it, neighbours);
            it->updateParticle(neighbours, target, bestPos, &newBestPos, &bestCost); 
        //}
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
                          glm::orientation(it->getParticleVel(), glm::vec3(0,0,1)) *
                          glm::scale(glm::vec3(0.5f, 0.2f, 0.2f));
        glUniformMatrix4fv(glGetUniformLocation(shader.programID, "M"), 1, GL_FALSE, glm::value_ptr(Model));
        glUniform1i(glGetUniformLocation(shader.programID, "fishes"), true);
        glActiveTexture(GL_TEXTURE0);
        float fishspeed =  it->getVelMagnitude()/SPEED_CAP;
        glUniform1f(glGetUniformLocation(shader.programID, "fishspeed"), fishspeed);

        glBindTexture(GL_TEXTURE_2D, fishTexture.textureID);
        fishModel.render();

        glUniform1i(glGetUniformLocation(shader.programID, "fishes"), false);
        Model = glm::translate(ceilPos);
        glUniformMatrix4fv(glGetUniformLocation(shader.programID, "M"), 1, GL_FALSE, glm::value_ptr(Model));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ceilingTex.textureID);
        glUniform1i(glGetUniformLocation(shader.programID, "ceiling"), true);
        ceiling.render();

        Model = glm::translate(target) *
                glm::scale(glm::vec3(0.1, 0.1 ,0.1));
        glUniformMatrix4fv(glGetUniformLocation(shader.programID, "M"), 1, GL_FALSE, glm::value_ptr(Model));
        glBindTexture(GL_TEXTURE_2D, foodTexture.textureID);
        glUniform1i(glGetUniformLocation(shader.programID, "ceiling"), false);
        food.render();
    }

}

void particleSystem::setTarget(glm::vec3 newTarget) {
    target = newTarget;
}
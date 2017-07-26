# Fishualization - TNM085 Modelling and Simulation Course @ Linköping University
## Introduction
Swarm behavior is a widely researched area but without many conclusive answers. Different kinds of swarms have different kinds of behaviors, and in this project the purpose is to simulate the schooling and shoaling patterns of fish using a Particle swarm optimization algorithm.
Each individual fish has a set of rules which depends on its position relative to its neighbors and a universal target. To gain an insight into how the algorithm should be implemented, the first testing was done in MATLAB, which has extensive support for calculating and displaying large numbers of positions.
The final program was written using C++ and OpenGL was used to generate the graphics.
## How to run
### MATLAB-version
1. Download the MATLAB folder.
2. Run FishSchool.m in MATLAB.
### C++ version
Depends on:
* OpenGL: Install OpenGL and build it with Cmake.
1. Download the OpenGL folder.
2. Compile the project. Make sure OpenGL is installed on your computer.
3. If neccessary dependencies are installed, compile project and run main.cpp.
Controls:
Move the target with the mouse cursor. To move the target closer or further away in the scene use W and S on the keyboard.
# Authors:
- [David Tran](https://github.com/ddavidtran)
- [Anton Sterner](https://github.com/antonsterner)
- [Jakob Bertlin](https://github.com/Jackbob)
- Rasmus Ståhl

As part of the TNM085 Project course @ Linköping University.
# Demo:
<a href="http://www.youtube.com/watch?feature=player_embedded&v=H6QdCxFZtf8
" target="_blank"><img src="http://img.youtube.com/vi/H6QdCxFZtf8/0.jpg" 
alt="Fishualization" width="240" height="180" border="10" /></a>

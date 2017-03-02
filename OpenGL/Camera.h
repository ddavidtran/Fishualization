#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <math.h>         // Used only for sin() and cos() functions

#include <GL/glew.h>      // Include OpenGL Framework library for the GLFW_PRESS constant only!
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
protected:
	// Camera position
	glm::vec3 position;

	//Camera view direction
	glm::vec3 viewDirection;

	// Camera rotation
	glm::vec3 rotation;

	// Camera movement speed. When we call the move() function on a camera, it moves using these speeds
	glm::vec3 speed;

	float movementSpeedFactor; // Controls how fast the camera moves
	float pitchSensitivity;    // Controls how sensitive mouse movements affect looking up and down
	float yawSensitivity;      // Controls how sensitive mouse movements affect looking left and right

								// Window size in pixels and where the midpoint of it falls
	int windowWidth;
	int windowHeight;
	int windowMidX;
	int windowMidY;

	// Method to set some reasonable default values. For internal use by the class only.
	void initCamera(glm::vec3 pos);

public:
	static const double TO_RADS; // The value of 1 degree in radians

	// Holding any keys down?
	bool holdingForward = false;
	bool holdingBackward = false;
	bool holdingLeftStrafe = false;
	bool holdingRightStrafe = false;

	// Constructor
	Camera(int windowWidth, int windowHeight, glm::vec3 pos);

	// Destructor
	~Camera();

	// Mouse movement handler to look around
	void handleMouseMove( int mouseX, int mouseY);

	// Method to convert an angle in degress to radians
	const double toRads(const double &angleInDegrees) const;

	// Method to move the camera based on the current direction
	void move(float deltaTime);

	// --------------------------------- Inline methods ----------------------------------------------

	// Setters to allow for change of vertical (pitch) and horizontal (yaw) mouse movement sensitivity
	float getPitchSensitivity() { return pitchSensitivity; }
	void  setPitchSensitivity(float value) { pitchSensitivity = value; }
	float getYawSensitivity() { return yawSensitivity; }
	void  setYawSensitivity(float value) { yawSensitivity = value; }

	// Position getters
	glm::vec3 getPosition() const { return position; }
	double getXPos()           const { return position.x; }
	double getYPos()           const { return position.y; }
	double getZPos()           const { return position.z; }

	// Rotation getters
	glm::vec3 getRotation() const { return rotation; }
	double getXRot()           const { return rotation.x; }
	double getYRot()           const { return rotation.y; }
	double getZRot()           const { return rotation.z; }

	//viewDirection getter
	glm::vec3 getViewDirection() const { return viewDirection; }

	void handleKeypress( int theKey, int theAction);
};

#endif // CAMERA_H
#include "Camera.h"

const double Camera::TO_RADS = 3.141592654 / 180.0; // The value of 1 degree in radians

Camera::Camera(int theWindowWidth, int theWindowHeight, glm::vec3 pos)
{
	initCamera(pos);

	windowWidth = theWindowWidth;
	windowHeight = theWindowHeight;

	// Calculate the middle of the window
	windowMidX = windowWidth / 2;
	windowMidY = windowHeight / 2;
}

Camera::~Camera()
{
	// Nothing to do here - we don't need to free memory as all member variables
	// were declared on the stack.
}

void Camera::initCamera(glm::vec3 pos)
{
	// Set position, rotation and speed values to zero
	position = pos;
	rotation = glm::vec3(0.0f);
	speed = glm::vec3(0.0f);

	// How fast we move (higher values mean we move and strafe faster)
	movementSpeedFactor = 5.0;

	pitchSensitivity = 0.003; // How sensitive mouse movements affect looking up and down
	yawSensitivity = 0.003; // How sensitive mouse movements affect looking left and right
	mouseSensitivity = 0.001; // How sensitive mouseX and mouseY is to mouse movements

						  // To begin with, we aren't holding down any keys
	holdingForward = false;
	holdingBackward = false;
	holdingLeftStrafe = false;
	holdingRightStrafe = false;
}

// Function to convert degrees to radians
const double Camera::toRads(const double &theAngleInDegrees) const
{
	return theAngleInDegrees * TO_RADS;
}

// Function to deal with mouse position changes
void Camera::handleMouseMove( int mouseX, int mouseY)
{
	MouseX = mouseX * mouseSensitivity;
	MouseY = -mouseY * mouseSensitivity;

	// Calculate our horizontal and vertical mouse movement from middle of the window
	double horizMovement = (mouseX) * yawSensitivity;
	double vertMovement = (mouseY) * pitchSensitivity;

	// Apply the mouse movement to our rotation vector. The vertical (look up and down)
	// movement is applied on the X axis, and the horizontal (look left and right)
	// movement is applied on the Y Axis
	rotation.x = vertMovement;
	rotation.y = horizMovement;

	double sinXRot = sin((rotation.x));
	double cosXRot = cos((rotation.x));

	double sinYRot = sin((rotation.y));
	double cosYRot = cos((rotation.y));

	double pitchLimitFactor = cosXRot;

	viewDirection.x = (-sinYRot * pitchLimitFactor);
	viewDirection.y = (sinXRot);
	viewDirection.z = (cosYRot * pitchLimitFactor);

	// Limit loking up to vertically up
	if (rotation.x < -90)
	{
		rotation.x = (-90);
	}

	// Limit looking down to vertically down
	if (rotation.x > 90)
	{
		rotation.x = (90);
	}

	// If you prefer to keep the angles in the range -180 to +180 use this code
	// and comment out the 0 to 360 code below.

	// Looking left and right - keep angles in the range 0.0 to 360.0
	// 0 degrees is looking directly down the negative Z axis "North", 90 degrees is "East", 180 degrees is "South", 270 degrees is "West"
	// We can also do this so that our 360 degrees goes -180 through +180 and it works the same, but it's probably best to keep our
	// range to 0 through 360 instead of -180 through +180.


	// Reset the mouse position to the centre of the window each frame
}

// Callback function to handle keypresses
void Camera::handleKeypress( int theKey, int theAction)
{
	// If a key is pressed, toggle the relevant key-press flag
	if (theAction == GLFW_PRESS)
	{
		switch (theKey)
		{
		case GLFW_KEY_W:
			holdingForward = true;
			break;
		case GLFW_KEY_S:
			holdingBackward = true;
			break;
		case GLFW_KEY_A:
			holdingLeftStrafe = true;
			break;
		case GLFW_KEY_D:
			holdingRightStrafe = true;
			break;
		default:
			// Do nothing...
			break;
		}
	}
	else if (theAction == GLFW_RELEASE)
	 // If a key is released, toggle the relevant key-release flag
	{
		switch (theKey)
		{
		case GLFW_KEY_W:
			holdingForward = false;
			break;
		case GLFW_KEY_S:
			holdingBackward = false;
			break;
		case GLFW_KEY_A:
			holdingLeftStrafe = false;
			break;
		case GLFW_KEY_D:
			holdingRightStrafe = false;
			break;
		default:
			// Do nothing...
			break;
		}
	}
}

// Function to calculate which direction we need to move the camera and by what amount
void Camera::move(float deltaTime)
{
	// Vector to break up our movement into components along the X, Y and Z axis
	glm::vec3 movement;

	// Get the sine and cosine of our X and Y axis rotation
	double sinXRot = sin((rotation.x));
	double cosXRot = cos((rotation.x));

	double sinYRot = sin((rotation.y));
	double cosYRot = cos((rotation.y));

	double pitchLimitFactor = cosXRot; // This cancels out moving on the Z axis when we're looking up or down

	if (holdingForward)
	{
		movement.x  = (-sinYRot * pitchLimitFactor);
		movement.y = (sinXRot);
		movement.z = (cosYRot * pitchLimitFactor);
	}

	if (holdingBackward)
	{
		movement.x  = (sinYRot * pitchLimitFactor);
		movement.y = (-sinXRot);
		movement.z = (-cosYRot * pitchLimitFactor);
	}

	if (holdingLeftStrafe)
	{
		movement.x  = (cosYRot);
		movement.z = (sinYRot);
	}

	if (holdingRightStrafe)
	{
		movement.x  = (-cosYRot);
		movement.z = (-sinYRot);
	}

	//Normalise our movement vector
	//movement = glm::normalize(movement);

	// Calculate our value to keep the movement the same speed regardless of the framerate...
	double framerateIndependentFactor = movementSpeedFactor * deltaTime;

	// .. and then apply it to our movement vector.
	movement *= framerateIndependentFactor;

	// Finally, apply the movement to our position
	position += movement;
}
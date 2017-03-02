#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "particleSystem.h"
#include "Shader.hpp"
#include "Camera.h"

#ifndef M_PI
#define M_PI (3.141592653589793)
#endif

// In MacOS X, tell GLFW to include the modern OpenGL headers.
// Windows does not want this, so we make this Mac-only.
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif

// In Linux, tell GLFW to include the modern OpenGL functions.
// Windows does not want this, so we make this Linux-only.
#ifdef __linux__
#define GL_GLEXT_PROTOTYPES
#endif

// Windows installations usually lack an up-to-date OpenGL extension header,
// so make sure to supply your own, or at least make sure it's of a recent date.
#ifdef __WIN32__
#include <GL/glext.h>
#endif

int SCR_HEIGHT = 900;
int SCR_WIDTH = 1400;

Camera camera(SCR_HEIGHT, SCR_WIDTH, glm::vec3(5.0f, -6.0f, 5.0f));

Shader myShader, depthShader;

void mouseMoveWrapper(GLFWwindow* window, double mouseX, double mouseY)
{
    camera.handleMouseMove(mouseX, mouseY);
}
void keypressWrapper(GLFWwindow* window, int theKey, int scancode, int theAction, int mods)
{
    camera.handleKeypress(theKey, theAction);
}

GLFWwindow* Initialize()
{
    // Initialization
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return NULL;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

// Open a window and create its OpenGL context
    // GLFWwindow* window; // (In the accompanying source code, this variable is global)
    GLFWwindow* window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "Fish Simulation", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return NULL;
    }

    // Specify the function which should execute when a key is pressed or released
    glfwSetKeyCallback(window, keypressWrapper);
    // Specify the function which should execute when the mouse is moved
    glfwSetCursorPosCallback(window, mouseMoveWrapper);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return window;
}


int main() {

    GLFWwindow* window = Initialize();
    if(window == NULL)
        return 0;

    glfwSwapInterval(0);
    myShader.createShader("vertexshader.glsl", "fragmentshader.glsl");
    depthShader.createShader("depthVertex.glsl", "depthFragment.glsl");
    glUseProgram(myShader.programID);

    GLint location_time, location_M, location_tex, location_lightView, location_lightSpaceMatrix
    ,location_lightPos, location_shadowMap, location_viewPos, location_View;
    float currentTime;
    glm::vec3 viewPos;

    location_M = glGetUniformLocation(myShader.programID, "M");
    location_time = glGetUniformLocation(myShader.programID, "time");
    location_lightSpaceMatrix = glGetUniformLocation(myShader.programID, "lightSpaceMatrix");
    location_lightPos = glGetUniformLocation(myShader.programID, "lightPos");
    location_viewPos = glGetUniformLocation(myShader.programID, "viewPos");
    location_View = glGetUniformLocation(myShader.programID, "V");

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Set texture samples
    glUniform1i(glGetUniformLocation(myShader.programID, "tex"), 0);
    glUniform1i(glGetUniformLocation(myShader.programID, "shadowMap"), 1);

    // Create matrices for Projection, Model and View
    float fov=45.0f;
    glm::mat4 Projection = glm::perspective(fov, (GLfloat) SCR_HEIGHT / (GLfloat) SCR_WIDTH, 0.1f, 10000.0f);

    float angle1=fov/2.0;
    float angle2=180 - (90 + angle1);
    float Z = 0.5 * SCR_HEIGHT * sin(glm::radians(angle2))/sin(glm::radians(angle1));
    glm::mat4 View = glm::lookAt(
            glm::vec3(SCR_WIDTH/2, SCR_WIDTH/2, Z), // camera position
            glm::vec3(SCR_WIDTH/2, SCR_WIDTH/2, 0), // look at origin
            glm::vec3(0, 1, 0)  // Head is up
    );

    glm::mat4 Model = glm::mat4(1.0f);

    glm::mat4 MVP = Projection * View * Model;


    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    particleSystem* swarm = new particleSystem(10);


    do{
        // Draw nothing, see you in tutorial 2 !
        swarm->updateSwarm();
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    return 0;
}
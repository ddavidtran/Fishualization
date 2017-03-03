#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "particleSystem.h"
#include "Shader.hpp"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Utilities.hpp"
#include <glm/gtx/transform.hpp>

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

Shader myShader;

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

// Open a window and create its OpenGL context
    // GLFWwindow* window; // (In the accompanying source code, this variable is global)
    GLFWwindow* window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "Fish Simulation", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=GL_TRUE; // Needed in core profile
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

    glewExperimental = GL_TRUE;
    glewInit();
    glfwInit();

    GLFWwindow* window = Initialize();
    if(window == NULL)
        return 0;

    Objects test;
    test.createSphere(1.0f, 50);
    Texture testTex;
    testTex.createTexture("C:\\Users\\Jakob\\Documents\\TNM085\\GitProjectFishSchool\\TNM085fish\\OpenGL\\assets\\trex.tga");

    glfwSwapInterval(0);
    myShader.createShader("vertexshader.glsl", "fragmentshader.glsl");
    glUseProgram(myShader.programID);

    GLint location_M, location_P, location_V;

    location_M = glGetUniformLocation(myShader.programID, "M");
    location_V = glGetUniformLocation(myShader.programID, "V");
    location_P = glGetUniformLocation(myShader.programID, "P");

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Set texture samples
    glUniform1i(glGetUniformLocation(myShader.programID, "tex"), 0);

    // Create matrices for Projection, Model and View
    float fov=45.0f;
    glm::mat4 Projection = glm::perspective(fov, (GLfloat) SCR_HEIGHT / (GLfloat) SCR_WIDTH, 0.1f, 10000.0f);

    float angle1=fov/2.0;
    float angle2=180 - (90 + angle1);
    float Z = 0.5 * SCR_HEIGHT * sin(glm::radians(angle2))/sin(glm::radians(angle1));
    glm::mat4 View = glm::lookAt(
            glm::vec3(0,0,5), // camera position
            glm::vec3(0, 0, 0), // look at origin
            glm::vec3(0, 1, 0)  // Head is up
    );

    glm::mat4 Model = glm::mat4();


    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    particleSystem* swarm = new particleSystem(10);

    /*********************************/
    /*          RENDER               */
    /*********************************/
    do{

        double x = camera.getXPos();
        double y = -5.5;
        double z = camera.getZPos();
        glm::vec3 lightPos = glm::vec3(1.0, 1.0, 1.0);

        //Poll and process events
        glfwPollEvents();
        Utilities::displayFPS(window);

        swarm->updateSwarm();

        //swarm->render();
        glEnable(GL_COLOR_MATERIAL);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glUniformMatrix4fv(location_M, 1, GL_FALSE, glm::value_ptr(Model));
        glUniformMatrix4fv(location_V, 1, GL_FALSE, glm::value_ptr(View));
        glUniformMatrix4fv(location_P, 1, GL_FALSE, glm::value_ptr(Projection));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, testTex.textureID);
        test.render();

        // Swap buffers
        glfwSwapBuffers(window);

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    return 0;
}
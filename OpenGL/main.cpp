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
#include <unistd.h>

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

int SCR_HEIGHT = 1800;
int SCR_WIDTH = 2500;

Camera camera(SCR_HEIGHT, SCR_WIDTH, glm::vec3(0.0f, 0.0f, 0.0f));

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

    GLFWwindow* window = Initialize();
    if(window == NULL)
        return 0;

    glewExperimental = GL_TRUE;
    glewInit();
    glfwInit();

    glfwSwapInterval(1);
    myShader.createShader("vertexshader.glsl", "fragmentshader.glsl");
    glUseProgram(myShader.programID);

    GLint location_M, location_P, location_V, location_lightPos, location_viewPos;

    location_M = glGetUniformLocation(myShader.programID, "M");
    location_V = glGetUniformLocation(myShader.programID, "V");
    location_P = glGetUniformLocation(myShader.programID, "P");
    location_viewPos = glGetUniformLocation(myShader.programID, "viewPos");
    location_lightPos = glGetUniformLocation(myShader.programID, "lightPos");

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);


    // Set samples
    glUniform1i(glGetUniformLocation(myShader.programID, "tex"), 0);

    glm::vec3 viewPos = glm::vec3(0.0f,0.0f,10.0f);
    glm::vec3 lightPos = glm::vec3(0.0f,3.0f,0.0f);

    // Create matrices for Projection, Model and View
    float fov=45.0f;
    glm::mat4 Projection = glm::perspective(fov, (GLfloat) SCR_HEIGHT / (GLfloat) SCR_WIDTH, 0.1f, 1000.0f);
    glm::mat4 Model = glm::mat4();


    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    particleSystem* swarm = new particleSystem(70);

    bool sharkControl = false;
    glm::vec3 foodPos;
    glm::vec3 sharkPos;

    /*********************************/
    /*          RENDER               */
    /*********************************/
    do{
        camera.move(DT);
        if(glfwGetKey(window, GLFW_KEY_E ) == GLFW_PRESS)
        {
            if(sharkControl)
                sharkControl = false;
            else
                sharkControl = true;
        }
        if(sharkControl) {
            sharkPos = glm::vec3(camera.getMouseX(), camera.getMouseY(), camera.getZPos());
            std::cout << sharkPos.x << " " << sharkPos.y << std::endl;
        }
        else {
            foodPos = glm::vec3(camera.getMouseX(), camera.getMouseY(), camera.getZPos());
            std::cout << foodPos.x << " " << foodPos.y << std::endl;
        }

        glm::mat4 View = glm::lookAt(
                viewPos, // camera position
                glm::vec3(0, 0, 0), // look at origin
                glm::vec3(0, 1, 0)  // Head is up
        );

        //lightPos = foodPos + glm::vec3(0.0,3.0,0.0);

        glUniformMatrix4fv(location_viewPos, 1, GL_FALSE, glm::value_ptr(viewPos));
        glUniformMatrix4fv(location_lightPos, 1, GL_FALSE, glm::value_ptr(lightPos));
        glUniformMatrix4fv(location_V, 1, GL_FALSE, glm::value_ptr(View));
        glUniformMatrix4fv(location_P, 1, GL_FALSE, glm::value_ptr(Projection));
        glUniform1f(glGetUniformLocation(myShader.programID, "time"), glfwGetTime());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        swarm->setShark(sharkPos);
        swarm->setTarget(foodPos);
        swarm->updateSwarm();
        swarm->render(myShader);

        //Poll and process events
        glfwPollEvents();
        Utilities::displayFPS(window);

        // Swap buffers
        glfwSwapBuffers(window);

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    return 0;
}
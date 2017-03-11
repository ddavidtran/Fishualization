/* Utilities.hpp */
/*
 * Some useful functions for the course TNM046
 * (Extension loading stuff for Windows and a frame timer)
 * Usage: call loadExtensions() after getting an OpenGL context.
 * Call displayFPS() once per frame to show the rendering speed.
 * Author: Stefan Gustavson 2013-2014 (stefan.gustavson@liu.se)
 * This code is in the public domain.
 */
#define GL_GLEXT_PROTOTYPES

#ifndef UTILITIES_HPP // Avoid including this header twice
#define UTILITIES_HPP

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <cstdio>  // For console messages


namespace Utilities {
/*
 * printError() - Signal an error.
 * Simple printf() to console for portability.
 */
void printError(const char *errtype, const char *errmsg);

/*
 * loadExtensions() - Load OpenGL extensions for anything above OpenGL
 * version 1.1. (This is a requirement only on Windows, so on other
 * platforms, this function does nothing.)
 */

/*
 * displayFPS() - Calculate, display and return frame rate statistics.
 * Called every frame, but statistics are updated only once per second.
 * The time per frame is a better measure of performance than the
 * number of frames per second, so both are displayed.
 *
 * NOTE: This function doesn't work properly if you call it for multiple
 * windows. Call it only for one window, and only once for each frame.
 */
double displayFPS(GLFWwindow *window);

}

#endif // UTILITIES_HPP

cmake_minimum_required(VERSION 3.1)

set(GLFW_SOURCE_DIR "external/glfw")
set(GLM_SOURCE_DIR "external/glm")
set(GLEW_SOURCE_DIR "external/glew")

# Building only the GLFW lib
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")
set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11


add_subdirectory(${GLFW_SOURCE_DIR} ${GLEW_SOURCE_DIR})

include_directories(${GLFW_SOURCE_DIR}/include
                    ${GLFW_SOURCE_DIR}/deps
                    ${GLM_SOURCE_DIR}
                    ${GLEW_SOURCE_DIR}/include)

add_library(glew STATIC
  ${GLEW_SOURCE_DIR}/src/glew.c
  ${GLEW_SOURCE_DIR}/include
)

target_link_libraries(glew ${GLFW_LIBRARIES})

add_definitions(
  -DGLEW_STATIC
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")



if (APPLE)
    set(APP_NAME "OpenGLBoilerplate")

    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/icon.icns)
        add_executable(${APP_NAME} MACOSX_BUNDLE main.cpp icon.icns)
        set_source_files_properties("icon.icns" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
        set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_ICON_FILE ${CMAKE_CURRENT_SOURCE_DIR}/icon.icns)
    else ()

        add_executable(${APP_NAME} MACOSX_BUNDLE main.cpp particleSystem.cpp particleSystem.h particle.cpp particle.h)
    endif ()

#    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/app.plist.in)

    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME ${APP_NAME})
    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0")
    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING "1.0")
    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_STRING "OpenGL boilerplate example app")
else()
    set(APP_NAME "opengl-boilerplate")
    add_executable(${APP_NAME} main.cpp particleSystem.cpp particleSystem.h particle.cpp particle.h Objects.cpp Shader.cpp Texture.cpp Utilities.cpp Camera.cpp)
endif()


target_link_libraries(${APP_NAME} glfw ${GLFW_LIBRARIES} glew)



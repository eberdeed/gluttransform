############################################################
#   The CMake File for OpenGLSDL2.  It provides for
#   the following libraries:  Boost, GLM, GL, GLEW,
#   stdc++, freeimageplus, SDL2, assimp and pthread.
#   Created by Edward C. Eberle <eberdeed@ebedeed.net>
#   March 2020 San Diego California USA
############################################################
cmake_minimum_required(VERSION 3.12)
if(POLICY CMP0015)
  cmake_policy(SET CMP0015 NEW)
endif()
project(gluttransform)
add_executable(gluttransform gluttransform.cpp skybox.cpp
createimage.cpp shader.cpp indexedcube.cpp camera.cpp threadcreate.cpp rotateblock.cpp moveblock.cpp)
add_definitions(-g -fPIC -std=c++17 -pthread)
include_directories(/usr/include /usr/include/glm /usr/include/GL
/usr/include/boost /usr/include/SDL2)
link_directories(/usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib)
target_link_libraries(gluttransform stdc++ GL glut GLEW freeimage freeimageplus sfml-audio sfml-system boost_filesystem boost_system pthread X11)
install(TARGETS gluttransform DESTINATION /usr/bin)

/**************************************************************
 * CommonHeader:  A header file to reduce repetition of #define
 * and #include statements.
 * Edward C. Eberle <eberdeed@eberdeed.net>
 * August 2020 San Diego, California USA
 *************************************************************/
#ifndef COMMONHEADER_H
#define COMMONHEADER_H

// GLEW The OpenGL library manager
#define GLEW_STATIC
#include <glew.h>
// GLM The OpenGL math library
#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/quaternion.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/matrix_interpolation.hpp>
#include <gtc/matrix_access.hpp> 
#include <gtx/euler_angles.hpp>
// GLUT aka Freeglut.
#include <glut.h>
#include <GL/freeglut.h>
// Simple Fast Multimedia Library SFML
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.h>
#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
// Free Image Plus
#include <FreeImagePlus.h>
// CPP Library
#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <sstream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <cstddef>
// Boost
#include <filesystem.hpp>
// X11
#include <X11/Xlib.h>


using namespace std;
using namespace glm;
using namespace boost::filesystem;

//! A vertex structure.
struct Particle
{
   float position[3];
   float texcoord[2];
};

//! A thread information structure.
struct ThreadInfo {    
    //! ID to access the pthread with.
    pthread_t   threadID;        
    //! ID returned by pthread_create()
    int         threadNum;       
    //! Application-defined thread name.
    string      threadName;      
    //! Set whether the thread is detached or joinable.  
    bool        detached = true;
    //! Set the stack size for each thread.
    int         stackSize  = 50000;
    
};

#endif // COMMONHEADER_H

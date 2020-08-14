/******************************************************************
 * GlutTransform:  A class to encapsulate the creation of a Glut 
 * window used for the drawing of an OpenGL scene that uses
 * transformation feedback to animate the objects.
 * Edward Charles Eberle <eberdeed@eberdeed.net>
 * August 2020 San Diego, California USA
******************************************************************/

#ifndef GLUTTRANSFORM_H
#define GLUTTRANSFORM_H

#include "commonheader.h"
#include "camera.h"
#include "threadcreate.h"
#include "skybox.h"
#include "moveblock.h"
#include "rotateblock.h"

/** \class GlutTransform A class to encapsulate the creation of a Glut 
 * window used for the drawing of an OpenGL scene that 
 * uses transformation feedback to animate the objects.
 */
class GlutTransform
{
public:
    //! \brief Echo the creation of the class and initialize the program.
    GlutTransform();
    //! \brief Destroy the program's variables.
    ~GlutTransform();

protected:
    /* Functions */
    //! \brief Create the window and start the sound.
    static void initProg();
    //! \brief Draw the scene.
    static void events();
    //! \brief Handle keyboard input.
    static void processInput(unsigned char key, int x, int y);
    //! \brief Handle keys that do not have ASCII code definitions.
    static void specialKeys(int key, int x, int y);
    //! \brief Handle mouse motion.
    static void mouseMove(int x, int y);
    /** \brief Hand mouse clicks, used to change from a 
     * rotation object to a translation object.
     */
    static void mouseClick(int button, int state, int x, int y);
    //! \brief Resize the window and OpenGL viewport.
	static void windowEvent(int width, int height);
    //! \brief Music creation function.
    static void* soundMaker(void *arg);
    //! \brief A debug function to print affine matrices.
    static void printMat4(mat4 val);

};

/* Variables */
//! The sky box.
SkyBox *skybox;
//! The transformation feedback translation cube.
MoveBlock *moveblock;
//! The transformation feedback rotation cube.
RotateBlock *rotateblock;
//! The Camera class defining the user's view in the scene.
Camera *camera;
//! The pthread to put the playing music in.
ThreadCreate *sndthread;
//! The vector with the thread information.
vector<ThreadInfo>threadInfo;
//! The affine transformations defining view and perspective.
mat4 orientation = mat4(1.0f), model, view, projection;
//! Move the translation object.
vec3 movement = vec3(0.0f);
//! The sound buffer class from SFML.
sf::SoundBuffer *buffer;
//! The sound class from SFML.
sf::Sound *sound;
//! The camera position.
vec3 viewPos;
//! Timing for the animation and the camera.
chrono::system_clock::time_point intbegin, intend;
//! The screen width at startup.
const unsigned int SCR_WIDTH = 1000;
//! The screen height at startup.
const unsigned int SCR_HEIGHT = 700;
int scrwidth = SCR_WIDTH, scrheight = SCR_HEIGHT;
//! The mouse position.
float lastX = 0, lastY = 0, delta = 0;
const float mouseSpeed = 0.005;
const float onedegree = acos(-1.0f) / 180.0f;
const float pi180 = acos(-1.0f);
const float boxsize = 3.0f;
/** Booleans for: The first time a mouse is used.
 * Full screen toggle.  Debugging.
 */
bool firstMouse = true, fullScreen = false, debug1 = false, switcher = true;
//! Xlib objects to obtain display size.
_XDisplay* d;
Screen*  s;
//! The file location of the music.
string soundFile = "/usr/share/openglresources/sound/gamelan1b.wav";
//! The name of the sound thread.
string arg = "soundout";
//! \brief Initialize glut and instantiate the class.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    GlutTransform transform;
    glutMainLoop();
    return 0;
}
#endif // GLUTTRANSFORM_H

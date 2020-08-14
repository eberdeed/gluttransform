/**************************************************************
 * SkyBox:  A class to encapsulate the creation and use of 
 * a set of a sky box images.  
 * Edward C. Eberle <eberdeed@eberdeed.net>
 * August 2020 San Diego, California USA
 ***********************************************************/


#ifndef SKYBOX_H
#define SKYBOX_H
#include "commonheader.h"
#include "createimage.h"
#include "shader.h"
#include "indexedcube.h"

/** \class SkyBox:  A class to encapsulate the creation and use of 
 * a set of a sky box images.
 */
class SkyBox
{
public:
    /** \brief Echo the creation of the class and initialize
     * the sky box data.
     */
    SkyBox();
    /** \brief Echo the destruction of the class and free up 
     * any memory used.
     */
    ~SkyBox();
    /** \brief Create the sky box vertices create the background
     * texture and create a cube texture object containing the
     * sides of the sky box/
     */
    void initSkyBox();
    /** \brief draw the skybox using the model, view, perspective
     * affine transform to allow for camera motion.
     */
    void drawSkyBox(mat4 model, mat4 view, mat4 perspective);
    //! \brief Display the cube data.
    void debug();
    /* Variables */
    //! Creates the texture objects from provided images.
    CreateImage *image;
    //! Creates the cube to hang the sky box on.
    IndexedCube *cuby;
    //! Shaders to draw the sky box with.
    Shader *skyboxShader;
    //! Vertex data pointer.
    float *skycube;
    //! Texture object, vertex object and buffer object handles.
    unsigned int skyboxTex, skyboxVAO, skyboxVBO;
    //! Images to create the sky box with.
    string skybox[6] =
    {
        "/usr/share/openglresources/images/skybox1/right.tga",
        "/usr/share/openglresources/images/skybox1/left.tga",
        "/usr/share/openglresources/images/skybox1/up.tga",
        "/usr/share/openglresources/images/skybox1/down.tga",
        "/usr/share/openglresources/images/skybox1/front.tga",
        "/usr/share/openglresources/images/skybox1/back.tga"
    };
    //! Debug data to read from the console.
    bool debug1 = false;
};

#endif // SKYBOX_H

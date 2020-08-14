/**************************************************************
 * RotateBlock:  A class that uses OpenGL Transformation
 * Feedback to rotate and scale an object and draw it 
 * to the screen.
 * Create August 2020 by Edward C. Eberle <eberdeed@eberdeed.net>
 * San Diego, California USA
 *************************************************************/

#ifndef ROTATEBLOCK_H
#define ROTATEBLOCK_H

#define NUM_VERTICES   36
#define TIME_INTERVAL  360.0f
#define ATTRIBUTE_POSITION      0
#define ATTRIBUTE_TEXCOORD      1

#include "commonheader.h"
#include "createimage.h"
#include "shader.h"
#include "indexedcube.h"

/** \class RotateBlock:  A class that uses OpenGL Transformation
 * Feedback to rotate and scale an object and draw it 
 * to the screen.
 */
class RotateBlock  
{
public:
    /** \brief Echo the construction of the class and initialize
    * all the data.
    */
    RotateBlock();
    /** \brief Echo the destruction of the class and free
    * up any memory used.
    */
    ~RotateBlock();
    //! \brief Initialize the transformation feedback data.
    void initEmitParticles();
    //! \brief Initialize the shader, buffers and textures.
    int init();
    //! \brief Defines the buffer emitted by the shader.
    void setupVertexAttributes(GLuint vboID);
    //! \brief Initialize the vertex data.
    void initParticles();
    //! \brief Update time-based variables and emit the buffer.
    void update(mat4 orientation, float deltaTime);
    /** \brief Draw a triangle using the shader 
    * pair created in init().
    */
    void draw(int width, int height, mat4 model, mat4 view, mat4 projection);
    //! \brief Debug the vertex data.
    void debug();
    //! \brief Debug function for displaying an affine matrix.
    void printMat4(mat4 val);
    //! Shader to alter the data.
    Shader *emitShader;
    //! Drawing shader.
    Shader *drawShader;
    //! Cube creation.
    IndexedCube *cuby;
    //! Vertex pointer.
    float *vertices;
    //! Create texture objects for display.
    CreateImage *image;
    // Texture handles
    GLuint background, sides;
    //! Orientation for rotation.
    mat4 orientation;
    //! Particle vertex data
    const vec3 movement = vec3(0.0f);
    // Particle vertex data
    Particle particleData[NUM_VERTICES];
    //! Vertex buffer objects.
    GLuint particleVBOs[2];

    /** Index into particleVBOs (0 or 1) as to which is the source.
     * Ping-pong between the two VBOs using the emit shader to
     * change the data.
     */
    GLuint curSrcIndex;
    // Current time
    float systime, sign;
    //! Degree -> Radian conversion.
    const float onedegree = acos(-1.0f) / 180.0f;
    /** Sync object to synchronize the transform feedback 
     * results and the draw.
     */
    GLsync emitSync;
    /** Names for the data for the transformation feedback.
     */
    const char *feedbackVaryings[2] =
    {
        "v_position",
        "v_texcoord"
    };
    //! Debug data flag.
    bool debug1 = false;
    //! Vector to hold the images for the sides of the cube.
    vector<string>sidedata;
    //! Names of the image files.
    string sidefiles[6] = 
    {
        "/usr/share/openglresources/images/abstract.png",
        "/usr/share/openglresources/images/awesomeface.png",
        "/usr/share/openglresources/images/panda.png",
        "/usr/share/openglresources/images/grapes.png",
        "/usr/share/openglresources/images/mexican.png",
        "/usr/share/openglresources/images/palette.png"
    };
};

#endif // ROTATEBLOCK_H

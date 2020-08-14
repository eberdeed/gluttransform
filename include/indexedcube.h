/**************************************************************
 * IndexedCube:  A class that creates a cube both for 
 * indexed vertex drawing and for regular vertex drawing.
 * Create August 2020 by Edward C. Eberle <eberdeed@eberdeed.net>
 * San Diego, California USA
 *************************************************************/

#ifndef INDEXEDCUBE_H
#define INDEXEDCUBE_H
#define NUM_VERTICES 36
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>

using namespace std;
using namespace glm;
/** \class IndexedCube A class that creates a cube both for 
 * indexed vertex drawing and for regular vertex drawing.
 */
class IndexedCube
{
public:
    /** \brief Echo the creation of the class and generate 
     * all the data.
     */
    IndexedCube();

    /** \brief Echo the destruction of the class and free
     * up any used memory.
     */
    ~IndexedCube();
    /** \brief generate the regular (unindexed) cube.
     * scale:  The scale of the cube. You are scaling a 0.5 cube.
     * colored:  Produces colored vertices.
     * normaled:  Produces normals.
     * textured:  Produces texture coordinates.
     */
    float *genCube(float scale, bool colored, bool normaled, bool textured);
    //! \brief Generate all the data for later use.
    void genMatrices();
    /** \brief Generate the texture coordinates.
     * normal:  The cube's normal.
     * triangle:  The current triangle the texture coordinates
     * are being generated for.
     */
    vec2 genTexture(vec3 normal, vec3 triangle);
    /* The Following functions produce indexed data. */
    //! \brief Get the indexed cube vertices.
    float *getCube();
    //! \brief Get the indexed cube colors.
    float *getColor();
    //! \brief Get the indexed cube normals.
    float *getNormals();
    //! \brief Get the indexed cube texture coordinates.
    float *getTexCoords();
    //! \brief Get the indices.
    unsigned int *getIndices();
    //! \brief The pointer to the unindexed cube.
    float *cubeptr = nullptr;
    /* The calculated information for the unindexed cube. */
    float calcTex[72];
    float calcColor[108];
    float calcNorm[108];
    float calcCube[108];
    //! The eight points defining the cube.
    vec3 cube[8] = {
    vec3(0.5f,  0.5f,  0.5f), //0
    vec3(-0.5f,  0.5f,  0.5f), //1
    vec3(-0.5f, -0.5f,  0.5f), //2
    vec3(0.5f, -0.5f,  0.5f), //3
    vec3(0.5f, -0.5f, -0.5f), //4
    vec3(0.5f,  0.5f, -0.5f), //5
    vec3(-0.5f,  0.5f, -0.5f), //6
    vec3(-0.5f, -0.5f, -0.5f)  //7
    };
    //! The six normals for the six directions.
    vec3 normals[6] = {
         vec3( 1.0f,   0.0f,  0.0f),
         vec3( 0.0f,   1.0f,  0.0f),
         vec3( 0.0f,   0.0f,  1.0f),
         vec3(-1.0f,   0.0f,  0.0f),
         vec3( 0.0f,  -1.0f,  0.0f),
         vec3( 0.0f,   0.0f, -1.0f)
    };
    //! The eight colors for the eight vertices.
    vec3 colors[8] = {
         vec3( 1.0f,   0.0f,  0.0f),
         vec3( 0.0f,   1.0f,  0.0f),
         vec3( 0.0f,   0.0f,  1.0f),
         vec3( 1.0f,   1.0f,  0.0f),
         vec3( 0.0f,   1.0f,  1.0f),
         vec3( 1.0f,   0.5f,  0.5f),
         vec3( 0.5f,   0.5f,  1.0f),
         vec3( 1.0f,   0.0f,  1.0f)
    };

    /** This array shows the order of processing
     * for each vertex in the cube array.  The cube 
     * array defines each corner of the cube.  The
     * indices array allows the genMatrices function 
     * to generate a cube from the eight vertices. 
     * Each face of the cube has two triangles
     * or six vertices and there are six faces.
     * This is used to create regular vertices
     * that have all the data attached and no
     * indexing involved.
     */
    unsigned int indices[NUM_VERTICES] = {
        0, 1, 2, 0, 2, 3,
        0, 3, 4, 0, 4, 5,
        0, 5, 6, 0, 6, 1,
        7, 1, 6, 7, 2, 1,
        7, 5, 4, 7, 6, 5,
        7, 3, 2, 7, 4, 3
    };
    
    /** The Vertices for the indexed cube.   This is 
    * needed because sometimes you want a given vertex
    * to have a normal point up and right (for example)
    * at the same time.  Each vertice is provided
    * for all the normal directions it supports.
    */
    float cubeVerts[72] =
    {
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
        0.5f,  0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
    };
    /** Same story as the vertices above. These normals
     * match the vertices.
     */
    float cubeNormals[72] =
    {
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };
    //! Texture coordinates matching the indexed vertices.
    float cubeTex[48] =
    {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };
    //! Cube colors matching the indexed vertices.
    float cubeColors[72] = {
         1.0f,   0.0f,  0.0f,
         0.0f,   1.0f,  0.0f,
         0.0f,   0.0f,  1.0f,
         1.0f,   1.0f,  0.0f,
         0.0f,   1.0f,  1.0f,
         1.0f,   0.5f,  0.5f,
         0.5f,   0.5f,  1.0f,
         1.0f,   0.0f,  1.0f,
         1.0f,   0.0f,  0.0f,
         0.0f,   1.0f,  0.0f,
         0.0f,   0.0f,  1.0f,
         1.0f,   1.0f,  0.0f,
         0.0f,   1.0f,  1.0f,
         1.0f,   0.5f,  0.5f,
         0.5f,   0.5f,  1.0f,
         1.0f,   0.0f,  1.0f,
         1.0f,   0.0f,  0.0f,
         0.0f,   1.0f,  0.0f,
         0.0f,   0.0f,  1.0f,
         1.0f,   1.0f,  0.0f,
         0.0f,   1.0f,  1.0f,
         1.0f,   0.5f,  0.5f,
         0.5f,   0.5f,  1.0f,
         1.0f,   0.0f,  1.0f
    };
    /** The indices for the indexed vertices, colors, 
     * textures and normals.
     */
    unsigned int cubeIndices[36] =
    {
        0, 2, 1,
        0, 3, 2,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
        12, 15, 14,
        12, 14, 13,
        16, 17, 18,
        16, 18, 19,
        20, 23, 22,
        20, 22, 21
    };
    
};

#endif // INDEXEDCUBE_H

/**************************************************************
 * Shader:  A class to encapsulate the creation and use of 
 * a set of shaders.  
 * Edward C. Eberle <eberdeed@eberdeed.net>
 * August 2020 San Diego, California USA
 ***********************************************************/

#ifndef SHADER_H
#define SHADER_H

#include "commonheader.h"
#include <iostream>
#include <string>
// GLM The OpenGL math library
#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;
/** \class Shader A class to encapsulate the uploading, compiling, 
 * linking and using a shader.  
 */

class Shader
{
public:
    /** \brief The constructor signals the creation of the class.
     */
    Shader();
    /** \brief The destructor signals the destruction of the class,
     *  and deletes the shader program.
     */  
    ~Shader();
    /** \brief Read and build the shader program from two files.
     *  Delete the two shader objects afterwards.
     *  The variables are as follows:
     *  vertexPath : The vertex shader's location in the 
     *  file structure.
     *  fragmentPath : The fragment shader's location in the 
     *  file structure.
     */
    void initShader(string vertexPath, string fragmentPath);
    /** \brief Create either the vertex or fragment shader from a file.
     */
    unsigned int createShader(unsigned int type, string fpath);
    /** \brief Use the program object for display.
     */
    void Use();
    /** \brief Link the two shaders to form the program.
     */
    void linkShader();
    /** \brief Utility uniform functions that set values in the 
     * shader program.
     */
    void setBool(const string name, bool value) const;  
    void setInt(const string name, int value) const;   
    void setFloat(const string name, float value) const;
    void setVec2(const std::string name, vec2 value) const;
    void setVec3(const std::string name, vec3 value) const;
    void setVec4(const string name, vec4 value) const; 
    void setMat4(const string name, mat4 value) const;    
    
    /** Variables **/
    //! The shader program object.
    GLuint Program;
    //! Class global variables.
    //! Debugging information.
    bool debug1 = false;
    //! Indicates success of OpenGL function calls.
    int success = 0;
    //! Length of an OpenGL error information message.
    int infoLength = 0;
    //! Handles for vertex and fragment shader programs respectively.
    GLuint vertex, fragment;
    //! Vertex shader path and fragment shader path.
    string vertpath, fragpath;
};
  
#endif //SHADER_H

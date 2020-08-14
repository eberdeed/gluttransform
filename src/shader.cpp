/**************************************************************
 * Shader:  A class to encapsulate the creation and use of 
 * a set of shaders.  
 * Edward C. Eberle <eberdeed@eberdeed.net>
 * August 2020 San Diego, California USA
 ***********************************************************/

#include "../include/shader.h"


Shader::Shader()
{
    cout << "\n\n\tCreating Shader.\n\n";
}

Shader::~Shader()
{
    cout << "\n\n\tDestroying Shader.\n\n";
    glDeleteProgram(Program);
}

void Shader::initShader(string vertexPath, string fragmentPath)
{
    FILE *shaderFile;
    vertpath = vertexPath;
    fragpath = fragmentPath;
    unsigned char c;
    char *infoLog;
    Program = glCreateProgram();
    vertex = createShader(GL_VERTEX_SHADER, vertexPath);
    fragment = createShader(GL_FRAGMENT_SHADER, fragmentPath);
    if ((!vertex) || (!fragment))
    {
        cout << "\n\n\tError compiling shaders for shader:  " 
        << vertexPath << " and " << fragmentPath << ".\n\n";
        exit(1);
    }
}
void Shader::linkShader()
{
    glAttachShader(Program, vertex);
    glAttachShader(Program, fragment);
    glLinkProgram(Program);
    // Print linking errors if any
    glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &infoLength);
    if(infoLength > 0)
    {
        char *infoLog = new char[infoLength];
        glGetProgramInfoLog(Program, infoLength, NULL, infoLog);
        cout << "\n\n\tShader Program Link Error\n\t" << infoLog 
        << "\n\tFor shader files:  " 
        << vertpath << " and " << fragpath 
        << "\n\n";
        exit(-1);
    }
    else
    {
        if(debug1)
        {
            cout << "\n\n\tShader agregate program created for files:  "
            << vertpath << " and " << fragpath
            << ".\n\n";
        }
    }
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

unsigned int Shader::createShader(unsigned int type, string fpath)
{
    char c;
    string shaderCode;
    unsigned int shaderobj;
    FILE *shaderFile = fopen(fpath.c_str(), "r");
    if (!shaderFile)
    {
        cout << "\n\n\tError opening file " << fpath << ".\n\n";
        return 0;
    }
    // Read file's buffer contents into streams
    while ((c = std::fgetc(shaderFile)) != EOF) 
    { // standard C I/O file reading loop
        shaderCode += c;
    }
    fclose(shaderFile);
    const GLchar* glShaderCode = shaderCode.c_str();
    // Vertex Shader
    try
    {
        shaderobj = glCreateShader(type);
        glGetShaderiv(shaderobj, GL_INFO_LOG_LENGTH, &infoLength);
        if ((!shaderobj) && (infoLength == 0))
        {
            cout << "\n\n\tError creating shader object:  " << fpath << ".\n\n";
            if (debug1)
            {            
                exit(-1);
            }
        }
        else if(infoLength > 0)
        {
            char infoLog[infoLength];
            glGetShaderInfoLog(shaderobj, infoLength, NULL, infoLog);
            cout << "\n\nShader Program Creation Error\n" << infoLog << "\n\tFor shader:  " << fpath << ".\n\n";
            if (debug1)
            {            
                exit(-1);
            }
        }
        else
        {
            if(debug1)
            {
                cout << "\n\n\tCreated the shader object:  " << fpath << ".\n\n";
            }
        }
        glShaderSource(shaderobj, 1, &glShaderCode, nullptr);
        glCompileShader(shaderobj);
        // Print compile errors if any
        glGetShaderiv(shaderobj, GL_INFO_LOG_LENGTH, &infoLength);
        if ((!shaderobj) && (infoLength == 0))
        {
            cout << "\n\n\tError compiling shader object for shader:  " << fpath << ".\n\n";
            if (debug1)
            {            
                exit(-1);
            }
        }
        else if(infoLength > 0)
        {
            char infoLog[infoLength];
            glGetShaderInfoLog(shaderobj, infoLength, NULL, infoLog);
            cout << "\n\n\tShader compilation error: \n" << infoLog 
            << "\n\tFor shader " << fpath << "\n\n";
            glDeleteShader(shaderobj);
            return 0;
        }
        else
        {
            if(debug1)
            {
                cout << "\n\n\tShader compiled.\n\n";
            }
        }
        return shaderobj;
    }
    catch(exception exc)
    {
        cout << "\n\n\tError making shader:  " << exc.what() << "\n\n";
        return 0;
    }
}

void Shader::Use() 
{ 
    glUseProgram(Program); 
}   

    
void Shader::setBool(const std::string name, bool value) const
{         
    glUniform1i(glGetUniformLocation(Program, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string name, int value) const
{ 
    glUniform1i(glGetUniformLocation(Program, name.c_str()), value); 
}
void Shader::setFloat(const std::string name, float value) const
{ 
    glUniform1f(glGetUniformLocation(Program, name.c_str()), value); 
} 
void Shader::setVec2(const std::string name, vec2 value) const
{ 
    glUniform2fv(glGetUniformLocation(Program, name.c_str()), 1, value_ptr(value)); 
} 
void Shader::setVec3(const std::string name, vec3 value) const
{ 
    glUniform3fv(glGetUniformLocation(Program, name.c_str()), 1, value_ptr(value)); 
} 
void Shader::setVec4(const std::string name, vec4 value) const
{ 
    glUniform4fv(glGetUniformLocation(Program, name.c_str()), 1, value_ptr(value)); 
} 
void Shader::setMat4(const std::string name, mat4 value) const
{ 
    glUniformMatrix4fv(glGetUniformLocation(Program, name.c_str()), 1, GL_FALSE, &value[0][0]); 
} 

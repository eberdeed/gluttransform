/**************************************************************
 * RotateBlock:  A class that uses OpenGL Transformation
 * Feedback to rotate and scale an object and draw it 
 * to the screen.
 * Created on 08/2020 by Edward C. Eberle <eberdeed@eberdeed.net>
 * San Diego, California USA
 *************************************************************/

#include "../include/rotateblock.h"

RotateBlock::RotateBlock()
{
    cout << "\n\n\tCreating RotateBlock.\n\n";
    init();
}

RotateBlock::~RotateBlock()
{
    cout << "\n\n\tDestroying RotateBlock.\n\n";
    glDeleteBuffers(2, particleVBOs);
    glDeleteTextures(1, &background);
    glDeleteTextures(1, &sides);
    delete emitShader;
    delete drawShader;
    delete cuby;
    delete image;
}
void RotateBlock::initEmitParticles ()
{

   {

      // Set the vertex emitShader outputs as transform feedback varyings
      glTransformFeedbackVaryings (emitShader->Program, 2, feedbackVaryings, GL_INTERLEAVED_ATTRIBS );

      // Link program must occur after calling glRotateBlockVaryings
      emitShader->linkShader();

   }
}
void RotateBlock::debug()
{
    for (int x = 0; x < NUM_VERTICES; x++)
    {
        cout << "\n\tDatum:  " << x 
        << " Position: " 
        << particleData[x].position[0]
        << ", " << particleData[x].position[1]
        << ", " << particleData[x].position[2]
        << " Texture Coordinate: " << particleData[x].texcoord[0]
        << ", " << particleData[x].texcoord[1];
    }
    cout << "\n\n";
}
///
// Initialize the shader and program object
//
int RotateBlock::init()
{

    // Load the shaders and get a linked program object
    emitShader = new Shader();
    emitShader->initShader("/usr/share/openglresources/shaders/emittransfeed.vert", "/usr/share/openglresources/shaders/emittransfeed.frag");
    drawShader = new Shader();
    drawShader->initShader("/usr/share/openglresources/shaders/drawtransfeed.vert", "/usr/share/openglresources/shaders/drawtransfeed.frag");  
    drawShader->linkShader();
    initEmitParticles ();
    cuby = new IndexedCube();
    systime = 0.0f;
    curSrcIndex = 0;

    glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

    image = new CreateImage();
    background = image->setImage("/usr/share/openglresources/images/container.png" );
    background = image->textureObject();
    for (int x = 0; x < 6; x++)
    {
        sidedata.push_back(sidefiles[x]);
    }
    image->create2DTexArray(sides, sidedata);

    cuby = new IndexedCube();
    // Initialize particle data
    cuby = new IndexedCube();
    vertices = cuby->genCube(1.0f, false, false, true);
    initParticles();
    if (debug1)
    {
        debug();
    }
    // Create the particle VBOs
    glGenBuffers (2, particleVBOs);

    for (int i = 0; i < 2; i++ )
    {
        glBindBuffer ( GL_ARRAY_BUFFER, particleVBOs[i] );
        glBufferData ( GL_ARRAY_BUFFER, sizeof ( Particle ) * NUM_VERTICES, particleData, GL_DYNAMIC_COPY );
    }
    return TRUE;
}

void RotateBlock::setupVertexAttributes(GLuint vboID)
{
   glBindBuffer(GL_ARRAY_BUFFER, vboID);

   glVertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const void*) 0);
   glEnableVertexAttribArray(ATTRIBUTE_POSITION);

   glVertexAttribPointer(ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (const void*) (3 * sizeof(float)));
   glEnableVertexAttribArray(ATTRIBUTE_TEXCOORD);
}

///
//  Update time-based variables
//
void RotateBlock::update(mat4 orientation, float deltaTime)
{
    systime += deltaTime;
    if(debug1)
    {
        cout << "\n\tTime:  " << systime 
        << " delta time:  " << deltaTime;
    }
    GLuint srcVBO = particleVBOs[ curSrcIndex ];
    GLuint dstVBO = particleVBOs[(curSrcIndex + 1) % 2 ];

    emitShader->Use();

    setupVertexAttributes(srcVBO);
    // Set transform feedback buffer
    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, dstVBO);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, dstVBO);

    // Turn off rasterization - we are not drawing
    glEnable(GL_RASTERIZER_DISCARD);
    if (cos(systime * onedegree * 100.0f) > 0.0)
    {
        sign = 1.0f;
    }
    else
    {
        sign = -1.0f;
    }
    if(debug1)
    {
        cout << "\n\tSign: " << sign << "  Cosine: " << cos(systime * onedegree * 100.0f);
    }
    emitShader->setFloat("sign", sign);
    emitShader->setVec3("movement", movement);
    emitShader->setMat4("orientation", orientation);

    // Emit particles using transform feedback
    glBeginTransformFeedback(GL_TRIANGLES);
    glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
    glEndTransformFeedback();

    // Create a sync object to ensure transform feedback results are completed before the draw that uses them.
    emitSync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    // Restore state
    glDisable(GL_RASTERIZER_DISCARD);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Ping pong the buffers
    curSrcIndex =(curSrcIndex + 1) % 2;
    if (systime > TIME_INTERVAL)
    {
        systime = 0;
    }
}

void RotateBlock::draw(int width, int height, mat4 model, mat4 view, mat4 projection)
{
    // Block the GL server until transform feedback results are completed
    glWaitSync(emitSync, 0, GL_TIMEOUT_IGNORED);
    glDeleteSync(emitSync);

    // Set the viewport
    glViewport(0, 0, width, height);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // Use the program object
    drawShader->Use();

    // Load the VBO and vertex attributes
    setupVertexAttributes(particleVBOs[curSrcIndex ]);
    
    // Set uniforms
    drawShader->setMat4("model", model);
    drawShader->setMat4("view", view);
    drawShader->setMat4("projection", projection);
    // Bind the texture
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, background);
    // Set the sampler texture unit to 0.
    drawShader->setInt("s_texture", 1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D_ARRAY, sides);
    // Set the sampler texture unit to 1.
    drawShader->setInt("sides", 2);
    for (int x = 0; x < 6; x++)
    {
        drawShader->setInt("index", x);
        glDrawArrays(GL_TRIANGLES, x * 6, ((x + 1) * 6));
    }
}

void RotateBlock::initParticles()
{
   for (int i = 0; i < NUM_VERTICES; i++ )
   {
      particleData[i].position[0] = vertices[i * 5];
      particleData[i].position[1] = vertices[i * 5 + 1];
      particleData[i].position[2] = vertices[i * 5 + 2];
      particleData[i].texcoord[0] = vertices[i * 5 + 3];
      particleData[i].texcoord[1] = vertices[i * 5 + 4];
   }
}


void RotateBlock::printMat4(mat4 val)
{
    for (int y = 0; y < 4; y++)
    {
        cout << "\n\t";
        for(int x = 0; x < 4; x++)
        {
            cout << val[x][y] << ", ";
        }
    }
    cout << "\n\n";
}

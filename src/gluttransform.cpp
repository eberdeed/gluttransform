/********************************************************************
 * GlutTransform:  A class to draw a simple triangle.
 * Edward Charles Eberle <eberdeed@eberdeed.net>
 * 12/2019 San Diego, California USA
 ********************************************************************/

#include "../include/gluttransform.h"


GlutTransform::GlutTransform()
{
    cout << "\n\n\tCreating GlutTransform\n\n";
    initProg();
}

GlutTransform::~GlutTransform()
{
    cout << "\n\n\tDestroying GlutTransform\n\n";
    sound->stop();
    sound->resetBuffer();
    buffer->~SoundBuffer();
    sound->~Sound();
    delete rotateblock;
    delete moveblock;
    delete skybox;
    //sndthread->cancelThread(0);
    //delete sndthread;
    delete camera;
}

void GlutTransform::initProg()
{
    try
    {
        d = XOpenDisplay(NULL);
        s = DefaultScreenOfDisplay(d);
        sound = new sf::Sound();
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
        glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT); 
        glutInitWindowPosition((s->width / 2) - (SCR_WIDTH / 2), (s->height / 2) - (SCR_HEIGHT / 2)); 
        glutCreateWindow("Glut OpenGL Transformation Feedback Demo");
        cout << "\n\tWindow width:  " << glutGet(GLUT_WINDOW_WIDTH) << "  Window height:  " 
        << glutGet(GLUT_WINDOW_HEIGHT) << "\n\n";
        glutDisplayFunc(GlutTransform::events);
        glutReshapeFunc(GlutTransform::windowEvent);
        glutKeyboardFunc(GlutTransform::processInput);
        glutSpecialFunc(GlutTransform::specialKeys);
        glutPassiveMotionFunc(GlutTransform::mouseMove);
        glutMouseFunc(GlutTransform::mouseClick);
        glewExperimental=true;
        GLenum err=glewInit();
        if(err!=GLEW_OK)
        {
            //Problem: glewInit failed, something is seriously wrong.
            cout<<"glewInit failed, aborting."<<endl;
            exit(1);
        }
        /*  Commented out because github will not accept wav files.
        ThreadInfo tmpInfo;
        threadInfo.push_back(tmpInfo);
        sndthread = new ThreadCreate(arg, threadInfo);
        int error = sndthread->execute(GlutTransform::soundMaker, 0);
        if (error != 0)
        {
            cout << "\n\n\tSound thread error.\n\n";
        }
        else
        {
            cout << "\n\n\tSound thread success.\n\n";
        }
        */
        skybox = new SkyBox();
        rotateblock = new RotateBlock();
        moveblock = new MoveBlock();
        camera = new Camera(SCR_WIDTH, SCR_HEIGHT, vec3(10.0f, -10.0f, 30.0f), vec3(0.0f, 0.0f, 0.0f));
        windowEvent(SCR_WIDTH, SCR_HEIGHT);
    }
    catch(exception exc)
    {
        cout << "\n\n\tProgram Initialization Error:  " << exc.what() << "\n\n";
    }
}

void GlutTransform::events()
{
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    intbegin = chrono::system_clock::now();
    viewPos = camera->getPosition();
    model = mat4(1.0f);
    view = camera->getViewMatrix(); //! render
    projection = camera->getPerspective();
    if (debug1)
    {
        cout << "\n\n\tView Matrix:  \n";
        printMat4(view);
    }
    skybox->drawSkyBox(model, view, projection);
    projection = ortho(-boxsize, boxsize, -boxsize, boxsize);
    if (switcher)
    {
        rotateblock->update(orientation, delta);
        rotateblock->draw(scrwidth, scrheight, model, view, projection);
        orientation = mat4(1.0f);
    }
    else
    {
        moveblock->update(movement, delta);
        moveblock->draw(scrwidth, scrheight, model, view, projection);
        movement = vec3(0.0f);
    }
    intend = chrono::system_clock::now();
    delta = (float)         chrono::duration_cast<chrono::nanoseconds>(intend - intbegin).count() * 0.0000001f;
    if (debug1)
    {
        cout << "\n\tDelta:  " << delta;
    }
    glutSwapBuffers();
    glutPostRedisplay();
}

// ---------------------------------------------------------------------------------------------------------
void GlutTransform::processInput(unsigned char key, int x, int y)
{
    int keyval = (int) key;
    movement = vec3(0.0f);
    int mods = glutGetModifiers();
    if (debug1)
    {
        cout << "\n\tKey:  " << keyval  << " : " << key 
        << " Delta:  " << delta;
    }
    int glutWin = glutGetWindow();
    float cameraSpeed = 0.5f * delta;
    switch(keyval)
    {
        case 0x001B:
            glutDestroyWindow(glutWin);
            exit(0);
            break;
        //! Forward motion.
        case 0x0077:
        case 0x0057:
            camera->processKeyboard(Camera::Camera_Movement::FORWARD, cameraSpeed);
            movement = vec3(0.0f, 0.0f, delta);
            break;
        //! Backwards motion.
        case 0x0073:
        case 0x0053:
            camera->processKeyboard(Camera::Camera_Movement::BACKWARD, cameraSpeed);
            movement = vec3(0.0f, 0.0f, -delta);
            break;
        //! Move left.
        case 0x0061:
        case 0x0041:
            camera->processKeyboard(Camera::Camera_Movement::LEFT, cameraSpeed);
            movement = vec3(-delta, 0.0f, 0.0f);
            break;
        //! Move right.
        case 0x0064:
        case 0x0044:
            camera->processKeyboard(Camera::Camera_Movement::RIGHT, cameraSpeed);
            movement = vec3(delta, 0.0f, 0.0f);
            break;
        //! Move up.
        case 0x0072:
        case 0x0052:
            camera->processKeyboard(Camera::Camera_Movement::UP, cameraSpeed);
            movement = vec3(0.0f, delta, 0.0f);
            break;
        //! Move down.
        case 0x0066:
        case 0x0046:
            camera->processKeyboard(Camera::Camera_Movement::DOWN, cameraSpeed);
            movement = vec3(0.0f, -delta, 0.0f);
            break;
        //! Reset the camera.
        case 0x007A:
        case 0x005A:
            camera->resetCamera();
            moveblock->init();
            break;
        //! Reverse the camera.
        case 0x0078:
        case 0x0058:
            camera->reverseDirection();
            break;
        case 0x000D:
            if (mods == GLUT_ACTIVE_ALT)
            {
                fullScreen = !fullScreen;
                if (fullScreen)
                {
                    glutFullScreen();
                    windowEvent(s->width, s->height);
                }
                else
                {
                    glutReshapeWindow(SCR_WIDTH, SCR_HEIGHT);
                    glutPositionWindow((s->width / 2) - (SCR_WIDTH / 2), (s->height / 2) - (SCR_HEIGHT / 2)); 
                    windowEvent(SCR_WIDTH, SCR_HEIGHT);
                }
            }
            break;
    }
    if (debug1)
    {
        cout << "\n\tMovement:  " << movement.x
        << ", " << movement.y << ", " << movement.z;
    }
    glutPostRedisplay();
}

void GlutTransform::specialKeys(int key, int x, int y)
{
    switch(key)
    {
        //! Zoom keys.
        //! Zoom in.
        case GLUT_KEY_UP:
            camera->processMouseScroll(Camera::Camera_Movement::CLOSER);
            break;
        //! Zoom out.
        case GLUT_KEY_DOWN:
            camera->processMouseScroll(Camera::Camera_Movement::AWAY);
            break;
    }
    glutPostRedisplay();
}

void GlutTransform::mouseMove(int x, int y)
{
    orientation = mat4(1.0f);
    if(firstMouse)
    {
        lastX = (float) x;
        lastY = (float) y;
        firstMouse = false;
    }
    float xoffset = (float) x - lastX;
    float yoffset = (float) y - lastY; 
    /** Call the camera class with the information
     *  about the movement of the mouse.
     */
    camera->processMouseMovement(xoffset, yoffset);
    orientation = -rotate(orientation, mouseSpeed * (x - lastX), vec3(0.0f, 1.0f, 0.0f));
    orientation = -rotate(orientation, mouseSpeed * (y - lastY), vec3(1.0f, 0.0f, 0.0f));
    if (debug1)
    {
        cout << "\n\tOrientation:  ";
        printMat4(orientation);
    }
    lastX = (float) x;
    lastY = (float) y;
    glutPostRedisplay();
}

void GlutTransform::mouseClick(int button, int state, int x, int y)
{
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
        switcher = !switcher;
    }
}
    
void GlutTransform::windowEvent(int width, int height)
{
    scrwidth = width;
    scrheight = height;
    glViewport(0, 0, width, height);
    camera->resizeView(width, height);
}
void GlutTransform::printMat4(mat4 val)
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

void* GlutTransform::soundMaker(void *arg)
{
    ThreadInfo *tinfo = (ThreadInfo*) arg;
    string uargv = "";
    char *tmpptr;
    cout << "\n\n\tThread " << tinfo->threadNum 
    << " : Thread Name " << tinfo->threadName << "\n\n";
    for (int x = 0; x < tinfo->threadName.length(); x++)
    {
        uargv = + toupper(tinfo->threadName.at(x));
    }
    if (uargv.length() == 0)
    {
        cout << "\n\n\tNo string name alloted.\n\n";
    }
    buffer = new sf::SoundBuffer();
    if (!buffer->loadFromFile(soundFile)){
        cout << "\n\n\tUnable to load sound.\n\n";
    }
    sound->setBuffer(*buffer);
    while (true)
    {
        sound->play();
        sleep(452000);
    };
    sound->stop();
    tmpptr = (char*) uargv.c_str();
    return (void*) tmpptr;
}


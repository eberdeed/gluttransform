
    gluttransform is a program that displays two examples of
    transformation feedback.  One display is rotation and
    scaling of an object and the other is translation and
    scaling.  You can cycle between the two displays by 
    clicking on the window. The rotation display can be
    manipulated by moving the mouse.  The translation display
    has a number of keys enabled.
    The keys are as follows.
    a right
    s back
    d left
    w forward
    r up
    f down
    
    For both displays:
    Escape ends the program
    Alt+Return sets full screen.
    
    To compile the program you will need the following libraries:
    FreeImage, SDL2, Boost, GLEW and pthreads.
    You must also have cmake and doxygen.
    The commands are:
    
    mkdir build
    cd build
    cmake ..
    sudo make doc
    sudo make install
    
    To run a program use:
    
    gluttransform
    
    The documentation is located in:
    
    /usr/share/doc/gluttransform-doc
    
    The sources I used to educate myself concerning OpenGL are
    as follows:
        "OpenGL ES 3.0 Programming Guide Second Edition" 
    by Dan Ginsburg and Budirijanto Purnomo published by Addison-Wesley 2014.
        www.learnopengl.com.  On pages 380-385 you will find the example this 
        program was built from.
    GLEW http://glew.sourceforge.net, and
    CMAKE http://www.cmake.org.
    Doxygen http://www.doxygen.nl
    GraphViz https://www.graphviz.org for the "dot" program used by doxygen.
    SDL2 https://wiki.libsdl.org/FrontPage
    pthread https://www.gnu.org/software/hurd/libpthread.html
    OpenGL is generally available on any system as part 
    of the underlying graphics subsystem and GLEW will 
    get you access to it.
    
    The program was written and compiled on debian linux available at:  www.debian.org.
    
    You can reach me at <eberdeed@eberdeed.net>.
    Updates will be available at www.eberdeed.net.
    Edward Charles Eberle 
    April 17th, 2020 San Diego, California United States of America
    
    This program is licensed under the Lesser GNU Public license.
    It can be found in the LGPL directory 
    and once installed it will be also found at 
    /usr/share/doc/gluttransform-doc/LGPL.  This 
    program is given as an instructional aid for learning
    and using the libraries presented and is not to 
    be considered fit for any particular use.
    
    

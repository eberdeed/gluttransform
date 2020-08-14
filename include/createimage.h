/**********************************************************
 *   CreateImage:  A class to encapsulate loading an image
 *   into a GLvoid blob and returning OpenGL texture objects.
 *   Designed for OpenGL. 
 *   Created by: Edward Charles Eberle <eberdeed@eberdeed.net>
 *   August 2020 San Diego, California USA
 * ********************************************************/

#define LIMIT 75
#ifndef CREATEIMAGE_H
#define CREATEIMAGE_H
#include "commonheader.h"

using namespace std;

/* \class CreateImage : Using Free Image Plus, this class loads an 
 * image into memory, converts it to a 32 bit format with alpha, 
 * and then passes it to an array of unsigned characters, which 
 * is then passed using a cast to a GLvoid blob. Optionally the 
 * image can be turned into an OpenGL buffer object. It provides
 * for a single image, a vector of images, or a sky box containing
 * six images. 
 */
class CreateImage
{
public:
    //! \breif Echo the creation of the class.
    CreateImage();
    //! \breif Free the storage used by the pixels array.
    ~CreateImage();
    /* Functions */
    //!  \breif Load image and convert it.
    bool setImage(string imagefile);
    //! Accessor functions for the given image's dimensions and data.
    //! \breif Image width in pixels.
    GLsizei getWidth();
    //! \breif Image height in pixels.
    GLsizei getHeight();
    //! \breif The overall size of the image in bytes.
    GLsizei getSize();
    //! \breif The void* blob containing the picture data.
    GLvoid *getData();
    //! \breif Return an OpenGL texture buffer object.
    GLuint textureObject();
    /** \breif Return an OpenGL sky box texture object.
     * textureID:  The OpenGL samplerCube texture object.
     * filenames" The array containing the sides of the
     * sky box (see below).
     */
    void createSkyBoxTex(GLuint &textureID, string filenames[6]);
    /** \brief Create an 2D array of texture images for an 
     * OpenGL Texture2DArray object.
     * textureID: The 2D texture array object.
     * filenames: a vector of the images to be used, my
     * system will accept 256 images.
     */
    void create2DTexArray(GLuint &textureID, vector<string>filenames);
protected:
    /* Variables */
    //! Class global variables.
    //! The Free Image Plus image object.
    fipImage *txtImage;
    //! A line of image data.
    BYTE *picLine;
    //! Image dimensions.
    GLsizei width;
    GLsizei height;
    //! The size in bytes.
    int size = 0;
    //! Image data.
    unsigned char *pixels = nullptr;
    //! Byte and line counters.
    int count, line;
    //! A little tiny bit of debug info.
    bool debug1 = false;
};
#endif // CreateImage.h

#include "nxTextureLoader.h"

static nxUInt currentTextureIdx = 0;
static nxUInt textureIndices[NX_MAX_TEXTURES];

static int powerOfTwo( int value )
{
    int result = 1 ;

    while ( result < value )
    {
        result *= 2 ;
    }

    return result ;		
}


/**
 * Creates a texture from a surface. Set the alpha according to the color key. 
 * Pixels that match the color key get an alpha of zero while all other
 * pixels get an alpha of one.
 *
 * The source surface can come from example from a PNG file.
 *
 * @url:http://osdl.sourceforge.net/main/documentation/rendering/SDL-openGL-examples.html#loadnonalphaexample
 */
static GLuint uploadTextureFromSurface( 
        SDL_Surface* sourceSurface, 
        Uint8 colorKeyRed, 
        Uint8 colorKeyGreen, 
        Uint8 colorKeyBlue,
        Uint8 colorKeyAlpha)
{

    /*
     * Use the surface width and height expanded to powers of 2 :
     * (one may call also gluScaleImage.
     */

    int w = powerOfTwo( sourceSurface->w ) ;
    int h = powerOfTwo( sourceSurface->h ) ;
    
    //    int w = sourceSurface->w; 
    //    int h = sourceSurface->h;

    /*
     //TODO:Remove
    // Min X :
    texcoord[0] = 0.0f ;
    // Min Y :
    texcoord[1] = 0.0f ;
    // Max X :
    texcoord[2] = (GLfloat) surface->w / w ;
    // Max Y :
    texcoord[3] = (GLfloat) surface->h / h ;
    */

    /* Create the target alpha surface with correct color component ordering */
    SDL_Surface* alphaImage = SDL_CreateRGBSurface( SDL_SWSURFACE, 
            sourceSurface->w,
            sourceSurface->h, 
            32 /* bits */,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN // OpenGL RGBA masks 
            0x000000FF, 
            0x0000FF00, 
            0x00FF0000, 
            0xFF000000
#else
            0xFF000000,
            0x00FF0000, 
            0x0000FF00, 
            0x000000FF
#endif
            );

    if ( alphaImage == NX_NULL )
    {
        NX_ASSERT("uploadTextureFromSurface : RGB surface creation failed.");
    }

    // Set up so that colorkey pixels become transparent :
    //Uint32 colorkey = SDL_MapRGBA( alphaImage->format, colorKeyRed, colorKeyGreen, colorKeyBlue, colorKeyAlpha );
    Uint32 colorkey = SDL_MapRGBA( alphaImage->format, colorKeyRed, colorKeyGreen, colorKeyBlue, colorKeyAlpha );
    SDL_FillRect( alphaImage, 0, colorkey );

    colorkey = SDL_MapRGBA( sourceSurface->format, colorKeyRed, colorKeyGreen, colorKeyBlue, colorKeyAlpha);
    SDL_SetColorKey( sourceSurface, SDL_SRCCOLORKEY, colorkey );

    SDL_Rect area;

//    SDL_SetAlpha(sourceSurface, 0, 0); //http://www.gamedev.net/topic/518525-opengl--sdl--transparent-image-make-textures/
    SDL_SetAlpha(sourceSurface, 0, colorKeyAlpha); //http://www.gamedev.net/topic/518525-opengl--sdl--transparent-image-make-textures/
            
//    SDL_SetAlpha(sourceSurface, SDL_ALPHA_TRANSPARENT, 255); //http://www.gamedev.net/topic/518525-opengl--sdl--transparent-image-make-textures/

    // Copy the surface into the GL texture image : 
    area.x = 0;
    area.y = 0; 
    area.w = sourceSurface->w;
    area.h = sourceSurface->h;
    SDL_BlitSurface( sourceSurface, &area, alphaImage, &area );

    // Create an OpenGL texture for the image 

    GLuint textureID;
    glGenTextures( 1, &textureID );
    glBindTexture( GL_TEXTURE_2D, textureID );

    /* Prepare the filtering of the texture image */

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    /* Map the alpha surface to the texture */
    glTexImage2D( GL_TEXTURE_2D,
            0,
            GL_RGBA,
            w, 
            h,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            alphaImage->pixels );

    // No longer needed :
    SDL_FreeSurface(alphaImage); 

    return textureID ;
}

static SDL_Surface* loadImage(const char* filename) 
{
    SDL_Surface* tempSurface = NX_NULL;
    SDL_Surface* result = NX_NULL;
 
    if((tempSurface = IMG_Load(filename)) == NX_NULL) 
    {
        NX_ASSERT("Cannot load image file");
    }
 
    result = SDL_DisplayFormatAlpha(tempSurface);
    SDL_FreeSurface(tempSurface);
 
    return result;
}

//---------------------------------------------------------------

GLuint nxTextureLoader_loadImageFromFilename(const char* filename)
{
    SDL_Surface* image = loadImage(filename);

    //This code gotten from http://osdl.sourceforge.net/main/documentation/rendering/SDL-openGL-examples.html#loadnonalphaexample
    Uint32 rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

    GLuint texture = uploadTextureFromSurface( 
        image, 
        rmask, 
        gmask, 
        bmask, 
        amask);

    textureIndices[currentTextureIdx++] = texture; //Keep track of textures for deletion

    SDL_FreeSurface(image);
    return texture; 
}

void nxTextureLoader_shutdown()
{
    //Delete all textures alloced
    for(int i = 0;i<currentTextureIdx;i++)
    {
        glDeleteTextures( 1, &textureIndices[i] );
    }    
}

//---------------------------------------------------------------

/*
#define NX_UNITTEST 
#ifdef NX_UNITTEST

#include <nxTextureLoader.h>

int main(void)
{
    nxTextureLoader_loadImageFromFilename("../media/man_still.png");
}

#endif
*/

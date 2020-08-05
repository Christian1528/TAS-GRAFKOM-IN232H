/*#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include "Image.h"
enum
{
	DIFFUSE_TEXTURE,
	SPECULAR_TEXTURE,
	NORMAL_TEXTURE,
	HEIGHT_TEXTURE
};
class Texture
{
private:
public:
	Image	image;
	int	width;
	int	height;
	char*	pixelData;
	GLuint	texId;

	Texture( const std::string fileName );
	Texture( const GLint internalformat, const GLenum format, const int _width, const int _height );
	~Texture(  );
	GLuint getTexId(  ) const;
	// All image loading methods will fill pixelData with RGB values
	int loadImage( const std::string fileName );
};
#endif*/
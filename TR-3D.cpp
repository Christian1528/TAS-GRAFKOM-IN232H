/*#include "Texture.h"
Texture::Texture( const std::string fileName )
{
	glGenTextures( 1, &texId );
	glBindTexture( GL_TEXTURE_2D, texId );
	int loaded = loadImage( fileName );
	if ( loaded == IMAGE_LOADED )
	{
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		switch ( image.header.bitsPerPixel )
		{
		case 32:
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, image.header.width, image.header.height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixelData );
			break;
		case 24:
			// Access Violation!
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB8, image.header.width, image.header.height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixelData );
			break;
		default:
			std::cout << "Format unsupported" << std::endl;
			break;
		}

		// Access Violation!
		glGenerateMipmap( GL_TEXTURE_2D );
		// Remove texture from memory. This will eventually be optional
		delete[] pixelData;
	}
}
Texture::Texture( const GLint internalformat, const GLenum format, const int _width, const int _height )
{
	glGenTextures( 1, &texId );
	glBindTexture( GL_TEXTURE_2D, texId );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	switch ( internalformat )
	{
	case GL_RGB8:
	case GL_RGBA8:
		glTexImage2D( GL_TEXTURE_2D, 0, internalformat, _width, _height, 0, format, GL_UNSIGNED_BYTE, NULL );
		break;
	case GL_RGB16F:
	case GL_RGB32F:
	case GL_RGBA16F:
	case GL_RGBA32F:
		glTexImage2D( GL_TEXTURE_2D, 0, internalformat, _width, _height, 0, format, GL_FLOAT, NULL );
		break;
	case GL_DEPTH24_STENCIL8:
		glTexImage2D( GL_TEXTURE_2D, 0, internalformat, _width, _height, 0, format, GL_UNSIGNED_INT_24_8, NULL );
		break;
	}
}
Texture::~Texture(  )
{
	glDeleteTextures( 1, &texId );
}
GLuint Texture::getTexId(  ) const
{
	return texId;
}
int Texture::loadImage( const std::string fileName )
{
	return image.loadImage( fileName );
}*/
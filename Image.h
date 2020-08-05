#ifndef IMAGE_H_
#define IMAGE_H_

#include <fstream>
#include <iostream>
#include <string>

// TGA Specification - http://netghost.narod.ru/gff/vendspec/tga/tga.txt
struct TGAHEADER
{
	// Length of id string
	char	idLength;

	// Image storage info
	char	colourMapType;
	char	imageType;

	// Colour Map
	short	firstEntry;
	short	numEntries;
	char	bitsPerEntry;

	// Image description
	short	xOrigin;
	short	yOrigin;
	short	width;
	short	height;
	char	bitsPerPixel;
	char	descriptor;
};

enum
{
	TGA_UNSUPPORTED = 1,
	TGA_NO_IMAGE = 2,
	TGA_MAP = 4,
	TGA_RGB = 8,
	TGA_BW = 16,
	TGA_RLE = 32
};

// Generic header that image data will be stored in
// regardless of image format
// Fields will be added as required
struct ImageHeader
{
	int width;
	int height;
	char bitsPerPixel;
};

enum
{
	IMAGE_LOADED,
	ERROR,
	UNSUPPORTED_IMAGE_FORMAT
};

// Currently only supports TGA
class Image
{
public:
	ImageHeader header;
	char* pixelData;

	~Image();

	int loadImage(const std::string& fileName);

private:
	// loadImage() will handle the call to format specifc methods
	int loadTGA(const std::string& fileName);
};

#endif
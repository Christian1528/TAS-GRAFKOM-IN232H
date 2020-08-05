#include "Image.h"

Image::~Image()
{

}

int Image::loadImage(const std::string& fileName)
{
	// For now only TGA is supported
	return loadTGA(fileName);
}

int Image::loadTGA(const std::string& fileName)
{
	TGAHEADER tgaHeader;

	// Holds bitwise flags for TGA file
	int tgaDesc = 0;

	std::cout << "Loading TGA: " << fileName.c_str() << std::endl;

	std::ifstream tgaFile(fileName, std::ios::in | std::ios::binary);

	if (!tgaFile.is_open())
	{
		std::cout << "Error opening " << fileName.c_str() << std::endl;
		return ERROR;
	}

	// Go to end of file to check TGA version
	tgaFile.seekg(0, std::ios::end);

	// We need to store the file size for a worst case scenario
	// RLE compression can increase the amount of data
	// depending on the image. (This scenario will only arise, in
	// an image with very few same pixel runs).
	int fileSize = (int)tgaFile.tellg();

	//std::cout << "Filesize: " << fileSize << " bytes" << std::endl;

	// Seek to version identifier (Always specified as being 18
	// characters from the end of the file)
	tgaFile.seekg(-18, std::ios::end);

	// Read version identifier
	char versionCheck[17] = "";
	tgaFile.read(versionCheck, 16);

	// Check version
	int version = 1;
	if (strcmp(versionCheck, "TRUEVISION-XFILE") == 0)
		version = 2;

	//std::cout << "TGA Version: " << version << std::endl;

	// Back to the beginning of the file
	tgaFile.seekg(0, std::ios::beg);

	// Read Header
	//std::cout << "Reading Header" << std::endl;

	// Need to read each field in one at a time since the structure padding likes
	// to eat the 4th and 10th bytes
	tgaFile.read(&tgaHeader.idLength, sizeof(tgaHeader.idLength));
	tgaFile.read(&tgaHeader.colourMapType, sizeof(tgaHeader.colourMapType));
	tgaFile.read(&tgaHeader.imageType, sizeof(tgaHeader.imageType));

	// If colourMapType is 0 and these 3 fields below are not 0, something may have went wrong
	tgaFile.read((char*)(&tgaHeader.firstEntry), sizeof(tgaHeader.firstEntry));
	tgaFile.read((char*)(&tgaHeader.numEntries), sizeof(tgaHeader.numEntries));
	tgaFile.read(&tgaHeader.bitsPerEntry, sizeof(tgaHeader.bitsPerEntry));


	tgaFile.read((char*)(&tgaHeader.xOrigin), sizeof(tgaHeader.xOrigin));
	tgaFile.read((char*)(&tgaHeader.yOrigin), sizeof(tgaHeader.yOrigin));
	tgaFile.read((char*)(&tgaHeader.width), sizeof(tgaHeader.width));
	tgaFile.read((char*)(&tgaHeader.height), sizeof(tgaHeader.height));
	tgaFile.read(&tgaHeader.bitsPerPixel, sizeof(tgaHeader.bitsPerPixel));
	tgaFile.read(&tgaHeader.descriptor, sizeof(tgaHeader.descriptor));

	header.width = tgaHeader.width;
	header.height = tgaHeader.height;

	// Output image header
	//std::cout << "ID LENGTH: " << (int)tgaHeader.idLength << std::endl;
	//std::cout << "CM TYPE: " << (int)tgaHeader.colourMapType << std::endl;
	//std::cout << "IMAGE TYPE: " << (int)tgaHeader.imageType << std::endl;
	//std::cout << "FIRST MAP ENTRY: " << tgaHeader.firstEntry << std::endl;
	//std::cout << "NUM MAP ENTRIES: " << tgaHeader.numEntries << std::endl;
	//std::cout << "BYTES PER ENTRY: " << (int)tgaHeader.bitsPerEntry << std::endl;
	//std::cout << "ORIGIN: " << tgaHeader.xOrigin << "," << tgaHeader.yOrigin << std::endl;
	//std::cout << "SIZE: " << tgaHeader.width << "," << tgaHeader.height << ":" << (int)tgaHeader.bitsPerPixel << std::endl;
	//std::cout << "DESCRIPTOR: " << (int)tgaHeader.descriptor << std::endl;*/

	//std::cout << "Checking Format" << std::endl;
	switch (tgaHeader.imageType)
	{
	case 0:
		tgaDesc |= TGA_NO_IMAGE;
		break;
		//case 1:
		//	tgaDesc |= TGA_MAP;
		//	break;
	case 2:
		tgaDesc |= TGA_RGB;
		break;
		//case 3:
		//	tgaDesc |= TGA_BW;
		//	break;
		//case 9:
		//	tgaDesc |= ( TGA_MAP | TGA_RLE );
		//	break;
	case 10:
		tgaDesc |= (TGA_RGB | TGA_RLE);
		break;
		//case 11:
		//	tgaDesc |= ( TGA_BW | TGA_RLE );
		//	break;
	default:
		tgaDesc |= TGA_UNSUPPORTED;
		break;
	}

	if ((tgaDesc & TGA_UNSUPPORTED) == 0)
	{
		std::cout << "TGA Format Supported" << std::endl;
	}
	else
	{
		std::cout << "TGA Format Unsupported" << std::endl;
		return UNSUPPORTED_IMAGE_FORMAT;
	}

	// Skip the ID String
	//std::cout << "Skipping ID String bytes: " << (int)tgaHeader.idLength << std::endl;
	char* skip = "";
	tgaFile.read(skip, tgaHeader.idLength);

	// Skip the colour map if it doesn't exist
	if (!(tgaDesc & TGA_MAP))
	{
		int colourMapSize = tgaHeader.colourMapType * tgaHeader.numEntries;
		//std::cout << "Skipping colour map bytes: " << colourMapSize << std::endl;
		tgaFile.read(skip, colourMapSize);
	}

	// imageDataSize is the total number of bytes taken by the image
	// after being loaded and decompressed if necessary
	int imageDataSize = tgaHeader.width * tgaHeader.height * (tgaHeader.bitsPerPixel / 8);
	pixelData = new char[imageDataSize];

	// Read the image data
	//std::cout << "Reading image data" << std::endl;
	int originalPosition = (int)tgaFile.tellg();

	// This read operation may read past the end of the file
	// so could break something (hasn't happened yet)
	tgaFile.read(pixelData, imageDataSize);
	//std::cout << "Pixel Data: " << imageDataSize << " bytes" << std::endl;

	// RLE decoding
	if (tgaDesc & TGA_RLE)
	{
		std::cout << "Decoding RLE" << std::endl;

		// Used to decode RLE
		char* tempPixelData;
		tempPixelData = new char[fileSize];

		// Copy data over for decoding
		memcpy(tempPixelData, pixelData, fileSize);

		// Holds the current pixel index for the j loop below
		int indexAccum = 0;
		int bytesPerPixel = (tgaHeader.bitsPerPixel / 8);
		int bytesPerPixelRLE = bytesPerPixel + 1;

		// Increments of i are controlled in the for loop because depending
		// on whether or not the packet being checked is run-length encoded 
		// the increment may have to be between bytesPerPixel and 128 (Max size of either packet)
		for (int i = 0; indexAccum < imageDataSize; )
		{
			// runCount holds the length of the packet taken from the packet info byte
			// runCount can be a maximum of 127.
			int runCount = (127 & tempPixelData[i]) + 1;

			// Check the packet info byte for RLE
			// Run-length encoded packet
			if (128 & tempPixelData[i])
			{
				// In an encoded packet, runCount specifies
				// the repititions of the pixel data (up to 127)
				for (int j = 0; j < runCount; j++)
				{
					for (int k = 1; k < bytesPerPixelRLE; k++)
						pixelData[indexAccum++] = tempPixelData[i + k];
				}

				i += bytesPerPixelRLE;
			}

			// Raw data packet
			else if (!(128 & tempPixelData[i]))
			{
				// Skip past the packet info byte
				i++;

				// In a raw packet, runCount specifies
				// the number of pixels that are to follow (up to 127)
				for (int j = 0; j < runCount; j++)
				{
					for (int k = 0; k < bytesPerPixel; k++)
						pixelData[indexAccum++] = tempPixelData[i + k];

					i += bytesPerPixel;
				}
			}
		}

		delete[] tempPixelData;
	}

	if (tgaDesc & TGA_RGB)
	{
		int imageDataSize = tgaHeader.width * tgaHeader.height * (tgaHeader.bitsPerPixel / 8);
		std::cout << fileName.c_str() << " loaded" << std::endl;
	}

	header.bitsPerPixel = tgaHeader.bitsPerPixel;
	header.height = tgaHeader.height;
	header.width = tgaHeader.width;

	return 0;
}
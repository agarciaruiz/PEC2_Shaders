#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture2D {
public:
	// Id for the texture obj
	unsigned int ID;
	// Image dimensions
	unsigned int Width, Height;
	// Texture format
	unsigned int InternalFormat;
	unsigned int ImageFormat;
	// Texture config
	unsigned int WrapS;
	unsigned int WrapT;
	unsigned int FilterMin;
	unsigned int FilterMax;

	// Constructor
	Texture2D();
	// Generates a texture from an image
	void Generate(unsigned int width, unsigned int height, unsigned char* data);
	// Bind texture to texture object
	void Bind() const;
};
#endif
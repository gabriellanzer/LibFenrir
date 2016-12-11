#pragma once
#include "Image.h"
#include <FreeImage.h>
#include <string>
#include <GLFW/glfw3.h>

using namespace std;
#ifndef UINT_H
typedef unsigned int uint;
#endif // !UINT_H

class IMGReader
{
public:
	IMGReader();
	~IMGReader();
	//GLint level = 0, GLint  internal_format = GL_RGB, GLint border = GL_BGR_EXT, GLenum image_format = GL_UNSIGNED_BYTE
	static Image * loadImageInToTexture(uint n, string path);
	static Image* loadPTM(uint n, string path);
	static Image* loadPPM(uint n, string path);

	static bool writeImage(Image *img, string path);
private:
};


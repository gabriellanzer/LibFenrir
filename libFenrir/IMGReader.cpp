#include "IMGReader.h"
#include <iostream>
#include <fstream>


IMGReader::IMGReader()
{
}


IMGReader::~IMGReader()
{
}

Image * IMGReader::loadImageInToTexture(uint n, string path)
{
	ifstream arq(path);

	if (!arq.is_open())
	{
		cout << "error while loading " << path << " couldn't open file\n";
		return false;
	}
	//cout << "Reading image at" << path << " ";
	arq.close();

#pragma region Format
	//Get the format with the information on the file or on the path
	FREE_IMAGE_FORMAT format = FIF_UNKNOWN;
	format = FreeImage_GetFileType(path.c_str(), 0);
	if (format == FIF_UNKNOWN)
		format = FreeImage_GetFIFFromFilename(path.c_str());
	//If not find
	if (format == FIF_UNKNOWN)
	{
		cout << "Couldn't guess image format of " << path << " \n";
		return false;
	}
	//See if FreeImage supports
	if (!FreeImage_FIFSupportsReading(format))
	{
		cout << "Image format of " << path << " not supported. \n";
 		return false;
	}
#pragma endregion
#pragma region Loading
	//	FIBITMAP *BitMap(0);
	//	int width, height;
	//
	//	//Load
	//	BitMap = FreeImage_Load(format, path.c_str());
	//
	//	if (!BitMap)
	//	{
	//		cout << "Couldn't load.\n";
	//		return false;
	//	}
	//
	//	FIBITMAP* temp = BitMap;
	//	BitMap = FreeImage_ConvertTo32Bits(BitMap);
	//	FreeImage_Unload(temp);
	//
	//	char* pixeles = (char*)FreeImage_GetBits(BitMap);
	//
	//	//get the Dimension
	//	width = FreeImage_GetWidth(BitMap);
	//	height = FreeImage_GetHeight(BitMap);
	//
	//	cout << (int)pixeles[0] << endl;
	//	cout << (int)pixeles[1] << endl;
	//	cout << (int)pixeles[2] << endl;
	//	cout << (int)pixeles[3] << endl;
	//
	//	Image *img = new Image(width, height);
	//	for (int y = 0; y < height; y++)
	//	{
	//		for (int x = 0; x < width; x++)
	//		{
	//			img->setPixel(pixeles[x + y * width + 2 ], pixeles[x + y * width + 1], pixeles[x + y * width ], pixeles[x + y * width + 3], x, y);
	//		}
	//	}

	FIBITMAP* imagen = FreeImage_Load(format, path.c_str());
	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);

	int w = FreeImage_GetWidth(imagen);
	int h = FreeImage_GetHeight(imagen);

	GLubyte* textura = new GLubyte[4 * w*h];
	char* pixeles = (char*)FreeImage_GetBits(imagen);
	//FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).

	Image *img = new Image(w, h);
	for (int j = 0; j < w*h; j++) {
		textura[j * 4 + 0] = pixeles[j * 4 + 2];
		textura[j * 4 + 1] = pixeles[j * 4 + 1];
		textura[j * 4 + 2] = pixeles[j * 4 + 0];
		textura[j * 4 + 3] = pixeles[j * 4 + 3];

		img->setPixel(textura[j * 4 + 0], textura[j * 4 + 1], textura[j * 4 + 2], textura[j * 4 + 3], j);
	}
	img->inverterVertical();
	//Now generate the OpenGL texture object 
#pragma endregion

#pragma region Setting as Texture
	glBindTexture(GL_TEXTURE_2D, n);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	GLenum huboError = glGetError();
	if (huboError) {

		cout << "There was an error loading the texture at " << path << endl;
	}

#pragma endregion

	return img;

}

Image* IMGReader::loadPTM(uint n, string path)
{
	ifstream arq(path);
	if (arq.is_open())
	{
		cout << "Reading " << path << "...";
		int w, h;
		string temp;
		arq >> temp;
		// P3
		arq >> temp;
		if (temp[0] == '#')
		{
			getline(arq, temp);
			arq >> w;
		}
		else
			w = stoi(temp);
		arq >> h;
		Image *image = new Image(w, h);
		arq >> temp;
		int r, g, b, a;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				arq >> a >> r >> g >> b;
				image->setPixel(r, g, b, a, j, i);
			}
		}

		glBindTexture(GL_TEXTURE_2D, n);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, image->getPixels());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		cout << "finished\n";
		return image;
	}

	else
		cout << path << " not found.\n";
	return false;

}

Image* IMGReader::loadPPM(uint n, string adress)
{
	ifstream arq(adress);
	if (arq.is_open())
	{
		cout << "Readig " << adress << "...\n";
		int w, h;
		string temp;
		arq >> temp;
		// P3
		arq >> temp;
		if (temp[0] == '#')
		{
			getline(arq, temp);
			arq >> w;
		}
		else
			w = stoi(temp);
		arq >> h;
		Image *image = new Image(w, h);
		arq >> temp;
		int r, g, b;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				arq >> r >> g >> b;
				image->setPixel(r, g, b, 255, j, i);
			}
		}

		glBindTexture(GL_TEXTURE_2D, n);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, image->getPixels());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		return image;
	}
	else
		cout << adress << " not found.\n";
	return false;
}

bool IMGReader::writeImage(Image * img, string path)
{
	FREE_IMAGE_FORMAT format = FIF_UNKNOWN;
	format = FreeImage_GetFileType(path.c_str(), 0);
	if (format == FIF_UNKNOWN)
		format = FreeImage_GetFIFFromFilename(path.c_str());
	//If not find
	if (format == FIF_UNKNOWN)
	{
		cout << "Couldn't guess image format of " << path << " \n";
		return false;
	}
	//See if FreeImage supports
	if (!FreeImage_FIFSupportsReading(format))
	{
		cout << "Image format of " << path << " not supported. \n";
		return false;
	}	int w = img->getWidth();
	int h = img->getHeight();
	FIBITMAP *bitmap = FreeImage_Allocate(w, h, 32);
	RGBQUAD color;	img->inverterVertical();	for (int y = 0; y < h; y++)	{		for (int x = 0; x < w; x++)		{			color.rgbRed = img->getRed(x, y);			color.rgbGreen = img->getGreen(x, y);			color.rgbBlue = img->getBlue(x, y);			color.rgbReserved = img->getAlpha(x, y);			FreeImage_SetPixelColor(bitmap, x, y, &color);		}	}	img->inverterVertical();	if (FreeImage_Save(format, bitmap, path.c_str()))	{		cout << "Image saved at " << path<< endl;	}	else	{		cout << "Couldn't save image.\n";	}
	return false;
}




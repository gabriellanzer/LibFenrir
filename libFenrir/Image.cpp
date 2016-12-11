#include "Image.h"
#include <assert.h>
#include <iostream>
using namespace std;
Image::Image(int w, int h)
{
	if (w == 0 || h == 0)
		return;
	if (w < 0 || h < 0)
	{
		cout << "size lesser than 0";
		assert(false);
	}
	width = w;
	height = h;
	pixel = new (nothrow) int[w * h];

	if (pixel == nullptr)
	{
		cout << "There was an errror while trying to alloc pointer";
		assert(false);
	}
}
Image::Image(Image *image)
{
	int w = image->getWidth();
	int h = image->getHeight();
	Image *temp = new Image(w, h);
	int size = w * h;
	if (w == 0 || h == 0)
		return;
	if (w < 0 || h < 0)
	{
		cout << "size lesser than 0";
		assert(false);
	}
	width = w;
	height = h;
	pixel = new (nothrow) int[w * h];

	if (pixel == nullptr)
	{
		cout << "There was an errror while trying to alloc pointer";
		assert(false);
	}

	for (int i = 0; i < size; i++)
	{
		pixel[i] = image->getPixels()[i];
	}


}
Image::Image(Image &image)
{
	int w = image.getWidth();
	int h = image.getHeight();
	Image *temp = new Image(w, h);
	int size = w * h;
	if (w == 0 || h == 0)
		return;
	if (w < 0 || h < 0)
	{
		cout << "size lesser than 0";
		assert(false);
	}
	width = w;
	height = h;
	pixel = new (nothrow) int[w * h];

	if (pixel == nullptr)
	{
		cout << "There was an errror while trying to alloc pointer";
		assert(false);
	}

	for (int i = 0; i < size; i++)
	{
		pixel[i] = image.getPixels()[i];
	}


}
Image::~Image()
{
	delete[] pixel;
}
void Image::setPixel(int rgb, int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
		pixel[x + y*width] = rgb;
}
void Image::setPixels(int *rgb)
{
	for (int i = 0; i < (width * height); i++)
	{
		pixel[i] = rgb[i];
	}
}
void Image::setPixel(int rgba, int n)
{
	if (n >= (width * height))
		assert(false);
	pixel[n] = rgba;
}

void Image::setPixels(int *r, int *g, int *b, int *a)
{
	for (int i = 0; i < (width * height); i++)
	{
		pixel[i] = (a[i] << 24) | (r[i] << 16) | (g[i] << 8) | (b[i]);
	}
}
void Image::plotPixel(int argb, int x, int y)
{
	if (x < 0 && x >= width)
		assert(false);

	if (y < 0 && y >= height)
		assert(false);

	pixel[x + y*width] =
		(255 << 24) |
		(CalcPlot(((pixel[x + y*width] >> 16) & 0xFF), ((argb >> 16) & 0xFF), ((argb >> 24) & 0xFF)) << 16) |
		(CalcPlot(((pixel[x + y*width] >> 8) & 0xFF), ((argb >> 8) & 0xFF), ((argb >> 24) & 0xFF)) << 8) |
		CalcPlot(((pixel[x + y*width]) & 0xFF), ((argb)& 0xFF), ((argb >> 24) & 0xFF));

}
void Image::plotPixel(int argb, int n)
{
	pixel[n] =
		(255 << 24) |
		(CalcPlot(((pixel[n] >> 16) & 0xFF), ((argb >> 16) & 0xFF), ((argb >> 24) & 0xFF)) << 16) |
		(CalcPlot(((pixel[n] >> 8) & 0xFF), ((argb >> 8) & 0xFF), ((argb >> 24) & 0xFF)) << 8) |
		CalcPlot(((pixel[n]) & 0xFF), ((argb)& 0xFF), ((argb >> 24) & 0xFF));
}
void Image::plotPixel(int r, int g, int b, int a, int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	pixel[x + y*width] =
		(255 << 24) |
		(CalcPlot(((pixel[x + y*width] >> 16) & 0xFF), r, a) << 16) |
		(CalcPlot(((pixel[x + y*width] >> 8) & 0xFF), g, a) << 8) |
		CalcPlot(((pixel[x + y*width]) & 0xFF), b, a);
}
void Image::plotPixel(int r, int g, int b, int a, int n)
{
	pixel[n] =
		(255 << 24) |
		(CalcPlot(((pixel[n] >> 16) & 0xFF), r, a) << 16) |
		(CalcPlot(((pixel[n] >> 8) & 0xFF), g, a) << 8) |
		CalcPlot(((pixel[n]) & 0xFF), b, a);
}
void Image::plotPixels(int * rgba)
{
	int size = width * height;
	for (int i = 0; i < size; i++)
	{
		plotPixel(rgba[i], i);
	}
}
void Image::setPixel(int r, int g, int b, int a, int x, int y)
{
	setPixel(((a << 24) | (r << 16) | (g << 8) | (b)), x, y);
}
void Image::setPixel(int r, int g, int b, int a, int n)
{
	setPixel((a << 24) | (r << 16) | (g << 8) | (b), n);

}

int Image::getPixel(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
		return pixel[x + y * width];
	return 0xff000000;
}
int Image::getPixelRepeat(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		return pixel[y * width + x];
	}
	else
	{
		int j, k;
		j = x / width;
		k = y / height;
		x = x - width * j;
		y = y - height * k;

		if (x < 0)
		{
			x += width;
		}
		if (y < 0)
		{
			y += height;
		}
		return pixel[y * width + x];


	}
}
int* Image::getPixels()
{
	return pixel;
}

int Image::getPixel_X(int n)
{
	return (n % width);
}
int Image::getPixel_Y(int n)
{
	return (n / width);
}

int Image::getWidth()
{
	return width;
}
int Image::getHeight()
{
	return height;
}

void Image::swap(int pos1, int pos2)
{
	int temp;
	temp = pixel[pos1];
	pixel[pos1] = pixel[pos2];
	pixel[pos2] = temp;
}
void Image::swap(int x, int y, int x2, int y2)
{
	int temp = pixel[x + width * y];
	pixel[x + width * y] = pixel[x2 + width * y2];
	pixel[x2 + width * y2] = temp;

}

/*void Image::cutImgtoImg(Image *imgfinal, int widht, int height, int *pos)
{
//*imgfinal = new Image(widht, height);
//**imgfinal = cutImg(widht, height, pos);
delete imgfinal;
imgfinal = new Image(widht, height);

if (pos == 0)
{
pos = new int[2];
pos[0] = 0;
pos[1] = 0;
}
for (int i = 0; i < 2; i++)
{
if (pos[i] < 0)
pos[i] = 0;
}
//see if you're not out of bounds
if ((pos[0] + width) > this->width)
{
cout << "Tried to acess " << pos[0] + width << "x on a Image of maximum x equals to " << this->width << endl;

widht = (this->width - pos[0]);

}
if ((pos[1] + height) > this->height)
{
cout << "Tried to acess " << pos[1] + height << "y on a Image of maximum y equals to " << this->height << endl;

height = (this->height - pos[1]);

}

for (int y = 0; y < height; y++)
{
for (int x = 0; x < width; x++)
{
imgfinal->setPixel(getPixel(x + pos[0], y + pos[1]), x, y);
}

}
} */
void Image::cutImgtoImg(Image **imgfinal, int widht, int height, int *pos, bool repeat)
{

	if (pos == 0)
	{
		pos = new int[2];
		pos[0] = 0;
		pos[1] = 0;
	}
	for (int i = 0; i < 2; i++)
	{
		if (pos[i] < 0)
			pos[i] = 0;
	}

	if (repeat)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{

				(*imgfinal)->setPixel(getPixelRepeat(x + pos[0], y + pos[1]), x, y);
			}

		}
	}
	else
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				(*imgfinal)->setPixel(getPixel(x + pos[0], y + pos[1]), x, y);
			}

		}
	}
}
Image Image::cutImg(int width, int height, int *pos, bool repeat)
{
	//if the position is not set
	if (pos == 0)
	{
		pos = new int[2];
		pos[0] = 0;
		pos[1] = 0;
	}
	for (int i = 0; i < 2; i++)
	{
		if (pos[i] < 0)
			pos[i] = 0;
	}
	Image temp(width, height);

	if (repeat)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{

				temp.setPixel(getPixelRepeat(x + pos[0], y + pos[1]), x, y);

			}

		}
	}
	else
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{

				temp.setPixel(getPixel(x + pos[0], y + pos[1]), x, y);

			}

		}

	}
	return temp;
}

void Image::plotImageTo(Image &imgfinal, int width, int height, int *pos, bool repeat)
{
	plotImageInTo(imgfinal, width, height, pos, 0, repeat);
}
/*void Image::plotImageInTo(Image &imgfinal, int width, int height, int *posOnTheActualImage, int *posF)
{
//if the width/height is not set, set it to the smallest;
if (width == 0)
{
if (imgfinal.getWidth() > this->width)
{
width = this->width;
}
else
{
width = imgfinal.getWidth();
}
} // if the widh
if (height == 0)
{
if (imgfinal.getHeight() > this->height)
{
height = this->height;
}
else
{
height = imgfinal.getHeight();
}
}

Image temp(cutImg(width, height, posOnTheActualImage));
// if the position on the Final Image is not set, set it to zero
if (posF == 0)
{
posF = new int[2];
posF[0] = 0;
posF[1] = 0;
}
for (int i = 0; i < 2; i++)
{
if (posF[i] < 0)
posF[i] = 0;
}
if ((posF[0] + width) > imgfinal.getWidth())
{
cout << "\nTrying to use the x " << (posF[0] + width) << " while the final image only have " << imgfinal.getWidth();
width = imgfinal.getWidth() - posF[0];
}
if ((posF[1] + height) > imgfinal.getHeight())
{
cout << "\nTrying to use the y " << (posF[1] + height) << " while the final image only have " << imgfinal.getHeight();
height = imgfinal.getHeight() - posF[1];
}

for (int y = 0; y < height && y < temp.getHeight(); y++)
{
for (int x = 0; x < width && x < temp.getWidth(); x++)
{
int color[3];
//calcula o plot
int alpha;
alpha = temp.getAlpha(x, y);
if (alpha != 0)
{
for (int i = 0; i < 3; i++)
{
color[i] = CalcPlot(imgfinal.getColor(posF[0] + x, posF[1] + y, i), temp.getColor(x, y, i), alpha);
}
//setcada pixel
imgfinal.setPixel(color[0], color[1], color[2], 255, posF[0] + x, posF[1] + y);
}
}
}

}*/
void Image::plotImageInTo(Image &imgfinal, int width, int height, int *pos, int *posf, bool repeat)
{
	//if the width/height is not set, set it to the smallest;
	if (width == 0)
	{
		if (imgfinal.getWidth() > this->width)
		{
			width = this->width;
		}
		else
		{
			width = imgfinal.getWidth();
		}
	}
	if (height == 0)
	{
		if (imgfinal.getHeight() > this->height)
		{
			height = this->height;
		}
		else
		{
			height = imgfinal.getHeight();
		}
	}
	if (posf == 0)
	{
		posf = new int[2];
		posf[0] = 0;
		posf[1] = 0;
	}
	if (pos == 0)
	{
		pos = new int[2];
		pos[0] = 0;
		pos[1] = 0;
	}
	for (int i = 0; i < 2; i++)
	{
		if (posf[i] < 0)
			posf[i] = 0;
		if (pos[i] < 0)
			pos[i] = 0;
	}

	int color[3];
	int alpha;
	if (repeat)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				//calcula o plot

				alpha = getAlphaRepeat(x + pos[0], y + pos[1]);
				if (alpha != 0)
				{
					for (int i = 0; i < 3; i++)
					{
						/*
						color[i] = ((imgfinal.getColor(posf[0] + x, posf[1] + y, i) * (1 - alpha)) + (getColor(x + pos[0], y + pos[1], i)));*/
						color[i] = CalcPlot(imgfinal.getColorRepeat(posf[0] + x, posf[1] + y, i), getColorRepeat(x + pos[0], y + pos[1], i), alpha);

					}
					//setcada pixel
					imgfinal.setPixel(color[0], color[1], color[2], 255, posf[0] + x, posf[1] + y);
				}
			}
		}
	}
	else
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				//calcula o plot

				alpha = getAlpha(x + pos[0], y + pos[1]);
				if (alpha != 0)
				{
					for (int i = 0; i < 3; i++)
					{
						/*color[i] = ((imgfinal.getColor(posf[0] + x, posf[1] + y, i) * (1 - alpha)) + (getColor(x + pos[0], y + pos[1], i)));*/
						color[i] = CalcPlot(imgfinal.getColor(posf[0] + x, posf[1] + y, i), getColor(x + pos[0], y + pos[1], i), alpha);
					}
					//setcada pixel
					imgfinal.setPixel(color[0], color[1], color[2], 255, posf[0] + x, posf[1] + y);
				}
			}
		}
	}

}
void Image::plotZbuffer(Image &zbuffer, int numberOfTheLayer, int width, int height, int *pos, int *posf, bool repeat)
{
	if (width == 0)
	{
		if (zbuffer.getWidth() > this->width)
		{
			width = this->width;
		}
		else
		{
			width = zbuffer.getWidth();
		}
	}
	if (height == 0)
	{
		if (zbuffer.getHeight() > this->height)
		{
			height = this->height;
		}
		else
		{
			height = zbuffer.getHeight();
		}
	}
	if (posf == 0)
	{
		posf = new int[2];
		posf[0] = 0;
		posf[1] = 0;
	}
	if (pos == 0)
	{
		pos = new int[2];
		pos[0] = 0;
		pos[1] = 0;
	}
	for (int i = 0; i < 2; i++)
	{
		if (posf[i] < 0)
			posf[i] = 0;
		if (pos[i] < 0)
			pos[i] = 0;
	}

	int alpha;
	if (repeat)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				//calcula o plot
				alpha = getAlphaRepeat(x + pos[0], y + pos[1]);
				if (alpha != 0)
				{
					zbuffer.setPixel(numberOfTheLayer, posf[0] + x, posf[1] + y);
				}
			}
		}
	}
	else
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				//calcula o plot
				alpha = getAlpha(x + pos[0], y + pos[1]);
				if (alpha != 0)
				{
					zbuffer.setPixel(numberOfTheLayer, posf[0] + x, posf[1] + y);
				}
			}
		}
	}

}
void Image::plotImageInToBasedOn(Image &imgfinal, Image &zbuffer, int numberOfTheLayer, int width, int height, int *pos, int *posf, bool repeat)
{
	if (width == 0)
	{
		if (imgfinal.getWidth() > this->width)
		{
			width = this->width;
		}
		else
		{
			width = imgfinal.getWidth();
		}
	}
	if (height == 0)
	{
		if (imgfinal.getHeight() > this->height)
		{
			height = this->height;
		}
		else
		{
			height = imgfinal.getHeight();
		}
	}
	if (posf == 0)
	{
		posf = new int[2];
		posf[0] = 0;
		posf[1] = 0;
	}
	if (pos == 0)
	{
		pos = new int[2];
		pos[0] = 0;
		pos[1] = 0;
	}
	//for (int i = 0; i < 2; i++)
	//{
	//	if (posf[i] < 0)
	//		posf[i] = 0;
	//	if (pos[i] < 0)
	//		pos[i] = 0;
	//}

	int color[3];
	int alpha;
	/*if (repeat)
	{

	for (int y = 0; y < height; y++)
	{
	for (int x = 0; x < width; x++)
	{
	// see if the current pixel is "drawable" -> on the layer or before
	if (zbuffer.getPixel(posf[0] + x, posf[1] + y) >= numberOfTheLayer)
	{
	//calcula o plot

	alpha = getAlphaRepeat(x + pos[0], y + pos[1]);
	if (alpha != 0)
	{
	for (int i = 0; i < 3; i++)
	{
	//color[i] = ((imgfinal.getColor(posf[0] + x, posf[1] + y, i) * (1 - alpha)) + (getColor(x + pos[0], y + pos[1], i)));
	color[i] = CalcPlot(imgfinal.getColor(posf[0] + x, posf[1] + y, i), getColorRepeat(x + pos[0], y + pos[1], i), alpha);
	}
	//setcada pixel
	imgfinal.setPixel(color[0], color[1], color[2], 255, posf[0] + x, posf[1] + y);
	}
	}
	else
	{
	alpha = imgfinal.getAlphaRepeat(x + posf[0], y + posf[1]);
	if (alpha != 255)
	{
	for (int i = 0; i < 3; i++)
	{
	//color[i] = ((imgfinal.getColor(posf[0] + x, posf[1] + y, i) * (1 - alpha)) + (getColor(x + pos[0], y + pos[1], i)));
	color[i] = CalcPlot(getColorRepeat(x + pos[0], y + pos[1], i), imgfinal.getColorRepeat(posf[0] + x, posf[1] + y, i), alpha);

	}
	imgfinal.setPixel(color[0], color[1], color[2], alpha, posf[0] + x, posf[1] + y);
	}

	}
	}
	}
	}
	else
	{*/
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// see if the current pixel is "drawable" -> on the layer or before
			if (zbuffer.getPixel(posf[0] + x, posf[1] + y) >= numberOfTheLayer)
			{
				//calcula o plot


				alpha = getAlpha(x + pos[0], y + pos[1]);
				if (alpha != 0)
				{
					for (int i = 0; i < 3; i++)
					{
						//color[i] = ((imgfinal.getColor(posf[0] + x, posf[1] + y, i) * (1 - alpha)) + (getColor(x + pos[0], y + pos[1], i)));
						color[i] = CalcPlot(imgfinal.getColor(posf[0] + x, posf[1] + y, i), getColor(x + pos[0], y + pos[1], i), alpha);

					}
					//setcada pixel
					imgfinal.setPixel(color[0], color[1], color[2], alpha, posf[0] + x, posf[1] + y);
				}
			}
			else
			{
				alpha = imgfinal.getAlpha(x + posf[0], y + posf[1]);
				if (alpha != 255)
				{
					for (int i = 0; i < 3; i++)
					{
						//color[i] = ((imgfinal.getColor(posf[0] + x, posf[1] + y, i) * (1 - alpha)) + (getColor(x + pos[0], y + pos[1], i)));
						color[i] = CalcPlot(getColor(x + pos[0], y + pos[1], i), imgfinal.getColor(posf[0] + x, posf[1] + y, i), alpha);

					}
					imgfinal.setPixel(color[0], color[1], color[2], alpha, posf[0] + x, posf[1] + y);
				}

			}
		}
	}
	//}

}

inline int Image::CalcPlot(int cb, int c2, int a2)
{
	float a = a2 / 255.0f;
	return (cb * (1 - a)) + (c2 * a);
}

int Image::getColor(int x, int y, int color)
{
	if (x >= 0 && x < width && y >= 0 && y < width)
		return getColor(x + y *width, color);
	else
		return 0;
}
int Image::getRed(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < width)
		return getRed(x + y * width);
	else
		return 0;
}
int Image::getGreen(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < width)
		return getGreen(x + y * width);
	else
		return 0;
}
int Image::getBlue(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < width)
		return getBlue(x + y * width);
	else
		return 0;
}
int Image::getAlpha(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < width)
		return getAlpha(x + y * width);
	else
		return 255;
}

inline int Image::getRed(int n)
{
	int i = pixel[n] >> 16 & 0x0ff;
	return i;
}
inline int Image::getGreen(int n)
{
	int i = pixel[n] >> 8 & 0x0ff;
	return i;
}
inline int Image::getBlue(int n)
{
	int i = pixel[n] & 0x0ff;
	return i;
}
inline int Image::getAlpha(int n)
{
	int i = pixel[n] >> 24 & 0x0ff;
	return i;
}
inline int Image::getColor(int n, int color)
{
	switch (color)
	{
	case 0:
		return getRed(n);
		break;
	case 1:
		return getGreen(n);
		break;
	case 2:
		return getBlue(n);
		break;
	case 3:
		return getAlpha(n);
		break;
	default:
		return 0;
	}
}

int Image::getColorRepeat(int x, int y, int color)
{
	switch (color)
	{
	case 0:
		return getRedRepeat(x, y);
		break;
	case 1:
		return getGreenRepeat(x, y);
		break;
	case 2:
		return getBlueRepeat(x, y);
		break;
	case 3:
		return getAlphaRepeat(x, y);
		break;
	default:
		return 0;
	}
}
inline int Image::getRedRepeat(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		int i = pixel[y * width + x] >> 16 & 0x0ff;
		return i;
	}
	else if (y < 0 || y >= height)  // Adaptação para funcionar o scrolling forever e não repetir imagens com menor altura.
	{
		return 0;
	}
	else
	{
		int j, k;
		j = x / width;
		k = y / height;
		x = x - width * j;
		y = y - height * k;
		int i = pixel[y * width + x] >> 16 & 0x0ff;
		return i;

	}
}
inline int Image::getGreenRepeat(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		int i = pixel[y * width + x] >> 8 & 0x0ff;
		return i;
	}
	else if (y < 0 || y >= height) // Adaptação para funcionar o scrolling forever e não repetir imagens com menor altura.
	{
		return 0;
	}
	else
	{
		int j, k;
		j = x / width;
		k = y / height;
		x = x - width * j;
		y = y - height * k;
		int i = pixel[y * width + x] >> 8 & 0x0ff;
		return i;

	}
}
inline int Image::getBlueRepeat(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		int i = pixel[y * width + x] & 0x0ff;
		return i;
	}
	else if (y < 0 || y >= height) // Adaptação para funcionar o scrolling forever e não repetir imagens com menor altura.
	{
		return 0;
	}
	else
	{
		int j, k;
		j = x / width;
		k = y / height;
		x = x - width * j;
		y = y - height * k;
		int i = pixel[y * width + x] & 0x0ff;
		return i;

	}
}
inline int Image::getAlphaRepeat(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		int i = pixel[y * width + x] >> 24 & 0x0ff;
		return i;
	}
	else if (y < 0 || y >= height)  // Adaptação para funcionar o scrolling forever e não repetir imagens com menor altura.
	{
		return 0;
	}
	else
	{
		int j, k;
		j = x / width;
		k = y / height;
		x = x - width * j;
		y = y - height * k;
		int i = pixel[y * width + x] >> 24 & 0x0ff;
		return i;

	}
}
int * Image::at(int x, int y)
{
	return &pixel[x + y *width];
}
int*Image::at(int n)
{
	if (n >= 0 && n < (width * height))
		return &pixel[n];
	//cout << "out of range";
	return 0;
}

void Image::inverterVertical()
{

	int max = (height);
	int maxmeio = (height / 2);
	/*for (int i = 0; i < maxmeio; i++)
	image.swap(i, (max - 1) - i);*/
	for (int y = 0; y < maxmeio; y++)
	{
		for (int x = 0; x < width; x++)
			swap(x, y, x, (max - 1) - y);
	}
}

#pragma once
#include <string>
#include <ctime>
#include <iostream>
using namespace std;


class Image
{
public:

	Image(int w, int h);
	Image(Image *);
	Image(Image &);
	~Image();

	void setPixel(int argb, int x, int y);
	void setPixel(int argb, int n);
	void setPixel(int r, int g, int b, int a, int x, int y);
	void setPixel(int r, int g, int b, int a, int n);
	void setPixels(int *rgba);
	void setPixels(int *r, int *g, int *b, int *a = NULL);

	void plotPixel(int argb, int x, int y);
	void plotPixel(int argb, int n);
	void plotPixel(int r, int g, int b, int a, int x, int y);
	void plotPixel(int r, int g, int b, int a, int n);
	void plotPixels(int *rgba);

	
	int getPixel(int x, int y);
	int*getPixels();
	int getPixel_X(int n);
	int getPixel_Y(int n);
	int getPixelRepeat(int x, int y);

	int getColor(int x, int y, int color);
	int getRed(int x, int y);
	int getGreen(int x, int y);
	int getBlue(int x, int y);
	int getAlpha(int x, int y);
	int getColor(int n, int color);

	int getColorRepeat(int x, int y, int color);
	inline int getRedRepeat(int x, int y);
	inline int getGreenRepeat(int x, int y);
	inline int getBlueRepeat(int x, int y);
	inline int getAlphaRepeat(int x, int y);

	inline int getRed(int n);
	inline int getGreen(int n);
	inline int getBlue(int n);
	inline int getAlpha(int n);

	int getWidth();
	int getHeight();

	void swap(int pos1, int pos2);
	void swap(int x, int y, int x2, int y2);

	void cutImgtoImg(Image **imgfinal, int width, int height, int *pos = 0, bool repeat= false);
	
	Image cutImg(int width,  int height , int *pos = 0, bool repeat = false);

	void plotImageTo(Image &imgfinal, int width, int height, int *pos, bool repeat = false);
	void plotImageInTo(Image &imgfinal, int width, int height, int *posOnTheCurrentImage = 0, int *posOnTheFinalImage = 0, bool repeat = false);
	void plotZbuffer(Image &zbuffer, int numberOfTheLayer, int width, int height, int *posOnTheCurrentImage = 0, int *posOnTheFinalImage = 0, bool repeat = false);
	void plotImageInToBasedOn(Image &imgfinal, Image &zbuffer, int numberOfTheLayer, int width, int height, int *posOnTheCurrentImage = 0, int *posOnTheFinalImage = 0, bool repeat = false);

	inline int CalcPlot(int colorbase, int colorOverLay, int AlphaOverLay);
	
	int *at(int x, int y);
	int *at(int n);

	void inverterVertical();
private:
	int *pixel;
	int width, height;
};


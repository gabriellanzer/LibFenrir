#pragma once
#ifndef PrimitiveDrawer_H
#define PrimitiveDrawer_H
#include <stack>
#include "Image.h"
#include "Primitives.h"


class PrimitiveDrawer
{
public:
	static PrimitiveDrawer *Instantiate();
	~PrimitiveDrawer();
	void drawPoint(Image &img, Point &p);
	void drawPoint(Image &img, int x, int y, int*cor);
	void plotPoint(Image &img, Point &p);

	void drawLine(Image &img, int x1, int y1, int x2, int y2, int color); // x1 <= x2 && y1 <= y2
	void drawLine(Image &img, int x1, int y1, int x2, int y2, int *color);

	void drawLine(Image &img, Point p1, Point p2);

	void plotLine(Image &img, int x1, int y1, int x2, int y2, int *color);
	void plotLine(Image &img, Point p1, Point p2);

	void drawRect(Image &img, int x1, int y1, int x2, int y2, int color, bool paint = false);
	void drawRect(Image &img, int x1, int y1, int x2, int y2, int *color, bool paint = false);
	void drawRect(Image &img, LRectangle &r, bool paint = true);

	void plotRect(Image &img, int x1, int y1, int x2, int y2, int *color);
	void plotRect(Image &img, LRectangle &r);

	void drawPolygon(Image &img, Point *p, int numberOfPoints, bool paint = false);
	void drawPolygon(Image &img, LPolygon &p, bool pintar = false);

	void plotPolygon(Image &img, Point *p, int numberOfPoints);
	void plotPolygon(Image &img, LPolygon &p);

	void drawEllipse(Image &img, int n, int cx, int cy, int rx, int ry, int *color, bool paint = false);
	//void drawEllipse(Ellipse e);

	void plotEllipse(Image &img, int n, int cx, int cy, int rx, int ry, int *color);

	void drawBrush(Image *img, int cx, int cy, int brushSize, int &color, float focus = 1.0f);
	void drawBrushPixel(Image *img, int cx, int cy, int x, int y, int brushSize, int &color, float focus = 1.0f);

	//void plotEllipse(Ellipse e);

	/*void Fill(Image &img, LPolygon polygon, int *fillColor = 0, int *backcolor = intToPointer(0,0,0,255));
	void Fill(Image &img, LRectangle rectangle, int *fillColor = 0, int *backcolor = intToPointer(0, 0, 0, 255));
	void Fill(Image &img, Point *points, int numberOfPoints, int *fillColor = 0, int *backcolor = intToPointer(0, 0, 0, 255));*/
	
	

	void Fill(Image &img, int x, int y, int color, int backcolor);
	//void Fill(Image &img, int x, int y, int *color, int *backcolor);
	//void FillPlot(Image &img, int x, int y, int *color, int *BoardColor);

	
private:
	static PrimitiveDrawer *instace;
	PrimitiveDrawer();

	//Auxiliar functions
	float max(float a, float b)
	{
		if (a > b)
			return a;
		else
			return b;
	}

	float min(float a, float b)
	{
		if (a < b)
			return a;
		else
			return b;
	}
};

#endif

#define gPritiveDrawer PrimitiveDrawer::Instantiate()
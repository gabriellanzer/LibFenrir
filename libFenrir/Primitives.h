#ifndef Primitive_H
#define Primitive_H

#define PI 3.141592635898
struct Point
{

	int x, y;
	//int *_color;
	int *_color, color; // Uso excessivo de memória :V


	void setcolor(int red, int green, int blue, int alpha)
	{
		_color = new int[4];
		_color[0] = red;
		_color[1] = green;
		_color[2] = blue;
		_color[3] = alpha;
		color = (alpha << 24) | (red << 16) | (green << 8) | (blue);
	}
	void set(int xi, int yi, int red, int green, int blue, int alpha = 255)
	{
		x = xi;
		y = yi;
		setcolor(red, green, blue, alpha);
	}

	inline int getAlpha()
	{
		return (color >> 24 & 0x0ff);
	}
	inline int getRed()
	{
		return (color >> 16 & 0x0ff);
	}
	inline int getGreen()
	{
		return (color >> 8 & 0x0ff);
	}
	inline int getBlue()
	{
		return (color & 0x0ff);
	}

};
struct LRectangle
{
	Point p[2];

	void set(int x1, int y1, int x2, int y2, int red, int green, int blue, int alpha)
	{
		p[0].set(x1, y1, red, green, blue, alpha);
		p[1].set(x2, y2, red, green, blue, alpha);
	}
};
struct LPolygon
{
	Point* p;
	int numberOfPoints;
	void Init()
	{
		p = 0;
		numberOfPoints = 0;
	}
	void set(Point *pi, int numberOfPoints)
	{
		this->numberOfPoints = numberOfPoints;
		p = new Point[numberOfPoints];
		for (int i = 0; i < numberOfPoints; i++)
			p[i] = pi[i];
	}
	void createEllipse(int ni, int cxi, int cyi, int rxi, int ryi, int *color)
	{
		numberOfPoints = ni;
		float inc = 1 / float(ni);
		int j = 0;
		p = new Point[ni];
		float angle;
		for (float i = 0; i < 1; i += inc, j++)
		{
			angle = 2 * PI *i;
			p[j].set(cos(angle)*rxi + cxi, sin(angle)*ryi + cyi, color[0], color[1], color[2], color[3]);
		}

	}
	void addPoint(int x, int y, int red, int green, int blue, int alpha)
	{
		if (p != 0)
		{
			Point *temp = new Point[numberOfPoints];
			for (int i = 0; i < numberOfPoints; i++)
				temp[i] = p[i];
			delete[]p;
			p = new Point[numberOfPoints + 1];
			for (int i = 0; i < numberOfPoints; i++)
				p[i] = temp[i];
			p[numberOfPoints].set(x, y, red, green, blue, alpha);
			numberOfPoints++;
		}
		else
		{
			p = new Point[1];
			p[numberOfPoints].set(x, y, red, green, blue, alpha);
			numberOfPoints++;
		}


	}
	void clear()
	{
		if (p != 0)
			delete[]p;
		p = 0;
		numberOfPoints = 0;

	}
};
#endif
#include "PrimitiveDrawer.h"
#include "glm\glm.hpp"
//#include "maths_funcs.h"

PrimitiveDrawer* PrimitiveDrawer::instace = nullptr;
PrimitiveDrawer::PrimitiveDrawer()
{
}


PrimitiveDrawer * PrimitiveDrawer::Instantiate()
{
	if (instace == nullptr)
		instace = new PrimitiveDrawer();
	return instace;
}

PrimitiveDrawer::~PrimitiveDrawer()
{
}

void PrimitiveDrawer::drawLine(Image &img, int x1, int y1, int x2, int y2, int color) // x1 <= x2 && y1 <= y2
{

	if (x1 == x2)
	{
		if (y2 < y1)
		{
			int t = y2;
			y2 = y1;
			y1 = t;
		}
		for (int i = y1; i < y2; i++)
		{
			img.setPixel(color, x1, i);
		}
	}
	else if (y1 == y2)
	{
		if (x2 < x1)
		{
			int t = x2;
			x2 = x1;
			x1 = t;
		}
		for (int i = x1; i < x2; i++)
		{
			img.setPixel(color, i, y1);
		}
	}
	else
	{
		if (x2 < x1)
		{
			int t = x2;
			x2 = x1;
			x1 = t;
			t = y2;
			y2 = y1;
			y1 = t;
		}

		float dx = abs(x2 - x1);
		float dy = abs(y2 - y1);
		float error = 0;
		float d = dy / dx;
		int y = y1;
		for (int i = x1; i < x2; i++)
		{
			img.setPixel(color, i, y);

			error += d;
			while (error >= 0.5)
			{
				if (y1 > y2)
					y--;
				else
					y++;

				error -= 1;
				img.setPixel(color, i, y);

			}
		}

	}

}
void PrimitiveDrawer::drawLine(Image &img, int x1, int y1, int x2, int y2, int *color)
{
	if (x1 == x2)
	{
		if (y2 < y1)
		{
			int t = y2;
			y2 = y1;
			y1 = t;
		}
		for (int i = y1; i < y2; i++)
		{
			img.setPixel(color[0], color[1], color[2], 255, x1, i);
		}
	}
	else if (y1 == y2)
	{
		if (x2 < x1)
		{
			int t = x2;
			x2 = x1;
			x1 = t;
		}
		for (int i = x1; i < x2; i++)
		{
			img.setPixel(color[0], color[1], color[2], 255, i, y1);
		}
	}
	else
	{
		if (x2 < x1)
		{
			int t = x2;
			x2 = x1;
			x1 = t;
			t = y2;
			y2 = y1;
			y1 = t;
		}
		float dx = abs(x2 - x1);
		float dy = abs(y2 - y1);
		float error = 0;
		float d = dy / dx;
		int y = y1;
		for (int i = x1; i < x2; i++)
		{
			img.setPixel(color[0], color[1], color[2], 255, i, y);

			error += d;
			while (error >= 0.5)
			{
				if (y1 > y2)
					y--;
				else
					y++;
				error -= 1;
				img.setPixel(color[0], color[1], color[2], 255, i, y);
			}
		}
	}
}
void PrimitiveDrawer::drawLine(Image &img, Point p1, Point p2)
{
	if (p1.x == p2.x)
	{
		if (p2.y < p1.y)
		{
			int t = p2.y;
			p2.y = p1.y;
			p1.y = t;
		}
		for (int i = p1.y; i < p2.y; i++)
		{
			img.setPixel(p1._color[0], p1._color[1], p1._color[2], 255, p1.x, i);
		}
	}
	else if (p1.y == p2.y)
	{
		if (p2.x < p1.x)
		{
			int t = p2.x;
			p2.x = p1.x;
			p1.x = t;

		}
		for (int i = p1.x; i < p2.x; i++)
		{
			img.setPixel(p1._color[0], p1._color[1], p1._color[2], 255, i, p1.y);
		}
	}
	else
	{
		if (p2.x < p1.x)
		{
			int t = p2.x;
			p2.x = p1.x;
			p1.x = t;
			t = p2.y;
			p2.y = p1.y;
			p1.y = t;
		}

		float dx = abs(p2.x - p1.x);
		float dy = abs(p2.y - p1.y);
		float error = 0;
		float d = dy / dx;


		int y = p1.y;
		for (int i = p1.x; i < p2.x; i++)
		{
			img.setPixel(p1._color[0], p1._color[1], p1._color[2], 255, i, y);
			error += d;
			while (error >= 0.5)
			{
				if (p1.y > p2.y)
					y--;
				else
					y++;
				error -= 1;
				img.setPixel(p1._color[0], p1._color[1], p1._color[2], 255, i, y);
			}
		}
	}
}
void PrimitiveDrawer::plotLine(Image &img, int x1, int y1, int x2, int y2, int *color)
{
	if (x1 == x2)
	{
		if (y2 < y1)
		{
			int t = y2;
			y2 = y1;
			y1 = t;

		}
		for (int i = y1; i < y2; i++)
		{
			img.plotPixel(color[0], color[1], color[2], color[3], x1, i);
		}
	}
	else if (y1 == y2)
	{
		if (x2 < x1)
		{
			int t = x2;
			x2 = x1;
			x1 = t;

		}
		for (int i = x1; i < x2; i++)
		{
			img.plotPixel(color[0], color[1], color[2], color[3], i, y1);
		}
	}
	else
	{
		if (x2 < x1)
		{
			int t = x2;
			x2 = x1;
			x1 = t;
			t = y2;
			y2 = y1;
			y1 = t;
		}
		float dx = abs(x2 - x1);
		float dy = abs(y2 - y1);
		float error = 0;
		float d = dy / dx;
		int y = y1;
		for (int i = x1; i < x2; i++)
		{
			img.plotPixel(color[0], color[1], color[2], color[3], i, y);

			error += d;
			while (error >= 0.5)
			{

				if (y1 > y2)
					y--;
				else
					y++;
				error -= 1;
				img.plotPixel(color[0], color[1], color[2], color[3], i, y1);
			}
		}
	}
}
void PrimitiveDrawer::plotLine(Image &img, Point p1, Point p2)
{
	if (p1.x == p2.x)
	{
		if (p2.y < p1.y)
		{
			int t = p2.y;
			p2.y = p1.y;
			p1.y = t;
		}

		for (int i = p1.y; i < p2.y; i++)
		{
			img.plotPixel(p1.color, p1.x, i);
		}
	}
	else if (p1.y == p2.y)
	{
		if (p2.x < p1.x)
		{
			int t = p2.x;
			p2.x = p1.x;
			p1.x = t;
		}
		for (int i = p1.x; i < p2.x; i++)
		{
			img.plotPixel(p1.color, i, p1.y);


		}
	}
	else
	{
		if (p2.x < p1.x)
		{
			int t = p2.x;
			p2.x = p1.x;
			p1.x = t;
			t = p2.y;
			p2.y = p1.y;
			p1.y = t;
		}
		float dx = abs(p2.x - p1.x);
		float dy = abs(p2.y - p1.y);
		float error = 0;
		float d = dy / dx;
		int y = p1.y;
		for (int i = p1.x; i < p2.x; i++)
		{
			img.plotPixel(p1.color, i, y);


			error += d;
			while (error >= 0.5)
			{
				if (p1.y > p2.y)
					y--;
				else
					y++;
				error -= 1;
				img.plotPixel(p1.color, i, y);
			}
		}
	}
}

void PrimitiveDrawer::drawPoint(Image &img, Point &p)
{
	img.setPixel(p.color, p.x, p.y);
}
void PrimitiveDrawer::drawPoint(Image &img, int x, int y, int*cor)
{
	img.setPixel(cor[0], cor[1], cor[2], cor[3], x, y);
}
void PrimitiveDrawer::plotPoint(Image &img, Point &p)
{
	img.plotPixel(p.color, p.x, p.y);
}

void PrimitiveDrawer::drawRect(Image &img, int x1, int y1, int x2, int y2, int color, bool paint)
{
	if (x1 > x2)
	{
		int t = x1;
		x1 = x2;
		x2 = t;
	}
	if (y1 > y2)
	{
		int t = y1;
		y1 = y2;
		y2 = t;
	}
	for (int y = y1; y < y2; y++)
	{
		img.setPixel(color, x1, y);
		img.setPixel(color, x2, y);
	}
	for (int x = x1; x < x2; x++)
	{
		img.setPixel(color, x, y1);
		img.setPixel(color, x, y2);
	}
	int x, y;
	if (x1 > x2)
	{
		x = x2;
	}
	else
	{
		x = x1;

	}

	if (y2 > y1)
	{
		y = y1;
	}
	else
	{
		y = y1;

	}
	if (paint)
		Fill(img, x + abs((x1 - x2) / 2), y + abs((y1 - y2) / 2), color, 0x000000ff);
}
void PrimitiveDrawer::drawRect(Image &img, int x1, int y1, int x2, int y2, int *color, bool paint)
{
	if (x1 > x2)
	{
		int t = x1;
		x1 = x2;
		x2 = t;
	}
	if (y1 > y2)
	{
		int t = y1;
		y1 = y2;
		y2 = t;
	}
	for (int y = y1; y < y2; y++)
	{
		img.setPixel(color[0], color[1], color[2], 255, x1, y);
		img.setPixel(color[0], color[1], color[2], 255, x2, y);
	}
	for (int x = x1; x < x2; x++)
	{
		img.setPixel(color[0], color[1], color[2], 255, x, y1);
		img.setPixel(color[0], color[1], color[2], 255, x, y2);
	}
	int x, y;
	if (x1 > x2)
	{
		x = x2;
	}
	else
	{
		x = x1;

	}

	if (y2 > y1)
	{
		y = y1;
	}
	else
	{
		y = y1;

	}
	if (paint)
		Fill(img, x + abs((x1 - x2) / 2), y + abs((y1 - y2) / 2), (color[3] << 24 | color[0] << 16 | color[1] << 8 | color[2]), 255 << 16);
}
void PrimitiveDrawer::drawRect(Image &img, LRectangle &r, bool paint)
{
	if (r.p[0].x > r.p[1].x)
	{
		int t = r.p[0].x;
		r.p[0].x = r.p[1].x;
		r.p[1].x = t;
	}
	if (r.p[0].y > r.p[1].y)
	{
		int t = r.p[0].y;
		r.p[0].y = r.p[1].y;
		r.p[1].y = t;
	}
	for (int y = r.p[0].y; y < r.p[1].y; y++)
	{
		img.setPixel(r.p[0].color, r.p[0].x, y);
		img.setPixel(r.p[0].color, r.p[1].x, y);
	}
	for (int x = r.p[0].x; x < r.p[1].x; x++)
	{
		img.setPixel(r.p[0].color, x, r.p[0].y);
		img.setPixel(r.p[0].color, x, r.p[1].y);
	}
	int x, y;
	if (r.p[0].x > r.p[1].x)
	{
		x = r.p[1].x;
	}
	else
	{
		x = r.p[0].x;

	}

	if (r.p[0].y > r.p[1].y)
	{
		y = r.p[1].y;
	}
	else
	{
		y = r.p[0].y;

	}
	if (paint)
		Fill(img, x + abs((r.p[0].x - r.p[1].x) / 2), y + abs((r.p[0].y - r.p[1].y) / 2), r.p[0].color, 255 << 16);

}
void PrimitiveDrawer::plotRect(Image &img, int x1, int y1, int x2, int y2, int *color)
{
	if (x1 > x2)
	{
		int t = x1;
		x1 = x2;
		x2 = t;
	}
	if (y1 > y2)
	{
		int t = y1;
		y1 = y2;
		y2 = t;
	}
	for (int y = y1; y < y2; y++)
	{
		img.plotPixel(color[0], color[1], color[2], color[3], x1, y);
		img.plotPixel(color[0], color[1], color[2], color[3], x2, y);
	}
	for (int x = x1; x < x2; x++)
	{
		img.plotPixel(color[0], color[1], color[2], color[3], x, y1);
		img.plotPixel(color[0], color[1], color[2], color[3], x, y2);
	}


}
void PrimitiveDrawer::plotRect(Image &img, LRectangle &r)
{
	if (r.p[0].x > r.p[1].x)
	{
		int t = r.p[0].x;
		r.p[0].x = r.p[1].x;
		r.p[1].x = t;
	}
	if (r.p[0].y > r.p[1].y)
	{
		int t = r.p[0].y;
		r.p[0].y = r.p[1].y;
		r.p[1].y = t;
	}
	for (int y = r.p[0].y; y < r.p[1].y; y++)
	{
		img.plotPixel(r.p[0].color, r.p[0].x, y);
		img.plotPixel(r.p[1].color, r.p[1].x, y);
	}
	for (int x = r.p[0].x; x < r.p[1].x; x++)
	{
		img.plotPixel(r.p[0].color, x, r.p[0].y);
		img.plotPixel(r.p[0].color, x, r.p[1].y);
	}

}

void PrimitiveDrawer::drawPolygon(Image &img, Point *p, int n, bool paint)
{
	if (n > 0)
	{
		Point max, min;
		max.x = p[0].x;
		min.x = p[0].x;
		max.y = p[0].y;
		min.y = p[0].y;
		for (int i = 0; i < (n - 1); i++)
		{
			drawLine(img, p[i], p[i + 1]);
			if (max.x < p[i].x)
			{
				max.x = p[i].x;
			}
			else if (min.x > p[i].x)
			{
				min.x = p[i].x;
			}

			if (max.y < p[i].y)
			{
				max.y = p[i].y;
			}
			else if (min.y > p[i].y)
			{
				min.y = p[i].y;
			}
		}
		drawLine(img, p[n - 1], p[0]);
		if (paint)
			Fill(img, min.x + abs(max.x - min.x) / 2, min.y + abs(max.y - min.y) / 2, p[0].color, 255 << 24);
	}
}
void PrimitiveDrawer::drawPolygon(Image &img, LPolygon &p, bool paint)
{
	if (p.numberOfPoints > 0)
	{


		Point max, min;

		max.x = p.p[0].x;
		min.x = p.p[0].x;
		max.y = p.p[0].y;
		min.y = p.p[0].y;

		for (int i = 0; i < (p.numberOfPoints - 1); i++)
		{
			drawLine(img, p.p[i], p.p[i + 1]);


			if (max.x < p.p[i].x)
			{
				max.x = p.p[i].x;
			}
			else if (min.x > p.p[i].x)
			{
				min.x = p.p[i].x;
			}

			if (max.y < p.p[i].y)
			{
				max.y = p.p[i].y;
			}
			else if (min.y > p.p[i].y)
			{
				min.y = p.p[i].y;
			}

		}

		drawLine(img, p.p[p.numberOfPoints - 1], p.p[0]);
		if (paint)
			Fill(img, min.x + (abs(max.x - min.x)) / 2.0, min.y + abs((max.y - min.y)) / 2.0, p.p[0].color, 255 << 24);
	}
}
void PrimitiveDrawer::plotPolygon(Image &img, Point *p, int n)
{
	for (int i = 0; i < (n - 1); i++)
	{
		plotLine(img, p[i], p[i + 1]);


	}
	plotLine(img, p[n - 1], p[0]);

}
void PrimitiveDrawer::plotPolygon(Image &img, LPolygon &p)
{
	if (p.numberOfPoints > 0)
	{

		for (int i = 0; i < (p.numberOfPoints - 1); i++)
		{
			plotLine(img, p.p[i], p.p[i + 1]);


		}
		plotLine(img, p.p[p.numberOfPoints - 1], p.p[0]);





	}
}

void  PrimitiveDrawer::drawEllipse(Image &img, int ni, int cxi, int cyi, int rxi, int ryi, int *color, bool paint)
{
	float inc = 1 / ni;
	int j = 0;
	LPolygon pol;
	pol.p = new Point[ni];
	float angle;
	for (float i = 0; i < 1; i += inc)
	{
		angle = 2 * PI *i;
		pol.p[j].set(cos(angle)*rxi + cxi, sin(angle)*ryi + cyi, color[0], color[1], color[2], color[3]);
	}
	drawPolygon(img, pol);

	if (paint)
		Fill(img, cxi, cyi, (color[3] << 24 | color[0] << 16 | color[1] << 8 | color[2]), 255 << 24);
}
void PrimitiveDrawer::plotEllipse(Image &img, int ni, int cxi, int cyi, int rxi, int ryi, int *color)
{
	float inc = 1 / ni;
	int j = 0;
	LPolygon pol;
	pol.p = new Point[ni];
	float angle;
	for (float i = 0; i < 1; i += inc)
	{
		angle = 2 * PI *i;
		pol.p[j].set(cos(angle)*rxi + cxi, sin(angle)*ryi + cyi, color[0], color[1], color[2], color[3]);
	}
	plotPolygon(img, pol);
}

void PrimitiveDrawer::Fill(Image &img, int x, int y, int color, int backcolor)
{
	stack<int*> stock;
	stack<int> temp;
	stock.push(img.at(x, y));
	temp.push(x + y * img.getWidth());

	while (!stock.empty())
	{
		if (stock.top() != 0)
		{

			if (*stock.top() == backcolor)
			{
				*stock.top() = color;

				int  a = temp.top();

				stock.pop();
				temp.pop();

				temp.push(a + 1);//x+
				stock.push(img.at(a + 1));

				temp.push(a - 1);//x-
				stock.push(img.at(a - 1));

				temp.push(a + img.getWidth());//y+
				stock.push(img.at(a + img.getWidth()));

				temp.push(a - img.getWidth());//y-
				stock.push(img.at(a - img.getWidth()));

			}
			else
			{
				stock.pop();
				temp.pop();
			}
		}
		else
		{
			stock.pop();
			temp.pop();
		}
	}
	cout << "Finished. \n";
}

void PrimitiveDrawer::drawBrush(Image *img, int cx, int cy, int brushSize, int &color, float focus)
{
	//y = (sqrt(r^2-x^2))/r
	float radius = brushSize*0.5f;
	float root1 = -radius;
	float root2 = radius;

	for (float x = root1; x <= root2; x++)
	{
		for (float y = root1; y < root2; y++)
		{
			float opacity = sqrt(pow(radius, 2) - pow(x, 2) - pow(y, 2)) / radius*focus; //Create a function based on brush size

			//Imaginary check, for when x,y gives a point out of the hemi-sphere
			if (isnan(opacity))
				opacity = 0;
			else
				opacity = glm::clamp<float>(opacity, 0, 1);

			int newColor = (((int)(opacity * 255) << 24) | 0x00ffffff) & color;

			if ((cx + x) >= 0 && (cx + x) < img->getWidth() && (cy + y) >= 0 && (cy + y) < img->getHeight())
				img->plotPixel(newColor, cx + x, cy + y);
		}

	}

}

void PrimitiveDrawer::drawBrushPixel(Image *img, int cx, int cy, int x, int y, int brushSize, int & color, float focus)
{
	//y = (sqrt(r^2-x^2))/r
	float radius = brushSize*0.5f;
	float root1 = -radius;
	float root2 = radius;

	float opacity = sqrt(pow(radius, 2) - pow(x, 2) - pow(y, 2)) / radius*focus; //Create a function based on brush size

	//Imaginary check, for when x,y gives a point out of the hemi-sphere
	if (isnan(opacity))
		opacity = 0;
	else
		opacity = glm::clamp<float>(opacity, 0, 1);

	int newColor = ((int)(opacity * 255) << 24 | 0x00ffffff) & color;

	if ((cx + x) >= 0 && (cx + x) < img->getWidth() && (cy + y) >= 0 && (cy + y) < img->getHeight())
		img->plotPixel(newColor, cx + x, cy + y);
}

//void PrimitiveDrawer::Fill(Image &img, int x, int y, int color, int backcolor)
//{
//	stack<int*> stock;
//	stack<int> temp;
//	stock.push(img.at(x, y));
//	temp.push(x + y * img.getWidth());
//
//	while (!stock.empty())
//	{
//		if (stock.top() != 0)
//		{
//
//			if (*stock.top() == backcolor)
//			{
//				*stock.top() = color;
//
//				int  a = temp.top();
//
//				stock.pop();
//				temp.pop();
//
//				temp.push(a + 1);//x+
//				stock.push(img.at(a + 1));
//
//				temp.push(a - 1);//x-
//				stock.push(img.at(a - 1));
//
//				temp.push(a + img.getWidth());//y+
//				stock.push(img.at(a + img.getWidth()));
//
//				temp.push(a - img.getWidth());//y-
//				stock.push(img.at(a - img.getWidth()));
//
//			}
//			else
//			{
//				stock.pop();
//				temp.pop();
//			}
//		}
//		else
//		{
//			stock.pop();
//			temp.pop();
//		}
//	}
//	cout << "Finished. \n";
//
//}
//void PrimitiveDrawer::Fill(Image &img, int x, int y, int *color, int *backcolor)
//{
//	if (backcolor == 0)
//	{
//		backcolor = new int[4];
//		backcolor[Red] = 0;
//		backcolor[Green] = 0;
//		backcolor[Blue] = 0;
//		backcolor[Alpha] = 255;
//	}
//	cout << "Started Filling\n";
//	int c = (color[3] << 24) | (color[0] << 16) | (color[1] << 8) | (color[2]), cf = (backcolor[3] << 24) | (backcolor[0] << 16) | (backcolor[1] << 8) | (backcolor[2]);
//	stack<int*> stock;
//	stack<int> temp;
//	if (x < img.getWidth() && y < img.getHeight())
//	{
//		temp.push(x + y * img.getWidth());
//		stock.push(img.at(temp.top()));
//	}
//
//	while (!stock.empty())
//	{
//		if (stock.top() != 0)
//		{
//
//			if (*stock.top() == cf)
//			{
//				*stock.top() = c;
//
//				int  a = temp.top();
//
//				stock.pop();
//				temp.pop();
//
//				
//				temp.push(a + 1);//x+
//				stock.push(img.at(a + 1));
//
//				temp.push(a - 1);//x-
//				stock.push(img.at(a - 1));
//
//				temp.push(a + img.getWidth());//y+
//				stock.push(img.at(a + img.getWidth()));
//
//				temp.push(a - img.getWidth());//y-
//				stock.push(img.at(a - img.getWidth()));
//
//			}
//			else
//			{
//				stock.pop();
//				temp.pop();
//			}
//		}
//		else
//		{
//			stock.pop();
//			temp.pop();
//		}
//	}
//	cout << "Finished. \n";
//
//
//}

//void PrimitiveDrawer::Fill(Image &img, LPolygon p, int *fillColor, int *backcolor)
//{
//	if (p.numberOfPoints > 0)
//	{
//		Point max, min;
//
//		max.x = p.p[0].x;
//		min.x = p.p[0].x;
//		max.y = p.p[0].y;
//		min.y = p.p[0].y;
//
//		for (int i = 0; i < (p.numberOfPoints - 1); i++)
//		{
//			drawLine(img, p.p[i], p.p[i + 1]);
//
//
//			if (max.x < p.p[i].x)
//			{
//				max.x = p.p[i].x;
//			}
//			else if (min.x > p.p[i].x)
//			{
//				min.x = p.p[i].x;
//			}
//
//			if (max.y < p.p[i].y)
//			{
//				max.y = p.p[i].y;
//			}
//			else if (min.y > p.p[i].y)
//			{
//				min.y = p.p[i].y;
//			}
//
//		}
//		if (fillColor == 0)
//			Fill(img, min.x + (abs(max.x - min.x)) / 2.0, min.y + abs((max.y - min.y)) / 2.0, p.p[0]._color, backcolor);
//		else
//			Fill(img, min.x + (abs(max.x - min.x)) / 2.0, min.y + abs((max.y - min.y)) / 2.0, fillColor, backcolor);
//	}
//
//}
//void PrimitiveDrawer::Fill(Image &img, Point *p, int n, int *fillColor, int *backcolor)
//{
//	Point max, min;
//
//	max.x = p[0].x;
//	min.x = p[0].x;
//	max.y = p[0].y;
//	min.y = p[0].y;
//	for (int i = 0; i < (n - 1); i++)
//	{
//		if (max.x < p[i].x)
//		{
//			max.x = p[i].x;
//		}
//		else if (min.x > p[i].x)
//		{
//			min.x = p[i].x;
//		}
//
//		if (max.y < p[i].y)
//		{
//			max.y = p[i].y;
//		}
//		else if (min.y > p[i].y)
//		{
//			min.y = p[i].y;
//		}
//	}
//	if (fillColor == 0)
//		Fill(img, min.x + abs(max.x - min.x) / 2, min.y + abs(max.y - min.y) / 2, p[0]._color, backcolor);
//	else
//		Fill(img, min.x + (abs(max.x - min.x)) / 2.0, min.y + abs((max.y - min.y)) / 2.0, fillColor, backcolor);
//	/*if (min.x + (abs(max.x - min.x)) / 2.0 == 0)
//		cout << "opa";
//		if (fillColor == 0)
//		drawPoint(img, min.x + (abs(max.x - min.x)) / 2.0, min.y + abs((max.y - min.y)) / 2.0, p[0]._color);
//		else
//		drawPoint(img, min.x + (abs(max.x - min.x)) / 2.0, min.y + abs((max.y - min.y)) / 2.0, fillColor); */
//}
//void PrimitiveDrawer::Fill(Image &img, LRectangle r, int *fillColor, int *backcolor)
//{
//	int x, y;
//	if (r.p[0].x > r.p[1].x)
//	{
//		x = r.p[1].x;
//	}
//	else
//	{
//		x = r.p[0].x;
//
//	}
//
//	if (r.p[0].y > r.p[1].y)
//	{
//		y = r.p[1].y;
//	}
//	else
//	{
//		y = r.p[0].y;
//
//	}
//	if (fillColor == 0)
//		Fill(img, x + abs((r.p[0].x - r.p[1].x) / 2), y + abs((r.p[0].y - r.p[1].y) / 2), r.p[0]._color, backcolor);
//	else
//		Fill(img, x + abs((r.p[0].x - r.p[1].x) / 2), y + abs((r.p[0].y - r.p[1].y) / 2), fillColor, backcolor);
//}

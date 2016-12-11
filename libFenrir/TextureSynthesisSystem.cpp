#include "TextureSynthesisSystem.h"
#include <iostream>
#include <cmath>
#include <assert.h>
using namespace std;

TextureSynthesisSystem * TextureSynthesisSystem::instance = nullptr;

TextureSynthesisSystem::TextureSynthesisSystem()
{
	maxNumInterations = 10000;
	minNumInterations = 100;
	minDistance = 10;
	//5x3
	neighborsWidth = 10;
	neighborsHeight = 6;
}

float TextureSynthesisSystem::distanceBetweenColor(const int & arg1, const int & arg2)
{
	static int r1, g1, b1,
		r2, g2, b2;
	r1 = (arg1 >> 16) & 0xff;
	g1 = (arg1 >> 8) & 0xff;
	b1 = (arg1)& 0xff;

	r2 = (arg2 >> 16) & 0xff;
	g2 = (arg2 >> 8) & 0xff;
	b2 = (arg2)& 0xff;

	r1 -= r2;
	g1 -= g2;
	b1 -= b2;

	r1 *= r1;
	g1 *= g1;
	b1 *= b1;

	return sqrtf(r1 + g1 + b1);
}


TextureSynthesisSystem * TextureSynthesisSystem::Instantiate()
{
	if (instance == nullptr)
		instance = new TextureSynthesisSystem();
	return instance;

}

void TextureSynthesisSystem::run(Image * sample, Image * output, bool generateNoise)
{
	int wo = output->getWidth(), ho = output->getHeight();
	int ws = sample->getWidth(), hs = sample->getHeight();

	if (generateNoise)
	{
		for (int y = ho - 2; y < ho; y++)
		{
			for (int x = 0; x < wo; x++)
			{
				output->setPixel(sample->getPixel(rand() % ws, rand() % hs), x + y * wo);
			}
		}

		for (int x = wo - 2; x < wo; x++)
		{
			for (int y = 0; y < ho; y++)
			{
				output->setPixel(sample->getPixel(rand() % ws, rand() % hs), x + y * wo);
			}
		}
	}

	bool found, doIt;
	int it;
	float closerDistance;
	int closerPixel;
	int xs, ys;
	int xi, xl;
	float sum;

	float timer = clock();
	if (neighborsWidth % 2)
		xi = neighborsWidth / 2;
	else
		xi = neighborsWidth / 2 + 1;
	xl = neighborsWidth / 2;
	cout << "Started Synthesis...\n";
	cout << "Min number of iterations: " << minNumInterations << endl;
	cout << "Max number of iterations: " << maxNumInterations << endl;
	cout << "Min distance: " << minDistance << endl;
	cout << "Neighboors: " << neighborsWidth << " x " << neighborsHeight << endl;

	//DEBUG Variables
	int maximum = 0;
	int minimun = 0;
	int middle = 0;
	int mediaIt = 0;
	int mediaMiddleIt = 0;
	float distanceMedia = 0;

	for (int yo = 0; yo < ho; yo++)
	{
		for (int xo = 0; xo < wo; xo++)
		{
			doIt = true;
			found = false;
			it = 0;
			closerDistance = 10000;
			do
			{
				it++;

				xs = rand() % ws;
				ys = rand() % hs;

				/*
				neighboors in this format
				|0|0|0|0|0|
				|0|0|0|0|0|
				|0|0|x|
				*/

				sum = 0;
				int n = 0;

				for (int y = -neighborsHeight; y <= 0; y++)
				{
					for (int x = -xi; x <= xl; x++)
					{
						if (y == 0 && x == 0)
						{
							break;
						}

						sum += distanceBetweenColor(
							sample->getPixelRepeat(xs + x, ys + y),
							output->getPixelRepeat(xo + x, yo + y));

					}
				}
				sum /= neighborsWidth * neighborsHeight + xi; // media

				if (sum < closerDistance)
				{
					closerDistance = sum;
					closerPixel = sample->getPixelRepeat(xs, ys);
					if (sum < minDistance)
						found = true;
				}



				if (it >= minNumInterations)
				{
					if (found)
					{
						doIt = false;

					}
					else if (it == maxNumInterations)
					{
						doIt = false;

					}

				}
				//debug
				if (!doIt)
				{
					if (it == minNumInterations)
						minimun++;
					else if (it == maxNumInterations)
						maximum++;
					else
					{
						middle++;
						if (mediaMiddleIt == 0)
						{
							mediaMiddleIt = it;
						}
						else
						{
							mediaMiddleIt += it;
							mediaMiddleIt /= 2;
						}
					}
					if (mediaIt == 0)
					{
						mediaIt = it;
					}
					else
					{
						mediaIt += it;
						mediaIt /= 2;
					}

				}
			} while (doIt);

			if (distanceMedia == 0)
			{
				distanceMedia = closerDistance;
			}
			else
			{
				distanceMedia += closerDistance;
				distanceMedia /= 2;
			}

			output->setPixel(closerPixel, xo + yo * wo);

		}
	}

	cout << "Finished in " << (clock() - timer) / CLOCKS_PER_SEC << " seconds.\n";
	cout << "min: " << minimun << endl;
	cout << "max: " << maximum << endl;;
	cout << "others: " << middle << endl;;
	cout << "media it: " << mediaIt << endl;
	cout << "media it mddle: " << mediaMiddleIt << endl;
	cout << "media distance: " << distanceMedia << endl;

	cout << '\a';
	cout << '\a';

}

void TextureSynthesisSystem::runWithMask(Image * sample, Image * output, Image * mask)
{
	int wo = output->getWidth(), ho = output->getHeight();
	int ws = sample->getWidth(), hs = sample->getHeight();

	Image *temp;
	int minY = -1, maxY = -1;
	int minX = -1, maxX = -1;

	{

		int tempPixel;
		int height = mask->getHeight();
		int width = mask->getWidth();
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				tempPixel = mask->getPixel(x, y) & 0xff;
				if (tempPixel != 0)
				{
					
					if (minX == -1)
					{
						minX = x;
						maxX = x;
						minY = y;
						maxY = y;
					}
					else
					{
						if (minX > x)
							minX = x;
						else if (maxX < x)
							maxX = x;
						if (minY > y)
							minY = y;
						else if (maxY < y)
							maxY = y;
					}
				}
			}
		}

	}

	int wt = maxX - minX;
	int ht = maxY - minY;

	if (wt <= 0 || ht <= 0)
	{
		cout << "Mask too smal.\n";
		return;
	}
	temp = new Image(wt, ht);

	if (ht > 2)
	{
		for (int y = ht - 2; y < ht; y++)
		{
			for (int x = 0; x < wt; x++)
			{
				temp->setPixel(sample->getPixel(rand() % ws, rand() % hs), x + y * wt);
			}
		}
	}
	else
	{
		for (int y = 0; y < ht; y++)
		{
			for (int x = 0; x < wt; x++)
			{
				temp->setPixel(sample->getPixel(rand() % ws, rand() % hs), x + y * wt);
			}
		}
	}

	if (wt > 2)
	{
		for (int x = wt - 2; x < wt; x++)
		{
			for (int y = 0; y < ht; y++)
			{
				temp->setPixel(sample->getPixel(rand() % ws, rand() % hs), x + y * wt);
			}
		}

	}
	else
	{

		for (int x = 0; x < wt; x++)
		{
			for (int y = 0; y < ht; y++)
			{
				temp->setPixel(sample->getPixel(rand() % ws, rand() % hs), x + y * wt);
			}
		}
	}

	bool found, doIt;
	int it;
	float closerDistance;
	int closerPixel;
	int xs, ys;
	int xi, xl;
	float sum;

	float timer = clock();
	if (neighborsWidth % 2)
		xi = neighborsWidth / 2;
	else
		xi = neighborsWidth / 2 + 1;
	xl = neighborsWidth / 2;
	cout << "Started Synthesis with mask...\n";
	if (mask->getWidth() != output->getWidth() || (mask->getHeight() != output->getHeight()))
	{
		cout << "Mask isn't the same size as the output, this can lead to problems\n";
	}
	cout << "Mask size: " << wt << " x " << ht << endl;
	cout << "Min number of iterations: " << minNumInterations << endl;
	cout << "Max number of iterations: " << maxNumInterations << endl;
	cout << "Min distance: " << minDistance << endl;
	cout << "Neighboors: " << neighborsWidth << " x " << neighborsHeight << endl;

	//DEBUG Variables
	int maximum = 0;
	int minimun = 0;
	int middle = 0;
	int mediaIt = 0;
	int mediaMiddleIt = 0;
	float distanceMedia = 0;

	for (int yt = 0; yt < ht; yt++)
	{
		for (int xt = 0; xt < wt; xt++)
		{
			doIt = true;
			found = false;
			it = 0;
			closerDistance = 10000;
			do
			{
				it++;

				xs = rand() % ws;
				ys = rand() % hs;

				/*
				neighboors in this format
				|0|0|0|0|0|
				|0|0|0|0|0|
				|0|0|x|
				*/

				sum = 0;
				int n = 0;

				for (int y = -neighborsHeight; y <= 0; y++)
				{
					for (int x = -xi; x <= xl; x++)
					{
						if (y == 0 && x == 0)
						{
							break;
						}

						sum += distanceBetweenColor(
							sample->getPixelRepeat(xs + x, ys + y),
							temp->getPixelRepeat(xt + x, yt + y));

					}
				}
				sum /= neighborsWidth * neighborsHeight + xi; // media

				if (sum < closerDistance)
				{
					closerDistance = sum;
					closerPixel = sample->getPixelRepeat(xs, ys);
					if (sum < minDistance)
						found = true;
				}



				if (it >= minNumInterations)
				{
					if (found)
					{
						doIt = false;

					}
					else if (it == maxNumInterations)
					{
						doIt = false;

					}

				}
				//debug
				if (!doIt)
				{
					if (it == minNumInterations)
						minimun++;
					else if (it == maxNumInterations)
						maximum++;
					else
					{
						middle++;
						if (mediaMiddleIt == 0)
						{
							mediaMiddleIt = it;
						}
						else
						{
							mediaMiddleIt += it;
							mediaMiddleIt /= 2;
						}
					}
					if (mediaIt == 0)
					{
						mediaIt = it;
					}
					else
					{
						mediaIt += it;
						mediaIt /= 2;
					}

				}
			} while (doIt);

			if (distanceMedia == 0)
			{
				distanceMedia = closerDistance;
			}
			else
			{
				distanceMedia += closerDistance;
				distanceMedia /= 2;
			}

			temp->setPixel(closerPixel, xt + yt * wt);

		}
	}

	int tempPixel;
	int argb;
	for (int y = 0; y < ht; y++)
	{
		for (int x = 0; x < wt; x++)
		{
			tempPixel = mask->getPixel(x + minX, y + minY) & 0xFF;
			if (tempPixel != 0)
			{
				argb = temp->getPixel(x, y);
				argb &= (tempPixel << 24) | 0xffffff;
				output->plotPixel(argb, x + minX, y + minY);
			}
		}
	}

	delete temp;

	cout << "Finished in " << (clock() - timer) / CLOCKS_PER_SEC << " seconds.\n";
	cout << "min: " << minimun << endl;
	cout << "max: " << maximum << endl;;
	cout << "others: " << middle << endl;;
	cout << "media it: " << mediaIt << endl;
	cout << "media it mddle: " << mediaMiddleIt << endl;
	cout << "media distance: " << distanceMedia << endl;

	cout << '\a';
	cout << '\a';
}

void TextureSynthesisSystem::run(Image * sample, Image * output, Image * base)
{
	int wo = output->getWidth(), ho = output->getHeight();
	int ws = sample->getWidth(), hs = sample->getHeight();

	bool found, doIt;
	int it;
	float closerDistance;
	int closerPixel;
	int xs, ys;
	int xi, xl;
	float sum;

	float timer = clock();
	if (neighborsWidth % 2)
		xi = neighborsWidth / 2;
	else
		xi = neighborsWidth / 2 + 1;
	xl = neighborsWidth / 2;
	cout << "Started Synthesis with sample...\n";
	cout << "Min number of iterations: " << minNumInterations << endl;
	cout << "Max number of iterations: " << maxNumInterations << endl;
	cout << "Min distance: " << minDistance << endl;
	cout << "Neighboors: " << neighborsWidth << " x " << neighborsHeight << endl;

	//DEBUG Variables
	int maximum = 0;
	int minimun = 0;
	int middle = 0;
	int mediaIt = 0;
	int mediaMiddleIt = 0;
	float distanceMedia = 0;

	for (int yo = 0; yo < ho; yo++)
	{
		for (int xo = 0; xo < wo; xo++)
		{
			doIt = true;
			found = false;
			it = 0;
			closerDistance = 10000;
			do
			{
				it++;

				xs = rand() % ws;
				ys = rand() % hs;

				/*
				neighboors in this format
				|0|0|0|0|0|
				|0|0|0|0|0|
				|0|0|x|
				*/

				sum = 0;
				int n = 0;

				for (int y = -neighborsHeight; y <= 0; y++)
				{
					for (int x = -xi; x <= xl; x++)
					{
						if (y == 0 && x == 0)
						{
							break;
						}

						sum += distanceBetweenColor(
							sample->getPixelRepeat(xs + x, ys + y),
							base->getPixelRepeat(xo + x, yo + y));

					}
				}
				sum /= neighborsWidth * neighborsHeight + xi; // media

				if (sum < closerDistance)
				{
					closerDistance = sum;
					closerPixel = sample->getPixelRepeat(xs, ys);
					if (sum < minDistance)
						found = true;
				}



				if (it >= minNumInterations)
				{
					if (found)
					{
						doIt = false;

					}
					else if (it == maxNumInterations)
					{
						doIt = false;

					}

				}
				//debug
				if (!doIt)
				{
					if (it == minNumInterations)
						minimun++;
					else if (it == maxNumInterations)
						maximum++;
					else
					{
						middle++;
						if (mediaMiddleIt == 0)
						{
							mediaMiddleIt = it;
						}
						else
						{
							mediaMiddleIt += it;
							mediaMiddleIt /= 2;
						}
					}
					if (mediaIt == 0)
					{
						mediaIt = it;
					}
					else
					{
						mediaIt += it;
						mediaIt /= 2;
					}

				}
			} while (doIt);

			if (distanceMedia == 0)
			{
				distanceMedia = closerDistance;
			}
			else
			{
				distanceMedia += closerDistance;
				distanceMedia /= 2;
			}

			output->setPixel(closerPixel, xo + yo * wo);

		}
	}

	cout << "Finished in " << (clock() - timer) / CLOCKS_PER_SEC << " seconds.\n";
	cout << "min: " << minimun << endl;
	cout << "max: " << maximum << endl;;
	cout << "others: " << middle << endl;;
	cout << "media it: " << mediaIt << endl;
	cout << "media it middle: " << mediaMiddleIt << endl;
	cout << "media distance: " << distanceMedia << endl;

	cout << '\a';
	cout << '\a';

}

TextureSynthesisSystem::~TextureSynthesisSystem()
{
}

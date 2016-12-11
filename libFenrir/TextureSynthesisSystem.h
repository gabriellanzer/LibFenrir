#pragma once
#include "Image.h"
class TextureSynthesisSystem
{
public:
	static TextureSynthesisSystem* Instantiate();

	void run(Image *sample, Image *output, Image *base);

	void run(Image *sample, Image *output, bool generateNoise);

	void runWithMask(Image *sample, Image *output, Image *mask);
	int maxNumInterations; /*Max number of iterations it can do to find the color of pixel by its neighbors,
						   if reached and can't find an number, it gets the most similar pixel */
	float minNumInterations; /*Min number of iterations it have to do to find the color of pixel by its neighbors
							 if find before reached it, it continues to run until reached the min nº*/
	float minDistance; /*
					   Min distance that the neighboors have to have
					   */
	int neighborsWidth, neighborsHeight;
private:
	~TextureSynthesisSystem();
	TextureSynthesisSystem();
	float distanceBetweenColor(const int &arg1, const int&arg2);

	
	static TextureSynthesisSystem *instance;
};

#define gSynthesis TextureSynthesisSystem::Instantiate()
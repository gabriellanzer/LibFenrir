#pragma once
#include "MeshShader.h"

class ClickSystem
{
public:
	~ClickSystem();

	static ClickSystem *Instantiate();

	void setSize(int w, int h);

	int click(int x, int y);

	void changeFrameBuffer(MeshShader *m = nullptr, glm::mat4 model = glm::mat4());

	void setMesh(MeshShader *i);
	MeshShader * getMesh();

	float getU();
	float getV();

	int getFaceIndex();
	int getGroupIndex();

private:
	static ClickSystem *instance;

	int x, y, w, h;
	int *frameGroup, *frameFace, *frameVertex;
	MeshShader* mesh;
	bool haveToChange;
	glm::mat4 model;
	float u, v;
	int groupIndex;
	int faceIndex;

	ClickSystem();

};

#define gClick ClickSystem::Instantiate()
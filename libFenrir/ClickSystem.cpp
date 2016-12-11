#include "ClickSystem.h"
#include "RendererSystem.h"
#include <GLFW\glfw3.h>

ClickSystem *ClickSystem::instance;

ClickSystem::ClickSystem()
{
	w = 800;
	h = 640;
	mesh = nullptr;
	frameGroup = new int[w * h];
	frameFace = new int[w * h];
	frameVertex = new int[w * h];
	haveToChange = true;
}


ClickSystem::~ClickSystem()
{
}

ClickSystem * ClickSystem::Instantiate()
{
	if (!instance)
		instance = new ClickSystem();
	return instance;
}

void ClickSystem::setSize(int w, int h)
{
	this->w = w;
	this->h = h;
}


int ClickSystem::click(int x, int y)
{
	int w, h;
	glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
	if (x >= 0 && x < w && y >= 0 && y < h)
	{
		if (haveToChange)
		{
			if (mesh == nullptr)
			{
				cout << "Can't try to click because there's no mesh attached to the system.\n";
				return -1;
			}
			haveToChange = false;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//gRenderer->render3DColor(mesh, e_group, model);
			glFlush();
			glFinish();
			glReadPixels(0, 0, w, h, GL_BGRA_EXT, GL_UNSIGNED_BYTE, frameGroup);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//gRenderer->render3DColor(mesh, e_face, model);
			glFlush();
			glFinish();
			glReadPixels(0, 0, w, h, GL_BGRA_EXT, GL_UNSIGNED_BYTE, frameFace);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//gRenderer->render3DColor(mesh, e_vertexColor, model);
			glFlush();
			glFinish();
			glReadPixels(0, 0, w, h, GL_BGRA_EXT, GL_UNSIGNED_BYTE, frameVertex);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		}

		if (x >= w || x < 0 || y >= h || y < 0)
		{
			return -2;
		}

		int posMatrix = x + w * y;

		//Group Color
		//uint c = (16777216 / (m->sizeGroup() + 1)*(g + 1));

		//Get Group Color
		//g = (frameGroup[posMatrix]*(m->sizeGroup() + 1)/16777216)-1

		uint groupCount = mesh->getGroups()->size();
		int groupIndex = (((unsigned int)frameGroup[posMatrix] & 0xffffff) * (groupCount + 1) / 16777216) - 1;

		//Has clicked any group?
		if (groupIndex < 0) {
			return -3; //Nope
		}

		//cout << "GroupIndex: " << groupIndex << endl;

		//Face Color
		//unsigned int c = (16777216 / (size / 3 + 1)*(i / 3 + 1));

		//Get Face Color
		//faceIndex = ((((unsigned int)frameFace[posMatrix] & 0xffffff) * (size / 3 + 1)/16777216) - 1) * 3


		uint vertexCount = mesh->getGroup(groupIndex)->getVertex()->size();
		faceIndex = ((((unsigned int)frameFace[posMatrix] & 0xffffff) * (vertexCount / 3 + 1) / 16777216));
		//cout << "FaceIndex: " << faceIndex << endl;

		//Vertex Color
		/*switch (i % 3)
		{
		case 0:
		vertexColorF[i * 3] = 1.0f;
		vertexColorF[i * 3 + 1] = 0.0f;
		vertexColorF[i * 3 + 2] = 0.0f;
		break;
		case 1:
		vertexColorF[i * 3] = 0.5f;
		vertexColorF[i * 3 + 1] = 0.0f;
		vertexColorF[i * 3 + 2] = 0.5f;
		break;
		case 2:
		vertexColorF[i * 3] = 0.0f;
		vertexColorF[i * 3 + 1] = 0.0f;
		vertexColorF[i * 3 + 2] = 1.0f;
		break;
		}*/

		//Get ClickCoords (in percentage of X and Y)
		int red = ((unsigned int)frameVertex[posMatrix] >> 16) & 0xff;
		int blue = ((unsigned int)frameVertex[posMatrix]) & 0xff;
		//cout << "Red: " << red << "\tBlue: " << blue << endl;

		v = red / 255.0f;
		u = blue / 255.0f;

		return groupIndex;
	}
	else
		return -4;
}

void ClickSystem::changeFrameBuffer(MeshShader *m, glm::mat4 model)
{
	if (m != nullptr)
		mesh = m;
	haveToChange = true;
	this->model = model;
}


void ClickSystem::setMesh(MeshShader * i)
{
	mesh = i;
}

MeshShader * ClickSystem::getMesh()
{
	return mesh;
}

float ClickSystem::getU()
{
	return u;
}

float ClickSystem::getV()
{
	return v;
}

int ClickSystem::getFaceIndex()
{
	return faceIndex;
}

int ClickSystem::getGroupIndex()
{
	return groupIndex;
}




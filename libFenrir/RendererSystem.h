#pragma once
//#include "maths_funcs.h"
#include <map>
#include "glm\glm.hpp"
#include "glm\fwd.hpp"
#include "glm\mat4x4.hpp"
#include "glm\common.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "Shader.h"
#include "MeshShader.h"

#ifndef UINT_H
#define UINT_H
typedef unsigned int uint;
#endif // !UINT_H




class RendererSystem
{
public:
	static RendererSystem *Instantiate();
	~RendererSystem();

	void init();

	Shader *getShader(string index);

	void updateAllShadersView(glm::mat4 view);
	void updateAllShadersProj(glm::mat4 proj);

	glm::mat4 getView();
	glm::mat4 getProj();

	void addShader(string name, string vertexPath, string fragmentPath);

private:

	RendererSystem();
	glm::mat4 view, proj;
	map<string, Shader*> shaders;
	static RendererSystem *instance;

};


#define gRenderer RendererSystem::Instantiate()

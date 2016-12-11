#include "RendererSystem.h"
#include "ResourceManager.h"
#include <gl\glew.h>
#include <fstream>
#include <GLFW\glfw3.h>
#include <string>
#include <iostream>

RendererSystem *RendererSystem::instance;

RendererSystem::RendererSystem()
{

}


RendererSystem * RendererSystem::Instantiate()
{
	if (instance)
		return instance;
	else
		instance = new RendererSystem();

	return instance;
}

RendererSystem::~RendererSystem()
{
}

void RendererSystem::init()
{
#pragma region Shader

	addShader("2DTexture", "shader/vertex2dTexture.glsl", "shader/fragmentTexture.glsl");
	shaders.at("2DTexture")->addAtt("model");

	addShader("2D", "shader/vertex2d.glsl", "shader/fragmentColor.glsl");
	shaders.at("2D")->addAtt("model");

	addShader("3D", "shader/vertex3d.glsl", "shader/fragmentTexture.glsl");
	shaders.at("3D")->addAtt("model");
	shaders.at("3D")->addAtt("view");
	shaders.at("3D")->addAtt("proj");

	addShader("3DColor", "shader/vertex3DColor.glsl", "shader/fragmentColor.glsl");
	shaders.at("3DColor")->addAtt("model");
	shaders.at("3DColor")->addAtt("view");
	shaders.at("3DColor")->addAtt("proj");

	addShader("3DColorLight", "shader/vertex3DColorLightV.glsl", "shader/fragmentColorLightV.glsl");
	shaders.at("3DColorLight")->addAtt("model");
	shaders.at("3DColorLight")->addAtt("view");
	shaders.at("3DColorLight")->addAtt("proj");

	addShader("3DLight", "shader/vertex3DLight.glsl", "shader/fragmentTextureLight.glsl");
	shaders.at("3DLight")->addAtt("model");
	shaders.at("3DLight")->addAtt("view");
	shaders.at("3DLight")->addAtt("proj");

	addShader("3DDepth", "shader/vertex3D.glsl", "shader/fragmentDepth.glsl");
	shaders.at("3DDepth")->addAtt("model");
	shaders.at("3DDepth")->addAtt("view");
	shaders.at("3DDepth")->addAtt("proj");

	addShader("FBO_RGB_NOR_DEPTH", "shader/vertex_RGB_NOR_DEPTH.glsl", "shader/fragment_RGB_NOR_DEPTH.glsl");
	shaders.at("FBO_RGB_NOR_DEPTH")->addAtt("model");
	shaders.at("FBO_RGB_NOR_DEPTH")->addAtt("normal");
	shaders.at("FBO_RGB_NOR_DEPTH")->addAtt("view");
	shaders.at("FBO_RGB_NOR_DEPTH")->addAtt("proj");
	shaders.at("FBO_RGB_NOR_DEPTH")->addAtt("basic_texture");

	addShader("SCREEN_PASS", "shader/vertexScreenPass.glsl", "shader/fragmentScreenPass.glsl");
	shaders.at("SCREEN_PASS")->addAtt("rgb_texture");
	shaders.at("SCREEN_PASS")->addAtt("normals_texture");
	shaders.at("SCREEN_PASS")->addAtt("depth_texture");
	shaders.at("SCREEN_PASS")->addAtt("hbao_texture");
	shaders.at("SCREEN_PASS")->addAtt("blur_texture");
	shaders.at("SCREEN_PASS")->addAtt("zNear");
	shaders.at("SCREEN_PASS")->addAtt("zFar");
	shaders.at("SCREEN_PASS")->addAtt("mode");

	addShader("HBAO", "shader/vertexHBAO.glsl", "shader/fragmentHBAO.glsl");
	shaders.at("HBAO")->addAtt("depth_texture");
	shaders.at("HBAO")->addAtt("noise_texture");
	shaders.at("HBAO")->addAtt("normals_texture");
	shaders.at("HBAO")->addAtt("zNear");
	shaders.at("HBAO")->addAtt("zFar");
	shaders.at("HBAO")->addAtt("invproj");

	addShader("BLUR", "shader/vertexBlur.glsl", "shader/fragmentBlur.glsl");
	shaders.at("BLUR")->addAtt("hbao_texture");

	
	/*
	gResource->readShader("shader/vertex2d.glsl", GL_VERTEX_SHADER, "vertex2d");
	gResource->readShader("shader/fragmentColor.glsl" , GL_FRAGMENT_SHADER, "fragment2d");
	gResource->readShader("shader/vertex2dTexture.glsl" , GL_VERTEX_SHADER, "vertex2dTexture");
	gResource->readShader("shader/fragmentTexture.glsl" , GL_FRAGMENT_SHADER, "fragmentTexture");
	gResource->readShader("shader/vertex3d.glsl", GL_VERTEX_SHADER, "vertex3d");
	gResource->readShader("shader/vertex3dcolor.glsl", GL_VERTEX_SHADER, "vertex3dcolor");


	gResource->generateProgram("2dColor");
	gResource->addShaderToProgram("vertex2d", "2dColor");
	gResource->addShaderToProgram("fragment2d", "2dColor");


	gResource->generateProgram("2dTexture");
	gResource->addShaderToProgram("vertex2dTexture", "2dTexture");
	gResource->addShaderToProgram("fragmentTexture", "2dTexture");


	gResource->generateProgram("3d");
	gResource->addShaderToProgram("vertex3d", "3d");
	gResource->addShaderToProgram("fragmentTexture", "3d");

	gResource->generateProgram("3dColor");
	gResource->addShaderToProgram("vertex3dcolor", "3dColor");
	gResource->addShaderToProgram("fragment2d", "3dColor");

	gResource->linkAllPrograms();

#pragma endregion
#endif
	glUseProgram(gResource->getProgram("2dColor"));
	matrixLocation = glGetUniformLocation(gResource->getProgram("2dColor"), "matrix");

	glUseProgram(gResource->getProgram("2dTexture"));
	matrixLocation = glGetUniformLocation(gResource->getProgram("2dTexture"), "matrix");


	glUseProgram(gResource->getProgram("3d"));
	viewLocation = glGetUniformLocation(gResource->getProgram("3d"), "view");
	projLocation = glGetUniformLocation(gResource->getProgram("3d"), "proj");
	modelLocation = glGetUniformLocation(gResource->getProgram("3d"), "model");

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(proj));

	glUseProgram(gResource->getProgram("3dColor"));
	viewLocationC = glGetUniformLocation(gResource->getProgram("3dColor"), "view");
	projLocationC = glGetUniformLocation(gResource->getProgram("3dColor"), "proj");
	modelLocationC = glGetUniformLocation(gResource->getProgram("3dColor"), "model");
	hasBegan = true;

	glUniformMatrix4fv(viewLocationC, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLocationC, 1, GL_FALSE, glm::value_ptr(proj));

	*/

}

Shader * RendererSystem::getShader(string index)
{
	return shaders.at(index);
}

static const string viewAT = "view";
void RendererSystem::updateAllShadersView(glm::mat4 view)
{
	this->view = view;
	for (map<string, Shader*>::iterator it = shaders.begin(); it != shaders.end(); it++)
	{
		if (it->second->containsAtt(viewAT)) {
			it->second->updateAtt(viewAT, glm::value_ptr(view));
		}
	}
}
static const string projAT = "proj";
void RendererSystem::updateAllShadersProj(glm::mat4 proj)
{
	this->proj = proj;

	for (map<string, Shader*>::iterator it = shaders.begin(); it != shaders.end(); it++)
	{
		if (it->second->containsAtt(projAT)) {
			it->second->updateAtt(projAT, glm::value_ptr(proj));
		}
	}
}


glm::mat4 RendererSystem::getView()
{
	return view;
}

glm::mat4 RendererSystem::getProj()
{
	return proj;
}

void RendererSystem::addShader(string name, string vertexPath, string fragmentPath)
{
	Shader *s = new Shader(vertexPath, fragmentPath);
	if (s->isCompiled()) {
		shaders.insert(map<string, Shader*>::value_type(name, s));
	}
	else {
		cout << "Problem with " << name << "\n";
	}
}

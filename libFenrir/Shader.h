#pragma once
#include <string>
#include <map>
#include <glm\glm.hpp>
#include "MeshShader.h"
#ifndef UINT_H
#define UINT_H
typedef unsigned int  uint;
#endif

using namespace std;
class Shader
{
public:
	Shader(string vertex, string fragment);
	~Shader();

	void readShader(string path, int mode);

	void addAtt(string t);
	void updateAtt(string t, float *);
	bool containsAtt(string att);

	void render(uint vao, int count, int start);
	void render(uint vao, int count, int start, glm::mat4 model);
	void render3D(MeshShader *m, glm::mat4 model = glm::mat4());

	void createAndCompileProgram();

	bool isCompiled();

	uint getAtt(string att);
	uint getIndexProgram();
private:
	bool is_compiled;
	uint indexVertex, indexFragment, indexProgram;
	map<string, uint> att;
};


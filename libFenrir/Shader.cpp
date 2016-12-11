#include "Shader.h"
#include <fstream>
#include <iostream>
#include <assert.h>
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include "GLError.h"
#include "glm\glm.hpp"
#include "glm\fwd.hpp"
#include "glm\mat4x4.hpp"
#include "glm\common.hpp"
#include "glm\gtc\type_ptr.hpp"


Shader::Shader(string vertex, string fragment)
{
	readShader(vertex, GL_VERTEX_SHADER);
	readShader(fragment, GL_FRAGMENT_SHADER);
	is_compiled = false;
	createAndCompileProgram();
}

Shader::~Shader()
{
}

void Shader::readShader(string path, int mode)
{
	ifstream arq(path);
	string s, t;
	if (!arq.is_open())
	{
		cout << "Couldn't find in " << path << "\n Operation aborted.";
		assert(false);

		return;
	}
	getline(arq, s);
	t = s;
	while (!arq.eof())
	{
		getline(arq, s);
		t += "\n" + s;
	}

	char* shader = (char*)t.c_str();
	uint *index = nullptr;
	if (mode == GL_VERTEX_SHADER)
		index = &indexVertex;
	else if (mode == GL_FRAGMENT_SHADER)
		index = &indexFragment;
	else
	{
		cout << "the mode isn't vertex neither is fragment";
	}

	*index = glCreateShader(mode);
	check_gl_error();

	glShaderSource(*index, 1, &shader, NULL);
	glCompileShader(*index);
	GLint isCompiled;
	glGetShaderiv(*index, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		cout << "In reading from " << path << ":\n";
		GLint maxLength = 0;
		glGetShaderiv(*index, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		char* infoLog = new char[maxLength];
		glGetShaderInfoLog(*index, maxLength, &maxLength, infoLog);

		//The shader is useless now. So delete it.
		glDeleteShader(*index);

		//Provide the infolog in whatever manner you deem best.
		cout << infoLog;


		assert(false);
	}
	check_gl_error();

}

void Shader::addAtt(string t)
{
	att.insert(map<string, uint>::value_type(t, glGetUniformLocation(indexProgram, t.c_str())));
}

void Shader::updateAtt(string t, float *f)
{
	glUseProgram(indexProgram);
	glUniformMatrix4fv(att.at(t), 1, GL_FALSE, f);
}

bool Shader::containsAtt(string at)
{
	for (map<string, uint>::iterator it = att.begin(); it != att.end(); it++)
	{
		if (it->first == at) {
			return true;
		}
	}
	return false;
}

void Shader::render(uint vao, int count, int start)
{
	glUseProgram(indexProgram);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, start, count);
}

const static string modelAT = "model";
const static string normalAT = "normal";
void Shader::render(uint vao, int count, int start, glm::mat4 model)
{
	glUseProgram(indexProgram);
	glBindVertexArray(vao);
	glUniformMatrix4fv(att.at(modelAT), 1, GL_FALSE, glm::value_ptr(model));
	uint normalId = att.at(normalAT);
	if (normalId) {
		glm::mat3 normal = glm::mat3(glm::transpose(glm::inverse(model)));
		glUniformMatrix3fv(normalId, 1, GL_FALSE, glm::value_ptr(normal));
	}
	check_gl_error();
	glDrawArrays(GL_TRIANGLES, start, count);
}

void Shader::render3D(MeshShader * m, glm::mat4 model)
{
	glUseProgram(indexProgram);
	uint vao;
	int count;
	glUniformMatrix4fv(att.at(modelAT), 1, GL_FALSE, glm::value_ptr(model));
	uint normalId = att.at(normalAT);
	if (normalId) {
		glm::mat3 normal = glm::mat3(glm::transpose(glm::inverse(model)));
		glUniformMatrix3fv(normalId, 1, GL_FALSE, glm::value_ptr(normal));
	}
	for (int i = 0; i < m->getGroups()->size(); i++) {
		glBindVertexArray(m->getGroup(i)->getVAO());
		glDrawArrays(GL_TRIANGLES, 0, m->getGroup(i)->getVertex()->size());
	}
}

void Shader::createAndCompileProgram()
{
	indexProgram = glCreateProgram();

	glAttachShader(indexProgram, indexVertex);
	glAttachShader(indexProgram, indexFragment);


	glLinkProgram(indexProgram);
	GLint isLinked = 0;
	glGetProgramiv(indexProgram, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		cout << "In compiling " << indexProgram << ":\n";
		GLint maxLength = 0;
		glGetProgramiv(indexProgram, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		char* infoLog = new char[maxLength];
		glGetProgramInfoLog(indexProgram, maxLength, &maxLength, infoLog);

		//The program is useless now. So delete it.
		glDeleteProgram(indexProgram);

		//Provide the infolog in whatever manner you deem best.
		cout << infoLog;
		assert(false);
	}
	else {
		is_compiled = true;
	}
	check_gl_error();

}

bool Shader::isCompiled()
{
	return is_compiled;
}

uint Shader::getAtt(string att)
{
	return this->att.at(att);
}

uint Shader::getIndexProgram()
{
	return indexProgram;
}


#include "GroupShader.h"
#include <gl\glew.h>

#include <GLFW\glfw3.h>


GroupShader::GroupShader()
{
	vao = 0;
	vbo[e_vertex] = 0;
	vbo[e_texture] = 0;
	vbo[e_group] = 0;
	vbo[e_face] = 0;
	vbo[e_vertexColor] = 0;
	this->color = 0;
}

GroupShader::GroupShader(unsigned int color)
{
	vao = 0;
	vbo[e_vertex] = 0;
	vbo[e_texture] = 0;
	vbo[e_group] = 0;
	vbo[e_face] = 0;
	vbo[e_vertexColor] = 0;
	this->color = color;
}


GroupShader::~GroupShader()
{
}

vector<uint>* GroupShader::getVertex()
{
	return &vertex;
}

uint & GroupShader::getVertex(int i)
{
	return vertex[i];
}

vector<uint>* GroupShader::getUV()
{
	return &uv;
}

uint & GroupShader::getUV(int i)
{
	return uv[i];

}

vector<uint>* GroupShader::getNormal()
{
	return &normal;
}

uint & GroupShader::getNormal(int i)
{
	return normal[i];
}


uint & GroupShader::getVAO()
{
	return vao;
}

void GroupShader::setVAO(uint i)
{
	vao = i;
}

uint & GroupShader::getVBO(int i)
{
	return vbo[i];
}

void GroupShader::setVBO(int i, int n)
{
	vbo[i] = n;
}

uint GroupShader::getColor()
{
	return color;
}

void GroupShader::bindVBO(int i)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
	if (i == e_texture)
	{
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	else
	{
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}
}




#pragma once
#include <vector>


#ifndef UINT_H
#define UINT_H
typedef unsigned int uint;
#endif // !UINT_H

using namespace std;

enum vboEnum {
	e_vertex,
	e_texture,
	e_group,
	e_face,
	e_vertexColor,
	e_normal
};

class GroupShader
{
public:
	GroupShader();
	GroupShader(unsigned int color);
	~GroupShader();

	vector<uint>* getVertex();
	uint &getVertex(int);

	vector<uint>* getUV();
	uint &getUV(int);

	vector<uint>* getNormal();
	uint &getNormal(int);

	uint &getVAO();
	void setVAO(uint);

	uint &getVBO(int);
	void setVBO(int i, int newValeu);

	uint getColor();

	void bindVBO(int vbo);

private:
	unsigned int color;
	uint vao, vbo[6];
	vector<uint> vertex;
	vector<uint> uv;
	vector<uint> normal;
};


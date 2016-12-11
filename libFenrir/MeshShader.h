#pragma once
#include "GroupShader.h"
//#include "maths_funcs.h"
#include "glm\glm.hpp"
#include "Vector2D.h"
#include "Vector3D.h"


class MeshShader
{
public:
	MeshShader();
	~MeshShader();

	vector<Vector3Df> *getVertex();
	Vector3Df &getVertex(int n);
	void setVertex(vector<Vector3Df> *v);

	vector<Vector2Df> *getUV();
	Vector2Df &getUV(int n);
	void setUV(vector<Vector2Df> *v);

	vector<GroupShader> *getGroups();
	GroupShader* getGroup(int n);
	void setGroups(vector<GroupShader> *g);


	bool GrouptoVAO(GroupShader *g);

	void toVAO();

	void bindVBO(int vbo);
private:
	vector<Vector3Df> vertex;
	vector<Vector2Df> uv;
	vector<Vector3Df> normal;
	vector<GroupShader> group;

};


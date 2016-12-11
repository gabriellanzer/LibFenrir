#pragma once
#include "Group.h"
#include "Vector2D.h"
#include "Vector3D.h"

using namespace std;
class Mesh
{
public:
	Mesh();
	Mesh(string &s);
	~Mesh();

	bool operator==(const Mesh &l)
	{
		return path == l.path;
	}
	//Vertex
	vector<Vector3Df> *Vertex();
	Vector3Df& Vertex(int n);
	Vector3Df* Vertex_(int n);

	Vector3Df * newVertex();
	void setVertex(vector<Vector3Df> &n);
	void addVertex(Vector3Df& n);
	void addVertexAt(Vector3Df & n, int& w);

	void removeVertex(Vector3Df &n);
	void removeVertexAt(int &n);

	int sizeVertex();

	//Normal
	vector<Vector3Df> *Normal();
	Vector3Df& Normal(int n);
	Vector3Df* Normal_(int n);

	Vector3Df * newNormal();
	void setNormal(vector<Vector3Df> &n);
	void addNormal(Vector3Df& n);
	void addNormalAt(Vector3Df & n, int& w);

	void removeNormal(Vector3Df &n);
	void removeNormalAt(int &n);

	int sizeNormal();

	//Mapping
	vector<Vector2Df> *Mapping();
	Vector2Df& Mapping(int n);
	Vector2Df* Mapping_(int n);

	Vector2Df * newMapping();
	void setMapping(vector<Vector2Df> &n);
	void addMapping(Vector2Df& n);
	void addMappingAt(Vector2Df & n, int& w);

	void removeMapping(Vector2Df &n);
	void removeMappingAt(int &n);

	int sizeMapping();

	//Group

	vector<Group>* group();
	Group* group(int n);
	Group* group(string n);

	void setGroup(vector<Group> &n);
	void addGroup(Group& n);
	void addGroupAt(Group & n, int& w);

	void removeGroup(Group &n);
	void removeGroup(string &n);
	void removeGroupAt(int &n);

	int sizeGroup();

	string& getPath();
	void setPath(string &);
	

private:
	vector<Vector3Df> vertex;
	vector<Vector3Df> normal;
	vector<Vector2Df> mapping;

	vector<Group> groupV;
	string path;
	
};


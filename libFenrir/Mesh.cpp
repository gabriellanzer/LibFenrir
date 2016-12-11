#include "Mesh.h"



Mesh::Mesh()
{
}

Mesh::Mesh(string & s)
{
	path = s;
}


Mesh::~Mesh()
{
}

vector<Vector3Df>* Mesh::Vertex()
{
	return &vertex;
}

Vector3Df & Mesh::Vertex(int  n)
{
	return vertex[n];
}

Vector3Df * Mesh::Vertex_(int n)
{
	return &vertex[n];
}

Vector3Df * Mesh::newVertex()
{
	vertex.emplace_back();
	return &vertex[vertex.size() -1];
}

void Mesh::setVertex(vector<Vector3Df>& n)
{
	vertex = n;
}

void Mesh::addVertex(Vector3Df & n)
{
	vertex.push_back(n);
}

void Mesh::addVertexAt(Vector3Df & n, int & w)
{
	vertex.insert(vertex.begin() + w, n);
}

void Mesh::removeVertex(Vector3Df & n)
{
	for (std::vector<Vector3Df>::iterator i = vertex.begin(); i != vertex.end(); i++)
	{
		if (*i == n)
		{
			vertex.erase(i);
		}
	}
}

void Mesh::removeVertexAt(int & n)
{
	vertex.erase(vertex.begin() + n);
}

int Mesh::sizeVertex()
{
	return vertex.size();
}

vector<Vector3Df>* Mesh::Normal()
{
	return &normal;
}

Vector3Df & Mesh::Normal(int  n)
{
	return normal[n];
}

Vector3Df * Mesh::Normal_(int n)
{
	return &normal[n];
}

Vector3Df * Mesh::newNormal()
{
	normal.emplace_back();
	return &normal[normal.size() - 1];
}

void Mesh::setNormal(vector<Vector3Df>& n)
{
	normal = n;
}

void Mesh::addNormal(Vector3Df & n)
{
	normal.push_back(n);
}

void Mesh::addNormalAt(Vector3Df & n, int & w)
{
	normal.insert(normal.begin() + w, n);
}

void Mesh::removeNormal(Vector3Df & n)
{
	for (std::vector<Vector3Df>::iterator i = normal.begin(); i != normal.end(); i++)
	{
		if (*i == n)
		{
			normal.erase(i);
		}
	}
}

void Mesh::removeNormalAt(int & n)
{
	normal.erase(normal.begin() + n);
}

int Mesh::sizeNormal()
{
	return normal.size();
}

vector<Vector2Df>* Mesh::Mapping()
{
	return &mapping;
}

Vector2Df & Mesh::Mapping(int  n)
{
	return mapping[n];
}

Vector2Df * Mesh::Mapping_(int n)
{
	return &mapping[n];
}

Vector2Df * Mesh::newMapping()
{
	mapping.emplace_back();
	return &mapping[mapping.size() - 1];
}

void Mesh::setMapping(vector<Vector2Df>& n)
{
	mapping = n;
}

void Mesh::addMapping(Vector2Df & n)
{
	mapping.push_back(n);
}

void Mesh::addMappingAt(Vector2Df & n, int & w)
{
	mapping.insert(mapping.begin() + w, n);
}

void Mesh::removeMapping(Vector2Df & n)
{
	for (std::vector<Vector2Df>::iterator i = mapping.begin(); i != mapping.end(); i++)
	{
		if (*i == n)
		{
			mapping.erase(i);
		}
	}
}

void Mesh::removeMappingAt(int & n)
{
	mapping.erase(mapping.begin() + n);
}

int Mesh::sizeMapping()
{
	return mapping.size();
}

vector<Group>* Mesh::group()
{
	return &groupV;
}

Group* Mesh::group(int n)
{
	return &groupV[n];
}

Group * Mesh::group(string n)
{
	for (int i = 0; i < groupV.size(); i++)
	{
		if (groupV[i].name() == n)
			return &groupV[i];
	}
	groupV.emplace_back(n);
	return &groupV[groupV.size() - 1];
}

void Mesh::setGroup(vector<Group>& n)
{
	groupV = n;
}

void Mesh::addGroup(Group & n)
{
	groupV.push_back(n);
}

void Mesh::addGroupAt(Group & n, int & w)
{
	groupV.insert(groupV.begin() + w, n);
}

void Mesh::removeGroup(Group & n)
{
	for (vector<Group>::iterator i = groupV.begin(); i != groupV.end(); i++)
	{
		if (*i == n)
		{
			groupV.erase(i);
		}
	}
}

void Mesh::removeGroup(string & n)
{
	for (vector<Group>::iterator i = groupV.begin(); i != groupV.end(); i++)
	{
		if (i->name() == n)
		{
			groupV.erase(i);
		}
	}
}

void Mesh::removeGroupAt(int & n)
{
	groupV.erase(groupV.begin() + n);
}

int Mesh::sizeGroup()
{
	return groupV.size();
}

string & Mesh::getPath()
{
	return path;
}

void Mesh::setPath(string &s)
{
	path = s;
}

#include "Face.h"



Face::Face()
{
}

Face::Face(std::vector<uint>& ve)
{
	v = ve;
}


Face::~Face()
{
}

std::vector<uint>& Face::vertex()
{
	return v;
}

uint & Face::vertex(int & n)
{
	return v[n];
}

std::vector<uint>& Face::normal()
{
	return vn;
}

uint & Face::normal(int & n)
{
	return vn[n];
}

std::vector<uint>& Face::mapping()
{
	return t;
}

uint & Face::mapping(int & n)
{
	return t[n];
}

void Face::set(std::vector<uint>&ve, std::vector<uint> &vne, std::vector<uint> &te)
{
	v = ve;
	vn = vne;
	t = te;
}

void Face::addVertex(uint & n)
{
	v.push_back(n);
}

void Face::addVertexAt(uint & n, int& w)
{
	v.insert(v.begin() + w, n);
}

void Face::removeVertex(uint & n)
{
	for (std::vector<uint>::iterator i = v.begin(); i != v.end(); i++)
	{
		if (*i == n)
		{
			v.erase(i);
		}
	}
	
}

void Face::removeVertexAt(int & n)
{
	v.erase(v.begin() + n);
}

void Face::addNormal(uint & n)
{
	vn.push_back(n);
}

void Face::addNormalAt(uint & n, int & w)
{
	vn.insert(vn.begin() + w, n);
}

void Face::removeNormal(uint & n)
{
	for (std::vector<uint>::iterator i = vn.begin(); i != vn.end(); i++)
	{
		if (*i == n)
		{
			vn.erase(i);
		}
	}
}

void Face::removeNormalAt(int & n)
{
	vn.erase(vn.begin() + n);
}

void Face::addMapping(uint & n)
{
	t.push_back(n);
}

void Face::addMappingAt(uint & n, int & w)
{
	t.insert(t.begin() + w,n);
}

void Face::removeMapping(uint & n)
{
	for (std::vector<uint>::iterator i = t.begin(); i != t.end(); i++)
	{
		if (*i == n)
		{
			t.erase(i);
		}
	}
}

void Face::removeMappingAt(int & n)
{
	t.erase(t.begin() + n);
}

int Face::sizeVertex()
{
	return v.size();
}

int Face::sizeMapping()
{
	return t.size();
}

int Face::sizeNormal()
{
	return vn.size();
}

#include "Group.h"



Group::Group()
{
	mtl = 0;
	mtlS = "";
	enabled = true;
}

Group::Group(std::string na)
{
	n = na;
	mtl = 0;
	mtlS = "";
	enabled = true;
}


Group::~Group()
{
}


std::vector<Face>* Group::face()
{
	return &v;
}

Face * Group::face(int & n)
{
	return &v[n];
}

void Group::set(std::vector<Face>& ve)
{
	v = ve;
}

Face * Group::addFace()
{
	 v.emplace_back();
	 return &v[v.size() - 1];
}

void Group::addFace(Face & n)
{
	v.push_back(n);
}

void Group::addFaceAt(Face & n, int& w)
{
	v.insert(v.begin() + w, n);
}

void Group::removeFace(Face & n)
{
	for (std::vector<Face>::iterator i = v.begin(); i != v.end(); i++)
	{
		if (*i == n)
		{
			v.erase(i);
		}
	}

}

void Group::removeFaceAt(int & n)
{
	v.erase(v.begin() + n);
}

std::string Group::name()
{
	return n;
}

void Group::setName(std::string na)
{
	n = na;
}

int Group::size()
{
	return v.size();
}

uint & Group::MTL()
{
	return mtl;
}

void Group::setMTL(uint & m)
{
	mtl = m;
}

std::string & Group::pathMTL()
{
	return mtlS;
}

void Group::setPathMTL(std::string s)
{
	mtlS = s;
}

bool & Group::getEnabled()
{
	return enabled;
}

void Group::setEnabled(bool b) 
{
	enabled = b;
}

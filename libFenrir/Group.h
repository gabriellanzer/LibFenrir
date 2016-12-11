#pragma once
#include <vector>
#include <string>
#include "Face.h"
class Group
{
public:
	Group();
	Group(std::string n);
	~Group();

	inline bool operator==(const Group& lhs) {
		if (lhs.v.size() == v.size())
		{
			bool b;
			for (int i = 0; i < v.size(); i++)
			{
				if (v[i] != lhs.v[i])
					return false;
			}
			return true;
		}
		else
			return false;
	}

	inline bool operator!=(const Group& lhs) {
		return !(&lhs == &*this);
	}

	std::vector<Face>* face();
	Face* face(int& n);

	void set(std::vector<Face> &v);

	Face* addFace();
	void addFace(Face& n);
	void addFaceAt(Face & n, int &w);

	void removeFace(Face &n);
	void removeFaceAt(int &n);

	std::string name();
	void setName(std::string n);

	int size();

	uint& MTL();
	void setMTL(uint &m);

	std::string &pathMTL();
	void setPathMTL(std::string s);


	bool &getEnabled();
	void setEnabled(bool);

private:
	std::vector<Face> v;
	std::string n;
	uint mtl;
	std::string mtlS;
	bool enabled;

};


#pragma once
#include "Mesh.h"
#include <fstream>
#include <string>
#include <sstream>

class OBJReader
{
public:
	OBJReader();
	~OBJReader();

	vector<string>* readOBJ(Mesh * mesh, string path);

};


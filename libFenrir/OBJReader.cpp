#include "OBJReader.h"
#include <ctime>


OBJReader::OBJReader()
{
}


OBJReader::~OBJReader()
{
}

vector<string>* OBJReader::readOBJ(Mesh *mesh, string path)
{
	ifstream arq(path);

	if (mesh == NULL)
		mesh = new Mesh();
	// Mesh mesh;
	if (!arq.is_open())
	{
		cout << "error while loading " << path << " couldn't open file\n";
		return NULL;
	}
	cout << "Reading obj at " << path << " ";
	float timer = clock();
	Group *currentgroup = mesh->group("default");

	uint tn;

	char cn;
	string c, t;
	stringstream ss;

	Vector3Df *v;
	Vector2Df *tm;
	bool b = true;
	vector<string> *mtlreturn = new vector<string>; // To return to the resource manager what MTL lib has to be loaded
	char *BUFFER = new char[500];

	arq.getline(BUFFER, 500);

	//getline(arq, t); // trocar getline

	//ss << BUFFER;

	ss >> c;

	while (arq.eof() == false)
	{
		if (c == "g")
		{
			//Create a new group;
			getline(ss, c);
			c.erase(c.begin());
			currentgroup = mesh->group(c);
		}
		else if (c == "v")
		{
			// Create Vertex
			v = mesh->newVertex();
			ss >> *v;

		}
		else if (c == "vn")
		{
			// Create Normal
			v = mesh->newNormal();
			ss >> *v;

		}
		else if (c == "vt")
		{
			// Create Normal
			tm = mesh->newMapping();
			ss >> *tm;

		}
		else if (c == "f")
		{
			getline(ss, t);
			c.clear();
			Face *f = currentgroup->addFace();
			cn = 0;
			for (int i = 0; i < t.size(); i++)
			{
				if (t[i] == ' ')
				{
					if (c.size() > 0)
					{
						tn = (((uint)(atoi(c.c_str()))) - 1);

						if (cn == 2)
							f->addNormal(tn);
						else if (cn == 1)
							f->addMapping(tn);
						else
							f->addVertex(tn);

						c.clear();
					}
					cn = 0;
				}
				else if (t[i] == '/')
				{
					if (c.size() > 0)
					{
						tn = (((uint)(atoi(c.c_str()))) - 1);

						/*if (cn == 2)
							f.addNormal(tn);*/
						if (cn == 1)
							f->addMapping(tn);
						else
							f->addVertex(tn);

						c.clear();
					}
					cn++;
				}
				else {
					c.push_back(t[i]);
				}

			}
			if (c.size() > 0)
			{
				tn = (((uint)(atoi(c.c_str()))) - 1);

				if (cn == 2)
					f->addNormal(tn);
				else if (cn == 1)
					f->addMapping(tn);
				else
					f->addVertex(tn);

				c.clear();
			}

		}
		else if (c == "usemtl")
		{
			getline(ss, c);
			c.erase(c.begin());
			if (currentgroup->pathMTL() != "")
			{
				static string tmps;
				static char cn;
				tmps = currentgroup->name();
				if (tmps.size() > 0)
					cn = tmps.back();
				else
					cn = 0;

				if (cn > '0' && cn <= '9')
				{
					static int tmp;
					tmp = atoi(&cn);
					tmp++;

					tmps.pop_back();
					tmps += to_string(tmp);
				}
				else
				{
					tmps += "_1";
				}


				currentgroup = mesh->group(tmps);
			}
			else
			{
				currentgroup->pathMTL() = c;
			}
		}
		else if (c == "mtllib")
		{
			getline(ss, c);
			c.erase(c.begin());

			mtlreturn->push_back(c);
		}


		//getline(arq, t);
		arq.getline(BUFFER, 500);

		ss.str("");
		ss.clear();

		//ss << t;
		ss << BUFFER;


		ss >> c;


	}

	cout << "Finished in " << (clock() - timer) / CLOCKS_PER_SEC << " seconds.\n";
	return mtlreturn;


}

#include "ResourceManager.h"
#include <iostream>
#include <gl\glew.h>
#include <stdio.h>
#include "IMGReader.h"
#include <GLFW\glfw3.h>
#include "PrimitiveDrawer.h"

#include <assert.h>
ResourceManager *ResourceManager::instance;
ResourceManager::ResourceManager()
{

}


ResourceManager::~ResourceManager()
{
}

ResourceManager * ResourceManager::Instantiate()
{
	if (instance)
		return instance;
	else
	{
		instance = new ResourceManager();
		return instance;
	}
}

void ResourceManager::addVAO(string s, uint u)
{
	mapVAO.insert(map<string, uint>::value_type(s, u));
}

map<string, uint>* ResourceManager::getMapVAO()
{
	return &mapVAO;
}

uint &ResourceManager::getVAO(string s)
{
	return mapVAO.at(s);
}

void ResourceManager::addFBO(string s, FrameBuffer *u)
{
	mapFBO.insert(pair<string, FrameBuffer*>(s, u));
}

map<string, FrameBuffer*>* ResourceManager::getMapFBO()
{
	return &mapFBO;
}

FrameBuffer* ResourceManager::getFBO(string s)
{
	return mapFBO.at(s);
}

void ResourceManager::addShader(string s, uint u)
{
	mapShader.insert(map<string, uint>::value_type(s, u));
}

map<string, uint>* ResourceManager::getShaderMap()
{
	return &mapShader;
}

uint &ResourceManager::getShader(string s)
{
	return mapShader.at(s);
}

void ResourceManager::addProgram(string s, uint u)
{
	mapProgram.insert(map<string, uint>::value_type(s, u));
}

map<string, uint>* ResourceManager::getProgramMap()
{
	return &mapProgram;
}

uint& ResourceManager::getProgram(string s)
{
	for (map<string, uint>::iterator it = mapProgram.begin(); it != mapProgram.end(); it++)
	{
		if (it->first == s)
			return it->second;
	}
}

void ResourceManager::addImage(string s, Image *i)
{
	mapImage.insert(map<string, Image*>::value_type(s, i));
}

map<string, Image*>* ResourceManager::getMapImage()
{
	return &mapImage;
}

Image * ResourceManager::getImage(string s)
{
	for (map<string, Image*>::iterator it = mapImage.begin(); it != mapImage.end(); it++)
	{
		if (it->first == s)
			return it->second;
	}
	return nullptr;
}

void ResourceManager::addMesh(string s, Mesh *m)
{
	mapMesh.insert(map<string, Mesh*>::value_type(s, m));
}

map<string, Mesh*>* ResourceManager::getMapMesh()
{
	return &mapMesh;
}

Mesh * ResourceManager::getMesh(string s)
{
	return mapMesh.at(s);
}

void ResourceManager::addMeshShader(string s, MeshShader *m)
{
	mapMeshShader.insert(map<string, MeshShader>::value_type(s, *m));

}

map<string, MeshShader>* ResourceManager::getMapMeshShader()
{
	return &mapMeshShader;
}

MeshShader * ResourceManager::getMeshShader(string s)
{
	return &mapMeshShader[s];
}

char * ResourceManager::readShader(string path, int mode, string name)
{
	ifstream arq(path);
	string s, t;
	if (!arq.is_open())
	{
		cout << "Couldn't find " << name << " in " << path << "\n Operation aborted.";
		assert(false);

		return nullptr;
	}
	getline(arq, s);
	t = s;
	while (!arq.eof())
	{
		getline(arq, s);
		t += "\n" + s;
	}

	char* shader = (char*)t.c_str();

	if (name == "")
		return shader;

	uint vs = glCreateShader(mode);
	glShaderSource(vs, 1, &shader, NULL);
	glCompileShader(vs);
	GLint isCompiled;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		cout << "In reading " << name << " from " << path << ":\n";
		GLint maxLength = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		char* infoLog = new char[maxLength];
		glGetShaderInfoLog(vs, maxLength, &maxLength, infoLog);

		//The shader is useless now. So delete it.
		glDeleteShader(vs);

		//Provide the infolog in whatever manner you deem best.
		cout << infoLog;


		assert(false);
	}
	mapShader.insert(map<string, uint>::value_type(name, vs));

	return shader;

}

void ResourceManager::addTexture(string s, uint u)
{
	mapTexture.insert(map<string, uint>::value_type(s, u));

}

map<string, uint>* ResourceManager::getMapTexture()
{
	return &mapTexture;
}

uint & ResourceManager::getTexture(string s)
{
	return mapTexture.at(s);
}

void ResourceManager::generateProgram(string s)
{
	uint shader_programme = glCreateProgram();
	mapProgram.insert(map<string, uint>::value_type(s, shader_programme));
}

void ResourceManager::addShaderToProgram(string ss, string sp)
{
	uint p = mapProgram.at(sp);
	uint s = mapShader.at(ss);
	glAttachShader(p, s);
}

void ResourceManager::linkAllPrograms()
{
	for (map<string, uint>::iterator it = mapProgram.begin(); it != mapProgram.end(); it++)
	{
		glLinkProgram(it->second);
		GLint isLinked = 0;
		glGetProgramiv(it->second, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			cout << "In compiling " << it->first << ":\n";
			GLint maxLength = 0;
			glGetProgramiv(it->second, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			char* infoLog = new char[maxLength];
			glGetProgramInfoLog(it->second, maxLength, &maxLength, infoLog);

			//The program is useless now. So delete it.
			glDeleteProgram(it->second);

			//Provide the infolog in whatever manner you deem best.
			cout << infoLog;
			assert(false);
		}
		else
		{
			cout << "Program " << it->first << " is linked.\n";
		}
	}
}

void ResourceManager::generateTriangle()
{
	float points[] = {
		-1.0f / 2.f, 1.0f / 2.f, 0,
		1.0f / 2.f, 1.0f / 2.f, 0.0f,
		0.0f, -1.0f / 2.f, 0 };
	uint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	uint vao;
	glGenVertexArrays(1, &vao);
	mapVAO.insert(map<string, uint>::value_type("triangle", vao));
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0); 	// habilitado primeiro atributo do vbo bound atual
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // identifica vbo atual	

	/* associação do vbo atual com primeiro atributo
	0 identifica que o primeiro atributo está sendo definido
	3, GL_FLOAT identifica que dados são vec3 e estão a cada 3 float.*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	float colors[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	uint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//float colors[] = { 0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f };
	//uint colorsVBO;
	//glGenBuffers(1, &colorsVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


	//glEnableVertexAttribArray(1);

	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);


}

void ResourceManager::generateQuad()
{
	float points[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

	};
	uint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	uint *vao = new uint[2];
	glGenVertexArrays(2, vao);
	mapVAO.insert(map<string, uint>::value_type("quadColor", vao[0]));
	mapVAO.insert(map<string, uint>::value_type("quadTexture", vao[1]));
	glBindVertexArray(vao[0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindVertexArray(vao[1]);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//Color
	{
		glBindVertexArray(vao[0]);

		float colors[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f };
		uint colorsVBO;
		glGenBuffers(1, &colorsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


		glEnableVertexAttribArray(1);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	//Texture
	{
		glBindVertexArray(vao[1]);

		float colors[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f
		};
		uint colorsVBO;
		glGenBuffers(1, &colorsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


		glEnableVertexAttribArray(1);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}

}

/*void ResourceManager::generateTeste()
{

	float points[] = {

		1, 1, 0,
		0.0f, -1, 0,
		0.f, 0.0, -1,
		-1, 1, 0,
		1, 1, 0,
		0.0f, -1, 0,
	};

	uint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(points), points, GL_STATIC_DRAW);

	uint vao;
	glGenVertexArrays(1, &vao);
	mapVAO.insert(map<string, uint>::value_type("teste", vao));
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0); 	// habilitado primeiro atributo do vbo bound atual
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // identifica vbo atual


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	float uv[] = {
		0.5, 0.5,
		0, 0.5,
		0.5, 0.0f,
		0.0f, 0.5,
		0.0f, 0.5,
		0.0f, 0.5 };

	uint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);


	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);


}*/

void ResourceManager::generateShader(string name, char* shader, int mode)
{
	uint vs = glCreateShader(mode);
	glShaderSource(vs, 1, &shader, NULL);
	glCompileShader(vs);
	GLint isCompiled;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		cout << "In compiling " << name << ":\n";
		GLint maxLength = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		char* infoLog = new char[maxLength];
		glGetShaderInfoLog(vs, maxLength, &maxLength, infoLog);

		//The program is useless now. So delete it.
		glDeleteShader(vs);

		//Provide the infolog in whatever manner you deem best.
		cout << infoLog;
		assert(false);
	}
	mapShader.insert(map<string, uint>::value_type(name, vs));
}

void ResourceManager::readImage(string path, string name)
{
	if (name == "")
		name = path;
	//static IMGReader imgR;
	uint i;
	glGenTextures(1, &i);
	Image *img;
	if (path[path.size() - 1] == 'm' && path[path.size() - 2] == 't' && path[path.size() - 3] == 'p')
		img = IMGReader::loadPTM(i, path);
	else
		img = IMGReader::loadImageInToTexture(i, path);
	if (img == nullptr)
		return;

	mapImage.insert(map<string, Image*>::value_type(name, img));
	mapTexture.insert(map<string, uint>::value_type(name, i));


}

void ResourceManager::readOBJ(string path, string name)
{
	if (name == "")
		name = path;

	static AssimpReader obj;
	//static OBJReader obj;
	Mesh **meshes;
	unsigned int meshCount = 0;
	if (obj.readObj(meshes, meshCount, path) == NULL)
		return;

	for (unsigned int i = 0; i < meshCount; i++)
	{
		mapMesh.insert(map<string, Mesh*>::value_type(name + " " + to_string(i), meshes[i]));
	}
}

void ResourceManager::treatFacesOf(Mesh * m)
{
#if false
	cout << "There's no algorithm of triangulization";
#else
	if (m == nullptr)
	{
		cout << "Couldn't treat the faces because the Mesh was null";
		return;
	}

	vector<Group> *v = m->group();
	cout << "Starting procees of triangulization with ";
	int ng = v->size();
	{
		int n = 0;
		for (int i = 0; i < ng; i++) {
			n += v->at(i).size();
		}
		cout << n << " faces...";
	}


	for (int i = 0; i < ng; i++)
	{
		Group *g = &(*v)[i];

		vector<Face> *fv = g->face();
		const vector<Face> fv_ = *g->face();

		int nf = fv->size();
		int changed = 0;

		fv->clear();
		for (int i = 0; i < nf; i++)
		{
			Face f = (fv_.at(i));
			if (f.sizeVertex() > 3)
			{
				int vt[3] = { 0,1,2 };
				for (int i = 2; i < f.sizeVertex(); i++)
				{
					Face newFace;
					for (int i = 0; i < 3; i++)
					{
						newFace.addVertex(f.vertex(vt[i]));
						if (f.sizeMapping())
							newFace.addMapping(f.mapping(vt[i]));
						// if (f.sizeNormal())
						//	newFace.addNormal(f.normal(vt[i]));
					}
					fv->push_back(newFace);

					for (int i = 1; i < 3; i++)
					{
						vt[i] += 1;
						if (vt[i] >= f.sizeVertex())
						{
							vt[i] -= f.sizeVertex();
						}
					}
				}
				changed++;
			}
			else
			{
				fv->push_back(f);
			}
		}

	}
	cout << " Ended with ";
	{
		int n = 0;
		for (int i = 0; i < ng; i++) {
			n += v->at(i).size();
		}
		cout << n << " faces.\n";
	}
#endif

}

void ResourceManager::treatFacesOf(string s)
{
	treatFacesOf(mapMesh.at(s));
}


Image *ResourceManager::generateUVImage(uint width, uint height, string mesh)
{

	Mesh *m = getMesh(mesh);
	if (m == nullptr)
	{
		cout << "Could not generate UV because mesh was null, check mesh name" << endl;
		return nullptr;
	}
	Image *img = new Image(width, height);

	{
		int size = width * height;
		for (int i = 0; i < size; i++)
		{
			img->setPixel(0 << 24, i);
		}

	}

	vector<Group> *v = m->group();
	cout << "Starting UV image generation with ";
	int ng = v->size();
	{
		int n = 0;
		for (int i = 0; i < ng; i++) {
			n += v->at(i).size();
		}
		cout << n << " faces...";
	}

	for (int i = 0; i < ng; i++)
	{
		Group *g = &(*v)[i];

		vector<Face> *fv = g->face();

		int nf = fv->size();

		for (int i = 0; i < nf; i++)
		{
			Face &f = (fv->at(i));

			for (int i = 0; i < f.sizeMapping(); i++)
			{

				Vector2Df uv1 = m->Mapping()->at(f.mapping().at(i));
				Vector2Df uv2;
				if (i == f.sizeMapping() - 1)
				{
					uv2 = m->Mapping()->at(f.mapping().at(0));
				}
				else
				{
					uv2 = m->Mapping()->at(f.mapping().at(i + 1));
				}
				int x1 = uv1.x() *  width;
				int x2 = uv2.x() *  width;
				int y1 = uv1.y() *  height;
				int y2 = uv2.y() *  height;

				gPritiveDrawer->drawLine(*img, x1, y1, x2, y2, 0xFFFFFFFF);


				//cout << "\tu: " << uv.x() << "\tv: " << uv.y() << endl;
			}
		}

	}
	/*cout << " Ended with ";
	{
		int n = 0;
		for (int i = 0; i < ng; i++) {
			n += v->at(i).size();
		}
		cout << n << " faces.\n";
	}*/

	return img;
}

void ResourceManager::generateVAOandRegister(string name)
{
	MeshShader *m = getMeshShader(name);
	m->toVAO();
	for (int i = 0; i < m->getGroups()->size(); i++) {
		mapVAO.insert(map<string, uint>::value_type(name + to_string(i), m->getGroup(i)->getVAO()));
		cout << "Registered vao " << m->getGroup(i)->getVAO() << " as " << name << i << endl;
	}
}

MeshShader * ResourceManager::adaptMeshtoShader(Mesh *m, string name)
{
	if (m == nullptr)
		return nullptr;
	MeshShader *mesh = nullptr;
	if (name != "")
	{
		mapMeshShader.insert(map<string, MeshShader>::value_type(name, MeshShader()));
		mesh = &mapMeshShader.at(name);
	}
	else
	{
		mesh = new MeshShader();
	}

	mesh->setUV(m->Mapping());
	mesh->setVertex(m->Vertex());

	//Get the vector of Groups of the MeshShader
	vector<GroupShader> *groups = mesh->getGroups();

	for (int g = 0; g < m->sizeGroup(); g++) //For each group
	{
		Group *group = m->group(g); //Get the current Group

		if (group->size() == 0) //If group doesn't have vertex, don't create it 
			continue;

		uint c = (16777216 / (m->sizeGroup() + 1)*(g + 1)) | (255 << 24);
		groups->emplace_back(c); // Create a new GroupShader and get it
		GroupShader *groupS = &(*groups)[groups->size() - 1];

		vector<uint> *vertex = groupS->getVertex(), *uv = groupS->getUV(), *normal = groupS->getNormal(); //Get the reference to the vector of indexes

		for (int f = 0; f < group->size(); f++)  //For each face
		{
			Face *face = group->face(f);
			if (face->sizeVertex() > 3) {
				cout << "Face " << f << "of Group" << g << " have more than 3 vertexes\n";
			}
			for (int i = 0; i < face->sizeVertex(); i++) //For each vertex in the face
			{
				vertex->push_back(face->vertex(i));

				if (face->sizeMapping())
					uv->push_back(face->mapping(i));

				if (face->sizeNormal())
					normal->push_back(face->normal(i));

			}
		}

	}
}

bool ResourceManager::adaptMeshtoShader(string nameOfMesh, string nameNewMesh)
{
	if (nameNewMesh == "") {
		nameNewMesh = nameOfMesh;
	}
	return adaptMeshtoShader(mapMesh.at(nameOfMesh), nameNewMesh) != nullptr;
}

int ResourceManager::getSizeOfVAO(string nameOf, int group)
{
	return mapMeshShader.at(nameOf).getGroup(group)->getVertex()->size();
}

void ResourceManager::registerVAOof(string name)
{
	MeshShader *m = getMeshShader(name);
	for (int i = 0; i < m->getGroups()->size(); i++) {
		mapVAO.insert(map<string, uint>::value_type(name + to_string(i), m->getGroup(i)->getVAO()));
		cout << "Registered vao " << m->getGroup(i)->getVAO() << " as " << name << i << endl;
	}
}

void ResourceManager::updateTextureOfImage(string name)
{
	uint n = mapTexture.at(name);

	Image *image = mapImage.at(name);

	glBindTexture(GL_TEXTURE_2D, n);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, image->getPixels());

}

uint ResourceManager::createTextureOfImage(string name, string newname, bool registerNewImageOnMap)
{
	uint n;
	glGenTextures(1, &n);
	Image *image = mapImage.at(name);

	glBindTexture(GL_TEXTURE_2D, n);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, image->getPixels());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	mapTexture.insert(map<string, uint>::value_type(newname, n));
	if (registerNewImageOnMap)
	{
		mapImage.insert(map<string, Image*>::value_type(newname, new Image(image)));
	}
	return n;
}

FrameBuffer * ResourceManager::createDefaultFrameBuffer(GLuint texWidth, GLuint texHeight, string name, bool depthAsTexture, bool attachNormalsTexture)
{
	if (name == "")
		name == "defaultFBO";

	FrameBuffer *fbo = new FrameBuffer();

	//Define RenderTexture
	{
		// The texture we're going to render to
		GLuint renderTexture;
		glGenTextures(1, &renderTexture);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, renderTexture);

		// Give an empty image to OpenGL ( the last "NULL" )
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		// Poor filtering. Needed !
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//Attach to FrameBuffer on layout 0
		fbo->Attach(Color_Attachment, renderTexture, 0);

		//Register on map
		addTexture(name + "_renderTexture", renderTexture);

		//Unbind Texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//Define NormalsTexture
	if (attachNormalsTexture)
	{
		// The texture we're going to render to
		GLuint normalsTexture;
		glGenTextures(1, &normalsTexture);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, normalsTexture);

		// Give an empty image to OpenGL ( the last "NULL" )
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		// Poor filtering. Needed !
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//Unbind Texture
		glBindTexture(GL_TEXTURE_2D, 0);

		//Attach to FrameBuffer on layout 2 or 3
		fbo->Attach(Color_Attachment, normalsTexture, 1);

		//Register on map
		addTexture(name + "_normalsTexture", normalsTexture);
	}

	//Define Depth (as buffer or as texture)
	if (depthAsTexture)
	{
		//Define DepthTexture
		//The texture we're going to render to
		GLuint depthTexture;
		glGenTextures(1, &depthTexture);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, depthTexture);

		// Give an empty image to OpenGL ( the last "NULL" )
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, texWidth, texHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

		// Poor filtering. Needed !
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		/*
		//==================Apparently these are all optionals?=================//
		//Especific parameters to depth texture
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
		//glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
		*/

		//Attach to FrameBuffer on layout 2
		fbo->Attach(Depth_Attachment, depthTexture);

		//Register on map
		addTexture(name + "_depthTexture", depthTexture);

		//Unbind Texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		//The depth as buffer
		GLuint depthrenderbuffer;
		glGenRenderbuffers(1, &depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, texWidth, texHeight);

		//Attach to FrameBuffer
		fbo->Attach(Depth_Attachment, depthrenderbuffer, 0, true);

		//Unbind RenderBuffer
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	return fbo;
}

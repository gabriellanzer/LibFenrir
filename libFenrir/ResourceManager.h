#pragma once
#include <map>
#include <string>
#include "OBJReader.h"
#include "AssimpReader.h"
#include "MeshShader.h"
#include "Image.h"
#include "FrameBuffer.h"
#ifndef UINT_H
#define UINT_H
typedef unsigned int  uint;
#endif

using namespace std;
class ResourceManager
{
public:
	~ResourceManager();

	static ResourceManager * Instantiate();

	void addVAO(string, uint);
	map<string, uint> *getMapVAO();
	uint &getVAO(string);

	void addShader(string, uint);
	map<string, uint> *getShaderMap();
	uint &getShader(string);

	void addProgram(string, uint);
	map<string, uint> *getProgramMap();
	uint &getProgram(string);

	void addTexture(string, uint);
	map<string, uint> *getMapTexture();
	uint& getTexture(string);

	void addImage(string, Image*);
	map<string, Image*> *getMapImage();
	Image* getImage(string);

	void addMesh(string, Mesh*);
	map<string, Mesh*> *getMapMesh();
	Mesh* getMesh(string);

	void addMeshShader(string, MeshShader*);
	map<string, MeshShader> *getMapMeshShader();
	MeshShader* getMeshShader(string);

	void addFBO(string, FrameBuffer*);
	map<string, FrameBuffer*> *getMapFBO();
	FrameBuffer* getFBO(string);

	char * readShader(string path, int mode, string name = ""); // to compile it needs the name.


	void generateProgram(string);
	void addShaderToProgram(string, string);
	void linkAllPrograms();

	void generateTriangle();
	void generateQuad();

	void generateShader(string name, char * shader, int mode);
	

	void readOBJ(string path, string name = "");
	void readImage(string path, string name = "");

	void treatFacesOf(Mesh *);
	void treatFacesOf(string);
	Image *generateUVImage(uint width, uint height, string mesh);

	void generateVAOandRegister(string);

	MeshShader * adaptMeshtoShader(Mesh *, string name = "");
	bool adaptMeshtoShader(string nameOfMesh, string nameNewMesh = "");

//debug
	
	int getSizeOfVAO(string nameOf, int group);

	void registerVAOof(string name);

	void updateTextureOfImage(string name);
	uint createTextureOfImage(string name, string newname, bool registerNewImageInMap = true);

	FrameBuffer *createDefaultFrameBuffer(GLuint texWidth, GLuint texHeight, string name = "", bool depthAsTexture = false, bool attachNormalsTexture = false);
	

private:
	ResourceManager();
	static ResourceManager *instance;
	map<string, MeshShader> mapMeshShader;
	map<string, uint> mapVAO;
	map<string, uint> mapShader;
	map<string, uint> mapProgram;
	map<string, uint> mapTexture;
	map<string, Mesh*> mapMesh;
	map<string, Image*> mapImage;
	map<string, FrameBuffer*> mapFBO; //Map of Frame Buffer Objects
};

#define gResource ResourceManager::Instantiate()

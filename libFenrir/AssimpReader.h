#pragma once
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "Mesh.h"

using namespace std;
class AssimpReader
{
public:
	AssimpReader();
	~AssimpReader();

	vector<string>* readObj(Mesh **&meshes, unsigned int &nMeshes, string path)
	{
		// Create an instance of the Importer class
		Assimp::Importer importer;
		// And have it read the given file with some example postprocessing
		// Usually - if speed is not the most important aspect for you - you'll 
		// propably to request more postprocessing than we do in this example.
		const aiScene* scene = importer.ReadFile(path,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		// If the import failed, report it
		if (!scene)
		{
			cout << "error while loading " << path << " couldn't open file\n";
			return NULL;
		}
		// Now we can access the file's contents. 

		//Vector for Materials name
		vector<string> *mtlreturn = new vector<string>;

		//Build mesh with scene
		//For each mesh
		nMeshes = scene->mNumMeshes;


		cout << "There is " << nMeshes << " meshes in " << path << ".\n";

		meshes = new Mesh*[nMeshes];

		for (int n = 0; n < nMeshes; n++)
		{
			//Instanciate Mesh
			meshes[n] = new Mesh();

			//Get first mesh for testing
			aiMesh *aMesh = scene->mMeshes[n];

			//Setup default group
			Group *currentgroup = meshes[n]->group("default");

			//Setup faces
			{
				aiFace *aFaces = aMesh->mFaces;
				//Construct faces
				for (unsigned int i = 0; i < aMesh->mNumFaces; i++)
				{
					//Add face
					Face *f = currentgroup->addFace();

					unsigned int nIndices = aFaces[i].mNumIndices;
					for (unsigned int j = 0; j < nIndices; j++)
					{
						f->addVertex(aFaces[i].mIndices[j]);

						if (aMesh->HasNormals())
							f->addNormal(aFaces[i].mIndices[j]);
						if (aMesh->HasTextureCoords(0))
							f->addMapping(aFaces[i].mIndices[j]);
					}
				}
			}


			//Create Vertex Attributes
			for (unsigned int i = 0; i < aMesh->mNumVertices; i++)
			{
				Vector3Df *v = meshes[n]->newVertex();
				*v = Vector3Df((aMesh->mVertices[i]).x, (aMesh->mVertices[i]).y, (aMesh->mVertices[i]).z);

				//Create Normals Attributes
				if (aMesh->HasNormals())
				{
					v = meshes[n]->newNormal();
					*v = Vector3Df((aMesh->mNormals[i]).x, (aMesh->mNormals[i]).y, (aMesh->mNormals[i]).z);
				}

				//Create UV Texture Coords Attributes
				if (aMesh->HasTextureCoords(0))
				{
					Vector2Df *uv = meshes[n]->newMapping();
					*uv = Vector2Df(aMesh->mTextureCoords[0][i].x, aMesh->mTextureCoords[0][i].y);
				}
			}

			//Register Materials in mesh
			aiString name;
			scene->mMaterials[aMesh->mMaterialIndex]->Get(AI_MATKEY_NAME, name);
			cout << "Material name " << name.C_Str() << endl;
			mtlreturn->push_back(name.C_Str());
		}



		// We're done. Everything will be cleaned up by the importer destructor
		return mtlreturn;
	}
};


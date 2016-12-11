#include "MeshShader.h"
#include <gl\glew.h>

#include <GLFW\glfw3.h>




MeshShader::MeshShader()
{
}


MeshShader::~MeshShader()
{
}

vector<Vector3Df>* MeshShader::getVertex()
{
	return &vertex;
}

Vector3Df & MeshShader::getVertex(int n)
{
	return vertex[n];
}

void MeshShader::setVertex(vector<Vector3Df>* v)
{
	vertex = *v;
}

vector<Vector2Df>* MeshShader::getUV()
{
	return &uv;
}

Vector2Df & MeshShader::getUV(int n)
{
	return uv[n];
}

void MeshShader::setUV(vector<Vector2Df>* v)
{
	uv = *v;
}

vector<GroupShader>* MeshShader::getGroups()
{
	return &group;
}

GroupShader * MeshShader::getGroup(int n)
{
	return &group[n];
}

void MeshShader::setGroups(vector<GroupShader>* g)
{
	group = *g;
}

bool MeshShader::GrouptoVAO(GroupShader * g)
{
	if (g == nullptr)
	{
		cout << "Null group\n";
		return false;
	}
	uint *vao = &g->getVAO();
	if (*vao == 0)
	{
		glGenVertexArrays(1, vao);
	}
	glBindVertexArray(*vao);

	vector<uint> *vI = g->getVertex();
	vector<uint> *uvI = g->getUV();
	vector<uint> *nI = g->getNormal();

	int size = vI->size();
	float *vF = new float[size * 3]; //vertex * num vertex
	float *groupColorF = new float[size * 3];
	float *faceColorF = new float[size * 3];
	float *vertexColorF = new float[size * 3];
	float *uvF = new float[size * 2];
	float *nF = new float[size * 3];

	for (int i = 0; i < size; i++)
	{
		//VERTEX
		Vector3Df vn = vertex[(*vI)[i]];
		for (int j = 0; j < 3; j++)
		{
			vF[i * 3 + j] = vn[j];
		}

		//NORMAL
		Vector3Df nn = vertex[(*nI)[i]];
		for (int j = 0; j < 3; j++)
		{
			nF[i * 3 + j] = nn[j];
		}

		//UV
		Vector2Df uvn;
		if (uvI->size() > 0)
			uvn = uv[(*uvI)[i]];

		for (int j = 0; j < 2; j++)
		{
			uvF[i * 2 + j] = uvn[j];
		}

		groupColorF[i * 3] = ((g->getColor() >> 16) & 0xff) / 255.0f;
		groupColorF[i * 3 + 1] = ((g->getColor() >> 8) & 0xff) / 255.0f;
		groupColorF[i * 3 + 2] = (g->getColor() & 0xff) / 255.0f;

		/*	for (int j = 0; j < 3; j++)
			{
				cout << groupColorF[i * 3 + j] << ", ";

			}
			cout << "\n";*/
		if (uvI->size() > 0) {
			/*switch (i % 3)
			{
			case 0:
				vertexColorF[i * 3] = uvn[1];
				vertexColorF[i * 3 + 1] = 0.0f;
				vertexColorF[i * 3 + 2] = uvn[0];
				break;
			case 1:
				vertexColorF[i * 3] = 0.0f;
				vertexColorF[i * 3 + 1] = 0.0f;
				vertexColorF[i * 3 + 2] = 0.0f;
				break;
			case 2:
				vertexColorF[i * 3] = 0.0f;
				vertexColorF[i * 3 + 1] = 0.0f;
				vertexColorF[i * 3 + 2] = uvn[0];
				break;
			}*/
			vertexColorF[i * 3] = uvn[1];
			vertexColorF[i * 3 + 1] = 0.0f;
			vertexColorF[i * 3 + 2] = uvn[0];
		}
		else
		{
			switch (i % 3)
			{
			case 0:
				vertexColorF[i * 3] = 1.0f;
				vertexColorF[i * 3 + 1] = 0.0f;
				vertexColorF[i * 3 + 2] = 0.0f;
				break;
			case 1:
				vertexColorF[i * 3] = 0.0f;
				vertexColorF[i * 3 + 1] = 0.0f;
				vertexColorF[i * 3 + 2] = 0.0f;
				break;
			case 2:
				vertexColorF[i * 3] = 0.0f;
				vertexColorF[i * 3 + 1] = 0.0f;
				vertexColorF[i * 3 + 2] = 1.0f;
				break;
			}
		}
		

		unsigned int c = (16777216 / (size / 3 + 1)*(i / 3 + 1)) | (255 << 24);
		faceColorF[i * 3] = ((c >> 16) & 0xff) / 255.0f;
		faceColorF[i * 3 + 1] = ((c >> 8) & 0xff) / 255.0f;
		faceColorF[i * 3 + 2] = (c & 0xff) / 255.0f;
	}




	uint *vvbo = new uint[6];

	glGenBuffers(6, vvbo);
	

	glBindBuffer(GL_ARRAY_BUFFER, vvbo[e_vertex]); // bind vbo of vertex

	//cout << "bytes : " << size * 3 * sizeof(float) << endl;

	glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(float), vF, GL_STATIC_DRAW); // fill the buffer

	glEnableVertexAttribArray(0); // enable atrib in the vao
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // put the information of the atrib in the vao


	glBindBuffer(GL_ARRAY_BUFFER, vvbo[e_texture]);
	glBufferData(GL_ARRAY_BUFFER, size * 2 * sizeof(float), uvF, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);


	glBindBuffer(GL_ARRAY_BUFFER, vvbo[e_normal]); // bind vbo of vertex


	glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(float), nF, GL_STATIC_DRAW); // fill the buffer

	glEnableVertexAttribArray(2); // enable atrib in the vao
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL); // put the information of the atrib in the vao


	glBindBuffer(GL_ARRAY_BUFFER, vvbo[e_group]);
	glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(float), groupColorF, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, vvbo[e_face]);
	glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(float) , faceColorF, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, vvbo[e_vertexColor]);
	glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(float), vertexColorF, GL_STATIC_DRAW);
	
	for (int i = 0; i < 6; i++)
	{
		g->setVBO(i, vvbo[i]);
	}

	return true;
}

void MeshShader::toVAO()
{

	for (int i = 0; i < group.size(); i++)
	{
		GrouptoVAO(&group[i]);
	}
}

void MeshShader::bindVBO(int vbo)
{
	for (int i = 0; i < group.size(); i++) 
	{
		group[i].bindVBO(vbo);
	}
}





/*void MeshShader::toVAO(uint n)
{





	uint *vbo =
	//uint *vbo = new uint[3]; // Generate three vbo, vertex, UV and normals
	//glGenBuffers(3, vbo);

	; // relate with the atribute 0 of the vao

															  /*glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
															  glBufferData(GL_ARRAY_BUFFER, sizeof(n_), n_, GL_STATIC_DRAW);

															  glEnableVertexAttribArray(1);
															  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_), m_, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);


}
*/
#include "Model.h"
#include <SOIL.h>
int Model::models = 0;


Model::Model(string file)
{
	name = file;
	VAO = models;
	VBO = models;
	//texture = models;
	models++;
	Import3DFromFile(file);
}

Model::Model()
{

}

Model::~Model()
{
	delete this;
}

void Model::draw()
{
<<<<<<< HEAD
		for (AssimpMesh *mesh : meshes)
			mesh->draw();
}


void Model::Import3DFromFile(const std::string& pFile)
{
	printf("\n Loading %s\n", name.c_str());
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes			    // slou�en� mal�ch plo�ek
		| aiProcess_JoinIdenticalVertices		// NUTN� jinak hodn� duplikuje
		| aiProcess_Triangulate					// prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace // vypocet tangenty, nutny pro spravne pouziti normalove mapy
		| aiProcess_GenNormals;			


	//aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

	const aiScene* scene = importer.ReadFile(pFile, importOptions);

	if (scene){ //pokud bylo nacteni uspesne
		printf("   scene->mNumMeshes = %d\n", scene->mNumMeshes);
		printf("   scene->mNumMaterials = %d\n", scene->mNumMaterials);

		for (unsigned int i = 0; i < scene->mNumMaterials; i++)						//Materials
		{
			const aiMaterial* mat = scene->mMaterials[i];

			aiString name;
			mat->Get(AI_MATKEY_NAME, name);
			printf("   Material [%d] name %s\n", i, name.C_Str());

			aiColor4D d;

			glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
				diffuse = glm::vec4(d.r, d.g, d.b, d.a);

		}
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)						//Objects
		{
			aiMesh* mesh = scene->mMeshes[i];


			AssimpMesh::Verte* pVertices = new AssimpMesh::Verte[mesh->mNumVertices];
			std::memset(pVertices, 0, sizeof(AssimpMesh::Verte)* mesh->mNumVertices);
			//if (mesh->mMaterialIndex != NULL) {
				mat = scene->mMaterials[mesh->mMaterialIndex];
				aiString *src = new aiString;
				mat->GetTexture(aiTextureType_DIFFUSE, 0, src);
				texture = SOIL_load_OGL_texture
					(
					("models/" + string(src->C_Str())).c_str(),
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
					);
				printf("\n   Loading %d\n", texture);
				printf("   %s", src->C_Str());
				if (0 == texture)
				{
					printf("SOIL loading error: '%s'\n", SOIL_last_result());
				}
				printf("\n____________________\n");
				mat->GetTexture(aiTextureType_HEIGHT, 0, src);
				textureNormal = SOIL_load_OGL_texture
					(
					("models/" + string(src->C_Str())).c_str(),
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
					);
				printf("\n   Loading %d\n", textureNormal);
				printf("   %s", src->C_Str());
				if (0 == textureNormal)
				{
					printf("\nSOIL loading error: '%s'\n", SOIL_last_result());
					textureNormal = -1;
				}
				//	glActiveTexture(GL_TEXTURE0);
		//	}
			 for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				if (mesh->HasPositions())
				{
					pVertices[i].Position[0] = mesh->mVertices[i].x;
					pVertices[i].Position[1] = mesh->mVertices[i].y;
					pVertices[i].Position[2] = mesh->mVertices[i].z;
				}
				if (mesh->HasNormals())
				{
					pVertices[i].Normal[0] = mesh->mNormals[i].x;
					pVertices[i].Normal[1] = mesh->mNormals[i].y;
					pVertices[i].Normal[2] = mesh->mNormals[i].z;
				}
				if (mesh->HasTextureCoords(0))
				{
					pVertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
					pVertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
				}
				if (mesh->HasTangentsAndBitangents())
				{
					pVertices[i].Tangent[0] = mesh->mTangents[i].x;
					pVertices[i].Tangent[1] = mesh->mTangents[i].y;
					pVertices[i].Tangent[2] = mesh->mTangents[i].z;
					//pVertices[i].Bitangens[0] = mesh->mBitangents[i].x;
					//pVertices[i].Bitangens[1] = mesh->mBitangents[i].y;
					//pVertices[i].Bitangens[2] = mesh->mBitangents[i].z;
				}
				
			}

			unsigned int* pIndices = nullptr;

			if (mesh->HasFaces())
			{

				pIndices = new unsigned int[mesh->mNumFaces * 3];
				for (unsigned int i = 0; i < mesh->mNumFaces; i++)
				{
					pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
					pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
					pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
				}
			}


			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &IBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(AssimpMesh::Verte)* mesh->mNumVertices, pVertices, GL_STATIC_DRAW);
			
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AssimpMesh::Verte), (GLvoid*)(nullptr));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AssimpMesh::Verte), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(AssimpMesh::Verte), (GLvoid*)(6 * sizeof(GLfloat)));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(AssimpMesh::Verte), (GLvoid*)(8 * sizeof(GLfloat)));
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(AssimpMesh::Verte), (GLvoid*)(11 * sizeof(GLfloat)));
			//glEnableVertexAttribArray(5);
			//glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(AssimpMesh::Verte), (GLvoid*)(14 * sizeof(GLfloat)));


			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(VAO);

			GLuint err = glGetError();
			if (err != GL_NO_ERROR)
			{
				std::cout << "GL ERROR: " << err << std::endl;
				return;
			}

			indicesCount = mesh->mNumFaces * 3;
			meshes.push_back(new AssimpMesh(i, VAO, VBO, IBO, indicesCount));
=======
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
}


void Model::Import3DFromFile(const std::string& pFile)
{
	printf("Loading %s\n", name.c_str());
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes			    // slou�en� mal�ch plo�ek
		| aiProcess_JoinIdenticalVertices		// NUTN� jinak hodn� duplikuje
		| aiProcess_Triangulate					// prevod vsech ploch na trojuhelniky
		| aiProcess_CalcTangentSpace;			// vypocet tangenty, nutny pro spravne pouziti normalove mapy


	//aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

	const aiScene* scene = importer.ReadFile(pFile, importOptions);

	if (scene){ //pokud bylo nacteni uspesne
		printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
		printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

		for (unsigned int i = 0; i < scene->mNumMaterials; i++)						//Materials
		{
			const aiMaterial* mat = scene->mMaterials[i];

			aiString name;
			mat->Get(AI_MATKEY_NAME, name);
			printf("Material [%d] name %s\n", i, name.C_Str());

			aiColor4D d;

			glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
				diffuse = glm::vec4(d.r, d.g, d.b, d.a);

		}

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)						//Objects
		{
			aiMesh* mesh = scene->mMeshes[i];


			AssimpMesh::Verte* pVertices = new AssimpMesh::Verte[mesh->mNumVertices];
			std::memset(pVertices, 0, sizeof(AssimpMesh::Verte)* mesh->mNumVertices);
			if (mesh->mMaterialIndex != NULL) {
				mat = scene->mMaterials[mesh->mMaterialIndex];
				aiString *src = new aiString;
				mat->GetTexture(aiTextureType_DIFFUSE, 0, src);
				printf("%s", src->C_Str());
				texture = SOIL_load_OGL_texture
					(
					("models/" + string(src->C_Str())).c_str(),
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
					);
				printf("\nLoading %d\n", texture);
				if (0 == texture)
				{
					printf("SOIL loading error: '%s'\n", SOIL_last_result());
				}
				//	glActiveTexture(GL_TEXTURE0);
			}
			 for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				if (mesh->HasPositions())
				{
					pVertices[i].Position[0] = mesh->mVertices[i].x;
					pVertices[i].Position[1] = mesh->mVertices[i].y;
					pVertices[i].Position[2] = mesh->mVertices[i].z;
				}
				if (mesh->HasNormals())
				{
					pVertices[i].Normal[0] = mesh->mNormals[i].x;
					pVertices[i].Normal[1] = mesh->mNormals[i].y;
					pVertices[i].Normal[2] = mesh->mNormals[i].z;
				}
				if (mesh->HasTextureCoords(0))
				{
					pVertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
					pVertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
				}
				if (mesh->HasTangentsAndBitangents())
				{
					pVertices[i].Tangent[0] = mesh->mTangents[i].x;
					pVertices[i].Tangent[1] = mesh->mTangents[i].y;
					pVertices[i].Tangent[2] = mesh->mTangents[i].z;
				}
				
			}

			unsigned int* pIndices = nullptr;

			if (mesh->HasFaces())
			{

				pIndices = new unsigned int[mesh->mNumFaces * 3];
				for (unsigned int i = 0; i < mesh->mNumFaces; i++)
				{
					pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
					pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
					pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
				}
			}


			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &IBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(AssimpMesh::Verte)* mesh->mNumVertices, pVertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AssimpMesh::Verte), (GLvoid*)(0));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AssimpMesh::Verte), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(AssimpMesh::Verte), (GLvoid*)(6 * sizeof(GLfloat)));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(AssimpMesh::Verte), (GLvoid*)(8 * sizeof(GLfloat)));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(VAO);

			GLuint err = glGetError();
			if (err != GL_NO_ERROR)
			{
				std::cout << "GL ERROR: " << err << std::endl;
				return;
			}

			indicesCount = mesh->mNumFaces * 3;
>>>>>>> origin/master

			delete[] pVertices;
			delete[] pIndices;
		}
	}
	else{
		printf("Error during parsing mesh from %s : %s \n", pFile.c_str(), importer.GetErrorString());
	}
	glBindVertexArray(0);
	}

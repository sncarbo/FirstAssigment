#include "Model.h"
#include <iostream>

Model::Model() : modelPath("./BakerHouse/BakerHouse.fbx")
{}

Model::~Model()
{}

void Model::Load()
{
	if (modelPath != nullptr)
	{
		scene = aiImportFile(modelPath, aiProcessPreset_TargetRealtime_MaxQuality);

		if (scene)
		{
			LoadMaterials();
			LoadMeshes();
		}
		else
		{
			LOG2("Error loading %s: %s", modelPath, aiGetErrorString());
		}
	}
}

void Model::LoadMaterials()
{
	aiString file;

	if(scene->mNumMaterials == 1)
	{
		if (scene->mMaterials[0]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			char* absolute_path = new char[MAX_PATH];
			GetFullPathName(file.data, MAX_PATH, absolute_path, nullptr);
			
			char* path = new char[MAX_PATH];
			unsigned index = 0;

			while (absolute_path[index] != string::npos)
			{
				if (absolute_path[index] == '\\\\')
				{
					path[index] = '\\';
					index ++;
				}
				else
				{
					path[index] = absolute_path[index];
					++index;
				}				
			}

			App->GetTextures()->SetTexturePath(absolute_path);

			material = App->GetTextures()->LoadTexture();
		}
	}
}

void Model::LoadMeshes()
{
	mesh = new Mesh();

	for (unsigned i = 0; i < scene->mNumMeshes; ++i)
	{
		mesh->LoadVBO(scene->mMeshes[i]);
		mesh->LoadEBO(scene->mMeshes[i]);
		mesh->CreateVAO(i);
	}
}

void Model::SetModelPath(const char* modelPath)
{
	this->modelPath = modelPath;
}

Mesh* Model::GetMesh() const
{
	return mesh;
}

unsigned Model::GetMaterial() const
{
	return material;
}
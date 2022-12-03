#include "Model.h"
#include <iostream>

const char* Model::modelPath = "Models/BakerHouse.fbx";

Model::Model()
{}

Model::~Model()
{}

void Model::Load(const char* path, const char* texturePath)
{
	if (path != nullptr)
	{
		scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

		if (scene)
		{
			LoadMaterials(path, texturePath);
			LoadMeshes();
		}
		else
		{
			LOG2("Error loading %s: %s", path, aiGetErrorString());
		}
	}
}

void Model::LoadMaterials(const char* path, const char* texturePath)
{
	if (path != nullptr)
	{
		if (texturePath == nullptr)
		{
			aiString file;

			if (scene->mNumMaterials == 1)
			{
				if (scene->mMaterials[0]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
				{
					material = App->GetTextures()->LoadTexture(modelPath, file.data);
				}
			}
		}
		else
			material = App->GetTextures()->LoadTexture(modelPath, texturePath);
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

Mesh* Model::GetMesh() const
{
	return mesh;
}

unsigned Model::GetMaterial() const
{
	return material;
}
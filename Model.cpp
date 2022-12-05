#include "Model.h"
#include <iostream>

const char* Model::modelPath = "Assets/BakerHouse.fbx";

Model::Model() : center(float3(0.0f, 0.0f, 0.0f))
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
			mesh = new Mesh();

			LoadMaterials(path, texturePath);
			LoadMeshes();
			CalculateModelCenter();
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
	}
	else
		material = App->GetTextures()->LoadTexture(modelPath, texturePath);
}

void Model::LoadMeshes()
{
	for (unsigned i = 0; i < scene->mNumMeshes; ++i)
	{
		mesh->LoadVBO(scene->mMeshes[i]);
		mesh->LoadEBO(scene->mMeshes[i]);
		mesh->CreateVAO(i);
	}
}

void Model::CalculateModelCenter()
{
	float averageX = 0.0f;
	float averageY = 0.0f;
	float averageZ = 0.0f;

	for (unsigned i = 0; i < scene->mNumMeshes; ++i)
	{
		averageX += scene->mMeshes[i]->mAABB.mMax.x;
		averageX += scene->mMeshes[i]->mAABB.mMin.x;

		averageY += scene->mMeshes[i]->mAABB.mMax.y;
		averageY += scene->mMeshes[i]->mAABB.mMin.y;

		averageZ += scene->mMeshes[i]->mAABB.mMax.z;
		averageZ += scene->mMeshes[i]->mAABB.mMin.z;
	}

	averageX = averageX / (2 * scene->mNumMeshes);
	averageY = averageY / (2 * scene->mNumMeshes);
	averageZ = averageZ / (2 * scene->mNumMeshes);

	center = float3(averageX, averageY, averageZ);
}

Mesh* Model::GetMesh() const
{
	return mesh;
}

unsigned Model::GetMaterial() const
{
	return material;
}

float3 Model::GetCenter() const
{
	return center;
}
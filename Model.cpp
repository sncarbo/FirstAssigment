#include "Model.h"
#include <iostream>

const char* Model::modelPath = "Assets/BakerHouse/BakerHouse.fbx";

Model::Model() :  center(float3(0.0f, 0.0f, 0.0f))
{}

Model::~Model()
{}

void Model::Load(const char* path, const char* texturePath)
{
	if (path != nullptr)
	{
		App->AssimpLOG("Creating aiScene structure.\n");

		scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

		if (scene)
		{
			mesh = new Mesh();

			LoadMaterials(path, texturePath);
			LoadMeshes();
			CalculateModelParameters();
		}
		else
		{
			LOG2("Error loading %s: %s", path, aiGetErrorString());
		}
	}
}

void Model::LoadMaterials(const char* path, const char* texturePath)
{
	App->AssimpLOG("Loading materials.\n");

	if (path != nullptr)
	{
		if (texturePath == nullptr)
		{
			aiString file;

			if (scene->mNumMaterials == 1)
			{
				App->AssimpLOG("Loading one material.\n");

				if (scene->mMaterials[0]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
				{
					App->AssimpLOG("Loading Diffuse Texture.\n");

					material = App->GetTextures()->LoadTexture(path, file.data);
				}
				else
					App->AssimpLOG("Error loading materials.\n");
			}
			else 
				App->AssimpLOG("Error loading materials.\n");
		}
		else
			App->AssimpLOG("Error loading materials.\n");
	}
	else
		material = App->GetTextures()->LoadTexture(modelPath, texturePath);
}

void Model::LoadMeshes()
{
	App->AssimpLOG("Loading all meshes.\n");

	for (unsigned i = 0; i < scene->mNumMeshes; ++i)
	{
		App->AssimpLOG("Loading VBOs.\n");

		mesh->LoadVBO(scene->mMeshes[i]);

		App->AssimpLOG("Loading EBOs.\n");

		mesh->LoadEBO(scene->mMeshes[i]);

		App->AssimpLOG("Creating VAOs.\n");

		mesh->CreateVAO(i);
	}
}

void Model::CalculateModelParameters()
{
	float averageX = 0.0f;
	float averageY = 0.0f;
	float averageZ = 0.0f;

	float maxX = 0.0f;
	float maxY = 0.0f;
	float maxZ = 0.0f;

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

const unsigned Model::GetMeshCount() const
{
	return scene->mNumMeshes;
}

unsigned Model::GetMaterial() const
{
	return material;
}

float3 Model::GetCenter() const
{
	return center;
}
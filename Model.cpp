#include "Model.h"

Model::Model()
{}

Model::~Model()
{}

void Model::Load(const char* filename)
{
	scene = aiImportFile(filename, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene)
	{
		LoadMaterials();
		LoadMeshes();
	}
	else
	{
		LOG2("Error loading %s: %s", filename, aiGetErrorString());
	}
}

void Model::LoadMaterials()
{
	aiString file;

	materials.reserve(scene->mNumMaterials);

	for (unsigned i = 0; i < scene->mNumMaterials; ++i)
	{
		if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->GetTextures()->LoadTexture(file.data));
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
		mesh->CreateVAO();
	}
}

Mesh* Model::GetMesh() const
{
	return mesh;
}

vector<unsigned>& Model::GetMaterials()
{
	return materials;
}
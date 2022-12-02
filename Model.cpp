#include "Model.h"

Model::Model() : modelPath()
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

	materials.reserve(scene->mNumMaterials);

	if(scene->mNumMaterials == 1)
	{
		if (scene->mMaterials[0]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			App->GetTextures()->SetTexturePath(file.data);

			materials.push_back(App->GetTextures()->LoadTexture());
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

void Model::SetModelPath(char* modelPath)
{
	this->modelPath = modelPath;
}

Mesh* Model::GetMesh() const
{
	return mesh;
}

vector<unsigned>& Model::GetMaterials()
{
	return materials;
}
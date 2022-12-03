#pragma once

#include "Globals.h"
#include "Application.h"

#include "Mesh.h"

#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"

#include <vector>

using namespace std;

class Mesh;

class Model
{
	public:
		Model();
		~Model();

		void Load(const char* path = modelPath, const char* texturePath = nullptr);
		void LoadMeshes();
		void LoadMaterials(const char* path = modelPath, const char* texturePath = nullptr);

		Mesh* GetMesh() const;
		unsigned GetMaterial() const;
	private:
		static const char* modelPath;

		const aiScene *scene;
		Mesh *mesh;
		unsigned material;
};

#pragma once

#include "Globals.h"
#include "Application.h"

#include "Mesh.h"

#include "assimp/scene.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"

#include <windows.h>
#include <vector>
#include <regex>

using namespace std;

class Mesh;

class Model
{
	public:
		Model();
		~Model();

		void Load();
		void LoadMeshes();
		void LoadMaterials();

		void SetModelPath(const char* modelPath);

		Mesh* GetMesh() const;
		unsigned GetMaterial() const;
	private:
		const aiScene *scene;
		Mesh *mesh;
		unsigned material;
		const char* modelPath;
};

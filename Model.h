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

		void Load(const char *filename);
		void LoadMeshes();
		void LoadMaterials();
		Mesh* GetMesh() const;
		vector<unsigned>& GetMaterials();
	private:
		const aiScene *scene;
		Mesh *mesh;
		vector<unsigned> materials;
};

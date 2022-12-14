#pragma once

#include "Application.h"

#include <vector>

#include "glew.h"

#include "Math/float2.h"
#include "Math/float4x4.h"

#include "assimp/scene.h"
#include "assimp/mesh.h"

using namespace std;

class Mesh
{
	public:
		Mesh();
		~Mesh();

		void LoadVBO(const aiMesh* mesh);
		void LoadEBO(const aiMesh* mesh);
		void CreateVAO(const int & index);
		void Draw(const unsigned& model_texture, const float4x4& model);

		const unsigned GetNumVertices() const;
		const unsigned GetNumIndices() const;
		const unsigned GetNumFaces() const;

		float3 GetMaxProportions() const;

	private:
		const unsigned indices_per_face = 3;

		vector<unsigned> vbo, ebo, vao;
		unsigned num_vertices, num_indices, num_faces;
		unsigned total_vertices, total_indices, total_faces;

		float3 maxProportions;
};

#pragma once

#include "Application.h"

#include <vector>

#include "glew.h"

#include "Math/float2.h"
#include "Math/float4x4.h"

#include "assimp/scene.h"
#include "assimp/mesh.h"

class Mesh
{
	public:
		Mesh();
		~Mesh();

		void LoadVBO(const aiMesh* mesh);
		void LoadEBO(const aiMesh* mesh);
		void CreateVAO();
		void Draw(const std::vector<unsigned>& model_textures);

	private:
		const unsigned indices_per_face = 3;

		unsigned vbo, ebo, vao;
		unsigned num_vertices, num_indices;
};

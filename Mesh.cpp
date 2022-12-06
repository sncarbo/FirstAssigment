#include "Mesh.h"

Mesh::Mesh() : maxProportions(float3(0.0f, 0.0f, 0.0f))
{}

Mesh::~Mesh()
{}

void Mesh::LoadVBO(const aiMesh* mesh)
{
	unsigned vbo;

	App->AssimpLOG("Generating VBO.\n");

	glGenBuffers(1, &vbo);

	this->vbo.push_back(vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	unsigned vertex_size = (sizeof(float) * 3 + sizeof(float) * 2);
	unsigned buffer_size = vertex_size * mesh->mNumVertices;

	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);

	unsigned position_size = sizeof(float) * 3 * mesh->mNumVertices;

	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, mesh->mVertices);
	
	unsigned uv_offset = position_size;
	
	unsigned uv_size = sizeof(float) * 2 * mesh->mNumVertices;
	float2* uvs = (float2*)(glMapBufferRange(GL_ARRAY_BUFFER, uv_offset, uv_size, GL_MAP_WRITE_BIT));
	
	App->AssimpLOG("Adding Texture Coordinates.\n");

	for (unsigned i = 0; i < mesh->mNumVertices; ++i)
	{
		uvs[i] = float2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

		if (Abs(mesh->mVertices[i].x) > maxProportions[0])
			maxProportions[0] = mesh->mVertices[i].x;

		if (Abs(mesh->mVertices[i].y) > maxProportions[1])
			maxProportions[1] = mesh->mVertices[i].y;

		if (Abs(mesh->mVertices[i].z) > maxProportions[2])
			maxProportions[2] = mesh->mVertices[i].z;
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);

	num_vertices = mesh->mNumVertices;
}

void Mesh::LoadEBO(const aiMesh* mesh)
{
	unsigned ebo;

	App->AssimpLOG("Generating EBO.\n");

	glGenBuffers(1, &ebo);

	this->ebo.push_back(ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	unsigned index_size = sizeof(unsigned) * mesh->mNumFaces * indices_per_face;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);

	unsigned *indices = (unsigned*)(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));

	App->AssimpLOG("Assigning indices.\n");

	for (unsigned i = 0; i < mesh->mNumFaces; ++i)
	{
		assert(mesh->mFaces[i].mNumIndices == indices_per_face);

		*(indices++) = mesh->mFaces[i].mIndices[0];
		*(indices++) = mesh->mFaces[i].mIndices[1];
		*(indices++) = mesh->mFaces[i].mIndices[2];
	}

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	num_indices = mesh->mNumFaces * indices_per_face;
}

void Mesh::CreateVAO(int index)
{
	unsigned vao;

	App->AssimpLOG("Generating VAO.\n");

	glGenVertexArrays(1, &vao);

	this->vao.push_back(vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[index]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * num_vertices));
}

void Mesh::Draw(const unsigned& model_texture, const float4x4& model)
{
	unsigned program = App->GetRenderer()->GetProgram()->GetShaderProgramId();;
	const float4x4& view = App->GetCamera()->GetFrustum().ViewMatrix();
	const float4x4& proj = App->GetCamera()->GetFrustum().ProjectionMatrix();

	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, (const float*)&model);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, (const float*)&view);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, (const float*)&proj);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model_texture);

	glUniform1i(glGetUniformLocation(program, "diffuse"), 0);

	for (unsigned i = 0; i < vao.size(); ++i)
	{
		glBindVertexArray(vao[i]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);

		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, nullptr);
	}
}

float3 Mesh::GetMaxProportions() const
{
	return maxProportions;
}


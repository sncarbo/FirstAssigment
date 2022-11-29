#pragma once

#include "Globals.h"
#include "Module.h"


#include "glew.h"
#include "DirectXTex.h"

using namespace DirectX;

class ModuleTexture : public Module
{
	public:
		ModuleTexture();
		~ModuleTexture();

		bool Init();
		update_status Start();
		update_status Update();
		bool CleanUp();

		GLuint LoadTexture(const char* path);

		TexMetadata& GetInfo();

	private:
		const Image* texture;
		GLuint textureId;
		TexMetadata info;
};

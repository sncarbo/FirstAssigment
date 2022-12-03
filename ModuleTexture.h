#pragma once

#include "Globals.h"
#include "Module.h"

#include "glew.h"
#include "DirectXTex.h"

#include <string>

using namespace std;
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

		GLuint LoadTexture(const char * modelPath, const char* texturePath);

		TexMetadata& GetInfo();

	private:
		const Image* texture;
		GLuint textureId;
		TexMetadata info;
};

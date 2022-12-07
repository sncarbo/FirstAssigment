#pragma once

#include "Globals.h"
#include "Module.h"
#include "Application.h"

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

		void SetFlippedTexture(bool value);

		GLuint LoadTexture(const char * modelPath, const char* texturePath);

		TexMetadata& GetInfo();

	private:
		ScratchImage auxImage;
		const Image* texture;
		const char * texturePath;
		GLuint textureId;
		TexMetadata info;

		bool flippedTexture;
};

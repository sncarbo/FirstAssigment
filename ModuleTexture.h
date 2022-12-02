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

		GLuint LoadTexture();

		void SetTexturePath(char* texturePath);

		char* GetTexturePath() const;
		TexMetadata& GetInfo();

	private:
		const Image* texture;
		char* texturePath;
		GLuint textureId;
		TexMetadata info;
};

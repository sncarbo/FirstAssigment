#include "ModuleTexture.h"

ModuleTexture::ModuleTexture() : texture(nullptr)
{}

bool ModuleTexture::Init()
{
	return true;
}

update_status ModuleTexture::Start()
{
	return UPDATE_CONTINUE;
}

update_status ModuleTexture::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp()
{
	return true;
}

ModuleTexture::~ModuleTexture()
{}

GLuint ModuleTexture::LoadTexture(const char* path)
{
	wchar_t* wpath_t = new wchar_t[strlen(path) + 1];

	mbstowcs(wpath_t, path, strlen(path) + 1);

	ScratchImage auxImage;

	HRESULT hr = LoadFromDDSFile(wpath_t, DDS_FLAGS_NONE, &info, auxImage);

	if (SUCCEEDED(hr))
	{
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		ScratchImage flippedTexture;
		FlipRotate(auxImage.GetImages(), auxImage.GetImageCount(), auxImage.GetMetadata(), TEX_FR_FLIP_VERTICAL, flippedTexture);
		texture = flippedTexture.GetImage(0, 0, 0);
	}
	else
	{
		hr = LoadFromTGAFile(wpath_t, TGA_FLAGS_NONE, &info, auxImage);

		if (FAILED(hr))
			hr = LoadFromWICFile(wpath_t, WIC_FLAGS_NONE, &info, auxImage);
	}
	

	return textureId;
}

TexMetadata& ModuleTexture::GetInfo()
{
	return info;
}
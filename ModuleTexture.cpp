#include "ModuleTexture.h"

ModuleTexture::ModuleTexture() : texture(nullptr), textureId(-1)
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

GLuint ModuleTexture::LoadTexture(const char * modelPath, const char* texturePath)
{
	ScratchImage auxImage;

	LOG2("First check: Path described in the FBX");

	wchar_t* wpath_t = new wchar_t[strlen(texturePath) + 1];

	mbstowcs(wpath_t, texturePath, strlen(texturePath) + 1);

	HRESULT hr = LoadFromDDSFile(wpath_t, DDS_FLAGS_NONE, &info, auxImage);

	if (FAILED(hr))
	{
		hr = LoadFromTGAFile(wpath_t, TGA_FLAGS_NONE, &info, auxImage);

		if (FAILED(hr))
			hr = LoadFromWICFile(wpath_t, WIC_FLAGS_NONE, &info, auxImage);

		delete wpath_t;
		wpath_t = nullptr;
	}

	if (FAILED(hr))
	{
		LOG2("Second check: Same folder where the FBX is loaded");

		size_t lengthPath = strlen(modelPath);

		bool loop = true;
		
		while (loop)
		{
			if (modelPath[lengthPath - 1] == '/')
				loop = false;

			--lengthPath;
		}

		lengthPath += strlen(texturePath);

		char* path = new char(sizeof(lengthPath));

		lengthPath -= strlen(texturePath);

		memcpy(path, modelPath, lengthPath + 1);

		unsigned index = 0;

		while (texturePath[index] != '\0')
		{
			path[++lengthPath] = texturePath[index];
			++index;
		}
		
		wpath_t = new wchar_t;

		mbstowcs(wpath_t, "Models/Baker_house.png", lengthPath + 1);

		HRESULT hr = LoadFromDDSFile(wpath_t, DDS_FLAGS_NONE, &info, auxImage);

		if (FAILED(hr))
		{
			hr = LoadFromTGAFile(wpath_t, TGA_FLAGS_NONE, &info, auxImage);

			if (FAILED(hr))
				hr = LoadFromWICFile(wpath_t, WIC_FLAGS_NONE, &info, auxImage);
		}

		delete wpath_t;
		wpath_t = nullptr;
	}

	if (FAILED(hr))
	{
		LOG2("Third check: 'Textures/' folder");

		HRESULT hr = LoadFromDDSFile(wpath_t, DDS_FLAGS_NONE, &info, auxImage);

		if (FAILED(hr))
		{
			hr = LoadFromTGAFile(wpath_t, TGA_FLAGS_NONE, &info, auxImage);

			if (FAILED(hr))
				hr = LoadFromWICFile(wpath_t, WIC_FLAGS_NONE, &info, auxImage);
		}
	}

	if (SUCCEEDED(hr))
	{
		ScratchImage flippedTexture;
		FlipRotate(auxImage.GetImages(), auxImage.GetImageCount(), auxImage.GetMetadata(), TEX_FR_FLIP_VERTICAL, flippedTexture);
		texture = flippedTexture.GetImage(0, 0, 0);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		GLint internalFormat, format, type;

		switch (flippedTexture.GetMetadata().format)
		{
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:

		case DXGI_FORMAT_R8G8B8A8_UNORM:
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
			type = GL_UNSIGNED_BYTE;
			break;

		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:

		case DXGI_FORMAT_B8G8R8A8_UNORM:
			internalFormat = GL_RGBA8;
			format = GL_BGRA;
			type = GL_UNSIGNED_BYTE;
			break;
			case DXGI_FORMAT_B5G6R5_UNORM:
			internalFormat = GL_RGB8;
			format = GL_BGR;
			type = GL_UNSIGNED_BYTE;
			break;
		default:
			assert(false && "Unsupported format");
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texture->width, texture->height, 0, format, type, texture->pixels);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	
	return textureId;
}

TexMetadata& ModuleTexture::GetInfo()
{
	return info;
}
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
			else
				--lengthPath;
		}

		lengthPath += strlen(texturePath);

		char* path = new char[lengthPath + 1];
		path[lengthPath] = '\0';

		memcpy(path, modelPath, lengthPath - strlen(texturePath));

		unsigned index = 0;

		while (texturePath[index] != '\0')
		{
			path[lengthPath - strlen(texturePath) + index] = texturePath[index];
			++index;
		}

		wchar_t* wpath_t2 = new wchar_t[lengthPath + 1];

		mbstowcs(wpath_t2, path, lengthPath + 1);

		hr = LoadFromDDSFile(wpath_t2, DDS_FLAGS_NONE, &info, auxImage);

		if (FAILED(hr))
		{
			hr = LoadFromTGAFile(wpath_t2, TGA_FLAGS_NONE, &info, auxImage);

			if (FAILED(hr))
				hr = LoadFromWICFile(wpath_t2, WIC_FLAGS_NONE, &info, auxImage);
		}
	}

	if (FAILED(hr))
	{
		LOG2("Third check: 'Textures/' folder");

		const char* folderTextures = "Textures/";
		char* texturesPath = new char[strlen(folderTextures) + strlen(texturePath) + 1];
		texturesPath[strlen(folderTextures) + strlen(texturePath)] = '\0';

		for (unsigned i = 0; i < strlen(folderTextures); ++i)
			texturesPath[i] = folderTextures[i];

		for (unsigned i = strlen(folderTextures); i < (strlen(folderTextures) + strlen(texturePath)); ++i)
			texturesPath[i] = texturePath[i - strlen(folderTextures)];

		wchar_t* wpath_t3 = new wchar_t[strlen(texturesPath) + 1];

		mbstowcs(wpath_t3, texturesPath, strlen(texturesPath) + 1);

		hr = LoadFromDDSFile(wpath_t3, DDS_FLAGS_NONE, &info, auxImage);

		if (FAILED(hr))
		{
			hr = LoadFromTGAFile(wpath_t3, TGA_FLAGS_NONE, &info, auxImage);

			if (FAILED(hr))
				hr = LoadFromWICFile(wpath_t3, WIC_FLAGS_NONE, &info, auxImage);
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
#pragma once

#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleDebugDraw.h"
#include "ShadersProgram.h"
#include "Model.h"

#include "SDL.h"
#include "glew.h"
#include "Math/float4x4.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ShadersProgram;
class Model;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	void InitSDL();
	void InitGlew();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void RenderVBO(unsigned vbo, unsigned program);

	float4x4 GetModelMatrix() const;
	float4x4 GetViewMatrix() const;
	float4x4 GetProjectionMatrix() const;

	void WindowResized(unsigned width, unsigned height);
	void* GetContext();
	ShadersProgram* GetProgram();

private:
	void *context;
	int width, height;
	unsigned int VBO;
	ShadersProgram *program;
	Model *model;
};
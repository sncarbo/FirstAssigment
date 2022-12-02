#pragma once

#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "DebugDraw.h"
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
	void Draw();

private:
	const float square_grid_mins = -50.0f;
	const float square_grid_maxs = 50.0f;
	const float square_grid_y = 0.0f;
	const float square_grid_step = 1.0f;

	void *context;
	int width, height;
	unsigned int VBO;
	ShadersProgram *program;
	Model *model;
};
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

	void SetModel(const char * path);
	void SetTexture(const char* path);

	void SetSquareGridMins(const float& mins);
	void SetSquareGridMaxs(const float& maxs);
	void SetSquareGridY(const float& y);
	void SetSquareGridStep(const float& step);

	Model* GetModel() const;

	void WindowResized(const unsigned & width, const unsigned & height);
	void* GetContext();
	ShadersProgram* GetProgram() const;
	void Draw();

private:
	float square_grid_mins;
	float square_grid_maxs;
	float square_grid_y;
	float square_grid_step;

	void *context;
	int width, height;
	unsigned int VBO;
	ShadersProgram *program;
	Model *model;
};
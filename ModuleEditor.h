#pragma once

#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ShadersProgram.h"
#include "glew.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include <string>

class ModuleEditor : public Module
{
public:

	ModuleEditor();
	~ModuleEditor();

	bool Init();
	update_status Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	bool showCase;
};

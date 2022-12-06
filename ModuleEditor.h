#pragma once

#include "Globals.h"
#include "Module.h"
#include "Application.h"

#include "ShadersProgram.h"

#include "glew.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include <vector>
#include <string>

using namespace std;

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
	ImVec2 generalDisplayProportions;
	ImVec2 propertiesDisplayProportions;
	ImVec2 configurationDisplayProportions;
	ImVec2 assimpConsoleDisplayProportions;

	char fpsTitleBuffer[25];
	vector<float> fpsLog;

	bool showProperties;
	bool showConfiguration;
	bool showAssimpConsole;

	ImGuiIO io;
};

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

	void GeneralMenu();
	void ConfigurationWindow();
	void PropertiesWindow();
	void AssimpConsole();

private:
	update_status engineStatus;

	bool p_open_general;
	bool p_open_properties;
	bool p_open_configuration;
	bool p_open_console;
	bool p_open_about;

	ImGuiWindowFlags generalWindowFlags;
	ImGuiWindowFlags propertiesWindowFlags;
	ImGuiWindowFlags configurationWindowFlags;
	ImGuiWindowFlags consoleWindowFlags;

	char fpsTitleBuffer[25];
	vector<float> fpsLog;

	SDL_version compiledSDLVersion;
	SDL_version linkedSDLVersion;

	char* majorCompiledSDLVersion;
	char* minorCompiledSDLVersion;
	char* patchCompiledSDLVersion;
	char* majorLinkedSDLVersion;
	char* minorLinkedSDLVersion;
	char* patchLinkedSDLVersion;
	char * openGLVersion;
	char * CPUL1CacheLineSize;
	char * CPUCoresAvalaible;
	char * RAMComsuption;

	bool showProperties;
	bool showConfiguration;
	bool showAssimpConsole;

	ImGuiIO io;
};

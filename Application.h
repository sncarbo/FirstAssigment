#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleEditor.h"
#include "ModuleDebugDraw.h"
#include "ModuleTexture.h"

using namespace std;

class ModuleWindow;
class ModuleCamera;
class ModuleRender;
class ModuleTextures;
class ModuleInput;
class ModuleEditor;
class ModuleDebugDraw;
class ModuleTexture;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Start();
	update_status Update();
	bool CleanUp();

	ModuleWindow *GetWindow() const;
	ModuleCamera *GetCamera() const;
	ModuleEditor *GetEditor() const;
	ModuleRender *GetRenderer() const;
	ModuleInput *GetInput() const;
	ModuleDebugDraw *GetDebugDraw() const;
	ModuleTexture *GetTextures() const;

private:
	list<Module*> modules;

	ModuleWindow *window;
	ModuleCamera *camera;
	ModuleEditor *editor;
	ModuleRender *renderer;
	ModuleInput *input;
	ModuleDebugDraw *debugDraw;
	ModuleTexture *textures;
};

extern Application* App;

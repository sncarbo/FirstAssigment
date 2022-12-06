#include "Application.h"

using namespace std;

Application::Application()
{
	modules.push_back(window = new ModuleWindow());
	modules.push_back(input = new ModuleInput());
	modules.push_back(textures = new ModuleTexture());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(camera = new ModuleCamera());
	modules.push_back(debugDraw = new ModuleDebugDraw());
	modules.push_back(editor = new ModuleEditor());

	timer = new Timers();
	assimpLOG = string();
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

update_status Application::Start()
{
	update_status ret = UPDATE_CONTINUE;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Start();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	timer->StartSimpleTimer();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	deltaTime = timer->ReadSimpleTimer() / toSeconds;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}

ModuleWindow* Application::GetWindow() const
{
	return window;
}

ModuleCamera* Application::GetCamera() const
{
	return camera;
}

ModuleEditor* Application::GetEditor() const
{
	return editor;
}

ModuleRender* Application::GetRenderer() const
{
	return renderer;
}

ModuleInput* Application::GetInput() const
{
	return input;
}

ModuleDebugDraw* Application::GetDebugDraw() const
{
	return debugDraw;
}

ModuleTexture* Application::GetTextures() const
{
	return textures;
}

const float Application::GetSimpleDeltaTime() const
{
	return deltaTime;
}

const string Application::GetAssimpLOG() const
{
	return assimpLOG;

}

void Application::AssimpLOG(const char* log)
{
	if ((assimpLOG.size() + strlen(log) + 2) >= assimpLOG.max_size())
		assimpLOG.clear();

	assimpLOG.insert(0, "-");
	assimpLOG.insert(1, " ");
	assimpLOG.insert(2, log);
}

void Application::ClearAssimpLOG()
{
	assimpLOG.clear();
}
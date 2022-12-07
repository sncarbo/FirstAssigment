#pragma once
#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();
	virtual ~ModuleWindow();

	bool Init();
	update_status Update();
	bool CleanUp();

	void SetFullscreen(bool mode);
	void SetFullscreenDesktop(bool mode);
	void SetResizable(bool mode);

	float GetWidth() const;
	float GetHeight() const;

public:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_DisplayMode displayProportions;

	float width;
	float height;

	bool fullscreen;
	bool fullscreenDesktop;
	bool resizable;
};
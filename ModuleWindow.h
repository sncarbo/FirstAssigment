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
	bool CleanUp();

	float GetWidth() const;
	float GetHeight() const;

public:
	SDL_Window* window = NULL;
	SDL_Surface* screen_surface = NULL;

	float width;
	float height;
};
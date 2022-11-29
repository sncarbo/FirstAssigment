#include "ModuleWindow.h"

ModuleWindow::ModuleWindow() : width(SCREEN_WIDTH), height(SCREEN_HEIGHT)
{}

ModuleWindow::~ModuleWindow()
{}

bool ModuleWindow::Init()
{
	LOG2("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG2("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		width = SCREEN_WIDTH;
		height = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			LOG2("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{	
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

bool ModuleWindow::CleanUp()
{
	LOG2("Destroying SDL window and quitting all SDL systems");

	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
	return true;
}

float ModuleWindow::GetWidth() const
{
	return width;
}

float ModuleWindow::GetHeight() const
{
	return height;
}


#include "ModuleWindow.h"

ModuleWindow::ModuleWindow() : window(nullptr), screenSurface(nullptr), displayProportions(SDL_DisplayMode()),
								width(0.0f), height(0.0f), 
								fullscreen(false), fullscreenDesktop(false), resizable(true)
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
		if (SDL_GetDesktopDisplayMode(0, &displayProportions) == 0)
		{
			width = 3.0f * displayProportions.w / 4.0f;
			height = 3.0f * displayProportions.h / 4.0f;
		}
		else
		{
			width = SCREEN_WIDTH;
			height = SCREEN_HEIGHT;
		}

		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

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
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

update_status ModuleWindow::Update()
{
	SDL_GetWindowSize(window, (int*) &width, (int*) &height);

	return UPDATE_CONTINUE;
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

void  ModuleWindow::SetFullscreen(bool mode)
{
	fullscreen = mode;

	if (fullscreen)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	else
	{
		if(fullscreenDesktop)
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		else
			SDL_SetWindowFullscreen(window, 0);
	}
}

void  ModuleWindow::SetFullscreenDesktop(bool mode)
{
	fullscreenDesktop = mode;

	if (fullscreenDesktop)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		SDL_SetWindowFullscreen(window, 0);
}

void ModuleWindow::SetResizable(bool mode)
{
	resizable = mode;

	if (resizable)
		SDL_SetWindowResizable(window, SDL_TRUE);
	else
		SDL_SetWindowResizable(window, SDL_FALSE);
}

float ModuleWindow::GetWidth() const
{
	return width;
}

float ModuleWindow::GetHeight() const
{
	return height;
}


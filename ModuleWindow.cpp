#include "ModuleWindow.h"

ModuleWindow::ModuleWindow() : window(nullptr), screenSurface(nullptr), displayProportions(SDL_DisplayMode()),
								width(0.0f), height(0.0f)
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

float ModuleWindow::GetWidth() const
{
	return width;
}

float ModuleWindow::GetHeight() const
{
	return height;
}


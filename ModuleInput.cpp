#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "imgui_impl_sdl.h"

ModuleInput::ModuleInput() : keyboard(NULL), mouseWheel(0)
{}

ModuleInput::~ModuleInput()
{}

bool ModuleInput::Init()
{
	LOG2("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG2("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;

            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->GetRenderer()->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                break;

            case SDL_MOUSEBUTTONDOWN:
                break;

            case SDL_MOUSEBUTTONUP:
                break;

            case SDL_MOUSEMOTION:
                break;

            case SDL_MOUSEWHEEL:
                mouseWheel = sdlEvent.wheel.y;
                break;

        }
    }

    ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
    keyboard = SDL_GetKeyboardState(NULL);

    return UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp()
{
	LOG2("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

int ModuleInput::GetMouseWheel() const
{
    return mouseWheel;
}

bool ModuleInput::Scroll()
{
    return (mouseWheel != 0);
}

bool ModuleInput::CheckScanCode(int scancode)
{
    bool result = false;

    if (keyboard[scancode])
        result = true;

    return result;
}
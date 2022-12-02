#include "ModuleInput.h"

ModuleInput::ModuleInput() : keyboard(NULL), mouseDown(false), mouseMotion(false), 
                                mouseX(0.0), mouseY(0.0), mouseWheel(0), fileChange(false), 
                                fbxFile(nullptr), pngFile(nullptr), ddsFile(nullptr)
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
        if (sdlEvent.button.x != mouseX || sdlEvent.button.y != mouseY)
            mouseMotion = true;
        else
            mouseMotion = false;

        if (file != sdlEvent.drop.file)
            fileChange = true;
        else
            fileChange = false;

        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;

            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->GetRenderer()->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                break;

            case SDL_DROPFILE:
                if(sdlEvent.drop.file != nullptr){
                    string sFile = sdlEvent.drop.file;
                    const char* cFile = sFile.substr(sFile.length() - 4, sFile.length() - 1).c_str();

                    if(strcmp(cFile, ".fbx"))
                        fbxFile = sdlEvent.drop.file;
                    else if(strcmp(cFile, ".png"))
                        pngFile = sdlEvent.drop.file;
                    else if(strcmp(cFile, ".dds"))
                        ddsFile = sdlEvent.drop.file;
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                if (sdlEvent.button.button == SDL_BUTTON_RIGHT)
                    mouseDown = true;
                break;

            case SDL_MOUSEBUTTONUP:
                if(sdlEvent.button.button == SDL_BUTTON_RIGHT)
                    mouseDown = false;
                break;

            case SDL_MOUSEMOTION:
                mouseX = sdlEvent.button.x;
                mouseY = sdlEvent.button.y;
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

bool ModuleInput::GetMouseDown() const
{
    return mouseDown;
}

bool ModuleInput::GetMouseMotion() const
{
    return mouseMotion;
}

float ModuleInput::GetMouseX() const
{
    return mouseX;
}

float ModuleInput::GetMouseY() const
{
    return mouseY;
}

int ModuleInput::GetMouseWheel() const
{
    return mouseWheel;
}

bool ModuleInput::GetFileChange() const
{
    return fileChange;
}

char* ModuleInput::GetFile() const
{
    return file;
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
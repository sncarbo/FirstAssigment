#include "ModuleInput.h"

ModuleInput::ModuleInput() : keyboard(NULL), leftMouseDown(false), rightMouseDown(false),
                                mouseX(0.0), mouseY(0.0), mouseWheel(0), modelChange(false)
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

    mouseWheel = 0;
    mouseX = 0.0f;
    mouseY = 0.0f;
    modelChange = false;

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

            case SDL_DROPFILE:
                if(sdlEvent.drop.file != nullptr){
                    const char * sFile = sdlEvent.drop.file;
                    char* cFile = new char[strlen(sFile) + 1];
                    cFile[strlen(sFile)] = '\0';
                    memcpy(cFile, sFile, strlen(sFile));

                    for (unsigned i = 0; i < strlen(sFile); ++i)
                    {
                        if (sFile[i] == '\\')
                            cFile[i] = '/';
                        else
                            cFile[i] = sFile[i];
                    }

                    if (strcmp(&cFile[strlen(sFile) - 4], ".fbx") == 0)
                    {
                        App->GetRenderer()->SetModel(cFile);
                        modelChange = true;
                    }
                    else if(strcmp(&cFile[strlen(sFile) - 4], ".png") == 0)
                        App->GetRenderer()->SetTexture(cFile);
                    else if (strcmp(&cFile[strlen(sFile) - 4], ".jpg") == 0)
                        App->GetRenderer()->SetTexture(cFile);
                    else if(strcmp(&cFile[strlen(sFile) - 4], ".dds") == 0)
                        App->GetRenderer()->SetTexture(cFile);
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                if (sdlEvent.button.button == SDL_BUTTON_LEFT)
                    leftMouseDown = true;

                if (sdlEvent.button.button == SDL_BUTTON_RIGHT)
                    rightMouseDown = true;
                break;

            case SDL_MOUSEBUTTONUP:
                if (sdlEvent.button.button == SDL_BUTTON_LEFT)
                    leftMouseDown = false;

                if (sdlEvent.button.button == SDL_BUTTON_RIGHT)
                    rightMouseDown = false;
                break;

            case SDL_MOUSEMOTION:
                mouseX = sdlEvent.motion.xrel;
                mouseY = sdlEvent.motion.yrel;
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

bool ModuleInput::GetLeftMouseDown() const
{
    return leftMouseDown;
}

bool ModuleInput::GetRightMouseDown() const
{
    return rightMouseDown;
}

float ModuleInput::GetMouseX() const
{
    return mouseX;
}

float ModuleInput::GetMouseY() const
{
    return mouseY;
}

bool ModuleInput::GetMouseMotionX() const
{
    return (mouseX != 0.0);
}

bool ModuleInput::GetMouseMotionY() const
{
    return (mouseY != 0.0);
}

int ModuleInput::GetMouseWheel() const
{
    return mouseWheel;
}

bool ModuleInput::GetModelChange() const
{
    return modelChange;
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
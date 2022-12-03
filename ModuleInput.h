#pragma once

#include "Globals.h"
#include "Module.h"

#include "Application.h"

#include "SDL/include/SDL.h"
#include "imgui_impl_sdl.h"
#include <string>

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();

	bool GetMouseDown() const;
	bool GetMouseMotion() const;
	float GetMouseX() const;
	float GetMouseY() const;
	int GetMouseWheel() const;
	bool GetFileChange() const;
	char* GetFile() const;

	bool Scroll();

	bool CheckScanCode(int scancode);

private:
	const unsigned scrolling_up = 1;
	const unsigned scrolling_down = 2;

	const Uint8 *keyboard;
	bool mouseDown;
	bool mouseMotion;
	float mouseX, mouseY;
	int mouseWheel;
};
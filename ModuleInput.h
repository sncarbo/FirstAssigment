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

	void SetMouseMotionSensitivity(const float & value);
	void SetInverseMouse(bool value);

	bool GetLeftMouseDown() const;
	bool GetRightMouseDown() const;
	float GetMouseX() const;
	float GetMouseY() const;
	bool GetMouseMotionX() const;
	bool GetMouseMotionY() const;
	int GetMouseWheel() const;
	bool GetModelChange() const;

	bool Scroll();

	bool CheckScanCode(const int & scancode);

private:
	const unsigned scrolling_up = 1;
	const unsigned scrolling_down = 2;

	const Uint8 *keyboard;
	bool leftMouseDown;
	bool rightMouseDown;
	float mouseX, mouseY;
	int mouseWheel;

	float mouseMotionSensitivity;
	int inverseMouse;

	bool modelChange;
};
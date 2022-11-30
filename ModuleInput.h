#pragma once
#include "Module.h"
#include "Globals.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();

	int GetMouseWheel() const;

	bool Scroll();

	bool CheckScanCode(int scancode);

private:
	const unsigned scrolling_up = 1;
	const unsigned scrolling_down = 2;

	const Uint8 *keyboard;
	int mouseWheel;
};
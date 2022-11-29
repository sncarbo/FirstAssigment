#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleDummy : public Module
{
	bool Init()
	{
		LOG2("Dummy Init!");
		return true;
	}

	bool CleanUp()
	{
		LOG2("Dummy CleanUp!");
		return true;
	}
};
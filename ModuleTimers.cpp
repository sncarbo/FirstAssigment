#include "ModuleTimers.h"

ModuleTimers::ModuleTimers():quitSimpleTimer(true), simpleTimer(0), quitPerformanceTimer(true), performanceTimer(0.0) {}

ModuleTimers::~ModuleTimers() {}

void ModuleTimers::StartSimpleTimer()
{
	quitSimpleTimer = false;
}

Uint32 ModuleTimers::ReadSimpleTimer()
{
	if(!quitSimpleTimer)
		simpleTimer = SDL_GetTicks();

	return simpleTimer;
}

void ModuleTimers::StopSimpleTimer()
{
	quitSimpleTimer = true;
}

Uint64 ModuleTimers::ReadPerformanceFrequency()
{
	return SDL_GetPerformanceFrequency();
}

void ModuleTimers::StartPerformanceTimer()
{
	quitPerformanceTimer = false;
}

Uint64 ModuleTimers::ReadPerformanceTimer()
{
	if (!quitPerformanceTimer)
		performanceTimer = SDL_GetPerformanceCounter();

	return performanceTimer;
}

void ModuleTimers::StopPerformanceTimer()
{
	quitPerformanceTimer = true;
}
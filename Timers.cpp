#include "Timers.h"

Timers::Timers():quitSimpleTimer(true), startSimpleTimer(0), lastSimpleTimer(0),
					quitPerformanceTimer(true), startPerformanceTimer(0.0), lastPerformanceTimer(0.0)
{}

Timers::~Timers() {}

void Timers::StartSimpleTimer()
{
	startSimpleTimer = SDL_GetTicks();
	quitSimpleTimer = false;
}

Uint32 Timers::ReadSimpleTimer()
{
	if(!quitSimpleTimer)
		lastSimpleTimer = SDL_GetTicks() - startSimpleTimer;

	return lastSimpleTimer;
}

void Timers::StopSimpleTimer()
{
	quitSimpleTimer = true;
}

Uint64 Timers::ReadPerformanceFrequency()
{
	return SDL_GetPerformanceFrequency();
}

void Timers::StartPerformanceTimer()
{
	startPerformanceTimer = SDL_GetPerformanceCounter();
	quitPerformanceTimer = false;
}

Uint64 Timers::ReadPerformanceTimer()
{
	if (!quitPerformanceTimer)
		lastPerformanceTimer = SDL_GetPerformanceCounter() - startPerformanceTimer;

	return lastPerformanceTimer;
}

void Timers::StopPerformanceTimer()
{
	quitPerformanceTimer = true;
}
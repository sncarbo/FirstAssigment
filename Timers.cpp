#include "Timers.h"

Timers::Timers():quitSimpleTimer(true), simpleTimer(0), quitPerformanceTimer(true), performanceTimer(0.0) {}

Timers::~Timers() {}

void Timers::StartSimpleTimer()
{
	quitSimpleTimer = false;
}

Uint32 Timers::ReadSimpleTimer()
{
	if(!quitSimpleTimer)
		simpleTimer = SDL_GetTicks();

	return simpleTimer;
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
	quitPerformanceTimer = false;
}

Uint64 Timers::ReadPerformanceTimer()
{
	if (!quitPerformanceTimer)
		performanceTimer = SDL_GetPerformanceCounter();

	return performanceTimer;
}

void Timers::StopPerformanceTimer()
{
	quitPerformanceTimer = true;
}
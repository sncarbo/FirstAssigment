#pragma once

#include "Module.h"
#include "SDL.h"

class ModuleTimers : Module
{
public:
	ModuleTimers();
	~ModuleTimers();

	void StartSimpleTimer();
	Uint32 ReadSimpleTimer();
	void StopSimpleTimer();

	static Uint64 ReadPerformanceFrequency();

	void StartPerformanceTimer();
	Uint64 ReadPerformanceTimer();
	void StopPerformanceTimer();

private:
	bool quitSimpleTimer;
	bool quitPerformanceTimer;
	Uint32 simpleTimer;
	Uint64 performanceTimer;
};
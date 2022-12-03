#pragma once

#include "SDL.h"

class Timers
{
public:
	Timers();
	~Timers();

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

	Uint32 startSimpleTimer;
	Uint32 lastSimpleTimer;

	Uint64 startPerformanceTimer;
	Uint64 lastPerformanceTimer;
};
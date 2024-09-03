#pragma once

#include <windows.h>
#include <winnt.h>

NAMESPACE_OPEN(GEngine)

class Time
{
public:
	G_ENGINE_CORE_API static float deltaTime() { return s_deltaTime; }

public:
	G_ENGINE_CORE_API static void Init();
	G_ENGINE_CORE_API static void Update();
private:
	static LARGE_INTEGER s_cpuFrequency;
	static LARGE_INTEGER s_prevFrequency;
	static LARGE_INTEGER s_currentFrequency;

	static float s_deltaTime;
};

NAMESPACE_CLOSE


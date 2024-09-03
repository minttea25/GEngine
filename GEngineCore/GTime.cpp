#include "pch.h"
#include "GTime.h"

NAMESPACE_OPEN(GEngine)

LARGE_INTEGER Time::s_cpuFrequency = {};
LARGE_INTEGER Time::s_prevFrequency = {};
LARGE_INTEGER Time::s_currentFrequency = {};
float Time::s_deltaTime = 0.0f;

 void Time::Init()
{
	// cpu natural frequency
	QueryPerformanceFrequency(&s_cpuFrequency);

	// frequency since app starts
	QueryPerformanceCounter(&s_prevFrequency);
}

 void Time::Update()
{
	QueryPerformanceCounter(&s_currentFrequency);

	LONGLONG dFrequency = s_currentFrequency.QuadPart - s_prevFrequency.QuadPart;

	// Update deltaTime
	s_deltaTime = static_cast<float>(dFrequency) / s_cpuFrequency.QuadPart;

	// Update prev frequency
	s_prevFrequency.QuadPart = s_currentFrequency.QuadPart;
}

NAMESPACE_CLOSE
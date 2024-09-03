#pragma once

#include "CoreMacro.h"

class G_ENGINE_CORE_API Test
{
public:
	static constexpr int Add(const int a, const int b) { return a + b; }
	static constexpr int Sub(const int a, const int b) { return a - b; }
};


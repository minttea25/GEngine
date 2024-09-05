#pragma once

#include "CoreHeader.h"
#include "Component.h"

NAMESPACE_OPEN(GEngine)

class G_ENGINE_CORE_API Behaviour : public Component
{
public:
	Behaviour() {}
	virtual ~Behaviour() {}

	// TODO : internal call
	//bool enabled() { return true; }
	//bool isActive() { return true; }
};

NAMESPACE_CLOSE

